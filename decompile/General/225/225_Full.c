#include <common.h>

extern struct RectMenu menuVS;
extern struct RectMenu menuBattle;

enum VsPosY
{
	VsPosY_TITLE = 0,
	VsPosY_P1,
	VsPosY_P2,
	VsPosY_P3,
	VsPosY_P4,
	VsPosY_NUM
};

// 2P, 3P, 4P
short VsPosY_Config[3*VsPosY_NUM] =
{
	0x32, 0x5a, 0x82, 0, 0,		// 2P
	0x1e, 0x46, 0x6e, 0x96, 0,	// 3P
	0xa, 0x35, 0x5b, 0x81, 0xa7	// 4P
};

void DECOMP_VB_EndEvent_DrawMenu(void)
{
  struct GameTracker *gGT;
  struct Instance *bigNum;
  struct PushBuffer* view;
  struct RectMenu *endMenu;
  char numPlyr;
  short pos[2];
  RECT box;

  short sVar1;
  int iVar2;
  u_int uVar3;
  short sVar5;
  int iVar6;
  int uVar7;
  short *psVar8;
  short sVar9;
  int iVar10;
  int iVar11;
  u_int uVar13;
  int iVar14;
  char acStack160[24];
  short asStack128[4];
  u_short uStack112;
  short sStack104;
  u_short uStack96;
  u_short uStack88;
  short sStack80;
  short sStack72;
  int iStack60;
  u_int uStack52;
  int iStack48;
  int iStack44;
  int VsConfigIndex;

  sStack104 = 0;
  uStack88 = 1;
  sStack80 = 0;

  memset(asStack128, 0, 8);

  sStack72 = 0;
  gGT = sdata->gGT;
  numPlyr = gGT->numPlyrCurrGame;
  VsConfigIndex = numPlyr-2;

  if (sdata->framesSinceRaceEnded < FPS_DOUBLE(0xf0))
  {
    sdata->framesSinceRaceEnded++;
  }

  // lng index for BATTLE
  iVar10 = 0x50;

  // if you are not in battle mode
  if ((gGT->gameMode1 & 0x20) == 0)
  {
    // lng index for VERSUS
    iVar10 = 0x14f;

    // number of battle teams
    uStack96 = numPlyr;

    uVar13 = VsPosY_Config[VsPosY_NUM*VsConfigIndex + VsPosY_TITLE];
  }
  // if you are in battle mode
  else
  {
    // number of battle teams
    uStack96 = gGT->battleSetup.numTeams;

    // if you don't have zero players
    for (iVar11 = 0; iVar11 < numPlyr; iVar11++)
    {
      // increment something based on which team each player is on
      asStack128[gGT->drivers[iVar11]->BattleHUD.teamID]++;
    }

    uVar13 = 0xd8 - ((gGT->battleSetup.numTeams + -1) * 10 + numPlyr * 0x1a + 0x28) >> 1;
  }

  // Disable drawing lines between multiplayer screens
  gGT->renderFlags &= ~(0x8000);

  RaceFlag_SetFullyOnScreen();

  if (sdata->framesSinceRaceEnded <= FPS_DOUBLE(25))
  {
    uVar7 = 0x296;
    iVar11 = sdata->framesSinceRaceEnded;
  }

  else
  {
    uVar7 = 0x180;
    iVar11 = sdata->framesSinceRaceEnded - FPS_DOUBLE(25);
  }

  // fly-in interpolation
  DECOMP_UI_Lerp2D_Linear(
	&pos[0],
	0x296, uVar13,
	uVar7, uVar13,
	iVar11, FPS_DOUBLE(5));

  iVar14 = uVar13 + 0x28;

  // "Versus" or "Battle"
  DecalFont_DrawLine(
	sdata->lngStrings[iVar10],
	pos[0], pos[1],
	1, 0xffff8000);

  // STANDINGS
  DecalFont_DrawLine(
	sdata->lngStrings[0xCA],
	pos[0], (pos[1] + 0x11),
	1, 0xffff8000);

  iVar10 = uStack96;
  iVar11 = 0;

  {
    iStack60 = iVar10;
    uStack52 = (u_int)(iVar10 < 3);
    iStack48 = FPS_DOUBLE(0x1e);
    iStack44 = FPS_DOUBLE(5);

    for (iVar11 = 0; iVar11 < iStack60; iVar11++)
    {
      sVar1 = asStack128[gGT->battleSetup.unk1dc8[iVar11]];
      sVar5 = (short)iVar14;
      if (iStack48 < sdata->framesSinceRaceEnded)
      {
        uVar7 = 0x165;
        iVar10 = (sdata->framesSinceRaceEnded - FPS_DOUBLE(25)) - iStack44;
      }
      else
      {
        uVar7 = 0x296;
        iVar10 = sdata->framesSinceRaceEnded;
      }

      // fly-in interpolation
      DECOMP_UI_Lerp2D_Linear(
		&pos[0],
		0x296, sVar5,
		uVar7, sVar5,
		iVar10, FPS_DOUBLE(5));

      sVar9 = 0;

      // If you are not in battle mode
      if ((gGT->gameMode1 & 0x20) == 0)
      {
        uStack112 = VsPosY_Config[VsPosY_NUM*VsConfigIndex + uStack88];

        // Draw character icon
        DecalHUD_DrawPolyFT4(
			gGT->ptrIcons[data.MetaDataCharacters[data.characterIDs[gGT->drivers[gGT->battleSetup.unk1dc8[iVar11]]->driverID]].iconID],

            // Position X and Position Y
            pos[0], uStack112,

            // pointer to PrimMem struct
            &gGT->backBuffer->primMem,

            // pointer to OT mem
            gGT->pushBuffer_UI.ptrOT,

            1, 0x1000);
      }

	  // if battle mode
      else
      {
        iVar10 = sVar1 * 0x1b0000;
        uStack112 = (sVar5 + (short)((iVar10 >> 0x10) - (iVar10 >> 0x1f) >> 1)) - 0xd;

        // loop through all players
        for (iVar10 = 0; iVar10 < numPlyr; iVar10++)
        {
          // player -> battleTeam == (teamID)
          if (gGT->drivers[iVar10]->BattleHUD.teamID == gGT->battleSetup.unk1dc8[iVar11])
          {
            iVar6 = sVar9;
            sVar9 = sVar9 + 1;

            DecalHUD_DrawPolyFT4(
			gGT->ptrIcons[data.MetaDataCharacters[data.characterIDs[gGT->drivers[iVar10]->driverID]].iconID],
              pos[0], sVar5 + iVar6 * 0x1b,

              // pointer to PrimMem struct
              &gGT->backBuffer->primMem,

              // pointer to OT mem
              gGT->pushBuffer_UI.ptrOT,

              1, 0x1000);
          }
        }

		iVar14 = sVar1 * 0x1b + iVar14 + 10;
      }

      uStack88 = uStack88 + 1;
      sVar1 = 2;
      if (uStack52 == 0)
      {
        sVar1 = uStack96 - 1;
      }
      iVar6 = sVar1;
      if (0 < iVar6)
      {
        for (iVar10 = 0; iVar10 < iVar6; iVar10++)
        {
          // If you are not in Battle Mode
          if ((gGT->gameMode1 & 0x20) == 0)
          {
            // get position player finished in race
            iVar2 = gGT->drivers[gGT->battleSetup.unk1dc8[iVar11]]->driverRank;
          }
          // If you are in Battle Mode
          else
          {
            // get position of the team in battle
            iVar2 = gGT->battleSetup.finishedRankOfEachTeam[gGT->battleSetup.unk1dc8[iVar11]];
          }

          uVar7 = 0x4003;
          if ((iVar10 == iVar2) &&
              (uVar7 = 0x4004,
               // odd number frames
               (gGT->timer & FPS_DOUBLE(1)) != 0))
          {
            uVar7 = 0x4003;
          }

          iVar2 = iVar10 + 1;

          // string for each player rank and count from standings (0x1e80)
          sprintf(acStack160, "%d%s-%2.02ld", iVar2,
                  sdata->lngStrings[((short *)0x800a0200)[iVar10]],
                  (gGT->standingsPoints[gGT->battleSetup.unk1dc8[iVar11] * 3 + iVar10]));

          // Draw string
          DecalFont_DrawLine(acStack160, (pos[0] + 0x79), ((uStack112 - (iVar6 * 4 + -0xd)) + iVar10 * 8), 2, uVar7);
        }
      }

      if (gGT->battleSetup.unk_afterTeams[gGT->battleSetup.unk1dc8[iVar11]] == sStack80)
      {
        sStack72 = sStack72 + 1;
      }
      else
      {
        sStack72 = 0;
      }

      sVar1 = (short)iVar11 - sStack72;
      if (sStack72 == 0)
      {
        sVar1 = (short)iVar11;
      }

      iStack48 = iStack48 + FPS_DOUBLE(5);
      iStack44 = iStack44 + FPS_DOUBLE(5);

	  sStack80 = gGT->battleSetup.unk_afterTeams[gGT->battleSetup.unk1dc8[iVar11]];
      sprintf(acStack160, "%d%s", sVar1 + 1, sdata->lngStrings[((short *)0x800a0200)[sVar1]]);

      // Draw String
      DecalFont_DrawLine(acStack160, (pos[0] - 0x24), (uStack112 + 5), 1, 0xffff8000);
    }
  }

  for (uVar13 = 0; uVar13 < numPlyr; uVar13++)
  {
    // get pointer to instance of Big Number in HUD
    bigNum = gGT->drivers[uVar13]->instBigNum;
    view = &gGT->pushBuffer[uVar13];

    // if the pointer is valid
    if (bigNum != NULL)
    {
      // clear the scale
      bigNum->scale[0] = 0;
      bigNum->scale[1] = 0;
      bigNum->scale[2] = 0;
    }

	// Winner not found
    if (sStack104 == 0)
    {
      // if this is not battle mode, get first place racer, else get battle winner
      uVar3 = ((gGT->gameMode1 & 0x20) == 0) ? gGT->driversInRaceOrder[0]->driverID : gGT->winnerIndex[0];

      if (uVar3 != uVar13)
        goto LAB_8009ff4c;

	  // === PushBuffer is the winner ===

      sStack104 = 1;

	  // default
	  #ifndef USE_NEW2P
      if (
          // If there are two players
          (numPlyr == 2) &&

          (0x100 < view->rect.w))
      {
        view->rect.w -= FPS_HALF(0xc);
        view->distanceToScreen_CURR = 0x80;
      }

	  // vertical 2P split
	  #else
      if (
          // If there are two players
          (numPlyr == 2) &&

          (0x6c < view->rect.h))
      {
        view->rect.h -= FPS_HALF(0x6);
        view->distanceToScreen_CURR = 0x80;
      }
	  #endif

      // fly-in interpolation
      DECOMP_UI_Lerp2D_Linear(
		&pos[0],
		view->rect.x, view->rect.y,
		0x14, 0xc,
		sdata->framesSinceRaceEnded, FPS_DOUBLE(25));

      box.x = pos[0] - 3;
      box.y = pos[1] - 2;
      box.w = view->rect.w + 6;
      box.h = view->rect.h + 4;

      Color color;
      color.self = sdata->battleSetup_Color_UI_1;
      DECOMP_RECTMENU_DrawOuterRect_HighLevel(&box, color, 0, gGT->backBuffer->otMem.startPlusFour);

      view->rect.x = pos[0];
      view->rect.y = pos[1];
    }

	// === Winner already found ===
    else
    {

	// === PushBuffer is not winner ===
    LAB_8009ff4c:

      if (view->rect.w > 0)
      {
        view->rect.x += FPS_HALF(5);
        view->rect.y += FPS_HALF(3);
        view->rect.w -= FPS_HALF(10);
        view->rect.h -= FPS_HALF(6);
      }

	  #ifdef USE_NEW2P
	  // this is required cause rendering is stopped
	  // if h<0, but not if w<0, and w reaches zero
	  // faster than h because of the mod
	  if (view->rect.w < 0)
	  {
        view->rect.w = 0;
        view->rect.h = 0;
	  }
	  #endif
    }
  }

  if (((sdata->menuReadyToPass & 1) == 0) && (FPS_DOUBLE(25) < sdata->framesSinceRaceEnded))
  {
    // if you're in battle mode.
    endMenu = ((gGT->gameMode1 & 0x20) == 0) ? &menuVS : &menuBattle;

    // Make Menu Box appear based on the game mode
    RECTMENU_Show(endMenu);

    sdata->menuReadyToPass |= 1;
  }
}

struct MenuRow rowsVS[5] =
{
    // Retry
    {
        .stringIndex = 4,
        .rowOnPressUp = 0,
        .rowOnPressDown = 1,
        .rowOnPressLeft = 0,
        .rowOnPressRight = 0,
    },
    // Change Level
    {
        .stringIndex = 6,
        .rowOnPressUp = 0,
        .rowOnPressDown = 2,
        .rowOnPressLeft = 1,
        .rowOnPressRight = 1,
    },
    // Change Character
    {
        .stringIndex = 5,
        .rowOnPressUp = 1,
        .rowOnPressDown = 3,
        .rowOnPressLeft = 2,
        .rowOnPressRight = 2,
    },
    // Quit
    {
        .stringIndex = 3,
        .rowOnPressUp = 2,
        .rowOnPressDown = 3,
        .rowOnPressLeft = 3,
        .rowOnPressRight = 3,
    },
    // NULL, end of menu
    {
        .stringIndex = 0xFFFF,
        .rowOnPressUp = 0,
        .rowOnPressDown = 0,
        .rowOnPressLeft = 0,
        .rowOnPressRight = 0,
    }
};

struct RectMenu menuVS =
{
    .stringIndexTitle = 0xFFFF,
    .posX_curr = 143,
    .posY_curr = 162,
    .unk1 = 0,
    .state = (0x800 | EXECUTE_FUNCPTR | USE_SMALL_FONT | CENTER_ON_COORDS), // 0xC83
    .rows = rowsVS,
    .funcPtr = DECOMP_UI_RaceEnd_MenuProc,
    .drawStyle = 4,
    // rest of variables all default zero
};

struct MenuRow rowsBattle[6] =
{
    // Retry
    {
        .stringIndex = 4,
        .rowOnPressUp = 0,
        .rowOnPressDown = 1,
        .rowOnPressLeft = 0,
        .rowOnPressRight = 0,
    },
    // Change Level
    {
        .stringIndex = 6,
        .rowOnPressUp = 0,
        .rowOnPressDown = 2,
        .rowOnPressLeft = 1,
        .rowOnPressRight = 1,
    },
    // Change Setup
    {
        .stringIndex = 10,
        .rowOnPressUp = 1,
        .rowOnPressDown = 3,
        .rowOnPressLeft = 2,
        .rowOnPressRight = 2,
    },
    // Change Character
    {
        .stringIndex = 5,
        .rowOnPressUp = 2,
        .rowOnPressDown = 4,
        .rowOnPressLeft = 3,
        .rowOnPressRight = 3,
    },
    // Quit
    {
        .stringIndex = 3,
        .rowOnPressUp = 3,
        .rowOnPressDown = 4,
        .rowOnPressLeft = 4,
        .rowOnPressRight = 4,
    },
    // NULL, end of menu
    {
        .stringIndex = 0xFFFF,
        .rowOnPressUp = 0,
        .rowOnPressDown = 0,
        .rowOnPressLeft = 0,
        .rowOnPressRight = 0,
    }
};

struct RectMenu menuBattle =
{
    .stringIndexTitle = 0xFFFF,
    .posX_curr = 143,
    .posY_curr = 166,
    .unk1 = 0,
    .state = (0x800 | EXECUTE_FUNCPTR | USE_SMALL_FONT | CENTER_ON_COORDS), // 0xC83
    .rows = rowsBattle,
    .funcPtr = DECOMP_UI_RaceEnd_MenuProc,
    .drawStyle = 4,
    // rest of variables all default zero
};