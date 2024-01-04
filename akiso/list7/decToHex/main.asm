%include "../functions.asm"

section .data
welcomeMsg  db "Please enter a number: ", 0h

section .bss
userInput:  resb 255

section .text
global _start

_start:
    mov     eax, welcomeMsg
    call    printStr

    mov     edx, 255
    mov     ecx, userInput
    mov     ebx, 0
    mov     eax, 3
    int     80h

    mov     eax, userInput
    call    stringToInt
    call    printHexLF
    call    quit
