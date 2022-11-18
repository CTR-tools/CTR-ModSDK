#include <common.h>

// This is not a mod,
// this tests addresses
// in common.h to see if
// we make mistakes

struct x
{
	int a,b,c,d;
};

#define TEST16(x) { (int)x, 0,0,0 }

// by aligning everything to 16 bytes,
// it makes the binary easier to read
// in hex editors like HxD

struct x y[] =
{
	TEST16(&rdata.s_warpball),

	TEST16(&data),
	TEST16(&data.s_XA_ENG_XNF),
	TEST16(&data.xaLanguagePtrs),
	TEST16(&data.ptrRenderedQuadblockDestination_forEachPlayer),
	TEST16(&data.colors),
	TEST16(&data.ptrColor),
	TEST16(&data.menuBox_optionsMenu_racingWheel),
	TEST16(&data.PtrClipBuffer),
	TEST16(&data.menuRow_advHub),
	TEST16(&data.menuBox_arcadeRace),
	TEST16(&data.s_BASCUS_94426G_Question),
	TEST16(&data.checkerFlagVariables),
	TEST16(&data.menuBox_greenLoadSave),
	TEST16(&data.menuBox_LoadProfileFromHub),
	TEST16(&data.hud_1P_P1[0]),
	TEST16(&data.menuRow_Retry_ExitToMap),
	TEST16(&data.speedometerBG_vertData),
	TEST16(&data.advCupStringIndex),
	TEST16(&data.characterIDs),
	TEST16(&data.metaPhys),
	TEST16(&data.placeholder_lastByte),

	TEST16(&sdata),
	TEST16(&sdata.s_camera),
	TEST16(&sdata.s_ghost),
	TEST16(&sdata.s_HOWL),
	TEST16(&sdata.queueReady),
	TEST16(&sdata.gGT),
	TEST16(&sdata.PtrMempack),
	TEST16(&sdata.s_token),
	TEST16(&sdata.numIconsEOR),
	TEST16(&sdata.s_NOSCRUB),
	TEST16(&sdata.useDisc),
	TEST16(&sdata.ReadFileAsyncCallbackFuncPtr),
	TEST16(&sdata.lngStrings),
	TEST16(&sdata.ptrLoadSaveObj),
	TEST16(&sdata.ptrActiveMenuBox),
	TEST16(&sdata.unk_saveGame_related),
	TEST16(&sdata.trackSelIndex),
	TEST16(&sdata.AnyPlayerTap),
	TEST16(&sdata.AnyPlayerHold),
	TEST16(&sdata.ptrRelic),
	TEST16(&sdata.ptrToken),
	TEST16(&sdata.ptrTimebox1),

	// Haven't found these on all versions,
	// but they are important so I should do that

	//TEST16(&sdata.GameProgress),
	//TEST16(&sdata.AdvProgress),
	//TEST16(&sdata.GhostRecording),

	TEST16(&sdata.queueSlots),
	TEST16(&sdata.gamepadSystem),
	TEST16(&sdata.gameTracker),
	TEST16(&sdata.gameTracker.levelID),
	TEST16(&sdata.s_bu00_BASCUS_94426_slots),
	TEST16(&sdata.mempack),
	TEST16(&sdata.numGhostProfilesSaved),

	// 926 - 0x2584
	// 1006 - 0x258C
	// 1020 - 0x2594
	TEST16(sizeof(struct GameTracker)),

	#define OFFSETOF(TYPE, ELEMENT) ((size_t)&(((TYPE *)0)->ELEMENT))
	TEST16(OFFSETOF(struct GameTracker, camera110_UI)),
	TEST16(OFFSETOF(struct Driver, BattleHUD.teamID)),
	TEST16(OFFSETOF(struct Driver, reserves)),
	TEST16(OFFSETOF(struct Driver, numTimesMaskGrab)),
	TEST16(OFFSETOF(struct Turbo, fireVisibilityCooldown))
};