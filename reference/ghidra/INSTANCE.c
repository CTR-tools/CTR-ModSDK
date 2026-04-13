// INSTANCE_Birth
// param1 ptrInstance
// param2 ptrModel
// param3 name string
// param4 thread
// param5 instance flags
void FUN_80030778(int param_1,undefined4 param_2,undefined *param_3,undefined4 param_4,
                 undefined4 param_5)

{
  bool bVar1;
  undefined *puVar2;
  undefined *puVar3;
  int iVar4;
  int iVar5;

  // name gets stored 8 bytes into instance
  puVar3 = (undefined *)(param_1 + 8);

  // name can be 16 bytes long, max
  puVar2 = (undefined *)(param_1 + 0x17);

  // loop through 16 characters
  bVar1 = puVar2 < puVar3;
  if (puVar3 < puVar2) {

	// copy string from parameter into instance
	do {
      *puVar3 = *param_3;
      puVar3 = puVar3 + 1;
      param_3 = param_3 + 1;
    } while (puVar3 < puVar2);
    bVar1 = puVar2 < puVar3;
  }

  while (!bVar1) {
    *puVar3 = 0;
    puVar3 = puVar3 + 1;
    bVar1 = puVar2 < puVar3;
  }
  *(undefined *)(param_1 + 0x50) = 0xfe;
  *(undefined *)(param_1 + 0x51) = 0xc;

  // animation
  *(undefined *)(param_1 + 0x52) = 0;

  *(undefined *)(param_1 + 0x53) = 1;

  puVar3 = PTR_DAT_8008d2ac;

  // model pointer
  *(undefined4 *)(param_1 + 0x18) = param_2;

  // set scale (x, y, z)
  *(undefined2 *)(param_1 + 0x1c) = 0x1000;
  *(undefined2 *)(param_1 + 0x1e) = 0x1000;
  *(undefined2 *)(param_1 + 0x20) = 0x1000;

  *(undefined2 *)(param_1 + 0x22) = 0;
  *(undefined4 *)(param_1 + 0x24) = 0;
  *(undefined4 *)(param_1 + 0x2c) = 0;
  *(undefined2 *)(param_1 + 0x54) = 0;
  *(undefined2 *)(param_1 + 0x56) = 0;
  *(undefined4 *)(param_1 + 0x58) = 0x7f7f7f;

  // set thread
  *(undefined4 *)(param_1 + 0x6c) = param_4;

  *(undefined4 *)(param_1 + 0x70) = 0;

  // set flags
  *(undefined4 *)(param_1 + 0x28) = param_5;

  // loop counter
  iVar4 = 0;

  // if numPlyrCurrGame is not zero
  if (puVar3[0x1ca8] != '\0')
  {
	// offset of 8008d2ac where pushBuffer structs
	// are held for each player (pos, size, etc)
    iVar5 = 0x168;

	// loop for the numPlyrCurrGame,
	// each instance's InstDrawPerPlayer
    do
	{
	  // pointer to pushBuffer struct
      puVar2 = puVar3 + iVar5;

	  // increment pointer to next winow struct
      iVar5 = iVar5 + 0x110;

	  // pointer to LOD ModelHeader
      *(undefined4 *)(param_1 + 0xe0) = 0;

	  // pushBuffer
      *(undefined **)(param_1 + 0x74) = puVar2;

	  // inst flags per player
	  *(undefined4 *)(param_1 + 0xb8) = 0;

	  // increment loop counter
      iVar4 = iVar4 + 1;

	  // next InstDrawPerPlayer
      param_1 = param_1 + 0x88;

    } while (iVar4 < (int)(uint)(byte)puVar3[0x1ca8]);
  }
  return;
}


// param1 = model pointer
// param2 = name string
// param3 = thread (can be null)
// INSTANCE_Birth3D
int FUN_8003086c(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;

  // PTR_DAT_8008d2ac + 0x18f8
  // Instance Pool

  // JitPool_Add in Instance Pool
  iVar1 = FUN_800310d4(PTR_DAT_8008d2ac + 0x18f8);

  // check if the instance allocated properly
  if (iVar1 != 0)
  {
	// INSTANCE_Birth
	// 0xf instance flags, means model will draw
    FUN_80030778(iVar1,param_1,param_2,param_3,0xf);
  }
  return iVar1;
}

// param1 = model pointer
// param2 = name string
// param3 = thread (can be null)
// INSTANCE_Birth2D
int FUN_800308e4(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  undefined *puVar2;
  int iVar3;
  int iVar4;

  // JitPool_Add in Instance Pool
  iVar3 = FUN_800310d4(PTR_DAT_8008d2ac + 0x18f8);

  // check if the instance allocated properly
  if (iVar3 != 0)
  {
	// INSTANCE_Birth
	// iVar3 is instance allocated
	// instance flag & 0x400, means screenspace
    FUN_80030778(iVar3,param_1,param_2,param_3,0x40f);
  }

  puVar2 = PTR_DAT_8008d2ac;

  // pushBuffer_UI
  *(undefined **)(iVar3 + 0x74) = PTR_DAT_8008d2ac + 5000;

  // iteration counter starts at 1, not 0
  iVar4 = 1;

  // copy pointer to instance
  iVar1 = iVar3;

  // if numPlyrCurrGame is more than 1
  if (1 < (byte)puVar2[0x1ca8])
  {
	// for iVar4 = 1 (not zero); iVar4 < numPlyrCurrGame; iVar4++)
    do 
	{
	  // pushBuffer pointer for P2, P3, P4
      *(undefined4 *)(iVar1 + 0xfc) = 0;

	  // increment loop counter
      iVar4 = iVar4 + 1;

	  // next InstDrawPerPlayer
      iVar1 = iVar1 + 0x88;
    } while (iVar4 < (int)(uint)(byte)puVar2[0x1ca8]);
  }
  return iVar3;
}


// INSTANCE_BirthWithThread -- ND name
// Create Thread, Object, and Instance
// param1 is model ID (see 96b20+2160)
// param2 is a string
// param3 is stackSize, and thread relation
// param4 is bucket type, and thread relation
// param5 is ThTick update func
// param6 is size in bytes
// param7 is parent thread (driver shooting weapon), can be nullptr
undefined4
FUN_800309a4(int param_1,undefined4 param_2,uint param_3,uint param_4,undefined4 param_5,
            uint param_6,undefined4 param_7)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;

  // Get model pointer, given index in array from param1
  iVar3 = *(int *)(PTR_DAT_8008d2ac + param_1 * 4 + 0x2160);

  // Do nothing if the model is garbage
  if (iVar3 == 0)
  {
	// June 1999
	// printf("INSTANCE_BirthWithThread: object type %d not found!\n",param_1);

    uVar1 = 0;
  }

  // if model is valid
  else
  {
	// If the desired size is aligned 4 bytes
    if ((param_6 & 3) == 0)
	{
	  // bit shift and use
      param_6 = param_6 << 0x10;
    }

	// if the desired size is not aligned
    else
	{
	  // round up to the nearest 4 bytes, then bit shift
      param_6 = (param_6 - ((param_6 & 3) - 4)) * 0x10000;
    }

	// PROC_BirthWithObject
    iVar2 = FUN_8004205c(param_3 | param_6 | param_4,param_5,param_2,param_7);

	/*

	June 1999
    if (iVar2 == 0) {
      printf("%s thread create failed (b)\n",param_2);
      do {
                    // WARNING: Do nothing block with infinite loop
      } while( true );
    }

	*/

	// set model index
	*(undefined2 *)(iVar2 + 0x44) = (short)param_1;

	// INSTANCE_Birth3D -- ptrModel, name, thread
    uVar1 = FUN_8003086c(iVar3,param_2,iVar2);

	/*

    if (iVar3 == 0) {
      printf("%s instance create failed (b)\n",param_2);
      do {
                    // WARNING: Do nothing block with infinite loop
      } while( true );
    }

	*/

	// t->inst = inst
	*(undefined4 *)(iVar2 + 0x34) = uVar1;
  }

  // return instance
  return uVar1;
}

// used for every explosion
// INSTANCE_BirthWithThread_Stack
void* FUN_80030a50(undefined4 *param_1)

{
  // same as previous function, but this time with struct instead of typing parameters by hand
  return FUN_800309a4(*param_1,param_1[1],param_1[2],
	param_1[3],param_1[4],param_1[5],param_1[6]);
}


// param1 is an instance
// INSTANCE_Death
void FUN_80030aa8(undefined4 param_1)

{
  // JitPool_Remove
  // 18f8 = Instance Pool
  FUN_8003112c(PTR_DAT_8008d2ac + 0x18f8,param_1);
  return;
}


// INSTANCE_LevInitAll
// copy InstDef to InstancePool
// param1 - pointer to Instance Descriptions
// param2 - number of instances
void FUN_80030ad4(undefined4 *param_1,int param_2)

{
  char cVar1;
  ushort uVar2;
  undefined *puVar3;
  undefined4 *puVar4;
  short sVar5;
  int iVar6;
  undefined4 *puVar7;
  undefined4 *puVar8;
  undefined *puVar9;
  short sVar10;
  undefined4 *puVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  undefined4 uVar15;
  undefined4 uVar16;
  undefined4 uVar17;
  int *piVar18;
  int iVar19;

  iVar19 = 0;

  // loop through all instances
  if (0 < param_2)
  {
	// InstDef starting address of important data
	// (skip name[0x10])
    piVar18 = param_1 + 4;

	do
	{
	  // LIST_RemoveFront
	  // get first free item in Instance Pool
      iVar6 = FUN_8003186c(PTR_DAT_8008d2ac + 0x18f8);

	  // NOT writing to model
	  // InstDef + 0x10 + 0x1c
	  // InstDef -> 0x2C = ptrInstance
	  piVar18[7] = iVar6;

	  // if allocation failed
	  if (iVar6 == 0)
	  {
		// June 1999
		// printf("OOPS! more instdefs than instances");

		// quit
        return;
      }

	  // pointer to InstDef in LEV
	  puVar8 = param_1;

	  // pointer to instance in pool,
	  // add 8 bytes to skip Prev and Next
      puVar4 = (undefined4 *)(iVar6 + 8);

	  // copy InstDef data from LEV to instance pool
      do
	  {
        puVar11 = puVar4;
        puVar7 = puVar8;
        uVar15 = puVar7[1];
        uVar16 = puVar7[2];
        uVar17 = puVar7[3];
        *puVar11 = *puVar7;
        puVar11[1] = uVar15;
        puVar11[2] = uVar16;
        puVar11[3] = uVar17;
        puVar8 = puVar7 + 4;
        puVar4 = puVar11 + 4;
      } while (puVar8 != param_1 + 8);

      uVar15 = puVar7[5];
      uVar16 = puVar7[6];
      puVar11[4] = *puVar8;
      puVar11[5] = uVar15;
      puVar11[6] = uVar16;
      *(char *)(iVar6 + 0x50) = *(char *)(piVar18 + 5) + -2;
      cVar1 = *(char *)(piVar18 + 5);

	  // reflect color
	  *(undefined4 *)(iVar6 + 0x58) = 0x7f7f7f;

      *(undefined *)(iVar6 + 0x52) = 0;
      *(undefined2 *)(iVar6 + 0x54) = 0;

	  // instace -> instDef
	  // the two are now linked on both ends
      *(undefined4 **)(iVar6 + 0x2c) = param_1;

	  *(undefined2 *)(iVar6 + 0x56) = 0;
      *(undefined *)(iVar6 + 0x53) = 1;
      *(undefined4 *)(iVar6 + 0x70) = 0;
      *(char *)(iVar6 + 0x51) = cVar1 + '\f';

	   // convert 3 rotation shorts into rotation matrix,
	   // offset 0x36 is InstDef rotation data
      FUN_8006c2a4(iVar6 + 0x30,(int)param_1 + 0x36);

      puVar3 = PTR_DAT_8008d2ac;

	  // instance posX and posY
      *(int *)(iVar6 + 0x44) = (int)*(short *)(piVar18 + 8);
      *(int *)(iVar6 + 0x48) = (int)*(short *)((int)piVar18 + 0x22);

	  // instance posZ
      sVar10 = *(short *)(piVar18 + 9);

	  // instance -> thread = nullptr;
      *(undefined4 *)(iVar6 + 0x6c) = 0;

	  // instance posZ
      *(int *)(iVar6 + 0x4c) = (int)sVar10;

	  // loop iteration counter
      iVar13 = 0;

	  // if numPlyrCurrGame is not zero
      if (puVar3[0x1ca8] != '\0')
	  {
		// offset of 8008d2ac where pushBuffer structs
		// are held for each player (pos, size, etc)
        iVar14 = 0x168;

        iVar12 = iVar6;

		// loop through InstDrawPerPlayer
		// for iVar13 = 0; iVar13 < numPlyrCurrGame; iVar13++
        do
		{
		  // pointer to pushBuffer struct
          puVar9 = puVar3 + iVar14;

		  // increment pointer to next pushBuffer struct
          iVar14 = iVar14 + 0x110;

		  // LOD ModelHeader
          *(undefined4 *)(iVar12 + 0xe0) = 0;

		  // pushBuffer
          *(undefined **)(iVar12 + 0x74) = puVar9;

		  // increment counter
          iVar13 = iVar13 + 1;

		  // next InstDrawPerPlayer
          iVar12 = iVar12 + 0x88;
		  
        } while (iVar13 < (int)(uint)(byte)puVar3[0x1ca8]);
      }

      if (
		  (
			// Only continue if LEV instances are enabled,
			// they may be disabled due to podium scene on adv hub
			((*(uint *)(PTR_DAT_8008d2ac + 8) & 0x100) == 0) &&

			(
				// COLL_LevModelMeta
				iVar13 = FUN_8001d094((int)*(short *)(*piVar18 + 0x10)),

				// if pointer is not nulllptr
				iVar13 != 0
			)
		  ) &&

		  // If funcLevInstDefBirth
          (*(code **)(iVar13 + 4) != (code *)0x0)
		 )
	  {
		// call funcLevInstDefBirth, make thread for this instance
        (**(code **)(iVar13 + 4))(iVar6);
      }

      if (
			(
				// If you're not in Time Trial
				(*(uint *)PTR_DAT_8008d2ac & 0x20000) == 0
			) ||

			// OR, if you're in time trial, with these conditions...
			(
				(
					(
						// model ID
						uVar2 = *(ushort *)(*piVar18 + 0x10),

						// if PU_TIME_CRATE (1,2,3)
						1 < (uint)uVar2 - 7 &&

						// if not wumpa fruit
						(uVar2 != 2)
					) &&
					(
						(
							// not STATIC_TIME_CRATE_01
							uVar2 != 0x5c &&
							(
								(
									// not STATIC_TIME_CRATE_02
									uVar2 != 100 &&

									// not STATIC_TIME_CRATE_03
									(uVar2 != 0x65)
								)
							)
						)
					)
				)
			)
		 )
	  {

		// If you're not in a Relic Race
        if ((*(uint *)PTR_DAT_8008d2ac & 0x4000000) == 0)
		{
		  // model ID
          sVar10 = *(short *)(*piVar18 + 0x10);

		  // time crate (1,2,3)
		  if ((sVar10 != 0x5c) && (sVar5 = 0x65, sVar10 != 100)) {
LAB_80030d94:
            if (sVar10 != sVar5) goto LAB_80030dac;
          }
          goto LAB_80030d9c;
        }

		// model ID
        sVar10 = *(short *)(*piVar18 + 0x10);

		// time crate (1,2,3)
		if ((sVar10 != 0x5c) && ((sVar10 != 100 && (sVar10 != 0x65))))
		{
          sVar5 = 2;

		  // PU_TIME_CRATE (what's the difference)?
          if (1 < (ushort)(*(short *)(*piVar18 + 0x10) - 7U)) goto LAB_80030d94;

		  goto LAB_80030d9c;
        }

		// increase count in time crates
        *(int *)(PTR_DAT_8008d2ac + 0x1e2c) = *(int *)(PTR_DAT_8008d2ac + 0x1e2c) + 1;
      }

	  // in time trial, and conditions are not met
      else
	  {
		// do not draw instance
LAB_80030d9c:
        *(uint *)(iVar6 + 0x28) = *(uint *)(iVar6 + 0x28) & 0xfffffff0;
      }
LAB_80030dac:
	  // If you're not in Crystal Challenge (in adventure mode)
      if ((*(uint *)PTR_DAT_8008d2ac & 0x8000000) == 0)
	  {
		// modelID
        sVar10 = *(short *)(*piVar18 + 0x10);

		// disable anything that isn't Crystal, TNT, or Nitro
        if ((sVar10 != 0x60) && (sVar5 = 0x27, sVar10 != 6)) goto LAB_80030e18;
LAB_80030e20:
        *(uint *)(iVar6 + 0x28) = *(uint *)(iVar6 + 0x28) & 0xfffffff0;
      }

	  // If you're in crystal challenge
      else
	  {
		// get model ID
        sVar10 = *(short *)(*piVar18 + 0x10);

		// fruit crate
		sVar5 = 7;

		// if modelID is crystal
		if (sVar10 == 0x60)
		{
		  // increase numCrystals in LEV
          *(int *)(PTR_DAT_8008d2ac + 0x1e28) = *(int *)(PTR_DAT_8008d2ac + 0x1e28) + 1;
        }

		// if not crystal
		else
		{
LAB_80030e18:

		  // if model is fruit crate,
		  // dont draw instance, dont collide, etc
          if (sVar10 == sVar5) goto LAB_80030e20;
        }
      }


      if (
			(
				// If you're not in Adventure Mode
				((*(uint *)PTR_DAT_8008d2ac & 0x80000) == 0) ||

				// If you're not in a CTR Token race
				((*(uint *)(PTR_DAT_8008d2ac + 8) & 8) == 0)
			) &&

			// If any of the C-T-R letter instances appear
			((uint)*(ushort *)(*piVar18 + 0x10) - 0x93 < 3)
			)
	  {
		// disable them
        *(uint *)(iVar6 + 0x28) = *(uint *)(iVar6 + 0x28) & 0xfffffff0;
      }

	  // loop counter
      iVar19 = iVar19 + 1;

      piVar18 = piVar18 + 0x10;

	  // next InstDef
      param_1 = param_1 + 0x10;

    } while (iVar19 < param_2);
  }
  return;
}

// INSTANCE_LevDelayedLInBs
// only for podium->driving (233->232)
void FUN_80030ed4(int param_1,int param_2)

{
  int iVar1;
  undefined4 *puVar2;
  int iVar3;

  iVar3 = 0;

  // if numInstance is more than zero
  if (0 < param_2)
  {
	// first instance -> InstDef
    puVar2 = (undefined4 *)(param_1 + 0x2c);

	// loop through all instances
	do
	{
	  // ThreadMeta
	  // model -> modelID
      iVar1 = FUN_8001d094((int)*(short *)(puVar2[-7] + 0x10));

	  if (
			// if pointer is not nullptr
			(iVar1 != 0) &&

			// if LInB
			(*(code **)(iVar1 + 4) != (code *)0x0))
	  {
		// execute LInB for this instance
        (**(code **)(iVar1 + 4))(*puVar2);
      }

	  // index counter
	  iVar3 = iVar3 + 1;

	  // next InstDef
      puVar2 = puVar2 + 0x10;

    } while (iVar3 < param_2);
  }
  return;
}

// INSTANCE_GetNumAnimFrames
// param_1 is instance
// param_2 is animation index (for models with many animations)
undefined4 FUN_80030f58(int param_1,int param_2)

{
  int iVar1;

  // instance -> model
  iVar1 = *(int *)(param_1 + 0x18);

  if (
		(
			(
				// if model is valid
				(iVar1 != 0) &&

				// if model has more than one model_header
				(0 < *(short *)(iVar1 + 0x12))
			) &&
			(
				// get pointer to first model_header
				iVar1 = *(int *)(iVar1 + 0x14),

				// if pointer to model_header is valid
				iVar1 != 0
			)
		) &&

		// param_2 is less than numAnimations
		(param_2 < *(int *)(iVar1 + 0x34))
	  )
  {
	// if pointer to animatino data is valid
    if (*(int *)(iVar1 + 0x38) != 0)
	{
	  // get pointer to animation, from array of animation pointers
      iVar1 = *(int *)(param_2 * 4 + *(int *)(iVar1 + 0x38));

	  // if animation data is valid
      if (iVar1 != 0)
	  {
		// return number of frames
        return (uint)*(ushort *)(iVar1 + 0x10) & 0x7fff;
      }
      return 0;
    }
  }
  return 0;
}
