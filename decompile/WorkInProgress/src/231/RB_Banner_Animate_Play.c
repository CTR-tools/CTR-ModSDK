#include <common.h>

void RB_Banner_Animate_Play(struct ModelHeader* headers, short param_2)
{
  char bVar1;
  int iVar2;
  u_int uVar3;
  u_int *puVar4;
  u_int *puVar5;
  char *pbVar6;
  char *pbVar8;
  u_int uVar9;

  puVar4 = headers->ptrColors;

  uVar9 = *puVar4;
  puVar5 = puVar4;
  for (char i = 0; i < 64; i++) {
   puVar5 = puVar5 + 1;
    *puVar4 = *puVar5;
    puVar4 = puVar4 + 1;
  }
   
  *puVar4 = uVar9;

  pbVar6 = (char *)(headers->ptrFrameData[headers->ptrFrameData->unk16[12]]);

  pbVar8 = pbVar6 + (int)param_2 * 3;
  do
  {
    if (pbVar8 <= pbVar6)
    {
      return;
    }
    bVar1 = *(char*)&headers->ptrColors[(*pbVar6 >> 2) + 10];
    uVar3 = *pbVar6;
    if (uVar3 < 0x40)
    {
      iVar2 = uVar3 << 2;
    LAB_800b5788:
      bVar1 = (char)((bVar1 - 0x80) * iVar2 >> 8) + 0x80;
    }
    else
    {
      if (0xc0 < uVar3)
      {
        iVar2 = (0x100 - uVar3) * 4;
        goto LAB_800b5788;
      }
    }
    pbVar6[1] = bVar1;
    pbVar6 += 3;
  } while (true);
}