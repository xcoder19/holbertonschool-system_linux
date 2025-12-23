#ifndef LAPS_H
#define LAPS_H

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct
{
	int laps;
	int id;
} Car;

typedef struct
{
	Car	  *items;
	size_t count;
	size_t capacity;
} Cars;

void race_state(int *id, size_t size);
void sort_cars(Cars *cars);

#define da_append(da, item)                                                    \
	do                                                                         \
	{                                                                          \
		if ((da)->count >= (da)->capacity)                                     \
		{                                                                      \
			(da)->capacity = (da)->capacity == 0 ? 8 : (da)->capacity * 2;     \
			(da)->items =                                                      \
				realloc((da)->items, (da)->capacity * sizeof(*(da)->items));   \
		}                                                                      \
		(da)->items[(da)->count++] = (item);                                   \
	} while (0)

#endif /* LAPS_H */

