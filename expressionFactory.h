//
// Created by alon on 12/20/18.
//

#ifndef ADVANCEDPROG_EXPRESSIONFACTORY_H
#define ADVANCEDPROG_EXPRESSIONFACTORY_H

#include <vector>
#include <string>
#include <list>
#include "symbolTable.h"
#include "expression.h"
using namespace std;
struct opertor {
    string rep;
    int precedence;
};
class expressionFactory {
public:
    double parse(vector<string> vec, symbolTable* table);
private:
    bool is_number(string& s);
    bool is_operator(string& s);
    bool is_variable(string& s);
    opertor makeOpertor(string& s);
    list<string> shuntingYard(vector<string> vec);
    vector<string> removeUnaryMinus(vector<string> vec);
    double calc(double first, string s, double second);
};


#endif //ADVANCEDPROG_EXPRESSIONFACTORY_H
