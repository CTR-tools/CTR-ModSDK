#include <common.h>

void UI_ThTick_Reward(struct Thread*);
void UI_ThTick_CountPickup(struct Thread*);
void UI_ThTick_CtrLetters(struct Thread*);
void UI_ThTick_big1(struct Thread*);

void DECOMP_UI_INSTANCE_InitAll(void)
{
  struct GameTracker *gGT;
  struct Instance* crystal;
  struct Instance* token;
  u_int relicType;
  int iVar5;
  undefined2 *puVar6;
  undefined2 *puVar7;
  int i;

  gGT = sdata->gGT;
  sdata->menuReadyToPass &= 0xfffffffe;
  gGT->renderFlags |= 0x8000;
  
  relicType = gGT->gameMode1;

  // For most of the function

  // If you're not in Crystal Challenge (in adventure mode)
  if ((relicType & CRYSTAL_CHALLENGE) == 0)
  {
	// If you're in Adventure Arena
    if ((relicType & ADVENTURE_ARENA) != 0)
	{
      UI_INSTANCE_BirthWithThread(0x61,UI_ThTick_Reward,0xe,1,0,sdata->s_relic1);
      UI_INSTANCE_BirthWithThread(99,UI_ThTick_Reward,0xf,1,0,sdata->s_key1);
      UI_INSTANCE_BirthWithThread(0x62,UI_ThTick_Reward,0x10,0,0,sdata->s_trophy1);

      GAMEPROG_AdvPercent(&sdata->advProgress);
      return;
    }

	// ???
    if ((relicType & (LOADING | ADVENTURE_ARENA | MAIN_MENU)) != 0) {
      puVar7 = &DAT_800862d8;
      puVar6 = &DAT_800862c8;

    for (i = 0; i < 8; i++)
	  {
		// loop through all player structures

		// player structure + 0x482 is your rank in the race
		// 0 = 1st place, 1 = 2nd place, 2 = 3rd place, etc
        *puVar6 = gGT->drivers[i]->driverRank;

		// if more than 1 screen
        if (1 < gGT->numPlyrCurrGame) {
          *puVar7 = 5;
        }

		    puVar7 = puVar7 + 1;
        puVar6 = puVar6 + 1;
      } 

	  // If you're not in a Relic Race
      if ((relicType & RELIC_RACE) == 0) {
        return;
      }

    int relicType;
	  // The rest of this block only happens in Relic Mode

      sdata->ptrRelic = UI_INSTANCE_BirthWithThread(0x61,UI_ThTick_Reward,0xe,1,0,sdata->s_relic1);
      sdata->ptrTimebox1 = UI_INSTANCE_BirthWithThread(0x5c,UI_ThTick_CountPickup,0x13,1,0,sdata->s_timebox1);

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

	  // Level ID
    int levID = (gGT->levelID);
      
	  // int offset in table
	  int relicOffs = relicType * 4;

	  // [change for easy reading]
	  // get relic time on this track, for this relic type (sapphire, gold, platinum)
	  int relicTime = (data.RelicTime[levID+relicOffs]);

	  // [change for easy reading]
	  // store globally for HUD to access later
      i = relicTime >> 0x1f;
      sdata->relicTime_1ms= relicTime / 0xe100;
      sdata->relicTime_10ms = ((relicTime * 100) / 0x3c0) % 10;
      sdata->relicTime_1sec = ((relicTime / 6 + i >> 4) - i) % 10;
      sdata->relicTime_10sec = (relicTime / 0x2580) % 6;
      sdata->relicTime_1min = (relicTime / 0x3c0) % 10;
      return;
    }
    *(struct TileView*)0x8008d4b4 = NULL;

	// if more than 1 screen
	if (1 < gGT->numPlyrCurrGame)
	{
      *(struct TileView*)0x8008d4b4 = sdata->tileView_DecalMP;
    }
	
	// second half of pixel-LOD tileView, copy from TileView_UI
    sdata->dataLibFiller[40] = gGT->tileView_UI.matrix_ViewProj.m[0][0];
    sdata->dataLibFiller[44] = gGT->tileView_UI.matrix_ViewProj.m[0][2];
    sdata->dataLibFiller[48] = gGT->tileView_UI.matrix_ViewProj.m[1][1];
    sdata->dataLibFiller[52] = gGT->tileView_UI.matrix_ViewProj.m[2][0];
    sdata->dataLibFiller[56] = gGT->tileView_UI.matrix_ViewProj.m[2][2];
    sdata->dataLibFiller[60] = gGT->tileView_UI.matrix_ViewProj.t[0];
    sdata->dataLibFiller[64] = gGT->tileView_UI.matrix_ViewProj.t[1];
    sdata->dataLibFiller[68] = gGT->tileView_UI.matrix_ViewProj.t[2];
	
	// first half of pixel-LOD tileView, copy from TileView_UI
    sdata->dataLibFiller[0] = gGT->tileView_UI.pos[0];
    sdata->dataLibFiller[2] = gGT->tileView_UI.pos[1];
    sdata->dataLibFiller[4] = gGT->tileView_UI.pos[2];
    sdata->dataLibFiller[28] = gGT->tileView_UI.rect.x;
    sdata->dataLibFiller[30] = gGT->tileView_UI.rect.y;
    sdata->dataLibFiller[32] = gGT->tileView_UI.rect.w;
    sdata->dataLibFiller[34] = gGT->tileView_UI.rect.h;

	// pointer to OT mem
    sdata->tileView_DecalMP->ptrOT = &gGT->backBuffer->primMem;

    (u_long*)(((int)sdata->tileView_DecalMP) + 0xf8)= gGT->tileView->ptrOT;

	// create thread and Instance for "fruitdisp"
	// the function returns an enttity
    *(void*)0x8008d4b8 = UI_INSTANCE_BirthWithThread(0x37,UI_ThTick_CountPickup,3,1,*(struct TileView*)0x8008d4b4,sdata->s_fruitdisp);

    if (
			// If numPlyrCurrGame is less than 3
			(gGT->numPlyrCurrGame < 3) &&

			// If you're not in Battle Mode
			((relicType & BATTLE_MODE) == 0)
		)
	{
	  // UI_INSTANCE_BirthWithThread
      UI_INSTANCE_BirthWithThread(0x38,UI_ThTick_big1,2,0,0,sdata->s_big1);
    }

	// If you're not in Adventure Mode
    if ((relicType & ADVENTURE_MODE) == 0) {
      return;
    }
    sdata->ptrHudC = UI_INSTANCE_BirthWithThread(0x93,UI_ThTick_CtrLetters,0x12,0,0,sdata->s_hudc);
    sdata->ptrHudT = UI_INSTANCE_BirthWithThread(0x94,UI_ThTick_CtrLetters,0x12,0,0,sdata->s_hudt);
    sdata->ptrHudR = UI_INSTANCE_BirthWithThread(0x95,UI_ThTick_CtrLetters,0x12,0,0,sdata->s_hudr);
    sdata->ptrToken = UI_INSTANCE_BirthWithThread(0x7d,UI_ThTick_Reward,0x12,0,0,sdata->s_token);

    sdata->ptrHudC->flags |= 0x80;
    sdata->ptrHudT->flags |= 0x80;
    sdata->ptrHudR->flags |= 0x80;
  }

  // If you're in Crystal Challenge
  else
  {
	//Make a separate crystal for End of Race menu
    sdata->ptrMenuCrystal = UI_INSTANCE_BirthWithThread(0x60,UI_ThTick_Reward,0x11,0,0,sdata->s_crystal1);

	// Make a crystal for HUD
    sdata->ptrHudCrystal = UI_INSTANCE_BirthWithThread(0x60,UI_ThTick_Reward,0x11,0,0,sdata->s_crystal1);

	// Make a token
    sdata->ptrToken = UI_INSTANCE_BirthWithThread(0x7d,UI_ThTick_Reward,0x12,0,0,sdata->s_token);

	// make copy of hudCrystal pointer
  crystal = sdata->ptrHudCrystal;
  // make copy of Token pointer
  token = sdata->ptrToken;
  }

  // make invisible, either crystal in HUD, or letter R in HUD
  crystal->flags = crystal->flags | 0x80;

  // set Token scale (x, y, z) to zero
  token->scale[0] = 0;
  token->scale[1] = 0;
  token->scale[2] = 0;

  // make Token invisible
  token->flags |= 0x80;
  return;
}
 