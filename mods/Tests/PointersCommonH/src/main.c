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
	TEST16(&data.menuRacingWheelConfig),
	TEST16(&data.PtrClipBuffer),
	TEST16(&data.rowsAdvHub),
	TEST16(&data.menuArcadeRace),
	TEST16(&data.s_BASCUS_94426G_Question),
	TEST16(&data.checkerFlagVariables),
	TEST16(&data.menuGreenLoadSave),
	TEST16(&data.menuQueueLoadHub),
	TEST16(&data.hud_1P_P1[0]),
	TEST16(&data.rowsRetryExit),
	TEST16(&data.speedometerBG_vertData),
	TEST16(&data.advCupStringIndex),
	TEST16(&data.characterIDs),
	TEST16(&data.metaPhys),
	//TEST16(&data.placeholder_lastByte),

	TEST16(&sdata_static),
	TEST16(&sdata_static.s_camera),
	TEST16(&sdata_static.s_ghost),
	TEST16(&sdata_static.s_HOWL),
	TEST16(&sdata_static.queueReady),
	TEST16(&sdata_static.gGT),
	TEST16(&sdata_static.PtrMempack),
	TEST16(&sdata_static.s_token),
	TEST16(&sdata_static.numIconsEOR),
	TEST16(&sdata_static.s_NOSCRUB),
	TEST16(&sdata_static.boolUseDisc),
	TEST16(&sdata_static.ReadFileAsyncCallbackFuncPtr),
	TEST16(&sdata_static.lngStrings),
	TEST16(&sdata_static.ptrLoadSaveObj),
	TEST16(&sdata_static.ptrActiveMenu),
	TEST16(&sdata_static.unk_saveGame_related),
	TEST16(&sdata_static.trackSelBackup),
	TEST16(&sdata_static.AnyPlayerTap),
	TEST16(&sdata_static.AnyPlayerHold),
	TEST16(&sdata_static.ptrRelic),
	TEST16(&sdata_static.ptrToken),
	TEST16(&sdata_static.ptrTimebox1),

	// Haven't found these on all versions,
	// but they are important so I should do that

	//TEST16(&sdata_static.GameProgress),
	//TEST16(&sdata_static.AdvProgress),
	//TEST16(&sdata_static.GhostRecording),

	TEST16(&sdata_static.queueSlots),
	TEST16(&sdata_static.gamepadSystem),
	TEST16(&sdata_static.gameTracker),
	TEST16(&sdata_static.gameTracker.levelID),
	TEST16(&sdata_static.s_bu00_BASCUS_94426_slots),
	TEST16(&sdata_static.mempack),
	TEST16(&sdata_static.numGhostProfilesSaved),

	TEST16(&sdata_static.GhostRecording.boostCooldown1E),

	// 926 - 0x2584
	// 1006 - 0x258C
	// 1020 - 0x2594
	TEST16(sizeof(struct GameTracker)),

	TEST16(OFFSETOF(struct GameTracker, pushBuffer_UI)),
	TEST16(OFFSETOF(struct Driver, BattleHUD.teamID)),
	TEST16(OFFSETOF(struct Driver, reserves)),
	TEST16(OFFSETOF(struct Driver, numTimesMaskGrab)),
	TEST16(OFFSETOF(struct Turbo, fireVisibilityCooldown))
};