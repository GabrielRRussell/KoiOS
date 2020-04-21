.PHONY: all clean run debug
CC = /usr/local/i386elfgcc/bin/i686-elf-gcc
GDB = /usr/local/i386elfgcc/bin/i386-elf-gdb

koiOS.img: stage1/stage1.bin
	touch koiOS.img; \
	truncate -s +64M koiOS.img; \
	mkdosfs -F 32 -I -S 512 -v koiOS.img; \
	dd if=stage1/stage1.bin of=koiOS.img bs=512 count=1 conv=notrunc; \
	dd if=stage1/stage1.bin of=koiOS.img bs=512 count=1 seek=6 conv=notrunc

stage1/stage1.bin: stage1/boot.asm stage1/disk.asm stage1/gdt.asm stage1/string.asm
	nasm -f bin stage1/boot.asm -o stage1/stage1.bin

clean:
	rm -rf stage1/*.bin
