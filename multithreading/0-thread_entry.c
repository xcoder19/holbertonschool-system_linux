#include "multithreading.h"
#include <stdio.h>
#include <pthread.h>

/**
 * thread_entry - entry point to a new thread
 * @arg: argument
 *
 * Return: NULL
 */
void *thread_entry(void *arg)
{
	printf("%s\n", (char *)arg);
	pthread_exit(NULL);
	return (NULL);
}
