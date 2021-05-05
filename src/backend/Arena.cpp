#include "Arena.hpp"


Arena::Arena(int n_pits) {
    for (int i = 0; i < n_pits; i++) {
        m_pits.push_back(Pit(i));
    }
    // TODO Verifcar erro
    sem_init(&m_sem, SHARED_BETWEEN_THREADS, n_pits);
}