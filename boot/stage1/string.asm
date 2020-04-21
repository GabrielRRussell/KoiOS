[bits 16]

hex_output: db "0x0000", 10, 13, 0
; Print DX Register
print_register:
  pusha
  mov cx, 0
.loop:
  cmp cx, 4
  je .exit

  mov ax, dx
  and ax, 0x000F
  add al, 0x30
  cmp al, 0x39
  jle .step2
  add al, 7
.step2:
  mov bx, hex_output + 5
  sub bx, cx
  mov [bx], al
  ror dx, 4

  add cx, 1
  jmp .loop
.exit:
  mov si, hex_output
  call print_string
  popa
  ret

;-------------------------------------------------------------------------------
; Print String located at SI
print_string:
  pusha
.loop:
  lodsb
  or al, al
  jz .exit
  mov ah, 0xE
  int 10h
  jmp .loop
.exit:
  popa
  ret
