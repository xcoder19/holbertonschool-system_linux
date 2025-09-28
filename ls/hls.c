#include <dirent.h>
#include <stdio.h>

/**
 * main - entry point
 *
 * Return: 1 if error and 0 if success
 */
int main(void)
{
	DIR			  *directory;
	struct dirent *entry;

	directory = opendir(".");

	if (directory == NULL)
	{
		return (1);
	}

	while ((entry = readdir(directory)) != NULL)
	{
		if (entry->d_name[0] != '.')
		{
			printf("%s ", entry->d_name);
		}
	}
	if (closedir(directory) == -1)
	{
		return (1);
	}
	return (0);
}
