/*
** utils.c for myftp in /home/rootkid/rendu/psu/PSU_2016_myftp
** 
** Made by theo champion
** Login   <theo.champion@epitech.eu>
** 
** Started on  Wed May 10 16:24:37 2017 theo champion
** Last update Fri May 19 18:30:53 2017 theo champion
*/

#include "header.h"

void		log_msg(int mode, const char *fmt, ...)
{
  va_list	ap;

  va_start(ap, fmt);
  if (mode == INFO)
    fprintf(stderr, "\033[95m[INFO] ");
  else if (mode == ERROR)
    fprintf(stderr, "\033[91m[ERROR] ");
  else
    fprintf(stderr, "\033[93m[DEBUG] ");
  vfprintf(stderr, fmt, ap);
  fprintf(stderr, "\n\033[0m");
  va_end(ap);
}

char	*gen_fullpath(t_handle *hdl, char *path)
{
  char	*fullpath;
  char	*resolved;

  if (!path)
    return (NULL);
  if (!(fullpath = malloc(sizeof(char) *
			 strlen(hdl->wd) + strlen(path) + 2)))
    return (NULL);
  sprintf(fullpath, "%s/%s", hdl->wd, path);
  log_msg(INFO, "fullpath is \"%s\"", fullpath);
  resolved = realpath(fullpath, NULL);
  log_msg(INFO, "resolved is \"%s\"", resolved);
  free(fullpath);
  if (!resolved)
    return (NULL);
  if (strlen(resolved) < strlen(hdl->home))
    {
      free(resolved);
      return (strdup(hdl->home));
    }
  else
    return (resolved);
  return (NULL);
}

FILE	*open_file(t_handle *hdl, char *filepath, char *mode)
{
  char	*fullpath;
  char	*dirc;
  char	*basec;
  char	*dname;
  char	*bname;
  FILE	*file;

  dirc = strdup(filepath);
  basec = strdup(filepath);
  dname = dirname(dirc);
  bname = basename(basec);
  file = NULL;
  if ((fullpath = gen_fullpath(hdl, dname)) != NULL)
    {
      fullpath = realloc(fullpath, sizeof(char) *
                         strlen(fullpath) + strlen(bname) + 2);
      sprintf(fullpath, "%s/%s", fullpath, bname);
      file = fopen(fullpath, mode);
      log_msg(INFO, "File to open is \"%s\"", fullpath);
    }
  free(fullpath);
  free(dirc);
  free(basec);
  return (file);
}

DIR	*open_dir(t_handle *hdl, char *dirname)
{
  char	*fullpath;
  DIR	*dir;

  if (!(fullpath = gen_fullpath(hdl, dirname)))
    return (NULL);
  log_msg(INFO, "Dir to open is %s", fullpath);
  dir = opendir(fullpath);
  free(fullpath);
  return (dir);
}
