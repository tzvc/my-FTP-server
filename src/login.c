/*
** login.c for myftp in /home/rootkid/rendu/psu/PSU_2016_myftp
** 
** Made by theo champion
** Login   <theo.champion@epitech.eu>
** 
** Started on  Tue May  9 19:32:12 2017 theo champion
** Last update Wed May 10 16:44:30 2017 theo champion
*/

#include "header.h"

void	cmd_user(t_handle *hdl)
{
  if (hdl->login_status == 2)
    set_rep(hdl, 230, "User logged in, proceed.");
  else
    {
      if (!strcmp(USER, hdl->cmd_arg))
        hdl->login_status = 1;
      else
        hdl->login_status = 0;
      set_rep(hdl, 331, "Please specify the password.");
    }
}

void	cmd_pass(t_handle *hdl)
{
  if (hdl->login_status < 0)
    set_rep(hdl, 503, "Login with USER first.");
  else if (hdl->login_status == 0)
    set_rep(hdl, 530, "Login incorrect.");
  else
    {
      hdl->login_status = 2;
      set_rep(hdl, 230, "Login successful.");
    }
}

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

void	cmd_quit(t_handle *hdl)
{
  hdl->quit = true;
  set_rep(hdl, 221, "Goodbye.");
}
