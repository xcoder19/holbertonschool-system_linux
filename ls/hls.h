#ifndef HLS_H
#define HLS_H

#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/stat.h>

void print_error(const char *prog_name, const char *argument);
void iterate(DIR *directory);
int cmp(const void *a, const void *b);
int print_dirs(char **dirs, int dir_count, int argc, char *prog, int *printed);
int process_args(int argc, char **argv, char **files, char **dirs, int *counts);

#endif /* HLS_H */
