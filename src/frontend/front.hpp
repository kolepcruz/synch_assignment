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

void time (WINDOW* win, int udelay);
void printChar(WINDOW* win, int y, int x, int color, int val);
void printChar(WINDOW* win, int y, int x, int color, const char* c);
void desenhaLeito(int n_leitos);
void printLuts(WINDOW* win, vector<vector<int> > &luts, vector<int> & y_id, 
                  vector<vector<int> > & x_id, 
                  bool pos, int color, unsigned utime);
void printPowersSync(vector<vector<int> > &luts, vector<vector<int> > &x_id, vector<int> &y_id);
void desenhaLutDinamico (vector<vector<int> > luts);
void drawInicial(int n_leitos);
bool drawDinamico(int n_leitos, vector<int> pacientes, vector<vector<int> > lutadores);
void intro();
int frontend(int n_leitos, vector<Saiyan*> saiyans);

#endif 