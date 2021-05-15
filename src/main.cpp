#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#include <chrono>
#include <iostream>
#include <vector>

#include "backend/Arena.hpp"
#include "backend/Context.hpp"
#include "backend/Infirmary.hpp"
#include "backend/Saiyan.hpp"
#include "backend/Updater.cpp"
#include "frontend/ss_view.hpp"

#define SAIYAN_AMMOUNT 4

using namespace ::std;
typedef void* (*THREADFUNCPTR)(void*);

//TODO implement semaphore for main, read semaphore value 
void run_backend() {
    sem_t backend_sema;
    // sem_init(&backend_sema,1,SAIYAN_AMMOUNT-1); //n - 1 saiyan ira virar super saiyan, talvez nao precisa desse semaforo
    sem_t *p_backend_sema = &backend_sema;
    int* result;
    Infirmary* inf = new Infirmary(4);
    Arena* arena = new Arena(2);
    std::vector<Saiyan*> saiyans;
    int n_saiyans = SAIYAN_AMMOUNT;
    pthread_t threads[n_saiyans];
    for (int i = 0; i < n_saiyans; ++i) {
        saiyans.push_back(new Saiyan(100, 10, i, arena));
    }
    for (int i = 0; i < n_saiyans; ++i) {
        Context* p_context = new Context{saiyans[i], *inf, *p_backend_sema};
        if (pthread_create(&threads[i], NULL, (THREADFUNCPTR)behavior,
                           (void*)p_context) != 0) {
            perror("unable to create thread");
            exit(1);
        }
    }

    Updater* updater = new Updater(arena, saiyans);
    pthread_t thread_updater;
    if (pthread_create(&thread_updater, NULL, Updater::pthread_printer,
    updater)) {
        exit(1);
    }

    
    usleep(4000000);
    for (int i = 0; i < n_saiyans; ++i) {
        pthread_join(threads[i],NULL);
        
    }
    delete updater;
    return;
}

int main() {
    run_backend();
    return 0;
}