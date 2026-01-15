#include "libc.h"
#include "system_calls.h"

char read_character() {
    char character = 0;
    read(0, &character, 1);
    return character;
}

void write_character(char character) {
    write(1, &character, 1);
}

void print(char *string) {
    while (*string != '\0') {
        write_character(*string);
        string++;
    }
}

void handle_command_execution(char *command) {
    char arguments[64][64];
    int argument_index = 0;
    int argument_character_index = 0;

    for (int i = 0; i < 64; i++) {
        for (int j = 0; j < 64; j++) {
            arguments[i][j] = '\0';
        }
    }

    for (int i = 0; i < 256; i++) {
        if (command[i] == ' ' || command[i] == '\0') {
            if (argument_character_index != 0) {
                argument_character_index = 0;
                argument_index += 1;
            }
        } else {
            arguments[argument_index][argument_character_index] = command[i];
            argument_character_index += 1;
        }
    }

    if (argument_index < 1) {
        return;
    }

    char *arguments_list[64];
    for (int i = 0; i < 64; i++) {
        arguments_list[i] = 0;
    }
    for (int i = 0; i < argument_index; i++) {
        arguments_list[i] = (char *)&arguments[i];
    }

    int parent_to_child[2];
    pipe(parent_to_child);
    int child_to_parent[2];
    pipe(child_to_parent);

    if (fork() == 0) {
        // child
        close(0);
        close(1);
        close(parent_to_child[1]);
        close(child_to_parent[0]);
        int new_stdin = copy(parent_to_child[0]);
        int new_stdout = copy(child_to_parent[1]);
        exec(arguments[0], arguments_list);
        exit(0);
    } else {
        // parent
        close(parent_to_child[0]);
        close(child_to_parent[1]);
        char character_from_child = 1;
        while (character_from_child != 0) {
            if (read(child_to_parent[0], &character_from_child, 1) != 0) {
                write(1, &character_from_child, 1);
            }
        }
        wait();
    }
}

int main() {
    char command[256];
    int index = 0;
    for (;;) {
        write_character('$');
        write_character(' ');
        char character = 0;
        for (;;) {
            character = read_character();
            if (character != 13) {
                if (character >= 32 && character <= 126) {
                    if (index < 255) {
                        write_character(character);
                        write_character(0);
                        command[index] = character;
                        index += 1;
                    }
                } else if (character == 127) {
                    if (index > 0) {
                        write_character('\b');
                        write_character(' ');
                        write_character('\b');
                        write_character(0);
                        index -= 1;
                        command[index] = 0;
                    }
                }
            } else {
                write_character('\n');
                write_character(0);
                handle_command_execution(command);
                for (int i = 0; i < index; i++) {
                    command[i] = 0;
                }
                index = 0;
                break;
            }
        }
    }
    exit(0);
}
