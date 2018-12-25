#ifndef ADVANCEDPROG_RUNCOMMAND_H
#define ADVANCEDPROG_RUNCOMMAND_H
#include "command.h"
#include <vector>
#include <string>
using namespace std;
class runCommand: public Command {
    bool doCommand(vector<string> strings, DataReaderServer* reader,
                   symbolTable* table, int* outSockId, commandGiver* giver, istream& in);
};
#endif //ADVANCEDPROG_RUNCOMMAND_H
