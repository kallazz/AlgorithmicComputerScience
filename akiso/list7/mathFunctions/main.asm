; nasm -f elf -g main.asm && gcc -m32 main.o
%include "../functions.asm"
%include "./mathFunctions.asm"

section .data
f1Output        db "f1: %lf", 10, 0
f2Output        db "f2: %lf", 10, 0
f3Output        db "f3: %lf", 10, 0
f4Output        db "f4: %lf", 10, 0

a:              dq 5.0                  ; 8 bytes(double)
b:              dd 2.0                  ; 4 bytes(float)
c:              dq 10.0                  ; 8 bytes(double)
d:              dd 2                    ; 4 bytes(int)
result:         dq 0.0

section .text

extern printf
global main

main:
    finit                       ; initialize FPU

    mov eax, a
    mov ebx, b
    mov ecx, c
    mov edx, d
    call f1
    ; printf
    push dword [result + 4]     ; push the lower 4 bytes
    push dword [result]         ; push the higher 4 bytes
    push f1Output
    call printf
    add esp, 12                 ; remove params from the stack to adjust the stack pointer

    mov eax, a
    mov ebx, d
    call f2
    ; printf
    push dword [result + 4]
    push dword [result]
    push f2Output
    call printf
    add esp, 12

    mov eax, a
    mov ebx, d
    call f3
    ; printf
    push dword [result + 4]
    push dword [result]
    push f3Output
    call printf
    add esp, 12

    mov eax, b
    mov ebx, d
    call f4
    ; printf
    push dword [result + 4]
    push dword [result]
    push f4Output
    call printf
    add esp, 12

    call    quit
