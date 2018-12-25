#ifndef ADVANCEDPROG_CREATEVARCOMMAND_H
#define ADVANCEDPROG_CREATEVARCOMMAND_H

#include "command.h"
#include "DataReaderServer.h"
#include "symbolTable.h"
class createVarCommand : public Command {
public:
    bool doCommand(vector<string> strings, DataReaderServer* server,
                   symbolTable* table, int* outSockId, commandGiver* giver, istream& in);
};
#endif //ADVANCEDPROG_CREATEVARCOMMAND_H
