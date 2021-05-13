#ifndef __CONTEXT_HPP__
#define __CONTEXT_HPP__
#include "Infirmary.hpp"
#include "Saiyan.hpp"

struct Context{
    Saiyan* self;
    Infirmary &inf;
};

#endif //__CONTEXT_HPP__