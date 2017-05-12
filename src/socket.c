/*
** socket.c for myftp in /home/rootkid/rendu/psu/PSU_2016_myftp
** 
** Made by theo champion
** Login   <theo.champion@epitech.eu>
** 
** Started on  Fri May 12 12:38:10 2017 theo champion
** Last update Fri May 12 16:23:27 2017 theo champion
*/

#include "header.h"

int	create_s_socket(struct sockaddr_in *sock, int port)
{
  int	socket_fd;
  int	enable;

  if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    return (-1);
  enable = 1;
  if (setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0)
    return (-1);
  sock->sin_family = AF_INET;
  sock->sin_addr.s_addr = htonl(INADDR_LOOPBACK);
  sock->sin_port = htons(port);
  if (bind(socket_fd, (struct sockaddr *)sock, sizeof(*sock)) < 0)
    return (-1);
  return (socket_fd);
}

int	create_c_socket(struct sockaddr_in *sock, uint32_t ip, int port)
{
  int	socket_fd;
  int	enable;

  if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    return (-1);
  enable = 1;
  if (setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0)
    return (-1);
  sock->sin_family = AF_INET;
  sock->sin_addr.s_addr = ip;
  sock->sin_port = htons(port);
  if (connect(socket_fd, (struct sockaddr *)sock, sizeof(*sock)) < 0)
    return (-1);
  return (socket_fd);
}


int			accept_connection(int socket_fd)
{
  socklen_t		len;
  struct sockaddr_in	client;

  len = sizeof(client);
  return (accept(socket_fd, (struct sockaddr*) &client, &len));
}
