#ifndef CALPH_H
#define CALPH_H 1

#define HEADERS (<stdio.h>)(<stdlib.h>)(<ctype.h>)(<string.h>)(<stdbool.h>)
#include "Headers.inl"

#ifdef __unix
#define fopen_s(pFile, filename, mode) ((*(pFile))=fopen((filename), (mode)))==NULL
#endif

#define CALPH_VERSION "0.3.3"

#define ERR_NO 0                // Successful: No Error
#define ERR_GENERIC 1
#define ERR_NOFILE 2            // Error: No File
#define ERR_NOARG 3             // Error: No Arguments given
#define ERR_NOLOGFILE 4         // Error: No log file location/name

#include <stdio.h>
#include <stdlib.h>

void help(int exitCode) {
    if (exitCode == 0) {
        printf("\nUse: calph [options] [input]\n\n");
        printf("Available [options] are:\n\t\t\t--file\n\t\t\t\tTo open a file provided as filepath via [input].\n\t\t\t--text\n\t\t\t\tTo open text provided via [input]\n");
    } else if (exitCode == ERR_NOFILE)
        printf("File does not exist or is otherwise unavailable\nTry supplying a (valid) filename\n");
    else if (exitCode == ERR_NOLOGFILE)
        printf("No (valid) location/name for output logfile provided\n");
    exit(exitCode);
}

#endif