// called "EffectSfx" for no good reason,
// but is related to rain sounds, no proof of name

// DropRain_MakeSound
// handle rain on tiger temple and cortex castle
void FUN_80024464(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  uint uVar4;

  uVar4 = 0;

  if (
		// if LevelID is 4
		// if you are on Tiger Temple
		(*(int *)(PTR_DAT_8008d2ac + 0x1a10) == 4) ||

		// if LevelID is 10
		// if you are on Cortex Castle
		(*(int *)(PTR_DAT_8008d2ac + 0x1a10) == 10)
	  )
  {
	// loop counter
    iVar3 = 0;

	// param1 is PTR_DAT_8008d2ac
    iVar2 = param_1;

	// if numPlyrCurrGame is not zero
    if (*(byte *)(param_1 + 0x1ca8) != 0)
	{
	  // for iVar3 = 0; iVar3 < numPlyrCurrGame; iVar3++
      do
	  {
		// increment loop counter
        iVar3 = iVar3 + 1;

        uVar4 = uVar4 | *(uint *)(iVar2 + 0x1a40);
        iVar2 = iVar2 + 0x30;
      } while (iVar3 < (int)(uint)*(byte *)(param_1 + 0x1ca8));
    }

	// if nobody is rained on
    if (uVar4 == 0)
	{
	  // if there is rain
      if (*(int *)(param_1 + 0x1ec8) != 0)
	  {
		// OtherFX_Stop1
        FUN_80028808();

		// no more rain
		*(undefined4 *)(param_1 + 0x1ec8) = 0;
      }
    }

	// if at least one is rained on
	else
	{
	  // if there is no rain
      if (*(int *)(param_1 + 0x1ec8) == 0)
	  {
		// OtherFX_Play
        uVar1 = FUN_80028468(0x82,0);

		// uVar 1 is for rain sound???

		// now there is rain
        *(undefined4 *)(param_1 + 0x1ec8) = uVar1;
      }
    }
  }
  return;
}


// param1 is PTR_DAT_8008d2ac
// DropRain_Reset
void FUN_8002451c(int param_1)

{
  *(undefined4 *)(param_1 + 0x1ec8) = 0;
  return;
}
