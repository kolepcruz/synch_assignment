#ifndef __VIEW_H__
#define __VIEW_H__
#include<bits/stdc++.h>
#include <ncurses.h>
#include <ctype.h>
#include <string>
#include <sys/ioctl.h> // biblioteca útil para mensurar tamanhos do terminal.

#ifdef _WIN32
    #define _WIN32
    #include <Windows.h>
#else
    #include <unistd.h>
#endif

typedef unsigned int ui;

using namespace std;
int frontend();
void drawInicial(int n_leitos, int n_lutadores);
void intro();
void desenhaLutadores(WINDOW* ringue, int n_lut);
void desenhaLeito(WINDOW * enfermaria, int n_leitos);
int get_lutadores();
int get_leitos();

#endif //__VIEW_H__

