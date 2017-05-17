/*
** main.c for myftp in /home/rootkid/rendu/psu/PSU_2016_myftp
** 
** Made by theo champion
** Login   <theo.champion@epitech.eu>
** 
** Started on  Tue May  9 13:57:08 2017 theo champion
** Last update Wed May 17 18:05:08 2017 theo champion
*/

#include "header.h"

static volatile bool	g_run_server;
static int	g_socket_fd;

void	signal_handler(int signal)
{
  (void)signal;
  log_msg(INFO, "Ctrl-C catched, exiting cleanly...");
  shutdown(g_socket_fd, SHUT_RDWR);
  g_run_server = false;
}

static void		handle_new_connections(char *home)
{
  t_handle		hdl;
  struct sockaddr_in	client;
  pid_t			pid;
  socklen_t		cli_addr_size;

  log_msg(INFO, "Waiting for incoming connections...");
  if ((hdl.path = realpath(home, NULL)) == NULL)
    return;
  cli_addr_size = sizeof(client);
  while (g_run_server
         && (hdl.ctrl_fd = accept(g_socket_fd,
                                  (struct sockaddr *)&client,
                                  (socklen_t*)&cli_addr_size)) != -1)
    {
      log_msg(INFO, "Connection accepted [%s]", inet_ntoa(client.sin_addr));
      if ((pid = fork()) == 0)
        {
          handle_client(&hdl);
          log_msg(INFO, "Client [%s] exited", inet_ntoa(client.sin_addr));
          return;
        }
      else
        close(hdl.ctrl_fd);
    }
  free(hdl.path);
}

int			main(int argc, char **argv)
{
  struct sockaddr_in	ctrl_sock;
  int			port;

  if (argc < 3)
    printf("Usage : %s port path\n", argv[0]);
  else if ((port = (int)strtol(argv[1], NULL, 10)) <= 0)
    fprintf(stderr, "Invalid port number\n");
  else if (access(argv[2], F_OK) == -1)
    fprintf(stderr, "Invalid path %s\n", argv[2]);
  else if ((g_socket_fd = create_s_socket(&ctrl_sock, port)) == -1)
    fprintf(stderr, "Unable to create socket: %s\n", strerror(errno));
  else
    {
      signal(SIGINT, signal_handler);
      g_run_server = true;
      listen(g_socket_fd, QUEUE_SIZE);
      handle_new_connections(argv[2]);
      return (0);
    }
  return (1);
}
