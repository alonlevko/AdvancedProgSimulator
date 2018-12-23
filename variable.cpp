//
// Created by alon on 12/18/18.
//

#include "variable.h"

void variable::bind(string s) {
    if (table->isVariable(s)) {
        isServer = false;
        isVar = true;
    } else {
        isServer = true;
        isVar = false;
    }
    bindTo = s;
    table->bindVariable(this->name, s);
}

double variable::calculate() {
        if(isVar) { // our variable is binded to another
            value = (table->getVariable(bindTo))->calculate();
        } else if(isServer) {
            value = server->getValue(bindTo);
        }
        return value;
}

void variable::setValue(double d) {
    value = d;
}
