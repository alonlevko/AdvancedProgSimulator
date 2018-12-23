//
// Created by alon on 12/21/18.
//

#include "ifCommand.h"
#include "utils.h"
#include "expressionFactory.h"
#include "lexer.h"
vector<string> separate(vector<string> input) {

}
void ifCommand::doCommand(vector<string> strings, DataReaderServer* server,
               symbolTable* table, int* outSockId, commandGiver* giver,istream& in) {
    // comparators with double tokens are in two elements
    //strings = removeLeftBracet(strings);
    if(!skip) {
    bool startRev = false;
    if((strings.back().back()) == '{') {
        strings.back().erase(strings.back().end() - 1);
        startRev = true;
    }
    strings = makeForParse(strings);
    vector<string> left;
    vector<string> right;
    bool swi = false;
    for(vector<string>::iterator it = strings.begin(); it != strings.end(); it++) {
        if((it->size() == 1) && (isComparator((*it)[0]))) {
            comparator += ((*it)[0]);
            swi = true;
            continue;
        }
        if(swi) {
            right.push_back(*it);
        } else {
            left.push_back(*it);
        }
    }
    expressionFactory fact;
    left = fact.removeUnaryMinus(left);
    right = fact.removeUnaryMinus(right);
    rpnLeft = fact.shuntingYard(left, table);
    rpnRight = fact.shuntingYard(right, table);
    // start getting next statments;
    Lexer lex;
    string line;
    bool end = false;
        while (getline(in, line)) {
            if (hasStart(line) && !startRev) {
                startRev = true;
                continue;
            } else {
                if (!startRev) {
                    // no start of scope error
                    break;
                }
            }
            if (hasEnd(line)) {
                if (line.size() > 1) {
                    end = true;
                } else {
                    break;
                }
            }
            vector<string> toDo = lex.lex(line);
            Command *command = giver->getCommand(toDo[0]);
            toDo.erase(toDo.begin());
            toExcecute.push_back(command);
            aruments.push_back(toDo);
            toDo.clear();
            line.clear();
            if (end) {
                break;
            }
        }
    }
    if(checkStatment(table)) {
        list<vector<string>>::iterator iterator1 = aruments.begin();
        list<Command*>::iterator iterator2 = toExcecute.begin();
        while(iterator1 != aruments.end() && iterator2 != toExcecute.end()) {
            (*iterator2)->doCommand(*iterator1, server, table, outSockId, giver,
                    in);
            ++iterator1;
            ++iterator2;
        }
    }
    if(!inWhile) {
        aruments.clear();
        toExcecute.clear();
        rpnLeft.clear();
        rpnRight.clear();
        comparator.clear();
    }
}
bool ifCommand::checkStatment(symbolTable* table) {
    expressionFactory fact;
    double valLeft = fact.RPNCalc(rpnLeft, table);
    double valRight = fact.RPNCalc(rpnRight, table);
    if(comparator == "==") {
        return valLeft == valRight;
    } else if (comparator == "!=") {
        return valLeft != valRight;
    } else if (comparator == ">") {
        return valLeft > valRight;
    } else if (comparator == "<") {
        return valLeft < valRight;
    } else if (comparator == ">=") {
        return valLeft >= valRight;
    } else if (comparator == "<=") {
        return valLeft <= valRight;
    } else {
        // no such comparator error
        return false;
    }
}
// if returns true removes the end of scope
bool ifCommand::hasEnd(string& s) {
    size_t found = s.find('}');
    if(found == string::npos) {
        return false;
    } else {
        s.erase(found);
        return true;
    }
}
// if returns true removes the start of scope
bool ifCommand::hasStart(string& s) {
    size_t found = s.find('{');
    if(found == string::npos) {
        return false;
    } else {
        s.erase(found);
        return true;
    }
}