#ifdef __unix
#define fopen_s(pFile, filename, mode) ((*(pFile))=fopen((filename), (mode)))==NULL
#endif

#include "calph.h"

char characters[] = {' ', '!', '"', '#', '$', '%', '&', '\'', '(', ')', '*', '+', ',', '-', '.', '/', '0',
                     '1', '2', '3', '4', '5', '6', '7', '8', '9', ':', ';', '<', '=', '>', '?', '@',
                     'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
                     'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '[', '\\', ']', '^', '_', '`',
                     '{', '|', '}', '~'};
unsigned int count[(sizeof(characters)/sizeof(*characters))] = {0};
size_t countArraySize = sizeof(count) / sizeof(*count);
unsigned int sum = 0;
              
FILE* file; FILE* logfile;

bool logFileProvided = 0;

void help(int exitCode) {
    if (exitCode == 0) {
        printf("\nUse: calph [options] [input]\n\n");
        printf("Available [options] are:\n\t\t\t--file\n\t\t\t\tTo open a file provided as filepath via [input].\n\t\t\t--text\n\t\t\t\tTo open text provided via [input]\n");
    } else if (exitCode == ERR_NOFILE) printf("File does not exist or is otherwise unavailable\nTry supplying a (valid) filename\n");
    else if (exitCode == ERR_NOLOGFILE) printf("No (valid) location/name for output logfile provided\n");
    else if (exitCode == ERR_NOARG) printf("Not enough arguments given, use calph --help or calph -h to see syntax\n");
    exit(exitCode);
}

void checkArgs(int argc, char ** argv) {
    if (!(argc > 1)) help(ERR_NOARG);
    if (argc > 3) {
        if (strcmp(argv[3], "--log") == 0 || strcmp(argv[3], "-l") == 0) {  // Lowercase 'L', neither the number '1' or uppercase 'i'
            int err = fopen_s(&logfile, argv[4], "a");
            if (!(err == 0)) help(ERR_NOLOGFILE);
            logFileProvided = 1;
        }
    }
}

void checkFile(FILE* file, int exitCode) {
    help(exitCode);
}

void counter(char * mode, char ** argv) {
    if (strcmp(mode, "file") == 0) for (int i = 0; i < (countArraySize); i++) {
            for (int get = getc(file); get != EOF; get = getc(file)) if (get == characters[i] || get == toupper(characters[i])) count[i]++;
            fseek(file, 0, SEEK_SET);
        }
    else if (strcmp(mode, "text") == 0) {
        for (int i = 0; i < (countArraySize); i++) {
            if (argv[2] == NULL) argv[2] = argv[1];
            for (int k = 0; k < strlen(argv[2]); k++) {
                char character = argv[2][k];
                if (character == characters[i] || character == toupper(characters[i])) count[i]++;
            }
        }
    }
}

void sumItUp() {
    for (int i = 0; i < countArraySize; i++) {
        sum+=count[i];
        if (!(count[i] == 0)) {
            printf("%c: %d\n", characters[i], count[i]);
            if (logFileProvided) fprintf(logfile, "%c: %d\n", characters[i], count[i]);
        }
    }
}