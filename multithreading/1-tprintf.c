#include "multithreading.h"
#include <stdarg.h>
#include <stdio.h>
/**
 * tprintf - prints a formatted string with thread ID
 * @format: format string
 *
 * Return: number of characters printed
 */
int tprintf(char const *format, ...)
{
	va_list args;
	int		ret = 0;

	va_start(args, format);
	printf("[%lu] ", pthread_self());
	ret = vprintf(format, args);
	va_end(args);
	return (ret);
}
