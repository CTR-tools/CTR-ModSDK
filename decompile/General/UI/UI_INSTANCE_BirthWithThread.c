#include <common.h>

int DECOMP_UI_INSTANCE_BirthWithThread(int param_1,int param_2,int param_3,int param_4,int param_5,int param_6)

{
  short modelID;
  short sVar2;
  short sVar3;
  short uVar5;
  struct Thread* hudThread;
  long lVar7;
  struct UiElement2D *hudStruct;
  int color;
  struct UiElement2D *puVar10;
  short *psVar11;
  struct UiElement3D* ui3D;
  struct Instance* bigNum;
  struct Driver* driver;
  struct Thread* driverThread;
  struct Model* model;
  short rot[3];
  
  struct GameTracker* gGT;
  gGT = sdata->gGT;

  // get model pointer
  model = gGT->modelPtr[param_1];

  hudStruct = data.hudStructPtr[gGT->numPlyrCurrGame - 1];

  bigNum = 0;
  // if model exist
  if (model != 0)
  {
    driverThread = gGT->threadBuckets[0].thread;

    while (driverThread != 0)
	{
      driver = driverThread->object;

	  // Create a new thread for this HUD element
	  // 0x38 = size
	  // 0 = no relation to param4
	  // 0x300 = SmallStackPool
	  // 0x10 = hud thread bucket
      hudThread = DECOMP_THREAD_BirthWithObject(0x380310,param_2,param_6,0);

	  // Get the object attached to the thread
      ui3D = hudThread->object;

	  // Big Number HUD element
      bigNum = DECOMP_INSTANCE_Birth2D(model,0,hudThread);

	  // give the Instance to the thread
      hudThread->inst = bigNum;

	  modelID = model->id;

      if (modelID == 0x38)
	  {
		driver->BigNumber[0] = bigNum;
      }
	  
      else if (modelID == 0x37) 
	  {
        driver->BigNumber[1] = bigNum;
      }

	  // if this is a gem
	  else if (modelID == 0x5f) {
        color = 0x6c08080;
LAB_8004cc4c:
        ui3D->lightDir[0] = 0xf368;
        ui3D->lightDir[1] = 0x99f;
        ui3D->lightDir[2] = 0x232;
LAB_8004cc58:
        bigNum->colorRGBA = color;

		// specular lighting
        bigNum->flags |= 0x20000;
      }
      
	  // crystal
      else if (modelID == 0x60) 
	  {
        ui3D->lightDir[0] = 0xf4a0;
        ui3D->lightDir[1] = 0xb60;
        ui3D->lightDir[2] = 0xfd28;
        color = 0xd22fff0;
        goto LAB_8004cc58;
      }
	  
	  // relic
	  else if (modelID == 0x61) 
	  {
        color = 0x60a5ff0;
        goto LAB_8004cc4c;
	  }

	  // key
      else if (modelID == 99) 
	  {
        color = 0xdca6000;
        goto LAB_8004cc4c;
      }

	  // if C-T-R letters
      if ((unsigned int)(modelID - 0x93U) < 3) 
	  {	    
	    // -4 for C
	    // +0 for T
	    // +4 for R
        ui3D->rot[0] = (modelID-0x94) * 4;
        ui3D->rot[1] = 0xc;
	  
	    // Set color
        bigNum->colorRGBA = 0xffc8000;
	  
		goto lightDir_spec0x30000;
      }
        
	  // token
	  else if (modelID == 0x7d)
	  {
		// get AdvCup ID from level metadata
        int advCupID = data.metaDataLEV[gGT->levelID].ctrTokenGroupID;
	  	  	
	  	short* cupColor = &data.AdvCups[advCupID].color[0];
	  	
        bigNum->colorRGBA = 
			(cupColor[0] << 0x14) | 
			(cupColor[1] << 0xc) | 
			(cupColor[2] << 4);
        
lightDir_spec0x30000:
		
	  	ui3D->lightDir[0] = 0xf368;
        ui3D->lightDir[1] = 0x99f;
        ui3D->lightDir[2] = 0x232;
	  
	  	bigNum->flags |= 0x30000;
	  }

	  // if no tileView is supplied
	  if (param_5 == 0)
	  {
		// TODO: fix struct size
        psVar11 = &hudStruct[2*param_3].x;

		// Convert X
        color = DECOMP_UI_ConvertX_2(*psVar11,psVar11[2]);
        bigNum->matrix.t[0] = color;

		// Convert Y
		color = DECOMP_UI_ConvertY_2(psVar11[1],psVar11[2]);
        bigNum->matrix.t[1] = color;

		bigNum->matrix.t[2] = psVar11[2];
      }

	  // if tileView is supplied,
	  // for decalMP and fruitDisp
      else
	  {
		struct InstDrawPerPlayer* idpp = INST_GETIDPP(bigNum);
        idpp[0].tileView = param_5;

		// record that tileView is present
		bigNum->flags |= 0x100;

        bigNum->matrix.t[0] = 0;
        bigNum->matrix.t[1] = 0;
        bigNum->matrix.t[2] = 0x200;
      }

	  // TODO: There's 0x14 elements, 8 bytes large,
	  // There are NOT 0x28 elements, 4 bytes large
	  puVar10 = &hudStruct[2*param_3];
      uVar5 = puVar10[1].y;
      bigNum->scale[0] = uVar5;
      bigNum->scale[1] = uVar5;
      bigNum->scale[2] = uVar5;
	  
      bigNum->unk50 = 0x80;
      bigNum->unk51 = 0x80;
      if (param_4 == 0) {
        rot[0] = 0;
      }
      else {
        lVar7 = ratan2(bigNum->matrix.t[1],bigNum->matrix.t[2]);
        rot[0] = -(short)lVar7;
      }
      rot[1] = 0;
      rot[2] = 0;

#ifndef REBUILD_PS1
      ConvertRotToMatrix(&ui3D->m,&rot[0]);
#else
	  TEST_ConvertRotToMatrix(&ui3D->m,&rot[0]);
#endif

      ui3D->rot[0] = 0;
      ui3D->rot[1] = 0;
      ui3D->rot[2] = 0;
      ui3D->rot[3] = 0x1000;

	  // thread = thread -> next
      driverThread = driverThread->next;

	  // TODO: fix struct size
	  hudStruct += 0x28;
    }
  }
  return bigNum;
}