/*
** utils.c for myftp in /home/rootkid/rendu/psu/PSU_2016_myftp
** 
** Made by theo champion
** Login   <theo.champion@epitech.eu>
** 
** Started on  Wed May 10 16:24:37 2017 theo champion
** Last update Wed May 10 21:32:14 2017 theo champion
*/

#include "header.h"

void		set_rep(t_handle *hdl, int code, const char *fmt, ...)
{
  va_list	ap;
  size_t	len;

  va_start(ap, fmt);
  len = vsnprintf(NULL, 0, fmt, ap);
  va_start(ap, fmt);
  if ((hdl->rep_text = malloc(sizeof(char) * len + 1)) == NULL)
    return;
  vsprintf(hdl->rep_text, fmt, ap);
  hdl->rep_code = code;
  va_end(ap);
}
