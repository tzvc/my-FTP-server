/*
** client_handler.c for myftp in /home/rootkid/rendu/psu/PSU_2016_myftp
** 
** Made by theo champion
** Login   <theo.champion@epitech.eu>
** 
** Started on  Tue May  9 15:12:44 2017 theo champion
** Last update Mon May 15 17:01:42 2017 theo champion
*/

#include "header.h"

const char	*g_cmd_list[] =
  {
    "USER", "PASS", "QUIT", "CWD", "CDUP",
   "PWD", "PORT", "PASV", "STOR", "RETR",
   "LIST", "DELE","HELP", "NOOP"
  };

cmd_ptr	g_funcs[] =
  {
    cmd_user, cmd_pass, cmd_quit, cmd_cwd, cmd_cdup,
    cmd_pwd, cmd_port, cmd_pasv, cmd_stor, cmd_retr,
    cmd_list, cmd_dele, cmd_help, cmd_noop
  };

static char	*recv_cmd(int ctrl_fd)
{
  char		*cmd;
  int		i;

  i = 0;
  if ((cmd = malloc(sizeof(char) * CMD_SIZE)) == NULL)
    return (NULL);
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

  i = 0;
  hdl->cmd_nb = -1;
  hdl->cmd_arg = NULL;
  while (cmd[i] && cmd[i] != SP)
    i++;
  h = 0;
  while (g_cmd_list[h] && strncmp(cmd, g_cmd_list[h], i) != 0)
    h++;
  if (g_cmd_list[h])
    log_msg(INFO, "Executing command \"%s\"", g_cmd_list[h]);
  else
    log_msg(ERROR, "Unknown command \"%s\"", cmd);
  if (!g_cmd_list[h])
    return;
  hdl->cmd_nb = h;
  while (cmd[i] == SP)
    i++;
  if (!cmd[i])
    return;
  hdl->cmd_arg = &cmd[i];
}

static bool	exec_cmd(t_handle *hdl)
{
  if (hdl->cmd_nb < 0)
    return (reply(hdl, 502, "Command not implemented."));
  else if (hdl->cmd_nb >= 0 && hdl->cmd_nb <= 2)
    return (g_funcs[hdl->cmd_nb](hdl));
  else
    {
      if (hdl->login_status != LOGGED)
        return (reply(hdl, 530, "Please login with USER and PASS."));
      return (g_funcs[hdl->cmd_nb](hdl));
    }
}

bool		reply(t_handle *hdl, int code, const char *fmt, ...)
{
  char		*text;
  char		*reply;
  va_list	ap;
  size_t	len;

  va_start(ap, fmt);
  len = vsnprintf(NULL, 0, fmt, ap);
  va_start(ap, fmt);
  if ((text = malloc(sizeof(char) * len + 1)) == NULL)
    return (false);
  vsprintf(text, fmt, ap);
  if ((reply = malloc(sizeof(char) * strlen(text) + 7)) == NULL)
    return (false);
  sprintf(reply, "%d %s\r\n", code, text);
  write(hdl->ctrl_fd, reply, strlen(reply));
  free(text);
  free(reply);
  va_end(ap);
  return (code >= 300 ? false : true);
}

void		handle_client(t_handle *hdl)
{
  char		*cmd;

  reply(hdl, 220, "Welcome user, don't break anything pls.");
  hdl->login_status = 0;
  hdl->quit = false;
  while (!hdl->quit)
    {
      cmd = recv_cmd(hdl->ctrl_fd);
      parse_cmd(cmd, hdl);
      exec_cmd(hdl);
      free(cmd);
    }
  free(hdl->path);
  close(hdl->ctrl_fd);
}
