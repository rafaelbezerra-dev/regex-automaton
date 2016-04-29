#include "nfa.h"

/*******************************************
 *
 * ### NFA TABLE METHODS IMPLEMENTATIONS ###
 *
 *******************************************/

void NFATable::setFinalState(int i){
    this->finalStateIndex = i;
}

void NFATable::addTransition(int from, int to, string symbol){
    this->alphabet.insert(symbol);

    unordered_map<int, unordered_map<string, vector<int>>>::const_iterator itr
            = this->tb.find(from);
    if (itr != this->tb.end()){
        unordered_map<string, vector<int>> row = itr->second;
        unordered_map<string, vector<int>>::const_iterator row_itr
                = row.find(symbol);
        if (row_itr != row.end()){
//           vector<int> col = row_itr->second;
//           col.push_back(to);
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
 * ### NFA METHODS IMPLEMENTATIONS ###
 *
 *************************************/

NFA::NFA(){}

NFA::NFA(string regex) : regex(regex){}

NFA::NFA(vector<State> states, int finalState)
    : states(states){
    this->finalStateIndex = 0;
    this->setFinalState(finalState);
}

vector<State> NFA::getStates()
{
    return this->states;
}

State NFA::getState(int i)
{
    return this->states[i];
}

void NFA::addState(string name){
    this->states.push_back(State(name));
    int i = this->states.size() -1;
    this->table.addTransition(i, i, Symbol::EPSILON);
}

int NFA::countState(){
    return this->states.size();
}

void NFA::setFinalState(int i){
    ((State)this->states[this->finalStateIndex]).setFinal(false);
    ((State)this->states[i]).setFinal(true);
    this->finalStateIndex = i;
    this->table.setFinalState(i);
}

void NFA::display(){
    cout << "NFA display not implemented yet." << endl;
}

void NFA::displayTable(){
    cout << "NFA displayTable not implemented yet." << endl;
}


/********************************************
 *
 * ### NFA STATIC METHODS IMPLEMENTATIONS ###
 *
 ********************************************/

NFA NFA::concat(NFA left, NFA right){

}

NFA NFA::or_selection(NFA left, NFA right){

}

NFA NFA::zero_or_more(NFA nfa){

}

NFA NFA::zero_or_one(NFA nfa){

}

NFA NFA::one_or_more(NFA nfa){

}
