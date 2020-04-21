; gdt.asm
; GDT

gdt_null:
	dq 0 ; 8 Null Bytes
gdt_code:
	dw 0xFFFF
	dw 0x0
	db 0x0
	db 10011010b
	db 11001111b
	db 0x0
gdt_data:
	dw 0xFFFF
	dw 0x0
	db 0x0
	db 10010010b
	db 11001111b
	db 0x0
gdt_descriptor:
	dw gdt_descriptor - gdt_null - 1
	dd gdt_null

CODE_SEG equ gdt_code - gdt_null
DATA_SEG equ gdt_data - gdt_null
