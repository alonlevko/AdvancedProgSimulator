#ifndef ADVANCEDPROG_SETCOMMAND_H
#define ADVANCEDPROG_SETCOMMAND_H

#include "command.h"
class setCommand: public Command {
private:
    variable* var;
public:
    setCommand(variable* v) {
        this->var = v;
    }
    bool doCommand(vector<string> strings, DataReaderServer* server,
                   symbolTable* table, int* outSockId, commandGiver* giver, istream& in);
};


#endif //ADVANCEDPROG_SETCOMMAND_H
