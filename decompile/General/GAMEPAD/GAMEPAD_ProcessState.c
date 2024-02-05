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
      pad->motorPower[0] = 0;
      pad->motorPower[1] = 0;
      break;
    case 6:
      if (pad->gamepadType == 0) 
	  {
        iVar2 = PadSetMainMode(id, 1, 0);
        if (iVar2 != 0) {
          pad->gamepadType = 1;
        }
      } 
	  else if (pad->gamepadType == 1) 
	  {
		// get number of motors on pad
        iVar2 = PadInfoAct(id, 0xffffffff, 0);
        if (iVar2 > 2) {
          iVar2 = 2;
        }
		
		// set to zero by default
		*(short*)&pad->motorPower[0] = 0;
		
		// loop through motors
		for(iVar3 = 0; iVar3 < iVar2; iVar3++)
		{
            uVar1 = PadInfoAct(id, iVar3, 4);
            pad->motorPower[iVar3] = uVar1;
        }

        PadSetAct(id, &pad->motorSubmit[0], sizeof(pad->motorSubmit));

        if (PadSetActAlign(id, &sdata->unkPadSetActAlign) != 0) 
		{
          pad->gamepadType = 2;
        }
      }
      break;
  }
  return;
}
