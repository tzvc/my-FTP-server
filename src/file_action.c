/*
** file_action.c for myftp in /home/rootkid/rendu/psu/PSU_2016_myftp
** 
** Made by theo champion
** Login   <theo.champion@epitech.eu>
** 
** Started on  Thu May 11 11:20:45 2017 theo champion
** Last update Fri May 12 19:20:12 2017 theo champion
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
      if ((hdl->data_fd = accept(hdl->pasv_fd, (struct sockaddr*)NULL, NULL)) <= 0)
        return (reply(hdl, 425, "Can't open data connection."));
    }
  log_msg(DEBUG, "file opened correctly");
  while ((nread = read(hdl->data_fd, buf, BLOCK_SIZE)) > 0) {
    log_msg(DEBUG, "nread = %d", nread);
    if (fwrite(buf, sizeof(char), nread, file) != BLOCK_SIZE)
      log_msg(ERROR, "write: %s", strerror(errno));
  }
  log_msg(DEBUG, "nread = %d", nread);
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
