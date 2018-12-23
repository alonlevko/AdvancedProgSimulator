//
// Created by alon on 12/21/18.
//

#include "utils.h"
vector<string> makeForParse(vector<string> vec) {
    vector<string> temp;
    for(vector<string>::iterator it = vec.begin(); it != vec.end(); it++) {
        string str = *it;
        string until;
        if(str == "") {
            continue;
        }
        if(str.size() == 1) {
            temp.push_back(str);
            continue;
        }
        for(string::iterator itr = str.begin(); itr != str.end(); itr++) {
            if (isOperator(*itr)) {
                if(until.size() > 0) {
                    temp.push_back(until);
                    until.clear();
                }
                string x;
                x.push_back(*itr);
                temp.push_back(x);
            } else {
                until.push_back(*itr);
            }
        }
        if(until.size() > 0) {
            temp.push_back(until);
            until.clear();
        }
    }
    return temp;
}

bool isOperator(char c) {
    if (c == '+') {
        return true;
    } else if (c == '-') {
        return true;
    } else if (c == '/') {
        return true;
    } else if (c == '*') {
        return true;
    } else if (c == '(') {
        return true;
    } else if (c == ')') {
        return true;
    } else if (isComparator(c)){
        return true;
    } else {
        return false;
    }
}

vector<string> removeLeftBracet(vector<string> vec) {
    if((vec.back().back()) == '{') {
        vec.back().erase(vec.back().end() - 1);
    } else {
        // throw not left bracet error
    }
}

bool isComparator(char c) {
    if (c == '=') {
        return true;
    } else if (c == '<') {
        return true;
    } else if (c == '>') {
        return true;
    } else if (c == '!') {
        return true;
    } else {
        return false;
    }
}