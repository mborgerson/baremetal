CC           = gcc
CFLAGS      += -m32
CFLAGS      += -Werror -Wpedantic -ansi
CFLAGS      += -Os
CFLAGS      += -g
CFLAGS      += -fno-stack-protector
CFLAGS      += -ffunction-sections
CFLAGS      += -ffreestanding
CFLAGS      += -MMD
CPPC         = g++
CPPFLAGS     = $(CFLAGS)
CPPFLAGS    += -fno-rtti
CPPFLAGS    += -fno-exceptions
LD           = ld
LD_SCRIPT    = link.ld
LDFLAGS      = --script=$(LD_SCRIPT) -m elf_i386 --gc-sections
NASM         = nasm
NASM_FLAGS   = -felf
OBJCOPY      = objcopy
OBJCOPYFLAGS = --output-target=binary
TARGET       = prog.bin
OBJECTS      = _start.o main.o util.o
DEPS         = $(OBJECTS:.o=.d)

all: $(TARGET)
.PRECIOUS: %.elf

%.bin: %.elf
	$(OBJCOPY) $(OBJCOPYFLAGS) $^ $@

%.elf: $(OBJECTS) $(LD_SCRIPT)
	$(LD) $(LDFLAGS) -o $@ $(OBJECTS)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

%.o: %.nasm
	$(NASM) -o $@ $(NASM_FLAGS) $<

%.o: %.cpp
	$(CPPC) $(CPPFLAGS) -o $@ -c $<

.PHONY: clean
clean:
	rm -f \
		$(TARGET) \
		$(TARGET:.bin=.elf) \
		$(OBJECTS) \
		$(DEPS)

.PRECIOUS: %.o

.PHONY: run
run: $(TARGET)
	qemu-system-i386 -kernel $(TARGET) -append "Hello World" --vnc none --serial stdio

-include $(DEPS)
