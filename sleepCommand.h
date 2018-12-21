//
// Created by alon on 12/21/18.
//

#ifndef ADVANCEDPROG_SLEEPCOMMAND_H
#define ADVANCEDPROG_SLEEPCOMMAND_H

#include "command.h"
class sleepCommand: public Command{
    void doCommand(vector<string> strings, DataReaderServer* server,
                           symbolTable* table, int* outSockId, commandGiver* giver);
};


#endif //ADVANCEDPROG_SLEEPCOMMAND_H
