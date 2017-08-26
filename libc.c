#include "libc.h"
#include "serial.h"

/*
 * Print a character
 */
int putchar(int c)
{
	serial_putchar(c);
	return c;
}

/*
 * Print a null-terminated string
 */
int puts(const char *s)
{
	int c;

	for (c=0; *s; c++, s++) {
		putchar(*s);
	}

	return c;
}

/*
 * Set bytes in a range of memory to a given value
 */
void *memset(void *ptr, int data, size_t len)
{
	char *p = (char *)ptr;

	while (len--) {
		*p++ = (char)data;
	}

	return ptr;
}
