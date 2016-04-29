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
#include <utility>

#include "symbol.h"
#include "transition.h"
#include "state.h"

using namespace std;


class NFATable
{
private:
    unordered_map<int, unordered_map<string, vector<int>>> tb;
    unordered_set<string> alphabet;
    int finalStateIndex;

public:
    void setFinalState(int i);
    void addTransition(int from, int to, string symbol);
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
    vector<State> getStates();
    State getState(int i);
    void addState(string name);
    int countState();
    void setFinalState(int i);
    void addTransition(int from, int to, string symbol);
    void display();
    void displayTable();

    static NFA concat(NFA left, NFA right);
    static NFA or_selection(NFA left, NFA right);
    static NFA zero_or_more(NFA nfa);
    static NFA zero_or_one(NFA nfa);
    static NFA one_or_more(NFA nfa);


};

#endif // NFA_H
