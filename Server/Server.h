/*
** Server.h for  in /home/ouroub_a/rendu/spider-2017-krier_g/Server
**
** Made by amina ourouba
** Login   <ouroub_a@epitech.net>
**
** Started on  Wed Oct 29 07:33:55 2014 amina ourouba
** Last update Sun Nov  9 11:47:45 2014 amina ourouba
*/

#pragma once

#include <string>
#include "UnixSocket.h"
#include "Serializer.h"
#include "Deserializer.h"

class Server
{
private:
  UnixSocket	*_socket;
  Deserializer	*_deserializer;
  Serializer	_serializer;

private:
  std::map<std::string, std::map<std::string, std::string> >	_answer(bool state);

public:
  Server(int &port, std::string &dbPasswd);
  void fdMonitor();
  ~Server();
};
