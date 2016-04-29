#ifndef SYMBOL_H
#define SYMBOL_H

#include <iostream>
#include <string>

using namespace std;


class Symbol
{
private:
    string symbol;

public:
    static const string EPSILON;
    Symbol(string symbol);
    string get();
};

#endif // SYMBOL_H
