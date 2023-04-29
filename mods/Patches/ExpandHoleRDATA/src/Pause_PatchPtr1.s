# overwrite function to use 8001 + 0000,
# rather than the default 8001 + whatever
.set noreorder
addiu $10, $2, 0x0
