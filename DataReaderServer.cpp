//
// Created by alon on 12/18/18.
//
#include "DataReaderServer.h"
#include <map>
#include <string>
#include <sstream>
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <vector>
#define MICRO_SECOND 100000
DataReaderServer fromServer;
DataReaderServer::DataReaderServer() {
    // map all of the strings of variables to numbers
    names[1] = "/instrumentation/airspeed-indicator/indicated-speed-kt";
    names[2] = "/instrumentation/altimeter/indicated-altitude-ft";
    names[3] = "/instrumentation/altimeter/pressure-alt-ft";
    names[4] = "/instrumentation/attitude-indicator/indicated-pitch-deg";
    names[5] = "/instrumentation/attitude-indicator/indicated-roll-deg";
    names[6] = "/instrumentation/attitude-indicator/internal-pitch-deg";
    names[7] = "/instrumentation/attitude-indicator/internal-roll-deg";
    names[8] = "/instrumentation/encoder/indicated-altitude-ft";
    names[9] = "/instrumentation/encoder/pressure-alt-ft";
    names[10] = "/instrumentation/gps/indicated-altitude-ft";
    names[11] = "/instrumentation/gps/indicated-ground-speed-kt";
    names[12] = "/instrumentation/gps/indicated-vertical-speed";
    names[13] = "/instrumentation/heading-indicator/indicated-heading-deg";
    names[14] = "/instrumentation/magnetic-compass/indicated-heading-deg";
    names[15] = "/instrumentation/slip-skid-ball/indicated-slip-skid";
    names[16] = "/instrumentation/turn-indicator/indicated-turn-rate";
    names[17] = "/instrumentation/vertical-speed-indicator/indicated-speed-fpm";
    names[18] = "/controls/flight/aileron";
    names[19] = "/controls/flight/elevator";
    names[20] = "/controls/flight/rudder";
    names[21] = "/controls/flight/flaps";
    names[22] = "/controls/engines/engine/throttle";
    names[23] = "/engines/engine/rpm";
    for(int i = 1; i <= 23; i++) {
        values[names[i]] = 0;
    }
}
double DataReaderServer::getValue(string& s) {
    if(values.find(s) != values.end()) {
        return values[s];
    } else{
        //throw value not in simulator error
        return 0;
    }
}
void DataReaderServer::setValue(double d, string& s) {
    //cout << d << endl;
    values[s] = d;
    //cout << "set " << s << " as: " << d <<endl;
}
string DataReaderServer::getStringFromXMlLocation(int i) {
    return names[i];
}
bool DataReaderServer::isInList(string& s) {
    if(values.find(s) == values.end()) {
        return false;
    } else {
        return true;
    }
}

void updateVals(int newsockfd, int timesPerSec, DataReaderServer* reader, symbolTable* table) {
    char buffer[300];
    bzero(buffer, 300);
    int n;
    while(true) {
        n = read(newsockfd, buffer, 300);
        if (n <= 0) {
            // error reading from socket
            exit(1);
        }
        //cout << buffer;
        istringstream strm(buffer);
        //string line;
        //vector<double> vec;
        double temp;
        string str;
        string str2;
        int i = 1;
        //for(int i = 0; i < 23; i++) {
        while(getline(strm, str, ',')) {
            temp = stod(str);
            //cout << temp;
            str2 = reader->getStringFromXMlLocation(i);
            reader->setValue(temp, str2);
            //table->updateFromServer(str2, temp);
            //vec.push_back(temp);
            i++;
        }
        //strm.clear();
        //usleep(MICRO_SECOND/timesPerSecond);
    }
}
