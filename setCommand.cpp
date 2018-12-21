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
bool isOperator(char c);
void setCommand::doCommand(vector<string> strings, DataReaderServer* server,
               symbolTable* table, int* outSockId, commandGiver* giver) {
    if(strings[0]=="bind") { // we have a bind command
        string str = strings[1].substr(1, strings[0].length() - 2);
        var.bind(str);
    } else { // we have just to calculate an expression
        vector<string> temp = makeForParse(strings);
        if(temp[0] == "=") {
            temp.erase(temp.begin());
        }
        expressionFactory fact;
        double exp = fact.parse(temp, table);
        if(var.isBindedServer()) {
            string toWrite = "set ";
            toWrite += var.boundTo();
            toWrite += " ";
            toWrite += to_string(var.calculate());
            toWrite += "\r\n";
            char buffer[200];
            strcpy(buffer, toWrite.c_str());
            int n = write(*outSockId, buffer, strlen(buffer));
            if(n <= 0) {
                cout << "error writing to socket" << endl;
            }
        } else if (var.isBindedVar()) {
            table->updateVariable(var.boundTo(), exp);
        }
        table->updateVariable(var.myName(), exp);
    }
}
// take expression inside vec and turn them to easy parse (2+3-->2 + 3
vector<string> setCommand::makeForParse(vector<string> vec) {
    vector<string> temp;
    for(vector<string>::iterator it = vec.begin(); it != vec.end(); it++) {
        string str = *it;
        string until;
        if(str == "") {
            continue;
        }
        if(str.size() == 1) {
            temp.push_back(str);
            continue;
        }
        for(string::iterator itr = str.begin(); itr != str.end(); itr++) {
            if (isOperator(*itr)) {
                if(until.size() > 0) {
                    temp.push_back(until);
                    until.clear();
                }
                string x;
                x.push_back(*itr);
                temp.push_back(x);
            } else {
                until.push_back(*itr);
            }
        }
        if(until.size() > 0) {
            temp.push_back(until);
            until.clear();
        }
    }
    return temp;
}
/*
 *
 * 5+3
 *
 */
bool isOperator(char c) {
    if (c == '+') {
        return true;
    } else if (c == '-') {
        return true;
    } else if (c == '/') {
        return true;
    } else if (c == '*') {
        return true;
    } else if (c == '=') {
        return true;
    } else if (c == '(') {
        return true;
    } else if (c == ')') {
        return true;
    } else {
        return false;
    }
}