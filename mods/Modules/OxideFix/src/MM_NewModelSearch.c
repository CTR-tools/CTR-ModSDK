// new implementation of FUN_800adb64,
// CharacterSelect_SearchModelByString,
// to return Crash's model instead of nullptr,
// if Oxide can not be found on first frame

#include <common.h>

// original, which compiles to 0x118 bytes instead of 0xA8 (original)
#if 0
// CharacterSelect_SearchModelByString
int * FUN_800adb64(int *param_1)

{
  int **ppiVar1;
  int *piVar2;

  // return value is nullptr by default
  piVar2 = (int *)0x0;

  if (
		// if lev -> model array exists,
		(
			// if LEV is valid
			(sdata->gGT->level1 != 0) &&
			(
				// pointer to array of every single model pointer
				ppiVar1 = (int **)(sdata->gGT->level1->ptrModelsPtrArray),
				ppiVar1!= (int **)0x0
			)
		) &&

		// if first member of the model array != nullptr
		(
			// piVar2 = address of first modelptr
			piVar2 = *ppiVar1,

			// if first modelptr is valid
			piVar2 != (int *)0x0
		)
	 )
  {
	// loop through all models until nullptr is found
    do
	{
	  // if model exists, check first 16 bytes for name
      if (((*piVar2 == *param_1) && (piVar2[1] == param_1[1])) &&
         ((piVar2[2] == param_1[2] && (piVar2[3] == param_1[3]))))
	  {
		// return model pointer
        return piVar2;
      }

	  // go to next model
      ppiVar1 = ppiVar1 + 1;
      piVar2 = *ppiVar1;

    } while (piVar2 != (int *)0x0);
  }
  return piVar2;
}
#endif

// custom version, which can't return nullptr
#if 1
void MM_EndOfFile();
// CharacterSelect_SearchModelByString
int * FUN_800adb64(int *param_1)

{
  int **ppiVar1;
  int *piVar2;
  int *piVar3;
  struct Model* m;

  if((int)sdata->gGT->level1 == (int)0) return (int*) 0;

  // pointer to array of every single model pointer
  ppiVar1 = (int **)(sdata->gGT->level1->ptrModelsPtrArray);

  // piVar2 = address of first modelptr
  piVar2 = *ppiVar1,

  // backup of first model (crash bandicoot)
  piVar3 = piVar2;

  // loop through all models until nullptr is found,
  // this only works because the first bytes after
  // the array, is mesh_info, with 0 quadblocks and 0 vertices
  do
  {
	// if model exists, check first 4 bytes for name
    if (*piVar2 == *param_1)
	{
		// return model pointer
        return piVar2;
    }

	// go to next model
    ppiVar1 = ppiVar1 + 1;
    piVar2 = *ppiVar1;

  } while (piVar2 != (int *)0x0);

  // if model was not found,
  // check oxide
  extern unsigned char oxideModel[];
  m = (struct Model*)(&oxideModel[4]);
  if(*param_1 == *(int*)m) return (int*)m;

  // at this point, fail
  return 0;
}
#endif