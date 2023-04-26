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
	
	// temporary
	if(dist < 0x9000)
	MainRaceTrack_RequestLoad(levelID);
}