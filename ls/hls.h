#ifndef HLS_H
#define HLS_H

#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

void  print_error(const char *prog_name, const char *argument);
int	  print_dir(char *name, char *prog, int multi, int *p);
void  sort_strings(char **arr, int n);
char *_strdup(const char *s);
int	  _strcasecmp(const char *s1, const char *s2);

#endif

