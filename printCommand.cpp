#include "printCommand.h"
// print to the cmd based on the input we got
void printCommand::doCommand(vector<string> strings, DataReaderServer* server,
               symbolTable* table, int* outSockId, commandGiver* giver, istream& in) {
    if (strings.size() == 1) { // if we have only 1 input we have a variable
        if(table->isVariable(strings[0])) { // make sure it is a variable/
            variable* v = table->getVariable(strings[0]);
            cout << v->calculate() << endl; // print his value/
        } else { // print the input without the ""
            cout << strings[0].substr(1, strings[0].length() - 2) << endl;
        }
        // we have a long string we need to output
    } else if(((*(strings.begin()->begin()) == '\"')) && (strings.back().back() == '\"')) {
        // erase the ""
        strings.begin()->erase(strings.begin()->begin());
        strings.back().erase(strings.back().length() - 1);
        // print all of the other input
        for(vector<string>::iterator it = strings.begin(); it != strings.end(); it++) {
            cout << *it << " ";
        }
        cout << endl;
    } else { // print that we had an error
        cout << "error" << endl;
    }
}