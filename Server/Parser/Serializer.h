/*
** Serialize.h for  in /home/ouroub_a/rendu/spider-2017-krier_g/Server
**
** Made by amina ourouba
** Login   <ouroub_a@epitech.net>
**
** Started on  Fri Oct 31 11:04:46 2014 amina ourouba
** Last update Sun Nov  9 11:50:00 2014 amina ourouba
*/

#pragma once

#include <map>
#include <string>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

class Serializer
{
private :

public:
  Serializer();
  static std::string SerializeData(std::map<std::string, std::map<std::string, std::string> > data);
  ~Serializer();
};
