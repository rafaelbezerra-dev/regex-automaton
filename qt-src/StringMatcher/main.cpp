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
    string arg = "",
            file = "",
            regx = "";
    bool run_unittest = false;
    float start, end;

    string last_arg = "";
    for (int i = 0; i < argc; ++i)
    {
        arg = argv[i];
//        cout << "argv[" << i << "]: " <<  << endl;
        if (last_arg == "-r" || last_arg == "--regex" || last_arg == "--regexp"){
            regx = arg;
        }
        else if (last_arg == "-f" || last_arg == "--file" || last_arg == "--input"){
            file = arg;
        }

        if (arg == "-t" || arg == "--tests"){
            run_unittest = true;
        }

        last_arg = arg;
    }

    if (run_unittest){
        UNIT_TEST::RUN_ALL();
        return 0;
    }


    if (file.size() == 0 || regx.size() == 0){
        cout << endl << red
             << "INCORRECT CALL!!!"
             << white << endl;
        return 1;
    }

    cout << "File: "    << green << file << white << endl;
//    string rgx_postfix = NFA::SHUNTING_YARD_STRING(regx);
    cout << "Regex: "   << green << regx << white << endl;
//         << "\t PostFix: " << rgx_postfix << endl;

    start = Utils::GET_TIME();
    NFA nfa = NFA::FROM_REGEX_USING_PARSER(regx);
//    cout << "\nNFA" << endl;
//    nfa.display();
//    cout << "\nDFA" << endl;
    DFA dfa = DFA::FROM_NFA(nfa);
//    dfa.display();
    dfa.generateRecognitionMatix();
    end = Utils::GET_TIME();

    cout << "\nThe parsing took " << (end - start) << " ms to run."
         << "\nPRESS ENTER TO CONTINUE...";
    cin.ignore();
    cout << endl;

    Matcher::MATCH_FILE(file, dfa, true);

    return 0;
}
