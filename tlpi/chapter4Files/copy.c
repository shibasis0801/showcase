#include<sys/stat.h>
#include<fcntl.h>
#include "tlpi_hdr.h"

#ifndef BUF_SIZE
#define BUF_SIZE 1024
#endif


int 
main(int argc, char *argv[]) {
    
    int inputFD, outputFD, openFlags;
    mode_t filePerms;
    ssize_t numRead;
    char buffer[BUF_SIZE];

    if (argc != 3 || strcmp("--help", argv[1]) == 0)
        usageErr("%s old-file new-file\n", argv[0]);

    inputFD = open(argv[1], O_RDONLY);
    if (inputFD == -1 )
        errExit("opening file %s", argv[1]);

    openFlags = O_CREAT | O_TRUNC | O_WRONLY;
    filePerms = S_IRUSR | S_IWUSR;

    outputFD = open(argv[2], openFlags, filePerms);
    if ( outputFD == -1 )
        errExit("opening file %s", argv[2]);

    while ( (numRead = read(inputFD, buffer, BUF_SIZE) ) > 0 ) 
        if( write(outputFD, buffer, numRead) != numRead )
            fatal("couldn't write whole buffer");
        
    
    if ( numRead == -1 )
        errExit("read");
    
    if ( close(inputFD) == -1 )
        errExit("close input");

    if ( close(outputFD) == -1 )
        errExit("close output");

    exit(EXIT_SUCCESS);
}