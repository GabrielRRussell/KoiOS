.PHONY: all clean run debug

C_SOURCES := $(shell find . -name "*.c")
HEADERS :=  $(shell find . -name "*.h")
#C_SOURCES = $(wildcard kernel/*.c drivers/*.c drivers/keyboard/*.c drivers/cpu/*.c libc/*.c)
#HEADERS = $(wildcard kernel/*.h drivers/*.h cpu/*.h libc/*.h)

# Nice syntax for file extension replacement
OBJ := $(patsubst %.c,%.o,$(C_SOURCES) cpu/interrupts/interrupts.o)
OBJs := $(shell find . -name "*.o")
ELF := $(shell find . -name "*.elf")
BIN := $(shell find . -name "*.bin")

# Change this if your cross-compiler is somewhere else
CC = /usr/local/i386elfgcc/bin/i686-elf-gcc
GDB = /usr/local/i386elfgcc/bin/i386-elf-gdb
# -g: Use debugging symbols in gcc
CFLAGS = -g -ffreestanding -mno-sse -mno-sse2 -mno-mmx -mno-80387 -Wall -Wextra



# First rule is run by default
os-image.bin: boot/boot.bin kernel.bin
	cat $^ > os-image.bin; \
	truncate -s +1M os-image.bin

# '--oformat binary' deletes all symbols as a collateral, so we don't need
# to 'strip' them manually on this case
kernel.bin: boot/kernel_entry.o ${OBJ}
	i386-elf-ld -o $@ -Ttext 0x1000 $^ --oformat binary

# Used for debugging purposes
kernel.elf: boot/kernel_entry.o ${OBJ}
	i386-elf-ld -o $@ -Ttext 0x1000 $^

run: os-image.bin
	qemu-system-i386 -fda os-image.bin

# Open the connection to qemu and load our kernel-object file with symbols
debug: os-image.bin kernel.elf
	qemu-system-i386 -s -hda os-image.bin -S -serial file:serial.log &
	gdb -ex "target remote localhost:1234" -ex "symbol-file kernel.elf"

# Generic rules for wildcards
# To make an object, always compile from its .c
%.o: %.c ${HEADERS}
	${CC} ${CFLAGS} -c $< -o $@

%.o: %.asm
	nasm $< -f elf -o $@

%.bin: %.asm
	nasm $< -f bin -o $@

clean:
	rm -rf ${OBJs}
	rm -rf ${ELF}
	rm -rf ${BIN}
