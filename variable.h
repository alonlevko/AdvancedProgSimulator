#ifndef ADVANCEDPROG_VARIABLE_H
#define ADVANCEDPROG_VARIABLE_H
#include "expression.h"
#include "symbolTable.h"
#include "DataReaderServer.h"
#include <string>
class symbolTable;
class DataReaderServer;
using namespace std;
class variable : public expression{
public:
    // create a variable with no value
    variable(string name, symbolTable* t, DataReaderServer* s) {
        this->name = name;
        this->table = t;
        this->server = s;
        value = 0;
        this->isServer = false;
        this->isVar = false;
        this->setBind = false;
    }
    // create a vriable using a value
    variable(string name, symbolTable* t, DataReaderServer* s, double d) {
        this->name = name;
        this->table = t;
        this->value = d;
        this->server = s;
        this->isServer = false;
        this->isVar = false;
        this->setBind = false;
    }
    // create a null variable that is all empty
    variable() {
        this->name = "";
        this->server = nullptr;
        this->table = nullptr;
        this->value = 0;
        this->isServer = false;
        this->isVar = false;
        this->setBind = false;
    }
    // return the name of the variable
    string myName() {
        return name;
    }
    double calculate();
    void bind(string s);
    void setOnlyBind(string s);
    // return the string we are bound to
    string boundTo() {
        return bindTo;
    }
    // check if binded to the server
    bool isBindedServer() {
        return isServer;
    }
    // check if binded to variable
    bool isBindedVar() {
        return isVar;
    }
    bool isBindedSetOnly() {
        return setBind;
    };
    void setValue(double d);
private:
    bool isServer;
    bool isVar;
    bool setBind;
    string name;
    string bindTo;
    symbolTable* table;
    DataReaderServer* server;
    double value;
};
#endif //ADVANCEDPROG_VARIABLE_H
