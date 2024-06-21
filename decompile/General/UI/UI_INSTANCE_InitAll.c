#include <common.h>

void DECOMP_UI_INSTANCE_InitAll(void)
{
  struct GameTracker *gGT;
  struct Instance* crystal;
  struct Instance* token;
  u_int gameMode1;
  u_int relicType;
  int iVar5;

  #if 0
  undefined2 *puVar6;
  undefined2 *puVar7;
  #endif

  int i;

  gGT = sdata->gGT;
  sdata->menuReadyToPass &= 0xfffffffe;
  gGT->renderFlags |= 0x8000;

  gameMode1 = gGT->gameMode1;

  // For most of the function

  // If you're not in Crystal Challenge (in adventure mode)
  if ((gameMode1 & CRYSTAL_CHALLENGE) == 0)
  {
	// If you're in Adventure Arena
    if ((gameMode1 & ADVENTURE_ARENA) != 0)
	{
	  #ifdef USE_HIGHMP
	  if(gGT->numPlyrCurrGame != 1)
		  return;
	  #endif

      DECOMP_UI_INSTANCE_BirthWithThread(0x61,	DECOMP_UI_ThTick_Reward,0xe,1,0,/*sdata->s_relic1*/0);
      DECOMP_UI_INSTANCE_BirthWithThread(99,	DECOMP_UI_ThTick_Reward,0xf,1,0,/*sdata->s_key1*/0);
      DECOMP_UI_INSTANCE_BirthWithThread(0x62,	DECOMP_UI_ThTick_Reward,0x10,0,0,/*sdata->s_trophy1*/0);

	  #ifndef REBUILD_PS1
      GAMEPROG_AdvPercent(&sdata->advProgress);
      #endif

	  return;
    }

    if ((gameMode1 & (RELIC_RACE | ADVENTURE_ARENA | TIME_TRIAL)) != 0)
	{

// Mistake? Why would this happen if there's no icons in these modes?
#if 0
	  for (i = 0; i < 8; i++)
	  {
        data.rankIconsCurr[i] = gGT->drivers[i]->driverRank;

		// if more than 1 screen
        if (1 < gGT->numPlyrCurrGame) {
          data.rankIconsTransitionTimer[i] = 5;
        }
	  }
#endif

	  // If you're not in a Relic Race
      if ((gameMode1 & RELIC_RACE) == 0) {
        return;
      }

	  // The rest of this block only happens in Relic Mode
      sdata->ptrRelic = 	DECOMP_UI_INSTANCE_BirthWithThread(0x61,DECOMP_UI_ThTick_Reward, 0xe,1,0,/*sdata->s_relic1*/0);
      sdata->ptrTimebox1 = 	DECOMP_UI_INSTANCE_BirthWithThread(0x5c,DECOMP_UI_ThTick_CountPickup, 0x13,1,0,/*sdata->s_timebox1*/0);

	  // if instance
      if (sdata->ptrRelic != 0)
	  {
		// set scale to zero
        sdata->ptrRelic->scale[0] = 0;
        sdata->ptrRelic->scale[1] = 0;
        sdata->ptrRelic->scale[2] = 0;
      }

	  // Get Relic Time to put in HUD
	  if(
			// no platinum and no gold
			(CHECK_ADV_BIT(sdata->advProgress.rewards, (gGT->levelID + 0x3a)) == 0) &&
			(CHECK_ADV_BIT(sdata->advProgress.rewards, (gGT->levelID + 0x28)) == 0)
		)
	  {
		  // 0 if sapphire not unlocked, (show sapphire)
		  // 1 if sapphire is unlocked (show gold)
		  relicType = CHECK_ADV_BIT(sdata->advProgress.rewards, (gGT->levelID + 0x16));
	  }

	  // if unlocked gold or unlocked platinum
      else
	  {
		// put platinum time on screen
        relicType = 2;
      }

	  // get relic time on this track, for this relic type (sapphire, gold, platinum)
	  unsigned int relicTime = data.RelicTime[gGT->levelID*3 + relicType];

	  // store globally for HUD to access later
      sdata->relicTime_1min = relicTime / 0xe100;
      sdata->relicTime_10sec = (relicTime / 0x2580) % 6;
      sdata->relicTime_1sec = (relicTime / 0x3c0) % 10;
      sdata->relicTime_10ms = ((relicTime * 100) / 0x3c0) % 10;
      sdata->relicTime_1ms = ((relicTime * 1000) / 0x3c0) % 10;

      return;
    }

	// used for multiplayer wumpa
    sdata->ptrPushBufferUI = NULL;
	if (1 < gGT->numPlyrCurrGame)
	{
      sdata->ptrPushBufferUI = &sdata->pushBuffer_DecalMP;
    }

// skipping pixelLOD
#if 0
	// second half of pixel-LOD pushBuffer, copy from PushBuffer_UI
    sdata->dataLibFiller[40] = gGT->pushBuffer_UI.matrix_ViewProj.m[0][0];
    sdata->dataLibFiller[44] = gGT->pushBuffer_UI.matrix_ViewProj.m[0][2];
    sdata->dataLibFiller[48] = gGT->pushBuffer_UI.matrix_ViewProj.m[1][1];
    sdata->dataLibFiller[52] = gGT->pushBuffer_UI.matrix_ViewProj.m[2][0];
    sdata->dataLibFiller[56] = gGT->pushBuffer_UI.matrix_ViewProj.m[2][2];
    sdata->dataLibFiller[60] = gGT->pushBuffer_UI.matrix_ViewProj.t[0];
    sdata->dataLibFiller[64] = gGT->pushBuffer_UI.matrix_ViewProj.t[1];
    sdata->dataLibFiller[68] = gGT->pushBuffer_UI.matrix_ViewProj.t[2];

	// first half of pixel-LOD pushBuffer, copy from PushBuffer_UI
    sdata->dataLibFiller[0] = gGT->pushBuffer_UI.pos[0];
    sdata->dataLibFiller[2] = gGT->pushBuffer_UI.pos[1];
    sdata->dataLibFiller[4] = gGT->pushBuffer_UI.pos[2];
    sdata->dataLibFiller[28] = gGT->pushBuffer_UI.rect.x;
    sdata->dataLibFiller[30] = gGT->pushBuffer_UI.rect.y;
    sdata->dataLibFiller[32] = gGT->pushBuffer_UI.rect.w;
    sdata->dataLibFiller[34] = gGT->pushBuffer_UI.rect.h;
#endif

    sdata->pushBuffer_DecalMP.ptrOT = gGT->pushBuffer->ptrOT;
    sdata->pushBuffer_DecalMP.distanceToScreen_PREV = gGT->pushBuffer->distanceToScreen_PREV;

	// Replace PushBufferUI with regular PushBuffer,
	// workaround for decompile, and it just looks better
    sdata->ptrFruitDisp =
		DECOMP_UI_INSTANCE_BirthWithThread(0x37,DECOMP_UI_ThTick_CountPickup,3,1,/*sdata->ptrPushBufferUI*/0,/*sdata->s_fruitdisp*/0);

    if (
			(gGT->numPlyrCurrGame < 3) &&

			// If you're not in Battle Mode
			((gameMode1 & BATTLE_MODE) == 0)
		)
	  {
      #ifndef USE_ONLINE
      DECOMP_UI_INSTANCE_BirthWithThread(0x38,DECOMP_UI_ThTick_big1,2,0,0,/*sdata->s_big1*/0);
      #endif
    }

	// If you're not in Adventure Mode
    if ((gameMode1 & ADVENTURE_MODE) == 0) {
      return;
    }

	#ifndef USE_ONLINE
    sdata->ptrHudC = DECOMP_UI_INSTANCE_BirthWithThread(0x93,DECOMP_UI_ThTick_CtrLetters,0x12,0,0,/*sdata->s_hudc*/0);
    sdata->ptrHudT = DECOMP_UI_INSTANCE_BirthWithThread(0x94,DECOMP_UI_ThTick_CtrLetters,0x12,0,0,/*sdata->s_hudt*/0);
    sdata->ptrHudR = DECOMP_UI_INSTANCE_BirthWithThread(0x95,DECOMP_UI_ThTick_CtrLetters,0x12,0,0,/*sdata->s_hudr*/0);
	#endif

#ifdef REBUILD_PC
    if (sdata->ptrHudC == 0)
        return;
#endif

    sdata->ptrHudC->flags |= 0x80;
    sdata->ptrHudT->flags |= 0x80;
    sdata->ptrHudR->flags |= 0x80;
  }

  // If you're in Crystal Challenge
  else
  {
    sdata->ptrMenuCrystal = DECOMP_UI_INSTANCE_BirthWithThread(0x60,DECOMP_UI_ThTick_Reward,0x11,0,0,/*sdata->s_crystal1*/0);
	sdata->ptrHudCrystal = DECOMP_UI_INSTANCE_BirthWithThread(0x60,DECOMP_UI_ThTick_Reward,0x11,0,0,/*sdata->s_crystal1*/0);
	sdata->ptrHudCrystal->flags |= 0x80;
  }

  // Make a token
  sdata->ptrToken = DECOMP_UI_INSTANCE_BirthWithThread(0x7d,DECOMP_UI_ThTick_Reward,0x12,0,0,/*sdata->s_token*/0);

  // make copy of Token pointer
  token = sdata->ptrToken;

  // set Token scale (x, y, z) to zero
  token->scale[0] = 0;
  token->scale[1] = 0;
  token->scale[2] = 0;

  // make Token invisible
  token->flags |= 0x80;
  return;
}
