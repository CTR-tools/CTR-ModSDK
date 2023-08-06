#include <common.h>

void LoadSave_ThTick(struct Thread* th)
{
  char i;
  int iVar1;
  int iVar2;
  int *piVar3;
  int *piVar4;
  short local_28;
  short local_26;
  short local_24;

  piVar4 = *(int **)((struct LoadSaveData *)th->object)->data[0];
  piVar3 = piVar4 + 1;

  // loop through 12 instances,
  // 3 per profile, 4 profiles
  for (i = 0; i < 12; i++) 
  {
    iVar1 = (i % 3);
    *(short *)((int)piVar3 + 2) += ((short*)0x8008d47c)[iVar1];

	 // convert 3 rotation shorts into rotation matrix
    ConvertRotToMatrix(*piVar4 + 0x30,piVar3);

    if (iVar1 != 1)
	{
	  // from MetaDataSaveLoad
      local_28 = data.MetaDataLoadSave[i]->vec3_specular_inverted[0];
      local_26 = data.MetaDataLoadSave[i]->vec3_specular_inverted[1];
      local_24 = data.MetaDataLoadSave[i]->vec3_specular_inverted[2];
	  // 
      Vector_SpecLightSpin3D(*piVar4,piVar3,&local_28);
    }
    piVar3 = piVar3 + 3;
    piVar4 = piVar4 + 3;
  }
  return;
}