#ifndef SYMBOL_H
#define SYMBOL_H

#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>

using namespace std;


class Symbol
{
private:
//    string symbol;
public:
    static unordered_map<string, unordered_set<char>> RESOVLED_SYMBOLS;
    static const unordered_map<string, string> SYMBOL_MAPPING;
    static const string EPSILON;
//    Symbol(string symbol);
//    string get();

    static void ADD_RESOVLED_SYMBOLS(string symbol, unordered_set<char> resolution);

};

#endif // SYMBOL_H
