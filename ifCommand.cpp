#include "ifCommand.h"
#include "utils.h"
#include "expressionFactory.h"
#include "lexer.h"
// do the if command, get the commands input and then run them if the statment is correct
void ifCommand::doCommand(vector<string> strings, DataReaderServer* server,
               symbolTable* table, int* outSockId, commandGiver* giver,istream& in) {
    // comparators with double tokens are in two elements
    if(!skip) { // if we have been commanded by our creator to skip the invokation
    bool startRev = false; // flag for if the { has been removed
    if((strings.back().back()) == '{') { // if the end is { remove it
        strings.back().erase(strings.back().end() - 1);
        startRev = true;
    }
    // get the expression ready for parsing by seperating tokens.
    strings = makeForParse(strings);
    vector<string> left;
    vector<string> right;
    bool swi = false;
    // get the comparator in a different string anseperato to right and left
    for(vector<string>::iterator it = strings.begin(); it != strings.end(); it++) {
        if((it->size() == 1) && (isComparator((*it)[0]))) { // append the comparator
            comparator += ((*it)[0]);
            swi = true;
            continue;
        }
        // swi stand for switch to right.
        if(swi) {
            right.push_back(*it);
        } else {
            left.push_back(*it);
        }
    }
    expressionFactory fact;
    // ready the left and right for calculation
    left = fact.removeUnaryMinus(left);
    right = fact.removeUnaryMinus(right);
    // save them as members
    rpnLeft = fact.shuntingYard(left, table);
    rpnRight = fact.shuntingYard(right, table);
    Lexer lex;
    string line;
    bool end = false;
        // get the commands from the input stream
        while (getline(in, line)) {
            // when we get a line with { continue
            if (hasStart(line) && !startRev) {
                startRev = true;
                continue;
            } else {
                if (!startRev) {
                    // no start of scope error
                    break;
                }
            }
            // if we get a line with } we parse it and exit
            if (hasEnd(line)) {
                if (line.size() > 1) {
                    end = true;
                } else {
                    break;
                }
            }
            // parse the commands and hold them in a list.
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
    // check if the statment stands, if it does excecute it.
    if(checkStatment(table)) {
        list<vector<string>>::iterator iterator1 = aruments.begin();
        list<Command*>::iterator iterator2 = toExcecute.begin();
        // iterate both over commands and arguments and doCommand.
        while(iterator1 != aruments.end() && iterator2 != toExcecute.end()) {
            (*iterator2)->doCommand(*iterator1, server, table, outSockId, giver,
                    in);
            ++iterator1;
            ++iterator2;
        }
    }
    // if we are in a while command we don't want to clear we want to use it again
    if(!inWhile) {
        aruments.clear();
        toExcecute.clear();
        rpnLeft.clear();
        rpnRight.clear();
        comparator.clear();
    }
}
// use the string comparator and the table to calculate the value of expression and check statments.
bool ifCommand::checkStatment(symbolTable* table) {
    expressionFactory fact;
    // calculate the value of right and left.
    double valLeft = fact.RPNCalc(rpnLeft, table);
    double valRight = fact.RPNCalc(rpnRight, table);
    // chek what is the comparator and compare with it/
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