#include <stdlib.h>
#include <stdio.h>
#include <time.h>

float** case_1_randgen (int seed, int v)
{
	if (seed == 0)
		srand(time(NULL));
	else
		srand(seed);

	float** array = malloc(v * sizeof(float*));

	for (int i = 1 ; i < v ; i++)
	{
		array[i] = malloc(i * sizeof(float));
		for (int j = 0 ; j < i ; j++)
			array[i][j] = (float) rand() / (float) RAND_MAX ;
	}

	return array;

}

int main(int argc, char *argv[]) {
	if (argc == 3)
		float** arr = case_1_randgen(atoi(argv[1]), atoi(argv[2]));
	else
		printf("Yo! You suck!\n");
}