;;=======================================
;; CS 2110 - Spring 2019
;; Timed Lab 4
;;=======================================
;; Name: Hardik Sangwan
;;=======================================

;; A little reminder from your friendly neighborhood 2110 TA staff:
;; Do not try to run this directly by pressing 'RUN' in Complx.
;; Instead, load it and use 'Debug' -> 'Simulate Subroutine Call'
;; and choose the 'countMult7' label.

.orig x3000

halt ; Do not remove this line – see note above

; mod(a, b)
;
; This looks funky, but it is a subroutine you can call
; like normal. Just be sure to use the LC3 calling convention!
;
; return 1 if a % b == 0 and 0 otherwise
mod
    .fill x1dbf
    .fill x1dbf
    .fill x7f80
    .fill x1dbf
    .fill x7b80
    .fill x1dbf
    .fill x1ba0
    .fill x1dbe
    .fill x7381
    .fill x7580
    .fill x6344
    .fill x6545
    .fill x94bf
    .fill x14a1
    .fill x1242
    .fill x0402
    .fill x0805
    .fill x03fc
    .fill x5260
    .fill x1261
    .fill x7343
    .fill x0e02
    .fill x5260
    .fill x7343
    .fill x6580
    .fill x6381
    .fill x1d63
    .fill x6f42
    .fill x6b41
    .fill xc1c0

; return count of arguments that are multiples of 7
countMult7 ; countMult7(a, ...)
    ; TODO Stack SETUP code here
    ADD R6, R6, -4  
    STR R7, R6, 2       
    STR R5, R6, 1   
    ADD R5, R6, 0

    ADD R6, R6, -5
    STR R0, R5, -1
    STR R1, R5, -2
    STR R2, R5, -3
    STR R3, R5, -4
    STR R4, R5, -5

    AND R0, R0, 0
    AND R1, R1, 0
    AND R2, R2, 0
    AND R3, R3, 0
    AND R4, R4, 0

    LDR R1, R5, 5
    LDR R0, R5, 4
    ST R0, CHECKPOINT1
    LDR R0, R5, 4
    BRp NOTZERO
    ST R0, CHECKPOINT2
    BR RETURN
NOTZERO
    ST R1, CHECKPOINT2
    BR LOOP
    ; TODO your function body code here
LOOP
    ADD R6, R6, -1
    AND R2, R2, 0
    ADD R2, R2, 7
    STR R2, R6, 0
    ADD R6, R6, -1
    STR R1, R6, 0
    JSR mod
    LDR R2, R6, 0
    ADD R3, R3, R2
    LDR R1, R5, 6
    ADD R0, R0, -1
    BRp LOOP
    BR RETURN

RETURN
    LDR R3, R5, 3
    BR TEARDOWN

    ; TODO your TEARDOWN code here
TEARDOWN
    LDR R0, R5, -1
    LDR R1, R5, -2
    LDR R2, R5, -3
    LDR R3, R5, -4
    LDR R4, R5, -5

    ADD R6, R5, 0
    LDR R7, R6, 2
    LDR R5, R6, 1
    ADD R6, R6, 3
    RET

; Do not remove or modify anything below this line
; Needed for subroutine calls and grading
STACK .fill xF000
CHECKPOINT1 .blkw 1 ; Should store n
CHECKPOINT2 .blkw 1 ; Should store address of first variable argument

.end
