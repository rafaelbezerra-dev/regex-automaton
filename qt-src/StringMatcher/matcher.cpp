#include "matcher.h"

//Matcher::Matcher(){}

Matcher::Matcher(DFA dfa) : dfa(dfa){}

/*void Matcher::match(string src){
    vector<pair<int, int>> matched_index_vector;
    fa_table table_map = dfa.getTable().getMapping();
    int curr_state_index = 0;
    uint32_t src_size = src.size();

    pair<int, int> matched_index = {-1, -1};

    for(string::size_type i = 0; i < src_size; ++i) {
        string letter;
        letter += src[i];

        if (this->dfa.getState(curr_state_index).isFinal()){
            matched_index.second = i - 1;
            if (table_map[curr_state_index].find(letter) != table_map[curr_state_index].end()){
                int_set::iterator it = table_map[curr_state_index][letter].begin();
                curr_state_index = *it;
                continue;
            }
            else{
                curr_state_index = 0;
            }
        }

//        int next_state_index = 0;
        if (table_map[curr_state_index].find(letter) != table_map[curr_state_index].end()){
            int_set::iterator it = table_map[curr_state_index][letter].begin();
//            next_state_index = *it;

            if (curr_state_index == 0){
                if (matched_index.first != -1 && matched_index.second != -1 )
                    matched_index_vector.push_back(matched_index);
                matched_index = {i, -1};

            }

            curr_state_index = *it;
        }
        else{
            curr_state_index = 0;
            if (table_map[curr_state_index].find(letter) != table_map[curr_state_index].end()){
                int_set::iterator it = table_map[curr_state_index][letter].begin();
                if (curr_state_index == 0){
                    if (matched_index.first != -1 && matched_index.second != -1 )
                        matched_index_vector.push_back(matched_index);
                    matched_index = {i, -1};

                }

                curr_state_index = *it;
            }
        }

//        curr_state_index = next_state_index;
    }

    if (matched_index.first != -1 && matched_index.second != -1 )
        matched_index_vector.push_back(matched_index);

    cout << "\n### MATCHED: ###" << endl;
    for (auto p : matched_index_vector){
        int count = p.second - p.first + 1;
        cout << src.substr(p.first, count)
             << "[" << p.first + 1<< ", " << p.second + 1<< "]"
             << endl;
    }



}*/

vector<pair<int, int>> Matcher::match(string src){
    vector<pair<int, int>> matched_index_vector;
    DFATable table = dfa.getTable();
    fa_table table_map = table.getMapping();
    int curr_state_index = 0;
    uint32_t src_size = src.size();
    pair<int, int> matched_index = {-1, -1};
    int line_count = 0;

    for(string::size_type i = 0; i < src_size; ++i) {
        char c = src[i];
        string letter;
        letter += src[i];

        if (c == '\n')
            line_count++;

        if (this->dfa.getState(curr_state_index).isFinal()){
            matched_index.second = i - 1;
            curr_state_index = table.getNextState(curr_state_index, c);
            if (curr_state_index != 0)
                continue;

        }

        int next_state_index = table.getNextState(curr_state_index, c);
        if (curr_state_index == 0){
            if (matched_index.first != -1 && matched_index.second != -1 )
                matched_index_vector.push_back(matched_index);
            matched_index = {i, -1};

        }

        if (next_state_index == 0){
            if (matched_index.first != -1 && matched_index.second != -1 )
                matched_index_vector.push_back(matched_index);
            matched_index = {i, -1};
            next_state_index = table.getNextState(next_state_index, c);
        }


        curr_state_index = next_state_index;
    }

    if (matched_index.first != -1 && matched_index.second != -1 )
        matched_index_vector.push_back(matched_index);

//    cout << "\n### MATCHED: ###" << endl;
//    for (auto p : matched_index_vector){
//        int count = p.second - p.first + 1;
//        cout << src.substr(p.first, count)
//             << "[" << p.first + 1<< ", " << p.second + 1<< "]"
//             << endl;
//    }
      return matched_index_vector;
}

void Matcher::MATCH_FILE(string file, DFA dfa, bool print_nicely){
    string src = "";
    float start, end;
    ifstream input(file);
    for( string line; getline( input, line ); )
    {
        src += line + "\n";
    }

    start = Utils::GET_TIME();
    Matcher m = Matcher(dfa);
    vector<pair<int, int>> res = m.match(src);
    end = Utils::GET_TIME();
    if (print_nicely){
        PRINT_NICELY(src, res);
        cout << "\n------------------------------------------------\n"
             << "Time to match against file: "
             << (end - start)
             << " ms."
             << endl << endl;
    }
    else{
        cout << "\n### MATCHED: ###" << endl;
        for (auto p : res){
            int count = p.second - p.first + 1;
            cout << src.substr(p.first, count)
                 << "[" << p.first + 1<< ", " << p.second + 1<< "]"
                 << endl;
        }
    }
}

vector<pair<int, int>> Matcher::MATCH_STRING(string src, DFA dfa){
    Matcher m = Matcher(dfa);
    return m.match(src);
}

void Matcher::PRINT_NICELY(string src, vector<pair<int, int>> matched_indexes){
    cout << "\n### MATCHED: ###" << endl;

    int last_index = 0;

    for (auto p : matched_indexes){
        int start = p.first,
            end = p.second;
        cout << src.substr(last_index, start - last_index);

        int count = end - start + 1;
        cout << green
             << src.substr(start, count)
//             << "[" << p.first + 1<< ", " << p.second + 1<< "]"
             << white;
//             << endl;
        last_index = end + 1;
    }

    cout << src.substr(last_index, src.size() - last_index);

    cout << endl;
}
