/*
** main.c for myftp in /home/rootkid/rendu/psu/PSU_2016_myftp
** 
** Made by theo champion
** Login   <theo.champion@epitech.eu>
** 
** Started on  Tue May  9 13:57:08 2017 theo champion
** Last update Fri May 12 12:43:12 2017 theo champion
*/

#include "header.h"

static void		handle_new_connections(int socket_fd, char *home)
{
  t_handle		hdl;
  struct sockaddr_in	client;
  pid_t			pid;
  socklen_t		cli_addr_size;

  log_msg(INFO, "Waiting for incoming connections...");
  log_msg(ERROR, "Waiting for incoming connections...");
  hdl.path = realpath(home, NULL);
  cli_addr_size = sizeof(client);
  while ((hdl.ctrl_fd = accept(socket_fd,
			       (struct sockaddr *)&client,
			       (socklen_t*)&cli_addr_size)) != -1)
  {
    log_msg(INFO, "Connection accepted");
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
  else if ((port = (int)strtol(argv[1], NULL, 10)) <= 0)
    fprintf(stderr, "Invalid port number\n");
  else if (access(argv[2], F_OK) == -1)
    fprintf(stderr, "Invalid path %s\n", argv[2]);
  else if ((socket_fd = create_s_socket(&ctrl_sock, port)) == -1)
    fprintf(stderr, "Unable to create socket: %s\n", strerror(errno));
  else
    {
      listen(socket_fd, 3);
      handle_new_connections(socket_fd, argv[2]);
      return (0);
    }
  return (1);
}
