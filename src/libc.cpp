#include <cstddef>
#include <cstdint>

extern "C" auto memmove(void *dstptr, const void *srcptr, size_t size) -> void * {
    auto *dst = (unsigned char *)dstptr;
    const auto *src = (const unsigned char *)srcptr;
    if (dst < src) {
        for (size_t i = 0; i < size; i++) {
            dst[i] = src[i];
        }
    } else {
        for (size_t i = size; i != 0; i--) {
            dst[i - 1] = src[i - 1];
        }
    }
    return dstptr;
}

extern "C" auto memcmp(const void *aptr, const void *bptr, size_t size) -> int {
    const auto *a = (const unsigned char *)aptr;
    const auto *b = (const unsigned char *)bptr;
    for (size_t i = 0; i < size; i++) {
        if (a[i] < b[i]) {
            return -1;
        }
        if (b[i] < a[i]) {
            return 1;
        }
    }
    return 0;
}

extern "C" auto memset(void *bufptr, int value, size_t size) -> void * {
    auto *buf = (unsigned char *)bufptr;
    for (size_t i = 0; i < size; i++) {
        buf[i] = (unsigned char)value;
    }
    return bufptr;
}

extern "C" auto memcpy(void *dstptr, void *srcptr, size_t size) -> void * {
    for (size_t i = 0; i < size; i++) {
        reinterpret_cast<volatile char *>(dstptr)[i] = reinterpret_cast<char *>(srcptr)[i];
    }
    return dstptr;
}
