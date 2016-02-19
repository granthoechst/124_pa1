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
	{
		int seed = atoi(argv[1]);
		int v = atoi(argv[2]);
		float** arr = malloc(sizeof(float*));
		arr = case_1_randgen(seed, v);
		for (int i = 1; i < v; i++)
			for (int j = 0 ; j < i ; j++)
				printf("%f\n", arr[i][j]);
	}
	else
		printf("Yo! You suck!\n");
}
