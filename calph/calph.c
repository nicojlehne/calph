#ifdef __unix
#define fopen_s(pFile, filename, mode) ((*(pFile))=fopen((filename), (mode)))==NULL
#endif

#define CALPH_VERSION "0.0.6"

#include <stdio.h>
#include <ctype.h>

#define ERR_NO 0                // Successful: No Error
#define ERR_GENERIC 1
#define ERR_NOFILE 2            // Error: No File
#define ERR_NOARG 3             // Error: No Arguments given


unsigned int count[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

char characters[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
                'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', ' '};
              
FILE* file;

// Counts all symbols in the given file
void counter() {  
    int get;
    for (int i = 0; i < (sizeof(count) / sizeof(count[0])); i++) {
        for (get = getc(file); get != EOF; get = getc(file)) {
            char character = characters[i];
            if(get == character || get == toupper(character))
                count[i]++;
        }
        fseek(file, 0, SEEK_SET);
    }
}

int main(int argc, char** argv)
{

    if (argc > 1)
        ;
    else {
        printf("Not enough arguments given, use calph --help to see syntax\nExiting\n");
        return ERR_NOARG;
    }

    // Tests if given file exists
    int err = fopen_s(&file, argv[1], "r");
    if (err == 0)
        ;
    else {
        printf("File doesn't exist or is otherwise unavailable\nTry supplying a (valid) filename\n");
        return ERR_NOFILE;
    }
    //

    int sum;
    int space;

    counter();
    size_t arraysize = sizeof(count) / sizeof(count[0]);
    for(int i = 0; i < arraysize; i++)
        sum+=count[i];
    sum = sum + space;
    // Show user how many of each alphabetical character are in the given file
    for(int i = 0; i < arraysize; i++)
        printf("%c: %d\n", characters[i], count[i]);
    printf("Sum: %d characters\n", sum);
    // Show user how many of each character are in the given file excluding spaces
    printf("Sum (without spaces): %d characters\n", sum-count[26]);

    return ERR_NO;
}
