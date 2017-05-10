/*
** client_handler.c for myftp in /home/rootkid/rendu/psu/PSU_2016_myftp
** 
** Made by theo champion
** Login   <theo.champion@epitech.eu>
** 
** Started on  Tue May  9 15:12:44 2017 theo champion
** Last update Wed May 10 20:48:01 2017 theo champion
*/

#include "header.h"

static char	*recv_cmd(int ctrl_fd)
{
  char		*cmd;
  int		i;

  i = 0;
  cmd = malloc(sizeof(char) * CMD_SIZE);
  while (42)
    {
      if (read(ctrl_fd, &cmd[i], 1) != 0)
        {
          if (cmd[i] == LF && cmd[i - 1] == CR)
            break;
          if (++i >= CMD_SIZE)
            cmd = realloc(cmd, sizeof(cmd) + sizeof(char) * CMD_SIZE);
        }
    }
  cmd[i - 1] = 0;
  return (cmd);
}

static void	parse_cmd(char *cmd, t_handle *hdl)
{
  int		i;
  int		h;
  static char	*names[] = {"USER", "PASS", "QUIT", "CWD", "CDUP",
			    "PWD", "PORT", "PASV", "STOR", "RETR", "LIST",
			    "DELE", "PWD", "HELP", "NOOP"};

  i = 0;
  hdl->cmd_nb = -1;
  hdl->cmd_arg = NULL;
  while (cmd[i] && cmd[i] != SP)
    i++;
  h = 0;
  while (names[h] && strncmp(cmd, names[h], i) != 0)
    h++;
  printf("found %s\n", names[h]);
  if (!names[h])
    return;
  hdl->cmd_nb = h;
  hdl->cmd_arg = &cmd[++i];
}

static void	exec_cmd(t_handle *hdl)
{
  cmd_ptr	funcs[] = {cmd_user, cmd_pass, cmd_quit, cmd_cwd, cmd_cdup,
			   cmd_pwd, cmd_port, cmd_pasv};

  if (hdl->cmd_nb >= 0)
    funcs[hdl->cmd_nb](hdl);
  else
    set_rep(hdl, 500, "Unknown command.");
}

static void	send_reply_sequence(t_handle *hdl)
{
  char		*rep_msg;

  if ((rep_msg = malloc(sizeof(char) * (7 + strlen(hdl->rep_text)))))
    {
      sprintf(rep_msg, "%d %s\r\n", hdl->rep_code, hdl->rep_text);
      write(hdl->ctrl_fd, rep_msg, strlen(rep_msg));
      free(rep_msg);
    }
  free(hdl->rep_text);
}

void		handle_client(t_handle *hdl)
{
  char		*cmd;

  set_rep(hdl, 220, "Welcome, don't break anything pls");
  send_reply_sequence(hdl);
  hdl->login_status = 0;
  hdl->quit = false;
  while (!hdl->quit)
    {
      cmd = recv_cmd(hdl->ctrl_fd);
      parse_cmd(cmd, hdl);
      exec_cmd(hdl);
      send_reply_sequence(hdl);
      free(cmd);
    }
  free(hdl->path);
  close(hdl->ctrl_fd);
}
