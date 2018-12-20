//
// Created by alon on 12/16/18.
//

#ifndef ADVANCEDPROG_SIMULATORVALUES_H
#define ADVANCEDPROG_SIMULATORVALUES_H
#include <map>
#include <string>
#include <exception>
#include <sstream>
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <vector>
#include <thread>
#include "symbolTable.h"
#define MICRO_SECOND 100000
using namespace std;
class DataReaderServer {
private:
    map<string, double> values;
    map<int, string> names;
public:
    DataReaderServer();
    double getValue(string& s);
    void setValue(double d, string& s);
    string getStringFromXMlLocation(int i);
};
void updateVals(int newsockfd, int timesPerSecond, DataReaderServer* reader,
        symbolTable* table);
#endif //ADVANCEDPROG_SIMULATORVALUES_H
