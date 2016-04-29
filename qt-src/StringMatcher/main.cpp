#include <iostream>
#include <unordered_set>
#include <unordered_map>

#include "nfa.h"

using namespace std;

int main(int argc, char *argv[])
{
    cout << "Hello World!" << endl;

    vector<Transition> trans;
    trans.push_back(Transition(0, 1, "a"));
    trans.push_back(Transition(0, 1, "b"));
    for (vector<Transition>::iterator it = trans.begin();
         it != trans.end();++it){
        cout << it->symbol << endl;
    }

    cout << Symbol::EPSILON << endl;

    return 0;
}
