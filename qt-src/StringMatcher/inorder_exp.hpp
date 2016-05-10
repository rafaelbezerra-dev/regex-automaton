//
//  inorder_exp.hpp
//  parser
//
//  Created by 向嘉彬 on 5/7/16.
//  Copyright © 2016 Jacob. All rights reserved.
//

#ifndef inorder_exp_hpp
#define inorder_exp_hpp

#include "regex_library.hpp"

#include <iostream>
#include <vector>
using namespace std;

class inorder_exp {
private:
    regex_library library;
    string reg_exp;
    vector<string> in_order;
    string::iterator itr;
    vector<long> parenth_stack;
public:
    inorder_exp();
    inorder_exp(string reg_exp);
//    void input();
    string::iterator split(string::iterator it);
    void push(string::iterator it_l, string::iterator it_r);
    
    void first_inorder();
    void second_inorder();
    
    void set_expand(string::iterator it_l, string::iterator it_r);
    void quantifier_expand(string::iterator it_l, string::iterator it_r);
    void show();
    vector<string> get_inorder() const;
};

#endif /* inorder_exp_hpp */
