//
//  regex_library.hpp
//  parser
//
//  Created by 向嘉彬 on 5/7/16.
//  Copyright © 2016 Jacob. All rights reserved.
//

#ifndef regex_library_hpp
#define regex_library_hpp

#include <iostream>
#include <set>
#include <map>
#include <string>
using namespace std;





//quantifier: (1){n} (2){n,} (3){n,m}

//operator: (1)+ (2)* (3)?   (4)| (5).

//set[]:
// .[^\n]
// \w[a-zA-Z0-9_]
// \W
// \d[0-9]
// \D
// \s[\f\n\r\t\v\u00A0\u2028\u2029] (spaces,tabs,linbreaks)
// \S

//group()

//escaped char:
// \t htab(char code 9)
// \n line feed(char code 10)
// \v vtab(char code 11)
// \f from feed(char code 12)
// \r carriage return(char code 13)
// \0 null(char code 0)

// \cX control-X
// \xhh hexadecimal
// \uhhhh unicode

// \(.46) (\92) (+43) (*42) (?63) (^94) ($36) ([91) (]93) ({123) (}125) [(40] [)41] (|124) (/47)


//Anchor:
// ^
// $
// \b match a position not a character(between a word and a space)
// \B
//back reference
// \positive int




class regex_library {
private:
    set<char> oper; // all operators will be saved in this set.
    set<char> escape; // all escaped charaters will be saved in this set
    set<char> sets;
    map<string,string> sets_map;// all sets will be saved in this set
public:
    regex_library();
    string::iterator is_operator(string::iterator it);
    string::iterator is_set(string::iterator it);
    string::iterator is_group(string::iterator it);
    string::iterator is_escape(string::iterator it);
    string::iterator is_anchor(string::iterator it);
    string::iterator is_quantifier(string::iterator it);
};

#endif /* regex_library_hpp */
