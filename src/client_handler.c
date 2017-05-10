/*
** client_handler.c for myftp in /home/rootkid/rendu/psu/PSU_2016_myftp
** 
** Made by theo champion
** Login   <theo.champion@epitech.eu>
** 
** Started on  Tue May  9 15:12:44 2017 theo champion
** Last update Wed May 10 11:59:36 2017 theo champion
*/

#include "header.h"
#include "protocol_ref.h"

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
  static char	*names[] = {"USER", "PASS", "CWD", "CDUP", "QUIT",
			    "DELE", "PWD", "PASV", "PORT", "HELP",
			    "NOOP", "RETR", "STOR", "LIST"};

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
  cmd_ptr	funcs[] = {cmd_user, cmd_pass, cmd_cwd, cmd_cdup, cmd_quit};

  if (hdl->cmd_nb >= 0)
    funcs[hdl->cmd_nb](hdl);
  else
    hdl->rep_code = 0;
}

static void	send_reply_sequence(t_handle *hdl, int rep_code)
{
  int		i;
  char		*rep_msg;
  t_pair	rep[] = {{120, T120}, {125, T125}, {150, T150},
			 {200, T200}, {214, T214}, {220, T220},
	                 {221, T221}, {226, T226}, {227, T227},
			 {230, T230}, {250, T250}, {257, T257},
			 {331, T331}, {332, T332}, {0, XXX}};
  i = 0;
  while (rep[i].code != rep_code)
    i++;
  rep_msg = malloc(sizeof(char) * (6 + strlen(rep[i].text)));
  if (rep_code == 0)
    sprintf(rep_msg, "xxx %s\r\n", rep[i].text);
  else
    sprintf(rep_msg, "%d %s\r\n", rep[i].code, rep[i].text);
  write(hdl->ctrl_fd, rep_msg, strlen(rep_msg));
  free(rep_msg);
}

void		handle_client(t_handle *hdl)
{
  char		*cmd;

  send_reply_sequence(hdl, 220);
  hdl->login_status = 0;
  hdl->quit = false;
  while (!hdl->quit)
    {
      cmd = recv_cmd(hdl->ctrl_fd);
      parse_cmd(cmd, hdl);
      exec_cmd(hdl);
      send_reply_sequence(hdl, hdl->rep_code);
      free(cmd);
    }
  free(hdl->path);
  close(hdl->ctrl_fd);
}
