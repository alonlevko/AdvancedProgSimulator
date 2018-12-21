//
// Created by alon on 12/19/18.
//
#include "commandGiver.h"
#include "openDataServer.h"
#include "connectCommand.h"
#include "createVarCommand.h"
#include "setCommand.h"
#include "printCommand.h"
commandGiver::commandGiver(){
    table = nullptr;
    this->makeCommands();
}
commandGiver::commandGiver(symbolTable* t){
    table = t;
    this->makeCommands();
}
commandGiver::~commandGiver() {
    for(map<string, Command*>::iterator it = commands.begin() ;
        it != commands.end(); it++) {
        Command * c = it->second;
        delete c;
    }
}
Command* commandGiver::getCommand(string str) {
    if(table->isVariable(str)) {
        variable temp = table->getVariable(str);
        if (commands.find(str) == commands.end()) { // we dont have set command on that vriable
            commands[str] = new setCommand(temp);
            return commands[str];
        } else {  //we have set command on that vriable
            return commands[str];
        }
    }
    if(commands.find(str) != commands.end()) {
        return commands[str];
    } else {
        return nullptr;
    }
}

void commandGiver::makeCommands() {
    // create all commands we have and put them into the map
    commands["openDataServer"] = new openDataServer();
    commands["connect"] = new connectCommand();
    commands["var"] = new createVarCommand();
    commands["print"] = new printCommand();
}