#include <common.h>

short letterLightDir[4] =
{
	0x94F, 0x94F, -0x94F, 0
};

void DECOMP_RB_CtrLetter_ThTick(struct Thread* t)
{
	int sine;
	struct Instance* letterInst;
	struct CtrLetter* letterObj;
	
	letterInst = t->inst;
	letterObj = t->object;
	
	// rotate each frame
	letterObj->rot[1] += FPS_HALF(0x40);
	ConvertRotToMatrix(&letterInst->matrix, &letterObj->rot[0]);
	
	Vector_SpecLightSpin3D(letterInst, &letterObj->rot[0], &letterLightDir[0]);
}

void DECOMP_RB_CtrLetter_LInB(struct Instance* inst)
{
	struct CtrLetter* letterObj;
	
	struct Thread* t = 
		PROC_BirthWithObject
		(
			// creation flags
			SIZE_RELATIVE_POOL_BUCKET
			(
				sizeof(struct CtrLetter), 
				NONE, 
				SMALL, 
				STATIC
			), 
			
			DECOMP_RB_CtrLetter_ThTick,	// behavior
			0,							// debug name
			0							// thread relative
		);
	
	if(t == 0) return;
	inst->thread = t;
	t->inst = inst;
	
	letterObj = ((struct CtrLetter*)t->object);
	letterObj->rot[0] = 0;
	letterObj->rot[1] = 0;
	letterObj->rot[2] = 0;
	
	inst->scale[0] = 0x1800;
	inst->scale[1] = 0x1800;
	inst->scale[2] = 0x1800;
	
	inst->colorRGBA = 0xffc8000;
	
	// specular light, plus another
	inst->flags |= 0x30000;
	
	RB_Default_LInB(inst);
}

void RB_Fruit_GetScreenCoords(struct PushBuffer* pb, struct Instance* inst, short* output);

int DECOMP_RB_CtrLetter_LInC(
	struct Instance* letterInst,
	struct Thread* driverTh,
	struct ScratchpadStruct* sps)
{
	short posScreen[2];
	MATRIX* m;
	struct Driver* driver;
	struct PushBuffer* pb;
	int driverID;
	int modelID;

	modelID = sps->Input1.modelID;
	
	// if crystal did not collide with 
	// DYNAMIC_PLAYER, quit function
	if (modelID != 0x18) return 0;
	
	// handle scale
	if(letterInst->scale[0] == 0) return 0;
	letterInst->scale[0] = 0;
	letterInst->scale[1] = 0;
	letterInst->scale[2] = 0;
	
	// kill thread
	letterInst->thread->flags |= 0x800;
	letterInst->thread = 0;
	
	// play sound
	PlaySound3D(100,letterInst);
	
	// get driver object
	driver = driverTh->object;
	driverID = driver->driverID;
	
	pb = &sdata->gGT->pushBuffer[driverID];
	RB_Fruit_GetScreenCoords(pb, letterInst, &posScreen[0]);
	
	// screenPosXY
	driver->PickupLetterHUD.startX = pb->rect.x + posScreen[0];
	driver->PickupLetterHUD.startY = pb->rect.y + posScreen[1] - 0x14;
	
	// transition should last 10 frames
	driver->PickupLetterHUD.cooldown = FPS_DOUBLE(10);
	
	// increment number of items in hud
	driver->PickupLetterHUD.numCollected++;
	
	// which letter was grabbed
	driver->PickupLetterHUD.modelID = letterInst->model->id;
	
	return 1;
}