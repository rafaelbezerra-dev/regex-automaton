#ifndef STATE_H
#define STATE_H

#include <iostream>
#include <vector>
#include "transition.h"

using namespace std;

class State
{
private:
    string name;
    bool isFinalState;

public:
    State(string name);
    void setFinal(bool isFinal);
    bool isFinal();
};

#endif // STATE_H
