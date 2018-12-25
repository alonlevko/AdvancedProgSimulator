#include "whileCommand.h"
#include "ifCommand.h"
bool whileCommand::doCommand(vector<string> strings, DataReaderServer* server,
                       symbolTable* table, int* outSockId, commandGiver* giver, istream& in) {
    // invoke an if command that we will run in a loop
    bool exit = true;
    ifCommand toDo(true);
    // tell it to do the command if the condition is met
    toDo.doCommand(strings, server, table, outSockId, giver, in);
    // tell it to skip the new reading nex time
    toDo.skipRead();
    while(toDo.checkStatment(table) && exit) { // check if the condition is met
        // just run the commands in the if variable
        exit = toDo.doCommand(strings, server, table, outSockId, giver, in);
    }
    return exit;
}