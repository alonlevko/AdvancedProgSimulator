//
// Created by alon on 12/20/18.
//

#include "setCommand.h"
#include "expressionFactory.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include "utils.h"
bool isOperator(char c);
void setCommand::doCommand(vector<string> strings, DataReaderServer* server,
               symbolTable* table, int* outSockId, commandGiver* giver, istream& in) {
    if((strings.size() > 2) && (strings[2]=="bind")) { // we have a bind command
        if(table->isVariable(strings[3])) {
            var->bind(strings[3]);
        } else {
            string str = strings[3].substr(1, strings[3].length() - 2);
            if (server->isInList(str)) {
                var->bind(str);
            } else {
                //throw bad bind error
                return;
            }
        }
    } else { // we have just to calculate an expression
        vector<string> temp = makeForParse(strings);
        if(temp[0] == "=") {
            temp.erase(temp.begin());
        }
        expressionFactory fact;
        double exp = fact.parse(temp, table);
        table->updateVariable(var->myName(), exp);
        if(var->isBindedServer()) {
            string toWrite = "set ";
            toWrite += var->boundTo();
            toWrite += " ";
            toWrite += to_string(exp);
            toWrite += "\r\n";
            char buffer[200];
            strcpy(buffer, toWrite.c_str());
            int n = write(*outSockId, buffer, strlen(buffer));
            if(n <= 0) {
                cout << "error writing to socket" << endl;
            }
        } else if (var->isBindedVar()) {
            table->updateVariable(var->boundTo(), exp);
        }

    }
}