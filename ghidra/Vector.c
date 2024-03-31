
// Vector_SpecLightSpin2D
// instance, ptr rot[6], cop registers
void FUN_800572d0(int param_1,undefined4 param_2,SVECTOR *param_3)

{
  undefined *puVar1;
  int iVar2;
  undefined4 uVar3;
  undefined *puVar4;
  undefined auStack104 [16];
  undefined auStack88 [72];

  puVar4 = auStack104;

  // ConvertRotToMatrix_Transpose
  FUN_8006c378(auStack88, param_2);

  gte_ldv0(param_3);
  gte_rtv0();
  uVar3 = gte_stMAC1();
  *(undefined4 *)(puVar4 + 0x30) = uVar3;
  uVar3 = gte_stMAC2();
  *(undefined4 *)(puVar4 + 0x34) = uVar3;
  uVar3 = gte_stMAC3();
  *(undefined4 *)(puVar4 + 0x38) = uVar3;
  *(undefined *)(param_1 + 0x53) = puVar4[0x30];
  *(undefined4 *)(param_1 + 0x58) = *(undefined4 *)(puVar4 + 0x38);
  *(undefined2 *)(puVar4 + 0x50) = 0;
  *(undefined2 *)(puVar4 + 0x52) = 0;
  *(undefined2 *)(puVar4 + 0x54) = 0x1000;
  gte_ldv0((SVECTOR *)(puVar4 + 0x50));
  gte_rtv0();
  uVar3 = gte_stMAC1();
  *(undefined4 *)(puVar4 + 0x40) = uVar3;
  uVar3 = gte_stMAC2();
  *(undefined4 *)(puVar4 + 0x44) = uVar3;
  uVar3 = gte_stMAC3();
  *(undefined4 *)(puVar4 + 0x48) = uVar3;
  *(short *)(puVar4 + 0x50) = *(short *)(puVar4 + 0x30) + *(short *)(puVar4 + 0x40);
  *(short *)(puVar4 + 0x52) = *(short *)(puVar4 + 0x34) + *(short *)(puVar4 + 0x44);
  *(short *)(puVar4 + 0x54) = *(short *)(puVar4 + 0x38) + *(short *)(puVar4 + 0x48);

  // MATH_VectorNormalize
  FUN_8003d378();

  puVar1 = PTR_DAT_8008d2ac;
  iVar2 = 0;

  // if numPlyrCurrGame != 0
  if (PTR_DAT_8008d2ac[0x1ca8] != '\0')
  {
	// each InstDrawPerPlayer
	// for iVar2 = 0; iVar2 < numPlyrCurrGame; iVar2++
    do 
	{
	  // write specular values,
	  // increment loop index
      *(undefined2 *)(param_1 + 0xf4) = *(undefined2 *)(puVar4 + 0x50);
      *(undefined2 *)(param_1 + 0xf6) = *(undefined2 *)(puVar4 + 0x52);
      iVar2 = iVar2 + 1;
      *(undefined2 *)(param_1 + 0xf8) = *(undefined2 *)(puVar4 + 0x54);
	
	  // next InstDrawPerPlayer
      param_1 = param_1 + 0x88;
    
	} while (iVar2 < (int)(uint)(byte)puVar1[0x1ca8]);
  }
  return;
}


// Vector_SpecLightSpin3D
// param_1 MATRIX
// param_2 vec3s rotation
void FUN_8005741c(int param_1,undefined4 param_2,SVECTOR *param_3)

{
  short *psVar1;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  SVECTOR *r0;
  MATRIX *r0_00;
  undefined *puVar8;
  undefined auStack136 [16];
  MATRIX aMStack120 [2];
  SVECTOR local_38 [2];
  undefined *puVar2;

  puVar8 = auStack136;

  // ConvertRotToMatrix_Transpose
  FUN_8006c378(aMStack120, param_2);

  iVar4 = 0;

  // if numPlyrCurrGame is not zero
  if (PTR_DAT_8008d2ac[0x1ca8] != '\0')
  {
    r0_00 = aMStack120;
    r0 = local_38;

	// offset of 8008d2ac for pushBuffer buffers
	iVar7 = 0x168;

	// offset in pushBuffer buffer array (0 for p1, 0x110 for p2, etc)
    iVar6 = 0;

    puVar2 = PTR_DAT_8008d2ac;
    iVar5 = param_1;

	// for iVar6 = 0; iVar6 < numPlyrCurrGame; iVar6++
    do
	{
	  // pointer to start of pushBuffer buffer array
      psVar1 = (short *)(puVar2 + iVar7);

	  // Genius idea from Naughty Dog:
	  // Transpose-View + Vec3-Inverted = Inverse-Transpose-View + Vec3.

	  // pushBuffer offset 0x68, CameraMatrix
      gte_SetLightMatrix((MATRIX *)((int)psVar1 + iVar6 + 0x68));

	  // param_3 = inverted specular light vector 
      gte_ldv0(param_3);
	  
      gte_llv0();
	  
	  // generate stack-matrix from result
      uVar3 = gte_stMAC1();
      *(undefined4 *)(puVar8 + 0x30) = uVar3;
      uVar3 = gte_stMAC2();
      *(undefined4 *)(puVar8 + 0x34) = uVar3;
      uVar3 = gte_stMAC3();
      *(undefined4 *)(puVar8 + 0x38) = uVar3;
      *(undefined2 *)(puVar8 + 0x58) = *(undefined2 *)(puVar8 + 0x30);
      *(undefined2 *)(puVar8 + 0x5a) = *(undefined2 *)(puVar8 + 0x34);
      *(undefined2 *)(puVar8 + 0x5c) = *(undefined2 *)(puVar8 + 0x38);

	  gte_SetLightMatrix(r0_00);

	  gte_ldv0((SVECTOR *)(puVar8 + 0x58));
      gte_llv0();
      uVar3 = gte_stMAC1();
      *(undefined4 *)(puVar8 + 0x30) = uVar3;
      uVar3 = gte_stMAC2();
      *(undefined4 *)(puVar8 + 0x34) = uVar3;
      uVar3 = gte_stMAC3();
      *(undefined4 *)(puVar8 + 0x38) = uVar3;
      *(undefined *)(iVar5 + 0x53) = puVar8[0x30];
      *(uint *)(iVar5 + 0x58) = (uint)*(ushort *)(puVar8 + 0x38);
      *(short *)(puVar8 + 0x50) = *(short *)(iVar5 + 0x44) - *psVar1;
      *(short *)(puVar8 + 0x52) = *(short *)(iVar5 + 0x48) - psVar1[1];
      *(short *)(puVar8 + 0x54) = *(short *)(iVar5 + 0x4c) - psVar1[2];

	  // MATH_VectorNormalize
	  FUN_8003d378(r0);

      gte_SetLightMatrix(r0_00);

	  gte_ldv0(r0);
      gte_llv0();
      uVar3 = gte_stMAC1();
      *(undefined4 *)(puVar8 + 0x40) = uVar3;
      uVar3 = gte_stMAC2();
      *(undefined4 *)(puVar8 + 0x44) = uVar3;
      uVar3 = gte_stMAC3();
      *(undefined4 *)(puVar8 + 0x48) = uVar3;
      *(short *)(puVar8 + 0x50) = *(short *)(puVar8 + 0x30) + *(short *)(puVar8 + 0x40);
      *(short *)(puVar8 + 0x52) = *(short *)(puVar8 + 0x34) + *(short *)(puVar8 + 0x44);
      *(short *)(puVar8 + 0x54) = *(short *)(puVar8 + 0x38) + *(short *)(puVar8 + 0x48);

	  // MATH_VectorNormalize
	  FUN_8003d378(r0);

      puVar2 = PTR_DAT_8008d2ac;

	  // next pushBuffer
	  iVar7 = iVar7 + 0x110;

	  *(undefined2 *)(param_1 + 0xf4) = *(undefined2 *)(puVar8 + 0x50);

	  // next pushBuffer
	  iVar6 = iVar6 + 0x110;

      *(undefined2 *)(param_1 + 0xf6) = *(undefined2 *)(puVar8 + 0x52);

	  // next loop index
	  iVar4 = iVar4 + 1;

	  *(undefined2 *)(param_1 + 0xf8) = *(undefined2 *)(puVar8 + 0x54);
	
	  // next InstDrawPerPlayer
      param_1 = param_1 + 0x88;
    
	} while (iVar4 < (int)(uint)(byte)puVar2[0x1ca8]);
  }
  return;
}


// Vector_SpecLightNoSpin3D
// used on flamejet
// param_1 - instance
// param_2 - inst->instDef->rot[3]
// param_3 - specLightDir
void FUN_800576b8(int param_1,undefined4 param_2,SVECTOR *param_3)

{
  short *psVar1;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  SVECTOR *r0;
  int iVar6;
  undefined *puVar7;
  undefined auStack112 [16];
  MATRIX aMStack96 [2];
  undefined *puVar2;

  puVar7 = auStack112;

  // ConvertRotToMatrix_Transpose
  FUN_8006c378(aMStack96, param_2);

  gte_SetLightMatrix(aMStack96);
  gte_ldv0(param_3);
  gte_llv0();
  uVar3 = gte_stMAC1();
  *(undefined4 *)(puVar7 + 0x30) = uVar3;
  uVar3 = gte_stMAC2();
  *(undefined4 *)(puVar7 + 0x34) = uVar3;
  uVar3 = gte_stMAC3();
  *(undefined4 *)(puVar7 + 0x38) = uVar3;
  *(undefined *)(param_1 + 0x53) = puVar7[0x30];
  puVar2 = PTR_DAT_8008d2ac;
  *(uint *)(param_1 + 0x58) = (uint)*(ushort *)(puVar7 + 0x38);
  iVar4 = 0;

  // if numPlyrCurrGame is not zero
  if (puVar2[0x1ca8] != '\0')
  {
    r0 = (SVECTOR *)(puVar7 + 0x50);
    iVar5 = 0x168;
    iVar6 = param_1;

	// for iVar3 = 0; iVar3 < numPlyrCurrGame; iVar3++
    do
	{
	  // pointer to pushBuffer buffer
      psVar1 = (short *)(puVar2 + iVar5);

	  // direction vector from object to camera
      *(short *)(puVar7 + 0x50) = *(short *)(iVar6 + 0x44) - *psVar1;
      *(short *)(puVar7 + 0x52) = *(short *)(iVar6 + 0x48) - psVar1[1];
      *(short *)(puVar7 + 0x54) = *(short *)(iVar6 + 0x4c) - psVar1[2];

	  // MATH_VectorNormalize
      FUN_8003d378(r0);

      gte_ldv0(r0);
      gte_llv0();
      uVar3 = gte_stMAC1();
      *(undefined4 *)(puVar7 + 0x40) = uVar3;
      uVar3 = gte_stMAC2();
      *(undefined4 *)(puVar7 + 0x44) = uVar3;
      uVar3 = gte_stMAC3();
      *(undefined4 *)(puVar7 + 0x48) = uVar3;

	  // ???
      *(short *)(puVar7 + 0x50) = *(short *)(puVar7 + 0x30) + *(short *)(puVar7 + 0x40);
      *(short *)(puVar7 + 0x52) = *(short *)(puVar7 + 0x34) + *(short *)(puVar7 + 0x44);
      *(short *)(puVar7 + 0x54) = *(short *)(puVar7 + 0x38) + *(short *)(puVar7 + 0x48);

	  // MATH_VectorNormalize
	  FUN_8003d378(r0);

      puVar2 = PTR_DAT_8008d2ac;
      *(undefined2 *)(param_1 + 0xf4) = *(undefined2 *)(puVar7 + 0x50);

	  // increment offset to next pushBuffer buffer
	  iVar5 = iVar5 + 0x110;

	  *(undefined2 *)(param_1 + 0xf6) = *(undefined2 *)(puVar7 + 0x52);

	  // loop index
      iVar4 = iVar4 + 1;

      *(undefined2 *)(param_1 + 0xf8) = *(undefined2 *)(puVar7 + 0x54);

	  // next InstDrawPerPlayer
	  param_1 = param_1 + 0x88;

	} while (iVar4 < (int)(uint)(byte)puVar2[0x1ca8]);
  }
  return;
}


// Vector_BakeMatrixTable
// called once during init, not related to spec light,
// NOP will distort the following driver animations into squishing:
// crashing, boosting, jumping, blasted
void FUN_80057884(undefined *param_1)

{
  int iVar1;
  MATRIX *r0;
  undefined *puVar2;
  VECTOR *r0_00;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  int iVar6;
  undefined **ppuVar7;
  undefined2 *puVar8;
  int iVar9;
  int *piVar10;
  int iVar11;
  uint uVar12;
  undefined *puVar13;
  undefined auStack128 [16];
  
  // another local matrix
  uint local_70;
  undefined4 local_6c;
  uint local_68;
  undefined4 local_64;
  undefined2 local_60;
  
  MATRIX localMatrix;
  VECTOR local_30;

  puVar13 = auStack128;

  // DAT_80087f28 is a constant for how many frames are in "blasted" anim

  // if function has not run
  if (DAT_8008d590 == '\0')
  {
	// remember the function has run
    DAT_8008d590 = '\x01';

    iVar11 = 0;

	// bakedGteMath[6].numEntires "blasted"
    if (0 < DAT_80087f28)
	{

	  iVar9 = 0;

	  // loop through blasted frames
	  do
	  {
		// pointer to matrix array
		// bakedGteMath[6], "blasted"
        puVar2 = PTR_DAT_80087f24;

		iVar6 = iVar11 << 0xd;

		// fail-safe to alert debugger
        if (DAT_80087f28 == 0) trap(0x1c00);
        if ((DAT_80087f28 == -1) && (iVar6 == -0x80000000)) trap(0x1800);

        *(short *)(PTR_DAT_80087f24 + iVar11 * 0x20 + 0xc) = (short)(iVar6 / DAT_80087f28);

		// fail-safe to alert debugger
		if (DAT_80087f28 == 0) trap(0x1c00);
        if ((DAT_80087f28 == -1) && (iVar9 == -0x80000000)) trap(0x1800);

		// MATH_Sin
        iVar1 = FUN_8003d184(iVar9 / DAT_80087f28);
        *(short *)(puVar2 + iVar11 * 0x20 + 8) = (short)(-iVar1 / 7);

		// fail-safe to alert debugger
        if (DAT_80087f28 == 0) trap(0x1c00);
        if ((DAT_80087f28 == -1) && (iVar6 == -0x80000000)) trap(0x1800);

		// MATH_Sin
        iVar1 = FUN_8003d184(iVar6 / DAT_80087f28);
        *(short *)(puVar2 + iVar11 * 0x20 + 0x10) = (short)((iVar1 * 6) / 0x28) + 0x1000;

		// fail-safe to alert debugger
        if (DAT_80087f28 == 0) trap(0x1c00);
        if ((DAT_80087f28 == -1) && (iVar6 == -0x80000000)) trap(0x1800);

		// MATH_Sin
        iVar1 = FUN_8003d184(iVar6 / DAT_80087f28);
        *(short *)(puVar2 + iVar11 * 0x20 + 0x14) = (short)((iVar1 * 6) / 0x28) + 0x1000;
        iVar_a0 = (undefined *)(iVar6 / DAT_80087f28);

		// fail-safe to alert debugger
        if (DAT_80087f28 == 0) trap(0x1c00);
        if ((DAT_80087f28 == -1) && (iVar6 == -0x80000000)) trap(0x1800);

		// MATH_Sin
        iVar6 = FUN_8003d184(iVar_a0);

        if (iVar6 < 0) {
          iVar6 = iVar6 + 3;
        }

		*(short *)(puVar2 + iVar11 * 0x20 + 0x10) = (short)(iVar6 >> 2) + 0x1000;

		// next index
		iVar11 = iVar11 + 1;

        iVar9 = iVar9 + 0x3000;

      } while (iVar11 < DAT_80087f28);
    }

    uVar12 = 0;

	// start of pointer table
	piVar10 = &DAT_80087ef4;

	// another local matrix
    local_70 = 0;
    local_6c = 0;
    local_68 = 0;
    local_64 = 0;
    local_60 = 0;
	
	// loop through 14 arrays
    do 
	{
	  // number of elements != 0, ptr to array != 0
      if (((piVar10[1] != 0) && (*piVar10 != 0)) && (iVar11 = 0, 0 < piVar10[1])) 
	  {
		// loop through each matrix of the array
        do 
		{
		  // &matrix[loopIndex]
          iVar9 = *piVar10 + iVar11 * 0x20;

		   // convert 3 rotation shorts into rotation matrix
          FUN_8006c2a4(&localMatrix,iVar9 + 8);

		  // another local matrix
          local_70 = local_70 & 0xffff0000 | (uint)*(ushort *)(iVar9 + 0x10);
          local_68 = local_68 & 0xffff0000 | (uint)*(ushort *)(iVar9 + 0x12);
          local_60 = *(undefined2 *)(iVar9 + 0x14);
		  
		  // MatrixRotate (param_1 = param_2 matrix rotated by param_3 matrix)
          FUN_8006c3b0(iVar9 + 8,&local_70,&localMatrix);
		  
		  // loop index
          iVar11 = iVar11 + 1;
          
		  param_1 = &localMatrix;
        } while (iVar11 < piVar10[1]);
      }
      uVar12 = uVar12 + 1;
      piVar10 = piVar10 + 2;
    } while (uVar12 < 0x14);
	
	// pointer to matrix array
	// bakedGteMath[6], "blasted"
    ppuVar7 = &PTR_DAT_80087f24;
	
	// loop index
    iVar11 = 0;
	
	// bakedGteMath[6].numEntires
    if (0 < DAT_80087f28) 
	{
      uVar5 = 0x2000;
      r0_00 = &local_30;
      uVar4 = 0xe0000000;
      uVar3 = 0;
      
	  // loop through all entries
	  do 
	  {  
		// bakedGteMath[6].physEntry (matArr06)
		puVar2 = *ppuVar7;
		
        *(undefined4 *)(puVar13 + 0x50) = 0;
        *(undefined4 *)(puVar13 + 0x54) = uVar5;
        *(undefined4 *)(puVar13 + 0x58) = 0;
		
		// &matrix[loopIndex]
        puVar8 = (undefined2 *)(puVar2 + iVar11 * 0x20);
        
		r0 = (MATRIX *)(puVar8 + 4);
        gte_SetRotMatrix(r0);
        gte_SetTransVector(r0_00);
        gte_ldVXY0(uVar4);
        gte_ldVZ0(uVar3);
        gte_rt();
        read_mt(r0,puVar2,param_1);
		
		// write result [0] [1] and [2]
        *puVar8 = (short)r0;
        puVar8[1] = (short)puVar2;
        puVar8[2] = (short)param_1;
        
		// loop index
		iVar11 = iVar11 + 1;
		
      } while (iVar11 < (int)ppuVar7[1]);
    }
  }
  return;
}
