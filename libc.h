#ifndef LIBC_H
#define LIBC_H
#include "util.h"

#ifdef __cplusplus
extern "C" {
#endif

int putchar(int c);
int puts(const char *s);
void *memset(void *ptr, int data, size_t len);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
