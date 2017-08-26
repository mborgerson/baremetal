#ifndef SERIAL_H
#define SERIAL_H

#ifdef __cplusplus
extern "C" {
#endif

/* Serial port access */
int serial_getc(void);
int serial_putchar(int ch);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
