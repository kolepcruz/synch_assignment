
#ifndef __UPDATER_HPP__
#define __UPDATER_HPP__

#include <pthread.h>

#include <chrono>
#include <iostream>
#include <thread>
#include <vector>

#include "Arena.hpp"
#include "Pit.hpp"
#include "Saiyan.hpp"
#include "stdio.h"
class Updater {
   private:
    Arena* m_p_arena;
    std::vector<Saiyan*> m_saiyans;
    std::thread m_thread;
    pthread_t m_pthread;
    int m_stop = 0;

   
   public:
    static void* pthread_printer(void* me__) {
        using std::cerr;
        using std::cout;
        using std::endl;
        Updater* me = (Updater*)me__;
        while (!me->m_stop) {
            std::cout << "-------frame-------" << '\n';
            char buf[256];
            char pattern[] = "%2d %3d /%4d %3d  %2d";
            std::cout << "Lutadores:" << '\n';
            std::cout << "id  hp / t_hp atck c_pit" << '\n';
            for (Saiyan* s : me->m_saiyans) {
                sprintf(buf, pattern, s->get_id(), s->get_current_hp(),
                        s->get_total_hp(), s->get_attack_pwr(),s->current_pit);
                std::cout << buf << '\n';
            }

            char pattern_arena[] = "%2d %3d %3d    %1d       %d";
            std::cout << "Arena" << '\n';
            std::cout << "id0 id1 id2 pit_state sem_val" << '\n';
            for (Pit p : me->m_p_arena->get_pits()) {
                int id1;
                int id2;
                if (p.lutador1 == nullptr) {
                    id1 = -1;
                } else {
                    id1 = p.lutador1->get_id();
                }
                if (p.lutador2 == nullptr) {
                    id2 = -1;
                } else {
                    id2 = p.lutador2->get_id();
                }
                int aux;
                sem_getvalue(p.get_act_sem(),&aux);
                sprintf(buf, pattern_arena, p.get_id(), id1, id2, p.ready_to_fight,aux);
                std::cout << buf << '\n';
            }

            std::cout << "-------------------" << '\n';
            std::cout.flush();
            std::this_thread::sleep_for(std::chrono::milliseconds(500 / 2));
        }
        return NULL;
    }

    Updater(Arena* p_arena, std::vector<Saiyan*> saiyans)
        : m_p_arena{p_arena}, m_saiyans{saiyans} {}
    ~Updater() {
        m_stop = 1;
    }
};

#endif  //__UPDATER_HPP__
