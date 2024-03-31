#include <common.h>

short crystalLightDir[4] =
{
	0x94F, 0x94F, 0x94F, 0
};

void DECOMP_RB_Crystal_ThTick(struct Thread* t)
{
	int sine;
	struct Instance* crystalInst;
	struct Crystal* crystalObj;
	
	crystalInst = t->inst;
	crystalObj = t->object;
	
	// rotate each frame
	crystalObj->rot[1] += FPS_HALF(0x80);
	ConvertRotToMatrix(&crystalInst->matrix, &crystalObj->rot[0]);
	
	// sine curve for vertical bounce
	sine = MATH_Sin(crystalObj->rot[1]);
	
	// set posY
	crystalInst->matrix.t[1] =
		crystalInst->instDef->pos[1] + 	// original posY
		((sine << 4) >> 0xc) +			// sine (bounce up/down)
		0x30;							// airborne bump
	
	Vector_SpecLightSpin3D(crystalInst, &crystalObj->rot[0], &crystalLightDir[0]);
}

void DECOMP_RB_Crystal_LInB(struct Instance* inst)
{
	struct Crystal* crystalObj;
	
	struct Thread* t = 
		PROC_BirthWithObject
		(
			// creation flags
			SIZE_RELATIVE_POOL_BUCKET
			(
				sizeof(struct Crystal), 
				NONE, 
				SMALL, 
				STATIC
			), 
			
			DECOMP_RB_Crystal_ThTick,	// behavior
			0,							// debug name
			0							// thread relative
		);
	
	if(t == 0) return;
	inst->thread = t;
	t->inst = inst;
	
	crystalObj = ((struct Crystal*)t->object);
	
	// rotX, rotY, rotZ
	*(int*)&crystalObj->rot[0] = 0;
	crystalObj->rot[2] = 0;
	
	inst->colorRGBA = 0xd22fff0;
	
	// specular light
	inst->flags |= 0x20000;
	
	RB_Default_LInB(inst);
}

void RB_Fruit_GetScreenCoords(struct PushBuffer* pb, struct Instance* inst, short* output);

int DECOMP_RB_Crystal_LInC(
	struct Instance* LevInst,
	struct Thread* driverTh,
	struct ScratchpadStruct* sps)
{
	struct PushBuffer* pb;
	short posScreen[2];
	struct Driver* driver;
	int modelID;

	modelID = sps->Input1.modelID;
	
	// wumpa fruit or crystal can be grabbed
	// by player, or robotcar, and there's no
	// AIs in Crystal Challenge anyway
	if (
			// not DYNAMIC_PLAYER
			(modelID != 0x18) && 
			
			// not DYNAMIC_ROBOT_CAR
			(modelID != 0x3f)
		)
	{
		return 0;
	}
	
	// kill crystal thread
	if(LevInst->thread != 0)
	{
		// kill thread
		LevInst->thread->flags |= 0x800;
		LevInst->thread = 0;
	}
	
	// check scale, and erase
	if(LevInst->scale[0] == 0) return 0;
	*(int*)&LevInst->scale[0] = 0;
	LevInst->scale[2] = 0;
	
	// play sound
	PlaySound3D(0x43,LevInst);
	
	// get driver object, get screen coords
	driver = driverTh->object;
	pb = &sdata->gGT->pushBuffer[driver->driverID];
	RB_Fruit_GetScreenCoords(pb, LevInst, &posScreen[0]);
	
	// lasts 5 frames, give start position, count numCollected
	driver->PickupWumpaHUD.startX = pb->rect.x + posScreen[0];
	driver->PickupWumpaHUD.startY = pb->rect.y + posScreen[1] - 0x14;
	driver->PickupWumpaHUD.cooldown = FPS_DOUBLE(5);
	driver->PickupWumpaHUD.numCollected++;
	
	return 1;
}