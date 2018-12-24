#include "DataReaderServer.h"
#include <map>
#include <string>
#include <sstream>
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <vector>
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
    // initialize the values map with the string names.
    for(int i = 1; i <= 23; i++) {
        values[names[i]] = 0;
    }
}
// get a value from the map only if the strings is correct
double DataReaderServer::getValue(string& s) {
    if(values.find(s) != values.end()) { // make sure the strings is in
        return values[s];
    } else{
        //throw value not in simulator error
        return 0;
    }
}
// set a new value for a string in the server
void DataReaderServer::setValue(double d, string& s) {
    values[s] = d;
}
// get a strings from the number of position in the xml
string DataReaderServer::getStringFromXMlLocation(int i) {
    return names[i];
}
// check if a string is in out list of strings/
bool DataReaderServer::isInList(string& s) {
    if(values.find(s) == values.end()) {
        return false;
    } else {
        return true;
    }
}
// static method that will run in a diffrent thread and update the values in the server reader.
void updateVals(int newsockfd, int timesPerSec, DataReaderServer* reader, symbolTable* table) {
    char buffer[400];
    bzero(buffer, 400);
    int n;
    while(true) { // keep running while we have a connection.
        // read values into the buffer
        n = read(newsockfd, buffer, 400);
        if (n <= 0) {
            // error reading from socket
            break;
        }
        // create a string stream from the buffer
        istringstream strm(buffer);
        double temp;
        string str;
        string str2;
        int i = 1;
        // get a line from the stream, the delimiter is ,
        while(getline(strm, str, ',')) {
            // save out number
            temp = stod(str);
            // get the right strings for the positions
            str2 = reader->getStringFromXMlLocation(i);
            // update the value.
            reader->setValue(temp, str2);
            i++;
        }
    }
    close(newsockfd);
}
