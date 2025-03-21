#include <common.h>

void CS_Camera_ThTick_Boss(struct Thread* t)
{
  char i;

  int cutsceneID;
  short levID;

  struct Instance* inst;
  struct CutsceneObj* cs;
  struct GameTracker* gGT;

  gGT = sdata->gGT;
  levID = gGT->levelID;

  // for undecided cutscene:
  //	hub*2+0 - intro (after winning trophy)
  //	hub*2+1 - outro (after winning key)
  if (OVR_233.bossCutsceneIndex < 0)
  {
    cutsceneID = (levID - 0x19) * 2;
    
	if (gGT->podiumRewardID == 99)
      cutsceneID++;
  }
  
  else
  {
    cutsceneID = OVR_233.bossCutsceneIndex;
  }

  struct BossCutsceneData* bcd = 
	&OVR_233.bossCS[cutsceneID];

  switch (OVR_233.cutsceneState)
  {
	  
  // Start Fade-to-black
  case 0:
  case 1:
    gGT->pushBuffer_UI.fadeFromBlack_desiredResult = 0;
    gGT->pushBuffer_UI.fade_step = -0x400;
    OVR_233.cutsceneState = 2;
    break;
	
  // Wait for fade-to-black
  // Start loading process
  case 2:

    // wait for fade
    if (gGT->pushBuffer_UI.fadeFromBlack_currentValue != 0)
		break;
    
    // kill all podium "other" threads
    t = gGT->threadBuckets[OTHER].thread;
    while (t != 0)
    {
      t->flags |= 0x800;
      t = t->siblingThread;
    }

    // wait one frame, for the thread recycler to finish
    if (gGT->threadBuckets[OTHER].thread != 0)
		break;
    
    DECOMP_CS_LoadBoss(bcd);
    OVR_233.cutsceneState = 3;
    break;

  // Wait for loading callback,
  // start thread for head+body
  // start fade-to-normal
  case 3:

	// NULLPTR checks if load started
	// IS_PATCHED checks if load finished
	if (OVR_233.ptrModelBossHead == 0) break;
	if (!DRAM_IS_PATCHED(OVR_233.ptrModelBossHead)) break;

	struct Model** mArr = &OVR_233.ptrModelBossHead;
	
	gGT->modelPtr[mArr[0]->id] = mArr[0];
	gGT->modelPtr[mArr[1]->id] = mArr[1];

	struct CsThreadInitData initData;
	initData.podiumPos[0] = bcd->bossPos[0];
	initData.podiumPos[1] = bcd->bossPos[1];
	initData.podiumPos[2] = bcd->bossPos[2];
	initData.rot[0] = bcd->bossRot[0];
	initData.rot[1] = bcd->bossRot[1];
	initData.rot[2] = bcd->bossRot[2];
	initData.characterPos[0] = 0;
	initData.characterPos[1] = 0;
	initData.characterPos[2] = 0;

	// MUST go backwards,
	// Body first, sibling = 0
	// Head next, sibling = body
	t = 0;
    for (i = 1; i >= 0; i--)
    {
      t =
		CS_Thread_Init(mArr[i]->id, mArr[i], &initData, 0, t);

      inst = t->inst;
      cs = t->object;

	  // head
      if (i == 0)
      {
        CS_ScriptCmd_OpcodeAt(cs, bcd->opcode);
        cs->unk14 = 0;
		continue;
      }

      // body
      inst->scale[0] = 0x1000;
      inst->scale[1] = 0x1000;
      inst->scale[2] = 0x1000;
      cs->desiredScale = 0x1000;
    }

    // set camera position and rotation for cutscene
    gGT->pushBuffer[0].pos[0] = bcd->camPos[0];
    gGT->pushBuffer[0].pos[1] = bcd->camPos[1];
    gGT->pushBuffer[0].pos[2] = bcd->camPos[2];

    gGT->pushBuffer[0].rot[0] = bcd->camRot[0] + 0x800;
    gGT->pushBuffer[0].rot[1] = bcd->camRot[1];
    gGT->pushBuffer[0].rot[2] = bcd->camRot[2];

	// fade back in
    gGT->pushBuffer_UI.fadeFromBlack_desiredResult = 0x1000;
    gGT->pushBuffer_UI.fade_step = 0x400;
    OVR_233.cutsceneState = 4;
    break;
	
  case 4:

    // wait for fade
    if (gGT->pushBuffer_UI.fadeFromBlack_currentValue != 0x1000)
		break;
    
    OVR_233.cutsceneState = 5;
    break;

  case 5:

    // wait for cutscene to end
    if (OVR_233.isCutsceneOver != 1)
		break;
    
    gGT->podiumRewardID = 0;
    t->flags |= 0x800;
    
  }
}