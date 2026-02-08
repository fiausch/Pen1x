section .asm

extern int21h_handler
extern no_interrupt_handler
extern isr80h_handler

global int21h
global no_interrupt
global idt_load
global enable_interrupts
global disable_interrupts
global isr80h_wrapper

disable_interrupts:
    cli
    ret
    
enable_interrupts:
    sti
    ret

idt_load:
    push ebp
    mov ebp, esp

    mov ebx, [ebp+8]
    lidt [ebx]
    pop ebp
    ret

int21h:
    pushad
    call int21h_handler
    popad
    sti
    iret

no_interrupt:
    pushad
    call no_interrupt_handler
    popad
    sti
    iret 

isr80h_wrapper:
    ; INTERRUPT FRAME START
    ; ALREADY PUSHED TO US BY PROCESSOR UPON ENTRY TO THIS INTERRUPT
    ; uint32_t ip;
    ; uint32_t cs;
    ; uint32_t flags;
    ; uint32_t sp;
    ; uint32_t ss;
    ;pushes the general registers to the stack
    pushad

    ; INTERRUPT FRAME END

    ; push the stack pointer so we are pointing to the interrupt frame
    push esp

    ; eax holds our command - lets push it to the stack for isr80h_handler
    push eax
    call isr80_handler
    mov dword[tmp_res], eax
    add esp, 8
    
    ;Restore general purpose registers for user land
    popad 
    mov eax, [tmp_res]
    iretd

section .data
;inside here is stored the return result from isr80h_handler
tmp_res: dd 0