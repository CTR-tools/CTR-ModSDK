#include <common.h>
#include "macro.h"

short difficulty[] = {0, 0x50, 0xa0, 0xf0, 0x140, 0x280};
extern struct RectMenu new_retryExitToMap;

char VehPickupItem_MaskBoolGoodGuy(struct Driver*);

void MenuProc_Difficulty(struct RectMenu* menu)
{
    MainFreeze_SafeAdvDestroy();
    struct GameTracker *gGT = sdata->gGT;
    u_int gameMode = gGT->gameMode1;
    struct RectMenu *pause = DECOMP_MainFreeze_GetMenuPtr();

    if (sdata->AnyPlayerTap & BTN_TRIANGLE)
    {
        if (!(gameMode & END_OF_RACE))
        {
            sdata->ptrDesiredMenu = DECOMP_MainFreeze_GetMenuPtr(pause);
            return;
        }
        struct RectMenu *endmenu;
        if ((gameMode & ADVENTURE_MODE) != 0)
            endmenu = &data.menuRetryExit;
        else
            #if BUILD == UsaRetail
            endmenu = (gGT->numPlyrCurrGame == 1) ? (struct RectMenu *)0x800a0b58 : (struct RectMenu *)0x800a0b84;
            #endif
            #if BUILD == EurRetail
            endmenu = (gGT->numPlyrCurrGame == 1) ? (struct RectMenu *)0x800a0f9c : (struct RectMenu *)0x800a0fc8;
            #endif
            #if BUILD == JpnRetail
            endmenu = (gGT->numPlyrCurrGame == 1) ? (struct RectMenu *)0x800a4138 : (struct RectMenu *)0x800a4164;
            #endif

        RECTMENU_Show(endmenu);
        return;
    }

    if (!(sdata->AnyPlayerTap & (BTN_CROSS | BTN_CIRCLE)))
        return;

    char validRows = (gameMode & ARCADE_MODE) ? 5 : 6;
    short row = menu->rowSelected;

    if (row >= validRows)
        return;
    #if BUILD == JpnRetail
    gGT->arcadeDifficulty = (menu->rows[0].stringIndex != 355) ? difficulty[row] : difficulty[row + 1];
    #else
    gGT->arcadeDifficulty = (menu->rows[0].stringIndex != 346) ? difficulty[row] : difficulty[row + 1];
    #endif

    if (gameMode & ADVENTURE_ARENA)
    {
        sdata->ptrDesiredMenu = pause;
        return;
    }
    
    if (gameMode & END_OF_RACE)
    {
        gGT->hudFlags &= 0xfe;
    }
    else
    {
        gGT->gameMode1 &= ~PAUSE_1;

        if (sdata->boolReplayHumanGhost || sdata->ptrGhostTapePlaying)
        {
            data.characterIDs[1] = sdata->ptrGhostTapePlaying->characterID;
        }
    }

    if (RaceFlag_IsFullyOffScreen())
        RaceFlag_BeginTransition(1);

    sdata->Loading.stage = -5;
    menu->state |= NEEDS_TO_CLOSE;
}

#if BUILD == UsaRetail

struct MenuRow rows_advDifficulty[] =
    {
        [0] = MENU_ROW(590, ROW_ADV_CLASSIC, ROW_ADV_EASY, ROW_ADV_CLASSIC, ROW_ADV_CLASSIC),
        [1] = MENU_ROW(346, ROW_ADV_CLASSIC, ROW_ADV_MEDIUM, ROW_ADV_EASY, ROW_ADV_EASY),
        [2] = MENU_ROW(347, ROW_ADV_EASY, ROW_ADV_HARD, ROW_ADV_MEDIUM, ROW_ADV_MEDIUM),
        [3] = MENU_ROW(348, ROW_ADV_MEDIUM, ROW_ADV_SUPER_HARD, ROW_ADV_HARD, ROW_ADV_HARD),
        [4] = MENU_ROW(588, ROW_ADV_HARD, ROW_ADV_ULTRA_HARD, ROW_ADV_SUPER_HARD, ROW_ADV_SUPER_HARD),
        [5] = MENU_ROW(589, ROW_ADV_SUPER_HARD, ROW_ADV_ULTRA_HARD, ROW_ADV_ULTRA_HARD, ROW_ADV_ULTRA_HARD),
        [6] = FINALIZER_ROW};


struct MenuRow rows_extraDifficulty[] =
    {
        [0] = MENU_ROW(346, ROW_EASY, ROW_MEDIUM, ROW_EASY, ROW_EASY),
        [1] = MENU_ROW(347, ROW_EASY, ROW_HARD, ROW_MEDIUM, ROW_MEDIUM),
        [2] = MENU_ROW(348, ROW_MEDIUM, ROW_SUPER_HARD, ROW_HARD, ROW_HARD),
        [3] = MENU_ROW(588, ROW_HARD, ROW_ULTRA_HARD, ROW_SUPER_HARD, ROW_SUPER_HARD),
        [4] = MENU_ROW(589, ROW_SUPER_HARD, ROW_ULTRA_HARD, ROW_ULTRA_HARD, ROW_ULTRA_HARD),
        [5] = FINALIZER_ROW};

#endif

#if BUILD == EurRetail

struct MenuRow rows_advDifficulty[] =
    {
        [0] = MENU_ROW(598, ROW_ADV_CLASSIC, ROW_ADV_EASY, ROW_ADV_CLASSIC, ROW_ADV_CLASSIC),
        [1] = MENU_ROW(346, ROW_ADV_CLASSIC, ROW_ADV_MEDIUM, ROW_ADV_EASY, ROW_ADV_EASY),
        [2] = MENU_ROW(347, ROW_ADV_EASY, ROW_ADV_HARD, ROW_ADV_MEDIUM, ROW_ADV_MEDIUM),
        [3] = MENU_ROW(348, ROW_ADV_MEDIUM, ROW_ADV_SUPER_HARD, ROW_ADV_HARD, ROW_ADV_HARD),
        [4] = MENU_ROW(596, ROW_ADV_HARD, ROW_ADV_ULTRA_HARD, ROW_ADV_SUPER_HARD, ROW_ADV_SUPER_HARD),
        [5] = MENU_ROW(597, ROW_ADV_SUPER_HARD, ROW_ADV_ULTRA_HARD, ROW_ADV_ULTRA_HARD, ROW_ADV_ULTRA_HARD),
        [6] = FINALIZER_ROW};

struct MenuRow rows_extraDifficulty[] =
    {
        [0] = MENU_ROW(346, ROW_EASY, ROW_MEDIUM, ROW_EASY, ROW_EASY),
        [1] = MENU_ROW(347, ROW_EASY, ROW_HARD, ROW_MEDIUM, ROW_MEDIUM),
        [2] = MENU_ROW(348, ROW_MEDIUM, ROW_SUPER_HARD, ROW_HARD, ROW_HARD),
        [3] = MENU_ROW(596, ROW_HARD, ROW_ULTRA_HARD, ROW_SUPER_HARD, ROW_SUPER_HARD),
        [4] = MENU_ROW(597, ROW_SUPER_HARD, ROW_ULTRA_HARD, ROW_ULTRA_HARD, ROW_ULTRA_HARD),
        [5] = FINALIZER_ROW};

#endif

#if BUILD == JpnRetail

struct MenuRow rows_advDifficulty[] =
    {
        [0] = MENU_ROW(644, ROW_ADV_CLASSIC, ROW_ADV_EASY, ROW_ADV_CLASSIC, ROW_ADV_CLASSIC),
        [1] = MENU_ROW(355, ROW_ADV_CLASSIC, ROW_ADV_MEDIUM, ROW_ADV_EASY, ROW_ADV_EASY),
        [2] = MENU_ROW(356, ROW_ADV_EASY, ROW_ADV_HARD, ROW_ADV_MEDIUM, ROW_ADV_MEDIUM),
        [3] = MENU_ROW(357, ROW_ADV_MEDIUM, ROW_ADV_SUPER_HARD, ROW_ADV_HARD, ROW_ADV_HARD),
        [4] = MENU_ROW(642, ROW_ADV_HARD, ROW_ADV_ULTRA_HARD, ROW_ADV_SUPER_HARD, ROW_ADV_SUPER_HARD),
        [5] = MENU_ROW(643, ROW_ADV_SUPER_HARD, ROW_ADV_ULTRA_HARD, ROW_ADV_ULTRA_HARD, ROW_ADV_ULTRA_HARD),
        [6] = FINALIZER_ROW};

struct MenuRow rows_extraDifficulty[] =
    {
        [0] = MENU_ROW(355, ROW_EASY, ROW_MEDIUM, ROW_EASY, ROW_EASY),
        [1] = MENU_ROW(356, ROW_EASY, ROW_HARD, ROW_MEDIUM, ROW_MEDIUM),
        [2] = MENU_ROW(357, ROW_MEDIUM, ROW_SUPER_HARD, ROW_HARD, ROW_HARD),
        [3] = MENU_ROW(642, ROW_HARD, ROW_ULTRA_HARD, ROW_SUPER_HARD, ROW_SUPER_HARD),
        [4] = MENU_ROW(643, ROW_SUPER_HARD, ROW_ULTRA_HARD, ROW_ULTRA_HARD, ROW_ULTRA_HARD),
        [5] = FINALIZER_ROW};

#endif

struct MenuRow new_advHub[] =
    {
        MENU_ROW(2, 4, 1, 0, 0),
        MENU_ROW(11, 0, 2, 1, 1),
        MENU_ROW(7, 1, 3, 2, 2),
        MENU_ROW(14, 2, 4, 3, 3),
        MENU_ROW(3, 3, 0, 4, 4),
        FINALIZER_ROW};

struct MenuRow new_advRace[] =
    {
        MENU_ROW(2, 4, 1, 0, 0),
        MENU_ROW(1, 0, 2, 1, 1),
        MENU_ROW(7, 1, 3, 2, 2),
        MENU_ROW(14, 2, 4, 3, 3),
        MENU_ROW(13, 3, 0, 4, 4),
        FINALIZER_ROW};

struct MenuRow new_arcadeRace[] =
    {
        MENU_ROW(2, 6, 1, 0, 0),
        MENU_ROW(1, 0, 2, 1, 1),
        MENU_ROW(5, 1, 3, 2, 2),
        MENU_ROW(6, 2, 4, 3, 3),
        MENU_ROW(7, 3, 5, 4, 4),
        MENU_ROW(14, 4, 6, 5, 5),
        MENU_ROW(3, 5, 0, 6, 6),
        FINALIZER_ROW};

struct RectMenu AdvHubDifficulty = {
    #if BUILD == JpnRetail
    .stringIndexTitle = 354,
    #else
    .stringIndexTitle = 345,
    #endif
    .posX_curr = 256,
    .posY_curr = 108,
    .unk1 = 0,
    .state = CENTER_ON_COORDS | ALL_PLAYERS_USE_MENU | USE_SMALL_FONT | BIG_TEXT_IN_TITLE | EXECUTE_FUNCPTR,
    .rows = rows_advDifficulty,
    .funcPtr = MenuProc_Difficulty,
    .width = 209,
    .height = 74};

struct RectMenu AdvMainFreeze_Difficulty = {
    #if BUILD == JpnRetail
    .stringIndexTitle = 354,
    #else
    .stringIndexTitle = 345,
    #endif
    .posX_curr = 256,
    .posY_curr = 108,
    .unk1 = 0,
    .state = CENTER_ON_COORDS | ALL_PLAYERS_USE_MENU | USE_SMALL_FONT | BIG_TEXT_IN_TITLE | EXECUTE_FUNCPTR,
    .rows = rows_advDifficulty,
    .funcPtr = MenuProc_Difficulty,
    .width = 209,
    .height = 74};

struct RectMenu arcadeMainFreeze_Difficulty = {
    #if BUILD == JpnRetail
    .stringIndexTitle = 354,
    #else
    .stringIndexTitle = 345,
    #endif
    .posX_curr = 256,
    .posY_curr = 108,
    .unk1 = 0,
    .state = CENTER_ON_COORDS | ALL_PLAYERS_USE_MENU | USE_SMALL_FONT | BIG_TEXT_IN_TITLE | EXECUTE_FUNCPTR,
    .rows = rows_extraDifficulty,
    .funcPtr = MenuProc_Difficulty,
    .width = 209,
    .height = 74};

void GetMenuDifficulty(struct RectMenu* menu)
{ // not optimized at all, but it saves space.
    struct GameTracker *gGT = sdata->gGT;
    u_int gamemode = gGT->gameMode1;
    if (mb == &data.menuAdvHub)
        new_advHub[1].stringIndex = (VehPickupItem_MaskBoolGoodGuy(gGT->drivers[0]) & 1) ? 11 : 12;
    if (mb == &data.menuAdvRace)
        menu->rows = (gamemode & (RELIC_RACE | CRYSTAL_CHALLENGE)) ? &data.rowsAdvRace[0] : &new_advRace[0];
    if (mb == &data.menuArcadeRace)
        menu->rows = (gamemode & TIME_TRIAL) ? &data.rowsArcadeRace[0] : &new_arcadeRace[0];
    if (mb == &data.menuRetryExit)
    {
        RECTMENU_Show(&new_retryExitToMap);
    }
}