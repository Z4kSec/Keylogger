#pragma once

#include <string>
#include <iostream>
#include <stdlib.h>

#include "sOpenSSL.h"

// DATA_BUFSIZE, define the BSON data max size
#define WIN32_LEAN_AND_MEAN

class sSocket
	: public sOpenssl
{
public:
	sSocket(std::string const & addrIP, std::string const & port);
	~sSocket();

	bool sClose(SOCKET sock);
	bool sRecv(char *data);

	bool sSocket::sSend(const void *msg_send, size_t size) const;
	bool sSend(std::string const & msg_send) const;

private:

	/*
	** Atribut
	*/
	const std::string	_addrIP;
	const std::string	_port;
};