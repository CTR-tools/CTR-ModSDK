#include <common.h>

void DECOMP_BOTS_ThTick_RevEngine(struct Thread* botThread)
{
  struct MaskHeadWeapon* maskObj;
  struct Driver* bot;

  bot = botThread->object;

  // AI Mask Object
  maskObj = bot->maskObj;

  // if AI is being mask grabbed
  if (bot->ai_posBackup[1] < bot->posCurr.y)
  {
    bot->posCurr[1] -= ((sdata->gGT->elapsedTimeMS << 9) >> 5);

    // if you have a mask from mask-grab
    if (maskObj)
    {
      // set mask position to driver position
      maskObj->pos[0] = (short)(bot->posCurr.x >> 8);
      maskObj->pos[1] = (short)(bot->posCurr.y >> 8);
      maskObj->pos[2] = (short)(bot->posCurr.z >> 8);
    }

    VehPhysForce_TranslateMatrix(botThread, bot);

    VehFrameProc_Driving(botThread, bot);

    VehEmitter_DriverMain(botThread, bot);
  }
  // if not mask grab
  else
  {
    // if mask object exists
    if (maskObj)
    {
      // clean up?
      maskObj->scale = 0x1000;
      maskObj->duration = 0;
      maskObj->rot[2] &= 0xfffe;
    }

    bot->maskObj = NULL;
    bot->kartState = KS_ENGINE_REVVING;
    bot->clockReceive = 0;
    bot->squishTimer = 0;

    // execute, then assign BOTS_ThTick_Drive
    ThTick_SetAndExec(botThread, BOTS_ThTick_Drive);
  }
  return;
}
