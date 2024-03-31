#include <common.h>

// First 0x14 bytes of the overlay are padding
void JunkFunc()
{
	asm(
	"nop;"
	"nop;"
	"nop;"
	);
}

struct RingRallyGame
{
	char inited;
	char numRingsOnTrack;
	short numRingsCollected;
	char numRingsCollectedLap;
	short laps;
	int points;
	short ringsPointsPerLap;
	struct Instance* ring[10];
};

struct RingData
{
	int pos[3];
	short rot[3];
	unsigned char modelIndex;
	unsigned char placeholder;
};

struct Tracks
{
	char *name;
	char *file;
	char id;
};

struct GlobalGameVariables
{
	char beatPb;
	char raceFinished;
	char onSettingsMenu;
	int personalBest;
};

struct SettingsMenu
{
	char *selectCharStr;
	char *helpStr[2];
	char *playStr;
	char stringColors[3];
	char cursorPos;
	char currChar;
	char currTrack;
};

char trackDataFilePath[] = "\\RINGRALLY\\TRACKS.BIN;1";

char ring_name[] = "Ring Rally Game";
char ring_inst_name[] = "Ring";
char ringsStr[] = "Rings: 00000";
char ringsStrFinal[] = "Rings:   00000";
char lapsStr[] =  "Laps: 000";
char lapsStrFinal[] = "Laps:      000";
char pointsStr[] = "0000000";
char scoreStr[] = "Score: 0000000";
char pbStr[] = "Personal Best: 0000000";
char newRecordStr[] = "NEW RECORD!!!";
char newRecordColor = 0;
char s_endStr[] = "Press * to play again";
char gotoMenuStr[] = "Press [ to change track or character";

struct GlobalGameVariables ggv;

struct SettingsMenu menu =
{
	.selectCharStr = "Select Character:",
	.helpStr = {"Press LEFT or RIGHT to", "change your settings."},
	.playStr = "Play",
	.stringColors = {0, 0, 0},
	.currChar = 0,
	.currTrack = 5,
};

// Array that stores the amount of seconds that each ring will give you per lap
int timePerLap[] = { 2.5 * 32 * 30, 2.25 * 32 * 30, 2 * 32 * 30, 1.75 * 32 * 30, 1.5 * 32 * 30,
				1.25 * 32 * 30, 1 * 32 * 30, 0.85 * 32 * 30, 0.7 * 32 * 30, 0.6 * 32 * 30, 0.5 * 32 * 30};

RECT menuWindow = {80, 40, 360, 106};
RECT recordWindow = {131, 40, 250, 79};
int iconID;

struct RingData * ringData;
struct Tracks * tracks;
int size;

void CameraHook();

// Only need declaration for functions being injected.
// At some point, they should all be declared anyway
void FUN_8001a0bc(int param_1,int param_2,short *param_3,int param_4,short *param_5);
void Init_Camera(unsigned int *param_1,unsigned int param_2,unsigned int param_3,unsigned int param_4);
void DrawCrystalChallHUD_Game(void);
void InjectCameraHook();
void MainUpdateLoop();
void InjectRetroFueled();

// End of Race menu in Crystal Challenge,
// This executes as soon as light turns
// green in Dingo Canyon
void EndCrystalChallenge(void)
{
	unsigned int funcPtr;

	// Had to store the pointer somewhere, where it isn't touched,
	// kinda hacky, I put it where a pointer is used for loading
	// a 2nd hub while in adventure arena. If it works, it works
	struct RingRallyGame* rrg = (struct RingRallyGame*)semiGlobal.gameConfig.level2;

	// if this is the first boot
	if(rrg == 0)
	{

		// hacky way to avoid the game executing code from this if block more than one time
		semiGlobal.gameConfig.level2 = 1;

		// Change camera thread function
		InjectCameraHook();

		// Remove instruction that changes LOD,
		// so now it should default to 8 (time trial),
		// This way, weapon boxes wont spawn on track

		// This function changes between regions, be careful,
		// look for lbu v1, 0x----(a1)
		#if BUILD == UsaRetail || BUILD == JpnRetail
		*(unsigned int*)(LOAD_TenStages + 0x4BC) = 0;
		#elif BUILD == EurRetail
		*(unsigned int*)(LOAD_TenStages + 0x4B0) = 0;
		#endif

		// Remove instruction to draw number crystals
		*(unsigned int*)(DrawCrystalChallHUD_Game + 0xB0) = 0;

		// disable hud, just like 2P NF mod,
		// also disable countdown timer
		*(char*)(FUN_8001a0bc + 0xF7C) = 0;

		// Copy/Paste from ModMenuV2
		InjectRetroFueled();

		// load track data
		tracks = FileToBuffer(trackDataFilePath, 0, 0);

		// send the player to the settings menu
		ggv.onSettingsMenu = 1;

	}

	// if you're in the settings menu
	if (ggv.onSettingsMenu) {

		// if you pressed up, move cursor up and
		// change the color of the former string to orange
		if (semiGlobal.AnyPlayerTap & BTN_UP) {

			menu.stringColors[menu.cursorPos] = 0;

			if (--menu.cursorPos == 255) {
				menu.cursorPos = 0;
			}

		}

		// if you pressed down, move cursor down and
		// change the color of the former string to orange
		else if (semiGlobal.AnyPlayerTap & BTN_DOWN) {

			menu.stringColors[menu.cursorPos] = 0;

			if (++menu.cursorPos == 3) {
				menu.cursorPos = 2;
			}
		}

		// if you're in the character selection
		// Pressing left and right changes your character
		if (menu.cursorPos == 0)
		{
			if (semiGlobal.AnyPlayerTap & BTN_LEFT) {

				if (--menu.currChar == 255) {

					menu.currChar = 14;
				}

			} else if (semiGlobal.AnyPlayerTap & BTN_RIGHT) {

				if (++menu.currChar == 15) {

					menu.currChar = 0;
				}
			}
		}

		// if you're in the track selection
		// pressing left and right changes your track
		else if (menu.cursorPos == 1) {

			if (semiGlobal.AnyPlayerTap & BTN_LEFT) {

				if (--menu.currTrack == 255) {

					menu.currTrack = 17;
				}

			} else if (semiGlobal.AnyPlayerTap & BTN_RIGHT) {

				if (++menu.currTrack == 18) {

					menu.currTrack = 0;
				}
			}

		}

		// making the string of the current selected option flash
		menu.stringColors[menu.cursorPos] = (menu.stringColors[menu.cursorPos] + 1) & 0x1;

		// Drawing strings in the menu
		DecalFont_DrawLine(menu.selectCharStr, 93, 50, FONT_BIG, menu.stringColors[0]);
		// the track string comes from the TRACKS file in the folder RINGRALLY
		DecalFont_DrawLine((char *) ((int) tracks + tracks[menu.currTrack].name), 260, 70, FONT_BIG, (menu.stringColors[1] | JUSTIFY_CENTER));
		DecalFont_DrawLine(menu.playStr, 260, 106, FONT_BIG, (menu.stringColors[2] | JUSTIFY_CENTER));
		DecalFont_DrawLine(menu.helpStr[0], 93, 126, FONT_SMALL, RED);
		DecalFont_DrawLine(menu.helpStr[1], 93, 134, FONT_SMALL, RED);

		// updating the iconID of the current selected character
		iconID = (int)*(short *)( &global.dataIcons[(menu.currChar * 0x10) + 8]);

		// draw icon of the current selected character
		UI_DrawDriverIcon(

			// pointer to icon
			semiGlobal.gameConfig.ptrIcons[iconID],

			// x and y
			0x180, 0x2C,

			// pointer to PrimMem struct
			&semiGlobal.gameConfig.backBuffer->primMem,

			// pointer to OT mem (struct?)
			*(int*)semiGlobal.gameConfig.pushBuffer_UI.ptrOT,

			1, 0x1000, 0x808080
		);

		// draw black box for the menu
		DrawBox2D(&menuWindow, 5, semiGlobal.gameConfig.backBuffer->otMem.startPlusFour);

		// if you selected PLAY
		if (menu.cursorPos == 2 && semiGlobal.AnyPlayerTap & BTN_OX) {

			// set color of the string to the default orange
			menu.stringColors[menu.cursorPos] = 0;

			// set the character with the selected character
			global.characterIDs[0] = menu.currChar;

			// Set the PB as the lowest score possible
			ggv.personalBest = 0;

			// load selected level
			MainRaceTrack_RequestLoad(tracks[menu.currTrack].id);

			// load ring data of the selected level
			ringData = FileToBuffer((char *) ((int) tracks + tracks[menu.currTrack].file), 0, &size);

		}

	}

	// if you're not in the menu
	else {

		// Draw your Personal Best
		DecalFont_DrawLine(pbStr, 0x100, 12, FONT_BIG, (JUSTIFY_CENTER | ORANGE));

		// if you beat your personal best
		if (ggv.beatPb) {

			// Change the color of the NEW RECORD!!! string so it appears as flashing
			newRecordColor = (newRecordColor + 1) & 0x1;

			// draw a NEW RECORD!!! congratulating the player
			DecalFont_DrawLine(newRecordStr, 0x100, 139, FONT_BIG, newRecordColor | JUSTIFY_CENTER);
		}

		// Draw your score
		DecalFont_DrawLine(scoreStr, 140, 98, FONT_BIG, RED);

		// Draw number of rings
		DecalFont_DrawLine(ringsStrFinal, 140, 66, FONT_BIG, PERIWINKLE);

		// Draw number of lapsStr
		DecalFont_DrawLine(lapsStrFinal, 140, 45, FONT_BIG, PERIWINKLE);

		// Draw instructions for restart
		DecalFont_DrawLine(s_endStr, 0x100, 0xB0, FONT_SMALL, (JUSTIFY_CENTER | ORANGE));

		// Draw instructions to change character and/or track
		DecalFont_DrawLine(gotoMenuStr, 0x100, 0xC0, FONT_SMALL, (JUSTIFY_CENTER | ORANGE));

		// draw invi box to show the record time
		DrawBox2D(&recordWindow, 4, semiGlobal.gameConfig.backBuffer->otMem.startPlusFour);

		// If you press Cross or Circle
		if(semiGlobal.AnyPlayerTap & BTN_OX)
		{
			// restart race
			semiGlobal.mainGameState = 2;
		}

		// if you press Square
		else if (semiGlobal.AnyPlayerTap & BTN_SQUARE)
		{

			// send player to the menu
			ggv.onSettingsMenu = 1;
		}
	}
}

void Junk(int param1, int param2, int param3)
{
	// leave it empty
}

void InjectCameraHook()
{
	// You can do this with any thread, not just camera

	// Generate assembly in this function
	// to pass this parameter. Need 3 params
	// so that compiler doesn't put 2nd param
	// into the branch of calling "Junk"
	Junk(0, (int)CameraHook, 0);

	// Copy the assembly compiled in this function, to CameraInit,
	// which is "lui" and "addiu" of register "a1", so our function is
	// passed to the camera thread, and executed once per frame
	*(unsigned int*)(Init_Camera + 0x28) = *(unsigned int*)(InjectCameraHook + 0x0C);
	*(unsigned int*)(Init_Camera + 0x2C) = *(unsigned int*)(InjectCameraHook + 0x10);

	// now we can end the function
	return;
}

void MainUpdateLoop();

void CameraHook(struct Thread* t)
{
	// mod function
	MainUpdateLoop();

	// call the original camera function
	PerFrame_Camera(t);
}

// Declarations for RF
void FUN_8005abfc(int param_1,int param_2,unsigned int param_3,int param_4);
void FUN_8005ebac(int param_1,int param_2);
void FUN_8006181c(int param_1,int param_2);

void InjectRetroFueled()
{
	// port of Retro Fueled by TheRedhotbr

	*(unsigned char*)(FUN_8005abfc + 0x37A) = 0;

	// Set pads to USF
	//*(unsigned char*)(FUN_8005ebac + 0xB9) = 8;

	*(unsigned int* )(FUN_8006181c + 0xA30) = 0x8222040D;
	*(unsigned int* )(FUN_8006181c + 0xA34) = 0x30B80002;
	*(unsigned int* )(FUN_8006181c + 0xA38) = 0x30B90020;
	*(unsigned int* )(FUN_8006181c + 0xA3C) = 0x17000006;
	*(unsigned int* )(FUN_8006181c + 0xA40) = 0x319C020;
	*(unsigned int* )(FUN_8006181c + 0xA44) = 0x13200004;
	*(unsigned int* )(FUN_8006181c + 0xA48) = 0;
	*(unsigned int* )(FUN_8006181c + 0xA60) = 0x20190022;
	*(unsigned char*)(FUN_8006181c + 0xA70) = 3;
	*(unsigned int* )(FUN_8006181c + 0xA80) = 0x13190002;
	*(unsigned int* )(FUN_8006181c + 0xA84) = 0;
	*(unsigned int* )(FUN_8006181c + 0xA88) = 0x14400002;
	*(unsigned int* )(FUN_8006181c + 0xA8C) = 0x24020006;
	*(unsigned int* )(FUN_8006181c + 0xA90) = 0x1682001C;
}

short min(short a, short b) {

	if (a > b) {

		return b;
	}

	return a;
}

short max(short a, short b) {

	if (a > b) {

		return a;
	}

	return b;
}

// this is what the code is doing:

/*updateNumOnStr(ringsStr, rrg->numRingsCollected, 5, 11);
ringsStr[7] =  '0' + (rrg->numRingsCollected / 10000) % 10;
ringsStr[8] =  '0' + (rrg->numRingsCollected / 1000) % 10;
ringsStr[9] =  '0' + (rrg->numRingsCollected / 100) % 10;
ringsStr[10] = '0' + (rrg->numRingsCollected / 10) % 10;
ringsStr[11] = '0' + (rrg->numRingsCollected) % 10;*/

void updateNumOnStr(char * str, short num, char size, char index)
{
	int i;

	for (i = 0; i < size; i++) {

		str[index - i] = '0' + num % 10;
		num = num / 10;
	}
}

void InitGame()
{
	// Normally the game starts with 5 seconds,
	// and you get 1.5 seconds for each ring

	// 5 seconds in event
	semiGlobal.gameConfig.originalEventTime = 5 * 30 * 32;

	// event has not started
	semiGlobal.gameConfig.elapsedEventTime = 0;

	// the game treats wumpa fruit as crystals,
	// make sure the game doesn't end by collecting them.
	// Wumpa crates dont count, just fruit on ground
	semiGlobal.gameConfig.numCrystalsInLEV = 128;

	// Disable default HUD, then we draw HUD
	// anyway, so we can remove extra crystal

	// make crystals invisible
	semiGlobal.ptrHudCrystal->flags =
	semiGlobal.ptrHudCrystal->flags | 0x80;

	semiGlobal.ptrMenuCrystal->flags =
	semiGlobal.ptrMenuCrystal->flags | 0x80;

	// Resetting global game variables and strings
	ggv.beatPb = 0;
	ggv.raceFinished = 0;
	ggv.onSettingsMenu = 0;

	// reset points counter
	updateNumOnStr(pointsStr, 0, 7, 6);

	// reset ring counter
	updateNumOnStr(ringsStr, 0, 5, 11);

	// reset lap counter
	updateNumOnStr(lapsStr, 0, 3, 8);

}

char CollideRing(int loop)
{
	int ringRadius;
	struct Driver* driver;
	int playerX;
	int playerY;
	int playerZ;

	// Had to store the pointer somewhere, where it isn't touched,
	// kinda hacky, I put it where a pointer is used for loading
	// a 2nd hub while in adventure arena. If it works, it works
	struct RingRallyGame* rrg = (struct RingRallyGame*)semiGlobal.gameConfig.level2;

	ringRadius = (int)rrg->ring[loop]->scale[0];

	driver = semiGlobal.gameConfig.drivers[0];

	playerX = driver->posCurr[0];
	playerY = driver->posCurr[1];
	playerZ = driver->posCurr[2];

	if(ringData[loop].rot[0] == 0)
	{
		return
		(
			( (ringData[loop].pos[0] - playerX) < (ringRadius << 1) ) &&
			( (ringData[loop].pos[0] - playerX) > (ringRadius << 1) * -1 ) &&
			( (ringData[loop].pos[1] - playerY) < (ringRadius << 2) ) &&
			( (ringData[loop].pos[1] - playerY) > (ringRadius << 2) * -1 ) &&
			( (ringData[loop].pos[2] - playerZ) < (ringRadius << 2) ) &&
			( (ringData[loop].pos[2] - playerZ) > (ringRadius << 2) * -1 )
		);
	}

	else
	{
		return
		(
			( (ringData[loop].pos[0] - playerX) < (ringRadius << 2) ) &&
			( (ringData[loop].pos[0] - playerX) > (ringRadius << 2) * -1 ) &&
			( (ringData[loop].pos[1] - playerY) < (ringRadius << 2) ) &&
			( (ringData[loop].pos[1] - playerY) > (ringRadius << 2) * -1 ) &&
			( (ringData[loop].pos[2] - playerZ) < (ringRadius << 1) ) &&
			( (ringData[loop].pos[2] - playerZ) > (ringRadius << 1) * -1 )
		);
	}

	return 0;
}

void MainUpdateLoop()
{
	int loop;
	int loop2;
	int modelPtr;
	char boolCollide;

	// Had to store the pointer somewhere, where it isn't touched,
	// kinda hacky, I put it where a pointer is used for loading
	// a 2nd hub while in adventure arena. If it works, it works
	struct RingRallyGame* rrg = (struct RingRallyGame*)semiGlobal.gameConfig.level2;

	if(
			// rrg has never been allocated,
			// works almost always
			semiGlobal.gameConfig.level2 == 0 ||

			// allocator stopped, right before allocating this,
			// needed for when you pause and restart
			semiGlobal.gameConfig.level2 == semiGlobal.mempack.firstFreeByte
		)
	{

		InitGame();

		// allocate memory
		rrg = (void*)MEMPACK_AllocMem(sizeof(struct RingRallyGame),ring_name);

		// store RRG
		semiGlobal.gameConfig.level2 = rrg;

		// reset game variables
		rrg->laps = 0;
		rrg->numRingsCollected = 0;
		rrg->points = 0;
		rrg->numRingsCollectedLap = 0;
		rrg->ringsPointsPerLap = 1000;
		rrg->numRingsOnTrack = size / sizeof(struct RingData);

		for(loop = 0; loop < rrg->numRingsOnTrack; loop++)
		{
			// get model pointer
			modelPtr = semiGlobal.gameConfig.modelPtr[ringData[loop].modelIndex];

			// instance flags will be 0xf by default
			rrg->ring[loop] = (struct Instance*)CreateInstanceOfModel(modelPtr, ring_inst_name, 0);

			// Fix LOD for Uka rings,
			// This value is set by default for Aku, but Uka is lower
			rrg->ring[loop]->model->dist_until_LOD1_drop = 0x4E20;

			for (loop2 = 0; loop2 < 3; loop2++) {

				// same scale for all, since token is rotated
				rrg->ring[loop]->scale[loop2] = 0x7fff;

				// Instance takes pos >> 8 for driver struct as well,
				// we dont shift initially because we need the top bits
				// to determine + or -, with signed variables, or else
				// all collisions break
				rrg->ring[loop]->matrix.t[loop2] = ringData[loop].pos[loop2] >> 8;
			}

			// rot -> matrix
			ConvertRotToMatrix(&rrg->ring[loop]->matrix, ringData[loop].rot);

		}
	}

	if (ggv.raceFinished == 1) {
		return;
	}

	// if you are right about to run out of time
	if(
		semiGlobal.gameConfig.originalEventTime -
		semiGlobal.gameConfig.elapsedEventTime < 40
	  )
	{

		ggv.raceFinished = 1;

		// Checking if you beat your best record
		if (rrg->points > ggv.personalBest) {

			// Update best record
			ggv.personalBest = rrg->points;

			// Update PB string
			updateNumOnStr(pbStr, ggv.personalBest, 7, 21);

			// Set boolean that checks whether you beat your PB to true
			ggv.beatPb = 1;
		}

		// Update score strings
		updateNumOnStr(scoreStr, rrg->points, 7, 13);
		updateNumOnStr(lapsStrFinal, rrg->laps, 3, 13);
		updateNumOnStr(ringsStrFinal, rrg->numRingsCollected, 5, 13);

		// put HUD back, or EndCrystalChallenge wont execute
		semiGlobal.gameConfig.hudFlags =
		semiGlobal.gameConfig.hudFlags | 1;

		// resetting menu variables
		menu.cursorPos = 0;

		return;
	}

	// If you are not about to finish

	// remove HUD
	semiGlobal.gameConfig.hudFlags =
	semiGlobal.gameConfig.hudFlags & 0xfe;

	// If intro anim cutscene ended,
	// and traffic lights either started, or finished
	if(semiGlobal.gameConfig.trafficLightsTimer < 3840)
	{
		// Draw crystal challenge HUD
		DrawCrystalChallHUD_Game();

		// Draw number of rings
		DecalFont_DrawLine(ringsStr, 0x160,8,FONT_SMALL,ORANGE);

		// Draw number of lapsStr
		DecalFont_DrawLine(lapsStr, 0x160,0x10,FONT_BIG,ORANGE);

		// Draw number of points
		DecalFont_DrawLine(pointsStr, 0xB8, 12, FONT_BIG, ORANGE);
	}

	for(loop = 0; loop < rrg->numRingsOnTrack; loop++)
	{
		// skip ring if it is invisible
		if(rrg->ring[loop]->flags & 0x80)
			continue;

		if(CollideRing(loop))
		{

			// increase reserves (depending on the lap)
			char lap_index = min(rrg->laps, 10);
			semiGlobal.gameConfig.drivers[0]->reserves += 430;

			// update base speed
			semiGlobal.gameConfig.drivers[0]->maxGroundSpeed = max(semiGlobal.gameConfig.drivers[0]->maxGroundSpeed, 0xC00 + 0x600 * lap_index);

			// keep count of rings
			rrg->numRingsCollected++;
			rrg->numRingsCollectedLap++;

			// increase number of points
			rrg->points += rrg->ringsPointsPerLap;

			// add 3 seconds to the clock
			semiGlobal.gameConfig.originalEventTime += timePerLap[lap_index];

			// set the counter string
			updateNumOnStr(ringsStr, rrg->numRingsCollected, 5, 11);

			// make this ring invisible
			rrg->ring[loop]->flags =
			rrg->ring[loop]->flags | 0x80;

			// play sound
			PlaySound(0x67,1);
		}
	}


	// capping reserves to a stack of 30s
	if (semiGlobal.gameConfig.drivers[0]->reserves > 28800) {

		semiGlobal.gameConfig.drivers[0]->reserves = 28800;
	}

	// if the lap finished
	if(semiGlobal.gameConfig.drivers[0]->numLaps == 1)
	{

		// set the total laps completed (race) to zero,
		// so we can have an endless race
		semiGlobal.gameConfig.drivers[0]->numLaps = 0;

		// increase bonus points for the rings per lap
		// this is a simple logic that mimics NF point system
		if (rrg->laps < 7) {

			rrg->ringsPointsPerLap += 100;

		} else {

			if (rrg->laps < 10) {

				rrg->ringsPointsPerLap += 100 + 25 * (rrg->laps - 7);
			}
		}

		// if you collected every ring
		if (rrg->numRingsCollectedLap == rrg->numRingsOnTrack) {

			// get bonus points
			rrg->points += 4000 + 100 * rrg->laps;

		}

		// if you did not collect every ring
		else {

			// get punished by each ring that you missed
			rrg->points += 2500 - (50 * (rrg->numRingsOnTrack - rrg->numRingsCollectedLap));
		}

		// increase the number of laps
		rrg->laps++;

		// Increase your number of points depending on how much time remaining you have
		rrg->points += ((semiGlobal.gameConfig.originalEventTime - semiGlobal.gameConfig.elapsedEventTime) * rrg->laps) >> 4;

		// reset the number of rings collected in the current lap
		rrg->numRingsCollectedLap = 0;

		// update lap string
		updateNumOnStr(lapsStr, rrg->laps, 3, 8);


		for(loop = 0; loop < rrg->numRingsOnTrack; loop++)
		{

			// make all rings visible
			rrg->ring[loop]->flags =
			rrg->ring[loop]->flags & 0xffffff7f;

			if (rrg->laps < 8) {

				// updating position of each ring, so the rings don't get stuck in the map
				ringData[loop].pos[1] += 0x800;
				rrg->ring[loop]->matrix.t[1] += 0x8;

				// decreasing scale, so every ring becomes smaller
				for (loop2 = 0; loop2 < 3; loop2++) {
					rrg->ring[loop]->scale[loop2] -= 0xF00;
				}
			}
		}
	}

	// update the points string
	updateNumOnStr(pointsStr, rrg->points, 7, 6);

}