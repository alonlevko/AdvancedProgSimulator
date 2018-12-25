//
// Created by alon on 12/25/18.
//

#ifndef ADVANCEDPROG_EXITCOMMAND_H
#define ADVANCEDPROG_EXITCOMMAND_H
#include "command.h"
class exitCommand: public Command {
    bool doCommand(vector<string> strings, DataReaderServer* server,
                           symbolTable* table, int* outSockId, commandGiver* giver, istream& in) {
        return false;
    }
};
#endif //ADVANCEDPROG_EXITCOMMAND_H
