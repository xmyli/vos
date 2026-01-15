#include "system_calls.h"

void print(char *string) {
    while (*string != '\0') {
        write(1, string, 1);
        string++;
    }
}

int main() {
    int sckt = socket(0);
    if (connect(sckt, 167772674, 2001)) {
        print("CONNECTED.\n");
    } else {
        print("ERROR: connect() failed\n");
        exit(0);
    }
    char data[13] = "Hello, World!";
    if (write(sckt, data, 13) == 0) {
        print("ERROR: transmit() failed\n");
    } else {
        print("DATA TRANSMITTED\n");
    }
    exit(0);
}
