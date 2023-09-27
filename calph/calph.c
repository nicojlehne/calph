#ifdef __unix
#define fopen_s(pFile, filename, mode) ((*(pFile))=fopen((filename), (mode)))==NULL
#endif

#define CALPH_VERSION "0.0.7"

#include <stdio.h>
#include <ctype.h>

#define ERR_NO 0                // Successful: No Error
#define ERR_GENERIC 1
#define ERR_NOFILE 2            // Error: No File
#define ERR_NOARG 3             // Error: No Arguments given

char characters[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
                'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', ' '};

unsigned int count[(sizeof(characters)/sizeof(*characters))] = {0};
              
FILE* file;

void counter() {  
    for (int i = 0; i < (sizeof(count) / sizeof(*count)); i++) {
        for (int get = getc(file); get != EOF; get = getc(file)) {
            if(get == characters[i] || get == toupper(characters[i]))
                count[i]++;
        }
        fseek(file, 0, SEEK_SET);
    }
}

int main(int argc, char** argv)
{

    if(!(argc > 1)) {
        printf("Not enough arguments given, use calph --help to see syntax\nExiting\n");
        return ERR_NOARG;
    }

    int err = fopen_s(&file, argv[1], "r");
    if (!(err == 0)) {
        printf("File doesn't exist or is otherwise unavailable\nTry supplying a (valid) filename\n");
        return ERR_NOFILE;
    }

    int sum, space;

    counter();
    size_t arraysize = sizeof(count) / sizeof(*count);
    for(int i = 0; i < arraysize; i++)
        sum+=count[i];
    sum = sum + space;

    for(int i = 0; i < arraysize; i++)
        printf("%c: %d\n", characters[i], count[i]);

    printf("Sum: %d characters\n", sum);

    printf("Sum (without spaces): %d characters\n", sum-count[sizeof(count) / sizeof(*count) - 1]);

    return ERR_NO;
}
