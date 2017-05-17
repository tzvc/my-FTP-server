/*
** utils.c for myftp in /home/rootkid/rendu/psu/PSU_2016_myftp
** 
** Made by theo champion
** Login   <theo.champion@epitech.eu>
** 
** Started on  Wed May 10 16:24:37 2017 theo champion
** Last update Wed May 17 12:12:16 2017 theo champion
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

FILE	*open_file(char *path, char *filename, char *mode)
{
  char	*fullpath;
  FILE	*file;

  if (!(fullpath = malloc(sizeof(char) *
                          strlen(path) + strlen(filename) + 2)))
    return (NULL);
  sprintf(fullpath, "%s/%s", path, filename);
  log_msg(INFO, "File to open is %s", fullpath);
  file = fopen(fullpath, mode);
  free(fullpath);
  return (file);
}

DIR	*open_dir(char *path, char *dirname)
{
  char	*fullpath;
  DIR	*dir;

  if (!(fullpath = malloc(sizeof(char) *
                          strlen(path)
                          + (dirname ? strlen(dirname) : 1) + 2)))
    return (NULL);
  if (dirname)
    sprintf(fullpath, "%s/%s", path, dirname);
  else
    sprintf(fullpath, "%s/.", path);
  log_msg(INFO, "Dir to open is %s", fullpath);
  dir = opendir(fullpath);
  free(fullpath);
  return (dir);
}
