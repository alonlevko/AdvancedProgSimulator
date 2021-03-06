#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <thread>
#include <sstream>
#include <iostream>
#include "openDataServer.h"
#include "DataReaderServer.h"
// open a data servet and then call a thread to run it.
bool openDataServer::doCommand(vector <string> strings, DataReaderServer* server,
        symbolTable* table, int* outSockId, commandGiver* giver, istream& in) {
    // make sure we have 2 arguments only
    if(strings.size() != 2) {
        // no good arguments error
        return false;
    }
    // the generic code to open a sever.
    int sockfd, newsockfd, portno, clilen;
    struct sockaddr_in serv_addr, cli_addr;

    /* First call to socket() function */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0) {
        perror("ERROR opening socket");
        return false;
    }

    /* Initialize socket structure */
    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = stoi(strings[0]); // the first parameter is the port num

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);

    /* Now bind the host address using bind() call.*/
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        perror("ERROR on binding");
        return false;
    }

    /* Now start listening for the clients, here process will
       * go in sleep mode and will wait for the incoming connection
    */
    int wait = stoi(strings[1]);
    listen(sockfd,5);
    clilen = sizeof(cli_addr);

    /* Accept actual connection from the client */
    newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, (socklen_t*)&clilen);
    //printf("connection made");
    if (newsockfd < 0) {
        perror("ERROR on accept");
        return false;
    }
    char buffer[400];
    bzero(buffer, 400);
    int n;
    while(true) {
        n = read(newsockfd, buffer, 400);
        if (n > 0) {
            //the connection has been made and we can continue
            break;
        }
    }
    // create a new thread that will update the values from the simulator
    thread t1(updateVals, newsockfd, wait, server, table);
    // let it run seperatly from the main code.
    t1.detach();
    return true;
}


 