[bits 16]

disk_load:
	pusha
	push dx

	mov ah, 0x02
	mov al, dh
	mov cl, 0x02

	mov ch, 0x00
	mov dh, 0x00

	int 0x13
	jc .disk_error

	pop dx
	cmp al, dh
	jne .sectors_error
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
