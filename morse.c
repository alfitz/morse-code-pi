#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "morse_functions.h"

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

void close_file_io(FILE *io_file)
{
    fprintf(io_file, "%d", 0);
    fclose(io_file);
}

void input_to_lowercase(char *user_input)
{
    while (*user_input != '\0') {
        *user_input = tolower(*user_input);
        user_input++;
    }
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
