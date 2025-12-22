#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
void print_error(const char *prog_name, const char *argument);
void iterate(DIR *directory);

/**
 * iterate - iterate on directory and print name of files
 * @directory: DIR *
 * Return: 1 if error and 0 if success
 */

void iterate(DIR *directory)
{
	struct dirent *entry;

	while ((entry = readdir(directory)) != NULL)
	{
		if (entry->d_name[0] != '.')
			printf("%s ", entry->d_name);
	}
	putchar('\n');
}

/**
 * print_error - prints error message to stderr
 * @prog_name : program name
 * @argument: argument
 */

void print_error(const char *prog_name, const char *argument)
{
	fprintf(stderr, "%s: cannot access %s: %s\n", prog_name, argument,
			strerror(errno));
}
/**
 * main - entry point
 * @argc: argument count
 * @argv: argument array
 * Return: 2 if error and 0 if success
 */
int main(int argc, char *argv[])
{
	int exit_status = 0;
	int i;

	if (argc < 2)
	{
		DIR *dir = opendir(".");

		if (!dir)
		{
			print_error(argv[0], ".");
			return (2);
		}

		iterate(dir);
		closedir(dir);
		return (0);
	}
	for (i = argc - 1; i >= 1; i--)
	{
		struct stat st;

		if (stat(argv[i], &st) == -1)
		{
			print_error(argv[0], argv[i]);
			exit_status = 2;
			continue;
		}

		if (S_ISDIR(st.st_mode))
		{
			DIR *dir = opendir(argv[i]);

			if (!dir)
			{
				print_error(argv[0], argv[i]);
				exit_status = 2;
				continue;
			}

			if (argc > 2)
				printf("%s:\n", argv[i]);

			iterate(dir);
			closedir(dir);
			if (i != 1)
				putchar('\n');
		}
		else
			printf("%s\n", argv[i]);
	}
	return (exit_status);
}
