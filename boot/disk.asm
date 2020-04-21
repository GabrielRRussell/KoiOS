[bits 16]

;-------------------------------------------------------------------------------
; DISK ADDRESS PACKET
dap:
	db 10h ; Size of Packet, 16B
	db 0
dap_sector_count: dw 28 ; Number of Sectors to Read
dap_offset:				dw 0x1000
dap_segment:			dw 0
dap_lba_lo:				dd 1
dap_lba_hi:				dd 0
;-------------------------------------------------------------------------------

read_sectors_lba:
	pusha
	mov dl, 0x80 ; Should be 0x80
	mov ah, 42h ; EXT Read Sectors
	mov si, dap
	int 13h ; Read Sectors
	mov ah, 0xE
	jc .error
.success:
	mov al, ','
	int 0x10
	popa
	hlt
	ret
.error:
	; Carry Flag Set
	mov al, '!'
	int 0x10
	cli
	jmp $ ; Hang Here
;-------------------------------------------------------------------------------
; Convert LBA value in AX, to CHS.
; AX 	: LBA

result_sector: 	db 0
result_head:		db 0
result_track:		db 0

lba_to_chs:
	xor dx, dx
	mov bx, 18
	div bx
	inc dl
	mov byte [result_sector], dl

	xor dx, dx
	mov bx, 2
	div bx
	mov byte [result_head], dl
	mov byte [result_track], al
	ret
;-------------------------------------------------------------------------------
; Convert Cluster Number in AX to LBA Value
cluster_to_lba:
	; First Two Clusters always reserved
	sub ax, 2
	; Multiply by number of sectors to get our LBA count
	xor bx, bx
	mov bl, byte [sectors_per_cluster]
	mul bx
	ret
;-------------------------------------------------------------------------------
