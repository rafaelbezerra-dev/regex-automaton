#include "symbol.h"

//Symbol::Symbol(string symbol)
//    : symbol(symbol)
//{}

//string Symbol::get(){
//    return this->symbol;
//}


const string Symbol::EPSILON = ":e:";
const unordered_map<string, string> Symbol::SYMBOL_MAPPING = {
    {"\\.", "[^\n\r]"},
    {"\\w", "[A-Za-z0-9_]"},
    {"\\W", "[^A-Za-z0-9_]"},
    {"\\d", "[0-9]"},
    {"\\D", "[^0-9]"},
    {"\\s", "[\n\r\t]"},
    {"\\S", "[^\n\r\t]"},
//    {"", ""},
//    {"", ""}
};

unordered_map<string, unordered_set<char>> Symbol::RESOVLED_SYMBOLS = unordered_map<string, unordered_set<char>>{};

void Symbol::ADD_RESOVLED_SYMBOLS(string symbol, unordered_set<char> resolution){
    RESOVLED_SYMBOLS.insert({symbol, resolution});
}

string Symbol::MAP(string symbol){
    unordered_map<string, string>::const_iterator i = Symbol::SYMBOL_MAPPING.find(symbol);
    if (i != Symbol::SYMBOL_MAPPING.end())
        return i->second;
    else
        return symbol;
}
