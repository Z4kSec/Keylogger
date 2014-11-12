/*
** IPSocket.h for  in /home/ouroub_a/rendu/spider-2017-krier_g/PSocket/PSocket
**
** Made by amina ourouba
** Login   <ouroub_a@epitech.net>
**
** Started on  Sun Oct 26 12:05:06 2014 jeremy pouyet
** Last update Fri Oct 31 17:19:26 2014 amina ourouba
*/

#pragma once

#include <string>

#include "UnixOpenssl.h"

class IPSocket
{
public:
  IPSocket() {};
  virtual bool		sCreate() = 0;
  virtual std::string	sRecv(t_structFD &structFD) = 0;
  virtual bool		sSend(const int &socket, std::string cmd) = 0;
  virtual void		sDelete(int &socket) = 0;
};
