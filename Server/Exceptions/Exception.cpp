//
// Exceptions.cpp for  in /home/ouroub_a/rendu/spider-2017-krier_g/PSocket/PSocket
//
// Made by amina ourouba
// Login   <ouroub_a@epitech.net>
//
// Started on  Tue Oct 21 20:05:02 2014 amina ourouba
// Last update Sun Oct 26 16:02:13 2014 amina ourouba
//

#include "Exception.h"

const char *Exception::what() const throw()
{
  return (this->_msg.c_str());
}

const char *Exception::function() const throw()
{
  return (this->_function.c_str());
}

const char *Exception::file() const throw()
{
  return (this->_file.c_str());
}

const int &Exception::line() const throw()
{
  return (this->_line);
}
