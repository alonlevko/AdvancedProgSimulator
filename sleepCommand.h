#ifndef ADVANCEDPROG_SLEEPCOMMAND_H
#define ADVANCEDPROG_SLEEPCOMMAND_H

#include "command.h"
class sleepCommand: public Command{
    void doCommand(vector<string> strings, DataReaderServer* server,
                           symbolTable* table, int* outSockId, commandGiver* giver, istream& in);
};


#endif //ADVANCEDPROG_SLEEPCOMMAND_H
