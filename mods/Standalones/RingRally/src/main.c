#include <common.h>
#include "ring.h"

struct RingRallyGame
{
	// 4 byte aligned
	char laps;
	char numRingsOnTrack;
	short numRingsCollected;

	// 4 byte aligned
	struct RingData* ringData;

	// 4 byte aligned
	struct Instance* ring[10];
};

struct RingRallyGame* rrg asm("k1");

char ring_name[] = "Ring Rally Game";
char ring_inst_name[] = "Ring";
char ringsStr[] = "Rings: 000000";
char lapsStr[] =  "Laps: 0000";
char s_endString[] = "Press * to play again";


// Only need declaration for functions being injected.
// At some point, they should all be declared anyway
void CC_EndEvent_DrawMenu();
void CAM_FollowDriver_Normal(int param_1,int param_2,short *param_3,int param_4,short *param_5);

void MainUpdateLoop();
void InjectRetroFueled();

void KillCrystals()
{
	// make crystals invisible
	sdata->ptrHudCrystal->flags =
	sdata->ptrHudCrystal->flags | 0x80;
	sdata->ptrMenuCrystal->flags =
	sdata->ptrMenuCrystal->flags | 0x80;
}

// dont store in 221,
// cause 221 is used for rings
void EndCrystalChallenge(void)
{
	// freeze driver
	sdata->gGT->drivers[0]->funcPtrs[0] = VehPhysProc_FreezeEndEvent_Init;

	// make invisible
	KillCrystals();

	// Draw number of rings
	DecalFont_DrawLine(ringsStr, 0x100,0x68,FONT_SMALL,(JUSTIFY_CENTER | ORANGE));

	// Draw number of lapsStr
	DecalFont_DrawLine(lapsStr, 0x100,0x70,FONT_BIG,(JUSTIFY_CENTER | ORANGE));

	// Draw instructions for restart
	DecalFont_DrawLine(s_endString, 0x100, 0xa0, FONT_SMALL, (JUSTIFY_CENTER | ORANGE));

	// If you press Cross or Circle
	if(sdata->AnyPlayerTap & 0x50)
	{
		// restart race
		sdata->mainGameState = 2;
	}
}

// To do: Make the new RF with blue fire,
// work modularly with other mods (like this one)
void InjectRetroFueled()
{
	// port of Retro Fueled by TheRedhotbr

	*(unsigned char*)(VehFire_Increment + 0x37A) = 0;

	// Set pads to USF
	*(unsigned char*)(VehPhysForce_CollideDrivers + 0xB9) = 8;

	*(unsigned int* )(VehPhysProc_Driving_PhysLinear + 0xA30) = 0x8200040D;
	*(unsigned int* )(VehPhysProc_Driving_PhysLinear + 0xA34) = 0x30B80002;
	*(unsigned int* )(VehPhysProc_Driving_PhysLinear + 0xA38) = 0x30B90020;
	*(unsigned int* )(VehPhysProc_Driving_PhysLinear + 0xA3C) = 0x17000006;
	*(unsigned int* )(VehPhysProc_Driving_PhysLinear + 0xA40) = 0x319C020;
	*(unsigned int* )(VehPhysProc_Driving_PhysLinear + 0xA44) = 0x13200004;
	*(unsigned int* )(VehPhysProc_Driving_PhysLinear + 0xA48) = 0;
	*(unsigned int* )(VehPhysProc_Driving_PhysLinear + 0xA60) = 0x20190022;
	*(unsigned char*)(VehPhysProc_Driving_PhysLinear + 0xA70) = 3;
	*(unsigned int* )(VehPhysProc_Driving_PhysLinear + 0xA80) = 0x13190002;
	*(unsigned int* )(VehPhysProc_Driving_PhysLinear + 0xA84) = 0;
	*(unsigned int* )(VehPhysProc_Driving_PhysLinear + 0xA88) = 0x14400002;
	*(unsigned int* )(VehPhysProc_Driving_PhysLinear + 0xA8C) = 0x24020006;
	*(unsigned int* )(VehPhysProc_Driving_PhysLinear + 0xA90) = 0x1682001C;
}

// To do: finish collision for spinning ring (in PL test),
// then bring that into gameplay
char CollideRing(int loop)
{
	int ringRadius;
	struct Driver* driver;
	int playerX;
	int playerY;
	int playerZ;

	ringRadius = (int)rrg->ring[loop]->scale[0];

	driver = sdata->gGT->drivers[0];

	playerX = driver->posCurr[0];
	playerY = driver->posCurr[1];
	playerZ = driver->posCurr[2];

	if(rrg->ringData[loop].rot == 0)
	{
		return
		(
			( ((rrg->ringData[loop].posX << 12) - playerX) < (ringRadius << 1) ) &&
			( ((rrg->ringData[loop].posX << 12) - playerX) > (ringRadius << 1) * -1 ) &&
			( ((rrg->ringData[loop].posY << 12) - playerY) < (ringRadius << 2) ) &&
			( ((rrg->ringData[loop].posY << 12) - playerY) > (ringRadius << 2) * -1 ) &&
			( ((rrg->ringData[loop].posZ << 12) - playerZ) < (ringRadius << 2) ) &&
			( ((rrg->ringData[loop].posZ << 12) - playerZ) > (ringRadius << 2) * -1 )
		);
	}

	else
	{
		return
		(
			( ((rrg->ringData[loop].posX << 12) - playerX) < (ringRadius << 2) ) &&
			( ((rrg->ringData[loop].posX << 12) - playerX) > (ringRadius << 2) * -1 ) &&
			( ((rrg->ringData[loop].posY << 12) - playerY) < (ringRadius << 2) ) &&
			( ((rrg->ringData[loop].posY << 12) - playerY) > (ringRadius << 2) * -1 ) &&
			( ((rrg->ringData[loop].posZ << 12) - playerZ) < (ringRadius << 1) ) &&
			( ((rrg->ringData[loop].posZ << 12) - playerZ) > (ringRadius << 1) * -1 )
		);
	}

	return 0;
}

void RunInitHook()
{
	int i;
	int loop;
	struct Model* modelPtr;
	short newRot[3];

	// To do: find something smarter, like NOP-ing a Crate OnInit,
	// or replacing the code for Crate OnInit to destroy the instance,
	// and wumpa fruit on the track

	#if BUILD == UsaRetail || BUILD == JpnRetail
	// Remove instruction that changes LOD,
	// so now it should default to 8 (time trial),
	// This way, weapon boxes wont spawn on track
	*(unsigned int*)(LOAD_TenStages + 0x4BC) = 0;
	#elif BUILD == EurRetail
	*(unsigned int*)(LOAD_TenStages + 0x4B0) = 0;
	#endif

	// Remove instruction to draw number crystals
	*(unsigned int*)(UI_RenderFrame_CrystChall + 0xB0) = 0;

	// disable hud, just like 2P NF mod,
	// also disable countdown timer
	*(char*)(CAM_FollowDriver_Normal + 0xF7C) = 0;

	// Copy/Paste from ModMenuV2
	InjectRetroFueled();





	// only run if this is a race track
	if(sdata->gGT->levelID > TURBO_TRACK) return;






	// 10 seconds in event
	sdata->gGT->originalEventTime = 10 * 30 * 32;

	// event has not started
	sdata->gGT->elapsedEventTime = 0;

	// the game treats wumpa fruit as crystals,
	// make sure the game doesn't end by collecting them.
	// Wumpa crates dont count, just fruit on ground
	sdata->gGT->numCrystalsInLEV = 100;

	// Disable default HUD, then we draw HUD
	// anyway, so we can remove extra crystal
	KillCrystals();



	// globals
	rrg = (struct RingRallyGame*)0x8000FF00;




	rrg->laps = 0;
	rrg->numRingsCollected = 0;

	// To do: make this dynamic depending on levelID
	rrg->numRingsOnTrack = CocoPark_NUM;
	rrg->ringData = (struct RingData*)
	(
		(char*)CC_EndEvent_DrawMenu + 0x10 + sizeof(struct RingData) * CocoPark_BASE
	);

	// reset ring counter
	ringsStr[7] =  '0';
	ringsStr[8] =  '0';
	ringsStr[9] =  '0';
	ringsStr[10] = '0';
	ringsStr[11] = '0';
	ringsStr[12] = '0';

	// reset lap counter
	lapsStr[6] = '0';
	lapsStr[7] = '0';
	lapsStr[8] = '0';
	lapsStr[9] = '0';

	for(loop = 0; loop < rrg->numRingsOnTrack; loop++)
	{
		// get model pointer
		modelPtr = sdata->gGT->modelPtr[rrg->ringData[loop].modelIndex+0x3e];

		// instance flags will be 0xf by default
		rrg->ring[loop] = (struct Instance*)INSTANCE_Birth3D(modelPtr, ring_inst_name, 0);

		// Fix LOD for Uka rings,
		// This value is set by default for Aku, but Uka is lower
		rrg->ring[loop]->model->headers[0].maxDistanceLOD = 0x4E20;

		// same scale for all, since token is rotated
		rrg->ring[loop]->scale[0] = 0x7fff;
		rrg->ring[loop]->scale[1] = 0x7fff;
		rrg->ring[loop]->scale[2] = 0x7fff;

		// pos << 4 = 32bit>>8
		rrg->ring[loop]->matrix.t[0] = rrg->ringData[loop].posX << 4;
		rrg->ring[loop]->matrix.t[1] = rrg->ringData[loop].posY << 4;
		rrg->ring[loop]->matrix.t[2] = rrg->ringData[loop].posZ << 4;

		// multiply by 4, cause we compressed 2 bits
		newRot[0] = rrg->ringData[loop].rot << 2;
		newRot[1] = 0;
		newRot[2] = 0x400;

		// rot -> matrix
		ConvertRotToMatrix(&rrg->ring[loop]->matrix, newRot);
	}
}

void RunUpdateHook()
{
	int loop;
	int loop2;
	char boolCollide;

	// only run if this is a race track
	if(sdata->gGT->levelID > TURBO_TRACK) return;

	// if you are right about to run out of time
	if(
		sdata->gGT->originalEventTime -
		sdata->gGT->elapsedEventTime < 40
	  )
	{
		// put HUD back, or EndCrystalChallenge wont execute
		sdata->gGT->hudFlags =
		sdata->gGT->hudFlags | 1;

		return;
	}

	// remove HUD
	sdata->gGT->hudFlags =
	sdata->gGT->hudFlags & 0xfe;

	// If intro anim cutscene ended,
	// and traffic lights either started, or finished
	if(sdata->gGT->trafficLightsTimer < 3840)
	{
		// Draw crystal challenge HUD
		UI_RenderFrame_CrystChall();

		// Draw number of rings
		DecalFont_DrawLine(ringsStr, 0x150,8,FONT_SMALL,ORANGE);

		// Draw number of lapsStr
		DecalFont_DrawLine(lapsStr, 0x150,0x10,FONT_BIG,ORANGE);
	}

	for(loop = 0; loop < rrg->numRingsOnTrack; loop++)
	{
		// skip ring if it is invisible
		if(rrg->ring[loop]->flags & 0x80)
			continue;

		if(CollideRing(loop))
		{
			// keep count of rings
			rrg->numRingsCollected++;

			// add 3 seconds to the clock
			sdata->gGT->originalEventTime += 3 * 30 * 32;

			// subtract half a second
			sdata->gGT->originalEventTime -= 15 * 32;

			// set the counter string
			ringsStr[7] =  '0' + (rrg->numRingsCollected / 100000) % 10;
			ringsStr[8] =  '0' + (rrg->numRingsCollected / 10000) % 10;
			ringsStr[9] =  '0' + (rrg->numRingsCollected / 1000) % 10;
			ringsStr[10] = '0' + (rrg->numRingsCollected / 100) % 10;
			ringsStr[11] = '0' + (rrg->numRingsCollected / 10) % 10;
			ringsStr[12] = '0' + (rrg->numRingsCollected    ) % 10;

			// make this ring invisible
			rrg->ring[loop]->flags =
			rrg->ring[loop]->flags | 0x80;

			// make all other rings visible
			for(loop2 = 0; loop2 < rrg->numRingsOnTrack; loop2++)
			{
				if(loop == loop2)
					continue;

				rrg->ring[loop2]->flags =
				rrg->ring[loop2]->flags & 0xffffff7f;
			}

			// play sound
			OtherFX_Play(0x67,1);
		}
	}

	if(sdata->gGT->drivers[0]->lapIndex == 1)
	{
		sdata->gGT->drivers[0]->lapIndex = 0;

		rrg->laps++;

		lapsStr[6] = '0' + rrg->laps / 1000;
		lapsStr[7] = '0' + rrg->laps / 100;
		lapsStr[8] = '0' + rrg->laps / 10;
		lapsStr[9] = '0' + rrg->laps % 10;

		if(rrg->laps < 8)
		{
			for(loop = 0; loop < rrg->numRingsOnTrack; loop++)
			{
				// same scale for all, since token is rotated
				rrg->ring[loop]->scale[0] = 0x7fff - (0x1000 * rrg->laps);
				rrg->ring[loop]->scale[1] = 0x7fff - (0x1000 * rrg->laps);
				rrg->ring[loop]->scale[2] = 0x7fff - (0x1000 * rrg->laps);
			}
		}
	}
}

