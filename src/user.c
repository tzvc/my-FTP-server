/*
** user.c for myftp in /home/rootkid/rendu/psu/PSU_2016_myftp
** 
** Made by theo champion
** Login   <theo.champion@epitech.eu>
** 
** Started on  Wed May 10 20:36:55 2017 theo champion
** Last update Fri May 12 15:47:00 2017 theo champion
*/

#include "header.h"

bool	cmd_user(t_handle *hdl)
{
  if (hdl->login_status == 2)
    return (reply(hdl, 230, "User logged in, proceed."));
  if (!strcmp(USER, hdl->cmd_arg))
    hdl->login_status = 1;
  else
    hdl->login_status = 0;
  return (reply(hdl, 331, "Please specify the password."));
}

bool	cmd_pass(t_handle *hdl)
{
  if (hdl->login_status < 0)
    return (reply(hdl, 503, "Login with USER first."));
  else if (hdl->login_status == 0)
    return (reply(hdl, 530, "Login incorrect."));
  hdl->login_status = 2;
  return (reply(hdl, 230, "Login successful."));
}

bool	cmd_quit(t_handle *hdl)
{
  hdl->quit = true;
  return (reply(hdl, 221, "Goodbye."));
}
