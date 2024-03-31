
// draws heat effect as found in tiger temple (fire) or behind rockets
void FUN_8004b470(int *param_1,int param_2,int param_3,int param_4,undefined4 param_5)

{
  bool bVar1;
  short sVar2;
  int iVar3;
  undefined4 uVar4;
  uint uVar5;
  int iVar6;
  undefined4 uVar7;
  uint uVar8;
  undefined4 uVar9;
  int iVar10;
  uint uVar11;
  uint uVar12;
  uint uVar13;
  int iVar14;
  undefined4 unaff_s0;
  undefined4 unaff_s1;
  undefined4 unaff_s2;
  undefined4 unaff_s3;
  undefined4 unaff_s4;
  undefined4 unaff_s5;
  undefined4 unaff_s6;
  uint uVar15;
  undefined4 unaff_s7;
  uint uVar16;
  uint uVar17;
  int iVar18;
  undefined4 unaff_s8;
  undefined4 unaff_retaddr;
  undefined auStackX0 [16];
  
  iVar3 = 0x1f800000;
  DAT_1f800020 = &DAT_8008cf6c;
  param_4 = param_4 + -1;
  uVar4 = *(undefined4 *)(param_3 + 0xc);
  DAT_1f800000 = unaff_s0;
  DAT_1f800004 = unaff_s1;
  DAT_1f800008 = unaff_s2;
  DAT_1f80000c = unaff_s3;
  DAT_1f800010 = unaff_s4;
  DAT_1f800014 = unaff_s5;
  DAT_1f800018 = unaff_s6;
  DAT_1f80001c = unaff_s7;
  DAT_1f800024 = (undefined *)register0x00000074;
  DAT_1f800028 = unaff_s8;
  DAT_1f80002c = unaff_retaddr;
  DAT_1f800030 = (int)param_1;
  if (param_1 != (int *)0x0) {
    DAT_1f800038 = param_5;
    iVar18 = 0xc;
    DAT_1f80005c._2_2_ = 0;
    do {
      uVar11 = *(uint *)(param_2 + 0x28);
      uVar12 = *(uint *)(param_2 + 0x30);
      uVar5 = *(uint *)(param_2 + 0x3c);
      iVar6 = *(int *)(param_2 + 0x40);
      uVar7 = *(undefined4 *)(param_2 + 0x44);
      gte_ldL11L12(uVar11);
      gte_ldL13L21(*(undefined4 *)(param_2 + 0x2c));
      gte_ldL22L23(uVar12);
      gte_ldL31L32(*(undefined4 *)(param_2 + 0x34));
      gte_ldL33(*(undefined4 *)(param_2 + 0x38));
      gte_ldbkdir(uVar5,iVar6,uVar7);
      gte_ldR11R12(0x1000);
      gte_ldR13R21(0);
      gte_ldR31R32(0);
      gte_ldR33(0x1000);
      gte_ldtr(0,0,0);
      sVar2 = *(short *)(param_2 + 0x22);
      uVar9 = *(undefined4 *)(param_2 + 0x18);
      *(int *)(iVar3 + 0x48) = (int)*(short *)(param_2 + 0x20) << 0xf;
      *(int *)(iVar3 + 0x4c) = (int)sVar2 << 0xf;
      gte_ldH(uVar9);
      sVar2 = *(short *)(param_2 + 0x1e);
      *(undefined2 *)(iVar3 + 0x50) = *(undefined2 *)(param_2 + 0x1c);
      *(short *)(iVar3 + 0x52) = sVar2 + (short)*(undefined4 *)(iVar3 + 0x38);
      sVar2 = *(short *)(param_2 + 0x22);
      *(short *)(iVar3 + 0x54) = *(short *)(param_2 + 0x20) + -1;
      *(short *)(iVar3 + 0x56) = sVar2 + -1;
      iVar14 = *(int *)(param_2 + 0x20);
      while (param_1 != (int *)0x0) {
        gte_ldVXY0(param_1[9] >> 8 & 0xffffU | (param_1[0xb] >> 8) << 0x10);
        gte_ldVZ0(param_1[0xd] >> 8);
        uVar15 = (uint)*(byte *)((int)param_1 + 0x3d);
        uVar16 = (uint)*(byte *)((int)param_1 + 0x45);
        gte_llv0bk_b();
        uVar17 = (uint)*(byte *)((int)param_1 + 0x4d);
        *(uint *)(iVar3 + 0x44) =
             (uint)CONCAT12(*(undefined *)((int)param_1 + 0x6d),
                            CONCAT11(*(undefined *)((int)param_1 + 0x65),
                                     *(undefined *)((int)param_1 + 0x5d)));
        read_mt(uVar5,iVar6,uVar7);
        gte_ldVZ0(uVar7);
        gte_ldVZ1(uVar7);
        gte_ldVZ2(uVar7);
        gte_ldR22R23(0x1000);
        gte_ldOFX(*(undefined4 *)(iVar3 + 0x48));
        gte_ldOFY(*(undefined4 *)(iVar3 + 0x4c));
        gte_ldVXY0(iVar6 << 0x10 | uVar5 & 0xffff);
        gte_rtps_b();
        uVar8 = (int)(uVar15 * 0xb50) >> 0xc;
        uVar5 = gte_stSXY2();
        iVar10 = gte_stFLAG();
        iVar6 = (int)uVar5 >> 0x10;
        uVar5 = uVar5 & 0xffff;
        if (-1 < iVar10 << 0xe) {
          gte_stSXY2();
          gte_ldR22R23(0xa00);
          gte_ldOFX(0);
          gte_ldOFY(0);
          gte_ldVXY0(uVar15);
          gte_ldVXY1(uVar15 << 0x10);
          gte_ldVXY2(uVar8 | uVar8 << 0x10);
          gte_rtpt_b();
          uVar8 = (int)(uVar16 * 0xb50) >> 0xc;
          uVar15 = gte_stSXY0();
          uVar13 = gte_stSXY1();
          gte_ldVXY0(uVar16);
          if ((int)(uVar15 - 0x80) < 0) {
            gte_ldVXY1(uVar16 << 0x10);
            gte_ldVXY2(uVar8 | uVar8 << 0x10);
            uVar4 = FUN_8004b914(uVar5,iVar6);
            if (((0 < ((int)uVar12 >> 0x10) + -0x18) &&
                (uVar8 = ~(uVar11 - iVar14 | uVar15 - iVar14 | uVar12 - iVar14 | uVar13 - iVar14) |
                         uVar11 & uVar15 & uVar12 & uVar13, -1 < (int)uVar8)) &&
               (-1 < (int)(uVar8 << 0x10))) {
              FUN_8004b94c();
              gte_rtpt_b();
              uVar5 = (int)(uVar17 * 0xb50) >> 0xc;
              gte_stSXY0();
              gte_stSXY1();
              gte_ldVXY0(uVar17);
              gte_ldVXY1(uVar17 << 0x10);
              gte_ldVXY2(uVar5 | uVar5 << 0x10);
              FUN_8004b914();
              FUN_8004b94c();
              gte_rtpt_b();
              gte_stSXY0();
              gte_stSXY1();
              FUN_8004b914();
              FUN_8004b94c();
              FUN_8004b9cc();
              FUN_8004bd84(iVar3 + 8,iVar3 + 4);
              FUN_8004c348(iVar3 + 4,iVar3 + 8);
              FUN_8004b9cc();
              FUN_8004bd84(iVar3 + 8,iVar3 + 0xc);
              FUN_8004c348(iVar3 + 0xc,iVar3 + 8);
              FUN_8004b9cc();
              FUN_8004bd84(iVar3 + 0xc,iVar3 + 0x10);
              FUN_8004c348(iVar3 + 0xc,iVar3 + 0x10);
              FUN_8004bd84(iVar3 + 0x10,iVar3 + 0x14);
              FUN_8004c348(iVar3 + 0x14,iVar3 + 0x10);
              FUN_8004b9cc();
              FUN_8004bbe8(iVar3 + 0x18,iVar3 + 0x14);
              FUN_8004c134(iVar3 + 0x18,iVar3 + 0x14);
              FUN_8004b9cc();
              FUN_8004ba4c(iVar3 + 0x1c,iVar3 + 0x18);
              FUN_8004bf20(iVar3 + 0x1c,iVar3 + 0x18);
              FUN_8004b9cc();
              FUN_8004ba4c(iVar3 + 0x20,iVar3 + 0x1c);
              FUN_8004bf20(iVar3 + 0x20,iVar3 + 0x1c);
              FUN_8004b9cc();
              FUN_8004bbe8(iVar3 + 0x20,iVar3 + 4);
              uVar5 = iVar3 + 0x20;
              iVar6 = iVar3 + 4;
              uVar4 = FUN_8004c134(uVar5,iVar6);
            }
          }
        }
        iVar18 = iVar18 + -1;
        param_1 = (int *)*param_1;
        if (iVar18 < 1) goto LAB_8004b8d8;
      }
      param_1 = *(int **)(iVar3 + 0x30);
      param_2 = param_2 + 0x110;
      bVar1 = 0 < param_4;
      param_4 = param_4 + -1;
    } while (bVar1);
  }
LAB_8004b8d8:
  *(undefined4 *)(param_3 + 0xc) = uVar4;
  return;
}


// Should not be empty, Ghidra fail
void FUN_8004b914(void)

{
  // For some reason, Ghidra gives no C code for this

                             **************************************************************
                             *                          FUNCTION                          *
                             **************************************************************
                             undefined FUN_8004b914()
             undefined         v0:1           <RETURN>
                             FUN_8004b914                                    XREF[3]:     FUN_8004b470:8004b6c0(c),
                                                                                          FUN_8004b470:8004b74c(c),
                                                                                          FUN_8004b470:8004b790(c)
        8004b914 23 58 8c 00     subu       t3,a0,t4
             assume gp = <UNKNOWN>
        8004b918 21 60 8c 00     addu       t4,a0,t4
        8004b91c ff ff 6b 31     andi       t3,t3,0xffff
        8004b920 ff ff 8c 31     andi       t4,t4,0xffff
        8004b924 25 58 63 01     or         t3,t3,v1
        8004b928 25 60 83 01     or         t4,t4,v1
        8004b92c 03 74 0e 00     sra        t6,t6,0x10
        8004b930 23 68 ae 00     subu       t5,a1,t6
        8004b934 21 70 ae 00     addu       t6,a1,t6
        8004b938 00 6c 0d 00     sll        t5,t5,0x10
        8004b93c 00 74 0e 00     sll        t6,t6,0x10
        8004b940 25 68 a4 01     or         t5,t5,a0
        8004b944 08 00 e0 03     jr         ra
        8004b948 25 70 c4 01     _or        t6,t6,a0

  return;
}



void FUN_8004b94c(int param_1,int param_2,undefined4 param_3,int param_4)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  undefined4 in_t3;
  undefined4 in_t4;
  undefined4 in_t5;
  undefined4 in_t6;

  uVar2 = gte_stSXY2();
  *(undefined4 *)(param_4 + 0x1c) = in_t3;
  *(undefined4 *)(param_4 + 0xc) = in_t4;
  *(undefined4 *)(param_4 + 4) = in_t5;
  *(undefined4 *)(param_4 + 0x14) = in_t6;
  uVar1 = uVar2 & 0xffff;
  iVar3 = (int)uVar2 >> 0x10;
  *(uint *)(param_4 + 0x20) = param_1 - uVar1 & 0xffff | (param_2 - iVar3) * 0x10000;
  *(uint *)(param_4 + 8) = param_1 + uVar1 & 0xffff | (param_2 - iVar3) * 0x10000;
  *(uint *)(param_4 + 0x18) = param_1 - uVar1 & 0xffff | (param_2 + iVar3) * 0x10000;
  *(uint *)(param_4 + 0x10) = param_1 + uVar1 & 0xffff | (param_2 + iVar3) * 0x10000;
  return;
}



void FUN_8004b9cc(void)

{
  int in_at;
  uint in_v1;
  uint in_t0;

  if ((int)in_v1 < 0) {
    in_v1 = 0;
  }
  else {
    if (-1 < (int)(in_v1 - *(ushort *)(in_at + 0x54))) {
      in_v1 = (uint)*(ushort *)(in_at + 0x54);
    }
  }
  if ((int)in_t0 < 0) {
    in_t0 = 0;
  }
  else {
    if (-1 < (int)(in_t0 - *(ushort *)(in_at + 0x56))) {
      in_t0 = (uint)*(ushort *)(in_at + 0x56);
    }
  }
  *(ushort *)(in_at + 0x62) =
       (ushort)((in_v1 + (int)*(short *)(in_at + 0x50) & 0x3ff) >> 6) |
       (ushort)((in_t0 + (int)*(short *)(in_at + 0x52) & 0x100) >> 4) | 0x100;
  return;
}



// WARNING: Removing unreachable block (ram,0x8004bb5c)

uint * FUN_8004ba4c(int param_1,int param_2)

{
  ushort uVar1;
  ushort uVar2;
  int in_at;
  uint *in_v0;
  char cVar3;
  char cVar4;
  uint uVar5;
  uint uVar6;
  uint *unaff_s6;
  char unaff_s7;

  uVar1 = *(ushort *)(in_at + 0x68);
  cVar3 = (char)uVar1;
  uVar2 = *(ushort *)(in_at + 0x6a);
  cVar4 = (char)uVar2;
  if ((int)(uint)uVar1 < 0) {
    cVar3 = '\0';
  }
  else {
    if (-1 < (int)((uint)uVar1 - (uint)*(ushort *)(in_at + 0x54))) {
      cVar3 = (char)*(undefined2 *)(in_at + 0x54);
    }
  }
  if ((int)(uint)uVar2 < 0) {
    cVar4 = '\0';
  }
  else {
    if (-1 < (int)((uint)uVar2 - (uint)*(ushort *)(in_at + 0x56))) {
      cVar4 = (char)*(undefined2 *)(in_at + 0x56);
    }
  }
  *(char *)(in_at + 0x5c) = (cVar3 - unaff_s7) + (char)*(undefined2 *)(in_at + 0x50);
  *(char *)(in_at + 0x5d) = cVar4 + (char)*(undefined2 *)(in_at + 0x52);
  uVar1 = *(ushort *)(param_1 + 0xb0);
  cVar3 = (char)uVar1;
  uVar2 = *(ushort *)(param_1 + 0xb2);
  cVar4 = (char)uVar2;
  if ((int)(uint)uVar1 < 0) {
    cVar3 = '\0';
  }
  else {
    if (-1 < (int)((uint)uVar1 - (uint)*(ushort *)(in_at + 0x54))) {
      cVar3 = (char)*(undefined2 *)(in_at + 0x54);
    }
  }
  if ((int)(uint)uVar2 < 0) {
    cVar4 = '\0';
  }
  else {
    if (-1 < (int)((uint)uVar2 - (uint)*(ushort *)(in_at + 0x56))) {
      cVar4 = (char)*(undefined2 *)(in_at + 0x56);
    }
  }
  *(char *)(in_at + 0x60) = (cVar3 - unaff_s7) + (char)*(undefined2 *)(in_at + 0x50);
  *(char *)(in_at + 0x61) = cVar4 + (char)*(undefined2 *)(in_at + 0x52);
  uVar1 = *(ushort *)(param_2 + 0xb0);
  cVar3 = (char)uVar1;
  cVar4 = (char)*(ushort *)(param_2 + 0xb2);
  if ((int)(uint)uVar1 < 0) {
    cVar3 = '\0';
  }
  else {
    if (-1 < (int)((uint)uVar1 - (uint)*(ushort *)(in_at + 0x54))) {
      cVar3 = (char)*(undefined2 *)(in_at + 0x54);
    }
  }
  if (-1 < (int)((uint)*(ushort *)(param_2 + 0xb2) - (uint)*(ushort *)(in_at + 0x56))) {
    cVar4 = (char)*(undefined2 *)(in_at + 0x56);
  }
  *(char *)(in_at + 100) = (cVar3 - unaff_s7) + (char)*(undefined2 *)(in_at + 0x50);
  *(char *)(in_at + 0x65) = cVar4 + (char)*(undefined2 *)(in_at + 0x52);
  uVar5 = *(uint *)(param_1 + 0x8c);
  uVar6 = *(uint *)(param_2 + 0x8c);
  in_v0[2] = *(uint *)(in_at + 0x68);
  in_v0[4] = uVar5;
  in_v0[6] = uVar6;
  in_v0[1] = *(uint *)(in_at + 0x44) | 0x24000000;
  uVar5 = *(uint *)(in_at + 0x60);
  uVar6 = *(uint *)(in_at + 100);
  in_v0[3] = *(uint *)(in_at + 0x5c);
  in_v0[5] = uVar5;
  in_v0[7] = uVar6;
  *in_v0 = *unaff_s6 | 0x7000000;
  *unaff_s6 = (uint)in_v0 & 0xffffff;
  return in_v0 + 8;
}



// WARNING: Removing unreachable block (ram,0x8004bcf8)

uint * FUN_8004bbe8(int param_1,int param_2)

{
  ushort uVar1;
  ushort uVar2;
  int in_at;
  uint *in_v0;
  char cVar3;
  char cVar4;
  uint uVar5;
  uint uVar6;
  uint *unaff_s6;
  char unaff_s7;

  uVar1 = *(ushort *)(in_at + 0x68);
  cVar3 = (char)uVar1;
  uVar2 = *(ushort *)(in_at + 0x6a);
  cVar4 = (char)uVar2;
  if ((int)(uint)uVar1 < 0) {
    cVar3 = '\0';
  }
  else {
    if (-1 < (int)((uint)uVar1 - (uint)*(ushort *)(in_at + 0x54))) {
      cVar3 = (char)*(undefined2 *)(in_at + 0x54);
    }
  }
  if ((int)(uint)uVar2 < 0) {
    cVar4 = '\0';
  }
  else {
    if (-1 < (int)((uint)uVar2 - (uint)*(ushort *)(in_at + 0x56))) {
      cVar4 = (char)*(undefined2 *)(in_at + 0x56);
    }
  }
  *(char *)(in_at + 0x5c) = (cVar3 - unaff_s7) + (char)*(undefined2 *)(in_at + 0x50);
  *(char *)(in_at + 0x5d) = cVar4 + (char)*(undefined2 *)(in_at + 0x52);
  uVar1 = *(ushort *)(param_1 + 0xb0);
  cVar3 = (char)uVar1;
  uVar2 = *(ushort *)(param_1 + 0xb2);
  cVar4 = (char)uVar2;
  if ((int)(uint)uVar1 < 0) {
    cVar3 = '\0';
  }
  else {
    if (-1 < (int)((uint)uVar1 - (uint)*(ushort *)(in_at + 0x54))) {
      cVar3 = (char)*(undefined2 *)(in_at + 0x54);
    }
  }
  if ((int)(uint)uVar2 < 0) {
    cVar4 = '\0';
  }
  else {
    if (-1 < (int)((uint)uVar2 - (uint)*(ushort *)(in_at + 0x56))) {
      cVar4 = (char)*(undefined2 *)(in_at + 0x56);
    }
  }
  *(char *)(in_at + 0x60) = (cVar3 - unaff_s7) + (char)*(undefined2 *)(in_at + 0x50);
  *(char *)(in_at + 0x61) = cVar4 + (char)*(undefined2 *)(in_at + 0x52);
  uVar1 = *(ushort *)(param_2 + 0x8c);
  cVar3 = (char)uVar1;
  cVar4 = (char)*(ushort *)(param_2 + 0x8e);
  if ((int)(uint)uVar1 < 0) {
    cVar3 = '\0';
  }
  else {
    if (-1 < (int)((uint)uVar1 - (uint)*(ushort *)(in_at + 0x54))) {
      cVar3 = (char)*(undefined2 *)(in_at + 0x54);
    }
  }
  if (-1 < (int)((uint)*(ushort *)(param_2 + 0x8e) - (uint)*(ushort *)(in_at + 0x56))) {
    cVar4 = (char)*(undefined2 *)(in_at + 0x56);
  }
  *(char *)(in_at + 100) = (cVar3 - unaff_s7) + (char)*(undefined2 *)(in_at + 0x50);
  *(char *)(in_at + 0x65) = cVar4 + (char)*(undefined2 *)(in_at + 0x52);
  uVar5 = *(uint *)(param_1 + 0x8c);
  uVar6 = *(uint *)(param_2 + 0xb0);
  in_v0[2] = *(uint *)(in_at + 0x68);
  in_v0[4] = uVar5;
  in_v0[6] = uVar6;
  in_v0[1] = *(uint *)(in_at + 0x44) | 0x24000000;
  uVar5 = *(uint *)(in_at + 0x60);
  uVar6 = *(uint *)(in_at + 100);
  in_v0[3] = *(uint *)(in_at + 0x5c);
  in_v0[5] = uVar5;
  in_v0[7] = uVar6;
  *in_v0 = *unaff_s6 | 0x7000000;
  *unaff_s6 = (uint)in_v0 & 0xffffff;
  return in_v0 + 8;
}



// WARNING: Removing unreachable block (ram,0x8004be94)

uint * FUN_8004bd84(int param_1,int param_2)

{
  ushort uVar1;
  ushort uVar2;
  int in_at;
  uint *in_v0;
  char cVar3;
  char cVar4;
  uint uVar5;
  uint uVar6;
  uint *unaff_s6;
  char unaff_s7;

  uVar1 = *(ushort *)(in_at + 0x68);
  cVar3 = (char)uVar1;
  uVar2 = *(ushort *)(in_at + 0x6a);
  cVar4 = (char)uVar2;
  if ((int)(uint)uVar1 < 0) {
    cVar3 = '\0';
  }
  else {
    if (-1 < (int)((uint)uVar1 - (uint)*(ushort *)(in_at + 0x54))) {
      cVar3 = (char)*(undefined2 *)(in_at + 0x54);
    }
  }
  if ((int)(uint)uVar2 < 0) {
    cVar4 = '\0';
  }
  else {
    if (-1 < (int)((uint)uVar2 - (uint)*(ushort *)(in_at + 0x56))) {
      cVar4 = (char)*(undefined2 *)(in_at + 0x56);
    }
  }
  *(char *)(in_at + 0x5c) = (cVar3 - unaff_s7) + (char)*(undefined2 *)(in_at + 0x50);
  *(char *)(in_at + 0x5d) = cVar4 + (char)*(undefined2 *)(in_at + 0x52);
  uVar1 = *(ushort *)(param_1 + 0x8c);
  cVar3 = (char)uVar1;
  uVar2 = *(ushort *)(param_1 + 0x8e);
  cVar4 = (char)uVar2;
  if ((int)(uint)uVar1 < 0) {
    cVar3 = '\0';
  }
  else {
    if (-1 < (int)((uint)uVar1 - (uint)*(ushort *)(in_at + 0x54))) {
      cVar3 = (char)*(undefined2 *)(in_at + 0x54);
    }
  }
  if ((int)(uint)uVar2 < 0) {
    cVar4 = '\0';
  }
  else {
    if (-1 < (int)((uint)uVar2 - (uint)*(ushort *)(in_at + 0x56))) {
      cVar4 = (char)*(undefined2 *)(in_at + 0x56);
    }
  }
  *(char *)(in_at + 0x60) = (cVar3 - unaff_s7) + (char)*(undefined2 *)(in_at + 0x50);
  *(char *)(in_at + 0x61) = cVar4 + (char)*(undefined2 *)(in_at + 0x52);
  uVar1 = *(ushort *)(param_2 + 0x8c);
  cVar3 = (char)uVar1;
  cVar4 = (char)*(ushort *)(param_2 + 0x8e);
  if ((int)(uint)uVar1 < 0) {
    cVar3 = '\0';
  }
  else {
    if (-1 < (int)((uint)uVar1 - (uint)*(ushort *)(in_at + 0x54))) {
      cVar3 = (char)*(undefined2 *)(in_at + 0x54);
    }
  }
  if (-1 < (int)((uint)*(ushort *)(param_2 + 0x8e) - (uint)*(ushort *)(in_at + 0x56))) {
    cVar4 = (char)*(undefined2 *)(in_at + 0x56);
  }
  *(char *)(in_at + 100) = (cVar3 - unaff_s7) + (char)*(undefined2 *)(in_at + 0x50);
  *(char *)(in_at + 0x65) = cVar4 + (char)*(undefined2 *)(in_at + 0x52);
  uVar5 = *(uint *)(param_1 + 0xb0);
  uVar6 = *(uint *)(param_2 + 0xb0);
  in_v0[2] = *(uint *)(in_at + 0x68);
  in_v0[4] = uVar5;
  in_v0[6] = uVar6;
  in_v0[1] = *(uint *)(in_at + 0x44) | 0x24000000;
  uVar5 = *(uint *)(in_at + 0x60);
  uVar6 = *(uint *)(in_at + 100);
  in_v0[3] = *(uint *)(in_at + 0x5c);
  in_v0[5] = uVar5;
  in_v0[7] = uVar6;
  *in_v0 = *unaff_s6 | 0x7000000;
  *unaff_s6 = (uint)in_v0 & 0xffffff;
  return in_v0 + 8;
}



// WARNING: Removing unreachable block (ram,0x8004c098)

uint * FUN_8004bf20(int param_1,int param_2)

{
  ushort uVar1;
  ushort uVar2;
  int in_at;
  uint *in_v0;
  char cVar3;
  char cVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint *unaff_s6;
  char unaff_s7;

  uVar1 = *(ushort *)(param_1 + 0x68);
  cVar3 = (char)uVar1;
  uVar2 = *(ushort *)(param_1 + 0x6a);
  cVar4 = (char)uVar2;
  if ((int)(uint)uVar1 < 0) {
    cVar3 = '\0';
  }
  else {
    if (-1 < (int)((uint)uVar1 - (uint)*(ushort *)(in_at + 0x54))) {
      cVar3 = (char)*(undefined2 *)(in_at + 0x54);
    }
  }
  if ((int)(uint)uVar2 < 0) {
    cVar4 = '\0';
  }
  else {
    if (-1 < (int)((uint)uVar2 - (uint)*(ushort *)(in_at + 0x56))) {
      cVar4 = (char)*(undefined2 *)(in_at + 0x56);
    }
  }
  *(char *)(in_at + 0x5c) = (cVar3 - unaff_s7) + (char)*(undefined2 *)(in_at + 0x50);
  *(char *)(in_at + 0x5d) = cVar4 + (char)*(undefined2 *)(in_at + 0x52);
  uVar1 = *(ushort *)(param_2 + 0x68);
  cVar3 = (char)uVar1;
  uVar2 = *(ushort *)(param_2 + 0x6a);
  cVar4 = (char)uVar2;
  if ((int)(uint)uVar1 < 0) {
    cVar3 = '\0';
  }
  else {
    if (-1 < (int)((uint)uVar1 - (uint)*(ushort *)(in_at + 0x54))) {
      cVar3 = (char)*(undefined2 *)(in_at + 0x54);
    }
  }
  if ((int)(uint)uVar2 < 0) {
    cVar4 = '\0';
  }
  else {
    if (-1 < (int)((uint)uVar2 - (uint)*(ushort *)(in_at + 0x56))) {
      cVar4 = (char)*(undefined2 *)(in_at + 0x56);
    }
  }
  *(char *)(in_at + 0x60) = (cVar3 - unaff_s7) + (char)*(undefined2 *)(in_at + 0x50);
  *(char *)(in_at + 0x61) = cVar4 + (char)*(undefined2 *)(in_at + 0x52);
  uVar1 = *(ushort *)(param_1 + 0xb0);
  cVar3 = (char)uVar1;
  uVar2 = *(ushort *)(param_1 + 0xb2);
  cVar4 = (char)uVar2;
  if ((int)(uint)uVar1 < 0) {
    cVar3 = '\0';
  }
  else {
    if (-1 < (int)((uint)uVar1 - (uint)*(ushort *)(in_at + 0x54))) {
      cVar3 = (char)*(undefined2 *)(in_at + 0x54);
    }
  }
  if ((int)(uint)uVar2 < 0) {
    cVar4 = '\0';
  }
  else {
    if (-1 < (int)((uint)uVar2 - (uint)*(ushort *)(in_at + 0x56))) {
      cVar4 = (char)*(undefined2 *)(in_at + 0x56);
    }
  }
  *(char *)(in_at + 100) = (cVar3 - unaff_s7) + (char)*(undefined2 *)(in_at + 0x50);
  *(char *)(in_at + 0x65) = cVar4 + (char)*(undefined2 *)(in_at + 0x52);
  uVar1 = *(ushort *)(param_2 + 0xb0);
  cVar3 = (char)uVar1;
  cVar4 = (char)*(ushort *)(param_2 + 0xb2);
  if ((int)(uint)uVar1 < 0) {
    cVar3 = '\0';
  }
  else {
    if (-1 < (int)((uint)uVar1 - (uint)*(ushort *)(in_at + 0x54))) {
      cVar3 = (char)*(undefined2 *)(in_at + 0x54);
    }
  }
  if (-1 < (int)((uint)*(ushort *)(param_2 + 0xb2) - (uint)*(ushort *)(in_at + 0x56))) {
    cVar4 = (char)*(undefined2 *)(in_at + 0x56);
  }
  *(char *)(in_at + 0x66) = (cVar3 - unaff_s7) + (char)*(undefined2 *)(in_at + 0x50);
  *(char *)(in_at + 0x67) = cVar4 + (char)*(undefined2 *)(in_at + 0x52);
  in_v0[1] = *(uint *)(in_at + 0x44) | 0x2c000000;
  uVar5 = *(uint *)(in_at + 0x60);
  uVar6 = *(uint *)(in_at + 100);
  in_v0[3] = *(uint *)(in_at + 0x5c);
  in_v0[5] = uVar5;
  in_v0[7] = uVar6;
  in_v0[9] = uVar6 >> 0x10;
  uVar5 = *(uint *)(param_2 + 0x68);
  uVar6 = *(uint *)(param_1 + 0x8c);
  uVar7 = *(uint *)(param_2 + 0x8c);
  in_v0[2] = *(uint *)(param_1 + 0x68);
  in_v0[4] = uVar5;
  in_v0[6] = uVar6;
  in_v0[8] = uVar7;
  *in_v0 = *unaff_s6 | 0x9000000;
  *unaff_s6 = (uint)in_v0 & 0xffffff;
  return in_v0 + 10;
}



// WARNING: Removing unreachable block (ram,0x8004c2ac)

uint * FUN_8004c134(int param_1,int param_2)

{
  ushort uVar1;
  ushort uVar2;
  int in_at;
  uint *in_v0;
  char cVar3;
  char cVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint *unaff_s6;
  char unaff_s7;

  uVar1 = *(ushort *)(param_1 + 0x68);
  cVar3 = (char)uVar1;
  uVar2 = *(ushort *)(param_1 + 0x6a);
  cVar4 = (char)uVar2;
  if ((int)(uint)uVar1 < 0) {
    cVar3 = '\0';
  }
  else {
    if (-1 < (int)((uint)uVar1 - (uint)*(ushort *)(in_at + 0x54))) {
      cVar3 = (char)*(undefined2 *)(in_at + 0x54);
    }
  }
  if ((int)(uint)uVar2 < 0) {
    cVar4 = '\0';
  }
  else {
    if (-1 < (int)((uint)uVar2 - (uint)*(ushort *)(in_at + 0x56))) {
      cVar4 = (char)*(undefined2 *)(in_at + 0x56);
    }
  }
  *(char *)(in_at + 0x5c) = (cVar3 - unaff_s7) + (char)*(undefined2 *)(in_at + 0x50);
  *(char *)(in_at + 0x5d) = cVar4 + (char)*(undefined2 *)(in_at + 0x52);
  uVar1 = *(ushort *)(param_2 + 0x68);
  cVar3 = (char)uVar1;
  uVar2 = *(ushort *)(param_2 + 0x6a);
  cVar4 = (char)uVar2;
  if ((int)(uint)uVar1 < 0) {
    cVar3 = '\0';
  }
  else {
    if (-1 < (int)((uint)uVar1 - (uint)*(ushort *)(in_at + 0x54))) {
      cVar3 = (char)*(undefined2 *)(in_at + 0x54);
    }
  }
  if ((int)(uint)uVar2 < 0) {
    cVar4 = '\0';
  }
  else {
    if (-1 < (int)((uint)uVar2 - (uint)*(ushort *)(in_at + 0x56))) {
      cVar4 = (char)*(undefined2 *)(in_at + 0x56);
    }
  }
  *(char *)(in_at + 0x60) = (cVar3 - unaff_s7) + (char)*(undefined2 *)(in_at + 0x50);
  *(char *)(in_at + 0x61) = cVar4 + (char)*(undefined2 *)(in_at + 0x52);
  uVar1 = *(ushort *)(param_1 + 0xb0);
  cVar3 = (char)uVar1;
  uVar2 = *(ushort *)(param_1 + 0xb2);
  cVar4 = (char)uVar2;
  if ((int)(uint)uVar1 < 0) {
    cVar3 = '\0';
  }
  else {
    if (-1 < (int)((uint)uVar1 - (uint)*(ushort *)(in_at + 0x54))) {
      cVar3 = (char)*(undefined2 *)(in_at + 0x54);
    }
  }
  if ((int)(uint)uVar2 < 0) {
    cVar4 = '\0';
  }
  else {
    if (-1 < (int)((uint)uVar2 - (uint)*(ushort *)(in_at + 0x56))) {
      cVar4 = (char)*(undefined2 *)(in_at + 0x56);
    }
  }
  *(char *)(in_at + 100) = (cVar3 - unaff_s7) + (char)*(undefined2 *)(in_at + 0x50);
  *(char *)(in_at + 0x65) = cVar4 + (char)*(undefined2 *)(in_at + 0x52);
  uVar1 = *(ushort *)(param_2 + 0x8c);
  cVar3 = (char)uVar1;
  cVar4 = (char)*(ushort *)(param_2 + 0x8e);
  if ((int)(uint)uVar1 < 0) {
    cVar3 = '\0';
  }
  else {
    if (-1 < (int)((uint)uVar1 - (uint)*(ushort *)(in_at + 0x54))) {
      cVar3 = (char)*(undefined2 *)(in_at + 0x54);
    }
  }
  if (-1 < (int)((uint)*(ushort *)(param_2 + 0x8e) - (uint)*(ushort *)(in_at + 0x56))) {
    cVar4 = (char)*(undefined2 *)(in_at + 0x56);
  }
  *(char *)(in_at + 0x66) = (cVar3 - unaff_s7) + (char)*(undefined2 *)(in_at + 0x50);
  *(char *)(in_at + 0x67) = cVar4 + (char)*(undefined2 *)(in_at + 0x52);
  in_v0[1] = *(uint *)(in_at + 0x44) | 0x2c000000;
  uVar5 = *(uint *)(in_at + 0x60);
  uVar6 = *(uint *)(in_at + 100);
  in_v0[3] = *(uint *)(in_at + 0x5c);
  in_v0[5] = uVar5;
  in_v0[7] = uVar6;
  in_v0[9] = uVar6 >> 0x10;
  uVar5 = *(uint *)(param_2 + 0x68);
  uVar6 = *(uint *)(param_1 + 0x8c);
  uVar7 = *(uint *)(param_2 + 0xb0);
  in_v0[2] = *(uint *)(param_1 + 0x68);
  in_v0[4] = uVar5;
  in_v0[6] = uVar6;
  in_v0[8] = uVar7;
  *in_v0 = *unaff_s6 | 0x9000000;
  *unaff_s6 = (uint)in_v0 & 0xffffff;
  return in_v0 + 10;
}



// WARNING: Removing unreachable block (ram,0x8004c4c0)

uint * FUN_8004c348(int param_1,int param_2)

{
  ushort uVar1;
  ushort uVar2;
  int in_at;
  uint *in_v0;
  char cVar3;
  char cVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint *unaff_s6;
  char unaff_s7;

  uVar1 = *(ushort *)(param_1 + 0x8c);
  cVar3 = (char)uVar1;
  uVar2 = *(ushort *)(param_1 + 0x8e);
  cVar4 = (char)uVar2;
  if ((int)(uint)uVar1 < 0) {
    cVar3 = '\0';
  }
  else {
    if (-1 < (int)((uint)uVar1 - (uint)*(ushort *)(in_at + 0x54))) {
      cVar3 = (char)*(undefined2 *)(in_at + 0x54);
    }
  }
  if ((int)(uint)uVar2 < 0) {
    cVar4 = '\0';
  }
  else {
    if (-1 < (int)((uint)uVar2 - (uint)*(ushort *)(in_at + 0x56))) {
      cVar4 = (char)*(undefined2 *)(in_at + 0x56);
    }
  }
  *(char *)(in_at + 0x5c) = (cVar3 - unaff_s7) + (char)*(undefined2 *)(in_at + 0x50);
  *(char *)(in_at + 0x5d) = cVar4 + (char)*(undefined2 *)(in_at + 0x52);
  uVar1 = *(ushort *)(param_2 + 0x8c);
  cVar3 = (char)uVar1;
  uVar2 = *(ushort *)(param_2 + 0x8e);
  cVar4 = (char)uVar2;
  if ((int)(uint)uVar1 < 0) {
    cVar3 = '\0';
  }
  else {
    if (-1 < (int)((uint)uVar1 - (uint)*(ushort *)(in_at + 0x54))) {
      cVar3 = (char)*(undefined2 *)(in_at + 0x54);
    }
  }
  if ((int)(uint)uVar2 < 0) {
    cVar4 = '\0';
  }
  else {
    if (-1 < (int)((uint)uVar2 - (uint)*(ushort *)(in_at + 0x56))) {
      cVar4 = (char)*(undefined2 *)(in_at + 0x56);
    }
  }
  *(char *)(in_at + 0x60) = (cVar3 - unaff_s7) + (char)*(undefined2 *)(in_at + 0x50);
  *(char *)(in_at + 0x61) = cVar4 + (char)*(undefined2 *)(in_at + 0x52);
  uVar1 = *(ushort *)(param_1 + 0x68);
  cVar3 = (char)uVar1;
  uVar2 = *(ushort *)(param_1 + 0x6a);
  cVar4 = (char)uVar2;
  if ((int)(uint)uVar1 < 0) {
    cVar3 = '\0';
  }
  else {
    if (-1 < (int)((uint)uVar1 - (uint)*(ushort *)(in_at + 0x54))) {
      cVar3 = (char)*(undefined2 *)(in_at + 0x54);
    }
  }
  if ((int)(uint)uVar2 < 0) {
    cVar4 = '\0';
  }
  else {
    if (-1 < (int)((uint)uVar2 - (uint)*(ushort *)(in_at + 0x56))) {
      cVar4 = (char)*(undefined2 *)(in_at + 0x56);
    }
  }
  *(char *)(in_at + 100) = (cVar3 - unaff_s7) + (char)*(undefined2 *)(in_at + 0x50);
  *(char *)(in_at + 0x65) = cVar4 + (char)*(undefined2 *)(in_at + 0x52);
  uVar1 = *(ushort *)(param_2 + 0x68);
  cVar3 = (char)uVar1;
  cVar4 = (char)*(ushort *)(param_2 + 0x6a);
  if ((int)(uint)uVar1 < 0) {
    cVar3 = '\0';
  }
  else {
    if (-1 < (int)((uint)uVar1 - (uint)*(ushort *)(in_at + 0x54))) {
      cVar3 = (char)*(undefined2 *)(in_at + 0x54);
    }
  }
  if (-1 < (int)((uint)*(ushort *)(param_2 + 0x6a) - (uint)*(ushort *)(in_at + 0x56))) {
    cVar4 = (char)*(undefined2 *)(in_at + 0x56);
  }
  *(char *)(in_at + 0x66) = (cVar3 - unaff_s7) + (char)*(undefined2 *)(in_at + 0x50);
  *(char *)(in_at + 0x67) = cVar4 + (char)*(undefined2 *)(in_at + 0x52);
  in_v0[1] = *(uint *)(in_at + 0x44) | 0x2c000000;
  uVar5 = *(uint *)(in_at + 0x60);
  uVar6 = *(uint *)(in_at + 100);
  in_v0[3] = *(uint *)(in_at + 0x5c);
  in_v0[5] = uVar5;
  in_v0[7] = uVar6;
  in_v0[9] = uVar6 >> 0x10;
  uVar5 = *(uint *)(param_2 + 0xb0);
  uVar6 = *(uint *)(param_1 + 0x68);
  uVar7 = *(uint *)(param_2 + 0x68);
  in_v0[2] = *(uint *)(param_1 + 0xb0);
  in_v0[4] = uVar5;
  in_v0[6] = uVar6;
  in_v0[8] = uVar7;
  *in_v0 = *unaff_s6 | 0x9000000;
  *unaff_s6 = (uint)in_v0 & 0xffffff;
  return in_v0 + 10;
}
