//
// Created by alon on 12/16/18.
//
#include "lexer.h"
#include <sstream>
#include <iostream>
using namespace std;
vector<string> Lexer::lex(string str){
    istringstream iss(str);
    vector<string> strings;
    string temp;
    while(getline(iss, temp, ' ')) {
        strings.push_back(temp);
    }
    return strings;
}
