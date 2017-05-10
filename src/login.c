/*
** login.c for myftp in /home/rootkid/rendu/psu/PSU_2016_myftp
** 
** Made by theo champion
** Login   <theo.champion@epitech.eu>
** 
** Started on  Tue May  9 19:32:12 2017 theo champion
** Last update Wed May 10 12:25:46 2017 theo champion
*/

#include "header.h"

void	cmd_user(t_handle *hdl)
{
  if (hdl->login_status == 2)
    hdl->rep_code = 230;
  else
    {
      printf("cmd arg : %s\n", hdl->cmd_arg);
      if (!strcmp(USER, hdl->cmd_arg))
	hdl->login_status = 1;
      else
	hdl->login_status = 0;
      hdl->rep_code = 331;
    }
}

void	cmd_pass(t_handle *hdl)
{
  if (hdl->login_status < 1)
    hdl->rep_code = 332;
  else
    {
      hdl->login_status = 2;
      hdl->rep_code = 230;
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
      hdl->rep_code = 250;
    }
  else
    hdl->rep_code = 0;
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
      hdl->rep_code = 200;
    }
  else
    hdl->rep_code = 0;
  printf("new path: %s\n", hdl->path);
}

void	cmd_quit(t_handle *hdl)
{
  hdl->quit = true;
  hdl->rep_code = 221;
}
