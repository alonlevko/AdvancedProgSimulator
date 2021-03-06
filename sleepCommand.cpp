
#include <chrono>
#include <thread>
#include "sleepCommand.h"
bool sleepCommand::doCommand(vector<string> strings, DataReaderServer* server,
               symbolTable* table, int* outSockId, commandGiver* giver, istream& in) {
    if(strings.size() != 1) {
        //error in number of parameters
        return true;
    }
    // save the number that was inputed
    int milis = stoi(strings[0]);
    // sleep command
    std::this_thread::sleep_for(std::chrono::milliseconds(milis));
    return true;
}