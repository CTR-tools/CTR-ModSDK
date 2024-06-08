#include <common.h>

// add to buildList, overwrite original
// RB_CrateAny_ThTick_Explode at 800b3d04,
// and add new LinCs to zGlobalMetaModels.c

void RB_CrateAny_CheckBlockage(struct Thread* crateTh, int hitModelID_cast, struct Thread* mineTh)
{
	struct Crate* crateObj;
	struct MineWeapon* mw;
	
	crateObj = crateTh->object;
	mw = mineTh->object;
	
	// if model is on top of crate
	if(
		(hitModelID_cast == 6) || // nitro
		(hitModelID_cast == 0x27) || // tnt
		(hitModelID_cast == 0x46) || // red beaker
		(hitModelID_cast == 0x47) // green beaker
	)
	{	
		// prevent crate from growing back
		crateObj->boolPauseCooldown = 1;
		
		// store crateInst
		mw->crateInst = crateTh->inst;
	}
}

struct Driver* RB_CrateAny_GetDriver(struct Thread* t, struct ScratchpadStruct* sps)
{
	int hitModelID;
	int hitModelID_cast;
	struct Driver* driver;
	
	// get what hit the box
	hitModelID = sps->Input1.modelID;
	hitModelID_cast = hitModelID & 0x7fff;
	
	// if moving explosive
	if(
		(hitModelID_cast == 0x3b) || // bomb
		(hitModelID_cast == 0x29) || // missile
		(hitModelID_cast == 0x56) || // blue shield
		(hitModelID_cast == 0x5e)    // green shield
	)
	{
		// get driver that used the weapon
		driver = 
			(
				(struct TrackerWeapon*)t->object
			)->driverParent;
			
		// if this is an AI, quit
		if((driver->actionsFlagSet & 0x100000) != 0) return 1;
		
		return driver;
	}
	
	// if driver itself
	else if (hitModelID_cast == 0x18) // DYNAMIC_PLAYER
	{
		driver = (struct Driver*)t->object;
		
		return driver;
	}
	
	return 1;
}

void DECOMP_RB_CrateAny_ThTick_Explode(struct Thread* t) 
{	
	// this is an "exploded" crate, with 
	// it's own instance, thread, and object, 
	// separate from "solid" crate
	struct Instance* crateExplodeInst = t->inst;
	
	// if explosion is not over
	if(
		(crateExplodeInst->animFrame+1) < 
		INSTANCE_GetNumAnimFrames(crateExplodeInst, 0)
	)
	{
		// increment frame
		crateExplodeInst->animFrame = crateExplodeInst->animFrame+1;
		return;
	}
	
	// if explosion is over
	t->flags |= 0x800;
	DECOMP_INSTANCE_Death(crateExplodeInst);
}

void RB_CrateAny_ExplodeInit(struct Instance* crateInst, int color)
{
	struct Instance* explosionInst;
	struct Crate* crateObj;
	MATRIX matrix;
	short rot[3];
	
	// hide crate
	crateInst->scale[0] = 0;
	crateInst->scale[1] = 0;
	crateInst->scale[2] = 0;
	
	// birth explosion thread
	explosionInst = INSTANCE_BirthWithThread
	(			
		// 0x26 - box explosion model
		// 0x0 - debug name
		0x26, 0, 
		
		// pool, bucket, ThTick
		SMALL, OTHER, DECOMP_RB_CrateAny_ThTick_Explode,
		
		// PushBuffer and threadRelative
		0, 0
	);
	
	// color
	explosionInst->colorRGBA = color;
	explosionInst->alphaScale = 0x1000;
	
	// position
	explosionInst->matrix.t[0] = crateInst->matrix.t[0];
	explosionInst->matrix.t[1] = crateInst->matrix.t[1];
	explosionInst->matrix.t[2] = crateInst->matrix.t[2];
	
	// rotation matrix
	rot[0] = 0; 
	rot[1] = rand() % 0xfff;
	rot[2] = 0;
	ConvertRotToMatrix(&matrix, &rot[0]);
	
	// explosion matrix = rotated crate matrix
	MatrixRotate(&explosionInst->matrix, &crateInst->matrix, &matrix);
	
	PlaySound3D(0x3c, crateInst);
}

void DECOMP_RB_CrateAny_ThTick_Grow(struct Thread* t)
{
	struct Instance* crateInst;
	struct Crate* crateObj;
	int modelID;
	
	crateInst = t->inst;
	crateObj = (struct Crate*)t->object;
	modelID = crateInst->model->id;
	
	// if cooldown is not done (about a second long)
	if (crateObj->cooldown != 0)
	{
		// if cooldown not paused,
		// (no driver or mine, sitting in the way)
		if (crateObj->boolPauseCooldown == 0)
		{
			// reduce cooldown
			crateObj->cooldown--;
		}
		
		// dont procede until cooldown is done
		return;
	}
	
	// == ready to regrow ==
	
	crateInst->scale[0] += FPS_HALF(0x100);
	crateInst->scale[1] += FPS_HALF(0x100);
	crateInst->scale[2] += FPS_HALF(0x100);
	
	if (crateInst->scale[0] >= 0x1000)
	{
		crateInst->scale[0] = 0x1000;
		crateInst->scale[1] = 0x1000;
		crateInst->scale[2] = 0x1000;

		// kill thread
		crateInst->thread = 0;
		t->flags |= 0x800;
	}
}

struct Thread* RB_CrateAny_GrowInit(struct Instance* crateInst)
{
	struct Thread* crateThread;
	struct Crate* crateObj;
	
	// birth regrow thread
	crateThread = 
		PROC_BirthWithObject
		(
			// creation flags
			SIZE_RELATIVE_POOL_BUCKET
			(
				sizeof(struct Crate), 
				NONE, 
				SMALL, 
				STATIC
			), 
			
			DECOMP_RB_CrateAny_ThTick_Grow,	// behavior
			0,								// debug name
			0								// thread relative
		);
		
	if(crateThread == 0) return 0;
	crateInst->thread = crateThread;
	crateThread->inst = crateInst;
		
	crateObj = ((struct Crate*)crateThread->object);
	crateObj->cooldown = 0x1e;
	crateObj->boolPauseCooldown = 0;
	
	return crateThread;
}

void RB_Fruit_GetScreenCoords(struct PushBuffer* pb, struct Instance* inst, short* output);

int DECOMP_RB_CrateWeapon_LInC(
	struct Instance* crateInst,
	struct Thread* collidingTh,
	struct ScratchpadStruct* sps)
{
	struct PushBuffer* pb;
	short posScreen[2];
	struct Thread* crateThread;
	struct Crate* crateObj;
	int hitModelID;
	int hitModelID_cast;
	struct Driver* driver;
	
	crateThread = crateInst->thread;
	
	// if no regrow thread exists,
	// first frame of hitting a "full" crate
	if(crateThread == 0)
	{	
		RB_CrateAny_ExplodeInit(crateInst, 0xfafafa0);
		crateThread = RB_CrateAny_GrowInit(crateInst);
		if(crateThread == 0) return 0;
		
		driver = RB_CrateAny_GetDriver(collidingTh, sps);
		if(driver == 1) return 1;
		
		// if driver already has a weapon, quit
		if(
			(driver->heldItemID != 0xf) &&
			(driver->noItemTimer == 0)
		  )
		{
			return 1;
		}
		
		// held item count
		if(driver->numHeldItems != 0)
		{
			return 1;
		}
		
		// if driver is firing weapon, quit
		if((driver->actionsFlagSet & 0x8000) != 0)
		{
			return 1;
		}
		
		// if driver has raincloud and weapon is shuffling, quit
		if(driver->thCloud != 0)
		{
			if (
				(
					(struct RainCloud*)driver->thCloud->object
				)->boolScrollItem == 1
			)
			{
				return 1;
			}
		}

		// if driver is influenced by clock weapon, quit
		if(driver->clockReceive != 0)
		{
			return 1;
		}
		
		#ifdef USE_ONLINE
		if(driver->driverID != 0)
			return;
		
		// do nothing at end of race
		if((driver->actionsFlagSet & 0x2000000) != 0)
			return;
		#endif
		
		// == give driver weapon ==
		
		// set weapon to roulette
		driver->heldItemID = 0x10;
		
		// incrememt
		driver->numTimesHitWeaponBox++;
		
		// timer for weapon roulette
		driver->itemRollTimer = FPS_DOUBLE(90);
		
		// if no roulette
		if((sdata->gGT->gameMode1 & ROLLING_ITEM) == 0)
		{
			// start loop
			OtherFX_Play(0x5d, 0);
		
			sdata->gGT->gameMode1 |= ROLLING_ITEM;
		}
		
		driver->PickupTimeboxHUD.cooldown = FPS_DOUBLE(5);
		driver->noItemTimer = 0;
		
		if(driver->numWumpas == 10)
		{
			driver->BattleHUD.juicedUpCooldown = 10;
		}
				
		pb = &sdata->gGT->pushBuffer[driver->driverID];
		RB_Fruit_GetScreenCoords(pb, crateInst, &posScreen[0]);
		
		// screenPosXY
		driver->PickupTimeboxHUD.startX = pb->rect.x + posScreen[0];
		driver->PickupTimeboxHUD.startY = pb->rect.y + posScreen[1];
		
		// means thread was born?
		return 1;
	}
	
	// do this again, or else crateObj locally
	// is only initialized during thread birth
	crateObj = ((struct Crate*)crateThread->object);
	
	hitModelID = sps->Input1.modelID;
	hitModelID_cast = hitModelID & 0x7fff;
	
	// if crate hasn't grown back yet,
	// and something collides with it
	if(crateInst->scale[0] == 0) 
	{
		// reset cooldown
		crateObj->cooldown = 0x1e;
	}
	
	// determines if model already hit at least one crate?
	// so hitting two crates with one weapon doesn't double-reward?
	if((hitModelID & 0x8000) == 0) return 0;
	
	// overwrite, remove bit
	sps->Input1.modelID = hitModelID_cast;
	
	// block if needed
	RB_CrateAny_CheckBlockage(crateThread, hitModelID_cast, collidingTh);
	
	// means no thread born?
	return 0;
}

int DECOMP_RB_CrateFruit_LInC(
	struct Instance* crateInst,
	struct Thread* collidingTh,
	struct ScratchpadStruct* sps)
{
	struct PushBuffer* pb;
	short posScreen[2];
	struct Thread* crateThread;
	struct Crate* crateObj;
	int hitModelID;
	int hitModelID_cast;
	struct Driver* driver;
	int random;
	int newWumpa;
	
	crateThread = crateInst->thread;
	
	// if no regrow thread exists,
	// first frame of hitting a "full" crate
	if(crateThread == 0)
	{	
		RB_CrateAny_ExplodeInit(crateInst, 0xf2953a0);
		crateThread = RB_CrateAny_GrowInit(crateInst);
		if(crateThread == 0) return 0;
		
		driver = RB_CrateAny_GetDriver(collidingTh, sps);
		if(driver == 1) return 1;
		
		random = DECOMP_MixRNG_Scramble();
		newWumpa = random;
		if (random < 0) {
		newWumpa = random + 3;
		}
		newWumpa = random + (newWumpa >> 2) * -4 + 5;
		
		#ifdef USE_ONLINE
		if(driver->driverID != 0)
		{
			DECOMP_RB_Player_ModifyWumpa(driver, newWumpa);
			return;
		}
		#endif
		
		driver->PickupWumpaHUD.cooldown = FPS_DOUBLE(5);
		driver->PickupWumpaHUD.numCollected = newWumpa;
				
		pb = &sdata->gGT->pushBuffer[driver->driverID];
		RB_Fruit_GetScreenCoords(pb, driver->instSelf, &posScreen[0]);
		
		// screenPosXY
		driver->PickupWumpaHUD.startX = pb->rect.x + posScreen[0];
		driver->PickupWumpaHUD.startY = pb->rect.y + posScreen[1] - 0x14;
		
		// means thread was born?
		return 1;
	}
	
	// do this again, or else crateObj locally
	// is only initialized during thread birth
	crateObj = ((struct Crate*)crateThread->object);
	
	hitModelID = sps->Input1.modelID;
	hitModelID_cast = hitModelID & 0x7fff;
	
	// if crate hasn't grown back yet,
	// and something collides with it
	if(crateInst->scale[0] == 0) 
	{
		// reset cooldown
		crateObj->cooldown = 0x1e;
	}
	
	// determines if model already hit at least one crate?
	// so hitting two crates with one weapon doesn't double-reward?
	if((hitModelID & 0x8000) == 0) return 0;
	
	// overwrite, remove bit
	sps->Input1.modelID = hitModelID_cast;
	
	// block if needed
	RB_CrateAny_CheckBlockage(crateThread, hitModelID_cast, collidingTh);
	
	// means no thread born?
	return 0;
}

int DECOMP_RB_CrateTime_LInC(
	struct Instance* crateInst,
	struct Thread* driverTh,
	struct ScratchpadStruct* sps)
{
	struct PushBuffer* pb;
	short posScreen[2];
	struct Driver* driver;
	
	int modelID;
	struct GameTracker* gGT;
	
	// if box is broken, quit
	if(crateInst->scale[0] == 0) return;
	
	// == first frame of break ==
	
	RB_CrateAny_ExplodeInit(crateInst, 0x80ff000);
	
	gGT = sdata->gGT;
	driver = driverTh->object;
	modelID = crateInst->model->id;
	
	#ifdef USE_ONLINE
	if(driver->driverID != 0) return;
	#endif
	
	// if driver turned into AI during end-of-race menu
	if ((driver->actionsFlagSet & 0x100000) != 0)
		return;
	
	driver->numTimeCrates++;
	
	if(modelID == STATIC_TIME_CRATE_01)
	{
		gGT->frozenTimeRemaining += 0x3C0;
		gGT->timeCrateTypeSmashed = 1;
	}
	
	else if(modelID == STATIC_TIME_CRATE_02)
	{
		gGT->frozenTimeRemaining += 0x780;
		gGT->timeCrateTypeSmashed = 2;
	}
	
	else
	{
		gGT->frozenTimeRemaining += 0xb40;
		gGT->timeCrateTypeSmashed = 3;
		
		Voiceline_RequestPlay(0x13, data.characterIDs[driver->driverID], 0x10);
	}
		
	driver->PickupTimeboxHUD.cooldown = FPS_DOUBLE(10);
	
	pb = &gGT->pushBuffer[driver->driverID];
	RB_Fruit_GetScreenCoords(pb, crateInst, &posScreen[0]);
	
	// screenPosXY
	driver->PickupTimeboxHUD.startX = pb->rect.x + posScreen[0];
	driver->PickupTimeboxHUD.startY = pb->rect.y + posScreen[1];
}