#include <pthread.h>
#include <stdlib.h>

#include <iostream>

#include "frontend/ss_view.h"

#define NUM_THREADS 5

using namespace ::std;

static pthread_mutex_t func_mutex = PTHREAD_MUTEX_INITIALIZER;

int values[] = {0, 0, 0, 0, 0};

void func() {
    pthread_mutex_lock(&func_mutex);

    pthread_mutex_unlock(&func_mutex);
}

void* worker(void* arg) {
    int value = *((int*)arg);
    cout << value << endl;
    cout << value * 10 << endl;
    return 0;
}

int main() {
    pthread_t threads[NUM_THREADS];
    int result;
    int args[] = {1, 2, 3, 4, 5};
    for (int i = 0; i < NUM_THREADS; ++i) {
        result = pthread_create(&threads[i], NULL, worker, (void*)&args[i]);
    }

    for (int i = 0; i < NUM_THREADS; ++i) {
        result = pthread_join(threads[i], NULL);
    }

    return 0;
}