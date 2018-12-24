#include "commandGiver.h"
#include "openDataServer.h"
#include "connectCommand.h"
#include "createVarCommand.h"
#include "setCommand.h"
#include "printCommand.h"
#include "ifCommand.h"
#include "sleepCommand.h"
#include "whileCommand.h"
#include "runCommand.h"
#include "entercCommand.h"
// initialize an empty command giver
commandGiver::commandGiver(){
    table = nullptr;
    this->makeCommands();
}
//initialize a command giver with a pointer to out symbol table
commandGiver::commandGiver(symbolTable* t){
    table = t;
    this->makeCommands();
}
// destroy the command giver and get rid of all heap memory
commandGiver::~commandGiver() {
    // delete each command we have.
    for(map<string, Command*>::iterator it = commands.begin() ;
        it != commands.end(); it++) {
        Command * c = it->second;
        delete c;
    }
}
//get a pointer to a command based on its token/
Command* commandGiver::getCommand(string str) {
    if(table->isVariable(str)) { // check if the command is a variable name
        variable* temp = table->getVariable(str);
        if (commands.find(str) == commands.end()) { // we dont have set command on that vriable
            commands[str] = new setCommand(temp);
            return commands[str];
        } else {  //we have set command on that vriable
            return commands[str];
        }
    }
    // if we found the command
    if(commands.find(str) != commands.end()) {
        // return a pointer to the command
        return commands[str];
    } else {
        return nullptr;
    }
}
// initialize the table with the names of the commands.
void commandGiver::makeCommands() {
    // create all commands we have and put them into the map
    commands["run"] = new runCommand();
    commands["openDataServer"] = new openDataServer();
    commands["connect"] = new connectCommand();
    commands["var"] = new createVarCommand();
    commands["print"] = new printCommand();
    commands["if"] = new ifCommand();
    commands["sleep"] = new sleepCommand();
    commands["while"] = new whileCommand();
    commands["Enterc"] = new entercCommand();
    commands["enterc"] = new entercCommand();
}