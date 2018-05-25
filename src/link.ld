ENTRY(_start)

MEMORY
{
	RAM (RWX) : ORIGIN = 0x100000, LENGTH = 0x10000
}

SECTIONS
{
	/* Place the Multiboot header at the very front */
	.hdr : {
		_load_addr = .;
		KEEP(*(.multiboot_hdr*))
	} > RAM

	/* Bring all text sections into one, but keep _start in front */
	.text : {
		KEEP(*(._start))
		*(.text*)

		/* The following .init_array will contain function pointers that should
		 * be called before main()
		 */
		. = ALIGN(4);
		_init_array_addr = .;
		KEEP(*(.init_array))
		_init_array_end_addr = .;
	} > RAM = 0xff

	.rodata : {
		. = ALIGN(4);
		*(.rodata*)
	} > RAM = 0xff

	.data : {
		. = ALIGN(4);
		*(.data)
		BYTE(0xFF)
		. = ALIGN(0x10);
		_load_end_addr = .;
	} > RAM = 0xff

	.bss (NOLOAD) : {
		. = ALIGN(4);
		_bss_addr = .;
		*(.bss COMMON)
		_bss_end_addr = .;
	} > RAM

	.stack (NOLOAD) : {
		. = ALIGN(4K);
		_stack_addr = .;
		. += 4K;
		_stack_end_addr = .;
	}

	/DISCARD/ : {
		*(.comment)
		*(.note.GNU-stack)
		*(.eh_frame)
		*(.rela.eh_frame)
		*(.debug*)
	}

}

_bss_len = _bss_end_addr - _bss_addr;
_init_array_count = (_init_array_end_addr - _init_array_addr) / 4;
