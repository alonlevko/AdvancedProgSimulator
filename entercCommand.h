#ifndef ADVANCEDPROG_ENTERCCOMMAND_H
#define ADVANCEDPROG_ENTERCCOMMAND_H
#include "command.h"
class entercCommand : public Command {
    bool doCommand(vector<string> strings, DataReaderServer* server,
                           symbolTable* table, int* outSockId, commandGiver* giver, istream& in);
};
#endif //ADVANCEDPROG_ENTERCCOMMAND_H
