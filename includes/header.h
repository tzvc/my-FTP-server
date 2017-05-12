/*
** header.h for myftp in /home/rootkid/rendu/psu/PSU_2016_myftp
** 
** Made by theo champion
** Login   <theo.champion@epitech.eu>
** 
** Started on  Tue May  9 14:16:44 2017 theo champion
** Last update Fri May 12 17:57:54 2017 theo champion
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
#define BLOCK_SIZE 1024
#define SP ' '
#define CR '\r'
#define LF '\n'
#define USER "Anonymous"
#define INFO 0
#define ERROR 1
#define DEBUG 2

typedef struct	s_handle
{
  int		ctrl_fd;
  int		data_fd;
  int		pasv_fd;
  char		*path;
  int		cmd_nb;
  char		*cmd_arg;
  int		login_status;
  bool		quit;
}		t_handle;

typedef bool (*cmd_ptr)(t_handle *);

//MAIN.C
int	create_s_socket(struct sockaddr_in *sock, int port);
int	create_c_socket(struct sockaddr_in *sock, uint32_t ip, int port);
//CLIENT_HANDLER.C
bool	reply(t_handle *hdl, int code, const char *fmt, ...);
void	handle_client(t_handle *hdl);
//USER.C
bool	cmd_user(t_handle *hdl);
bool	cmd_pass(t_handle *hdl);
bool	cmd_quit(t_handle *hdl);
//FILE_NAVIGATION.C
bool	cmd_cwd(t_handle *hdl);
bool	cmd_cdup(t_handle *hdl);
bool	cmd_pwd(t_handle *hdl);
//FILE_ACTION.C
bool	cmd_stor(t_handle *hdl);
bool	cmd_retr(t_handle *hdl);
//TRANSFER.C
bool	cmd_port(t_handle *hdl);
bool	cmd_pasv(t_handle *hdl);
//UTILS.C
void	log_msg(int mode, const char *fmt, ...);
//SOCKET.C
int	create_s_socket(struct sockaddr_in *sock, int port);
int	create_c_socket(struct sockaddr_in *sock, uint32_t ip, int port);
int	accept_connection(int socket_fd);
#endif /* !HEADER_H_ */
