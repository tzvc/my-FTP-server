##
## Makefile for strace in /home/rootkid/rendu/psu/PSU_2016_strace
## 
## Made by theo champion
## Login   <theo.champion@epitech.eu>
## 
## Started on  Wed Apr 12 11:17:49 2017 theo champion
## Last update Wed May 10 10:26:00 2017 theo champion
##

CC	= gcc

RM	= rm -f

SRCDIR	= ./src

CFLAGS	+= -W -Wall -Wextra -Werror -g3
CFLAGS	+= -I./includes

NAME	= server

SRCS	= $(SRCDIR)/main.c		\
          $(SRCDIR)/client_handler.c	\
          $(SRCDIR)/login.c		\

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
