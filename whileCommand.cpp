//
// Created by alon on 12/22/18.
//

#include "whileCommand.h"
#include "ifCommand.h"
void whileCommand::doCommand(vector<string> strings, DataReaderServer* server,
                       symbolTable* table, int* outSockId, commandGiver* giver, istream& in) {
    ifCommand toDo(true);
    toDo.doCommand(strings, server, table, outSockId, giver, in);
    toDo.skipRead();
    while(toDo.checkStatment(table)) {
        toDo.doCommand(strings, server, table, outSockId, giver, in);
    }
}