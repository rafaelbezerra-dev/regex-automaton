#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <vector>

//#include "nfa.h"
#include "dfa.h"
#include "utils.h"
#include "matcher.h"

using namespace std;

unordered_set<char> test(string symbol){
    uint8_t number_of_chars = 128;
    unordered_set<char> _opr_ = {'[','-',']','\\', '^', '(', ')'};
    unordered_set<char> _sym_;
    stack<char> opr_stack;
    stack<char> sym_stack;
    // [A-Z], [A-C], [0-9], a, A, ^A,[A-Za-z0-9_]

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
                            if (char_set.find((char)i) != char_set.end())
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
    return _sym_;
}


int main(int argc, char *argv[])
{

    string symbol;
    symbol = "[A-Za-z0-9_]"; cout << "[A-Za-z0-9_]" << endl;
    unordered_set<char> _sym_ = test(symbol);
    cout << "\tG = " << std::boolalpha
         << (_sym_.find('G') != _sym_.end()) << endl;
    cout << "\th = " << std::boolalpha
         << (_sym_.find('h') != _sym_.end()) << endl;
    cout << "\t6 = " << std::boolalpha
         << (_sym_.find('6') != _sym_.end()) << endl;
    cout << "\t. = " << std::boolalpha
         << (_sym_.find('.') != _sym_.end()) << endl;

    symbol = "[A-Z]"; cout << "[A-Z]" << endl;
    _sym_ = test(symbol);
    cout << "\tG = " << std::boolalpha
         << (_sym_.find('G') != _sym_.end()) << endl;
    cout << "\th = " << std::boolalpha
         << (_sym_.find('h') != _sym_.end()) << endl;
    cout << "\t6 = " << std::boolalpha
         << (_sym_.find('6') != _sym_.end()) << endl;


    symbol = "[0-9]"; cout << "[0-9]" << endl;
    _sym_ = test(symbol);
    cout << "\th = " << std::boolalpha
         << (_sym_.find('h') != _sym_.end()) << endl;
    cout << "\t6 = " << std::boolalpha
         << (_sym_.find('6') != _sym_.end()) << endl;

    symbol = "[^0-9]"; cout << "[^0-9]" << endl;
    _sym_ = test(symbol);
    cout << "\th = " << std::boolalpha
         << (_sym_.find('h') != _sym_.end()) << endl;
    cout << "\t6 = " << std::boolalpha
         << (_sym_.find('6') != _sym_.end()) << endl;

    symbol = "[ABC]"; cout << "[ABC]" << endl;
    _sym_ = test(symbol);
    cout << "\tB = " << std::boolalpha
         << (_sym_.find('B') != _sym_.end()) << endl;
    cout << "\tD = " << std::boolalpha
         << (_sym_.find('D') != _sym_.end()) << endl;

    symbol = "[^ABC]"; cout << "[^ABC]" << endl;
    _sym_ = test(symbol);
    cout << "\tB = " << std::boolalpha
         << (_sym_.find('B') != _sym_.end()) << endl;
    cout << "\tD = " << std::boolalpha
         << (_sym_.find('D') != _sym_.end()) << endl;


    symbol = "^A"; cout << "^A" << endl;
    _sym_ = test(symbol);
    cout << "\tA = " << std::boolalpha
         << (_sym_.find('A') != _sym_.end()) << endl;
    cout << "\th = " << std::boolalpha
         << (_sym_.find('h') != _sym_.end()) << endl;
    cout << "\t6 = " << std::boolalpha
         << (_sym_.find('6') != _sym_.end()) << endl;

    symbol = "\\["; cout << "\\[" << endl;
    _sym_ = test(symbol);
    cout << "\tb = " << std::boolalpha
         << (_sym_.find('6') != _sym_.end()) << endl;
    cout << "\t[ = " << std::boolalpha
         << (_sym_.find('[') != _sym_.end()) << endl;

    return 0;

    string src = "Lorem ipsum dolor sit amet, ut qui corpora expetendis, vocibus facilisis cum in. Id rebum solet his, qui no recusabo consetetur. Putent tincidunt sadipscing eam ea. Denique legendos interpretaris ad cum, ei quod fierent ponderum his, quo ex paulo albucius. Mea veri vidit dissentiet ad, no ius admodum deseruisse.";

    NFA a, b;

//    cout<<"\nFor the regular expression segment : (a)";
    a.addState("q0");
    a.addState("q1");
    a.addTransition(0, 1, "a");
    a.setFinalState(1);
//    a.display();
//  getch();

//    cout<<"\nFor the regular expression segment : (b)";
    b.addState("q0");
    b.addState("q1");
    b.addTransition(0, 1, "b");
    b.setFinalState(1);
//    b.display();
//  getch();

//    cout<<"\nFor the regular expression segment [Concatenation] : (a.b)";
//    NFA::CONCAT(a, b).display();
////  getch();

//    cout<<"\nFor the regular expression segment [Or] : (a|b)";
//    NFA::OR(a, b).display();
////  getch();

//    cout<<"\nFor the regular expression segment [zero or one] : (a?)";
//    NFA::ZERO_OR_ONE(a).display();
////  getch();

//    cout<<"\nFor the regular expression segment [zero or more] : (a*)";
//    NFA::ZERO_OR_MORE(a).display();
////  getch();

//    cout<<"\nFor the regular expression segment [one or more] : (a+)";
//    NFA::ONE_OR_MORE(a).display();
////  getch();

//    cout << "Example 1 : a.(a|b)" << endl;
//    NFA nfa = NFA::CONCAT(a, NFA::OR(a, b));
//    cout << "\n### NFA ###" << endl;
//    nfa.display();
//    DFA dfa = DFA::FROM_NFA(nfa);
//    cout << "\n### DFA ###" << endl;
//    dfa.display();

//    cout << "Example 1 : a.(a|b).b+" << endl;
//    nfa = NFA::CONCAT(NFA::CONCAT(a, NFA::OR(a, b)), NFA::ONE_OR_MORE(b));
//    cout << "\n### NFA ###" << endl;
//    nfa.display();
//    dfa = DFA::FROM_NFA(nfa);
//    cout << "\n### DFA ###" << endl;
//    dfa.display();

//    cout << "Example 2 : (u).(m).( ) " << endl;
    NFA nfa;
//    nfa.addState("q0");
//    nfa.addState("q1");
//    nfa.addState("q2");
//    nfa.addState("q3");
//    nfa.addState("q4");
//    nfa.addTransition(0, 1, "u");
//    nfa.addTransition(1, 2, "m");
//    nfa.addTransition(2, 3, " ");
//    nfa.setFinalState(3);
//    cout << "\n### NFA ###" << endl;
//    nfa.display();
    DFA dfa;
//    dfa = DFA::FROM_NFA(nfa);
//    cout << "\n### DFA ###" << endl;
//    dfa.display();

//    Matcher::MATCH(src, dfa);

    src = "babaaaaaaabbaaabbbaabbbbbbbbaaabababaaa";
    cout << "\n\nExample 3 : (u).(m).( ) " << endl;
    nfa = NFA::CONCAT(a, NFA::ONE_OR_MORE(b));
    cout << "\n### NFA ###" << endl;
    nfa.display();
    dfa = DFA::FROM_NFA(nfa);
    cout << "\n### DFA ###" << endl;
    dfa.display();

    Matcher::MATCH(src, dfa);

//    string re;
//    set<char> symbols;

//    cout<<"\n*****\t*****\t*****\n";
//    cout<<"\nFORMAT : \n"
//        <<"> Explicitly mention concatenation with a '.' operator \n"
//        <<"> Enclose every concatenation and or section by parantheses \n"
//        <<"> Enclose the entire regular expression with parantheses \n\n";

//    cout<<"For example : \nFor the regular expression (a.(b|c))  -- \n";
//    NFA example_nfa = re_to_nfa("(a.(b|c))");
//    example_nfa.display();

//    cout<<"\n\nEnter the regular expression in the above mentioned format - \n\n";
//    cin>>re;


    return 0;
}
