
// called "COLL" for "Collisions"

// COLL_LevModelMeta
undefined ** FUN_8001d094(uint param_1)

{
  if (param_1 < 0xe2) {
    return &PTR_s_NO_FUNC_80081088 + param_1 * 3;
  }
  return &PTR_s_NO_FUNC_80081088;
}




// COLL_Instance
// param_1 - 0x1f800108
// param_2 - struct BSP* instanceHitbox
uint FUN_8001d0c4(short *param_1,byte *param_2)

{
  bool bVar1;
  short sVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  undefined4 uVar6;
  uint uVar7;
  uint uVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  uint uVar13;
  int iVar14;
  int iVar15;
  int iVar16;
  int iVar17;

  // if this is an instance you can drive through
  if (param_2[1] == 4) 
  {  
	*(byte **)(param_1 + 0x24) = param_2;
	
	// 1f80014a
    param_1[0x21] = param_1[0x21] + 1;
  }
  
  // if instance is on the track? (not floating in air)
  if ((param_1[0x11] & 0x40U) == 0) 
  { 
    *(undefined4 *)(param_1 + 0xe4) = 0;
    
	// subtract two points
	uVar5 = (int)*param_1 - (int)param_1[8];
    uVar7 = (int)param_1[2] - (int)param_1[10]; 
	
	// box size?
    *(uint *)(param_1 + 0xe2) = uVar5;
    *(uint *)(param_1 + 0xe6) = uVar7;
	
	// bsp->0x10
    sVar2 = *(short *)(param_2 + 0x10);
    *(undefined4 *)(param_1 + 0xea) = 0;
    iVar14 = (int)sVar2 - (int)param_1[8];
    *(int *)(param_1 + 0xe8) = iVar14;
    iVar12 = 0;
	
    iVar15 = (int)*(short *)(param_2 + 0x14) - (int)param_1[10];
    *(int *)(param_1 + 0xec) = iVar15;
	
    uVar13 = 0;
    if ((*param_2 & 0x40) != 0) {
      iVar12 = (int)param_1[1] - (int)param_1[9];
      *(int *)(param_1 + 0xe4) = iVar12;
      uVar13 = (int)*(short *)(param_2 + 0x12) - (int)param_1[9];
      *(uint *)(param_1 + 0xea) = uVar13;
    }
    uVar8 = uVar5 & 0xffff | iVar12 << 0x10;
    uVar3 = iVar15 * 0x10000;

	
    gte_ldR11R12(uVar8);
    gte_ldR13R21(uVar7 & 0xffff | iVar14 * 0x10000);
    gte_ldR22R23(uVar13 & 0xffff | uVar3);
    gte_ldVXY0(uVar8);
    gte_ldVZ0(uVar7);
    gte_mvmva(0,0,0,3,0);
    iVar11 = gte_stMAC1();
    iVar4 = gte_stMAC2();
	
	
	*(int *)(param_1 + 0xd6) = iVar11;
    *(int *)(param_1 + 0xd8) = iVar4;
    
	if (0 < iVar4) 
	{  
      gte_ldLZCS(iVar4);
      iVar9 = gte_stLZCR();
	  
      uVar3 = iVar9 - 2;
      uVar8 = uVar3;
      if ((int)uVar3 < 0) {
        uVar8 = 0;
      }
      if (0xc < (int)uVar3) {
        uVar8 = 0xc;
      }
      uVar3 = 0xc - uVar8;
      iVar9 = iVar11 >> (uVar3 & 0x1f);
      iVar4 = iVar4 << (uVar8 & 0x1f);
      if (-1 < iVar9) {
        iVar10 = 0;
        if (iVar9 != 0) {
          iVar10 = iVar4 / iVar9;
          if (iVar9 == 0) {
            trap(0x1c00);
          }
          if ((iVar9 == -1) && (iVar4 == -0x80000000)) {
            trap(0x1800);
          }
        }
        *(int *)(param_1 + 0xda) = iVar10;
        iVar4 = 0;
        iVar9 = (int)(iVar10 * uVar5) >> 0xc;
        if ((*param_2 & 0x40) != 0) {
          iVar4 = iVar10 * iVar12 >> 0xc;
        }
        uVar3 = iVar9 - iVar14 & 0xffffU | (iVar4 - uVar13) * 0x10000;
        *(int *)(param_1 + 0xee) = iVar9;
        *(int *)(param_1 + 0xf0) = iVar4;
        iVar4 = (int)(iVar10 * uVar7) >> 0xc;
        iVar9 = iVar4 - iVar15;
        *(int *)(param_1 + 0xf2) = iVar4;


        gte_ldR11R12(uVar3);
        gte_ldR13R21(iVar9);
        gte_ldVXY0(uVar3);
        gte_ldVZ0(iVar9);
        gte_mvmva(0,0,0,3,0);


        uVar3 = SEXT24(*(short *)(param_2 + 0x16));
        iVar4 = ((int)param_1[3] + uVar3) * ((int)param_1[3] + uVar3);
        iVar9 = getCopReg(2,0xc800);
        *(int *)(param_1 + 0xdc) = iVar4;
        iVar4 = iVar4 - iVar9;
        *(int *)(param_1 + 0xde) = iVar9;
        if (-1 < iVar4) {
          if (iVar4 != 0) {
            if (iVar11 != 0) {
              if (iVar11 == 0) {
                trap(0x1c00);
              }
              if ((iVar11 == -1) && (iVar4 * 0x1000 == -0x80000000)) {
                trap(0x1800);
              }
              iVar10 = iVar10 - (iVar4 * 0x1000) / iVar11;
            }
            *(int *)(param_1 + 0xe0) = iVar10;
          }
		  
		  // 1f80014a
          uVar3 = (uint)(*(int *)(param_1 + 0x42) < iVar10);
          
		  iVar11 = 0;
		  
		  // 1f80014a
          if (*(int *)(param_1 + 0x42) >= iVar10) {
            iVar9 = 0;
            iVar17 = 0;
            if (0 < iVar10) {
              iVar4 = uVar5 * iVar10;
              iVar11 = iVar4 >> 0xc;
              iVar9 = iVar12 * iVar10 >> 0xc;
              iVar17 = (int)(uVar7 * iVar10) >> 0xc;
            }
            
			if ((((*param_2 & 0x20) == 0) || ((int)*(short *)(param_2 + 0x12) <= iVar9)) ||
               (bVar1 = (int)*(short *)(param_2 + 0x12) + (int)*(short *)(param_2 + 2) < iVar9,
               uVar3 = (uint)bVar1, !bVar1)) 
			{
              *(byte **)(param_1 + 0x24) = param_2;
              *(int *)(param_1 + 0x42) = iVar10;
              
			  // 1f80014a
			  param_1[0x21] = param_1[0x21] + 1;
              
			  *(int *)(param_1 + 0xf4) = iVar11;
              *(int *)(param_1 + 0xf6) = iVar9;
              *(int *)(param_1 + 0xf8) = iVar17;
              iVar12 = 0;
              if ((*param_2 & 0x40) != 0) {
                iVar12 = iVar9 - uVar13;
              }
              iVar15 = iVar17 - iVar15;
              uVar5 = iVar11 - iVar14 & 0xffffU | iVar12 << 0x10;
			  
			  
              gte_ldR11R12(uVar5);
              gte_ldR13R21(iVar15);
              gte_ldVXY0(uVar5);
              gte_ldVZ0(iVar15);
			  
			  // Multiply Vector By Matrix With Vector Addition
              gte_mvmva(0,0,0,3,0);
			  
			  
			  uVar6 = gte_stMAC1();
              iVar4 = SquareRoot0(uVar6);
              
			  
			  iVar10 = 0x1000000 / iVar4;
              if (iVar4 == 0) {
                trap(0x1c00);
              }
              
			  // normalVecX
			  iVar16 = (iVar11 - iVar14) * iVar10 >> 0xc;
              *(int *)(param_1 + 0xfa) = iVar16;
			  
			  // normalVecY
              iVar14 = iVar12 * iVar10 >> 0xc;
              *(int *)(param_1 + 0xfc) = iVar14;
              
			  // normalVecZ
			  iVar4 = iVar15 * iVar10 >> 0xc;
              *(int *)(param_1 + 0xfe) = iVar4;
              
			  // length?
			  iVar15 = (int)*(short *)(param_2 + 0x16);
			  
              param_1[0xe] = param_1[8] + (short)iVar11;
			  
			  // set normal vector of quadblock
			  // 0x1F800178, 0x1F80017A, 0x1F80017C
              param_1[0x38] = (short)iVar16;
              param_1[0x39] = (short)iVar14;
              param_1[0x3a] = (short)iVar4;
			  
              param_1[0x10] = param_1[10] + (short)iVar17;
              param_1[0xf] = param_1[9] + (short)iVar9;
              *(undefined *)(param_1 + 0x3f) = 6;
			  
			  // normalVec * length
              iVar12 = iVar16 * iVar15 >> 0xc;
              *(int *)(param_1 + 0x100) = iVar12;
              iVar14 = iVar14 * iVar15 >> 0xc;
              *(int *)(param_1 + 0x102) = iVar14;
              iVar15 = iVar4 * iVar15 >> 0xc;
              *(int *)(param_1 + 0x104) = iVar15;
			  
              sVar2 = *(short *)(param_2 + 0x10) + (short)iVar12;
              param_1[0x3c] = sVar2;
              param_1[0x34] = sVar2;
              sVar2 = *(short *)(param_2 + 0x12) + (short)iVar14;
              param_1[0x3d] = sVar2;
              param_1[0x35] = sVar2;
              uVar3 = (uint)*(ushort *)(param_2 + 0x14) + iVar15;
              param_1[0x3e] = (short)uVar3;
              param_1[0x36] = (short)uVar3;
            }
          }
        }
      }
    }
  }
  
  // if instance is floating in air
  else 
  {
	// normal vector is {0, 0x1000, 0}
    param_1[0x39] = 0x1000;
    uVar3 = 6;
    param_1[0x38] = 0;
    param_1[0x3a] = 0;
	
    *(undefined *)(param_1 + 0x3f) = 6;
    *(undefined4 *)(param_1 + 0x42) = 0;
    *(byte **)(param_1 + 0x24) = param_2;
    param_1[0xe] = param_1[8];
    param_1[0xf] = param_1[9];
    param_1[0x10] = param_1[10];
    param_1[0x21] = param_1[0x21] + 1;
  }
  return uVar3;
}


// PerBspLeaf_CheckInstances
// param1 - bsp node
// param2 - 1f800108
void FUN_8001d610(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  int *piVar4;

  // bsp node, used for instance hitbox
  piVar3 = *(int **)(param_1 + 0x14);
  
  // if there are instances in this bsp
  if (piVar3 != (int *)0x0) 
  {
	// check for null flag
    iVar1 = *piVar3;
	
	// pointer to boundingbox
    piVar4 = piVar3 + 2;
	
    // check every instance hitbox until 
	// end of list (null flag) is found
    while (iVar1 != 0) 
	{
      // 1F8001CC
	  iVar1 = *(int *)(param_2 + 0xc4) + -1;
      if (-1 < iVar1) {
        iVar2 = iVar1 * 4 + param_2;
        do 
		{
          iVar1 = iVar1 + -1;
		  
		  // look for member in 1F800190 array
          if (piVar3 == *(int **)(iVar2 + 0x88)) goto LAB_8001d750;
		  
          iVar2 = iVar2 + -4;
        
		} while (-1 < iVar1);
      }
	  
      if (
			(
				(
					(
						// if data is invalid (what?)
						(
							// if collision for instance is disabled
							((*(byte *)piVar3 & 0x80) == 0) || 
						
							// if bspHitbox.InstDef doesn't exist
							(piVar4[5] == 0)
						) ||
						
						// if data is valid
						
						// bspHitbox.InstDef->Instance->flags, allows drawing
						((*(uint *)(*(int *)(piVar4[5] + 0x2c) + 0x28) & 0xf) != 0)
					) &&
			
				// compare bsp boundingbox to scratchpad boundingbox
				((*(short *)(param_2 + 0x30) <= *(short *)((int)piVar4 + 2) &&
				(*(short *)(piVar4 + -1) <= *(short *)(param_2 + 0x36))))) &&
				((*(short *)(param_2 + 0x32) <= *(short *)(piVar4 + 1) &&
				((*(short *)((int)piVar4 + -2) <= *(short *)(param_2 + 0x38) &&
				(*(short *)(param_2 + 0x34) <= *(short *)((int)piVar4 + 6))))))
			) &&
			
			(*(short *)piVar4 <= *(short *)(param_2 + 0x3a))
		 ) 
	  {
		// COLL_Instance
		// check with collision for this instance
        FUN_8001d0c4(param_2,piVar3); 
      }
LAB_8001d750:

	  // go to next in list, and check for null flag
      piVar3 = piVar3 + 8;
      iVar1 = *piVar3;
      piVar4 = piVar4 + 8;
    }
  }
  return;
}


// COLL_StartSearch_AI
// param1 is driver posCurr,
// param2 is driver posPrev
// param3 is 1f800108
void FUN_8001d77c(short *param_1,short *param_2,short *param_3)

{
  short sVar1;
  int iVar2;

  iVar2 = (int)param_3[3] * (int)param_3[3];
  *(int *)(param_3 + 4) = iVar2;
  
  // input1.pos = posCurr
  *param_3 = *param_1;
  param_3[1] = param_1[1];
  sVar1 = param_1[2];
  param_3[2] = sVar1;
  
  // QuadBlockColl.hitPos = posCurr (again)
  param_3[0xf] = param_3[1];
  param_3[0xe] = *param_3;
  *(int *)(param_3 + 0xc) = iVar2;
  param_3[0x10] = sVar1;
  
  param_3[0xb] = param_3[3];
  
  // QuadBlockColl.pos = posPrev
  param_3[8] = *param_2;
  param_3[9] = param_2[1];
  param_3[10] = param_2[2];
  
  // 1f800138 = boundingbox
  
  // minX = posPrevX - deltaPrevX
  sVar1 = (short)((int)param_3[8] - (int)param_3[0xb]);
  
  // if posCurrX - deltaCurrX is less than prev frame's minX
  if ((int)*param_3 - (int)param_3[3] < (int)param_3[8] - (int)param_3[0xb]) 
  {
	// use current frame minX
    sVar1 = (short)((int)*param_3 - (int)param_3[3]);
  }
  param_3[0x18] = sVar1;
  
  // all boundingbox variables check
  // current frame values and prev frame,
  // to make bounding box as big as possible
  
  // boundingbox minY
  sVar1 = (short)((int)param_3[9] - (int)param_3[0xb]);
  if ((int)param_3[1] - (int)param_3[3] < (int)param_3[9] - (int)param_3[0xb]) {
    sVar1 = (short)((int)param_3[1] - (int)param_3[3]);
  }
  param_3[0x19] = sVar1;
  
  // boundingbox minZ
  sVar1 = (short)((int)param_3[10] - (int)param_3[0xb]);
  if ((int)param_3[2] - (int)param_3[3] < (int)param_3[10] - (int)param_3[0xb]) {
    sVar1 = (short)((int)param_3[2] - (int)param_3[3]);
  }
  param_3[0x1a] = sVar1;
  
  // boundingbox maxX
  sVar1 = (short)((int)param_3[8] + (int)param_3[0xb]);
  if ((int)param_3[8] + (int)param_3[0xb] < (int)*param_3 + (int)param_3[3]) {
    sVar1 = (short)((int)*param_3 + (int)param_3[3]);
  }
  param_3[0x1b] = sVar1;
  
  // boundingbox maxY
  sVar1 = (short)((int)param_3[9] + (int)param_3[0xb]);
  if ((int)param_3[9] + (int)param_3[0xb] < (int)param_3[1] + (int)param_3[3]) {
    sVar1 = (short)((int)param_3[1] + (int)param_3[3]);
  }
  param_3[0x1c] = sVar1;
  
  // boundingbox maxZ
  sVar1 = (short)((int)param_3[10] + (int)param_3[0xb]);
  if ((int)param_3[10] + (int)param_3[0xb] < (int)param_3[2] + (int)param_3[3]) {
    sVar1 = (short)((int)param_3[2] + (int)param_3[3]);
  }
  
  // sps->unk4C[0x38]
  *(undefined4 *)(param_3 + 0x42) = 0x1000;
  
  param_3[0x1d] = sVar1;
  
  // boolDidTouchHitbox
  param_3[0x21] = 0;
  
  // unk3C
  param_3[0x1e] = 0;
  
  // sps->dataOutput[0]
  *(undefined4 *)(param_3 + 0xd2) = 0;
  
  // sps->unk4C[0x78]
  *(undefined4 *)(param_3 + 0x62) = 0;

  // COLL_SearchTree_FindX, callback
  // PerBspLeaf_CheckInstances
  FUN_8001ebec(
	*(undefined4 *)(*(int *)(param_3 + 0x16) + 0x18),
	param_3 + 0x18,
	FUN_8001d610,
	param_3);
	
  return;
}



// COLL_StartSearch_Player
// check collisions with all quadblocks (no instances)
void FUN_8001d944(int param_1,int param_2)
// param_1 = thread
// param_2 = Racer struct Pointer
{
  char cVar1;
  ushort uVar2;
  undefined *puVar3;
  byte bVar4;
  short sVar5;
  uint uVar6;
  undefined4 uVar7;
  long lVar8;
  int iVar9;
  uint uVar10;
  int iVar11;
  uint uVar12;
  int iVar13;
  int iVar14;
  int iVar15;
  int local_30;
  int local_2c;
  int local_28;

  //turn off 17th flag of Actions Flag set (means ?)
  *(uint *)(param_2 + 0x2c8) = *(uint *)(param_2 + 0x2c8) & 0xfffeffff;

  // not really a "box", more of a straight line,
  // possibly for a cylinder?

  // posPrev (which isn't really previous, just a second point of reference)
  DAT_1f800118._0_2_ = (short)((uint)*(undefined4 *)(param_2 + 0x2d4) >> 8);
  iVar13 = (*(int *)(param_2 + 0x2d8) >> 8) + 0x80;
  DAT_1f800118._2_2_ = (short)iVar13;
  DAT_1f80011c._0_2_ = (short)((uint)*(undefined4 *)(param_2 + 0x2dc) >> 8);
  
  // posCurr
  DAT_1f800108 = (short)((uint)*(undefined4 *)(param_2 + 0x2d4) >> 8);
  iVar9 = (*(int *)(param_2 + 0x2d8) >> 8) + -0x100;
  DAT_1f80010a = (short)iVar9;
  DAT_1f80010c = (short)((uint)*(undefined4 *)(param_2 + 0x2dc) >> 8);
  
  DAT_1f800134 = **(int **)(PTR_DAT_8008d2ac + 0x160);
  DAT_1f800130 = 0x10;

  // ground and wall quadblock flags
  DAT_1f80012c = 0x3000;

  // If 3P or 4P
  // low-LOD collision (2 triangles)
  DAT_1f80012a = 0;

  // if numPlyrCurrGame is less than 3 (1P or 2P)
  if ((byte)PTR_DAT_8008d2ac[0x1ca8] < 3) 
  {
	// high-LOD collision (8 triangles)
    DAT_1f80012a = 2;
  }

  DAT_1f800146 = 0;
  DAT_1f800144 = 0;
  
  // boundingbox minX
  DAT_1f800138 = (short)DAT_1f800118;
  if (DAT_1f800108 < (short)DAT_1f800118) {
    DAT_1f800138 = DAT_1f800108;
  }
  
  iVar13 = iVar13 * 0x10000 >> 0x10;
  iVar9 = iVar9 * 0x10000 >> 0x10;
  
  // boundingbox minY
  DAT_1f80013a = DAT_1f800118._2_2_;
  if (iVar9 < iVar13) {
    DAT_1f80013a = DAT_1f80010a;
  }
  
  // boundingbox minZ
  DAT_1f80013c = (short)DAT_1f80011c;
  if (DAT_1f80010c < (short)DAT_1f80011c) {
    DAT_1f80013c = DAT_1f80010c;
  }
  
  // boundingbox maxX
  DAT_1f80013e = (short)DAT_1f800118;
  if ((short)DAT_1f800118 < DAT_1f800108) {
    DAT_1f80013e = DAT_1f800108;
  }
  
  // boundingbox maxY
  DAT_1f800140 = DAT_1f800118._2_2_;
  if (iVar13 < iVar9) {
    DAT_1f800140 = DAT_1f80010a;
  }
  
  // boundingbox maxZ
  DAT_1f800142 = (short)DAT_1f80011c;
  if ((short)DAT_1f80011c < DAT_1f80010c) {
    DAT_1f800142 = DAT_1f80010c;
  }
  
  // position
  DAT_1f800124._0_2_ = DAT_1f800108;
  DAT_1f800124._2_2_ = DAT_1f80010a;
  DAT_1f800128 = DAT_1f80010c;

  // quadblock under driver
  if (*(int *)(param_2 + 0x350) != 0)
  {
	// check, if touching same quadblock still
	// COLL_PerQuadblock_CheckTriangles_Touching
    FUN_8001f41c(*(int *)(param_2 + 0x350),&DAT_1f800108);
  }

  // if no collision is found, search for another
  if (((DAT_1f800146 == 0) && (DAT_1f800134 != 0)) && (*(int *)(DAT_1f800134 + 0x18) != 0))
  {
	// COLL_SearchTree_FindX, callback
	// COLL_PerBspLeaf_CheckQuadblocks_Touching
    FUN_8001ebec(*(int *)(DAT_1f800134 + 0x18),&DAT_1f800138,FUN_8001f5f0,&DAT_1f800108);
  }

  // thread -> instance
  iVar9 = *(int *)(param_1 + 0x34);

  // if no collision with "new" block
  if (DAT_1f800146 == 0) 
  {
	// mid-air
    *(uint *)(iVar9 + 0x70) = ((uint)*(byte *)(param_2 + 0x4a) + 1) * 0x1000000 | 0x4000;
    *(uint *)(iVar9 + 0x28) = *(uint *)(iVar9 + 0x28) & 0xffffbfff;
    *(int *)(param_2 + 0x2d0) = *(int *)(param_2 + 0x2d8) + -0x10000;
  }

  // if collision with "new" block
  else
  {
	// driver on ground
	  
    *(uint *)(iVar9 + 0x70) =
         _DAT_1f800178 >> 6 & 0xff | (_DAT_1f800178 >> 0x10 & 0x3fc0) << 2 |
         ((uint)(DAT_1f80017c >> 6) & 0xff) << 0x10 |
         ((uint)*(byte *)(param_2 + 0x4a) + 1) * 0x1000000;

	// save quadblock height
    *(int *)(param_2 + 0x2d0) = (int)DAT_1f800124._2_2_ << 8;

	*(ushort *)(param_2 + 0xaa) = *(ushort *)(param_2 + 0xaa) | 4;

	// get quadblock terrain
    cVar1 = *(char *)(DAT_1f800188 + 0x38);

    if (

		(
			// if terrain is mud
			(cVar1 == '\x0e') ||

			// if terrain is water
			(cVar1 == '\x04')

		) ||

		// if terrain is "fastwater"
		(cVar1 == '\r')
	   )
	{
	  // set split height to zero,
	  // height of all water, and mud
      *(undefined2 *)(iVar9 + 0x56) = 0;

	  // instance is now vertically split
      *(uint *)(iVar9 + 0x28) = *(uint *)(iVar9 + 0x28) | 0x2000;
    }

    puVar3 = PTR_DAT_8008d2ac;

	// if numPlyrCurrGame is less than 2
    if ((byte)PTR_DAT_8008d2ac[0x1ca8] < 2)
	{
	  // quadblock flags
      uVar2 = *(ushort *)(DAT_1f800188 + 0x12);

	  // if quadblock is not wall
	  if ((uVar2 & 0x2000) == 0) {

		// if quadblock is not invisible
        if ((uVar2 & 1) == 0) {

		  // if quadblock is not reflective (ice)
          if ((uVar2 & 4) == 0)
		  {
			// instance is not reflective
            *(uint *)(iVar9 + 0x28) = *(uint *)(iVar9 + 0x28) & 0xffffbfff;
          }

		  // if quadblock is reflective (ice)
          else
		  {
			// instance is reflective
            *(uint *)(iVar9 + 0x28) = *(uint *)(iVar9 + 0x28) | 0x4000;

			// vertical line for split or reflection
            *(undefined2 *)(iVar9 + 0x56) = *(undefined2 *)(*(int *)(puVar3 + 0x160) + 0x184);
          }
        }

		// ====================

		// what? shouldn't 0x186 be ice reflection,
		// from personal tests? What does 0x184 do?

		// ====================


		// if quadblock is invisible
        else
		{
		  // instance is reflective
          *(uint *)(iVar9 + 0x28) = *(uint *)(iVar9 + 0x28) | 0x4000;

		  // vertical line for split or reflection
          *(undefined2 *)(iVar9 + 0x56) = *(undefined2 *)(*(int *)(puVar3 + 0x160) + 0x186);
        }
      }
    }
    
	// normalVec
	iVar15 = (int)*(short *)(param_2 + 0x370) * 5 + (int)DAT_1f800178 * 3;
    iVar14 = (int)*(short *)(param_2 + 0x372) * 5 + (int)DAT_1f80017a * 3;
    iVar13 = (int)*(short *)(param_2 + 0x374) * 5 + (int)(short)DAT_1f80017c * 3;

    // uVar6 = sqrt(x2+y2+z2 << 0x18)
    uVar6 = FUN_80059070(iVar15 * iVar15 + iVar14 * iVar14 + iVar13 * iVar13,0x18);

    uVar6 = uVar6 >> 0xc;
    if (uVar6 == 0) {
      trap(0x1c00);
    }
    if ((uVar6 == 0xffffffff) && (iVar15 * 0x1000 == -0x80000000)) {
      trap(0x1800);
    }
    if (uVar6 == 0) {
      trap(0x1c00);
    }
    if ((uVar6 == 0xffffffff) && (iVar14 * 0x1000 == -0x80000000)) {
      trap(0x1800);
    }
    if (uVar6 == 0) {
      trap(0x1c00);
    }
    if ((uVar6 == 0xffffffff) && (iVar13 * 0x1000 == -0x80000000)) {
      trap(0x1800);
    }
	
    // normalize a normalVec
    *(undefined2 *)(param_2 + 0x370) = (short)((iVar15 * 0x1000) / (int)uVar6);
    *(undefined2 *)(param_2 + 0x372) = (short)((iVar14 * 0x1000) / (int)uVar6);
    *(undefined2 *)(param_2 + 0x374) = (short)((iVar13 * 0x1000) / (int)uVar6);

	// if quadblock can make an echo sound
    if ((*(ushort *)(DAT_1f800188 + 0x12) & 0x80) != 0)
	{
      // turn on flag for engine sounds to echo
      *(uint *)(param_2 + 0x2c8) = *(uint *)(param_2 + 0x2c8) | 0x10000;
    }

	// quadblock under driver
    *(int *)(param_2 + 0x350) = DAT_1f800188;

    if (
			(*(int *)(param_2 + 0x2d8) <= *(int *)(param_2 + 0x2d0) + 0x1000) ||

			(
				(
					// if terrain is mud
					*(char *)(DAT_1f800188 + 0x38) == '\x0e' &&

					// mud is always at height (y = 0)

					// if you are under the mud
					(*(int *)(param_2 + 0x2d8) < 1)
				)
			)
		)
	 {
	  // if quadblock is ground
      if ((*(ushort *)(DAT_1f800188 + 0x12) & 0x1000) != 0)
	  {
		// normalVecUP[0,1]
        *(uint *)(param_2 + 0xa4) = _DAT_1f800178;
        uVar2 = DAT_1f80017c;

		// driver is not in air, they're on ground
        *(ushort *)(param_2 + 0xaa) = *(ushort *)(param_2 + 0xaa) | 8;

		// normalVecUP[2]
		*(ushort *)(param_2 + 0xa8) = uVar2;
      }

	  uVar6 = _DAT_1f800178;

	  // if driver was not previously touching quadblock
	  if (*(int *)(param_2 + 0xa0) == 0)
	  {
		  // set quadblock touched, to quadblock under you
        *(int *)(param_2 + 0xa0) = DAT_1f800188;

        *(uint *)(param_2 + 0x360) = uVar6;
        *(ushort *)(param_2 + 0x364) = DAT_1f80017c;
      }

      if (((DAT_1f8001d4 != 0) && (DAT_1f8001d8 != 0)) && (DAT_1f8001dc != 0)) {
        uVar12 = (uint)*(byte *)(DAT_1f8001d4 + 8);
        iVar14 = (int)DAT_1f8001d0;
        iVar13 = (int)DAT_1f8001d2;
        uVar10 = (uint)*(byte *)(DAT_1f8001d4 + 9);
        uVar6 = (uint)*(byte *)(DAT_1f8001d4 + 10);
        iVar15 = ((int)(iVar14 * (*(byte *)(DAT_1f8001d8 + 8) - uVar12)) >> 0xc) +
                 ((int)(iVar13 * (*(byte *)(DAT_1f8001dc + 8) - uVar12)) >> 0xc) + uVar12;
        iVar11 = ((int)(iVar14 * (*(byte *)(DAT_1f8001d8 + 9) - uVar10)) >> 0xc) +
                 ((int)(iVar13 * (*(byte *)(DAT_1f8001dc + 9) - uVar10)) >> 0xc) + uVar10;
        iVar13 = ((int)(iVar14 * (*(byte *)(DAT_1f8001d8 + 10) - uVar6)) >> 0xc) +
                 ((int)(iVar13 * (*(byte *)(DAT_1f8001dc + 10) - uVar6)) >> 0xc) + uVar6;
        if (iVar15 < 0) {
          iVar15 = 0;
        }
        if (0xff < iVar15) {
          iVar15 = 0xff;
        }
        iVar14 = iVar11;
        if (iVar11 < 0) {
          iVar14 = 0;
        }
        if (0xff < iVar11) {
          iVar14 = 0xff;
        }
        iVar11 = iVar13;
        if (iVar13 < 0) {
          iVar11 = 0;
        }
        if (0xff < iVar13) {
          iVar11 = 0xff;
        }
        iVar14 = ((iVar15 * 0x4c >> 8) + (iVar14 * 0x96 >> 8) + (iVar11 * 0x1e >> 8)) * -0x20 +
                 0xc00;
        iVar13 = iVar14;
        if (iVar14 < 0) {
          iVar13 = 0;
        }
        iVar15 = iVar13 << 3;
        if (0x1000 < iVar14) {
          iVar13 = 0x1000;
          iVar15 = 0x8000;
        }
        iVar13 = (iVar15 - iVar13) * 8;
        *(undefined2 *)(param_2 + 0x508) =
             (short)((uint)*(ushort *)(param_2 + 0x508) * 200 + iVar13 >> 8);
        *(undefined2 *)(iVar9 + 0x22) = (short)((uint)*(ushort *)(iVar9 + 0x22) * 200 + iVar13 >> 8)
        ;
      }
    }
  }
  
  // if driver is high above the quadblock
  if (*(int *)(param_2 + 0x2d0) + 0x8000 < *(int *)(param_2 + 0x2d8))
  {
	// VehAfterColl_GetTerrain (air)
    uVar7 = FUN_80057c68(10);
    *(undefined4 *)(param_2 + 0x35c) = uVar7;
  }

  // if driver height is under
  if (*(int *)(param_2 + 0x2d8) <

	  // fixed height value for instant death?
      ((int)*(short *)(*(int *)(**(int **)(PTR_DAT_8008d2ac + 0x160) + 0x18) + 6) + -0x40) * 0x100)
  {
	// player needs mask grab
    *(ushort *)(param_2 + 0xaa) = *(ushort *)(param_2 + 0xaa) | 1;
  }

  iVar9 = *(int *)(param_2 + 0x8c) - *(int *)(param_2 + 0x3a4);

  if (
	 (
		// quadblock under driver
		(*(int *)(param_2 + 0xa0) != 0) &&

		((*(ushort *)(param_2 + 0xaa) & 9) == 0)
	  ) &&

		// not mask grab
		(*(char *)(param_2 + 0x376) != '\x05')
	  )
  {
	// driver->velocityXYZ += normalVec/2
    *(int *)(param_2 + 0x88) =
         *(int *)(param_2 + 0x88) + ((int)((uint)*(ushort *)(param_2 + 0x360) << 0x10) >> 0x11);
    *(int *)(param_2 + 0x8c) =
         *(int *)(param_2 + 0x8c) + ((int)((uint)*(ushort *)(param_2 + 0x362) << 0x10) >> 0x11);
    *(int *)(param_2 + 0x90) =
         *(int *)(param_2 + 0x90) + ((int)((uint)*(ushort *)(param_2 + 0x364) << 0x10) >> 0x11);
  }

  // driver -> quadBlock (just touched)
  iVar13 = *(int *)(param_2 + 0xa0);

  // backup velocityXYZ
  *(undefined4 *)(param_2 + 0x3a0) = *(undefined4 *)(param_2 + 0x88);
  *(undefined4 *)(param_2 + 0x3a4) = *(undefined4 *)(param_2 + 0x8c);
  *(undefined4 *)(param_2 + 0x3a8) = *(undefined4 *)(param_2 + 0x90);

  // if you are not touching a quadblock (mid-jump)
  if (iVar13 == 0) {
LAB_8001e4d0:

    // jump timer
	if (*(short *)(param_2 + 0x3f2) != 0)
	{
      //turn on 20th bit of Actions Flag set, racer is now airborne
      *(uint *)(param_2 + 0x2c8) = *(uint *)(param_2 + 0x2c8) | 0x80000;
    }

    if (*(short *)(param_2 + 0x3fa) != 0)
	{
      //turn on 7th bit of Actions Flag set (means racer is doing an artificial jump?)
      *(uint *)(param_2 + 0x2c8) = *(uint *)(param_2 + 0x2c8) | 0x40;
    }

	// VehAfterColl_GetTerrain (air)
	uVar7 = FUN_80057c68(10);
    *(undefined4 *)(param_2 + 0x358) = uVar7;

	// terrainID "none" (mid-air)
    *(undefined *)(param_2 + 0xc2) = 10;

	puVar3 = PTR_DAT_8008d2ac;

    //turn off 1st bit of Actions Flag set (means player is not touching the ground)
    *(uint *)(param_2 + 0x2c8) = *(uint *)(param_2 + 0x2c8) & 0xfffffffe;

	// jump_LandingBoost
	*(short *)(param_2 + 0x3fc) = *(short *)(param_2 + 0x3fc) + *(short *)(puVar3 + 0x1d04);

	// jump_CoyoteTimerMS, 3-4 frames, 0xa0 milliseconds
	iVar9 = (uint)*(ushort *)(param_2 + 0x3f4) - (uint)*(ushort *)(puVar3 + 0x1d04);
    *(undefined2 *)(param_2 + 0x3f4) = (short)iVar9;

	// can't go negative
    if (iVar9 * 0x10000 < 0) {
      *(undefined2 *)(param_2 + 0x3f4) = 0;
    }

	// frames of lerp
    iVar9 = 7;
    if (*(short *)(param_2 + 0x3f4) == 0) {
      *(undefined2 *)(param_2 + 0x3f2) = 0;
      *(undefined2 *)(param_2 + 0x3fa) = 0;
    }
  }

  // if you are touching a quadblock
  else {

	// if quadblock is not killplane
    if ((*(ushort *)(iVar13 + 0x12) & 0x200) == 0) {

	  if (
			(
				// if you are not being mask grabbed
				(*(char *)(param_2 + 0x376) != '\x05') &&

				// if not already on killplane
				((*(ushort *)(param_2 + 0xaa) & 1) == 0)
			) &&

			// if quadblock is ground
			((*(ushort *)(iVar13 + 0x12) & 0x1000) != 0)
		  )
	  {

		// if quadblock (just touched) checkpointIndex is invalid
		if (*(byte *)(iVar13 + 0x3e) == 0xff) {

		  // Level ID on Adventure Arena
          if (*(int *)(PTR_DAT_8008d2ac + 0x1a10) - 0x19U < 5)
		  {
			// last "valid" quadblock (for mask grab)
			// = quadblock just touched
            *(int *)(param_2 + 0x354) = iVar13;
          }
        }

		// if checkpointIndex is valid
		else
		{
		  // === Natty Video ===
		  // https://www.youtube.com/watch?v=lDaT2rY6GKI
		  
		  // Part A: Start-line -> 32000 distToFinish
		  // Part B: 32000 distToFinish -> 1200 distToFinish
		  // Part C: 1200 distToFinish -> Finish-line
		  
		  // NMZ Shortcut occurs if a quadblock in Part B
		  // is assigned to checkpoint 0 or 1, such as Papu Pyramid
			
		  // level -> respawn points
          iVar13 = *(int *)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0x14c) +

					// checkpointIndex * 0xc
                   (uint)*(byte *)(iVar13 + 0x3e) * 0xc;
		  
		  
		  
		  // Can not skip 25% of trackLen FORWARD,
		  // unless you're in an NMZ, or if finishline is crossed backwards
          if (
				// if racer didn't cross the startline backwards
				((*(uint *)(param_2 + 0x2c8) & 0x1000000) == 0) &&

				// if respawn->0x8 is not 0, or 1,
				// if these are not the quadblocks right behind the finish line,
				// if this is not a No-Mask-Zone (NMZ),
				(1 < *(byte *)(iVar13 + 8)) &&

				// Is this a ghidra fail?
				// Could this be (checkpoint-newDist)*8?
				// That would mean (trackLen/4) < (checkpoint-newDist),
				// means can not go FORWARDS more than 25% of track
				(

					// track length * 2
					((int)((uint)(*(ushort *)(*(int *)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0x14c) + 6) >> 2) << 3)

					// less than
					<

					// distanceToFinish_checkpoint - newDistToFinish*8
					(int)(*(int *)(param_2 + 0x48c) - (uint)*(ushort *)(iVar13 + 6) * 8))
				)
			  )
		  {
			// player needs to be mask grabbed, illegal shortcut
            *(ushort *)(param_2 + 0xaa) = *(ushort *)(param_2 + 0xaa) | 1;
          }



		  // If not mask-grabbed yet
          else
		  {

			// track length
			// level -> respawn points[0] -> dist_to_finish
            uVar2 = *(ushort *)(*(int *)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0x14c) + 6);


			// Can not skip 25% of trackLen BACKWARD,
			// unless invalid checkpoint (papu pyramid bridge), or
			// unless lap progress < 7% (crossed finishline)
            if (
					(
						// if not in the first 7% of lap progression
						(
							// checkpoint->distToFinish
							(uint)*(ushort *)(iVar13 + 6) <

							// 93% track length
							(uint)((int)((uint)uVar2 * 0xf) >> 4)
						) &&

						// last valid quadblock has a "valid" checkpoint index
						(bVar4 = *(byte *)(*(int *)(param_2 + 0x354) + 0x3e), bVar4 != 0xff)
					) &&

					// can not go BACKWARD more than 25% of track
					(
					  (uint)*(ushort *)

					    // last valid quadblock
						// lev->restartPts[ quadblock (driver 0x354) -> respawn_index ] -> dist to finish
						
						// checkpointPrev->distToFinish
						((uint)bVar4 * 0xc + *(int *)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0x14c) + 6)

						// increasing distance (backwards)
						+

						// track length / 4
						(uint)(uVar2 >> 2)

						<

						// checkpointCurr->distToFinish
						(uint)*(ushort *)(iVar13 + 6)
					)
			   )
			{
			  // mask-grab the driver
			  goto LAB_8001e340;
			}

			// last "valid" quadblock touched (for mask grab) = quadblock just touched
			*(undefined4 *)(param_2 + 0x354) = *(undefined4 *)(param_2 + 0xa0);
          }
        }
      }
    }

	// if quadblock is killplane
	else {
LAB_8001e340:

	  // player needs to be mask grabbed
      *(ushort *)(param_2 + 0xaa) = *(ushort *)(param_2 + 0xaa) | 1;
    }

    *(undefined2 *)(param_2 + 0x3fc) = 0;

	//turn off 7th and 20th bits of Actions Flag set (means ? (7) and racer is in the air)
    *(uint *)(param_2 + 0x2c8) = *(uint *)(param_2 + 0x2c8) & 0xfff7ffbf;

	// if driver is not touching a quadblock (driver is in the air)
	if ((*(ushort *)(param_2 + 0xaa) & 8) == 0) goto LAB_8001e4d0;

    if (

		// If you are on ice
		// Also could be an effect after hitting Red Potion
		(*(short *)(param_2 + 0x50a) == 2) ||

		// If Icy Tracks Cheat is enabled
		((*(uint *)(PTR_DAT_8008d2ac + 8) & 0x80000) != 0))
	{

	  // Set terrain to Ice
      *(undefined *)(param_2 + 0xc2) = 6;
      uVar6 = 6;
    }

	// If you are not on ice
    else
	{
	  // driver -> quadblock -> terrainType
      bVar4 = *(byte *)(*(int *)(param_2 + 0xa0) + 0x38);

      uVar6 = (uint)bVar4;

      if (
			// if you are not currently on ice
			(bVar4 != 6) &&

			// you "were" on ice last frame
			(*(char *)(param_2 + 0xc2) == '\x06')
		  )
	  {
		// make the car hit the breaks for a second
        *(undefined2 *)(param_2 + 0x414) = 0xfec0;
      }

	  // set new driver -> terrainType
      *(byte *)(param_2 + 0xc2) = bVar4;
    }

	// VehAfterColl_GetTerrain
    uVar7 = FUN_80057c68(uVar6);
    *(undefined4 *)(param_2 + 0x358) = uVar7;
    *(undefined4 *)(param_2 + 0x35c) = uVar7;

	// driver can jump 0.16s after leaving quadblock
	*(undefined2 *)(param_2 + 0x3f4) = 0xa0;

    //uVar6 = Actions Flag set
    uVar6 = *(uint *)(param_2 + 0x2c8);
    //turn on 1st bit of Actions Flag set (means player is touching the ground)
    *(uint *)(param_2 + 0x2c8) = uVar6 | 1;
    if ((*(uint *)(param_2 + 0x2cc) & 1) == 0) {
      if (iVar9 < 0) {
        iVar9 = -iVar9;
      }
      //turn on 1st, 2nd and 8th bits of Actions Flag set (means racer is on the ground (1),
      //racer started touching the ground in this frame (2) and ? (8))
      *(uint *)(param_2 + 0x2c8) = uVar6 | 0x83;
      *(undefined2 *)(param_2 + 0x414) = 0x140;

      // Map value from [oldMin, oldMax] to [newMin, newMax]
      // inverting newMin and newMax will give an inverse range mapping
      uVar6 = FUN_80058f9c(iVar9,0x100,0x3c00,0x78,0xfa);

      //if racer is not being mask grabbed
      if (*(char *)(param_2 + 0x376) != '\x05')
	  {
		// volume
        uVar6 = (uVar6 & 0xff) << 0x10;

		// if no echo
        if ((*(uint *)(param_2 + 0x2c8) & 0x10000) == 0)
		{
		  // no distortion, equal left/right
          uVar6 = uVar6 | 0x8080;
        }

		// if echo
        else
		{
		  // add echo
          uVar6 = uVar6 | 0x1008080;
        }

		// OtherFX_Play_LowLevel
		// sound of landing on ground
        FUN_800284d0(7,1,uVar6);
      }
    }
    iVar9 = 6;
  }
  
  // inverse
  iVar13 = 8 - iVar9;
  
  // lerp from quadblockNormalVec to normalVecUP
  local_30 = iVar9 * *(short *)(param_2 + 0x368) + iVar13 * *(short *)(param_2 + 0xa4) >> 3;
  local_2c = iVar9 * *(short *)(param_2 + 0x36a) + iVar13 * *(short *)(param_2 + 0xa6) >> 3;
  local_28 = iVar9 * *(short *)(param_2 + 0x36c) + iVar13 * *(short *)(param_2 + 0xa8) >> 3;

  //if Hazard Timer is positive (racer in hazard)
  if (0 < (int)*(short *)(param_2 + 0xe)) {
  	//uVar6 = Hazard Timer * 0xC
    uVar6 = (int)*(short *)(param_2 + 0xe) * 0xc;

	// approximate trigonometry
	sVar5 = (short)*(int *)(&DAT_800845a0 + (uVar6 & 0x3ff) * 4);
    iVar9 = *(int *)(&DAT_800845a0 + (uVar6 & 0x3ff) * 4) >> 0x10;

	if ((uVar6 & 0x400) == 0) {
      iVar13 = (int)sVar5;
      if ((uVar6 & 0x800) != 0) {
        iVar14 = -iVar9;
        goto LAB_8001e680;
      }
    }
    else {
      iVar14 = (int)sVar5;
      iVar13 = iVar9;
      if ((uVar6 & 0x800) == 0) {
        iVar9 = -iVar14;
      }
      else {
LAB_8001e680:
        iVar13 = -iVar13;
        iVar9 = iVar14;
      }
    }
	
    gte_ldVXY0(iVar13 * 0x19 >> 10 & 0xffff);
    gte_ldVZ0(iVar9 * 0x19 >> 10);

	// rtv0     cop2 $0486012  v0 * rotmatrix
    gte_rtv0();

	read_mt(iVar9,iVar14,iVar13);
	
    local_30 = local_30 + iVar9;
    local_2c = local_2c + iVar14;
    local_28 = local_28 + iVar13;
  }

  // uVar6 = sqrt(x2+y2+z2 << 0x18)
  uVar6 = FUN_80059070(local_30 * local_30 + local_2c * local_2c + local_28 * local_28,0x18);

  uVar6 = uVar6 >> 0xc;
  if (uVar6 == 0) {
    trap(0x1c00);
  }
  if ((uVar6 == 0xffffffff) && (local_30 << 0xc == -0x80000000)) {
    trap(0x1800);
  }
  *(undefined2 *)(param_2 + 0x368) = (short)((local_30 << 0xc) / (int)uVar6);
  if (uVar6 == 0) {
    trap(0x1c00);
  }
  if ((uVar6 == 0xffffffff) && (local_2c << 0xc == -0x80000000)) {
    trap(0x1800);
  }
  *(undefined2 *)(param_2 + 0x36a) = (short)((local_2c << 0xc) / (int)uVar6);
  if (uVar6 == 0) {
    trap(0x1c00);
  }
  if ((uVar6 == 0xffffffff) && (local_28 << 0xc == -0x80000000)) {
    trap(0x1800);
  }
  uVar10 = SEXT24(*(short *)(param_2 + 0x39a));
  *(undefined2 *)(param_2 + 0x36c) = (short)((local_28 << 0xc) / (int)uVar6);

  // approximate trigonometry
  sVar5 = (short)*(int *)(&DAT_800845a0 + (uVar10 & 0x3ff) * 4);
  iVar9 = *(int *)(&DAT_800845a0 + (uVar10 & 0x3ff) * 4) >> 0x10;

  if ((uVar10 & 0x400) == 0) {
    iVar13 = (int)sVar5;
    if ((uVar10 & 0x800) != 0) {
      iVar14 = -iVar9;
      goto LAB_8001e84c;
    }
  }
  else {
    iVar14 = (int)sVar5;
    iVar13 = iVar9;
    if ((uVar10 & 0x800) == 0) {
      iVar9 = -iVar14;
    }
    else {
LAB_8001e84c:
      iVar13 = -iVar13;
      iVar9 = iVar14;
    }
  }
  lVar8 = ratan2(-(int)*(short *)(param_2 + 0x368) * iVar9 + *(short *)(param_2 + 0x36c) * iVar13 >>
                 0xc,(int)*(short *)(param_2 + 0x36a));
  *(undefined2 *)(param_2 + 0x2f0) = (short)lVar8;

  //if Hazard Timer is negative
  if (*(short *)(param_2 + 0xe) < 1)
  {
    //if racer is on the ground
    if ((*(uint *)(param_2 + 0x2c8) & 1) != 0)
	{
      //iVar9 = Speed
      iVar9 = (int)*(short *)(param_2 + 0x38c);

	  //iVar9 = |iVar9|
      if (iVar9 < 0) {
        iVar9 = -iVar9;
      }

	  //if |iVar9| > 0x1000
      if (0x1000 < iVar9)
	  {
      	//iVar9 = Visual Offset from Ground
        iVar9 = (int)*(char *)(param_2 + 0x377);

		//iVar9 = |iVar9|
        if (iVar9 < 0) {
          iVar9 = -iVar9;
        }

		//if Visual Offset from Ground < 4 and (?)
        if ((iVar9 < 4) && ((*(uint *)(*(int *)(param_2 + 0x358) + 4) & 1) != 0)) {
          *(undefined2 *)(param_2 + 0x3ee) = 4;
        }
        goto LAB_8001e964;
      }
    }
    *(undefined2 *)(param_2 + 0x3ee) = 0;
  }
  //if racer is in hazard
  else {

	//iVar9 = Visual Offset from Ground
    iVar9 = (int)*(char *)(param_2 + 0x377);

	//iVar9 = |iVar9|
    if (iVar9 < 0) {
      iVar9 = -iVar9;
    }
    //if Visual Offset from Ground < 4 and ((?), racer is not spinning)
    if ((iVar9 < 4) && (*(undefined2 *)(param_2 + 0x3ee) = 4, *(char *)(param_2 + 0x376) != '\x03'))
    {
      //iVar9 = Visual Offset from Ground
      iVar9 = (int)*(char *)(param_2 + 0x377);

      //if Visual Offset from Ground < 1, skip next 3 lines of code
      if (iVar9 < 1) goto code_r0x8001e96c;

	  // OtherFX_Play
      FUN_80028468(0x10,1);
    }
  }
LAB_8001e964:
	//iVar9 = Visual Offset from Ground
  iVar9 = (int)*(char *)(param_2 + 0x377);
code_r0x8001e96c:
	//iVar9 = |iVar9|
  if (iVar9 < 0) {
    iVar9 = -iVar9;
  }
  //if Visual Offset from Ground > 9
  if (9 < iVar9) {
    *(undefined2 *)(param_2 + 0x3ee) = 0;
  }

  // if you're close to the ground
  if (*(short *)(param_2 + 0x3ee) == 0) {

	//bVar4 = Visual Offset from Ground - 4
    bVar4 = *(char *)(param_2 + 0x377) - 4;

	if (
			//if Visual Offset from Ground is positive
			('\0' < *(char *)(param_2 + 0x377)) &&

			// Set new offset
			(*(byte *)(param_2 + 0x377) = bVar4,

			// if you are about to go through floor
			(int)((uint)bVar4 << 0x18) < 1))
	{
      //prevent Visual Offset from Ground from going negative
      *(undefined *)(param_2 + 0x377) = 0;

	  // if driver -> terrain -> flags & play_sound
	  if ((*(uint *)(*(int *)(param_2 + 0x358) + 4) & 0x20) != 0)
	  {
		// half volume, no distort, balance left/right
        uVar7 = 0x808080;

        // if echo
        if ((*(uint *)(param_2 + 0x2c8) & 0x10000) != 0)
		{
		  // add echo
          uVar7 = 0x1808080;
        }

		// OtherFX_Play_LowLevel
		// play sound depending on terrain
        FUN_800284d0((uint)*(ushort *)(*(int *)(param_2 + 0x358) + 0x32),0,uVar7);
      }
    }

	// Screen_OffsetY -= 4 
    bVar4 = *(char *)(param_2 + 0x377) - 4;
    *(byte *)(param_2 + 0x377) = bVar4;

    //if Visual Offset from Ground is negative
    if ((int)((uint)bVar4 << 0x18) < 0) {
    	//prevent it from going negative
      *(undefined *)(param_2 + 0x377) = 0;
    }
  }

  // if you're not close to the ground
  else 
  {
	// distanceFromGround++
    *(short *)(param_2 + 0x3ee) = *(short *)(param_2 + 0x3ee) + -1;
	
	// Screen_OffsetY += 3
    *(char *)(param_2 + 0x377) = *(char *)(param_2 + 0x377) + '\x03';
  }

  //if Y pos < -0x8000 and (?)
  if ((*(int *)(param_2 + 0x2d8) < -0x8000) &&

	 // Level -> 0xdc
	 // flag, toggle enable mask grab below height
     ((*(uint *)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0xdc) & 2) != 0))
  {
	// player needs to be mask grabbed,
	// too far underwater in Crash Cove
    *(ushort *)(param_2 + 0xaa) = *(ushort *)(param_2 + 0xaa) | 1;
  }

  if (
		(
			(
				//if racer is not being mask grabbed
				(*(char *)(param_2 + 0x376) != '\x05') &&

				// if player needs to be grabbed (hit kill plane)
				((*(ushort *)(param_2 + 0xaa) & 1) != 0)
			) &&

			// last quadblock touched by driver,
			// why?
			(*(int *)(param_2 + 0x354) != 0)
		) &&

		((
			// if debug no-grab variable is off
			(DAT_8008d000 & 0x1000) == 0 &&

			((*(uint *)(param_2 + 0xbc) & 8) == 0)
		))
	 )

  {
	// NOP-ing this allows you to jump out of bounds,
	// and not get mask-grabbbed when you hit kill planes

	// VehStuckProc_MaskGrab_Init
    FUN_800671b0(param_1,param_2);
  }
  return;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address

// COLL_SearchTree_FindQuadblock_Touching
// param1 - posTop
// param2 - posBottom
// param3 - 1f800108
// param4 - always zero except Camera_FixY(0x280) and TNT/Nitro/Beaker(0x40)
void FUN_8001eb0c(undefined4 *param_1,undefined4 *param_2,undefined4 *param_3,int param_4)

{
  short *psVar1;
  short sVar2;
  int iVar3;
  short sVar4;
  short sVar5;
  int iVar6;
  int iVar7;
  short sVar8;
  undefined4 uVar9;
  short sVar10;
  uint uVar11;
  undefined4 unaff_s0;
  undefined4 unaff_s1;
  undefined4 unaff_s2;
  int iVar12;
  undefined4 unaff_s3;
  undefined4 unaff_s4;
  undefined4 unaff_s5;
  undefined4 unaff_s6;
  undefined4 unaff_s7;
  int iVar13;
  int iVar14;
  undefined4 unaff_s8;
  undefined4 unaff_retaddr;
  undefined auStackX0 [16];

  *(short *)((int)param_3 + 6) = (short)param_4;
  *(short *)((int)param_3 + 0x16) = (short)param_4;
  
  // 1f80014a
  *(short *)((int)param_3 + 0x42) = 0;
  
  *(short *)(param_3 + 0xf) = 0;
  
  // 1f800136
  *(short *)((int)param_3 + 0x3e) = 0;
  
  param_3[0x69] = 0;
  param_3[0x31] = 0;
  uVar9 = *param_1;
  sVar2 = *(short *)(param_1 + 1);
  iVar7 = *(int *)(param_3[0xb] + 0x18);
  *param_3 = uVar9;
  *(short *)(param_3 + 1) = sVar2;
  param_3[7] = uVar9;
  *(short *)(param_3 + 8) = sVar2;
  sVar2 = *(short *)(param_2 + 1);
  param_3[4] = *param_2;
  *(short *)(param_3 + 5) = sVar2;
  param_3[0x21] = 0x1000;
  param_3[2] = param_4 * param_4;
  param_3[6] = param_4 * param_4;
  sVar2 = *(short *)param_3;
  sVar8 = *(short *)(param_3 + 4);
  sVar5 = *(short *)((int)param_3 + 2);
  sVar10 = *(short *)((int)param_3 + 0x12);
  sVar4 = sVar2;
  if ((int)sVar2 - (int)sVar8 < 0) {
    sVar4 = sVar8;
    sVar8 = sVar2;
  }
  *(short *)((int)param_3 + 0x36) = sVar4;
  *(short *)(param_3 + 0xc) = sVar8;
  sVar2 = *(short *)(param_3 + 1);
  sVar8 = *(short *)(param_3 + 5);
  sVar4 = sVar5;
  if ((int)sVar5 - (int)sVar10 < 0) {
    sVar4 = sVar10;
    sVar10 = sVar5;
  }
  *(short *)(param_3 + 0xe) = sVar4;
  *(short *)((int)param_3 + 0x32) = sVar10;
  sVar5 = sVar2;
  if ((int)sVar2 - (int)sVar8 < 0) {
    sVar5 = sVar8;
    sVar8 = sVar2;
  }
  *(short *)((int)param_3 + 0x3a) = sVar5;
  *(short *)(param_3 + 0xd) = sVar8;
  if (iVar7 == 0) {
    DAT_1f800030 = unaff_s0;
    return;
  }
  _DAT_1f800050 = &_gp_4;
  iVar3 = 0x1f800000;
  sVar2 = *(short *)(param_3 + 0xc);
  sVar8 = *(short *)((int)param_3 + 0x32);
  sVar5 = *(short *)(param_3 + 0xd);
  sVar10 = *(short *)((int)param_3 + 0x36);
  iVar13 = (int)*(short *)(param_3 + 0xe);
  iVar14 = (int)*(short *)((int)param_3 + 0x3a);
  iVar12 = iVar7;
  DAT_1f800030 = unaff_s0;
  DAT_1f800034 = unaff_s1;
  DAT_1f800038 = unaff_s2;
  DAT_1f80003c = unaff_s3;
  DAT_1f800040 = unaff_s4;
  DAT_1f800044 = unaff_s5;
  DAT_1f800048 = unaff_s6;
  _DAT_1f80004c = unaff_s7;
  DAT_1f800054 = (undefined *)register0x00000074;
  _DAT_1f800058 = unaff_s8;
  DAT_1f80005c = unaff_retaddr;
  do {
    uVar11 = *(uint *)(iVar12 + 0x18);
    if ((uVar11 + 1 & 0xffff) != 0) {
      iVar12 = (uVar11 & 0x3fff) * 0x20 + iVar7;
      if (((((*(int *)(iVar12 + 4) >> 0x10) - iVar13 < 1) &&
           (iVar6 = *(int *)(iVar12 + 0xc), (int)(short)*(int *)(iVar12 + 4) - (int)sVar10 < 1)) &&
          ((int)sVar2 - (*(int *)(iVar12 + 8) >> 0x10) < 1)) &&
         ((((short)*(int *)(iVar12 + 8) - iVar14 < 1 && ((int)sVar5 - (iVar6 >> 0x10) < 1)) &&
          (*(undefined2 *)(iVar3 + 0x70) = (short)uVar11, (int)sVar8 - (int)(short)iVar6 < 1)))) {
        iVar3 = iVar3 + 2;
      }
    }
    if ((int)uVar11 >> 0x10 != 0xffffffff) {
      iVar12 = ((int)uVar11 >> 0x10 & 0x3fffU) * 0x20 + iVar7;
      if ((((*(int *)(iVar12 + 4) >> 0x10) - iVar13 < 1) &&
          (iVar6 = *(int *)(iVar12 + 0xc), (int)(short)*(int *)(iVar12 + 4) - (int)sVar10 < 1)) &&
         (((int)sVar2 - (*(int *)(iVar12 + 8) >> 0x10) < 1 &&
          ((((short)*(int *)(iVar12 + 8) - iVar14 < 1 && ((int)sVar5 - (iVar6 >> 0x10) < 1)) &&
           (*(undefined2 *)(iVar3 + 0x70) = (short)(uVar11 >> 0x10),
           (int)sVar8 - (int)(short)iVar6 < 1)))))) {
        iVar3 = iVar3 + 2;
      }
    }
    while( true ) {
      if (iVar3 == 0x1f800000) {
        return;
      }
      psVar1 = (short *)(iVar3 + 0x6e);
      iVar3 = iVar3 + -2;

	  // bspRoot[iVar7]
      iVar12 = ((int)*psVar1 & 0x3fffU) * 0x20 + iVar7;

	  // If this is not a leaf node, break
      if (((int)*psVar1 & 0x4000U) == 0) break;
	  
	  // as long as we have leaf nodes, keep going...

	  DAT_1f800064 = iVar13;
      _DAT_1f800068 = iVar14;
      DAT_1f80006c = iVar3;

	  // COLL_PerBspLeaf_CheckQuadblocks_Touching
      FUN_8001f5f0(iVar12,param_3);

	  iVar3 = DAT_1f80006c;
      iVar13 = DAT_1f800064;
      iVar14 = _DAT_1f800068;
    }
  } while( true );
}


// COLL_SearchTree_FindX
// param1, pointer to bsp
// param2, pointer to boundingbox
// param3, callback if item collides with anything
// param4, 1f800108
void FUN_8001ebec(int param_1,short *param_2,code *param_3,undefined4 param_4)

{
  short *psVar1;
  short sVar2;
  short sVar3;
  short sVar4;
  short sVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  undefined4 unaff_s0;
  undefined4 unaff_s1;
  undefined4 unaff_s2;
  int iVar9;
  undefined4 unaff_s3;
  undefined4 unaff_s4;
  undefined4 unaff_s5;
  undefined4 unaff_s6;
  undefined4 unaff_s7;
  int iVar10;
  int iVar11;
  undefined4 unaff_s8;
  undefined4 unaff_retaddr;
  undefined auStackX0 [16];

  // if level has no bsp, quit
  if (param_1 == 0) {
    DAT_1f800030 = unaff_s0;
    return;
  }

  // start array of bspIDs
  // inside scratchpad
  iVar6 = 0x1f800000;

  // hitbox
  sVar2 = *param_2;
  sVar3 = param_2[1];
  sVar4 = param_2[2];
  sVar5 = param_2[3];
  iVar10 = (int)param_2[4];
  iVar11 = (int)param_2[5];
  
  iVar9 = param_1;
  DAT_1f800030 = unaff_s0;
  DAT_1f800034 = unaff_s1;
  DAT_1f800038 = unaff_s2;
  DAT_1f80003c = unaff_s3;
  DAT_1f800040 = unaff_s4;
  DAT_1f800044 = unaff_s5;
  DAT_1f800048 = unaff_s6;
  _DAT_1f80004c = unaff_s7;
  _DAT_1f800050 = (undefined *)register0x00000070;
  DAT_1f800054 = (undefined *)register0x00000074;
  _DAT_1f800058 = unaff_s8;
  DAT_1f80005c = unaff_retaddr;

  // at start of loop, iVar9 is first bsp in LEV,
  // which is the root node of the BSP tree
  do
  {
	// get child IDs (assuming branch, not leaf)
    uVar8 = *(uint *)(iVar9 + 0x18);

	// if left child exists
    if ((uVar8 + 1 & 0xffff) != 0)
	{
	  // set new bsp pointer, to left child
      iVar9 = (uVar8 & 0x3fff) * 0x20 + param_1;

      if (

			(
				(
					// if minPos[y] is less than iVar10
					((*(int *)(iVar9 + 4) >> 0x10) - iVar10 < 1) &&

					(
						iVar7 = *(int *)(iVar9 + 0xc),

						// if minPos[x] is less than sVar5
						(int)(short)*(int *)(iVar9 + 4) - (int)sVar5 < 1
					)
				) &&

				// if maxPos[x] is more than sVar2
				((int)sVar2 - (*(int *)(iVar9 + 8) >> 0x10) < 1)
			) &&
			(
				(
					(
						// if minPos[z] < iVar11
						(short)*(int *)(iVar9 + 8) - iVar11 < 1 &&

						// if maxPos[z] > sVar4
						((int)sVar4 - (iVar7 >> 0x10) < 1)
					) &&

					(
						// set ID list index to bsp left child ID,
						// array starts 0x70 bytes after start of scratchpad
						*(undefined2 *)(iVar6 + 0x70) = (short)uVar8,

						// if maxPos[y] > sVar3
						(int)sVar3 - (int)(short)iVar7 < 1
					)
				)
			)
		  )
	  {
		// increment array index
        iVar6 = iVar6 + 2;
      }
    }

	// if right child exists
    if ((int)uVar8 >> 0x10 != 0xffffffff)
	{
	  // set new bsp pointer, to right child
      iVar9 = ((int)uVar8 >> 0x10 & 0x3fffU) * 0x20 + param_1;

      if (
			(
				// if minPos[y] is less than iVar10
				((*(int *)(iVar9 + 4) >> 0x10) - iVar10 < 1) &&

				(
					iVar7 = *(int *)(iVar9 + 0xc),

					// if minPos[x] is less than sVar5
					(int)(short)*(int *)(iVar9 + 4) - (int)sVar5 < 1
				)
			) &&
			(
				(
					// if maxPos[x] is more than sVar2
					(int)sVar2 - (*(int *)(iVar9 + 8) >> 0x10) < 1 &&

					(
						(
							(
								// if minPos[z] is less than iVar11
								(short)*(int *)(iVar9 + 8) - iVar11 < 1 &&

								// if maxPos[z] is more than iVar11
								((int)sVar4 - (iVar7 >> 0x10) < 1)
							) &&

							// set ID list index to bsp right child ID,
							// array starts 0x70 bytes after start of scratchpad
							(*(undefined2 *)(iVar6 + 0x70) = (short)(uVar8 >> 0x10),

							// if maxPos[y] > sVar3
							(int)sVar3 - (int)(short)iVar7 < 1)
						)
					)
				)
			)
		  )
	  {
		// increment array index
        iVar6 = iVar6 + 2;
      }
    }

    while( true )
	{
	  // if nothing in the array was written,
	  // due to pointer never incrementing
      if (iVar6 == 0x1f800000) {
        return;
      }

	  // backtrack the array
      psVar1 = (short *)(iVar6 + 0x6e);
      iVar6 = iVar6 + -2;

	  // pointer to last BSP node of last index
	  iVar9 = ((int)*psVar1 & 0x3fffU) * 0x20 + param_1;

	  // If this is not a leaf node, break
      if (((int)*psVar1 & 0x4000U) == 0) break;
	  
	  // as long as we have leaf nodes, keep going...

      DAT_1f800064 = iVar10;
      _DAT_1f800068 = iVar11;
      DAT_1f80006c = iVar6;

	  // function callback
	  // iVar9 is bsp
      (*param_3)(iVar9,param_4);

	  iVar6 = DAT_1f80006c;
      iVar10 = DAT_1f800064;
      iVar11 = _DAT_1f800068;
    }

  } while( true );
}


// part of triangle collision
uint FUN_8001ede4(undefined2 *param_1,short *param_2,short *param_3,short *param_4)
{
  short sVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  uint uVar9;
  int iVar10;
  uint uVar11;

  iVar6 = (int)*param_2;
  iVar7 = (int)param_2[1];
  iVar8 = (int)param_2[2];
  sVar1 = param_4[1];
  uVar9 = *param_3 - iVar6;
  iVar10 = param_3[1] - iVar7;
  uVar11 = param_3[2] - iVar8;
  uVar2 = uVar9 & 0xffff | iVar10 * 0x10000;
  gte_ldR11R12(uVar2);
  gte_ldR13R21(uVar11 & 0xffff | (*param_4 - iVar6) * 0x10000);
  gte_ldR22R23(sVar1 - iVar7 & 0xffffU | (param_4[2] - iVar8) * 0x10000);
  gte_ldVXY0(uVar2);
  gte_ldVZ0(uVar11);
  gte_mvmva(0,0,0,3,0);
  iVar3 = gte_stMAC2();
  iVar4 = gte_stMAC1();
  gte_ldLZCS(iVar3);
  iVar5 = gte_stLZCR();
  uVar2 = iVar5 - 2;
  if ((int)uVar2 < 0) {
    uVar2 = 0;
  }
  else if (0 < iVar5 + -0xe) {
    uVar2 = 0xc;
  }
  if ((int)(uVar2 - 0xc) < 0) {
    iVar4 = iVar4 >> (-(uVar2 - 0xc) & 0x1f);
  }
  iVar5 = 0;
  if (iVar4 != 0) {
    iVar4 = (iVar3 << (uVar2 & 0x1f)) / iVar4;
    if ((-1 < iVar4) && (iVar5 = iVar4, 0 < iVar4 + -0x1000)) {
      iVar5 = 0x1000;
    }
  }
  gte_ldIR0(iVar5);
  gte_ldMAC1(iVar6);
  gte_ldMAC2(iVar7);
  gte_ldMAC3(iVar8);
  gte_ldsv_(uVar9,iVar10,uVar11);
  gte_gpl12();
  read_mt(uVar9,iVar10,uVar11);
  *param_1 = (short)uVar9;
  param_1[1] = (short)iVar10;
  param_1[2] = (short)uVar11;
  return sVar1 - iVar7;
}


// COLL_TestTriangle_Unused
// hand-written assembly, stores $s0, $s1, and $s2
// then restores registers, and saves t2 into $a0->58
void FUN_8001ef1c(void)
{
		// does a breakpoint at 8001ef1c ever hit anyway?

        8001ef1c e0 ff bd 27     addiu      sp,sp,-0x20
        8001ef20 10 00 b0 af     sw         s0,0x10(sp)
        8001ef24 14 00 b1 af     sw         s1,0x14(sp)
        8001ef28 1c 00 bf af     sw         ra,0x1c(sp)
        8001ef2c 18 00 b2 af     sw         s2,0x18(sp)

		// FUN_8001ef50, except skipping 9 instructions
		8001ef30 dd 7b 00 0c     jal        FUN_8001ef74
        8001ef34 58 00 8a 8c     _lw        t2,0x58(a0)

        8001ef38 1c 00 bf 8f     lw         ra,0x1c(sp)
        8001ef3c 18 00 b2 8f     lw         s2,0x18(sp)
        8001ef40 14 00 b1 8f     lw         s1,0x14(sp)
        8001ef44 10 00 b0 8f     lw         s0,0x10(sp)
        8001ef48 08 00 e0 03     jr         ra
        8001ef4c 20 00 bd 27     _addiu     sp,sp,0x20
}


// COLL_TestTriangle_FindAny
// param1 - 1f800108
// param2,3,4, triangle points
void FUN_8001ef50(int param_1,short *param_2,short *param_3,short *param_4)

{
  short sVar1;
  int iVar2;
  short *psVar3;
  undefined4 uVar4;
  int iVar5;
  undefined4 uVar6;
  int iVar7;
  uint uVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  uint uVar12;
  int iVar13;
  int iVar14;

  // FUN_8001ef74 is this same function, except skipping
  // the first 9 instructions

  // LevVertex offset 6 (in scratchpad)
  // collision flag
  sVar1 = param_2[3];
  
  uVar6 = *(undefined4 *)(param_2 + 6);
  iVar7 = *(int *)(param_2 + 8);
  *(short *)(param_1 + 0x3c) = *(short *)(param_1 + 0x3c) + 1;
  *(short *)(param_1 + 0x52) = sVar1;
  *(undefined4 *)(param_1 + 0x54) = uVar6;
  *(int *)(param_1 + 0x58) = iVar7;
  
  // hitbox data (center of hitbox?)
  uVar8 = (uint)*(short *)(param_1 + 0x14);
  gte_ldR11R12(*(undefined4 *)(param_1 + 0x10));
  iVar11 = (int)*(short *)(param_1 + 0x1c) - (int)*(short *)(param_1 + 0x10);
  uVar12 = (int)*(short *)(param_1 + 0x1e) - (int)*(short *)(param_1 + 0x12);
  iVar14 = (int)*(short *)(param_1 + 0x20) - uVar8;
  
  gte_ldR13R21(iVar11 * 0x10000 | uVar8 & 0xffff);
  gte_ldR22R23(uVar12 & 0xffff | iVar14 * 0x10000);
  gte_ldVXY0(param_1 + 0x54);
  gte_ldVZ0(iVar7);
  gte_mvmva_b(0,0,0,3,0);
  iVar5 = gte_stMAC2();
  iVar2 = gte_stMAC1();
  
  // quit function if this fails
  if (iVar5 < 0) 
  {
    iVar2 = -(iVar2 + (iVar7 >> 0x10) * -0x2000) / (iVar5 >> 0xc);
    gte_ldMAC1((int)*(short *)(param_1 + 0x10));
    gte_ldMAC2((int)*(short *)(param_1 + 0x12));
    gte_ldMAC3(uVar8);
    gte_ldsv_(iVar11,uVar12,iVar14);
    gte_ldIR0(iVar2);
	
	// quit function if this fails
    if ((-1 < iVar2) && (iVar2 + -0x1000 < 1)) 
	{
      gte_gpl12_b();
      read_mt(iVar11,uVar12,iVar14);
      
	  // position x,y,z
	  *(short *)(param_1 + 0x4c) = (short)iVar11;
      *(short *)(param_1 + 0x4e) = (short)uVar12;
      *(short *)(param_1 + 0x50) = (short)iVar14;
      
	  psVar3 = param_3;
	  
	  // flag == 3
      if (*(short *)(param_1 + 0x52) == 3) 
	  {
		// Z length vectors
        iVar2 = (int)param_2[2];
        iVar9 = param_3[2] - iVar2;
        iVar7 = param_4[2] - iVar2;
        iVar2 = iVar14 - iVar2;
        
		// absolute value
		iVar5 = iVar9;
        if (iVar9 < 0) {
          iVar5 = -iVar9;
        }
		
		// absolute value
        iVar14 = iVar7;
        if (iVar7 < 0) {
          iVar14 = -iVar7;
        }
		
		// flip if needed
        iVar10 = iVar9;
        if (iVar5 - iVar14 < 0) {
          psVar3 = param_4;
          param_4 = param_3;
          iVar10 = iVar7;
          iVar7 = iVar9;
        }
        
		// X length vectors
		iVar14 = (int)*param_2;
        iVar5 = *psVar3 - iVar14;
        iVar9 = *param_4 - iVar14;
        iVar11 = iVar11 - iVar14;
      }
      
	  // != 3
	  else 
	  {
        iVar2 = (int)*param_2;
		
		// flag == 1
        if (*(short *)(param_1 + 0x52) == 1) 
		{
		  // X length vectors
          iVar14 = *param_3 - iVar2;
          iVar7 = *param_4 - iVar2;
          iVar2 = iVar11 - iVar2;
          
		  // absolute value
		  iVar5 = iVar14;
          if (iVar14 < 0) {
            iVar5 = -iVar14;
          }
		  
		  // absolute value
          iVar11 = iVar7;
          if (iVar7 < 0) {
            iVar11 = -iVar7;
          }
		  
		  // flip if needed
          iVar10 = iVar14;
          if (iVar5 - iVar11 < 0) {
            psVar3 = param_4;
            param_4 = param_3;
            iVar10 = iVar7;
            iVar7 = iVar14;
          }
          
		  // Y length vectors
		  iVar11 = (int)param_2[1];
          iVar5 = psVar3[1] - iVar11;
          iVar9 = param_4[1] - iVar11;
          iVar11 = uVar12 - iVar11;
        }
        
		// != 1
		else 
		{
		  // Y length vectors
          iVar2 = (int)param_2[1];
          iVar11 = param_3[1] - iVar2;
          iVar7 = param_4[1] - iVar2;
          iVar2 = uVar12 - iVar2;
		  
		  // absolute value
          iVar5 = iVar11;
          if (iVar11 < 0) {
            iVar5 = -iVar11;
          }
		  
		  // absolute value
          iVar9 = iVar7;
          if (iVar7 < 0) {
            iVar9 = -iVar7;
          }
		  
		  // flip if needed
          iVar10 = iVar11;
          if (iVar5 - iVar9 < 0) {
            psVar3 = param_4;
            param_4 = param_3;
            iVar10 = iVar7;
            iVar7 = iVar11;
          }
		  
		  // Z length vectors
          iVar11 = (int)param_2[2];
          iVar5 = psVar3[2] - iVar11;
          iVar9 = param_4[2] - iVar11;
          iVar11 = iVar14 - iVar11;
        }
      }
	  
	  
      iVar14 = -0x1000;
      iVar13 = -0x1000;
	  
	  // if one length is zero
      if (iVar10 == 0) 
	  {
        iVar14 = -0x1000;
        
		// if other length is zero
		if (iVar7 == 0) 
		{
		  // no collision
          return;
        }
		
        iVar13 = (iVar2 << 0xc) / iVar7;
		
        if ((-1 < iVar13) && (iVar13 + -0x1000 < 1)) 
		{
          iVar14 = (iVar11 * 0x1000 - iVar13 * iVar9) / iVar5;
        }
      }
      
	  else 
	  {
        iVar9 = iVar9 * iVar10 - iVar7 * iVar5 >> 6;
        
		if (iVar9 != 0) 
		{
          iVar13 = ((iVar11 * iVar10 - iVar2 * iVar5) * 0x40) / iVar9;
          
		  if ((-1 < iVar13) && (iVar13 + -0x1000 < 1)) 
		  {
            iVar14 = (iVar2 * 0x1000 - iVar13 * iVar7) / iVar10;
          }
        }
      }
      
	  // quadblock
	  iVar2 = *(int *)(param_1 + 100);
	  
	  // if iVar14 or iVar13 is -0x1000,
	  // then the function quits
	  
	  // if neither of these are -0x1000
      if ((-1 < iVar14) && (iVar14 + iVar13 + -0x1000 < 1))
	  {
		// quadblock flags & TriggerScript,
		// such as turbo pad, and hub loading
        if ((*(ushort *)(iVar2 + 0x12) & 0x40) != 0) 
		{
		  // append bits, these get copied to driver->0xBC
          *(uint *)(param_1 + 0x1a4) = *(uint *)(param_1 + 0x1a4) | (uint)*(byte *)(iVar2 + 0x38);
          return;
        }
		
		// if collision is not disabled, record the detection
		
        *(int *)(param_1 + 0x80) = iVar2;
        *(short *)(param_1 + 200) = (short)iVar14;
        *(short *)(param_1 + 0xca) = (short)iVar13;
        uVar6 = *(undefined4 *)(psVar3 + 4);
        uVar4 = *(undefined4 *)(param_4 + 4);
        *(undefined4 *)(param_1 + 0xcc) = *(undefined4 *)(param_2 + 4);
        *(undefined4 *)(param_1 + 0xd0) = uVar6;
        *(undefined4 *)(param_1 + 0xd4) = uVar4;
        *(short *)(param_1 + 0x3e) = *(short *)(param_1 + 0x3e) + 1;
        *(undefined4 *)(param_1 + 0x68) = *(undefined4 *)(param_1 + 0x4c);
        *(undefined4 *)(param_1 + 0x1c) = *(undefined4 *)(param_1 + 0x4c);
        *(undefined2 *)(param_1 + 0x6c) = *(undefined2 *)(param_1 + 0x50);
        *(undefined2 *)(param_1 + 0x20) = *(undefined2 *)(param_1 + 0x50);
        *(undefined4 *)(param_1 + 0x70) = *(undefined4 *)(param_1 + 0x54);
        *(undefined4 *)(param_1 + 0x74) = *(undefined4 *)(param_1 + 0x58);
      }
    }
  }
  return;
}


// COLL_TestTriangle_GetNormalVector
void FUN_8001f2dc(int param_1,undefined4 *param_2,short *param_3,short *param_4)

{
  uint uVar1;
  short sVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;

  // vector param_4 minus param_2
  // flip param_2 axes, so normal is oriented with Y facing up
  gte_ldR11R12((int)*param_4 - (int)*(short *)param_2 & 0xffff);
  gte_ldR22R23((int)param_4[1] - (int)*(short *)((int)param_2 + 2) & 0xffff);
  gte_ldR33((int)param_4[2] - (int)*(short *)(param_2 + 1) & 0xffff);
  
  // vector param_3 minus param_2
  // flip param_2 axes, so normal is oriented with Y facing up
  gte_ldsv_((int)*param_3 - (int)*(short *)param_2,
            (int)param_3[1] - (int)*(short *)((int)param_2 + 2),
            (int)param_3[2] - (int)*(short *)(param_2 + 1));
  
  // 2 for low-poly, 0 for high-poly
  uVar1 = (uint)*(byte *)(param_1 + 0x1ab);
  
  // quadblock offset 0x3f
  uVar3 = (uint)*(byte *)(param_1 + 0x1aa);
  
  // cross product of two vectors on the triangle,
  //	param_4 - param_2 (v3-v1)
  //	param_3 - param_2 (v2-v1)
  gte_op0_b(0);
  
  // data from quadblock 0x48 - 0x5c
  iVar4 = (int)*(short *)(param_1 + 0x1a8);
  
  // result of cross product,
  // this is an un-normalized normal vector,
  iVar5 = gte_stMAC1();
  iVar6 = gte_stMAC2();
  iVar7 = gte_stMAC3();
  
  gte_ldR11R12(*param_2);
  gte_ldR13R21((uint)*(ushort *)(param_2 + 1));
  
  // [scaled normalVec]
  // breakpoint 8001f37c, (GTE result >> poly-level)
  // can be seen in registers t3, t4, t5
  
  // [footer]
  // tool math to generate footer, assuming quadblock3F
  // is always 0x12: normalize scaled vector, then:
  // footer = (normalizedVec << 12)/scaledVec
  
  // (GTE result >> poly-level) * (footer >> quadblock3F)
  iVar5 = (iVar5 >> (uVar1 & 0x1f)) * iVar4 >> (uVar3 & 0x1f);
  iVar6 = (iVar6 >> (uVar1 & 0x1f)) * iVar4 >> (uVar3 & 0x1f);
  iVar4 = (iVar7 >> (uVar1 & 0x1f)) * iVar4 >> (uVar3 & 0x1f);
  
  // load normalized normal vector onto GTE,
  // checked with t3,t4,t5 at 8001f3a4 with debugger
  gte_ldsv_(iVar5,iVar6,iVar4);
  
  // normal vector X and Y
  *(short *)(param_2 + 3) = (short)iVar5;
  *(short *)((int)param_2 + 0xe) = (short)iVar6;
  
  gte_rtir_b();
  
  iVar7 = gte_stMAC1();
  
  // normal vector Z
  *(short *)(param_2 + 4) = (short)iVar4;
  
  *(short *)((int)param_2 + 0x12) = (short)(iVar7 >> 1);
  
  // absolute value
  if (iVar5 < 0) iVar5 = -iVar5;
  if (iVar6 < 0) iVar6 = -iVar6;
  if (iVar4 < 0) iVar4 = -iVar4;
  
  sVar2 = 1;
  if (iVar5 - iVar6 < 0) {
    sVar2 = 1;
    if (-1 < iVar6 - iVar4) {
      sVar2 = 3;
    }
  }
  else if (-1 < iVar5 - iVar4) {
    sVar2 = 2;
  }
  
  *(short *)((int)param_2 + 6) = sVar2;
  
  return;
}


// COLL_PerQuadblock_CheckTriangles_Touching
// param1 - ptrQuadblock
// param2 - BSP Search Result: either 0x1f800108, 0x1f800118, 8008db1c
void FUN_8001f41c(int param_1,int param_2)

{
  // ??? used to write to quadBlocksRendered ???
  // "at + 100 = 80096404" from 226 ? which is quadblocksrendered
  *(int *)(param_2 + 100) = param_1;

  if (
		(
			(
				// quadblock flags
				((*(uint *)(param_2 + 0x24) & (int)*(short *)(param_1 + 0x12)) != 0) &&

				// quadblock flags
				((*(uint *)(param_2 + 0x28) & (int)*(short *)(param_1 + 0x12)) == 0)
			) &&

			// min[y] less than [???]
			((*(int *)(param_1 + 0x2c) >> 0x10) - (int)*(short *)(param_2 + 0x38) < 1)
		) &&

		(
			(
				(
					// min[x] less than [???]
					(int)(short)*(int *)(param_1 + 0x2c) - (int)*(short *)(param_2 + 0x36) < 1 &&

					// max[x] more than [???]
					((int)*(short *)(param_2 + 0x30) - (*(int *)(param_1 + 0x30) >> 0x10) < 1)
				) &&

				(
					(
						// min[z] less than [???]
						(int)(short)*(int *)(param_1 + 0x30) - (int)*(short *)(param_2 + 0x3a) < 1 &&

						// max[z] more than [???]
						((int)*(short *)(param_2 + 0x34) - (*(int *)(param_1 + 0x34) >> 0x10) < 1)
					)
				)
			)
		)
	  )
  {
	// max[y] more than [???]
    if ((int)*(short *)(param_2 + 0x32) - (int)(short)*(int *)(param_1 + 0x34) < 1)
	{
	  // if 3P or 4P mode,
	  // then use low-LOD quadblock collision (two triangles)
      if ((*(ushort *)(param_2 + 0x22) & 2) == 0) 
	  {
		// COLL_TestQuadblock_TwoTris
        FUN_8001f67c(param_2,param_1);
		
		// call FUN_8001ef50 two times, one per triangle
		  
        FUN_8001ef50(0x1f800108, 0x1f8001f8, 0x1f80020c, 0x1f800220); // 0,1,2
        if (*(uint *)(param_1 + 4) >> 0x10 != (*(uint *)(param_1 + 4) & 0xffff)) {
          FUN_8001ef50(0x1f800108, 0x1f80020c, 0x1f800234, 0x1f800220); // 1,3,2
        }
      }
      else {
        if ((*(ushort *)(param_2 + 0x22) & 8) == 0) 
		{
		  // COLL_TestQuadblock_EightTris
          FUN_8001f6f0(param_2,param_1);
        }
		
		// call FUN_8001ef50 eight times, one per triangle
		
		// all values are offset 0x10 from what they should be, for some reason?
		
        FUN_8001ef50(0x1f800118, 0x1f8002a8, 0x1f800280, 0x1f800294); // 8, 6, 7
        FUN_8001ef50(0x1f800118, 0x1f800294, 0x1f800244, 0x1f8002a8); // 7, 3, 8
        FUN_8001ef50(0x1f800118, 0x1f80021c, 0x1f800294, 0x1f800280); // 1, 7, 6
        FUN_8001ef50(0x1f800118, 0x1f800230, 0x1f800280, 0x1f8002a8); // 2, 6, 8
        if (*(uint *)(param_1 + 4) >> 0x10 != (*(uint *)(param_1 + 4) & 0xffff)) {
          FUN_8001ef50(0x1f800118, 0x1f800208, 0x1f800258, 0x1f80026c); // 0, 4, 5
          FUN_8001ef50(0x1f800118, 0x1f800258, 0x1f800280, 0x1f80026c); // 4, 6, 5
          FUN_8001ef50(0x1f800118, 0x1f800280, 0x1f800258, 0x1f80021c); // 6, 4, 1
          FUN_8001ef50(0x1f800118, 0x1f80026c, 0x1f800280, 0x1f800230); // 5, 6, 2
          return;
        }
      }
    }
  }
  return;
}


// COLL_PerBspLeaf_CheckQuadblocks_Touching
// param_1 is bsp node
// param_2 is 0x1f800108
void FUN_8001f5f0(uint *param_1,int param_2)

{
  uint uVar1;
  uint uVar2;

  // if bsp flag is water
  if ((*param_1 & 2) != 0) {
    *(uint *)(param_2 + 0x1a4) = *(uint *)(param_2 + 0x1a4) | 0x8000;
  }

  // number of quadblocks
  uVar1 = param_1[6];

  // pointer to quadblocks
  uVar2 = param_1[7];

  // loop through all quadblocks
  do
  {
	// COLL_PerQuadblock_CheckTriangles_Touching
    FUN_8001f41c(uVar2,param_2);

	// reduce count
	uVar1 = uVar1 - 1;
	
	// next quadblock
    uVar2 = uVar2 + 0x5c;
	
  } while (0 < (int)uVar1);

  if ((*(ushort *)(param_2 + 0x22) & 1) != 0)
  {
	// PerBspLeaf_CheckInstances
    FUN_8001d610(param_1,param_2);
  }
  return;
}


// COLL_TestQuadblock_TwoTris
void FUN_8001f67c(int param_1,int param_2)

{
  undefined uVar1;

  // COLL_ResetScratchpadCache
  FUN_8001f7f0(0x1f800108);
  
  // quadblock offset 0x3f
  uVar1 = *(undefined *)(param_2 + 0x3f);
  
  // always 2 for low poly (big block)
  *(undefined *)(param_1 + 0x1ab) = 2;
  
  *(undefined *)(param_1 + 0x1aa) = uVar1;
  
  // calculate normal vectors for two triangles,
  // no collision detection here
  
  if (*(short *)(param_1 + 0xec) != *(short *)(param_1 + 0xee)) {
    *(undefined2 *)(param_1 + 0x1a8) = *(undefined2 *)(param_2 + 0x5a);
    FUN_8001f2dc(0x1f800108, 0x1f80020c, 0x1f800234, 0x1f800220); // 1, 3, 2
  }
  *(undefined2 *)(param_1 + 0x1a8) = *(undefined2 *)(param_2 + 0x58);
  FUN_8001f2dc(0x1f800108, 0x1f8001f8, 0x1f80020c, 0x1f800220); // 0, 1, 2
  return;
}


// COLL_TestQuadblock_EightTris
void FUN_8001f6f0(int param_1,int param_2)

{
  undefined uVar1;

  // COLL_ResetScratchpadCache
  FUN_8001f7f0(0x1f800108);
  
  // quadblock offset 0x3f
  uVar1 = *(undefined *)(param_2 + 0x3f);
  
  // always 0 for high poly (small block)
  *(undefined *)(param_1 + 0x1ab) = 0;
  
  *(undefined *)(param_1 + 0x1aa) = uVar1;
  
  // calculate normal vectors for eight triangles,
  // no collision detection here
  
  if (*(short *)(param_1 + 0xec) != *(short *)(param_1 + 0xee)) {  // Do we hit two quads? if then, check two quads.
    *(undefined2 *)(param_1 + 0x1a8) = *(undefined2 *)(param_2 + 0x50); // triangle 4
    FUN_8001f2dc(0x1f800108, 0x1f800298, 0x1f800270, 0x1f800284); // 8, 6, 7
    *(undefined2 *)(param_1 + 0x1a8) = *(undefined2 *)(param_2 + 0x52); // triangle 5
    FUN_8001f2dc(0x1f800108, 0x1f800284, 0x1f800234, 0x1f800298); // 7, 3, 8
    *(undefined2 *)(param_1 + 0x1a8) = *(undefined2 *)(param_2 + 0x54); // triangle 6
    FUN_8001f2dc(0x1f800108, 0x1f80020c, 0x1f800284, 0x1f800270); // 1, 7, 6
    *(undefined2 *)(param_1 + 0x1a8) = *(undefined2 *)(param_2 + 0x56); // triangle 7
    FUN_8001f2dc(0x1f800108, 0x1f800220, 0x1f800270, 0x1f800298); // 2, 6, 8
  }
  *(undefined2 *)(param_1 + 0x1a8) = *(undefined2 *)(param_2 + 0x48); // triangle 0
  FUN_8001f2dc(0x1f800108, 0x1f8001f8, 0x1f800248, 0x1f80025c); // 0, 4, 5
  *(undefined2 *)(param_1 + 0x1a8) = *(undefined2 *)(param_2 + 0x4a); // triangle 1
  FUN_8001f2dc(0x1f800108, 0x1f800248, 0x1f800270, 0x1f80025c); // 4, 6, 5
  *(undefined2 *)(param_1 + 0x1a8) = *(undefined2 *)(param_2 + 0x4c); // triangle 2
  FUN_8001f2dc(0x1f800108, 0x1f800270, 0x1f800248, 0x1f80020c); // 6, 4, 1
  *(undefined2 *)(param_1 + 0x1a8) = *(undefined2 *)(param_2 + 0x4e); // triangle 3
  FUN_8001f2dc(0x1f800108, 0x1f80025c, 0x1f800270, 0x1f800220); // 5, 6, 2
  return;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address

// COLL_ResetScratchpadCache
void FUN_8001f7f0(int param_1)

{
  ushort uVar1;
  undefined4 *puVar2;
  uint uVar3;
  uint uVar4;
  undefined4 uVar5;
  int in_t8;
  uint *in_t9;
  
  // t9 - pointer to quadblock
  
  uVar3 = *in_t9;
  uVar4 = in_t9[1];
  
  // [0]
  puVar2 = (undefined4 *)((uVar3 & 0xffff) * 0x10 + in_t8);
  uVar5 = puVar2[1];
  *(undefined4 *)(param_1 + 0xf0) = *puVar2;
  *(undefined4 *)(param_1 + 0xf4) = uVar5;
  *(undefined4 **)(param_1 + 0xf8) = puVar2;
  
  // [1]
  puVar2 = (undefined4 *)((uVar3 >> 0x10) * 0x10 + in_t8);
  uVar5 = puVar2[1];
  *(undefined4 *)(param_1 + 0x104) = *puVar2;
  *(undefined4 *)(param_1 + 0x108) = uVar5;
  *(undefined4 **)(param_1 + 0x10c) = puVar2;
  
  *(uint *)(param_1 + 0xec) = uVar4;
  uVar3 = in_t9[2];
  
  // [2]
  puVar2 = (undefined4 *)((uVar4 & 0xffff) * 0x10 + in_t8);
  uVar5 = puVar2[1];
  *(undefined4 *)(param_1 + 0x118) = *puVar2;
  *(undefined4 *)(param_1 + 0x11c) = uVar5;
  *(undefined4 **)(param_1 + 0x120) = puVar2;
  
  // [3]
  puVar2 = (undefined4 *)((uVar4 >> 0x10) * 0x10 + in_t8);
  uVar5 = puVar2[1];
  *(undefined4 *)(param_1 + 300) = *puVar2;
  *(undefined4 *)(param_1 + 0x130) = uVar5;
  *(undefined4 **)(param_1 + 0x134) = puVar2;
  
  uVar4 = in_t9[3];
  
  // [4]
  puVar2 = (undefined4 *)((uVar3 & 0xffff) * 0x10 + in_t8);
  uVar5 = puVar2[1];
  *(undefined4 *)(param_1 + 0x140) = *puVar2;
  *(undefined4 *)(param_1 + 0x144) = uVar5;
  *(undefined4 **)(param_1 + 0x148) = puVar2;
  
  // [5]
  puVar2 = (undefined4 *)((uVar3 >> 0x10) * 0x10 + in_t8);
  uVar5 = puVar2[1];
  *(undefined4 *)(param_1 + 0x154) = *puVar2;
  *(undefined4 *)(param_1 + 0x158) = uVar5;
  *(undefined4 **)(param_1 + 0x15c) = puVar2;
  
  uVar1 = *(ushort *)(in_t9 + 4);
  
  // [6]
  puVar2 = (undefined4 *)((uVar4 & 0xffff) * 0x10 + in_t8);
  uVar5 = puVar2[1];
  *(undefined4 *)(param_1 + 0x168) = *puVar2;
  *(undefined4 *)(param_1 + 0x16c) = uVar5;
  *(undefined4 **)(param_1 + 0x170) = puVar2;
  
  // [7]
  puVar2 = (undefined4 *)((uVar4 >> 0x10) * 0x10 + in_t8);
  uVar5 = puVar2[1];
  *(undefined4 *)(param_1 + 0x17c) = *puVar2;
  *(undefined4 *)(param_1 + 0x180) = uVar5;
  *(undefined4 **)(param_1 + 0x184) = puVar2;
  
  // [8]
  puVar2 = (undefined4 *)((uint)uVar1 * 0x10 + in_t8);
  uVar5 = puVar2[1];
  *(undefined4 *)(param_1 + 400) = *puVar2;
  *(undefined4 *)(param_1 + 0x194) = uVar5;
  *(undefined4 **)(param_1 + 0x198) = puVar2;
  return;
}


// part of triangle collision in the function below
// param_1 - 1f800154,
// other parameters are the vertices
undefined4 FUN_8001f928(undefined4 *param_1,undefined4 *param_2,undefined4 *param_3,undefined4 *param_4)

{
  short sVar1;
  undefined4 *puVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;

  puVar2 = param_3;
  if (*(short *)((int)param_1 + 6) == 3) {
    iVar3 = (int)*(short *)(param_2 + 1);
    iVar5 = *(short *)(param_3 + 1) - iVar3;
    iVar9 = *(short *)(param_4 + 1) - iVar3;
    iVar3 = *(short *)(param_1 + 5) - iVar3;
    iVar4 = iVar5;
    if (iVar5 < 0) {
      iVar4 = -iVar5;
    }
    iVar10 = iVar9;
    if (iVar9 < 0) {
      iVar10 = -iVar9;
    }
    iVar6 = iVar5;
    if (iVar4 - iVar10 < 0) {
      puVar2 = param_4;
      param_4 = param_3;
      iVar6 = iVar9;
      iVar9 = iVar5;
    }
    iVar4 = (int)*(short *)param_2;
    iVar5 = *(short *)puVar2 - iVar4;
    iVar10 = *(short *)param_4 - iVar4;
    iVar4 = *(short *)(param_1 + 4) - iVar4;
  }
  else {
    iVar3 = (int)*(short *)param_2;
    if (*(short *)((int)param_1 + 6) == 1) {
      iVar5 = *(short *)param_3 - iVar3;
      iVar9 = *(short *)param_4 - iVar3;
      iVar3 = *(short *)(param_1 + 4) - iVar3;
      iVar4 = iVar5;
      if (iVar5 < 0) {
        iVar4 = -iVar5;
      }
      iVar10 = iVar9;
      if (iVar9 < 0) {
        iVar10 = -iVar9;
      }
      iVar6 = iVar5;
      if (iVar4 - iVar10 < 0) {
        puVar2 = param_4;
        param_4 = param_3;
        iVar6 = iVar9;
        iVar9 = iVar5;
      }
      iVar4 = (int)*(short *)((int)param_2 + 2);
      iVar5 = *(short *)((int)puVar2 + 2) - iVar4;
      iVar10 = *(short *)((int)param_4 + 2) - iVar4;
      iVar4 = *(short *)((int)param_1 + 0x12) - iVar4;
    }
    else {
      iVar3 = (int)*(short *)((int)param_2 + 2);
      iVar5 = *(short *)((int)param_3 + 2) - iVar3;
      iVar9 = *(short *)((int)param_4 + 2) - iVar3;
      iVar3 = *(short *)((int)param_1 + 0x12) - iVar3;
      iVar4 = iVar5;
      if (iVar5 < 0) {
        iVar4 = -iVar5;
      }
      iVar10 = iVar9;
      if (iVar9 < 0) {
        iVar10 = -iVar9;
      }
      iVar6 = iVar5;
      if (iVar4 - iVar10 < 0) {
        puVar2 = param_4;
        param_4 = param_3;
        iVar6 = iVar9;
        iVar9 = iVar5;
      }
      iVar4 = (int)*(short *)(param_2 + 1);
      iVar5 = *(short *)(puVar2 + 1) - iVar4;
      iVar10 = *(short *)(param_4 + 1) - iVar4;
      iVar4 = *(short *)(param_1 + 5) - iVar4;
    }
  }
  iVar7 = -0x1000;
  iVar8 = -0x1000;
  if (iVar6 == 0) {
    iVar7 = -0x1000;
    if (iVar9 == 0) {
      return 0xffffffff;
    }
    iVar8 = (iVar3 << 0xc) / iVar9;
    if (iVar5 != 0) {
      iVar7 = (iVar4 * 0x1000 - iVar8 * iVar10) / iVar5;
    }
  }
  else {
    iVar10 = iVar10 * iVar6 - iVar9 * iVar5 >> 6;
    if ((iVar10 != 0) && (iVar8 = ((iVar4 * iVar6 - iVar3 * iVar5) * 0x40) / iVar10, iVar6 != 0)) {
      iVar7 = (iVar3 * 0x1000 - iVar8 * iVar9) / iVar6;
    }
  }
  if ((iVar7 == -0x1000) || (iVar7 == -0x1000)) {
    return 0xffffffff;
  }
  if (iVar7 < 0) {
    if (iVar8 < 0) {
      sVar1 = *(short *)(param_2 + 1);
      *param_1 = *param_2;
      *(short *)(param_1 + 1) = sVar1;
      return 0;
    }
    if (-1 < iVar7 + iVar8 + -0x1000) {
      sVar1 = *(short *)(param_4 + 1);
      *param_1 = *param_4;
      *(short *)(param_1 + 1) = sVar1;
      return 4;
    }
    FUN_8001ede4(param_1,param_2,param_4,param_1 + 4);
    return 5;
  }
  iVar3 = iVar7 + iVar8 + -0x1000;
  if (-1 < iVar8) {
    if (iVar3 < 1) {
      *param_1 = param_1[4];
      *(undefined2 *)(param_1 + 1) = *(undefined2 *)(param_1 + 5);
      return 6;
    }
    FUN_8001ede4(param_1,puVar2,param_4,param_1 + 4);
    return 3;
  }
  if (-1 < iVar3) {
    sVar1 = *(short *)(puVar2 + 1);
    *param_1 = *puVar2;
    *(short *)(param_1 + 1) = sVar1;
    return 2;
  }
  FUN_8001ede4();
  return 1;
}

// WARNING: Instruction at (ram,0x8001fefc) overlaps instruction at (ram,0x8001fef8)
//

// COLL_TestTriangle_FindClosest
void FUN_8001fc40(undefined4 *param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  short sVar1;
  ushort uVar2;
  undefined4 in_zero;
  undefined4 in_at;
  int iVar3;
  uint uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;

  sVar1 = *(short *)(param_2 + 6);
  uVar5 = *(undefined4 *)(param_2 + 0xc);
  uVar6 = *(undefined4 *)(param_2 + 0x10);
  *(short *)(param_1 + 0xf) = *(short *)(param_1 + 0xf) + 1;
  *(short *)((int)param_1 + 0x52) = sVar1;
  param_1[0x15] = uVar5;
  param_1[0x16] = uVar6;
  iVar9 = param_1[0x19];

  // If collision on this quadblock is not scriptable
  // (TigerTempleTeeth, AdvHubDoors)
  if ((*(ushort *)(iVar9 + 0x12) & 0x400) == 0)
  {
    uVar5 = *param_1;
  }

  // if it is scriptable
  else
  {
    uVar5 = *param_1;

	// if the requirement is met to open the door
	if (((int)*(char *)(iVar9 + 0x38) & DAT_8008d728) != 0)
	{
	  // dont check for collision
      return;
    }
  }

  gte_ldR11R12(uVar5);
  gte_ldR13R21(param_1[4] << 0x10 | (uint)*(ushort *)(param_1 + 1));
  gte_ldR22R23((uint)param_1[4] >> 0x10 | (uint)*(ushort *)(param_1 + 5) << 0x10);
  gte_ldVXY0(param_1 + 0x15);
  gte_ldVZ0(param_1 + 0x16);
  gte_rtv0_b();
  iVar7 = gte_stMAC1();
  iVar8 = gte_stMAC2();

  iVar7 = iVar7 + (int)*(short *)((int)param_1 + 0x5a) * -2;
  iVar8 = iVar8 + (int)*(short *)((int)param_1 + 0x5a) * -2;
  
  if (iVar8 < 0) 
  {
    // quadblock->flags & TriggerScript (like turbo pad),
	
	// if NOT TriggerScript
	if ((*(ushort *)(iVar9 + 0x12) & 0x40) == 0) 
	{
      sVar1 = *(short *)(param_1 + 0x15);
      if (-1 < *(int *)(iVar9 + 0x14)) goto LAB_8001fd38;
    }
    
	// if TriggerScript
	else 
	{
      sVar1 = *(short *)(param_1 + 0x15);
    }
	
    iVar7 = -iVar7;
    iVar8 = -iVar8;
    *(short *)(param_1 + 0x15) = -sVar1;
    *(short *)((int)param_1 + 0x56) = -*(short *)((int)param_1 + 0x56);
    *(short *)(param_1 + 0x16) = -*(short *)(param_1 + 0x16);
    *(short *)((int)param_1 + 0x5a) = -*(short *)((int)param_1 + 0x5a);
  }
LAB_8001fd38:
  uVar2 = *(ushort *)(iVar9 + 0x12);
  *(short *)(param_1 + 0xf) = *(short *)(param_1 + 0xf) + 1;
  if (-1 < iVar7 - *(short *)((int)param_1 + 6)) {
    return;
  }
  if (iVar8 < 0) {
    return;
  }
  if (((uVar2 & 0x40) == 0) && (0 < iVar7 - iVar8)) {
    return;
  }
  if (-1 < iVar7) {
    gte_ldIR0(iVar7);
    gte_ldsv_((int)*(short *)(param_1 + 0x15),(int)*(short *)((int)param_1 + 0x56),
              (int)*(short *)(param_1 + 0x16));
  }
  else {
    gte_ldIR1((int)*(short *)param_1 - (int)*(short *)(param_1 + 4));
    gte_ldIR2((int)*(short *)((int)param_1 + 2) - (int)*(short *)((int)param_1 + 0x12));
    gte_ldIR3((int)*(short *)(param_1 + 1) - (int)*(short *)(param_1 + 5));
    gte_ldIR0((iVar7 * -0x1000) / (iVar8 - iVar7));
  }

  gte_gpf12_b();
  uVar5 = gte_stMAC1();
  uVar6 = gte_stMAC2();

  *(short *)(param_1 + 0x17) = *(short *)param_1 - (short)uVar5;

  uVar5 = gte_stMAC3();

  *(short *)((int)param_1 + 0x5e) = *(short *)((int)param_1 + 2) - (short)uVar6;
  *(short *)(param_1 + 0x18) = *(short *)(param_1 + 1) - (short)uVar5;
  param_1[0x36] = param_2;
  param_1[0x37] = param_3;
  param_1[0x38] = param_4;
  
  // always passes 1f800154
  iVar9 = FUN_8001f928(param_1 + 0x13,param_2,param_3,param_4);
  
  if (iVar9 < 0) {
    return;
  }
  if (-1 < iVar7) {
    *(short *)(param_1 + 0x39) = *(short *)param_1 - *(short *)(param_1 + 0x13);
    *(short *)((int)param_1 + 0xe6) = *(short *)((int)param_1 + 2) - *(short *)((int)param_1 + 0x4e)
    ;
    *(short *)(param_1 + 0x3a) = *(short *)(param_1 + 1) - *(short *)(param_1 + 0x14);
  }
  else {
    *(short *)(param_1 + 0x39) = *(short *)(param_1 + 0x17) - *(short *)(param_1 + 0x13);
    *(short *)((int)param_1 + 0xe6) =
         *(short *)((int)param_1 + 0x5e) - *(short *)((int)param_1 + 0x4e);
    *(short *)(param_1 + 0x3a) = *(short *)(param_1 + 0x18) - *(short *)(param_1 + 0x14);
  }


  gte_ldR11R12(param_1[0x39]);
  gte_ldR13R21((int)*(short *)(param_1 + 0x3a));
  gte_ldVXY0(param_1 + 0x39);
  gte_ldVZ0(param_1 + 0x3a);
  gte_mvmva(0,0,0,3,0);
  iVar3 = gte_stMAC1();

  // confirmed quadblock,
  // look at t9 on addr 8001fed4
  iVar10 = param_1[0x19];
  
  // quadblock -> flags
  uVar2 = *(ushort *)(iVar10 + 0x12);
  
  if (0 < iVar3 - param_1[2]) {
    return;
  }
  
  // if not triggerScript
  if ((uVar2 & 0x40) == 0) {
LAB_8001ff14:
    iVar8 = iVar8 - iVar7;
    if (iVar8 != 0) {
      iVar8 = 0x1000 - ((*(short *)((int)param_1 + 6) - iVar7) * 0x1000) / iVar8;
    }
	
	// if distance from player to triangle, is less than shortest distance
    if (iVar8 - param_1[0x21] < 0) 
	{
	  // if not out of bounds
      if ((uVar2 & 0x10) == 0) 
	  {
		// set new shortest distance
        param_1[0x21] = iVar8;
		
        uVar5 = *(undefined4 *)(param_1[0x37] + 8);
        uVar6 = *(undefined4 *)(param_1[0x38] + 8);
        param_1[0x33] = *(undefined4 *)(param_1[0x36] + 8);
        param_1[0x34] = uVar5;
        param_1[0x35] = uVar6;
        param_1[0x1a] = param_1[0x13];
        param_1[0x1b] = param_1[0x14];
        param_1[0x1c] = param_1[0x15];
        param_1[0x1d] = param_1[0x16];
        param_1[0x1e] = param_1[0x17];
        param_1[0x1f] = param_1[0x18];
        param_1[0x20] = iVar10;
		
		// triangle ID (0-9)
		// 0x1f800187
        *(undefined *)((int)param_1 + 0x7f) = *(undefined *)((int)param_1 + 99);
		
        *(char *)((int)param_1 + 0x7e) = (char)iVar9;
        if (iVar8 < 1) {
          param_1[7] = param_1[4];
          *(short *)(param_1 + 8) = *(short *)(param_1 + 5);
        }
        else {
          gte_ldIR0(iVar8);
          gte_ldIR1((int)*(short *)param_1 - (int)*(short *)(param_1 + 4));
          gte_ldIR2((int)*(short *)((int)param_1 + 2) - (int)*(short *)((int)param_1 + 0x12));
          gte_ldIR3((int)*(short *)(param_1 + 1) - (int)*(short *)(param_1 + 5));
          gte_gpf12_b();
          uVar5 = gte_stMAC1();
          uVar6 = gte_stMAC2();

          *(short *)(param_1 + 7) = *(short *)(param_1 + 4) + (short)uVar5;

		  uVar5 = gte_stMAC3();

          *(short *)((int)param_1 + 0x1e) = *(short *)((int)param_1 + 0x12) + (short)uVar6;
          *(short *)(param_1 + 8) = *(short *)(param_1 + 5) + (short)uVar5;
        }
		
		// 1F800146
        *(short *)((int)param_1 + 0x3e) = *(short *)((int)param_1 + 0x3e) + 1;
      }
      else 
	  {
		// if killplane
        if ((uVar2 & 0x200) != 0) {
          param_1[0x69] = param_1[0x69] | 0x4000;
        }
      }
    }
  }
  else {
    if (iVar7 < 0) {
      uVar4 = param_1[0x69];
    }
    else {
      uVar4 = param_1[0x69];
      if (-1 < (iVar7 - *(short *)((int)param_1 + 6) | iVar8 - *(short *)((int)param_1 + 6)))
      goto LAB_8001ff14;
    }
    param_1[0x69] = uVar4 | *(byte *)(iVar10 + 0x38);
  }
  return;
}


// COLL_PerQuadblock_CheckTriangles_NearPlayer
// param_1 - quadblock
// param_2 - 1f800108
void FUN_80020064(int param_1,int param_2)

{
  uint uVar1;

  *(int *)(param_2 + 100) = param_1;

  if (
		(
			(
				// quadblock flags
				((*(uint *)(param_2 + 0x24) & (int)*(short *)(param_1 + 0x12)) != 0) &&

				// quadblock flags
				((*(uint *)(param_2 + 0x28) & (int)*(short *)(param_1 + 0x12)) == 0)
			) &&

			// min[y] less than [???]
			((*(int *)(param_1 + 0x2c) >> 0x10) - (int)*(short *)(param_2 + 0x38) < 1)
		) &&

		(
			(
				(
					// min[x] less than [???]
					(int)(short)*(int *)(param_1 + 0x2c) - (int)*(short *)(param_2 + 0x36) < 1 &&

					// max[x] more than [???]
					((int)*(short *)(param_2 + 0x30) - (*(int *)(param_1 + 0x30) >> 0x10) < 1)
				) &&

				(
					(
						// min[z] less than [???]
						(int)(short)*(int *)(param_1 + 0x30) - (int)*(short *)(param_2 + 0x3a) < 1 &&

						// min[z] more than [???]
						((int)*(short *)(param_2 + 0x34) - (*(int *)(param_1 + 0x34) >> 0x10) < 1)
					)
				)
			)
		)
	  )
  {
	// min[y] more than [???]
    if ((int)*(short *)(param_2 + 0x32) - (int)(short)*(int *)(param_1 + 0x34) < 1)
	{
	  // if 3P or 4P mode,
	  // then use low-LOD quadblock collision (two triangles)
      if ((*(ushort *)(param_2 + 0x22) & 2) == 0) 
	  {
		// COLL_TestQuadblock_TwoTris
        FUN_8001f67c(param_2,param_1);
		
		// call FUN_8001fc40 two times, one per triangle
		
        *(undefined *)(param_2 + 99) = 0;
        FUN_8001fc40(0x1f800108, 0x1f8001f8, 0x1f80020c, 0x1f800220); // 0, 1, 2
        uVar1 = *(uint *)(param_1 + 4);
        *(undefined *)(param_2 + 99) = 1;
        if (uVar1 >> 0x10 != (uVar1 & 0xffff)) {
          FUN_8001fc40(0x1f800108, 0x1f80020c, 0x1f800234, 0x1f800220); // 1, 3, 2
        }
      }
      else {
        if ((*(ushort *)(param_2 + 0x22) & 8) == 0) 
		{
		  // COLL_TestQuadblock_EightTris
          FUN_8001f6f0(param_2,param_1);
        }
		
		// call FUN_8001fc40 eight times, one per triangle
		
        *(undefined *)(param_2 + 99) = 2;
        FUN_8001fc40(0x1f800108, 0x1f8001f8, 0x1f800248, 0x1f80025c); // 0, 4, 5
        *(undefined *)(param_2 + 99) = 3;                             
        FUN_8001fc40(0x1f800108, 0x1f800248, 0x1f800270, 0x1f80025c); // 4, 6, 5
        *(undefined *)(param_2 + 99) = 4;                             
        FUN_8001fc40(0x1f800108, 0x1f800270, 0x1f800248, 0x1f80020c); // 6, 4, 1
        *(undefined *)(param_2 + 99) = 5;
		FUN_8001fc40(0x1f800108, 0x1f80025c, 0x1f800270, 0x1f800220); // 5, 6, 2
        uVar1 = *(uint *)(param_1 + 4);
        *(undefined *)(param_2 + 99) = 6;
        if (uVar1 >> 0x10 != (uVar1 & 0xffff)) {
          FUN_8001fc40(0x1f800108, 0x1f800298, 0x1f800270, 0x1f800284); // 8, 6, 7
          *(undefined *)(param_2 + 99) = 7;                             
          FUN_8001fc40(0x1f800108, 0x1f800284, 0x1f800234, 0x1f800298); // 7, 3, 8
          *(undefined *)(param_2 + 99) = 8;                             
          FUN_8001fc40(0x1f800108, 0x1f80020c, 0x1f800284, 0x1f800270); // 1, 7, 6
          *(undefined *)(param_2 + 99) = 9;
          FUN_8001fc40(0x1f800108, 0x1f800220, 0x1f800270, 0x1f800298); // 2, 6, 8
          return;
        }
      }
    }
  }
  return;
}


// COLL_PerBspLeaf_CheckQuadblocks_NearPlayer
// param_1 is bsp node
// param_2 is 0x1f800108
void FUN_800202a8(uint *param_1,int param_2)

{
  uint uVar1;
  uint uVar2;

  // if bsp flag is water
  if ((*param_1 & 2) != 0) {
    *(uint *)(param_2 + 0x1a4) = *(uint *)(param_2 + 0x1a4) | 0x8000;
  }

  // number of quadblocks
  uVar1 = param_1[6];

  // pointer to quadblocks
  uVar2 = param_1[7];

  // loop through all quadblocks
  do 
  {
	// COLL_PerQuadblock_CheckTriangles_NearPlayer
    FUN_80020064(uVar2,param_2);

	// reduce count
    uVar1 = uVar1 - 1;

	// next quadblock
    uVar2 = uVar2 + 0x5c;

  } while (0 < (int)uVar1);

  if ((*(ushort *)(param_2 + 0x22) & 1) != 0)
  {
	// PerBspLeaf_CheckInstances
    FUN_8001d610(param_1,param_2);
  }
  return;
}


// COLL_TestTriangle_WithClosest
// param_1 = ptrQuadblock
// param_2 = triangleID
// param_3 = 0x1F800108
void FUN_80020334(int param_1,int param_2,int param_3)

{
  ushort uVar1;
  undefined2 uVar2;
  int iVar3;
  int *piVar4;
  int iVar5;

  uVar1 = *(ushort *)(param_3 + 0x22);

  // if no quadblock given,
  // first call before this function gets 15 more calls
  if (param_1 == 0)
  {
	// if param_1 is rigged nullptr,
	// driver gets stuck, but doesn't bounce

    *(ushort *)(param_3 + 0x22) = uVar1 & 0xffdf;
	
	// 1f800116 (no scrub)
    *(undefined2 *)(param_3 + 0xe) = 0;
	
    *(undefined4 *)(param_3 + 0x2c0) = 0;
	
    return;
  }

  // if this function is being called from the 
  // loop of 15 calls, from COLL_StartSearch_Player

  // since start of COLL_StartSearch_Player, check all existing
  // records of quadblock and triangle, so far
  iVar3 = *(int *)(param_3 + 0x2c0) + -1;
  
  if (-1 < iVar3) {
    
	// array of 0xC-byte struct
	iVar5 = iVar3 * 0xc + 0x20c;
    
	// if any are found with less than 4 frames,
	// then trigger scrub effect with 1f800116
	do 
	{
      piVar4 = (int *)(param_3 + iVar5);
      
	  // if quadblock and triangleID match,
	  // meaning we've already found collision with this triangle on this frame
	  if ((*piVar4 == param_1) && (piVar4[1] == param_2)) 
	  {
		// frame timer?
        iVar3 = piVar4[2];
        uVar2 = (undefined2)iVar3;
        
		// if collision is found less than 4 frames
		if (iVar3 < 0x401) 
		{
		  // increment
          uVar2 = (undefined2)(iVar3 + 0x100);
          piVar4[2] = iVar3 + 0x100;
        }
        
		*(ushort *)(param_3 + 0x22) = uVar1 | 0x20;
		
		// 1f800116
        *(undefined2 *)(param_3 + 0xe) = uVar2;
        
		return;
      }
      iVar3 = iVar3 + -1;
      iVar5 = iVar5 + -0xc;
    } while (-1 < iVar3);
  }
  
  // if collision was not found yet this frame,
  // with this quadblock and triangle
  
  // set a slot for a new record
  piVar4 = (int *)(param_3 + *(int *)(param_3 + 0x2c0) * 0xc + 0x20c);
  
  // record quadblock, triangle, and set counter to zero
  *piVar4 = param_1;
  piVar4[1] = param_2;
  piVar4[2] = 0;

  // similar to if-statement body
  *(ushort *)(param_3 + 0x22) = uVar1 & 0xffdf;
  
  // 1f800116 (no scrub)
  *(undefined2 *)(param_3 + 0xe) = 0;
  
  // write to next slot, next time a new triangle is found
  *(int *)(param_3 + 0x2c0) = *(int *)(param_3 + 0x2c0) + 1;

  return;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address

// COLL_StartSearch_NearPlayer
// param_1 = driver thread
// param_2 = driver ptr
void FUN_80020410(undefined4 param_1,int param_2)
{
  ushort uVar1;
  undefined2 uVar2;
  short sVar3;
  short sVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  undefined4 uVar8;
  short sVar9;
  short sVar10;
  int iVar11;
  undefined4 uVar12;
  int iVar13;
  int iVar14;

  // hitRadius and hitRadiusSquared
  DAT_1f80010e = 0x19;
  _DAT_1f800110 = 0x271;
  
  // hitRadius and hitRadiusSquared
  DAT_1f80011c._2_2_ = 0x19;
  DAT_1f800120 = 0x271;

  // pointer to LEV
  DAT_1f800134 = **(undefined4 **)(PTR_DAT_8008d2ac + 0x160);

  // ground and wall quadblock flags
  DAT_1f80012c = 0x3000;

  DAT_1f800130 = 0;

  // low-LOD collision (2 triangles)
  DAT_1f80012a = 1;

  // if numPlyrCurrGame is less than 3
  if ((byte)PTR_DAT_8008d2ac[0x1ca8] < 3)
  {
	// high-LOD collision (8 triangles)
    DAT_1f80012a = 3;
  }

  iVar13 = 0x1000;
  DAT_1f8001cc = 0;
  DAT_1f800114 = 0x18;
  DAT_1f8002ac = 0;
  
  // COLL_TestTriangle_WithClosest
  // quadblock, triangleID, search data
  FUN_80020334(0,0,&DAT_1f800108);
  
  // loop executes 0xF times
  iVar14 = 0xf;
  do 
  {
    // Calculate velocity in X, Y, and Z components, with driver->velocityXYZ
    iVar5 = (*(int *)(param_2 + 0x88) * *(int *)(PTR_DAT_8008d2ac + 0x1d04) >> 5) * iVar13 >> 0xc;
	iVar6 = (*(int *)(param_2 + 0x8c) * *(int *)(PTR_DAT_8008d2ac + 0x1d04) >> 5) * iVar13 >> 0xc;
    iVar7 = (*(int *)(param_2 + 0x90) * *(int *)(PTR_DAT_8008d2ac + 0x1d04) >> 5) * iVar13 >> 0xc;

    DAT_1f800146 = 0;
    DAT_1f800144 = 0;
    DAT_1f80014a = 0;
    DAT_1f800148 = 0;
    DAT_1f80018c = 0x1000;

	// kartCenter = vec3_originToCenter + driverPos (origin of model is bottom-center)
	sVar9 = *(short *)(param_2 + 0x94) + (short)((uint)*(undefined4 *)(param_2 + 0x2d4) >> 8);
    sVar10 = *(short *)(param_2 + 0x98) + (short)((uint)*(undefined4 *)(param_2 + 0x2d8) >> 8);
    DAT_1f800118 = CONCAT22(sVar10,sVar9);
    DAT_1f80011c._0_2_ = *(short *)(param_2 + 0x9c) + (short)((uint)*(undefined4 *)(param_2 + 0x2dc) >> 8);
	
	// kartCenter + velocity
    sVar3 = *(short *)(param_2 + 0x94) + (short)((uint)(*(int *)(param_2 + 0x2d4) + iVar5) >> 8);
    sVar4 = *(short *)(param_2 + 0x98) + (short)((uint)(*(int *)(param_2 + 0x2d8) + iVar6) >> 8);
    _DAT_1f800108 = CONCAT22(sVar4,sVar3);
    iVar11 = (uint)*(ushort *)(param_2 + 0x9c) + (*(int *)(param_2 + 0x2dc) + iVar7 >> 8);
    DAT_1f80010c = (short)iVar11;
	
    if (
			// if not moving in X or Y
			(_DAT_1f800108 == DAT_1f800118) &&
			(
				uVar1 = DAT_1f80012a | 1,

				// if not moving in Z
				iVar11 * 0x10000 == (uint)(ushort)DAT_1f80011c << 0x10
			)
		) 
	{
		// dont check for quadblock collision
		break;
	}
	
	// stretch hitbox to the edges of two positions,
	//	1: kartCenter
	//	2: kartCenter + velocity
	   
	// hitbox minX
    DAT_1f800138 = (short)((int)sVar9 - (int)DAT_1f80011c._2_2_);
    if ((int)sVar3 - (int)DAT_1f80010e < (int)sVar9 - (int)DAT_1f80011c._2_2_) {
      DAT_1f800138 = (short)((int)sVar3 - (int)DAT_1f80010e);
    }
    
	// hitbox minY
	DAT_1f80013a = (short)((int)sVar10 - (int)DAT_1f80011c._2_2_);
    if ((int)sVar4 - (int)DAT_1f80010e < (int)sVar10 - (int)DAT_1f80011c._2_2_) {
      DAT_1f80013a = (short)((int)sVar4 - (int)DAT_1f80010e);
    }
	
	// hitbox minZ
    DAT_1f80013c = (short)((int)(short)(ushort)DAT_1f80011c - (int)DAT_1f80011c._2_2_);
    if ((int)DAT_1f80010c - (int)DAT_1f80010e <
        (int)(short)(ushort)DAT_1f80011c - (int)DAT_1f80011c._2_2_) {
      DAT_1f80013c = (short)((int)DAT_1f80010c - (int)DAT_1f80010e);
    }
	
	// hitbox maxX
    DAT_1f80013e = (short)((int)sVar9 + (int)DAT_1f80011c._2_2_);
    if ((int)sVar9 + (int)DAT_1f80011c._2_2_ < (int)sVar3 + (int)DAT_1f80010e) {
      DAT_1f80013e = (short)((int)sVar3 + (int)DAT_1f80010e);
    }
	
	// hitbox maxY
    DAT_1f800140 = (short)((int)sVar10 + (int)DAT_1f80011c._2_2_);
    if ((int)sVar10 + (int)DAT_1f80011c._2_2_ < (int)sVar4 + (int)DAT_1f80010e) {
      DAT_1f800140 = (short)((int)sVar4 + (int)DAT_1f80010e);
    }
	
	// hitbox maxZ
    DAT_1f800142 = (short)((int)(short)(ushort)DAT_1f80011c + (int)DAT_1f80011c._2_2_);
    if ((int)(short)(ushort)DAT_1f80011c + (int)DAT_1f80011c._2_2_ <
        (int)DAT_1f80010c + (int)DAT_1f80010e) {
      DAT_1f800142 = (short)((int)DAT_1f80010c + (int)DAT_1f80010e);
    }
	
    DAT_1f80012a = DAT_1f80012a & 0xfff7 | 1;
    DAT_1f800124._0_2_ = sVar3;
    DAT_1f800124._2_2_ = sVar4;
    DAT_1f800128 = DAT_1f80010c;

    if (
		(
			// if LEV exists
			(*(int **)(PTR_DAT_8008d2ac + 0x160) != (int *)0x0) &&

			// if LEV mesh_info exists
			(iVar11 = **(int **)(PTR_DAT_8008d2ac + 0x160), iVar11 != 0)
		) &&

		// if mesh_info->bsp exists
		(iVar11 = *(int *)(iVar11 + 0x18), iVar11 != 0)
	   )
	{
	  // COLL_SearchTree_FindX, callback 
	  // COLL_PerBspLeaf_CheckQuadblocks_NearPlayer
      FUN_8001ebec(iVar11,&DAT_1f800138,FUN_800202a8,&DAT_1f800108);
    }

	// if collision was found in BSP
    if (DAT_1f800146 != 0)
	{
      *(ushort *)(param_2 + 0xaa) = *(ushort *)(param_2 + 0xaa) | 4;
    }

    if (0 < DAT_1f80018c) 
	{
      // increase position by velocity
      *(int *)(param_2 + 0x2d4) = *(int *)(param_2 + 0x2d4) + (iVar5 * DAT_1f80018c >> 0xc);
      *(int *)(param_2 + 0x2d8) = *(int *)(param_2 + 0x2d8) + (iVar6 * DAT_1f80018c >> 0xc);
      *(int *)(param_2 + 0x2dc) = *(int *)(param_2 + 0x2dc) + (iVar7 * DAT_1f80018c >> 0xc);
    }
	
    if (DAT_1f80014a == 0) 
	{
	  uVar1 = DAT_1f80012a;
      
	  // if quadblock was not found, quit
	  if (DAT_1f800146 == 0) break;

	  // if quadblock is a killplane
      if ((*(ushort *)(DAT_1f800188 + 0x12) & 0x200) != 0)
	  {
		// player needs to be mask grabbed
        *(ushort *)(param_2 + 0xaa) = *(ushort *)(param_2 + 0xaa) | 1;
      }

	  // COLL_TestTriangle_WithClosest
	  // quadblock, triangleID, search data
      FUN_80020334(DAT_1f800188,(uint)DAT_1f800187,&DAT_1f800108);

	  // get quadblock flag
	  uVar1 = *(ushort *)(DAT_1f800188 + 0x12);

	  // if quadblock is not ground
	  if ((uVar1 & 0x1000) == 0) 
	  {
		// NO SCRUB
        uVar12 = 6;
		
        // is not invisible
        if ((uVar1 & 1) == 0) 
		{
		  // SOLID
          uVar12 = 0;
        }
      }

	  // if quadblock is ground
	  else
	  {
        if (

			// compare to quadblock under driver
			(DAT_1f800188 != *(int *)(param_2 + 0x350)) &&

			// if quadblock is "kicker"??? even DCxDemo doesn't
			// fully know what this is right now
			((uVar1 & 8) != 0)
		   )
		{
		  // quadblock under driver
          *(undefined4 *)(param_2 + 0x350) = 0;
        }
        uVar8 = _DAT_1f800178;

		// set quadblock you are touching
        *(int *)(param_2 + 0xa0) = DAT_1f800188;

		*(undefined4 *)(param_2 + 0xa4) = uVar8;
        uVar8 = _DAT_1f800178;
        *(undefined2 *)(param_2 + 0xa8) = DAT_1f80017c;
        
		// ROAD
		uVar12 = 5;
        
		*(undefined4 *)(param_2 + 0x360) = uVar8;
        uVar2 = DAT_1f80017c;

		// driver is now on ground
        *(ushort *)(param_2 + 0xaa) = *(ushort *)(param_2 + 0xaa) | 8;

		*(undefined2 *)(param_2 + 0x364) = uVar2;
      }

	  // VehAfterColl_GetSurface
	  uVar12 = FUN_80057c44(uVar12);

      *(ushort *)(param_2 + 0xaa) = *(ushort *)(param_2 + 0xaa) | 2;
	  
	  // driver->spsHitPoint = sps->hitPoint
      uVar8 = DAT_1f800170;
      *(undefined4 *)(param_2 + 0xac) = uVar8;
      uVar8 = _DAT_1f800178;
      *(undefined2 *)(param_2 + 0xb0) = (undefined2)DAT_1f800174;
	  
	  // driver->spsNormalVec = sps->normalVec
      *(undefined4 *)(param_2 + 0xb4) = uVar8;
      *(undefined2 *)(param_2 + 0xb8) = DAT_1f80017c;

	  // COLL_Scrub
      iVar5 = FUN_80020c58(param_2,param_1,&DAT_1f800108,uVar12,param_2 + 0x88);

	  // if driver is "crashing" from COLL_Scrub
	  if (iVar5 == 2) {
        return;
      }
      
	  if (
			(0 < DAT_1f80018c) &&
			(
				iVar13 = iVar13 - (iVar13 * DAT_1f80018c >> 0xc), 
				uVar1 = DAT_1f80012a, 
				iVar13 < 100
			)
		 )
      break;
	  
      DAT_1f80012a = DAT_1f80012a | 8;
    }
    
	else 
	{
      DAT_1f80012a = DAT_1f80012a & 0xfff7;
      *(ushort *)(param_2 + 0xaa) = *(ushort *)(param_2 + 0xaa) & 0xfffd;
      iVar5 = 1;
      if ((*DAT_1f800150 & 0x80) == 0) {
        if (((*DAT_1f800150 & 0x10) != 0) && (iVar6 = *(int *)(DAT_1f800150 + 0x1c), iVar6 != 0)) 
		{
		  // instance->model->modelID
          sVar3 = *(short *)(*(int *)(iVar6 + 0x18) + 0x10);
          goto LAB_800209b0;
        }
      }
      else
	  {
        iVar7 = *(int *)(DAT_1f800150 + 0x1c);

		if (
				(
					// if InstDef is valid
					(iVar7 != 0) &&

					// InstDef->Instance
					(iVar6 = *(int *)(iVar7 + 0x2c), iVar6 != 0)
				) &&
				(
					// InstDef->modelID
					sVar3 = *(short *)(iVar7 + 0x3c),

					// Instance->flags are drawing to some degree
					(*(uint *)(iVar6 + 0x28) & 0xf) != 0
				)
			)
		{
LAB_800209b0:

		  // ThreadMeta for modelID
          iVar7 = FUN_8001d094((int)sVar3);

          if (
				// if it is not nullptr
				(iVar7 != 0) &&

				// If funcLevThreadsBirth is not nullptr
				(*(code **)(iVar7 + 8) != (code *)0x0)
			  )
		  {
			// execute funcLevThreadsBirth, make thread for this instance
			// upon collision with the instance, let it run thread->funcThCollide
            iVar5 = (**(code **)(iVar7 + 8))(iVar6,param_1,&DAT_1f800108);
          }
        }
      }
      if ((iVar5 == 2) || (DAT_1f800150[1] == 4)) 
	  {
        *(byte **)(&DAT_1f800190 + DAT_1f8001cc) = DAT_1f800150;
        DAT_1f8001cc = DAT_1f8001cc + 1;
      }
      else 
	  {
		// COLL_TestTriangle_WithClosest
		// quadblock, triangleID, search data
        FUN_80020334(DAT_1f800150,0,&DAT_1f800108);
        
		// exaggerate scrub effect?
		DAT_1f800116 = DAT_1f800116 + 0x200;
        
		iVar5 = 0;

		// VehAfterColl_GetSurface
        uVar8 = FUN_80057c44((uint)DAT_1f800150[1]);

        if ((DAT_1f800150[1] == 4) ||

			// COLL_Scrub
		   (iVar5 = FUN_80020c58(param_2,param_1,&DAT_1f800108,uVar8,param_2 + 0x88), iVar5 == 0)) {

		  *(byte **)(&DAT_1f800190 + DAT_1f8001cc) = DAT_1f800150;
          DAT_1f8001cc = DAT_1f8001cc + 1;
        }
		
		// if driver is "crashing" from COLL_Scrub
        if (iVar5 == 2) {
          return;
        }
      }
    }
    iVar14 = iVar14 + -1;
    uVar1 = DAT_1f80012a;
  } while (iVar14 != 0);

  DAT_1f80012a = uVar1;
  
  // driver->0xBC = scratchpad->0x1A4
  *(undefined4 *)(param_2 + 0xbc) = DAT_1f8002ac;
  return;
}

// COLL_Scrub
// "scrub" like rubbing, for sparks
// param_1 driver ptr
// param_2 driver thread
// param_3 scratchpad address 1f800108
// param_4 MetaDataScrub
undefined4 FUN_80020c58(int param_1,undefined4 param_2,int param_3,int param_4,int *param_5)

{
  short sVar1;
  bool bVar2;
  int iVar3;
  undefined4 uVar4;
  int iVar5;
  int iVar6;
  undefined4 in_t2;
  undefined4 in_t3;
  undefined4 uVar7;
  undefined4 uVar8;
  uint uVar9;
  uint uVar10;
  int iVar11;
  uint uVar12;
  int iVar13;
  int iVar14;
  int iVar15;
  ushort local_48;
  ushort local_46;
  ushort local_44;
  int local_30;

  local_48 = *(ushort *)(param_3 + 0x70);
  local_46 = *(ushort *)(param_3 + 0x72);
  local_44 = *(ushort *)(param_3 + 0x74);

  // offset 0x350 is quadblock underneath driver

  if (
		(
			((*(short *)(param_1 + 0x40a) != 0) && (*(short *)(param_3 + 0x3e) != 0)) &&

			// if quadblock is ground
			((*(ushort *)(*(int *)(param_3 + 0x80) + 0x12) & 0x1000) != 0)
		) &&
		(
			(
				*(char *)(param_3 + 0x7e) != '\x06' &&

				// if quadblock is not the quadblock under the driver
				(*(int *)(param_3 + 0x80) != *(int *)(param_1 + 0x350))
			)
		)
	 )
  {
    iVar3 = (int)*(short *)(param_1 + 0x38e);
    if (iVar3 < 0) {
      iVar3 = -iVar3;
    }
    if (iVar3 < 0x300) {
      iVar3 = (int)*(short *)(param_1 + 0x390);
      if (iVar3 < 0) {
        iVar3 = -iVar3;
      }
      if ((iVar3 < 0x300) && (*(short *)(param_1 + 0x39e) == 0)) 
	  {
		// driverPos - sps->hitPos
        uVar10 = (*(int *)(param_1 + 0x2d4) >> 8) - (int)*(short *)(param_3 + 0x68);
        uVar12 = (*(int *)(param_1 + 0x2dc) >> 8) - (int)*(short *)(param_3 + 0x6c);
        uVar9 = (*(int *)(param_1 + 0x2d8) >> 8) - (int)*(short *)(param_3 + 0x6a);
		
        if ((uVar10 | uVar9 | uVar12) != 0) {

          // iVar3 = sqrt(x2+y2+z2 << 0)
          iVar3 = FUN_80059070(uVar10 * uVar10 + uVar9 * uVar9 + uVar12 * uVar12,0);

          if (iVar3 == 0) {
            trap(0x1c00);
          }
          if ((iVar3 == -1) && (uVar10 * 0x1000 == -0x80000000)) {
            trap(0x1800);
          }
          if (iVar3 == 0) {
            trap(0x1c00);
          }
          if ((iVar3 == -1) && (uVar9 * 0x1000 == -0x80000000)) {
            trap(0x1800);
          }
          if (iVar3 == 0) {
            trap(0x1c00);
          }
          if ((iVar3 == -1) && (uVar12 * 0x1000 == -0x80000000)) {
            trap(0x1800);
          }
          local_48 = (ushort)((int)(uVar10 * 0x1000) / iVar3);
          local_46 = (ushort)((int)(uVar9 * 0x1000) / iVar3);
          local_44 = (ushort)((int)(uVar12 * 0x1000) / iVar3);
        }
      }
    }
  }

  iVar3 = (*param_5 >> 3) * (int)(short)local_48 + (param_5[1] >> 3) * (int)(short)local_46 +
          (param_5[2] >> 3) * (int)(short)local_44 >> 9;
  if (iVar3 < -0xa00) {
    //turn on 8th bit of Actions Flag set (means ?)
    *(uint *)(param_1 + 0x2c8) = *(uint *)(param_1 + 0x2c8) | 0x80;
  }
  
  // 1f800116
  iVar3 = iVar3 - *(short *)(param_3 + 0xe);
  
  uVar4 = 0;
  if (iVar3 < 0)
  {
	// scrubMeta->4
    uVar9 = *(uint *)(param_4 + 4);

	if ((uVar9 & 4) == 0)
	{
      //turn on 14th bit of Actions Flag set (means
      //racer is driving against a wall)
      *(uint *)(param_1 + 0x2c8) = *(uint *)(param_1 + 0x2c8) | 0x2000;
    }

	if ((uVar9 & 8) == 0)
	{
	  // reset reserves
      *(undefined2 *)(param_1 + 0x3e2) = 0;
      *(undefined2 *)(param_1 + 0x3de) = 0;
    }

	// scrubMeta->8
	iVar5 = *(int *)(param_4 + 8);

	// if just touched the wall for the first frame
	if (*(short *)(param_1 + 0x3fe) == 0)
	{
      bVar2 = 0x3e7ff < iVar5;
    }

	// if you've been touching the wall for several frames
	else
	{
      bVar2 = *(short *)(param_1 + 0x38a) < iVar5;
    }

	// just hit, (param_1 + 0x38a) >= iVar5;
	// or
	// already hit, 0x3e7ff >= iVar5;
	if (!bVar2)
	{
	  // if == 0xf0, emit wall sparks,
	  // millisecond timer since touching wall
      *(undefined2 *)(param_1 + 0x3fe) = 0xf0;

	  // driver scrubMeta
      *(undefined2 *)(param_1 + 0x38a) = (short)iVar5;
	  
	  // driver 0x384
	  // driver->posWallColl = sps->hitPos
      *(undefined4 *)(param_1 + 900) = *(undefined4 *)(param_3 + 0x68);
      *(undefined2 *)(param_1 + 0x388) = *(undefined2 *)(param_3 + 0x6c);
    }

	uVar4 = 0;
    if ((uVar9 & 1) != 0) {
      iVar15 = iVar3 * (short)local_46;
      local_30 = 0;
      uVar10 = iVar3 * (short)local_48 >> 0xc;
      iVar5 = iVar15 >> 0xc;
      iVar14 = iVar3 * (short)local_44 >> 0xc;

	  // scrubMeta -> 0xC
      if (*(int *)(param_4 + 0xc) != 0) {
        iVar15 = param_5[2] * param_5[2];
        local_30 = *param_5 * *param_5 + param_5[1] * param_5[1] + iVar15 >> 0xf;
      }
      iVar11 = *param_5;
      iVar13 = param_5[2];
      *param_5 = iVar11 - uVar10;
      param_5[2] = iVar13 - iVar14;
      param_5[1] = param_5[1] - iVar5;
	  
	  gte_ldVXY0(uVar10 & 0xffff | iVar5 << 0x10);
	  gte_ldVZ0(iVar14);
	  gte_llv0();
	  
	  // second paramter is never used
	  read_mt(iVar5,???,iVar14);
	  
      if ((((*(short *)(param_3 + 0x3e) != 0) && ((*(ushort *)(param_3 + 0x22) & 0x10) == 0)) &&
          ((*(uint *)(param_1 + 0x2cc) & 1) == 0)) &&
		  
		  // if quadblock is ground
         ((*(ushort *)(*(int *)(param_3 + 0x80) + 0x12) & 0x1000) != 0)) 
		 
	  {
		// gte_ldopv2
        setCopReg(2,in_t3,iVar13);
        setCopReg(2,iVar15,iVar11);
        setCopReg(2,in_t2,0);
		
		// gte_ldopv1SV
        setCopControlWord(2,0,(int)(short)local_48);
        setCopControlWord(2,0x1000,(int)(short)local_46);
        setCopControlWord(2,0x2000,(int)(short)local_44);

		// outer product
		gte_op12();
		
		uVar4 = gte_stR11R12();
        uVar7 = gte_stR22R23();
        uVar8 = gte_stR33();
        gte_ldsv_(uVar4,uVar7,uVar8);
		
		read_mt(uVar4,uVar7,uVar8);
		gte_ldR11R12(uVar4);
		gte_ldR22R23(uVar7);
		gte_ldR33(uVar8);

		// outer product
		gte_op12();
		
		// gte_stlvnl
		iVar15 = getCopReg(2,0x19);
        iVar11 = getCopReg(2,0x1a);
        iVar13 = getCopReg(2,0x1b);

		// some other approximation of speed?

        // uVar10 = sqrt(x2+y2+z2 << 0x10)
        uVar10 = FUN_80059070(iVar15 * iVar15 + iVar11 * iVar11 + iVar13 * iVar13,0x10);

        uVar10 = uVar10 >> 8;

		// speed approx
        iVar6 = (int)*(short *)(param_1 + 0x38e);

		// if you are moving
        if ((uVar10 != 0) && (0 < iVar6)) {
          *(ushort *)(param_3 + 0x22) = *(ushort *)(param_3 + 0x22) | 0x10;
          if (uVar10 == 0) {
            trap(0x1c00);
          }
          if ((uVar10 == 0xffffffff) && (iVar15 * iVar6 == -0x80000000)) {
            trap(0x1800);
          }
          *param_5 = (iVar15 * iVar6) / (int)uVar10;
          if (uVar10 == 0) {
            trap(0x1c00);
          }
          if ((uVar10 == 0xffffffff) && (iVar11 * iVar6 == -0x80000000)) {
            trap(0x1800);
          }
          param_5[1] = (iVar11 * iVar6) / (int)uVar10;
          if (uVar10 == 0) {
            trap(0x1c00);
          }
          if ((uVar10 == 0xffffffff) && (iVar13 * iVar6 == -0x80000000)) {
            trap(0x1800);
          }
          param_5[2] = (iVar13 * iVar6) / (int)uVar10;
          *param_5 = *param_5 - ((int)((uint)local_48 << 0x10) >> 0x11);
          param_5[1] = param_5[1] - ((int)((uint)local_46 << 0x10) >> 0x11);
          param_5[2] = param_5[2] - ((int)((uint)local_44 << 0x10) >> 0x11);
        }
      }
      if ((((uVar9 & 2) != 0) && (iVar3 < -0x13ff)) &&
         (
			// get approximate speed
			iVar5 = iVar5 * iVar5 + iVar14 * iVar14,

			// if speed is fast
			0x1900000 < iVar5))
	  {
		// if you are not being mask grabbed
        if (*(char *)(param_1 + 0x376) != '\x05')
		{
		  // simpTurnState
          if (*(char *)(param_1 + 0x4b) < '\x01') {
            uVar4 = 0x1f;
          }
          else {
            uVar4 = 0x2f;
          }

		  // GAMEPAD_JogCon1
          FUN_800263a0(param_1,uVar4,0x60);
        }

		// scrubMeta -> 0xC
        uVar9 = *(uint *)(param_4 + 0xc);

        if (uVar9 != 0)
		{
		  // approximate trigonometry
          iVar15 = *(int *)(&DAT_800845a0 + (uVar9 & 0x3ff) * 4);

		  if ((uVar9 & 0x400) == 0) {
            iVar15 = iVar15 << 0x10;
          }
          iVar15 = iVar15 >> 0x10;
          if ((uVar9 & 0x800) != 0) {
            iVar15 = -iVar15;
          }
          if (iVar3 * iVar3 >> 0xf <= (local_30 * iVar15 >> 0xc) * iVar15 >> 0xc) {
            return 1;
          }
        }

        if (
				// if you are not being mask-grabbed
				(*(char *)(param_1 + 0x376) != '\x05') &&

				// if speed is high
				(0x1900000 < iVar5)
			)
		{
		  // max volume, no distort, L/R
          uVar4 = 0xff8080;

		  // if echo required
          if ((*(uint *)(param_1 + 0x2c8) & 0x10000) != 0)
		  {
			// add echo
            uVar4 = 0x1ff8080;
          }

		  // OtherFX_Play_LowLevel
		  // play crashing sound
          FUN_800284d0(6,1,uVar4);

		  // Make driver talk
          FUN_8002cbe8(6,(int)(short)(&DAT_80086e84)[*(byte *)(param_1 + 0x4a)],0x10);

		  // both gamepad vibration
		  FUN_80026440(param_1,8,0);
          FUN_800264c0(param_1,8,0x7f);

		  // if you are power-sliding
          if (*(char *)(param_1 + 0x376) == '\x02')
		  {
			// get change in rotation for this frame
            sVar1 = *(short *)(param_1 + 0x3c6);
            *(undefined2 *)(param_1 + 0x3c6) = 0;

			// change character rotation
            *(short *)(param_1 + 0x39a) = *(short *)(param_1 + 0x39a) + sVar1;

			// change camera rotation (so camera wont spin with character)
            *(short *)(param_1 + 0x2f2) = *(short *)(param_1 + 0x2f2) - sVar1;
          }

		  // set animation to 2
          *(undefined *)(*(int *)(param_1 + 0x1c) + 0x52) = 2;

		  // set frame to zero
          *(undefined2 *)(*(int *)(param_1 + 0x1c) + 0x54) = 0;

          *(undefined *)(param_1 + 0x4c) = 4;
          *(undefined *)(param_1 + 0x4d) = 0;

		  // VehPhysProc_SlamWall_Init
          FUN_80063bd4(param_2);
          return 2;
        }
      }
      uVar4 = 1;
    }
  }
  return uVar4;
}
