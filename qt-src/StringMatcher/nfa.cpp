#include "nfa.h"

/*********************************************
 *                                           *
 * ### NFA TABLE METHODS IMPLEMENTATIONS ### *
 *                                           *
 *********************************************/

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

/***************************************
 *                                     *
 * ### NFA METHODS IMPLEMENTATIONS ### *
 *                                     *
 ***************************************/

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

NFA::NFA(string s1,string s2, string trans_symbol)
    : NFA({State(s1), State(s2)}, 1){
    this->addTransition(0, 1, trans_symbol);
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
//    cout<<"\n";
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


/**********************************************
 *                                            *
 * ### NFA STATIC METHODS IMPLEMENTATIONS ### *
 * ### THOMPSON'S CONSTRUCTION METHODS    ### *
 *                                            *
 **********************************************/

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


/**********************************************
 *                                            *
 * ### NFA STATIC METHODS IMPLEMENTATIONS ### *
 * ### REGEX PROCESSING METHODS           ### *
 *                                            *
 **********************************************/

unordered_set<char> NFA::RESOLVE_SYMBOL(string symbol){
    uint8_t number_of_chars = 128;
    unordered_set<char> _opr_ = {'[','-',']','\\', '^', '(', ')'};
    unordered_set<char> _sym_;
    stack<char> opr_stack;
    stack<char> sym_stack;
    // [A-Z], [A-C], [0-9], a, A, ^A,[A-Za-z0-9_]
//    unordered_map<string, string>::const_iterator i = Symbol::SYMBOL_MAPPING.find(symbol);
//    if (i != Symbol::SYMBOL_MAPPING.end())
//        symbol = i->second;
    symbol = Symbol::MAP(symbol);

    for (auto ch : symbol){

        char last_op;
        if (!opr_stack.empty()) {
            last_op = opr_stack.top();
            if (last_op == '\\'){
                _sym_.insert(ch);
//                break;
                continue;
            }
        }

        if (_opr_.find(ch) == _opr_.end()){
            sym_stack.push(ch);
            if (!opr_stack.empty()) {
                if (last_op == '[' || last_op == '(' || last_op == ')'){
                    continue;
                }
                else if (last_op == '-'){
                    opr_stack.pop();
                    char ch_end = sym_stack.top();
                    sym_stack.pop();
                    char ch_start = sym_stack.top();
                    sym_stack.pop();

                    if (opr_stack.top() != '^')
                        for (int i = ch_start; i <= ch_end; i++)
                            _sym_.insert((char)i);
                    else
                        for (int i = 0; i < number_of_chars; i++)
                            if (i < ch_start || i > ch_end)
                                _sym_.insert((char)i);
                }
//                else if (last_op == ']'){
//                    break;
//                }
//                else if (last_op == '^'){
//                    char c = sym_stack.top();
//                    for (int i = 0; i < 128; i++)
//                        if (c != i)
//                            _sym_.insert((char)i);
//                    sym_stack.pop();
//                    break;
//                }
            }

        }
        else{
            if (ch == ']'){
                if (!sym_stack.empty()){
                    unordered_set<char> char_set;
                    while (!sym_stack.empty()){
                        char_set.insert(sym_stack.top());
                        sym_stack.pop();
                    }
                    if (opr_stack.top() == '[')
                        for (auto c : char_set)
                            _sym_.insert(c);
                    else
                        for (int i = 0; i < number_of_chars; i++)
                            if (char_set.find((char)i) == char_set.end())
                                _sym_.insert((char)i);
                }
                break;
            }
            else
                opr_stack.push(ch);
        }
    }

    if (!sym_stack.empty()){
        char c = sym_stack.top();
        sym_stack.pop();
        if (!opr_stack.empty() && opr_stack.top() == '^'){
            for (int i = 0; i < number_of_chars; i++)
                if (c != i)
                    _sym_.insert((char)i);
        }
        else
            _sym_.insert(c);
    }

    Symbol::ADD_RESOVLED_SYMBOLS(symbol, _sym_);

    return _sym_;
}

vector<char> NFA::SHUNTING_YARD(string regex){
    // based on https://gist.github.com/gmenard/6161825
    unordered_map<char, int> __precedence_map__ = {
        {'(', 1},
        {'|', 2},
        {'.', 3}, // explicit concatenation operator
        {'?', 4},
        {'*', 4},
        {'+', 4},
//        {'\\', 5},
//        {'^', 5} // uncomment this line to have [^0-9] transformed to [0-9]^
    };
    unordered_map<char, int>::const_iterator top_itr, current_itr;

    vector<char> __out__;
    stack<char> __stack__;
    string aux;

    for (auto c : regex){
        if (c == '('){
            __stack__.push(c);
        }
        else if (c == ')'){
            while (__stack__.top() != '('){
//                aux = "";
//                aux += __stack__.top();
//                __out__.push_back(aux);
                __out__.push_back(__stack__.top());
                __stack__.pop();
            }
            __stack__.pop();
        }
        else{
            while(!__stack__.empty()){
                char top = __stack__.top();

                int top_preced = 6,
                    curr_c_preced = 6;

                top_itr = __precedence_map__.find(top);
                if (top_itr != __precedence_map__.end())
                    top_preced = top_itr->second;

                current_itr = __precedence_map__.find(c);
                if (current_itr != __precedence_map__.end())
                    curr_c_preced = current_itr->second;

                if (top_preced >= curr_c_preced){
//                    aux = "";
//                    aux += __stack__.top();
//                    __out__.push_back(aux);
                    __out__.push_back(__stack__.top());
                    __stack__.pop();
                }
                else
                    break;
            }
            __stack__.push(c);
        }
    }

    while(!__stack__.empty()){
//        aux = "";
//        aux += __stack__.top();
//        __out__.push_back(aux);
        __out__.push_back(__stack__.top());
        __stack__.pop();
    }


    return __out__;
}

string NFA::SHUNTING_YARD_STRING(string regex){
    vector<char> v = NFA::SHUNTING_YARD(regex);
    string __out__ = "";

    for (auto s : v)
        __out__ += s;

    return __out__;
}

NFA NFA::FROM_REGEX(string regex){
    // (A|a).b*|(c|d) ---> Aa|b*.cd||
//    uint8_t __n_chars__ = 128;
    string __aux__;
    unordered_set<char> __opr__ = {'[','-',']','\\', '^', '(', ')', '|', '*', '+', '?', '.'};
    vector<char> __regx__ = NFA::SHUNTING_YARD(regex);
    stack<NFA> __NFAs__;
    NFA *new_nfa;
    bool __keep_chars__ = false;
    string __chars_kept__ = "";

    for (auto c : __regx__){
        if (__opr__.find(c) == __opr__.end()){
            //TODO: process symbo
            __aux__ = "";
            __aux__ += c;

            if (__keep_chars__){
                if (__chars_kept__ == "\\" || __chars_kept__ == "^"){
                    __aux__ = __chars_kept__ + __aux__;
                    __keep_chars__ = false;
                }

                __chars_kept__ += c;
            }

            if (!__keep_chars__){
                new_nfa = new NFA("q0", "q1", __aux__);
                __NFAs__.push(*new_nfa);
                NFA::RESOLVE_SYMBOL(__aux__);
            }

        } else {
            if (c == '['){
                if (!__keep_chars__){
                    __keep_chars__ = true;
                    __chars_kept__ = "[";
                }
                else{
                    __chars_kept__ += c;
                }
            }
            else if (c == '-'){
                __chars_kept__ += c;
            }
            else if (c == ']'){
                if (__keep_chars__){
                    __keep_chars__ = false;
                    __chars_kept__ += c;
                    new_nfa = new NFA("q0", "q1", __chars_kept__);
                    __NFAs__.push(*new_nfa);
                    NFA::RESOLVE_SYMBOL(__chars_kept__);
                }
                else{
                    __chars_kept__ += c;
                }

            }
            else if (c == '\\'){
                if (!__keep_chars__){
                    __keep_chars__ = true;
                    __chars_kept__ = "\\";
                }
                else{
                    __chars_kept__ += c;
                }
            }
            else if (c == '^'){
                if (!__keep_chars__){
                    __keep_chars__ = true;
                    __chars_kept__ = "^";
                }
                else{
                    __chars_kept__ += c;
                }
            }
            else if (c == '('){
            }
            else if (c == ')'){
            }
            else if (c == '.'){
                NFA right = __NFAs__.top();
                __NFAs__.pop();
                NFA left = __NFAs__.top();
                __NFAs__.pop();
                __NFAs__.push(NFA::CONCAT(left, right));
            }
            else if (c == '|'){
                NFA right = __NFAs__.top();
                __NFAs__.pop();
                NFA left = __NFAs__.top();
                __NFAs__.pop();
                __NFAs__.push(NFA::OR(left, right));
            }
            else if (c == '*'){
                NFA n = __NFAs__.top();
                __NFAs__.pop();
                __NFAs__.push(NFA::ZERO_OR_MORE(n));
            }
            else if (c == '+'){
                NFA n = __NFAs__.top();
                __NFAs__.pop();
                __NFAs__.push(NFA::ONE_OR_MORE(n));
            }
            else if (c == '?'){
                NFA n = __NFAs__.top();
                __NFAs__.pop();
                __NFAs__.push(NFA::ZERO_OR_ONE(n));
            }
        }
    }

    NFA res = __NFAs__.top();
    return res;
}

NFA NFA::FROM_REGEX_USING_PARSER(string regex){
    inorder_exp i(regex);
    i.first_inorder();
    i.second_inorder();
    Shungting_yard p(i.get_inorder());
    vector<string> n2post = p.in2post();
//    p.show();
    string __regx__("");
    for (auto x : n2post){
        __regx__ += x;
    }
//    p.show();

    string __aux__;
    unordered_set<char> __opr__ = {'[','-',']','\\', '^', '(', ')', '|', '*', '+', '?', '.'};
//    vector<char> __regx__ = NFA::SHUNTING_YARD(regex);
    stack<NFA> __NFAs__;
    NFA *new_nfa;
    bool __keep_chars__ = false;
    string __chars_kept__ = "";

    for (auto c : __regx__){
        if (__opr__.find(c) == __opr__.end()){
            //TODO: process symbo
            __aux__ = "";
            __aux__ += c;

            if (__keep_chars__){
                if (__chars_kept__ == "\\" || __chars_kept__ == "^"){
                    __aux__ = __chars_kept__ + __aux__;
                    __keep_chars__ = false;
                }

                __chars_kept__ += c;
            }

            if (!__keep_chars__){
                new_nfa = new NFA("q0", "q1", __aux__);
                __NFAs__.push(*new_nfa);
                NFA::RESOLVE_SYMBOL(__aux__);
            }

        } else {
            if (c == '['){
                if (!__keep_chars__){
                    __keep_chars__ = true;
                    __chars_kept__ = "[";
                }
                else{
                    __chars_kept__ += c;
                }
            }
            else if (c == '-'){
                __chars_kept__ += c;
            }
            else if (c == ']'){
                if (__keep_chars__){
                    __keep_chars__ = false;
                    __chars_kept__ += c;
                    new_nfa = new NFA("q0", "q1", __chars_kept__);
                    __NFAs__.push(*new_nfa);
                    NFA::RESOLVE_SYMBOL(__chars_kept__);
                }
                else{
                    __chars_kept__ += c;
                }

            }
            else if (c == '\\'){
                if (!__keep_chars__){
                    __keep_chars__ = true;
                    __chars_kept__ = "\\";
                }
                else{
                    __chars_kept__ += c;
                }
            }
            else if (c == '^'){
                if (!__keep_chars__){
                    __keep_chars__ = true;
                    __chars_kept__ = "^";
                }
                else{
                    __chars_kept__ += c;
                }
            }
            else if (c == '('){
            }
            else if (c == ')'){
            }
            else if (c == '.'){
                NFA right = __NFAs__.top();
                __NFAs__.pop();
                NFA left = __NFAs__.top();
                __NFAs__.pop();
                __NFAs__.push(NFA::CONCAT(left, right));
            }
            else if (c == '|'){
                NFA right = __NFAs__.top();
                __NFAs__.pop();
                NFA left = __NFAs__.top();
                __NFAs__.pop();
                __NFAs__.push(NFA::OR(left, right));
            }
            else if (c == '*'){
                NFA n = __NFAs__.top();
                __NFAs__.pop();
                __NFAs__.push(NFA::ZERO_OR_MORE(n));
            }
            else if (c == '+'){
                NFA n = __NFAs__.top();
                __NFAs__.pop();
                __NFAs__.push(NFA::ONE_OR_MORE(n));
            }
            else if (c == '?'){
                NFA n = __NFAs__.top();
                __NFAs__.pop();
                __NFAs__.push(NFA::ZERO_OR_ONE(n));
            }
        }
    }

    NFA res = __NFAs__.top();
    return res;
}









