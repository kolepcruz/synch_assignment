#ifndef __FRONT__
#define __FRONT__
#include<bits/stdc++.h>
#include <ncurses.h>
#include <ctype.h>
#include <string>
#include <sys/ioctl.h> // biblioteca útil para mensurar tamanhos do terminal.
#include "../backend/Infirmary.hpp"
#include "../backend/Arena.hpp"
#include "../backend/Pit.hpp"
#include "../backend/Context.hpp"
#include "../backend/Saiyan.hpp"

#ifdef _WIN32
    #define _WIN32
    #include <Windows.h>
#else
    #include <unistd.h>
#endif

typedef unsigned int ui;
using namespace std;

#define T_CHARGE 300000
#define T_POWER   80000
#define T_BLOD   300000  

void time (WINDOW* win, int udelay);
void printChar(WINDOW* win, int y, int x, int color, int val);
void printChar(WINDOW* win, int y, int x, int color, const char* c);

void drawInfirmary (vector<int> pacientes, int n_leitos);

void print_in_arena(WINDOW* win, vector<vector<int> > &luts, vector<int> & y_id, 
                  vector<vector<int> > & x_id, 
                  bool pos, int color, unsigned utime);
void syncPowers(vector<vector<int> > &luts, vector<vector<int> > &x_id, vector<int> &y_id);
void manageFighters (vector<vector<int> > luts);

void drawScreens(int n_leitos, vector<int> pacientes, vector<vector<int> > lutadores);

int frontend(int n_leitos, vector<Saiyan*> saiyans);

#endif 