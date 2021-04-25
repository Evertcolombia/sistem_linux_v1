#include "laps.h"

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

void race_state(int *id, size_t size){

	static int cars[18][2];
	static unsigned int count = 0;

	unsigned int i = 0, c = 0;

	if (size == 0)
		return;

	if (count == 0)
	{
		for (c = 0; count < size && c < size; c++)
		{
			cars[count][0] = id[c], cars[count][1] = 0;
			printf("Car %d joined the race\n", cars[count][0]);
			count++;
		}
	}
	else
	{
		for (i = 0, c = 0; i < count || c < size; i++)
		{
			if (cars[i][0] == id[c])
				cars[i][1] += 1, c++;
			else if (i + 1 == count && c + 1 == size)
			{
				i++;
				cars[i][0] = id[c], cars[i][1] = 0;
				printf("Car %d joined the race\n", cars[i][0]);
				count++, c++;
			}
		}
	}
	print_race_state(cars, count);
}
