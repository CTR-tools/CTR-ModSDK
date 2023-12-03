# start 8006a8e0
.set noreorder
.set noat

#$6: &instance
#$23: &modelFrame->verts[0]
#$30: &ptrDelta[1]

#$28: ptrColors
#$29: ptrTexLayout

srl        $5,$11,0xd
andi       $5,$5,0x7f8
sll        $3,$11,0x5

bgez       $3,LAB_8006a900
addu      $5,$5,$1

lw         $8,0x140($5)

bgez       $0,LAB_8006aa80
lw        $3,0x144($5)

LAB_8006a900:

#if no ptrDelta, quit function
bne        $30,$0,LAB_8006a91c
andi      $8,$23,0x2

#basically, just quit function
addiu      $23,$23,0x3

beq        $8,$0,LAB_8006aa50
lwr       $3,-0x3($23)

bgez       $0,LAB_8006aa50
lwl       $3,0x0($23)

LAB_8006a91c:

#if ptrDelta is valid,
#$20 = ptrDelta[x]
# ptrDelta++
lw         $20,0x0($30)
addiu      $30,$30,0x4

# ((delta >> 6) & 7) ^ 0x1f
srl        $3,$20,0x6
andi       $3,$3,0x7
xori       $8,$3,0x1f
addiu      $3,$3,0x1
addiu      $10,$3,-0x8
addu       $19,$19,$3

blez       $19,LAB_8006a968
srav      $9,$17,$8

move       $9,$17

#$17 = model->verts[x]
#model->verts++
lw         $17,0x0($23)
addiu      $23,$23,0x4

subu       $3,$3,$19
srlv       $3,$17,$3
or         $9,$9,$3
srav       $9,$9,$8
move       $3,$19
addiu      $19,$19,-0x20

LAB_8006a968:

beq        $10,$0,LAB_8006a984
sllv      $17,$17,$3

# ((delta >> 0x19) & 7) ^ 0x1f
sra        $8,$20,0x19
sll        $8,$8,0x1
lb         $3,0x58($1)
addu       $9,$9,$8
addu       $9,$9,$3

LAB_8006a984:

# 0x58 = X
sb         $9,0x58($1)

srl        $3,$20,0x3
andi       $3,$3,0x7
xori       $8,$3,0x1f
addiu      $3,$3,0x1
addiu      $10,$3,-0x8
addu       $19,$19,$3

blez       $19,LAB_8006a9cc
srav      $9,$17,$8

move       $9,$17

#$17 = model->verts[x]
#model->verts++
lw         $17,0x0($23)
addiu      $23,$23,0x4

subu       $3,$3,$19
srlv       $3,$17,$3
or         $9,$9,$3
srav       $9,$9,$8
move       $3,$19
addiu      $19,$19,-0x20

LAB_8006a9cc:

beq        $10,$0,LAB_8006a9e8
sllv      $17,$17,$3

# ((delta << 7) >> 0x18)
sll        $8,$20,0x7
sra        $8,$8,0x18
lb         $3,0x5a($1)
addu       $9,$9,$8
addu       $9,$9,$3

LAB_8006a9e8:

# 0x5A = Z
sb         $9,0x5a($1)

# (delta & 0b111) ^ 0x1f
andi       $3,$20,0x7
xori       $8,$3,0x1f
addiu      $3,$3,0x1
addiu      $10,$3,-0x8
addu       $19,$19,$3

blez       $19,LAB_8006aa2c
srav      $9,$17,$8

move       $9,$17

#$17 = model->verts[x]
#model->verts++
lw         $17,0x0($23)
addiu      $23,$23,0x4

subu       $3,$3,$19
srlv       $3,$17,$3
or         $9,$9,$3
srav       $9,$9,$8
move       $3,$19
addiu      $19,$19,-0x20

LAB_8006aa2c:

beq        $10,$0,LAB_8006aa48
sllv      $17,$17,$3

# ((delta << 0xf) >> 0x18)
sll        $8,$20,0xf
sra        $8,$8,0x18
lb         $3,0x59($1)
addu       $9,$9,$8
addu       $9,$9,$3

LAB_8006aa48:

# 0x59 = Y
sb         $9,0x59($1)

# XZY in one 4-byte register
lw         $3,0x58($1)

LAB_8006aa50:
lw         $10,0x30($1)
and        $8,$3,$12
addu       $8,$8,$10
sll        $8,$8,0x2
and        $8,$8,$13
lw         $10,0x34($1)
srl        $3,$3,0x8
andi       $3,$3,0xff
addu       $3,$3,$10
sll        $3,$3,0x2
sw         $8,0x140($5)
sw         $3,0x144($5)

# from here to bottom: all color data

LAB_8006aa80:
srl        $9,$11,0x7
sll        $10,$11,0x4

bltz       $10,LAB_8006aa9c
andi      $9,$9,0x1fc

addu       $9,$9,$28

jr         $31
lw        $9,0x0($9)

LAB_8006aa9c:
addu       $9,$9,$1

jr         $31
lw        $9,0x140($9)

#$9, return color

# end 8006aaa8
