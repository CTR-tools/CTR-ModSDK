#include <common.h>

void SelectProfile_ThTick(struct Thread *t)
{
  // loop through 12 instances,
  // 3 instances per profile, 4 profile slots
  for (int i = 0; i < 12; i++)
  {
    // determine if it's Relic, Key or Trophy
    int objIndex = (i % 3);

    // and add its corresponding rate
    sdata->LoadSaveData[i].rot[1] += sdata->LoadSave_SpinRateY[objIndex];

    struct Instance * inst = sdata->LoadSaveData[i].inst;

    // convert 3 rotation shorts into rotation matrix
    ConvertRotToMatrix(inst->matrix, sdata->LoadSaveData[i].rot);

    if (objIndex != 1)
    {
      // from MetaDataSaveLoad
      short *rot = data.MetaDataLoadSave[i]->vec3_specular_inverted;
      Vector_SpecLightSpin3D(inst->matrix, sdata->LoadSaveData[i].rot, rot);
    }
  }
}