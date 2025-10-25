#include <common.h>

//TODO: i think door arrows are a little bit off ?
void DECOMP_AH_Map_HubItems(struct Map* hubPtrs, short *type)
{

  struct GameTracker *gGT;
  struct AdvProgress *adv;
  short levelID;
  short hubID;
  short iconType;
  short *trophies;
  bool open;
  unsigned char i;
  u_int bit;
  int arrowColIndex;
  unsigned char itemColorID; //must be for data.ptrColor[itemColorID]
  short boolKey;
  short itemMode;
  short typeCount;
  Vec3 boss_StarPos;
  
  //load/save instance on minimap
  Vec2 saveObjpos;
  
  //most likely the arrows for hub doors
  Vec2 arrow1;
  Vec2 arrow2;
  
  

  gGT = sdata->gGT;
  adv = &sdata->advProgress;
  levelID = gGT->levelID;
  hubID = levelID - GEM_STONE_VALLEY;  
  typeCount = type[0];
  


    for(struct HubItem* hubitem = D232.hubItemsXY_ptrArray[hubID];
	hubitem->pos.x != -1; hubitem++) //hubitem[lastIndex +1]->pos.x is always -1
    {
      itemMode = -1;
      boolKey = -1;
	  
	  // iconType
      iconType = hubitem->iconType;
	  
      open = true;
	  
	  // Arrow beach->gemstone
      if (iconType == -1)
      {
        boolKey = 0;

        if (levelID == N_SANITY_BEACH)
        {
		  // locked if key < 1
          boolKey = (gGT->currAdvProfile.numKeys < 1);
        }
		
      LAB_800b17e8:
        arrowColIndex = boolKey << 0x10;
      LAB_800b17ec:
        arrowColIndex = arrowColIndex >> 0x10;
      }
      else
      {
        if (iconType > -1)
        {
          boolKey = boolKey;
		  
		  // gemstone valley
          if (iconType == 4)
          {
            i = 0;
            arrowColIndex = 0;

			// check 4 boss keys
            for (i = 0; i < 4; i++)
            {
              bit = i + PRIZE_BOSS_KEY;

              if (CHECK_ADV_BIT(adv->rewards, bit) == 0)
              {
                open = false;
                break;
              }
            }
            if (!open)
            {
            LAB_800b17e4:
              itemMode = 0;
              goto LAB_800b17e8;
            }
            boolKey = sdata->advProgress.rewards[3] & 4;
          }
		  
		  // not gemstone valley
          else
          {
            arrowColIndex = 0;
			
            if (iconType > 3)
            {
              arrowColIndex = -0x10000;
			  
			  // saveLoad screen (0x64)
              if (iconType == 100)
              {
				
				saveObjpos.x = hubitem->pos.x -0x200;
				saveObjpos.y = hubitem->pos.y -0x100;
				
                DECOMP_UI_Map_GetIconPos(hubPtrs, &saveObjpos);
                
				DECOMP_AH_Map_LoadSave_Full(
					&saveObjpos, 
					&D232.loadSave_pos[0], (char*)&D232.loadSave_col[0],
					0x800, hubitem->angle
				);
				
                arrowColIndex = -0x10000;
              }
              goto LAB_800b17ec;
            }
			
			// did not use GOTO,
			// must be == 3, for Boss Garage
			
			
            for (i = 0; i < 4; i++)
            {
				//should skip gemstone valley
              trophies = &data.advHubTrackIDs[(hubID + 1) * 4];
			  
              if (CHECK_ADV_BIT(adv->rewards, (trophies[i]+PRIZE_TROPHY_RACE)) == 0)
              {
                open = false;
                break;
              }
            }
            if (!open)
              goto LAB_800b17e4;

			// check if key is unlocked
			//should skip gem stone valley
            boolKey = CHECK_ADV_BIT(adv->rewards, ((hubID +1)+PRIZE_BOSS_KEY));
          }
		  
		  // open, not beaten
          itemMode = 1;
		  
          arrowColIndex = -0x10000;
          
		  // boss is beaten
		  if (boolKey != 0)
          {
            itemMode = 2;
          }
          goto LAB_800b17ec;
        }
		
		// Arrow beach->glacier
        if (iconType == -4)
        {
		  // locked if keys < 2
          boolKey = ((gGT->currAdvProfile.numKeys) < 2);
          goto LAB_800b17e8;
        }
        if (iconType < -3)
        {
		  // Arrow glacier->citadel
          if (iconType == -5)
          {
			// locked if keys < 3
            boolKey = ((gGT->currAdvProfile.numKeys) < 3);
            goto LAB_800b17e8;
          }
          arrowColIndex = -1;
        }
		
        else
        {
		  // either arrow on Gemstone hub,
		  // pointing to beach or to ruins
          if ((iconType == -3) || (iconType == -2))
          {
			// never locked
            boolKey = 0;
			
            goto LAB_800b17e8;
          }
          arrowColIndex = -1;
        }
      }
	  
      if (arrowColIndex > -1)
      {
		
		arrow1.x = hubitem->pos.x -0x200;
		arrow1.y = hubitem->pos.y -0x100;
		
        DECOMP_UI_Map_GetIconPos(hubPtrs, &arrow1);
        if ((arrowColIndex == 0) && (D232.unkModeHubItems == 0))
        {
          DECOMP_AH_Map_HubArrowOutter(
              hubPtrs, typeCount, &arrow1,
              (0x1000 - hubitem->angle), 1);
			  
          typeCount++;
        }
		
        // if even frame
		if ((gGT->timer & FPS_DOUBLE(2)) == 0)
        {
          arrowColIndex = (int)boolKey * 6;
        }
        else
        {
          arrowColIndex = ((int)boolKey * 2 + 1) * 3;
        }

        DECOMP_AH_Map_HubArrow(
			&arrow1, 
			&D232.hubArrow_pos[0], (char*)&D232.hubArrow_col1[arrowColIndex],
			0x800, hubitem->angle);
      }
	  
      if (itemMode > -1)
      {
        boss_StarPos.x = hubitem->pos.x;
        boss_StarPos.y = 0;
        boss_StarPos.z = hubitem->pos.y;
        
		// if beat boss race
		if (itemMode == 2)
        {
		  // red
          itemColorID = 3;
        }
        else
        {
		  // locked boss race
		  
			
		  // grey
          itemColorID = 0x17;
		  
		  // open, not beaten
          if (itemMode == 1)
          {
			// blue and white
			// depending on frames
			itemColorID = 5;
            if ((gGT->timer & FPS_DOUBLE(2)) != 0)
				itemColorID = 4;
          }
        }
		
		// open, not beaten
        if (itemMode == 1)
        {
          D232.unkModeHubItems = itemMode;
		  
		  arrow2.x = hubitem->pos.x;
		  arrow2.y = hubitem->pos.y;

          DECOMP_UI_Map_GetIconPos(hubPtrs, &arrow2);

          DECOMP_AH_Map_HubArrowOutter(hubPtrs, typeCount, &arrow2, 0, 2);

          typeCount++;

        }
		
		// draw star icon for boss
        DECOMP_UI_Map_DrawRawIcon(hubPtrs, &boss_StarPos, 0x37, itemColorID, 0, 0x1000);
      }
	  
	  type[0] = typeCount;
    }
  
  return;
}