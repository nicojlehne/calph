#define CALPH_VERSION "0.3.2"

#define HEADERS (<stdio.h>)(<stdlib.h>)(<ctype.h>)(<string.h>)(<stdbool.h>)("calph.h")
#include "Headers.inl"

char characters[] = {' ', '!', '"', '#', '$', '%', '&', '\'', '(', ')', '*', '+', ',', '-', '.', '/', '0',
                     '1', '2', '3', '4', '5', '6', '7', '8', '9', ':', ';', '<', '=', '>', '?', '@',
                     'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
                     'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '[', '\\', ']', '^', '_', '`',
                     '{', '|', '}', '~'};
unsigned int count[(sizeof(characters)/sizeof(*characters))] = {0};
size_t countArraySize = sizeof(count) / sizeof(*count);
unsigned int sum = 0;
              
FILE* file;
FILE* logfile;

bool logFileProvided = 0;

void counter(char * mode, char ** argv) {
    if (strcmp(mode, "file") == 0) {
        for (int i = 0; i < (countArraySize); i++) {
            for (int get = getc(file); get != EOF; get = getc(file)) if (get == characters[i] || get == toupper(characters[i])) count[i]++;
            fseek(file, 0, SEEK_SET);
        }
    } else if (strcmp(mode, "text") == 0) {
        for (int i = 0; i < (countArraySize); i++) {
            if (argv[2] == NULL) argv[2] = argv[1];
            for (int k = 0; k < strlen(argv[2]); k++) {
                char character = argv[2][k];
                if (character == characters[i] || character == toupper(characters[i])) count[i]++;
            }
        }
    }
}

int main(int argc, char** argv) {
    if (!(argc > 1)) {
        printf("Not enough arguments given, use calph --help or calph -h to see syntax\nExiting\n");
        return ERR_NOARG;
    }

    if (strcmp(argv[1], "--file") == 0 || strcmp(argv[1], "-f") == 0) {
        int err = fopen_s(&file, argv[2], "r");
        if (!(err == 0)) {
            printf("File doesn't exist or is otherwise unavailable\nTry supplying a (valid) filename\n");
            return ERR_NOFILE;
        }
        counter("file", argv);
    } else if (strcmp(argv[1], "--text") == 0 || strcmp(argv[1], "-t") == 0) counter("text", argv);
    else if (strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0) help(0);
    else counter("text", argv);

    if (argc > 3) {
        if (strcmp(argv[3], "--log") == 0 || strcmp(argv[3], "-l") == 0) {
            int err = fopen_s(&logfile, argv[4], "a");
            if (!(err == 0)) {
                printf("No (valid) location/name for output logfile provided\n");
                return ERR_NOLOGFILE;
            }
            logFileProvided = 1;
        }
    }

    for (int i = 0; i < countArraySize; i++) {
        sum+=count[i];
        if (!(count[i] == 0)) {
            printf("%c: %d\n", characters[i], count[i]);
            if (logFileProvided) fprintf(logfile, "%c: %d\n", characters[i], count[i]);
        }
    }
    printf("Sum: %d characters\nSum (without spaces): %d characters\n", sum, sum-count[0]);
    if (logFileProvided) fprintf(logfile, "Sum: %d characters\nSum (without spaces): %d characters\n", sum, sum-count[0]);

    if (file != NULL) fclose(file);
    return ERR_NO;
}
