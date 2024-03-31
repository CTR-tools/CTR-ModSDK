#include <common.h>

void CS_Boss_ThTick(struct Thread *t)
{
  char i;

  int cutsceneID;
  int *piVar4;
  short levID;
  MATRIX mat;

  struct Instance *inst;
  struct Thread *otherThread;
  struct CutsceneObj *cs;
  struct GameTracker *gGT;

  gGT = sdata->gGT;
  levID = gGT->levelID;

  // first determine which cutscene will play
  if (OVR_233.unknown3 < 0)
  {
    // Intro Boss Cutscene

    // subtract 25 from lev ID to get adv hub index (0-5)
    otherThread = (levID - 25) * 2;
    cutsceneID = (levID - 25) * 4;

    // If you are at podium after winning a Key
    if (gGT->podiumRewardID == 99)
    {
      // Outro Boss Cutscene
      otherThread++;
      cutsceneID = otherThread * 2;
    }

    cutsceneID = cutsceneID * 4 + otherThread * 5;
  }
  else
  {
    cutsceneID = OVR_233.unknown3 * 0xd;
  }

  // array index
  cutsceneID = cutsceneID * 4;

  switch (OVR_233.cutsceneState)
  {
  // first state of boss cutscene
  case 0:
  case 1:

    OVR_233.cutsceneState = 2;

    // set desired screen brightness to black
    gGT->pushBuffer_UI.fadeFromBlack_desiredResult = 0;

    // set brightness to subtract each frame
    gGT->pushBuffer_UI.fade_step = -0x400;

    break;
  case 2:

    // if pushBuffer_UI is fully faded to black
    if (gGT->pushBuffer_UI.fadeFromBlack_currentValue == 0)
    {
      // podium "other" threads
      otherThread = gGT->threadBuckets[OTHER].thread;

      // kill this thread and all siblings
      while (otherThread != 0)
      {
        // This thread is now dead
        otherThread->flags |= 0x800;

        // thread = thread->sibling
        otherThread = otherThread->siblingThread;
      }

      // if all podium threads are dead
      if (gGT->threadBuckets[OTHER] == 0)
      {
        CS_Boss_Init(cutsceneID + 0x800B7488);
        OVR_233.cutsceneState = 3;
      }
    }

    break;

  case 3:

    if (*(int*)0x800b7778 != 0)
    {
      piVar4 = 0x800b7778;
      for (i = 0; i < 2; i++)
      {
        if (*piVar4 != 0)
        {
          if (otherThread != 0)
          {
            *piVar4 = *piVar4 + 4;
          }
          gGT->modelPtr[*piVar4 + 0x10] = *piVar4;
        }
        piVar4++;
      }

      MEMPACK_SwapPacks(gGT->activeMempackIndex);

      mat.m[0][0] = *(short *)(cutsceneID + 0x800B74AC); 
      mat.m[0][1] = *(short *)(cutsceneID + 0x800B74AE); 
      mat.m[0][2] = *(short *)(cutsceneID + 0x800B74B0); 

      // Boss cutscenes are always at ground level?
      mat.m[1][0] = 0;
      mat.m[1][1] = 0;
      mat.m[1][2] = 0;

      mat.m[2][0] = *(short *)(cutsceneID + 0x800B74B4);
      mat.m[2][1] = *(short *)(cutsceneID + 0x800B74B6);
      mat.m[2][2] = *(short *)(cutsceneID + 0x800B74B8);

      piVar4 = 0x800b777c;

      for (i = 2; i > 0; i--)
      {
        if (i > 0)
        {
          otherThread = NULL;
        }
        if ((*piVar4 != 0) &&
            
            // create thread return instance
            (otherThread = CS_Thread_Init(*(short *)(*piVar4 + 0x10), *piVar4, &mat, 0, otherThread),

            otherThread != NULL)
            )
        {
          // get instance from thread
          inst = otherThread->inst;

          // get object from thread
          cs = otherThread->object;

          if (i == 0)
          {
            CS_ScriptCmd_OpcodeAt(cs, *(int *)(cutsceneID + 0x800B7498));

            cs->unk14 = 0;
          }

          // Set scale (x, y, z)
          inst->scale[0] = 0x1000;
          inst->scale[1] = 0x1000;
          inst->scale[2] = 0x1000;

          cs->desiredScale = 0x1000;
        }
        piVar4--;
      }

      // set camera position and rotation for cutscene
      gGT->pushBuffer[0].pos[0] = *(short *)(cutsceneID + 0x800B749C);
      gGT->pushBuffer[0].pos[1] = *(short *)(cutsceneID + 0x800B74A0);
      gGT->pushBuffer[0].pos[2] = *(short *)(cutsceneID + 0x800B74A2);

      gGT->pushBuffer[0].rot[0] = *(short *)(cutsceneID + 0x800B74A4) + 0x800;
      gGT->pushBuffer[0].rot[1] = *(short *)(cutsceneID + 0x800B74A6);
      gGT->pushBuffer[0].rot[2] = *(short *)(cutsceneID + 0x800B74A8);

      OVR_233.cutsceneState = 4;

      // last camera variable
      // set desired brightness to normal brightness
      gGT->pushBuffer_UI.fadeFromBlack_desiredResult = 0x1000;

      // set screen to get brighter every frame
      gGT->pushBuffer_UI.fade_step = 0x400;
    }
    break;
  case 4:

    // if screen is at max brightness
    if (gGT->pushBuffer_UI.fadeFromBlack_currentValue == 0x1000)
    {
      // next stage, start playing cutscene
      OVR_233.cutsceneState = 5;
    }
    break;

  case 5:

    // if cutscene is over
    if (OVR_233.isCutsceneOver == 1)
    {
      // podium reward
      gGT->podiumRewardID = 0;

      // This thread is now dead
      t->flags = | 0x800;
    }
  }
}