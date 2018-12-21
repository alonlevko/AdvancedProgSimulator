//
// Created by alon on 12/19/18.
//

#include "createVarCommand.h"

void createVarCommand::doCommand(vector<string> strings, DataReaderServer* server,
               symbolTable* table, int* outSockId, commandGiver* giver){
    string name;
    for(string::iterator it = strings[0].begin(); it != strings[0].end(); it++) {
        if(*it == '=') {
            break;
        } else {
            name += *it;
            strings[0].erase(it);
            it--;
        }
    }
    variable v(name, table, server);
    table->addVariable(v);
    if(strings.size() > 0) { // we have a complex variable creation
        Command* c = giver->getCommand(name);// call a variable set command
        //strings.erase(strings.begin());
        c->doCommand(strings, server, table, outSockId, giver);
    }
}