
#ifndef __UPDATER_HPP__
#define __UPDATER_HPP__

#include <chrono>
#include <iostream>
#include <thread>
#include <vector>

#include "Arena.hpp"
#include "Pit.hpp"
#include "Saiyan.hpp"
class Updater {
   private:
    Arena* m_p_arena;
    std::vector<Saiyan*> m_saiyans;
    std::thread m_thread;
    int m_stop = 0;

    void printer() {
        using std::cout;
        using std::endl;
        // cout << (*m_p_arena).get_pits << endl;
        // for (Saiyan* s : m_saiyans) {
        //     cout << "id: " << (*s).get_id() << endl;
        //     cout << "t_hp: " << (*s).get_total_hp() << endl;
        // }

        while (!m_stop) {
            cout << "teste" << endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(1000 / 30));
        }
    }

   public:
    Updater(Arena* p_arena, std::vector<Saiyan*> saiyans)
        : m_p_arena{p_arena},
          m_saiyans{saiyans},
          m_thread(&Updater::printer, this) {}
    ~Updater() {
        m_stop = 1;
        m_thread.join();
    }
};

#endif  //__UPDATER_HPP__
