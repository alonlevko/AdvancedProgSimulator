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
// set a variable value based on an input string
void setCommand::doCommand(vector<string> strings, DataReaderServer* server,
               symbolTable* table, int* outSockId, commandGiver* giver, istream& in) {
    if((strings.size() > 2) && (strings[2]=="bind")) { // we have a bind command
        if(table->isVariable(strings[3])) {
            var->bind(strings[3]);
        } else { // we have a bind to a simulator location
            string str = strings[3].substr(1, strings[3].length() - 2);
            if (server->isInList(str)) { // make sure the path is good
                var->bind(str);
            } else {
                var->setOnlyBind(str);
                //throw bad bind error
                return;
            }
        }
    } else { // we have just to calculate an expression
        vector<string> temp = makeForParse(strings);
        if(temp[0] == "=") { // make sure we have = and erase it
            temp.erase(temp.begin());
        }
        expressionFactory fact;
        // get the vale of the expression in double
        double exp = fact.parse(temp, table);
        // update the valuse of the variable.
        table->updateVariable(var->myName(), exp);
        if(var->isBindedServer()) { // if the variable is binded to the server
            // send a command to update the server
            string toWrite = "set ";
            toWrite += var->boundTo();
            toWrite += " ";
            toWrite += to_string(exp);
            toWrite += "\r\n";
            char buffer[200];
            strcpy(buffer, toWrite.c_str());
            // send the command to the simulator
            int n = write(*outSockId, buffer, strlen(buffer));
            if(n <= 0) { // if we had a bad read
                cout << "error writing to socket" << endl;
            }
        } else if (var->isBindedVar()) {
            table->updateVariable(var->boundTo(), exp);
        } else if(var->isBindedSetOnly()) {
            string toWrite = "set ";
            toWrite += var->boundTo();
            toWrite += " ";
            toWrite += to_string(exp);
            toWrite += "\r\n";
            char buffer[200];
            strcpy(buffer, toWrite.c_str());
            // send the command to the simulator
            int n = write(*outSockId, buffer, strlen(buffer));
            if(n <= 0) { // if we had a bad read
                cout << "error writing to socket" << endl;
            }
        }

    }
}