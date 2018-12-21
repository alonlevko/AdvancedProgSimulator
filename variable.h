//
// Created by alon on 12/18/18.
//
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
    variable(string name, symbolTable* t, DataReaderServer* s) {
        this->name = name;
        this->table = t;
        this->server = s;
        value = 0;
        this->isServer = false;
        this->isVar = false;
    }
    variable(string name, symbolTable* t, DataReaderServer* s, double d) {
        this->name = name;
        this->table = t;
        this->value = d;
        this->server = s;
        this->isServer = false;
        this->isVar = false;
    }
    variable() {
        this->name = "";
        this->server = nullptr;
        this->table = nullptr;
        this->value = 0;
        this->isServer = false;
        this->isVar = false;
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
    void setValue(double d);
private:
    bool isServer;
    bool isVar;
    string name;
    string bindTo;
    symbolTable* table;
    DataReaderServer* server;
    double value;
};
#endif //ADVANCEDPROG_VARIABLE_H
