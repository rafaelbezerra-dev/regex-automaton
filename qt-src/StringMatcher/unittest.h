#ifndef UNITTEST_H
#define UNITTEST_H

#include <iostream>
#include <iterator>
#include <string>
#include <regex>
//#include <chrono>
//#include <sys/time.h>
//#include <time.h>       /* clock_t, clock, CLOCKS_PER_SEC */

#include "nfa.h"
#include "dfa.h"
#include "matcher.h"
#include "utils.h"

#include "inorder_exp.hpp"
#include "shungting_yard.hpp"
#include "regex_library.hpp"


using namespace std;
//using namespace std::chrono;

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

    static void NEW_PARSER_MATCH_STRING();
    static void NEW_PARSER_MATCH_FILE();

    static void BENCHMARK_SMALL();
    static void BENCHMARK_BIG();
};

#endif // UNITTEST_H
