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

int main(int argc, char **argv)
{
    UNIT_TEST::RUN_ALL();
    return 0;


    string file = "",
            regx = "";

    string last_arg = "";
    for (int i = 0; i < argc; ++i)
    {
//        cout << "argv[" << i << "]: " <<  << endl;
        if (last_arg == "-r" || last_arg == "--regex" || last_arg == "--regexp"){
            regx = argv[i];
        }
        else if (last_arg == "-f" || last_arg == "--file" || last_arg == "--input"){
            file = argv[i];
        }
        last_arg = argv[i];
    }

    if (file.size() == 0 || regx.size() == 0){
        cout << endl << red
             << "INCORRECT CALL!!!"
             << white << endl;
        return 1;
    }


//    file = "C:\\Projects\\Git\\stevens\\regexp-project\\qt-src\\StringMatcher\\Latin-Lipsum.txt";
//    regx = "[A-Z].\\w+";

    cout << "File: "    << green << file << white << endl;
    string rgx_postfix = NFA::SHUNTING_YARD_STRING(regx);
    cout << "Regex: "   << green << regx << white
         << "\t PostFix: " << rgx_postfix << endl;

    cout << "\nPRESS ENTER TO CONTINUE...";
    cin.ignore();
    cout << endl;

    NFA nfa = NFA::FROM_REGEX(regx);
//    cout << "\nNFA" << endl;
//    nfa.display();
//    cout << "\nDFA" << endl;
    DFA dfa = DFA::FROM_NFA(nfa);
//    dfa.display();
    dfa.generateRecognitionMatix();
    Matcher::MATCH_FILE(file, dfa, true);

    return 0;
}
