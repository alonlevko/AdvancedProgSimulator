//
// Created by alon on 12/16/18.
//
#ifndef ADVANCEDPROG_RUNCOMMAND_H
#define ADVANCEDPROG_RUNCOMMAND_H
#include "command.h"
#include <vector>
#include <string>
using namespace std;
class runCommand: public Command {
    void doCommand(vector<string> strings, DataReaderServer* reader,
                   symbolTable* table, int* outSockId, commandGiver* giver);
};
#endif //ADVANCEDPROG_RUNCOMMAND_H