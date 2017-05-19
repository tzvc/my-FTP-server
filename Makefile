##
## Makefile for myftp in /home/rootkid/rendu/psu/PSU_2016_myftp
## 
## Made by theo champion
## Login   <theo.champion@epitech.eu>
## 
## Started on  Wed May 17 11:35:56 2017 theo champion
## Last update Fri May 19 18:07:14 2017 theo champion
##

CC	= gcc

RM	= rm -f

SRCDIR	= ./src

CFLAGS	+= -W -Wall -Wextra -Werror -g3
CFLAGS	+= -I./includes

NAME	= server

SRCS	= $(SRCDIR)/main.c		\
          $(SRCDIR)/client_handler.c	\
          $(SRCDIR)/utils.c		\
          $(SRCDIR)/socket.c		\
          $(SRCDIR)/user.c		\
          $(SRCDIR)/file_navigation.c	\
          $(SRCDIR)/file_action.c	\
          $(SRCDIR)/transfer.c		\

OBJS	= $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY:	all clean fclean re
