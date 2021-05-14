#ifndef __INFIRMARY_HPP__
#define __INFIRMARY_HPP__

#include <semaphore.h>

#include <vector>
#include <iostream>
#include "Saiyan.hpp"

class Infirmary {
   private:
    unsigned int total_beds;
    // std::vector<Saiyan> patients;
    sem_t m_sem;

   public:
    Infirmary(unsigned int n_beds);
    unsigned int get_total_beds() { return this->total_beds; }
    sem_t* get_semaphore() { return &this->m_sem; }
    // std::vector<Saiyan> get_patients
    void print_meme();
};

#endif  //__INFIRMARY_HPP__