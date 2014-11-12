#include "UnixOpenssl.h"
#include "Exception.h"

UnixOpenssl::UnixOpenssl(int port)
  : _port(port)
{
  _ctx = 0;
//  _bioPort = 0;
  initOpenssl();
  initCTX();
  loadCertif();
//  initBIO();
}

UnixOpenssl::~UnixOpenssl()
{
  if (_ctx)
    SSL_CTX_free(_ctx);
//  if (_bioPort)
//    BIO_free(_bioPort);
}

void	UnixOpenssl::initOpenssl()
{
  std::cout << "initOpenssl" << std::endl;
  SSL_library_init();
  OpenSSL_add_all_algorithms();
  SSL_load_error_strings();
  ERR_load_crypto_strings();
  ERR_load_SSL_strings();
//  ERR_load_BIO_strings();
}

void	UnixOpenssl::acceptConnection(t_structFD & structFD)
{
  std::cout << "acceptConnection" << std::endl;
/*
  if (BIO_do_accept(_bioPort) <= 0)
    if (BIO_do_accept(_bioPort) <= 0)
      if (BIO_do_accept(_bioPort) <= 0)
      {
	ERR_print_errors_fp(stderr);
	throw Exception(__LINE__ - 5, __FILE__, __FUNCTION__, "Error accepting connection");
      }

  structFD.bio = BIO_pop(_bioPort);
  if (BIO_get_fd(structFD.bio, &structFD.pollfds.fd) < 0)
    throw Exception(__LINE__ - 1, __FILE__, __FUNCTION__, "Error get fd problem");
  std::cout << "COnnection accept" << std::endl;
  */
//  throw Exception(__LINE__ - 1, __FILE__, __FUNCTION__, "NICKEL");

//  SSL	*ssl;

  std::cout << "Go connection" << std::endl;
  structFD.ssl = SSL_new(_ctx);
  SSL_set_fd(structFD.ssl, structFD.pollfds.fd);
  if (SSL_accept(structFD.ssl) == 0)
    throw Exception(__LINE__, __FILE__, __FUNCTION__,
		    "ERROR : SSL_accept return NULL");
//  if ((SSL_get_peer_certificate(ssl)) == NULL)
//    std::cout << "WARNING : No certificates\n" << std::endl;
//  std::cout << "Init ssl ok" << std::endl;
//  return ssl;

}

void	UnixOpenssl::initBIO()
{
/*
  std::ostringstream conv;

  std::cout << "initBIO" << std::endl;
  conv << _port;
  _bioPort = BIO_new_accept((char *)(conv.str()).c_str());
  if (BIO_do_accept(_bioPort) <= 0)
    throw Exception(__LINE__ - 1, __FILE__, __FUNCTION__, "Error BIO_do_accept");
  if (BIO_get_fd(_bioPort, &_sock) < 0)
    throw Exception(__LINE__ - 1, __FILE__, __FUNCTION__, "Error BIO_get_fd");
*/
}

void	UnixOpenssl::initCTX()
{
  SSL_METHOD *method;

    std::cout << "initCTX" << std::endl;
  if ((method = (SSL_METHOD *)SSLv23_server_method()) == NULL)
    throw Exception(__LINE__ - 1, __FILE__, __FUNCTION__, "Error SSLv23_server_method");
  if ((_ctx = SSL_CTX_new(method)) == NULL)
    throw Exception(__LINE__ - 1, __FILE__, __FUNCTION__, "Error SSL_CTX_new");
  /*SSL_CTX_set_verify(_ctx, SSL_VERIFY_PEER | SSL_VERIFY_CLIENT_ONCE, NULL);
  SSL_CTX_set_verify_depth(_ctx, 1);
  SSL_CTX_set_session_cache_mode(_ctx, SSL_SESS_CACHE_OFF);*/
}

void	UnixOpenssl::loadCertif()
{
  std::cout << "loadCertif" << std::endl;
  //if ((SSL_CTX_load_verify_locations(_ctx, NAME_KEY, "./")) == 0)
  //  throw Exception(__LINE__ - 1, __FILE__, __FUNCTION__, "Error SSL_CTX_load_verify_location");
  if (SSL_CTX_use_certificate_file(_ctx, NAME_KEY, SSL_FILETYPE_PEM) != 1)
    throw Exception(__LINE__ - 1, __FILE__, __FUNCTION__, "Error SSL_CTX_use_certificate_chain_file");
  if (SSL_CTX_use_PrivateKey_file(_ctx, NAME_KEY_PRIV, SSL_FILETYPE_PEM) != 1)
    throw Exception(__LINE__ - 1, __FILE__, __FUNCTION__, "Error SSL_CTX_use_PrivateKey_file");
  if (!SSL_CTX_check_private_key(_ctx))
    throw Exception(__LINE__ - 1, __FILE__, __FUNCTION__, "Error SSL_CTX_check_private_key");
//  if ((SSL_CTX_load_verify_locations(_ctx, NAME_KEY, "./")) == 0)
//    throw Exception(__LINE__ - 1, __FILE__, __FUNCTION__, "Error SSL_CTX_load_verify_location");
}

void	UnixOpenssl::sSend(t_structFD & structFD, std::string const & msg)
{
  if (SSL_write(structFD.ssl, msg.c_str(), msg.size()) < 0)
      std::cout << "WARNING : SL_write return FAIL" << std::endl;
//  if (BIO_write(structFD.bio, msg.c_str(), msg.size()) < 0)
//      std::cout << "WARNING : SL_write return FAIL" << std::endl;
}

int	UnixOpenssl::sReicv(t_structFD & structFD, void *msg, size_t size)
{
  return (SSL_read(structFD.ssl, msg, size));
//  return (BIO_read(structFD.bio, msg, size));
}

/*
void	UnixOpenssl::setSock(int sock)
{
  _sock = sock;
}
*/


int	UnixOpenssl::getPort() const
{
  return _port;
}
/*
int	UnixOpenssl::getSock() const
{
  return _sock;
}
*/
