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

	  //is ignoring the return value of these calls intentional?
      DECOMP_UI_INSTANCE_BirthWithThread(0x61,	(int)DECOMP_UI_ThTick_Reward,0xe,1,0,/*sdata->s_relic1*/0);
      DECOMP_UI_INSTANCE_BirthWithThread(99,	(int)DECOMP_UI_ThTick_Reward,0xf,1,0,/*sdata->s_key1*/0);
      DECOMP_UI_INSTANCE_BirthWithThread(0x62,	(int)DECOMP_UI_ThTick_Reward,0x10,0,0,/*sdata->s_trophy1*/0);

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
      sdata->ptrRelic = 	DECOMP_UI_INSTANCE_BirthWithThread(0x61,(int)DECOMP_UI_ThTick_Reward, 0xe,1,0,/*sdata->s_relic1*/0);
      sdata->ptrTimebox1 = 	DECOMP_UI_INSTANCE_BirthWithThread(0x5c,(int)DECOMP_UI_ThTick_CountPickup, 0x13,1,0,/*sdata->s_timebox1*/0);

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
			(CHECK_ADV_BIT(sdata->advProgress.rewards, (gGT->levelID + PRIZE_RELIC_RACE + PRIZE_GOLD)) == 0) &&
			(CHECK_ADV_BIT(sdata->advProgress.rewards, (gGT->levelID + PRIZE_RELIC_RACE + PRIZE_PLATINUM)) == 0)
		)
	  {
		  // 0 if sapphire not unlocked, (show sapphire)
		  // 1 if sapphire is unlocked (show gold)
		  relicType = CHECK_ADV_BIT(sdata->advProgress.rewards, (gGT->levelID + (PRIZE_RELIC_RACE + PRIZE_SAPPHIRE)));
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
    sdata->ptrPushBufferUI = (int)NULL;
	
#ifdef USE_DECALMP // OG game
	if (1 < gGT->numPlyrCurrGame)
	{
	  struct PushBuffer* pb = &sdata->pushBuffer_DecalMP;
	  struct PushBuffer* ui = &gGT->pushBuffer_UI;
	  
      sdata->ptrPushBufferUI = (int)pb;
    
	  // second half of pixel-LOD pushBuffer, copy from PushBuffer_UI
	  *(int*)&pb->matrix_ViewProj.m[0][0] = *(int*)&ui->matrix_ViewProj.m[0][0];
	  *(int*)&pb->matrix_ViewProj.m[0][2] = *(int*)&ui->matrix_ViewProj.m[0][2];
	  *(int*)&pb->matrix_ViewProj.m[1][1] = *(int*)&ui->matrix_ViewProj.m[1][1];
	  *(int*)&pb->matrix_ViewProj.m[2][0] = *(int*)&ui->matrix_ViewProj.m[2][0];
	  *(int*)&pb->matrix_ViewProj.m[2][2] = *(int*)&ui->matrix_ViewProj.m[2][2];
	  pb->matrix_ViewProjmatrix.t.x = ui->matrix_ViewProj.t.x;
	  pb->matrix_ViewProj.t.y = ui->matrix_ViewProj.t.y;
	  pb->matrix_ViewProj.t.z = ui->matrix_ViewProj.t.z;
	  
	  // first half of pixel-LOD pushBuffer, copy from PushBuffer_UI
	  pb->pos[0] = ui->pos[0];
	  pb->pos[1] = ui->pos[1];
	  pb->pos[2] = ui->pos[2];
	  pb->rect.x = ui->rect.x;
	  pb->rect.y = ui->rect.y;
	  pb->rect.w = ui->rect.w;
	  pb->rect.h = ui->rect.h;
	  
	  pb->ptrOT = ui->ptrOT;
	  pb->distanceToScreen_PREV = ui->distanceToScreen_PREV;
	}
#endif

    sdata->ptrFruitDisp =
		(int) DECOMP_UI_INSTANCE_BirthWithThread(0x37,(int)DECOMP_UI_ThTick_CountPickup,3,1,sdata->ptrPushBufferUI,/*sdata->s_fruitdisp*/0);

    if (
			(gGT->numPlyrCurrGame < 3) &&

			// If you're not in Battle Mode
			((gameMode1 & BATTLE_MODE) == 0)
		)
	  {
      #ifndef USE_ONLINE
      DECOMP_UI_INSTANCE_BirthWithThread(0x38,(int)DECOMP_UI_ThTick_big1,2,0,0,/*sdata->s_big1*/0);
      #endif
    }

	// If you're not in Adventure Mode
    if ((gameMode1 & ADVENTURE_MODE) == 0) {
      return;
    }

	#ifndef USE_ONLINE
    sdata->ptrHudC = DECOMP_UI_INSTANCE_BirthWithThread(0x93,(int)DECOMP_UI_ThTick_CtrLetters,0x12,0,0,/*sdata->s_hudc*/0);
    sdata->ptrHudT = DECOMP_UI_INSTANCE_BirthWithThread(0x94,(int)DECOMP_UI_ThTick_CtrLetters,0x12,0,0,/*sdata->s_hudt*/0);
    sdata->ptrHudR = DECOMP_UI_INSTANCE_BirthWithThread(0x95,(int)DECOMP_UI_ThTick_CtrLetters,0x12,0,0,/*sdata->s_hudr*/0);
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
    sdata->ptrMenuCrystal = DECOMP_UI_INSTANCE_BirthWithThread(0x60,(int)DECOMP_UI_ThTick_Reward,0x11,0,0,/*sdata->s_crystal1*/0);
	sdata->ptrHudCrystal = DECOMP_UI_INSTANCE_BirthWithThread(0x60,(int)DECOMP_UI_ThTick_Reward,0x11,0,0,/*sdata->s_crystal1*/0);
	sdata->ptrHudCrystal->flags |= 0x80;
  }

  // Make a token
  sdata->ptrToken = DECOMP_UI_INSTANCE_BirthWithThread(0x7d,(int)DECOMP_UI_ThTick_Reward,0x12,0,0,/*sdata->s_token*/0);

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
