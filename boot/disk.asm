[bits 16]

;-------------------------------------------------------------------------------
; LOAD SECTORS
; INTERRUPT 13H / AH 0x02
; AL    : Sectors to Read
; CH 		: Track
; CL 		: Sector
; DH 		: Head
; DL 		: Drive
; ES:BX : Buffer to Read to

disk_load:
	; Preserve Stack
	pusha

	; Set Variables
	mov ch, [result_track]
	mov cl, [result_sector]
	mov dh, [result_head]
	mov dl, [drive_number]

	; Load Sectors using Interrupt 13h ah=2
	mov ah, 0x02
	int 0x13

	; Error Checking
	jc .disk_error
	cmp al, dh
	jne .sectors_error

	; Restore Stack, Return
	popa
	ret
.disk_error:
	mov al, "D"
	mov ah, 0xE
	int 0x13
	jmp .disk_loop
.sectors_error:
	mov al, "S"
	mov ah, 0xE
	int 0x13
.disk_loop:
	jmp $
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
; Compare two strings
; Located at si, di
; Length of strings: cx
; AL returns Result
compare_strings:
	cld
	repe cmpsb
	jne .miss
.success:
	mov al, 1
	ret
.miss:
	mov al, 0
	ret
