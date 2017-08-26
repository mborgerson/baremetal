#include "x86.h"

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
