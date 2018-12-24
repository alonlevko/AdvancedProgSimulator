#include "entercCommand.h"
// wait untill we read a char from the user
void entercCommand::doCommand(vector<string> strings, DataReaderServer* server,
               symbolTable* table, int* outSockId, commandGiver* giver, istream& in) {
    char c;
    cin >> c;
}