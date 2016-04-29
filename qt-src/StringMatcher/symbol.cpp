#include "symbol.h"

Symbol::Symbol(string symbol)
    : symbol(symbol)
{}

string Symbol::get(){
    return this->symbol;
}

const string Symbol::EPSILON = ":e:";
