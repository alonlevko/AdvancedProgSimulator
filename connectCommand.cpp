//
// Created by alon on 12/18/18.
//

#include "connectCommand.h"
#include <stdio.h>
#include <stdlib.h>

#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>

#include <string.h>
int outSockedId;
using namespace std;
void connectCommand::doCommand(vector<string> strings, DataReaderServer* reader,
        symbolTable* table, int* outSockId, commandGiver* giver) {
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    char buffer[] = "i am the king";
    if (strings.size() != 2) {
        // bad arguments error
        exit(0);
    }
    portno = stoi(strings[1]);

    /* Create a socket point */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0) {
        perror("ERROR opening socket");
        exit(1);
    }

    server = gethostbyname(strings[0].c_str());

    if (server == NULL) {
        fprintf(stderr, "ERROR, no such host\n");
        exit(0);
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *) server->h_addr, (char *) &serv_addr.sin_addr.s_addr,
          server->h_length);
    serv_addr.sin_port = htons(portno);

    /* Now connect to the server */
    if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) <
        0) {
        perror("ERROR connecting");
        exit(1);
    }
    *(outSockId) = sockfd;
    /* Send message to the server */

    n = write(sockfd, buffer, strlen(buffer));
    if (n <= 0) {
        perror("ERROR writing to socket");
        exit(1);
    }

    /* Now ask for a message from the user, this message
       * will be read by server
    */
}
