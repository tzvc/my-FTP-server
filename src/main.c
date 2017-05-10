/*
** main.c for myftp in /home/rootkid/rendu/psu/PSU_2016_myftp
** 
** Made by theo champion
** Login   <theo.champion@epitech.eu>
** 
** Started on  Tue May  9 13:57:08 2017 theo champion
** Last update Wed May 10 18:06:13 2017 theo champion
*/

#include "header.h"

int	create_socket(struct sockaddr_in *sock, int port)
{
  int		socket_fd;
  int		enable;

  if ((socket_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_IP)) == -1)
    return (-1);
  enable = 1;
  if (setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0)
    return (-1);
  sock->sin_family = AF_INET;
  sock->sin_addr.s_addr = htonl(INADDR_LOOPBACK);
  sock->sin_port = htons(port);
  if (bind(socket_fd,(struct sockaddr *)sock , sizeof(*sock)) < 0)
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

int			main(int argc, char **argv)
{
  int			socket_fd;
  struct sockaddr_in	ctrl_sock;
  int			port;

  if (argc < 3)
    fprintf(stderr, "Usage : ./server port path\n");
  else if (access(argv[1], F_OK) == -1)
    fprintf(stderr, "Invalid path %s\n", argv[1]);
  else if ((port = (int)strtol(argv[2], NULL, 10)) <= 0)
    fprintf(stderr, "Invalid port number\n");
  else if ((socket_fd = create_socket(&ctrl_sock, port)) == -1)
    fprintf(stderr, "Unable to create socket: %s\n", strerror(errno));
  else
    {
      listen(socket_fd, 3);
      handle_new_connections(socket_fd, argv[1]);
      return (0);
    }
  return (1);
}
