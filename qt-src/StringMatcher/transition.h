#ifndef TRANSITION_H
#define TRANSITION_H
#include <iostream>
#include "symbol.h"

using namespace std;

class Transition
{
private:
public:
    int from;
    int to;
    string symbol;
    Transition(int from, int to, string symbol);
};

#endif // TRANSITION_H
