#ifndef CALPH_H
#define CALPH_H 1

#ifdef __unix
#define fopen_s(pFile, filename, mode) ((*(pFile))=fopen((filename), (mode)))==NULL
#endif

// Headers
#define HEADERS (<stdio.h>)(<stdlib.h>)(<ctype.h>)(<string.h>)(<stdbool.h>)
#include "Headers.inl"

// Version
#define CALPH_VERSION "0.3.6"

// Error codes
static const int ERR_NO = 0;
static const int ERR_GENERIC = 1;
static const int ERR_NOFILE = 2;    // Error: No File
static const int ERR_NOARG = 3;     // Error: No arguments given
static const int ERR_NOLOGFILE = 4; // Error: No log file location/name

// Functions
void help(int);

void errorHandler(int);

void argumentHandler(int, char **);

int fileHandler(char **);

void yepHandler(bool, char *, const char *, int);

void counter(char *, char **);

void sumItUp(void);

#endif