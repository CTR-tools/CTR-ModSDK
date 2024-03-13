#include <common.h>

// To do:
// slight squish when landing jumps,
// wheels in the air when going over turbo pad,
// jump animation is mirrored for some reason?
// black smoke when boosting
// fire when boosting
// particles when driving on grass
// etc

void RunInitHook(void)
{
	// Disable collision
	*(unsigned int*)0x80042368 = 0;
}

void RunUpdateHook()
{
	int i;
	short rot[3];

	int buttons = sdata->gGamepads->gamepad[0].buttonsHeldCurrFrame;

	// no time trial, just spawn player on their own
	if(sdata->gGT->gameMode1 & TIME_TRIAL)
	{
		sdata->gGT->gameMode1 =
		sdata->gGT->gameMode1 & ~TIME_TRIAL;
	}

	if(buttons & BTN_R2)
	{
		if(sdata->gGT->drivers[1] == 0)
		{
			// get character ID
			data.characterIDs[1] = data.characterIDs[0];

			// spawn the AI
			BOTS_Driver_Init(1);

			// disable AI function, so all variables are free to edit
			sdata->gGT->threadBuckets[ROBOT].thread->funcThTick = 0;

			// set scale to default value
			for(i = 0; i < 3; i++)
			{
				sdata->gGT->drivers[1]->instSelf->scale[i] = 0xccc;
			}
		}
	}

	// only continue if driver exists
	if(sdata->gGT->drivers[1] == 0) return;

	// copy rotCurr[1] over network,
	// both for AngleAxis, and shadows
	sdata->gGT->drivers[1]->rotCurr[1] =
	sdata->gGT->drivers[0]->rotCurr[1];

	// dont copy normalVec over network, copy
	// quadblockID, then get normalVec from there,
	// or run a BSP search to find quadblock without network,
	VehPhysForce_RotAxisAngle(

		// P2 matrix
		&sdata->gGT->drivers[1]->instSelf->matrix,

		// P1 normal vector
		&sdata->gGT->drivers[0]->AxisAngle3_normalVec[0],

		// P2 rotY (already copied over)
		sdata->gGT->drivers[1]->rotCurr[1]
	);

	// copy position over network,
	for(i = 0; i < 3; i++)
	{
		// 9 bytes for position (3 for x, 3 for y, 3 for z)
		// ghost data uses bit shifting >> 3, so maybe less?

		// I'd love to change 3f to 00, but then wheels vanish,
		// I know only the bottom 3 bytes are used for rendering kart,
		// that's a fact. Tires are rendered by subtracting 4-byte
		// kart position from 4-byte camera position, for max accuracy,
		// that needs to be rewritten or patched before shaving bytes

		// experiment with alignment
		// remove bottom 3 bits: &f8
		// remove bottom 4 bits: &f0
		// remove bottom 5 bits: &e0

		// bit compression,
		sdata->gGT->drivers[1]->instSelf->matrix.t[i] =
		sdata->gGT->drivers[0]->instSelf->matrix.t[i] & 0xfffffffe;
	}

	// Move right, and up, for visibility test
	sdata->gGT->drivers[1]->instSelf->matrix.t[2] -= 0x80;
	//sdata->gGT->drivers[1]->instSelf->matrix.t[1] += 0x20;

	// copy to driver struct for shadows
	for(i = 0; i < 3; i++)
	{
		sdata->gGT->drivers[1]->posCurr[i] =
		sdata->gGT->drivers[1]->instSelf->matrix.t[i] << 8;
	}

	// dont copy over network, find it from quadblockID,
	// which is either sent over network, or found from BSP
	sdata->gGT->drivers[1]->quadBlockHeight =
	sdata->gGT->drivers[0]->quadBlockHeight;

	// 2 bytes for animation, one for index, one for frame,
	// even though these are shorts, they probably can be chars
	sdata->gGT->drivers[1]->instSelf->animIndex =
	sdata->gGT->drivers[0]->instSelf->animIndex;

	sdata->gGT->drivers[1]->instSelf->animFrame =
	sdata->gGT->drivers[0]->instSelf->animFrame;

	// alpha scale (ambient brightness)
	sdata->gGT->drivers[1]->instSelf->alphaScale =
	sdata->gGT->drivers[0]->instSelf->alphaScale;

	// driver flags (skidmarks, using mask weapon, etc)
	sdata->gGT->drivers[1]->actionsFlagSet =
	sdata->gGT->drivers[0]->actionsFlagSet;

	// skidmark flags
	sdata->gGT->drivers[1]->skidmarkEnableFlags =
	sdata->gGT->drivers[0]->skidmarkEnableFlags;

	// speed (needed for skids)
	sdata->gGT->drivers[1]->speedApprox =
	sdata->gGT->drivers[0]->speedApprox;

	// this is a PLAYER function being run on a ROBOTCAR,
	// how do ordinary AIs record skidmark buffer without this?
	VehEmitter_DriverMain(
		sdata->gGT->drivers[1]->instSelf->thread,
		sdata->gGT->drivers[1]);
}

