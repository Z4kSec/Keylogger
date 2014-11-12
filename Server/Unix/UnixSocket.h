/*
** UnixSocket.h for  in /home/ouroub_a/rendu/spider-2017-krier_g/PSocket/PSocket
**
** Made by amina ourouba
** Login   <ouroub_a@epitech.net>
**
** Started on  Sun Oct 26 11:58:15 2014 amina ourouba
** Last update Sun Nov  9 17:25:48 2014 amina ourouba
*/

#pragma once

#include <map>
#include <vector>
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h>
#include <poll.h>

#include "IPSocket.h"

const std::string NEW_CLIENT = "NEW_CLIENT";
const std::string CLOSED_SOCKET = "CLOSED_SOCKET";
const unsigned int ID_CLIENT_SIZE = 32;
const unsigned int MAGIC_KEY_SIZE = 8;

typedef	std::vector<std::pair<std::string, t_structFD> >::iterator	t_pollfds_iterator;


class UnixSocket
: public IPSocket,
  public UnixOpenssl
{
private:
  int							_port;
  struct sockaddr_in					_sockAddr;
  std::map<int, std::vector<std::string> >		_dataBufArr;
  std::vector<std::pair<std::string, t_structFD> >	_socketsFds;
  int		_sock;

private:
  virtual bool			sBind();
  virtual bool			sListen();
  virtual bool			sAccept();
  std::vector<t_pollfds>	fdsActions();

public:
  typedef struct	s_header
  {
    char		id_client[ID_CLIENT_SIZE];
    char		magic_key[MAGIC_KEY_SIZE];
    unsigned short	size_total;
    unsigned short	size_data;
    unsigned int	nb_packets;
    unsigned int	num_packet;
  }			t_header;
  typedef struct	s_header_clean
  {
    char		id_client[ID_CLIENT_SIZE + 1];
    char		magic_key[MAGIC_KEY_SIZE + 1];
    unsigned short	size_total;
    unsigned short	size_data;
    unsigned int	nb_packets;
    unsigned int	num_packet;
  }			t_header_clean;
  std::map<int, t_header_clean> _headers;

  UnixSocket(int &port);
  virtual		~UnixSocket();
  virtual bool		sCreate();
  void			sSelect();
  virtual std::string	sRecv(t_structFD &structFD);
  bool			readHeader(UnixSocket::t_header &h, t_header_clean &cleanHdr);
  virtual bool		sSend(const int &socket, std::string cmd);
  std::map<int, std::vector<std::string> > getDataBufArr() const;
  std::map<int, t_header_clean> getHeaders() const;
  virtual void		sDelete(int &socket);
};
