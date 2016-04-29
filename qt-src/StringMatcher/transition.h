#ifndef TRANSITION_H
#define TRANSITION_H
#include <iostream>
#include "symbol.h"

using namespace std;

class Transition
{
private:
    int from;
    int to;
    string symbol;
public:
    Transition(int from, int to, string symbol);
};

#endif // TRANSITION_H
