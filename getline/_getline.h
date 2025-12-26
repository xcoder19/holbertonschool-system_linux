#ifndef _GETLINE_H
#define _GETLINE_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define READ_SIZE 1024

/**
 * struct fd_state_s - state for a file descriptor
 * @fd: file descriptor
 * @buffer: read buffer
 * @buffer_pos: current position in buffer
 * @buffer_len: bytes currently in buffer
 * @next: pointer to next fd_state
 */
typedef struct fd_state_s
{
	int				   fd;
	char			   buffer[READ_SIZE];
	ssize_t			   buffer_pos;
	ssize_t			   buffer_len;
	struct fd_state_s *next;
} fd_state_t;

char *_getline(const int fd);

#endif /* _GETLINE_H */

