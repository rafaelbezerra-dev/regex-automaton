#ifndef DFA_H
#define DFA_H


#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <utility>

#include "symbol.h"
#include "transition.h"
#include "state.h"
#include "nfa.h"

using namespace std;



class DFATable
{
private:
    unordered_map<int, unordered_map<string, vector<int>>> tb;
    unordered_set<string> alphabet;
    unordered_set<int> finalStateIndexes;

public:
    void addFinalState(int i);
    void addTransition(int from, int to, string symbol);
};


class DFA
{
private:
    DFATable table;
    vector<State> states;
    vector<Transition> transitions;
    unordered_set<int> finalStateIndexes;
    string regex;
public:
    DFA();
    DFA(string regex);
    DFA(vector<State> states);
    vector<State> getStates();
    State getState(int i);
    void addState(string name);
    int countStates();
    void addFinalState(int i);
    unordered_set<int> getFinalStates();
    void addTransition(int from, int to, string symbol);
    vector<Transition> getTransitions();
    void display();
    void displayTable();

    static DFA FROM_NFA(NFA nfa);

};

#endif // DFA_H
