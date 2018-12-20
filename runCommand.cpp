//
// Created by alon on 12/16/18.
//
#include "runCommand.h"
#include <fstream>
#include <iostream>
#include <string>
#include "lexer.h"
#include "commandGiver.h"
using namespace std;
void runCommand::doCommand(vector<string> strings, DataReaderServer *reader,
                           symbolTable* table, int* outSockId, commandGiver* giver) {
    if(strings.size() != 1) {
        // exception - the only parameter is the file name
        return;
    }
    ifstream ifs(strings[0], ifstream::in);
    if(ifs.is_open()) {
        Lexer lexer;
        string input;
        vector<string> strtemp;
        while (getline(ifs, input)) {
            strings = lexer.lex(input);
            Command *command = giver->getCommand(strtemp[0]);
            strings.erase(strtemp.begin());
            command->doCommand(strtemp, reader, table, outSockId, giver);
            strtemp.clear();
            input.clear();
        }
    }
}