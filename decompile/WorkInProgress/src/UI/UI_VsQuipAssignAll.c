#include <common.h>

void DECOMP_UI_VsQuipAssignAll(void)

{
  struct GameTracker *gGT;
  struct Driver* driver;
  struct ThreadBucket* bucket;
  struct Thread* driverThread;
  char bVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  u_int uVar5;
  int iVar6;
  int *piVar7;
  int lives, point;
  u_int uVar9;
  char **ppuVar11;
  int iVar12;
  char **eor_start;
  int iVar15;
  int iVar16;
  u_short *puVar17;
  u_int uVar18;
  char **ppuVar20;
  int aiStack80 [8];
  char **eor_end;
  int local_2c;

  local_2c = 0;

  if (1 < gGT->numPlyrCurrGame) {

	// If you're not in Battle Mode
    if ((gGT->gameMode1 & BATTLE_MODE) == 0)
	{
	  // pointer to array of LNG index for end-of-race comment
      eor_start = &data.data850[0];
      eor_end = &data.data850[0x518];
    }

	// if in battle
    else
	{
	  // pointer to array of LNG index for end-of-race comment
      eor_start = &data.data850[0x688];
      eor_end = &data.data850[0x850];
    }

	// loop through all comments, and apply some 
	// kind of patch to each
    if (eor_start < eor_end) {
      ppuVar11 = eor_start + 1;
      ppuVar20 = eor_start;
      do {
        if (*ppuVar20 < *ppuVar11) {
          piVar7 = ppuVar20 + 4;
          do {
            ppuVar20 = ppuVar20 + 8;
            *piVar7 = *piVar7 + 1;
            piVar7 = piVar7 + 2;
          } while (*ppuVar20 < *ppuVar11);
        }
		
		// skip 0x18 bytes
        ppuVar20 = ppuVar20 + 6;
        ppuVar11 = ppuVar11 + 6;
		
      } while (ppuVar20 < eor_end);
    }

	// pointer to first Player thread
    bucket = &gGT->threadBuckets[0];

    iVar2 = 0;
    iVar3 = 0;
    iVar4 = 0;

	// loop through all Player threads
    while (bucket != 0)
	{
	  // get Driver object from thread
      driver = bucket->thread->object;

      driver->EndOfRaceComment_lngIndex = 0;

	  // If you dont have a point limit (battle)
      if ((gGT->gameMode1 & POINT_LIMIT) == 0)
	  {
		// get number of lives in life limit (3,6,9)
        lives = driver->BattleHUD.numLives;
      }

	  // if you have point limit in (battle)
      else
	  {
		// Get number of points on this driver's team
        point = (gGT->battleSetup.pointsPerTeam[driver->BattleHUD.teamID]);
      }

      aiStack80[driver->driverID] = point;
      iVar16 = iVar4;
      if ((point <= iVar4) &&
         (bVar1 = point == iVar4, point = iVar4, driver = iVar3, iVar16 = iVar2, bVar1)) {
        driver = 0;
        iVar16 = iVar4;
      }

	  bucket = bucket->thread->siblingThread;

      iVar2 = iVar16;
      iVar3 = driver;
      iVar4 = point;
    }
	
	// offset 0xA
    puVar17 = eor_start[10];
	
    if (eor_start < eor_end) {
      do {
        uVar18 = 0;
        if (puVar17[-1] == 5) {
          uVar18 = 0x7fffffff;
        }
		
		// short*
		// 0xA + 1*2 = 0xC
        puVar17 = puVar17 + 1;
		
        if ((*puVar17 & 1) != 0)
		{
		  // get number of laps in the race
          laps = gGT->numLaps;

		  // get absolute value
          if (laps < 0) {
            laps = -laps;
          }

          puVar17 = puVar17 * laps;
        }

		// pointer to first Player thread
        driverThread = &gGT->threadBuckets[0];

        iVar4 = 0;

		// loop through all Player threads
        while (driverThread != 0)
		{
		  // get driver object from thread
          driver = driverThread->object

          iVar? = iVar4;
          iVar16 = puVar17;
          uVar9 = uVar18;
		  
		  // short*
		  // 0xA + -1*2 = 0x8
          switch(puVar17[-1]) {
          case 0:
		  
		    // UI_VsQuipReaddriverThread
            iVar6 = UI_VsQuipReaddriverThread(driver,
								(puVar17 + 3), // 0xA + 3*2 = 0x10 (driverThreadOffset)
								(puVar17 + 5)  // 0xA + 5*2 = 0x14
								);
            lives = iVar15;
            iVar16 = iVar6;
            if (iVar6 <= bucket) {
LAB_80054f44:
              lives = iVar4;
              iVar16 = bucket;
              if (iVar6 == bucket) {
                lives = 0;
              }
            }
            break;
          case 1:
			// UI_VsQuipReaddriverThread
            iVar6 = UI_VsQuipReaddriverThread(driver,
								(puVar17 + 3), // 0xA + 3*2 = 0x10 (driverThreadOffset)
								(puVar17 + 5)  // 0xA + 5*2 = 0x14
								);
								
            if ((-1 < iVar6) && (lives = iVar15, iVar16 = iVar6, bucket <= iVar6))
            goto LAB_80054f44;
            break;
          case 3:

            iVar6 = iVar15;

			for (iVar12 = 0; iVar12 < 8; iVar12++)
			  {
              uVar9 = (iVar6 + 0x560);
              if (bucket < (uVar9 - uVar18)) {
                local_2c = iVar12;
                iVar4 = iVar15;
                uVar18 = uVar9;
              }
              else {
                if ((-bucket < (uVar9 - uVar18)) && (iVar4 = 0, uVar18 < uVar9)) {
                  uVar18 = uVar9;
                }
              }

			  // increment loop counter
              iVar12 = iVar12 + 1;

              iVar6 = iVar15 + iVar12;
              lives = iVar4;
              uVar9 = uVar18;
            } while (iVar12 < 8);
            break;
          case 4:
			// UI_VsQuipReaddriverThread
            uVar5 = UI_VsQuipReaddriverThread(driver,
								(puVar17 + 3), // 0xA + 3*2 = 0x10 (driverThreadOffset)
								(puVar17 + 5)  // 0xA + 5*2 = 0x14
								);
            lives = iVar15;
            uVar9 = uVar5;
            if (((uVar5 - uVar18) <= bucket) &&
               (bVar1 = uVar18 < uVar5, lives = iVar4, uVar9 = uVar18,
               -bucket < (uVar5 - uVar18))) {
LAB_80054fd0:
              lives = 0;
              uVar9 = uVar18;
              if (bVar1) {
                uVar9 = uVar5;
              }
            }
            break;
          case 5:
			// UI_VsQuipReaddriverThread
            uVar5 = UI_VsQuipReaddriverThread(driver,
								(puVar17 + 3), // 0xA + 3*2 = 0x10 (driverThreadOffset)
								(puVar17 + 5)  // 0xA + 5*2 = 0x14
								);
								
            if (((-1 < uVar5) &&
                (lives = iVar15, uVar9 = uVar5, (uVar18 - uVar5) <= bucket)) &&
               (bVar1 = uVar5 < uVar18, lives = iVar4, uVar9 = uVar18,
               -bucket < (uVar18 - uVar5))) goto LAB_80054fd0;
            break;
          case 6:
			// UI_VsQuipReaddriverThread
            uVar18 = UI_VsQuipReaddriverThread(driver,
								(puVar17 + 3), // 0xA + 3*2 = 0x10 (driverThreadOffset)
								(puVar17 + 5)  // 0xA + 5*2 = 0x14
								);
								
            if (uVar18 == (iVar15 + 0x559)) {
              lives = iVar15;
            }
            break;
          case 7:
            if (bucket == 0) {
              if (iVar15 == iVar3) {
                lives = iVar3;
              }
            }
            else {
              if (((bucket == 1) && (iVar2 != 0)) && (aiStack80[(iVar15 + 0x4a)] == iVar2))
              {
                lives = iVar15;
              }
            }
            break;
          case 8:
			// UI_VsQuipReaddriverThread
            iVar4 = UI_VsQuipReaddriverThread(driver,
								(puVar17 + 3), // 0xA + 3*2 = 0x10 (driverThreadOffset)
								(puVar17 + 5)  // 0xA + 5*2 = 0x14
								);
            if (iVar4 == bucket) {
              lives = iVar15;
            }
            break;
          case 9:
            if ((iVar15 + 0x56c) == 0)
			{
			  // UI_VsQuipAssign
              UI_VsQuipAssign(iVar15,eor_start,iVar3,0);
            }
          }
          if ((lives != 0) && ((*puVar17 & 0xc) != 0))
		  {
			// UI_VsQuipAssign
            UI_VsQuipAssign(lives,eor_start,iVar3,local_2c);
          }

		  // thread = thread -> sibling
          driverThread = driverThread->siblingThread;

          iVar4 = lives;
          bucket = iVar16;
          uVar18 = uVar9;
        }

		// UI_VsQuipAssign
        UI_VsQuipAssign(iVar4,eor_start,iVar3,local_2c);

		// jump 0x18 bytes
        eor_start = eor_start + 6;
        puVar17 = puVar17 + 0xc;
		
      } while (eor_start < eor_end);
    }
  }
  return;
}
