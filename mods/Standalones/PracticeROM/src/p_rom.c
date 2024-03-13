#include "../p_rom.h"

void VehBirth_SetConsts(struct Driver *d);

#define NumbersToString Torch_Subset1
#define SaveState Torch_Subset4
#define LoadState Torch_Subset7 // can potentially move back to subset6

// Strings
char s_slotSelected[] = "Slot 1 selected";
char s_slotSaved[] = "Slot 1 saved";
char s_slotLoaded[] = "Slot 1 loaded";
char s_infiniteReserves[] = "Saffi activated";
char s_flyingCheatOn[] = "Flying cheat on";
char s_flyingCheatOff[] = "Flying cheat off";
char s_ghostModeOn[] = "Ghost mode on";
char s_ghostModeOff[] = "Ghost mode off";

extern char s_numbers[6];

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
char *engineStrings[numSlots] = {s_balancedEngine, s_accelEngine, s_speedEngine, s_turnEngine, s_pentaEngine};

enum ButtonsExtra
{
	BTN_GHOST = BTN_R2 | BTN_DOWN,
	BTN_FLY = BTN_CROSS | BTN_R2 | BTN_SQUARE,
	BTN_ENGINE_SWAP = BTN_UP | BTN_R2,
	BTN_SAFFI = BTN_R2 | BTN_TRIANGLE
};

void BackupInstructions()
{
	// Saving the mask instructions for non TT purposes
	p_rom->maskInstructions[0] = *(int *)(VehPickupItem_MaskUseWeapon);
	p_rom->maskInstructions[1] = *(int *)(VehPickupItem_MaskUseWeapon + 0x4);
	p_rom->maskInstructions[2] = *(int *)(VehPickupItem_MaskUseWeapon + 0x8);
}

void EnableMask()
{
	*(u_int *)(VehPickupItem_MaskUseWeapon) = p_rom->maskInstructions[0];
	*(u_int *)(VehPickupItem_MaskUseWeapon + 0x4) = p_rom->maskInstructions[1];
	*(u_int *)(VehPickupItem_MaskUseWeapon + 0x8) = p_rom->maskInstructions[2];
}

void DisableMask()
{
	// setting return value to null pointer (v0 = 0)
	*(u_int *)(VehPickupItem_MaskUseWeapon) = 0x00001020;
	// jr ra
	*(u_int *)(VehPickupItem_MaskUseWeapon + 0x4) = 0x03E00008;
	// NOP to avoid making any register dirty
	*(u_int *)(VehPickupItem_MaskUseWeapon + 0x8) = 0x00000000;
}

// to do: should hook main(),
// right now happens at threadbuckets
void RunInitHook()
{
	p_rom = (struct P_ROM *)0x8000F000;

	if (p_rom->swappedEngine == false)
		p_rom->engine = data.MetaDataCharacters[data.characterIDs[0]].engineID;

	p_rom->currEngine = &engineStrings[p_rom->engine][8];
	data.MetaDataCharacters[data.characterIDs[0]].engineID = p_rom->engine;
	VehBirth_SetConsts(sdata->gameTracker.drivers[0]);

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

void SetSlotString(char *str, char slot)
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
		DecalFont_DrawLine(p_rom->slotString, 256, 39, FONT_SMALL, ORANGE | JUSTIFY_CENTER);
	else
		DecalFont_DrawLine(p_rom->slotString, 256, 22, FONT_SMALL, ORANGE | JUSTIFY_CENTER);
}

void ResetLag()
{
	p_rom->lagFrames = 0;
	p_rom->lagTime = 0;
	p_rom->lagDuration = 0;
}

void DrawLag()
{
	unsigned short ms = sdata->gameTracker.elapsedTimeMS;
	NumbersToString(s_ms, ms, 3);

	if (ms > msFrame)
	{
		DecalFont_DrawLine(s_ms, 256, 8, FONT_SMALL, RED | JUSTIFY_CENTER);
		p_rom->lagFrames++;
		p_rom->lagTime += (ms - msFrame);
		p_rom->lagDuration = textDuration;
	}
	else
	{
		DecalFont_DrawLine(s_ms, 256, 8, FONT_SMALL, ORANGE | JUSTIFY_CENTER);
		if (p_rom->lagDuration)
			p_rom->lagDuration--;
		else
			ResetLag();
	}

	if (p_rom->lagDuration)
	{
		DecalFont_DrawLine(s_frames, x_frames, y_frames, FONT_SMALL, RED);
		DecalFont_DrawLine(s_total, x_total, y_total, FONT_SMALL, RED);

		NumbersToString(s_numbers, p_rom->lagFrames, 4);
		DecalFont_DrawLine(s_numbers, x_numFrames, y_numFrames, FONT_SMALL, RED);

		NumbersToString(s_lag, p_rom->lagTime, 5);
		DecalFont_DrawLine(s_lag, x_lag, y_lag, FONT_SMALL, RED);
	}
}

void TemporarilyMuteFX()
{
	p_rom->fxVol = sdata->vol_FX;
	sdata->vol_FX = 0;
	p_rom->waitFrame = 1;
}

void Instance_Ghostify(struct Instance *inst, char isDriver, char becomeGhost)
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
		if (sdata->gameTracker.drivers[0]->reserves)
			inst->alphaScale = 0x600;
	}
}

void Ghostify(char becomeGhost)
{
	struct Turbo *turboObj;
	struct Thread *fireThread;
	struct GameTracker *gGT = sdata->gGT;
	struct Icon **ptrIconArray;

	if (becomeGhost)
		ptrIconArray = ICONGROUP_GETICONS(gGT->iconGroup[0xC]);
	else
		ptrIconArray = ICONGROUP_GETICONS(gGT->iconGroup[0]);

	gGT->drivers[0]->wheelSprites = ptrIconArray;

	Instance_Ghostify(gGT->drivers[0]->instSelf, 1, becomeGhost);

	fireThread = gGT->threadBuckets[TURBO].thread;
	if (!fireThread)
		return;

	turboObj = (struct Turbo *)fireThread->object;
	Instance_Ghostify(fireThread->inst, 0, becomeGhost);
	Instance_Ghostify(turboObj->inst, 0, becomeGhost);
}

void ResetControlVariables()
{
	int i;

	// Saving fx volume
	p_rom->fxVol = sdata->vol_FX;

	// Reset flying cheat
	p_rom->isFlying = 0;

	// Reset ghost cheat
	p_rom->isGhost = 0;

	// Reset save slot
	p_rom->slot = 0;

	// Restore prefered camera zoom
	sdata->gGT->cameraDC[0].nearOrFar = 1;

	// Hardcoding the speed-o-meter
	sdata->HudAndDebugFlags |= 8;

	// Reset cheat string drawing
	p_rom->drawDuration = 0;
}

// This executes our mod each frame
void RunUpdateHook()
{
	int *driver;
	char *flyingStr;
	int countdown;
	int i;
	int j;
	struct GameTracker *gGT = sdata->gGT;
	struct Driver *player = gGT->drivers[0];
	struct GamepadBuffer *pad = &sdata->gGamepads->gamepad[0];

	// if you went from a level to main menu
	// or you went from the main menu to a level
	if (
		((p_rom->currlevel != MAIN_MENU_LEVEL) && (gGT->levelID == MAIN_MENU_LEVEL)) ||
		((p_rom->currlevel == MAIN_MENU_LEVEL) && (gGT->levelID != MAIN_MENU_LEVEL)))
	{
		ResetLag();
	}

	p_rom->currlevel = gGT->levelID;

	// if the last frame did not draw a checkered flag, and the current frame does, then you must be in a loading screen
	// reset lag
	if ((!p_rom->flagFrame) && (gGT->renderFlags & 0x1000))
		ResetLag();

	if (gGT->renderFlags & 0x1000)
		p_rom->flagFrame = 1;
	else
		p_rom->flagFrame = 0;

	DrawLag();

	// if the player is menuing
	if (gGT->gameMode1 & (START_OF_RACE | MAIN_MENU | END_OF_RACE | GAME_CUTSCENE | LOADING | PAUSE_ALL) || (gGT->numPlyrNextGame > 1))
	{
		ResetControlVariables();
		return;
	}

	countdown = sdata->trafficLightsTimer_prevFrame;
	u_int tapped = pad->buttonsTapped;

	// if you're in time trial mode
	if (gGT->gameMode1 & TIME_TRIAL)
	{
		// Disable mask, since loading a state with a mask can give you the powerup in time trial
		DisableMask();

		// if the save state slots aren't initialized
		if (!gGT->drivers[1])
		{
			// Initializing memory to save instances
			p_rom->firstInstance = (int *)sdata->mempack[0].firstFreeByte;
			p_rom->firstSound = p_rom->firstInstance + (instanceSize * numSlots);

			for (i = 0; i < numSlots; i++)
			{
				// initialize the other 5 empty drivers remaining
				gGT->drivers[i + 1] = (struct Driver *)LIST_RemoveFront(&gGT->JitPools.largeStack.free);
				// clearing the 5 drivers to avoid silly side effects
				driver = (int *)gGT->drivers[i + 1];
				for (j = 0; j < driverSize; j++)
					driver[j] = 0;

				p_rom->hasSaved[i] = 0;
			}
		}

		// Save State Cheat
		if (tapped & BTN_CIRCLE)
		{
			TemporarilyMuteFX();
			SaveState();
			SetSlotString(s_slotSaved, 1);
			p_rom->hasSaved[p_rom->slot] = 1;
		}

		// Load State Cheat
		if ((p_rom->hasSaved[p_rom->slot]) && (tapped & BTN_SELECT))
		{
			TemporarilyMuteFX();
			LoadState();
			SetSlotString(s_slotLoaded, 1);
		}

		// Select Slot Cheat
		if ((countdown == -960) && (tapped & BTN_L2))
		{
			p_rom->slot = (p_rom->slot + 1) % numSlots;
			SetSlotString(s_slotSelected, 1);

			tapped ^= BTN_L2;
		}
	}
	else
	{
		EnableMask();
	}

	if (!sdata->boolDraw3D_AdvMask)
	{
		// Saffi Fire Cheat
		if (((pad->buttonsHeldPrevFrame & BTN_SAFFI) != BTN_SAFFI) &&
			((pad->buttonsHeldCurrFrame & BTN_SAFFI) == BTN_SAFFI))
		{
			// if the countdown to the race is over OR
			// you're in the adventure hub
			if ((countdown == -960) || (gGT->gameMode1 & ADVENTURE_ARENA))
			{
				player->reserves = saffi;
				SetSlotString(s_infiniteReserves, 0);
			}
		}

		// Flying Cheat
		if ((tapped & BTN_L3) ||
			(((pad->buttonsHeldPrevFrame & BTN_FLY) != BTN_FLY) &&
			 ((pad->buttonsHeldCurrFrame & BTN_FLY) == BTN_FLY)))
		{
			if (p_rom->isFlying)
			{
				flyingStr = s_flyingCheatOff;
				p_rom->isFlying = 0;
				player->const_JumpForce = p_rom->jumpBackup;
			}
			else
			{
				p_rom->jumpBackup = player->const_JumpForce;
				player->const_JumpForce = jump;
				flyingStr = s_flyingCheatOn;
				p_rom->isFlying = 1;
			}
			SetSlotString(flyingStr, 0);
		}

		// Engine Swap cheat
		if (((pad->buttonsHeldPrevFrame & BTN_ENGINE_SWAP) != BTN_ENGINE_SWAP) &&
			((pad->buttonsHeldCurrFrame & BTN_ENGINE_SWAP) == BTN_ENGINE_SWAP))
		{
			p_rom->swappedEngine = true;
			u_char swapEngine = (p_rom->engine + 1) % numEngines;
			p_rom->engine = swapEngine;
			SetSlotString(engineStrings[swapEngine], 0);

			// Update engine
			p_rom->currEngine = &engineStrings[swapEngine][8];

			int *prevEngine = &data.MetaDataCharacters[data.characterIDs[0]].engineID;

			// stop current engine sound
			EngineAudio_Stop(*prevEngine * 4);

			// swap engines
			*prevEngine = swapEngine;

			EngineAudio_InitOnce(swapEngine * 4, 0x8080);
			VehBirth_SetConsts(player);
		}

		// Change Camera Cheat
		if (tapped & BTN_R3)
		{
			// invert self
			gGT->cameraDC[0].nearOrFar ^= true;
		}

		// Ghost cheat
		if (((pad->buttonsHeldPrevFrame & BTN_GHOST) != BTN_GHOST) &&
			((pad->buttonsHeldCurrFrame & BTN_GHOST) == BTN_GHOST))
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
			gGT->drivers[0]->jump_CooldownMS = 0;
			gGT->drivers[0]->jump_CoyoteTimerMS = 0xA0;
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
		sdata->vol_FX = p_rom->fxVol;
}

void RunEntryHook()
{
	// Don't enable vibration by default
	sdata->gGT->gameMode1 |= P1_VIBRATE;
}

void LOAD_Callback_230_hook()
{
	*(int *)&sdata->gameProgress.unlocks[0] = -1;
	*(int *)&sdata->gameProgress.unlocks[1] = -1;
}