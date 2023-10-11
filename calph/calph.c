#include "calphimpl.c"

int main(int argc, char** argv) {
    argumentHandler(argc, argv);

    if (argv[1][0] == '-') if (strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0) help(0); else counter(argv[1], argv); else counter("--text", argv);

    sumItUp();

    if (file != NULL) fclose(file);
    return ERR_NO;
}
