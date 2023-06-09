;;=============================================================
;;CS 2110 - Spring 2019
;;Homework 7 - Recursive Reverse Linked List
;;=============================================================
;;Name:
;;=============================================================

.orig x3000
    ;; Below is a main function that will:
    ;;      - Print the linked list before reversing
    ;;      - Reverse the linked list
    ;;      - Print the reversed linked list
    ;; You shouldn't need to change this main function.

    LDI R1, LL          ; Load first node to R1
    JSR print_ll

    LD R6, STACK        ; Initialize stack pointer
    ADD R6, R6, -1      ; Make room on stack for argument
    STR R1, R6, 0       ; Place first node on stack as argument
    JSR reverse

    LDR R1, R6, 0       ; Load result of reverse
    JSR print_ll
    halt


reverse
;;=============================================================
;; YOUR CODE GOES HERE

;;=============================================================


; A subroutine that will print a linked list
; given the first node is in R1
print_ll
    ST R0, Save0        ; Save R0
    ST R1, Save1        ; Save R1
    ST R7, Save7        ; Save R7
    LD R0, QUOTES       ; print('"')
    OUT
loop
    LDR R0, R1, 1       ; R0 = curr.val
    OUT                 ; print(curr.val)
    LDR R1, R1, 0       ; R1 = curr.next
    BRz print_done      ; curr.next == null -> done
    BRnzp loop          ;
print_done
    LD R0, QUOTES       ; print('"')
    OUT
    LD R0, NEWLINE      ; print('\n')
    OUT
    LD R0, Save0        ; Restore R0
    LD R1, Save1        ; Restore R1
    LD R7, Save7        ; Restore R7
    RET
Save0       .blkw 1
Save1       .blkw 1
Save7       .blkw 1
QUOTES      .fill '"'
NEWLINE     .fill '\n'

LL .fill x6000
STACK .fill xF000
.end

.orig x4000
.fill x4002         ; x4000
.fill 'a'           ; x4001
.fill x4004         ; x4002
.fill 'b'           ; x4003
.fill x4006         ; x4004
.fill 'c'           ; x4005
.fill x4008         ; x4006
.fill 'd'           ; x4007
.fill x400A         ; x4008
.fill 'e'           ; x4009
.fill x0000         ; x400A
.fill 'f'           ; x400B
.end


.orig x6000
.fill x4000
.fill 6
.end
