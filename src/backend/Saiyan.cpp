#include "Saiyan.hpp"

#include "Context.hpp"
// este es el codigo con mas memory leak que ya hice
// esta funcion deberia receber un struct de argumentos que seria el contexto,
// recibiendo la thread y los punteros para la enfermaria, etc 
// para mi en este proyecto saiyan == thread 
void behavior(void* ptr) {
    Context* context = (Context*)(ptr);
    Saiyan* myself = static_cast<Saiyan*>(context->self); 
    Infirmary inf = static_cast<Infirmary>(context->inf);
    bool first = false;
    // poner un loop que rueda hasta que un saiyan le pase a determinado
    // parametro
    while (myself->get_total_hp() < LIFE_THRESHOLD) {
        while (myself->try_enter_pit() != 0);
        // std::cout << "Saiyan #" << myself->get_id() << std::endl;
        // std::cout << myself->get_current_state() << std::endl;

        Pit* current_pit = &myself->get_arena()->get_pits()[myself->current_pit];
        while (!current_pit->ready_to_fight) {
            if (current_pit->lutador1 != nullptr &&
                current_pit->lutador2 != nullptr)
                current_pit->ready_to_fight = true;
        }
        myself->set_current_state(FIGHTING);
        first = (current_pit->lutador1 == myself);
        // ate aqui tenho que confirmar que os dois lutadores estão na parada

        // aqui pode começar a luta, olhar semaforo da enfermaria se esta com
        // disponibilidade
        sem_wait(inf.get_semaphore());
        while (myself->get_current_hp() > 0) {
            // FIXME está como busy waiting
            sem_wait(current_pit->get_act_sem());  //semaforo de distribuição de porrada
            if (current_pit->ready_to_fight) {
                if (first) {
                    myself->receive_attack(*current_pit->lutador2);
                    
                } else {
                    myself->receive_attack(*current_pit->lutador1);
                }
                usleep(200); //adiciona tempo de distribuição de porrada
            }
            sem_post(current_pit->get_act_sem());
            //queria que fosse mutex
        }
        //sai do pit
        current_pit->ready_to_fight = false;
        myself->set_current_state(HEALING);
        if (first) {
            current_pit->lutador1 = nullptr;
        } else {
            current_pit->lutador2 = nullptr;
        }
        sem_post(current_pit->get_sem());
        myself->heal();
        sem_post(inf.get_semaphore());
    }
    // rotina para matar o resto das threads
}

Saiyan::Saiyan(unsigned int total_hp, unsigned int attack_pwr, unsigned int id, Arena* arena) {
    this->total_hp = total_hp;
    this->current_hp = total_hp;
    this->attack_pwr = attack_pwr;
    this->id = id;
    this->m_arena = arena;
    this->current_state = WAITING;
}

void Saiyan::heal() {
    this->total_hp += 20;
    while (this->get_current_hp() < this->get_total_hp()) {
        this->current_hp++;
        usleep(200);
        // std::cout << this->id << "# Saiyan is healing by " << this->get_current_hp() <<" of "<<  this->get_total_hp() << std::endl;
    }
}

void Saiyan::receive_attack(Saiyan enemy) {
    if (this->current_hp <= 0) {
        return;
    }
    this->current_hp -= enemy.get_attack_pwr();
}

int Saiyan::try_enter_pit() {
    for (Pit& pit : m_arena->get_pits()) {
        if (sem_trywait(pit.get_sem()) == 0) {
            if (pit.lutador1 == nullptr)
                pit.lutador1 = this;
            else if (pit.lutador2 == nullptr)
                pit.lutador2 = this;
            else {
                exit(1);  // Isso não deveria acontecer
            }
            this->current_pit = pit.get_id();
            return 0;
        }
    }
    return 1;
}
