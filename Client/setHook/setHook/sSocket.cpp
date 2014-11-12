// #pragma warning(disable : 4996)
#include "sSocket.h"

/*
** Initialize
*/

sSocket::sSocket(std::string const & addrIP, std::string const & port)
	: sOpenssl(), _addrIP(addrIP), _port(port)
{
	initCrypted();
	initBioConnection(addrIP, port);
}

/*
** Destroy
*/

sSocket::~sSocket()
{
}

/*
** Communication
*/

bool sSocket::sRecv(char *data)
{
	return receivMsg(data);
}

bool sSocket::sSend(const void *msg_send, size_t size) const
{
	return sendMsg(msg_send, size);
	return true;
}

bool sSocket::sSend(std::string const & msg_send) const
{
	return sendMsg((void *)msg_send.c_str(), msg_send.size() + 1);
}
