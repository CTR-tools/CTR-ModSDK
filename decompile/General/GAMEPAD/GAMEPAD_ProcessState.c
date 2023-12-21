#include <common.h>

void DECOMP_GAMEPAD_ProcessState(struct GamepadBuffer* pad, int padState, short id)
{
  char uVar1;
  int iVar2;
  int iVar3;

  switch (padState) {
    case 1:
      if (pad->gamepadType != 0) {
        pad->gamepadType = 1;
      }
      break;
    case 2:
      pad->motorStepRate[0] = 0;
      pad->motorStepRate[1] = 0;
      break;
    case 6:
      if (pad->gamepadType == 0) {
        iVar2 = PadSetMainMode(id, 1, 0);
        if (iVar2 != 0) {
          pad->gamepadType = 1;
        }
      } else if (pad->gamepadType == 1) {
        iVar2 = PadInfoAct(id, 0xffffffff, 0);
        if (2 < iVar2) {
          iVar2 = 2;
        }
		
        iVar3 = 0;
        
		if (0 < iVar2) {
          do {
            uVar1 = PadInfoAct(id, iVar3, 4);
            pad->motorStepRate[iVar3] = uVar1;
            iVar3 = iVar3 + 1;
          } while (iVar3 < iVar2);
        }
        
		while (iVar2 < 2) {
          pad->motorStepRate[iVar2] = 0;
          iVar2 = iVar2 + 1;
        }

        PadSetAct(id, &pad->motorPrev[0], 2);

        if (PadSetActAlign(sdata->unkPadSetActAlign[id]) != 0) {
          pad->gamepadType = 2;
        }
      }
      break;
  }
  return;
}
