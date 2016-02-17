#include <stdlib.h>
#include <stdio.h>
#include <time.h>

float** case_1_randgen (int seed, int v)
{
	if (seed == 0)
		srand(time(NULL));
	else
		srand(seed);

	float** array = malloc(v * size_of(float));

	for (int i = 1 ; i < v ; i++)
	{
		array[i] = malloc(i * size_of(float));
		for (int j = 0 ; j < i ; j++)
			array[i][j] = (float) rand() / (float) RAND_MAX ;
	}

	return array;

}