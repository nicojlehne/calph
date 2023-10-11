#include "calph.h"

unsigned char characterArray[] = {' ', '!', '"', '#', '$', '%', '&', '\'', '(', ')', '*', '+', ',', '-', '.', '/', '0',
                     '1', '2', '3', '4', '5', '6', '7', '8', '9', ':', ';', '<', '=', '>', '?', '@',
                     'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
                     'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '[', '\\', ']', '^', '_', '`',
                     '{', '|', '}', '~'};
unsigned int count[(sizeof(characterArray)/sizeof(*characterArray))] = {0};
size_t countArraySize = sizeof(count) / sizeof(*count);
unsigned int sum = 0;
unsigned int yep = 0;
              
FILE* file; FILE* logfile;

bool logFileProvided = 0;
bool debug = 0;

void help(int exitCode) {
    printf("\nUse: calph [options] [input]\n\n");
    printf("Available [options] are:\n\
        \t\t\t--file\n\
        \t\t\t\tTo open a file provided as filepath via [input].\n\
        \t\t\t--text\n\
        \t\t\t\tTo open text provided via [input]\n\
        \t\t\t--help\n\
        \t\t\t\tTo open this\n\n");
    exit(exitCode);
}

void errorHandler(int exitCode) {
    switch (exitCode) {
        case ERR_NOFILE:
            printf("File does not exist or is otherwise unavailable\n\
            Try supplying a (valid) filename\n");
            break;
        case ERR_NOLOGFILE:
            printf("No (valid) location/name for output logfile provided\n");
            break;
        case ERR_NOARG:
            printf("Not enough arguments given, use calph --help or calph -h to see syntax\n");
        default:
            break;
    }
}

void argumentHandler(int argc, char ** argv) {
    if (!(argc > 1)) errorHandler(ERR_NOARG);
    if (argc > 3) {
        if (strcmp(argv[3], "--log") == 0 || strcmp(argv[3], "-l") == 0) {  // Lowercase 'L', neither the number '1' or uppercase 'i'
            int err = fopen_s(&logfile, argv[4], "a");
            if (!(err == 0)) errorHandler(ERR_NOLOGFILE);
            logFileProvided = 1;
        }
    }
}

int fileHandler(char ** argv) {
    int err = fopen_s(&file, argv[2], "r");
        if (!(err == 0)) errorHandler(ERR_NOFILE);
    return 1;
}

void yepHandler(bool debug, char * fileLocation, const char * functionLocation, int lineLocation) {
    if(debug) {
        printf("Yep (%d)[%s, %s, %d]\n", yep, fileLocation, functionLocation, lineLocation);
        yep++;
    }
}

void counter(char * mode, char ** argv) {
    yepHandler(debug, (__FILE__), (__FUNCTION__), (__LINE__));
    if (strcmp(mode, "--file") == 0 || strcmp(mode, "-f") == 0) { if (fileHandler(argv)) for (int i = 0; i < (countArraySize); i++) {
            for (int get = getc(file); get != EOF; get = getc(file)) if (get == characterArray[i] || get == toupper(characterArray[i])) count[i]++;
            fseek(file, 0, SEEK_SET);
        }
        yepHandler(debug, (__FILE__), (__FUNCTION__), (__LINE__));
    } else if (strcmp(mode, "--text") == 0) {
        yepHandler(debug, (__FILE__), (__FUNCTION__), (__LINE__));
        for (int i = 0; i < (countArraySize); i++) {
            if (argv[2] == NULL) argv[2] = argv[1];
            for (int k = 0; k < strlen(argv[2]); k++) {
                char character = argv[2][k];
                if (character == characterArray[i] || character == toupper(characterArray[i])) count[i]++;
            }
            yepHandler(debug, (__FILE__), (__FUNCTION__), (__LINE__));
        }
    }
}

void sumItUp() {
    for (int i = 0; i < countArraySize; i++) {
        sum+=count[i];
        if (!(count[i] == 0)) {
            printf("%c: %d\n", characterArray[i], count[i]);
            if (logFileProvided) fprintf(logfile, "%c: %d\n", characterArray[i], count[i]);
        }
    }
    printf("Sum: %d characters\nSum (without spaces): %d characters\n", sum, sum-count[0]);
    if (logFileProvided) fprintf(logfile, "Sum: %d characters\nSum (without spaces): %d characters\n", sum, sum-count[0]);
}