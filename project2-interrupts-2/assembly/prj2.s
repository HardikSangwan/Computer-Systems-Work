! This program executes pow as a test program using the LC 2200 calling convention
! Check your registers ($v0) and memory to see if it is consistent with this program

        ! vector table
vector0:
        .fill 0x00000000                        ! device ID 0
        .fill 0x00000000                        ! device ID 1
        .fill 0x00000000                        ! ...
        .fill 0x00000000
        .fill 0x00000000
        .fill 0x00000000
        .fill 0x00000000
        .fill 0x00000000
        .fill 0x00000000
        .fill 0x00000000
        .fill 0x00000000
        .fill 0x00000000
        .fill 0x00000000
        .fill 0x00000000
        .fill 0x00000000
        .fill 0x00000000                        ! device ID 15
        ! end vector table

main:	lea $sp, initsp                         ! initialize the stack pointer
        lw $sp, 0($sp)                          ! finish initialization

                                                ! Install keyboard interrupt handler into vector table
        lea  $a0, timer_handler
        lea  $a1, vector0
        sw   $a0, 0x1($a1)

                                                ! Install keyboard interrupt handler into vector table
        lea $t0, keyboard_handler
        lea  $a1, vector0
        sw   $a0, 0x2($a1)
        
        EI                                      ! Enable interrupts

        lea $a0, BASE                           ! load base for pow
        lw $a0, 0($a0)
        lea $a1, EXP                            ! load power for pow
        lw $a1, 0($a1)
        lea $at, POW                            ! load address of pow
        jalr $ra, $at                           ! run pow
        lea $a0, ANS                            ! load base for pow
        sw $v0, 0($a0)

        halt                                    ! stop the program here
        addi $v0, $zero, -1                     ! load a bad value on failure to halt

BASE:   .fill 2
EXP:    .fill 8
ANS:	.fill 0                                 ! should come out to 256 (BASE^EXP)

POW:    addi $sp, $sp, -1                       ! allocate space for old frame pointer
        sw $fp, 0($sp)

        addi $fp, $sp, 0                        ! set new frame pinter
        
        skplt $zero, $a1                        ! check if $a1 is zero (if not, skip the goto)
        goto RET1                               ! if the power is 0 return 1
        skplt $zero, $a0
        goto RET0                               ! if the base is 0 return 0 (otherwise, the goto was skipped)

        addi $a1, $a1, -1                       ! decrement the power

        lea $at, POW                            ! load the address of POW
        addi $sp, $sp, -2                       ! push 2 slots onto the stack
        sw $ra, -1($fp)                         ! save RA to stack
        sw $a0, -2($fp)                         ! save arg 0 to stack
        jalr $ra, $at                           ! recursively call POW
        add $a1, $v0, $zero                     ! store return value in arg 1
        lw $a0, -2($fp)                         ! load the base into arg 0
        lea $at, MULT                           ! load the address of MULT
        jalr $ra, $at                           ! multiply arg 0 (base) and arg 1 (running product)
        lw $ra, -1($fp)                         ! load RA from the stack
        addi $sp, $sp, 2

        goto FIN                                ! return

RET1:   addi $v0, $zero, 1                      ! return a value of 1
        skplt $zero, $v0                        ! convenient use of skplt to get to FIN (0 < 1)

RET0:   add $v0, $zero, $zero                   ! return a value of 0

FIN:	lw $fp, 0($fp)                          ! restore old frame pointer
        addi $sp, $sp, 1                        ! pop off the stack
        jalr $zero, $ra

MULT:   add $v0, $zero, $zero                   ! return value = 0
        addi $t0, $zero, 1                      ! sentinel = 0
AGAIN:  add $v0, $v0, $a0                       ! return value += argument0
        addi $t0, $t0, 1                        ! increment sentinel
        skplt $a1, $t0                          ! if $t0 <= $a1, keep looping
        goto AGAIN                              ! loop again

        jalr $zero, $ra                         ! return from mult

timer_handler:
        addi $sp, $sp, -1
        sw $k0, 0x0($sp)                     ! save $k0 register

        EI                                   ! enable interrupt

        addi $sp, $sp, -1                     ! save registers
        sw $at, 0x0($sp)
        addi $sp, $sp, -1
        sw $v0, 0x0($sp)
        addi $sp, $sp, -1
        sw $a0, 0x0($sp)
        addi $sp, $sp, -1
        sw $a1, 0x0($sp)
        addi $sp, $sp, -1
        sw $a2, 0x0($sp)
        addi $sp, $sp, -1
        sw $t0, 0x0($sp)
        addi $sp, $sp, -1
        sw $t1, 0x0($sp)
        addi $sp, $sp, -1
        sw $t2, 0x0($sp)
        addi $sp, $sp, -1
        sw $s0, 0x0($sp)
        addi $sp, $sp, -1
        sw $s1, 0x0($sp)
        addi $sp, $sp, -1
        sw $s2, 0x0($sp)
        addi $sp, $sp, -1
        sw $fp, 0x0($sp)
        addi $sp, $sp, -1
        sw $ra, 0x0($sp)
        addi $sp, $sp, -1
        sw $sp, 0x0($sp)
            
        lea  $t1, ticks                      ! main interrrupt handler logic 
        lw $t0, 0x0($t1)
        lw $t2, 0x0($t0)
        addi $t2, $t2, 1
        sw $t2, 0x0($t0)

        lw $sp, 0x0($sp)                      ! save registers
        addi $sp, $sp, 1
        lw $ra, 0x0($sp)
        addi $sp, $sp, 1
        lw $fp, 0x0($sp)
        addi $sp, $sp, 1
        lw $s2, 0x0($sp)
        addi $sp, $sp, 1
        lw $s1, 0x0($sp)
        addi $sp, $sp, 1
        lw $s0, 0x0($sp)
        addi $sp, $sp, 1
        lw $t2, 0x0($sp)
        addi $sp, $sp, 1
        lw $t1, 0x0($sp)
        addi $sp, $sp, 1
        lw $t0, 0x0($sp)
        addi $sp, $sp, 1
        lw $a2, 0x0($sp)
        addi $sp, $sp, 1
        lw $a1, 0x0($sp)
        addi $sp, $sp, 1
        lw $a0, 0x0($sp)
        addi $sp, $sp, 1
        lw $v0, 0x0($sp)
        addi $sp, $sp, 1
        lw $at, 0x0($sp)
        addi $sp, $sp, 1

        DI                                    ! disable interrupt
      
        lw   $k0, 0x0($sp)                    ! restore $k0 register
        addi $sp, $sp, 1

        RETI                                  ! return from interrupt

keyboard_handler:
        addi $sp, $sp, -1
        sw $k0, 0x0($sp)

        EI

        addi $sp, $sp, -1
        sw $at, 0x0($sp)
        addi $sp, $sp, -1
        sw $v0, 0x0($sp)
        addi $sp, $sp, -1
        sw $a0, 0x0($sp)
        addi $sp, $sp, -1
        sw $a1, 0x0($sp)
        addi $sp, $sp, -1
        sw $a2, 0x0($sp)
        addi $sp, $sp, -1
        sw $t0, 0x0($sp)
        addi $sp, $sp, -1
        sw $t1, 0x0($sp)
        addi $sp, $sp, -1
        sw $t2, 0x0($sp)
        addi $sp, $sp, -1
        sw $s0, 0x0($sp)
        addi $sp, $sp, -1
        sw $s1, 0x0($sp)
        addi $sp, $sp, -1
        sw $s2, 0x0($sp)
        addi $sp, $sp, -1
        sw $fp, 0x0($sp)
        addi $sp, $sp, -1
        sw $ra, 0x0($sp)
        addi $sp, $sp, -1
        sw $sp, 0x0($sp)

        IN $s0, 0x2              
        lea $t1, key_buf_ptr     
        lw $t0, 0x0($t1)         
        sw $s0, 0x0($t0)         
        addi $t0, $t0, 1         
        sw $t0, 0x0($t1)         

        lw $sp, 0x0($sp)
        addi $sp, $sp, 1
        lw $ra, 0x0($sp)
        addi $sp, $sp, 1
        lw $fp, 0x0($sp)
        addi $sp, $sp, 1
        lw $s2, 0x0($sp)
        addi $sp, $sp, 1
        lw $s1, 0x0($sp)
        addi $sp, $sp, 1
        lw $s0, 0x0($sp)
        addi $sp, $sp, 1
        lw $t2, 0x0($sp)
        addi $sp, $sp, 1
        lw $t1, 0x0($sp)
        addi $sp, $sp, 1
        lw $t0, 0x0($sp)
        addi $sp, $sp, 1
        lw $a2, 0x0($sp)
        addi $sp, $sp, 1
        lw $a1, 0x0($sp)
        addi $sp, $sp, 1
        lw $a0, 0x0($sp)
        addi $sp, $sp, 1
        lw $v0, 0x0($sp)
        addi $sp, $sp, 1
        lw $at, 0x0($sp)
        addi $sp, $sp, 1
        

        DI

        
        lw   $k0, 0x0($sp)                    
        addi $sp, $sp, 1

        RETI

initsp: .fill 0xA000

ticks:  .fill 0xFFFF
key_buf_ptr: .fill 0xFFE0
