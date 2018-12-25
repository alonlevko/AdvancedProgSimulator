#include "runCommand.h"
#include <fstream>
#include <iostream>
#include <string>
#include "lexer.h"
#include "commandGiver.h"
using namespace std;
// run commands from a file
bool runCommand::doCommand(vector<string> strings, DataReaderServer *reader,
                           symbolTable* table, int* outSockId, commandGiver* giver, istream& in) {
    if(strings.size() != 1) {
        // exception - the only parameter is the file name
        return true;
    }
    // create a stream based on the file that was inputed
    ifstream ifs(strings[0], ifstream::in);
    if(ifs.is_open()) { // make sure we can open the file
        Lexer lexer;
        string input;
        vector<string> strtemp;
        bool exit = true;
        // get a line from the file
        while (getline(ifs, input) && exit) {
            // run the command that was in the file
            strtemp = lexer.lex(input);
            Command *command = giver->getCommand(strtemp[0]);
            strtemp.erase(strtemp.begin());
            // the next commands will need to read also from this file
            exit = command->doCommand(strtemp, reader, table, outSockId, giver, ifs);
            strtemp.clear();
            input.clear();
        }
    }
    ifs.close();
    return exit;
}