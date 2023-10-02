#include <common.h>

void DECOMP_BOTS_ThTick_EngineRevving(struct Thread* botThread)
{
  struct MaskHeadWeapon* maskObj;
  struct Driver* bot;

  bot = botThread->object;

  // AI Mask Object
  maskObj = bot->maskObj;

  // if AI is being mask grabbed
  if (bot->ai_posBackup[1] < bot->posCurr[1])
  {
    bot->posCurr[1] -= ((sdata->gGT->elapsedTimeMS << 9) >> 5);

    // if you have a mask from mask-grab
    if (maskObj)
    {
      // set mask position to driver position
      maskObj->pos[0] = (short)(bot->posCurr[0] >> 8);
      maskObj->pos[1] = (short)(bot->posCurr[1] >> 8);
      maskObj->pos[2] = (short)(bot->posCurr[2] >> 8);
    }

    OnRender(botThread, bot);

    OnAnimate_Driving(botThread, bot);

    VehParticle_DriverMain(botThread, bot);
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

    // erase pointer to object
    bot->maskObj = NULL;

    // kart state engineRevving
    bot->kartState = ENGINE_REVVING;

    // clock weapon recv
    bot->clockReceive = 0;

    // squish timer
    bot->squishTimer = 0;

    // execute, then assign BOTS_ThTick_Drive
    ThTick_SetAndExec(botThread, BOTS_ThTick_Drive);
  }
  return;
}
 