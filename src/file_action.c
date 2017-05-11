/*
** file_action.c for myftp in /home/rootkid/rendu/psu/PSU_2016_myftp
** 
** Made by theo champion
** Login   <theo.champion@epitech.eu>
** 
** Started on  Thu May 11 11:20:45 2017 theo champion
** Last update Thu May 11 13:59:37 2017 theo champion
*/

#include "header.h"

void	cmd_stor(t_handle *hdl)
{
  (void)hdl;
}

void		cmd_retr(t_handle *hdl)
{
  char		*fullpath;
  FILE		*file;
  size_t	nread;
  char		buf[BLOCK_SIZE];

  if (hdl->data_fd > 0)
    {
      if (hdl->cmd_arg)
	{
	  fullpath = malloc(sizeof(char) *
			    strlen(hdl->path) + strlen(hdl->cmd_arg) + 2);
	  sprintf(fullpath, "%s/%s", hdl->path, hdl->cmd_arg);
	  if ((file = fopen(fullpath, "r")) != NULL)
	    {
	      while ((nread = fread(buf, sizeof(char), BLOCK_SIZE, file)) > 0)
		write(hdl->data_fd, buf, nread);
	    }
	  else
	    set_rep(hdl, 000, "File \"%s\" not found", fullpath);
	  free(fullpath);
	}
      else
	set_rep(hdl, 000, "Missing arg");
    }
  else
    set_rep(hdl, 000, "Data connection not open fd %d", hdl->data_fd);
}
