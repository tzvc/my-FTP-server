/*
** file_action.c for myftp in /home/rootkid/rendu/psu/PSU_2016_myftp
** 
** Made by theo champion
** Login   <theo.champion@epitech.eu>
** 
** Started on  Thu May 11 11:20:45 2017 theo champion
** Last update Mon May 15 14:04:29 2017 theo champion
*/

#include "header.h"

bool	cmd_stor(t_handle *hdl)
{
  FILE		*file;
  int		nread;
  char		buf[BLOCK_SIZE];

  if (!hdl->cmd_arg)
    return (reply(hdl, 501, "Syntax error in parameters or arguments."));
  if ((file = open_file(hdl->path, hdl->cmd_arg, "w+")) == NULL)
    return (reply(hdl, 550, "Failed to open file."));
  log_msg(INFO, "File to retrieve is %s", hdl->cmd_arg);
  if (hdl->data_fd > 0)
    reply(hdl, 125, "Data connection already open; transfer starting.");
  else
    {
      reply(hdl, 150, "File status okay; about to open data connection.");
      if ((hdl->data_fd = accept(hdl->pasv_fd, (struct sockaddr*)0, 0)) <= 0)
        return (reply(hdl, 425, "Can't open data connection."));
    }
  while ((nread = read(hdl->data_fd, buf, BLOCK_SIZE)) > 0)
    if (fwrite(buf, sizeof(char), nread, file) != BLOCK_SIZE)
      log_msg(ERROR, "write: %s", strerror(errno));
  reply(hdl, 226, "Closing data connection.");
  close(hdl->data_fd);
  hdl->data_fd = -1;
  return (true);
}

bool		cmd_retr(t_handle *hdl)
{
  FILE		*file;
  int		nread;
  char		buf[BLOCK_SIZE];

  if (!hdl->cmd_arg)
    return (reply(hdl, 501, "Syntax error in parameters or arguments."));
  if ((file = open_file(hdl->path, hdl->cmd_arg, "r")) == NULL)
    return (reply(hdl, 550, "Failed to open file."));
  if (hdl->data_fd > 0)
    reply(hdl, 125, "Data connection already open; transfer starting.");
  else
    {
      reply(hdl, 150, "File status okay; about to open data connection.");
      if ((hdl->data_fd = accept(hdl->pasv_fd, (struct sockaddr*)0, 0)) <= 0)
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

bool	cmd_dele(t_handle *hdl)
{
  char	*fullpath;

  if (!hdl->cmd_arg)
    return (reply(hdl, 501, "Syntax error in parameters or arguments."));
  if (!(fullpath = malloc(sizeof(char) *
                          strlen(hdl->path) + strlen(hdl->cmd_arg) + 2)))
    return (false);
  sprintf(fullpath, "%s/%s", hdl->path, hdl->cmd_arg);
  log_msg(INFO, "File to access is %s", fullpath);
  if (access(fullpath, F_OK) == -1)
    reply(hdl, 550, "Requested action not taken. File unavailable.");
  else if (remove(fullpath) == -1)
    reply(hdl, 500, "Internal error: remove: %s", strerror(errno));
  else
    reply(hdl, 250, "Requested file action okay, completed.");
  free(fullpath);
  return (true);
}
