#ifndef SYSTEM_CALLS_H
#define SYSTEM_CALLS_H

#include <stddef.h>
#include <stdint.h>

// file system
int open(char *, int, int, int);
void close(int);
int copy(int);
size_t read(int, void *, size_t);
size_t write(int, void *, size_t);

// process management
int fork();
int exec(char *, char **);
int wait();
void exit(int);

// inter-process communication
int pipe(int *);

// networking
size_t receive(int, void *, size_t, uint32_t *, uint16_t *);
size_t transmit(int, void *, size_t, uint32_t, uint16_t);
int socket(int);
int bind(int, int);
int connect(int, int, int);
int listen(int);
int accept(int);

#endif
