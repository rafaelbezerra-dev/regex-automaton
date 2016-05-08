#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <vector>

//#include "nfa.h"
#include "dfa.h"
#include "utils.h"
#include "matcher.h"
#include "unittest.h"

using namespace std;

int main(int argc, char *argv[])
{
    UNIT_TEST::RUN_ALL();
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
    cout << "\n\nExample 3 : a.b+ " << endl;
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
