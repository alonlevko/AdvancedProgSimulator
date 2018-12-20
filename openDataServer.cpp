//
// Created by alon on 12/16/18.
//
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
void openDataServer::doCommand(vector <string> strings, DataReaderServer* server,
        symbolTable* table, int* outSockId, commandGiver* giver) {
    if(strings.size() != 2) {
        // no good arguments error
        return;
    }
    int sockfd, newsockfd, portno, clilen;
    char buffer[256];
    struct sockaddr_in serv_addr, cli_addr;
    int  n;

    /* First call to socket() function */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0) {
        perror("ERROR opening socket");
        exit(1);
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
        exit(1);
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
        exit(1);
    }
    thread t1(updateVals, newsockfd, wait, server, table);
    t1.detach();
}


 