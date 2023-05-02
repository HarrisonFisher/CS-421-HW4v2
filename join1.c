#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define NTHREADS 10
#define LIST_MAX_SIZE 50

// Struct for array-based list.
typedef struct list_t {
    int size;
    int data[LIST_MAX_SIZE];
} list_t;
list_t shared_list = { 0, { 0 } };

void *work_on_list(void *);    
void add_to_list(int value);
void print_list();

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
int  counter = 0;


main() {
    
    // Seed the random number generator with the current time
    srand(time(NULL)); 

    pthread_t threads[NTHREADS];
    int num_ops;

    // Prompt for the number of operations to do.
    printf("How many operations do you want each thread to do on the list? ");
    scanf("%d", &num_ops);


    // Create the threads.
    pthread_mutex_lock(&mutex1); 
    for (int i = 0; i < NTHREADS; i++) {
        pthread_create(&threads[i], NULL, work_on_list, &num_ops);
    }
    pthread_mutex_unlock(&mutex1);


    // Wait for the threads to finish.
    for (int i = 0; i < NTHREADS; i++) {
        pthread_join(threads[i], NULL);
    }
    printf("The end\n");
    return 0;
}

// Perform a number of random operations on the shared list.
void *work_on_list(void *dummyPtr) {
    int num_ops = *(int *)dummyPtr;
    for (int i = 0; i < num_ops; i++) {
        // Randomly choose to add a value between 0-99 or print the list.
        if (rand() % 3 == 0) {
            int value = rand() % 100;
             add_to_list(value);
        } else {
            print_list();
        }
    }
}


// Will add a value to the end of the array if it fits.
void add_to_list(int value) {
    if (shared_list.size >= LIST_MAX_SIZE) {
        printf("Thread number %ld: ", pthread_self());
        printf("List is full\n");
        return;
    }
    shared_list.data[shared_list.size] = value;
    shared_list.size++;
    printf("Thread number %ld: ", pthread_self());
    printf("Adding %d\n", value);
}


// Will display the values separated by spaces on a line
void print_list() {
    // printf("List contents: ");
    printf("Thread number %ld: ", pthread_self());
    for (int i = 0; i < shared_list.size; i++) {
        printf("%d ", shared_list.data[i]);
    }
    printf("\n");
}

