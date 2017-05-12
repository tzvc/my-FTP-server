/*
** file_action.c for myftp in /home/rootkid/rendu/psu/PSU_2016_myftp
** 
** Made by theo champion
** Login   <theo.champion@epitech.eu>
** 
** Started on  Thu May 11 11:20:45 2017 theo champion
** Last update Fri May 12 17:59:33 2017 theo champion
*/

#include "header.h"

bool	cmd_stor(t_handle *hdl)
{
  (void)hdl;
  return (true);
}

bool		cmd_retr(t_handle *hdl)
{
  char		*fullpath;
  FILE		*file;
  int		nread;
  char		buf[BLOCK_SIZE];

  if (!hdl->cmd_arg)
    return (reply(hdl, 501, "Syntax error in parameters or arguments."));
  fullpath = malloc(sizeof(char) *
                    strlen(hdl->path) + strlen(hdl->cmd_arg) + 2);
  sprintf(fullpath, "%s/%s", hdl->path, hdl->cmd_arg);
  log_msg(INFO, "File to retrieve is %s", fullpath);
  file = fopen(fullpath, "r");
  free(fullpath);
  if (!file)
    return (reply(hdl, 550, "Failed to open file \"%s\"", fullpath));
  if (hdl->data_fd > 0)
    reply(hdl, 125, "Data connection already open; transfer starting.");
  else
    {
      reply(hdl, 150, "File status okay; about to open data connection.");
      if ((hdl->data_fd = accept(hdl->pasv_fd, (struct sockaddr*)NULL, NULL)) <= 0)
	return (reply(hdl, 425, "Can't open data connection."));
    }
  log_msg(DEBUG, "file opened correctly");
  while ((nread = fread(buf, sizeof(char), BLOCK_SIZE, file)) > 0)
    if (write(hdl->data_fd, buf, nread) == -1)
      log_msg(ERROR, "write: %s", strerror(errno));
  reply(hdl, 226, "Closing data connection.");
  close(hdl->data_fd);
  hdl->data_fd = -1;
  return (true);
}
