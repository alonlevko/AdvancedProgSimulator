#include "lexer.h"
#include <sstream>
#include <iostream>
#include <algorithm>
using namespace std;
// split the string into a strings vector seperated by whitespace
vector<string> Lexer::lex(string str){
    str.erase(remove(str.begin(), str.end(), '\t'), str.end());
    istringstream iss(str);
    vector<string> strings;
    string temp;
    while(getline(iss, temp, ' ')) {
        strings.push_back(temp);
    }
    return strings;
}
