#include <common.h>

void UI_ThTick_Reward(struct Thread*);
void UI_ThTick_CountPickup(struct Thread*);

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
  short *puVar12;
  struct Instance* bigNum;
  struct Driver* driver;
  struct Thread* driverThread;
  struct Model* model;
  short local_30;
  short local_2e;
  short local_2c;

  // get model pointer
  model = sdata->gGT->modelPtr[param_1];

  hudStruct = data.hudStructPtr[sdata->gGT->numPlyrCurrGame - 1];

  bigNum = 0;
  // if model exist
  if (model != 0)
  {
    driverThread = sdata->gGT->threadBuckets[0].thread;

    while (driverThread != 0)
	{
      driver = driverThread->object;

	  // Create a new thread for this HUD element
	  // 0x38 = size
	  // 0 = no relation to param4
	  // 0x300 = SmallStackPool
	  // 0x10 = hud thread bucket
      hudThread = THREAD_BirthWithObject(0x380310,param_2,param_6,0);

	  // Get the object attached to the thread
      puVar12 = hudThread->object;

	  // Big Number HUD element
      bigNum = INSTANCE_Birth2D(model,0,hudThread);

	  // give the Instance to the thread
      hudThread->inst = bigNum;

      if (model->id == 0x38)
	  {
		// set pointer to instance of Big Number in HUD
        driver->BigNumber[0] = bigNum;
      }
      else {
        if (model->id == 0x37) {
          driver->BigNumber[1] = bigNum;
        }
      }

	  // model -> id
	  modelID = model->id;

	  // if this is a gem
	  if (modelID == 0x5f) {
        color = 0x6c08080;
LAB_8004cc4c:
        puVar12[0x14] = 0xf368;
        puVar12[0x15] = 0x99f;
        puVar12[0x16] = 0x232;
LAB_8004cc58:
        bigNum->colorRGBA = color;

		// specular lighting
        bigNum->flags |= 0x20000;
      }
      else
	  {
		// relic
        if (modelID == 0x61) {
          color = 0x60a5ff0;
          goto LAB_8004cc4c;
        }

		// crystal
        if (modelID == 0x60) {
          puVar12[0x14] = 0xf4a0;
          puVar12[0x15] = 0xb60;
          color = 0xd22fff0;
          puVar12[0x16] = 0xfd28;
          goto LAB_8004cc58;
        }

		// key
        if (modelID == 99) {
          color = 0xdca6000;
          goto LAB_8004cc4c;
        }

		// if C-T-R letters
        if ((short)(model->id - 0x93U) < 3) {
          puVar12[0x14] = 0xf368;
          puVar12[0x15] = 0x99f;
          puVar12[0x16] = 0x232;
          puVar12[0x19] = 0xc;

		  // modelID
          modelID = model->id;

		  // letter C
          if (modelID == 0x93) {
            uVar5 = 0xfffc;
LAB_8004ccc8:
            puVar12[0x18] = uVar5;
          }
          else
		  {
			// letter T
            if (modelID == 0x94)
			{
              puVar12[0x18] = 0;
            }

			else
			{
			  // letter R
              if (modelID == 0x95) {
                uVar5 = 4;
                goto LAB_8004ccc8;
              }
            }
          }

		  // Set color
          bigNum->colorRGBA = 0xffc8000;

		  // specular lighting
          bigNum->flags |= 0x30000;
        }
        else
		{
		  // token model
          if (modelID == 0x7d)
		  {
			// get AdvCup ID from level metadata
            int advCupID = data.metaDataLEV[sdata->gGT->levelID].ctrTokenGroupID;

			puVar12[0x14] = 0xf368;
            puVar12[0x15] = 0x99f;
            puVar12[0x16] = 0x232;

			// get color from Adv Cup ID
			advCupID = advCupID << 3;
            modelID = data.AdvCups[advCupID].color[0];
            sVar2 = data.AdvCups[advCupID].color[1];
            sVar3 = data.AdvCups[advCupID].color[2];

			bigNum->flags |= 0x30000;
            bigNum->colorRGBA = modelID << 0x14 | sVar2 << 0xc | sVar3 << 4;
          }
        }
      }

	  // if no tileView is supplied
	  if (param_5 == 0)
	  {
        psVar11 = hudStruct[param_3].x;

		// Convert X
        color = UI_ConvertX_2(*psVar11,psVar11[2]);
        bigNum->matrix.t[0] = color;

		// Convert Y
		color = UI_ConvertY_2(psVar11[1],psVar11[2]);
        bigNum->matrix.t[1] = color;

		bigNum->matrix.t[2] = psVar11[2];
      }

	  // if tileView is supplied
      else
	  {
		// instance->tileView
        bigNum->idpp[0].tileView = param_5;

		// record that tileView is present
		bigNum->flags = bigNum->flags | 0x100;

        bigNum->matrix.t[0] = 0;
        bigNum->matrix.t[1] = 0;
        bigNum->matrix.t[2] = 0x200;
      }

	  puVar10 = &hudStruct[param_3];
      bigNum->scale[0] = puVar10->x + 6;
      bigNum->scale[1] = puVar10->x + 6;
      uVar5 = puVar10->x + 6;
      bigNum->unk50 = 0x80;
      bigNum->unk51 = 0x80;
      bigNum->scale[2] = uVar5;
      if (param_4 == 0) {
        local_30 = 0;
      }
      else {
        lVar7 = ratan2(*(long *)bigNum->matrix.t[1],*(long *)bigNum->matrix.t[2]);
        local_30 = -(short)lVar7;
      }
      local_2e = 0;
      local_2c = 0;

	   // convert 3 rotation shorts into rotation matrix
      ConvertRotToMatrix(puVar12 + 4,&local_30);

      *puVar12 = 0;
      puVar12[1] = 0;
      puVar12[2] = 0;
      puVar12[3] = 0x1000;

	  // thread = thread -> next
      driverThread = driverThread->next;

	  hudStruct += 0xa0;
    }
  }
  return bigNum;
}