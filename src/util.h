#ifndef UTIL_H
#define UTIL_H

#ifdef __STRICT_ANSI__
#define asm __asm__
#endif

/*****************************************************************************
 * Helpful Macros
 ****************************************************************************/

#define NULL ((void*)0)
#define ARRAY_COUNT(a) (sizeof((a))/sizeof((a)[0]))

/*****************************************************************************
 * Platform Types
 ****************************************************************************/

typedef unsigned char  uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int   uint32_t;
typedef unsigned int   size_t;

#ifdef __cplusplus
extern "C" {
#endif

void io_write_8(uint16_t port, uint8_t val);
uint8_t io_read_8(uint16_t port);
int putchar(int c);
int puts(const char *s);
void *memset(void *ptr, int data, size_t len);

#ifdef __cplusplus
}
#endif

#endif
