#include "state.h"

State::State(string name)
    : name(name)
{
    this->isFinalState = false;
}

void State::setFinal(bool isFinal){
    this->isFinalState = isFinal;
}

bool State::isFinal(){
    return this->isFinalState;
}
