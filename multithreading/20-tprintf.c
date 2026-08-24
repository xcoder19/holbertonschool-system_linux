#include "multithreading.h"
#include <pthread.h>
#include <stdarg.h>
#include <stdio.h>

/**
 * tprintf - prints a formatted string with thread ID
 * @format: format string
 *
 * Return: number of characters printed
 */

pthread_mutex_t my_mutex = PTHREAD_MUTEX_INITIALIZER;

int tprintf(char const *format, ...)
{
	va_list args;
	int		ret = 0;

	(void)format;
	va_start(args, format);
	pthread_mutex_lock(&my_mutex);
	printf("[%lu] ", pthread_self());
	ret = vprintf(format, args);
	pthread_mutex_unlock(&my_mutex);
	va_end(args);
	return (ret);
}
