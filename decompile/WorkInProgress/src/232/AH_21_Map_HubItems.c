#include <common.h>

void DECOMP_AH_Map_HubItems(undefined4 param_1, short *param_2)
{

  struct GameTracker *gGT;
  struct AdvProgress *adv;
  short levelID;
  short hubID;
  short sVar1;
  short *trophies;
  bool open;
  int iVar3;
  u_int bit;
  int iVar5;
  undefined4 uVar6;
  short sVar7;
  short sVar8;
  short *psVar9;
  short *psVar10;
  int local_50;
  undefined4 local_4c;
  int local_48;
  int local_40;
  int local_3c;
  int local_38;
  int local_34;
  int local_30;
  int local_2c;

  gGT = sdata->gGT;
  adv = &sdata->advProgress;
  levelID = gGT->levelID;
  hubID = levelID - N_SANITY_BEACH;

  psVar10 = (short *)(&PTR_DAT_800b4ed4_800b4f9c)[hubID];
  if (*psVar10 != -1)
  {
    psVar9 = psVar10 + 1;
    do
    {
      sVar8 = -1;
      sVar8 = -1;
      sVar7 = 0xffffffff;
      sVar7 = -1;
      sVar7 = -1;
      sVar1 = psVar9[2];
      open = true;
      if (sVar1 == -1)
      {
        sVar7 = 0;

        if (levelID == N_SANITY_BEACH)
        {
          sVar7 = (gGT->currAdvProfile.numKeys < 1);
        }
      LAB_800b17e8:
        iVar5 = sVar7 << 0x10;
        sVar8 = sVar8;
        sVar7 = (short)sVar7;
      LAB_800b17ec:
        iVar5 = iVar5 >> 0x10;
      }
      else
      {
        if (-1 < sVar1)
        {
          sVar7 = sVar7;
          if (sVar1 == 4)
          {
            iVar3 = 0;
            iVar5 = 0;

            for (iVar3 = 0; iVar3 < 4; iVar3++)
            {
              bit = iVar3 + 0x5e;

              if (CHECK_ADV_BIT(adv->rewards, bit) == 0)
              {
                open = false;
                break;
              }
            }
            if (!open)
            {
            LAB_800b17e4:
              sVar8 = 0;
              goto LAB_800b17e8;
            }
            sVar7 = DAT_8008fbb0 & 4;
          }
          else
          {
            iVar5 = 0;
            if (3 < sVar1)
            {
              iVar5 = -0x10000;
              sVar8 = sVar8;
              if (sVar1 == 100)
              {
                local_40 = (int)*psVar10 + -0x200;
                local_3c = (int)*psVar9 + -0x100;
                UI_Map_GetIconPos(param_1, &local_40, &local_3c);
                AH_Map_LoadSave_Full(local_40, local_3c, &DAT_800b4fcc,
                                     &DAT_800b4fdc, 0x800, (int)psVar9[1]);
                iVar5 = -0x10000;
              }
              goto LAB_800b17ec;
            }
            for (iVar3 = 0; iVar3 < 4; iVar3++)
            {
              trophies = &data.advTrackIDs_orderOfTrophies[(levelID - N_SANITY_BEACH) * 4];
              if (CHECK_ADV_BIT(adv->rewards, trophies[iVar3]) == 0)
              {
                open = false;
                break;
              }
            }
            if (!open)
              goto LAB_800b17e4;

            sVar7 = CHECK_ADV_BIT(adv->rewards, levelID + 0x44);
          }
          sVar8 = 1;
          iVar5 = -0x10000;
          if (sVar7 != 0)
          {
            sVar8 = 2;
          }
          goto LAB_800b17ec;
        }
        if (sVar1 == -4)
        {
          sVar7 = ((gGT->currAdvProfile.numKeys) < 2);
          goto LAB_800b17e8;
        }
        if (sVar1 < -3)
        {
          if (sVar1 == -5)
          {
            sVar7 = ((gGT->currAdvProfile.numKeys) < 3);
            goto LAB_800b17e8;
          }
          iVar5 = -1;
        }
        else
        {
          if ((sVar1 == -3) || (sVar1 == -2))
          {
            sVar7 = 0;
            goto LAB_800b17e8;
          }
          iVar5 = -1;
        }
      }
      if (-1 < iVar5)
      {
        local_38 = (int)*psVar10 + -0x200;
        local_34 = (int)*psVar9 + -0x100;
        UI_Map_GetIconPos(param_1, &local_38, &local_34);
        if ((iVar5 == 0) && (0x800b5670 == 0))
        {
          AH_Map_HubArrowOutter(
              param_1, (int)*param_2, local_38, local_34,
              (0x1000 - (u_short)psVar9[1]), 1);
          *param_2 = *param_2 + 1;
        }
        // if even frame
        if (((gGT->timer) & 2) == 0)
        {
          iVar5 = (int)sVar7 * 6;
        }
        else
        {
          iVar5 = ((int)sVar7 * 2 + 1) * 3;
        }

        AH_Map_HubArrow(local_38, local_34, &DAT_800b4fec, iVar5 * 4 + 0x800B4FF8, 0x800, (int)psVar9[1]);
      }
      if (-1 < sVar8)
      {
        local_50 = (int)*psVar10;
        local_4c = 0;
        local_48 = (int)*psVar9;
        if (sVar8 == 2)
        {
          uVar6 = 3;
        }
        else
        {
          uVar6 = 0x17;
          if ((sVar8 == 1) && (uVar6 = 5,
                               // if even frame
                               ((gGT->timer) & 2) != 0))
          {
            uVar6 = 4;
          }
        }
        if (sVar8 == 1)
        {
          *(short *)0x800b5670 = sVar8;
          local_30 = local_50;
          local_2c = local_48;

          UI_Map_GetIconPos(param_1, &local_30, &local_2c);

          AH_Map_HubArrowOutter(param_1, (int)*param_2, local_30, local_2c, 0, 2);

          *param_2 = *param_2 + 1;
        }
        UI_Map_DrawRawIcon(param_1, &local_50, 0x37, uVar6, 0, 0x1000);
      }
      psVar10 = psVar10 + 4;
      psVar9 = psVar9 + 4;
    } while (*psVar10 != -1);
  }
  return;
}
