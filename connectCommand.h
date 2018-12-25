#ifndef ADVANCEDPROG_CONNECTCOMMAND_H
#define ADVANCEDPROG_CONNECTCOMMAND_H
#include "command.h"
class Command;
class commandGiver;
class connectCommand: public Command {
public:
    bool doCommand(vector<string> strings, DataReaderServer* reader,
            symbolTable* table, int* outSockId, commandGiver* giver, istream& in);
};


#endif //ADVANCEDPROG_CONNECTCOMMAND_H
