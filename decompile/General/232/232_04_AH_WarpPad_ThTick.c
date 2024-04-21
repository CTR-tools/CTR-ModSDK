#include <common.h>

void DECOMP_AH_WarpPad_ThTick(struct Thread* t)
{
	int i;
	int j;
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
	
	int rewardScale;
	int rewardScale2;
	
	int champID;
	int champSlot;
	
	char randKartSpawn[8];
	
	boolOpen = 0;
	gGT = sdata->gGT;
	warppadObj = t->object;
	warppadInst = t->inst;
	visInstSrc = gGT->cameraDC[0].visInstSrc;
	
#ifndef REBUILD_PS1
	while(visInstSrc[0] != 0)
	{
		if(visInstSrc[0] == warppadInst)
		{
			boolOpen = 1;
			break;
		}
		
		visInstSrc++;
	}
#else
	boolOpen = 1;
#endif
	
	// array of instances in warppad object
	instArr = &warppadObj->inst[0];
	warppadMatrix = &warppadInst->matrix;
	
	// make instances visible
	if(boolOpen == 1)
	{
		for(i = 0; i < WPIS_NUM_INSTANCES; i++)
			if (instArr[i] != 0)
				instArr[i]->flags &= ~(0x80);
	}
	
	// make instances invisible
	else
	{
		for(i = 0; i < WPIS_NUM_INSTANCES; i++)
			if (instArr[i] != 0)
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
		((((unsigned short)(levelID))		>= 100)	&& (dist < 0x90000))
	  )
	{
		// if you are near a new warppad, or if you already were
		// determined as near the same warppad in the last frame,
		// then use this warppad as the "closest". Otherwise the
		// game could run this for two warppads right next to each other
		if(
				(D232.levelID == -1) ||
				(D232.levelID == levelID)
		  )
		{
			// saved as nearest warppad
			D232.levelID = levelID;
			
			// if not giving Aku Hint
			if(sdata->AkuAkuHintState == 0)
			{
				// default
				if(levelID < 100)
					warppadLNG = 
						sdata->lngStrings
						[data.metaDataLEV[levelID].name_LNG];
				
				// gem cups
				else
					warppadLNG = 
						sdata->lngStrings
						[data.AdvCups[levelID-100].lngIndex_CupName];
				
				// midpoing X,
				// 30 pixels above botttom Y
				DECOMP_DecalFont_DrawLine
				(
					warppadLNG,
					gGT->pushBuffer[0].rect.x + gGT->pushBuffer[0].rect.w/2,
					gGT->pushBuffer[0].rect.x + gGT->pushBuffer[0].rect.h - 30,
					FONT_BIG, (JUSTIFY_CENTER | ORANGE)
				);
			}
			
			// if track is unlocked, ignore all other ELSE-IFs
			if(instArr[WPIS_CLOSED_1S] == 0) {}
			
			else if
			  (

				// gem cup
				(levelID >= 100) &&
				
				// Dont have hint "you must have 4 tokens for a gem"
				((sdata->advProgress.rewards[4] & 0x20000) == 0)
				
			   )
			{
				// give hint "you must have 4 tokens for a gem"
				DECOMP_MainFrame_RequestMaskHint(0x1b, 0);
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
				DECOMP_MainFrame_RequestMaskHint(2, 0);
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
				DECOMP_MainFrame_RequestMaskHint(0x1C, 0);
			}
		}
	}
	
	// not near portal
	else
	{
		D232.levelID = -1;
	}
	
	// if warppad is locked
	if (instArr[WPIS_CLOSED_1S] != 0)
	{	
		angleCamToWarppad =
			ratan2(
				warppadMatrix->t[0] - gGT->pushBuffer[0].pos[0],
				warppadMatrix->t[2] - gGT->pushBuffer[0].pos[2]
			);
			
		angleCamToWarppad = -angleCamToWarppad;
		
		angleSin = DECOMP_MATH_Sin(angleCamToWarppad);
		angleCos = DECOMP_MATH_Cos(angleCamToWarppad);
		
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
		
		warppadObj->spinRot_Prize[1] += FPS_HALF(0x40);
		
		// reuse variable,
		// end of function anyway
		warppadInst = instArr[WPIS_CLOSED_ITEM];
		#define InstArr0 warppadInst
		
		// converted to TEST in rebuildPS1
		ConvertRotToMatrix(
			&InstArr0->matrix,
			&warppadObj->spinRot_Prize[0]);
		
		modelID = InstArr0->model->id;

#ifndef REBUILD_PS1
		// Trophy has no specular light
		if(modelID == 0x62) return;
		
		// OG code had pointers to warppadObj->specLightXXX
		// but that was replaced with pointers to globals,
		// because the arrays didnt actually change per warppad
				
		// Relic
		if(modelID == 0x61) 
		{
			Vector_SpecLightSpin3D(InstArr0, &warppadObj->spinRot_Prize[0], &D232.specLightRelic[0]);
			return;
		}
		
		// Token
		if(modelID == 0x7d) 
		{
			Vector_SpecLightSpin3D(InstArr0, &warppadObj->spinRot_Prize[0], &D232.specLightToken[0]);
			return;
		}
		
		// If Gem, change colors every 2 seconds
		if(modelID == 0x5f)
		{
			i = (gGT->timer / FPS_DOUBLE(0x3C)) % 5;
			
			InstArr0->colorRGBA =
				((unsigned int)data.AdvCups[i].color[0] << 0x14) |
				((unsigned int)data.AdvCups[i].color[1] << 0xc) |
				((unsigned int)data.AdvCups[i].color[2] << 0x4);
				
		}
		
		// for Key or Gem
		Vector_SpecLightSpin3D(InstArr0, &warppadObj->spinRot_Prize[0], &D232.specLightGem[0]);
#endif
		return;
	}
	
	// === Assume Unlocked ===
	
	if(
		(instArr[WPIS_OPEN_BEAM] != 0) &&
		((gGT->timer & FPS_DOUBLE(1)) != 0)
	  )
	{	
		warppadObj->spinRot_Beam[0] = 0;
		warppadObj->spinRot_Beam[2] = 0;
		
		// what on earth was this RNG?
		// how'd they come up with something so random, that looks so good?
		i = DECOMP_MixRNG_Scramble();
		warppadObj->spinRot_Beam[1] += ((short)(i >> 3) + (short)((i >> 3) / 6) * -6 + 1) * 0x200;
	
		// converted to TEST in rebuildPS1
		ConvertRotToMatrix(
			&instArr[WPIS_OPEN_BEAM]->matrix, 
			&warppadObj->spinRot_Beam[0]);
	}
	
	wispRiseRate = FPS_HALF(0x20);
	
	wispMaxHeight = 0x600;
	
	// if close to this warppad
	if(D232.levelID != -1)
		wispMaxHeight = 0x400;
	
	for(i = 0; i < 2; i++)
	{
		if(instArr[WPIS_OPEN_RING1+i] != 0)
		{			
			warppadObj->spinRot_Wisp[i][0] = 0;
			warppadObj->spinRot_Wisp[i][2] = 0;
			
			warppadObj->spinRot_Wisp[i][1] += FPS_HALF(0x100);
			
			// converted to TEST in rebuildPS1
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
				
				rng1 = DECOMP_MixRNG_Scramble() >> 3;
				
				rng2 = rng1;
				if(rng1 < 0)
					rng2 = rng1 + 0xfff;
				
				warppadObj->spinRot_Wisp[i][1] = (short)rng1 + (short)(rng2 >> 0xc) * -0x1000;
			}
		}
		
		wispRiseRate += FPS_HALF(0x10);
	}
	
	warppadObj->spinRot_Prize[1] += FPS_HALF(0x80);
	
	rewardScale = 0x100;
	
	if(dist > 0x900000*2)
	{
		rewardScale = 0;
	}
	
	else if(dist > 0x900000)
	{
		// range [90, 90*2] to [0%, 100%]
		rewardScale = ((((0x900000*2)-dist) * 0x100) / 0x900000);
	}
	
	for(i = 0; i < 3; i++)
	{
		warppadObj->spinRot_Prize[2] = 0x155;
		
		if(instArr[WPIS_OPEN_PRIZE1+i] != 0)
		{
			DECOMP_AH_WarpPad_SpinRewards(
				instArr[WPIS_OPEN_PRIZE1+i],
				warppadObj, i,
				warppadInst->matrix.t[0],
				warppadInst->matrix.t[1],
				warppadInst->matrix.t[2]);
				
			modelID = instArr[WPIS_OPEN_PRIZE1+i]->model->id;
			
			if(rewardScale == 0)
			{
				// invisible
				instArr[WPIS_OPEN_PRIZE1+i]->flags |= 0x80;
			}
			
			else
			{
				// visible
				instArr[WPIS_OPEN_PRIZE1+i]->flags &= ~(0x80);
				
				// token
				rewardScale2 = 0x2000;
	
				// not token
				if(modelID != 0x7d)
				{
					// trophy
					rewardScale2 = 0x2800;
					
					// relic
					if(modelID == 0x61)
					{
						rewardScale2 = 0x1800;
					}
				}
				
				rewardScale2 = (unsigned int)(rewardScale2 * rewardScale) >> 8;
				instArr[WPIS_OPEN_PRIZE1+i]->scale[0] = (short)rewardScale2;
				instArr[WPIS_OPEN_PRIZE1+i]->scale[1] = (short)rewardScale2;
				instArr[WPIS_OPEN_PRIZE1+i]->scale[2] = (short)rewardScale2;
			}
			
		}
			
		warppadObj->thirds[i] += FPS_HALF(0x20);
		warppadObj->spinRot_Rewards[1] += FPS_HALF(0x4);
	}
		
	// if flag is on-screen, loading has already been finalized
	if(DECOMP_RaceFlag_IsTransitioning() != 0) return;
		
	// if driver has not entered this warppad
	if(warppadObj->boolEnteredWarppad == 0)
	{
		// if far away from warppad, quit
		if(dist > 0x8fff) return;
		
		// close to warppad, first frame
		else
		{
			// now in warppad
			warppadObj->boolEnteredWarppad = 1;
			warppadObj->framesWarping = 0;
		}
	}
	
	// Spam every frame (not a bug, more like last-minute hack).
	// This wont have a negative performance impact cause it's IF-guarded,
	// needed cause mask hint sets state to 0xB (Freeze), then this sets
	// warp back. Without this, Freeze causes mask-grab, which makes you drive.
	// However, with this, state goes 0xA, then 0xB, then 0xA, and warp SFX
	// plays a second time. Animation also plays twice but is invisible second time
#ifndef REBUILD_PS1
	gGT->drivers[0]->funcPtrs[0] = DECOMP_VehStuckProc_Warp_Init;
#endif
	
	if (warppadObj->framesWarping < FPS_DOUBLE(0x400))
		warppadObj->framesWarping++;
	
	// optimization, dont do this "every" frame,
	// which the original game did. Also this needs
	// to happen before the frames<61, to preserve
	// OG bug (pause->quit->adventure->load->spawn8th)
	if (warppadObj->framesWarping == 1)
	{
		// Assign Characters
		// Dont worry about Token or Relic, those dont 
		// use kartSpawnOrderArray, the OG game just did
		// this without an IF check at all
		if( (levelID < 0x10) || (levelID >= 100) )
		{
			// assign characterIDs, not actually "load"
			DECOMP_LOAD_Robots1P(data.characterIDs[0]);
			
			// spawn P1 in the back
			sdata->kartSpawnOrderArray[0] = 7;
			
			// variable reuse, get track speed champion
			champID = data.metaDataLEV[levelID].characterID_Champion;
			
			// default
			champSlot = 0;
			
			// If Speed Champion is on the track (Crash-Pura)
			// and is not the same characterID as Player 1
			if(
				(champID < 8) &&
				(champID != data.characterIDs[0])
			)
			{
				// set everyone to spawn in order
				for(i = 1; i < 7; i++) 
				{
					if(champID == data.characterIDs[i])
					{
						sdata->kartSpawnOrderArray[i] = 0;
						champSlot = i;
					}
					
					else
						sdata->kartSpawnOrderArray[i] = i;
				}
				
				sdata->kartSpawnOrderArray[7] = champSlot;
			}
			
			// Speed Champion is invalid
			else
			{
				for(i = 1; i < 8; i++) randKartSpawn[i] = i;
				
				for(i = 0; i < 7; i++)
				{
					#ifndef REBUILD_PS1
					rng1 = RngDeadCoed(&sdata->const_0x30215400);
					#else
					rng1 = 0;
					#endif
					
					rng2 = 7 - i;
					
					rng2 = (rng1 & 0xfff) % rng2 + 1;
					rng2 = (short)rng2;
					
					sdata->kartSpawnOrderArray[randKartSpawn[rng2]] = (char)i;
					
					while(rng2 < 7)
					{
						randKartSpawn[rng2] = randKartSpawn[rng2+1];
						rng2++;
					}
				}
			}
		}
	}
	
	// wait 2 full seconds before loading
	if (warppadObj->framesWarping <= FPS_DOUBLE(60)) return;

	// only works for trophy tracks rn
	if(levelID < 0x10)
	{
		// if trophy is unlocked
		if(CHECK_ADV_BIT(sdata->advProgress.rewards, (levelID + 6)) != 0)
		{
			// if never opened
			if(sdata->boolOpenTokenRelicMenu == 0)
			{
				D232.menuTokenRelic.rowSelected =
					(CHECK_ADV_BIT(sdata->advProgress.rewards, (levelID + 0x4c)) != 0);
				
				// now opened
				sdata->boolOpenTokenRelicMenu = 1;
				
				DECOMP_RECTMENU_Show(&D232.menuTokenRelic);
				
				// dont load level
				return;
			}
			
			// if opened, but not closed yet
			if((DECOMP_RECTMENU_BoolHidden(&D232.menuTokenRelic) & 0xffff) == 0)
			{
				// dont load level
				return;
			}
			
			// if opened, then closed
			else
			{
				// Relic Hint
				i = 0x1d;
				
				// CTR Token Hint
				if((gGT->gameMode2 & 8) != 0)
					i = 0x1a;
				
				// if hint is locked
				if(CHECK_ADV_BIT(sdata->advProgress.rewards, (i+0x76)) == 0)
					DECOMP_MainFrame_RequestMaskHint(i, 1);
				
				// if can't spawn aku cause he's already here,
				// quit function, wait till he's done to start race
				i = DECOMP_AH_MaskHint_boolCanSpawn();
				if((i & 0xffff) == 0) return;
				
				// reset for future gameplay
				sdata->boolOpenTokenRelicMenu = 0;
			}
		}
	}
	
	// Slide Col or Turbo Track
	else if(levelID < 0x12)
	{
		// Add Relic
		sdata->Loading.OnBegin.AddBitsConfig0 |= 0x4000000;
	}
	
	// Battle Tracks
	else if(levelID < 0x19)
	{
		// Add Crystal Challenge
		sdata->Loading.OnBegin.AddBitsConfig0 |= 0x8000000;
		
		// Dont have hint "collect every crystal"
		if ((sdata->advProgress.rewards[4] & 0x8000) == 0)
			DECOMP_MainFrame_RequestMaskHint(0x19, 1);
		
		// if can't spawn aku cause he's already here,
		// quit function, wait till he's done to start race
		i = DECOMP_AH_MaskHint_boolCanSpawn();
		if((i & 0xffff) == 0) return;
		
		gGT->originalEventTime = D232.timeCrystalChallenge[levelID-0x12];
	}
	
	// gem cups
	else
	{
		// Add Adv Cup
		sdata->Loading.OnBegin.AddBitsConfig0 |= 0x10000000;
		
		gGT->cup.cupID = levelID-100;
		gGT->cup.trackIndex = 0;
		for(i = 0; i < 8; i++)
			gGT->cup.points[i] = 0;
		
		levelID = data.advCupTrackIDs[4*gGT->cup.cupID];
	}
		
	// Rem Adventure Arena
	sdata->Loading.OnBegin.RemBitsConfig0 |= 0x100000;
	
	DECOMP_MainRaceTrack_RequestLoad(levelID);
}