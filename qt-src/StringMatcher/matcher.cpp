#include "matcher.h"

//Matcher::Matcher(){}

Matcher::Matcher(DFA dfa) : dfa(dfa){}

void Matcher::match(string src){
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



}

void Matcher::MATCH(string src, DFA dfa){
    Matcher m = Matcher(dfa);
    m.match(src);
}

