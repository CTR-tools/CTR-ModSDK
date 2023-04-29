
// param1 is gGT (8008d2ac)
// param2 is numModels in LEV
// param3 is array of model pointers
// LibraryOfModels_Store
void FUN_8003147c(int param_1,int param_2,int *param_3)

{
  int iVar1;

  if (param_2 != 0) {
    do
	{
	  // Model pointer
      iVar1 = *param_3;

	  // if model is nullptr
      if (iVar1 == 0)
	  {
		// quit
        return;
      }

	  // if model -> ID is not -1
      if ((int)*(short *)(iVar1 + 0x10) != -1)
	  {
		// Set pointer in array of models
		// modelPtr[model->id] = pointer
        *(int *)(param_1 + (int)*(short *)(iVar1 + 0x10) * 4 + 0x2160) = iVar1;
      }

      param_2 = param_2 + -1;
      param_3 = param_3 + 1;
    } while (param_2 != 0);
  }
  return;
}


// param1 is PTR_DAT_8008d2ac
// LibraryOfModels_Clear
void FUN_800314c0(int param_1)

{
  int iVar1;

  iVar1 = 0xe1;
  param_1 = param_1 + 900;
  do
  {
    *(undefined4 *)(param_1 + 0x2160) = 0;
    iVar1 = iVar1 + -1;
    param_1 = param_1 + -4;
  } while (-1 < iVar1);
  return;
}
