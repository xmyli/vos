#include "system_calls.h"

void write_character(char character) {
    write(1, &character, 1);
}

void print(char *string) {
    while (*string != '\0') {
        write_character(*string);
        string++;
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        print("cat: argc < 2\n");
        exit(0);
    }
    int file = open(argv[1], 1, 0, 0);
    if (file == -1) {
        print("cat: unable to open file\n");
        exit(0);
    }
    char data[64];
    int number_of_bytes = 0;
    while (number_of_bytes = read(file, &data, 64)) {
        write(1, &data, number_of_bytes);
    }
    print("\n");
    exit(0);
}
