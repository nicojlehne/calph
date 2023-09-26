#ifdef __unix
#define fopen_s(pFile, filename, mode) ((*(pFile))=fopen((filename), (mode)))==NULL
#endif

#define CALPH_VERSION "0.0.1"

#include <stdio.h>

#define ERR_NO 0                // Successful: No Error
#define ERR_GENERIC 1
#define ERR_NOFILE 2            // Error: No File
#define ERR_NOARG 3             // Error: No Arguments given

int a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z = 0;
int space = 0;
int get;
FILE* file;

// Counts all symbols in the given file
void count() {
    for (get = getc(file); get != EOF; get = getc(file)) {
        switch (get) {
        case 'a':
        case 'A':
            a++;
            break;
        case 'b':
        case 'B':
            b++;
            break;
        case 'c':
        case 'C':
            c++;
            break;
        case 'd':
        case 'D':
            d++;
            break;
        case 'e':
        case 'E':
            e++;
            break;
        case 'f':
        case 'F':
            f++;
            break;
        case 'g':
        case 'G':
            g++;
            break;
        case 'h':
        case 'H':
            h++;
            break;
        case 'i':
        case 'I':
            i++;
            break;
        case 'j':
        case 'J':
            j++;
            break;
        case 'k':
        case 'K':
            k++;
            break;
        case 'l':
        case 'L':
            l++;
            break;
        case 'm':
        case 'M':
            m++;
            break;
        case 'n':
        case 'N':
            n++;
            break;
        case 'o':
        case 'O':
            o++;
            break;
        case 'p':
        case 'P':
            p++;
            break;
        case 'q':
        case 'Q':
            q++;
            break;
        case 'r':
        case 'R':
            r++;
            break;
        case 's':
        case 'S':
            s++;
            break;
        case 't':
        case 'T':
            t++;
            break;
        case 'u':
        case 'U':
            u++;
            break;
        case 'v':
        case 'V':
            v++;
            break;
        case 'w':
        case 'W':
            w++;
            break;
        case 'x':
        case 'X':
            x++;
            break;
        case 'y':
        case 'Y':
            y++;
            break;
        case 'z':
        case 'Z':
            z++;
            break;
        case ' ':
            space++;
            break;
        }
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

    count();
    int sum = a + b + c + d + e + f + g + h + i + j + k + l + m + n + o + p + q + r + s + t + u + v + w + x + y + z;
    sum = sum + space;
    // Show user how many of each alphabetical character are in the given file
    printf("a: %d\nb: %d\nc: %d\nd: %d\ne: %d\nf: %d\ng: %d\nh: %d\ni: %d\nj: %d\nk: %d\nl: %d\nm: %d\nn: %d\no: %d\np: %d\nq: %d\nr: %d\ns: %d\nt: %d\nu: %d\nv: %d\nw: %d\nx: %d\ny: %d\nz: %d\n", a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z);
    // Show user how many of each special character are in the given file (additionally the sum of all symbols as calculated earlier)
    printf("' ': %d\nsum: %d\n", space, sum);
    // Show user how many of each character are in the given file excluding spaces
    printf("sum (without spaces): %d characters\n", sum-space);

    return ERR_NO;
}
