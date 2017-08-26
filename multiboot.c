#include "multiboot.h"

extern char _load_addr[];
extern char _load_end_addr[];
extern char _bss_end_addr[];
extern void _start(void);

#define MULTIBOOT_FLAGS (1<<16)

const struct multiboot_hdr multiboot_hdr __attribute__((section(".multiboot_hdr"))) = {
	/* magic         */ MULTIBOOT_MAGIC,
	/* flags         */ MULTIBOOT_FLAGS,
	/* checksum      */ 0-(MULTIBOOT_MAGIC+MULTIBOOT_FLAGS),
	/* header_addr   */ (uint32_t)&multiboot_hdr,
	/* load_addr     */ (uint32_t)_load_addr,
	/* load_end_addr */ (uint32_t)_load_end_addr,
	/* bss_end_addr  */ (uint32_t)_bss_end_addr,
	/* entry_addr    */ (uint32_t)&_start,
	/* mode_type     */ 0,
	/* width         */ 0,
	/* height        */ 0,
	/* depth         */ 0,
};

struct multiboot_info *multiboot_info = NULL;
