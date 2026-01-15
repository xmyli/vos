#include "libc.h"
#include "system_calls.h"

void print(char *string) {
    while (*string != '\0') {
        write(1, string, 1);
        string++;
    }
}

int main() {
    int sckt = socket(0);
    if (!bind(sckt, 2000)) {
        print("ERROR: bind() failed\n");
        exit(0);
    }
    if (!listen(sckt)) {
        print("ERROR: listen() failed\n");
        exit(0);
    }
    print("LISTENING...\n");
    int conn = accept(sckt);
    while (conn != -1) {
        for (;;) {
            char data[64] = {};
            if (read(conn, data, 64) == 0) {
                break;
            }
            print("DATA: ");
            print(data);
            print("\n");
        }
        close(conn);
        conn = accept(sckt);
    }
    print("ERROR: accept() failed\n");
    close(sckt);
    exit(0);
}
