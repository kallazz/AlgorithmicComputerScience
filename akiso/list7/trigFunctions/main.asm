
%include "../functions.asm"

section .data
prompt:             db "Enter a float: ", 0
promptFormat:       db "%s", 0
inputFormat:        db "%lf", 0
outputFormat:       db "%lf", 10, 0

outSin:             db "sin(x) = %lf", 10, 0
outCos:             db "cos(x) = %lf", 10, 0
outSqrt:            db "sqrt(x) = %lf", 10, 0
outExp:             db "exp(x) = %lf", 10, 0

eValue:             dq 2.71828

section .bss
inputFloat          resb 8

jes
section .text

global main
extern printf
extern scanf
main:
    ; print the prompt
    push    prompt
    push    promptFormat
    call    printf
    add     esp, 8

    push    inputFloat
    push    inputFormat
    call    scanf
    add     esp, 8


    finit
    fld     qword [inputFloat]       ; load x to the stack
    fld     st0
    fld     st0
    fld     st0

    fsin
    fst     qword [inputFloat]       ; store the top stack value at z, z = sqrt(x * x + y * y)
    fstp    st0
    ; print
    push    dword [inputFloat + 4]  ; push the higher 4 bytes of float
    push    dword [inputFloat + 0]  ; push the lower 4 bytes of float
    push    outSin
    call    printf
    add     esp, 12

    fcos
    fst     qword [inputFloat]
    fstp    st0
    ; print
    push    dword [inputFloat + 4]  ; push the higher 4 bytes of float
    push    dword [inputFloat + 0]  ; push the lower 4 bytes of float
    push    outCos
    call    printf
    add     esp, 12

    fsqrt
    fst     qword [inputFloat]
    fstp    st0
    ; print
    push    dword [inputFloat + 4]  ; push the higher 4 bytes of float
    push    dword [inputFloat + 0]  ; push the lower 4 bytes of float
    push    outSqrt
    call    printf
    add     esp, 12

    fld     qword [eValue]
    fld     st0
    fmul
    fst     qword [inputFloat]
    fstp    st0
    ; print
    push    dword [inputFloat + 4]  ; push the higher 4 bytes of float
    push    dword [inputFloat + 0]  ; push the lower 4 bytes of float
    push    outExp
    call    printf
    add     esp, 12










.finished:
    pop ebx     ; restore the stack
    ; finish with exit code 0
    call quit