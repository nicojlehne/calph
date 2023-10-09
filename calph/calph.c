#ifdef __unix
#define fopen_s(pFile, filename, mode) ((*(pFile))=fopen((filename), (mode)))==NULL
#endif

#define CALPH_VERSION "0.3.0"

#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define ERR_NO 0                // Successful: No Error
#define ERR_GENERIC 1
#define ERR_NOFILE 2            // Error: No File
#define ERR_NOARG 3             // Error: No Arguments given

char characters[] = {' ', '!', '"', '#', '$', '%', '&', '\'', '(',
                     ')', '*', '+', ',', '-', '.', '/', '0',
                     '1', '2', '3', '4', '5', '6', '7', '8',
                     '9', ':', ';', '<', '=', '>', '?', '@',
                     'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h',
                     'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
                     'q', 'r', 's', 't', 'u', 'v', 'w', 'x',
                     'y', 'z', '[', '\\', ']', '^', '_', '`',
                     '{', '|', '}', '~'};
unsigned int count[(sizeof(characters)/sizeof(*characters))] = {0};
size_t countArraySize = sizeof(count) / sizeof(*count);
              
FILE* file;

void help() {
    printf("\nUse: calph [options] [input]\n\n");
    printf("Available [options] are:\n\t\t\t--file\n\t\t\t\tTo open a file provided as filepath via [input].\n\t\t\t--text\n\t\t\t\tTo open text provided via [input]\n");
}

void counter(char * mode, char ** argv) {  
    if (strcmp(mode, "file") == 0) {
        for (int i = 0; i < (countArraySize); i++) {
            for (int get = getc(file); get != EOF; get = getc(file))
                if(get == characters[i] || get == toupper(characters[i]))
                    count[i]++;
            fseek(file, 0, SEEK_SET);
        }
    } else if (strcmp(mode, "text") == 0) {
        for (int i = 0; i < (countArraySize); i++) {
            if(argv[2] == NULL)
                argv[2] = argv[1];
            for (int k = 0; k < strlen(argv[2]); k++) {
                char character = argv[2][k];
                if(character == characters[i] || character == toupper(characters[i]))
                    count[i]++;
            }
        }
    }
}

int main(int argc, char** argv) {
    if(!(argc > 1)) {
        printf("Not enough arguments given, use calph --help or calph -h to see syntax\nExiting\n");
        return ERR_NOARG;
    }

    int sum;

    if (strcmp(argv[1], "--file") == 0 || strcmp(argv[1], "-f") == 0) {
        int err = fopen_s(&file, argv[2], "r");
        if (!(err == 0)) {
            printf("File doesn't exist or is otherwise unavailable\nTry supplying a (valid) filename\n");
            return ERR_NOFILE;
        }
        counter("file", argv);
    } else if (strcmp(argv[1], "--text") == 0 || strcmp(argv[1], "-t") == 0) {
        counter("text", argv);
    } else if (strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0) {
        help();
        return 0;
    } else {
        counter("text", argv);
    }

    for(int i = 0; i < countArraySize; i++) {
        sum+=count[i];
        if(!(count[i] == 0))
            printf("%c: %d\n", characters[i], count[i]);
    }
    printf("Sum: %d characters\n", sum);
    printf("Sum (without spaces): %d characters\n", sum-count[0]);

    if (file != NULL)
        fclose(file);
    return ERR_NO;
}
