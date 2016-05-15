#include "utils.h"

Utils::Utils(){}

string Utils::TO_STRING(vector<int> v){
    string str_to = "";
    for (auto i: v)
      str_to += to_string(i) + ' ';
    return str_to;
}

string Utils::TO_STRING(int_set s){
    string str_to = "";
    for (auto i: s)
      str_to += to_string(i) + ' ';
    return str_to;
}


float Utils::GET_TIME(){
    clock_t t = clock();
    return ((float)t)/CLOCKS_PER_SEC;
}

