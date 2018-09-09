/*

To create a SOCK_STREAM server

1 Create Socket
2 Create Server Address
3 Bind Socket to Server Address
4 Start Listening
5 Accept Incoming Connections
6 Shutdown

*/
#include <arpa/inet.h>
#include <netinet/in.h>
#include <errno.h>
#include <unistd.h>
#include <sys/un.h>
#include <sys/socket.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define BACKLOG 5
#define BUFSIZE 1024

/* 
Blocked Run to allow multiline macro expansion
Runs a statement and since many library functions return -1 on error, 
has a callback like functionality for that.
*/ 

#define run(statement, onMinusOne) { \
    if ( (statement) == -1 )         \
        onMinusOne;                  \
}

void 
log_error(const char* const message) {
    fprintf(stderr, "%s", message);
}

void 
exit_error(const char* const message) {
    fprintf(stderr, "%s", message);
    exit(-1);
}

int main() {
    int serverFD;
    run(
        serverFD = socket(AF_INET, SOCK_STREAM, 0),
        exit_error("Socket Creation Failed")
    )

    int server_port = 8000;
    struct sockaddr_in server_address;
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(server_port);
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);

    run(
        bind(serverFD, (struct sockaddr *) &server_address, sizeof(struct sockaddr)),
        exit_error("Socket Binding Failed")
    )

    run(
        listen(serverFD, BACKLOG),
        exit_error("Listening Error")
    )

    struct sockaddr_in client_address; 
    int clientFD;
    ssize_t bytesRead;
    char buffer[BUFSIZE];
    while(1) {
        run(
            clientFD = accept(serverFD, (struct sockaddr *) &client_address, sizeof(struct sockaddr)),
            exit_error("Client Connection Failed")
        )
        
        
        while( (bytesRead = recv(clientFD, buffer, BUFSIZE, 0)) > 0 ) {
            if ( send(clientFD, buffer, bytesRead, 0) != bytesRead ) {
                log_error("Incomplete Write\n");
            } 
            else {
                printf("Echoed : ");
                write(STDOUT_FILENO, buffer, bytesRead);
            }   
        }
        run(close(clientFD), exit_error("Client Connection Closing Failed"))
    }
    run(close(serverFD), exit_error("Server Closing Failed"));
}