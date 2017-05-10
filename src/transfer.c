/*
** transfer.c for myftp in /home/rootkid/rendu/psu/PSU_2016_myftp
** 
** Made by theo champion
** Login   <theo.champion@epitech.eu>
** 
** Started on  Wed May 10 15:40:21 2017 theo champion
** Last update Wed May 10 19:19:48 2017 theo champion
*/

#include "header.h"

void			cmd_port(t_handle *hdl)
{
  struct sockaddr_in	data_sock;
  int			port;

  printf("%s\n", hdl->cmd_arg);
  port = (int)strtol(hdl->cmd_arg, NULL, 10);
  if (port > 0 && port < USHRT_MAX)
    {
      if ((hdl->data_fd = create_socket(&data_sock, port)) != -1)
	{

	}
    }
}

void			cmd_pasv(t_handle *hdl)
{
  struct sockaddr_in	data_sock;
  char			rep_msg[100];
  uint16_t		port;
  socklen_t		len;

  if ((hdl->data_fd = create_socket(&data_sock, 0)) != -1)
    {
      getsockname(hdl->data_fd, (struct sockaddr *)&data_sock, &len);
      port = ntohs(data_sock.sin_port);
      sprintf(rep_msg, "Entering Passive Mode (%d,%d,%d,%d,%d,%d).",
	      (int)(data_sock.sin_addr.s_addr & 0xFF),
	      (int)((data_sock.sin_addr.s_addr & 0xFF00) >> 8),
	      (int)((data_sock.sin_addr.s_addr & 0xFF0000) >> 16),
	      (int)((data_sock.sin_addr.s_addr & 0xFF000000) >> 24),
	      port / 256, port % 256);
      printf("%s  %d\n", rep_msg, port);
      set_rep(hdl, 227, rep_msg);
      hdl->rep_text = strdup(rep_msg);
    }
  else
    set_rep(hdl, 500, "Canno open data connection");
}
