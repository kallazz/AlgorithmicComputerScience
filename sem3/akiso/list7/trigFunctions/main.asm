
%include "../functions.asm"

section .data
prompt:             db "Enter a number: ", 0
promptFormat:       db "%s", 0
inputFormat:        db "%lf", 0
outSin:             db "sin(x) = %lf", 10, 0
outCos:             db "cos(x) = %lf", 10, 0
outSqrt:            db "sqrt(x) = %lf", 10, 0
outExp:             db "exp(x) = %lf", 10, 0

eValue:             dq 2.71828
result:             dq 0.0

section .bss
userInput           resb 8

section .text
global main
extern printf
extern scanf

printResult:
    push    dword [result + 4]      ; push the higher 4 bytes
    push    dword [result + 0]      ; push the lower 4 bytes
    push    eax
    call    printf
    add     esp, 12
    ret

main:
    ; print the prompt
    push    prompt
    push    promptFormat
    call    printf
    add     esp, 8

    ; store the input
    push    userInput
    push    inputFormat
    call    scanf
    add     esp, 12

    ; initialize FPU
    finit

    ; push input to the stack and duplicate it 3 times
    fld     qword [userInput]
    fld     st0
    fld     st0
    fld     st0

    ; sin(x)
    fsin
    fstp    qword [result]
    mov     eax, outSin
    call    printResult

    ; cos(x)
    fcos
    fstp    qword [result]
    mov     eax, outCos
    call    printResult

    ; sqrt(x)
    fsqrt
    fstp    qword [result]
    mov     eax, outSqrt
    call    printResult

    ; exp(x)
    fld     qword [eValue]

    fyl2x                       ; st0 = x * log2(e)
    fld     st0                 ; duplicate

    frndint                     ; get integer part
    fxch                        ; swap st0 with st1
    fsub    st0, st1            ; get fractional part
    f2xm1                       ; 2^frac(x * log2(e))
    fld1
    faddp

    fxch                        ; swap st0 with st1
    fld1
    fscale                      ; 1 * 2^int(x * log2(2))
    fstp    st1
    fmulp                       ; 2^frac(x * log2(e)) * 2^int(x * log2(e)) = 2^(x * log2(e))

    fstp    qword [result]
    mov     eax, outExp
    call    printResult

    call    quit
