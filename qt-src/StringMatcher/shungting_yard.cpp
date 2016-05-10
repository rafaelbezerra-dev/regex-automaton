//
//  shungting_yard.cpp
//  parser
//
//  Created by 向嘉彬 on 5/9/16.
//  Copyright © 2016 Jacob. All rights reserved.
//

#include "shungting_yard.hpp"
Shungting_yard::Shungting_yard(vector<string> v) : inorder_input(v){
    precedence["("] = 4;
    precedence[")"] = 4;
    precedence["+"] = 3;
    precedence["*"] = 3;
    precedence["?"] = 3;
    precedence["|"] = 2;
    precedence["."] = 1;
}
vector<string> Shungting_yard::in2post(){
    for(vector<string>::iterator it=inorder_input.begin(); it!=inorder_input.end(); ++it) {
        if (precedence.find(*it) == precedence.end()) { //is operand
            postorder_output.push_back(*it);
        } else { //is operator
            if (*it == ")") {
                while (stack.back()!="(") {
                    postorder_output.push_back(stack.back());
                    stack.pop_back();
                }
                stack.pop_back();
            } else {
                while(!stack.empty() && stack.back() != "(" && precedence.find(*it)->second <= precedence.find(stack.back())->second) {
                    postorder_output.push_back(stack.back());
                    stack.pop_back();
                }
                stack.push_back(*it);
            }
        }
    }
    while (!stack.empty()) {
        postorder_output.push_back(stack.back());
        stack.pop_back();
    }
    
    return postorder_output;
}

void Shungting_yard::show(){
    for(vector<string>::iterator it=postorder_output.begin(); it!=postorder_output.end(); ++it) 
        cout << *it << " ";
    cout << endl;
};
