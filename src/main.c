/*
** main.c for myftp in /home/rootkid/rendu/psu/PSU_2016_myftp
** 
** Made by theo champion
** Login   <theo.champion@epitech.eu>
** 
** Started on  Tue May  9 13:57:08 2017 theo champion
** Last update Fri May 19 15:18:36 2017 theo champion
*/

#include "header.h"

static volatile bool	g_run_server;
static int	g_socket_fd;

void	signal_handler(int signal)
{
  (void)signal;
  log_msg(INFO, "Ctrl-C catched, shutting down server...");
  shutdown(g_socket_fd, SHUT_RDWR);
  g_run_server = false;
}

static int		handle_new_connections(int port, char *home)
{
  t_handle		hdl;
  struct sockaddr_in	l_addr;
  socklen_t		addrlen;

  log_msg(INFO, "Waiting for incoming connections...");
  if ((g_socket_fd = create_s_socket(&l_addr, port)) == -1)
    return (-1);
  listen(g_socket_fd, QUEUE_SIZE);
  if ((hdl.home = realpath(home, NULL)) == NULL)
    return (-1);
  while (g_run_server && ((hdl.ctrl_fd = accept_con(g_socket_fd)) != -1))
    {
      if (fork() == 0)
        {
          addrlen = sizeof(l_addr);
          getsockname(hdl.ctrl_fd, (struct sockaddr *)&l_addr, &addrlen);
          hdl.local_ip = l_addr.sin_addr.s_addr;
          handle_client(&hdl);
          log_msg(INFO, "Client exited.");
          return (0);
        }
      close(hdl.ctrl_fd);
    }
  free(hdl.home);
  return (0);
}

int			main(int argc, char **argv)
{
  int			port;

  g_run_server = true;
  signal(SIGINT, signal_handler);
  if (argc < 3)
    printf("Usage : %s port path\n", argv[0]);
  else if ((port = (int)strtol(argv[1], NULL, 10)) <= 0)
    fprintf(stderr, "Invalid port number\n");
  else if (access(argv[2], F_OK) == -1)
    fprintf(stderr, "Invalid path %s\n", argv[2]);
  else if (handle_new_connections(port, argv[2]) == -1)
    fprintf(stderr, "Error launching server: %s\n", strerror(errno));
  else
    return (0);
  return (1);
}
