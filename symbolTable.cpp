//
// Created by alon on 12/18/18.
//

#include "symbolTable.h"
void symbolTable::addVariable(variable v) {
    variables[v.myName()] = v;
}
variable symbolTable::getVariable(string s) {
    return variables[s];
}

bool symbolTable::isVariable(string s){
    if(variables.find(s) != variables.end()) {
        return true;
    } else {
        return false;
    }
}

void symbolTable::updateFromServer(string bind, double number) {
    if(binded.find(bind) != binded.end()) {
        (binded[bind]).setValue(number);
    } else {
        return;
    }
}
void symbolTable::bindVariable(string name, string bindTo) {
    variable var = this->getVariable(name);
    binded[bindTo] = var;
}