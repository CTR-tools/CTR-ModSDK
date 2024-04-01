#include <common.h>

void DECOMP_AH_Map_HubItems(void* hubPtrs, short *param_2)
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
  int uVar6;
  short sVar7;
  short sVar8;
  short *psVar9;
  short *psVar10;
  int pos3D[3];
  int local_40;
  int local_3c;
  int local_38;
  int local_34;
  int local_30;
  int local_2c;

  gGT = sdata->gGT;
  adv = &sdata->advProgress;
  levelID = gGT->levelID;

  psVar10 = D232.hubItemsXY_ptrArray[levelID-0x19];
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
	  
	  // iconType
      sVar1 = psVar9[2];
	  
      open = true;
	  
	  // Arrow beach->gemstone
      if (sVar1 == -1)
      {
        sVar7 = 0;

        if (levelID == N_SANITY_BEACH)
        {
		  // locked if key < 1
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
		  
		  // gemstone valley
          if (sVar1 == 4)
          {
            iVar3 = 0;
            iVar5 = 0;

			// check 4 boss keys
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
            sVar7 = sdata->advProgress.rewards[3] & 4;
          }
		  
		  // not gemstone valley
          else
          {
            iVar5 = 0;
			
            if (3 < sVar1)
            {
              iVar5 = -0x10000;
              sVar8 = sVar8;
			  
			  // saveLoad screen (0x64)
              if (sVar1 == 100)
              {
                local_40 = (int)*psVar10 + -0x200;
                local_3c = (int)*psVar9 + -0x100;
				
                DECOMP_UI_Map_GetIconPos(hubPtrs, &local_40, &local_3c);
                
				DECOMP_AH_Map_LoadSave_Full(
					local_40, local_3c, 
					&D232.loadSave_pos[0], &D232.loadSave_col[0], 
					0x800, (int)psVar9[1]
				);
				
                iVar5 = -0x10000;
              }
              goto LAB_800b17ec;
            }
			
			// did not use GOTO,
			// must be == 3, for Boss Garage
			
			int base = levelID - N_SANITY_BEACH;
			
            for (iVar3 = 0; iVar3 < 4; iVar3++)
            {
              trophies = &data.advHubTrackIDs[base * 4];
			  
              if (CHECK_ADV_BIT(adv->rewards, (trophies[iVar3]+6)) == 0)
              {
                open = false;
                break;
              }
            }
            if (!open)
              goto LAB_800b17e4;

			// check if key is unlocked
            sVar7 = CHECK_ADV_BIT(adv->rewards, (base+0x5e));
          }
		  
		  // open, not beaten
          sVar8 = 1;
		  
          iVar5 = -0x10000;
          
		  // boss is beaten
		  if (sVar7 != 0)
          {
            sVar8 = 2;
          }
          goto LAB_800b17ec;
        }
		
		// Arrow beach->glacier
        if (sVar1 == -4)
        {
		  // locked if keys < 2
          sVar7 = ((gGT->currAdvProfile.numKeys) < 2);
          goto LAB_800b17e8;
        }
        if (sVar1 < -3)
        {
		  // Arrow glacier->citadel
          if (sVar1 == -5)
          {
			// locked if keys < 3
            sVar7 = ((gGT->currAdvProfile.numKeys) < 3);
            goto LAB_800b17e8;
          }
          iVar5 = -1;
        }
		
        else
        {
		  // either arrow on Gemstone hub,
		  // pointing to beach or to ruins
          if ((sVar1 == -3) || (sVar1 == -2))
          {
			// never locked
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
        DECOMP_UI_Map_GetIconPos(hubPtrs, &local_38, &local_34);
        if ((iVar5 == 0) && (D232.unkModeHubItems == 0))
        {
          DECOMP_AH_Map_HubArrowOutter(
              hubPtrs, (int)*param_2, local_38, local_34,
              (0x1000 - (u_short)psVar9[1]), 1);
          *param_2 = *param_2 + 1;
        }
		
        // if even frame
		if ((gGT->timer & FPS_DOUBLE(2)) == 0)
        {
          iVar5 = (int)sVar7 * 6;
        }
        else
        {
          iVar5 = ((int)sVar7 * 2 + 1) * 3;
        }

        DECOMP_AH_Map_HubArrow(
			local_38, local_34, 
			&D232.hubArrow_pos[0], &D232.hubArrow_col1[iVar5], 
			0x800, (int)psVar9[1]);
      }
	  
      if (-1 < sVar8)
      {
        pos3D[0] = (int)*psVar10;
        pos3D[1] = 0;
        pos3D[2] = (int)*psVar9;
        
		// if beat boss race
		if (sVar8 == 2)
        {
		  // red
          uVar6 = 3;
        }
        else
        {
		  // locked boss race
		  // sVar6 == 0
			
		  // grey
          uVar6 = 0x17;
		  
		  // open, not beaten
          if (sVar8 == 1)
          {
			// blue and white
			// depending on frames
			uVar6 = 5;
            if ((gGT->timer & FPS_DOUBLE(2)) != 0)
				uVar6 = 4;
          }
        }
		
		// open, not beaten
        if (sVar8 == 1)
        {
          D232.unkModeHubItems = sVar8;
          local_30 = pos3D[0];
          local_2c = pos3D[2];

          DECOMP_UI_Map_GetIconPos(hubPtrs, &local_30, &local_2c);

          DECOMP_AH_Map_HubArrowOutter(hubPtrs, (int)*param_2, local_30, local_2c, 0, 2);

          *param_2 = *param_2 + 1;
        }
		
		// draw star icon for boss
        DECOMP_UI_Map_DrawRawIcon(hubPtrs, &pos3D[0], 0x37, uVar6, 0, 0x1000);
      }
      psVar10 = psVar10 + 4;
      psVar9 = psVar9 + 4;
    } while (*psVar10 != -1);
  }
  return;
}
