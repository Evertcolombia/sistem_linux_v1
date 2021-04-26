#include "laps.h"

void keep_sort(int (*array)[2], ssize_t low, ssize_t high, size_t size);
ssize_t partition(int (*array)[2], ssize_t low, ssize_t high);
void do_swap(int (*array)[2], int pos1, int pos2);

/**
 * print_race_state - print cars in the race
 * @cars: int of array
 * @size: size of the array
 *
 * Return: None
 */
void print_race_state(int (*cars)[2], unsigned int size)
{
	unsigned int i = 0;

	printf("Race state:\n");
	for (i = 0; i < size; i++)
	{
		printf("Car %d [%d laps]\n", (*cars)[0], (*cars)[1]);
		cars++;
	}
}

/**
 * binary_search - binary sewarch in array 2D
 * @array: 2d array
 * @low: low pos
 * @high: high pos
 * @search: search num
 *
 * Return: index on success
 */
int binary_search(int (*array)[2], int low, int high, int search)
{
	int med;

	if (low > high)
		return (-1); /* Not found*/

	med = (low + high) / 2;

	if (array[med][0] == search)
		return (med);
	else if (search > array[med][0])
		return (binary_search(array, (med + 1), high, search));
	else
		return (binary_search(array, low, (med - 1), search));
}
/**
 * quick_sort -sorting algoritmh
 * @array: list array
 * @size: size array
 *
 * Return: none
 */
void quick_sort(int (*array)[2], size_t size)
{
	unsigned int low, high;

	if (size < 2 || !array)
		return;
	low = 0, high = size - 1;
	keep_sort(array, low, high, size);
}

/**
 * keep_sort - keep sorting the array
 * @array: list array
 * @low: low pont of the array
 * @high: high part of the array
 * @size: size array
 *
 * Return: None
 */

void keep_sort(int (*array)[2], ssize_t low, ssize_t high, size_t size)
{
	ssize_t pivot;

	if (low < high)
	{
		pivot = partition(array, low, high);
		keep_sort(array, low, pivot - 1, size);
		keep_sort(array, pivot + 1, high, size);
	}
}

/**
 * partition - partition the array
 * @array: list array
 * @low: low part of the array
 * @high: high part of the array
 *
 * Return: pivot point in the partitioned array
 */
ssize_t partition(int (*array)[2], ssize_t low, ssize_t high)
{
	int pivot;
	ssize_t i, j;

	pivot = array[high][0];
	i = (low - 1);

	for (j = low; j < high; j++)
	{
		if (array[j][0] < pivot)
		{
			i++;
			if (i != j)
				do_swap(array, i, j);
		}
	}

	if (array[i + 1][0] > array[high][0])
	{
		do_swap(array, (i + 1), high);
	}
	return (i + 1);
}

/**
 * do_swap - change  positions in array
 * @array: array list
 * @pos1: position to change
 * @pos2: position to change
 *
 * Return: array pointer
 */
void do_swap(int (*array)[2], int pos1, int pos2)
{
	int temp[2];

	temp[0] = array[pos1][0];
	temp[1] = array[pos1][1];
	array[pos1][0] = array[pos2][0];
	array[pos1][1] = array[pos2][1];
	array[pos2][0] = temp[0];
	array[pos2][1] = temp[1];
}


/**
 * race_state - main funciont on race
 * @id: id of arrays
 * @size: size of the array
 *
 * Return: None
 */
void race_state(int *id, size_t size)
{
	static int cars[100][2];
	static unsigned int count;

	unsigned int c = 0;
	int low = 0, res = 0, i = 0;

	if (size == 0)
		return;

	if (count == 0)
	{
		for (c = 0; count < size && c < size; c++)
		{
			cars[count][0] = id[c], cars[count][1] = 0;
			printf("Car %d joined the race\n", cars[count][0]);
			count++, i = 1;
		}
	}
	else
	{
		for (c = 0; c < size; c++)
		{
			res = binary_search(cars, low, count, id[c]);
			if (res == -1)
			{
				cars[count][0] = id[c], cars[count][1] = 0;
				printf("Car %d joined the race\n", cars[count][0]);
				count++, i = 1;
			}
			else
				cars[res][1] += 1;
		}
	}

	if (i > 0)
		quick_sort(cars, count);
	print_race_state(cars, count);
}
