#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#include <chrono>
#include <iostream>
#include <vector>

#include "backend/Arena.hpp"
#include "backend/Saiyan.hpp"
#include "backend/Updater.cpp"
#include "frontend/ss_view.hpp"

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
    Arena* arena = new Arena(5);
    std::vector<Saiyan*> saiyans;
    int n_saiyans = 5;
    for (int i = 0; i < n_saiyans; ++i) {
        saiyans.push_back(new Saiyan(100, 10, i, arena));
    }
    Updater* updater = new Updater(arena, saiyans);
    usleep(4000000);
    // while (1) {
    // }
    delete updater;
    return 0;
}