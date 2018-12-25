#include "connectCommand.h"
#include <stdio.h>
#include <stdlib.h>

#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>

#include <string.h>
using namespace std;
// this command connects us as a client to the simulator and sets the socketid
bool connectCommand::doCommand(vector<string> strings, DataReaderServer* reader,
        symbolTable* table, int* outSockId, commandGiver* giver, istream& in) {
    // the general client code
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    char buffer[] = "i am the king";
    if (strings.size() != 2) {
        // bad arguments error
        return false;
    }
    portno = stoi(strings[1]);

    /* Create a socket point */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0) {
        perror("ERROR opening socket");
        return false;
    }

    // get the host
    server = gethostbyname(strings[0].c_str());

    if (server == NULL) {
        fprintf(stderr, "ERROR, no such host\n");
        return false;
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
        return false;
    }
    // set the socket to be the correct socket number/
    *(outSockId) = sockfd;
}
