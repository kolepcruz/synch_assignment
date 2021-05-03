#include "Pit.hpp"
Pit::Pit() {
    lutador1 = nullptr;
    lutador2 = nullptr;
    sem_init(&m_sem, SHARED_BETWEEN_THREADS, 2);
}