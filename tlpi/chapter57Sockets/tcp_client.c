#include <errno.h>
#include <unistd.h>
#include <sys/un.h>
#include <sys/socket.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <netinet/in.h>

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
    const char* server_name = "localhost";
    const int server_port = 8000;
    struct sockaddr_in server_address;
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    inet_pton(AF_INET, server_name, &server_address.sin_addr);
    server_address.sin_port = htons(server_port);

    int serverFD;
    run(
        serverFD = socket(AF_INET, SOCK_STREAM, 0),
        exit_error("Server Socket opening failed")
    )
    
    run(
        connect(serverFD, (struct sockaddr *) &server_address, sizeof(struct sockaddr)),
        exit_error("Server Connection Failed")
    )

    const char *message = "Hello World";
    if (send(serverFD, message, strlen(message), 0) != strlen(message))
        log_error("incomplete send");

    char buffer[BUFSIZE];
    recv(serverFD, buffer, BUFSIZE, 0);
    write(STDOUT_FILENO, buffer, BUFSIZE);
    close(serverFD);

}