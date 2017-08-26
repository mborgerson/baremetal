#include "util.h"
#include "multiboot.h"

/*
 * This inline assembly code is the entry point to our code. It will set up the
 * stack, then jump to init().
 */
asm (" \
.section    ._start\n\
.global     _start\n\
.extern     _stack_addr\n\
_start:\n\
	cli\n\
	mov     $_stack_addr, %esp\n\
	push    %ebx\n\
	call    init\n\
	jmp     .\n\
");

extern char _bss_addr[];
extern char _bss_len[];

extern void (*_init_array_addr[])(void);
extern char _init_array_count[];

extern int main(int argc, char const *argv[]);

void *__dso_handle = NULL;

/* atexit() registry for functions to be called after main() returns
 *
 * Once you have a memory allocator, you should dynamically grow the registry to
 * support an arbitrary number of atexit() calls. For now, just use a statically
 * allocated registry of ten items.
 */
struct atexit_registry_entry {
	void (*func)(void *);
	void *arg;
	void *dso_handle;
} atexit_registry[10]; /* FIXME */

unsigned atexit_registry_index = 0;
unsigned atexit_registry_size = ARRAY_COUNT(atexit_registry);

/*
 * Basic startup function to get the environment ready
 */
void init(void *multiboot_info_ptr)
{
	unsigned i;
	int argc = 0;
	const char *argv[10]; /* FIXME */

	/* Blank BSS section */
	memset(_bss_addr, 0, (size_t)_bss_len);

	/* Multiboot info structure pointer is passed via EBX */
	multiboot_info = (struct multiboot_info *)multiboot_info_ptr;
	if (multiboot_info != NULL &&
		(multiboot_info->flags & MULTIBOOT_INFO_FLAG_CMDLINE)) {
		argv[argc] = (const char *)multiboot_info->cmdline;
		argc += 1;
	}

	/* Call statically allocated object constructors (found in .init_array) */
	for (i=0; i < (unsigned)_init_array_count; i++) {
		_init_array_addr[i]();
	}

	/* Begin main */
	main(argc, argv);

	/* Call atexit registered functions */
	for (i=0; i < atexit_registry_index; i++) {
		atexit_registry[i].func(atexit_registry[i].arg);
	}
}

/*
 * atexit() handler which will be called by the _init_array functions
 */
int __cxa_atexit(void (*func)(void *), void *arg, void *dso_handle)
{
	if (atexit_registry_index >= atexit_registry_size) {
		puts("*** Error: atexit registry overflow()!\n");
		return 1;
	}
	atexit_registry[atexit_registry_index].func = func;
	atexit_registry[atexit_registry_index].arg = arg;
	atexit_registry[atexit_registry_index].dso_handle = dso_handle;
	atexit_registry_index++;
	return 0;
}
