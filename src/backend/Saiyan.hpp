#ifndef __SAIYAN_H__
#define __SAIYAN_H__

#include "Arena.hpp"
class Arena;

class Saiyan {
    typedef enum {
        FIGHTING,
        HEALING,
        WAITING,
    } State;

   private:
    unsigned int id;
    unsigned int total_hp;
    unsigned int current_hp;
    unsigned int attack_pwr;
    State current_state;
     Arena *m_arena;
    int try_enter_pit();

   public:
    Saiyan(unsigned int total_hp, unsigned int attack_pwr, unsigned int id,
            Arena *arena);
    void receive_attack(Saiyan enemy);
    void log_saiyan();
    void behavior();

    // IGetters and setters
    State get_current_state() { return this->current_state; }
    unsigned int get_id() { return this->id; }
    unsigned int get_total_hp() { return this->total_hp; }
    unsigned int get_current_hp() { return this->current_hp; }
    unsigned int get_attack_pwr() { return this->attack_pwr; }
    //
    void set_current_state(State state) { this->current_state = state; }
    void set_id(unsigned int id) { this->id = id; }
    void set_total_hp(unsigned int total_hp) { this->total_hp = total_hp; }
    void set_current_hp(unsigned int current_hp) {
        this->current_hp = current_hp;
    }
    void set_attack_pwr(unsigned int attack_pwr) {
        this->attack_pwr = attack_pwr;
    }
};

#endif  //__SAIYAN_H__