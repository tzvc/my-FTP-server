/*
** main.c for myftp in /home/rootkid/rendu/psu/PSU_2016_myftp
** 
** Made by theo champion
** Login   <theo.champion@epitech.eu>
** 
** Started on  Tue May  9 13:57:08 2017 theo champion
** Last update Wed May 10 11:59:10 2017 theo champion
*/

#include "header.h"

static int	init_listening_socket(struct sockaddr_in *server)
{
  int		socket_fd;
  int		enable;

  if ((socket_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_IP)) == -1)
    return (-1);
  enable = 1;
  if (setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0)
    return (-1);
  server->sin_family = AF_INET;
  server->sin_addr.s_addr = INADDR_ANY;
  server->sin_port = htons( 8888 );
  if (bind(socket_fd,(struct sockaddr *)server , sizeof(*server)) < 0)
    return (-1);
  return (socket_fd);
}

static void		handle_new_connections(int socket_fd, char *home)
{
  t_handle		hdl;
  struct sockaddr_in	client;
  pid_t			pid;
  socklen_t		cli_addr_size;

  puts("Waiting for incoming connections...");
  hdl.path = realpath(home, NULL);
  cli_addr_size = sizeof(client);
  while ((hdl.ctrl_fd = accept(socket_fd,
			       (struct sockaddr *)&client,
			       (socklen_t*)&cli_addr_size)) != -1)
  {
    puts("Connection accepted");
    if ((pid = fork()) == 0)
      {
	handle_client(&hdl);
	break;
      }
  }
}

int main(void)
{
  int socket_fd;
  struct sockaddr_in server;

  if ((socket_fd = init_listening_socket(&server)) == -1)
    {
      fprintf(stderr, "Unable to create socket: %s\n", strerror(errno));
      return (1);
    }
  listen(socket_fd, 3);
  handle_new_connections(socket_fd, "/");
  return 0;
}
