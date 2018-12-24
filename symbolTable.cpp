#include "symbolTable.h"
// add a variable to the table by copy
void symbolTable::addVariable(variable v) {
    variables[v.myName()] = v;
}
// get a pointer to a variable that is in the table
variable* symbolTable::getVariable(string s) {
    if(isVariable(s)) {
        return &(variables[s]);
    } else {
        return nullptr;
    }
}
// update the value of a variable that is in the table
void symbolTable::updateVariable(string s, double d) {
    if(isVariable(s)) {
        variables[s].setValue(d);
    } else {
        // no such variable error
        return;
    }
}
// check if a string is a name of a variable in the table
bool symbolTable::isVariable(string s){
    if(variables.find(s) != variables.end()) {
        return true;
    } else {
        return false;
    }
}
// bind a variable to a strings that is inputed.
void symbolTable::bindVariable(string name, string bindTo) {
    variable* var = this->getVariable(name);
    binded[bindTo] = *var;
}