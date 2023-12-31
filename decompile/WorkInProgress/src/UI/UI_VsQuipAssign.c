#include <common.h>

void DECOMP_UI_VsQuipAssign(struct Driver* d,u_int *param_2,int param_3,int param_4)
{
  struct GameTracker *gGT;
  short timer;
  int currIndex;
  u_int uVar4;
  u_int uVar5;

  if (
		// if driver object exists
		(d != 0) &&

		(((*(u_short *)((int)param_2 + 10) & 4) == 0 || (d == param_3)))
	  )
  {
    uVar5 = *param_2;
    uVar4 = uVar5 + 8;
    if (uVar4 < param_2[1]) {
      do {
        if (
				((uVar5 + 4) < (uVar4 + 4)) ||
				(
					(
						(uVar4 + 4) == (uVar5 + 4) &&
						(
							// random number
							currIndex = DECOMP_MixRNG_Scramble(),
							(currIndex >> 3 & 0xffU) < 0x40
						)
					)
				)
			)
		{
          uVar5 = uVar4;
        }
        uVar4 = uVar4 + 8;
      } while (uVar4 < param_2[1]);
    }
    if (d->EndOfRaceComment_lngIndex != 0) {
      currIndex = (d->EndOfRaceComment_lngIndex + 4);
      if ((uVar5 + 4) <= currIndex) {
        if ((uVar5 + 4) != currIndex) {
          return;
        }

		// Get random number
        currIndex = DECOMP_MixRNG_Scramble();

        if (0x3f < (currIndex >> 3 & 0xffU)) {
          return;
        }
      }
      currIndex = d->EndOfRaceComment_lngIndex;
      if (currIndex != 0 && currIndex < -4) {
        currIndex = -currIndex - 4;
      }
    }
    if (uVar5 < -4) {
      uVar5 = -(uVar5 + 4);
    }
    gGT = sdata->gGT;
    d->EndOfRaceComment_lngIndex= uVar5;
    d->EndOfRaceComment_characterID = param_4;

	// 150 frames (5 seconds) for Battle
    timer = 0x96;

	// if not battle mode (VS)
    if ((gGT->gameMode1 & BATTLE_MODE) == 0)
	{
	  // 300 frames (10 seconds) for VS
      timer = 300;
    }

	// set cooldown after end of VS race
	gGT->timerEndOfRaceVS = timer;
  }
  return;
}