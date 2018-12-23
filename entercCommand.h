//
// Created by alon on 12/22/18.
//

#ifndef ADVANCEDPROG_ENTERCCOMMAND_H
#define ADVANCEDPROG_ENTERCCOMMAND_H

#include "command.h"
class entercCommand : public Command {
    void doCommand(vector<string> strings, DataReaderServer* server,
                           symbolTable* table, int* outSockId, commandGiver* giver, istream& in);
};


#endif //ADVANCEDPROG_ENTERCCOMMAND_H
