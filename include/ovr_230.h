enum TransitionState
{
	ENTERING_MENU,
	IN_MENU,
	EXITING_MENU,
};

// MainMenu
struct Title
{
	// 0x0
	struct Thread *t;

	// 0x4
	struct Instance *i[6];

	// 0x1c
	short cameraPosOffset[3];

	// 0x22
	short UnusedPadding;

	// 0x24 -- size of struct
};

// array at 0x800b53b0
struct MainMenu_LevelRow
{
	// 0 - dingo canyon
	// 3 - crash cove
	// etc
	short levID;

// NTSC-J also has this, 
// but changing it now without proper refactor will break pointer compiles
#if BUILD >= EurRetail
	// Do not represent AI Difficulty
	// Number of Wumpas drawn representing levels of difficulty on NTSC-J
	// Left unused on PAL
	short difficulty_level;
#endif

	// texture that shows before video plays
	short videoThumbnail;

	// which black+white map draws
	short mapTextureID;

	// 0xFFFF for unlock by default
	// otherwise has a flag for what is needed,
	// 0xFFFE means "only show in 1P mode" (oxide station)
	short unlock;

#if BUILD >= EurRetail
	short unlock_padding;
#endif

	// changes which video of level plays
	int videoID;

	// how long video plays before looping
	int videoLength;

	// Struct is 16 bytes large in NTSC-U, and 20 bytes in PAL & NTSC-J
	// this structure is now complete
};

struct CharacterSelectMeta
{
	// 0x0
	short posX;
	short posY;

	// 0x4
	// up, down, left, right
	// must be array, needs enum,
	// see MM_Characters_GetNextDriver,
	// which means MenuRow needs the same
	char indexNext[4];

	// 0x8
	short characterID;
	u_short unlockFlags;

	// 0xC -- size
};

struct TransitionMeta
{
	short distX;
	short distY;

	// change when each one starts to move
	short headStart;

	short currX;
	short currY;

	// 0xA -- size
};

// 800ab9f0 - UsaRetail
// 800abe04 - EurRetail
// 800aef2c - JpnRetail
struct OverlayRDATA_230
{
	// (tag given by compiler, meaningless to game)
	// do not compile this "tag" in the struct when we're actually building the overlay
	int overlayTag;

	// 800ab9f4
	void *jmpPtrs_Title_MenuUpdate[6];

	// 800aba0c - UsaRetail
	// 800abe20 - EurRetail
	// 800aef48 - JpnRetail
	// "title"
	char s_title[8];

	// 800aba14 - UsaRetail
	// 800abe28 - EurRetail
	// 800aef50 - JpnRetail
	// 0,1,2,3,4,5,6,7
	int characterID_default[2];

	// strings for the player numbers in the character select screen
	//
	// 800abe30 - EurRetail
	// 800aef58 - JpnRetail

	// "4"
	char s_4[4];
	// "3"
	char s_3[4];
	// "2"
	char s_2[4];
	// "1"
	char s_1[4];

	// 800aba28
	char jmpPtrs_Characters_MenuProc[0x18];

	// 800aba44 - UsaRetail
	// 800abe58 - EurRetail
	// 800aef80 - JpnRetail
	char s_loaded_ghost_data[0x18];

	// 800aba5c
	char jmpPtrs_Battle_MenuProc[0x30];

	// 800aba88 - UsaRetail
	// 800abe9c - EurRetail
	// 800aefc4 - JpnRetail
	// " test.str 1"
	char s_teststr1[12];
};

// 800b44e4 - UsaRetail
// 800b4c4c - EurRetail
// 800b7f68 - JpnRetail
struct OverlayDATA_230
{
	// =========== Main Menu CONST =============

	// 800b44e4 - UsaRetail
	// 800b4c4c - EurRetail
	// 800b7f68 - JpnRetail
#if BUILD == EurRetail
	struct MenuRow rowsMainMenuBasic[8];
#else
	struct MenuRow rowsMainMenuBasic[7];
	char padding800b450E[2];
#endif

	// 800b4510 - UsaRetail
	// 800b4c7c - EurRetail
	// 800b7f94 - JpnRetail
#if BUILD == EurRetail
	struct MenuRow rowsMainMenuWithScrapbook[9];
	char padding800b4cb2[2];
#else
	struct MenuRow rowsMainMenuWithScrapbook[8];
#endif

	// 800b4540 - UsaRetail
	// 800b4cb4 - EurRetail
	// 800b7fc4 - JpnRetail
	struct RectMenu menuMainMenu;

	// 800b456c - UsaRetail
	// 800b4ce0 - EurRetail
	// 800b7ff0 - JpnRetail
	struct MenuRow rowsPlayers1P2P[3];

// ????
#if (BUILD == EurRetail) || (BUILD == UsaRetail)
	char padding800b4cf2[2];
#endif

	// 800b4580 - UsaRetail
	// 800b4cf4 - EurRetail
	// 800b7ffc - JpnRetail
	struct RectMenu menuPlayers1P2P;

	// 800b45ac - UsaRetail
	// 800b4d20 - EurRetail
	// 800b8030 - JpnRetail
	struct MenuRow rowsPlayers2P3P4P[4];

	// 800b45c4 - UsaRetail
	// 800b4d38 - EurRetail
	// 800b8042 - JpnRetail
	struct RectMenu menuPlayers2P3P4P;

	// 800b45f0 - UsaRetail
	// 800b4d64 - EurRetail
	// 800b8074 - JpnRetail
	struct MenuRow rowsDifficulty[4];

	// 800b4608 - UsaRetail
	// 800b4d7c - EurRetail
	// 800b808c - JpnRetail
	struct RectMenu menuDifficulty;

	// 800b4634 - UsaRetail
	// 800b4da8 - EurRetail
	// 800b80b8 - JpnRetail
	struct MenuRow rowsRaceType[3];

#if (BUILD == EurRetail) || (BUILD == UsaRetail)
	char padding800b4dba[2];
#endif

	// 800b4648 - UsaRetail
	// 800b4dbc - EurRetail
	// 800b80cc - JpnRetail
	struct RectMenu menuRaceType;

	// 800b4674 - UsaRetail
	// 800b4de8 - EurRetail
	// 800b80f8 - JpnRetail
	struct MenuRow rowsAdventure[3];

// ???
#if (BUILD == EurRetail) || (BUILD == UsaRetail)
	char padding800b4dfa[2];
#endif

	// 800b4688 - UsaRetail
	// 800b4dfc - EurRetail
	// 800b810c - JpnRetail
	struct RectMenu menuAdventure;

#if BUILD == EurRetail
	// 800b4e28
	short langIndex[6];

	// 800b4e34
	struct MenuRow rowsLanguage[7];

	char padding800b4e5e[2];

	// 800b4e60
	struct RectMenu menuLanguage;
#endif

	// 800b46b4 - UsaRetail
	// 800b4e8c - EurRetail
	// 800b8138 - JpnRetail
	struct RectMenu menuCharacterSelect;

	// 800b46e0 - UsaRetail
	// 800b4eb8 - EurRetail
	// 800b8164 - JpnRetail
	struct RectMenu menuTrackSelect;

	// 800b470c - UsaRetail
	// 800b4ee4 - EurRetail
	// 800b8190 - JpnRetail
	struct MenuRow rowsCupSelect[5];

// ????
#if (BUILD == EurRetail) || (BUILD == UsaRetail)
	char padding800b4f02[2];
#endif

	// 800b472c - UsaRetail
	// 800b4f04 - EurRetail
	// 800b81b0 - JpnRetail
	struct RectMenu menuCupSelect;

	// 800b4758 - UsaRetail
	// 800b4f30 - EurRetail
	// 800b81dc - JpnRetail
	struct RectMenu menuBattleWeapons;

	// 800b4784 - UsaRetail
	// 800b4f5c - EurRetail
	// 800b8208 - JpnRetail
	struct RectMenu menuHighScores;

	// 800b47b0 - UsaRetail
	// 800b4f88 - EurRetail
	// 800b8234 - JpnRetail
	struct RectMenu menuScrapbook;

	// 800b47dc - UsaRetail
	// 800b4fb4 - EurRetail
	// 800b8260 - JpnRetail
	// array of menu pointers
#if BUILD == EurRetail
	struct RectMenu *arrayMenuPtrs[10];
#else
	struct RectMenu *arrayMenuPtrs[9];
#endif

#if BUILD == JpnRetail
	// unknown 2 big structures in NTSC-J
	char unk800b8284[0x570];
#endif

	// 800B4800 - UsaRetail
	// 800b4fdc - EurRetail
	// 800b87f4 - JpnRetail
	struct
	{
		short modelID;

		// related to frame, or sound, idk
		short frameIndex_startMoving;
		short unk2;

		u_short boolTrophy;
	}
#if BUILD == JpnRetail
	 titleInstances[7];
#else
	 titleInstances[6];
#endif

	// 800B4830 - UsaRetail
	// 800b500c - EurRetail
	// 800b882c - JpnRetail
	short titleCameraPos[4];
	short titleCameraRot[4];

	// 800B4840 - UsaRetail
	// 800b501c - EurRetail
	// 800b883c - JpnRetail
	// random stuff related to the title animation,
	// come up with better names later
#if BUILD == JpnRetail
	char title_OtherStuff[0x8C];
#else

	// Full block is 0x84 bytes

	// 800B4840
	int title_numFrameTotal;
	
	// 800B4844
	int title_numTransition;

	// 800B4848
	short title_mainPosX;
	short title_mainPosY;

	// 800B484c
	short title_advPosX;
	short title_advPosY;
	
	// 800B4850
	short title_racePosX;
	short title_racePosY;
	
	// 800B4854
	short title_plyrPosX;
	short title_plyrPosY;
	
	// 800B4858
	short title_diffPosX;
	short title_diffPosY;
	
	// 800B485c
	short title_camPos[4];
	
	// 800B4864
	struct TransitionMeta transitionMeta_Menu[8];
	
	// 800B48B4
	char title_unkEmpty[0x10];

#endif

	// 800b48c4 - UsaRetail
	// 800b50a0 - EurRetail
	// 800b88c8 - JpnRetail
	struct
	{
		short frameToPlay;
		short soundID;
	}
#if BUILD != JpnRetail
	titleSounds[8];
#else
	titleSounds[7];

	char unkTitleData[0x18];
#endif

	// 800b48e4 - UsaRetail
	// 800b50c0 - EurRetail
	// 800b88fc - JpnRetail
	struct
	{
#if BUILD == JpnRetail
		int holdCode;
#endif
		int numButtons;
		int buttons[10];
		void *funcPtr;
	}
#if BUILD == JpnRetail
	cheats[0x15];
#else
	cheats[0x16];
#endif

	// 800B4D04 - UsaRetail
	// 800b54e0 - EurRetail
	// 800B8D40 - JpnRetail
	int cheatButtonEntry[10];

	// 800B4D2C - UsaRetail
	// 800b5508 - EurRetail
	// 800B8D68 - JpnRetail
	u_short cupDifficultyUnlockFlags[4];

	// 800B4D34 - UsaRetail
	// 800b5510 - EurRetail
	// 800B8D70 - JpnRetail
	short cupDifficultyLngIndex[4];

	// 800B4D3C - UsaRetail
	// 800B5518 - EurRetail
	// 800B8D78 - JpnRetail
	short cupDifficultySpeed[4];

	// ============= Character Select CONST ================

	// 800B4D44 - UsaRetail
	// 800b5520 - EurRetail
	// 800b8d80 - JpnRetail
	struct
	{
		short posX;
		short posY;
	} characterSelectWindowPos[0xD];

	// pointer
	// 800b4d78 - UsaRetail
	// 800b5554 - EurRetail
	void *ptrSelectWindowPos[6];

	// 800B4D90 - UsaRetail
	// 800b556c - EurRetail
	short windowW[6];

	// 800B4D9C - UsaRetail
	// 800b5578 - EurRetail
	short windowH[6];

	// 800b4da8 - UsaRetail
	// 800b5584 - EurRetail
	short driverPosZ[6];

	// 800b4db4 - UsaRetail
	// 800b5590 - EurRetail
	short driverPosY[6];

	// 800b4dc0 - UsaRetail
	// 800b559c - EurRetail
	short textPosArr[6];

	// 800b4dcc - UsaRetail
	// 800b55a8 - EurRetail
	struct CharacterSelectMeta csm_1P2P_limited[0xF];

	// 800b4e80 - UsaRetail
	// 800b565c - EurRetail
	struct CharacterSelectMeta csm_1P2P[0xF];

	// 800b4f34 - UsaRetail
	// 800b5710 - EurRetail
	struct CharacterSelectMeta csm_3P[0xF];

	// 800b4fe8 - UsaRetail
	// 800b57c4 - EurRetail
	struct CharacterSelectMeta csm_4P[0xF];

	// 800b509C - UsaRetail
	// 800b5878 - EurRetail
	struct CharacterSelectMeta *ptrCsmArr[6];

	// 800b50B4 - UsaRetail
	// 800b5890 - EurRetail
	// the character select menu has a different order for playable characters
	// this array contains the IDs used for each character in the character select menu
	// each member of the array corresponds to the character order used in the rest of the game, see enum Characters
	short characterMenuID[0x10];

	// 0x15 for transition meta array:
	// 14 character icons + title text + 4 kart screens + 2 more?

	// 800b50D4 - UsaRetail
	// 800b58b0 - EurRetail
	// 1P/2P mode
	struct TransitionMeta transitionMeta_csm_1P2P[0x15];

	// 0x2 byte padding
	short padding800b51A6;

	// 3P mode
	// 800b51A8 - UsaRetail
	// 800b5984 - EurRetail
	struct TransitionMeta transitionMeta_csm_3P[0x15];

	// 0x2 byte padding
	short padding800B527A;

	// 4P mode
	// 800b527c - UsaRetail
	// 800b5a58 - EurRetail
	struct TransitionMeta transitionMeta_csm_4P[0x15];

	// 0x2 byte padding
	short padding800B534E;

	// 800B5350 - UsaRetail
	// 800b5b2c - EurRetail
	struct TransitionMeta *ptr_transitionMeta_csm[4];

	// 800B5360 - UsaRetail
	// 800b5b3c - EurRetail
	short csm_instPos[4];
	short csm_instRot[3];
	short moveModels;

	// 800B5370 - UsaRetail
	// 800b5b4c - EurRetail
	int unkCharacterWindows;

	// 800b5374 - UsaRetail
	// 800b5b50 - EurRetail
	// points to s_1, s_2, s_3, s_4
	int *PlayerNumberStrings[4];

	// 800b5384
	char getNextDriver1[4];
	
	// 800b5388
	char getNextDriver2[4];

	// 800b538c -- UsaRetail
	u_int characterSelect_Outline;

	// 800b5390 - UsaRetail
	// 800b5b6c - EurRetail
	u_int characterSelect_NeutralColor;

	// 800b5394 - UsaRetail
	// 800b5b70 - EurRetail
	u_int characterSelect_ChosenColor;

	// 800b5398 - UsaRetail
	// 800b5b74 - EurRetail
	char characterSelect_BlueRectColors[0x18];
	// u_int characterSelect_BlueRectColors[6];

	// =========== Track Select CONST ============

	// 800b53b0 - UsaRetail
	// 800b5b8c - EurRetail
	// 800b93ec - JpnRetail
	struct MainMenu_LevelRow arcadeTracks[0x12];

	// 800b54d0 - UsaRetail
	// 800b5cf4 - EurRetail
	// 800b9554 - JpnRetail
	struct MainMenu_LevelRow battleTracks[0x7];

	// 800b5540 - UsaRetail
	// 800b5d80 - EurRetail
	// 800b95e0 - JpnRetail
	// Not all of this is actually transitionmeta, needs proper look
	struct TransitionMeta transitionMeta_trackSel[5];
	short padding_800B5572;
	
	// 800b5574
	short lapRowVal[4];
	
	// 800b557c
	struct MenuRow rowsLapSel[4];
	
	// 800B5594
	struct RectMenu menuLapSel;
	
	// 800B55C0
	int videoCol;
	
	// 800B55C4
	short timeTrialStarCol[2];
	short timeTrialFlagGet[2];
	
#if BUILD == JpnRetail
	// 800b966c
	char wumpaShadowRGBA[4];
#endif
	
	// 800b55cc -- UsaRetail
	// 800b9670 -- JpnRetail
	struct
	{
		short offsetX;
		short offsetY;
		short type;
	} drawMapOffset[6];

	// ============== Cup Select ==================

	// 800b55f0 - UsaRetail
	// 800b5e30 - EurRetail
	// 800b9694 - JpnRetail
	struct TransitionMeta transitionMeta_cupSel[0x6];

	// 800b562c - UsaRetail
	// 800b5e6c - EurRetail
	// 800b96d0 - JpnRetail
	short cupSel_StarColorIndex[4];

	// 800b5634 - UsaRetail
	// 800b5e74 - EurRetail
	// 800b96d8 - JpnRetail
	u_short cupSel_StarUnlockFlag[4];

	// 800b563c - UsaRetail
	// 800b5e7c - EurRetail
	// 800b96e0 - JpnRetail
	u_int cupSel_Color; // of what?

	// ============= Battle CONST ================

	// 800b5640 - UsaRetail
	// 800b5e80 - EurRetail
	// 800b96e4 - JpnRetail
	struct TransitionMeta transitionMeta_battle[0xB];

	// 2 byte padding
	short padding800b56ae;

	// 800b56b0 - UsaRetail
	// 800b5ef0 - EurRetail
	// 800b9754 - JpnRetail
	struct MenuRow rowsBattleType[4];

	// 800b56c8 - UsaRetail
	// 800b5f08 - EurRetail
	// 800b976c - JpnRetail
	struct RectMenu menuBattleType;

	// 800b56f4 - UsaRetail
	// 800b5f34 - EurRetail
	// 800b9798 - JpnRetail
	struct MenuRow rowsBattleLengthLifeTime[4];

	// 800b570c - UsaRetail
	// 800b5f4c - EurRetail
	// 800b97b0 - JpnRetail
	struct RectMenu menuBattleLengthLifeTime;

	// 800b5738 - UsaRetail
	// 800b5f78 - EurRetail
	// 800b97dc - JpnRetail
	struct MenuRow rowsBattleLengthTimeTime[4];

	// 800b5750 - UsaRetail
	// 800b5f90 - EurRetail
	// 800b97f4 - JpnRetail
	struct RectMenu menuBattleLengthTimeTime;

	// 800b577c - UsaRetail
	// 800b5fbc - EurRetail
	// 800b9820 - JpnRetail
	struct MenuRow rowsBattleLengthPoints[4];

	// 800b5794 - UsaRetail
	// 800b5fd4 - EurRetail
	// 800b9838 - JpnRetail
	struct RectMenu menuBattleLengthPoints;

	// 800b57c0 - UsaRetail
	// 800b6000 - EurRetail
	// 800b9864 - JpnRetail
	struct MenuRow rowsBattleLengthLifeLife[4];

	// 800b57d8 - UsaRetail
	// 800b6018 - EurRetail
	// 800b987c - JpnRetail
	struct RectMenu menuBattleLengthLifeLife;

	// 800b5804 - UsaRetail
	// 800b6044 - EurRetail
	// 800b98a8 - JpnRetail
	struct MenuRow rowsBattleStartGame[2];

	// 800b5810 - UsaRetail
	// 800b6050 - EurRetail
	// 800b98b4 - JpnRetail
	struct RectMenu menuBattleStartGame;

	// 800b583c - UsaRetail
	// 800b607c - EurRetail
	// 800b98e0 - JpnRetail
	struct RectMenu *battleMenuArray[5];

	// 800b5850 - UsaRetail
	// 800b6090 - EurRetail
	// 800b98f4 - JpnRetail
	int battleWeaponsEnabled[22];

	// 800b58a8 - UsaRetail
	// 800b60e8 - EurRetail
	// 800b994c - JpnRetail
	u_int FlagesGameMode1_BattleType[3];

	// 800b58b4 - UsaRetail
	// 800b60f4 - EurRetail
	// 800b9958 - JpnRetail
	char time_3_6_9[4];
	char time_3_6_INF[4];
	char lives_3_6_9[4];
	char points_5_10_15[4];

	// 800b58c4 - UsaRetail
	// 800b6104 - EurRetail
	// 800b9968 - JpnRetail
	int color1;
	int color2;
	int color3;

	// ================ High Score CONST ==================

	// 800b58d0 - UsaRetail
	// 800b6110 - EurRetail
	// 800b9974 - JpnRetail
	struct TransitionMeta transitionMeta_HighScores[0xC];

	// 800b5948 - UsaRetail
	// 800b6188 - EurRetail
	// 800b99ec - JpnRetail
	short colorIndexArray[2];

	// 800b594c - UsaRetail
	// 800b618c - EurRetail 
	// 800b99f0 - JpnRetail
	u_short highscore_unkflags[2];

	// 800b5950 - UsaRetail
	// 800b6190 - EurRetail
	// 800b99f4 - JpnRetail
	u_int highscore_iconColor;

	// 800b5954 - UsaRetail
	// 800b6194 - EurRetail
	// 800b99f8 - JpnRetail
	struct MenuRow rowsHighScore[4];

	// 800b596c - UsaRetail
	// 800b61ac - EurRetail
	// 800b9a10 - JpnRetail
	struct RectMenu menuHighScore;

	// 800B5998 - UsaRetail
	// 800b61d8 - EurRetail
	// 800b9a3c - JpnRetail
	short highScore_trackDesired;
	short highScore_rowDesired;
	short highScore_trackCurr;
	short highScore_rowCurr;

#if BUILD == EurRetail
	
	// 800b61e0 - EurRetail
	// why not just use the one at 800b4e28?
	short fileIndexLngBoot[6];

	// 800b61ec - EurRetail
	struct MenuRow rowsLngBoot[7];

	char padding800b6216[2];

	// 800b6218 - EurRetail
	// Language menu on game start
	struct RectMenu menuLngBoot;

#elif BUILD == JpnRetail
	// 800b9a44 - JpnRetail
	char unk800b9a44[8];
#endif

	// 800b59a0 - UsaRetail
	// 800b6244 - EurRetail
	// 800b9a4c - JpnRetail
	struct Title *titleObj;

	// ============== Track Select DYN ====================

	// 800b59a4 - UsaRetail
	// 800b6248 - EurRetail
	// 800b9a50 - JpnRetail
	int trackSel_changeTrack_frameCount;
	// 800b59a8 - UsaRetail
	// 800b624c - EurRetail
	// 800b9a54 - JpnRetail
	short trackSel_currTrack;
	// 800b59aa - UsaRetail
	// 800b625e - EurRetail
	short trackSel_direction;
	// 800b59ac - UsaRetail
	// 800b6250 - EurRetail
	short trackSel_boolOpenLapBox;
	// 800b59ae - UsaRetail
	// 800b6252 - EurRetail
	short trackSel_transitionState;
	// 800b59b0 - UsaRetail
	// 800b6254 - EurRetail
	short trackSel_StartRaceAfterFadeOut;
	// 800b59b2 - UsaRetail
	// 800b6256 - EurRetail
	short trackSel_transitionFrames;
	// 800b59b4 - UsaRetail
	// 800b6258 - EurRetail
	short trackSel_video_frameCount; // video box transition frames instead?
	// 800b59b6 - UsaRetail
	// 800b625a - EurRetail
	short trackSel_video_boolAllocated;

	// Also used in HighScore menu
	// 800b59b8 - UsaRetail
	// 800b625c - EurRetail
	short trackSel_video_state;
	// 800b59ba - UsaRetail
	// 800b625e - EurRetail
	short trackSel_unk;

	// ============== Cup Select DYN ========================

	// 800b59bc - UsaRetail
	// 800b6260 - EurRetail
	short cupSel_transitionState;
	// 800b59be - UsaRetail
	// 800b6262 - EurRetail
	short cupSel_postTransition_boolStart;
	// 800b59c0 - UsaRetail
	// 800b6264 - EurRetail
	short cupSel_transitionFrames;

	// ============== Battle DYN ==========================

	// 800b59c2 - UsaRetail
	// 800b6266 - EurRetail
	short battle_transitionState;
	// 800b59c4 - UsaRetail
	// 800b6268 - EurRetail
	short battle_postTransition_boolStart;
	// 800b59c6 - UsaRetail
	// 800b626a - EurRetail
	short battle_transitionFrames;

	// =============== High Score DYN ===================

	// 800b59c8 - UsaRetail
	// 800b626c - EurRetail
	short highScore_transitionState;

	// 800b59ca - UsaRetail
	// 800b626e - EurRetail
	// 0) Transition in/out menu
	// 1) Horizontal (in-menu)
	// 2) Vertical (in-menu)
	short highScore_transitionFrames[3];

	// 800b59d0 - UsaRetail
	// 800b6274 - EurRetail
	// X (horizontal) and Y (vertical) Axes
	// -1 for negative direction and 1 for positive direction
	// not sure why each need two buffers, perhaps to prevent mid-transition error
	short highScore_horizontalMove[2];
	short highScore_verticalMove[2];

	// =============== Scrapbook ===================

	// 800b59d8 - UsaRetail
	// 800b627c - EurRetail
	int scrapbookState;

	// ============= Character Select DYN ====================

	// 800b59dc - UsaRetail
	// 800b6280 - EurRetail
	short characterSelect_sizeY;
	short unk_aftercharacterselect_sizey;

	// 800b59e0 - UsaRetail
	// 800b6284 - EurRetail
	// 800b9a8c - JpnRetail
	int desiredMenuIndex;

	// 800b59e4 -- UsaRetail
	// 800b6288 -- EurRetail
	// 800b9a90 -- JpnRetail
	short movingToTrackMenu;
	short unk_aftermovingtotrackmenu;

	// 800b59e8 -- UsaRetail
	// 800b628c -- EurRetail
	short characterSelect_MoveDir[4];

	// 800b59f0 -- UsaRetail
	// 800b6294 -- EurRetail
	short characterSelect_charIDs_desired[4];

	// 800b59f8 - UsaRetail
	// 800b629c - EurRetail
	short characterSelect_charIDs_curr[4];

	// 800b5a00 - UsaRetail
	// 800b62a4 - EurRetail
	short characterSelect_angle[4];

	// 800b5a08 - UsaRetail
	// 800b62ac - EurRetail
	// 800b9ab4 - JpnRetail
	int characterSelect_transitionState;

	// 800b5a0c - UsaRetail
	// 800b62b0 - EurRetail
	short *characterSelect_ptrWindowXY;

	// 800b5a10 - UsaRetail
	// 800b62b4 - EurRetail
	int characterSelectIconLayout;

	// 800b5a14 - UsaRetail
	// 800b62b8 - EurRetail
	// 800b9ac0 - JpnRetail
	int timerInTitle;

	// 800b5a18 - UsaRetail
	// 800b62bc - EurRetail
	struct CharacterSelectMeta *csm_Active;

	// 800b5a1c - UsaRetail
	// 800b62c0 - EurRetail
	// 800b9ac8 - JpnRetail
	int MM_State;

	// 800b5a20 - UsaRetail
	// 800b62c4 - EurRetail
	// 800b9acc - JpnRetail
	// 0 = transitioning in, 1 = in focus/still, 2 = transitioning out
	int isMenuTransitioning;

	// 800b5a24 - UsaRetail
	// 800b62c8 - EurRetail
	// 800b9ad0 - JpnRetail
	short timerPerPlayer[4];

#if BUILD == EurRetail
	// 800b62d0
	// starts at 900 frames (30 secs). If ran out (-1),
	// menu will automatically choose current selection
	int langMenuTimer;
#endif

	// 800b5a2c - UsaRetail
	// 800b62d4 - EurRetail
	// 800b9ad8 - JpnRetail
	int isRosterExpanded;

	// 800b5a30 - UsaRetail
	// 800b62d8 - EurRetail
	// 800b9adc - JpnRetail
	int characterSelect_sizeX;

	// 800b5a34 - UsaRetail
	// 800b62dc - EurRetail
	// 800b9ae0 - JpnRetail
	short *ptrIntroCam;

	// 800b5a38 - UsaRetail
	// 800b62e0 - EurRetail
	// 800b9ae4 - JpnRetail
	int textPos;

	// 800b5a3c - UsaRetail
	// 800b62e4 - EurRetail
	// 800b9ae8 - JpnRetail
	struct TransitionMeta *ptrTransitionMeta;

	// 800b5a40 - UsaRetail
	// 800b62e8 - EurRetail
	// 800b9aec - JpnRetail
	int countMeta0xD; // this might be related to transitionFrames instead

	// 800b5a44 - UsaRetail
	// 800b62ec - EurRetail
	// 800b9af0 - JpnRetail
	int transitionFrames;

	// ================= Video RDATA ===========================

	// 800b5a48 - UsaRetail
	// 800b62f0 - EurRetail
	// 800b9af4 - JpnRetail
	char s_SliceBuf[0xC];
	char s_VlcBuf[8];
	char s_RingBuf[8];

	// 800b5a64 MM_Video_DecDCToutCallbackFunc
};

// starts at 800b67ac
struct OVR_230_VideoBSS
{
    int field0_0x0;
    int field1_0x4;
    int field2_0x8;
    int field3_0xc;

    // 800b67bc
    short totalFrames;

    // 800b67be
    short frameCounter;

    // 800b67c0
    short DCT_MODE;

    // 800b67c2
    short drawNextFrame;

	// 800b67c4
    short field8_0x18;
    short field9_0x1a;
	
	// 800b67c8
    short field10_0x1c;

    // 800b67ca
    short imgId;

	// 800b67cc 
    short field12_0x20;
    short field13_0x22;
	
	// 800b67d0
    int field14_0x24;

    // 800b67d4
    int numFrames;

    // 800b67d8
    int frameCount;
    int field19_0x30;
    int field20_0x34;
    int field21_0x38;

    // 800b67e8
    // 1 - IS_RGB24
    // 2 - has Audio
    // 4 - is looping
    // 8 - is Scrapbook (?)
    u_int flags;

    // 800b67ec
    int RING_SIZE;

    // 800b67f0
    u_int isDone;

    int field25_0x48;

	// field 26,27,28,29
    char unk800b67f8[4];

	// 30,31...
    // 800b67fc
    u_long* in_Buf[2];
	
	int field32_0x58;

    char field33_0x5c;
    char field34_0x5d;
    char field35_0x5e;
    char field36_0x5f;

    // 800b680c
    u_long *out_Buf[4];

    // 800b681c
    RECT slice;

    // 800b6824
    CdlLOC cdLocation1;

    // 800b6828
    CdlLOC cdLocation2;

    // 800b682c
    CdlLOC cdLocation3;
	
	// 800b6830
    CdlLOC* ptrCdLoc;
};

extern struct OverlayRDATA_230 R230;
extern struct OverlayDATA_230 D230;
extern struct OVR_230_VideoBSS V230;


#if BUILD >= EurRetail
	_Static_assert(sizeof(struct MainMenu_LevelRow) == 0x14);
#else
	_Static_assert(sizeof(struct MainMenu_LevelRow) == 0x10);
#endif
	_Static_assert(sizeof(struct CharacterSelectMeta) == 0xC);
	_Static_assert(sizeof(struct TransitionMeta) == 0xA);
