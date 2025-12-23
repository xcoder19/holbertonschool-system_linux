#include "laps.h"

/**
 * car_exists - check if a car with given id exists in the array
 * @cars: pointer to Cars dynamic array
 * @id: car identifier to search for
 * Return: true if car exists, false otherwise
 */
bool car_exists(Cars *cars, int id)
{
	for (size_t i = 0; i < cars->count; i++)
	{
		if (cars->items[i].id == id)
			return (true);
	}
	return (false);
}

/**
 * create_car - create a new car and add it to the array
 * @cars: pointer to Cars dynamic array
 * @id: car identifier
 */
void create_car(Cars *cars, int id)
{
	Car new_car;

	new_car.id	 = id;
	new_car.laps = 0;

	da_append(cars, new_car);

	printf("Car %d joined the race\n", id);
}

/**
 * increment_lap_for_car - increment lap count for a specific car
 * @cars: pointer to Cars dynamic array
 * @id: car identifier to increment
 */
void increment_lap_for_car(Cars *cars, int id)
{
	for (size_t i = 0; i < cars->count; i++)
	{
		if (cars->items[i].id == id)
		{
			cars->items[i].laps++;
			return;
		}
	}
}

/**
 * freeall - free all memory and reset the cars array
 * @cars: pointer to Cars dynamic array
 */
void freeall(Cars *cars)
{
	free(cars->items);
	cars->items	   = NULL;
	cars->count	   = 0;
	cars->capacity = 0;
}

/**
 * race_state - update and display the state of the race
 * @id: array of car identifiers
 * @size: number of cars in the array
 */

void race_state(int *id, size_t size)
{
	static Cars cars = {0};

	if (size == 0)
	{
		freeall(&cars);
		return;
	}

	for (size_t i = 0; i < size; ++i)
	{
		if (!car_exists(&cars, id[i]))
		{
			create_car(&cars, id[i]);
		}
		else
		{
			increment_lap_for_car(&cars, id[i]);
		}
	}

	puts("Race state:");
	sort_cars(&cars);
	for (size_t i = 0; i < cars.count; i++)

	{
		printf("Car %d [%d laps]\n", cars.items[i].id, cars.items[i].laps);
	}
}

