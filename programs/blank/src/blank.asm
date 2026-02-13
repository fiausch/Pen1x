[BITS 32]

section .asm

global _start

_start:
    call getkey
    push message
    mov eax, 1      ;print
    int 0x80        ;kernie int
    add esp, 4
    jmp $

getkey:
    mov eax, 2 ;command getkey
    int 0x80
    cmp eax 0x00
    jne getkey
    ret


section .data
message: db 'communcating with the kernie', 0
