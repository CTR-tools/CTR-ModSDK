// Podium_InitModels
void FUN_80041c84(int param_1)

{
  char cVar1;
  short sVar2;
  int iVar3;
  int *piVar4;
  int iVar5;

  // loop counter
  iVar5 = 0;

  // pointer to player 1 structure
  piVar4 = (int *)(param_1 + 0x24ec);

  // default podium values
  *(undefined *)(param_1 + 0x2575) = 0;
  *(undefined *)(param_1 + 0x2576) = 0;
  *(undefined *)(param_1 + 0x2577) = 0;

  // STATIC_TAWNA1
  *(undefined *)(param_1 + 0x2578) = 0x8f;

  // for iVar5 = 0; iVar5 < 8; iVar5++
  do
  {
	// address to structure of current player (0-7)
    iVar3 = *piVar4;

	// if address is not nullptr
    if (iVar3 != 0)
	{
		// player structure + 0x482 is your rank in the race
		// 0 = 1st place, 1 = 2nd place, 2 = 3rd place, etc
      sVar2 = *(short *)(iVar3 + 0x482);

	  // If you're in 2nd place
      if (sVar2 == 1)
	  {
		// Player / AI structure + 0x4a shows driver index (0-7)

													// character ID						+ 126
        *(char *)(param_1 + 0x2576) = *(char *)(&DAT_80086e84 + *(byte *)(iVar3 + 0x4a)) + '~';
      }
      else {
        if (sVar2 < 2)
		{
		  // first place
          if (sVar2 == 0) {
            cVar1 = *(char *)(&DAT_80086e84 + *(byte *)(iVar3 + 0x4a));
            *(char *)(param_1 + 0x2575) = cVar1 + '~';
            switch(cVar1 + '~') {
            case '~':
            case -0x7f:
			  // STATIC_TAWNA2
              *(undefined *)(param_1 + 0x2578) = 0x90;
              break;
            case '\x7f':
            case -0x7e:
			  // STATIC_TAWNA3
              *(undefined *)(param_1 + 0x2578) = 0x92;
              break;
            case -0x7c:
            case -0x7b:
			  // STATIC_TAWNA4
              *(undefined *)(param_1 + 0x2578) = 0x91;
            }
          }
        }
        else
		{
		  // third place
          if (sVar2 == 2)
		  {
			  // Player / AI structure + 0x4a shows driver index (0-7)

														// character ID						+ 126
            *(char *)(param_1 + 0x2577) = *(char *)(&DAT_80086e84 + *(byte *)(iVar3 + 0x4a)) + '~';
          }
        }
      }
    }

	// increment loop counter
    iVar5 = iVar5 + 1;

	// pointer (int*) increment, really adds 4 to address
    piVar4 = piVar4 + 1;

  } while (iVar5 < 8);
  return;
}
