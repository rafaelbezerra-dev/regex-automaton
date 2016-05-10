#include "unittest.h"

void UNIT_TEST::RUN_ALL(){

    cout << "*****************************" << endl
         << "*    STARTING UNIT TESTS    *"   << endl
         << "*****************************" << endl;

//    cout << "\n\nTEST: CONSTRUCTIONS... " << endl;
//    UNIT_TEST::CONSTRUCTIONS();

//    cout << "\n\nTEST: NFA_RESOLVE_SYMBOL... " << endl;
//    UNIT_TEST::NFA_RESOLVE_SYMBOL();

//    cout << "\n\nTEST: NFA_SHUNTING_YARD... " << endl;
//    UNIT_TEST::NFA_SHUNTING_YARD();

//    cout << "\n\nTEST: NFA_FROM_REGEX... " << endl;
//    UNIT_TEST::NFA_FROM_REGEX();

//    cout << "\n\nTEST: NFA_FROM_REGEX2... " << endl;
//    UNIT_TEST::MATCHER_MATCH_FILE();

    cout << "\n\nTEST: BENCHMARK_SMALL... " << endl;
    UNIT_TEST::BENCHMARK_SMALL();

    cout << "\n\nTEST: BENCHMARK_BIG... " << endl;
    UNIT_TEST::BENCHMARK_BIG();

//    cout << "\n\nTEST: NEW_PARSER_MATCH_STRING... " << endl;
//    UNIT_TEST::NEW_PARSER_MATCH_STRING();

//    cout << "\n\nTEST: NEW_PARSER_MATCH_FILE... " << endl;
//    UNIT_TEST::NEW_PARSER_MATCH_FILE();
}

void UNIT_TEST::CONSTRUCTIONS(){

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
//  getch();

    cout<<"\nFor the regular expression segment [Concatenation] : (a.b)";
    NFA::CONCAT(a, b).display();
//  getch();

    cout<<"\nFor the regular expression segment [Or] : (a|b)";
    NFA::OR(a, b).display();
//  getch();

    cout<<"\nFor the regular expression segment [zero or one] : (a?)";
    NFA::ZERO_OR_ONE(a).display();
//  getch();

    cout<<"\nFor the regular expression segment [zero or more] : (a*)";
    NFA::ZERO_OR_MORE(a).display();
//  getch();

    cout<<"\nFor the regular expression segment [one or more] : (a+)";
    NFA::ONE_OR_MORE(a).display();
//  getch();

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
}

void UNIT_TEST::NFA_RESOLVE_SYMBOL(){

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

//    return true;
}

void UNIT_TEST::NFA_SHUNTING_YARD(){

//    for (auto s : NFA::SHUNTING_YARD("a.b*|c")){
//        cout << s << endl
//    }

//    cout << "\"a.b*|c\"  ->  \"ab*.c|\" --- result: " << NFA::SHUNTING_YARD_STRING("a.b*|c") << endl;
    cout << "\"(A|a).b*|(c|d)\"  ->  \"ab*.c|\" --- result: " << NFA::SHUNTING_YARD_STRING("(A|a).b*|(c|d)") << endl;
    cout << "\"[A-Z].\\w+\"  ->  \"[A-Z]\\w+.\" --- result: " << NFA::SHUNTING_YARD_STRING("[A-Z].\\w+") << endl;
    cout << "\"[^0-9].\\w+\"  ->  \"[^0-9]\\w+.\" --- result: " << NFA::SHUNTING_YARD_STRING("[^0-9].\\w+") << endl;
//    return true;
}

void UNIT_TEST::NFA_FROM_REGEX(){
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


    src = "babaaaaaaabbaaabbbaabbbbbbbbaaabababaaa";
    vector<pair<int, int>> res = Matcher::MATCH_STRING(src, dfa);
    Matcher::PRINT_NICELY(src, res);
//    return true;
}

void UNIT_TEST::MATCHER_MATCH_FILE(){
    string file = "C:\\Projects\\Git\\stevens\\regexp-project\\qt-src\\StringMatcher\\Latin-Lipsum.txt";
    string rgx = "[A-Z].\\w+";

    cout << "File: " << file;
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
    Matcher::MATCH_FILE(file, dfa, true);
//    return true;
}

void UNIT_TEST::BENCHMARK_SMALL(){
    string src = "";
    string file = "C:\\Projects\\Git\\stevens\\regexp-project\\lorem_small.txt";
    ifstream input(file);
    for( string line; getline( input, line ); )
    {
        src += line + "\n";
    }
    float start, end;

    cout << "DEFAULT C++ REGEX LIBRARY" << endl;
    start = Utils::GET_TIME();

    regex self_regex("REGULAR EXPRESSIONS", regex_constants::ECMAScript | regex_constants::icase);

    regex word_regex("([A-Z]\\w+)");
    auto words_begin =
        sregex_iterator(src.begin(), src.end(), word_regex);
    auto words_end = sregex_iterator();

    end = Utils::GET_TIME();

    cout << "Found "
         << distance(words_begin, words_end)
         << " words in "
         << (end - start)
         << " ms"
         << endl;

    cout << "OUR C++ REGEX LIBRARY" << endl;
    start = Utils::GET_TIME();

//    NFA nfa = NFA::FROM_REGEX("[A-Z].\\w+");
    NFA nfa = NFA::FROM_REGEX_USING_PARSER("[A-Z]\\w+");
    DFA dfa = DFA::FROM_NFA(nfa);
    dfa.generateRecognitionMatix();
    vector<pair<int, int>> res = Matcher::MATCH_STRING(src, dfa);

    end = Utils::GET_TIME();

    cout << "Found "
         << res.size()
         << " words in "
         << (end - start)
         << " ms"
         << endl;
}


void UNIT_TEST::BENCHMARK_BIG(){
    string src = "";
    string file = "C:\\Projects\\Git\\stevens\\regexp-project\\lorem_big.txt";
    ifstream input(file);
    for( string line; getline( input, line ); )
    {
        src += line + "\n";
    }
    float start, end;

    cout << "DEFAULT C++ REGEX LIBRARY" << endl;
    start = Utils::GET_TIME();

    regex self_regex("REGULAR EXPRESSIONS", regex_constants::ECMAScript | regex_constants::icase);

    regex word_regex("([A-Z]\\w+)");
    auto words_begin =
        sregex_iterator(src.begin(), src.end(), word_regex);
    auto words_end = sregex_iterator();

    end = Utils::GET_TIME();

    cout << "Found "
         << distance(words_begin, words_end)
         << " words in "
         << (end - start)
         << " ms"
         << endl;

    cout << "OUR C++ REGEX LIBRARY" << endl;
    start = Utils::GET_TIME();

//    NFA nfa = NFA::FROM_REGEX("[A-Z].\\w+");
    NFA nfa = NFA::FROM_REGEX_USING_PARSER("[A-Z]\\w+");
    DFA dfa = DFA::FROM_NFA(nfa);
    dfa.generateRecognitionMatix();
    vector<pair<int, int>> res = Matcher::MATCH_STRING(src, dfa);

    end = Utils::GET_TIME();

    cout << "Found "
         << res.size()
         << " words in "
         << (end - start)
         << " ms"
         << endl;
}

void UNIT_TEST::NEW_PARSER_MATCH_STRING(){
    string src;
    string rgx;
    rgx = "((aa)|(bb))a*";
//    rgx = "[A-Z]\\w+";


    cout << "Regex: " << rgx << endl;
//    string rgx_postfix = NFA::SHUNTING_YARD_STRING(rgx);
//    cout << "\t PostFix: " << rgx_postfix << endl;
    NFA nfa = NFA::FROM_REGEX_USING_PARSER(rgx);
    cout << "\nNFA" << endl;
    nfa.display();
    cout << "\nDFA" << endl;
    DFA dfa = DFA::FROM_NFA(nfa);
    dfa.display();
    dfa.generateRecognitionMatix();

    src = "babaaaaaaabbaaabbbaabbbbbbbbaaabababaaa";
    vector<pair<int, int>> res = Matcher::MATCH_STRING(src, dfa);
    Matcher::PRINT_NICELY(src, res);
    cout << "\n### MATCHED: ###" << endl;
    for (auto p : res){
        int count = p.second - p.first + 1;
        cout << src.substr(p.first, count)
             << "[" << p.first + 1<< ", " << p.second + 1<< "]"
             << endl;
    }
}

void UNIT_TEST::NEW_PARSER_MATCH_FILE(){
    string file = "C:\\Projects\\Git\\stevens\\regexp-project\\lorem_small.txt";
    string rgx = "[A-Z]\\w+";

    cout << "File: " << file;
    cout << "Regex: " << rgx;

//    string rgx_postfix = NFA::SHUNTING_YARD_STRING(rgx);
//    cout << "\t PostFix: " << rgx_postfix << endl;
    NFA nfa = NFA::FROM_REGEX_USING_PARSER(rgx);
//    cout << "\nNFA" << endl;
//    nfa.display();
    cout << "\nDFA" << endl;
    DFA dfa = DFA::FROM_NFA(nfa);
//    dfa.display();
    dfa.generateRecognitionMatix();
    Matcher::MATCH_FILE(file, dfa, true);
}
