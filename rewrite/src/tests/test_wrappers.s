.set noreorder
.align 2
.macro SAVE_CONTEXT
    addiu  $sp, $sp, -44
    sw     $s0, 0($sp)
    sw     $s1, 4($sp)
    sw     $s2, 8($sp)
    sw     $s3, 12($sp)
    sw     $s4, 16($sp)
    sw     $s5, 20($sp)
    sw     $s6, 24($sp)
    sw     $s7, 28($sp)
    sw     $fp, 32($sp)
    sw     $gp, 36($sp)
    sw     $ra, 40($sp)
.endm

.macro RESTORE_CONTEXT
    lw     $ra, 40($sp)
    lw     $gp, 36($sp)
    lw     $fp, 32($sp)
    lw     $s7, 28($sp)
    lw     $s6, 24($sp)
    lw     $s5, 20($sp)
    lw     $s4, 16($sp)
    lw     $s3, 12($sp)
    lw     $s2, 8($sp)
    lw     $s1, 4($sp)
    lw     $s0, 0($sp)
    addiu  $sp, $sp, 44
.endm

.global WRAPPER_ND_COLL_BarycentricTest
.type WRAPPER_ND_COLL_BarycentricTest, @function
WRAPPER_ND_COLL_BarycentricTest:
    SAVE_CONTEXT
    jal    ND_COLL_BarycentricTest
    nop
    RESTORE_CONTEXT
    jr     $ra
    nop
