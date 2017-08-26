#include "serial.h"
#include "x86.h"

#define SERIAL_COM1 0x3f8
#define SERIAL_COM2 0x2f8
#define SERIAL_PORT SERIAL_COM1

#define SERIAL_THR 0
#define SERIAL_RBR 0
#define SERIAL_LSR 5

int serial_getc(void)
{
	/* Wait for data */
	while ((io_read_8(SERIAL_PORT + SERIAL_LSR) & 1) == 0);
	return io_read_8(SERIAL_PORT + SERIAL_RBR);
}

int serial_putchar(int ch)
{
	/* Wait for THRE (bit 5) to be high */
	while ((io_read_8(SERIAL_PORT + SERIAL_LSR) & (1<<5)) == 0);
	io_write_8(SERIAL_PORT + SERIAL_THR, ch);
	return ch;
}
