global set_reg_dummy
global set_regs

section .bss

section .data

section .text
set_reg_dummy:
        mov r13, rdi
        mov rax, r13
        ret

set_regs:
        ret
