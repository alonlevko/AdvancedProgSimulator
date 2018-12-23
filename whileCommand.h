//
// Created by alon on 12/22/18.
//

#ifndef ADVANCEDPROG_WHILECOMMAND_H
#define ADVANCEDPROG_WHILECOMMAND_H

#include "command.h"
class whileCommand: public Command {
    void doCommand(vector<string> strings, DataReaderServer* server,
                           symbolTable* table, int* outSockId, commandGiver* giver, istream& in);
};


#endif //ADVANCEDPROG_WHILECOMMAND_H
