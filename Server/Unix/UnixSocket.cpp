//
// UnixSocket.cpp for  in /home/ouroub_a/rendu/spider-2017-krier_g/PSocket/PSocket
//
// Made by amina ourouba
// Login   <pouyet_j@epitech.net>
//
// Started on  Thu Oct 16 17:28:51 2014 jeremy pouyet
// Last update Sun Nov  9 17:30:00 2014 amina ourouba
//

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include <sstream>
#include <algorithm>
#include <cstring>
#include <cerrno>
#include <poll.h>
#include <vector>
#include "Server.h"
#include "Exception.h"
#include "UnixSocket.h"

UnixSocket::UnixSocket(int &port)
  : UnixOpenssl(port)
{
}

bool					UnixSocket::sCreate()
{
  std::pair<std::string, t_structFD>	first_fd;
  struct protoent			*s_sock;
  int					opt;

  opt = 1;
  s_sock = getprotobyname("TCP");
  if ((_sock = socket(AF_INET, SOCK_STREAM, s_sock->p_proto)) == -1)
    throw Exception(__LINE__ - 1, __FILE__, __FUNCTION__, strerror(errno));
  if (setsockopt(_sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)))
    throw Exception(__LINE__ - 1, __FILE__, __FUNCTION__, strerror(errno));
  std::cout << "Successfully created socket " << _sock << "." << std::endl;
  this->sBind();
  this->sListen();

  first_fd.first = std::string("127.0.0.1");
  first_fd.second.pollfds.fd = _sock;
  first_fd.second.pollfds.events = POLLIN;
  _socketsFds.push_back(first_fd);
  return (true);
}

UnixSocket::~UnixSocket()
{
  t_pollfds_iterator	it;

  for (it = _socketsFds.begin(); it != _socketsFds.end(); ++it)
  {
    if (close(it->second.pollfds.fd) == -1)
      throw Exception(__LINE__ - 1, __FILE__, __FUNCTION__, strerror(errno));
  }
  std::cout << "Successfully closed socket." << std::endl;
}

bool UnixSocket::sBind()
{
  _sockAddr.sin_family = AF_INET;
  _sockAddr.sin_addr.s_addr = INADDR_ANY;
  _sockAddr.sin_port = htons(getPort());

  if (bind(_sock, (sockaddr *)&_sockAddr, sizeof(_sockAddr)) == -1)
    throw Exception(__LINE__ - 1, __FILE__, __FUNCTION__, strerror(errno));
  std::cout << "Successfully associated socket to address." << std::endl;
  return (true);
}

bool UnixSocket::sListen()
{
  if (listen(_sock, 42) == -1)
    throw Exception(__LINE__ - 1, __FILE__, __FUNCTION__, strerror(errno));
  std::cout << "Successfully listening on socket " << _sock << "." << std::endl;
  return (true);
}

std::vector<t_pollfds>		UnixSocket::fdsActions()
{
  t_pollfds_iterator		it;
  std::vector<t_pollfds>	pollfds;

  for (it = _socketsFds.begin(); it != _socketsFds.end(); ++it)
  {
    (_dataBufArr[it->second.pollfds.fd]).clear();
    it->second.pollfds.events = POLLIN | POLLRDHUP;
    pollfds.push_back(it->second.pollfds);
  }
  return (pollfds);
}

void				 	UnixSocket::sSelect()
{
  std::vector<t_pollfds>::iterator	it;
  std::vector<t_pollfds>		fdsArr;
  int cpt;

  fdsArr = this->fdsActions();
  if (poll(fdsArr.data(), _socketsFds.size(), 10000) < 0)
    throw Exception(__LINE__, __FILE__, __FUNCTION__, strerror(errno));
  for (cpt = 0, it = fdsArr.begin(); it != fdsArr.end(); ++it, ++cpt)
  {
    if (it->revents & POLLRDHUP)
      this->sDelete(it->fd);
    else if (it->revents & POLLIN)
      this->sRecv(_socketsFds.at(cpt).second);
  }
}

bool					UnixSocket::sAccept()
{
  std::pair<std::string, t_structFD>	newClientSocket;
  socklen_t				cliLen;
  struct sockaddr_storage		addr;
  struct sockaddr_in			*s = (struct sockaddr_in *)&addr;
  char					ipstr[INET6_ADDRSTRLEN];
  std::vector<std::string>		vec;

  cliLen = sizeof(_sockAddr);
  newClientSocket.second.pollfds.fd = accept(_sock, (struct sockaddr *)&_sockAddr, &cliLen);
  acceptConnection(newClientSocket.second);
  if (newClientSocket.second.pollfds.fd == -1)
    throw Exception(__LINE__ - 2, __FILE__, __FUNCTION__, strerror(errno));
  this->_socketsFds.push_back(newClientSocket);
  cliLen = sizeof(addr);
  getpeername(newClientSocket.second.pollfds.fd, (struct sockaddr*)&addr, &cliLen);
  if (addr.ss_family == AF_INET)
    inet_ntop(AF_INET, &s->sin_addr, ipstr, sizeof(ipstr));
  newClientSocket.first = std::string(ipstr);
  std::cout << "Accepting new connexion from " << ipstr << std::endl;
  this->_dataBufArr[newClientSocket.second.pollfds.fd] = vec;
  return (true);
}

void				UnixSocket::sDelete(int &socket)
{
  int				i;
  t_pollfds_iterator		it;

  for (i = 0, it = _socketsFds.begin(); it != _socketsFds.end(); ++i, ++it)
    if (it->second.pollfds.fd == socket)
    {
      if (it->second.bio)
	BIO_free(it->second.bio);
      break;
    }
  _socketsFds.erase(_socketsFds.begin() + i);
  _dataBufArr.erase(socket);
  _headers.erase(socket);
  if (close(socket) == -1)
    std::cerr << "Error while closing socket: " << strerror(errno) << std::endl;
}

bool		UnixSocket::readHeader(UnixSocket::t_header &h, t_header_clean &cleanHdr)
{
  std::string		condition;

  std::copy(h.id_client, h.id_client + ID_CLIENT_SIZE, cleanHdr.id_client);
  cleanHdr.id_client[ID_CLIENT_SIZE] = 0;
  std::copy(h.magic_key, h.magic_key + MAGIC_KEY_SIZE, cleanHdr.magic_key);
  cleanHdr.magic_key[MAGIC_KEY_SIZE] = 0;

  std::cout << "hdr cleaned : " << cleanHdr.id_client << std::endl;
  if ((std::string(cleanHdr.id_client)).length() < 32)
  {
    std::cout << "bad header" << std::endl;
    return (false);
  }
  if (std::string(cleanHdr.magic_key) != MAGIC_KEY)
  {
    std::cout << "bad key " << cleanHdr.magic_key << std::endl;
    return (false);
  }
  cleanHdr.size_total = h.size_total;
  cleanHdr.size_data = h.size_data;
  cleanHdr.nb_packets = h.nb_packets;
  cleanHdr.num_packet = h.num_packet;
  return (true);
}

std::string			UnixSocket::sRecv(t_structFD &structFD)
{
//  int				r;
  char				buf[BUFFSIZE - HEADER_SIZE];
  t_header			header;
  t_header_clean		cleanHdr;
  int				rReicv;

  if (structFD.pollfds.fd == _sock)
  {
    this->sAccept();
    return (std::string(NEW_CLIENT));
  }
  std::cout << "reading" << std::endl;
  rReicv = sReicv(structFD, &header, sizeof(t_header));
  std::cout << "read" << std::endl;
  if (rReicv == 0)
    return (std::string(""));
  if (rReicv == -1)
  {
    this->sDelete(structFD.pollfds.fd);
    return (std::string(""));
  }
//  if ((r = recv(structFD.pollfds.fd, &header, sizeof(t_header), 0)) < 0)
//    std::cerr << "And error occured while receiving data: " << strerror(errno) << std::endl;
//  if (r == 0)
//  {
//    sSSL_free()
//    this->sDelete(structFD.pollfds.fd);
//    return (std::string(""));
//  }
  if (this->readHeader(header, cleanHdr))
  {
    this->_headers[structFD.pollfds.fd] = cleanHdr;
    rReicv = sReicv(structFD, buf, cleanHdr.size_data + 1);
    if (rReicv == 0)
      return (std::string(""));
    if (rReicv == -1)
    {
      this->sDelete(structFD.pollfds.fd);
      return (std::string(""));
    }
    std::cout << std::endl << buf << std::endl;
//    if ((r = recv(structFD.pollfds.fd, buf, cleanHdr.size_data, 0)) < -1)
//      std::cerr << "And error occured while receiving data: " << strerror(errno) << std::endl;
//    buf[r] = 0;
    (_dataBufArr[structFD.pollfds.fd]).push_back(std::string(buf));
    std::cout << "num_pack : " << cleanHdr.num_packet << " nb_pack : " << cleanHdr.nb_packets << std::endl;
    if (cleanHdr.num_packet < cleanHdr.nb_packets)
      this->sRecv(structFD);
  }
  return (std::string(""));
}

bool UnixSocket::sSend(const int &socket, std::string buf)
{
  if (send(socket, buf.c_str(), buf.size(), 0) == -1)
    std::cout << "And error occured while sending data: " << strerror(errno) << std::endl;
  return true;
}

std::map<int, std::vector<std::string> > UnixSocket::getDataBufArr() const
{
  return (this->_dataBufArr);
}

std::map<int, UnixSocket::t_header_clean> UnixSocket::getHeaders() const
{
  return (this->_headers);
}
