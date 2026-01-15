#include "stdint.h"
#include "system_calls.h"

#define maximum_path_length 108

struct directory_entry_t {
    uint8_t name[maximum_path_length];
    uint64_t length;
    uint32_t index;
};

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
    int directory = -1;
    if (argc < 2) {
        directory = open("/", 1, 0, 0);
    } else {
        directory = open(argv[1], 1, 0, 0);
    }
    if (directory == -1) {
        print("ls: unable to open directory\n");
        exit(0);
    }
    struct directory_entry_t directory_entry;
    while (read(directory, &directory_entry, sizeof(struct directory_entry_t)) != 0) {
        for (int i = 1; i < directory_entry.length; i++) {
            if (directory_entry.name[i] != '\0') {
                write(1, &directory_entry.name[i], 1);
            }
        }
        char next_line = '\n';
        write(1, &next_line, 1);
    }
    exit(0);
}
