//
//  regex_library.cpp
//  parser
//
//  Created by 向嘉彬 on 5/7/16.
//  Copyright © 2016 Jacob. All rights reserved.
//

#include "regex_library.hpp"

regex_library::regex_library() {
    char op[4] = {'+','*','?','|'};
    char es[24] = {'t','n','v','f','r','0','c','x','u','.','\\','+','*','?','^','$','[',']','{','}','[',']','|','/'};
    char se[6] = {'w','W','d','D','s','S'};
    oper = set<char>(op, op+4);
    escape = set<char>(es,es+24);
    sets = set<char>(se, se+6);
    sets_map["."]="[^\n]";
    sets_map["\\w"]="[a-zA-Z0-9_]";
    sets_map["\\W"]="[^a-zA-Z0-9_]";
    sets_map["\\d"]="[0-9]";
    sets_map["\\D"]="[^0-9]";
    sets_map["\\s"]="[\f\n\r\t\v\u00A0\u2028\u2029]";
    sets_map["\\S"]="[^\f\n\r\t\v\u00A0\u2028\u2029]";
}

string::iterator regex_library::is_operator(string::iterator it){
    if (oper.find(*it) != oper.end()) {
        return ++it;
    }
    return it;
};
string::iterator regex_library::is_set(string::iterator it) {
    if (*it == '.') {
        it++;
    }
    if (*it == '\\' && sets.find(*(it+1)) != sets.end()) {
        it += 2;
    }
    if (*it == '[') {
        while (*(it++) != ']');
    }
    return it;
}

string::iterator regex_library::is_group(string::iterator it) {
    if (*it == '(') {
        while (*(it++) != ')');
    }
    return it;
}
string::iterator regex_library::is_escape(string::iterator it) {
    if (*it == '\\' && escape.find(*(it+1)) != escape.end()) {
        it += 2;
    }
    return it;
}
string::iterator regex_library::is_anchor(string::iterator it) {
    if (*it == '^' || *it == '$') {
        it++;
    }
    if (*it == '\\' && (*(it+1) == 'b' || *(it+1) == 'B')) {
        it += 2;
    }
    return it;
}
string::iterator regex_library::is_quantifier(string::iterator it) {
    if (*it == '{') {
        while (*(it++) != ')');
    }
    return it;

}