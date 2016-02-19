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
    size_t i;
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
    i = q->size;
    // move up the value while it's smaller than its parent
    // while(q->weights[i].value <= q->weights[PARENT(i)].value)
    // {
    //     temp = q->weights[i];
    //     q->weights[i] = q->weights[PARENT(i)];
    //     q->weights[PARENT(i)] = temp;
    //     i = PARENT(i);
    // }

    sort(q);

    // for(i = 1 ; i < q->size + 1 ; i ++)
    // {
    //     printf("pq nums: %f", q->weights[i].value);
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
    if (seed == 0)
        srand(time(NULL));
    else
        srand(seed);

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

    // Priqu *queue = malloc(sizeof(Priqu));
    // // maximum size of edge weights
    // queue->weights = malloc(v * v * sizeof(boxes));
    // queue->capacity = v * v;
    // queue->size = 0;
    // // initial value isn't used, assign it -1 so no value is ever smaller
    // queue->weights[0].value = -1;

    // for (int i = 0 ; i < v*v ; i++)
    // {
    //     insert(queue, ((float) rand() / (float) RAND_MAX));
    // }

    // return (queue);

}

// int main(int argc, char *argv[]) {
//     if (argc == 3)
//     {
//         float del;
//         int seed = atoi(argv[1]);
//         int v = atoi(argv[2]);
//         // will need to adjust this when prim's is really working
//         float *final = malloc(v * v * sizeof(float));
//         int size = 0;
//         Priqu *q = malloc(sizeof(Priqu));
//         q = case_1_randgen(seed, v);
//         for (int i = 0; i < v*v; i++)
//         {
//             del = deletemin(q);
//             printf("%f\n", del);
//             final[size] = del;
//             size++;
//         }
//     }
//     else
//         printf("Yo! You suck!\n");
// }

// for actual prim's
int main(int argc, char *argv[]) {
    if (argc == 3)
    {
        boxes del;
        int seed = atoi(argv[1]);

        int v = atoi(argv[2]);
        // will need to adjust this when prim's is really working
        float *final = malloc(v * sizeof(float));
        int size = 0;

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

        q->weights = malloc(v * v * sizeof(boxes));
        q->capacity = v * v;
        q->size = 0;
        // initial value isn't used, assign it -1 so no value is ever smaller
        q->weights[0].value = -1;

        int row = 0;
        int col = 0;

        // printf("made it here\n");

        for (int i = row + 1 ; i < v ; i++)
            {
                if (arrayvis[i][row] == 1)
                {
                    // printf("initial for loop\n");
                    insert(q, arr[i][row], i, row);
                    arrayvis[i][row] = 0;
                    // printf("inserting %f\n", arr[i][row]);
                }
            }

        while (size < v - 1)
        {
            del = deletemin(q);
            final[size] = del.value;
            // printf("one number is %f\n", final[size]);
            size++;
            row = del.row;
            // printf("row at next insert is %i\n", row);
            col = del.col;
            // printf("col at next insert is %i\n", col);

            for (int i = row + 1 ; i < v ; i++)
            {
                if (arrayvis[i][row] == 1)
                {
                    // printf("starting first for loop\n");
                    insert(q, arr[i][row], i, row);
                    arrayvis[i][row] = 0;
                    // printf("inserting %f\n", arr[i][row]);
                }
            }

            // printf("between inserts\n");
            // printf("row is %i\n", row);


            for (int j = col ; j < row ; j++)
            {
                if (arrayvis[row][j] == 1)
                {
                    // printf("staring second for loop\n");
                    insert(q, arr[row][j], row, j);
                    arrayvis[row][j] = 0;
                    // printf("insert %f\n",arr[row][j]);
                }
            }
        }

        for(int k = 0 ; k < v - 1 ; k ++)
        {
            printf("%f | ", final[k]);
        }
    }
    else
        printf("Yo! You suck!\n");
}

