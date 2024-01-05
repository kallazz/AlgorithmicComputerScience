@ compile: arm-none-eabi-as main.asm -o main.o && arm-none-eabi-gcc -specs=rdimon.specs main.o
@ run:     qemu-arm-static a.out

.include "armFunctions.asm"

.data
format_str: .asciz "%d\n"       @ format for printf

.text
.global main
.extern printf
main:
    ldr     r4, =#100000        @ set how many times to execute the loop
    mov     r5, #0              @ set loop counter to 0

main_loop:
    add     r5, r5, #1          @ increment the loop counter
    cmp     r5, r4              @ check if loop counter reached max number
    beq     main_finished       @ if so, finish the program

    mov     r0, r5              @ set current number as the argument for isPrime
    bl      isPrime             @ call isPrime
    cmp     r1, #1              @ check if the provided number is prime
    beq     main_printNumber    @ if so, print it

    b       main_loop           @ go back to the loop

main_printNumber:
    ldr     r0, =format_str     @ set the format for printing
    mov     r1, r5              @ pass the current number as the value to print
    bl      printf              @ call printf
    b       main_loop           @ go back to the loop

main_finished:
    mov     r7, #1              @ syscall for exiting
    mov     r0, #0              @ exit code
    swi     0                   @ make the syscall
