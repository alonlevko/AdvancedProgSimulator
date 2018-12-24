#ifndef ADVANCEDPROG_COMMAND_H
#define ADVANCEDPROG_COMMAND_H
#include <vector>
#include <string>
#include "DataReaderServer.h"
#include "symbolTable.h"
#include "commandGiver.h"
#include <iostream>
class DataReaderServer;
class symbolTable;
class commandGiver;
using namespace std;
// interface all commands must impelment so we can run them.
class Command {
public:
    // the functions to run the command.
    virtual void doCommand(vector<string> strings, DataReaderServer* server,
            symbolTable* table, int* outSockId, commandGiver* giver, istream& in) = 0;
};
#endif //ADVANCEDPROG_COMMAND_H
