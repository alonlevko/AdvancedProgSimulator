//
// Created by alon on 12/19/18.
//

#include "createVarCommand.h"
// create a new variable and put is into the symbol table.
// if this is a complex creation call the set command.
void createVarCommand::doCommand(vector<string> strings, DataReaderServer* server,
               symbolTable* table, int* outSockId, commandGiver* giver, istream& in){
    string name;
    // go over each char in the first string and save it to the name untill the =
    for(string::iterator it = strings[0].begin(); it != strings[0].end(); it++) {
        if(*it == '=') {
            break;
        } else {
            name += *it;
            strings[0].erase(it);
            it--;
        }
    }
    // initialize the variable
    variable v(name, table, server);
    // copy the variable into the table.
    table->addVariable(v);
    if(strings.size() > 1) { // we have a complex variable creation
        Command* c = giver->getCommand(name);// call a variable set command
        c->doCommand(strings, server, table, outSockId, giver, in);
    }
}