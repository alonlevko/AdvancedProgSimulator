#ifndef ADVANCEDPROG_EXPRESSIONFACTORY_H
#define ADVANCEDPROG_EXPRESSIONFACTORY_H
#include <vector>
#include <string>
#include <list>
#include "symbolTable.h"
#include "expression.h"
using namespace std;
// used to represent an operator in the shunting yard.
struct opertor {
    string rep;
    int precedence;
};
// has public methods that we can use to evaluate the values of string inputs.
class expressionFactory {
public:
    double parse(vector<string> vec, symbolTable* table);
    bool is_number(string& s);
    bool is_operator(string& s);
    bool is_variable(string& s);
    opertor makeOpertor(string& s);
    list<string> shuntingYard(vector<string> vec, symbolTable* table);
    vector<string> removeUnaryMinus(vector<string> vec);
    double calc(double first, string s, double second);
    double RPNCalc(list<string> tokens, symbolTable* table);
};


#endif //ADVANCEDPROG_EXPRESSIONFACTORY_H
