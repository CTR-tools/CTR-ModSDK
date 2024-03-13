#include <common.h>

void ConvertRotToMatrix(MATRIX* m, short* rot);

struct PortalTest
{
	struct Instance* p_enter;
	struct Instance* p_exit;
};

char pt_name[] = "PortalTest";
char pEnter[] = "Entrance Portal";
char pExit[] = "Exit Portal";

// forward declaration
// dont need to put params, wont call directly
void VehStuckProc_Warp_Init();
void VehPhysProc_Driving_Init();

void RunInitHook()
{
	short rot[3];
	struct Model* modelPtr;
	struct PortalTest* pt;

	struct GameTracker* gGT;
	gGT = sdata->gGT;

	// This can definitely be global, not using old OV anymore
	gGT->level2 = (void*)MEMPACK_AllocMem(sizeof(struct PortalTest),pt_name);
	pt = (struct PortalTest*)gGT->level2;

	// Get pointer of CTR Token
	modelPtr = sdata->gGT->modelPtr[0x7d];

	// instance flags will be 0xf by default
	pt->p_enter = INSTANCE_Birth3D(modelPtr, pEnter, 0);
	pt->p_exit  = INSTANCE_Birth3D(modelPtr, pExit, 0);

	// Get coordinates from driver->2D4, then bit shift 8

	// position of entrance portal
	pt->p_enter->matrix.t[0] = 0xFFFC0FFF >> 8;
	pt->p_enter->matrix.t[1] = 0;
	pt->p_enter->matrix.t[2] = 0x3E6A0 >> 8;

	// scale of entrance portal
	pt->p_enter->scale[0] = 0x7ccc;
	pt->p_enter->scale[1] = 0x7ccc;
	pt->p_enter->scale[2] = 0x1ccc;

	// position of exit portal
	pt->p_exit->matrix.t[0] = 0x4CB6F >> 8;
	pt->p_exit->matrix.t[1] = 0;
	pt->p_exit->matrix.t[2] = 0xFFFFB8C7 >> 8;

	// scale of exit portal
	pt->p_exit->scale[0] = 0x7ccc;
	pt->p_exit->scale[1] = 0x7ccc;
	pt->p_exit->scale[2] = 0x1ccc;

	// set rotations
	rot[0] = 0x400;
	rot[1] = 0;
	rot[2] = 0;
	ConvertRotToMatrix(&pt->p_enter->matrix, rot);
	ConvertRotToMatrix(&pt->p_exit->matrix, rot);
}

void RunUpdateHook()
{
	struct Driver* driver;
	struct Instance* collisionDriverInst;
	struct Driver* collisionDriverObj;
	int collisionX;
	int collisionY;
	int collisionZ;
	struct PortalTest* pt;

	struct GameTracker* gGT;
	gGT = sdata->gGT;

	// This can definitely be global, not using old OV anymore
	pt = (struct PortalTest*)gGT->level2;

	// The rest of the code is hard-coded for one driver
	driver = gGT->drivers[0];

	// This handles collision just like Ring Rally.
	// Collisions can also be handled by pulling data
	// from matrices, like Crash Ball

	collisionX = 0xFFFC0FFF;
	collisionY = 0;
	collisionZ = 0x3E6A0;

	if
	(
		( (collisionX - driver->posCurr[0]) < (0x7ccc << 1) ) &&
		( (collisionX - driver->posCurr[0]) > (0x7ccc << 1) * -1 ) &&
		( (collisionY - driver->posCurr[1]) < (0x7ccc << 1) ) &&
		( (collisionY - driver->posCurr[1]) > (0x7ccc << 1) * -1 ) &&
		( (collisionZ - driver->posCurr[2]) < (0x7ccc << 1) ) &&
		( (collisionZ - driver->posCurr[2]) > (0x7ccc << 1) * -1 )
	)
	{
		driver->funcPtrs[0] = VehStuckProc_Warp_Init;
	}

	// If driver is invisible, when warp pad animation is done
	if(driver->instSelf->flags & 0x80)
	{
		// Move driver to exit portal
		driver->posCurr[0] = pt->p_exit->matrix.t[0] << 8;
		driver->posCurr[1] = pt->p_exit->matrix.t[1] << 8;
		driver->posCurr[2] = pt->p_exit->matrix.t[2] << 8;

		// remove flag, make driver visible
		driver->instSelf->flags =
		driver->instSelf->flags & 0xffffff7f;

		// We dont have a struct variable for this yet, cause we don't fully understand it.
		// It gets set to 3 when the camera detaches from player, and zero when it follows player
		*(unsigned char*) ( (char*)&sdata->gGT->cameraDC[0] + 0x9A ) = 0;

		// fix driver scale
		driver->instSelf->scale[0] = 0xccc;
		driver->instSelf->scale[1] = 0xccc;
		driver->instSelf->scale[2] = 0xccc;

		// Turn Exhaust back on, we dont have a variable
		// for this yet cause we dont fully understand it
		*(unsigned int*) ( (char*)driver + 0x4FC ) = 0;

		// Change state back to driving
		driver->funcPtrs[0] = VehPhysProc_Driving_Init;
	}
}

