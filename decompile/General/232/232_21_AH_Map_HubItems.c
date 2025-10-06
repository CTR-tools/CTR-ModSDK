#include <common.h>

void DECOMP_AH_Map_HubItems(struct Map* hubPtrs, short* type)
{

  struct GameTracker *gGT;
  struct AdvProgress *adv;
  short levelID;
  short hubID;
  short iconType;
  short *trophies;
  bool open;
  int menu_TrackIndex;
  u_int bit;
  int iVar5;
  int uVar6;
  short sVar7;
  short sVar8;
  struct HubItem* hubItems;
  SVec2 pos;
  Vec3 pos3D;

  gGT = sdata->gGT;
  adv = &sdata->advProgress;
  levelID = gGT->levelID;

  hubItems = D232.hubItemsXY_ptrArray[levelID - GEM_STONE_VALLEY];
  pos = hubItems->pos;
  
  if (pos.x != -1)
  {

    do
    {
      sVar8 = -1;
      sVar8 = -1;
      sVar7 = (short)0xffffffff; //???
      sVar7 = -1;
      sVar7 = -1;
	  
	  // iconType
      iconType = hubItems->iconType;
	  
      open = true;
	  
	  // Arrow beach->gemstone
      if (iconType == -1)
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
        if (iconType > -1)
        {
		  
		  // gemstone valley
          if (iconType == 4)
          {
            menu_TrackIndex = 0;
            iVar5 = 0;

			// check 4 boss keys
            for (menu_TrackIndex = 0; menu_TrackIndex < 4; menu_TrackIndex++)
            {
              bit = menu_TrackIndex + PRIZE_BOSS_KEY;

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
			
            if (3 < iconType)
            {
              iVar5 = -0x10000;
              sVar8 = sVar8;
			  
			  // saveLoad screen (0x64)
              if (iconType == 100)
              {
				Vec2 newPos;
                newPos.x = (int)hubItems->pos.x -0x200;
                newPos.y = (int)hubItems->pos.y -0x100;
				
                DECOMP_UI_Map_GetIconPos(hubPtrs, &newPos);
                
				DECOMP_AH_Map_LoadSave_Full(
					&newPos,
					&D232.loadSave_pos[0], (char*)&D232.loadSave_col[0],
					0x800, (int)hubItems->angle
				);
				
                iVar5 = -0x10000;
              }
              goto LAB_800b17ec;
            }
			
			// did not use GOTO,
			// must be == 3, for Boss Garage
			
			int base = levelID - N_SANITY_BEACH;
			
            for (menu_TrackIndex = 0; menu_TrackIndex < 4; menu_TrackIndex++)
            {
              trophies = &data.advHubTrackIDs[base * 4];
			  
              if (CHECK_ADV_BIT(adv->rewards, (trophies[menu_TrackIndex]+PRIZE_TROPHY_RACE)) == 0)
              {
                open = false;
                break;
              }
            }
            if (!open)
              goto LAB_800b17e4;

			// check if key is unlocked
            sVar7 = CHECK_ADV_BIT(adv->rewards, (base+PRIZE_BOSS_KEY));
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
        if (iconType == -4)
        {
		  // locked if keys < 2
          sVar7 = ((gGT->currAdvProfile.numKeys) < 2);
          goto LAB_800b17e8;
        }
        if (iconType < -3)
        {
		  // Arrow glacier->citadel
          if (iconType == -5)
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
          if ((iconType == -3) || (iconType == -2))
          {
			// never locked
            sVar7 = 0;
			
            goto LAB_800b17e8;
          }
          iVar5 = -1;
        }
      }
	  
      if (iVar5 > -1)
      {
		Vec2 newPos;
		
        newPos.x = (int)hubItems->pos.x -0x200;
        newPos.y = (int)hubItems->pos.y -0x100;
        DECOMP_UI_Map_GetIconPos(hubPtrs, &newPos);
        if ((iVar5 == 0) && (D232.unkModeHubItems == 0))
        {
          DECOMP_AH_Map_HubArrowOutter(
              hubPtrs, (int)*type, &newPos,
              (0x1000 - hubItems->angle), 1);
          *type++;
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
			&newPos, 
			&D232.hubArrow_pos[0], (char*)&D232.hubArrow_col1[iVar5],
			0x800, (int)hubItems->angle);
      }
	  
      if (-1 < sVar8)
      {
        pos3D.x = (int)hubItems->pos.x;
        pos3D.y = 0;
        pos3D.z = (int)hubItems->pos.y;
        
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

          DECOMP_UI_Map_GetIconPos(hubPtrs, &pos3D);

          DECOMP_AH_Map_HubArrowOutter(hubPtrs, (int)*type, &pos3D, 0, 2);

          *type++;
        }
		
		// draw star icon for boss
        DECOMP_UI_Map_DrawRawIcon(hubPtrs, &pos3D, 0x37, uVar6, 0, 0x1000);
      }

    } while (hubItems->angle != -1);
  }
  return;
}
