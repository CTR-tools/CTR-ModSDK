#include <common.h>

#define gte_ldVXY0(r0) __asm__ volatile("mtc2   %0, $0" \
                                        :               \
                                        : "r"(r0))
#define gte_ldVZ0(r0) __asm__ volatile("mtc2   %0, $1" \
                                       :               \
                                       : "r"(r0))
#define read_mt(r0, r1, r2) __asm__ volatile( \
    "mfc2   %0, $25;"                         \
    "mfc2   %1, $26;"                         \
    "mfc2   %2, $27;"                         \
    :                                         \
    : "r"(r0), "r"(r1), "r"(r2))

void FUN_80060630(struct Thread* t, struct Driver* d)

{
  char uVar1;
  bool bVar2;
  short sVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  short sVar7;
  int iVar8;
  int iVar9;
  unsigned int uVar10;
  unsigned int uVar11;
  unsigned int uVar12;
  int iVar13;
  unsigned int uVar14;
  char *puVar15;
  int param_1;
  int param_2;
  int param_3;
  char auStack_40 [40];
  
  puVar15 = auStack_40;
  uVar12 = d;
  gte_SetRotMatrix(&d->matrixMovingDir);
  if (((*(char *)(uVar12 + 0x376) != '\x02') && ((*(unsigned int *)(uVar12 + 0x2c8) & 0x800000) == 0)) &&
     (param_2 = 0, *(short *)(uVar12 + 0x3e2) == 0)) {
    uVar1 = *(char *)(uVar12 + 0x43b);
    iVar9 = (int)((unsigned int)*(unsigned short *)(uVar12 + 0xc0) << 0x10) >> 0x18;
    if (iVar9 < 0) {
      iVar9 = -iVar9;
    }
	
	// Part 1
    *(int *)(puVar15 + 0x10) = (int)*(short *)(uVar12 + 0x43c);
    param_1 = DECOMP_VehCalc_MapToRange(iVar9,0,uVar1,0, (int)*(short *)(uVar12 + 0x43c));
    param_3 = (int)*(short *)(uVar12 + 0x39c);
    
	// commenting out THIS line breaks it, WHY?
	// Need to make VehPhysGeneral_4_JumpAndFriction work
	param_2 = (unsigned int)*(unsigned short *)(uVar12 + 0x39c);
    
	// Part 2
	iVar9 = param_3;
    if (param_3 < 0) {
      iVar9 = -param_3;
    }
	
	// Part 3
    if (iVar9 < param_1) {
      param_1 = iVar9;
    }
    sVar7 = (short)param_1;
    
	// Part 4
	sVar3 = -sVar7;
    if (param_3 < 0) {
      param_1 = -param_1;
      sVar3 = sVar7;
    }
	
	// Part 5
    *(unsigned short *)(uVar12 + 0x39c) = *(unsigned short *)(uVar12 + 0x39c) + sVar3;
  }
  if (*(short *)(uVar12 + 0x3fe) != 0) {
    if (*(short *)(uVar12 + 0x38a) < *(short *)(uVar12 + 0x39c)) {
      *(unsigned short *)(uVar12 + 0x39c) = *(unsigned short *)(uVar12 + 0x38a);
    }
    if ((int)*(short *)(uVar12 + 0x39c) < -(int)*(short *)(uVar12 + 0x38a)) {
      *(short *)(uVar12 + 0x39c) = -*(short *)(uVar12 + 0x38a);
    }
  }
  *(unsigned int *)(puVar15 + 0x18) = *(unsigned int *)(uVar12 + 0x88);
  *(unsigned int *)(puVar15 + 0x1c) = *(unsigned int *)(uVar12 + 0x8c);
  uVar14 = 0;
  *(unsigned int *)(puVar15 + 0x20) = *(unsigned int *)(uVar12 + 0x90);
  iVar9 = 0;
  
  if ((*(unsigned int *)(uVar12 + 0x2c8) & 1) == 0) {

LAB_80060ab0:

// UNUSED Spring Weapon
#if 0
    if (((*(unsigned int *)(uVar12 + 0x2c8) & 0x8000) != 0) && (*(char *)(uVar12 + 0x36) == '\x05')) {
      *(unsigned int *)(uVar12 + 0x2c8) = *(unsigned int *)(uVar12 + 0x2c8) & 0xffff7fff;
      if ((*(short *)(uVar12 + 0x3f4) != 0) && (*(short *)(uVar12 + 0x3f2) == 0)) {
        *(unsigned short *)(uVar12 + 0x3f6) = 0xa0;
        iVar9 = *(short *)(uVar12 + 0x418) * 9;
        if (iVar9 < 0) {
          iVar9 = iVar9 + 3;
        }
        *(short *)(uVar12 + 0x3f8) = (short)(iVar9 >> 2);
        DECOMP_OtherFX_Play_Echo(9,1,*(unsigned short *)(uVar12 + 0x2ca) & 1);
        *(unsigned short *)(uVar12 + 0x3fa) = 0x180;
        goto LAB_80060c30;
      }
      *(unsigned short *)(uVar12 + 0x3c) = 0;
    }
#endif
	
	if (*(char *)(uVar12 + 0x366) == '\0') {
      if (((*(short *)(uVar12 + 0x3f4) == 0) || (*(short *)(uVar12 + 0x3f0) == 0)) ||
         (*(short *)(uVar12 + 0x3f2) != 0)) {
        if ((*(unsigned int *)(uVar12 + 0x2c8) & 1) != 0) {
          if ((*(int *)(uVar12 + 0x350) != 0) &&
             (iVar9 = (int)*(char *)(*(int *)(uVar12 + 0x350) + 0x3b), iVar9 != 0)) {
            iVar13 = (int)*(short *)(uVar12 + 0x38e);
            if (iVar13 < 0) {
              iVar13 = -iVar13;
            }
            gte_ldVXY0((iVar9 * iVar13 >> 8) << 0x10);
            gte_ldVZ0(0);
            gte_rtv0();
			
			
            read_mt(iVar9,puVar15 + 0x18,param_3);
            *(int *)(puVar15 + 0x18) = *(int *)(puVar15 + 0x18) + iVar9;
            *(int *)(puVar15 + 0x20) = *(int *)(puVar15 + 0x20) + param_3;
            *(char **)(puVar15 + 0x1c) = puVar15 + 0x18 + *(int *)(puVar15 + 0x1c);
			
			//int temp;
            //read_mt(iVar9,temp,param_3);
            //*(int *)(puVar15 + 0x18) = *(int *)(puVar15 + 0x18) + iVar9;
            //*(int *)(puVar15 + 0x1c) = *(int *)(puVar15 + 0x1c) + temp;
            //*(int *)(puVar15 + 0x20) = *(int *)(puVar15 + 0x20) + param_3;
          }
        }
        goto LAB_80060e1c;
      }
      *(unsigned short *)(uVar12 + 0x3f6) = 0xa0;
      *(short *)(uVar12 + 0x554) = *(short *)(uVar12 + 0x554) + 1;
      *(unsigned short *)(uVar12 + 0x3f8) = *(unsigned short *)(uVar12 + 0x418);
      DECOMP_OtherFX_Play_Echo(8,1,*(unsigned short *)(uVar12 + 0x2ca) & 1);
    }
    else {
      if ((*(short *)(uVar12 + 0x3f6) == 0) ||
         (*(short *)(uVar12 + 0x3f8) == *(short *)(uVar12 + 0x418))) {
        DECOMP_OtherFX_Play(0x7e,1);
      }
      *(unsigned short *)(uVar12 + 0x3f6) = 0xa0;
      if (*(char *)(uVar12 + 0x366) == '\x02') {
        *(unsigned short *)(uVar12 + 0x3fa) = 0x180;
        *(short *)(uVar12 + 0x3f8) = *(short *)(uVar12 + 0x418) * 3;
      }
      else {
        *(short *)(uVar12 + 0x3f8) = (short)((*(short *)(uVar12 + 0x418) * 3) / 2);
      }
      *(char *)(uVar12 + 0x366) = 0;
    }
  }
  else {
    if (((*(unsigned int *)(uVar12 + 0xbc) & 3) == 0) || (*(short *)(uVar12 + 0x39c) < 1)) {
      if (*(short *)(uVar12 + 0x39c) != 0) {
        if ((((*(unsigned int *)(*(int *)(uVar12 + 0x358) + 4) & 4) == 0) ||
            (*(short *)(uVar12 + 0x39c) < 1)) || (-1 < *(short *)(uVar12 + 0x38e))) {
          iVar8 = (int)*(short *)(uVar12 + 0x38e);
          iVar13 = iVar8;
          if (iVar8 < 0) {
            iVar13 = -iVar8;
          }
          if (((0x2ff < iVar13) && ((*(short *)(uVar12 + 0x39c) < 1 || (iVar8 < 1)))) &&
             ((-1 < *(short *)(uVar12 + 0x39c) || (-1 < iVar8)))) goto LAB_800608fc;
        }
        param_1 = (int)*(short *)(uVar12 + 0x428);
        iVar9 = param_1 + ((int)*(char *)(uVar12 + 0x33) << 5) / 5;
        if ((*(unsigned int *)(uVar12 + 0xbc) & 3) == 0) {
          if ((*(short *)(uVar12 + 0x3e2) != 0) && (0 < *(short *)(uVar12 + 0x39c))) {
            iVar9 = (int)*(short *)(uVar12 + 0x42a);
          }
          param_1 = *(int *)(*(int *)(uVar12 + 0x358) + 0xc);
          if ((param_1 != 0x100) && ((*(unsigned int *)(uVar12 + 0x2c8) & 0x800000) == 0)) {
            iVar9 = param_1 * iVar9 >> 8;
          }
        }
        else if (0 < *(short *)(uVar12 + 0x39c)) goto LAB_8006089c;
      }
    }
    else {
LAB_8006089c:
      iVar9 = 8000;
    }
LAB_800608fc:
    uVar10 = (iVar9 * sdata->gGT->elapsedTimeMS) >> 5;
    gte_ldVXY0(0);
    gte_ldVZ0(uVar10 & 0xffff);
    gte_rtv0();
    read_mt(param_1,param_2,param_3);
    if (*(short *)(uVar12 + 0x39c) < 0) {
      *(short *)(uVar12 + 0x3b2) = -(short)uVar10;
      *(int *)(puVar15 + 0x18) = *(int *)(puVar15 + 0x18) - param_1;
      *(int *)(puVar15 + 0x20) = *(int *)(puVar15 + 0x20) - param_3;
      *(unsigned int *)(puVar15 + 0x1c) = *(int *)(puVar15 + 0x1c) - param_2;
      *(short *)(uVar12 + 0x3ac) = -(short)param_1;
      *(short *)(uVar12 + 0x3ae) = -(short)param_2;
      *(short *)(uVar12 + 0x3b0) = -(short)param_3;
    }
    else {
      *(short *)(uVar12 + 0x3b2) = (short)uVar10;
      *(int *)(puVar15 + 0x18) = *(int *)(puVar15 + 0x18) + param_1;
      *(int *)(puVar15 + 0x20) = *(int *)(puVar15 + 0x20) + param_3;
      *(unsigned int *)(puVar15 + 0x1c) = *(int *)(puVar15 + 0x1c) + param_2;
      *(short *)(uVar12 + 0x3ac) = (short)param_1;
      *(short *)(uVar12 + 0x3ae) = (short)param_2;
      *(short *)(uVar12 + 0x3b0) = (short)param_3;
    }
    uVar14 = VehCalc_FastSqrt(*(int *)(puVar15 + 0x18) * *(int *)(puVar15 + 0x18) +
                          *(int *)(puVar15 + 0x1c) * *(int *)(puVar15 + 0x1c) +
                          *(int *)(puVar15 + 0x20) * *(int *)(puVar15 + 0x20),0x10);
    iVar9 = (int)*(short *)(uVar12 + 0x39c);
    if (iVar9 < 0) {
      iVar9 = -iVar9;
    }
    uVar14 = (uVar14 >> 8) - iVar9;
    bVar2 = (int)uVar10 < (int)uVar14;
    if ((int)uVar14 < 0) {
      uVar14 = 0;
      bVar2 = (int)uVar10 < 0;
    }
    if (bVar2) {
      uVar14 = uVar10;
    }
    if (((*(unsigned int *)(uVar12 + 0x2c8) & 1) == 0) || (*(short *)(uVar12 + 0x3f6) == 0))
    goto LAB_80060ab0;
    if (*(short *)(uVar12 + 0x3fa) != 0) {
      *(unsigned short *)(uVar12 + 0x3fa) = 0x180;
    }
    if (*(char *)(uVar12 + 0x376) == '\x06') {
      DECOMP_GAMEPAD_ShockFreq(uVar12,8,0);
      DECOMP_GAMEPAD_ShockForce1(uVar12,8,0x7f);
    }
  }

// PROCESS_JUMP
LAB_80060c30:

  iVar9 = 0;
  iVar8 = 0x378;
  *(unsigned short *)(uVar12 + 0x3f2) = 0x180;
  *(unsigned short *)(uVar12 + 0x3f0) = 0;
  *(unsigned int *)(uVar12 + 0x2c8) = *(unsigned int *)(uVar12 + 0x2c8) | 0x480;
  iVar13 = iVar9;
  do {
    iVar4 = DECOMP_VehPhysGeneral_JumpGetVelY(uVar12 + iVar8,puVar15 + 0x18);
    iVar6 = iVar4;
    if (iVar4 < 0) {
      iVar6 = -iVar4;
    }
    iVar5 = iVar9;
    if (iVar9 < 0) {
      iVar5 = -iVar9;
    }
    if (iVar5 < iVar6) {
      iVar9 = iVar4;
    }
    iVar13 = iVar13 + 1;
    iVar8 = iVar8 + 8;
  } while (iVar13 < 1);
  iVar13 = uVar12 + 0x360;
  if ((*(unsigned int *)(uVar12 + 0x2c8) & 1) == 0) {
    iVar13 = uVar12 + 0x368;
  }
  iVar8 = DECOMP_VehPhysGeneral_JumpGetVelY(iVar13,puVar15 + 0x18);
  iVar13 = iVar8;
  if (iVar8 < 0) {
    iVar13 = -iVar8;
  }
  iVar6 = iVar9;
  if (iVar9 < 0) {
    iVar6 = -iVar9;
  }
  iVar4 = iVar9 * iVar9;
  if (iVar6 < iVar13) {
    iVar4 = iVar8 * iVar8;
    iVar9 = iVar8;
  }
  iVar13 = VehCalc_FastSqrt(iVar4 + (int)*(short *)(uVar12 + 0x3f8) * (int)*(short *)(uVar12 + 0x3f8) >>
                        8, 8);
  uVar10 = sdata->gGT->level1->unk_18C << 8;
  if (sdata->gGT->level1->unk_18C == 0) {
    uVar10 = 0x3700;
  }
  else if (0x5000 < uVar10) {
    uVar10 = 0x5000;
  }
  uVar11 = iVar13 - iVar9;
  if ((int)uVar10 < iVar13 - iVar9) {
    uVar11 = uVar10;
  }
  if (*(int *)(puVar15 + 0x1c) < (int)uVar11) {
    *(unsigned int *)(puVar15 + 0x1c) = uVar11;
  }

// [end of the first frame of jump]

// skip here if not jumping
  
LAB_80060e1c:
  VehPhysCrash_ConvertVecToSpeed(uVar12,puVar15 + 0x18/*,0*/);
  iVar9 = *(unsigned short *)(uVar12 + 0x38c) - uVar14;
  *(short *)(uVar12 + 0x38c) = (short)iVar9;
  if (iVar9 * 0x10000 < 0) {
    *(unsigned short *)(uVar12 + 0x38c) = 0;
  }
  iVar9 = (int)*(short *)(uVar12 + 0x38e);
  if (iVar9 < 0) {
    if (iVar9 < 0) {
      iVar9 = -iVar9;
    }
    if (iVar9 < 0x100) {
      sVar7 = *(short *)(uVar12 + 0x36e) - (*(short *)(uVar12 + 0x36e) >> 3);
    }
    else {
      sVar7 = (short)(*(short *)(uVar12 + 0x36e) * 0xd +
                      (sdata->gGT->timer & 7) * 0x300 >> 4);
    }
  }
  else {
    sVar7 = (short)(*(short *)(uVar12 + 0x36e) * 0xd + iVar9 * 3 >> 4);
  }
  *(short *)(uVar12 + 0x36e) = sVar7;
  return;
}