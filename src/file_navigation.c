/*
** file_navigation.c for myftp in /home/rootkid/rendu/psu/PSU_2016_myftp
** 
** Made by theo champion
** Login   <theo.champion@epitech.eu>
** 
** Started on  Wed May 10 20:34:44 2017 theo champion
** Last update Mon May 15 14:05:22 2017 theo champion
*/

#include "header.h"

bool	cmd_cwd(t_handle *hdl)
{
  char	*new_path;

  new_path = NULL;
  if (access(hdl->cmd_arg, F_OK) != -1)
    new_path = realpath(hdl->cmd_arg, NULL);
  if (new_path)
    {
      free(hdl->path);
      hdl->path = new_path;
      return (reply(hdl, 250, "Directory successfully changed."));
    }
  return (reply(hdl, 550, "Failed to change directory."));
}

bool	cmd_cdup(t_handle *hdl)
{
  int	i;

  i = strlen(hdl->path) - 1;
  while (hdl->path[i] && hdl->path[i] != '/')
    i--;
  if (hdl->path[i + 1])
    {
      hdl->path[(i > 0 ? i : i + 1)] = 0;
      hdl->path = realloc(hdl->path, sizeof(char) * (strlen(hdl->path) + 1));
      return (reply(hdl, 200, "Directory successfully changed."));
    }
  log_msg(INFO, "New path set to \"%s\"\n", hdl->path);
  return (reply(hdl, 550, "Failed to change directory."));
}

bool	cmd_pwd(t_handle *hdl)
{
  return (reply(hdl, 257, "\"%s\"", hdl->path));
}

bool		cmd_list(t_handle *hdl)
{
  DIR		*dir;
  struct dirent	*ep;

  if (!(dir = open_dir(hdl->path, hdl->cmd_arg)))
    return (reply(hdl, 500, "Cannot open dir."));
  if (hdl->data_fd > 0)
    reply(hdl, 125, "Data connection already open; transfer starting.");
  else
    {
      reply(hdl, 150, "File status okay; about to open data connection.");
      if ((hdl->data_fd = accept(hdl->pasv_fd, (struct sockaddr*)NULL, NULL)) <= 0)
        return (reply(hdl, 425, "Can't open data connection."));
    }
  log_msg(DEBUG, "Directory opened correctly");
  while ((ep = readdir(dir)) != NULL)
    {
      write(hdl->data_fd, ep->d_name, strlen(ep->d_name));
      write(hdl->data_fd, "\n", 1);
    }
  closedir(dir);
  reply(hdl, 226, "Closing data connection.");
  close(hdl->data_fd);
  hdl->data_fd = -1;
  return (true);
}
