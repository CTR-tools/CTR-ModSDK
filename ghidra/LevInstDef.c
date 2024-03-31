// LevInstDef_UnPack
void FUN_8003116c(int *param_1)

{
  int *piVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;

  // First quadblock
  // ptrQuadBlockArray
  uVar3 = param_1[3];

  // Last quadblock
  // ptrQuadBlockArray + numQuadBlock * sizeof(QuadBlock)
  uVar4 = uVar3 + *param_1 * 0x5c;

  // loop through all quadblocks
  while (uVar3 < uVar4)
  {
    if (
			// quadblock -> ptr_add_tex
			(*(int *)(uVar3 + 0x44) != 0) &&

			(
				// array of InstDef pointers
				piVar1 = *(int **)(*(int *)(uVar3 + 0x44) + 8),

				piVar1 != (int *)0x0
			)
		)
	{
      iVar2 = *piVar1;

	  // loop through all
      while (iVar2 != 0)
	  {
		// InstDef = InstDef -> Instance
        *piVar1 = *(int *)(*piVar1 + 0x2c);

        piVar1 = piVar1 + 1;
        iVar2 = *piVar1;
      }
    }

	// go to next quadblock
    uVar3 = uVar3 + 0x5c;
  }

  // get pointer to array of InstDef
  piVar1 = *(int **)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0x24);

  // if pointer is valid
  if (piVar1 != (int *)0x0)
  {
	// get the first instance in array
    iVar2 = *piVar1;

	while (iVar2 != 0)
	{
	  // item = InstDef->instance
      *piVar1 = *(int *)(*piVar1 + 0x2c);

      piVar1 = piVar1 + 1;
      iVar2 = *piVar1;
    }
  }
  return;
}


// LevInstDef_RePack
void FUN_80031268(int *param_1,int param_2)

{
  int *piVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;

  // First quadblock
  // ptrQuadBlockArray
  uVar5 = param_1[3];

  // Last quadblock
  // ptrQuadBlockArray + numQuadBlock * sizeof(QuadBlock)
  uVar3 = uVar5 + *param_1 * 0x5c;

  // loop through all quadblocks
  while (uVar5 < uVar3)
  {
    if (
			// quadblock -> ptr_add_tex
			(*(int *)(uVar5 + 0x44) != 0) &&

			(
				// array of instances visible from quadblock
				piVar1 = *(int **)(*(int *)(uVar5 + 0x44) + 8),

				piVar1 != (int *)0x0
			)
		)
	{

	  iVar2 = *piVar1;

	  // loop through all
	  while (iVar2 != 0)
	  {
		// convert back to InstDef
        *piVar1 = *(int *)(*piVar1 + 0x2c);

        piVar1 = piVar1 + 1;
        iVar2 = *piVar1;
      }
    }

	// go to next quadblock
    uVar5 = uVar5 + 0x5c;
  }

  // get pointer to array of instance pointers
  piVar1 = *(int **)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0x24);

  // if pointer is valid
  if (piVar1 != (int *)0x0)
  {
	// get the first instance in array
    iVar2 = *piVar1;

	// loop through all
    while (iVar2 != 0)
	{
	  // get InstDef
      iVar2 = *(int *)(*piVar1 + 0x2c);

	  // if this function is called when
	  // swapping LEVs in Adventure hub
	  if (param_2 != 0)
	  {
		// get thread from instance
        iVar4 = *(int *)(*piVar1 + 0x6c);

		// if thread is attached to this instance
        if (iVar4 != 0)
		{
		  // 0x800 = this thread needs to be deleted
          *(uint *)(iVar4 + 0x1c) = *(uint *)(iVar4 + 0x1c) | 0x800;
        }

		// LIST_AddFront
		// free list of instance pool
        FUN_80031744(PTR_DAT_8008d2ac + 0x18f8,*piVar1);
      }

	  // instance = InstDef
      *piVar1 = iVar2;

      piVar1 = piVar1 + 1;
      iVar2 = *piVar1;
    }
  }

  // PROC_CheckAllForDead
  FUN_80041ff4();

  return;
}
