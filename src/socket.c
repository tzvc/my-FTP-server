/*
** socket.c for myftp in /home/rootkid/rendu/psu/PSU_2016_myftp
** 
** Made by theo champion
** Login   <theo.champion@epitech.eu>
** 
** Started on  Fri May 12 12:38:10 2017 theo champion
** Last update Thu May 18 00:10:29 2017 theo champion
*/

#include "header.h"

int	create_s_socket(struct sockaddr_in *sock, int port)
{
  int	socket_fd;
  int	en;

  memset(sock, 0, sizeof(*sock));
  if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    return (-1);
  en = 1;
  if (setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &en, sizeof(int)) < 0)
    return (-1);
  sock->sin_family = AF_INET;
  sock->sin_addr.s_addr = INADDR_ANY;
  sock->sin_port = htons(port);
  if (bind(socket_fd, (struct sockaddr *)sock, sizeof(*sock)) < 0)
    return (-1);
  return (socket_fd);
}

int	create_c_socket(struct sockaddr_in *sock, uint32_t ip, int port)
{
  int	socket_fd;
  int	en;

  memset(sock, 0, sizeof(*sock));
  if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    return (-1);
  en = 1;
  if (setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &en, sizeof(int)) < 0)
    return (-1);
  sock->sin_family = AF_INET;
  sock->sin_addr.s_addr = ip;
  sock->sin_port = htons(port);
  if (connect(socket_fd, (struct sockaddr *)sock, sizeof(*sock)) < 0)
    return (-1);
  return (socket_fd);
}

int			accept_con(int socket_fd)
{
  struct sockaddr_in	r_addr;
  socklen_t		addrlen;
  int			out_fd;

  addrlen = sizeof(struct sockaddr_in);
  if ((out_fd = accept(socket_fd,
                       (struct sockaddr *)&r_addr,
                       (socklen_t*)&addrlen)) == -1)
    return (-1);
  log_msg(INFO, "Connection accepted [%s]", inet_ntoa(r_addr.sin_addr));
  return (out_fd);
}
