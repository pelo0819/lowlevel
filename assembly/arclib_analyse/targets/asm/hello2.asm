global print_msg2
global print_msg3
global exit

[section .data]
msg2: db 'goodball', 10
msg3: db 'doraemon', 10

[section .text]
print_msg2:
        mov rax, 1
        mov rdi, 1
        mov rsi, msg2
        mov rdx, 9
        syscall

print_msg3:
        mov rax, 1
        mov rdi, 1
        mov rsi, msg3
        mov rdx, 9
        syscall

exit:
        mov rax, 60
        xor rdi, rdi
        syscall



