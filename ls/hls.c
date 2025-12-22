#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

void print_error(const char *prog_name, const char *argument);
void iterate(DIR *directory);
int	 cmp(const void *a, const void *b);

/**
 * cmp - compare function for qsort
 * @a: first string pointer
 * @b: second string pointer
 * Return: comparison result
 */
int cmp(const void *a, const void *b)
{
	return (strcmp(*(const char **)a, *(const char **)b));
}

/**
 * iterate - iterate on directory and print name of files
 * @directory: DIR *
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
	int			exit_status = 0;
	int			i, file_count = 0, dir_count = 0;
	char	  **files, **dirs;
	struct stat st;
	int			printed = 0;

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

	files = malloc(sizeof(char *) * argc);
	dirs  = malloc(sizeof(char *) * argc);
	if (!files || !dirs)
		return (2);

	/* First pass: categorize arguments and handle errors */
	for (i = 1; i < argc; i++)
	{
		if (stat(argv[i], &st) == -1)
		{
			print_error(argv[0], argv[i]);
			exit_status = 2;
			continue;
		}
		if (S_ISDIR(st.st_mode))
			dirs[dir_count++] = argv[i];
		else
			files[file_count++] = argv[i];
	}

	/* Sort files and directories alphabetically */
	if (file_count > 1)
		qsort(files, file_count, sizeof(char *), cmp);
	if (dir_count > 1)
		qsort(dirs, dir_count, sizeof(char *), cmp);

	/* Print files first (no blank lines between them) */
	for (i = 0; i < file_count; i++)
	{
		printf("%s\n", files[i]);
		printed = 1;
	}

	/* Print directories */
	for (i = 0; i < dir_count; i++)
	{
		DIR *dir = opendir(dirs[i]);

		if (!dir)
		{
			print_error(argv[0], dirs[i]);
			exit_status = 2;
			continue;
		}

		if (printed)
			putchar('\n');

		if (argc > 2)
			printf("%s:\n", dirs[i]);

		iterate(dir);
		closedir(dir);
		printed = 1;
	}

	free(files);
	free(dirs);
	return (exit_status);
}
