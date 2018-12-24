#ifndef ADVANCEDPROG_OPENDATASERVER_H
#define ADVANCEDPROG_OPENDATASERVER_H
#include <vector>
#include <string>
#include "command.h"
using namespace std;
class openDataServer: public Command {
public:
    void doCommand(vector<string> strings, DataReaderServer* reader,
            symbolTable* table, int* outSockId, commandGiver* giver, istream& in);
};
#endif //ADVANCEDPROG_OPENDATASERVER_H
