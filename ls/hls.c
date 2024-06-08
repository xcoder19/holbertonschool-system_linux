#include <stdio.h>
#include <dirent.h>

/**
 * main - entry point
 *
 * Return: 1 if error and 0 if success
 */
int main(void)
{
	struct dirent *entry;
	DIR *dp = opendir(".");

	if (dp == NULL)
	{
		perror("opendir");
		return (1);
	}

	while ((entry = readdir(dp)))
	{
		if (entry->d_name[0] != '.')
		printf("%s  ", entry->d_name);
	}

	closedir(dp);
	printf("\n");

	return (0);
}
