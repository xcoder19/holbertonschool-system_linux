#include "_getline.h"

/**
 * safe_free - frees memory and sets pointer to NULL
 * @ptr: pointer to pointer to free
 */
void safe_free(char **ptr)
{
	free(*ptr);
	*ptr = NULL;
}

/**
 * handle_eof - handles end of file or error from read
 * @bytes_read: return value from read()
 * @line: pointer to line buffer
 * @i: number of characters in line
 *
 * Return: line if partial data exists, NULL otherwise
 */
char *handle_eof(ssize_t bytes_read, char **line, int i)
{
	if (bytes_read == 0)
	{
		if (i == 0)
		{
			safe_free(line);
			return (NULL);
		}
		(*line)[i] = '\0';
		return (*line);
	}
	if (bytes_read == -1)
	{
		safe_free(line);
		return (NULL);
	}
	return (NULL);
}

/**
 * _getline - reads an entire line from a file descriptor
 * @fd: file descriptor to read from
 *
 * Return: null-terminated string without newline, or NULL on error/EOF
 */
char *_getline(const int fd)
{
	static char	   buffer[READ_SIZE];
	static ssize_t buffer_pos;
	static ssize_t buffer_len;
	int			   i	= 0;
	char		  *line = malloc(READ_SIZE);
	ssize_t		   bytes_read;
	char		  *result;

	if (line == NULL)
		return (NULL);
	while (1)
	{
		while (buffer_pos < buffer_len)
		{
			if (buffer[buffer_pos] == '\n')
			{
				line[i] = '\0';
				buffer_pos++;
				return (line);
			}
			line[i++] = buffer[buffer_pos++];
		}
		bytes_read = read(fd, buffer, READ_SIZE);
		if (bytes_read <= 0)
		{
			result = handle_eof(bytes_read, &line, i);
			return (result);
		}
		buffer_len = bytes_read;
		buffer_pos = 0;
	}
}
