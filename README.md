Bare Metal C/C++ Example
========================
Demo to show running C, and even basic C++, code on bare metal is not so
difficult.

How it Works
------------
The code is compiled as stand-alone. No system libraries (libc, for instance)
are required. A custom linker script is used to construct an initial memory
layout, and explicitly specify where the program should expect to be loaded to,
and execute from.

Entry begins in assembly code at the `_start` label. This simply sets up the
stack and jumps to the early C-code function `init` which does some other early
initialization. Finally, control is passed to the `main` function, as you would
typically have in an application. Functions can now be called, objects can be
instantiated, etc.

Note that there is no malloc/free new/delete support! This is because there is
no memory allocator implemented here. (Fun exercise: implement one!)

Multiboot
---------
[Multiboot](https://www.gnu.org/software/grub/manual/multiboot/multiboot.html)
is a simple interface between the loader and the program. The program contains
a header, and when transferring control to the program the loader will provide
some info via a pointer to a data structure.

While it is not necessary to implement a Multiboot header in your program (for
instance, if you have no loader...) but it helps to test in common environments
such as GRUB or QEMU. This demo includes Multiboot support.

Build
-----
Build with standard tools (i.e. `make`, `g++`):

	$ make

Test
----
You can easily test with QEMU:

	$ qemu-system-i386 -kernel prog.bin --vnc none --serial stdio

This will start a new Qemu instance, load the program, disable the screen
output (we aren't drawing anything there yet), and enable the serial port.

If you want to debug, you can request QEMU to host a GDB server which you can
connect to.