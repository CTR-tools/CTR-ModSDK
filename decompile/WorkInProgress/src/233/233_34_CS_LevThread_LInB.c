#include <common.h>

void CS_Thread_ThTick(struct Thread*);

void CS_LevThread_LInB(struct Instance* inst)
{
  struct Thread* t;
  short modelID;
  short* meta;
  u_char *puVar6;
  struct CutsceneObj* cs;

  OVR_233.isCutsceneOver = 0;

  // If this Instance's thread does not exist
  if (inst->thread == NULL)
  {
    // thread for CS_Thread_ThTick
    t = PROC_BirthWithObject(
        SIZE_RELATIVE_POOL_BUCKET
        (
          0x60, 
          NONE, 
          MEDIUM, 
          STATIC
        ), 
        
        CS_Thread_ThTick(),	  // behavior
        OVR_233.s_introguy,  // debug name
        0						          // thread relative
      );

    // give thread to Instance
    inst->thread = t;

    // if the thread failed to allocate
    if (t == NULL) return;
    
    // get the object that is attached to the thread
    cs = t->object;

    // Give Instance to thread
    t->inst = inst;

    cs->metadata = (int*)(cs + 0x13);
    cs.prevOpCode = -1; // 0xFFFFFFFF

    // disable subtitles
    cs->Subtitles.lngIndex = -1;

    modelID = inst->model->id;

    if (modelID < NDI_BOX_BOX_01)
    {
      // more than 0x96
      if ((modelID - STATIC_CRASHINTRO) < 16)
      {
        // 0x96 - 0xA6, all STATIC_INTRO types
        puVar6 = (&PTR_DAT_800b41cc_800b457c)[modelID - STATIC_CRASHINTRO];
      }
      // between 0xA6 and 0xB6
      else
      {
        puVar6 = 0x800b2e28;
      }
    }
    // more than 0xB6
    else
    {
      // any of the ND Box types
      puVar6 = (&PTR_DAT_800b49b8_800b5a7c)[modelID - NDI_BOX_BOX_01];
    }

    CS_ScriptCmd_OpcodeAt(cs, puVar6);

    meta = cs->metadata;

    cs->unk18 = (int)meta[4];
    cs->unk14 = meta[2] + (short)(((DECOMP_MixRNG_Scramble() >> 2 & 0xfffU) * ((meta[3] - meta[2]) + 1)) >> 0xc);

    cs->unk1c = 0;
    cs->unk20 = 0;
    cs->unk22 = 0;
    cs->unk24 = 0;
    cs->unk28 = 0;

    cs->unk1e = 0;
    cs->flags = 0;
    cs->unk48 = 0;
    
    cs->scaleSpeed = 0;
    cs->desiredScale = 0x1000;
    cs->unk44[0] = 0xff;
    cs->unk4 = 0;
    cs->unk6 = 0;
    cs->unk8 = 0x2e808080;
    cs->unk_C = 0;
    cs->unk_E = 0;
    cs->ptrIcons = sdata->gGT->iconGroup[5];
  }

  // intro montage for Polar
  if (sdata->gGT->levelID == INTRO_POLAR)
  {
    inst->vertSplit = 0;
    inst->flags |= 0x4000;
  }
}