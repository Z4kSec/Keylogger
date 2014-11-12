##
## Makefile for  in /home/ouroub_a/rendu/spider-2017-krier_g/PSocket/PSocket
##
## Made by amina ourouba
## Login   <ouroub_a@epitech.net>
##
## Started on  Fri Oct 17 16:16:06 2014 amina ourouba
## Last update Sun Nov  9 15:18:51 2014 amina ourouba
##

# ifdef ComSpec
# 	CXXFLAGS = -Wall -Werror -Wextra

CXX		=	g++

CXXFLAGS	+=	-Wall -Wextra -Werror
CXXFLAGS	+=	-I. -I./Exceptions -I./Unix -I./DB -I./Parser

SQL_FLAGS	=	`mysql_config --cflags --libs`

SQL_LIB		=	-L/usr/include/mysql -lmysqlclient -lssl -lcrypto

DEBUG		=	1

ifeq ($(DEBUG), 1)
  CXXFLAGS	+=	-g3 -O0
endif

SRC		=	Exceptions/Exception.cpp \
			Unix/UnixSocket.cpp \
			Unix/UnixOpenssl.cpp \
			TermcapsUtils.cpp \
			DB/DataBase.cpp \
			Parser/Serializer.cpp \
			Parser/Deserializer.cpp \
			Server.cpp \
			main.cpp

OBJ		=	$(SRC:.cpp=.o)

NAME		=	server

$(NAME)	 	:	$(OBJ)
			$(CXX) $(OBJ) $(SQL_FLAGS) $(SQL_LIB) -o $(NAME)

all		:	$(NAME)

clean		:
			rm -rf $(OBJ)

fclean		:	clean
			rm -rf $(NAME)

re		:	fclean all

.PHONY		:	all clean fclean re
