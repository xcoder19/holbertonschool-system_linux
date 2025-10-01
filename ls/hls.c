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
 * print_error - prints error and exit with status code 2
 * @prog_name : program name
 * @argument: argument
 */

void print_error(const char *prog_name, const char *argument)
{
	fprintf(stderr, "%s: cannot access '%s': %s\n", prog_name, argument,
			strerror(errno));
	exit(2);
}
/**
 * main - entry point
 * @argc: argument count
 * @argv: argument array
 * Return: 2 if error and 0 if success
 */
int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		DIR *dir = opendir(".");

		if (!dir)
			print_error(argv[0], NULL);

		iterate(dir);
		closedir(dir);
		return (0);
	}
	for (int i = argc - 1; i <= argc - 1 && i != 0; i--)
	{
		struct stat st;

		if (stat(argv[i], &st) == -1)
			print_error(argv[0], argv[i]);

		if (S_ISDIR(st.st_mode))
		{
			DIR *dir = opendir(argv[i]);

			if (!dir)
				print_error(argv[0], argv[i]);

			if (argc > 2)
				printf("%s:\n", argv[i]);

			iterate(dir);
			closedir(dir);
			if (i != 1)
				putchar('\n');
		}
		else
			printf("%s ", argv[i]);
	}
	return (0);
}
