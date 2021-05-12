#include "Saiyan.hpp"

std::string arr[] = {"WAITING", "HEALING", "FIGHTING"};


//esta funcion deberia receber un struct de argumentos que seria el contexto, recibiendo la thread y los punteros para la enfermaria, etc
void behavior(void* ptr) {
    Saiyan* myself = static_cast<Saiyan*>(ptr);
    //poner un loop que rueda hasta que un saiyan le pase a determinado parametro
    while (myself->try_enter_pit() != 0);
    std::cout<< "Saiyan #"<<myself->get_id()<<std::endl;
    myself->set_current_state(FIGHTING);
    std::cout<<myself->get_current_state()<<std::endl;
    if(myself->get_arena()->get_pits()[myself->current_pit].lutador1 != nullptr && myself->get_arena()->get_pits()[myself->current_pit].lutador2 != nullptr)
        std::cout<<"Acho que deu certo"<<std::endl;
    //ate aqui tenho que confirmar que os dois lutadores estão na parada

    //aqui pode começar a luta, olhar semaforo da enfermaria se esta com disponibilidade
    while(1);
}

Saiyan::Saiyan(unsigned int total_hp, unsigned int attack_pwr, unsigned int id,
               Arena* arena) {
    this->total_hp = total_hp;
    this->current_hp = total_hp;
    this->attack_pwr = attack_pwr;
    this->id = id;
    this->m_arena = arena;
    this->current_state = WAITING;
}

void Saiyan::receive_attack(Saiyan enemy) {
    if (this->current_hp <= 0) {
        return;
    }
    this->current_hp -= enemy.get_attack_pwr();
}
int Saiyan::try_enter_pit() {
    // sleep(this->get_id());
    for (Pit &pit : m_arena->get_pits()) {
        int test;
        // std::cout << "Saiyan " << this->get_id() << " trying to enter pit "
        //           << pit.get_id() << std::endl;

        sem_getvalue(pit.get_sem(), &test);
        if (test == 0) continue;

        if (pit.lutador1 == nullptr && pit.lutador2 == nullptr)
            // std::cout << "Empty pit" << std::endl;
        sem_wait(pit.get_sem());
        sem_getvalue(pit.get_sem(), &test);
        std::cout << "Current value of sem for pit " << pit.get_id() << " is "
                  << test << std::endl;
        if(pit.lutador1 == nullptr)
            pit.lutador1 = this;
        else if (pit.lutador2 == nullptr)
            pit.lutador2 = this;
        else 
            continue;
        // pit.lutador1 = this;
        // std::cout << "Pit has a fighter " << pit.lutador1->get_id()
        //           << std::endl;
        // std::cout << "Pit has a fighter " << pit.lutador2->get_id()
        //           << std::endl;
        this->current_pit = pit.get_id();
        // sleep(this->get_id());
        // std::cout<<"Leaving function"<<std::endl;
        return 0;
    }

    return 1;
}
