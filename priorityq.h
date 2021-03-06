#include <stdlib.h>
#include <stdio.h>

// for accessing specific elements in our tree
#define LEFT(x) (2 * x)
#define RIGHT(x) (2 * (x) + 1)
#define PARENT(x) (2 / (x))

// creating my priority queue struct
typedef struct Priqu {
    size_t size;
    size_t capacity;
    float *weights;
} Priqu ;

// to create the initial, empty priority queue
Priqu *initialize(size_t capacity) {
    // malloc for the pointer
    Priqu *queue = malloc(sizeof(Priqu));
    // maximum size of edge weights
    queue->weights = malloc(capacity * sizeof(float));
    queue->capacity = capacity;
    queue->size = 0;
    // initial value isn't used, assign it -1 so no value is ever smaller
    queue->weights[0] = -1;
    return (queue);
};

// to organize our heap
void min_heapify(Priqu *q, size_t index) {
    float temp;
    size_t left_index = LEFT(index);
    size_t right_index = RIGHT(index);
    size_t large;
    
    if(left_index <= q->size && q->weights[left_index] > q->weights[index])
    {
        large = left_index;
    }
    else
    {
        large = index;
    }

    if (right_index <= q->size && q->weights[right_index] > q->weights[large])
    {
        large = right_index;
    }

    if (large != index)
    {
        temp = q->weights[large];
        q->weights[large] = q->weights[index];
        q->weights[index] = temp;
        min_heapify(q, large);
    }
};

// adding elements to the queue, takes in the queue and the value
void insert(Priqu *q, float val) {
    // need a variable of size_t and a pointer
    size_t i;
    float temp;
    // don't operate if our queue is full
    if (q->size + 1 >= q-> capacity)
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
    min_heapify(q, 1);
    return edge;
};
