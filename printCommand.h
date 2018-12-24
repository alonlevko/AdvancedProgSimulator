#ifndef ADVANCEDPROG_PRINTCOMMAND_H
#define ADVANCEDPROG_PRINTCOMMAND_H

#include "command.h"
class printCommand:public Command {
    void doCommand(vector<string> strings, DataReaderServer* server,
                           symbolTable* table, int* outSockId, commandGiver* giver, istream& in);
};


#endif //ADVANCEDPROG_PRINTCOMMAND_H
