//
// Created by alon on 12/22/18.
//

#include "entercCommand.h"
#include <unistd.h>
#include <termios.h>
void entercCommand::doCommand(vector<string> strings, DataReaderServer* server,
               symbolTable* table, int* outSockId, commandGiver* giver, istream& in) {
    char c;
    cin >> c;
}