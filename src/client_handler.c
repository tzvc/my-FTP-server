/*
** client_handler.c for myftp in /home/rootkid/rendu/psu/PSU_2016_myftp
** 
** Made by theo champion
** Login   <theo.champion@epitech.eu>
** 
** Started on  Tue May  9 15:12:44 2017 theo champion
** Last update Thu May 18 19:39:10 2017 theo champion
*/

#include "header.h"

const char	*g_cmd_list[] =
  {
    "USER", "PASS", "QUIT", "CWD", "CDUP",
    "PWD", "PORT", "PASV", "STOR", "RETR",
    "LIST", "DELE","HELP", "NOOP", "TYPE"
  };

cmd_ptr	g_funcs[] =
  {
    cmd_user, cmd_pass, cmd_quit, cmd_cwd, cmd_cdup,
    cmd_pwd, cmd_port, cmd_pasv, cmd_stor, cmd_retr,
    cmd_list, cmd_dele, cmd_help, cmd_noop, cmd_type
  };

static void	recv_and_parse_cmd(t_handle *hdl)
{
  char		*raw;
  char		cmd[5];
  size_t	len;
  unsigned int	h;

  len = 0;
  hdl->cmd_nb = -1;
  hdl->cmd_arg = NULL;
  if (getline(&raw, &len, fdopen(hdl->ctrl_fd, "r")) == -1)
    return;
  if ((h = sscanf(raw, "%s %ms\r\n", cmd, &hdl->cmd_arg)) == 0)
    free(raw);
  if (h == 0)
    return;
  free(raw);
  h = 0;
  while (h < (sizeof(g_cmd_list) / sizeof(g_cmd_list[0])) &&
         (strcmp(cmd, g_cmd_list[h]) != 0))
    h++;
  if (!g_cmd_list[h])
    return;
  log_msg(INFO, "Executing \"%s\" \"%s\"", g_cmd_list[h], hdl->cmd_arg);
  hdl->cmd_nb = h;
}

static bool	exec_cmd(t_handle *hdl)
{
  if (hdl->cmd_nb < 0)
    return (reply(hdl, 500, "Unknown command."));
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
  reply(hdl, 220, "Welcome m8, don't break anything pls.");
  hdl->login_status = 0;
  hdl->data_fd = -1;
  hdl->quit = false;
  while (!hdl->quit)
    {
      recv_and_parse_cmd(hdl);
      exec_cmd(hdl);
    }
  free(hdl->path);
  close(hdl->ctrl_fd);
}
