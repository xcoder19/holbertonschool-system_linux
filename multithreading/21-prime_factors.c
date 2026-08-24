#include "list.h"
#include "multithreading.h"
#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * add_factor - Allocates and adds a factor to a list
 * @list: List to which the factor is added
 * @factor: Factor value to add
 *
 * Return: 1 on success, 0 on error
 */
static int add_factor(list_t *list, unsigned long factor)
{
	node_t		  *node;
	unsigned long *value;

	value = malloc(sizeof(*value));

	if (value == NULL)
	{
		return (0);
	}
	*value = factor;
	node   = list_add(list, value);
	if (node == NULL)
	{
		free(value);
		return (0);
	}
	return (1);
}

/**
 * free_list - Destroys a list and its factor values
 * @list: List to destroy
 *
 * Return: Always NULL
 */
static list_t *free_list(list_t *list)
{
	list_destroy(list, free);
	free(list);
	return (NULL);
}

/**
 * parse_number - Converts a string to a positive unsigned long
 * @s: String to convert
 * @number: Address where the converted number is stored
 *
 * Return: 1 on success, 0 on error
 */
static int parse_number(char const *s, unsigned long *number)
{
	char *end;

	if (s == NULL)
		return (0);
	while (isspace((unsigned char)*s))
		s++;
	if (*s == '-' || *s == '\0')
		return (0);
	errno	= 0;
	*number = strtoul(s, &end, 10);
	if (errno == ERANGE || *end != '\0' || *number == 0)
		return (0);
	return (1);
}

/**
 * prime_factors - Finds the prime factors of a number
 * @s: String representation of number to factorize
 *
 * Return: List with malloced prime factors, NULL on error
 */
list_t *prime_factors(char const *s)
{
	unsigned long n;
	list_t		 *list;

	if (!parse_number(s, &n))
		return (NULL);
	list = malloc(sizeof(*list));
	if (list == NULL)
		return (NULL);
	list_init(list);

	while (n % 2 == 0)
	{
		if (!add_factor(list, 2))
			return (free_list(list));
		n /= 2;
	}

	for (unsigned long factor = 3; factor <= n / factor; factor += 2)
	{
		while (n % factor == 0)
		{
			if (!add_factor(list, factor))
				return (free_list(list));
			n /= factor;
		}
	}

	if (n > 2)
	{
		if (!add_factor(list, n))
			return (free_list(list));
	}
	return (list);
}
