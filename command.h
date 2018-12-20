//
// Created by alon on 12/16/18.
//
#ifndef ADVANCEDPROG_COMMAND_H
#define ADVANCEDPROG_COMMAND_H
#include <vector>
#include <string>
#include "DataReaderServer.h"
#include "symbolTable.h"
#include "commandGiver.h"
class DataReaderServer;
class symbolTable;
class commandGiver;
using namespace std;
class Command {
public:
    virtual void doCommand(vector<string> strings, DataReaderServer* server,
            symbolTable* table, int* outSockId, commandGiver* giver) = 0;
};
#endif //ADVANCEDPROG_COMMAND_H
