#include "state.h"

State::State(string name)
    : name(name)
{
    this->isFinalState = false;
}

void State::setFinal(bool isFinal){
    this->isFinalState = isFinal;
}

string State::getName(){
    return this->name;
}


bool State::isFinal(){
    return this->isFinalState;
}
