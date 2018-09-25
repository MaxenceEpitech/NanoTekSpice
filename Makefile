##
## EPITECH PROJECT, 2018
## make
## File description:
## make
##

CXX		=	g++

NAME		=	nanotekspice

RM		=	rm -f

CXXFLAGS	+=	-std=c++11
CXXFLAGS	+=	-Werror -Wall -Wextra
CXXFLAGS	+=	-I./include/

OBJS		=	$(SRCS:.cpp=.o)

NAME		=	nanotekspice

ECHO		=	/bin/echo -e
DEFAULT		=	"\033[00m"
GREEN		=	"\033[0;32m"
TEAL		=	"\033[1;36m"
RED		=	"\033[0;31m"

SRCDIR		=	src

INCDIR		=	include

RM		=	rm -f

CXXFLAGS		=	-pipe -march=native -W -Wall -Wextra -I$(INCDIR)

SRC		=	$(SRCDIR)/main.cpp		\
			$(SRCDIR)/C4071.cpp		\
			$(SRCDIR)/C4001.cpp		\
			$(SRCDIR)/C4011.cpp		\
			$(SRCDIR)/C4030.cpp		\
			$(SRCDIR)/C4081.cpp		\
			$(SRCDIR)/Exception.cpp		\
			$(SRCDIR)/LogicalGate.cpp	\
			$(SRCDIR)/Parser.cpp		\
			$(SRCDIR)/Pin.cpp		\
			$(SRCDIR)/ReadLoop.cpp		\
			$(SRCDIR)/links.cpp		\
			$(SRCDIR)/C4069.cpp		\

OBJ		=	$(SRC:.cpp=.o)

all		:	title $(NAME)

title		:
			@$(ECHO) $(GREEN)"\tNano"$(TEAL)"tekspice\n"$(DEFAULT)

$(NAME)		:	$(OBJ)
			@$(CXX) -o $(NAME) $(OBJ) $(CXXFLAGS) $(LDFLAGS) &&	\
			$(ECHO) $(GREEN) "[OK]" $(TEAL) $(NAME) $(DEFAULT) ||	\
			$(ECHO) $(RED) "[XX]" $(TEAL) $(NAME) $(DEFAULT)

.c.o		:
			@$(CXX) $(CXXFLAGS) $(LDFLAGS) -c $< -o $@ &&		\
			$(ECHO) $(GREEN) "[OK]" $(TEAL) $< $(DEFAULT) ||	\
			$(ECHO) $(RED) "[XX]" $(TEAL) $< $(DEFAULT)

clean		:
			@$(RM) $(OBJ)
			@$(ECHO) $(GREEN) "[OK]" $(TEAL) "clean"

fclean		:	clean
			@$(RM) $(NAME)
			@$(ECHO) $(GREEN) "[OK]" $(TEAL) "fclean"

re		:	fclean all

debug		:	fclean all

.PHONY	: all title clean fclean re
