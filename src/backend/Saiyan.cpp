#include "Saiyan.hpp"

Saiyan::Saiyan(unsigned int total_hp, unsigned int attack_pwr, unsigned int id,
               Arena *arena) {
    this->total_hp = total_hp;
    this->current_hp = total_hp;
    this->attack_pwr = attack_pwr;
    this->id = id;
    this->m_arena = arena;
}

void Saiyan::receive_attack(Saiyan enemy) {
    if (this->current_hp <= 0) {
        return;
    }
    this->current_hp -= enemy.get_attack_pwr();
}
int Saiyan::try_enter_pit() {
    for (Pit pit : m_arena->get_pits()) {
        if (sem_trywait(pit.get_sem()) == 0) {
            return 0;
        }
    }
    return 1;
}

void Saiyan::behavior() {
    while (try_enter_pit() != 0)
        ;
}
