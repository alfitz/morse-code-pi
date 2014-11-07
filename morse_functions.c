#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "morse_functions.h"

#define TIME 300000

char *get_morse_code(char letter)
{
    // allocate 8 bytes for max morse size + buffer
    char *morse_code = malloc(sizeof(char) * 10);

    switch(letter) {

        case 'a':
            strcpy(morse_code, "*_-");
            break;
        case 'b':
            strcpy(morse_code, "-_*_*_*");
            break;
        case 'c':
            strcpy(morse_code, "-_*_-_*");
            break;
        case 'd':
            strcpy(morse_code, "-_*_*");
            break;
        case 'e':
            strcpy(morse_code, "*");
            break;
        case 'f':
            strcpy(morse_code, "*_*_-_*");
            break;
        case 'g':
            strcpy(morse_code, "-_-_*");
            break;
        case 'h':
            strcpy(morse_code, "*_*_*_*");
            break;
        case 'i':
            strcpy(morse_code, "*_*");
            break;
        case 'j':
            strcpy(morse_code, "*_-_-_-");
            break;
        case 'k':
            strcpy(morse_code, "-_*_-");
            break;
        case 'l':
            strcpy(morse_code, "*_-_*_*");
            break;
        case 'm':
            strcpy(morse_code, "-_-");
            break;
        case 'n':
            strcpy(morse_code, "-_*");
            break;
        case 'o':
            strcpy(morse_code, "-_-_-");
            break;
        case 'p':
            strcpy(morse_code, "*_-_-_*");
            break;
        case 'q':
            strcpy(morse_code, "-_-_*_-");
            break;
        case 'r':
            strcpy(morse_code, "*_-_*");
            break;
        case 's':
            strcpy(morse_code, "*_*_*");
            break;
        case 't':
            strcpy(morse_code, "-");
            break;
        case 'u':
            strcpy(morse_code, "*_*_-");
            break;
        case 'v':
            strcpy(morse_code, "*_*_*_-");
            break;
        case 'w':
            strcpy(morse_code, "*_-_-");
            break;
        case 'x':
            strcpy(morse_code, "-_*_*_-");
            break;
        case 'y':
            strcpy(morse_code, "-_*_-_-");
            break;
        case 'z':
            strcpy(morse_code, "-_-_*_*");
            break;
        case '0':
            strcpy(morse_code, "-_-_-_-_-");
            break;
        case '1':
            strcpy(morse_code, "*_-_-_-_-");
            break;
        case '2':
            strcpy(morse_code, "*_*_-_-_-");
            break;
        case '3':
            strcpy(morse_code, "*_*_*_-_-");
            break;
        case '4':
            strcpy(morse_code, "*_*_*_*_-");
            break;
        case '5':
            strcpy(morse_code, "*_*_*_*_*");
            break;
        case '6':
            strcpy(morse_code, "-_*_*_*_*");
            break;
        case '7':
            strcpy(morse_code, "-_-_*_*_*");
            break;
        case '8':
            strcpy(morse_code, "-_-_-_*_*");
            break;
        case '9':
            strcpy(morse_code, "-_-_-_-_*");
            break;
        default:
            fprintf(stderr, "Unknown character detected: %c\n", letter);
            exit(-1);
    }

    return morse_code;
}

void print_morse_letter(char code, FILE *io_file)
{
    switch(code) {

        // dot
        case '*':
            fprintf(io_file, "%d", 1);
            fflush(io_file);
            usleep(TIME);
            break;

            // dash
        case '-':
            fprintf(io_file, "%d", 1);
            fflush(io_file);
            usleep(TIME * 3);
            break;

            // interval between code in the same letter
        case '_':
            fprintf(io_file, "%d", 0);
            fflush(io_file);
            usleep(TIME);
            break;

            // interval between letters in same word)
        case 'i':
            fprintf(io_file, "%d", 0);
            fflush(io_file);
            usleep(TIME * 3);
            break;

            // space (between words)
        case 's':
            fprintf(io_file, "%d", 0);
            fflush(io_file);
            usleep(TIME * 7);
            break;
    }
}
