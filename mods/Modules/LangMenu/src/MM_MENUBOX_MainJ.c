#include <common.h>

void MM_MENUBOX_Main(struct MenuBox *mb)
{
  struct GameTracker *gGT = sdata->gGT;
  int timer;
  u_int state;
  short choose;
  struct MenuBox *nextBox;

  if ((sdata->gameProgress.unlocks[1] & 0x10) != 0)
  {
    D230.menubox_mainMenu.rows = D230.rows_mainMenu_WithScrapbook;
  }

  MM_ParseCheatCodes();
  MM_ToggleRows_Difficulty();
  MM_ToggleRows_PlayerCount();

  if (mb->unk1e == 1)
  {
    MM_Title_MenuUpdate();

    if (((D230.MM_State == 1) && (D230.titleObj != 0)) && (190 < D230.timerInTitle))
    {
      DecalFont_DrawLineOT(sdata->lngStrings[0x250], 0x11d, 0xb8, 2, 0,
                           gGT->backBuffer->otMem.startPlusFour[3]);
    }

    if ((D230.menubox_mainMenu.state & 0x10) == 0)
    {
      if (D230.MM_State != 2)
      {
        gGT->numPlyrNextGame = 1;
      }
      if (sdata->gGamepads->anyoneHeldCurr == 0)
      {
        timer = gGT->demoCountdownTimer + -1;
        gGT->demoCountdownTimer = timer;
        if (timer < 1)
        {
          D230.MM_State = 2;
          D230.desiredMenu = 4;
        }
      }
      else
      {
        gGT->demoCountdownTimer = 900;
      }
    }
  }

  MM_Title_Init();
  if ((mb->state & 0x10) != 0)
  {
    D230.timerInTitle = 1000;
  }

  if ((mb->state & 0x400) == 0)
  {
    return;
  }

  if (D230.titleObj != 0)
  {
    D230.titleObj->cameraPosOffset[2] = 0;
  }

  if (mb->unk1e != 0)
  {
    return;
  }

  if (mb->rowSelected < 0)
  {
    return;
  }

  gGT->gameMode1 &= 0xefa5ffdf;
  gGT->gameMode2 &= 0xffffffef;

  mb->state |= 4;
  gGT->numLaps = 3;

  choose = mb->rows[mb->rowSelected].stringIndex;

  if (choose == 0x4f)
  {
    if ((gGT->gameMode2 & 0x800000) != 0)
    {
      gGT->numLaps = 1;
    }
    state = mb->state;
    nextBox = &D230.menubox_raceType;
  }
  else
  {
    if (0x4f < choose)
    {
      if (choose == 0x51)
      {
        D230.desiredMenu = 3;
      }
      else
      {
        if (choose < 0x51)
        {
          D230.characterSelect_transitionState = 2;
          gGT->gameMode1 |= 0x20;
          state = mb->state;
          nextBox = &D230.menubox_players2P3P4P;
          goto LAB_OVR_230__800b0b24;
        }
        if (choose != 0x240)
        {
          return;
        }
        D230.desiredMenu = 5;
      }
      D230.MM_State = 2;
      return;
    }
    if (choose == 0x4d)
    {
      D230.MM_State = 2;
      D230.desiredMenu = 2;
      gGT->numPlyrNextGame = 1;
      gGT->gameMode1 |= 0x20000;
      gGT->gameMode2 &= 0xffaef1ff;
      return;
    }
    if (choose < 0x4e)
    {
      if (choose != 0x4c)
      {
        return;
      }
      gGT->gameMode1 |= 0x80000;
      gGT->gameMode2 &= 0xffaef1ff;
      state = mb->state;
      nextBox = &D230.menubox_adventure;
    }
    else
    {
      if ((gGT->gameMode2 & 0x800000) != 0)
      {
        gGT->numLaps = 1;
      }
      gGT->gameMode1 |= 0x400000;
      state = mb->state;
      nextBox = &D230.menubox_raceType;
    }
  }
LAB_OVR_230__800b0b24:
  mb->ptrNextBox_InHierarchy = nextBox;
  mb->state = state | 0x10;
}
