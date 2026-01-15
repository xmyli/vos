#include "libc.h"
#include "system_calls.h"

void print(char *string) {
    while (*string != '\0') {
        write(1, string, 1);
        string++;
    }
}

int main() {
    print("pong\n");
    int sckt = socket(1);
    if (!bind(sckt, 2000)) {
        print("bind failure\n");
        exit(0);
    }
    print("bind success\n");
    char data[64] = {};
    uint32_t internet_protocol_address = 0;
    uint16_t port_number = 0;
    size_t number_of_bytes_received = receive(sckt, data, 3, &internet_protocol_address, &port_number);
    while (number_of_bytes_received != 0) {
        print("receive success\n");
        if (transmit(sckt, data, number_of_bytes_received, internet_protocol_address, port_number) == 0) {
            print("transmit failure\n");
            exit(0);
        }
        print("transmit success\n");
        number_of_bytes_received = receive(sckt, data, 3, &internet_protocol_address, &port_number);
    }
    print("receive failure\n");
    close(sckt);
    exit(0);
}
