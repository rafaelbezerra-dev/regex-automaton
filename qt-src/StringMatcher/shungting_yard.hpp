//
//  shungting_yard.hpp
//  parser
//
//  Created by 向嘉彬 on 5/9/16.
//  Copyright © 2016 Jacob. All rights reserved.
//

#ifndef shungting_yard_hpp
#define shungting_yard_hpp

#include <iostream>
#include <vector>
#include <map>
using namespace std;

class Shungting_yard {
private:
    vector<string> inorder_input;
    vector<string> postorder_output;
    map<string, int> precedence;
    vector<string> stack;
public:
    Shungting_yard(vector<string> v);
    vector<string> in2post();
    void show();
};

#endif /* shungting_yard_hpp */
