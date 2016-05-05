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

//    unordered_map<int, unordered_map<string, vector<int>>>::const_iterator itr
//            = this->tb.find(from);
//    if (itr != this->tb.end()){
    if (this->tb.find(from) != this->tb.end()){
//        unordered_map<string, vector<int>> row = itr->second;
//        unordered_map<string, vector<int>>::const_iterator row_itr
//                = row.find(symbol);
//        if (row_itr != row.end()){
        if (this->tb[from].find(symbol) != this->tb[from].end()){
            this->tb[from][symbol].insert(to);
        }
        else{
            pair<string, unordered_set<int>> p;
            p.first = symbol;
            p.second = unordered_set<int>{to};
            this->tb[from].insert(p);
        }
    }
    else{
        pair<int, table_row> p;
        p.first = from;
        p.second = table_row{{ symbol, unordered_set<int>{to} }};
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

void DFA::setTransitions(vector<Transition> transitions){
    this->transitions = transitions;
}

DFATable DFA::getTable(){
    return this->table;
}

void DFA::setTable(DFATable table){
    this->table = table;
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


/********************************************
 *
 * ### NFA STATIC METHODS IMPLEMENTATIONS ###
 *
 ********************************************/


DFA DFA::FROM_NFA(NFA nfa){
    NFATable nfa_tabel = nfa.getTable();
    unordered_set<string> sets_visited;
    queue<unordered_set<int>> sets_queue;
    nfa_tabel.getTable()[0][Symbol::EPSILON];

}
