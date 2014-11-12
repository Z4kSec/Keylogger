#include "sOpenssl.h"

sOpenssl::sOpenssl()
	: _isConnected(true)
{ 
	_ctx = NULL;
	_bio = NULL;
	initOpenSSL();
}


sOpenssl::~sOpenssl()
{
	if (_ctx)
		SSL_CTX_free(_ctx);
	if (_bio)
		BIO_free(_bio);
}

void	sOpenssl::initOpenSSL()
{
	ERR_load_BIO_strings();
	OpenSSL_add_all_algorithms();
	SSL_load_error_strings();
	SSL_library_init();
}

bool	sOpenssl::initCrypted()
{
	const SSL_METHOD *method;

	if ((method = SSLv23_client_method()) == NULL)
		return false;
	if ((_ctx = SSL_CTX_new(method)) == NULL)
		return false;
	if (SSL_CTX_load_verify_locations(_ctx, NAME_KEY, "./") == 0)
		return false;
	return true;
}

bool	sOpenssl::initBioConnection(const std::string & addrIP, const std::string & port)
{
	_bio = BIO_new_ssl_connect(_ctx);
	const std::string adrrIP_Port(addrIP + ":" + port);
	BIO_set_conn_hostname(_bio, adrrIP_Port.c_str());
	if (BIO_do_connect(_bio) < 1)
		return false;
	return true;
}

bool	sOpenssl::sendMsg(const void *msg, size_t size) const
{
	BIO_write(_bio, msg, (int)size);
	return true;
}

bool	sOpenssl::receivMsg(char* msg)
{
	t_HeadData head;

	BIO_read(_bio, &head, sizeof(head));
	BIO_read(_bio, msg, DATA_BUFSIZE);
	return true;
}

SSL_CTX	*sOpenssl::getCTX() const
{
	return _ctx;
}

BIO	*sOpenssl::getBIO() const
{
	return _bio;
}

void	sOpenssl::setIsConnected(bool set)
{
	_isConnected = set;
}

bool sOpenssl::isConnected() const
{
	return _isConnected;
}
