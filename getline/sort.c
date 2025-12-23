#include "laps.h"

/**
 * sort_cars - sort cars array by id using bubble sort
 * @cars: pointer to Cars dynamic array
 */
void sort_cars(Cars *cars)
{
	size_t i, j;
	Car	   tmp;

	for (i = 0; i < cars->count - 1; i++)
	{
		for (j = 0; j < cars->count - i - 1; j++)
		{
			if (cars->items[j].id > cars->items[j + 1].id)
			{
				tmp				   = cars->items[j];
				cars->items[j]	   = cars->items[j + 1];
				cars->items[j + 1] = tmp;
			}
		}
	}
}
