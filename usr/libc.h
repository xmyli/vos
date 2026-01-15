#ifndef LIBC_H
#define LIBC_H

void *memset(void *dst, int c, unsigned long n) {
    char *cdst = (char *)dst;
    int i;
    for (i = 0; i < n; i++) {
        cdst[i] = c;
    }
    return dst;
}

#endif
