#ifndef MATCHER_H
#define MATCHER_H

#include "dfa.h"
#include "nfa.h"
#include "utils.h"
#include <vector>

using namespace std;

class Matcher
{
private:
    DFA dfa;
public:
//    Matcher();
    Matcher(DFA dfa);

    void match(string src);

    static void MATCH(string src, DFA dfa);
};

#endif // MATCHER_H
