#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <time.h>
#include <string.h>
#include <algorithm>

#include "sJson.h"
#include "sSocket.h"

#define MAGIC_KEY "SPIDER42"


typedef std::vector<std::string> VSListPackets;

class Handling
	: public sJson,
	public sSocket
{
public:
	Handling(std::string const & addrIP, std::string const & port);
	~Handling();

	void	doPackets(std::string const & buffer);
	void	sendPackets();

	void	sendStartUp(std::string const & userName = "nothing",
		std::string const & hostName = "0.0.0.0",
		std::string const & userRights = "admin");
	void	sendAnswerCommand(std::string const & cmd, std::string const & ret, std::string const & time);


private:

	void		doData(std::string const & buffer, unsigned int & cpt);
	char*		getGUID();
	s_HeaderDataForPacket _header;
};

