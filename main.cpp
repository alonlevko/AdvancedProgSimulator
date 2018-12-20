#include <iostream>
#include <string>
#include <vector>
#include "lexer.h"
#include "command.h"
#include "commandGiver.h"
#include "DataReaderServer.h"
using namespace std;
//extern DataReaderServer fromServer;
int main() {
    Lexer lexer;
    commandGiver giver;
    DataReaderServer reader;
    string input;
    vector<string> strings;
    symbolTable table;
    int outSocket;
    while(true) {
        getline(cin, input);
        if (input.compare("exit") == 1) {
            terminate();
            break;
        }
        strings = lexer.lex(input);
        Command *command = giver.getCommand(strings[0]);
        strings.erase(strings.begin());
        command->doCommand(strings, &reader, &table, &outSocket, &giver);
        strings.clear();
        input.clear();
    }
}