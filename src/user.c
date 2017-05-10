/*
** user.c for myftp in /home/rootkid/rendu/psu/PSU_2016_myftp
** 
** Made by theo champion
** Login   <theo.champion@epitech.eu>
** 
** Started on  Wed May 10 20:36:55 2017 theo champion
** Last update Wed May 10 20:36:57 2017 theo champion
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

void	cmd_quit(t_handle *hdl)
{
  hdl->quit = true;
  set_rep(hdl, 221, "Goodbye.");
}
