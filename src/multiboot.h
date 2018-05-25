/*****************************************************************************
 * Multiboot Interface
 ****************************************************************************/
#ifndef MULTIBOOT_H
#define MULTIBOOT_H

#include "util.h"

#ifdef __cplusplus
extern "C" {
#endif

#define MULTIBOOT_MAGIC 0x1badb002

/*
 * This header will be located at the start of the program image and will be
 * used by the loader to determine how to load the program.
 */
struct multiboot_hdr {
	uint32_t magic;
	uint32_t flags;
	uint32_t checksum;
	uint32_t header_addr;
	uint32_t load_addr;
	uint32_t load_end_addr;
	uint32_t bss_end_addr;
	uint32_t entry_addr;
	uint32_t mode_type;
	uint32_t width;
	uint32_t height;
	uint32_t depth;
};

/*
 * When using Multiboot, this data structure will be prepared by the loader
 * and a pointer to this structure will be available via the EBX register.
 */
struct multiboot_info {
	uint32_t flags;             /* (required) */
		#define MULTIBOOT_INFO_FLAG_MEM               (1<<0)
		#define MULTIBOOT_INFO_FLAG_BOOT_DEVICE       (1<<1)
		#define MULTIBOOT_INFO_FLAG_CMDLINE           (1<<2)
		#define MULTIBOOT_INFO_FLAG_MODS              (1<<3)
		#define MULTIBOOT_INFO_FLAG_SYMS              ((1<<4)|(1<<5))
		#define MULTIBOOT_INFO_FLAG_MMAP              (1<<6)
		#define MULTIBOOT_INFO_FLAG_DRIVES            (1<<7)
		#define MULTIBOOT_INFO_FLAG_CONFIG_TABLE      (1<<8)
		#define MULTIBOOT_INFO_FLAG_BOOT_LOADER_NAME  (1<<9)
		#define MULTIBOOT_INFO_FLAG_APM_TABLE         (1<<10)
		#define MULTIBOOT_INFO_FLAG_VBE_CONTROL_INFO  (1<<11)
	uint32_t mem_lower;         /* (present if flags[0] is set) */
	uint32_t mem_upper;         /* (present if flags[0] is set) */
	uint32_t boot_device;       /* (present if flags[1] is set) */
	uint32_t cmdline;           /* (present if flags[2] is set) */
	uint32_t mods_count;        /* (present if flags[3] is set) */
	uint32_t mods_addr;         /* (present if flags[3] is set) */
	uint32_t syms[3];           /* (present if flags[4] or flags[5] is set) */
	uint32_t mmap_length;       /* (present if flags[6] is set) */
	uint32_t mmap_addr;         /* (present if flags[6] is set) */
	uint32_t drives_length;     /* (present if flags[7] is set) */
	uint32_t drives_addr;       /* (present if flags[7] is set) */
	uint32_t config_table;      /* (present if flags[8] is set) */
	uint32_t boot_loader_name;  /* (present if flags[9] is set) */
	uint32_t apm_table;         /* (present if flags[10] is set) */
	uint32_t vbe_control_info;  /* (present if flags[11] is set) */
	uint32_t vbe_mode_info;
	uint16_t vbe_mode;
	uint32_t vbe_interface_seg;
	uint32_t vbe_interface_off;
	uint32_t vbe_interface_len;
};

extern struct multiboot_info *multiboot_info;

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
