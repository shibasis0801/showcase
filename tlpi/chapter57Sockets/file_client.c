#include <unistd.h>
#include <sys/un.h>
#include <sys/socket.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFSIZE 1024
#define TMP_FILE_LOCATION "/tmp/overlord_unix_stream"


#define run(statement, onMinusOne) { \
    if ( (statement) == -1 )         \
        onMinusOne;                  \
}

//errno gets fucked. 

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

    // Get Server Socket
    int serverFD;
    run(
        serverFD = socket(AF_UNIX, SOCK_STREAM, 0),
        exit_error("Socket Creation Failed")
    );

    
    struct sockaddr_un server_address;
    // Null terminated string happens automatically due to memset and size - 1 later.
    memset(&server_address, 0, sizeof(server_address));
    server_address.sun_family = AF_UNIX;
    strncpy(server_address.sun_path, TMP_FILE_LOCATION, sizeof(server_address.sun_path) - 1 );

    
    run(
        connect(serverFD, (struct sockaddr *) &server_address, sizeof(struct sockaddr)),
        exit_error("Server Setup With File Failed")
    )


    char buffer[BUFSIZE];
    ssize_t bytesRead;
    while( (bytesRead = read(STDIN_FILENO, buffer, BUFSIZE)) > 0 )
        if ( write(serverFD, buffer, bytesRead) != bytesRead )
            log_error("Failed/Partial Write");

    run(bytesRead, log_error("Failed Read"));
    run(close(serverFD), log_error("Failed Server Close"))
}