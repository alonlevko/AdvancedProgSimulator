#include "utils.h"
// make a file ready from parsing by spliting it up into tokens
vector<string> makeForParse(vector<string> vec) {
    vector<string> temp;
    //iterate over the strings an seperate them
    for(vector<string>::iterator it = vec.begin(); it != vec.end(); it++) {
        string str = *it;
        string until;
        if(str == "") { // if the string is nothing we dont need it
            continue;
        }
        if(str.size() == 1) { // if its just 1 char we can't seperate it
            temp.push_back(str);
            continue;
        }
        // iterate over each char in the string
        for(string::iterator itr = str.begin(); itr != str.end(); itr++) {
            // if the char is an operator we split here
            if (isOperator(*itr)) {
                if(until.size() > 0) {
                    temp.push_back(until);
                    until.clear();
                }
                string x;
                x.push_back(*itr);
                temp.push_back(x);
            } else { // if we dont have a operetor push it
                until.push_back(*itr);
            }
        }
        if(until.size() > 0) { // if we have somthing push in into the output
            temp.push_back(until);
            until.clear();
        }
    }
    return temp;
}
// check if the char is an operator
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
// check if the char is a comparator
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