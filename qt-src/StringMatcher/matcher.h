#ifndef MATCHER_H
#define MATCHER_H

#include "dfa.h"
#include "nfa.h"
#include "utils.h"

#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

class Matcher
{
private:
    DFA dfa;
public:
//    Matcher();
    Matcher(DFA dfa);

    vector<pair<int, int>> match(string src);

    static void MATCH_FILE(string file, DFA dfa, bool print_nicely);
    static vector<pair<int, int>> MATCH_STRING(string src, DFA dfa);
    static void PRINT_NICELY(string src, vector<pair<int, int>> matched_indexes);
};

#endif // MATCHER_H
