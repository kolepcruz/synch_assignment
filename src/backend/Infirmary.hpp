#ifndef __INFIRMARY_HPP__
#define __INFIRMARY_HPP__

#include <semaphore.h>

#include <vector>
#include <iostream>
#include "Saiyan.hpp"

class Infirmary {
   private:
    const unsigned int total_beds;
    // std::vector<Saiyan> patients;
    sem_t sem;

   public:
    Infirmary();
    unsigned int get_total_beds() { return this->total_beds; }
    sem_t get_semaphore() { return this->sem; }
    // std::vector<Saiyan> get_patients
    void print_meme();
};

#endif  //__INFIRMARY_HPP__