#include <common.h>

// budget: 4992

void AH_WarpPad_ThTick(struct Thread* t)
{
	int i;
	int boolOpen;
	struct GameTracker* gGT;
	struct WarpPad* warppadObj;
	struct Instance* warppadInst;
	struct Instance** visInstSrc;
	struct Instance** instArr;
	
	struct Driver* driver;
	struct Instance* driverInst;
	
	int modelID;
	int levelID;
	int x,y,z,dist;
	char* warppadLNG;
	
	int angleCamToWarppad;
	int angleSin, angleCos;
	MATRIX* warppadMatrix;
	
	int wispMaxHeight;
	int wispRiseRate;
	int rng1;
	int rng2;
	
	boolOpen = 0;
	gGT = sdata->gGT;
	warppadObj = t->object;
	warppadInst = t->inst;
	visInstSrc = gGT->cameraDC[0].visInstSrc;
	
	while(visInstSrc[0] != 0)
	{
		if(visInstSrc[0] == warppadInst)
		{
			boolOpen = 1;
			break;
		}
		
		visInstSrc++;
	}
	
	// array of instances in warppad object
	instArr = &warppadObj->inst[0];
	warppadMatrix = &warppadInst->matrix;
	
	// make instances visible
	if(boolOpen == 1)
	{
		for(i = 0; i < WPIS_NUM_INSTANCES; i++)
			instArr[i]->flags &= ~(0x80);
	}
	
	// make instances invisible
	else
	{
		for(i = 0; i < WPIS_NUM_INSTANCES; i++)
			instArr[i]->flags |= 0x80;
	}
	
	// This is the red triangle in DCxDemo's
	// level viewer, make it invisible. 
	// Instance only exists for debugging
	warppadInst->flags |= 0x80;
	
	driver = gGT->drivers[0];
	driverInst = driver->instSelf;
	
	x = warppadMatrix->t[0] - driverInst->matrix.t[0];
	y = warppadMatrix->t[1] - driverInst->matrix.t[1];
	z = warppadMatrix->t[2] - driverInst->matrix.t[2];
	dist = x*x + y*y + z*z;
	
	levelID = warppadObj->levelID;
	
	// if near a portal
	if(
		// Trophy tracks
		((((unsigned short)(levelID))		< 0x10)	&& (dist < 0x144000)) ||
		
		// Slide Col + Turbo Track
		((((unsigned short)(levelID-0x10))	< 2) 	&& (dist < 0x90000)) ||
		
		// Battle tracks
		((((unsigned short)(levelID-0x12))	< 7)	&& (dist < 0x144000)) ||
		
		// Gem cups
		((((unsigned short)(levelID))		> 99)	&& (dist < 0x90000))
	  )
	{
		// if you are near a new warppad, or if you already were
		// determined as near the same warppad in the last frame,
		// then use this warppad as the "closest". Otherwise the
		// game could run this for two warppads right next to each other
		if(
				(*(short*)0x800b4e86 == -1) ||
				(*(short*)0x800b4e86 == levelID)
		  )
		{
			// saved as nearest warppad
			*(short*)0x800b4e86 = levelID;
			
			// if not giving Aku Hint
			if(sdata->AkuAkuHintState == 0)
			{
				// default
				warppadLNG = 
						sdata->lngStrings
						[data.metaDataLEV[levelID].name_LNG];
				
				// gem cups
				if(levelID > 99)
					warppadLNG = 
						sdata->lngStrings
						[data.AdvCups[levelID-100].lngIndex_CupName];
				
				// midpoing X,
				// 30 pixels above botttom Y
				DecalFont_DrawLine
				(
					warppadLNG,
					gGT->tileView[0].rect.x + gGT->tileView[0].rect.w/2,
					gGT->tileView[0].rect.x + gGT->tileView[0].rect.h - 30,
					FONT_BIG, (CENTER_TEXT | ORANGE)
				);
			}
			
			// if track is unlocked, ignore all other ELSE-IFs
			if(instArr[WPIS_CLOSED_1S] == 0) {}
			
			else if
			  (

				// gem cup
				(levelID > 99) &&
				
				// Dont have hint "you must have 4 tokens for a gem"
				((sdata->advProgress.rewards[4] & 0x20000) == 0)
				
			   )
			{
				// give hint "you must have 4 tokens for a gem"
				MainFrame_RequestMaskHint(0x1b, 0);
			}
			
			else if
			   (
			   
				// Trophy track
				(levelID < 0x10) &&
				
				// Dont have hint "you must have more trophies"
				((sdata->advProgress.rewards[3] & 0x1000000) == 0) &&
				
				// required item is not KEY
				(instArr[WPIS_CLOSED_ITEM]->model->id != 99)
			   )
			{
				// give hint for "need more trophies"
				MainFrame_RequestMaskHint(2, 0);
			}
			
			else if
			   (
				
				// Slide Col
				(levelID == 0x10) &&
				
				// Dont have hint "you must have 10 relics"
				((sdata->advProgress.rewards[4] & 0x40000) == 0)
			   )
			{
				// give hint for "need more trophies"
				MainFrame_RequestMaskHint(0x1C, 0);
			}
		}
	}
	
	// not near portal
	else
	{
		*(short*)0x800b4e86 = -1;
	}
	
	// if warppad is locked
	if (instArr[WPIS_CLOSED_1S] != 0)
	{	
		angleCamToWarppad =
			ratan2(
				warppadMatrix->t[0] - gGT->tileView[0].pos[0],
				warppadMatrix->t[2] - gGT->tileView[0].pos[2]
			);
			
		angleCamToWarppad = -angleCamToWarppad;
		
		angleSin = MATH_Sin(angleCamToWarppad);
		angleCos = MATH_Cos(angleCamToWarppad);
		
		// no 10s digit
		if(instArr[WPIS_CLOSED_10S] == 0)
		{
			instArr[WPIS_CLOSED_1S]->matrix.t[0] = warppadMatrix->t[0] + (angleCos * -0x80 >> 0xC);
			instArr[WPIS_CLOSED_1S]->matrix.t[2] = warppadMatrix->t[2] + (angleSin * -0x80 >> 0xC);
			
			instArr[WPIS_CLOSED_ITEM]->matrix.t[0] = warppadMatrix->t[0] + ((angleCos << 7) >> 0xC);
			instArr[WPIS_CLOSED_ITEM]->matrix.t[2] = warppadMatrix->t[2] + ((angleSin << 7) >> 0xC);
		}
		
		// 10s digit
		else
		{
			instArr[WPIS_CLOSED_ITEM]->matrix.t[0] = warppadMatrix->t[0] + (angleCos * 0xC0 >> 0xC);
			instArr[WPIS_CLOSED_ITEM]->matrix.t[2] = warppadMatrix->t[2] + (angleSin * 0xC0 >> 0xC);
			
			instArr[WPIS_CLOSED_X]->matrix.t[0] = warppadMatrix->t[0] + ((angleCos << 6) >> 0xC);
			instArr[WPIS_CLOSED_X]->matrix.t[2] = warppadMatrix->t[2] + ((angleSin << 6) >> 0xC);
			
			instArr[WPIS_CLOSED_10S]->matrix.t[0] = warppadMatrix->t[0] + (angleCos * -0x40 >> 0xC);
			instArr[WPIS_CLOSED_10S]->matrix.t[2] = warppadMatrix->t[2] + (angleSin * -0x40 >> 0xC);
			
			instArr[WPIS_CLOSED_1S]->matrix.t[0] = warppadMatrix->t[0] + (angleCos * -0xa0 >> 0xC);
			instArr[WPIS_CLOSED_1S]->matrix.t[2] = warppadMatrix->t[2] + (angleSin * -0xa0 >> 0xC);
		}
		
		warppadObj->spinRot_Prize[0] = 0;
		warppadObj->spinRot_Prize[2] = 0;
		
		warppadObj->spinRot_Prize[1] += 0x40;
		
		// reuse variable,
		// end of function anyway
		warppadInst = instArr[WPIS_CLOSED_ITEM];
		#define InstArr0 warppadInst
		
		ConvertRotToMatrix(
			&InstArr0->matrix,
			&warppadObj->spinRot_Prize[0]);
		
		modelID = InstArr0->model->id;
		
		// If Gem, change colors every 2 seconds
		if(modelID == 0x5f)
		{
			i = (gGT->timer / 0x3C) % 5;
			
			InstArr0->colorRGBA =
				((unsigned int)data.AdvCups[i].color[0] << 0x14) |
				((unsigned int)data.AdvCups[i].color[1] << 0xc) |
				((unsigned int)data.AdvCups[i].color[2] << 0x4);
				
			Vector_SpecLightSpin3D(InstArr0, &warppadObj->spinRot_Prize[0], &warppadObj->specLightGem[0]);
			return;
		}
		
		// Relic
		if(modelID == 0x61) 
		{
			Vector_SpecLightSpin3D(InstArr0, &warppadObj->spinRot_Prize[0], &warppadObj->specLightRelic[0]);
			return;
		}
		
		// Token
		if(modelID == 0x7d) 
		{
			Vector_SpecLightSpin3D(InstArr0, &warppadObj->spinRot_Prize[0], &warppadObj->specLightToken[0]);
			return;
		}
		
		return;
	}
	
	// === Assume Unlocked ===
	
	// [Skip block that loads track]
	// Read ghidra "DontLoadLevelYet"
	// That goes below, and then the code
	// between LAB_800ac860 and LAB_800acef8
	// will be at the bottom
	
	if(
		(instArr[WPIS_OPEN_BEAM] != 0) &&
		((gGT->timer & 1) != 0)
	  )
	{	
		warppadObj->spinRot_Beam[0] = 0;
		warppadObj->spinRot_Beam[2] = 0;
		
		// what on earth was this RNG?
		// how'd they come up with something so random, that looks so good?
		i = MixRNG_Scramble();
		warppadObj->spinRot_Beam[1] += ((short)(i >> 3) + (short)((i >> 3) / 6) * -6 + 1) * 0x200;
	
		ConvertRotToMatrix(
			&instArr[WPIS_OPEN_BEAM]->matrix, 
			&warppadObj->spinRot_Beam[0]);
	}
	
	wispRiseRate = 0x20;
	
	wispMaxHeight = 0x600;
	
	// if close to this warppad
	if(*(short*)0x800b4e86 != -1)
		wispMaxHeight = 0x400;
	
	for(i = 0; i < 2; i++)
	{
		if(instArr[WPIS_OPEN_RING1+i] != 0)
		{			
			warppadObj->spinRot_Wisp[i][0] = 0;
			warppadObj->spinRot_Wisp[i][2] = 0;
			
			warppadObj->spinRot_Wisp[i][1] += 0x100;
			
			ConvertRotToMatrix(
				&instArr[WPIS_OPEN_RING1+i]->matrix, 
				&warppadObj->spinRot_Wisp[i][0]);
			
			// if height hasn't reached max height
			if(
				instArr[WPIS_OPEN_RING1+i]->matrix.t[1] < 
				(warppadInst->matrix.t[1] + wispMaxHeight)
			  )
			{
				instArr[WPIS_OPEN_RING1+i]->matrix.t[1] += wispRiseRate;
				
				// if height hasn't reached 4x RiseRate,
				// first 4 frames of rising
				if(
					instArr[WPIS_OPEN_RING1+i]->matrix.t[1] < 
					(warppadInst->matrix.t[1] + wispRiseRate*4)
				)
				{
					// reduce transparency
					instArr[WPIS_OPEN_RING1+i]->alphaScale -= 0x380;
				}
				
				// after first 4 frames
				else
				{
					// add transparency as the wisp spirals upward (~0x60  per frame)
					instArr[WPIS_OPEN_RING1+i]->alphaScale += 0xc00 / (wispMaxHeight/wispRiseRate);
				}
			}
			
			// eached max height
			else
			{
				// reset height
				instArr[WPIS_OPEN_RING1+i]->matrix.t[1] = warppadInst->matrix.t[1];
				
				// full transparency
				instArr[WPIS_OPEN_RING1+i]->alphaScale = 0x1000;
				
				rng1 = MixRNG_Scramble() >> 3;
				
				rng2 = rng1;
				if(rng1 < 0)
					rng2 = rng1 + 0xfff;
				
				warppadObj->spinRot_Wisp[i][1] = (short)rng1 + (short)(rng2 >> 0xc) * -0x1000;
			}
		}
		
		wispRiseRate += 0x10;
	}
	
	// [ continue here, ghidra line 1260 ]
	
	warppadObj->spinRot_Prize[1] += 0x80;
	
	// [...]
	
	for(i = 0; i < 3; i++)
	{
		if(instArr[WPIS_OPEN_PRIZE1+i] != 0)
		{
			AH_WarpPad_SpinRewards(
				instArr[WPIS_OPEN_PRIZE1+i],
				warppadObj, i,
				warppadInst->matrix.t[0],
				warppadInst->matrix.t[1],
				warppadInst->matrix.t[2]);
				
			// [set scale]
			// [set visibility]
		}
			
		warppadObj->thirds[i] += 0x20;
		warppadObj->spinRot_Rewards[1] += 0x4;
			
	}
	
	// [if unlocked, erase locked instances]
	// would those ever initialize anyway?
	
	
	
	// [remove this, put it in GameProg.h]
// copy/paste from GameProg
#define CHECK_ADV_BIT(rewards, bitIndex) \
	((rewards[bitIndex>>5] >> (bitIndex & 0x1f)) & 1) != 0
	
	
	
	// [temporary]
	// This is all rough draft, not copied from ghidra,
	// just eye-balling how this should work...
	
	// if flag is on-screen, loading has already been finalized
	if(TitleFlag_IsTransitioning() != 0) return;
	
	// dont load track far away
	if(dist > 0x8fff) return;
	
	// only works for trophy tracks rn
	if(levelID >= 0x10) return;
	
	void VehPtr_Freeze_Init();
	gGT->drivers[0]->funcPtrs[0] = VehPtr_Freeze_Init;
	
	// if trophy is unlocked
	if(CHECK_ADV_BIT(sdata->advProgress.rewards, levelID + 6))
	{
		// if never opened
		if(sdata->boolOpenTokenRelicMenu == 0)
		{
			// now opened
			sdata->boolOpenTokenRelicMenu = 1;
			
			MenuBox_Show(0x800b4e50);
			
			// dont load level
			return;
		}
		
		// if opened, but not closed yet
		if((MenuBox_BoolHidden(0x800b4e50) & 0xffff) == 0)
		{
			// dont load level
			return;
		}
		
		// if opened, then closed
		else
		{
			// reset for future gameplay
			sdata->boolOpenTokenRelicMenu = 0;
			
			sdata->ptrActiveMenuBox = 0;
			
			// [no return, allow level to load]
		}
	}
	
	// === Will allow Trophy Tracks to load ===
	// Any portal with levelID >= 0x10 will break here
	
	MainRaceTrack_RequestLoad(levelID);
}