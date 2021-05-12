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
#include "backend/Infirmary.hpp"

#define NUM_THREADS 5
#define SAIYAN_AMMOUNT 2

using namespace ::std;
typedef void * (*THREADFUNCPTR)(void *);

void run_backend(){
    Infirmary* inf = new Infirmary(2);
    Arena* arena = new Arena(5);
    std::vector<Saiyan*> saiyans;
    int n_saiyans = SAIYAN_AMMOUNT;
    pthread_t threads[n_saiyans];
    for (int i = 0; i < n_saiyans; ++i) {
        saiyans.push_back(new Saiyan(100, 10, i, arena));
    }
    for(int i = 0; i < n_saiyans;++i){
        Saiyan* saiyan = saiyans[i];
        std::cout<<saiyans[i]->get_id()<<std::endl;
        // std::cout<<saiyans[i]->get_arena()<<std::endl;

        if(pthread_create(&threads[i], NULL,(THREADFUNCPTR) &behavior, (void *) saiyans[i]) != 0) {
            perror("unable to create thread");
            exit(1);
        }

    }
    for(int i = 0; i < n_saiyans;++i){
        pthread_join(threads[i],NULL);
    }

    // Updater* updater = new Updater(arena, saiyans);
    // pthread_t thread_updater;
    // if (pthread_create(&thread_updater, NULL, Updater::pthread_printer, updater)) {
    //     exit(1);
    // }
    // usleep(4000000);
    // // while (1) {
        
    // // }
    // delete updater;
    return;
}


int main() {
    run_backend();
    return 0;
}