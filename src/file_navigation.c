/*
** file_navigation.c for myftp in /home/rootkid/rendu/psu/PSU_2016_myftp
** 
** Made by theo champion
** Login   <theo.champion@epitech.eu>
** 
** Started on  Wed May 10 20:34:44 2017 theo champion
** Last update Wed May 10 21:10:42 2017 theo champion
*/

#include "header.h"

void	cmd_cwd(t_handle *hdl)
{
  char	*new_path;
  //Verif the user is logged in
  printf("path: %s\n", hdl->path);
  new_path = NULL;
  if (access(hdl->cmd_arg, F_OK) != -1)
    new_path = realpath(hdl->cmd_arg, NULL);
  if (new_path)
    {
      free(hdl->path);
      hdl->path = new_path;
      set_rep(hdl, 250, "Directory successfully changed.");
    }
  else
    set_rep(hdl, 550, "Failed to change directory.");
  printf("new path: %s\n", hdl->path);
}

void	cmd_cdup(t_handle *hdl)
{
  int	i;
  //Verif the user is logged in
  printf("cdup path: %s\n", hdl->path);
  i = strlen(hdl->path) - 1;
  while (hdl->path[i] && hdl->path[i] != '/')
    i--;
  if (hdl->path[i + 1])
    {
      hdl->path[(i > 0 ? i : i + 1)] = 0;
      hdl->path = realloc(hdl->path, (i > 0 ? i : i + 1));
      set_rep(hdl, 200, "Directory successfully changed.");
    }
  else
    set_rep(hdl, 550, "Failed to change directory.");
  printf("new path: %s\n", hdl->path);
}

void	cmd_pwd(t_handle *hdl)
{
  set_rep(hdl, 257, "\"%s\"", hdl->path);
}
