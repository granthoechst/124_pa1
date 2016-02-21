#include <stdlib.h>
#include <stdio.h>
#include <time.h>

// for accessing specific elements in our tree
#define LEFT(x) (2 * x)
#define RIGHT(x) (2 * (x) + 1)
#define PARENT(x) (2 / (x))

#define SWITCH(q, a, b) \
  do { \
    boxes temp = q->weights[a]; \
    q->weights[a] = q->weights[b]; \
    q->weights[b] = temp; \
  } while (0)

// creating the values for the priority queue
typedef struct boxes {
    float value;
    int row;
    int col;
} boxes;

// creating my priority queue struct
typedef struct Priqu {
    size_t size;
    size_t capacity;
    boxes *weights;
} Priqu ;


//2D
typedef struct tuple_point {
    float x;
    float y;
    float* edges;
} tuple_point;

float euc_dist_2d (tuple_point a, tuple_point b) {
    return sqrt(pow((a.x - b.x), 2) + pow((a.y - b.y), 2));
}

tuple_point* case_2d_randgen (int seed, int v)
{
    // if (seed == 0)
    //     srand(time(NULL));
    // else
    //     srand(seed);

    tuple_point* array = malloc(v * sizeof(tuple_point));

    array[0].x = (float) rand() / (float) RAND_MAX;
    array[0].y = (float) rand() / (float) RAND_MAX;
    array[0].edges = NULL;

    for (int i = 1 ; i < v ; i++)
    {
        array[i].x = (float) rand() / (float) RAND_MAX;
        array[i].y = (float) rand() / (float) RAND_MAX;
        array[i].edges = malloc(i * sizeof(float));
        for (int j = 0 ; j < i ; j++)
            array[i].edges[j] = euc_dist_2d(array[i], array[j]);
    }

    return array;
}

typedef struct triple_point {
    float x;
    float y;
    float z;
    float* edges;
} triple_point;

float euc_dist_3d (triple_point a, triple_point b) {
    return sqrt(pow((a.x - b.x), 2) + pow((a.y - b.y), 2) + 
                pow((a.z - b.z), 2));
}

triple_point* case_3d_randgen (int seed, int v)
{
    // if (seed == 0)
    //     srand(time(NULL));
    // else
    //     srand(seed);

    triple_point* array = malloc(v * sizeof(triple_point));

    array[0].x = (float) rand() / (float) RAND_MAX;
    array[0].y = (float) rand() / (float) RAND_MAX;
    array[0].z = (float) rand() / (float) RAND_MAX;
    array[0].edges = NULL;

    for (int i = 1 ; i < v ; i++)
    {
        array[i].x = (float) rand() / (float) RAND_MAX;
        array[i].y = (float) rand() / (float) RAND_MAX;
        array[i].z = (float) rand() / (float) RAND_MAX;
        array[i].edges = malloc(i * sizeof(float));
        for (int j = 0 ; j < i ; j++)
            array[i].edges[j] = euc_dist_3d(array[i], array[j]);
    }

    return array;
}


//4D

typedef struct quad_point {
    float x;
    float y;
    float z;
    float w;
    float* edges;
} quad_point;

float euc_dist_4d (quad_point a, quad_point b) {
    return sqrt(pow((a.x - b.x), 2) + pow((a.y - b.y), 2) + 
                pow((a.z - b.z), 2) + pow((a.w - b.w), 2));
}

quad_point* case_4d_randgen (int seed, int v)
{
    // if (seed == 0)
    //     srand(time(NULL));
    // else
    //     srand(seed);

    quad_point* array = malloc(v * sizeof(quad_point));

    array[0].x = (float) rand() / (float) RAND_MAX;
    array[0].y = (float) rand() / (float) RAND_MAX;
    array[0].z = (float) rand() / (float) RAND_MAX;
    array[0].w = (float) rand() / (float) RAND_MAX;
    array[0].edges = NULL;

    for (int i = 1 ; i < v ; i++)
    {
        array[i].x = (float) rand() / (float) RAND_MAX;
        array[i].y = (float) rand() / (float) RAND_MAX;
        array[i].z = (float) rand() / (float) RAND_MAX;
        array[i].w = (float) rand() / (float) RAND_MAX;
        array[i].edges = malloc(i * sizeof(float));
        for (int j = 0 ; j < i ; j++)
            array[i].edges[j] = euc_dist_4d(array[i], array[j]);
    }

    return array;
}


size_t todo;

// to organize our heap
void min_heapify(Priqu *q, size_t index) {
    size_t left_index = LEFT(index);
    size_t right_index = RIGHT(index);
    size_t large = index;

    if (left_index <= todo && q->weights[left_index].value > q->weights[large].value)
    {
        large = left_index;
    }
    if (right_index <= todo && q->weights[right_index].value > q->weights[large].value)
    {
        large = right_index;
    }
    if (large != index) {
        SWITCH(q, index, large);
        min_heapify(q, large);
    }
};

void sort(Priqu *q)
{
    todo = q->size;

    for (size_t i = todo / 2; i >= 1; i--)
        min_heapify(q, i);

    for (size_t i = todo; i > 1; i--) {
        SWITCH(q, 1, i);
        todo--;
        min_heapify(q, 1);
    }
}

// adding elements to the queue, takes in the queue and the value
void insert(Priqu *q, float val, int ro, int co) {
    // need a variable of size_t and a pointer
    boxes temp;
    // don't operate if our queue is full
    if (q->size + 1 > q->capacity)
    {
        printf("The priority queue is full!\n");
        return;
    }
    // increment the size
    q->size++;
    // put the new value at the end of the queue
    q->weights[q->size].value = val;
    q->weights[q->size].row = ro;
    q->weights[q->size].col = co;
    

    sort(q);

    // move up the value while it's smaller than its parent
    // while(q->weights[i].value <= q->weights[PARENT(i)].value)
    // {
    //     temp = q->weights[i];
    //     q->weights[i] = q->weights[PARENT(i)];
    //     q->weights[PARENT(i)] = temp;
    //     i = PARENT(i);
    // }
};

// return a pointer to the edge
boxes deletemin(Priqu *q) {
    // this will be the return value
    boxes edge;
    // can't do anything if nothing is there
    if (q->size < 1)
    {
        printf("Nothing in the priority queue!\n");
        exit(0);
    }
    // selecting the edge at the beginning
    edge = q->weights[1];
    // moving the last edge to the beginning
    q->weights[1] = q->weights[q->size];
    // decrementing size
    q->size--;
    // now need to reheapify
    sort(q);
    return edge;
};

float** case_1_randgen (int seed, int v)
{
    // if (seed == 0)
    //     srand(time(NULL));
    // else
    //     srand(seed);

    float** array = malloc(v * sizeof(float*));

    for (int i = 1 ; i < v ; i++)
    {
        array[i] = malloc(i * sizeof(float));
        for (int j = 0 ; j < i ; j++)
        {
            array[i][j] = ((float) rand() / (float) RAND_MAX) ;
        }
    }

    return array;
}

// for actual prim's
int main(int argc, char *argv[]) {
    if (argc == 5)
    {
        // int num_trials = atoi(argv[3]);
        // float *trial_weight = malloc(num_trials * sizeof(float));

        if (atoi(argv[4]) == 0)
        {  
            // testing, testing
            int seed = atoi(argv[1]);
            if (seed == 0)
            srand(time(NULL));
            else
            srand(seed);


            int num_trials = atoi(argv[3]);
            float *trial_weight = malloc(num_trials * sizeof(float));

            for (int trials = 0 ; trials < num_trials ; trials++)
            {
                // need the for loop to start here
                boxes del;

                // int seed = atoi(argv[1]);

                int v = atoi(argv[2]);

                float *final = malloc(v * sizeof(float));
                int size = 0;

                // need to figure out how to randgen this better
                float** arr = malloc(sizeof(float*));
                arr = case_1_randgen(seed, v);
                for (int i = 1; i < v; i++)
                    for (int j = 0 ; j < i ; j++)
                        printf("%f\n", arr[i][j]);

                int** arrayvis = malloc(v * sizeof(int*));
                    for (int i = 1; i < v; i++)
                    {
                        arrayvis[i] = malloc(i * sizeof(int));
                        for (int j = 0 ; j < i ; j++)
                            arrayvis[i][j] = 1;
                    }

                Priqu *q = malloc(sizeof(Priqu));

                q->weights = malloc((v * v / 2) * sizeof(boxes));
                q->capacity = v * v;
                q->size = 0;
                // initial value isn't used, assign it -1 so no value is ever smaller
                q->weights[0].value = -1;

                int row = 0;
                int col = 0;

                for (int i = row + 1 ; i < v ; i++)
                    {
                        if ((arrayvis[i][row] == 1) 
                            && arr[i][row] < (20.0/(float) v)
                            )
                        {
                            insert(q, arr[i][row], i, row);
                            arrayvis[i][row] = 0;
                        }
                    }

                while (size < v - 1)
                {
                    del = deletemin(q);
                    final[size] = del.value;
                    size++;
                    row = del.row;
                    col = del.col;

                    for (int i = row + 1 ; i < v ; i++)
                    {
                        if (arrayvis[i][row] == 1
                            && arr[i][row] < (20.0/(float) v)
                            )
                        {
                            insert(q, arr[i][row], i, row);
                            arrayvis[i][row] = 0;
                        }
                    }

                    for (int j = col ; j < row ; j++)
                    {
                        if (arrayvis[row][j] == 1
                            && arr[row][j] < (20.0/(float) v)
                            )
                        {
                            insert(q, arr[row][j], row, j);
                            arrayvis[row][j] = 0;
                        }
                    }
                }


                float sum = 0;

                printf("our MST: ");
                for(int k = 0 ; k < v - 1 ; k ++)
                {
                    sum += final[k];
                    printf("%f | ", final[k]);
                }
                printf("\n");

                printf("our tree weight: %f\n", sum);

                trial_weight[trials] = sum;

                free(q->weights);
                free(q);

                // problems freeing
                for (int i = 1; i < v; i++)
                {
                    free(arrayvis[i]);
                }
                free(arrayvis);

                // problems freeing
                for (int i = 1; i < v; i++)
                {
                    free(arr[i]);
                }
                free(arr);
                free(final);

                // for loop should end here
            }
            
        
            float total_weight;

            for (int k = 0 ; k < num_trials ; k++)
            {
                total_weight += trial_weight[k];
            }

            float average_weight = (total_weight / (float) num_trials);

            printf("our average weight is: %f\n", average_weight);

            free(trial_weight);
        }

        if (atoi(argv[4]) == 2)
        {   
            // testing, testing
            int seed = atoi(argv[1]);
            if (seed == 0)
            srand(time(NULL));
            else
            srand(seed);

            int num_trials = atoi(argv[3]);
            float *trial_weight = malloc(num_trials * sizeof(float));

            for (int trials = 0 ; trials < num_trials ; trials++)
            {
                // int seed = atoi(argv[1]);

                int v = atoi(argv[2]);

                tuple_point* arr2 = malloc(sizeof(tuple_point*));
                arr2 = case_2d_randgen(seed, v);
                for (int i = 1; i < v; i++)
                    for (int j = 0 ; j < i ; j++)
                        printf("%f\n", arr2[i].edges[j]);

                boxes del;

                float *final = malloc(v * sizeof(float));
                int size = 0;

                int** arrayvis = malloc(v * sizeof(int*));
                    for (int i = 1; i < v; i++)
                    {
                        arrayvis[i] = malloc(i * sizeof(int));
                        for (int j = 0 ; j < i ; j++)
                            arrayvis[i][j] = 1;
                    }

                Priqu *q = malloc(sizeof(Priqu));

                q->weights = malloc((v * v / 2) * sizeof(boxes));
                q->capacity = v * v;
                q->size = 0;
                // initial value isn't used, assign it -1 so no value is ever smaller
                q->weights[0].value = -1;

                int row = 0;
                int col = 0;

                for (int i = row + 1 ; i < v ; i++)
                    {
                        if (arrayvis[i][row] == 1
                            && arr2[i].edges[row] < pow(2.178, (-0.02 * (float) v)) * 0.5 + 0.135)
                        {
                            insert(q, arr2[i].edges[row], i, row);
                            arrayvis[i][row] = 0;
                        }
                    }

                while (size < v - 1)
                {
                    del = deletemin(q);
                    final[size] = del.value;
                    size++;
                    row = del.row;
                    col = del.col;

                    for (int i = row + 1 ; i < v ; i++)
                    {
                        if (arrayvis[i][row] == 1
                            && arr2[i].edges[row] < pow(2.178, (-0.02 * (float) v)) * 0.5 + 0.135)
                        {
                            insert(q, arr2[i].edges[row], i, row);
                            arrayvis[i][row] = 0;
                        }
                    }

                    for (int j = col ; j < row ; j++)
                    {
                        if (arrayvis[row][j] == 1
                            && arr2[row].edges[j] < pow(2.178, (-0.02 * (float) v)) * 0.5 + 0.135)
                        {
                            insert(q, arr2[row].edges[j], row, j);
                            arrayvis[row][j] = 0;
                        }
                    }
                }

                // float sum = 0;

                // printf("our MST: ");
                // for(int k = 0 ; k < v - 1 ; k ++)
                // {
                //     sum += final[k];
                //     printf("%f | ", final[k]);
                // }
                // printf("\n");

                // printf("our tree weight: %f\n", sum);

                // free(q->weights);
                // free(q);
                // for (int i = 1; i < v; i++)
                // {
                //     free(arrayvis[i]);
                // }
                // free(arrayvis);
                // //figure out how to free this
                // for (int i = 1; i < v; i++)
                // {
                //     free(arr2[i].edges);
                // }
                // free(arr2);
                // free(final);

                float sum = 0;

                printf("our MST: ");
                for(int k = 0 ; k < v - 1 ; k ++)
                {
                    sum += final[k];
                    printf("%f | ", final[k]);
                }
                printf("\n");

                printf("our tree weight: %f\n", sum);

                trial_weight[trials] = sum;

                free(q->weights);
                free(q);

                // problems freeing
                for (int i = 1; i < v; i++)
                {
                    free(arrayvis[i]);
                }
                free(arrayvis);

                // problems freeing
                for (int i = 1; i < v; i++)
                {
                    free(arr2[i].edges);
                }
                free(arr2);
                free(final);
            }

            float total_weight;

            for (int k = 0 ; k < num_trials ; k++)
            {
                total_weight += trial_weight[k];
            }

            float average_weight = (total_weight / (float) num_trials);

            printf("our average weight is: %f\n", average_weight);

            free(trial_weight);
        }

        if (atoi(argv[4]) == 3)
        {
            // testing, testing
            int seed = atoi(argv[1]);
            if (seed == 0)
            srand(time(NULL));
            else
            srand(seed);

            int num_trials = atoi(argv[3]);
            float *trial_weight = malloc(num_trials * sizeof(float));


            for (int trials = 0 ; trials < num_trials ; trials++)
            {   
                // int seed = atoi(argv[1]);

                int v = atoi(argv[2]);

                triple_point* arr3 = malloc(sizeof(triple_point*));
                arr3 = case_3d_randgen(seed, v);
                for (int i = 1; i < v; i++)
                    for (int j = 0 ; j < i ; j++)
                        printf("%f\n", arr3[i].edges[j]);

                boxes del;

                float *final = malloc(v * sizeof(float));
                int size = 0;

                int** arrayvis = malloc(v * sizeof(int*));
                    for (int i = 1; i < v; i++)
                    {
                        arrayvis[i] = malloc(i * sizeof(int));
                        for (int j = 0 ; j < i ; j++)
                            arrayvis[i][j] = 1;
                    }

                Priqu *q = malloc(sizeof(Priqu));

                q->weights = malloc((v * v / 2) * sizeof(boxes));
                q->capacity = v * v;
                q->size = 0;
                // initial value isn't used, assign it -1 so no value is ever smaller
                q->weights[0].value = -1;

                int row = 0;
                int col = 0;

                for (int i = row + 1 ; i < v ; i++)
                    {
                        if (arrayvis[i][row] == 1)
                        {
                            insert(q, arr3[i].edges[row], i, row);
                            arrayvis[i][row] = 0;
                        }
                    }

                while (size < v - 1)
                {
                    del = deletemin(q);
                    final[size] = del.value;
                    size++;
                    row = del.row;
                    col = del.col;

                    for (int i = row + 1 ; i < v ; i++)
                    {
                        if (arrayvis[i][row] == 1)
                        {
                            insert(q, arr3[i].edges[row], i, row);
                            arrayvis[i][row] = 0;
                        }
                    }

                    for (int j = col ; j < row ; j++)
                    {
                        if (arrayvis[row][j] == 1)
                        {
                            insert(q, arr3[row].edges[j], row, j);
                            arrayvis[row][j] = 0;
                        }
                    }
                }

                // float sum = 0;

                // printf("our MST: ");
                // for(int k = 0 ; k < v - 1 ; k ++)
                // {
                //     sum += final[k];
                //     printf("%f | ", final[k]);
                // }
                // printf("\n");

                // printf("our tree weight: %f\n", sum);

                // free(q->weights);
                // free(q);
                // for (int i = 0; i < v; i++)
                // {
                //     free(arrayvis[i]);
                // }
                // free(arrayvis);

                // for (int i = 1; i < v; i++)
                // {
                //      free(arr3[i].edges);
                // }
                // free(arr3);
                // free(final);

                float sum = 0;

                printf("our MST: ");
                for(int k = 0 ; k < v - 1 ; k ++)
                {
                    sum += final[k];
                    printf("%f | ", final[k]);
                }
                printf("\n");

                printf("our tree weight: %f\n", sum);

                trial_weight[trials] = sum;

                free(q->weights);
                free(q);

                // problems freeing
                for (int i = 1; i < v; i++)
                {
                    free(arrayvis[i]);
                }
                free(arrayvis);

                // problems freeing
                for (int i = 1; i < v; i++)
                {
                    free(arr3[i].edges);
                }
                free(arr3);
                free(final);
            }

            float total_weight;

            for (int k = 0 ; k < num_trials ; k++)
            {
                total_weight += trial_weight[k];
            }

            float average_weight = (total_weight / (float) num_trials);

            printf("our average weight is: %f\n", average_weight);

            free(trial_weight);
        }

        if (atoi(argv[4]) == 4)
        {   
            // testing, testing
            int seed = atoi(argv[1]);
            if (seed == 0)
            srand(time(NULL));
            else
            srand(seed);

            int num_trials = atoi(argv[3]);
            float *trial_weight = malloc(num_trials * sizeof(float));

            for (int trials = 0 ; trials < num_trials ; trials++)
            {
                // int seed = atoi(argv[1]);

                int v = atoi(argv[2]);

                quad_point* arr4 = malloc(sizeof(quad_point*));
                arr4 = case_4d_randgen(seed, v);
                for (int i = 0; i < v; i++)
                    for (int j = 0 ; j < i ; j++)
                        printf("%f\n", arr4[i].edges[j]);

                boxes del;

                float *final = malloc(v * sizeof(float));
                int size = 0;

                int** arrayvis = malloc(v * sizeof(int*));
                    for (int i = 1; i < v; i++)
                    {
                        arrayvis[i] = malloc(i * sizeof(int));
                        for (int j = 0 ; j < i ; j++)
                            arrayvis[i][j] = 1;
                    }

                Priqu *q = malloc(sizeof(Priqu));

                q->weights = malloc((v * v / 2) * sizeof(boxes));
                q->capacity = v * v;
                q->size = 0;
                // initial value isn't used, assign it -1 so no value is ever smaller
                q->weights[0].value = -1;

                int row = 0;
                int col = 0;

                for (int i = row + 1 ; i < v ; i++)
                    {
                        if (arrayvis[i][row] == 1)
                        {
                            insert(q, arr4[i].edges[row], i, row);
                            arrayvis[i][row] = 0;
                        }
                    }

                while (size < v - 1)
                {
                    del = deletemin(q);
                    final[size] = del.value;
                    size++;
                    row = del.row;
                    col = del.col;

                    for (int i = row + 1 ; i < v ; i++)
                    {
                        if (arrayvis[i][row] == 1)
                        {
                            insert(q, arr4[i].edges[row], i, row);
                            arrayvis[i][row] = 0;
                        }
                    }

                    for (int j = col ; j < row ; j++)
                    {
                        if (arrayvis[row][j] == 1)
                        {
                            insert(q, arr4[row].edges[j], row, j);
                            arrayvis[row][j] = 0;
                        }
                    }
                }

                // float sum = 0;

                // printf("our MST: ");
                // for(int k = 0 ; k < v - 1 ; k ++)
                // {
                //     sum += final[k];
                //     printf("%f | ", final[k]);
                // }
                // printf("\n");

                // printf("our tree weight: %f\n", sum);

                // free(q->weights);
                // free(q);
                // for (int i = 0; i < v; i++)
                // {
                //     free(arrayvis[i]);
                // }
                // free(arrayvis);

                // for (int i = 1; i < v; i++)
                // {
                //     free(arr4[i].edges);
                // }
                // free(arr4);
                // free(final);

                float sum = 0;

                printf("our MST: ");
                for(int k = 0 ; k < v - 1 ; k ++)
                {
                    sum += final[k];
                    printf("%f | ", final[k]);
                }
                printf("\n");

                printf("our tree weight: %f\n", sum);

                trial_weight[trials] = sum;

                free(q->weights);
                free(q);

                // problems freeing
                for (int i = 1; i < v; i++)
                {
                    free(arrayvis[i]);
                }
                free(arrayvis);

                // problems freeing
                for (int i = 1; i < v; i++)
                {
                    free(arr4[i].edges);
                }
                free(arr4);
                free(final);
            }

            float total_weight;

            for (int k = 0 ; k < num_trials ; k++)
            {
                total_weight += trial_weight[k];
            }

            float average_weight = (total_weight / (float) num_trials);

            printf("our average weight is: %f\n", average_weight);

            free(trial_weight);
        }
    }
    else
        printf("Yo! You suck!\n");
}