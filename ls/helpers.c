#include "hls.h"

/**
 * _strlen - get length of string
 * @s: string
 * Return: length
 */
static int _strlen(const char *s)
{
	int len = 0;

	while (s[len])
		len++;
	return (len);
}

/**
 * _strdup - duplicate a string using malloc
 * @s: string to duplicate
 * Return: pointer to new string or NULL
 */
char *_strdup(const char *s)
{
	int	  len = _strlen(s);
	char *dup = malloc(len + 1);
	int	  i;

	if (!dup)
		return (NULL);
	for (i = 0; i <= len; i++)
		dup[i] = s[i];
	return (dup);
}

/**
 * _tolower - convert char to lowercase
 * @c: character
 * Return: lowercase char
 */
static int _tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + 32);
	return (c);
}

/**
 * _strcasecmp - case insensitive string compare
 * @s1: first string
 * @s2: second string
 * Return: difference
 */
int _strcasecmp(const char *s1, const char *s2)
{
	while (*s1 && *s2 && _tolower(*s1) == _tolower(*s2))
	{
		s1++;
		s2++;
	}
	return (_tolower(*s1) - _tolower(*s2));
}

/**
 * sort_strings - sort array of strings case-insensitively
 * @arr: array of strings
 * @n: number of elements
 */
void sort_strings(char **arr, int n)
{
	int	  i, j;
	char *tmp;

	for (i = 0; i < n - 1; i++)
		for (j = 0; j < n - i - 1; j++)
			if (_strcasecmp(arr[j], arr[j + 1]) > 0)
			{
				tmp		   = arr[j];
				arr[j]	   = arr[j + 1];
				arr[j + 1] = tmp;
			}
}

