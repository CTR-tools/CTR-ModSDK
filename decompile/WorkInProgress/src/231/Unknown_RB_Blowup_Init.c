#include <common.h>

void DECOMP_RB_Blowup_Init(struct Instance* weaponInst)
{
  struct Instance* shockwaveInst;
  struct ModelHeader* headers;
  struct GameTracker* gGT = sdata->gGT;
  unsigned short color;
  int *blowup;
  
  // initialize thread for blowup
  shockwaveInst = INSTANCE_BirthWithThread(0x26,sdata->s_BLOWUP, SMALL, BLOWUP, RB_Blowup_ThTick, 0xc, 0);
  
  shockwaveInst->flags |= 0x2040000;
  
  // instance -> thread -> object
  blowup = shockwaveInst->thread->object;
  
  // set explosion instance
  blowup[1] = shockwaveInst;
  
  // copy position and rotation from weapon to explosion
  shockwaveInst->matrix.m[0][0] = weaponInst->matrix.m[0][0];
  shockwaveInst->matrix.m[0][2] = weaponInst->matrix.m[0][2];
  shockwaveInst->matrix.m[1][1] = weaponInst->matrix.m[1][1];
  shockwaveInst->matrix.m[2][0] = weaponInst->matrix.m[2][0];
  shockwaveInst->matrix.m[2][2] = weaponInst->matrix.m[2][2];
  shockwaveInst->matrix.t[0] = weaponInst->matrix.t[0];
  shockwaveInst->matrix.t[1] = weaponInst->matrix.t[1];
  shockwaveInst->matrix.t[2] = weaponInst->matrix.t[2];
  
  // if instance -> model -> modelID == tnt
  if (weaponInst->model->id == 0x27) 
  {
	// red
    color = 0xad10000;
  }
  // if it is not tnt
  else 
  {
	// green
    color = 0x1eac000;
  }
  
  // set color
  shockwaveInst->colorRGBA = color;
  
  // set scale
  shockwaveInst->alphaScale = 0x1000;
  
  // green shockwave
  num_model = 0x45;
  
  // if instance -> model -> modelID == tnt
  if (weaponInst->model->id == 0x27) 
  {
	// red shockwave
    num_model = 0x44;
  }
  
  shockwaveInst = INSTANCE_Birth3D(gGT->modelPtr[num_model],sdata->s_shockwave1);
  
  // set shockwave instance
  blowup[0] = shockwaveInst;
  
  // instane flags
  shockwaveInst->flags |= 0x200;
  
  // set showckwave position to weapon position
  shockwaveInst->matrix.t[0] = weaponInst->matrix.t[0];
  shockwaveInst->matrix.t[1] = weaponInst->matrix.t[1];
  shockwaveInst->matrix.t[2] = weaponInst->matrix.t[2];
  
  headers = shockwaveInst->model->headers;
  
  // set flag to always point to camera
  headers->flags |= 2;
  
  // Do it again? Should this be explosion instance?
  headers = shockwaveInst->model->headers;
  // is this also header->flags?
  *(unsigned short *)(headers + 0x56) |= 2;
  
  // Instance -> matrix, Identity 3x3 rotation
  shockwaveInst->matrix.m[0][0] = 0x1000;
  shockwaveInst->matrix.m[0][2] = 0;
  shockwaveInst->matrix.m[1][1] = 0x1000;
  shockwaveInst->matrix.m[2][0] = 0;
  shockwaveInst->matrix.m[2][2] = 0x1000;
  
  // put weapon position on scratchpad
  DAT_1f800108 = weaponInst->matrix.t[0];
  DAT_1f80010a = weaponInst->matrix.t[1];
  DAT_1f80010c = weaponInst->matrix.t[2];

  // if you're in boss mode
  if (gGT->gameMode1 < 0) 
  {
	// hitRadius and hitRadiusSquared
    DAT_1f80010e = 0x100;
    DAT_1f800110 = 0x10000;
  }
  
  // if you're not in boss mode
  else 
  {
	// hitRadius and hitRadiusSquared
    DAT_1f80010e = 0x140;
    DAT_1f800110 = 0x19000;
  }
  
  DAT_1f800130 = RB_Burst_CollThBucket;
  DAT_1f800120 = weaponInst->thread;
  DAT_1f800114 = weaponInst->model->id;
  
  PROC_StartSearch_Self(&DAT_1f800108);
  
  PROC_CollideHitboxWithBucket(gGT->threadBuckets[ROBOT].thread,&DAT_1f800108,0);
  
  PROC_CollideHitboxWithBucket(gGT->threadBuckets[MINE].thread,&DAT_1f800108,0);
  
  // If this is TNT
  if (weaponInst->model->id != 0x27) {
	// hitRadius and hitRadiusSquared
    DAT_1f80010e = 0x80;
    DAT_1f800110 = 0x4000;
  }
  // check collision with player threads
  PROC_CollideHitboxWithBucket(gGT->threadBuckets[PLAYER].thread,&DAT_1f800108,0);

  DAT_1f800130 = RB_Burst_CollLevInst;
  return;
}
 