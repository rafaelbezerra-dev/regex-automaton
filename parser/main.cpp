//
//  main.cpp
//  parser
//
//  Created by 向嘉彬 on 5/7/16.
//  Copyright © 2016 Jacob. All rights reserved.
//
#include "inorder_exp.hpp"
#include "shungting_yard.hpp"
#include <iostream>

int main(int argc, const char * argv[]) {
    inorder_exp i;
    i.first_inorder();
    i.second_inorder();
    i.show();
    Shungting_yard p(i.get_inorder());
    p.in2post();
    p.show();
}
