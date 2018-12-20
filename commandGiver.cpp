//
// Created by alon on 12/19/18.
//
#include "commandGiver.h"
#include "openDataServer.h"
#include "connectCommand.h"
commandGiver::commandGiver(){
    // create all commands we have and put them into the map
    commands["openDataServer"] = new openDataServer();
    commands["connect"] = new connectCommand();
}
commandGiver::~commandGiver() {
    for(map<string, Command*>::iterator it = commands.begin() ;
        it != commands.end(); it++) {
        Command * c = it->second;
        delete c;
    }
}
Command* commandGiver::getCommand(string str) {
    if(commands.find(str) != commands.end()) {
        return commands[str];
    } else {
        return nullptr;
    }
}