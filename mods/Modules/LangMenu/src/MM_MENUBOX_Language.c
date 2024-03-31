#include <common.h>
#include "macro.h"

char langIndex[7] =
    {
        0, // JAPANESE (no text, language glitch)
        // 2 ENGLISH - UK
        1, // ENGLISH - US
        3, // FRENCH
        4, // GERMAN
        5, // ITALIAN
        6, // SPANISH
        7  // NETHERLANDS
};

int timer;

void MM_MenuProc_Language(struct RectMenu* menu)
{
  struct GameTracker *gGT = sdata->gGT;
  char row = menu->rowSelected;

  if (menu->ptrPrevBox_InHierarchy == 0)
  {
    if (menu->unk1e == 1)
    {
      // if anyone move the menu cursor
      if (sdata->gGamepads->anyoneHeldCurr != 0)
      {
        // reset menu timer
        timer = 900;
      }

      timer--;

      // if the timer ran out,
      // automatically choose current selection (do the rest of the func)
      if (-1 < timer)
      {
        return;
      }
    }
    struct RectMenu *mainMenu = &D230.menuMainMenu;
    gGT->notFoundInCode2 = 1; // boolLangChosen
    mainMenu->state |= DISABLE_INPUT_ALLOW_FUNCPTRS;
    sdata->ptrDesiredMenu = mainMenu;
    goto LOAD_LNG;
  }

  if (
      (row > -1) &&
#if BUILD == JpnRetail
      (row < 7)
#else
      (row < 6)
#endif
  )
  {
  LOAD_LNG:
    gGT->langIndex = langIndex[row
#if BUILD != JpnRetail
                               + 1
#endif
    ];
    gGT->gameMode2 |= 0x10000000; // LANG_CHANGE
  }

  menu->unk1e = 0;
  menu->ptrPrevBox_InHierarchy->state &= ~(DRAW_NEXT_MENU_IN_HIERARCHY | ONLY_DRAW_TITLE);
};

#if BUILD == JpnRetail
struct MenuRow rowsLanguage[] =
    {
        [0] = MENU_ROW(642, 0, 1, 0, 0),
        [1] = MENU_ROW(133, 0, 2, 1, 1),
        [2] = MENU_ROW(134, 1, 3, 2, 2),
        [3] = MENU_ROW(135, 2, 4, 3, 3),
        [4] = MENU_ROW(136, 3, 5, 4, 4),
        [5] = MENU_ROW(137, 4, 6, 5, 5),
        [6] = MENU_ROW(138, 5, 6, 6, 6),
        [7] = FINALIZER_ROW};
#else
struct MenuRow rowsLanguage[] =
    {
        [0] = MENU_ROW(133, ROW_ENGLISH, ROW_FRENCH, ROW_ENGLISH, ROW_FRENCH),
        [1] = MENU_ROW(134, ROW_ENGLISH, ROW_GERMAN, ROW_ENGLISH, ROW_GERMAN),
        [2] = MENU_ROW(135, ROW_FRENCH, ROW_ITALIAN, ROW_FRENCH, ROW_ITALIAN),
        [3] = MENU_ROW(136, ROW_GERMAN, ROW_SPANISH, ROW_GERMAN, ROW_SPANISH),
        [4] = MENU_ROW(137, ROW_ITALIAN, ROW_DUTCH, ROW_ITALIAN, ROW_DUTCH),
        [5] = MENU_ROW(138, ROW_SPANISH, ROW_DUTCH, ROW_SPANISH, ROW_DUTCH),
        [6] = FINALIZER_ROW};
#endif

struct RectMenu menuLanguage =
    {
        .stringIndexTitle = -1,
        .posX_curr = 256,
        .posY_curr = 118,
        .unk1e = 1,
        .state = (CENTER_ON_COORDS | EXECUTE_FUNCPTR | 0x800),
        .rows = rowsLanguage,
        .funcPtr = MM_MenuProc_Language,
        .width = 171,
        .height = 120};

struct RectMenu *MM_menuLanguageBoot(struct GameTracker *gGT)
{
  if (!gGT->notFoundInCode2)
  {
    timer = 900;
    return &menuLanguage;
  }
  else
  {
    return &D230.menuMainMenu;
  }
};