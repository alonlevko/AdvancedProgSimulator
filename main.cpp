#include <iostream>
#include <string>
#include <vector>
#include "lexer.h"
#include "command.h"
#include "commandGiver.h"
#include "DataReaderServer.h"
using namespace std;
int main(int argc, char*argv[]) {
    // create on the stack the classes we will nee
    bool exitFlag;
    Lexer lexer;
    DataReaderServer reader;
    string input;
    vector<string> strings;
    symbolTable table;
    commandGiver giver(&table);
    int outSocket;
    if(argc == 2) { // we have a file input
        Command *command = giver.getCommand("run");
        string str(argv[1]);
        strings.push_back(str);
        exitFlag = command->doCommand(strings, &reader, &table, &outSocket, &giver, cin);
        strings.clear();
    }
    // continue getting input from the user.
    while(exitFlag) {
        getline(cin, input);
        // if the user inputed exit we leave
        if (input.compare("exit") == 0) {
            break;
        }
        // seperate the input string.
        strings = lexer.lex(input);
        // get the command based on the token
        Command *command = giver.getCommand(strings[0]);
        strings.erase(strings.begin());
        // call the command with the rest of the input
        exitFlag = command->doCommand(strings, &reader, &table, &outSocket, &giver, cin);
        strings.clear();
        input.clear();
    }
    close(outSocket);
}