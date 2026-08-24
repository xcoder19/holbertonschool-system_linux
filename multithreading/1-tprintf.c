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

	va_start(args, format);
	printf("[%lu] ", pthread_self());
	int ret = vprintf(format, args);

	va_end(args);
	return (ret);
}
