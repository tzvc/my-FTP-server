/*
** file_action.c for myftp in /home/rootkid/rendu/psu/PSU_2016_myftp
** 
** Made by theo champion
** Login   <theo.champion@epitech.eu>
** 
** Started on  Thu May 11 11:20:45 2017 theo champion
** Last update Fri May 19 15:17:43 2017 theo champion
*/

#include "header.h"

bool		cmd_stor(t_handle *hdl)
{
  FILE		*file;
  size_t	nread;
  char		buf[BLOCK_SIZE];

  if (!hdl->cmd_arg)
    return (reply(hdl, 501, "Syntax error in parameters or arguments."));
  if ((file = open_file(hdl, hdl->cmd_arg, "wb")) == NULL)
    return (reply(hdl, 550, "Failed to open file."));
  log_msg(INFO, "File to receive is \"%s\"", hdl->cmd_arg);
  if (hdl->data_fd > 0)
    reply(hdl, 125, "Data connection already open; transfer starting.");
  else
    {
      reply(hdl, 150, "File status okay; about to open data connection.");
      if ((hdl->data_fd = accept(hdl->pasv_fd, (struct sockaddr *)0, 0)) <= 0)
        return (reply(hdl, 425, "Can't open data connection."));
    }
  while ((nread = read(hdl->data_fd, buf, BLOCK_SIZE)) > 0)
    if (fwrite(buf, sizeof(char), nread, file) < nread)
      return (reply(hdl, 426, "Connection closed; transfer aborted."));
  reply(hdl, 226, "Closing data connection.");
  close(hdl->data_fd);
  fclose(file);
  hdl->data_fd = -1;
  return (true);
}

bool		cmd_retr(t_handle *hdl)
{
  FILE		*file;
  size_t	nread;
  char		buf[BLOCK_SIZE];

  if (!hdl->cmd_arg)
    return (reply(hdl, 501, "Syntax error in parameters or arguments."));
  if ((file = open_file(hdl, hdl->cmd_arg, "rb")) == NULL)
    return (reply(hdl, 550, "Failed to open file."));
  if (hdl->data_fd > 0)
    reply(hdl, 125, "Data connection already open; transfer starting.");
  else
    {
      reply(hdl, 150, "File status okay; about to open data connection.");
      if ((hdl->data_fd = accept(hdl->pasv_fd, (struct sockaddr *)0, 0)) <= 0)
        return (reply(hdl, 425, "Can't open data connection."));
    }
  while ((nread = fread(buf, sizeof(char), BLOCK_SIZE, file)) > 0)
    if (write(hdl->data_fd, buf, nread) == -1)
      return (reply(hdl, 426, "Connection closed; transfer aborted."));
  reply(hdl, 226, "Closing data connection.");
  close(hdl->data_fd);
  fclose(file);
  hdl->data_fd = -1;
  return (true);
}

bool	cmd_dele(t_handle *hdl)
{
  char	*fullpath;

  if (!hdl->cmd_arg)
    return (reply(hdl, 501, "Syntax error in parameters or arguments."));
  if (!(fullpath = gen_fullpath(hdl, hdl->cmd_arg)))
    return (reply(hdl, 550, "Requested action not taken. File unavailable."));
  if (remove(fullpath) == -1)
    reply(hdl, 500, "Internal error: remove: %s", strerror(errno));
  else
    reply(hdl, 250, "Requested file action okay, completed.");
  free(fullpath);
  return (true);
}
