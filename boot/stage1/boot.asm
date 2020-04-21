; Boot.asm
; Bootloader Stage 1

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
total_sectors:       	dw 0					; File is too large, we use a 64MB Image
media_descriptor:    	db 0xF8
sectors_per_fat:     	dw 0
sectors_per_track:   	dw 32
num_of_heads:        	dw 64
hidden_sectors:      	dd 0    			; No partitioning. Yet.
large_sector: 				dd 0x00020000 ; 64MB Disk 512*0x20000
;-------------------------------------------------------------------------------
; EBPB FAT32
ebpb_sectors_per_fat:	dd 0x000003F1 ; This is what mkdosfs gives us
ebpb_flags:						dw 0					; Reserved
version:							dw 0
root_start:						dd 2					; Cluster 2
info_sector:					dw 1					; Sector 1
backup_sector:				dw 6					; Sector 6
reserved_bytes: 			times 12 db 0
drive_number: 				db 0x80 			; Default HDD
reserved:							db 0
signature:						db 0x29
vol_id:								dd 0
vol_label:						db "KOI OS BOOT"
sys_id:								db "FAT32   "
; END OF BPB
;-------------------------------------------------------------------------------
; Bootloader Variables
STAGE2_NAME: db "BOOT2   BIN", 0	; File Name of Stage2
STAGE2_CLUSTER_START: dw 0				; Cluster Number of Stage2
STAGE2_FILE_SIZE: dd 0						; File Size of Stage2 in Bytes
LOAD_OFFSET equ 0x1000						; Where Stage2 is loaded to
ENTRY_OFFSET equ 0x0803

;-------------------------------------------------------------------------------
; Includes
%include "stage1/gdt.asm"
%include "stage1/disk.asm"
%include "stage1/string.asm"
;-------------------------------------------------------------------------------
boot:
	; Set stack away from bootloader
	mov bp, 0x8000
	mov sp, bp
	mov ax, 0
	mov ds, ax
	; Save our Drive Number for Later
	; This will probably be 0x80, to be fair
	mov [drive_number], dl

	; Get the size of the FATs
	mov ax, [ebpb_sectors_per_fat]

	mov bx, 2
	mul bx
	xor bx, bx
	; Add reserved sectors
	add ax, [reserved_sectors]
	add ax, [hidden_sectors]

	; Load this sector into the DAP, then read to 0x0000:0x1000
	mov [dap_lba_lo], ax
	mov word [dap_sector_count], 1
	mov bx, LOAD_OFFSET
	mov word [dap_offset], LOAD_OFFSET
	call read_sectors_lba

	; Get to our Cluster Number
	add bx, 0x1A
	mov ax, word [bx]
	call cluster_to_lba
	mov [dap_lba_lo], ax

	; Get file size in Bytes
	mov bx, LOAD_OFFSET
	add bx, 28
	mov eax, dword [bx]

	; Divide by 512 to get file size in sectors, aka clusters to load
	mov bx, 512
	div bx

	; See if there's an uneven number of bytes. If so, load an extra cluster
	cmp dx, 0
	je .part2
	add ax, 1
.part2:

	mov dl, 0x80
	mov word [dap_sector_count], ax
	call read_sectors_lba

	cli
	lgdt[gdt_descriptor]
	sti
	; Enable A20 Using BIOS
	; We don't bother with checks, mostly because I'm lazy
	;@TODO Fix This
	mov ax, 2401h
	int 15h

	mov eax, cr0
	or eax, 0x1
	mov cr0, eax
	jmp CODE_SEG:init_pm

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
	call LOAD_OFFSET
	jmp $

times 510 - ($-$$) db 0
dw 0xAA55
