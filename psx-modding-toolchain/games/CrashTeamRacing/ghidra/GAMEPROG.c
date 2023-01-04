
// called "GAMEPROG" for "Game Progress"
// no direct proof, might be "Game Tracker"
// which appeared in a string for "gGT"

// GAMEPROG_AdvPercent
void FUN_800265c0(int param_1)

{
  bool bVar1;
  undefined *puVar2;
  undefined *puVar3;
  int iVar4;
  uint uVar5;
  short sVar6;
  short sVar7;
  int iVar8;

  puVar2 = PTR_DAT_8008d2ac;

  // no gems unlocked
  sVar7 = 0;

  // no doors open
  sVar6 = 0;

  // oxide is not beaten
  iVar8 = 0;

  // all relics unlocked (this is soon overwritten)
  uVar5 = 1;

  iVar4 = 4;
  puVar3 = PTR_DAT_8008d2ac + 0x10;

  // no relics
  *(undefined4 *)(PTR_DAT_8008d2ac + 0x1e34) = 0;

  // no trophies
  *(undefined4 *)(puVar2 + 0x1e30) = 0;

  // no keys
  *(undefined4 *)(puVar2 + 0x1e38) = 0;

  // no CTR tokens
  *(undefined4 *)(puVar2 + 0x1e3c) = 0;

  do {
    *(undefined4 *)(puVar3 + 0x1e40) = 0;
    puVar2 = PTR_DAT_8008d2ac;
    iVar4 = iVar4 + -1;
    puVar3 = puVar3 + -4;
  } while (-1 < iVar4);

  // loop counter
  iVar4 = 0;

  // pointer for determining which CTR tokens are unlocked
  // Probably does more than just that though
  puVar3 = &DAT_80083a80;

  // for iVar4 = 0; iVar4 < 0x12 (18); iVar4++
  do
  {
	// If you have a Relic on this track
    if ((*(uint *)(param_1 + ((int)(iVar4 + 0x16U) >> 5) * 4) >> (iVar4 + 0x16U & 0x1f) & 1) != 0)
	{
		// Increment number of relics
      *(int *)(puVar2 + 0x1e34) = *(int *)(puVar2 + 0x1e34) + 1;
    }

	// If track is less than 16 (not slide col or Turbo Track)
    if (iVar4 < 0x10)
	{
	  // If you have a trophy on this track
      if ((*(uint *)(param_1 + ((int)(iVar4 + 6U) >> 5) * 4) >> (iVar4 + 6U & 0x1f) & 1) != 0)
	  {
		// Increment number of trophies
        *(int *)(puVar2 + 0x1e30) = *(int *)(puVar2 + 0x1e30) + 1;
      }

	  // If you have a CTR Token on this track
      if ((*(uint *)(param_1 + ((int)(iVar4 + 0x4cU) >> 5) * 4) >> (iVar4 + 0x4cU & 0x1f) & 1) != 0)
      {
		// Increment a separate counter of CTR tokens
        *(int *)(puVar2 + (int)*(short *)(puVar3 + 0x12) * 4 + 0x1e40) =
        *(int *)(puVar2 + (int)*(short *)(puVar3 + 0x12) * 4 + 0x1e40) + 1;

		// Increment number of CTR Tokens
        *(int *)(puVar2 + 0x1e3c) = *(int *)(puVar2 + 0x1e3c) + 1;
      }
    }

	// Check if any of the 4 bosses are beaten
    if ((iVar4 < 4) &&

		// If Key has been collected (0, 1, 2, 3)
       ((*(uint *)(param_1 + ((int)(iVar4 + 0x5eU) >> 5) * 4) >> (iVar4 + 0x5eU & 0x1f) & 1) != 0))
    {
	  // increment number of keys
      *(int *)(puVar2 + 0x1e38) = *(int *)(puVar2 + 0x1e38) + 1;
    }

	// Check if any of the five gems are collected
    if ((iVar4 < 5) &&
       ((*(uint *)(param_1 + ((int)(iVar4 + 0x6aU) >> 5) * 4) >> (iVar4 + 0x6aU & 0x1f) & 1) != 0))
    {
	  // increment number of gems collected
      sVar7 = sVar7 + 1;
    }

	// Check if any of the 4 purple tokens
    if ((iVar4 < 4) &&
       ((*(uint *)(param_1 + ((int)(iVar4 + 0x6fU) >> 5) * 4) >> (iVar4 + 0x6fU & 0x1f) & 1) != 0))
    {
	  // increment number of purple tokens
      sVar6 = sVar6 + 1;
      *(int *)(puVar2 + 0x1e50) = *(int *)(puVar2 + 0x1e50) + 1;
    }

	// Check if oxide was beaten twice
    if ((iVar4 < 2) &&
       ((*(uint *)(param_1 + ((int)(iVar4 + 0x73U) >> 5) * 4) >> (iVar4 + 0x73U & 0x1f) & 1) != 0))
    {
	  // If he was beaten once
      if (iVar4 == 0)
	  {
		// add 2% to completion percentage
        iVar8 = 2;
      }

	  // If he was beaten twice
      else {
        if (iVar4 == 1)
		{
		  // add 3% to completion percentage
          iVar8 = 3;
        }
      }
    }

	// increment loop counter
    iVar4 = iVar4 + 1;

	// increment pointer
    puVar3 = puVar3 + 0x18;

  } while (iVar4 < 0x12);

  // loop counter
  iVar4 = 0;

  // iVar5 is 1 before the loop starts

  // for iVar4 = 0; iVar4 < 0x12 (18); iVar4++
  do
  {
	// only continue if the previous iteration was true
    bVar1 = uVar5 != 0;

	// prepare for false
    uVar5 = 0;

	// if previous iteration was true
    if (bVar1)
	{
	  // Check if you have gold relic
	  // Unlocking platinum relics will also set the bit for gold
      uVar5 = *(uint *)(param_1 + ((int)(iVar4 + 0x28U) >> 5) * 4) >> (iVar4 + 0x28U & 0x1f) & 1;
    }

	// increment loop counter
	iVar4 = iVar4 + 1;

  } while (iVar4 < 0x12);

  // percentage of completion in adventure profile
  *(uint *)(PTR_DAT_8008d2ac + 0x1e54) =

		// add extra 1% if all relics are gold or platinum
       (uint)(uVar5 != 0) +

	   // 2% for beating oxide once
	   // 3% for beating oxide twice (after getting all relics)
       iVar8 +

	   // 2% for each relic, and 2% for each trophy

	   //		number of relics			+			number of trophies		   * 2
	   (*(int *)(PTR_DAT_8008d2ac + 0x1e34) + *(int *)(PTR_DAT_8008d2ac + 0x1e30)) * 2 +

		// 		number of keys							number of CTR tokens
		*(int *)(PTR_DAT_8008d2ac + 0x1e38) + *(int *)(PTR_DAT_8008d2ac + 0x1e3c) +

		// one percent for every purple token
		(int)sVar6 +

		// one percent for every gem
		(int)sVar7;

  return;
}


// GAMEPROG_ResetHighScores
// Load all high scores (9:59:99)
void FUN_8002689c(int param_1)

{
  int iVar1;
  short sVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  short local_40;

  local_40 = 0;

  // Load 5 high scores
  // for 2 game modes (relic + time trial)
  // on 18 tracks

  // all tracks
  // for local_40 = 0; local_40 < 0x12 (18); local_40++
  do {
    iVar8 = 0;
    iVar7 = (int)local_40 * 0x124;

	// two modes (time trial and relic)
	// for iVar8 = 0; iVar8 < 2; iVar8++
    do {
      iVar1 = (int)(short)iVar8;
      iVar3 = (int)local_40 + iVar1;
      iVar6 = 0;

	  // copy name
      strcpy();

	  iVar4 = param_1 + iVar1 * 0x90 + iVar7;
      *(short *)(iVar4 + 0x22) = (short)iVar3 + (short)(iVar3 / 0xd) * -0xd;

	  // set lap time to 9:59:99
      *(undefined4 *)(iVar4 + 0xc) = 0x8c640;

	  // five track times
	  // for iVar6 = 0; iVar6 < 5; iVar6++
      do {
        sVar2 = (short)iVar6;
        iVar5 = iVar3 + (int)sVar2 + 1;
        strcpy();

		// increment loop counter
        iVar6 = iVar6 + 1;

		iVar4 = param_1 + (int)sVar2 * 0x18 + iVar1 * 0x90 + iVar7;
        *(short *)(iVar4 + 0x3a) = (short)iVar5 + (short)(iVar5 / 0xd) * -0xd;

		// set track time to 9:59:99
        *(undefined4 *)(iVar4 + 0x24) = 0x8c640;

      } while (iVar6 * 0x10000 >> 0x10 < 5);

	  // increment loop counter
	  iVar8 = iVar8 + 1;

    } while (iVar8 * 0x10000 >> 0x10 < 2);

	// increment loop counter
	local_40 = local_40 + 1;

  } while (local_40 < 0x12);
  return;
}


// Check if ghosts are beaten on all tracks
// 0 for N Tropy Open
// 1 for N Tropy Beaten
// 2 for N Oxide Beaten
// GAMEPROG_CheckGhostsBeaten
uint FUN_80026ae4(uint param_1)
{
  bool bVar1;
  short sVar2;
  uint uVar3;
  int iVar4;

  // value to return
  uVar3 = 1;

  // loop iteration counter
  iVar4 = 0;

  // set var2 to levelID
  sVar2 = *(short *)(PTR_DAT_8008d2ac + 0x1a10);

  // loop through all 18 tracks
  // for iVar4 = 0; iVar4 < 18; iVar4++
  do {

	// change levelID to the iteration of the For-Loop
    *(int *)(PTR_DAT_8008d2ac + 0x1a10) = (int)(short)iVar4;

	// GAMEPROG_GetPtrHighScoreTrack
	FUN_80026e80();

	// only calculate uVar3 if the last iteration's
	// uVar3 was not equal to zero
	bVar1 = uVar3 != 0;

	// basically, if uVar3 is zero for one track.
	// then the function will return zero
    uVar3 = 0;

	// recalculate
	if (bVar1)
	{
	  // Check timeTrialFlags to see if a ghost has been beaten on this track.
	  // if param_1 = 1, then uVar3 is boolean of N Tropy Beaten
	  // if param_1 = 2, then uVar3 is boolean of N Oxide Beaten

      uVar3 = *(uint *)(&DAT_8008e814 +
                       ((int)(param_1 << 0x10) >> 0x15) * 4 +

							// Level ID
                       *(int *)(PTR_DAT_8008d2ac + 0x1a10) * 0x124) >> (param_1 & 0x1f) & 1;
    }

	// increment
    iVar4 = iVar4 + 1;

	// Ghidra fail,
	// while iVar4 < 0x12
  } while (iVar4 * 0x10000 >> 0x10 < 0x12);

  // set levelID back to var2
  // resets to the value it had before the loop
  *(int *)(PTR_DAT_8008d2ac + 0x1a10) = (int)sVar2;

  // GAMEPROG_GetPtrHighScoreTrack
  FUN_80026e80();

  // 0 if not beaten on all tracks,
  // 1 if beaten on all tracks
  return uVar3;
}


// GAMEPROG_NewProfile_OutsideAdv
void FUN_80026bf0(undefined4 param_1)

{
  // Wipes unlock flags
  //	characters, tracks, cups, battle

  // erase GameProgress and GameOptions
  memset(param_1,0,0x14bc);

  // GAMEPROG_ResetHighScores
  FUN_8002689c(param_1);
  return;
}


// GAMEPROG_InitFullMemcard
void FUN_80026c24(undefined2 *param_1)

{
  short sVar1;
  int iVar2;

  // erase copy of memoryCard in RAM
  memset(param_1,0,0x1600);

  // unlockables come right after four adv profiles

  // GAMEPROG_NewProfile_OutsideAdv
  // "short" increment, 0xa2 is really 0x144
  FUN_80026bf0(param_1 + 0xa2);

  iVar2 = 0;

  // CTR Header
  *param_1 = 0xffee;
  param_1[1] = 0x1600;

  // Set four adventure profiles
  // to spawn you on N Sanity Beach (1a)
  // and to unlock some Aku hints (0xffff), I think?
  do
  {
    sVar1 = (short)iVar2;
    iVar2 = iVar2 + 1;

	// "short" increment, 0x28 is really 0x50
    (param_1 + (int)sVar1 * 0x28)[0x17] = 0xffff;
    (param_1 + (int)sVar1 * 0x28)[0x19] = 0x1a;

  } while (iVar2 * 0x10000 >> 0x10 < 4);

  return;
}


// GAMEPROG_NewProfile_InsideAdv
void FUN_80026cb8(int param_1)

{
  // clear individual adventure profile
  memset(param_1,0,0x50);

  // characterID
  *(undefined2 *)(param_1 + 0x2a) = 0xffff;

  // set spawn map to N Sanity Beach
  *(undefined2 *)(param_1 + 0x2e) = 0x1a;
  return;
}


// GAMEPROG_SaveCupProgress
void FUN_80026cf4(void)

{
  int iVar1;
  uint uVar2;
  int iVar3;

  // loop counter
  iVar3 = 0;
  iVar1 = 0;

  // Loop through all 12 bits,
  // 4 cups, 3 completions

  // for iVar3 = 0; iVar3 < 0xc (12); iVar3++
  do
  {
	// bit index + 0xc (cup completion curr)
    uVar2 = (iVar1 >> 0x10) + 0xc;

	// 4 bytes of rewards (characters + tracks)
	// bits 0x18 + [C to 18]
    if (((uint)(&DAT_8008e6ec)[(int)uVar2 >> 5] >> (uVar2 & 0x1f) & 1) != 0)
	{
	  // bit index + 0x18 (cup completion prev)
      uVar2 = (iVar1 >> 0x10) + 0x18;

	  // byte index
      iVar1 = (int)uVar2 >> 5;

	  // 4 bytes of rewards (characters + tracks)
	  // bits 0x18 + [0 to C]
	  (&DAT_8008e6ec)[iVar1] = (&DAT_8008e6ec)[iVar1] | 1 << (uVar2 & 0x1f);
    }

	// increment loop counter
    iVar3 = iVar3 + 1;

	// shift up
    iVar1 = iVar3 * 0x10000;

  } while (iVar3 * 0x10000 >> 0x10 < 0xc);
  return;
}

// GAMEPROG_SyncGameAndCard
// combine progress of game instance, and memcard,
// this allows multiple memcards to combine progress
// param1 - GameProgress memcard buffer
// param2 - GameProgress sdata global buffer
void FUN_80026d7c(int param_1,int param_2)

{
  uint uVar1;
  uint uVar2;
  uint *puVar3;
  uint *puVar4;
  int iVar5;
  int iVar6;

  // GameProgress.Unlocks
  puVar4 = (uint *)(param_1 + 4);
  puVar3 = (uint *)(param_2 + 4);

  iVar5 = 0;

  // combine unlock flags for 
  // characters, tracks, scrapbook
  do
  {
    iVar5 = iVar5 + 1;

	uVar1 = *puVar3;
    uVar2 = *puVar4;

	*puVar3 = uVar1 | uVar2;
    puVar3 = puVar3 + 1;

	*puVar4 = uVar1 | uVar2;
    puVar4 = puVar4 + 1;

  } while (iVar5 * 0x10000 >> 0x10 < 2);

  // track index counter
  iVar6 = 0;

  iVar5 = 0;

  // loop through 18 tracks
  do
  {
	// high score data
    iVar5 = (iVar5 >> 0x10) * 0x124 + 0xc;

	// time trial flags
    puVar4 = (uint *)(param_1 + iVar5 + 0x120);
    puVar3 = (uint *)(param_2 + iVar5 + 0x120);

    iVar5 = 0;

	// combine flags for which ghosts
	// have been beaten, (n tropy / oxide)
	do
	{
      iVar5 = iVar5 + 1;

	  // get flags from both
      uVar1 = *puVar3;
      uVar2 = *puVar4;

	  // write combined flags
      *puVar3 = uVar1 | uVar2;
      puVar3 = puVar3 + 1;

	  // write combined flags
      *puVar4 = uVar1 | uVar2;
      puVar4 = puVar4 + 1;

    } while (iVar5 * 0x10000 < 1);

	// loop index
    iVar6 = iVar6 + 1;

	// shift up
    iVar5 = iVar6 * 0x10000;

  } while (iVar6 * 0x10000 >> 0x10 < 0x12);
  return;
}


// GAMEPROG_NewGame_OnBoot
void FUN_80026e48(void)

{
  // GAMEPROG_NewProfile_OutsideAdv
  FUN_80026bf0(&DAT_8008e6e8);

  // GAMEPROG_NewProfile_InsideAdv
  FUN_80026cb8(&DAT_8008fba4);

  // GAMEPROG_GetPtrHighScoreTrack
  FUN_80026e80();
  return;
}


// GAMEPROG_GetPtrHighScoreTrack
void FUN_80026e80(void)

{
  // Calculates pointer to the array of 6 highScoreEntry structs,
  // for your given track, and given mode (time trial or relic)

  DAT_8008d738 = &DAT_8008e6f4 +

				 // If you're in a Relic Race    * 0x24
                 (uint)((*(uint *)PTR_DAT_8008d2ac & 0x4000000) != 0) * 0x24 +

				 // Level ID     * 0x49
                 *(int *)(PTR_DAT_8008d2ac + 0x1a10) * 0x49;
  return;
}
