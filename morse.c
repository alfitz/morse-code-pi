#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#define TIME 300000

int write_to_file(char *file_name, char *data)
{
    FILE *f;

    if (f = fopen(file_name, "w")) {
        fprintf(f, "%s", data);
        fclose(f);
    } else {
        fprintf(stderr, "Failed to open %s\n", file_name);
        exit(-1);
    }
}

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

void input_to_lowercase(char *user_input)
{
    while (*user_input != '\0') {
        *user_input = tolower(*user_input);
        user_input++;
    }
}

void close_file_io(FILE *io_file)
{
    fprintf(io_file, "%d", 0);
    fclose(io_file);
}

int main(int argc, char *argv[])
{
    FILE *pin_17;
    char next_letter;
    char *user_input, *token, *current_token;

    if (argc != 2) {
        fprintf(stderr, "Invalid number of arguments.\n Usage: %s \"<word to print in Morse code>\"\n", argv[0]);
        exit(-1);
    }

    write_to_file("/sys/class/gpio/export", "17");
    write_to_file("/sys/class/gpio/gpio17/direction", "out");
    pin_17 = fopen("/sys/class/gpio/gpio17/value", "w");

    user_input = argv[1];
    input_to_lowercase(user_input);
    token = strtok(user_input, " ");
    current_token = token;

    while (token != NULL) {

        // walk through every letter of the current word
        while (*current_token != '\0') {

            // get Morse Code for current char
            char *current_char_code = get_morse_code(*current_token);

            // walk through Morse Code of current letter
            while (*current_char_code != '\0') {
                print_morse_letter(*current_char_code, pin_17);
                current_char_code++;
            }

            // add interval between letters in the same word
            current_token++;

            if (*current_token != '\0')
                print_morse_letter('i', pin_17);
        }

        // add a long space between words
        token = strtok(NULL, " ");
        current_token = token;

        if (current_token != NULL)
            print_morse_letter('s', pin_17);
    }

    close_file_io(pin_17);
    write_to_file("/sys/class/gpio/unexport", "17");

    return 0;
}
