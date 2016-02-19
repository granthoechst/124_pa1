#include <stdlib.h>
#include <stdio.h>
#include <time.h>

// for accessing specific elements in our tree
#define LEFT(x) (2 * x)
#define RIGHT(x) (2 * (x) + 1)
#define PARENT(x) (2 / (x))

#define SWITCH(q, a, b) \
  do { \
    float temp = q->weights[a]; \
    q->weights[a] = q->weights[b]; \
    q->weights[b] = temp; \
  } while (0)

// creating my priority queue struct
typedef struct Priqu {
    size_t size;
    size_t capacity;
    float *weights;
} Priqu ;

size_t todo;

// to organize our heap
void min_heapify(Priqu *q, size_t index) {
    size_t left_index = LEFT(index);
    size_t right_index = RIGHT(index);
    size_t large = index;

    if (left_index <= todo && q->weights[left_index] > q->weights[large])
    {
        large = left_index;
    }
    if (right_index <= todo && q->weights[right_index] > q->weights[large])
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
void insert(Priqu *q, float val) {
    // need a variable of size_t and a pointer
    size_t i;
    float temp;
    // don't operate if our queue is full
    if (q->size + 1 > q->capacity)
    {
        printf("The priority queue is full!\n");
        return;
    }
    // increment the size
    q->size++;
    // put the new value at the end of the queue
    q->weights[q->size] = val;
    i = q->size;
    // move up the value while it's smaller than its parent
    while(q->weights[i] <= q->weights[PARENT(i)])
    {
        temp = q->weights[i];
        q->weights[i] = q->weights[PARENT(i)];
        q->weights[PARENT(i)] = temp;
        i = PARENT(i);
    }
};

// return a pointer to the edge
float deletemin(Priqu *q) {
    // this will be the return value
    float edge;
    // can't do anything if nothing is there
    if (q->size < 1)
    {
        printf("Nothing in the priority queue!\n");
        return 0;
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

Priqu* case_1_randgen (int seed, int v)
{
    if (seed == 0)
        srand(time(NULL));
    else
        srand(seed);

    // float** array = malloc(v * sizeof(float*));

    // for (int i = 1 ; i < v ; i++)
    // {
    //     array[i] = malloc(i * sizeof(float));
    //     for (int j = 0 ; j < i ; j++)
    //         array[i][j] = ((float) rand() / (float) RAND_MAX) ;
    // }

    // return array;

    Priqu *queue = malloc(sizeof(Priqu));
    // maximum size of edge weights
    queue->weights = malloc(v * v * sizeof(float));
    queue->capacity = v * v;
    queue->size = 0;
    // initial value isn't used, assign it -1 so no value is ever smaller
    queue->weights[0] = -1;

    for (int i = 0 ; i < v*v ; i++)
    {
        insert(queue, ((float) rand() / (float) RAND_MAX));
    }

    return (queue);

}

int main(int argc, char *argv[]) {
    if (argc == 3)
    {
        float del;
        int seed = atoi(argv[1]);
        int v = atoi(argv[2]);
        Priqu *q = malloc(sizeof(Priqu));
        q = case_1_randgen(seed, v);
        for (int i = 0; i < v*v; i++)
        {
            del = deletemin(q);
            printf("%f\n", del);
        }
    }
    else
        printf("Yo! You suck!\n");
}

