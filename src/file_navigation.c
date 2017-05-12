/*
** file_navigation.c for myftp in /home/rootkid/rendu/psu/PSU_2016_myftp
** 
** Made by theo champion
** Login   <theo.champion@epitech.eu>
** 
** Started on  Wed May 10 20:34:44 2017 theo champion
** Last update Fri May 12 15:48:49 2017 theo champion
*/

#include "header.h"

bool	cmd_cwd(t_handle *hdl)
{
  char	*new_path;
  //Verif the user is logged in
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
  //Verif the user is logged in
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
