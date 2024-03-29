#include <common.h>

void DECOMP_VehTalkMask_ThTick(struct Thread* t)
{
	struct GameTracker* gGT = sdata->gGT;
	
	struct MaskHint* mhObj = t->object;
	struct Instance* mhInst = t->inst;
	
	int scale = mhObj->scale;
	
	if(sdata->modelMaskHints3D != 0)
	{
		mhInst->model = sdata->modelMaskHints3D;
		scale *= 2;
	}
	
	else
	{	
		// do we need this IF ???
		if(gGT->drivers[0] != 0)
		{
			int boolGoodGuy = 
				DECOMP_VehPickupItem_MaskBoolGoodGuy(gGT->drivers[0]);
				
			// 0x3A for Uka, 0x39 for Aku
			int modelID = 0x3A - boolGoodGuy;
			mhInst->model = gGT->modelPtr[modelID];
		}
	}
	
	mhInst->scale[0] = scale;
	mhInst->scale[1] = scale;
	mhInst->scale[2] = scale;

	sdata->unk_8008d9f4[1] = sdata->XA_MaxSampleValInArr;
	
	int iVar4 = sdata->unk_8008d9f4[1] * 7;

	if (iVar4 < 0) {
		iVar4 = iVar4 + 0x3fff;
	}
	
	iVar4 = iVar4 >> 0xe;
	
	if (sdata->unk_8008d9f4[2] < iVar4)
		sdata->unk_8008d9f4[2] = iVar4;
	
  int iVar6 = iVar4;
  if (iVar4 < 2) {
    iVar6 = 0;
  }
  
  int iVar5 = mhInst->animFrame;
  
  if (iVar4 > 3)
  {
	iVar4 = iVar5 - iVar6;

	if (iVar4 < 0) {
      iVar4 = -iVar4;
    }

    if (iVar4 > 3)
	{
	  mhInst->animFrame = (short)iVar6;

      goto SkipLerp;
    }
  }

  mhInst->animFrame = 
	#ifndef REBUILD_PS1
	EngineSound_VolumeAdjust(iVar6,iVar5,1);
	#else
	0;
	#endif

SkipLerp:

  iVar5 = mhInst->animFrame;

  // animFrame
  iVar4 = iVar5 - iVar6;

  if (iVar4 < 0) {
    iVar4 = -iVar4;
  }

  if (iVar4 < 6)
  {
	mhInst->animFrame = 
		#ifndef REBUILD_PS1
		EngineSound_VolumeAdjust(iVar6,iVar5,1);
		#else
		0;
		#endif
  }
  else
  {
    mhInst->animFrame = (short)iVar6;
  }

  // animation frame goes back and forth
  // 0x00: mouth close
  // 0x0C: mouth open

  int lastFrame = 
	DECOMP_VehFrameInst_GetNumAnimFrames(mhInst,0) - 1;

  if (mhInst->animFrame < 0)
	mhInst->animFrame = 0;

  else if (lastFrame < mhInst->animFrame)
      mhInst->animFrame = lastFrame;

  if (sdata->talkMask_boolDead != 0)
  {
    sdata->talkMask_boolDead = 0;

	// dead thread
	t->flags |= 0x800;
  }
}