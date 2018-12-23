//
// Created by alon on 12/21/18.
//

#include "printCommand.h"
void printCommand::doCommand(vector<string> strings, DataReaderServer* server,
               symbolTable* table, int* outSockId, commandGiver* giver, istream& in) {
    if (strings.size() == 1) {
        if(table->isVariable(strings[0])) {
            variable* v = table->getVariable(strings[0]);
            cout << v->calculate() << endl;
        } else {
            cout << strings[0].substr(1, strings[0].length() - 2) << endl;
        }
    } else if(((*(strings.begin()->begin()) == '\"')) && (strings.back().back() == '\"')) {
        strings.begin()->erase(strings.begin()->begin());
        strings.back().erase(strings.back().length() - 1);
        for(vector<string>::iterator it = strings.begin(); it != strings.end(); it++) {
            cout << *it << " ";
        }
        cout << endl;
    } else {
        cout << "error" << endl;
    }
}