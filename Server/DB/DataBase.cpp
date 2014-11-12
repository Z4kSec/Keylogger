//
// DataBase.cpp for  in /home/ouroub_a/rendu/spider-2017-krier_g/Server/DB
//
// Made by amina ourouba
// Login   <ouroub_a@epitech.net>
//
// Started on  Sat Nov  1 22:39:02 2014 amina ourouba
// Last update Sun Nov  9 23:23:30 2014 amina ourouba
//

#include <vector>
#include <string>
#include <iostream>
#include "DataBase.h"
#include "Exception.h"

DataBase::DataBase(std::string &password)
  : _result(NULL)
{
  mysql_init(&_mysql);
  mysql_options(&_mysql,MYSQL_READ_DEFAULT_GROUP,"option");
  if(!mysql_real_connect(&_mysql, "localhost", "root", password.c_str(), "keylogger",0,NULL,0))
    throw Exception(__LINE__ - 1, __FILE__, __FUNCTION__, "Can't connect to DB. Your password might be incorrect. Did you run scripts/sql_config.sh?");
}

DataBase::~DataBase()
{
  mysql_close(&_mysql);
}

int	DataBase::query(std::string &q)
{
  return (mysql_query(&_mysql, q.c_str()));
}

std::map<std::string, std::string>	DataBase::selectInTable(const std::string &table, std::string data, std::string where)
{
  int				i;
  std::string			selectCmd;
  std::map<std::string, std::string>	resArray;
  std::map<std::string, std::string>::iterator	it;

  selectCmd = "SELECT " + data + " FROM " + table;
  if (where.length())
    selectCmd += " WHERE " + where;
  if (this->query(selectCmd))
    std::cerr << "Cannot perform 'select' query on DB." << std::endl;
  _result = mysql_store_result(&_mysql);

  if (!(_result))
    return (std::map<std::string, std::string>());
  for (i = 0; (_field = mysql_fetch_field(this->_result)); ++i)
  {
    if (std::string(_field->name) == "id")
      resArray[_field->name + std::string(".") + table] = "";
    else
      resArray[_field->name] = "";
  }

  this->_row = mysql_fetch_row(_result);
  if (_row)
  {
    for (it = resArray.begin(); it != resArray.end(); ++it)
      it->second = _row[i];
    mysql_free_result(_result);
  }
  return (resArray);
}

void DataBase::insertInTable(const std::string &table, std::map<std::string, std::string> &data)
{
  std::map<std::string, std::string>::iterator it;
  std::string columns;
  std::string values;
  std::string insertCmd;

  insertCmd = "INSERT INTO " + table + " (";
  for (it = data.begin(); it != data.end(); ++it)
  {
    columns += it->first + ",";
    values += "'" + it->second + "', ";
  }
  columns.erase(columns.size() - 1, 1);
  columns += ")";
  values.erase(values.size() - 1, 1);
  values += ")";
  insertCmd += columns + " VALUES(" + values + ";";
  if (this->query(insertCmd))
    std::cerr << "Cannot perform 'insert' query on DB." << std::endl;
}
