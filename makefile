.PHONY: all clean run debug

C_SOURCES = $(wildcard kernel/*.c kernel/memory/*.c cpu/interrupts/*.c cpu/timer/*.c cpu/*.c drivers/ata/*.c drivers/keyboard/*.c drivers/screen/*.c drivers/serial/*.c libk/mem/*.c libk/string/*.c)
HEADERS = $(wildcard kernel/*.h kernel/memory/*.h cpu/interrupts/*.h cpu/timer/*.h cpu/*.h drivers/ata/*.h drivers/keyboard/*.h drivers/screen/*.h drivers/serial/*.h libk/mem/*.h libk/string/*.h)

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
koiOS.img: boot/koiOS.img kernel.bin
	mv boot/koiOS.img koiOS.img; \
	mcopy -i koiOS.img kernel.bin ::/

boot/koiOS.img:
	$(MAKE) -C boot

# '--oformat binary' deletes all symbols as a collateral, so we don't need
# to 'strip' them manually on this case
kernel.bin: kernel/kernel_entry.o ${OBJ}
	i386-elf-ld -o $@ -Ttext 0x1000 $^ --oformat binary

# Used for debugging purposes
kernel.elf: kernel/kernel_entry.o ${OBJ}
	i386-elf-ld -o $@ -Ttext 0x1000 $^

run: koiOS.img
	qemu-system-i386 -hda koiOS.img -serial file:serial.log

# Open the connection to qemu and load our kernel-object file with symbols
debug: koiOS.img kernel.elf
	qemu-system-i386 -s -hda koiOS.img -S -serial file:serial.log &
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
