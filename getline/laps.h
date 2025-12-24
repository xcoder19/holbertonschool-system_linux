#ifndef LAPS_H
#define LAPS_H

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * struct Car - represents a car in the race
 * @laps: number of laps completed by the car
 * @id: unique identifier of the car
 */
typedef struct Car
{
	int laps;
	int id;
} Car;

/**
 * struct Cars - dynamic array of cars
 * @items: pointer to array of Car structs
 * @count: number of cars currently in the array
 * @capacity: total allocated capacity of the array
 */
typedef struct Cars
{
	Car	  *items;
	size_t count;
	size_t capacity;
} Cars;

void race_state(int *id, size_t size);
void sort_cars(Cars *cars);

#endif /* LAPS_H */
