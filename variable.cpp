#include "variable.h"
// bind a variable to a string
void variable::bind(string s) {
    if (table->isVariable(s)) { // if the string is a variable name
        isServer = false;
        isVar = true;
    } else { // the string should be a server path
        isServer = true;
        isVar = false;
    }
    // bind us to this
    bindTo = s;
    // update the table that we are bounded
    table->bindVariable(this->name, s);
}
// calculate the value of the variable
double variable::calculate() {
        if(isVar) { // our variable is binded to another
            value = (table->getVariable(bindTo))->calculate();
        } else if(isServer) { // our variable is binded to simulator value
            value = server->getValue(bindTo);
        }
        return value;
}
// set the value of the vriable to a new one
void variable::setValue(double d) {
    value = d;
}

void variable::setOnlyBind(string s) {
    this->bindTo = s;
    this->setBind = true;
}
