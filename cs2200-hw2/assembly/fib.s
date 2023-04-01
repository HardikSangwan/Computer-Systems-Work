!============================================================
! CS 2200 Homework 2 Part 2: fib
!
! Apart from initializing the stack,
! please do not edit main's functionality.
!============================================================

main:
    lea     $sp, stack          ! load ADDRESS of stack label into $sp

    add     $zero, $zero, $zero ! TODO: Here, you need to initialize the stack
                                ! using the label below by loading its
                                ! VALUE into $sp (CHANGE THIS INSTRUCTION)

    lea     $at, fib            ! load address of fib label into $at
    addi    $a0, $zero, 5       ! $a0 = 5, the number a to compute fib(n)
    jalr    $ra, $at            ! jump to fib, set $ra to return addr
    halt                        ! when we return, just halt

fib:
    add     $zero, $zero, $zero ! TODO: perform post-call portion of
                                ! the calling convention. Make sure to
                                ! save any registers you'll be using!

    add     $zero, $zero, $zero ! TODO: Implement the following pseudocode in assembly:
    addi	$t0, $t0, 2         ! IF (a0 <= 1)
    skplt	$a0, t0
    goto 	else
    goto 	base
                                !    GOTO BASE
                                ! ELSE
                                !    GOTO ELSE

base:
    add     $zero, $zero, $zero ! TODO: If $a0 is less than 0, set $a0 to 0
    addi    $v0, $a0, 0         ! return a
    goto    teardown            ! teardown the stack

else:
    add     $zero, $zero, $zero ! TODO: Save the value of the $a0 into a saved register

    addi    $a0, $a0, -1        ! $a0 = $a0 - 1 (n - 1)

    add     $zero, $zero, $zero ! TODO: Implement the recursive call to fib
                                ! You should not have to set any of the argument registers here.
                                ! Per the PDF, do not save any temp registers!

    add     $zero, $zero, $zero ! TODO: Save the return value of the fib call into a register

    add     $zero, $zero, $zero ! TODO: Restore the old value of $a0 that we saved earlier

    addi    $a0, $a0, -2        ! $a0 = $a0 - 2 (n - 2)

    add     $zero, $zero, $zero ! TODO: Implement the recursive call to fib
                                ! If your previous recursive call worked correctly,
                                ! you should be able to copy and paste it here :)

    add     $zero, $zero, $zero ! TODO: Compute fib(n - 1) [stored from earlier] + fib(n - 2) [just computed]
                                ! Place the sum of those two values into $v0
    goto    teardown            ! return
    
teardown:
    add     $zero, $zero, $zero ! TODO: perform pre-return portion
                                !       of the calling convention

    jalr    $zero, $ra          ! return to caller

stack: .word 0xFFFF             ! the stack begins here
