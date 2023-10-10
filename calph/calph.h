#ifndef CALPH_H
#define CALPH_H 1

#ifdef __unix
#define fopen_s(pFile, filename, mode) ((*(pFile))=fopen((filename), (mode)))==NULL
#endif

#define ERR_NO 0                // Successful: No Error
#define ERR_GENERIC 1
#define ERR_NOFILE 2            // Error: No File
#define ERR_NOARG 3             // Error: No Arguments given
#define ERR_NOLOGFILE 4         // Error: No log file location/name

#include <stdio.h>
#include <stdlib.h>

void help(int exitCode) {
    printf("\nUse: calph [options] [input]\n\n");
    printf("Available [options] are:\n\t\t\t--file\n\t\t\t\tTo open a file provided as filepath via [input].\n\t\t\t--text\n\t\t\t\tTo open text provided via [input]\n");
    exit(exitCode);
}

#endif