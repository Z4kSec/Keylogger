//
// Server.cpp for  in /home/ouroub_a/rendu/spider-2017-krier_g/Server
//
// Made by amina ourouba
// Login   <ouroub_a@epitech.net>
//
// Started on  Wed Oct 29 07:34:11 2014 amina ourouba
// Last update Sun Nov  9 23:15:19 2014 amina ourouba
//

#include <iostream>
#include "Server.h"

Server::Server(int &port, std::string &dbPasswd)
{
  _socket = new UnixSocket(port);
  _deserializer = new Deserializer(dbPasswd);
  _socket->sCreate();
}

std::map<std::string, std::map<std::string, std::string> >	Server::_answer(bool state)
{
  std::map<std::string, std::map<std::string, std::string> >	answer;

  if (state == true)
    answer["StartupAnswer"].insert(std::pair<std::string, std::string>("answer", "true"));
  else
    answer["StartupAnswer"].insert(std::pair<std::string, std::string>("answer", "false"));
  return (answer);
}

void		_sendCommand(std::vector<std::string> commands)
{

  std::vector<std::string>::iterator it;

  for (it = commands.begin(); it != commands.end(); ++it)
  {
    std::istringstream	ss(*it);


  }
}

void							Server::fdMonitor()
{
  std::map<int, std::vector<std::string> >		dataBufArr;
  std::map<int, UnixSocket::t_header_clean>		headers;
  std::map<int, UnixSocket::t_header_clean>::iterator	ith;
  std::map<int, std::string>::iterator	it;

  while (1)
  {
    _socket->sSelect();
    dataBufArr =_socket->getDataBufArr();
    headers = _socket->getHeaders();
    for (ith = headers.begin(); ith != headers.end(); ++ith)
    {
      if ((_deserializer->DeserializeData(ith->second, dataBufArr[ith->first])) ==  GREET)
	_socket->sSend(ith->first, _serializer.SerializeData(this->_answer(true)));
    }
  }
}

Server::~Server()
{
  delete _socket;
  delete _deserializer;
}
