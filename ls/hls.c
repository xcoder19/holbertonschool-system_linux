#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/stat.h>

/**
 * cmp - compare function for qsort (case-insensitive)
 * @a: first string pointer
 * @b: second string pointer
 * Return: comparison result
 */
int cmp(const void *a, const void *b)
{
	return (strcasecmp(*(const char **)a, *(const char **)b));
}

/**
 * print_error - prints error message to stderr
 * @prog_name: program name
 * @argument: argument
 */
void print_error(const char *prog_name, const char *argument)
{
	fprintf(stderr, "%s: cannot access %s: %s\n", prog_name, argument,
			strerror(errno));
}

/**
 * iterate - iterate on directory and print name of files (sorted)
 * @directory: DIR *
 */
void iterate(DIR *directory)
{
	struct dirent *entry;
	char		 **names;
	int			   count = 0, cap = 64, i;

	names = malloc(sizeof(char *) * cap);
	if (!names)
		return;
	while ((entry = readdir(directory)) != NULL)
		if (entry->d_name[0] != '.')
		{
			if (count >= cap)
			{
				cap *= 2;
				names = realloc(names, sizeof(char *) * cap);
				if (!names)
					return;
			}
			names[count] = strdup(entry->d_name);
			if (!names[count])
				return;
			count++;
		}
	if (count > 1)
		qsort(names, count, sizeof(char *), cmp);
	for (i = 0; i < count; i++)
	{
		printf("%s", names[i]);
		if (i < count - 1)
			printf("  ");
		free(names[i]);
	}
	putchar('\n');
	free(names);
}

/**
 * print_dir - print a single directory
 * @name: directory name
 * @prog: program name
 * @multi: if multiple arguments
 * @p: pointer to printed flag
 * Return: 0 on success, 2 on error
 */
int print_dir(char *name, char *prog, int multi, int *p)
{
	DIR *dir = opendir(name);

	if (!dir)
	{
		print_error(prog, name);
		return (2);
	}
	if (*p)
		putchar('\n');
	if (multi)
		printf("%s:\n", name);
	iterate(dir);
	closedir(dir);
	*p = 1;
	return (0);
}

/**
 * main - entry point
 * @argc: argument count
 * @argv: argument array
 * Return: 2 if error and 0 if success
 */
int main(int argc, char *argv[])
{
	int			s = 0, i, fc = 0, dc = 0, p = 0;
	char	  **f, **d;
	struct stat st;

	if (argc < 2)
	{
		p = 0;
		return (print_dir(".", argv[0], 0, &p) ? 2 : 0);
	}
	f = malloc(sizeof(char *) * argc);
	d = malloc(sizeof(char *) * argc);
	if (!f || !d)
		return (2);
	for (i = 1; i < argc; i++)
		if (stat(argv[i], &st) == -1)
		{
			print_error(argv[0], argv[i]);
			s = 2;
		}
		else if (S_ISDIR(st.st_mode))
			d[dc++] = argv[i];
		else
			f[fc++] = argv[i];
	if (fc > 1)
		qsort(f, fc, sizeof(char *), cmp);
	if (dc > 1)
		qsort(d, dc, sizeof(char *), cmp);
	for (i = 0; i < fc; i++, p = 1)
		printf("%s\n", f[i]);
	for (i = 0; i < dc; i++)
		if (print_dir(d[i], argv[0], argc > 2, &p))
			s = 2;
	free(f);
	free(d);
	return (s);
}

