; Boot.asm
; Bootloader Stage 0

[org 0x7c00]
[bits 16]

jmp boot

%include "boot/gdt.asm"
%include "boot/disk.asm"

KERNEL_OFFSET equ 0x1000

boot:
	; Set stack away from bootloader
	mov bp, 0x8000 
	mov sp, bp

	mov bx, 0x1000
	mov dh, 16
	
	call disk_load

	cli
	lgdt[gdt_descriptor]

	mov ax, 2401h
	int 15h

	mov eax, cr0
	or eax, 0x1
	mov cr0, eax
	jmp CODE_SEG:init_pm

	; Should never reach here, if you do, something fucked up	
	jmp $

[bits 32]
init_pm:
	mov ax, DATA_SEG
	mov ds, ax
	mov ss, ax
	mov es, ax
	mov fs, ax
	mov gs, ax

	mov ebp, 0x90000
	mov esp, ebp

	call BEGIN_PM

BEGIN_PM:
	mov eax, 0xb8000
	mov [eax], byte "!"
	mov [eax+1], byte 0x0f

	call KERNEL_OFFSET
	jmp $

times 510 - ($-$$) db 0
dw 0xAA55
