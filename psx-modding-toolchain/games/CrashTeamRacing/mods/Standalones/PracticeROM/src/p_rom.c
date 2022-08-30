#include "../p_rom.h"

void DecalFont_DrawLine(char*, int, int, int, int);
void DrawHeat_Subset1();
void DrawHeat_Subset4();
void DrawHeat_Subset7();
void Driver_SetConsts(struct Driver* d);
void howl_TogglePause(int enable);
void* LIST_RemoveFront(struct LinkedList* L);
int MATH_FastSqrt(int dist, int unk);

#define NumbersToString DrawHeat_Subset1
#define SaveState DrawHeat_Subset4
#define LoadState DrawHeat_Subset7 // can potentially move back to subset6

// String variables
unsigned char speedVal[numSpeedColor] = {151, 165, 175, 185, 196, 207, 218, 229, 240, 255};
int speedColorVal[numSpeedColor] = {darkGreen, green, yellow, orange, red, pink, purple, darkPurple, blue, lightBlue};

// Strings
char s_slotSelected[] = "Slot 1 selected";
char s_slotSaved[] = "Slot 1 saved";
char s_slotLoaded[] = "Slot 1 loaded";
char s_infiniteReserves[] = "Saffi activated";
char s_flyingCheatOn[] = "Flying cheat on";
char s_flyingCheatOff[] = "Flying cheat off";
char s_ghostModeOn[] = "Ghost mode on";
char s_ghostModeOff[] = "Ghost mode off";

char s_numbers[] = " 0000";
char s_checkpointStr[] = "Check:";
char s_progressStr[] = "Progr:";

char s_ms[] = " 000 ms";
char s_frames[] = "Frames:";
char s_total[] = "Total:";
char s_lag[] = " 00000 ms";

char s_balancedEngine[] = "Engine: Balanced";
char s_accelEngine[] = "Engine: Accel";
char s_turnEngine[] = "Engine: Turn";
char s_speedEngine[] = "Engine: Speed";
char s_pentaEngine[] = "Engine: Penta";

// Engine swap strings flow
char * engineStrings[numSlots] = {s_balancedEngine, s_accelEngine, s_speedEngine, s_turnEngine, s_pentaEngine};

enum ButtonsExtra
{
	BTN_SHOULDERS = BTN_R1 | BTN_R2 | BTN_L1 | BTN_L2,
	BTN_FLY = BTN_CROSS | BTN_R2 | BTN_SQUARE,
	BTN_ENGINE_SWAP = BTN_UP | BTN_R2,
};


// Declaring functions to use as variables
void * Weapon_Mask_UseWeapon(int param_1,int param_2);

void BackupInstructions()
{
	// Saving the mask instructions for non TT purposes
	p_rom->maskInstructions[0] = *(int *)(Weapon_Mask_UseWeapon);
	p_rom->maskInstructions[1] = *(int *)(Weapon_Mask_UseWeapon + 0x4);
	p_rom->maskInstructions[2] = *(int *)(Weapon_Mask_UseWeapon + 0x8);
}

void EnableMask()
{
	*(int *)(Weapon_Mask_UseWeapon) = p_rom->maskInstructions[0];
	*(int *)(Weapon_Mask_UseWeapon + 0x4) = p_rom->maskInstructions[1];
	*(int *)(Weapon_Mask_UseWeapon + 0x8) = p_rom->maskInstructions[2];
}

void DisableMask()
{
	// setting return value to null pointer (v0 = 0)
	*(int *)(Weapon_Mask_UseWeapon)        = 0x00001020;
	// jr ra
	*(int *)(Weapon_Mask_UseWeapon + 0x4)  = 0x03E00008;
	// NOP to avoid making any register dirty
	*(int *)(Weapon_Mask_UseWeapon + 0x8)  = 0x00000000;
}

// to do: should hook main(),
// right now happens at threadbuckets
void RunInitHook()
{
	p_rom = (struct P_ROM*)0x8000F000;

	// initialize to penta
	p_rom->engine = 4;
	p_rom->currEngine = &engineStrings[p_rom->engine][8];
	data.MetaDataCharacters[data.characterIDs[0]].engineID = p_rom->engine;
	Driver_SetConsts(gp->gameTracker.drivers[0]);

	BackupInstructions();

	// Tell the game to only draw shadows from player 1
	#if BUILD == UsaRetail
	*(char *)(0x8005b8c4) = 1;
	#elif BUILD == EurRetail
	*(char *)(0x8005b9bc) = 1; // shadows
	#elif BUILD == JpnRetail
	*(char *)(0x8005e74c) = 1; // shadows
	#endif

	return;
}

void SetSlotString(char * str, char slot)
{
	p_rom->slotString = str;
	p_rom->drawDuration = textDuration;
	p_rom->isSlot = slot;
}

void DrawSlotString()
{
	if (p_rom->isSlot)
		p_rom->slotString[5] = '0' + p_rom->slot + 1;

	if (p_rom->lagDuration)
		DecalFont_DrawLine(p_rom->slotString, 256, 39, 2, ND_Orange | 0x8000);
	else
		DecalFont_DrawLine(p_rom->slotString, 256, 22, 2, ND_Orange | 0x8000);
}

void ResetLag()
{
	p_rom->lagFrames = 0;
	p_rom->lagTime = 0;
	p_rom->lagDuration = 0;
}

void DrawLag()
{
	unsigned short ms = gp->gameTracker.elapsedMillisecondsTime;
	NumbersToString(s_ms, ms, 3);

	if (ms > msFrame)
	{
		DecalFont_DrawLine(s_ms, 256, 8, 2, red | 0x8000);
		p_rom->lagFrames++;
		p_rom->lagTime += (ms - msFrame);
		p_rom->lagDuration = textDuration;
	}
	else
	{
		DecalFont_DrawLine(s_ms, 256, 8, 2, ND_Orange | 0x8000);
		if (p_rom->lagDuration)
			p_rom->lagDuration--;
		else
			ResetLag();
	}

	if (p_rom->lagDuration)
	{
		DecalFont_DrawLine(s_frames, x_frames, y_frames, 2, red);
		DecalFont_DrawLine(s_total, x_total, y_total, 2, red);

		NumbersToString(s_numbers, p_rom->lagFrames, 4);
		DecalFont_DrawLine(s_numbers, x_numFrames, y_numFrames, 2, red);
		
		NumbersToString(s_lag, p_rom->lagTime, 5);
		DecalFont_DrawLine(s_lag, x_lag, y_lag, 2, red);
	}
}

void DrawDebugString()
{
	int xSpeed;
	int zSpeed;
	int speed;
	int progress;
	int checkpoint;
	int i;
	int speedColor = silver;
	xSpeed = gp->gameTracker.drivers[0]->xSpeed;
	zSpeed = gp->gameTracker.drivers[0]->zSpeed;
	progress = gp->gameTracker.drivers[0]->distanceToFinish_curr;
	checkpoint = gp->gameTracker.drivers[0]->distanceToFinish_checkpoint;
	speed = MATH_FastSqrt((xSpeed * xSpeed) + (zSpeed * zSpeed), 0);

	for (i = 0; i < numSpeedColor; i++)
	{
		if (speed < (int)speedVal[i]*100)
		{
			speedColor = speedColorVal[i];
			break;
		}
	}

	DecalFont_DrawLine(s_progressStr, x_progressStr, y_progressStr, 2, white);
	DecalFont_DrawLine(s_checkpointStr, x_checkpointStr, y_checkpointStr, 2, white);
	DecalFont_DrawLine(p_rom->currEngine, x_engine, y_engine, 2, white);

	NumbersToString(s_numbers, gp->gameTracker.drivers[0]->reserves / 10, 4);
	DecalFont_DrawLine(s_numbers, x_reserves, y_reserves, 2, lime);
	
	NumbersToString(s_numbers, speed / 10, 4);
	DecalFont_DrawLine(s_numbers, x_speed, y_speed, 2, speedColor);
	
	NumbersToString(s_numbers, progress / 10, 5);
	DecalFont_DrawLine(s_numbers, x_progress, y_progress, 2, white);
	
	NumbersToString(s_numbers, checkpoint / 10, 5);
	DecalFont_DrawLine(s_numbers, x_checkpoint, y_checkpoint, 2, white);
}


void TemporarilyMuteFX()
{
	p_rom->fxVol = gp->vol_FX;
	gp->vol_FX = 0;
	p_rom->waitFrame = 1;
}

void Instance_Ghostify(struct Instance* inst, char isDriver, char becomeGhost)
{
	if (!inst)
		return;

	if (isDriver)
	{
		if (becomeGhost)
			inst->flags |= 0x60000;
		else
			inst->flags &= ~0x60000;
		inst->alphaScale = 0xA00;
	}
	else
	{
		if (becomeGhost)
			inst->flags |= 0x10000;
		else
			inst->flags &= ~0x10000;
		if (gp->gameTracker.drivers[0]->reserves)
			inst->alphaScale = 0x600;
	}
}

void Ghostify(char becomeGhost)
{
	struct Turbo * turboObj;
	struct Thread * fireThread;
	if (becomeGhost)
		gp->gameTracker.drivers[0]->wheelSprites = &gp->gameTracker.iconGroup[0xC]->icons[0];
	else
		gp->gameTracker.drivers[0]->wheelSprites = &gp->gameTracker.iconGroup[0x0]->icons[0];

	Instance_Ghostify(gp->gameTracker.drivers[0]->instSelf, 1, becomeGhost);

	fireThread = gp->gameTracker.threadBuckets[0x9].thread;
	if (!fireThread)
		return;

	turboObj = (struct Turbo *) fireThread->object;
	Instance_Ghostify(fireThread->inst, 0, becomeGhost);
	Instance_Ghostify(turboObj->inst, 0, becomeGhost);
}

void ResetControlVariables()
{
	int i;

	// Saving fx volume
	p_rom->fxVol = gp->vol_FX;

	// Reset flying cheat
	p_rom->isFlying = 0;

	// Reset ghost cheat
	p_rom->isGhost = 0;

	// Reset save slot
	p_rom->slot = 0;

	// Restore prefered camera zoom
	gp->gameTracker.cameraDC[0].data40[6] = 1;

	// Hardcoding the speed-o-meter
	gp->HudAndDebugFlags |= 8;

	// Reset cheat string drawing
	p_rom->drawDuration = 0;
}

// This executes our mod each frame
void RunUpdateHook()
{
	int * driver;
	char * flyingStr;
	struct Driver * player;
	int countdown;
	int i;
	int j;

	// if you went from a level to main menu
	// or you went from the main menu to a level
	if (
		((p_rom->currlevel != levelMainMenu) && (gp->gameTracker.levelID == levelMainMenu)) ||
		((p_rom->currlevel == levelMainMenu) && (gp->gameTracker.levelID != levelMainMenu))
	   )
	{
		ResetLag();
	}

	p_rom->currlevel = gp->gameTracker.levelID;

	// if the last frame did not draw a checkered flag, and the current frame does, then you must be in a loading screen
	// reset lag
	if ((!p_rom->flagFrame) && (gp->gameTracker.renderFlags & 0x1000))
		ResetLag();

	if (gp->gameTracker.renderFlags & 0x1000)
		p_rom->flagFrame = 1;
	else
		p_rom->flagFrame = 0;

	DrawLag();

	// if the player is menuing
	if (gp->gameTracker.gameMode1 & (RACE_INTRO_CUTSCENE | MAIN_MENU | RACE_OUTRO_CUTSCENE | GAME_INTRO | LOADING))
	{
		ResetControlVariables();
		return;
	}

	countdown = gp->trafficLightsTimer_prevFrame;

	// if you're in time trial mode
	if (gp->gameTracker.gameMode1 == TIME_TRIAL)
	{
		// Disable mask, since loading a state with a mask can give you the powerup in time trial
		DisableMask();

		// if the save state slots aren't initialized
		if (!gp->gameTracker.drivers[1])
		{
			// Initializing memory to save instances
			p_rom->firstInstance = (int *) gp->mempack[0].firstFreeByte;
			p_rom->firstSound = p_rom->firstInstance + (instanceSize * numSlots);

			for (i = 0; i < numSlots; i++)
			{
				// initialize the other 5 empty drivers remaining
				gp->gameTracker.drivers[i + 1] = (struct Driver *) LIST_RemoveFront(&gp->gameTracker.AllocPools.largeStack.free);
				// clearing the 5 drivers to avoid silly side effects
				driver = (int *) gp->gameTracker.drivers[i + 1];
				for (j = 0; j < driverSize; j++)
					driver[j] = 0;

				p_rom->hasSaved[i] = 0;
			}
		}

		// Save State Cheat
		if (gp->gamepadSystem.controller[0].buttonsTapped & BTN_CIRCLE)
		{
			TemporarilyMuteFX();
			SaveState();
			SetSlotString(s_slotSaved, 1);
			p_rom->hasSaved[p_rom->slot] = 1;
		}

		// Load State Cheat
		if ((p_rom->hasSaved[p_rom->slot]) && (gp->gamepadSystem.controller[0].buttonsTapped & BTN_SELECT))
		{
			TemporarilyMuteFX();
			LoadState();
			SetSlotString(s_slotLoaded, 1);
		}

		// Select Slot Cheat
		if ((countdown == -0x3C0) && (gp->gamepadSystem.controller[0].buttonsTapped & BTN_L2))
		{
			p_rom->slot = (p_rom->slot + 1) % numSlots;
			SetSlotString(s_slotSelected, 1);

			gp->gamepadSystem.controller[0].buttonsTapped ^= BTN_L2;
		}
	}
	else
	{
		EnableMask();
	}

	if (!gp->boolDraw3D_AdvMask)
	{
		// Saffi Fire Cheat
		if (gp->gamepadSystem.controller[0].buttonsTapped & BTN_TRIANGLE)
		{
			// if the countdown to the race is over OR
			// you're in the adventure hub
			if ((countdown == -0x3C0) || (gp->gameTracker.gameMode1 == ADVENTURE_HUB))
			{
				gp->gameTracker.drivers[0]->reserves = saffi;
				SetSlotString(s_infiniteReserves, 0);
			}
			gp->gamepadSystem.controller[0].buttonsTapped ^= BTN_TRIANGLE;
		}

		// Flying Cheat
		if (
			(gp->gamepadSystem.controller[0].buttonsTapped & BTN_L3) ||
			(
			((gp->gamepadSystem.controller[0].buttonsHeldPrevFrame & BTN_FLY) != BTN_FLY) &&
				((gp->gamepadSystem.controller[0].buttonsHeldCurrFrame & BTN_FLY) == BTN_FLY)
			)
		)
		{
			if (p_rom->isFlying)
			{
				flyingStr = s_flyingCheatOff;
				p_rom->isFlying = 0;
				gp->gameTracker.drivers[0]->const_JumpForce = p_rom->jumpBackup;
			}
			else
			{
				p_rom->jumpBackup = gp->gameTracker.drivers[0]->const_JumpForce;
				gp->gameTracker.drivers[0]->const_JumpForce = jump;
				flyingStr = s_flyingCheatOn;
				p_rom->isFlying = 1;
			}
			SetSlotString(flyingStr, 0);
		}

		// Engine Swap cheat
		if (
			((gp->gamepadSystem.controller[0].buttonsHeldPrevFrame & BTN_ENGINE_SWAP) != BTN_ENGINE_SWAP) &&
				((gp->gamepadSystem.controller[0].buttonsHeldCurrFrame & BTN_ENGINE_SWAP) == BTN_ENGINE_SWAP)
			)
		{
			p_rom->engine = (p_rom->engine + 1) % numEngines;
			SetSlotString(engineStrings[p_rom->engine], 0);
			
			// Update engine
			p_rom->currEngine = &engineStrings[p_rom->engine][8];
			
			// swap engines
			data.MetaDataCharacters[data.characterIDs[0]].engineID = p_rom->engine;
			
			// initialize
			Driver_SetConsts(gp->gameTracker.drivers[0]);
		}

		// Change Camera Cheat
		if (gp->gamepadSystem.controller[0].buttonsTapped & BTN_R3)
		{
			// invert self
			gp->gameTracker.cameraDC[0].data40[6] = !gp->gameTracker.cameraDC[0].data40[6];
		}

		// Ghost cheat
		if (
			((gp->gamepadSystem.controller[0].buttonsHeldPrevFrame & BTN_SHOULDERS) != BTN_SHOULDERS) &&
				((gp->gamepadSystem.controller[0].buttonsHeldCurrFrame & BTN_SHOULDERS) == BTN_SHOULDERS)
			)
		{
			p_rom->isGhost ^= 1;
			if (p_rom->isGhost)
				SetSlotString(s_ghostModeOn, 0);
			else
				SetSlotString(s_ghostModeOff, 0);
			Ghostify(p_rom->isGhost);
		}

		if (p_rom->isFlying)
		{
			gp->gameTracker.drivers[0]->jump_CooldownMS = 0;
			gp->gameTracker.drivers[0]->jump_CoyoteTimerMS = 0xA0;
		}

		if (p_rom->isGhost)
		{
			Ghostify(p_rom->isGhost);
		}
	}

	if (p_rom->drawDuration > 0)
	{
		DrawSlotString();
		p_rom->drawDuration--;
	}

	if (p_rom->waitFrame)
		p_rom->waitFrame--;
	else
		gp->vol_FX = p_rom->fxVol;

	DrawDebugString();
}