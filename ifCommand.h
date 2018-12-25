//
// Created by alon on 12/21/18.
//

#ifndef ADVANCEDPROG_IFCOMMAND_H
#define ADVANCEDPROG_IFCOMMAND_H
#include "list"
#include "string"
#include "vector"
#include "command.h"
class ifCommand : public Command{
public:
    // if we are created in a while loop we need to know
    ifCommand(bool inWhile) {
        this->inWhile = inWhile;
        skip = false;
    }
    // not in a while loop
    ifCommand(){
        this->inWhile = false;
        skip = false;
    }
    bool doCommand(vector<string> strings, DataReaderServer* server,
                   symbolTable* table, int* outSockId, commandGiver* giver, istream& in);
    bool checkStatment(symbolTable* table);
    bool hasEnd(string& s);
    bool hasStart(string& s);
    void skipRead() {
        skip = true;
    }
private:
    bool inWhile;
    bool skip;
    list<Command*> toExcecute;
    list<vector<string>> aruments;
    list<string> rpnLeft;
    list<string> rpnRight;
    string comparator;
};


#endif //ADVANCEDPROG_IFCOMMAND_H
