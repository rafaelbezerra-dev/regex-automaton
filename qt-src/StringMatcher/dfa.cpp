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

int DFA::countStates() {
    return this->states.size();
}

void DFA::addFinalState(int i){
    this->states[i].setFinal(true);
    this->finalStateIndexes.insert(i);
    this->table.addFinalState(i);
}

unordered_set<int> DFA::getFinalStates(){
    return this->finalStateIndexes;
}

void DFA::addTransition(int from, int to, string symbol){
    this->transitions.push_back(Transition(from, to, symbol));
    this->table.addTransition(from, to, symbol);
}

vector<Transition> DFA::getTransitions(){
    return this->transitions;
}

void DFA::display(){
    cout<<"\n";
    Transition trans;
    for(unsigned int i = 0; i < this->transitions.size(); i++) {
        trans = this->transitions.at(i);
        string fromStName;
        string toStName;

        if (this->states[trans.from].isFinal()){
            fromStName = "{" + this->states[trans.from].getName() + "}";
        }
        else{
            fromStName = " " + this->states[trans.from].getName()+ " ";
        }

        if (this->states[trans.to].isFinal()){
            toStName = "{" + this->states[trans.to].getName()+ "}";
        }
        else{
            toStName = " " + this->states[trans.to].getName()+ " ";
        }

        cout << fromStName << " --> " << toStName
             << " : Symbol - " << trans.symbol
             << endl;
    }
}

void DFA::displayTable(){
    cout << "DFA displayTable not implemented yet." << endl;
}


///********************************************
// *
// * ### NFA STATIC METHODS IMPLEMENTATIONS ###
// *
// ********************************************/


//static DFA DFA::FROM_NFA(NFA nfa);
