#include <common.h>

// Byte budget: /860
// boolPlaySound (0 for mask grab, 1 for weapon)
struct MaskHeadWeapon* DECOMP_VehPickupItem_MaskUseWeapon(struct Driver *driver, int boolPlaySound)

{
    struct Thread *currThread;
    struct MaskHeadWeapon *maskObj;
    struct Model *modelPtr;
    struct Thread *t;
    struct GameTracker *gGT;
    struct Instance *instance;
    int soundID;
	
	gGT = sdata->gGT;

    if (
			(DECOMP_LOAD_IsOpen_RacingOrBattle() == 0) ||
			((gGT->gameMode1 & ADVENTURE_ARENA) != 0)
		)
    {
		// no mask object in adv arena
        maskObj = NULL; 
        return maskObj;
    }

    t = driver->instSelf->thread;

    // check for existing mask
    for(
			currThread = t->childThread;
			currThread != 0;
			currThread = currThread->siblingThread
		)
    {
        // if thread->modelIndex is NOT Aku or Uka
        if ((unsigned int)(currThread->modelIndex - 0x39) >= 2)
			continue;

        currThread->funcThTick = DECOMP_RB_MaskWeapon_ThTick;

        maskObj = currThread->object;
        maskObj->duration = (driver->numWumpas < 10) ? 0x2d00 : 0x1e00;

        if (
				#ifdef USE_ONLINE
				(driver->driverID == 0) &&
				#else
				// If this is human and not AI
				((driver->actionsFlagSet & 0x100000) == 0) &&
				#endif

				(boolPlaySound != 0)
			)
        {
			// 0x3a: uka model
			// 0x39: aku model
			
			// 0x54: uka sound
			// 0x53: aku model
			
            soundID = currThread->modelIndex + 0x1A;
            OtherFX_Play_Echo(soundID, 1, driver->actionsFlagSet & 0x10000);
        }

		// un-kill thread
        currThread->flags &= ~(0x800);
		
        // return object attached to thread
        return (struct MaskHeadWeapon *)currThread->object;
        
    }

	int boolGoodGuy =
		DECOMP_VehPickupItem_MaskBoolGoodGuy(driver);
		
	int modelID = 0x3a - boolGoodGuy;

    // 0x3a: uka head model idx in modelPtr array
    instance = 
		DECOMP_INSTANCE_BirthWithThread(
			modelID, 0, SMALL, OTHER,
			DECOMP_RB_MaskWeapon_ThTick, 
			sizeof(struct MaskHeadWeapon), t);
			
	soundID = modelID + 0x1A;

    
    if (
			#ifdef USE_ONLINE
			(driver->driverID == 0) &&
			#else
			// If this is human and not AI
			((driver->actionsFlagSet & 0x100000) == 0) &&
			#endif
        
			(
				OtherFX_Play_Echo(soundID, 1, driver->actionsFlagSet & 0x10000),

				1 < (u_int)(driver->kartState - 4)
			)
		)
    {
		if (boolGoodGuy == 0)
		{
			gGT->gameMode1 &= ~(AKU_SONG);
			gGT->gameMode1 |= UKA_SONG;
		}
		
		else
		{
			gGT->gameMode1 &= ~(UKA_SONG);
			gGT->gameMode1 |= AKU_SONG;
		}
    }

	// 0x3a: uka model
	// 0x39: aku model
	
	// 0x40: uka beam
	// 0x3E: aku beam
	
    modelPtr = gGT->modelPtr[0x3E + ((modelID-0x39)*2)];

    t = instance->thread;

    maskObj = 
		(struct MaskHeadWeapon *)t->object;

    maskObj->maskBeamInst = 
		DECOMP_INSTANCE_Birth3D(modelPtr, 0, t);

    t->funcThDestroy = 
		DECOMP_PROC_DestroyInstance;

    t->flags |= 0x1000;                   // disable collision
    instance->flags |= 0x80;              // make mask head invisible
    maskObj->maskBeamInst->flags |= 0x80; // make mask beam invisible
    maskObj->duration = (driver->numWumpas > 9) ? 0x2d00 : 0x1e00;
    maskObj->rot[0] = 0x40;  // rotX
    maskObj->rot[1] = 0;     // rotY
    maskObj->rot[2] = 0;     // rotZ
    maskObj->scale = 0x1000; // scale

    return maskObj;
}