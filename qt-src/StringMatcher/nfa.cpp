#include "nfa.h"

/*******************************************
 *
 * ### NFA TABLE METHODS IMPLEMENTATIONS ###
 *
 *******************************************/

void NFATable::setFinalState(int i){
    this->finalStateIndex = i;
}

int NFATable::getFinalState(){
    return this->finalStateIndex;
}

void NFATable::addTransition(int from, int to, string symbol){
    this->alphabet.insert(symbol);

//    unordered_map<int, unordered_map<string, vector<int>>>::const_iterator itr
//            = this->tb.find(from);
//    if (itr != this->tb.end()){
    if (this->tb.find(from) != this->tb.end()){
//        unordered_map<string, vector<int>> row = itr->second;
//        unordered_map<string, vector<int>>::const_iterator row_itr
//                = row.find(symbol);
//        if (row_itr != row.end()){
            //           vector<int> col = row_itr->second;
            //           col.push_back(to);
        if (this->tb[from].find(symbol) != this->tb[from].end()){
            this->tb[from][symbol].insert(to);
        }
        else{
            pair<string, int_set> p;
            p.first = symbol;
            p.second = int_set{to};
            this->tb[from].insert(p);
        }
    }
    else{
        pair<int, fa_table_row> p;
        p.first = from;
        p.second = fa_table_row{{ symbol, int_set{to} }};
        this->tb.insert(p);

    }
}


unordered_set<string> NFATable::getAlphabet(){
    return this->alphabet;
}

fa_table NFATable::getMapping(){
    return this->tb;
}

/*************************************
 *
 * ### NFA METHODS IMPLEMENTATIONS ###
 *
 *************************************/

NFA::NFA(){
    this->finalStateIndex = 0;
}

NFA::NFA(string regex) : regex(regex){}

NFA::NFA(vector<State> states, int finalState)
    : states(states){
    int size = states.size();
    for (int i = 0; i < size; i++)
        this->table.addTransition(i, i, Symbol::EPSILON);
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
    int i = this->states.size();
    this->states.push_back(State(name));
//  int i = this->states.size() - 1;
    this->table.addTransition(i, i, Symbol::EPSILON);
}

int NFA::countStates(){
    return this->states.size();
}

void NFA::setFinalState(int i){
    this->states[this->finalStateIndex].setFinal(false);
    this->states[i].setFinal(true);
    this->finalStateIndex = i;
    this->table.setFinalState(i);
}

int NFA::getFinalState(){
    return this->finalStateIndex;
}

void NFA::addTransition(int from, int to, string symbol){
    this->transitions.push_back(Transition(from, to, symbol));
    this->table.addTransition(from, to, symbol);
}

vector<Transition> NFA::getTransitions(){
    return this->transitions;
}

void NFA::setTransitions(vector<Transition> transitions){
    this->transitions = transitions;
}

NFATable NFA::getTable(){
    return this->table;
}

void NFA::setTable(NFATable table){
    this->table = table;
}


void NFA::display(){
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

void NFA::displayTable(){
    cout << "NFA displayTable not implemented yet." << endl;
}


/********************************************
 *
 * ### NFA STATIC METHODS IMPLEMENTATIONS ###
 *
 ********************************************/

NFA NFA::CONCAT(NFA left, NFA right){
    int nStates = left.countStates() + right.countStates() - 1;
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
    int nStates = nfa.countStates() + 1;
    vector<State> states;
    for (int i = 0; i < nStates; ++i) {
        states.push_back(State("q" + to_string(i)));
    }
    NFA res = NFA(states, nStates-1);

    vector<Transition> trans = nfa.getTransitions();
    for (vector<Transition>::iterator it = trans.begin();
         it != trans.end();++it){
        res.addTransition(it->from, it->to, it->symbol);
    }

    res.addTransition(0, nStates-1, Symbol::EPSILON);
    res.addTransition(nStates-2, 0, Symbol::EPSILON);

    return res;
}

NFA NFA::ZERO_OR_ONE(NFA nfa){
    int nStates = nfa.countStates() + 1;
    vector<State> states;
    for (int i = 0; i < nStates; ++i) {
        states.push_back(State("q" + to_string(i)));
    }
    NFA res = NFA(states, nStates-1);

    vector<Transition> trans = nfa.getTransitions();
    for (vector<Transition>::iterator it = trans.begin();
         it != trans.end();++it){
        res.addTransition(it->from, it->to, it->symbol);
    }

    res.addTransition(0, nStates-1, Symbol::EPSILON);
    res.addTransition(nStates-2, nStates-1, Symbol::EPSILON);

    return res;

}

NFA NFA::ONE_OR_MORE(NFA nfa){
    int nStates = nfa.countStates() + 1;
    vector<State> states;
    for (int i = 0; i < nStates; ++i) {
        states.push_back(State("q" + to_string(i)));
    }
    NFA res = NFA(states, nStates-1);

    vector<Transition> trans = nfa.getTransitions();
    for (vector<Transition>::iterator it = trans.begin();
         it != trans.end();++it){
        res.addTransition(it->from, it->to, it->symbol);
    }

    res.addTransition(nStates-2, 0, Symbol::EPSILON);
    res.addTransition(nStates-2, nStates-1, Symbol::EPSILON);

    return res;

}
