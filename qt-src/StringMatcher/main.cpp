#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <vector>

//#include "nfa.h"
#include "dfa.h"
#include "utils.h"

using namespace std;

int main(int argc, char *argv[])
{
    NFA a, b;

    cout<<"\nFor the regular expression segment : (a)";
    a.addState("q0");
    a.addState("q1");
    a.addTransition(0, 1, "a");
    a.setFinalState(1);
    a.display();
//  getch();

    cout<<"\nFor the regular expression segment : (b)";
    b.addState("q0");
    b.addState("q1");
    b.addTransition(0, 1, "b");
    b.setFinalState(1);
    b.display();
////  getch();


//    cout<<"\nNFA for : (a.(a|b).(a+))" << endl;
//    NFA nfa = NFA::CONCAT(NFA::CONCAT(a, NFA::OR(a, b)), NFA::ONE_OR_MORE(a));
//    nfa.display();
//    cout << endl << endl;
//    DFA dfa = DFA::FROM_NFA(nfa);
//    dfa.display();

//    return 0;

    cout<<"\nFor the regular expression segment [Concatenation] : (a.b)";
//    NFA ab = concat(a, b);
    NFA::CONCAT(a, b).display();
////  getch();

    cout<<"\nFor the regular expression segment [Or] : (a|b)";
    NFA::OR(a, b).display();
////  getch();

    cout<<"\nFor the regular expression segment [zero or one] : (a?)";
    NFA::ZERO_OR_ONE(a).display();
////  getch();

    cout<<"\nFor the regular expression segment [zero or more] : (a*)";
    NFA::ZERO_OR_MORE(a).display();
////  getch();

    cout<<"\nFor the regular expression segment [one or more] : (a+)";
    NFA::ONE_OR_MORE(a).display();
////  getch();

    cout << "Example 1 : a.(a|b)" << endl;
    NFA nfa = NFA::CONCAT(a, NFA::OR(a, b));
    cout << "\n### NFA ###" << endl;
    nfa.display();
    DFA dfa = DFA::FROM_NFA(nfa);
    cout << "\n### DFA ###" << endl;
    dfa.display();

    cout << "Example 1 : a.(a|b).b+" << endl;
    nfa = NFA::CONCAT(NFA::CONCAT(a, NFA::OR(a, b)), NFA::ONE_OR_MORE(b));
    cout << "\n### NFA ###" << endl;
    nfa.display();
    dfa = DFA::FROM_NFA(nfa);
    cout << "\n### DFA ###" << endl;
    dfa.display();

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
