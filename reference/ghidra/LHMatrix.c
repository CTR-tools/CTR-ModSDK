// LHMatrix = Link Hierarchal Matrix

// LHMatrix_Parent
// param1 - instance_dst
// param2 - instance_src
// param3 - transform vector (x,y,z)
void FUN_800313c8(int param_1,int param_2,undefined4 *param_3)

{
  undefined4 in_zero;
  undefined4 in_at;
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;

  // each matrix has 3x3 shorts, which is 9 shorts,
  // which is 18 bytes, or 0x12 bytes

  // Copy rotation from one instance to another
  uVar1 = *(undefined4 *)(param_2 + 0x34);
  uVar2 = *(undefined4 *)(param_2 + 0x38);
  uVar3 = *(undefined4 *)(param_2 + 0x3c);
  *(undefined4 *)(param_1 + 0x30) = *(undefined4 *)(param_2 + 0x30);
  *(undefined4 *)(param_1 + 0x34) = uVar1;
  *(undefined4 *)(param_1 + 0x38) = uVar2;
  *(undefined4 *)(param_1 + 0x3c) = uVar3;

  // Get position from one instance
  uVar1 = *(undefined4 *)(param_2 + 0x44);
  uVar2 = *(undefined4 *)(param_2 + 0x48);
  uVar3 = *(undefined4 *)(param_2 + 0x4c);

  // one more rotation variable
  *(undefined4 *)(param_1 + 0x40) = *(undefined4 *)(param_2 + 0x40);

  // set position to the other instance
  *(undefined4 *)(param_1 + 0x44) = uVar1;
  *(undefined4 *)(param_1 + 0x48) = uVar2;
  *(undefined4 *)(param_1 + 0x4c) = uVar3;

  // set the new matrix

  SetRotMatrix((MATRIX *)(param_1 + 0x30));
  SetTransMatrix((MATRIX *)(param_1 + 0x30));

  // (x,y,z,0)
  setCopReg(2,cop_r0,param_3[0]);
  setCopReg(2,cop_r1,param_3[1]);

  // rtv0tr   cop2 $0480012  v0 * rotmatrix + tr vector
  copFunction(2,0x480012);

  uVar1 = getCopReg(2,0x19);
  *(undefined4 *)(param_1 + 0x44) = uVar1;
  uVar1 = getCopReg(2,0x1a);
  *(undefined4 *)(param_1 + 0x48) = uVar1;
  uVar1 = getCopReg(2,0x1b);
  *(undefined4 *)(param_1 + 0x4c) = uVar1;
  return;
}
