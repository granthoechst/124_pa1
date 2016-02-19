#include <stdlib.h>
#include <stdio.h>
#include <time.h>

typedef struct tuple_point {
	float x;
	float y;
	float* edges;
} tuple_point;


float euc_dist (tuple_point a, tuple_point b) {
	return sqrt(pow((a.x - b.x), 2) + pow((a.y - b.y), 2));
}

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

tuple_point* case_2d_randgen (int seed, int v)
{
	if (seed == 0)
		srand(time(NULL));
	else
		srand(seed);

	tuple_point* array = malloc(v * sizeof(tuple_point));

	for (int i = 1 ; i < v ; i++)
	{
		array[i].x = (float) rand() / (float) RAND_MAX;
		array[i].y = (float) rand() / (float) RAND_MAX;
		array[i].edges = malloc(i * sizeof(float));
		for (int j = 0 ; j < i ; j++)
			array[i].edges[j] = euc_dist(array[i], array[j]);
	}

	return array;
}

int main(int argc, char *argv[]) {
	if (argc == 3)
	{
		printf("Case 1:\n\n");
		int seed = atoi(argv[1]);
		int v = atoi(argv[2]);
		float** arr = malloc(sizeof(float*));
		arr = case_1_randgen(seed, v);
		for (int i = 0; i < v; i++)
			for (int j = 0 ; j < i ; j++)
				printf("%f\n", arr[i][j]);

		printf("\nCase 2:\n\n");
		tuple_point* arr2 = malloc(sizeof(tuple_point*));
		arr2 = case_2d_randgen(seed, v);
		for (int i = 0; i < v; i++)
			for (int j = 0 ; j < i ; j++)
				printf("%f\n", arr2[i].edges[j]);
	}
	else
		printf("Yo! You suck!\n");
}