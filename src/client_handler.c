/*
** client_handler.c for myftp in /home/rootkid/rendu/psu/PSU_2016_myftp
** 
** Made by theo champion
** Login   <theo.champion@epitech.eu>
** 
** Started on  Tue May  9 15:12:44 2017 theo champion
** Last update Tue May 23 10:58:49 2017 theo champion
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

static bool	recv_and_parse_cmd(t_handle *hdl)
{
  char		*raw;
  char		cmd[5];
  size_t	len;
  unsigned int	h;
  FILE		*input_stream;

  len = 0;
  hdl->cmd_nb = -1;
  hdl->cmd_arg = NULL;
  raw = NULL;
  if ((input_stream = fdopen(dup(hdl->ctrl_fd), "r")) == NULL)
    return (false);
  if ((getline(&raw, &len, input_stream) == -1) || strlen(raw) <= 2)
    return (false);
  fclose(input_stream);
  if ((h = sscanf(raw, "%s %ms\r\n", cmd, &hdl->cmd_arg)) == 0)
    return (true);
  h = 0;
  while (strcmp(cmd, g_cmd_list[h]) != 0)
    if (++h >= (sizeof(g_cmd_list) / sizeof(g_cmd_list[0])))
      return (true);
  hdl->cmd_nb = h;
  return (true);
}

static bool	exec_cmd(t_handle *hdl)
{
  if (hdl->cmd_nb < 0)
    {
      log_msg(ERROR, "Command not implemented.");
      return (reply(hdl, 500, "Unknown command."));
    }
  log_msg(INFO, "Executing \"%s\" \"%s\"",
          g_cmd_list[hdl->cmd_nb], hdl->cmd_arg);
  if (hdl->cmd_nb >= 0 && hdl->cmd_nb <= 2)
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
  hdl->login_status = 0;
  hdl->data_fd = -1;
  hdl->quit = false;
  hdl->wd = strdup(hdl->home);
  reply(hdl, 220, "Welcome m8, don't break anything pls.");
  while (!hdl->quit)
    {
      if (recv_and_parse_cmd(hdl))
        {
          exec_cmd(hdl);
          if (hdl->cmd_arg)
            free(hdl->cmd_arg);
        }
    }
  free(hdl->home);
  free(hdl->wd);
  close(hdl->ctrl_fd);
}
