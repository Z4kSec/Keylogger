//
// TermcapsUtils.cpp for  in /home/ouroub_a/rendu/spider-2017-krier_g/Server
//
// Made by amina ourouba
// Login   <ouroub_a@epitech.net>
//
// Started on  Fri Nov  7 10:04:14 2014 amina ourouba
// Last update Fri Nov  7 10:28:48 2014 amina ourouba
//

#include <termios.h>
#include "TermcapsUtils.h"

TermcapsUtils::TermcapsUtils(){}
TermcapsUtils::~TermcapsUtils(){}

void TermcapsUtils::hideEntry()
{
  termios tty;

  tcgetattr(0, &tty);
  tty.c_lflag &= ~ECHO;
  tcsetattr(0, TCSANOW, &tty);
}

void TermcapsUtils::showEntry()
{
  termios tty;

  tcgetattr(0, &tty);
  tty.c_lflag |= ECHO;
  tcsetattr(0, TCSANOW, &tty);
}
