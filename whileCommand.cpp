#include "whileCommand.h"
#include "ifCommand.h"
void whileCommand::doCommand(vector<string> strings, DataReaderServer* server,
                       symbolTable* table, int* outSockId, commandGiver* giver, istream& in) {
    // invoke an if command that we will run in a loop
    ifCommand toDo(true);
    // tell it to do the command if the condition is met
    toDo.doCommand(strings, server, table, outSockId, giver, in);
    // tell it to skip the new reading nex time
    toDo.skipRead();
    while(toDo.checkStatment(table)) { // check if the condition is met
        // just run the commands in the if variable
        toDo.doCommand(strings, server, table, outSockId, giver, in);
    }
}