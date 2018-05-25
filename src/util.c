#include "util.h"

/*
 * Write to I/O port
 */
void io_write_8(uint16_t port, uint8_t val)
{
	asm volatile (
		"outb    %%al, %%dx;"
		/* Outputs  */ : /* None */
		/* Inputs   */ : "a" (val), "d" (port)
		/* Clobbers */ : /* None */
		);
}

/*
 * Read from I/O port
 */
uint8_t io_read_8(uint16_t port)
{
	uint8_t val;

	asm volatile (
		"inb     %%dx, %%al;"
		/* Outputs  */ : "=a" (val)
		/* Inputs   */ : "d" (port)
		/* Clobbers */ : /* None */
		);

	return val;
}

#define SERIAL_COM1 0x3f8
#define SERIAL_COM2 0x2f8
#define SERIAL_PORT SERIAL_COM1

#define SERIAL_THR 0
#define SERIAL_LSR 5

/*
 * Print a character
 */
int putchar(int c)
{
	/* Wait for THRE (bit 5) to be high */
	while ((io_read_8(SERIAL_PORT + SERIAL_LSR) & (1<<5)) == 0);
	io_write_8(SERIAL_PORT + SERIAL_THR, c);
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
