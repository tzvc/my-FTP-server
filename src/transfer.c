/*
** transfer.c for myftp in /home/rootkid/rendu/psu/PSU_2016_myftp
** 
** Made by theo champion
** Login   <theo.champion@epitech.eu>
** 
** Started on  Wed May 10 15:40:21 2017 theo champion
** Last update Wed May 17 12:18:20 2017 theo champion
*/

#include "header.h"

bool			cmd_port(t_handle *hdl)
{
  struct sockaddr_in	data_sock;
  int			ip[4];
  char			ip_text[16];
  int			port[2];

  sscanf(hdl->cmd_arg, "%d,%d,%d,%d,%d,%d",
         &ip[0], &ip[1], &ip[2], &ip[3], &port[0], &port[1]);
  log_msg(DEBUG, "Parsed infos %d,%d,%d,%d,%d,%d",
          ip[0], ip[1], ip[2], ip[3], port[0], port[1]);
  sprintf(ip_text, "%d.%d.%d.%d", ip[0], ip[1], ip[2], ip[3]);
  if ((hdl->data_fd = create_c_socket(&data_sock, inet_addr(ip_text),
                                      (port[0] * 256 + port[1]))) == -1)
    return (reply(hdl, 500, "Error: %s", strerror(errno)));
  return (reply(hdl, 200, "PORT command successful. Consider using PASV."));
}

bool			cmd_pasv(t_handle *hdl)
{
  struct sockaddr_in	data_sock;
  uint16_t		port;
  socklen_t		len;

  len = sizeof(data_sock);
  if ((hdl->pasv_fd = create_s_socket(&data_sock, 0)) == -1)
    return (reply(hdl, 500, "Internal error"));
  listen(hdl->pasv_fd, MAX_CON);
  getsockname(hdl->pasv_fd, (struct sockaddr *)&data_sock, &len);
  port = ntohs(data_sock.sin_port);
  log_msg(DEBUG, "Data line port: %d", port);
  return (reply(hdl, 227, "Entering Passive Mode (%d,%d,%d,%d,%d,%d).",
                (int)(data_sock.sin_addr.s_addr & 0xFF),
                (int)((data_sock.sin_addr.s_addr & 0xFF00) >> 8),
                (int)((data_sock.sin_addr.s_addr & 0xFF0000) >> 16),
                (int)((data_sock.sin_addr.s_addr & 0xFF000000) >> 24),
                (int)(port / 256), (int)(port % 256)));
}

bool	cmd_type(t_handle *hdl)
{
  if (hdl->cmd_arg[0] == 'I')
    return (reply(hdl, 200, "Switching to Binary mode."));
  return (reply(hdl, 504, "Command not implemented for that parameter."));
}
