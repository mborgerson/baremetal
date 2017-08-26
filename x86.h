#ifndef X86_H
#define X86_H
#include "util.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Utility functions to access I/O ports */
void io_write_8(uint16_t port, uint8_t val);
uint8_t io_read_8(uint16_t port);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
