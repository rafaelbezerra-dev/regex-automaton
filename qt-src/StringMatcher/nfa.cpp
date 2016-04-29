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

int NFA::countStates(){
    return this->states.size();
}

void NFA::setFinalState(int i){
    ((State)this->states[this->finalStateIndex]).setFinal(false);
    ((State)this->states[i]).setFinal(true);
    this->finalStateIndex = i;
    this->table.setFinalState(i);
}

void NFA::addTransition(int from, int to, string symbol){
    this->transitions.push_back(Transition(from, to, symbol));
    this->table.addTransition(from, to, symbol);
}

vector<Transition> NFA::getTransitions(){
    return this->transitions;
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

NFA NFA::CONCAT(NFA left, NFA right){
    int nStates = left.countStates() + right.countStates() + 1;
    vector<State> states;
    for (int i = 0; i < nStates; ++i) {
        states.push_back(State("q" + to_string(i)));
    }
    NFA res = NFA(states, nStates-1);

    vector<Transition> trans = left.getTransitions();
    for (vector<Transition>::iterator it = trans.begin();
         it != trans.end();++it){
        res.addTransition(it->from, it->to, it->symbol);
    }

    int i = left.countStates() - 1;

    trans = right.getTransitions();
    for (vector<Transition>::iterator it = trans.begin();
         it != trans.end();++it){
        res.addTransition(it->from + i, it->to + i, it->symbol);
    }

    return res;
}

NFA NFA::OR(NFA left, NFA right){
    int nStates = left.countStates() + right.countStates() + 2;
    int finalState = nStates -1;
    vector<State> states;
    for (int i = 0; i < nStates; ++i) {
        states.push_back(State("q" + to_string(i)));
    }
    NFA res = NFA(states, nStates-1);

    res.addTransition(0, 1, Symbol::EPSILON);
    vector<Transition> trans = left.getTransitions();
    for (vector<Transition>::iterator it = trans.begin();
         it != trans.end();++it){
        res.addTransition(it->from+1, it->to+1, it->symbol);
    }
    int i = left.countStates();
    res.addTransition(i, finalState, Symbol::EPSILON);

    i++;
    res.addTransition(0, i, Symbol::EPSILON);
    trans = right.getTransitions();
    for (vector<Transition>::iterator it = trans.begin();
         it != trans.end();++it){
        res.addTransition(it->from+i, it->to+i, it->symbol);
    }
    res.addTransition(right.countStates()+i-1, finalState, Symbol::EPSILON);

    return res;
}

NFA NFA::ZERO_OR_MORE(NFA nfa){

}

NFA NFA::ZERO_OR_ONE(NFA nfa){

}

NFA NFA::ONE_OR_MORE(NFA nfa){

}
