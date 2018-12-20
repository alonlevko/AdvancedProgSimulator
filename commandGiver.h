//
// Created by alon on 12/16/18.
//

#ifndef ADVANCEDPROG_COMMANDGIVER_H
#define ADVANCEDPROG_COMMANDGIVER_H
#include "command.h"
#include <map>
class Command;
class commandGiver {
private:
    map<string, Command*> commands;
public:
    commandGiver();
    ~commandGiver();
    Command* getCommand(string str);
};
#endif //ADVANCEDPROG_COMMANDGIVER_H
