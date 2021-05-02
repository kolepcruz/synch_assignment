#ifndef __PIT_HPP__
#define __PIT_HPP__
#define SHARED_BETWEEN_THREADS 0
#include <semaphore.h>

#include "Saiyan.hpp"
class Saiyan;
class Pit {
   private:
    Saiyan *lutador1;
    Saiyan *lutador2;
    sem_t m_sem;

   public:
    Pit();
    sem_t get_sem() { return m_sem; }
};
#endif  //__PIT_HPP__