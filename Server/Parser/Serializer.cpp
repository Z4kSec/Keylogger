//
// Serialize.cpp for  in /home/ouroub_a/rendu/spider-2017-krier_g/Server
//
// Made by amina ourouba
// Login   <ouroub_a@epitech.net>
//
// Started on  Fri Oct 31 11:04:33 2014 amina ourouba
// Last update Sun Nov  9 11:50:25 2014 amina ourouba
//

#include <sstream>
#include <string>
#include "Serializer.h"

Serializer::Serializer()
{

}

std::string		Serializer::SerializeData(std::map<std::string, std::map<std::string, std::string> > data)
{
  boost::property_tree::ptree		jsonArr;
  boost::property_tree::ptree		innerJsonArr;

  std::map<std::string, std::map<std::string, std::string> >::iterator it;
  std::map<std::string, std::string>::iterator innerIt;
  std::map<std::string, std::string> tmpTab;
  std::ostringstream buf;

  for (it = data.begin(); it != data.end(); ++it)
  {
    tmpTab = it->second;
    for (innerIt = tmpTab.begin(); innerIt != tmpTab.end(); ++innerIt)
      innerJsonArr.put(innerIt->first, innerIt->second);
    jsonArr.put_child(it->first, innerJsonArr);
  }
  boost::property_tree::write_json(buf, jsonArr, false);
  return (buf.str());
}

Serializer::~Serializer()
{

}
