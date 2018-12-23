//
// Created by alon on 12/20/18.
//

#ifndef ADVANCEDPROG_SETCOMMAND_H
#define ADVANCEDPROG_SETCOMMAND_H

#include "command.h"
class setCommand: public Command {
private:
    variable* var;
public:
    setCommand(variable* v) {
        this->var = v;
    }
    void doCommand(vector<string> strings, DataReaderServer* server,
                   symbolTable* table, int* outSockId, commandGiver* giver, istream& in);
};


#endif //ADVANCEDPROG_SETCOMMAND_H
