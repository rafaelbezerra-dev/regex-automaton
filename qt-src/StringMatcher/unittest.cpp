#include "unittest.h"

void UNIT_TEST::RUN_ALL(){

    cout << "*****************************" << endl
         << "*    STARTING UNIT TESTS    *"   << endl
         << "*****************************" << endl
         << endl;
//    cout << "TEST: NFA_RESOLVE_SYMBOL... " << endl;
//    UNIT_TEST::NFA_RESOLVE_SYMBOL();

//    cout << "TEST: NFA_SHUNTING_YARD... " << endl;
//    UNIT_TEST::NFA_SHUNTING_YARD();

    cout << "TEST: NFA_FROM_REGEX... " << endl;
    UNIT_TEST::NFA_FROM_REGEX();
}
bool UNIT_TEST::NFA_RESOLVE_SYMBOL(){

    string symbol;
    symbol = "[A-Za-z0-9_]"; cout << symbol << endl;
    unordered_set<char> _sym_ = NFA::RESOLVE_SYMBOL(symbol);
    cout << "\tG = " << std::boolalpha
         << (_sym_.find('G') != _sym_.end()) << endl;
    cout << "\th = " << std::boolalpha
         << (_sym_.find('h') != _sym_.end()) << endl;
    cout << "\t6 = " << std::boolalpha
         << (_sym_.find('6') != _sym_.end()) << endl;
    cout << "\t. = " << std::boolalpha
         << (_sym_.find('.') != _sym_.end()) << endl;
    cout << "\t_ = " << std::boolalpha
         << (_sym_.find('_') != _sym_.end()) << endl;

    symbol = "[A-Z]"; cout << symbol << endl;
    _sym_ = NFA::RESOLVE_SYMBOL(symbol);
    cout << "\tG = " << std::boolalpha
         << (_sym_.find('G') != _sym_.end()) << endl;
    cout << "\th = " << std::boolalpha
         << (_sym_.find('h') != _sym_.end()) << endl;
    cout << "\t6 = " << std::boolalpha
         << (_sym_.find('6') != _sym_.end()) << endl;


    symbol = "[0-9]"; cout << symbol << endl;
    _sym_ = NFA::RESOLVE_SYMBOL(symbol);
    cout << "\th = " << std::boolalpha
         << (_sym_.find('h') != _sym_.end()) << endl;
    cout << "\t6 = " << std::boolalpha
         << (_sym_.find('6') != _sym_.end()) << endl;

    symbol = "[^0-9]"; cout << symbol << endl;
    _sym_ = NFA::RESOLVE_SYMBOL(symbol);
    cout << "\th = " << std::boolalpha
         << (_sym_.find('h') != _sym_.end()) << endl;
    cout << "\t6 = " << std::boolalpha
         << (_sym_.find('6') != _sym_.end()) << endl;

    symbol = "[ABC]"; cout << symbol << endl;
    _sym_ = NFA::RESOLVE_SYMBOL(symbol);
    cout << "\tB = " << std::boolalpha
         << (_sym_.find('B') != _sym_.end()) << endl;
    cout << "\tD = " << std::boolalpha
         << (_sym_.find('D') != _sym_.end()) << endl;

    symbol = "[^ABC]"; cout << symbol << endl;
    _sym_ = NFA::RESOLVE_SYMBOL(symbol);
    cout << "\tB = " << std::boolalpha
         << (_sym_.find('B') != _sym_.end()) << endl;
    cout << "\tD = " << std::boolalpha
         << (_sym_.find('D') != _sym_.end()) << endl;


    symbol = "^A"; cout << symbol << endl;
    _sym_ = NFA::RESOLVE_SYMBOL(symbol);
    cout << "\tA = " << std::boolalpha
         << (_sym_.find('A') != _sym_.end()) << endl;
    cout << "\th = " << std::boolalpha
         << (_sym_.find('h') != _sym_.end()) << endl;
    cout << "\t6 = " << std::boolalpha
         << (_sym_.find('6') != _sym_.end()) << endl;

    symbol = "\\["; cout << symbol << endl;
    _sym_ = NFA::RESOLVE_SYMBOL(symbol);
    cout << "\tb = " << std::boolalpha
         << (_sym_.find('b') != _sym_.end()) << endl;
    cout << "\t[ = " << std::boolalpha
         << (_sym_.find('[') != _sym_.end()) << endl;

    symbol = "\\w"; cout << symbol << endl;
    _sym_ = NFA::RESOLVE_SYMBOL(symbol);
    cout << "\tH = " << std::boolalpha
         << (_sym_.find('H') != _sym_.end()) << endl;
    cout << "\tj = " << std::boolalpha
         << (_sym_.find('j') != _sym_.end()) << endl;
    cout << "\t8 = " << std::boolalpha
         << (_sym_.find('8') != _sym_.end()) << endl;
    cout << "\t_ = " << std::boolalpha
         << (_sym_.find('_') != _sym_.end()) << endl;

    symbol = "\\s"; cout << symbol << endl;
    _sym_ = NFA::RESOLVE_SYMBOL(symbol);
    cout << "\t\\n = " << std::boolalpha
         << (_sym_.find('\n') != _sym_.end()) << endl;
    cout << "\t\\r = " << std::boolalpha
         << (_sym_.find('\r') != _sym_.end()) << endl;
    cout << "\tH = " << std::boolalpha
         << (_sym_.find('H') != _sym_.end()) << endl;

    symbol = "\\S"; cout << symbol << endl;
    _sym_ = NFA::RESOLVE_SYMBOL(symbol);
    cout << "\t\\n = " << std::boolalpha
         << (_sym_.find('\n') != _sym_.end()) << endl;
    cout << "\t\\r = " << std::boolalpha
         << (_sym_.find('\r') != _sym_.end()) << endl;
    cout << "\tH = " << std::boolalpha
         << (_sym_.find('H') != _sym_.end()) << endl;

    return true;
}

bool UNIT_TEST::NFA_SHUNTING_YARD(){

//    for (auto s : NFA::SHUNTING_YARD("a.b*|c")){
//        cout << s << endl
//    }

//    cout << "\"a.b*|c\"  ->  \"ab*.c|\" --- result: " << NFA::SHUNTING_YARD_STRING("a.b*|c") << endl;
    cout << "\"(A|a).b*|(c|d)\"  ->  \"ab*.c|\" --- result: " << NFA::SHUNTING_YARD_STRING("(A|a).b*|(c|d)") << endl;
    cout << "\"[A-Z].\\w+\"  ->  \"[A-Z]\\w+.\" --- result: " << NFA::SHUNTING_YARD_STRING("[A-Z].\\w+") << endl;
    cout << "\"[^0-9].\\w+\"  ->  \"[^0-9]\\w+.\" --- result: " << NFA::SHUNTING_YARD_STRING("[^0-9].\\w+") << endl;
    return true;
}

bool UNIT_TEST::NFA_FROM_REGEX(){
    string src;
    string rgx;
//    string rgx = "(A|a).b*|(c|d)";
//    rgx = "r.a.f.a.e.l";
//    rgx = "a.b+";
//    rgx = "(a.a|b.b).a*";
    rgx = "[A-Z].\\w+";


    cout << "Regex: " << rgx;
    string rgx_postfix = NFA::SHUNTING_YARD_STRING(rgx);
    cout << "\t PostFix: " << rgx_postfix << endl;
    NFA nfa = NFA::FROM_REGEX(rgx);
    cout << "\nNFA" << endl;
    nfa.display();
    cout << "\nDFA" << endl;
    DFA dfa = DFA::FROM_NFA(nfa);
    dfa.display();
    dfa.generateRecognitionMatix();

//    cout << "\nNEXT STATES FOLLOWING MATIX" << endl;
//    cout << "0[A] -> " << dfa.getTable().getNextState(0, 'A') << endl;
//    cout << "0[B] -> " << dfa.getTable().getNextState(0, 'B') << endl;
//    cout << "0[a] -> " << dfa.getTable().getNextState(0, 'a') << endl;
//    cout << "1[a] -> " << dfa.getTable().getNextState(1, 'a') << endl;
//    cout << "1[A] -> " << dfa.getTable().getNextState(1, 'A') << endl;
//    cout << "1[8] -> " << dfa.getTable().getNextState(1, '8') << endl;
//    cout << "1[_] -> " << dfa.getTable().getNextState(1, '_') << endl;
//    cout << "1[;] -> " << dfa.getTable().getNextState(1, ';') << endl;


//    src = "babaaaaaaabbaaabbbaabbbbbbbbaaabababaaa";
//    Matcher::MATCH(src, dfa);
}
