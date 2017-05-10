/*
** header.h for myftp in /home/rootkid/rendu/psu/PSU_2016_myftp
** 
** Made by theo champion
** Login   <theo.champion@epitech.eu>
** 
** Started on  Tue May  9 14:16:44 2017 theo champion
** Last update Wed May 10 20:48:38 2017 theo champion
*/

#ifndef HEADER_H_
#define HEADER_H_

#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>

#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stropts.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <limits.h>
#include <stdarg.h>

#define CMD_SIZE 1024
#define SP ' '
#define CR '\r'
#define LF '\n'
#define USER "Anonymous"

typedef struct	s_handle
{
  int		ctrl_fd;
  int		data_fd;
  char		*path;
  int		cmd_nb;
  char		*cmd_arg;
  char		*cmd_rep;
  int		rep_code;
  char		*rep_text;
  int		login_status;
  bool		quit;
}		t_handle;

typedef void (*cmd_ptr)(t_handle *);

//MAIN.C
int	create_socket(struct sockaddr_in *sock, int port);
//CLIENT_HANDLER.C
void	handle_client(t_handle *hdl);
//USER.C
void	cmd_user(t_handle *hdl);
void	cmd_pass(t_handle *hdl);
void	cmd_quit(t_handle *hdl);
//FILE_NAVIGATION.C
void	cmd_cwd(t_handle *hdl);
void	cmd_cdup(t_handle *hdl);
void	cmd_pwd(t_handle *hdl);
//TRANSFER.C
void	cmd_port(t_handle *hdl);
void	cmd_pasv(t_handle *hdl);
//UTILS.C
void	set_rep(t_handle *hdl, int code, const char *fmt, ...);
#endif /* !HEADER_H_ */
