;------------------------------------------------------------------------------------
; void quit()
; quit the program with status 0
quit:
    mov       ebx, 0
    mov       eax, 1
    int       80h
    ret


;------------------------------------------------------------------------------------
; int strlen(String message)
; returns the length of the string
strlen:
    push      ebx               ; push ebx value to the stack to save it
    mov       ebx,  eax

.nextChar:
    cmp       byte [eax], 0     ; look for 0 in string(end of string)
    jz        .finished         ; jump if zero flag is set(cmp can set it if x == y)
    inc       eax               ; increment eax by one byte
    jmp       .nextChar         ; jump to nextChar label

.finished:
    sub       eax, ebx          ; eax = eax - ebx, this is the string's length
    pop       ebx               ; pop from stack back into into ebx
    ret                         ; return to where the function was called


;------------------------------------------------------------------------------------
; void printStr(String message)
; prints the string
printStr:
    push      edx
    push      ecx
    push      ebx
    push      eax
    call      strlen

    mov       edx, eax
    pop       eax

    mov       ecx, eax
    mov       ebx, 1
    mov       eax, 4
    int       80h

    pop       ebx
    pop       ecx
    pop       edx
    ret


;------------------------------------------------------------------------------------
; void printLF(String message)
; prints the LF character
printLF:
    push    eax
    mov     eax, 0Ah
    push    eax         ; push eax with LF character to the stack
    mov     eax, esp    ; use esp to get the adress(which is required by write syscall)
    call    printStr
    pop     eax
    pop     eax
    ret


;------------------------------------------------------------------------------------
; void printStrLF(String message)
; prints the string with linfeed(newline) character
printStrLF:
    call    printStr
    call    printLF
    ret


;------------------------------------------------------------------------------------
; void printInt(Integer number)
; prints integer
printInt:
    ; push to stack to preserve the values
    push    eax
    push    ecx
    push    edx
    push    esi
    mov     ecx, 0      ; will count how many bytes to print

.divideLoop:
    inc     ecx
    mov     edx, 0
    mov     esi, 10
    idiv    esi         ; divides eax by esi, eax = result, edx = remainder
    add     edx, 48     ; make the remainder an ASCII int
    push    edx         ; push the string representation of the remainder onto the stack
    cmp     eax, 0      ; check if the result can be divided more
    jnz     .divideLoop

.printLoop:
    dec     ecx         ; decrease the bytes to print counter
    mov     eax, esp
    call    printStr    ; print the digit
    pop     eax         ; remove this digit from the stack
    cmp     ecx, 0
    jnz     .printLoop

    pop     esi
    pop     edx
    pop     ecx
    pop     eax
    ret


;------------------------------------------------------------------------------------
; void printIntLF(Integer number)
; prints integer with newline
printIntLF:
    call    printInt
    call    printLF
    ret


;------------------------------------------------------------------------------------
; int getHexDigitASCII(Integer decimal_number)
; converts the given number to a hex digit in ASCII int form
getHexDigitASCII:
    cmp     eax, 9
    jg      .letter     ; if this is a number 10-15

    add     eax, 48     ; mapping 0-9 to ASCII 0-9
    jmp     .numberReady

.letter:
    add     eax, 55     ; mapping 10-15 to A-F

.numberReady:
    ret


;------------------------------------------------------------------------------------
; void printHex(Integer decimalNumber)
; takes a decimal number and prints it out as a hexadecimal number
printHex:
    ; push to stack to preserve the values
    push    eax
    push    ecx
    push    edx
    push    esi
    mov     ecx, 0      ; will count how many bytes to print

.divideLoop:
    inc     ecx
    mov     edx, 0
    mov     esi, 16
    idiv    esi         ; divides eax by esi, eax = result, edx = remainder

    push    eax
    mov     eax, edx
    call    getHexDigitASCII
    mov     edx, eax
    pop     eax

    push    edx         ; push the string representation of the remainder onto the stack
    cmp     eax, 0      ; check if the result can be divided more
    jnz     .divideLoop

.printLoop:
    dec     ecx         ; decrease the bytes to print counter
    mov     eax, esp
    call    printStr    ; print the digit
    pop     eax         ; remove this digit from the stack
    cmp     ecx, 0
    jnz     .printLoop

    pop     esi
    pop     edx
    pop     ecx
    pop     eax
    ret


;------------------------------------------------------------------------------------
; void printHexLF(Integer decimalNumber)
; takes a decimal number and prints it out as a hexadecimal number with newline
printHexLF:
    call    printHex
    call    printLF
    ret


;------------------------------------------------------------------------------------
; int stringToInt(String text)
; takes a string(can have LF at the end) and converts it to an int
stringToInt:
    push    ebx,
    push    ecx,
    push    edx,
    push    esi,
    mov     esi, eax
    mov     eax, 0          ; eax will hold the int
    mov     ecx, 0

.multiplyLoop:
    ; bl is a part of ebx, which only takes 8 bits and this is the size of 1 ASCII character
    xor     ebx, ebx        ; set ebx to 0
    mov     bl, [esi+ecx]   ; move byte at adress computed by adding values esi+ecx to ebx register's lower half
                            ; [esi+ecx] just gets one character from the char array(string)
                            ; esi is the beggining of the array and ecx is the counter that gets incremented
    cmp     bl, 48
    jl      .finished
    cmp     bl, 57
    jg      .finished

    sub     bl, 48          ; bl = bl - 48   ebx's lower half gets converted to decimal representation of ascii value
    add     eax, ebx        ; eax = eax + ebx
    mov     ebx, 10
    mul     ebx             ; eax = eax * ebx = eax * 10
    inc     ecx             ; increment the counter
    jmp     .multiplyLoop 

.finished:
    cmp     ecx, 0          ; check if the counter == 0     that means that no ints were provided
    je      .restore
    mov     ebx, 10
    div     ebx             ; eax = eax / ebx = eax / 10

.restore:
    pop     esi,
    pop     edx,
    pop     ecx,
    pop     ebx,
    ret


;------------------------------------------------------------------------------------
; bool isPrime(int number)
; checks if the provided int is a prime number
isPrime:
    push    ebx
    push    ecx
    push    edx

    cmp     eax, 2
    jl      .notPrime
    mov     ecx, 2          ; set loop counter to 2
    mov     ebx, eax        ; ebx will hold the number value

.loop:
    cmp     ecx, ebx        ; stop when counter == number
    je      .prime

    mov     eax, ebx
    mov     edx, 0          ; clear the remainder register before division
    div     ecx             ; number = number / i
    cmp     edx, 0          ; check if remainder is 0
    je      .notPrime       ; if so, this is not a prime

    inc     ecx             ; increment the counter
    jmp     .loop


.prime:
    mov     eax, 1
    jmp     .finished

.notPrime:
    mov     eax, 0

.finished:
    pop     edx
    pop     ecx
    pop     ebx
    ret
