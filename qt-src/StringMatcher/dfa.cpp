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


unordered_set<string> DFATable::getAlphabet(){
    return this->alphabet;
}

fa_table DFATable::getMapping(){
    return this->tb;
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
//    int i = this->states.size() -1;
//    this->table.addTransition(i, i, Symbol::EPSILON);
}

int DFA::countStates() {
    return this->states.size();
}

void DFA::addFinalState(int i){
    this->states[i].setFinal(true);
    this->finalStateIndexes.insert(i);
    this->table.addFinalState(i);
}

int_set DFA::getFinalStates(){
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
    DFA dfa;
    NFATable nfa_table = nfa.getTable();
    fa_table nfa_table_map = nfa_table.getMapping();
    unordered_set<string> visited;
    int_set first_set = nfa_table_map[0][Symbol::EPSILON];
    queue<int_set> set_queue= queue<int_set>{{first_set}};
//    set_queue.push(first_set);
    int dfa_state_count = 0;
    string set_name = Utils::TO_STRING(first_set);
    unordered_map<string, int> dfa_state_mapping
            = unordered_map<string, int> {{ set_name, 0 }};
    dfa.addState("q" + to_string(0));
    int nfa_state_count = nfa_table_map.size();

    while (!set_queue.empty()){
        int_set curr_state_set = set_queue.front();
        set_queue.pop();
//        set_name = Utils::TO_STRING(curr_state_set);
        string state_name = Utils::TO_STRING(curr_state_set);
        if (visited.find(state_name) != visited.end())
            continue;
        visited.insert(state_name);
        bool is_final_state = false;

        {
            bool states_visited[nfa_state_count] = { 0 };
            for (auto st : curr_state_set)
                states_visited[st] = true;

            for (auto curr_state : curr_state_set){
                int_set e_closure = nfa_table_map[curr_state][Symbol::EPSILON];
                for (auto e_closure_state : e_closure){
                    if (!states_visited[e_closure_state]){
                        curr_state_set.insert(e_closure_state);
                        states_visited[e_closure_state] = true;
                    }
                }
            }

//            delete states_visited;
        }

        for (auto symbol : nfa_table.getAlphabet()){
            if (symbol == Symbol::EPSILON)
                continue;
            int_set next_set;
            bool states_visited[nfa_state_count] = { 0 };
            for (auto curr_state : curr_state_set){
                if (!is_final_state && curr_state == nfa_table.getFinalState())
                    is_final_state = true;
                if (nfa_table_map[curr_state].find(symbol) != nfa_table_map[curr_state].end()){
                    int_set next_states = nfa_table_map[curr_state][symbol];
                    for (auto ns : next_states){
                        int_set e_closure = nfa_table_map[ns][Symbol::EPSILON];
                        for (auto e_closure_state : e_closure){
                            if (!states_visited[e_closure_state]){
                                next_set.insert(e_closure_state);
                                states_visited[e_closure_state] = true;
                            }
                        }
                    }

                }
            }

            string next_state_name = Utils::TO_STRING(next_set);
            if (next_set.size() > 0){
                if (dfa_state_mapping.find(next_state_name) == dfa_state_mapping.end()){
//                    dfa.addState(next_state_name);
                    dfa_state_count++;
                    dfa.addState("q" + to_string(dfa_state_count));
                    dfa_state_mapping.insert({next_state_name, dfa_state_count});
                }
                dfa.addTransition(dfa_state_mapping[state_name], dfa_state_mapping[next_state_name], symbol);
            }
//            else{
//                dfa.addTransition(dfa_state_mapping[state_name], 0, symbol);
//            }

            if (is_final_state)
                dfa.addFinalState(dfa_state_mapping[state_name]);

            if (next_set.size() > 0 && visited.find(next_state_name) == visited.end()){
                set_queue.push(next_set);
            }

//            delete states_visited;
        }

    }

    return dfa;
}
