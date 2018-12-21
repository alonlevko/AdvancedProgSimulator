//
// Created by alon on 12/18/18.
//

#ifndef ADVANCEDPROG_SYMBOLTABLE_H
#define ADVANCEDPROG_SYMBOLTABLE_H
#include "variable.h"
#include <map>
class variable;
using namespace std;
class symbolTable {
private:
    map<string, variable> variables;
    map<string, variable> binded;

public:
    void addVariable(variable v);
    variable getVariable(string s);
    bool isVariable(string s);
    void updateFromServer(string bind, double number);
    void bindVariable(string name, string bindTo);
    void updateVariable(string s, double);

};


#endif //ADVANCEDPROG_SYMBOLTABLE_H
