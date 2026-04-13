
// DecalGlobal_EmptyFunc_MainFrame_ResetDB
void FUN_80022b94(void)

{
  return;
}


// DecalGlobal_Clear
void FUN_80022b9c(int param_1)
{
  // Clear all icon pointers
  memset(param_1 + 0x1eec,0,0x220);
  memset(param_1 + 0x2114,0,0x44);
  return;
}


// DecalGlobal_Store
// param_1 is gGT,
// pram_2 is LevTexLookup
void FUN_80022bdc(int param_1,int *param_2)

{
  ushort uVar1;
  int *piVar2;
  uint uVar3;
  uint uVar4;
  int *piVar5;

  // lev->0x3C
  if (param_2 != (int *)0x0) 
  {
	// loop through all icons
    uVar3 = param_2[1];
    uVar4 = uVar3 + *param_2 * 0x20;
    while (uVar3 < uVar4)
	{
	  // if IconID is less than 0x88 (max number of icon pointers)
      if (*(uint *)(uVar3 + 0x10) < 0x88)
	  {
		// Load Icons from LEV
        *(uint *)(param_1 + *(uint *)(uVar3 + 0x10) * 4 + 0x1eec) = uVar3;
      }
      uVar3 = uVar3 + 0x20;
    }
	
	// loop through all iconGroups
    piVar2 = (int *)param_2[3];
    piVar5 = piVar2 + param_2[2];
    while (piVar2 < piVar5)
	{
	  // IconGroupID
      uVar1 = *(ushort *)(*piVar2 + 0x10);

	  // if ID is less than 0x11 (max number of IconGroups)
	  if (uVar1 < 0x11)
	  {
		// Load IconGroup from LEV
        *(int *)(param_1 + ((int)((uint)uVar1 << 0x10) >> 0xe) + 0x2114) = *piVar2;
      }
      piVar2 = piVar2 + 1;
    }
  }
  return;
}


// DecalGlobal_FindInLEV
int * FUN_80022c88(int param_1,int *param_2)

{
  int iVar1;
  int *piVar2;
  int **ppiVar3;
  int **ppiVar4;

  // lev -> levTexLookup
  iVar1 = *(int *)(param_1 + 0x3c);

  // if pointer is valid
  if (iVar1 != 0)
  {
	// pointer to first
    ppiVar3 = *(int ***)(iVar1 + 0xc);

	// pointer to end
    ppiVar4 = ppiVar3 + *(int *)(iVar1 + 8);

    if (ppiVar3 < ppiVar4) {
      do {
        piVar2 = *ppiVar3;

		// check first 16 bytes,
		// remember this is an int array, not char
        if (
			(
			  (
				(*piVar2 == *param_2) &&
				(piVar2[1] == param_2[1])
			  )
			  &&
			  (piVar2[2] == param_2[2])
			) &&
           (piVar2[3] == param_2[3])
		   )
		{
		  // return pointer
          return piVar2;
        }

		// next in loop
        ppiVar3 = ppiVar3 + 1;
      } while (ppiVar3 < ppiVar4);
    }
  }
  return (int *)0;
}


// DecalGlobal_FindInMPK
int * FUN_80022d2c(int *param_1,int *param_2)

{
  int *piVar1;

  // fourth character in string
  piVar1 = param_1 + 3;

  // if pointer is valid
  if (*(char *)param_1 != '\0')
  {
    do
	{
	  // check first 16 bytes,
	  // remember this is an int array, not char
      if (
			(
				(
					// first character [0]
					(*param_1 == *param_2) &&

					// second character [3] + [-2] = [1]
					(piVar1[-2] == param_2[1])
				) &&

				// third character [3] + [-1] = [2]
				(piVar1[-1] == param_2[2])
			) &&

			// fourth [3]
			(*piVar1 == param_2[3])
		)

	  {
		// found the texture
        return param_1;
      }

      param_1 = param_1 + 8;
      piVar1 = piVar1 + 8;
    } while (*(char *)param_1 != '\0');
  }
  return (int *)0;
}
