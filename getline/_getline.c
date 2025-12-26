#include "_getline.h"

/**
 * free_all_states - frees all fd states in the linked list
 * @head: pointer to head pointer of list
 */
void free_all_states(fd_state_t **head)
{
	fd_state_t *current = *head;
	fd_state_t *next;

	while (current != NULL)
	{
		next = current->next;
		free(current);
		current = next;
	}
	*head = NULL;
}

/**
 * get_fd_state - finds or creates state for a file descriptor
 * @head: pointer to head pointer of list
 * @fd: file descriptor to find
 *
 * Return: pointer to fd_state, or NULL on failure
 */
fd_state_t *get_fd_state(fd_state_t **head, int fd)
{
	fd_state_t *current = *head;
	fd_state_t *new_state;

	while (current != NULL)
	{
		if (current->fd == fd)
			return (current);
		current = current->next;
	}
	new_state = malloc(sizeof(fd_state_t));
	if (new_state == NULL)
		return (NULL);
	new_state->fd		  = fd;
	new_state->buffer_pos = 0;
	new_state->buffer_len = 0;
	new_state->next		  = *head;
	*head				  = new_state;
	return (new_state);
}

/**
 * read_line - reads a line from fd using given state
 * @state: fd state structure
 * @line: buffer to store line
 *
 * Return: line on success, NULL on EOF/error
 */
char *read_line(fd_state_t *state, char *line)
{
	int		i = 0;
	ssize_t bytes_read;

	while (1)
	{
		while (state->buffer_pos < state->buffer_len)
		{
			if (state->buffer[state->buffer_pos] == '\n')
			{
				line[i] = '\0';
				state->buffer_pos++;
				return (line);
			}
			line[i++] = state->buffer[state->buffer_pos++];
		}
		bytes_read = read(state->fd, state->buffer, READ_SIZE);
		if (bytes_read <= 0)
		{
			if (bytes_read == 0 && i > 0)
			{
				line[i] = '\0';
				return (line);
			}
			free(line);
			return (NULL);
		}
		state->buffer_len = bytes_read;
		state->buffer_pos = 0;
	}
}

/**
 * _getline - reads an entire line from a file descriptor
 * @fd: file descriptor to read from, -1 to free all and reset
 *
 * Return: null-terminated string without newline, or NULL on error/EOF
 */
char *_getline(const int fd)
{
	static fd_state_t *head;
	fd_state_t		  *state;
	char			  *line;

	if (fd == -1)
	{
		free_all_states(&head);
		return (NULL);
	}
	state = get_fd_state(&head, fd);
	if (state == NULL)
		return (NULL);
	line = malloc(READ_SIZE);
	if (line == NULL)
		return (NULL);
	return (read_line(state, line));
}
