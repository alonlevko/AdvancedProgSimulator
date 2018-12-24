#ifndef ADVANCEDPROG_COMMANDGIVER_H
#define ADVANCEDPROG_COMMANDGIVER_H
#include "command.h"
#include "symbolTable.h"
#include <map>
class Command;
// gives pointers to commands so anybody can run them.
class commandGiver {
private:
    symbolTable* table;
    map<string, Command*> commands;
    void makeCommands();
public:
    commandGiver();
    commandGiver(symbolTable* t);
    ~commandGiver();
    Command* getCommand(string str);
};
#endif //ADVANCEDPROG_COMMANDGIVER_H
