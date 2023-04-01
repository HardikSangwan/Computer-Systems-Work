;;=======================================
;; CS 2110 - Spring 2019
;; Homework 7
;;=======================================
;; Name: Hardik Sangwan
;;=======================================

;; Little reminder from your friendly neighborhood 2110 TA staff:
;; don't run this directly by pressing 'RUN' in complx, since there is nothing
;; put at address x3000. Instead, load it and use 'Debug' -> 'Simulate Subroutine
;; Call' and choose the 'decimalStringToInt' label.

.orig x3000
	halt

MULT
	ADD R6, R6, -4 	
	STR R7, R6, 2		
	STR R5, R6, 1 	
	ADD R5, R6, 0

	ADD R6, R6, -3
	STR R0, R5, -1
	STR R1, R5, -2
	STR R2, R5, -3

	LDR R0, R5, 4
	LDR R1, R5, 5
	AND R2, R2, 0
LOOPM 
	ADD R2, R0, 0
	ADD R1, R1, -1
	BRP LOOPM
SAVEM
	STR R2, R5, 3

	LDR R0, R5, 0
	LDR R1, R5, -1
	LDR R2, R5, -2

	ADD R6, R5, 0
	LDR R7, R6, 2
	LDR R5, R6, 1
	ADD R6, R6, 3
	RET 					;RETURN


LENGTH
	ADD R6, R6, -4 	
	STR R7, R6, 2		
	STR R5, R6, 1 	
	ADD R5, R6, 0

	ADD R6, R6, -2
	STR R0, R5, 0
	STR R1, R5, -1
	LDR R0, R5, 4
	AND R1, R1, 0
LOOPL 
	ADD R1, R1, 1
	LDR R0, R0, 1
	BRNP LOOPL
SAVEL
	STR R1, R5, 3

	LDR R0, R5, 0
	LDR R1, R5, -1
	
	ADD R6, R5, 0
	LDR R7, R6, 2
	LDR R5, R6, 1
	ADD R6, R6, 3
	RET 					;RETURN					

decimalStringToInt
	LD R6, STACK
	ADD R6, R6, -4	;Allocate space for core stack frame
	STR R7, R6, 2	;Save the return address
	STR R5, R6, 1	;Save oold FP
	ADD R5, R6, 0	;Set new FP		

	ADD R6, R6, -5
	STR R0, R5, -1
	STR R1, R5, -2
	STR R2, R5, -3
	STR R3, R5, -4
	STR R4, R5, -5
	LDR R2, R5, 4
	AND R0, R0, 0		;Answer/Return value
	AND R3, R3, 0 		;i in R3
	STR R2, R6, 0
	JSR LENGTH
	LDR R1, R6, 0
	ADD R6, R6, 1 		;length from length subroutine in R1
	LDR R4, R2, 0

LOOPD
	NOT R1, R1 			;Loop Check against length
	ADD R1, R1, 1
	ADD R3, R3, R1
	BRZP END
	ADD R3, R3, 1		;Increment of i
	ADD R6, R6, -1		;Passing 10 as argument for MULT
	ADD R2, R2, 10
	STR R2, R6, 0
	ADD R6, R6, -1		;Passing current return value as argument for mult
	STR R0, R6, 0
	JSR MULT
	LDR R0, R6, 0		;Loading answer from mult in answer
	ADD R6, R6, 1
	LDR R4, R4, 1		;Adding character at ith position of string address to answer as an integer
	LD R2, NUM
	NOT R2, R2
	ADD R2, R2, 1
	ADD R4, R4, R2
	ADD R0, R0, R5
	BR LOOPD

END
	STR R0, R5, 3		;Storing answer
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

NUM .fill 48
; Needed by Simulate Subroutine Call in complx
STACK .fill xF000
.end

.orig x6000
.stringz "10098"
.end


ADDR6,R6,#-1; push(B)
LDR0,B
STRR0,R6,#0
ADDR6,R6,#-1; push(A)
LDR0,A
STRR0,R6,#0
JSRDIV; M = DIV(A,B)
LDRR0,R6,#0
STR0,M
ADDR6,R6,#3; pop(), pop(), pop()


ADDR6, R6, -1 ; push(3(
ANDR0, R0, 0
ADDR0, R0, 3
STRR0, R6, 0
ADDR6, R6, -1 ; push(1(
ANDR0, R0, 0
ADD R0, R0, 1
STRR0, R6, 0
ADDR6, R6, -1 ; push(x(
LDR0, X
STRR0, R6, 0
JSRFOO     ; foo()

ADDR6, R6, -4 ; push 4 wds; set rv later
STRR7, R6, 2  ; save RA
STRR5, R6, 1  ; save old FP       ; set lv 0/1 later
ADDR5, R6, 0  ; FP = SP
ADDR6, R6, -3 ; push 3 wds    ; 2+2-1
STRR1, R5, -2 ; save SR1
STRR2, R5, -3 ; save SR2

i.e. return a + b – c;
LDRR1, R5, 4 ; a + b
LDRR2, R5, 5
ADDR1, R1, R2
STRR1, R5, 0; d=a+b
LDR R2, R5, 6; -c
NOTR2, R2
ADDR2, R2, 1
ADDR1, R1, R2
STRR1, R5, -1; e=d-c
STRR1, R5, 3

LDRR1, R5, -2 ; restore R1
LDRR2, R5, -3 ; restore R2
ADDR6, R5, 0  ; pop lv+sr
LDRR7, R5, 2  ; R7 = RA
LDRR5, R5, 1  ; FP = OldFP
ADDR6, R6, 3  ; pop 3 wds
RET; foo() is done!

LDR0, X
STRR0, R6, 0
JSRFOO     ; foo()
LDRR0, R6, 0   ; m = RV
STR0, M
ADDR6, R6, 4   ; pop 4 wds
