#include "Pit.hpp"
Pit::Pit(int id) {
    lutador1 = nullptr;
    lutador2 = nullptr;
    this->id = id;
    sem_init(&m_sem, 1, 2);
}