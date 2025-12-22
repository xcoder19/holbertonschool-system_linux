#include "hls.h"

/**
 * main - entry point
 * @argc: argument count
 * @argv: argument array
 * Return: 2 if error and 0 if success
 */
int main(int argc, char *argv[])
{
	int	   exit_status = 0, i, printed = 0, counts[2] = {0, 0};
	char **files, **dirs;
	DIR	  *dir;

	if (argc < 2)
	{
		dir = opendir(".");
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
	exit_status = process_args(argc, argv, files, dirs, counts);
	if (counts[0] > 1)
		qsort(files, counts[0], sizeof(char *), cmp);
	if (counts[1] > 1)
		qsort(dirs, counts[1], sizeof(char *), cmp);
	for (i = 0; i < counts[0]; i++)
	{
		printf("%s\n", files[i]);
		printed = 1;
	}
	if (print_dirs(dirs, counts[1], argc, argv[0], &printed) == 2)
		exit_status = 2;
	free(files);
	free(dirs);
	return (exit_status);
}
