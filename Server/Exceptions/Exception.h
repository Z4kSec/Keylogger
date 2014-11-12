/*
** Exceptions.h for  in /home/ouroub_a/rendu/spider-2017-krier_g/PSocket/PSocket
**
** Made by amina ourouba
** Login   <ouroub_a@epitech.net>
**
** Started on  Tue Oct 21 20:05:37 2014 amina ourouba
** Last update Sun Oct 26 15:46:44 2014 amina ourouba
*/

#pragma once

#include <exception>
#include <string>

class Exception : public std::exception
{
public:
  Exception(int const &line, std::string const &file = "", std::string const &func = "", std::string const &msg = "") throw()
    : _file(file), _function(func), _line(line), _msg(msg) {}
  virtual const char *file() const throw();
  virtual const char *what() const throw();
  virtual const char *function() const throw();
  virtual const int &line() const throw();
  virtual ~Exception() throw() {};

protected:
  std::string	_file;
  std::string	_function;
  int		_line;
  std::string	_msg;
};
