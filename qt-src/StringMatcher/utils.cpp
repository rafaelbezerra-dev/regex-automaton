#include "utils.h"

Utils::Utils(){}

string Utils::TO_STRING(vector<int> v){
    string str_to = "";
    for (auto i: v)
      str_to += to_string(i) + ' ';
    return str_to;
}

string Utils::TO_STRING(unordered_set<int> s){
    string str_to = "";
    for (auto i: s)
      str_to += to_string(i) + ' ';
    return str_to;
}

