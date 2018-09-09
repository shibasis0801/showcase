#include <errno.h>
#include <unistd.h>
#include <sys/un.h>
#include <sys/socket.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define BACKLOG 5
#define BUFSIZE 1024
#define TMP_FILE_LOCATION "/tmp/overlord_unix_datagram"

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


int main(int argc, char **argv) {

    int serverFD, j;
    run(
        serverFD = socket(AF_UNIX, SOCK_DGRAM, 0),
        exit_error("Creating Socket Failed")
    )

    if (remove(TMP_FILE_LOCATION) == -1 && errno != ENOENT) 
        exit_error("Please delete TMP_FILE_LOCATION");

    struct sockaddr_un server_address;
    memset(&server_address, 0, sizeof(server_address));
    server_address.sun_family = AF_UNIX;
    strncpy(server_address.sun_path, TMP_FILE_LOCATION, sizeof(server_address.sun_path) - 1);

    run(
        bind(serverFD, (struct sockaddr *) &server_address, sizeof(struct sockaddr)),
        exit_error("Failed Binding")
    )

    struct sockaddr_un client_address;
    ssize_t bytesRead;
    socklen_t len;
    char buffer[BUFSIZE];
    while(1) {
        len = sizeof(struct sockaddr_un);
        bytesRead = recvfrom(serverFD, buffer, BUFSIZE, 0, 
                        (struct sockaddr *) &client_address, sizeof(struct sockaddr));
        run(bytesRead, exit_error("recvfrom failed"));

        printf("Server recieved %ld bytes from %s\n", (long) bytesRead, client_address.sun_path);

        for(int j = 0; j < bytesRead; ++j) 
            buffer[j] = toupper((unsigned char) buffer[j]);

        if (sendto(serverFD, buffer, BUFSIZE, 0, (struct sockaddr *) &client_address, sizeof(struct sockaddr))
            != bytesRead) 
                log_error("Error in sending to client");
    }
}







