#include "dfa.h"

/*******************************************
 *
 * ### DFA TABLE METHODS IMPLEMENTATIONS ###
 *
 *******************************************/


void DFATable::addFinalState(int i){
    this->finalStateIndexes.insert(i);
}

void DFATable::addTransition(int from, int to, string symbol){
    this->alphabet.insert(symbol);

    unordered_map<int, unordered_map<string, vector<int>>>::const_iterator itr
            = this->tb.find(from);
    if (itr != this->tb.end()){
        unordered_map<string, vector<int>> row = itr->second;
        unordered_map<string, vector<int>>::const_iterator row_itr
                = row.find(symbol);
        if (row_itr != row.end()){
            this->tb[from][symbol].push_back(to);
        }
        else{
            pair<string, vector<int>> p;
            p.first = symbol;
            p.second = vector<int>{to};
            this->tb[from].insert(p);
        }
    }
    else{
        pair<int, unordered_map<string, vector<int>>> p;
        p.first = from;
        p.second = unordered_map<string, vector<int>>{{ symbol, vector<int>{to} }};
        this->tb.insert(p);

    }
}

/*************************************
 *
 * ### DFA METHODS IMPLEMENTATIONS ###
 *
 *************************************/

DFA::DFA(){}

DFA::DFA(string regex) : regex(regex){}

DFA::DFA(vector<State> states) : states(states){}

vector<State> DFA::getStates(){
    return this->states;
}

State DFA::getState(int i){
    return this->states[i];
}

void DFA::addState(string name){
    this->states.push_back(State(name));
    int i = this->states.size() -1;
    this->table.addTransition(i, i, Symbol::EPSILON);
}

//int DFA::countStates();

//void DFA::addFinalState(int i);

//unordered_set<int> DFA::getFinalStates();

//void DFA::addTransition(int from, int to, string symbol);

//vector<Transition> DFA::getTransitions();

//void DFA::display();

//void DFA::displayTable();


///********************************************
// *
// * ### NFA STATIC METHODS IMPLEMENTATIONS ###
// *
// ********************************************/


//static DFA DFA::FROM_NFA(NFA nfa);
