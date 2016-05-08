#ifndef UNITTEST_H
#define UNITTEST_H

#include <iostream>

#include "nfa.h"
#include "dfa.h"
#include "matcher.h"
#include "utils.h"

using namespace std;

class UNIT_TEST
{
public:
//    UnitTest();

    static void RUN_ALL();
    static void CONSTRUCTIONS();
    static void NFA_RESOLVE_SYMBOL();
    static void NFA_SHUNTING_YARD();
    static void NFA_FROM_REGEX();
    static void MATCHER_MATCH_FILE();
};

#endif // UNITTEST_H
