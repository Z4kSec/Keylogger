#ifndef UNIXOPENSSL_H_
# define UNIXOPENSSL_H_

#include <iostream>
#include <string>
#include <sstream>
#include <openssl/x509.h>

#include <openssl/crypto.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <openssl/bio.h>
#include <poll.h>

# define NAME_KEY "./spider_server.pem"
# define NAME_KEY_PRIV "./spider_server.key"

typedef	struct pollfd	t_pollfds;

struct	t_structFD
{
  t_pollfds	pollfds;
  BIO		*bio;
  SSL		*ssl;
};


class UnixOpenssl
{
public:
  UnixOpenssl(int port);
  ~UnixOpenssl();

  void	initOpenssl();
  void	acceptConnection(t_structFD & structFD);
  void	initBIO();
  void	initCTX();

  void	loadCertif();

  void	sSend(t_structFD & structFD, std::string const & msg);
  int	sReicv(t_structFD & structFD, void *msg, size_t size);

//  void	setSock(int sock);
  int	getPort() const;
//  int	getSock() const;

private:

  int		_port;
  BIO		*_bioPort;
  SSL_CTX	*_ctx;

};

#endif /* !UNIXOPENSSL_H_ */
