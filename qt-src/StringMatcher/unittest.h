#ifndef UNITTEST_H
#define UNITTEST_H

#include "nfa.h"

class UNIT_TEST
{
public:
//    UnitTest();

    static void RUN_ALL();
    static bool NFA_UNMARSHAL_SYMBOL();
    static bool NFA_SHUNTING_YARD();
    static bool NFA_FROM_REGEX();
};

#endif // UNITTEST_H
