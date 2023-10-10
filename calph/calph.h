#ifndef CALPH_H
#define CALPH_H 1

// Headers
#define HEADERS (<stdio.h>)(<stdlib.h>)(<ctype.h>)(<string.h>)(<stdbool.h>)
#include "Headers.inl"

// Version
#define CALPH_VERSION "0.3.5"

// Error codes
static const int ERR_NO = 0;
static const int ERR_GENERIC = 1;
static const int ERR_NOFILE = 2;    // Error: No File
static const int ERR_NOARG = 3;     // Error: No arguments given
static const int ERR_NOLOGFILE = 4; // Error: No log file location/name

// Functions
void help(int);

void checkArgs(int, char **);

void checkFile(FILE*, int);

void counter(char *, char **);

void sumItUp(void);

#endif