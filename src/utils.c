/*
** utils.c for myftp in /home/rootkid/rendu/psu/PSU_2016_myftp
** 
** Made by theo champion
** Login   <theo.champion@epitech.eu>
** 
** Started on  Wed May 10 16:24:37 2017 theo champion
** Last update Wed May 10 19:29:32 2017 theo champion
*/

#include "header.h"

void	set_rep(t_handle *hdl, int code, char *text)
{
  hdl->rep_code = code;
  hdl->rep_text = strdup(text);
}
