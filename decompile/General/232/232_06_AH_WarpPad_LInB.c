#include <common.h>

void DECOMP_AH_WarpPad_LInB(struct Instance* inst)
{
	int i;
	int levelID;
	struct Thread* t;
	struct WarpPad* warppadObj;
	
	struct GameTracker* gGT;
	
	int unlockItem_numOwned;
	int unlockItem_numNeeded;
	int unlockItem_modelID;
	
	int* arrTokenCount;
	struct Instance* newInst;
	
	//for human reading purposes
	unsigned char ADV_CUP = 100;
	
	gGT = sdata->gGT;
	
    t =	
		DECOMP_PROC_BirthWithObject
		(
			SIZE_RELATIVE_POOL_BUCKET
			(
				sizeof(struct WarpPad), 
				NONE, 
				MEDIUM, 
				WARPPAD
			), 
			
			DECOMP_AH_WarpPad_ThTick,	// behavior
			0,					// debug name
			0					// thread relative
		);
		
	if(t == NULL) return;
	inst->thread = t;
	t->inst = inst;
	
	t->funcThDestroy = DECOMP_AH_WarpPad_ThDestroy;
	
	// 0 - locked
	// 1 - open for trophy
	// 2 - unlocked all
	// 3 - open for relic/token
	// 4 - purple token or SlideCol/TurboTrack
	
	// locked
	t->modelIndex = WARPPAD_LOCKED;
	
	// make invisible
	// this is the red triangle 
	// instance from DCxDemo's LEV Viewer
	inst->flags |= 0x80;
		
	warppadObj = t->object;
	warppadObj->levelID = 0; //this is dingo canyon
	warppadObj->boolEnteredWarppad = 0;
	warppadObj->framesWarping = 0;
	
	for(i = 0; i < WPIS_NUM_INSTANCES; i++)
		warppadObj->inst[i] = 0;
	
	// each warppad has a name "warppad#xxx"
	// "warppad#0" is dingo canyon, level ID 0
	// "warppad#16" is slide col, level ID 16
	// "warppad#102" is gem cup 2
	// "warppad#104" is gem cup 4
	// etc
	
	levelID = 0;
	for(i = 8; inst->name[i] != 0; i++)
	{
		levelID = levelID * 10 + inst->name[i] - '0';
	}
		
	warppadObj->levelID = levelID;
	
	unlockItem_numNeeded = -1;
	
	// Trophy Track
	if (levelID < SLIDE_COLISEUM)
	{
		// optimization idea:
		// instead of data.metaDataLEV[levelID].hubID
		// can we just do gGT->levelID-0x19?
		
		// if trophy owned
		if(CHECK_ADV_BIT(sdata->advProgress.rewards, (levelID + 6)) != 0)
		{
GetKeysRequirement:
			
			// keys needed to unlock track again
			unlockItem_modelID = STATIC_KEY;
			unlockItem_numOwned = gGT->currAdvProfile.numKeys;
			unlockItem_numNeeded = D232.arrKeysNeeded[data.metaDataLEV[levelID].hubID];
		}
		
		// if trophy not owned
		else
		{
			// number trophies needed to open
			unlockItem_modelID = STATIC_TROPHY;
			unlockItem_numOwned = gGT->currAdvProfile.numTrophies;
			unlockItem_numNeeded = data.metaDataLEV[levelID].numTrophiesToOpen;
		}
	}
	
	// Slide Col
	else if (levelID == SLIDE_COLISEUM)
	{
		// number relics needed to open
		unlockItem_modelID = STATIC_RELIC;
		unlockItem_numOwned = gGT->currAdvProfile.numRelics;
		unlockItem_numNeeded = 10;
	}
	
	// Turbo Track
	else if (levelID == TURBO_TRACK)
	{
		// number gems needed to open
		unlockItem_modelID = STATIC_GEM;
		unlockItem_numNeeded = 5;
		
		// count number of gems owned
		unlockItem_numOwned = 0;
		for(i = 0; i < 5; i++)
			if(CHECK_ADV_BIT(sdata->advProgress.rewards, (i + 0x6a)) != 0)
				unlockItem_numOwned++;
	}
	
	// battle maps
	else if (levelID < GEM_STONE_VALLEY)
	{
		goto GetKeysRequirement;
	}
	
	// gem cups
	else
	{
		// number tokens needed to open
		unlockItem_modelID = STATIC_TOKEN;
		unlockItem_numNeeded = 4;
		
		arrTokenCount = &gGT->currAdvProfile.numCtrTokens.red;
		unlockItem_numOwned = arrTokenCount[levelID - ADV_CUP];
	}
	
	// if unlocked
	if(unlockItem_numOwned >= unlockItem_numNeeded)
	{		
		warppadObj->digit1s = 0;
		
		// if beam model exists
		if(gGT->modelPtr[STATIC_BEAM] != 0)
		{
			newInst = DECOMP_INSTANCE_Birth3D(gGT->modelPtr[STATIC_BEAM], 0, t);
				
			// copy matrix
			*(int*)((int)&newInst->matrix + 0x0) = *(int*)((int)&inst->matrix + 0x0);
			*(int*)((int)&newInst->matrix + 0x4) = *(int*)((int)&inst->matrix + 0x4);
			*(int*)((int)&newInst->matrix + 0x8) = *(int*)((int)&inst->matrix + 0x8);
			*(int*)((int)&newInst->matrix + 0xC) = *(int*)((int)&inst->matrix + 0xC);
			*(short*)((int)&newInst->matrix + 0x10) = *(short*)((int)&inst->matrix + 0x10);
			newInst->matrix.t[0] = inst->matrix.t[0];
			newInst->matrix.t[1] = inst->matrix.t[1];
			newInst->matrix.t[2] = inst->matrix.t[2];
			
			newInst->alphaScale = 0xc00;
			
			warppadObj->inst[WPIS_OPEN_BEAM] = newInst;
		}
		
		// if spiral ring exists
		if(gGT->modelPtr[STATIC_BOTTOMRING] != 0)
		{
			for(i = 0; i < 2; i++)
			{
				newInst = DECOMP_INSTANCE_Birth3D(gGT->modelPtr[STATIC_BOTTOMRING], 0, t);
					
				// copy matrix
				*(int*)((int)&newInst->matrix + 0x0) = *(int*)((int)&inst->matrix + 0x0);
				*(int*)((int)&newInst->matrix + 0x4) = *(int*)((int)&inst->matrix + 0x4);
				*(int*)((int)&newInst->matrix + 0x8) = *(int*)((int)&inst->matrix + 0x8);
				*(int*)((int)&newInst->matrix + 0xC) = *(int*)((int)&inst->matrix + 0xC);
				*(short*)((int)&newInst->matrix + 0x10) = *(short*)((int)&inst->matrix + 0x10);
				newInst->matrix.t[0] = inst->matrix.t[0];
				newInst->matrix.t[1] = inst->matrix.t[1] + i * 0x400;
				newInst->matrix.t[2] = inst->matrix.t[2];
				
				newInst->alphaScale = 0x400;
				
				warppadObj->inst[WPIS_OPEN_RING1+i] = newInst;
			}
		}
		
		for(i = 0; i < 3; i++)
			warppadObj->thirds[i] = 0x555*i;
		
		warppadObj->spinRot_Prize[0] = 0;
		warppadObj->spinRot_Prize[1] = 0;
		warppadObj->spinRot_Prize[2] = 0;
		
		warppadObj->spinRot_Beam[0] = 0;
		warppadObj->spinRot_Beam[1] = 0;
		warppadObj->spinRot_Beam[2] = 0;
		
		for(i = 0; i < 2; i++)
		{
			warppadObj->spinRot_Wisp[i][0] = 0;
			warppadObj->spinRot_Wisp[i][1] = 0;
			warppadObj->spinRot_Wisp[i][2] = 0;
		}
	
		if(levelID < SLIDE_COLISEUM)
		{
			// unlocked all
			t->modelIndex = WARPPAD_EMPTY;
			
			// if trophy not owned
			if(CHECK_ADV_BIT(sdata->advProgress.rewards, (levelID + PRIZE_TROPHY_RACE)) == 0)
			{
				// open for trophy
				t->modelIndex = WARPPAD_TROPHY;
				
				newInst = DECOMP_INSTANCE_Birth3D(gGT->modelPtr[STATIC_TROPHY], 0, t);
				
				newInst->scale[0] = 0x2800;
				newInst->scale[1] = 0x2800;
				newInst->scale[2] = 0x2800;
				
				warppadObj->inst[WPIS_OPEN_PRIZE1] = newInst;
			}
			
			// if token not owned
			if(CHECK_ADV_BIT(sdata->advProgress.rewards, (levelID + PRIZE_TOKEN_RACE)) == 0)
			{
				// not open for trophy
				if(t->modelIndex != WARPPAD_TROPHY)
				{	
					// open for relic/token
					t->modelIndex = WARPPAD_TOKEN;
				}
BattleTrack:
				newInst = DECOMP_INSTANCE_Birth3D(gGT->modelPtr[STATIC_TOKEN], 0, t);
				
				// specular lighting
				newInst->flags |= 0x30000;
				
				newInst->scale[0] = 0x2000;
				newInst->scale[1] = 0x2000;
				newInst->scale[2] = 0x2000;
				
				i = data.metaDataLEV[levelID].ctrTokenGroupID;
				
				// token color
				newInst->colorRGBA =
					((unsigned int)data.AdvCups[i].color[0] << 0x14) |
					((unsigned int)data.AdvCups[i].color[1] << 0xc) |
					((unsigned int)data.AdvCups[i].color[2] << 0x4);
				
				// === Naughty Dog Bug ===
				// They made an array where every token color
				// could have it's own specular light, but they're
				// all the same specLight, so just use the first one
				
				// And because they're all identical, dont bother storing
				// it, just give a pointer to the global, instead of a 
				// pointer to warppadObj->specLight (ThTick and SpinRewards)
				#if 0
				warppadObj->specLightToken[0] = D232.specLightToken[0];
				warppadObj->specLightToken[1] = D232.specLightToken[1];
				warppadObj->specLightToken[2] = D232.specLightToken[2];
				#endif
				
				warppadObj->inst[WPIS_OPEN_PRIZE2] = newInst;
			}
			
SlideColTurboTrack:
			
			// if relic not owned
			if(levelID < NITRO_COURT) // check this cause of "goto BattleTrack"
			if(CHECK_ADV_BIT(sdata->advProgress.rewards, (levelID + PRIZE_RELIC_RACE)) == 0)
			{
				// SlideCol/TurboTrack
				if(levelID>=SLIDE_COLISEUM)
					t->modelIndex = WARPPAD_GEMSTONE_ACTIVE;
				
				// if not open for token/relic
				else if(t->modelIndex != WARPPAD_TROPHY)
					t->modelIndex = WARPPAD_RELIC;
				
				newInst = DECOMP_INSTANCE_Birth3D(gGT->modelPtr[STATIC_RELIC], 0, t);
				
				// relic blue
				newInst->colorRGBA = 0x20a5ff0;
				
				// specular lighting
				newInst->flags |= 0x20000;
				
				newInst->scale[0] = 0x1800;
				newInst->scale[1] = 0x1800;
				newInst->scale[2] = 0x1800;
				
				warppadObj->inst[WPIS_OPEN_PRIZE3] = newInst;
			}
			
			for(i = 0; i < 3; i++)
			{
				newInst = warppadObj->inst[WPIS_OPEN_PRIZE1+i];
				
				if(newInst == 0) continue;
			
				// copy matrix
				*(int*)((int)&newInst->matrix + 0x0) = *(int*)((int)&inst->matrix + 0x0);
				*(int*)((int)&newInst->matrix + 0x4) = *(int*)((int)&inst->matrix + 0x4);
				*(int*)((int)&newInst->matrix + 0x8) = *(int*)((int)&inst->matrix + 0x8);
				*(int*)((int)&newInst->matrix + 0xC) = *(int*)((int)&inst->matrix + 0xC);
				*(short*)((int)&newInst->matrix + 0x10) = *(short*)((int)&inst->matrix + 0x10);
				newInst->matrix.t[0] = inst->matrix.t[0];
				newInst->matrix.t[1] = inst->matrix.t[1] + 0x100;
				newInst->matrix.t[2] = inst->matrix.t[2];
			}
		}
		
		// slide col, turbo track
		else if(levelID < NITRO_COURT)
		{
			// already unlocked
			t->modelIndex = WARPPAD_EMPTY;
			
			goto SlideColTurboTrack;
		}
		
		// battle tracks
		else if(levelID < GEM_STONE_VALLEY)
		{
			i = R232.battleTrackArr[levelID - NITRO_COURT] + PRIZE_CRYSTAL_CH;
			
			// already unlocked
			t->modelIndex = WARPPAD_EMPTY;
			
			if(CHECK_ADV_BIT(sdata->advProgress.rewards, i) == 0)
			{	
				// rainbow
				t->modelIndex = WARPPAD_CRYSTALCH;
				
				goto BattleTrack;
			}
		}
		
		// gemstone valley
		else
		{	
			// bit index of gem
			i = (levelID - ADV_CUP) + PRIZE_GEM_CUP;
	
			// if gem is already unlocked, quit
			if(CHECK_ADV_BIT(sdata->advProgress.rewards, i) != 0)
			{
				// beaten
				t->modelIndex = WARPPAD_EMPTY;
				
				return;
			}
			
			// rainbow color
			t->modelIndex = WARPPAD_GEMSTONE_ACTIVE;
			
			newInst = DECOMP_INSTANCE_Birth3D(gGT->modelPtr[STATIC_GEM], 0, t);
				
			// specular lighting
			newInst->flags |= 0x20000;

			i = levelID - ADV_CUP;
		
			// token color
			newInst->colorRGBA =
				((unsigned int)data.AdvCups[i].color[0] << 0x14) |
				((unsigned int)data.AdvCups[i].color[1] << 0xc) |
				((unsigned int)data.AdvCups[i].color[2] << 0x4);
				
			warppadObj->inst[WPIS_OPEN_PRIZE1] = newInst;
			
			#if 0
			// store in Gem array
			warppadObj->specLightGem[0] = D232.specLightGem[0];
			warppadObj->specLightGem[1] = D232.specLightGem[1];
			warppadObj->specLightGem[2] = D232.specLightGem[2];
			#endif
			
			// for matrix copy
			goto SlideColTurboTrack;
		}
		
		return;
	}
	
	// === if locked ===

	if(unlockItem_numNeeded < 10)
	{
		warppadObj->digit10s = 0;
		warppadObj->digit1s = unlockItem_numNeeded;
	}
	
	else
	{
		warppadObj->digit10s = 1;
		warppadObj->digit1s = unlockItem_numNeeded - 10;
	}
	
	// ====== Item ========
	
	// WPIS_CLOSED_ITEM
	newInst = DECOMP_INSTANCE_Birth3D(gGT->modelPtr[unlockItem_modelID], 0, t);
		
	// copy matrix
	*(int*)((int)&newInst->matrix + 0x0) = *(int*)((int)&inst->matrix + 0x0);
	*(int*)((int)&newInst->matrix + 0x4) = *(int*)((int)&inst->matrix + 0x4);
	*(int*)((int)&newInst->matrix + 0x8) = *(int*)((int)&inst->matrix + 0x8);
	*(int*)((int)&newInst->matrix + 0xC) = *(int*)((int)&inst->matrix + 0xC);
	*(short*)((int)&newInst->matrix + 0x10) = *(short*)((int)&inst->matrix + 0x10);
	newInst->matrix.t[0] = inst->matrix.t[0];
	newInst->matrix.t[1] = inst->matrix.t[1] + 0x100;
	newInst->matrix.t[2] = inst->matrix.t[2];
	
	newInst->scale[0] = 0x2000;
	newInst->scale[1] = 0x2000;
	newInst->scale[2] = 0x2000;
	
	// no specular for trophy
	if(unlockItem_modelID != STATIC_TROPHY) 
	{
		// specular lighting
		newInst->flags |= 0x20000;
		
		// relic
		if(unlockItem_modelID == STATIC_RELIC)
		{
			// Relic blue color
			newInst->colorRGBA = 0x20a5ff0;
			
			#if 0
			warppadObj->specLightRelic[0] = D232.specLightRelic[0];
			warppadObj->specLightRelic[1] = D232.specLightRelic[1];
			warppadObj->specLightRelic[2] = D232.specLightRelic[2];
			#endif
		}
		
		// Key
		else if(unlockItem_modelID == STATIC_KEY)
		{
			// Key color
			newInst->colorRGBA = 0xdca6000;
			
			#if 0
			// store in Gem array (intended by ND, not a bug)
			warppadObj->specLightGem[0] = D232.specLightGem[0];
			warppadObj->specLightGem[1] = D232.specLightGem[1];
			warppadObj->specLightGem[2] = D232.specLightGem[2];
			#endif
		}
		
		// Gem
		else if(unlockItem_modelID == STATIC_GEM)
		{
			// dont set color, that gets set in ThTick
			
			#if 0
			// store in Gem array
			warppadObj->specLightGem[0] = D232.specLightGem[0];
			warppadObj->specLightGem[1] = D232.specLightGem[1];
			warppadObj->specLightGem[2] = D232.specLightGem[2];
			#endif
		}
		
		// assume token
		else
		{
			i = levelID - ADV_CUP;
			
			// token color
			newInst->colorRGBA =
				((unsigned int)data.AdvCups[i].color[0] << 0x14) |
				((unsigned int)data.AdvCups[i].color[1] << 0xc) |
				((unsigned int)data.AdvCups[i].color[2] << 0x4);
			
			// === Naughty Dog Bug ===
			// They made an array where every token color
			// could have it's own specular light, but they're
			// all the same specLight, so just use the first one
			
			#if 0
			warppadObj->specLightToken[0] = D232.specLightToken[0];
			warppadObj->specLightToken[1] = D232.specLightToken[1];
			warppadObj->specLightToken[2] = D232.specLightToken[2];
			#endif
		}
	}
	
	warppadObj->inst[WPIS_CLOSED_ITEM] = newInst;
	
	// ====== "X" ========
	
	// WPIS_CLOSED_X
	newInst = DECOMP_INSTANCE_Birth3D(gGT->modelPtr[STATIC_BIGX], 0, t);
	
	// copy matrix
	*(int*)((int)&newInst->matrix + 0x0) = 0x1000;
	*(int*)((int)&newInst->matrix + 0x4) = 0;
	*(int*)((int)&newInst->matrix + 0x8) = 0x1000;
	*(int*)((int)&newInst->matrix + 0xC) = 0;
	*(short*)((int)&newInst->matrix + 0x10) = 0x1000;
	newInst->matrix.t[0] = inst->matrix.t[0];
	newInst->matrix.t[1] = inst->matrix.t[1] + 0x100;
	newInst->matrix.t[2] = inst->matrix.t[2];
	
	newInst->scale[0] = 0x2000;
	newInst->scale[1] = 0x2000;
	newInst->scale[2] = 0x2000;
	
	// always face camera
	newInst->model->headers[0].flags |= 1;
	
	warppadObj->inst[WPIS_CLOSED_X] = newInst;
	
	// ====== "10s" ========
	
	if(warppadObj->digit10s != 0)
	{
		// WPIS_CLOSED_10S
		newInst = DECOMP_INSTANCE_Birth3D(gGT->modelPtr[STATIC_BIG1], 0, t);
		
		// copy matrix
		*(int*)((int)&newInst->matrix + 0x0) = 0x1000;
		*(int*)((int)&newInst->matrix + 0x4) = 0;
		*(int*)((int)&newInst->matrix + 0x8) = 0x1000;
		*(int*)((int)&newInst->matrix + 0xC) = 0;
		*(short*)((int)&newInst->matrix + 0x10) = 0x1000;
		newInst->matrix.t[0] = inst->matrix.t[0];
		newInst->matrix.t[1] = inst->matrix.t[1] + 0x100;
		newInst->matrix.t[2] = inst->matrix.t[2];
		
		newInst->scale[0] = 0x2000;
		newInst->scale[1] = 0x2000;
		newInst->scale[2] = 0x2000;
		
		// always face camera
		for(i = 0; i < newInst->model->numHeaders; i++)	
			newInst->model->headers[i].flags |= 1;
		
		warppadObj->inst[WPIS_CLOSED_10S] = newInst;
	}
	
	// ====== "1s" ========
	
	// STATIC_BIG (1-8)
	i = 0x38;
	if(warppadObj->digit1s == 0) i = 0x6d; // '0'
	if(warppadObj->digit1s == 9) i = 0x6e; // '9'
	
	// WPIS_CLOSED_1S
	newInst = DECOMP_INSTANCE_Birth3D(gGT->modelPtr[i], 0, t);
	
	// copy matrix
	*(int*)((int)&newInst->matrix + 0x0) = 0x1000;
	*(int*)((int)&newInst->matrix + 0x4) = 0;
	*(int*)((int)&newInst->matrix + 0x8) = 0x1000;
	*(int*)((int)&newInst->matrix + 0xC) = 0;
	*(short*)((int)&newInst->matrix + 0x10) = 0x1000;
	newInst->matrix.t[0] = inst->matrix.t[0];
	newInst->matrix.t[1] = inst->matrix.t[1] + 0x100;
	newInst->matrix.t[2] = inst->matrix.t[2];
	
	newInst->scale[0] = 0x2000;
	newInst->scale[1] = 0x2000;
	newInst->scale[2] = 0x2000;
			
	// always face camera
	for(i = 0; i < newInst->model->numHeaders; i++)	
		newInst->model->headers[i].flags |= 1;
	
	warppadObj->inst[WPIS_CLOSED_1S] = newInst;
}