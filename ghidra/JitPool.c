// JitPool_Clear
void FUN_80030fdc(int param_1)

{
  uint uVar1;
  int iVar2;

  // Ptr to first element in pool
  iVar2 = *(int *)(param_1 + 0x24);

  // loop counter
  uVar1 = 0;

  // LIST_Clear free
  FUN_80031734(param_1);

  // LIST_Clear taken
  FUN_80031734(param_1 + 0xc);

  // If there are elements in the array
  if (*(int *)(param_1 + 0x18) != 0)
  {
	// loop through every element
    do
	{
	  // LIST_AddFront
	  // add to free list
      FUN_80031744(param_1,iVar2);

	  // increment loop counter
	  uVar1 = uVar1 + 1;

	  // Add the size of each element
      iVar2 = iVar2 + (*(uint *)(param_1 + 0x1c) & 0xfffffffc);

    } while (uVar1 < *(uint *)(param_1 + 0x18));
  }
  return;
}

// JitPool_Init
// param_1 = pointer
// param_2 = width or array length
// param_3 = height or sizeof(struct)
// param_4 = name
void FUN_8003105c(int param_1,int param_2,int param_3,undefined4 param_4)
{
  memset(param_1,0,0x28);

  // max items
  // size of item
  // size of pool
  *(int *)(param_1 + 0x18) = param_2;
  *(int *)(param_1 + 0x1c) = param_3;
  *(int *)(param_1 + 0x20) = param_2 * param_3;

  // MEMPACK_AllocMem
  uVar1 = FUN_8003e874(param_2 * param_3,param_4);

  // pointer to first element in pool
  *(undefined4 *)(param_1 + 0x24) = uVar1;

  // JitPool_Clear
  FUN_80030fdc(param_1);

  return;
}


// JitPool_Add
int FUN_800310d4(int *param_1)

{
  int iVar1;

  iVar1 = *param_1;

  if (iVar1 == 0)
  {
    iVar1 = 0;
  }

  else
  {
	// remove member from free
    // LIST_RemoveMember
    FUN_800317e4(param_1,iVar1);

	// add member to taken
    // LIST_AddFront
    FUN_80031744(param_1 + 3,iVar1);
  }

  return iVar1;
}


// JitPool_Remove
// param1 is element pool (pointer varies)
// param2 is element (type varies)
void FUN_8003112c(int param_1,undefined4 param_2)

{
  // remove member from taken
  // LIST_RemoveMember
  FUN_800317e4(param_1 + 0xc);

  // add member to free
  // LIST_AddFront
  FUN_80031744(param_1,param_2);

  return;
}
