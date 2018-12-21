//
// Created by alon on 12/21/18.
//
#include <chrono>
#include <thread>
#include "sleepCommand.h"
void sleepCommand::doCommand(vector<string> strings, DataReaderServer* server,
               symbolTable* table, int* outSockId, commandGiver* giver) {
    if(strings.size() != 1) {
        //error in number of parameters
        return;
    }
    int milis = stoi(strings[0]);
    std::this_thread::sleep_for(std::chrono::milliseconds(milis));
}