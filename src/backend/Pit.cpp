#include "Pit.hpp"
Pit::Pit(int id) {
    lutador1 = nullptr;
    lutador2 = nullptr;
    this->id = id;
    sem_init(&m_sem, SHARED_BETWEEN_THREADS, 2);
}