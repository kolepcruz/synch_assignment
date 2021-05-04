#ifndef __ARENA_HPP__
#define __ARENA_HPP__
#define SHARED_BETWEEN_THREADS 0
#include <semaphore.h>

#include <vector>

#include "Pit.hpp"
class Pit;
class Arena {
    // É uma classe de dados? SIM/NAO
   private:
    std::vector<Pit> m_pits;
    sem_t m_sem;

   public:
    Arena(int n_pits);
    std::vector<Pit>& get_pits() { return m_pits; }
};
#endif  //__ARENA_HPP__