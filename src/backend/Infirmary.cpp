#include "Infirmary.hpp"

Infirmary::Infirmary(unsigned int total_beds){
    this->total_beds = total_beds;
    sem_init(&m_sem,1,total_beds);
    // std::cout<<test<<std::endl;
}

void Infirmary::print_meme(){
    std::cout<<"Bruh come get nursed iq >>>> 8000"<<std::endl;
}