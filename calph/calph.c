#include "calphimpl.c"

int main(int argc, char** argv) {
    checkArgs(argc, argv);

    if (strcmp(argv[1], "--file") == 0 || strcmp(argv[1], "-f") == 0) {
        int err = fopen_s(&file, argv[2], "r");
        if (!(err == 0)) help(ERR_NOFILE);
        counter("file", argv);
    } else if (strcmp(argv[1], "--text") == 0 || strcmp(argv[1], "-t") == 0) counter("text", argv);
    else if (strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0) help(0);
    else counter("text", argv);

    sumItUp();
    printf("Sum: %d characters\nSum (without spaces): %d characters\n", sum, sum-count[0]);
    if (logFileProvided) fprintf(logfile, "Sum: %d characters\nSum (without spaces): %d characters\n", sum, sum-count[0]);

    if (file != NULL) fclose(file);
    return ERR_NO;
}
