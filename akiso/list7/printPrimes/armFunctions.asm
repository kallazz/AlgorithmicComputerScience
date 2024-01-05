@--------------------------------------------------------------------------------------------------
@ bool isPrime(int number)
@ checks if the provided number is prime
@ r0 should contain the number to check
@ r1 will be set to 0 if the number is not prime and to 1 if it is prime
isPrime:
    push    {r5, r6, r7, lr}        @ push the values to the stack to save them

    cmp     r0, #2                  @ compare the number to 2
    blt     notPrime                @ if the number is less than 2, it is not prime

    mov     r7, r0                  @ move the number to r7
    lsr     r5, r0, #1              @ calculate number / 2 by doing bit shift right, r5 = (r0 >> 1)

    mov     r6, #2                  @ set the loop counter to 2
loop:
    cmp     r6, r5                  @ check if counter >= n/2
    bgt     prime                   @ if so, stop comparing, the number is prime

    mov     r0, r7                  @ load the number
    mov     r1, r6                  @ load the counter as a divisor
    bl      __aeabi_uidivmod        @ divide and get the result in r0 and the remainder in r1
    cmp     r1, #0                  @ see if the remainder is zero
    beq     notPrime                @ if so, the number is not prime

    add     r6, r6, #1              @ increment the loop counter
    b       loop                    @ go back to the loop label
prime:
    mov     r1, #1                  @ set r1 = 1, because the number is prime
    b       finished                @ go to the finished label

notPrime:
    mov     r1, #0                  @ set r1 = 0, because the number is not prime

finished:
    pop     {r5, r6, r7, lr}        @ restore the saved values
    bx      lr                      @ return back to where the function was called from
