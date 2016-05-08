#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>
using namespace std;

char op[4] = {'+','*','?','|'};
char es[24] = {'t','n','v','f','r','0','c','x','u','.','\\','+','*','?','^','$','[',']','{','}','[',']','|','/'};
char se[6] = {'w','W','d','D','s','S'};


class Regex_Patterns {
private:
    //quantifier: (1){n} (2){n,} (3){n,m}
    
    //operator: (1)+ (2)* (3)?   (4)| (5).
    set<char> oper; // all operators will be saved in this set.
    
    //set[]:
        // .[^\n]
        // \w[a-zA-Z0-9_]
        // \W
        // \d[0-9]
        // \D
        // \s[\f\n\r\t\v\u00A0\u2028\u2029] (spaces,tabs,linbreaks)
        // \S
    set<char> sets; // all sets will be saved in this set
    map<string,string> sets_map;
    
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
    set<char> escape; // all escaped charaters will be saved in this set
    
    
    //Anchor:
        // ^
        // $
        // \b match a position not a character(between a word and a space)
        // \B
    //back reference
        // \positive int
    string reg_exp; // input value will be saved in this string
    vector<string> inorder; // this is the in-order output
    
public:
    string::iterator it_l,it_r;
    Regex_Patterns(string s) : reg_exp(s){
        it_l = reg_exp.begin();
        it_r = it_l;
        
        sets_map["."]="[^\n]";
        sets_map["\\w"]="[a-zA-Z0-9_]";
        sets_map["\\W"]="[^a-zA-Z0-9_]";
        sets_map["\\d"]="[0-9]";
        sets_map["\\D"]="[^0-9]";
        sets_map["\\s"]="[\f\n\r\t\v\u00A0\u2028\u2029]";
        sets_map["\\S"]="[^\f\n\r\t\v\u00A0\u2028\u2029]";
        
    }
    
    bool isOperator() {
        if (oper.find(*it_l) != oper.end()) {
            it_r++;
            return true;
        }
        return false;
    }
    
    bool isSet() {
        if (*it_l == '.'){
            it_r++;
            return true;
        }
        if (*it_l == '\\' && sets.find(*(it_l+1)) != sets.end()) {
            it_r += 2;
            return true;
        }
        if (*it_l == '[') {
            while (*(it_r++) != ']');
            //cout << it_r - it_l << endl;
            return true;
        }
        return false;
    }
    bool isGroup() {
        if (*it_l == '(') {
            while (*(it_r++) != ')');
            //cout << it_r - it_l << endl;
            return true;
        }
        return false;

    }
    bool isEscape() {
        if (*it_l == '\\' && escape.find(*(it_l+1)) != escape.end()) {
            it_r += 2;
            return true;
        }
        return false;
    }
    bool isAnchor() {
        if (*it_l == '^' || *it_l == '$') {
            it_r++;
            return true;
        }
        if (*it_l == '\\' && (*(it_l+1) == 'b' || *(it_l+1) == 'B')) {
            it_r += 2;
            return true;
        }
        return false;
    }
    
    bool isQuantifier() {
        if (*it_l == '{') {
            while (*(it_r++) != ')');
            return true;
        }
        return false;
    }
    /*
    void quantifier_translation() {
        
    }
    
    void split() {
    
    }
    */

    void split() {
        while (it_r != reg_exp.end()) {
            if (isGroup()||isEscape()||isAnchor()) {
                isQuantifier();
                inorder.push_back(reg_exp.substr( it_l-reg_exp.begin(), it_r-it_l ));
                it_l = it_r;
            } else if(isSet()) {
                if (*it_l == '[') {
                    isQuantifier();
                    inorder.push_back(reg_exp.substr( it_l-reg_exp.begin(), it_r-it_l ));
                    it_l = it_r;
                } else {
                    string temp_set = sets_map.find( reg_exp.substr(it_l-reg_exp.begin(), it_r-it_l) )->second;
                    it_l = it_r;
                    isQuantifier();
                    inorder.push_back(temp_set + reg_exp.substr( it_l-reg_exp.begin(), it_r-it_l ));
                    it_l = it_r;
                }
            } else {
                it_r++;
                inorder.push_back(reg_exp.substr( it_l-reg_exp.begin(), it_r-it_l ));
                it_l = it_r;
            }
        }
    }

    
    void show() {
        for (vector<string>::iterator it = inorder.begin(); it != inorder.end(); ++it)
            cout << *it << " ";
        cout << endl;
    }
    
};

int main() {
    string test;
    cout << "please input regex:" << endl;
    cin >> test;
    Regex_Patterns r(test);
    r.split();
    r.show();
}





/*
class Parser{
private:
    string reg_exp;
    vector<string> post_exp;
public:
    Parser(string& input_string) : reg_exp(input_string) {}
    vector<string> transfer() {
        string::iterator it;
        string::iterator it2;
        char c;
        for (it=reg_exp.begin(); it!=reg_exp.end(); ++it) {
           if (*it == '\\')
               
        }
    }
};
*/