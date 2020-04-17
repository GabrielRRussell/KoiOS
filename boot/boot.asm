; Boot.asm
; Bootloader Stage 0

[org 0x7c00]
[bits 16]

jmp boot
;-------------------------------------------------------------------------------
; BPB FAT32

oem_identifier:      	db "mkfs.fat"
bytes_per_sector:    	dw 512
sectors_per_cluster: 	db 1
reserved_sectors:    	dw 32   			; mkdosfs default
num_of_fats:         	db 2    			; we only need two FATs
num_of_dir_entries:  	dw 0	  			; Default for FAT32
total_sectors:       	dw 0					; File is too large, we use a 48MB Image
media_descriptor:    	db 0xF8
sectors_per_fat:     	dw 0
sectors_per_track:   	dw 0
num_of_heads:        	dw 0
hidden_sectors:      	dd 0    			; No partitioning. Yet.
large_sector: 				dd 0x00018000 ; 48MB Disk 512*0x18000
;-------------------------------------------------------------------------------
; EBPB FAT32
ebpb_sectors_per_fat:	dd 0x000002F4
ebpb_flags:						dw 0					; Reserved
version:							dw 0
root_start:						dd 2					; Sector 2
info_sector:					dw 1					; Sector 1
backup_sector:				dw 6					; Sector 6
;reserved_bytes: 			times 12 db 0
drive_number: 				db 0
reserved:							db 0
signature:						db 0x29
vol_id:								dd 0
vol_label:						db "KOI OS BOOT"
sys_id:								db "FAT32   "

; END OF BPB
;-------------------------------------------------------------------------------

STAGE2_NAME: db "BOOT2   BIN"

%include "boot/gdt.asm"
%include "boot/disk.asm"

KERNEL_OFFSET equ 0x1000

boot:
	; Set stack away from bootloader
	mov bp, 0x8000
	mov sp, bp
	; Save our Drive Number for Later
	mov [drive_number], dl

	; We'll overwrite this space with the kernel later
	mov bx, 0x1000
	mov ax, 20050
	call lba_to_chs
	call disk_load

	; Load Kernel
	mov bx, KERNEL_OFFSET
	mov dh, 16
	call disk_load

	cli
	lgdt[gdt_descriptor]

	; Enable A20 Using BIOS
	; We don't bother with checks, mostly because I'm lazy
	;@TODO Fix This
	mov ax, 2401h
	int 15h

	mov eax, cr0
	or eax, 0x1
	mov cr0, eax
	jmp CODE_SEG:init_pm

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
	call KERNEL_OFFSET
	jmp $

;times 510 - ($-$$) db 0
dw 0xAA55
