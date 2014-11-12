//
// main.cpp for  in /home/ouroub_a/rendu/cpp_spider/Server
//
// Made by amina ourouba
// Login   <ouroub_a@epitech.net>
//
// Started on  Thu Oct 16 11:32:48 2014 amina ourouba
// Last update Sat Nov  8 18:24:16 2014 amina ourouba
//

#include <boost/property_tree/json_parser.hpp>
#include <iostream>
#include "TermcapsUtils.h"
#include "Exception.h"
#include "UnixSocket.h"
#include "Server.h"

int		main(int, char **)
{
  int		port;
  std::string	password;

  do {
    std::cout << "Please enter a valid port to listen to: ";
    std::cin >> port;

    if(std::cin.fail())
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    if (std::cin.eof())
    {
      std::cerr << "Encountered EOF. Exiting now." << std::endl;
      return (0);
    }
  } while (port < 1024);

  std::cout << "Please enter your MySQL DB password (press CTRL-D for empty password): ";
  TermcapsUtils::hideEntry();
  do {
    getline(std::cin, password);
    if (std::cin.eof())
      break;
  } while (password.size() == 0);

  std::cout << std::endl;
  TermcapsUtils::showEntry();
  try
  {
    Server server(port, password);
    server.fdMonitor();
  }
  catch (std::bad_alloc &e)
  {
    std::cout << "Memory Allocation Error caught: " << e.what() << std::endl;
  }
  catch (Exception &e)
  {
    std::cout << "Error: in " << e.file() << ", " << "function " << e.function()
	      << "(line " << e.line() << ") : " << std::endl
	      << "\t" << e.what() << std::endl;
  }
  catch (boost::property_tree::json_parser_error &e)
  {
    std::cout << "JSON Parser Error caught: " << e.what() << std::endl;
  }
  return (1);
}
