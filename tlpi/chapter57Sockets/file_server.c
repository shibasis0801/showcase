/*

To create a SOCK_STREAM server

1 Create Socket
2 Create Server Address
3 Bind Socket to Server Address
4 Start Listening
5 Accept Incoming Connections
6 Shutdown

*/
#include <errno.h>
#include <unistd.h>
#include <sys/un.h>
#include <sys/socket.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include<sys/stat.h>
#include<fcntl.h>

#define BACKLOG 5
#define BUFSIZE 1024
#define TMP_FILE_LOCATION "/tmp/overlord_unix_server"

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
    
    // Create Socket - 1
    int serverFD; 
    run(
        serverFD = socket(AF_UNIX, SOCK_STREAM, 0),
        exit_error("Failed Socket Creation")
    )

    // Set Server Address - 2
    struct sockaddr_un server_address;
    memset(&server_address, 0, sizeof(server_address));
    server_address.sun_family = AF_UNIX;
    strncpy(server_address.sun_path, TMP_FILE_LOCATION, sizeof(server_address.sun_path) - 1);

    // If file exists, remove - 3.1
    if (remove(TMP_FILE_LOCATION) == -1 && errno != ENOENT)
        exit_error("Please Remove TMP_FILE_LOCATION");
    // Bind address to server - 3.2
    run(
        bind(serverFD, (struct sockaddr *) &server_address, sizeof(struct sockaddr)),
        exit_error("Server Binding Failed")
    )

    // Set Backlog(Kernel Queue depth for pending connections) as you start listening for client connections - 4
    run(
        listen(serverFD, BACKLOG),
        exit_error("Listening on Server Failed")
    )

    // Infinite Loop to connect to clients - 5
    int clientFD;
    ssize_t bytesRead;
    char filename[BUFSIZE];
    while(1) {
        run(
            clientFD = accept(serverFD, NULL, NULL),
            exit_error("Client Connection Accepting Failed")
        )

        memset(&filename, 0, BUFSIZE);
        while ( (bytesRead = read(clientFD, filename, BUFSIZE)) > 0 ) {
            int fileDescriptor;
            run(
                fileDescriptor = open(filename, O_RDONLY),
                exit_error("Couldn't Open File")
            )

            ssize_t numRead;
            char buffer[BUFSIZE];
    
            while ( (numRead = read(fileDescriptor, buffer, BUFSIZE) ) > 0 ) 
                if( write(clientFD, buffer, numRead) != numRead )
                    log_error("couldn't write whole buffer");
            
            memset(&filename, 0, BUFSIZE);
            run(close(fileDescriptor), log_error("Client FD not closed"))        
        }
            
    }

    // Shutdown - 6
    run(close(clientFD), log_error("Client FD not closed"))
    run(close(serverFD), log_error("Server FD not closed"))
    run(bytesRead, log_error("Failed/Partial Read")) 
}
