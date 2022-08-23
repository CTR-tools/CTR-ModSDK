# exit function (jr ra + return 0)
# disable AntiChip_CheckFraud_Entry in japan builds
.set noreorder
addiu $2, $0, 0x0
jr $31
nop
