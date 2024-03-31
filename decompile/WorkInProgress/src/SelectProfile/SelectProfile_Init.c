#include <common.h>

void SelectProfile_Init(u_int flags)
{
  char n, p;
  short scale;
  struct Thread *t;
  struct Instance *inst;
  u_int rgba;

  struct Thread **ppsVar8;
  struct GameTracker *gGT = sdata->gGT;

  // if loadsave object does not exist
  if (sdata->ptrLoadSaveObj == NULL)
  {
    t = PROC_BirthWithObject(
        SIZE_RELATIVE_POOL_BUCKET(
            0x90,
            NONE,
            SMALL,
            OTHER),

        SelectProfile_ThTick(), // behavior
        "LoadSave",        // debug name
        0                  // thread relative
    );

    // Get the object attached to the thread
    load = t->object;
    // store object globally
    sdata->ptrLoadSaveObj = load;
    // store thread in object
    load->thread = t;
  
    // init instance... 
    load->inst = &sdata.LoadSaveData[0].inst;

    memset(sdata.LoadSaveData[0].inst, 0, 0x90);

    // check if creation failed
    if (sdata->ptrLoadSaveObj == NULL)
      return;

    for (n = 0; n < 12; n++)
    {
      if (load->inst == NULL)
      {
        struct Model * m = gGT->modelPtr[data.MetaDataLoadSave[n]->modelID];
        if (m != NULL)
        {
          inst = INSTANCE_Birth3D(m, "loadsave", t);
          load->i[n] = inst;
          
          // if instance exists
          if (inst != NULL)
          {
            inst->flags |= 0x480;
            if ((n % 3) != 1)
            {
              inst->flags |= 0x20480;
            }

            // instance -> InstDrawPerPlayer[0].pushBuffer = PushBuffer_UI
            struct InstDrawPerPlayer* idpp = INST_GETIDPP(inst);
            idpp[0].pushBuffer = &gGT->pushBuffer_UI;

            // if more than 1 screen
            for (p = 1; p < gGT->numPlyrCurrGame; p++)
            {
              // erase pushBuffer
              idpp[p].pushBuffer= 0;
            }

            // decide colors
            if ((flags & 0x10) == 0)
            {
              rgba = (u_int)data.MetaDataLoadSave[n].r << 0x14 | data.MetaDataLoadSave[n].g << 0xc | data.MetaDataLoadSave->b << 4;
            }
            else
            {
              rgba = (u_int)(data.MetaDataLoadSave[n].r >> 1) << 0x14 | data.MetaDataLoadSave[n].g << 0xc | (data.MetaDataLoadSave->b >> 1) << 4;
            }

            inst->colorRGBA = rgba;

            // scale (x, y, z)
            scale = data.MetaDataLoadSave[n].scale;
            inst->scale[2] = scale;
            inst->scale[1] = scale;
            inst->scale[0] = scale;
            load->inst->next = 0;
            load->inst->prev = 0;
            load->inst->name = sdata->unk_80085d0c_LoadSave[(n % 3) >> 1]; // ??
            
            // set rotation (5 direction vectors)
            *(int *)&inst->matrix.m[0][0] = 0x1000;
            *(int *)&inst->matrix.m[0][2] = 0;
            *(int *)&inst->matrix.m[1][1] = 0x1000;
            *(int *)&inst->matrix.m[2][0] = 0;
            inst->matrix.m[2][2] = 0x1000;
          }
        }
        if (load->i[n] != NULL)
          goto LAB_80048878;
      }
      else
      {
      LAB_80048878:
        load->i[n]->flags |= HIDE_MODEL;
      }
      t = t->siblingThread; // ?
    }
  }
}
