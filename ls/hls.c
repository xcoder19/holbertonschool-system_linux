#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * iterate - iterate throught directories and files
 * @directory: directory
 * @entry: entry
 * Return: 1 if error and 0 if success
 */

int iterate(DIR *directory, struct dirent *entry)
{

	while ((entry = readdir(directory)) != NULL)
	{
		if (entry->d_name[0] != '.')
			printf("%s ", entry->d_name);
	}
	putchar('\n');
	return (0);
}
/**
 * main - entry point
 * @argc: argument count
 * @argv: argument array
 * Return: 1 if error and 0 if success
 */
int main(int argc, char *argv[])
{
	DIR			  *directory;
	struct dirent *entry = NULL;

	if (argc >= 2)
	{
		for (int i = 1; i < argc; i++)
		{
			if (argc >= 3)
				printf("%s:\n", argv[i]);

			directory = opendir(argv[i]);
			if (directory == NULL)
			{
				fprintf(stderr, "%s: %s %s: %s", argv[0], "cannot acess",
						argv[i], "No such a file or directory");
				return (1);
			}

			iterate(directory, entry);

			if (closedir(directory) == -1)
				return (1);
		}
	}
	else
	{
		directory = opendir(".");

		if (directory == NULL)
			return (1);

		iterate(directory, entry);

		if (closedir(directory) == -1)
			return (1);
	}
	return (0);
}
