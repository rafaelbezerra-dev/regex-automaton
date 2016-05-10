//
//  inorder_exp.cpp
//  parser
//
//  Created by 向嘉彬 on 5/7/16.
//  Copyright © 2016 Jacob. All rights reserved.
//

#include "inorder_exp.hpp"


inorder_exp::inorder_exp() {
    library = regex_library();
//    input();
    itr = reg_exp.begin();
}

inorder_exp::inorder_exp(string reg_exp)
    : reg_exp(reg_exp){
    library = regex_library();
    itr = this->reg_exp.begin();
}

//void inorder_exp::input() {
//    cout << "please input regex:" << endl;
//    cin >> reg_exp;
//}

void inorder_exp::first_inorder() {
    string::iterator temp_itr;
    while (itr != reg_exp.end()) {
        temp_itr = split(itr);
        if (temp_itr == itr) {
            push(itr, itr+1);
            if (*itr == '(') {
                parenth_stack.push_back(in_order.end()-in_order.begin()-1);
            }
            if (*(itr-1) == ')') {
                parenth_stack.pop_back();
            }
            temp_itr++;
        }
        itr = temp_itr;
    }
}

void inorder_exp::second_inorder() {
//    vector<string>::iterator it_t=in_order.begin();
//    while(it_t!=in_order.end()-1)
//    {
//                if (*it_t != "(" &&
//                    *it_t != "|" &&
//                    *it_t != "." &&
//                    *(it_t+1) != ")" &&
//                    *(it_t+1) != "|" &&
//                    *(it_t+1) != "." &&
//                    *(it_t+1) != "+" &&
//                    *(it_t+1) != "?" &&
//                    *(it_t+1) != "*" )
//                {
//                    in_order.insert(it_t+1, ".");
//                    it_t=in_order.begin();
//                }
//                else ++it_t;
//        
//    }
    vector<string> temp;
    for (vector<string>::iterator it_t = in_order.begin(); it_t != in_order.end()-1; ++it_t) {
        temp.push_back(*it_t);
        if (*it_t != "(" &&
            *it_t != "|" &&
            *it_t != "." &&
            *(it_t+1) != ")" &&
            *(it_t+1) != "|" &&
            *(it_t+1) != "." &&
            *(it_t+1) != "+" &&
            *(it_t+1) != "?" &&
            *(it_t+1) != "*" ) {
            temp.push_back(".");
        }
    }
    temp.push_back(in_order.back());
    in_order = temp;
}


string::iterator inorder_exp::split(string::iterator it) {
    string::iterator temp_it;
    temp_it = library.is_anchor(it);
    if (temp_it != it) {
        push(it,temp_it);
        return temp_it;
    }
    temp_it = library.is_escape(it);
    if (temp_it != it) {
        push(it,temp_it);
        return temp_it;
    }
    temp_it = library.is_set(it);
    if (temp_it != it) {
        set_expand(it, temp_it);
        return temp_it;
    }
    temp_it = library.is_quantifier(it);
    if (temp_it != it) {
        quantifier_expand(it, temp_it);
        return temp_it;
    }
    
    return temp_it;
}



void inorder_exp::push(string::iterator it_l, string::iterator it_r) {

    in_order.push_back(reg_exp.substr(it_l-reg_exp.begin(),it_r-it_l));
}

void inorder_exp::set_expand(string::iterator it_l, string::iterator it_r) {
    if (*it_l == '[') {
        push(it_l, it_r);
    }
    else {
        in_order.push_back(
             library.get_sets().find( reg_exp.substr(it_l-reg_exp.begin(), it_r-it_l) )->second
                           );
    }
}
void inorder_exp::quantifier_expand(string::iterator it_l, string::iterator it_r) {
    int m=0,n=0;
    unsigned long comma,brace;
    string s = reg_exp.substr(it_l-reg_exp.begin(),it_r-it_l);
    comma = s.find(',');
    brace = s.find('}');
    if (comma == -1) {
        m = stoi(s.substr(1,brace-1), nullptr, 10);
        if (*(it_l-1) != ')') {
            in_order.insert(in_order.end()-1,"(");
            for (int i=1; i<m; i++)
                in_order.push_back(in_order.back());
            in_order.push_back(")");
        } else {
            long end = in_order.end()-in_order.begin();
            for (int i=1; i<m; i++) {
                for (long i = parenth_stack.back(); i< end; i++) {
                    in_order.push_back(in_order[i]);
                }
            }
            in_order.insert(in_order.begin()+parenth_stack.back(),"(");
            in_order.insert(in_order.end(),")");
        }
        
    } else if (comma == brace-1) {
        m = stoi(s.substr(1,comma-1), nullptr, 10);
        n = -1;
        if (*(it_l-1) != ')') {
            in_order.insert(in_order.end()-1,"(");
            for (int i=0; i<m; i++)
                in_order.push_back(in_order.back());
            in_order.push_back("*");
            in_order.push_back(")");
        } else {
            long end = in_order.end()-in_order.begin();
            for (int i=0; i<m; i++) {
                for (long i = parenth_stack.back(); i< end; i++) {
                    in_order.push_back(in_order[i]);
                }
            }
            in_order.push_back("*");
            in_order.insert(in_order.begin()+parenth_stack.back(),"(");
            in_order.insert(in_order.end(),")");
        }

    } else {
        m = stoi(s.substr(1,comma-1), nullptr, 10);
        n = stoi(s.substr(comma+1,brace-comma-1), nullptr, 10);
        if (*(it_l-1) != ')') {
            in_order.insert(in_order.end()-1,"(");
            string temp = in_order.back();
            for (int i=1; i<m; i++)
                in_order.push_back(temp);
            for (int i=m; i<n; i++) {
                in_order.push_back(temp);
                in_order.push_back("?");
            }
            in_order.push_back(")");
        } else {
            long end = in_order.end()-in_order.begin();
            for (int i=1; i<m; i++) {
                for (long i = parenth_stack.back(); i< end; i++) {
                    in_order.push_back(in_order[i]);
                }
            }
            for (int i=m; i<n; i++) {
                for (long i = parenth_stack.back(); i< end; i++) {
                    in_order.push_back(in_order[i]);
                }
                in_order.push_back("?");
            }
            in_order.insert(in_order.begin()+parenth_stack.back(),"(");
            in_order.insert(in_order.end(),")");
        }
    }
    
    
}
void inorder_exp::show() {
    for (vector<string>::iterator it = in_order.begin(); it != in_order.end(); ++it)
        cout << *it << " ";
    cout << endl;
}
vector<string> inorder_exp::get_inorder() const {
    return in_order;
}
