.globl _start
.globl pprint
.globl pexit

#section .data
#message: db 'hello, world', 10

#section .text
_start:
    call main
    mov  $60, %eax
    xor  %rdi, %rdi   
    syscall
