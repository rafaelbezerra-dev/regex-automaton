#ifndef NFA_H
#define NFA_H

#include <iostream>
#include <vector>
#include <string>
//#include <set>
//#include <map>
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <queue>
#include <utility>

#include "symbol.h"
#include "transition.h"
#include "state.h"
#include "utils.h"

#include "inorder_exp.hpp"
#include "shungting_yard.hpp"
#include "regex_library.hpp"

using namespace std;

class NFATable
{
private:
    fa_table tb;
    unordered_set<string> alphabet;
    int finalStateIndex;

public:
    void setFinalState(int i);
    int getFinalState();
    void addTransition(int from, int to, string symbol);
    unordered_set<string> getAlphabet();
    fa_table getMapping();
};

class NFA
{
private:
    NFATable table;
    vector<State> states;
    vector<Transition> transitions;
    int finalStateIndex;
    string regex;
public:
    NFA();    
    NFA(string regex);
    NFA(vector<State> states, int finalState);
    NFA(string s1, string s2, string trans_symbol);
    vector<State> getStates();
    State getState(int i);
    void addState(string name);
    int countStates();
    void setFinalState(int i);
    int getFinalState();
    void addTransition(int from, int to, string symbol);
    vector<Transition> getTransitions();
    void setTransitions(vector<Transition> transitions);
    NFATable getTable();
    void setTable(NFATable table);
    void display();
    void displayTable();

    static NFA CONCAT(NFA left, NFA right);
    static NFA OR(NFA left, NFA right);
    static NFA ZERO_OR_MORE(NFA nfa);
    static NFA ZERO_OR_ONE(NFA nfa);
    static NFA ONE_OR_MORE(NFA nfa);

    static unordered_set<char> RESOLVE_SYMBOL(string symbol);
    static vector<char> SHUNTING_YARD(string regex);
    static string SHUNTING_YARD_STRING(string regex);
    static NFA FROM_REGEX(string regex);
    static NFA FROM_REGEX_USING_PARSER(string regex);


};

#endif // NFA_H
