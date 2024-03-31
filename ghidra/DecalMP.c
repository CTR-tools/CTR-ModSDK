// param_1[0x95b] & 0x100
// something only in multiplayer?
// same as function below this one

// Draws model to texture lods used in 2p-4p modes
// disabling this leads to demo behaviour with normal lod system for every kart

// responsible for multiplayer pixel-level LOD, how does it work?
// disabling this removes pixelation, does NOT impact geometric LOD
void FUN_80023488(void)

{
  int iVar1;
  undefined2 *puVar2;
  int *piVar3;
  undefined *puVar4;
  int iVar5;
  int iVar6;
  undefined2 *puVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  undefined2 *puVar11;
  int iVar12;
  int iVar13;

  // loop counter
  iVar9 = 0;

  // ???
  puVar7 = (undefined2 *)(PTR_DAT_8008d2ac + 0x5a8);

  // pushBuffer
  puVar11 = (undefined2 *)(PTR_DAT_8008d2ac + 0x168);

  // if numPlyrCurrGame is not zero
  if (PTR_DAT_8008d2ac[0x1ca8] != '\0') 
  {
	// gGT->pushBuffer[i].cameraID
    // 0x270 = 0x168+0x108
	puVar4 = PTR_DAT_8008d2ac + 0x270;
	
    iVar10 = 0;

	// for(int iVar9 = 0; iVar9 < numPlyrCurrGame; iVar9++)
    do {

	  // another loop counter
      iVar5 = 0;

      iVar8 = 0;
      piVar3 = (int *)(puVar7 + 4);

	  // for(int iVar5 = 0; iVar5 < 8; iVar5++)
	  do
	  {
        if (0xb < iVar8) break;

		// get the pointer to the structue of each player
        iVar1 = *(int *)(PTR_DAT_8008d2ac + iVar5 * 4 + 0x24ec);

		// if pointer is valid
        if (iVar1 != 0)
		{
		  // get instance
          iVar6 = *(int *)(iVar1 + 0x1c);

		  // instance flags
          *(uint *)(iVar6 + 0x28) = *(uint *)(iVar6 + 0x28) | 0x300;

		  // if this driver in the loop of 8,
		  // is not the driver on your own screen
          if (iVar5 != iVar9)
		  {
            //if player was blasted (with items: bomb, missile, tnt, bubble, mask, warpball)
            if (*(char *)(iVar1 + 0x376) == '\x06') {
              *(undefined *)((int)piVar3 + -6) = 6;
            }
            else {
              if (*(char *)((int)piVar3 + -6) == '\x06') {
                *(undefined *)((int)piVar3 + -6) = 0;
				
				// 0x5A8 -> 0x0
                *puVar7 = 1000;
              }
            }
			
			// pushBuffer->0x108-0xE0
			// pushBuffer->0x28
			
			// copy matrix pushBuffer->0x28
			// to piVar3 (gGT->0x5a8 region)
            iVar1 = *(int *)(puVar4 + -0xdc);
            iVar12 = *(int *)(puVar4 + -0xd8);
            iVar13 = *(int *)(puVar4 + -0xd4);
            piVar3[0xe] = *(int *)(puVar4 + -0xe0);
            piVar3[0xf] = iVar1;
            piVar3[0x10] = iVar12;
            piVar3[0x11] = iVar13;
			
			// copy matrix pushBuffer->0x38 (second half of 0x28)
			// to piVar3 (gGT->0x5a8 region)
            iVar1 = *(int *)(puVar4 + -0xcc);
            iVar12 = *(int *)(puVar4 + -200);
            iVar13 = *(int *)(puVar4 + -0xc4);
            piVar3[0x12] = *(int *)(puVar4 + -0xd0);
            piVar3[0x13] = iVar1;
            piVar3[0x14] = iVar12;
            piVar3[0x15] = iVar13;

			// store pointer to pushBuffer
            *(undefined2 *)(piVar3 + 4) = *puVar11;

			*(undefined2 *)((int)piVar3 + 0x12) = *(undefined2 *)(puVar4 + -0x106);
            *(undefined2 *)(piVar3 + 5) = *(undefined2 *)(puVar4 + -0x104);
			
			// pushBuffer->0x108-0xEC
			// pushBuffer->rect.x
			// startX, startY, sizeX, sizeY
            *(undefined2 *)(piVar3 + 0xb) = *(undefined2 *)(puVar4 + -0xec);
            *(undefined2 *)((int)piVar3 + 0x2e) = *(undefined2 *)(puVar4 + -0xea);
            *(undefined2 *)(piVar3 + 0xc) = *(undefined2 *)(puVar4 + -0xe8);
            *(undefined2 *)((int)piVar3 + 0x32) = *(undefined2 *)(puVar4 + -0xe6);
			
			// pushBuffer->0x108-0x14
			// pushBuffer->ptrOT 
            piVar3[0x41] = *(int *)(puVar4 + -0x14);
			
            puVar2 = puVar7 + 0xc;
			
			// pushBuffer->0x108-0xF0
			// pushBuffer->distToScreenPREV
            piVar3[10] = *(int *)(puVar4 + -0xf0);
            
			// next region of gGT->0x5a8 (0x128 bytes) (0x94*2)
			puVar7 = puVar7 + 0x94;
			
			// cameraID (0x108)
            *(undefined *)(piVar3 + 0x46) = *puVar4;

			// instance 88*i + 0x74 = pushBuffer pointer
            *(undefined2 **)(iVar6 + iVar10 + 0x74) = puVar2;

			*piVar3 = iVar6;
			
			// next region of gGT->0x5a8 (0x128 bytes) (0x4a*4)
            piVar3 = piVar3 + 0x4a;
          }
        }

		// increment loop counter
        iVar5 = iVar5 + 1;
        iVar8 = iVar8 + 1;
      } while (iVar5 < 8);


	  // InstDrawPerPlayer
      iVar10 = iVar10 + 0x88;

	  // loop counter
      iVar9 = iVar9 + 1;

	  // PushBuffer
      puVar4 = puVar4 + 0x110;

	  // InstDrawPerPlayer
      puVar11 = puVar11 + 0x88;

	  // for(int iVar9 = 0; iVar9 < numPlyrCurrGame; iVar9++)
    } while (iVar9 < (int)(uint)(byte)PTR_DAT_8008d2ac[0x1ca8]);
  }
  return;
}

// param_1[0x95b] & 0x100
// something only in multiplayer?
// same as function below this one
void FUN_80023640(uint *param_1)

{
  char cVar1;
  short sVar2;
  int iVar3;
  int iVar4;
  undefined2 *puVar5;
  uint *puVar6;
  uint uVar7;

  // 0x5A8 (0x16a*4)
  puVar6 = param_1 + 0x16a;
  
  uVar7 = 0;
  
  // 0x5A8 -> 6
  puVar5 = (undefined2 *)((int)param_1 + 0x5ae);

  // loop 12 times, 3 opponents on 4 screens
  do
  {
	// if instance is nullptr
    if (*(int *)(puVar5 + 1) == 0) {
      return;
    }
	
	// offset 6 + (0x8d*2) = offset 0x120
    cVar1 = *(char *)(puVar5 + 0x8d);
	
	// (puVar5 + 1) = 0x5A8->(6+2) = Instance
	// Instance->InstDrawPerPlayer[cVar1]
    iVar4 = *(int *)(puVar5 + 1) + (int)cVar1 * 0x88 + 0x74;
    
	sVar2 = 1000;
	
	// instance 0xB8 flags
    if ((*(uint *)(iVar4 + 0x44) & 0x140) == 0x140) 
	{
      sVar2 = *(short *)puVar6;
      iVar3 = *(int *)(puVar5 + 0x87) >> 3;
      if (iVar3 < 2) {
        iVar3 = 2;
      }
      if (
			((int)sVar2 < 1000) &&
			(
				(
					((int)sVar2 <= iVar3 && (*(int *)(puVar5 + 7) == *(int *)(iVar4 + 100))) ||
          
					// if it is not this DecalMP's "turn" to update,
					// only one of the twelve are updated per frame
					(((param_1[0x73b] ^ uVar7) & 1) == 0)
				)
			)
		 ) 
	  {
		// instance 0xB8 flags 
		*(uint *)(iVar4 + 0x44) = *(uint *)(iVar4 + 0x44) | 0x80;
		
		// not updating
        *puVar5 = 0;
      }
	  
	  // if it is this DecalMP's "turn" to update,
	  // only one of the twelve are updated per frame
      else 
	  {
		// this one is being rendered
        *puVar5 = 1;
		
        if ((*(undefined4 **)(puVar5 + 0x83) != (undefined4 *)0x0) && (*(int *)(puVar5 + 0x85) != 0)
           )
		{
		  // 0x97*4 = 0x25c
		  // pointer to OTMem (25c-168=0xf4)
		  // 0x44 * 4 = 0x110 (cameraSize)

		  // save ptrOT
          **(undefined4 **)(puVar5 + 0x83) =
               *(undefined4 *)((param_1 + (int)cVar1 * 0x44)[0x97] + 0xffc);

		  // set new ptrOT
          *(uint *)((param_1 + (int)cVar1 * 0x44)[0x97] + 0xffc) =
               *(uint *)(puVar5 + 0x85) & 0xffffff;
        }
      }
      sVar2 = sVar2 + 1;
      if ((*param_1 & 0xf) == 0) goto LAB_80023764;
    }
    else {
LAB_80023764:
      *(short *)puVar6 = sVar2;
    }
	
	// loop count
    uVar7 = uVar7 + 1;
	
	// next InstDrawPerPlayer
    puVar5 = puVar5 + 0x94;
    puVar6 = puVar6 + 0x4a;

	// loop 12 timse
    if (0xb < (int)uVar7) {
      return;
    }

  } while( true );
}

// (param_1[0x95b] & 0x100
// something only in multiplayer?
// same as function above this one
void FUN_80023784(int param_1)

{
  char cVar1;
  short sVar2;
  short sVar3;
  ushort uVar4;
  ushort uVar5;
  uint *puVar6;
  int iVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  uint *puVar11;
  int *piVar12;
  uint uVar13;
  uint uVar14;
  int iVar15;
  undefined2 *puVar16;
  int iVar17;
  ushort local_30;
  undefined2 local_2e;
  undefined2 local_2c;
  undefined2 local_2a;

  puVar16 = (undefined2 *)(param_1 + 0x5a8);
  uVar13 = 0x1a0;
  local_2c = 0x60;
  local_2a = 0x40;

  // if numPlyrCurrGame is not 2
  uVar14 = 0x100;

  // if numPlyrCurrGame is 2
  if (PTR_DAT_8008d2ac[0x1ca8] == '\x02') {
    uVar14 = 0x180;
  }

  // if 1-2 screens
  iVar17 = 0x380;

  // if more than 2 screens
  if (2 < *(byte *)(param_1 + 0x1ca8)) {
    iVar17 = 0x2c0;
  }

  // loop counter
  iVar15 = 0;
  
  // gGT->0x6bc = (0x5A8 + 0x114)
  piVar12 = (int *)(param_1 + 0x6bc);

  // 12 = three opponents on four screens,
  // max number of pixel-LOD drivers

  // for iVar15 = 0; iVar15 < 0xC; iVar15++
  do
  {
    uVar13 = uVar13 + 0x60;
    if (iVar17 < (int)uVar13) {
      uVar13 = 0x200;
      uVar14 = uVar14 + 0x40;
    }
	
	// 0x114 - 0x43*4(0x10C)
	// 0x5A8->0x8 (pointer to instance)
    
	// if no pointer to instance, return
	if (piVar12[-0x43] == 0) {
      return;
    }
	
    cVar1 = *(char *)(piVar12 + 3);
	
	// pointer to InstDrawPerPlayer
    iVar7 = 
	
		// 0x114 - 0x43*4(0x10C)
		// 0x5A8->0x8 (pointer to instance)
		piVar12[-0x43] + 
	
		// Instance->InstDrawPerPlayer[cVar1]
		(int)cVar1 * 0x88 + 0x74;
    
	// flags (inst 0xB8)
	if ((*(uint *)(iVar7 + 0x44) & 0x140) == 0x140) 
	{
	  // 0x114 - 0x10E
	  // 0x5A8->0x6
      if (*(short *)((int)piVar12 + -0x10e) != 0) 
	  {
        *puVar16 = 0;
		
		// 0x114 - (0x41*4)
		// 0x5A8->0x10
        *(undefined2 *)(piVar12 + -0x41) = *(undefined2 *)(piVar12 + 2);
        *(undefined2 *)((int)piVar12 + -0x102) = *(undefined2 *)((int)piVar12 + 10);
        piVar12[-0x40] = *(int *)(iVar7 + 100);
        
		local_2e = (undefined2)uVar14;
        local_30 = (ushort)uVar13;

		// called 12 times, once for each possible
		// driver that needs pixelLOD in multiplayer

		// PushBuffer_SetDrawEnv_DecalMP
        FUN_80042974(
						// ptrOT?
						piVar12[-1],

						// gGT->backBuffer
						*(undefined4 *)(PTR_DAT_8008d2ac + 0x10),

						// RECT
						&local_30,

						// ofsX
						(int)((uVar13 - (int)*(short *)(piVar12 + 1)) * 0x10000) >> 0x10,

						// ofsY
						(int)((uVar14 - (int)*(short *)((int)piVar12 + 6)) * 0x10000) >> 0x10,

						0,0,0,0,1
                    );
      }

	  // backBuffer->primMem.curr
      puVar11 = *(uint **)(*(int *)(PTR_DAT_8008d2ac + 0x10) + 0x80);

	  *(undefined *)((int)puVar11 + 7) = 0x2d;
      uVar9 = SEXT24(*(short *)(piVar12 + 1));
      sVar2 = *(short *)(piVar12 + 2);
      uVar10 = (int)*(short *)((int)piVar12 + 6) * 0x10000;
      sVar3 = *(short *)((int)piVar12 + 10);
      puVar11[2] = uVar9 | uVar10;
      uVar8 = uVar10 + (int)sVar3 * 0x10000;
      uVar5 = (ushort)uVar13 & 0x3f;
      puVar11[4] = uVar9 + (int)sVar2 | uVar10;
      puVar11[6] = uVar9 | uVar8;
      puVar11[8] = uVar9 + (int)sVar2 | uVar8;
      sVar2 = *(short *)(piVar12 + -0x41);
      iVar7 = (uVar14 & 0xff) + (int)*(short *)((int)piVar12 + -0x102);
      if (0xff < iVar7) {
        iVar7 = 0xff;
      }
      uVar4 = (ushort)((uVar14 & 0xff) << 8);
      *(ushort *)(puVar11 + 3) = uVar5 | uVar4;
      *(ushort *)(puVar11 + 5) = uVar5 + sVar2 | uVar4;
      uVar4 = (ushort)(iVar7 << 8);
      *(ushort *)(puVar11 + 7) = uVar5 | uVar4;
      *(ushort *)(puVar11 + 9) = uVar5 + sVar2 | uVar4;
      *(ushort *)((int)puVar11 + 0x16) =
           (ushort)((int)(uVar14 & 0x100) >> 4) | (ushort)((int)(uVar13 & 0x3ff) >> 6) | 0x100 |
           (ushort)((uVar14 & 0x200) << 2);

	  // pointer to OTMem (25c-168=0xf4)
      puVar6 = (uint *)(*(int *)(param_1 + (int)cVar1 * 0x110 + 0x25c) + (*piVar12 >> 2) * 4);

      *puVar11 = *puVar6 | 0x9000000;
      *puVar6 = (uint)puVar11 & 0xffffff;

	  // backBuffer->primMem.curr
      *(uint **)(*(int *)(param_1 + 0x10) + 0x80) = puVar11 + 10;
    }

	// increment loop counter
    iVar15 = iVar15 + 1;

    piVar12 = piVar12 + 0x4a;
    puVar16 = puVar16 + 0x94;
  } while (iVar15 < 0xc);
  return;
}
