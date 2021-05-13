#ifndef __PIT_HPP__
#define __PIT_HPP__
#define SHARED_BETWEEN_THREADS 0
#include <semaphore.h>

#include "Saiyan.hpp"
class Saiyan;
class Pit {
   private:
    int id;
    sem_t m_sem;
    sem_t m_act;

   public:
    Saiyan *lutador1;
    Saiyan *lutador2;
    Pit(int id);
    bool ready_to_fight;
    bool is_empty();
    sem_t *get_sem() { return &m_sem; }
    sem_t *get_act_sem() { return &m_act; }
    int get_id() { return id; }
};
#endif  //__PIT_HPP__