#ifndef ADVANCEDPROG_WHILECOMMAND_H
#define ADVANCEDPROG_WHILECOMMAND_H
#include "command.h"
class whileCommand: public Command {
    bool doCommand(vector<string> strings, DataReaderServer* server,
                           symbolTable* table, int* outSockId, commandGiver* giver, istream& in);
};
#endif //ADVANCEDPROG_WHILECOMMAND_H
