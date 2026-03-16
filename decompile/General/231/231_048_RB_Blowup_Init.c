#include <common.h>

void RB_Blowup_ThTick();
void RB_Burst_CollLevInst();
void RB_Burst_CollThBucket();

void DECOMP_RB_Blowup_Init(struct Instance* weaponInst)
{
  struct Thread* explosionTh;
  struct Instance* explosionInst;
  struct Instance* shockwaveInst;
  struct ModelHeadr* mh;
  struct GameTracker* gGT = sdata->gGT;
  unsigned short color;
  int *blowup;
  
  // initialize thread for blowup
  explosionInst = INSTANCE_BirthWithThread(
	0x26, 0, SMALL, BLOWUP, 
	RB_Blowup_ThTick, 0xc, 0);
  
  explosionInst->flags |= 0x2040000;
  
  explosionTh = explosionInst->thread;
  blowup = explosionTh->object;
  
  // set explosion instance
  blowup[1] = explosionInst;
  
  // copy position and rotation from weapon to explosion
  *(int*)&explosionInst->matrix.m[0][0] = *(int*)&weaponInst->matrix.m[0][0];
  *(int*)&explosionInst->matrix.m[0][2] = *(int*)&weaponInst->matrix.m[0][2];
  *(int*)&explosionInst->matrix.m[1][1] = *(int*)&weaponInst->matrix.m[1][1];
  *(int*)&explosionInst->matrix.m[2][0] = *(int*)&weaponInst->matrix.m[2][0];
  explosionInst->matrix.m[2][2] = weaponInst->matrix.m[2][2];
  explosionInst->matrix.t.x = weaponInst->matrix.t.x;
  explosionInst->matrix.t.y = weaponInst->matrix.t.y;
  explosionInst->matrix.t.z = weaponInst->matrix.t.z;

  // green
  color = 0x1eac000;

  // green shockwave
  int modelID = STATIC_SHOCKWAVE_GREEN;
  
  // if instance -> model -> modelID == tnt
  if (weaponInst->model->id == STATIC_CRATE_TNT) 
  {
	// red
    color = 0xad10000;
	
	// red shockwave
    modelID = STATIC_SHOCKWAVE_RED;
  }
  
  // set color
  explosionInst->colorRGBA = color;
  
  // set scale
  explosionInst->alphaScale = 0x1000;
  
  // ======== Next Instance ==========
  
  shockwaveInst = INSTANCE_Birth3D(gGT->modelPtr[modelID], 0, explosionTh);
  
  // set shockwave instance
  blowup[0] = shockwaveInst;
  
  // instane flags
  shockwaveInst->flags |= 0x200;
  
  *(int*)&shockwaveInst->matrix.m[0][0] = 0x1000;
  *(int*)&shockwaveInst->matrix.m[0][2] = 0;
  *(int*)&shockwaveInst->matrix.m[1][1] = 0x1000;
  *(int*)&shockwaveInst->matrix.m[2][0] = 0;
  shockwaveInst->matrix.m[2][2] = 0x1000;
  shockwaveInst->matrix.t.x = weaponInst->matrix.t.x;
  shockwaveInst->matrix.t.y = weaponInst->matrix.t.y;
  shockwaveInst->matrix.t.z = weaponInst->matrix.t.z;
  
  //ptrHeadersArray points to the first header
  mh = shockwaveInst->model->ptrHeadersArray;
  
  // set flag to always point to camera
  for (unsigned char i = 0; i < 2; i++)
  {
    mh[i].flags |= 2;
  }
  
  // ======== End Of Instance ==========
  
  struct ScratchpadStruct* sps = 0x1f800108;

  // put weapon position on scratchpad
  sps->Input1.pos[0] = weaponInst->matrix.t.x;
  sps->Input1.pos[1] = weaponInst->matrix.t.y;
  sps->Input1.pos[2] = weaponInst->matrix.t.z;

  // if you're in boss mode
  if ((gGT->gameMode1 & ADVENTURE_BOSS) != 0) 
  {
	// hitRadius and hitRadiusSquared
    sps->Input1.hitRadius = 0x100;
    sps->Input1.hitRadiusSquared = 0x10000;
  }
  
  // if you're not in boss mode
  else 
  {
	// hitRadius and hitRadiusSquared
    sps->Input1.hitRadius = 0x140;
    sps->Input1.hitRadiusSquared = 0x19000;
  }
  
  sps->Input1.modelID = weaponInst->model->id;
  
  sps->Union.ThBuckColl.thread = weaponInst->thread;
  sps->Union.ThBuckColl.funcCallback = RB_Burst_CollThBucket;
  
  PROC_StartSearch_Self(sps);
  
  PROC_CollideHitboxWithBucket(gGT->threadBuckets[ROBOT].thread,sps,0);
  PROC_CollideHitboxWithBucket(gGT->threadBuckets[MINE].thread,sps,0);
  
  // Nitro explosion has smaller radius than TNT explosion
  if (weaponInst->model->id != STATIC_CRATE_TNT) 
  {
	// hitRadius and hitRadiusSquared
    sps->Input1.hitRadius = 0x80;
    sps->Input1.hitRadiusSquared = 0x4000;
  }
  
  // check collision with player threads
  PROC_CollideHitboxWithBucket(gGT->threadBuckets[PLAYER].thread,sps,0);

  sps->Union.ThBuckColl.funcCallback = RB_Burst_CollLevInst;
  return;
}
 