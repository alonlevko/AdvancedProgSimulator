//
// Created by alon on 12/18/18.
//
#ifndef ADVANCEDPROG_VARIABLE_H
#define ADVANCEDPROG_VARIABLE_H
#include "expression.h"
#include "symbolTable.h"
#include <string>
class symbolTable;
using namespace std;
class variable : public expression{
public:
    variable(symbolTable* t) {
        this->table = t;
        value = 0;
    }
    variable(symbolTable* t, double d) {
        this->table = t;
        this->value = d;
    }
    variable() {
        this->table = nullptr;
        this->value = 0;
    }
    string myName() {
        return name;
    }
    double calculate();
    void bind(string s);
    string boundTo() {
        return bindTo;
    }
    bool isBindedServer() {
        return isServer;
    }
    bool isBindedVar() {
        return isVar;
    }
    void setValue(double d) {
        value = d;
    }
private:
    bool isServer;
    bool isVar;
    string name;
    string bindTo;
    symbolTable* table;
    double value;
};
#endif //ADVANCEDPROG_VARIABLE_H
