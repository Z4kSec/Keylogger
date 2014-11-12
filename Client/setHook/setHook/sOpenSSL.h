#pragma once

#include <string>
#include <iostream>
#include <winsock2.h>
#include <windows.h>

#include <openssl/x509.h>

#include <openssl/crypto.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <openssl/bio.h>

#define DATA_BUFSIZE 4096 // MIN struct s_HeaderDataForPacket+1 (53)
#define NAME_KEY "ca.pem"
#define HEADER_SIZE sizeof(sSocket::s_HeaderDataForPacket)

class sOpenssl
{
public:
	sOpenssl();
	~sOpenssl();

	void	initOpenSSL();
	bool	initCrypted();
	bool	initBioConnection(const std::string & addrIP, const std::string & port);

	bool	sendMsg(const void * msg, size_t size) const;
	bool	receivMsg(char* msg);

	SSL_CTX	*getCTX() const;
	BIO		*getBIO() const;

	void	setIsConnected(bool set);
	bool	isConnected() const;

	typedef struct				s_HeaderDataForPacket
	{
		char					idClient[32];
		char					magicKey[8];
		unsigned short			globalSize;
		unsigned short			dataSize;
		unsigned int			nbPacket;
		unsigned int			numPacket;
	}							t_HeadData;

private:

	bool		_isConnected;

	SSL_CTX	*_ctx;
	BIO		*_bio;
};

