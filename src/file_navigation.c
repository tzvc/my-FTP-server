/*
** file_navigation.c for myftp in /home/rootkid/rendu/psu/PSU_2016_myftp
** 
** Made by theo champion
** Login   <theo.champion@epitech.eu>
** 
** Started on  Wed May 10 20:34:44 2017 theo champion
** Last update Fri May 19 21:02:39 2017 theo champion
*/

#include "header.h"

bool	cmd_cwd(t_handle *hdl)
{
  char	*new_path;

  new_path = NULL;
  if ((new_path = gen_fullpath(hdl, hdl->cmd_arg)) == NULL)
    return (reply(hdl, 550, "Failed to change directory."));
  free(hdl->wd);
  hdl->wd = new_path;
  return (reply(hdl, 250, "Directory successfully changed."));
}

bool	cmd_cdup(t_handle *hdl)
{
  char	*new_path;

  new_path = NULL;
  if ((new_path = gen_fullpath(hdl, "..")) == NULL)
    return (reply(hdl, 550, "Failed to change directory."));
  free(hdl->wd);
  hdl->wd = new_path;
  return (reply(hdl, 250, "Directory successfully changed."));
}

bool		cmd_pwd(t_handle *hdl)
{
  size_t	offset;

  offset = strlen(hdl->home);
  offset += strlen(hdl->wd) == offset ? 0 : 1;
  return (reply(hdl, 257, "\"/%s\"", hdl->wd + offset));
}

bool		cmd_list(t_handle *hdl)
{
  FILE		*stream;
  char		*line;
  size_t	len;
  ssize_t	nread;

  if (!(stream = open_cmd_stream(hdl, (hdl->cmd_arg ? hdl->cmd_arg : "."))))
    return (reply(hdl, 450, "Requested file action not taken."));
  if (hdl->data_fd > 0)
    reply(hdl, 125, "Data connection already open; transfer starting.");
  else
    {
      reply(hdl, 150, "File status okay; about to open data connection.");
      if ((hdl->data_fd = accept(hdl->pasv_fd, (struct sockaddr *)0, 0)) <= 0)
        return (reply(hdl, 425, "Can't open data connection."));
    }
  len = 0;
  line = NULL;
  while ((nread = getline(&line, &len, stream)) != -1)
    write(hdl->data_fd, line, nread);
  free(line);
  pclose(stream);
  reply(hdl, 226, "Closing data connection.");
  close(hdl->data_fd);
  hdl->data_fd = -1;
  return (true);
}
