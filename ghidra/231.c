
// 231: 130/130

// RB_MakeInstanceReflective
// param_1 is BSP result
// param_2 is instance
void FUN_800abab0(int param_1,int param_2)

{
  ushort uVar1;
  undefined *puVar2;
  
  puVar2 = PTR_DAT_8008d2ac;
  if ((*(short *)(param_1 + 0x3e) == 0) || (*(short *)(param_1 + 0x42) != 0)) {
    *(undefined4 *)(param_2 + 0x70) = 0x4000;
  }
  else {
    *(uint *)(param_2 + 0x70) =
         (uint)(*(ushort *)(param_1 + 0x70) >> 6) & 0xff |
         ((uint)*(ushort *)(param_1 + 0x72) & 0x3fc0) << 2 |
         ((uint)(*(ushort *)(param_1 + 0x74) >> 6) & 0xff) << 0x10;
		 
	// quit if more than one player
    if (1 < (byte)puVar2[0x1ca8]) {
      return;
    }
	
	// if there is one player
	
	// quadblock -> flags
    uVar1 = *(ushort *)(*(int *)(param_1 + 0x80) + 0x12);
	
    if ((uVar1 & 0x2000) == 0) 
	{
	  // visible?
      if ((uVar1 & 1) != 0) 
	  {
		// make instance reflective
        *(uint *)(param_2 + 0x28) = *(uint *)(param_2 + 0x28) | 0x4000;
		
		// split line
        *(undefined2 *)(param_2 + 0x56) = *(undefined2 *)(*(int *)(puVar2 + 0x160) + 0x186);
		
        return;
      }
	  
	  // reflective (ice)
      if ((uVar1 & 4) != 0) 
	  {
		// make instance reflective
        *(uint *)(param_2 + 0x28) = *(uint *)(param_2 + 0x28) | 0x4000;
        
		// split line
		*(undefined2 *)(param_2 + 0x56) = *(undefined2 *)(*(int *)(puVar2 + 0x160) + 0x184);
		
        return;
      }
    }
  }
  
  // instance is not reflective
  *(uint *)(param_2 + 0x28) = *(uint *)(param_2 + 0x28) & 0xffffbfff;
  
  return;
}

// RB_Player_KillPlayer
void FUN_800abbb4(int param_1,int param_2)

{
  undefined *puVar1;
  uint uVar2;
  int iVar3;
  short *psVar4;
  undefined *puVar5;
  short sVar6;
  int iVar7;
  
  // boolIsTeamAlive
  short local_18 [4];
  
  uVar2 = *(uint *)PTR_DAT_8008d2ac;
  
  // quit if not in battle mode, or if 
  // either driver is nullptr
  
  if ((uVar2 & 0x20) == 0) return;
  if (param_1 == 0) return;
  if (param_2 == 0) return;
  
  // If you dont have a Point Limit (battle)
  if ((uVar2 & 0x4000) == 0) {
	  
	// If you dont have a Life Limit (battle)
    if ((uVar2 & 0x8000) == 0) {
		
	  // Quit the function
      return;
    }
	
	// If you are here, this is LIFE limit
	
	// subtract a life from player
    iVar3 = *(int *)(param_2 + 0x4e4) + -1;
	
    iVar7 = 0;
    
	// if player is alive
	if (0 < iVar3) 
	{
	  // set new number of lives
      *(int *)(param_2 + 0x4e4) = iVar3;
	  
	  // leave function
      return;
    }
	
	// if you get here, then player is out of lives
	
	// array of boolIsTeamAlive
    memset(local_18,0,8);
	
    sVar6 = 0;
	
	// VehStuckProc_RIP_Init
    *(undefined4 *)(param_2 + 0x54) = 0x80067930;
    
	puVar1 = PTR_DAT_8008d2ac;
	
	// set lives to zero
    *(undefined4 *)(param_2 + 0x4e4) = 0;
	
	// the race (or battle) is now over for this driver
    *(uint *)(param_2 + 0x2c8) = *(uint *)(param_2 + 0x2c8) | 0x2000000;
	
    iVar3 = 0;
    puVar5 = puVar1;
	
	// if there are players
    if (puVar1[0x1ca8] != '\0') 
	{
	  // loop through all players
      do 
	  {
		// If the race is not over for this driver
        if ((*(uint *)(*(int *)(puVar5 + 0x24ec) + 0x2c8) & 0x2000000) == 0) 
		{
		  // array[driver->teamID] = 1
          local_18[*(int *)(*(int *)(puVar5 + 0x24ec) + 0x4e8)] = 1;
        }
		
		// if race is over for this player
        else 
		{
		  // keep count of drivers dead
          iVar7 = iVar7 + 1;
        }
        iVar3 = iVar3 + 1;
        puVar5 = puVar5 + 4;
      } while (iVar3 < (int)(uint)(byte)puVar1[0x1ca8]);
    }
	
	// dead driver -> battleHUD.teamID
    uVar2 = *(uint *)(param_2 + 0x4e8);
	
    if (
			// if driver team exists
			((*(uint *)(PTR_DAT_8008d2ac + 0x1dd8) & 1 << (uVar2 & 0x1f)) != 0) &&
			
			// if no remaining players alive on team
			(local_18[uVar2] == 0)
		) 
	{
      if ((int)((uint)(byte)PTR_DAT_8008d2ac[0x1ca8] - iVar7) < 3) 
	  {
		// increment gGT Standing Points by 1,
		// record how many times players finished in each rank
        *(int *)(PTR_DAT_8008d2ac + (uVar2 * 3 + ((uint)(byte)PTR_DAT_8008d2ac[0x1ca8] - iVar7)) * 4 + 0x1e80) =
        *(int *)(PTR_DAT_8008d2ac + (uVar2 * 3 + ((uint)(byte)PTR_DAT_8008d2ac[0x1ca8] - iVar7)) * 4 + 0x1e80) + 1;
      }
	  
	  // save the rank that each team finished
      *(uint *)(PTR_DAT_8008d2ac + *(int *)(param_2 + 0x4e8) * 4 + 0x1da8) =
           (uint)(byte)PTR_DAT_8008d2ac[0x1ca8] - iVar7;
    }
	
	// count all living teams
    puVar1 = PTR_DAT_8008d2ac;
    uVar2 = 0;
    psVar4 = local_18;
	
	// loop through all teams
    do 
	{
      if (
			// if team exists
			((*(uint *)(PTR_DAT_8008d2ac + 0x1dd8) & 1 << (uVar2 & 0x1f)) != 0) && 
			
			// if someone is alive on this team
			(*psVar4 != 0)
		 ) 
	  {
		// count living teams
        sVar6 = sVar6 + 1;
      }
      uVar2 = uVar2 + 1;
      psVar4 = psVar4 + 1;
    } while ((int)uVar2 < 4);
	
	// if there is not only one team alive
    if (sVar6 != 1) 
	{
	  // no winner found yet
      return;
    }
	
	// at this point, a winner is found,
	// end the game for all drivers
	
    iVar3 = 0;
    puVar5 = PTR_DAT_8008d2ac;
    
	// if there are players
	if (PTR_DAT_8008d2ac[0x1ca8] != '\0') {
      
	  // loop through all players
	  do 
	  {  
		// The race (or battle) is now over for this driver
		*(uint *)(*(int *)(puVar5 + 0x24ec) + 0x2c8) =
        *(uint *)(*(int *)(puVar5 + 0x24ec) + 0x2c8) | 0x2000000;
			
        iVar3 = iVar3 + 1;
        puVar5 = puVar5 + 4;
      } while (iVar3 < (int)(uint)(byte)puVar1[0x1ca8]);
    }
  }
  
  // if Point Limit
  else {
    
	// if driver hit themself
	if (*(int *)(param_2 + 0x4e8) == *(int *)(param_1 + 0x4e8)) 
	{
	  // subtract a point
      iVar3 = *(int *)(PTR_DAT_8008d2ac + *(int *)(param_2 + 0x4e8) * 4 + 0x1d90) + -1;
      if (iVar3 < -9) 
	  {
		// can't go lower than -9
        return;
      }
	  
	  // save new score
      *(int *)(PTR_DAT_8008d2ac + *(int *)(param_2 + 0x4e8) * 4 + 0x1d90) = iVar3;
      return;
    }
	
	// add point to player who got a hit
    iVar3 = *(int *)(PTR_DAT_8008d2ac + *(int *)(param_1 + 0x4e8) * 4 + 0x1d90) + 1;
	
	// if scores is less than 100
    if (iVar3 < 100) 
	{
	  // increment score
      *(int *)(PTR_DAT_8008d2ac + *(int *)(param_1 + 0x4e8) * 4 + 0x1d90) = iVar3;
    }
	
    puVar1 = PTR_DAT_8008d2ac;
	
	// if amount of points earned by this driver is not equal to the winning amount
    if (*(int *)(PTR_DAT_8008d2ac + *(int *)(param_1 + 0x4e8) * 4 + 0x1d90) !=
        *(int *)(PTR_DAT_8008d2ac + 0x1d8c)) 
	{
	  // quit function
      return;
    }
	
	// if this is a time-limit game
    if ((*(uint *)PTR_DAT_8008d2ac & 0x10000) != 0) 
	{
	  // quit
      return;
    }
	
	// if this is not a time-limit game,
	// and the last kill has been made,
	// then end the game
	
    iVar3 = 0;
    puVar5 = PTR_DAT_8008d2ac;
	
	// if there are drivers
    if (PTR_DAT_8008d2ac[0x1ca8] != '\0') {
      
	  // loop through all drivers
	  do 
	  {
		// the race (or battle) is now over for this driver
        *(uint *)(*(int *)(puVar5 + 0x24ec) + 0x2c8) =
        *(uint *)(*(int *)(puVar5 + 0x24ec) + 0x2c8) | 0x2000000;
		
        iVar3 = iVar3 + 1;
        puVar5 = puVar5 + 4;
      } while (iVar3 < (int)(uint)(byte)puVar1[0x1ca8]);
    }
  }
  
  // MainGameEnd_Initialize
  FUN_8003a3fc();
  
  return;
}

// RB_Player_ModifyWumpa
void FUN_800abefc(int param_1,int param_2)

{
  // param_1 is address of player/AI structure
  // param_2 is number of wumpa fruit to add
	
  // get current number of wumpa fruit
  char cVar1;
  cVar1 = *(char *)(param_1 + 0x30);
  
  if (
		// if unlimited wumpa cheat is disabled
		((*(uint *)(PTR_DAT_8008d2ac + 8) & 0x200) == 0) &&
		
		(
			(
				// if wumpa fruit are being added, not subtracted
				-1 < param_2 || 
				
				// if driver is not using mask weapon
				((*(uint *)(param_1 + 0x2c8) & 0x800000) == 0)
			)
		)
	 ) 
  {
    
	if (
			// if wumpa is increasing
			(0 < param_2) && 
			
			// if this driver is not an AI
			((*(uint *)(param_1 + 0x2c8) & 0x100000) == 0)
		) 
	{
	  // increment how much fruit was collected by this driver
      *(char *)(param_1 + 0x569) = *(char *)(param_1 + 0x569) + (char)param_2;
    }
	
	// get new total amount of wumpa fruit (current + added amount)
    param_2 = (uint)*(byte *)(param_1 + 0x30) + param_2;
	
	// store the new value into current number of wumpa fruit
    *(undefined *)(param_1 + 0x30) = (char)param_2;
	
	// If total wumpa is negative
    if (param_2 * 0x1000000 < 0) 
	{
	  // reset wumpa fruit to zero
      *(undefined *)(param_1 + 0x30) = 0;
    }
	
	// if wumpa fruit count is more than 10
    if ('\n' < *(char *)(param_1 + 0x30)) 
	{
	  // set amount of wumpa fruit to 10
      *(undefined *)(param_1 + 0x30) = 10;
    }
	
	// if amount of wumpa was less than 10, and then changed to be 10
    if ((cVar1 < '\n') && (*(char *)(param_1 + 0x30) == '\n')) 
	{
	  // Play "juiced up" sound
      FUN_80028468(0x41,1);
	  
	  // 10 frames
      *(undefined4 *)(param_1 + 0x4e0) = 10;
    }
  }
  return;
}

// RB_MinePool_Init
void FUN_800abfec(void)

{
  int iVar1;
  undefined *puVar2;
  int iVar3;
  
  // LIST_Clear taken list
  FUN_80031734(&DAT_800b2e9c);
  
  // LIST_Clear free list
  FUN_80031734(&DAT_800b2ea8);
  
  // If you are not in Crystal Challenge
  if ((*(uint *)PTR_DAT_8008d2ac & 0x8000000) == 0) 
  {
	// if this is dragon mines boss race
    if (
			// If you are in Boss Race
			((int)*(uint *)PTR_DAT_8008d2ac < 0) && 
			
			// If level is Dragon Mines
			(*(int *)(PTR_DAT_8008d2ac + 0x1a10) == 1)
		) 
	{
	  // three mines max
      iVar1 = 3;
    }
	
	// if this is not dragon mines boss race
    else 
	{
	  // ten mines max,
	  // applies to Arcade, VS, Battle, etc
      iVar1 = 10;
      
	  if (
			// If you are in Boss Race
			(*(int *)PTR_DAT_8008d2ac < 0) && 
			
			(
				// boss race for Papu and Oxide,
				// ten mines max
				iVar1 = 10, 
				
				// If the level is Roo's Tubes
				*(int *)(PTR_DAT_8008d2ac + 0x1a10) == 6
			)
		  )
      {
		// Ripper Roo can only place 7 TNTs
		// before the last TNTs explode
        iVar1 = 7;
      }
    }
  }
  
  // if this is crystal challenge
  else 
  {
	// 40 items max
    iVar1 = 0x28;
  }
  
  iVar3 = 0;
  if (iVar1 != 0) 
  {
    puVar2 = &DAT_800b2eb4;
    do 
	{
	  // LIST_AddFront free list
      FUN_80031744(&DAT_800b2ea8,puVar2);
	  
      iVar3 = iVar3 + 1;
      puVar2 = puVar2 + 0xc;
    } while (iVar3 < iVar1);
  }
  return;
}

// RB_MinePool_Remove
// param_1 = struct MineWeapon
void FUN_800ac0e4(int param_1)
{
  if (*(int *)(param_1 + 0x18) != 0) 
  {
	// LIST_RemoveMember taken list
    FUN_800317e4(&DAT_800b2e9c,*(undefined4 *)(param_1 + 0x18));
	
	// LIST_AddFront free list
    FUN_80031744(&DAT_800b2ea8,*(undefined4 *)(param_1 + 0x18));
    
	// MineWeapon is now destroyed
	*(undefined2 *)(param_1 + 0x14) = 1;
	
	// MineWeapon has no WeaponSlot231 pointer anymore
    *(undefined4 *)(param_1 + 0x18) = 0;
  }
  return;
}

// RB_MinePool_Add
// param_1 = struct MineWeapon
void FUN_800ac13c(int param_1)

{
  int iVar1;
  
  // if no more items on free list
  // (800b2ea8 + 8 = 800b2eb0)
  if (DAT_800b2eb0 == 0) 
  {
	// remove oldest mine
	
	// RB_MinePool_Remove
	// (800b2e9c + 4 = 800b2ea0) (taken->last)
	// (*(int*)800b2ea0 + 8) (taken->last->mineWeapon)
    FUN_800ac0e4(*(undefined4 *)(DAT_800b2ea0 + 8));
  }
  
  // LIST_RemoveBack free list
  iVar1 = FUN_800318ec(&DAT_800b2ea8);
  
  // weaponSlot231->MineWeapon = param_1 (mineWeapon)
  *(int *)(iVar1 + 8) = param_1;
  
  // mineWeapon->weaponSlot231 = weaponSlot231
  *(int *)(param_1 + 0x18) = iVar1;
  
  // LIST_AddFront taken list
  FUN_80031744(&DAT_800b2e9c,iVar1);
  
  return;
}

// hazard can be a Mine instance,
// or level instance (spider, armadillo, etc)

// RB_Hazard_HurtDriver
// return 1 if driver was hurt,
// return 0 if driver was not hurt (mask grab, mask weapon, etc)
int FUN_800ac1b0(int param_1,undefined4 param_2, param_3, param_4)

{
  // if this driver is not an AI
  if ((*(uint *)(param_1 + 0x2c8) & 0x100000) == 0) 
  {
	// VehPickState_NewState
    return FUN_80064568(param_1,param_2,param_3,param_4);
  }
  
  // If driver is an AI
  else 
  {
    if (
			// if Level ID == 13, if this is Oxide Station
			(*(int *)(PTR_DAT_8008d2ac + 0x1a10) == 0xd) && 
			
			// If you are in "Boss Mode" (0x80000000)
			(*(int *)PTR_DAT_8008d2ac < 0)) 
	{
	  // override effect to spinning out,
	  // this make Oxide spin out
      param_2 = 1;
    }
	
	// BOTS_ChangeState
    return FUN_80016b00(param_1,param_2);
  }
}

// RB_Hazard_CollideWithDrivers
// param_1 weapon instance
// param_2 boolCanSkipParent
// param_3 collision radius
// param_4 mineParent_driverInst
int FUN_800ac220(int param_1,short param_2,uint param_3,int param_4)

{
  ushort uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  undefined *puVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  
  iVar7 = 0;
  puVar6 = PTR_DAT_8008d2ac;
  do {
	  
	// Get pointer to player (9900C)
    iVar2 = *(int *)(puVar6 + 0x24ec);
	
    if (
			// If pointer is not nullptr
			(iVar2 != 0) && 
			
			// If you're not being mask grabbed
			(*(char *)(iVar2 + 0x376) != '\x05')
		) 
	{
	  // get instance from driver
      iVar5 = *(int *)(iVar2 + 0x1c);
	  
	  // get X distance and Z distance between player and object
      iVar3 = *(int *)(iVar5 + 0x44) - *(int *)(param_1 + 0x44);
      iVar4 = *(int *)(iVar5 + 0x4c) - *(int *)(param_1 + 0x4c);
	  
	  // instance -> model -> modelID
      uVar1 = *(ushort *)(*(int *)(param_1 + 0x18) + 0x10);
	  
	  // get Y distance between player and object
      iVar2 = *(int *)(iVar5 + 0x48) - *(int *)(param_1 + 0x48);
	  
      if (
			// red or green potion
			((uint)uVar1 - 0x46 < 2) || 
			
			(
				(
					iVar8 = iVar3 * iVar3, 
					
					// nitro
					uVar1 == 6 || 
					
					// tnt
					(uVar1 == 0x27)
				)
			)
		) 
	  {
        iVar9 = iVar2 * iVar2;
        iVar8 = iVar3 * iVar3 + iVar4 * iVar4;
      }
      else {
        iVar9 = iVar4 * iVar4;
      }
	  
	  // if distance is less than param_3
      if (((uint)(iVar8 + iVar9) < param_3) &&
	  
		 // if driver did not hit their own mine
         (((param_2 == 0 || (iVar5 != param_4)) && (iVar2 * iVar2 < (int)(param_3 << 2))))) 
	  {
		// driver who hit the mine
        return iVar5;
      }
    }
    iVar7 = iVar7 + 1;
    puVar6 = puVar6 + 4;
    if (7 < iVar7) {
      return 0;
    }
  } while( true );
}

// RB_Hazard_CollideWithBucket
// param_1 - mine Inst,
// param_2 - mine Thread (unused)
// param_3 - bucket
// param_4 - boolCanSkipParent
// param_5 - radius
// param_6 - mineParent_driverInst
int FUN_800ac350
              (int param_1,undefined4 param_2,int param_3,short param_4,uint param_5,int param_6)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  // loop through all members in linked list
  if (param_3 != 0) {
    do 
	{
	  // get instance from thread
      iVar4 = *(int *)(param_3 + 0x34);
	  
	  // get distance (x, y, z) between two instances
      iVar1 = *(int *)(iVar4 + 0x44) - *(int *)(param_1 + 0x44);
      iVar2 = *(int *)(iVar4 + 0x4c) - *(int *)(param_1 + 0x4c);
      iVar3 = *(int *)(iVar4 + 0x48) - *(int *)(param_1 + 0x48);
	  
      if (
			// if distance is less than collision radius
			((uint)(iVar1 * iVar1 + iVar2 * iVar2 + iVar3 * iVar3) < param_5) &&
			
			((param_4 == 0 || (iVar4 != param_6)))
		 ) 
	  {
		// return the instance that collided
        return iVar4;
      }
	  
	  // check the next member in the linked list
      param_3 = *(int *)(param_3 + 0x10);
	  
	  
	// loop through all member in linked list
    } while (param_3 != 0);
  }
  return 0;
}

// RB_Hazard_ThCollide_Generic_Alt
void FUN_800ac3f8(undefined4 *param_1)
{
  // RB_Hazard_ThCollide_Generic
  // only really uses *param_1 for thread
  FUN_800ac4b8(*param_1,param_1[1],param_1[2],param_1[3]);
  return;
}

// RB_Hazard_ThCollide_Missile
// removes 2D target from player
undefined4 FUN_800ac42c(int param_1)
{
  int iVar1;
  int *piVar2;
  
  // thread -> instance -> thread -> object
  piVar2 = *(int **)(*(int *)(*(int *)(param_1 + 0x34) + 0x6c) + 0x30);
  
  // thread -> instance -> model -> modelID == missile
  if (*(short *)(*(int *)(*(int *)(param_1 + 0x34) + 0x18) + 0x10) == 0x29) 
  {
	// The first 4 bytes of missile object is 
	// the pointer to the player it was chasing
	  
	// iVar1 = player
    iVar1 = *piVar2;
	
	// if the player is valid
    if (iVar1 != 0) 
	{
	  // remove 2D square-target being drawn on the player's screen 
      *(uint *)(iVar1 + 0x2c8) = *(uint *)(iVar1 + 0x2c8) & 0xfbffffff;
    }
	
	// play audio of explosion
    FUN_8002f0dc(0x4c);
	
	// stop audio of moving
    FUN_8002e724(piVar2 + 9);
	
	// This thread is now dead
    *(uint *)(param_1 + 0x1c) = *(uint *)(param_1 + 0x1c) | 0x800;
  }
  return 1;
}

// RB_Hazard_ThCollide_Generic
// param_1 - thread
// param_2 - thread (again? unused)
// param_3 - funcThCollide (unused)
// param_4 - unknown, unused
undefined4 FUN_800ac4b8(int param_1)
{
  ushort uVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  int *piVar5;
  
  // thread->instance
  iVar4 = *(int *)(param_1 + 0x34);
  
  // instance->thread->object
  piVar5 = *(int **)(*(int *)(iVar4 + 0x6c) + 0x30);
  
  if (
		(
			// if mineWeapon->crateInst
			(piVar5[2] != 0) && 
			
			// instance -> thread
			(iVar2 = *(int *)(piVar5[2] + 0x6c), iVar2 != 0)
		) &&
     
		// thread -> object
		(iVar2 = *(int *)(iVar2 + 0x30), iVar2 != 0)
	  ) 
  {
	// unpause cooldown (boolPauseCooldown)
    *(undefined2 *)(iVar2 + 4) = 0;
  }
  
  // get model ID from inside model pointer
  uVar1 = *(ushort *)(*(int *)(iVar4 + 0x18) + 0x10);
  
  // If this is red beaker or green beaker
  if ((uint)uVar1 - 0x46 < 2) 
  {
	// play sound of glass shatter
    FUN_8002f0dc(0x3f,iVar4);
	
	// RB_MinePool_Remove
    FUN_800ac0e4(piVar5);
  }
  
  else 
  {
	// if this is a Nitro
    if (uVar1 == 6) 
	{
	  // sound of glass shatter
      uVar3 = 0x3f;
    }
	
    else 
	{
	  // if this is not a TNT
      if (uVar1 != 0x27) {
        return 1;
      }
	  
	  // at this point, it must be TNT
	  
	  // if driver hit the TNT
      if (*piVar5 != 0) 
	  {
		// quit, explosion is handled
		// by TNT thread instead
        return 1;
      }
	  
	  // if no driver hit TNT,
	  // handle explosion here
	  
	  // play sound of tnt explosion
      uVar3 = 0x3d;
    }
	
	// play sound
    FUN_8002f0dc(uVar3,iVar4);
    
	// RB_MinePool_Remove
	FUN_800ac0e4(piVar5);
	
	// RB_Explosion_InitGeneric
    FUN_800b1630(iVar4);
	
	// set scale (x, y, z) to zero
    *(undefined2 *)(iVar4 + 0x20) = 0;
    *(undefined2 *)(iVar4 + 0x1e) = 0;
    *(undefined2 *)(iVar4 + 0x1c) = 0;
	
	// make invisible
    *(uint *)(iVar4 + 0x28) = *(uint *)(iVar4 + 0x28) | 0x80;
  }
  
  // this thread is now dead
  *(uint *)(param_1 + 0x1c) = *(uint *)(param_1 + 0x1c) | 0x800;
  return 1;
}

// RB_Potion_OnShatter_TeethCallback
// param_2 Lev Hitbox (bsp)
void FUN_800ac5e8(undefined4 param_1,int param_2)

{
  int iVar1;
  
  // bsp->hitbox.instDef
  iVar1 = *(int *)(param_2 + 0x1c);
  
  if (
		(
			// if InstDef exists
			(iVar1 != 0) && 
			
			(*(int *)(iVar1 + 0x2c) != 0)
		) && 
		
		// modelID == STATIC_TEETH
		(*(short *)(iVar1 + 0x3c) == 0x70)
	) 
  {
	// RB_Teeth_OpenDoor
    FUN_800ba220(*(int *)(iVar1 + 0x2c));
  }
  return;
}

// RB_Potion_OnShatter_TeethSearch
void FUN_800ac638(int param_1)
{
  // This function is not a waste,
  // if potion explodes while sitting next to teeth,
  // either cause another driver hit it, 
  // or cause too many potions in MinePool,
  // then this is the only way for teeth to open
	
  // position
  DAT_1f800108 = *(undefined2 *)(param_1 + 0x44);
  DAT_1f80010a = *(undefined2 *)(param_1 + 0x48);
  DAT_1f80010c = *(undefined2 *)(param_1 + 0x4c);
  
  // hitRadius and hitRadiusSquared
  DAT_1f80010e = 0x140;
  DAT_1f800110 = 0x19000;
  
  // thread
  DAT_1f800120 = *(undefined4 *)(param_1 + 0x6c);
  
  // inst->modelPtr->modelID
  DAT_1f800114 = *(undefined2 *)(*(int *)(param_1 + 0x18) + 0x10);
  
  // RB_Potion_OnShatter_TeethCallback
  DAT_1f800130 = FUN_800ac5e8;
  
  // PROC_StartSearch_Self
  FUN_80042544(&DAT_1f800108);
  
  return;
}

// RB_Potion_ThTick_InAir
void FUN_800ac6b4(int param_1)
{
  bool bVar1;
  short sVar2;
  undefined *puVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  undefined2 local_28;
  short local_26;
  undefined2 local_24;
  undefined2 local_20;
  short local_1e;
  undefined2 local_1c;
  
  puVar3 = PTR_DAT_8008d2ac;
  
  // get instance from thread
  iVar6 = *(int *)(param_1 + 0x34);
  
  // instance -> thread -> object
  iVar7 = *(int *)(*(int *)(iVar6 + 0x6c) + 0x30);
  
  // X position
  *(int *)(iVar6 + 0x44) =
       *(int *)(iVar6 + 0x44) +
       ((int)*(short *)(iVar7 + 0xc) * *(int *)(PTR_DAT_8008d2ac + 0x1d04) >> 5);
  
  // Y position
  *(int *)(iVar6 + 0x48) =
       *(int *)(iVar6 + 0x48) + ((int)*(short *)(iVar7 + 0xe) * *(int *)(puVar3 + 0x1d04) >> 5);
  
  // Z position
  *(int *)(iVar6 + 0x4c) =
       *(int *)(iVar6 + 0x4c) + ((int)*(short *)(iVar7 + 0x10) * *(int *)(puVar3 + 0x1d04) >> 5);
  
  // gravity, decrease velocity over time
  iVar4 = (uint)*(ushort *)(iVar7 + 0xe) - ((*(int *)(puVar3 + 0x1d04) << 2) >> 5);
  *(undefined2 *)(iVar7 + 0xe) = (short)iVar4;
  
  // terminal velocity
  if (iVar4 * 0x10000 >> 0x10 < -0x60) {
    *(undefined2 *)(iVar7 + 0xe) = 0xffa0;
  }
  
  // reduce cooldown time, set from GenericMine_ThTick
  iVar4 = (uint)*(ushort *)(iVar7 + 0x2a) - (uint)*(ushort *)(PTR_DAT_8008d2ac + 0x1d04);
  *(undefined2 *)(iVar7 + 0x2a) = (short)iVar4;
  
  // if below zero, then set to zero
  if (iVar4 * 0x10000 < 0) {
    *(undefined2 *)(iVar7 + 0x2a) = 0;
  }
  
  // posBottom
  local_28 = *(undefined2 *)(iVar6 + 0x44);
  local_26 = *(short *)(iVar6 + 0x48) + -0x40;
  local_24 = *(undefined2 *)(iVar6 + 0x4c);
  
  // posTop
  local_20 = *(undefined2 *)(iVar6 + 0x44);
  local_1e = *(short *)(iVar6 + 0x48) + 0x100;
  local_1c = *(undefined2 *)(iVar6 + 0x4c);
  
  DAT_1f80012c = 0x1040;
  DAT_1f800130 = 0;
  DAT_1f80012a = 0x41;
  
  // numPlyrCurrGame is less than 3
  if ((byte)PTR_DAT_8008d2ac[0x1ca8] < 3) {
    DAT_1f80012a = 0x43;
  }
  
  DAT_1f800134 = **(undefined4 **)(PTR_DAT_8008d2ac + 0x160);
  
  // COLL_SearchTree_FindQuadblock_Touching
  FUN_8001eb0c(&local_28,&local_20,&DAT_1f800108,0);
  
  // RB_MakeInstanceReflective
  FUN_800abab0(&DAT_1f800108,iVar6);
  
  if ((DAT_1f8002ac & 4) != 0) 
  {
	// RB_GenericMine_ThDestroy
    FUN_800ad250(param_1,iVar6,iVar7);
  }
  
  // did not hit bsp hitbox
  if (DAT_1f80014a == 0) {
    if (DAT_1f800146 != 0) 
	{
	  // VehPhysForce_RotAxisAngle
      FUN_8005f89c(iVar6 + 0x30,&DAT_1f800178,0);
      
	  // hitbox minY
	  iVar4 = (int)DAT_1f800126;
      
	  // instance posY
	  iVar5 = *(int *)(iVar6 + 0x48);
      
	  if (iVar4 + 0x30 < iVar5) {
        return;
      }
	  
	  // if no cooldown
      if (*(short *)(iVar7 + 0x2a) == 0) 
	  {
        *(int *)(iVar6 + 0x48) = iVar4;
        sVar2 = DAT_1f800126;
        
		// reset cooldown (3.84s)
		// if potion hits ground, and hit within 3.84s,
		// then it counts in EndOfRace comments as hit by moving potion,
		// but will count as motionless potion if hit after 3.84s of
		// hitting the ground (after initially being Potion_InAir)
		*(undefined2 *)(iVar7 + 0x2a) = 0xf00;
		
		// clear velocity
        *(undefined2 *)(iVar7 + 0xc) = 0;
        *(undefined2 *)(iVar7 + 0xe) = 0;
        *(undefined2 *)(iVar7 + 0x10) = 0;
		
		// max height
        *(short *)(iVar7 + 0x12) = sVar2;
        
		// remove flag "| 2"
		*(ushort *)(iVar7 + 0x28) = *(ushort *)(iVar7 + 0x28) & 0xfffd;
		
		// ThTick_SetAndExec(self, RB_GenericMine_ThTick)
        FUN_800716ec(param_1,FUN_800acb60);
		
        return;
      }
	  
      if (iVar5 <= iVar4) {
        *(int *)(iVar6 + 0x48) = iVar4;
      }
      if ((*(int *)(iVar6 + 0x48) - iVar5) + 0x28 <= (int)*(short *)(iVar7 + 0xe)) {
        return;
      }
      *(short *)(iVar7 + 0xe) = (*(short *)(iVar6 + 0x48) - (short)iVar5) + 0x28;
      return;
    }
	
	// if did not touch quadblock in range [-0x40, 0x100],
	// check again with range [-0x900, 0x100]
	
	// posBottom
    local_28 = *(undefined2 *)(iVar6 + 0x44);
    local_26 = *(short *)(iVar6 + 0x48) + -0x900;
    local_24 = *(undefined2 *)(iVar6 + 0x4c);
    
	// COLL_SearchTree_FindQuadblock_Touching
	FUN_8001eb0c(&local_28,&local_20,&DAT_1f800108,0);
	
	// if quadblock exists within 0x900 units of Y axis,
	// do not destroy the potion, let it keep flying
    if (DAT_1f800146 != 0) {
      return;
    }
  }
  
  // This is not a waste,
  // Potion_OnShatter_SearchTeeth fails
  // to open Teeth while the potion is airborne
  
  // If hit bsp hitbox
  else {
    bVar1 = true;
    if (((((*DAT_1f800150 & 0x80) != 0) && (iVar4 = *(int *)(DAT_1f800150 + 0x1c), iVar4 != 0)) &&
        (*(short *)(iVar4 + 0x3c) == 0x70)) && (*(int *)(iVar4 + 0x2c) != 0)) 
	{
      
	  // if door is closed
	  if ((DAT_8008d728 & 1) == 0) 
	  {
		// RB_Teeth_OpenDoor
        FUN_800ba220();
      }
      else {
        bVar1 = false;
      }
    }
    if (!bVar1) {
      return;
    }
  }
  
  // hit TEETH door,
  // or no quadblock exists within 0x900 units of Y axis
  
  // RB_GenericMine_ThDestroy
  FUN_800ad250(param_1,iVar6,iVar7);
  return;
}

// RB_GenericMine_LInB
void FUN_800aca50(int param_1)
{
  // This is for Nitro crates
  // in Crystal Challenge, not 
  // for crates dropped by players
	
  undefined *puVar1;
  int iVar2;
  undefined4 *puVar3;
  
  // RB_Default_LInB
  FUN_800b4fe4(param_1);
  
  if (
		// If this Instance's thread does not exist
		(*(int *)(param_1 + 0x6c) == 0) && 
		
		// If you are in Crystal Challenge
		((*(uint *)PTR_DAT_8008d2ac & 0x8000000) != 0)
	 ) 
  {
	// PROC_BirthWithObject
	// 0x2c = size
	// 0 = no relation to param4
	// 0x300 = SmallStackPool
	// 0x4 = "mine" thread bucket
    iVar2 = FUN_8004205c(0x2c0304,FUN_800acb60,s_nitro_800ab9f4,0);
	
	// Give thread to Instance
    *(int *)(param_1 + 0x6c) = iVar2;
	
	// If the thread created successfully
    if (iVar2 != 0) 
	{
	  // Give Instance to thread
      *(int *)(iVar2 + 0x34) = param_1;
	  
      puVar1 = PTR_DAT_8008d2ac;
      
	  // Instance->thread->funcThCollide
	  *(undefined4 *)(*(int *)(param_1 + 0x6c) + 0x28) = 0x800ac4b8;
	  
	  // Instance->thread->playerthread = Player->Instance->thread
      *(undefined4 *)(*(int *)(param_1 + 0x6c) + 0xc) =
           *(undefined4 *)(*(int *)(*(int *)(puVar1 + 0x24ec) + 0x1c) + 0x6c);
	
	  // Instance->thread->modelIndex = Instance->Model->modelIndex
      *(undefined2 *)(*(int *)(param_1 + 0x6c) + 0x44) =
           *(undefined2 *)(*(int *)(param_1 + 0x18) + 0x10);
	  
	  // Get Nitro object attached to Instance's thread
      puVar3 = *(undefined4 **)(*(int *)(param_1 + 0x6c) + 0x30);
	  
	  // Get Instance attached to player
      puVar3[1] = *(undefined4 *)(*(int *)(puVar1 + 0x24ec) + 0x1c);
	  
	  // velocity[x,y,z] = 0
      *(undefined2 *)(puVar3 + 3) = 0;
      *(undefined2 *)((int)puVar3 + 0xe) = 0;
      *(undefined2 *)(puVar3 + 4) = 0;
	  
	  // frameCount_DontHurtParent
      *(undefined2 *)(puVar3 + 9) = 0;
	  
	  // boolDestroyed
      *(undefined2 *)(puVar3 + 5) = 0;
	  
	  // unk
      *(undefined2 *)((int)puVar3 + 0x26) = 0;
	  
	  // no target, no parent
      *puVar3 = 0;
      puVar3[2] = 0;
	  
	  // extraFlags
      *(undefined2 *)(puVar3 + 10) = 0;
      
	  // RB_MinePool_Add
	  FUN_800ac13c(puVar3);
	  
	  // mineWeapon->posY = instance->posY
      *(undefined2 *)((int)puVar3 + 0x12) = *(undefined2 *)(param_1 + 0x48);
    }
  }
  return;
}

// RB_GenericMine_ThTick
// TNT, Nitro, Potion
void FUN_800acb60(int param_1)

{
  short sVar1;
  ushort uVar2;
  undefined2 uVar3;
  undefined *puVar4;
  int iVar5;
  int iVar6;
  code *pcVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  undefined4 uVar10;
  int *piVar11;
  int iVar12;
  int *piVar13;
  
  // get instance from thread
  iVar12 = *(int *)(param_1 + 0x34);
  
  // instance -> thread -> object
  piVar13 = *(int **)(*(int *)(iVar12 + 0x6c) + 0x30);
  
  // if weapon is "thrown" like Komodo Joe,
  // this is offset 0x28
  if ((*(ushort *)(piVar13 + 10) & 2) != 0) 
  {
	// instance -> model -> modelID == TNT
    if (*(short *)(*(int *)(iVar12 + 0x18) + 0x10) == 0x27) 
	{
	  // RB_TNT_ThTick_ThrowOffHead
      pcVar7 = FUN_800ad310;
	  
	  // set scale (x, y, z)
      *(undefined2 *)(iVar12 + 0x1c) = 0x800;
      *(undefined2 *)(iVar12 + 0x1e) = 0x800;
      *(undefined2 *)(iVar12 + 0x20) = 0x800;
    }
	
	// Potion
    else 
	{
	  // cooldown of 0.24s
      *(undefined2 *)((int)piVar13 + 0x2a) = 0xf0;
	  
	  // RB_Potion_ThTick_InAir
      pcVar7 = FUN_800ac6b4;
    }
	
	// ThTick_SetAndExec
    FUN_800716ec(param_1,pcVar7);
  }
  
  // reduce cooldown
  iVar5 = (uint)*(ushort *)((int)piVar13 + 0x2a) - (uint)*(ushort *)(PTR_DAT_8008d2ac + 0x1d04);
  *(undefined2 *)((int)piVar13 + 0x2a) = (short)iVar5;
  
  // if negative, then set zero
  if (iVar5 * 0x10000 < 0) {
    *(undefined2 *)((int)piVar13 + 0x2a) = 0;
  }
  
  // instance -> animFrame
  sVar1 = *(short *)(iVar12 + 0x54);
  
  // INSTANCE_GetNumAnimFrames
  iVar5 = FUN_80030f58(iVar12,0);
  
  // if animation is not over
  if ((int)sVar1 + 1 < iVar5) 
  {
	// increment animation frame
    *(short *)(iVar12 + 0x54) = *(short *)(iVar12 + 0x54) + 1;
  }
  
  // if animation is over
  else 
  {
	// restart animation
    *(undefined2 *)(iVar12 + 0x54) = 0;
  }
  
  // increment posY by velY * time
  iVar5 = *(int *)(iVar12 + 0x48) +
          ((int)*(short *)((int)piVar13 + 0xe) * *(int *)(PTR_DAT_8008d2ac + 0x1d04) >> 5);
  *(int *)(iVar12 + 0x48) = iVar5;
  
  // if height is higher than max height
  if (iVar5 < (int)*(short *)((int)piVar13 + 0x12)) {
    *(int *)(iVar12 + 0x48) = (int)*(short *)((int)piVar13 + 0x12);
  }
  
  // decrease velocity by time, this is artificial gravity (negative acceleration)
  iVar5 = (uint)*(ushort *)((int)piVar13 + 0xe) - ((*(int *)(PTR_DAT_8008d2ac + 0x1d04) << 2) >> 5);
  *(undefined2 *)((int)piVar13 + 0xe) = (short)iVar5;
  
  if (iVar5 * 0x10000 >> 0x10 < -0x60) {
    *(undefined2 *)((int)piVar13 + 0xe) = 0xffa0;
  }
  
  // If scale is under 0x1000
  if (*(short *)(iVar12 + 0x1c) < 0x1000) 
  {
	// make scale larger each frame
    *(short *)(iVar12 + 0x1c) = *(short *)(iVar12 + 0x1c) + 0x200;
    *(short *)(iVar12 + 0x1e) = *(short *)(iVar12 + 0x1e) + 0x200;
    *(short *)(iVar12 + 0x20) = *(short *)(iVar12 + 0x20) + 0x200;
  }
  
  // if scale is done growing
  else 
  {
	// set to the intended size
    *(undefined2 *)(iVar12 + 0x1c) = 0x1000;
    *(undefined2 *)(iVar12 + 0x1e) = 0x1000;
    *(undefined2 *)(iVar12 + 0x20) = 0x1000;
  }
  uVar8 = 0x3840;
  
  // instance -> model -> modelID is red beaker or green beaker
  if ((uint)*(ushort *)(*(int *)(iVar12 + 0x18) + 0x10) - 0x46 < 2) 
  {
    uVar8 = 0x1900;
  }
  
  // RB_Hazard_CollideWithDrivers
  iVar5 = FUN_800ac220(iVar12,(int)*(short *)(piVar13 + 9),uVar8,piVar13[1]);
  
  // if no collision
  if (iVar5 == 0) goto LAB_800ad17c;
  
  // get driver who hit tnt (or nitro) 
  // from the object attached to thread
  iVar5 = *(int *)(*(int *)(iVar5 + 0x6c) + 0x30);
  
  // if mineWeapon->crateInst, if inst->thread, if thread->object
  if (((piVar13[2] != 0) && (iVar6 = *(int *)(piVar13[2] + 0x6c), iVar6 != 0)) &&
     (iVar6 = *(int *)(iVar6 + 0x30), iVar6 != 0)) 
  {
	// unpause cooldown (boolPauseCooldown)
    *(undefined2 *)(iVar6 + 4) = 0;
  }
  
  // instance -> model -> modelID
  uVar2 = *(ushort *)(*(int *)(iVar12 + 0x18) + 0x10);
  
  // red beaker or green beaker
  if ((uint)uVar2 - 0x46 < 2) 
  {
	// count times hit by motionless potion
    uVar8 = 2;
	
	// if fly-forward timer is still active
    if (*(short *)((int)piVar13 + 0x2a) != 0) {
      
	  // moving potion
	  uVar8 = 4;
    }
	
	// RB_Hazard_HurtDriver (spin out)
    iVar6 = FUN_800ac1b0(iVar5,1,*(undefined4 *)(*(int *)(piVar13[1] + 0x6c) + 0x30),uVar8);
    
	// if collision, and if this was a red potion
	if ((iVar6 != 0) && ((*(ushort *)(piVar13 + 10) & 1) != 0)) 
	{
	  // RB_RainCloud_Init
      FUN_800b1220(iVar5);
    }
	
    puVar4 = PTR_DAT_8008d2ac;
	
	// if this driver is not an AI
    if ((*(uint *)(iVar5 + 0x2c8) & 0x100000) == 0) 
	{
	  // current fade value (bright white)
      *(undefined2 *)(PTR_DAT_8008d2ac + (uint)*(byte *)(iVar5 + 0x4a) * 0x110 + 0x17a) = 0x1fff;
      
	  // desired fade value (neutral)
	  *(undefined2 *)(puVar4 + (uint)*(byte *)(iVar5 + 0x4a) * 0x110 + 0x17c) = 0x1000;
      
	  // fade step
	  *(undefined2 *)(puVar4 + (uint)*(byte *)(iVar5 + 0x4a) * 0x110 + 0x17e) = 0xff78;
    }
	
	// This block of code only executes for 
	// red beaker or green beaker
	
	// make player icon red
	// If this is a red beaker
    uVar8 = 0x1e;
	
	// instance -> model -> modelID == GreanBeaker
    if (*(short *)(*(int *)(iVar12 + 0x18) + 0x10) == 0x47) 
	{
	  // make player icon green
      uVar8 = 0xffffffe2;
    }
	
LAB_800ace88:
    
	// set icon damage timer
	*(undefined4 *)(iVar5 + 0x4ac) = uVar8;
	
LAB_800ad174:

	// RB_GenericMine_ThDestroy
    FUN_800ad250(param_1,iVar12,piVar13);
  }
  else {
	  
	// if driver->instTntRecv is valid
    if (*(int *)(iVar5 + 0x18) != 0) 
	{
	  // RB_Hazard_HurtDriver (blasted)
      FUN_800ac1b0(iVar5,2,0,2);
	  
	  // driver->instTntRecv
      iVar6 = *(int *)(iVar5 + 0x18);
	  
	  // icon damage timer, draw icon as red
      *(undefined4 *)(iVar5 + 0x4ac) = 0x1e;
	  
	  // set scale (x, y, z) to zero
      *(undefined2 *)(iVar6 + 0x20) = 0;
      *(undefined2 *)(iVar6 + 0x1e) = 0;
      *(undefined2 *)(iVar6 + 0x1c) = 0;
	  
	  // make invisible
      *(uint *)(*(int *)(iVar5 + 0x18) + 0x28) = *(uint *)(*(int *)(iVar5 + 0x18) + 0x28) | 0x80;
      
	  // driver -> instTntRecv -> thread
	  iVar6 = *(int *)(*(int *)(iVar5 + 0x18) + 0x6c);
	  
	  // this thread is now dead
      *(uint *)(iVar6 + 0x1c) = *(uint *)(iVar6 + 0x1c) | 0x800;
	  
	  // erase instTntRecv
      *(undefined4 *)(iVar5 + 0x18) = 0;
	  
      goto LAB_800ad174;
    }
	
	// if driver has squished timer
    if (*(short *)(iVar5 + 0x404) != 0) 
	{
	  // RB_Hazard_HurtDriver (blasted)
      FUN_800ac1b0(iVar5,2,0,2);
      
	  uVar8 = 0x1e;
      goto LAB_800ace88;
    }
	
	// if model is Nitro
    if (uVar2 == 6) 
	{
	  // RB_Hazard_HurtDriver (blasted)
      FUN_800ac1b0(iVar5,2,*(undefined4 *)(*(int *)(piVar13[1] + 0x6c) + 0x30),2);
      
	  // Why does icon turn red in gameplay?
	  
	  // icon damage timer, draw icon as green
	  *(undefined4 *)(iVar5 + 0x4ac) = 0xffffffe2;
	  
      goto LAB_800ad174;
    }
	
	// if model is TNT
    if (uVar2 == 0x27) 
	{
	  // RB_Hazard_HurtDriver (keep driving?)
      iVar6 = FUN_800ac1b0(iVar5,0,*(undefined4 *)(*(int *)(piVar13[1] + 0x6c) + 0x30),2);
      
	  if (iVar6 == 0) goto LAB_800ad174;
	  
	  // if Instance has no InstDef,
	  // if this TNT is not part of the level,
	  // use existing thread
      if (*(int *)(iVar12 + 0x2c) == 0) 
	  {
		// icon damage timer, draw icon as red
        *(undefined4 *)(iVar5 + 0x4ac) = 0x1e;
		
		// give driver to tnt object
        *piVar13 = iVar5;
		
		// driver -> instTntRecv
        *(int *)(iVar5 + 0x18) = iVar12;
		
		// RB_MinePool_Remove
        FUN_800ac0e4(piVar13);
		
		// play Hit TNT "bounce" sound
        FUN_8002f0dc(0x50,iVar12);
		
        *(undefined4 *)(iVar12 + 0x70) = 0;
        *(uint *)(iVar12 + 0x28) = *(uint *)(iVar12 + 0x28) | 0x200;
        *(undefined2 *)((int)piVar13 + 0xe) = 0x30;
        *(undefined2 *)(piVar13 + 3) = 0;
        *(undefined2 *)(piVar13 + 4) = 0;
        *(undefined2 *)(piVar13 + 7) = 0;
        *(undefined2 *)((int)piVar13 + 0x1e) = 0;
        *(undefined2 *)(piVar13 + 8) = 0;
        *(undefined2 *)((int)piVar13 + 0x12) = 0x3fff;
		
		// ThTick_SetAndExec RB_TNT_ThTick_ThrowOnHead
        FUN_800716ec(param_1,FUN_800ad710);
      }
	  
	  // if this TNT has an InstDef, then it is part of LEV,
	  // kill the old thread and birth a new one (why?)
      else 
	  {
		// DAT_800ab9fc
		// "tnt1"
		
		// INSTANCE_BirthWithThread
		// ThTick = RB_GenericMine_ThTick, but set later to RB_TNT_ThTick_ThrowOnHead
		// 0x300 flag = SmallStackPool
		// 4 = "mine" thread bucket
        iVar6 = FUN_800309a4(0x27,&DAT_800ab9fc,0x300,4,FUN_800acb60,0x2c,0);
		
		// get rotation of player and assign to tnt
        uVar9 = *(undefined4 *)(iVar12 + 0x34);
        uVar10 = *(undefined4 *)(iVar12 + 0x38);
        uVar8 = *(undefined4 *)(iVar12 + 0x3c);
        *(undefined4 *)(iVar6 + 0x30) = *(undefined4 *)(iVar12 + 0x30);
        *(undefined4 *)(iVar6 + 0x34) = uVar9;
        *(undefined4 *)(iVar6 + 0x38) = uVar10;
        *(undefined4 *)(iVar6 + 0x3c) = uVar8;
		
		// X, Y, Z positions of instance
        uVar9 = *(undefined4 *)(iVar12 + 0x44);
        uVar10 = *(undefined4 *)(iVar12 + 0x48);
        uVar8 = *(undefined4 *)(iVar12 + 0x4c);
		
		// finish last rotation variable
        *(undefined4 *)(iVar6 + 0x40) = *(undefined4 *)(iVar12 + 0x40);
        
		// X, Y, Z positions of TNT instanece
		*(undefined4 *)(iVar6 + 0x44) = uVar9;
        *(undefined4 *)(iVar6 + 0x48) = uVar10;
        *(undefined4 *)(iVar6 + 0x4c) = uVar8;
		
		// set funcThDestroy to remove instance from instance pool
        *(undefined4 *)(*(int *)(iVar6 + 0x6c) + 0x24) = 0x80041dfc;
		
		// set funcThCollide
        *(undefined4 *)(*(int *)(iVar6 + 0x6c) + 0x28) = 0x800ac4b8;
		
		// Get object from thread
        piVar11 = *(int **)(*(int *)(iVar6 + 0x6c) + 0x30);
		
		// mineWeapon->instParent
        piVar11[1] = *(int *)(iVar5 + 0x1c);
		
		// frameCount_DontHurtParent
        *(undefined2 *)(piVar11 + 9) = 10;
		
		// boolDestroyed
        *(undefined2 *)(piVar11 + 5) = 0;
		
		// unk
        *(undefined2 *)((int)piVar11 + 0x26) = 0;
		
		// crateInst
        piVar11[2] = 0;
        
		// extraFlags
		*(undefined2 *)(piVar11 + 10) = 0;
		
		// get posY
        uVar3 = *(undefined2 *)(iVar12 + 0x48);
        
		// give driver to tnt object (mineWeapon)
		*piVar11 = iVar5;
		
		// set mineWeapon posY
        *(undefined2 *)((int)piVar11 + 0x12) = uVar3;
		
		// driver -> instTntRecv
        *(int *)(iVar5 + 0x18) = iVar6;
		
		// TNT bounce sound
        FUN_8002f0dc(0x50,iVar6);
		
        *(undefined4 *)(iVar6 + 0x70) = 0;
        *(uint *)(iVar6 + 0x28) = *(uint *)(iVar6 + 0x28) | 0x200;
        *(undefined2 *)((int)piVar11 + 0xe) = 0x30;
        *(undefined2 *)(piVar11 + 3) = 0;
        *(undefined2 *)(piVar11 + 4) = 0;
        *(undefined2 *)(piVar11 + 7) = 0;
        *(undefined2 *)((int)piVar11 + 0x1e) = 0;
        *(undefined2 *)(piVar11 + 8) = 0;
		
		// set RB_TNT_ThTick_ThrowOnHead
        *(undefined4 *)(*(int *)(iVar6 + 0x6c) + 0x2c) = 0x800ad710;
		
		// RB_MinePool_Remove
        FUN_800ac0e4(piVar13);
		
		// set scale (x, y, z) to zero
        *(undefined2 *)(iVar12 + 0x20) = 0;
        *(undefined2 *)(iVar12 + 0x1e) = 0;
        *(undefined2 *)(iVar12 + 0x1c) = 0;
		
		// make invisible
        *(uint *)(iVar12 + 0x28) = *(uint *)(iVar12 + 0x28) | 0x80;
        
		// this thread is now dead
		*(uint *)(param_1 + 0x1c) = *(uint *)(param_1 + 0x1c) | 0x800;
      }
    }
  }
LAB_800ad17c:

  // frameCount_DontHurtParent
  if (*(short *)(piVar13 + 9) != 0) {
    *(short *)(piVar13 + 9) = *(short *)(piVar13 + 9) + -1;
  }
  
  // if mineWeapon->boolDestroyed == 0
  if (*(short *)(piVar13 + 5) == 0) {
    return;
  }
  
  // if thread is dead, quit function
  // this is if GenericMine_ThDestroy already ran
  if ((*(uint *)(param_1 + 0x1c) & 0x800) != 0) {
    return;
  }
  
  // === If destroyed from MinePool overflow ===
  
  // instance -> model -> modelID
  sVar1 = *(short *)(*(int *)(iVar12 + 0x18) + 0x10);
  
  // if model is Nitro
  if (sVar1 == 6) 
  {
	// glass shatter
    uVar8 = 0x3f;
  }
  
  else 
  {
	// if model is not TNT
    if (sVar1 != 0x27) 
	{
	  // if model is green or red beaker
      if ((ushort)(*(short *)(*(int *)(iVar12 + 0x18) + 0x10) - 0x46U) < 2) 
	  {
		// glass shatter sound
        FUN_8002f0dc(0x3f,iVar12);
		
		// RB_Explosion_InitPotion
        FUN_800b1458(iVar12);
      }
      goto LAB_800ad21c;
    }
	
	// tnt explosoin sound
    uVar8 = 0x3d;
  }
  
  // play sound
  FUN_8002f0dc(uVar8,iVar12);
  
  // RB_Blowup_Init
  FUN_800b18f8(iVar12);
LAB_800ad21c:

  // this thread is now dead
  *(uint *)(param_1 + 0x1c) = *(uint *)(param_1 + 0x1c) | 0x800;
  
  return;
}

// RB_GenericMine_ThDestroy
void FUN_800ad250(int param_1,int param_2,undefined4 param_3)

{
  short sVar1;
  undefined4 uVar2;
  
  // instance -> model -> modelID
  sVar1 = *(short *)(*(int *)(param_2 + 0x18) + 0x10);
  
  // if model is Nitro
  if (sVar1 == 6) 
  {
	// glass shatter sound
    uVar2 = 0x3f;
  }
  
  else 
  {
	// if model is not TNT
    if (sVar1 != 0x27) 
	{
	  // play sound of glass shatter
      FUN_8002f0dc(0x3f,param_2);
	  
	  // RB_Explosion_InitPotion
      FUN_800b1458(param_2);
      
	  goto LAB_800ad2c8;
    }
	
	// explosion sound
    uVar2 = 0x3d;
  }
  
  // play sound
  FUN_8002f0dc(uVar2,param_2);
  
  // RB_Blowup_Init
  FUN_800b18f8(param_2);
LAB_800ad2c8:

  // Set scale (x, y, z) to zero
  *(undefined2 *)(param_2 + 0x20) = 0;
  *(undefined2 *)(param_2 + 0x1e) = 0;
  *(undefined2 *)(param_2 + 0x1c) = 0;
  
  // make invisible
  *(uint *)(param_2 + 0x28) = *(uint *)(param_2 + 0x28) | 0x80;
  
  // RB_MinePool_Remove
  FUN_800ac0e4(param_3);
  
  // this thread is now dead
  *(uint *)(param_1 + 0x1c) = *(uint *)(param_1 + 0x1c) | 0x800;
  
  return;
}

// RB_TNT_ThTick_ThrowOffHead
// In air, after spamming L1 or R1,
// will explode on impact with ground
void FUN_800ad310(int param_1)

{
  int iVar1;
  int *piVar2;
  
  // thread -> instance
  iVar1 = *(int *)(param_1 + 0x34);
  
  // instance -> thread -> object (tnt)
  piVar2 = *(int **)(*(int *)(iVar1 + 0x6c) + 0x30);
  
  // inst->matrix.t[1]
  *(int *)(iVar1 + 0x48) =
       *(int *)(iVar1 + 0x48) +
       ((int)*(short *)((int)piVar2 + 0xe) * *(int *)(PTR_DAT_8008d2ac + 0x1d04) >> 5);
  
  // stopFallAtY
  if (*(short *)((int)piVar2 + 0x12) == 0x3fff) 
    *(undefined2 *)((int)piVar2 + 0x12) = *(undefined2 *)(*(int *)(*piVar2 + 0x1c) + 0x48);
  
  if (*(int *)(iVar1 + 0x48) <= (int)*(short *)((int)piVar2 + 0x12)) 
  {
	// plays tnt explosion sound 3D
    FUN_8002f0dc(0x3d,iVar1);
	
	// RB_Blowup_Init
    FUN_800b18f8(iVar1);
    
	// Set scale (x, y, z) to zero
	*(undefined2 *)(iVar1 + 0x20) = 0;
    *(undefined2 *)(iVar1 + 0x1e) = 0;
    *(undefined2 *)(iVar1 + 0x1c) = 0;
	
	// make invisible
    *(uint *)(iVar1 + 0x28) = *(uint *)(iVar1 + 0x28) | 0x80;
	
	// this thread is now dead
    *(uint *)(param_1 + 0x1c) = *(uint *)(param_1 + 0x1c) | 0x800;
	
	// tntObject -> driver -> tntRecv = 0
    *(undefined4 *)(*piVar2 + 0x18) = 0;
  }
  
  // decrease velocity (artificial gravity)
  iVar1 = (uint)*(ushort *)((int)piVar2 + 0xe) - ((*(int *)(PTR_DAT_8008d2ac + 0x1d04) << 2) >> 5);
  *(undefined2 *)((int)piVar2 + 0xe) = (short)iVar1;
  if (iVar1 * 0x10000 >> 0x10 < -0x60) {
    *(undefined2 *)((int)piVar2 + 0xe) = 0xffa0;
  }
  	
  // this skips $RA backup/restore, faster than JR $RA
  FUN_80071694(param_1);
  
  return;
}

// RB_TNT_ThTick_SitOnHead
void FUN_800ad44c(int param_1)
{
  char cVar1;
  short sVar2;
  undefined2 uVar3;
  int iVar4;
  int *piVar5;
  int iVar6;
  
  // thread->instance
  iVar6 = *(int *)(param_1 + 0x34);
  
  // instance->thread->object (tnt)
  piVar5 = *(int **)(*(int *)(iVar6 + 0x6c) + 0x30);
  
  // CopyMatrix
  // To: TNT instance
  // From: obj->driverWhoHitMe->instance
  // Delta: TNT -> 0x1c (position relative to driver)
  FUN_800313c8(iVar6,*(undefined4 *)(*piVar5 + 0x1c),piVar5 + 7);
  
  // Get Kart State
  cVar1 = *(char *)(*piVar5 + 0x376);
  
  // If crashing, spinning out, or being mask-grabbed
  if (((cVar1 == '\x01') || (cVar1 == '\x05')) || (cVar1 == '\x03')) {
    
	// Play explosion sound
	FUN_8002f0dc(0x3d,iVar6);
	
	// RB_Blowup_Init
    FUN_800b18f8(iVar6);
	
LAB_800ad4ec:

	// reset TNT-related pointers
    *(undefined2 *)(iVar6 + 0x20) = 0;
    *(undefined2 *)(iVar6 + 0x1e) = 0;
    *(undefined2 *)(iVar6 + 0x1c) = 0;
	
	// make invisible
    *(uint *)(iVar6 + 0x28) = *(uint *)(iVar6 + 0x28) | 0x80;
	
	// this thread is now dead
    *(uint *)(param_1 + 0x1c) = *(uint *)(param_1 + 0x1c) | 0x800;
	
	// tnt->driver->tntRecv = 0
    *(undefined4 *)(*piVar5 + 0x18) = 0;
		
	// this skips $RA backup/restore, faster than JR $RA
    FUN_80071694(param_1);
  }
  else 
  {
	// If you are already blasted
    if (cVar1 == '\x06') 
	{
	  // Play explosion sound
      FUN_8002f0dc(0x3d,iVar6);
	  
	  // RB_Explosion_InitGeneric
      FUN_800b1630(iVar6);
	  
      goto LAB_800ad4ec;
    }
  }
  
  // if this driver is not an AI
  if ((*(uint *)(*piVar5 + 0x2c8) & 0x100000) == 0) 
  {
	// if player did not start jumping this frame
    if ((*(uint *)(*piVar5 + 0x2c8) & 0x400) == 0) goto LAB_800ad5f8;
	
    if (*(short *)((int)piVar5 + 0x22) != 0) {
      *(short *)((int)piVar5 + 0x22) = *(short *)((int)piVar5 + 0x22) + -1;
      goto LAB_800ad5f8;
    }
    *(undefined2 *)((int)piVar5 + 0x22) = 0;
  }
  else {
    iVar4 = FUN_8003ea28();
    if (iVar4 != (iVar4 / 0x10e) * 0x10e) goto LAB_800ad5f8;
  }
  
  // set scale (x, y, z)
  *(undefined2 *)(iVar6 + 0x20) = 0x800;
  *(undefined2 *)(iVar6 + 0x1e) = 0x800;
  *(undefined2 *)(iVar6 + 0x1c) = 0x800;
  
  // tnt->driver->tntRecv = 0
  *(undefined4 *)(*piVar5 + 0x18) = 0;
  
  *(undefined2 *)(piVar5 + 3) = 0;
  *(undefined2 *)((int)piVar5 + 0xe) = 0x30;
  *(undefined2 *)(piVar5 + 4) = 0;
  *(undefined2 *)(piVar5 + 7) = 0;
  *(undefined2 *)((int)piVar5 + 0x1e) = 0;
  *(undefined2 *)(piVar5 + 8) = 0;
  
  // assign RB_TNT_ThTick_ThrowOffHead
  FUN_800716ec(param_1,FUN_800ad310);
  
LAB_800ad5f8:

  // Get how many frames the TNT has 
  // been on top of someone's head
  sVar2 = *(short *)((int)piVar5 + 0x16);
  
  // If there is time remaining until TNT blows up,
  // which takes 0x5a frames, 3 seconds
  if (sVar2 < 0x5a) 
  {
	// If frame is any of these 6 numbers
    if ((((sVar2 == 0) || (sVar2 == 0x14)) ||
        ((sVar2 == 0x28 || ((sVar2 == 0x3c || (sVar2 == 0x46)))))) || (sVar2 == 0x50)) 
	{
	  // Make a "honk" sound
      FUN_8002f0dc(0x3e,iVar6);
    }
	
	// add to the frame counter
    *(short *)((int)piVar5 + 0x16) = *(short *)((int)piVar5 + 0x16) + 1;
  }
  
  // If time runs out
  else 
  {
	// Blow up
	
	// RB_Hazard_HurtDriver (blasted)
    FUN_800ac1b0(*piVar5,2,*(undefined4 *)(*(int *)(piVar5[1] + 0x6c) + 0x30),0);
    
	// icon damage timer, draw icon as red
	*(undefined4 *)(*piVar5 + 0x4ac) = 0x1e;
	
	// play 3D sound for TNT explosion
    FUN_8002f0dc(0x3d,iVar6);
	
	// RB_Blowup_Init
    FUN_800b18f8(iVar6);
	
	// this thread is now dead
    *(uint *)(param_1 + 0x1c) = *(uint *)(param_1 + 0x1c) | 0x800;
	
	// tnt->driver->tntRecv = 0
    *(undefined4 *)(*piVar5 + 0x18) = 0;
	
	// this skips $RA backup/restore, faster than JR $RA
    FUN_80071694(param_1);
  }
  
  // set scale of TNT, given frame of animation
  uVar3 = *(undefined2 *)(&DAT_800b295c + (int)*(short *)((int)piVar5 + 0x16) * 4);
  *(undefined2 *)(iVar6 + 0x20) = uVar3;
  *(undefined2 *)(iVar6 + 0x1c) = uVar3;
  *(undefined2 *)(iVar6 + 0x1e) =
       *(undefined2 *)(&DAT_800b295e + (int)*(short *)((int)piVar5 + 0x16) * 4);
  return;
}

// RB_TNT_ThTick_ThrowOnHead
// In air, after hitting, before spamming L1 or R1
void FUN_800ad710(int param_1)
{
  int iVar1;
  int *piVar2;
  int iVar3;
  undefined2 local_38;
  undefined2 local_36;
  undefined2 local_34;
  undefined auStack48 [32];
  
  // get instance from thread
  iVar3 = *(int *)(param_1 + 0x34);
  
  // instance -> thread -> object
  piVar2 = *(int **)(*(int *)(iVar3 + 0x6c) + 0x30);
  
  // alter height of TNT as it flies onto a driver's head
  iVar1 = (uint)*(ushort *)((int)piVar2 + 0x1e) +
          ((int)*(short *)((int)piVar2 + 0xe) * *(int *)(PTR_DAT_8008d2ac + 0x1d04) >> 5);
  
  // new height of TNT
  *(undefined2 *)((int)piVar2 + 0x1e) = (short)iVar1;
  
  // if TNT velocity moves downward
  if (*(short *)((int)piVar2 + 0xe) < 0) 
  {
	// 0x800b2ac4
	// BSS before Baron_ThTick,
	// determines height of TNT for each player
    
	// if TNT landed on head
    if ((iVar1 * 0x10000 >> 0x10 <
         (int)*(short *)(&DAT_800b2ac4 +
                        (int)(short)(&DAT_80086e84)[*(byte *)(*piVar2 + 0x4a)] * 2)) &&
       (*(short *)((int)piVar2 + 0x1e) =
             *(short *)(&DAT_800b2ac4 +
                       (int)(short)(&DAT_80086e84)[*(byte *)(*piVar2 + 0x4a)] * 2),
       *(short *)(iVar3 + 0x1c) == 0x800)) 
	{
	  // Set TNT timer to 0, it blows up at 0x5a
      *(undefined2 *)((int)piVar2 + 0x16) = 0;
	  
	  // RNG
      iVar1 = FUN_8003ea28();
      
	  // Set number of required jumps to 8, with some RNG to mix it up
	  *(short *)((int)piVar2 + 0x22) = 8 - ((short)iVar1 + (short)(iVar1 / 2) * -2);
	  
	  // play sound that you hit a TNT
      FUN_8002f0dc(0x51,iVar3);
	  
      *(char *)(iVar3 + 0x50) = *(char *)(*(int *)(*piVar2 + 0x1c) + 0x50) + -1;
      *(char *)(iVar3 + 0x51) = *(char *)(*(int *)(*piVar2 + 0x1c) + 0x51) + -1;
      
	  // assign RB_TNT_ThTick_SitOnHead
	  FUN_800716ec(param_1,FUN_800ad44c);
    }
  }
  
  // CopyMatrix
  // To: TNT instance
  // From: obj->driverWhoHitMe->instance
  // Delta: TNT -> 0x1c (position relative to driver)
  FUN_800313c8(iVar3,*(undefined4 *)(*piVar2 + 0x1c),piVar2 + 7);
  
  // rotation (tntSpinY)
  local_38 = 0;
  local_36 = *(undefined2 *)((int)piVar2 + 0x26);
  local_34 = 0;
  
   // convert 3 rotation shorts into rotation matrix
  FUN_8006c2a4(auStack48,&local_38);
  
  FUN_8006c3b0(iVar3 + 0x30,iVar3 + 0x30,auStack48);
  
  // reduce time remaining until TNT lands on head
  iVar1 = (uint)*(ushort *)((int)piVar2 + 0xe) - ((*(int *)(PTR_DAT_8008d2ac + 0x1d04) << 2) >> 5);
  *(undefined2 *)((int)piVar2 + 0xe) = (short)iVar1;
  
  // set a minimum value (-0x60)
  if (iVar1 * 0x10000 >> 0x10 < -0x60) 
  {
    *(undefined2 *)((int)piVar2 + 0xe) = 0xffa0;
  }
  
  // rotation (tntSpinY)
  *(short *)((int)piVar2 + 0x26) = *(short *)((int)piVar2 + 0x26) + 0x100;
  
  // if scale is small
  if (*(short *)(iVar3 + 0x1c) < 0x801) 
  {
	// set min scale
    *(undefined2 *)(iVar3 + 0x1c) = 0x800;
    *(undefined2 *)(iVar3 + 0x1e) = 0x800;
    *(undefined2 *)(iVar3 + 0x20) = 0x800;
  }
  
  // if scale is large
  else 
  {
	// reduce scale
    *(short *)(iVar3 + 0x1c) = *(short *)(iVar3 + 0x1c) + -0x100;
    *(short *)(iVar3 + 0x1e) = *(short *)(iVar3 + 0x1e) + -0x100;
    *(short *)(iVar3 + 0x20) = *(short *)(iVar3 + 0x20) + -0x100;
  }
  return;
}

// RB_Explosion_ThTick,
// shatter or explosion
void FUN_800ad92c(int param_1)
{
  short sVar1;
  int iVar2;
  int iVar3;
  
  // thread -> instance
  iVar3 = *(int *)(param_1 + 0x34);
  
  // instance -> animFrame
  sVar1 = *(short *)(iVar3 + 0x54);
  
  // INSTANCE_GetNumAnimFrames
  iVar2 = FUN_80030f58(iVar3,0);
  
  // if instance is not at end of animation
  if ((int)sVar1 + 1 < iVar2) 
  {
	// increment animation frame
    *(short *)(iVar3 + 0x54) = *(short *)(iVar3 + 0x54) + 1;
  }
  
  // if animation is done
  else 
  {
	// This thread is now dead
    *(uint *)(param_1 + 0x1c) = *(uint *)(param_1 + 0x1c) | 0x800;
  }
  
  // this skips $RA backup/restore, faster than JR $RA
  FUN_80071694(param_1);
  
  return;
}

// RB_Hazard_CollLevInst (tnt, potion, warpball, etc) (not hazard? moving explosive?)
// param_1 - BSP result
// param_2 - bsp (hitbox)
undefined4 FUN_800ad9ac(int param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  
  if ((((**(byte **)(param_1 + 0x48) & 0x80) != 0) &&
      (iVar1 = *(int *)(*(byte **)(param_1 + 0x48) + 0x1c), iVar1 != 0)) &&
     
	 // instance = instDef->instance (lev only)
	 (iVar4 = *(int *)(iVar1 + 0x2c), iVar4 != 0)) 
  {
	// get modelID from InstDef
    iVar3 = (int)*(short *)(iVar1 + 0x3c);
	
	// ThreadMeta
    iVar1 = FUN_8001d094(iVar3);
	
	// if LThC is not nullptr
    if ((iVar1 != 0) && (*(code **)(iVar1 + 8) != (code *)0x0)) 
	{		
	  // execute LThC, make thread for this instance
	  // upon collision with the instance, let it run thread->funcThCollide
      uVar2 = (**(code **)(iVar1 + 8))(iVar4,param_2,param_1);
	  
	  // if not PU_WUMPA_FRUIT
      if (iVar3 != 2) 
	  {
		// useless
        if (iVar3 < 2) {
          return uVar2;
        }
		
		// anything except for
		// 7: PU_FRUIT_CRATE,
		// 8: PU_RANDOM_CRATE (weapon box)
        if (8 < iVar3) {
          return uVar2;
        }
        if (iVar3 < 7) {
          return uVar2;
        }
      }
      return 0;
    }
  }
  
  // make potion open teeth,
  // or make warpball turn around
  return 1;
}

// RB_Hazard_InterpolateValue
int FUN_800ada90(ushort param_1,ushort param_2,short param_3)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  ushort uVar4;
  
  uVar4 = param_1;
  
  // if current rotation is not desired rotation
  if ((int)(short)param_1 != (int)(short)param_2) 
  {
	// get difference between them
    uVar3 = (int)(short)param_2 - (int)(short)param_1 & 0xfff;
	
	// if difference is huge
    if (0x7ff < uVar3) 
	{
	  // rotate a negative direction
      uVar3 = uVar3 - 0x1000;
    }
	
    uVar1 = uVar3;
    if ((int)uVar3 < 0) {
      uVar1 = -uVar3;
    }
	
	// rotation speed
    iVar2 = (int)param_3;
	
	// if rotation speed is less than 
	// remaining needed rotation
    if (iVar2 <= (int)uVar1) 
	{
      if ((int)uVar3 < 1) 
	  {
        uVar4 = param_1 & 0xfff;
        if (-1 < (int)uVar3) goto LAB_800adb44;
		
		// new rotation is old rotation - speed
        param_2 = param_1 - (short)(iVar2 * *(int *)(PTR_DAT_8008d2ac + 0x1d04) >> 5);
      }
      else 
	  {
		// new rotation is old rotation + speed
        param_2 = param_1 + (short)(iVar2 * *(int *)(PTR_DAT_8008d2ac + 0x1d04) >> 5);
      }
    }
	
	// set new rotation, which is calculated rotation,
	// or the desired rotation if (desired-curr < speed)
    uVar4 = param_2 & 0xfff;
  }
LAB_800adb44:
  return (int)(short)uVar4;
}

// RB_MovingExplosive_ThTick
// function for moving bomb, shiledbomb, or missile
void FUN_800adb50(int param_1)
{
  short sVar1;
  undefined *puVar2;
  short sVar3;
  code *pcVar4;
  undefined2 uVar5;
  int iVar6;
  undefined4 uVar7;
  int iVar8;
  int *piVar9;
  int iVar10;
  undefined2 local_30;
  short local_2e;
  undefined2 local_2c;
  undefined2 local_28;
  short local_26;
  undefined2 local_24;
  
  // get instance from thread
  iVar10 = *(int *)(param_1 + 0x34);
  
  // get object, from thread, from instance
  piVar9 = *(int **)(*(int *)(iVar10 + 0x6c) + 0x30);
  
  piVar9[0x12] = piVar9[0x12] + *(int *)(PTR_DAT_8008d2ac + 0x1d04);
  
  // instance -> model -> modelID
  sVar3 = *(short *)(*(int *)(iVar10 + 0x18) + 0x10);
  
  // if model is missile
  if (sVar3 == 0x29) 
  {
    if ((*(uint *)(param_1 + 0x1c) & 0x800) == 0) {
      uVar7 = 0x4b;
      goto LAB_800adc00;
    }
  }
  else 
  {
	// if model is bomb
    if (sVar3 == 0x3b) 
	{
      uVar7 = 0x48;
    }
    else 
	{
	  // if model is not blue or green shield
      if ((sVar3 != 0x56) && (sVar3 != 0x5e)) goto LAB_800adc08;
	  
	  // if model is blue or green shield
      uVar7 = 0x59;
    }
LAB_800adc00:

	// PlaySound3D_Flags,
	// offset 0x24
    FUN_8002f31c(piVar9 + 9,uVar7,iVar10);
  }
LAB_800adc08:

  // driver -> invisibleTimer
  if (*(int *)(*piVar9 + 0x28) == 0) 
  {
    if (
			(*(int *)(*piVar9 + 0x2cc) < 0) && 
			
			// instance -> model -> objectID == missile
			(*(short *)(*(int *)(iVar10 + 0x18) + 0x10) == 0x29)
		) 
	{
      piVar9[0x15] = 10;
    }
  }
  
  // if driver is invisible
  else 
  {
	// erase pointer to driver,
	// cause tracker can't find invisible driver
    *piVar9 = 0;
  }
  
  // "tracker" can be missile, bomb, or shield
  
  // get driver the tracker is chasing
  iVar8 = *piVar9;
  
  if (
		// if driver is invalid
		(iVar8 == 0) || 
		(*(short *)((int)piVar9 + 0x22) != 0)
	 ) 
  {
    if (*(short *)((int)piVar9 + 0x22) != 0) {
      *(short *)((int)piVar9 + 0x22) = *(short *)((int)piVar9 + 0x22) + -1;
    }
  }
  else 
  {
	// tw->framesSeekMine
    if (piVar9[0x15] == 0) 
	{
	  // get distance between tracker and the driver being chased
      iVar6 = (*(int *)(iVar8 + 0x2d4) >> 8) - *(int *)(iVar10 + 0x44);
      iVar8 = (*(int *)(iVar8 + 0x2dc) >> 8) - *(int *)(iVar10 + 0x4c);
      piVar9[10] = iVar6 * iVar6 + iVar8 * iVar8;
	  
LAB_800add14:

	  // get direction, given X and Y distance to travel
      sVar3 = ratan2(iVar6,iVar8);
    }
	
	// if seeking mine
    else {
      piVar9[0x15] = piVar9[0x15] + -1;
      iVar8 = *(int *)(*piVar9 + 0x20);
      if (iVar8 != 0) 
	  {
		// Get X and Y differences between two instances
        iVar6 = *(int *)(iVar8 + 0x44) - *(int *)(iVar10 + 0x44);
        iVar8 = *(int *)(iVar8 + 0x4c) - *(int *)(iVar10 + 0x4c);
        goto LAB_800add14;
      }
      sVar3 = *(short *)((int)piVar9 + 0x1e);
      piVar9[0x15] = 0;
    }
    
	// instance -> model -> modelID
	sVar1 = *(short *)(*(int *)(iVar10 + 0x18) + 0x10);
    
	// DYNAMIC_BOMB or DYNAMIC_SHIELD
	if ((sVar1 == 0x3b) || (sVar1 == 0x56)) 
	{
	  // RB_Hazard_InterpolateValue
      sVar3 = FUN_800ada90(
		(int)*(short *)((int)piVar9 + 0x1e),(int)sVar3,4);  
	  *(short *)((int)piVar9 + 0x1e) = sVar3;
      
	  // Sine(angle)
	  iVar8 = FUN_8003d184((int)sVar3);
      
	  // posX += velocity >> 7
	  *(short *)(piVar9 + 4) = (short)((uint)(iVar8 * 3) >> 7);
      
	  // Cosine(angle)
	  iVar8 = FUN_8003d1c0((int)*(short *)((int)piVar9 + 0x1e));
      
	  // posZ += velocity >> 7
	  sVar3 = (short)((uint)(iVar8 * 3) >> 7);
	  *(short *)(piVar9 + 5) = sVar3;
      
	  // if bomb is rolled backwards
	  if ((*(ushort *)((int)piVar9 + 0x16) & 0x20) != 0) {
        *(short *)(piVar9 + 5) = -sVar3;
        *(short *)(piVar9 + 4) = -*(short *)(piVar9 + 4);
      }
    }
	
	// if 0x29 (MISSILE)
    else 
	{
	  // if 10 wumpa were not used
      if ((*(ushort *)((int)piVar9 + 0x16) & 1) == 0) 
	  {
		// RB_Hazard_InterpolateValue
        sVar3 = FUN_800ada90((int)*(short *)((int)piVar9 + 0x1e),(int)sVar3,0x40);  
		*(short *)((int)piVar9 + 0x1e) = sVar3;
        
		// Sine(angle)
		iVar8 = FUN_8003d184((int)sVar3);
        
		// posX += velocity >> 8
		*(short *)(piVar9 + 4) = (short)((uint)(iVar8 * 5) >> 8);
        
		// Cosine(angle)
		iVar8 = FUN_8003d1c0((int)*(short *)((int)piVar9 + 0x1e));
        
		// posZ += velocity >> 8
		uVar5 = (undefined2)((uint)(iVar8 * 5) >> 8);
      }
	  
	  // if 10 wumpa were used
      else 
	  {
		// RB_Hazard_InterpolateValue
        sVar3 = FUN_800ada90((int)*(short *)((int)piVar9 + 0x1e),(int)sVar3,0x80);
		*(short *)((int)piVar9 + 0x1e) = sVar3;
        
		// Sine(angle)
		iVar8 = FUN_8003d184((int)sVar3);
        
		// posX += velocity >> 7
		*(short *)(piVar9 + 4) = (short)((uint)(iVar8 * 3) >> 7);
        
		// Cosine(angle)
		iVar8 = FUN_8003d1c0((int)*(short *)((int)piVar9 + 0x1e));
        
		// posZ += velocity >> 7
		uVar5 = (undefined2)((uint)(iVar8 * 3) >> 7);
      }
	  
	  // posZ += velocity
      *(undefined2 *)(piVar9 + 5) = uVar5;
	  
      *(undefined2 *)(piVar9 + 6) = 0;
      *(undefined2 *)(piVar9 + 7) = 0;
      *(undefined2 *)((int)piVar9 + 0x1a) = *(undefined2 *)((int)piVar9 + 0x1e);
	  
	   // convert 3 rotation shorts into rotation matrix
      FUN_8006c2a4(iVar10 + 0x30,piVar9 + 6);
    }
  }
  
  // instance -> animFrame
  sVar3 = *(short *)(iVar10 + 0x54);
  
  // INSTANCE_GetNumAnimFrames
  iVar8 = FUN_80030f58(iVar10,0);
  
  // if instance is not at end of animation
  if ((int)sVar3 + 1 < iVar8) 
  {
	// increment animation frame
    *(short *)(iVar10 + 0x54) = *(short *)(iVar10 + 0x54) + 1;
  }
  
  // if animation finished
  else 
  {
	// go back to first frame of animation
    *(undefined2 *)(iVar10 + 0x54) = 0;
  }
  
  if (
		(
			// if instance -> model -> modelID == missile
			(*(short *)(*(int *)(iVar10 + 0x18) + 0x10) == 0x29) && 
			
			// numPlyrCurrGame < 2
			((byte)PTR_DAT_8008d2ac[0x1ca8] < 2)
		) && 
		(
			// DAT_800b2ae4
			// ParticleEmitter emSet[]
		
			// Make Instane in Particle Pool
			iVar8 = FUN_80040308(0,*(undefined4 *)(PTR_DAT_8008d2ac + 0x2114),&DAT_800b2ae4),
			iVar8 != 0
		)
	 ) 
  {
	// Position in a particle struct
	  
    *(int *)(iVar8 + 0x24) = *(int *)(iVar10 + 0x44) << 8;
    *(int *)(iVar8 + 0x2c) = *(int *)(iVar10 + 0x48) << 8;
    *(int *)(iVar8 + 0x34) = *(int *)(iVar10 + 0x4c) << 8;
  }
  
  puVar2 = PTR_DAT_8008d2ac;
  
  // posX
  *(int *)(iVar10 + 0x44) =
       *(int *)(iVar10 + 0x44) +
       ((int)*(short *)(piVar9 + 4) * *(int *)(PTR_DAT_8008d2ac + 0x1d04) >> 5);
  
  // posY
  *(int *)(iVar10 + 0x48) =
       *(int *)(iVar10 + 0x48) +
       ((int)*(short *)((int)piVar9 + 0x12) * *(int *)(puVar2 + 0x1d04) >> 5);
  
  // posZ
  *(int *)(iVar10 + 0x4c) =
       *(int *)(iVar10 + 0x4c) + ((int)*(short *)(piVar9 + 5) * *(int *)(puVar2 + 0x1d04) >> 5);
  
  // If this is bomb
  if (*(short *)(*(int *)(iVar10 + 0x18) + 0x10) == 0x3b) 
  {  
	// if bomb is forwards
	if ((*(ushort *)((int)piVar9 + 0x16) & 0x20) == 0) 
	{
	  // rotation
      sVar3 = *(short *)(piVar9 + 6) + 0x200;
    }
    
	// if bomb is backwards
	else 
	{
	  // rotation
      sVar3 = *(short *)(piVar9 + 6) + -0x200;
    }
	
	// rotation
    *(short *)(piVar9 + 6) = sVar3;
	
	 // convert 3 rotation shorts into rotation matrix
    FUN_8006c2a4(iVar10 + 0x30,piVar9 + 6);
  }
  
  local_30 = *(undefined2 *)(iVar10 + 0x44);
  local_2e = *(short *)(iVar10 + 0x48) + -0x40;
  local_2c = *(undefined2 *)(iVar10 + 0x4c);
  local_28 = *(undefined2 *)(iVar10 + 0x44);
  local_26 = *(short *)(iVar10 + 0x48) + 0x100;
  local_24 = *(undefined2 *)(iVar10 + 0x4c);
  DAT_1f80012c = 0x1040;
  DAT_1f800130 = 0;
  DAT_1f80012a = 0x41;
  
  // numPlyrCurrGame < 3
  if ((byte)PTR_DAT_8008d2ac[0x1ca8] < 3) {
    DAT_1f80012a = 0x43;
  }
  
  DAT_1f800134 = **(undefined4 **)(PTR_DAT_8008d2ac + 0x160);
  
  // COLL_SearchTree_FindQuadblock_Touching
  FUN_8001eb0c(&local_30,&local_28,&DAT_1f800108,0);
  
  // RB_MakeInstanceReflective
  FUN_800abab0(&DAT_1f800108,iVar10);
  
  puVar2 = PTR_DAT_8008d2ac;
  
  if ((DAT_1f8002ac & 4) != 0) 
  {
	// negate velocity in all directions
    *(short *)(piVar9 + 4) = -*(short *)(piVar9 + 4);
    *(short *)(piVar9 + 5) = -*(short *)(piVar9 + 5);
    *(short *)((int)piVar9 + 0x12) = -*(short *)((int)piVar9 + 0x12);
	
	// posX += -VelX
    *(int *)(iVar10 + 0x44) =
         *(int *)(iVar10 + 0x44) + ((int)*(short *)(piVar9 + 4) * *(int *)(puVar2 + 0x1d04) >> 5);
    
	// posY += -VelY
	*(int *)(iVar10 + 0x48) =
         *(int *)(iVar10 + 0x48) +
         ((int)*(short *)((int)piVar9 + 0x12) * *(int *)(puVar2 + 0x1d04) >> 5);
    
	// posZ += -VelZ
	*(int *)(iVar10 + 0x4c) =
         *(int *)(iVar10 + 0x4c) + ((int)*(short *)(piVar9 + 5) * *(int *)(puVar2 + 0x1d04) >> 5);
    
	// RB_MovingExplosive_Explode
	FUN_800ae478(param_1,iVar10,piVar9);
    return;
  }
  
  if (DAT_1f80014a == 0) {
    if (DAT_1f800146 == 0) 
	{
	  // hitbox
      local_30 = *(undefined2 *)(iVar10 + 0x44);
      *(undefined2 *)(iVar10 + 0x56) = 0;
      local_2e = *(short *)(iVar10 + 0x48) + -0x900;
      local_2c = *(undefined2 *)(iVar10 + 0x4c);
	  
	  // COLL_SearchTree_FindQuadblock_Touching
      FUN_8001eb0c(&local_30,&local_28,&DAT_1f800108,0);
	  
      if (DAT_1f800146 == 0) goto LAB_800ae42c;
      iVar8 = *(int *)(PTR_DAT_8008d2ac + 0x1d04) << 2;
	  
	  // if instance -> model -> modelID == missile
      if (*(short *)(*(int *)(iVar10 + 0x18) + 0x10) == 0x29) 
	  {
        iVar8 = *(int *)(PTR_DAT_8008d2ac + 0x1d04) << 3;
      }
      
	  iVar8 = (int)*(short *)((int)piVar9 + 0x12) - (iVar8 >> 5);
      *(undefined2 *)((int)piVar9 + 0x12) = (short)iVar8;
      if (iVar8 * 0x10000 >> 0x10 < -0x60) {
        *(undefined2 *)((int)piVar9 + 0x12) = 0xffa0;
      }
    }
    else {
      *(undefined2 *)((int)piVar9 + 0x12) = 0;
	  
	  // DYNAMIC_ROCKET
      if (*(short *)(*(int *)(iVar10 + 0x18) + 0x10) == 0x29) 
	  {
	    // VehPhysForce_RotAxisAngle
        FUN_8005f89c(iVar10 + 0x30,&DAT_1f800178,(int)*(short *)((int)piVar9 + 0x1e));
      }
	  
	  // position
      *(int *)(iVar10 + 0x44) = (int)(short)DAT_1f800124;
      *(int *)(iVar10 + 0x48) = (int)DAT_1f800124._2_2_ + 0x30;
      *(int *)(iVar10 + 0x4c) = (int)DAT_1f800128;
    }
  }
  else 
  {
	// if instance -> model -> modelID
    DAT_1f800114 = *(undefined2 *)(*(int *)(iVar10 + 0x18) + 0x10);
	
	// RB_Hazard_CollLevInst
    iVar8 = FUN_800ad9ac(&DAT_1f800108,param_1);
    
	if (iVar8 == 1) {
      if ((((*DAT_1f800150 & 0x80) != 0) && (iVar8 = *(int *)(DAT_1f800150 + 0x1c), iVar8 != 0)) &&
         ((*(int *)(iVar8 + 0x2c) != 0 && (*(short *)(iVar8 + 0x3c) == 0x70)))) 
	  {
		// RB_Teeth_OpenDoor 
        FUN_800ba220();
      }
      goto LAB_800ae42c;
    }
  }
  
  // RB_Hazard_CollideWithDrivers
  iVar8 = FUN_800ac220(iVar10,(int)*(short *)(piVar9 + 8),0x2400,piVar9[2]);
  
  // if no driver hit
  if (iVar8 == 0) 
  {
	// RB_Hazard_CollideWithBucket, check Mine threadbucket
    iVar8 = FUN_800ac350(iVar10,param_1,*(undefined4 *)(PTR_DAT_8008d2ac + 0x1b7c),
                       (int)*(short *)(piVar9 + 8),0x2400,piVar9[2]);
    
	// if mine was not hit
	if (iVar8 == 0) {
      
	  // instance -> model -> modelID is not bomb
	  if (*(short *)(*(int *)(iVar10 + 0x18) + 0x10) != 0x3b) {
LAB_800ae440:
        if (*(short *)(piVar9 + 8) == 0) {
          return;
        }
        *(short *)(piVar9 + 8) = *(short *)(piVar9 + 8) + -1;
        return;
      }
      
	  // === Assume Bomb ===
	  
	  // RB_Hazard_CollideWithBucket, check Tracking threadbucket
	  iVar8 = FUN_800ac350(iVar10,param_1,*(undefined4 *)(PTR_DAT_8008d2ac + 0x1ba4),
                         (int)*(short *)(piVar9 + 8),0x2400,piVar9[2]);
      
	  // if no collision
	  if (iVar8 == 0) {
        if ((*(ushort *)((int)piVar9 + 0x16) & 2) == 0) goto LAB_800ae440;
      }
      
	  // if bomb collides with Tracker
	  else 
	  {
		// instance -> model -> modelID != missile
        if (*(short *)(*(int *)(iVar8 + 0x18) + 0x10) != 0x29) 
		{
		  // quit, warpball collisions dont matter
          return;
        }
		
		// this must be a missile
		
		// instance -> thread -> funcThCollide
        pcVar4 = *(code **)(*(int *)(iVar8 + 0x6c) + 0x28);
		
		// execute funcThCollide
        (*pcVar4)(*(int *)(iVar8 + 0x6c),param_1,pcVar4,0);
      }
    }
    
	// if mine was hit
	else 
	{
	  // instance -> thread -> funcThCollide
      pcVar4 = *(code **)(*(int *)(iVar8 + 0x6c) + 0x28);
	  
	  // execute funcThCollide
      (*pcVar4)(*(int *)(iVar8 + 0x6c),param_1,pcVar4,0);
    }
  }
  
  // if driver was hit
  else {
    
	// icon damage timer, draw icon as red
	*(undefined4 *)(*(int *)(*(int *)(iVar8 + 0x6c) + 0x30) + 0x4ac) = 0x1e;
	
	// thread -> inst -> object -> offset0x0 == ???
    if (*(int *)(*(int *)(iVar8 + 0x6c) + 0x30) == *piVar9) 
	{
	  // flags
      *(ushort *)((int)piVar9 + 0x16) = *(ushort *)((int)piVar9 + 0x16) | 0x10;
    }
  }
LAB_800ae42c:

  // RB_MovingExplosive_Explode
  FUN_800ae478(param_1,iVar10,piVar9);
  return;
}

// RB_MovingExplosive_Explode
void FUN_800ae478(int param_1,int param_2,int *param_3)
{
  undefined4 uVar1;
  int iVar2;
  
  // if instance -> model -> modelID == bomb
  if (*(short *)(*(int *)(param_2 + 0x18) + 0x10) == 0x3b) {
    
	// bomb explode
	uVar1 = 0x49;
	
    *(undefined4 *)(param_3[1] + 0x10) = 0;
  }
  
  // missile
  else 
  {
    iVar2 = *param_3;
    
	if (iVar2 != 0) 
	{
	  // remove 2D square-target being drawn on the player's screen 
      *(uint *)(iVar2 + 0x2c8) = *(uint *)(iVar2 + 0x2c8) & 0xfbffffff;
    }
    
	// missile explode
	uVar1 = 0x4c;
  }
  
  // play explosion sound
  FUN_8002f0dc(uVar1,param_2);
  
  // stop audio of rolling,
  // offset 0x24 of object
  FUN_8002e724(param_3 + 9);
  
  // RB_Burst_Init
  FUN_800b2154(param_2);
  
  // This thread is now dead
  *(uint *)(param_1 + 0x1c) = *(uint *)(param_1 + 0x1c) | 0x800;
  return;
}

// RB_Warpball_FadeAway
void FUN_800ae524(int param_1)
{
  short sVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  
  // get object from thread
  piVar3 = *(int **)(param_1 + 0x30);
  
  // get instance from thread
  iVar4 = *(int *)(param_1 + 0x34);
  
  // frame counter more than 5
  if (5 < (uint)piVar3[0xc]) 
  {
    iVar4 = *piVar3;
    
	if (iVar4 != 0) 
	{
	  // remove 2D square-target being drawn on the player's screen 
      *(uint *)(iVar4 + 0x2c8) = *(uint *)(iVar4 + 0x2c8) & 0xfbffffff;
    }
	
	// remove active wrapball flag
    *(uint *)PTR_DAT_8008d2ac = *(uint *)PTR_DAT_8008d2ac & 0xffffefff;
	
	// This thread is now dead
    *(uint *)(param_1 + 0x1c) = *(uint *)(param_1 + 0x1c) | 0x800;
    return;
  }
  
  // frame counter
  sVar1 = *(short *)(piVar3 + 0xc);
  
  iVar2 = (int)sVar1 * 6;
  
  // set scale (x, y, z)
  *(undefined2 *)(iVar4 + 0x1c) = *(undefined2 *)(&DAT_800b2c88 + iVar2);
  *(undefined2 *)(iVar4 + 0x1e) = *(undefined2 *)(&DAT_800b2c8a + iVar2);
  *(undefined2 *)(iVar4 + 0x20) = *(undefined2 *)(&DAT_800b2c8c + iVar2);
  
  *(int *)(iVar4 + 0x48) = piVar3[0xe] + *(int *)(&DAT_800b2cac + (int)sVar1 * 4);
  
  // increment counter
  piVar3[0xc] = piVar3[0xc] + 1;
  
  return;
}

// RB_Warpball_Death
void FUN_800ae604(int param_1)
{
  int iVar1;
  
  // get object from thread
  iVar1 = *(int *)(param_1 + 0x30);
  
  *(undefined4 *)(iVar1 + 0x38) = *(undefined4 *)(*(int *)(param_1 + 0x34) + 0x48);
  *(undefined2 *)(*(int *)(iVar1 + 0xc) + 0x10) = 0;
  *(undefined4 *)(iVar1 + 0x30) = 0;
  
  // play sound of warpball death
  FUN_8002f0dc(0x4f);
  
  // stop audio of moving
  FUN_8002e724(iVar1 + 0x24);
  
  // ThTick_SetAndExec RB_Warpball_FadeAway
  FUN_800716ec(param_1,&FUN_800ae524);
  return;
}

// RB_Warpball_NewPathNode
// param1 position data from LEV path
// param2 driver object
int FUN_800ae668(int param_1,int param_2)
{
  byte bVar1;
  bool bVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  
  bVar2 = false;
  
  // if no driver is chased
  if (param_2 == 0) 
  {
LAB_800ae750:
    return *(int *)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0x14c) + (uint)*(byte *)(param_1 + 8) * 0xc
    ;
  }
  
  // pathPoint -> next index
  uVar4 = (uint)*(byte *)(param_1 + 9);
  
  // if driver is not near that point
  if ((uint)*(byte *)(param_2 + 0x494) != uVar4) 
  {
	// if next point is valid
    if (*(byte *)(param_1 + 9) != 0xff) 
	{
      iVar5 = 0;
      iVar3 = param_1;
      do 
	  {
		// path index
        if (*(char *)(iVar3 + 9) == -1) {
          bVar1 = *(byte *)(iVar3 + 8);
        }
		
		// path index
        else {
          bVar1 = *(byte *)(iVar3 + 9);
        }
		
		// path node
        iVar3 = *(int *)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0x14c) + (uint)bVar1 * 0xc;
        iVar5 = iVar5 + 1;
		
		// compare path index
        if (*(char *)(param_2 + 0x494) == *(char *)(iVar3 + 8)) {
          bVar2 = true;
          break;
        }
		
      } while (iVar5 * 0x10000 >> 0x10 < 3);
    }
    if (!bVar2) goto LAB_800ae750;
    uVar4 = (uint)*(byte *)(param_1 + 9);
  }
  
  // new path node
  return *(int *)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0x14c) + uVar4 * 0xc;
}

// RB_Warpball_Start
void FUN_800ae778(undefined4 *param_1)
{
  undefined4 uVar1;
  int iVar2;
  
  iVar2 = 0;
  uVar1 = param_1[0xf];
  do 
  {
	// RB_Warpball_NewPathNode
    uVar1 = FUN_800ae668(uVar1,*param_1);
    iVar2 = iVar2 + 1;
  } while (iVar2 * 0x10000 < 1);
  
  // node
  param_1[0xf] = uVar1;
  
  // RB_Warpball_NewPathNode
  uVar1 = FUN_800ae668(uVar1,*param_1);
  param_1[0x10] = uVar1;
  
  return;
}

// RB_Warpball_GetDriverTarget
// param1 - warpball object
// param2 - warpball instance
int FUN_800ae7dc(int param_1,int param_2)
{
  ushort uVar1;
  int iVar2;
  short *psVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  short *psVar8;
  int iVar9;
  int iVar10;
  undefined4 local_30;
  undefined4 local_28;
  short local_24;
  
  iVar10 = 0;
  
  // if 10 wumpa fruit were not used
  if ((*(ushort *)(param_1 + 0x16) & 1) == 0) 
  {
	// loop counter
    iVar7 = 0;
    
	iVar6 = 0;
	
	// for iVar7 = 0; iVar7 < 8; iVar7++
    do 
	{
	  // check next driver until you get the driver
	  // farthest in the lead, that has not finished race
      iVar6 = *(int *)(PTR_DAT_8008d2ac + (iVar6 >> 0xe) + 0x250c);
      
	  if (
			(
				// if driver is valid
				(iVar6 != 0) && 
				
				// if driver is not the same as driver that fired warpball
				(iVar6 != *(int *)(param_1 + 4))
			) &&
			
			// if the race is not over for this driver
			((*(uint *)(iVar6 + 0x2c8) & 0x2000000) == 0)
		 ) 
	  {
        return iVar6;
      }
	  
	  // increment loop counter
      iVar7 = iVar7 + 1;
	
	  // loop index << 0xe
      iVar6 = iVar7 * 0x10000;
    
	} while (iVar7 * 0x10000 >> 0x10 < 8);
  }
  
  // if 10 wumpa fruit were used
  else 
  {
	// start of lev->path
    iVar6 = *(int *)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0x14c);
	
	// node1
    psVar8 = (short *)(iVar6 + (uint)*(byte *)(*(int *)(param_1 + 0x3c) + 8) * 0xc);
    
	// node2
	psVar3 = (short *)(iVar6 + (uint)*(byte *)(psVar8 + 4) * 0xc);
    
	uVar1 = *(ushort *)(iVar6 + 6);
    iVar9 = (uint)uVar1 * 8;
    
	// direction from node1 to node2
	local_28 = CONCAT22(psVar8[1] - psVar3[1],*psVar8 - *psVar3);
    local_24 = psVar8[2] - psVar3[2];
    
	// MATH_VectorNormalize
	FUN_8003d378(&local_28);
	
    gte_ldR11R12(local_28);
    gte_ldR13R21((int)local_24);
	
    local_30 = CONCAT22(
		*(short *)(param_2 + 0x48) - psVar8[1],
		*(short *)(param_2 + 0x44) - *psVar8);
	
    gte_ldVXY0(2,0,local_30);
    gte_ldVZ0(2,0x800,(int)(short)(*(short *)(param_2 + 0x4c) - psVar8[2]));
    
	copFunction(2,0x406012);
    
	iVar4 = getCopReg(2,0xc800);
    getCopReg(2,0xd000);
    iVar6 = 0x7fffffff;
	
	// loop counter
    iVar7 = 0;
	
    iVar4 = (uint)(ushort)psVar8[3] * 8 + (iVar4 >> 0xc) + 0x200;
    if (uVar1 == 0) {
      trap(0x1c00);
    }
    if ((iVar9 == -1) && (iVar4 == -0x80000000)) {
      trap(0x1800);
    }
    iVar2 = 0;
	
	// for iVar7 = 0; iVar7 < 8; iVar7++
    do 
	{
	  // pointer to structure of each player
      iVar5 = *(int *)(PTR_DAT_8008d2ac + (iVar2 >> 0x10) * 4 + 0x24ec);
	  
      if (
			(
				// if pointer is not nullptr
				(iVar5 != 0) && 
				((*(uint *)(param_1 + 0x34) & 1 << (iVar2 >> 0x10 & 0x1fU)) == 0)
			) &&
			(
				(
					// If the race is not over for this player
					(*(uint *)(iVar5 + 0x2c8) & 0x2000000) == 0 && 
					
					// If you are not being mask-grabbed
					(*(char *)(iVar5 + 0x376) != '\x05')
				)
			)
		  ) 
	  {
        iVar2 = iVar4 % iVar9 - *(int *)(iVar5 + 0x488);
        if (iVar2 < 0) {
          iVar2 = iVar2 + iVar9;
        }
        if (iVar2 < iVar6) {
          iVar6 = iVar2;
          iVar10 = iVar5;
        }
      }
	  
	  // increment loop counter
      iVar7 = iVar7 + 1;
      iVar2 = iVar7 * 0x10000;
    } while (iVar7 * 0x10000 >> 0x10 < 8);
  }
  return iVar10;
}

// RB_Warpball_SetTargetDriver
void FUN_800aeaac(int *param_1)

{
  undefined *puVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int local_20;
  int local_1c;
  
  // driver being chased
  iVar2 = *param_1;
  
  // if driver is valid
  if (iVar2 != 0) 
  {
	// driver -> distanceToFinish
    iVar5 = *(int *)(iVar2 + 0x488);
	
	// path node
    iVar2 = *(int *)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0x14c) +
            (uint)*(byte *)(iVar2 + 0x495) * 0xc;
    
	iVar4 = iVar2;
    
	while ((iVar3 = iVar2, puVar1 = PTR_DAT_8008d2ac,
           
		   // distance is less than path node distance
		   iVar5 <= (int)((uint)*(ushort *)(iVar3 + 6) << 3) &&
		   
		   // path node is not first node
           (iVar3 != *(int *)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0x14c)))) 
	{
	  // RB_Warpball_NewPathNode
      iVar2 = FUN_800ae668(iVar3,*param_1);
      iVar4 = iVar3;
    }
    iVar2 = 0;
    local_1c = 0;
    local_20 = param_1[0xf];
    if ((*(ushort *)((int)param_1 + 0x16) & 4) == 0) {
      iVar5 = 0;
      do {
        iVar5 = *(int *)((int)&local_20 + (iVar5 >> 0xe));
        if (iVar5 != 0) {
          iVar3 = 0;
          do {
            if (iVar5 == iVar4) {
              *(ushort *)((int)param_1 + 0x16) = *(ushort *)((int)param_1 + 0x16) & 0xfff7 | 4;
              break;
            }
            if (*(byte *)(iVar5 + 0xb) != 0xff) 
			{
			  // path node
              local_1c = *(int *)(*(int *)(puVar1 + 0x160) + 0x14c) +
                         (uint)*(byte *)(iVar5 + 0xb) * 0xc;
            }
            iVar3 = iVar3 + 1;
			
			// path node
            iVar5 = *(int *)(*(int *)(puVar1 + 0x160) + 0x14c) + (uint)*(byte *)(iVar5 + 10) * 0xc;
          
		  } while (iVar3 * 0x10000 >> 0x10 < 3);
        }
        iVar2 = iVar2 + 1;
      } while ((iVar2 * 0x10000 >> 0x10 < 2) &&
              (iVar5 = iVar2 * 0x10000, (*(ushort *)((int)param_1 + 0x16) & 4) == 0));
    }
    
	// path node
	iVar2 = param_1[0xf];
	
    iVar5 = 0;
    do {
      if (iVar2 == iVar4) {
        *(ushort *)((int)param_1 + 0x16) = *(ushort *)((int)param_1 + 0x16) & 0xfff7 | 4;
        return;
      }
	  
	  // RB_Warpball_NewPathNode
      iVar2 = FUN_800ae668(iVar2,*param_1);
	  
      iVar5 = iVar5 + 1;
    } while (iVar5 * 0x10000 >> 0x10 < 3);
  }
  return;
}

// RB_Warpball_SeekDriver
// param1 warpball object
void FUN_800aece0(undefined4 *param_1,uint param_2,int param_3)

{
  int iVar1;
  
  if (
		// if driver is valid
		(param_3 != 0) && 
		
		// if path node index is valid
		((param_2 & 0xff) != 0xff)
	  ) 
  {
	// pointer to path node
    iVar1 = *(int *)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0x14c) + (param_2 & 0xff) * 0xc;
    
	while (
			// driver distanceToFinish < pathNode -> distanceToFinish
			(*(int *)(param_3 + 0x488) <= (int)((uint)*(ushort *)(iVar1 + 6) << 3) &&
           
			// node is not first node
			(iVar1 != *(int *)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0x14c))
			)
		   ) 
	{
	  // RB_Warpball_NewPathNode
      iVar1 = FUN_800ae668(iVar1,*param_1);
    }
	
	// path index = pathPtr2 - pathPtr1
    *(char *)(param_1 + 0x11) =
         (char)((iVar1 - *(int *)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0x14c)) * -0x55555555 >> 2);
  }
  return;
}

// RB_Warpball_TurnAround
void FUN_800aede0(int param_1)

{
  ushort uVar1;
  undefined *puVar2;
  short sVar3;
  undefined2 uVar4;
  int *piVar5;
  int iVar6;
  
  // thread -> object
  piVar5 = *(int **)(param_1 + 0x30);
  
  uVar1 = *(ushort *)((int)piVar5 + 0x16);
  
  // thread -> instance
  iVar6 = *(int *)(param_1 + 0x34);
  
  if (
		// if not snap to point???
		((uVar1 & 0x100) != 0) || 
		
		// if no driver is being chased
		(*piVar5 == 0)
	  ) 
  {
    if ((uVar1 & 4) != 0) {
      *(ushort *)((int)piVar5 + 0x16) = uVar1 & 0xfffb | 0x208;
    }
	
	// turn around
	// velX = -velX
	// velZ = -velZ
	// velY = -velY
    *(short *)(piVar5 + 4) = -*(short *)(piVar5 + 4);
    *(short *)(piVar5 + 5) = -*(short *)(piVar5 + 5);
    *(short *)((int)piVar5 + 0x12) = -*(short *)((int)piVar5 + 0x12);
	
    puVar2 = PTR_DAT_8008d2ac;
	
	// posX += velX
    *(int *)(iVar6 + 0x44) =
         *(int *)(iVar6 + 0x44) +
         ((int)*(short *)(piVar5 + 4) * *(int *)(PTR_DAT_8008d2ac + 0x1d04) >> 5);
		 
	// posY += velY
    *(int *)(iVar6 + 0x48) =
         *(int *)(iVar6 + 0x48) +
         ((int)*(short *)((int)piVar5 + 0x12) * *(int *)(puVar2 + 0x1d04) >> 5);
		 
	// posZ += velZ
    *(int *)(iVar6 + 0x4c) =
         *(int *)(iVar6 + 0x4c) + ((int)*(short *)(piVar5 + 5) * *(int *)(puVar2 + 0x1d04) >> 5);
    
	// increment counter
	sVar3 = *(short *)((int)piVar5 + 0x52) + 1;
    *(short *)((int)piVar5 + 0x52) = sVar3;
    
	if (
			// if count too high
			(0x78 < sVar3) || 
			
			// pointer to driver being chased,
			// is null, so warpball is chasing nobody
			(*piVar5 == 0)
		) 
	{
      *(undefined4 *)(piVar5[1] + 0x10) = 0;
	  
	  // play sound warpball death
      FUN_8002f0dc(0x4f,iVar6);
      
	  // RB_Warpball_Death
	  FUN_800ae604(param_1);
    }
	
	// if attempted to turn around 3 times
    if ((*(ushort *)((int)piVar5 + 0x52) & 3) == 0) 
	{
	  // move backwards on path
		
	  // start = end (current)
      piVar5[0x10] = piVar5[0xf];
	  
	  // set new end to 10 path indices ahead of current
      piVar5[0xf] = *(int *)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0x14c) +
                    (uint)*(byte *)(piVar5[0xf] + 10) * 0xc;
    }
	
	// rotation
    uVar4 = ratan2((int)*(short *)piVar5[0xf] - *(int *)(iVar6 + 0x44),
                         (int)((short *)piVar5[0xf])[2] - *(int *)(iVar6 + 0x4c));
		
	// rotation
    *(undefined2 *)((int)piVar5 + 0x1a) = uVar4;
  }
  return;
}

// RB_Warpball_ThTick
void FUN_800aef9c(int param_1)

{
  ushort uVar1;
  bool bVar2;
  undefined *puVar3;
  short sVar4;
  undefined2 uVar5;
  int iVar6;
  int iVar7;
  undefined4 uVar8;
  code *pcVar9;
  uint uVar10;
  int *piVar11;
  short sVar12;
  ushort uVar13;
  short *psVar14;
  int iVar15;
  short *psVar16;
  int iVar17;
  int iVar18;
  int iVar19;
  undefined2 local_48;
  short local_46;
  undefined2 local_44;
  undefined2 local_40;
  short local_3e;
  undefined2 local_3c;
  int local_38;
  int local_34;
  int local_30;
  
  // thread -> instance
  iVar17 = *(int *)(param_1 + 0x34);
  
  // thread -> object
  piVar11 = *(int **)(param_1 + 0x30);
  
  // save short inst position in object
  *(undefined2 *)(piVar11 + 0x13) = *(undefined2 *)(iVar17 + 0x44);
  *(undefined2 *)((int)piVar11 + 0x4e) = *(undefined2 *)(iVar17 + 0x48);
  *(undefined2 *)(piVar11 + 0x14) = *(undefined2 *)(iVar17 + 0x4c);
  
  // instance -> animFrame
  sVar12 = *(short *)(iVar17 + 0x54);
  
  // INSTANCE_GetNumAnimFrames
  iVar6 = FUN_80030f58(iVar17,0);
  
  // if animation is finished
  if ((int)sVar12 + 1 < iVar6) 
  {
	// increment animFrame
    *(short *)(iVar17 + 0x54) = *(short *)(iVar17 + 0x54) + 1;
  }
  
  // if animation is finished
  else 
  {
	// restart animation
    *(undefined2 *)(iVar17 + 0x54) = 0;
  }
  
  // If driver pointer is not zero
  if (*piVar11 != 0) 
  {
	
    if (
			// if you are being mask-grabbed
			(*(char *)(*piVar11 + 0x376) == '\x05') && 
		
			((*(ushort *)((int)piVar11 + 0x16) & 4) != 0)
		) 
	{
      *(ushort *)((int)piVar11 + 0x16) = *(ushort *)((int)piVar11 + 0x16) & 0xfffb | 0x18;
      
	  // pointer to desired position on path, given path index
	  iVar6 = *(int *)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0x14c) +
              (uint)*(byte *)((int)piVar11 + 0x45) * 0xc;
      piVar11[0xf] = iVar6;
	  
	  // RB_Warpball_NewPathNode
      iVar6 = FUN_800ae668(iVar6,*piVar11);
      piVar11[0x10] = iVar6;
	  
	  // RB_Warpball_GetDriverTarget
      iVar6 = FUN_800ae7dc(piVar11,iVar17);
      
	  // set driver being chased by warpball
	  *piVar11 = iVar6;
      
	  // RB_Warpball_SetTargetDriver
	  FUN_800aeaac(piVar11);
    }
	
    if ((*(ushort *)((int)piVar11 + 0x16) & 0x204) == 0) 
	{
	  // RB_Warpball_GetDriverTarget
      iVar6 = FUN_800ae7dc(piVar11,iVar17);
      
	  // set driver being chased by warpball
	  *piVar11 = iVar6;
      
	  // if driver exists
	  if (iVar6 != 0) 
	  {
		// RB_Warpball_SetTargetDriver
        FUN_800aeaac(piVar11);
      }
    }
  }
  
  // get driver the warpball is chasing
  iVar6 = *piVar11;
  
  *(ushort *)((int)piVar11 + 0x16) = *(ushort *)((int)piVar11 + 0x16) & 0xfdff;
  
  // if no driver is bein chased
  if (iVar6 == 0) 
  {
LAB_800af580:
    puVar3 = PTR_DAT_8008d2ac;
	
	// move in the direction the warpball was shot in
	
	// increase posX by velX
    *(int *)(iVar17 + 0x44) =
         *(int *)(iVar17 + 0x44) +
         ((int)*(short *)(piVar11 + 4) * *(int *)(PTR_DAT_8008d2ac + 0x1d04) >> 5);
    
	// increase posY by velY
	*(int *)(iVar17 + 0x48) =
         *(int *)(iVar17 + 0x48) +
         ((int)*(short *)((int)piVar11 + 0x12) * *(int *)(puVar3 + 0x1d04) >> 5);
    
	// increase posZ by velZ
	*(int *)(iVar17 + 0x4c) =
         *(int *)(iVar17 + 0x4c) + ((int)*(short *)(piVar11 + 5) * *(int *)(puVar3 + 0x1d04) >> 5);
  }
  else 
  {
	// get distance from tracker to target
    iVar19 = (*(int *)(iVar6 + 0x2d4) >> 8) - *(int *)(iVar17 + 0x44);
    iVar18 = (*(int *)(iVar6 + 0x2dc) >> 8) - *(int *)(iVar17 + 0x4c);
    iVar15 = (*(int *)(iVar6 + 0x2d8) >> 8) - *(int *)(iVar17 + 0x48);
    iVar7 = iVar19 * iVar19 + iVar18 * iVar18;
    
	// save distance
	piVar11[10] = iVar7;
	
	// RB_GetThread_ClosestTracker
    uVar8 = FUN_800b28c0(iVar6);
	
	// give tracker thread to driver
    *(undefined4 *)(*piVar11 + 0x4a4) = uVar8;
	
    if ((piVar11[5] & 0xc0000U) != 0) {
      sVar12 = 0x100;
      
	  if ((*(ushort *)((int)piVar11 + 0x16) & 4) == 0) 
	  {
		// pointer to position on path
        psVar16 = (short *)piVar11[0xf];
		
		// distance from instance to next point
        iVar19 = (int)*psVar16 - *(int *)(iVar17 + 0x44);
        iVar18 = (int)psVar16[2] - *(int *)(iVar17 + 0x4c);
        iVar15 = (int)psVar16[1] - *(int *)(iVar17 + 0x48);
		
		// distance to next point
        iVar7 = iVar19 * iVar19 + iVar18 * iVar18;
		
		// low distance
        if (iVar7 < 0x4000) 
		{
		  // snap to next point???
          *(ushort *)((int)piVar11 + 0x16) = *(ushort *)((int)piVar11 + 0x16) & 0xfff7 | 0x100;
        }
        
		else {
          sVar12 = 0x100;
          if (iVar7 < 0x24000) {
            sVar12 = 0x400;
          }
        }
      }
      if ((iVar7 < 0x90000) &&
         (iVar6 = 0x400 - (iVar7 >> 9), sVar12 = (short)iVar6, iVar6 * 0x10000 >> 0x10 < 0x100)) {
        sVar12 = 0x100;
      }
      if (0 < *(short *)(piVar11 + 8)) {
        sVar12 = 0x40;
      }
      sVar4 = ratan2(iVar19,iVar18);
      *(undefined2 *)(piVar11 + 6) = 0;
	  
	  // RB_Hazard_InterpolateValue
      uVar5 = FUN_800ada90((int)*(short *)((int)piVar11 + 0x1a),(int)sVar4,(int)sVar12);
      *(undefined2 *)((int)piVar11 + 0x1a) = uVar5;
      
	  *(undefined2 *)(piVar11 + 7) = 0;
      
	  // Sine(angle)
	  iVar6 = FUN_8003d184((int)*(short *)((int)piVar11 + 0x1a));
      
	  *(short *)(piVar11 + 4) = (short)((uint)(iVar6 * 7) >> 8);
      
	  // Cosine(angle)
	  iVar6 = FUN_8003d1c0((int)*(short *)((int)piVar11 + 0x1a));
      
	  *(short *)(piVar11 + 5) = (short)((uint)(iVar6 * 7) >> 8);
      
	  if (iVar15 < 1) {
        if (iVar15 < 0) {
          iVar6 = (uint)*(ushort *)((int)piVar11 + 0x12) -
                  ((*(int *)(PTR_DAT_8008d2ac + 0x1d04) << 2) >> 5);
          *(undefined2 *)((int)piVar11 + 0x12) = (short)iVar6;
          if (iVar6 * 0x10000 >> 0x10 < iVar15) {
            *(undefined2 *)((int)piVar11 + 0x12) = (short)iVar15;
          }
          uVar5 = 0xffa0;
          if (*(short *)((int)piVar11 + 0x12) < -0x60) goto LAB_800af34c;
        }
      }
      else {
        iVar6 = (uint)*(ushort *)((int)piVar11 + 0x12) +
                ((*(int *)(PTR_DAT_8008d2ac + 0x1d04) << 2) >> 5);
        *(undefined2 *)((int)piVar11 + 0x12) = (short)iVar6;
        if (iVar15 < iVar6 * 0x10000 >> 0x10) {
          *(undefined2 *)((int)piVar11 + 0x12) = (short)iVar15;
        }
        if (0x60 < *(short *)((int)piVar11 + 0x12)) {
          uVar5 = 0x60;
LAB_800af34c:
          *(undefined2 *)((int)piVar11 + 0x12) = uVar5;
        }
      }
      goto LAB_800af580;
    }
	
	// path nodes
    psVar16 = (short *)piVar11[0x10];
    psVar14 = (short *)piVar11[0xf];
	
	// distance
    local_38 = (int)*psVar16 - (int)*psVar14;
    local_34 = (int)psVar16[1] - (int)psVar14[1];
    local_30 = (int)psVar16[2] - (int)psVar14[2];
	
	// distance
    iVar6 = FUN_8006c618(local_38 * local_38 + local_34 * local_34 + local_30 * local_30);
	
    iVar7 = piVar11[0xb] + (*(int *)(PTR_DAT_8008d2ac + 0x1d04) * 0x70 >> 5);
    if (iVar6 <= iVar7) {
      iVar7 = iVar7 - iVar6;
      do {
        psVar14 = psVar16;
		
		// RB_Warpball_NewPathNode
        psVar16 = (short *)FUN_800ae668(psVar14,*piVar11);
		
		// distance
        local_38 = (int)*psVar16 - (int)*psVar14;
        local_34 = (int)psVar16[1] - (int)psVar14[1];
        local_30 = (int)psVar16[2] - (int)psVar14[2];
		
		// distance
        iVar6 = FUN_8006c618(local_38 * local_38 + local_34 * local_34 + local_30 * local_30);
        bVar2 = iVar6 <= iVar7;
        iVar7 = iVar7 - iVar6;
      } while (bVar2);
      iVar7 = iVar7 + iVar6;
    }
    piVar11[0xb] = iVar7;
	
	// path nodes
    *(short **)(piVar11 + 0xf) = psVar14;
    *(short **)(piVar11 + 0x10) = psVar16;
	
    if (iVar6 == 0) {
      iVar15 = 0;
    }
    else 
	{
	  // percentage between points
      iVar15 = (iVar7 << 0xc) / iVar6;
	  
      if (iVar6 == 0) {
        trap(0x1c00);
      }
      if ((iVar6 == -1) && (iVar7 << 0xc == -0x80000000)) {
        trap(0x1800);
      }
    }
    
	// position = path node + distance * percentage
	*(int *)(iVar17 + 0x44) = (int)*psVar14 + (local_38 * iVar15 >> 0xc);
    *(int *)(iVar17 + 0x48) = (int)psVar14[1] + (local_34 * iVar15 >> 0xc);
    *(int *)(iVar17 + 0x4c) = (int)psVar14[2] + (local_30 * iVar15 >> 0xc);
    
	// adjust rotation, given distX and distZ
	uVar8 = ratan2(local_38,local_30);
    *(undefined2 *)((int)piVar11 + 0x1a) = (short)uVar8;
	
	// Sine(angle)
    iVar6 = FUN_8003d184(uVar8);
    
	// velX
	*(short *)(piVar11 + 4) = (short)((uint)(iVar6 * 7) >> 8);
    
	// Cosine(angle)
	iVar6 = FUN_8003d1c0(uVar8);
    
	// velZ
	*(short *)(piVar11 + 5) = (short)((uint)(iVar6 * 7) >> 8);
    
	// velY
	*(undefined2 *)((int)piVar11 + 0x12) = 0;
  }
  
  // PlaySound3D_Flags
  // warpball moving
  FUN_8002f31c(piVar11 + 9,0x4e,iVar17);
  
  local_48 = *(undefined2 *)(iVar17 + 0x44);
  local_46 = *(short *)(iVar17 + 0x48) + -0x80;
  local_44 = *(undefined2 *)(iVar17 + 0x4c);
  local_40 = *(undefined2 *)(iVar17 + 0x44);
  local_3e = *(short *)(iVar17 + 0x48) + 0x80;
  local_3c = *(undefined2 *)(iVar17 + 0x4c);
  DAT_1f80012c = 0x1040;
  DAT_1f800130 = 0;
  
  // If you have 3 or 4 screens
  DAT_1f80012a = 0x41;
  
  // numPlyrCurrGame < 3
  if ((byte)PTR_DAT_8008d2ac[0x1ca8] < 3) {
    DAT_1f80012a = 0x43;
  }
  
  DAT_1f800134 = **(undefined4 **)(PTR_DAT_8008d2ac + 0x160);
  
  // COLL_SearchTree_FindQuadblock_Touching
  FUN_8001eb0c(&local_48,&local_40,&DAT_1f800108,0);
  
  // RB_MakeInstanceReflective
  FUN_800abab0(&DAT_1f800108,iVar17);
  
  if ((DAT_1f8002ac & 4) != 0) 
  {
	// RB_Warpball_TurnAround
    FUN_800aede0(param_1);
  }
  
  if (DAT_1f80014a != 0) {
    DAT_1f800114 = 0x36;
	
	// RB_Hazard_CollLevInst
    iVar6 = FUN_800ad9ac(&DAT_1f800108,param_1);
    
	if (iVar6 == 1) 
	{
	  // RB_Warpball_TurnAround
      FUN_800aede0(param_1);
    }
  }
  if (DAT_1f800146 == 0) 
  {
	// hitbox
    local_48 = *(undefined2 *)(iVar17 + 0x44);
    local_46 = *(short *)(iVar17 + 0x48) + -0x900;
    local_44 = *(undefined2 *)(iVar17 + 0x4c);
	
	// COLL_SearchTree_FindQuadblock_Touching
    FUN_8001eb0c(&local_48,&local_40,&DAT_1f800108,0);
	
    if (DAT_1f800146 != 0) {
      *(ushort *)((int)piVar11 + 0x16) = *(ushort *)((int)piVar11 + 0x16) | 0x100;
      if (*(char *)(DAT_1f800188 + 0x3e) != -1) {
        *(char *)((int)piVar11 + 0x45) = *(char *)(DAT_1f800188 + 0x3e);
      }
      if (DAT_1f800146 != 0) goto LAB_800af82c;
    }
    if (((*(ushort *)((int)piVar11 + 0x16) & 0xc) != 0) || (*piVar11 == 0)) 
	{
	  // RB_Warpball_TurnAround
      FUN_800aede0(param_1);
    }
  }
  else {
    *(ushort *)((int)piVar11 + 0x16) = *(ushort *)((int)piVar11 + 0x16) | 0x100;
    if (*(char *)(DAT_1f800188 + 0x3e) != -1) {
      *(char *)((int)piVar11 + 0x45) = *(char *)(DAT_1f800188 + 0x3e);
    }
    *(undefined2 *)((int)piVar11 + 0x12) = 0;
    if (((*(ushort *)((int)piVar11 + 0x16) & 0xc) != 0) &&
       (*(int *)(iVar17 + 0x48) < (int)DAT_1f800124._2_2_)) {
      *(int *)(iVar17 + 0x48) = (int)DAT_1f800124._2_2_;
      *(char *)(iVar17 + 0x50) = *(char *)(DAT_1f800188 + 0x14) + -1;
    }
  }
LAB_800af82c:
  if (
		(DAT_800b2c84 != 0) && 
		
		// if particle effect
		(piVar11[3] != 0)
	 ) 
  {
	// update particle effect that surrounds warpball
    *(int *)(piVar11[3] + 0x24) = *(int *)(iVar17 + 0x44) << 8;
    *(int *)(piVar11[3] + 0x2c) = (*(int *)(iVar17 + 0x48) + (uint)DAT_800b2c84) * 0x100;
    *(int *)(piVar11[3] + 0x34) = *(int *)(iVar17 + 0x4c) << 8;
    uVar10 = (uint)DAT_800b2c84;
    *(int *)(piVar11[3] + 0x3c) = uVar10 << 8;
    *(int *)(piVar11[3] + 0x44) = uVar10 * 0xc0;
    *(int *)(piVar11[3] + 0x4c) = uVar10 << 7;
    *(char *)(piVar11[3] + 0x18) = *(char *)(iVar17 + 0x50) + '\x01';
    *(undefined2 *)(piVar11[3] + 0x10) = 0xffff;
  }
  
  // RB_Hazard_CollideWithDrivers
  iVar6 = FUN_800ac220(iVar17,(int)*(short *)(piVar11 + 8),0x9000,piVar11[2]);
  
  // if no driver was hit
  if (iVar6 == 0) 
  {
	// RB_Hazard_CollideWithBucket, check Mine threadbucket
    iVar6 = FUN_800ac350(iVar17,param_1,*(undefined4 *)(PTR_DAT_8008d2ac + 0x1b7c),
                       (int)*(short *)(piVar11 + 8),0x2400,piVar11[2]);
    
	// if mine was hit by mine
	if (iVar6 != 0) 
	{
	  // Get OnDestroy
      pcVar9 = *(code **)(*(int *)(iVar6 + 0x6c) + 0x28);
	  
	  // destroy the mine
      (*pcVar9)(*(int *)(iVar6 + 0x6c),param_1,pcVar9,0);
    }
  }
  
  // if a driver was hit
  else 
  {
	// get the driver object
    iVar6 = *(int *)(*(int *)(iVar6 + 0x6c) + 0x30);
	
	// if driver hit was not the driver who used the weapon
    if (iVar6 != piVar11[1]) 
	{
      uVar13 = *(ushort *)((int)piVar11 + 0x16) & 4;
	  
	  // RB_Hazard_HurtDriver (blasted)
      FUN_800ac1b0(iVar6,2,piVar11[1],0);
      
	  // icon damage timer, draw icon as red
	  *(undefined4 *)(iVar6 + 0x4ac) = 0x1e;
	  
      uVar1 = *(ushort *)((int)piVar11 + 0x16);
      *(ushort *)((int)piVar11 + 0x16) = uVar1 | 0x40;
	  
	  // if the driver hit, was the driver in first place
      if (
			(
				// if 10 wumpa were not used
				((uVar1 & 1) == 0) && 
				
				// if driver hit, was the intended target
				(*piVar11 == iVar6)
			) || 
				
			// driver hit was in first place
			(*(short *)(iVar6 + 0x482) == 0)
		 ) 
	  {
        *(undefined4 *)(piVar11[1] + 0x10) = 0;
		
		// RB_Warpball_Death
        FUN_800ae604(param_1);
        
		return;
      }
	  
      piVar11[0xd] = piVar11[0xd] | 1 << ((uint)*(byte *)(iVar6 + 0x4a) & 0x1f);
      puVar3 = PTR_DAT_8008d2ac;
      iVar7 = (int)*(short *)(iVar6 + 0x482);
      
	  // loop counter
	  iVar15 = iVar7;
	  
	  // for iVar15 = iVar7; iVar15 < 8; iVar15++
      while (iVar15 < 8) 
	  {
        if (*(int *)(puVar3 + ((iVar7 << 0x10) >> 0xe) + 0x250c) != 0) 
		{
          piVar11[0xd] = piVar11[0xd] |
                         1 << ((uint)*(byte *)(*(int *)(puVar3 + ((iVar7 << 0x10) >> 0xe) + 0x250c)
                                              + 0x4a) & 0x1f);
        }
		
		// increment loop counter
        iVar7 = iVar7 + 1;
        iVar15 = iVar7 * 0x10000 >> 0x10;
      }
	  
	  // if the targetted driver was just blasted
      if (*piVar11 == iVar6) 
	  {
		// no target is being seeked
        *(ushort *)((int)piVar11 + 0x16) = *(ushort *)((int)piVar11 + 0x16) & 0xfffb;
        
		// RB_Warpball_GetDriverTarget
		iVar17 = FUN_800ae7dc(piVar11,iVar17);
        
	    // set driver being chased by warpball
		*piVar11 = iVar17;
        
		// if no driver is found
		if (iVar17 == 0) 
		{
          *(undefined4 *)(piVar11[1] + 0x10) = 0;
		  
		  // RB_Warpball_Death
          FUN_800ae604(param_1);
        }
        
		else 
		{
		  // RB_Warpball_SetTargetDriver
          FUN_800aeaac(piVar11);
        }
		
		// if driver is targetted
        if (uVar13 != 0) 
		{
		  // RB_Warpball_SeekDriver
          FUN_800aece0(piVar11,(uint)*(byte *)(iVar6 + 0x495),iVar6);
        }
		
        if (
				// if intended target was destroyed
				((*(ushort *)((int)piVar11 + 0x16) & 4) == 0) && 
				
				// there was a target last frame
				(uVar13 != 0)
			) 
		{
		  // path point index
          if (*(byte *)(piVar11 + 0x11) != 0xff) 
		  {
			// get pathNode
            iVar6 = *(int *)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0x14c) +
                    (uint)*(byte *)(piVar11 + 0x11) * 0xc;
            piVar11[0xf] = iVar6;
			
			// RB_Warpball_NewPathNode
            iVar6 = FUN_800ae668(iVar6,*piVar11);
            piVar11[0x10] = iVar6;
          }
          *(ushort *)((int)piVar11 + 0x16) = *(ushort *)((int)piVar11 + 0x16) | 8;
        }
      }
    }
  }
  
  // frameCount_DontHurtParent
  if (*(short *)(piVar11 + 8) != 0) {
    *(short *)(piVar11 + 8) = *(short *)(piVar11 + 8) + -1;
  }
  return;
}

// RB_MaskWeapon_FadeAway
void FUN_800afb70(int param_1)

{
  ushort uVar1;
  short sVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  // thread -> instance
  iVar4 = *(int *)(param_1 + 0x34);
  
  // instance -> thread -> object
  iVar5 = *(int *)(*(int *)(iVar4 + 0x6c) + 0x30);

  // Sine(angle)  
  iVar3 = FUN_8003d184((int)*(short *)(iVar5 + 2));

  DAT_1f800130._2_2_ = 0x40;
  DAT_1f800130._0_2_ =
       (undefined2)
       ((((int)((uint)*(ushort *)(iVar5 + 6) << 0x10) >> 0x15) * -4 + 0x40) * iVar3 >> 0xc);
  
  // Cosine(angle)
  iVar3 = FUN_8003d1c0((int)*(short *)(iVar5 + 2));
  
  DAT_1f800134._0_2_ =
       (undefined2)
       ((((int)((uint)*(ushort *)(iVar5 + 6) << 0x10) >> 0x15) * -4 + 0x40) * iVar3 >> 0xc);
  
  // Copy Matrix:
  // To: Mask
  // From: Player
  FUN_800313c8(iVar4,*(undefined4 *)(*(int *)(*(int *)(param_1 + 0xc) + 0x30) + 0x1c),&DAT_1f800130)
  ;
  
  // alter angle for rotation
  *(short *)(iVar5 + 2) = *(short *)(iVar5 + 2) + -0x100;
  
  // decrease scale (x, y, z)
  *(short *)(iVar4 + 0x1c) = *(short *)(iVar4 + 0x1c) + -0x100;
  *(short *)(iVar4 + 0x20) = *(short *)(iVar4 + 0x20) + -0x100;
  *(short *)(iVar4 + 0x1e) = *(short *)(iVar4 + 0x1e) + -0x100;
  
  DAT_1f800130._0_2_ = 0;
  DAT_1f800130._2_2_ = 0x40;
  DAT_1f800134._0_2_ = 0;
  
  // Copy Matrix:
  // To: Mask (Beam within mask obj?)
  // From: Player
  FUN_800313c8(*(undefined4 *)(iVar5 + 8),
               *(undefined4 *)(*(int *)(*(int *)(param_1 + 0xc) + 0x30) + 0x1c),&DAT_1f800130);
  
  DAT_1f800128 = 0;
  DAT_1f80012a = *(undefined2 *)(iVar5 + 2);
  DAT_1f80012c._0_2_ = 0;
  
   // convert 3 rotation shorts into rotation matrix
  FUN_8006c2a4(&DAT_1f800108,&DAT_1f800128);
  
  iVar3 = *(int *)(iVar5 + 8) + 0x30;
  FUN_8006c3b0(iVar3,iVar3,&DAT_1f800108);
  
  // decrease scale (x, y, z)
  *(short *)(*(int *)(iVar5 + 8) + 0x1c) = *(short *)(*(int *)(iVar5 + 8) + 0x1c) + -0x100;
  *(short *)(*(int *)(iVar5 + 8) + 0x1e) = *(short *)(*(int *)(iVar5 + 8) + 0x1e) + -0x100;
  *(short *)(*(int *)(iVar5 + 8) + 0x20) = *(short *)(*(int *)(iVar5 + 8) + 0x20) + -0x100;
  
  uVar1 = *(ushort *)(*(int *)(iVar5 + 8) + 0x22);
  if (uVar1 < 0x1000) {
    *(short *)(*(int *)(iVar5 + 8) + 0x22) = uVar1 + 0x200;
  }
  if (*(short *)(iVar5 + 6) < 0x200) {
    sVar2 = *(short *)(iVar5 + 6) + *(short *)(PTR_DAT_8008d2ac + 0x1d04);
    *(short *)(iVar5 + 6) = sVar2;
    if (0x200 < sVar2) {
      *(undefined2 *)(iVar5 + 6) = 0x200;
    }
  }
  else 
  {
	// INSTANCE_Death
    FUN_80030aa8(*(undefined4 *)(iVar5 + 8));
	
	// This thread is now dead
    *(uint *)(param_1 + 0x1c) = *(uint *)(param_1 + 0x1c) | 0x800;
  }
  return;
}

// RB_MaskWeapon_ThTick
void FUN_800afdbc(int param_1)

{
  short sVar1;
  undefined *puVar2;
  undefined *puVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  
  puVar2 = PTR_DAT_8008d2ac;
  
  // (mask) thread -> instance
  iVar10 = *(int *)(param_1 + 0x34);
  
  // instance -> thread -> object
  iVar9 = *(int *)(*(int *)(iVar10 + 0x6c) + 0x30);
  
  // (mask) thread -> (player) parentthread -> instance
  iVar11 = *(int *)(*(int *)(param_1 + 0xc) + 0x34);
  
  // thread -> parentthread -> (Driver*)object -> invisibleTimer == 0
  if (*(int *)(*(int *)(*(int *)(param_1 + 0xc) + 0x30) + 0x28) == 0) 
  {
	// If driver is visible
	  
	// iteration counter
    iVar4 = 0;
	
	// numPlyrCurrGame is not zero
    if (PTR_DAT_8008d2ac[0x1ca8] != '\0') 
	{
      iVar8 = 0x168;
      iVar6 = 0;
      iVar7 = iVar10;
	  
	  // For iVar4 = 0; iVar4 < numPlyrCurrGame; iVar4++
      do {
        puVar3 = puVar2 + iVar8;
        iVar8 = iVar8 + 0x110;
        *(undefined **)(iVar7 + 0x74) = puVar3;
        iVar7 = iVar7 + 0x88;
		
		// keep count of loop iteration
        iVar4 = iVar4 + 1;
		
        *(undefined **)(*(int *)(iVar9 + 8) + iVar6 + 0x74) = puVar3;
        iVar6 = iVar6 + 0x88;
		
      } while (iVar4 < (int)(uint)(byte)puVar2[0x1ca8]);
    }
  }
  
  // if driver is invisible
  else 
  {
	// count loop iteration
    uVar5 = 0;
	
	// if numPlyrCurrGame is not zero
    if (PTR_DAT_8008d2ac[0x1ca8] != '\0') 
	{
      iVar7 = 0;
      iVar4 = iVar10;
	  
	  // for uVar5 = 0; uVar5 < numPlyrCurrGame; uVar5++
      do {
        if (uVar5 != (uint)*(byte *)(*(int *)(*(int *)(param_1 + 0xc) + 0x30) + 0x4a)) {
          *(undefined4 *)(iVar4 + 0x74) = 0;
          *(undefined4 *)(*(int *)(iVar9 + 8) + iVar7 + 0x74) = 0;
        }
        iVar4 = iVar4 + 0x88;
		
		// increment loop counter
        uVar5 = uVar5 + 1;
		
        iVar7 = iVar7 + 0x88;
      } while ((int)uVar5 < (int)(uint)(byte)puVar2[0x1ca8]);
    }
  }
  
  // if driverInst is not reflective
  if ((*(uint *)(iVar11 + 0x28) & 0x4000) == 0) 
  {
	// mask is not reflective
    *(uint *)(iVar10 + 0x28) = *(uint *)(iVar10 + 0x28) & 0xffffbfff;
  }
  
  // if driverInst is reflective
  else 
  {
	// mask is reflective
    *(uint *)(iVar10 + 0x28) = *(uint *)(iVar10 + 0x28) | 0x4000;
	
	// copy split line
    *(undefined2 *)(iVar10 + 0x56) = *(undefined2 *)(iVar11 + 0x56);
	
	// mask beam is reflective
    *(uint *)(*(int *)(iVar9 + 8) + 0x28) = *(uint *)(*(int *)(iVar9 + 8) + 0x28) | 0x4000;
    
	// copy split line
	*(undefined2 *)(*(int *)(iVar9 + 8) + 0x56) = *(undefined2 *)(iVar11 + 0x56);
  }
  *(undefined *)(iVar10 + 0x50) = *(undefined *)(iVar11 + 0x50);
  *(undefined *)(iVar10 + 0x51) = *(undefined *)(iVar11 + 0x51);
  
  // Sine(angle)
  iVar4 = FUN_8003d184((int)*(short *)(iVar9 + 2));
  
  DAT_1f800130._0_2_ = (short)(((iVar4 << 6) >> 0xc) * (int)*(short *)(iVar9 + 0x12) >> 0xc);
  DAT_1f800130._2_2_ =
       *(short *)(&DAT_800b2cc4 + (int)*(short *)(*(int *)(iVar9 + 8) + 0x54) * 2) + 0x40;
  
  // Cosine(angle)
  iVar4 = FUN_8003d1c0((int)*(short *)(iVar9 + 2));
  
  DAT_1f800128 = 0;
  DAT_1f800134._0_2_ = (short)(((iVar4 << 6) >> 0xc) * (int)*(short *)(iVar9 + 0x12) >> 0xc);
  DAT_1f80012a = *(undefined2 *)(iVar9 + 2);
  DAT_1f80012c._0_2_ = 0;
  
  if ((*(ushort *)(iVar9 + 4) & 1) == 0) 
  {
	// Copy Matrix:
	// To: Mask
	// From: Player
    FUN_800313c8(iVar10,iVar11,&DAT_1f800130);
	
	 // convert 3 rotation shorts into rotation matrix
    FUN_8006c2a4(&DAT_1f800108,&DAT_1f800128);
	
    FUN_8006c3b0(iVar10 + 0x30,iVar10 + 0x30,&DAT_1f800108);
  }
  else {
    *(int *)(iVar10 + 0x44) = (int)*(short *)(iVar9 + 0xc) + (int)(short)DAT_1f800130;
    *(int *)(iVar10 + 0x48) = (int)*(short *)(iVar9 + 0xe) + (int)DAT_1f800130._2_2_;
    *(int *)(iVar10 + 0x4c) = (int)*(short *)(iVar9 + 0x10) + (int)(short)DAT_1f800134;
	
	 // convert 3 rotation shorts into rotation matrix
    FUN_8006c2a4(iVar10 + 0x30,&DAT_1f800128);
  }
  
  DAT_1f800130._0_2_ = 0;
  DAT_1f800130._2_2_ = 0x40;
  DAT_1f800134._0_2_ = 0;
  DAT_1f800128 = 0;
  DAT_1f80012a = *(undefined2 *)(iVar9 + 2);
  DAT_1f80012c._0_2_ = 0;
  
  if ((*(ushort *)(iVar9 + 4) & 1) == 0) {
    FUN_800313c8(*(undefined4 *)(iVar9 + 8),iVar11,&DAT_1f800130);
	
	 // convert 3 rotation shorts into rotation matrix
    FUN_8006c2a4(&DAT_1f800108,&DAT_1f800128);
	
	// mask -> beam -> object
    iVar11 = *(int *)(iVar9 + 8) + 0x30;
    FUN_8006c3b0(iVar11,iVar11,&DAT_1f800108);
  }
  else {
    *(int *)(*(int *)(iVar9 + 8) + 0x44) = (int)*(short *)(iVar9 + 0xc);
    *(int *)(*(int *)(iVar9 + 8) + 0x48) = (int)*(short *)(iVar9 + 0xe) + (int)DAT_1f800130._2_2_;
    *(int *)(*(int *)(iVar9 + 8) + 0x4c) = (int)*(short *)(iVar9 + 0x10) + (int)(short)DAT_1f800134;
	
	 // convert 3 rotation shorts into rotation matrix
    FUN_8006c2a4(*(int *)(iVar9 + 8) + 0x30,&DAT_1f800128);
  }
  
  // get animFrame
  sVar1 = *(short *)(*(int *)(iVar9 + 8) + 0x54);
  
  // INSTANCE_GetNumAnimFrames
  iVar11 = FUN_80030f58(*(int *)(iVar9 + 8),0);
  
  // if animation is not finished
  if ((int)sVar1 + 1 < iVar11) 
  {
	// increment animation frame
    *(short *)(*(int *)(iVar9 + 8) + 0x54) = *(short *)(*(int *)(iVar9 + 8) + 0x54) + 1;
  }
  
  // if animation is finished
  else 
  {
	// restart animation
    *(undefined2 *)(*(int *)(iVar9 + 8) + 0x54) = 0;
  }
  
  // adjust rotation
  *(short *)(iVar9 + 2) = *(short *)(iVar9 + 2) + -0x100;
  
  // If duration is over
  if (*(short *)(iVar9 + 6) == 0) 
  {
	// end duration
    *(undefined2 *)(iVar9 + 6) = 0;
	
	// ThTick_SetAndExec RB_MaskWeapon_FadeAway
    FUN_800716ec(param_1,FUN_800afb70);
  }
  
  // if duration is not over
  else 
  {
	// reduce duration time by milliseconds
    iVar11 = (uint)*(ushort *)(iVar9 + 6) - (uint)*(ushort *)(PTR_DAT_8008d2ac + 0x1d04);
    
	// set new duration
	*(undefined2 *)(iVar9 + 6) = (short)iVar11;
    
	// check for negatives
	if (iVar11 * 0x10000 < 0) {
      *(undefined2 *)(iVar9 + 6) = 0;
    }
  }
  
  // make Beam visible
  *(uint *)(*(int *)(iVar9 + 8) + 0x28) = *(uint *)(*(int *)(iVar9 + 8) + 0x28) & 0xffffff7f;
  
  // Set Beam Scale (x, y, z)
  *(undefined2 *)(*(int *)(iVar9 + 8) + 0x1c) = *(undefined2 *)(iVar9 + 0x12);
  *(undefined2 *)(*(int *)(iVar9 + 8) + 0x1e) = *(undefined2 *)(iVar9 + 0x12);
  *(undefined2 *)(*(int *)(iVar9 + 8) + 0x20) = *(undefined2 *)(iVar9 + 0x12);
  
  *(undefined2 *)(*(int *)(iVar9 + 8) + 0x22) = 0;
  
  // make Head visible
  *(uint *)(iVar10 + 0x28) = *(uint *)(iVar10 + 0x28) & 0xffffff7f;
  
  // Set Head Scale (x, y, z)
  *(undefined2 *)(iVar10 + 0x1c) = *(undefined2 *)(iVar9 + 0x12);
  *(undefined2 *)(iVar10 + 0x1e) = *(undefined2 *)(iVar9 + 0x12);
  *(undefined2 *)(iVar10 + 0x20) = *(undefined2 *)(iVar9 + 0x12);
  return;
}

// RB_ShieldDark_ThTick_Pop
void FUN_800b0278(int param_1)

{
  int *piVar1;
  int iVar2;
  undefined2 local_18;
  undefined2 local_16;
  undefined2 local_14;
  
  // This is a weapon thread
  
  // get instance from thread
  iVar2 = *(int *)(param_1 + 0x34);
  
  // get object from thread from instance
  piVar1 = *(int **)(*(int *)(iVar2 + 0x6c) + 0x30);
  
  local_18 = 0;
  local_16 = 0;
  local_14 = 0;
  
  // get the driver that shot this weapon
  
  // Copy matrix
  // To: shield instance, highlight instance, etc
  // From: thread (shield) -> parentthread (player) -> object (driver) -> instance
  FUN_800313c8(iVar2,*(undefined4 *)(*(int *)(*(int *)(param_1 + 0xc) + 0x30) + 0x1c),&local_18);
  FUN_800313c8(piVar1[2],*(undefined4 *)(*(int *)(*(int *)(param_1 + 0xc) + 0x30) + 0x1c),&local_18)
  ;
  
  // set rotation
  *(undefined4 *)(iVar2 + 0x30) = 0x1000;
  *(undefined4 *)(iVar2 + 0x34) = 0;
  *(undefined4 *)(iVar2 + 0x38) = 0x1000;
  *(undefined4 *)(iVar2 + 0x3c) = 0;
  *(undefined2 *)(iVar2 + 0x40) = 0x1000;
  
  // set rotation
  *(undefined4 *)(piVar1[2] + 0x30) = 0x1000;
  *(undefined4 *)(piVar1[2] + 0x34) = 0;
  *(undefined4 *)(piVar1[2] + 0x38) = 0x1000;
  *(undefined4 *)(piVar1[2] + 0x3c) = 0;
  *(undefined2 *)(piVar1[2] + 0x40) = 0x1000;
  
  // if animation is not done
  if (*piVar1 < 0xb) 
  {
	// set scale
    *(undefined2 *)(iVar2 + 0x1c) = *(undefined2 *)(&DAT_800b2d14 + *piVar1 * 4);
    *(undefined2 *)(iVar2 + 0x1e) = *(undefined2 *)(&DAT_800b2d16 + *piVar1 * 4);
    *(undefined2 *)(iVar2 + 0x20) = *(undefined2 *)(&DAT_800b2d14 + *piVar1 * 4);
	
	// set scale
    *(undefined2 *)(piVar1[2] + 0x1c) = *(undefined2 *)(&DAT_800b2d14 + *piVar1 * 4);
    *(undefined2 *)(piVar1[2] + 0x1e) = *(undefined2 *)(&DAT_800b2d16 + *piVar1 * 4);
    *(undefined2 *)(piVar1[2] + 0x20) = *(undefined2 *)(&DAT_800b2d14 + *piVar1 * 4);
	
    *piVar1 = *piVar1 + 1;
  }
  
  // if animation is done
  else 
  {
	// play 3D sound for "green shield fade away"
    FUN_8002f0dc(0x58,iVar2);
	
	// INSTANCE_Death
    FUN_80030aa8(piVar1[2]);
    FUN_80030aa8(piVar1[3]);
	
	// this thread is now dead
    *(uint *)(param_1 + 0x1c) = *(uint *)(param_1 + 0x1c) | 0x800;
  }
  return;
}

// RB_ShieldDark_ThTick_Grow
void FUN_800b0454(int param_1)

{
  ushort uVar1;
  undefined2 uVar2;
  undefined *puVar3;
  short sVar4;
  undefined *puVar5;
  int iVar6;
  undefined4 uVar7;
  int iVar8;
  uint uVar9;
  int iVar10;
  undefined4 *puVar11;
  int iVar12;
  undefined4 uVar13;
  undefined4 uVar14;
  int *piVar15;
  int iVar16;
  undefined2 local_20;
  undefined2 local_1e;
  undefined2 local_1c;
  
  // thread -> instance
  iVar16 = *(int *)(param_1 + 0x34);
  
  // instance -> thread -> object
  piVar15 = *(int **)(*(int *)(iVar16 + 0x6c) + 0x30);
  
  local_20 = 0;
  local_1e = 0;
  local_1c = 0;
  
  // if highlight cooldown is gone
  if (*(short *)((int)piVar15 + 0x16) == 0) 
  {
    *(short *)((int)piVar15 + 0x12) = *(short *)((int)piVar15 + 0x12) + 0x100;
	
	// highlight is now visible
    *(uint *)(piVar15[3] + 0x28) = *(uint *)(piVar15[3] + 0x28) & 0xffffff7f;
    
	// highlightRot[1]
	iVar10 = (int)*(short *)((int)piVar15 + 0x12);
    
	iVar8 = iVar10;
    if (iVar10 < 0) {
      iVar8 = iVar10 + 0xfff;
    }
	
	// if highlight is finished
    if ((iVar10 + (iVar8 >> 0xc) * -0x1000) * 0x10000 >> 0x10 == 0x400) 
	{
	  // highlightTimer (30 frames)
      *(undefined2 *)((int)piVar15 + 0x16) = 0x1e;
	  
	  // highlightRot[1]
      *(undefined2 *)((int)piVar15 + 0x12) = 0xc00;
	  
	  // make highlight invisible
      *(uint *)(piVar15[3] + 0x28) = *(uint *)(piVar15[3] + 0x28) | 0x80;
    }
  }
  
  // if highlight cooldown is not done
  else 
  {
	// decrease counter, make invisible when this is zero
    *(short *)((int)piVar15 + 0x16) = *(short *)((int)piVar15 + 0x16) + -1;
	
	// make invisible
    *(uint *)(piVar15[3] + 0x28) = *(uint *)(piVar15[3] + 0x28) | 0x80;
	
	// if timer runs out (last frame)
    if (*(short *)((int)piVar15 + 0x16) == 0) 
	{
	  // make visible
      *(uint *)(piVar15[3] + 0x28) = *(uint *)(piVar15[3] + 0x28) & 0xffffff7f;
    }
  }
  puVar3 = PTR_DAT_8008d2ac;
  
  // If the driver that used this weapon is visible
  
  // thread -> parentthread -> object -> invisibility == 0
  if (*(int *)(*(int *)(*(int *)(param_1 + 0xc) + 0x30) + 0x28) == 0) {
    
	// loop counter
	iVar8 = 0;
	
	// if numPlyrCurrGame is not zero
    if (PTR_DAT_8008d2ac[0x1ca8] != '\0') {
      iVar12 = 0x168;
      iVar6 = 0;
      iVar10 = iVar16;
	  
	  // for iVar8 = 0; iVar8 < numPlyrCurrGame; iVar8++
      do 
	  {
        puVar5 = puVar3 + iVar12;
        iVar12 = iVar12 + 0x110;
        *(undefined **)(iVar10 + 0x74) = puVar5;
        iVar10 = iVar10 + 0x88;
        *(undefined **)(piVar15[2] + iVar6 + 0x74) = puVar5;
		
		// increment loop counter
        iVar8 = iVar8 + 1;
		
        *(undefined **)(piVar15[3] + iVar6 + 0x74) = puVar5;
        iVar6 = iVar6 + 0x88;
      } while (iVar8 < (int)(uint)(byte)puVar3[0x1ca8]);
    }
  }
  else 
  {
	// loop counter
    uVar9 = 0;
	
	// if numPlyrCurrGame is not zero
    if (PTR_DAT_8008d2ac[0x1ca8] != '\0') 
	{
      iVar10 = 0;
      iVar8 = iVar16;
	  
	  // for iVar9 = 0; iVar9 < numPlyrCurrGame; iVar9++
      do {
        if (uVar9 != (uint)*(byte *)(*(int *)(*(int *)(param_1 + 0xc) + 0x30) + 0x4a)) {
          *(undefined4 *)(iVar8 + 0x74) = 0;
          *(undefined4 *)(piVar15[2] + iVar10 + 0x74) = 0;
          *(undefined4 *)(piVar15[3] + iVar10 + 0x74) = 0;
        }
        iVar8 = iVar8 + 0x88;
		
		// increment loop counter
        uVar9 = uVar9 + 1;
		
        iVar10 = iVar10 + 0x88;
      } while ((int)uVar9 < (int)(uint)(byte)puVar3[0x1ca8]);
    }
  }
  
  // Copy matrix
  // To: shield instance, highlight instance, etc
  // From: thread (shield) -> parentthread (player) -> object (driver) -> instance
  FUN_800313c8(iVar16,*(undefined4 *)(*(int *)(*(int *)(param_1 + 0xc) + 0x30) + 0x1c),&local_20);
  FUN_800313c8(piVar15[2],*(undefined4 *)(*(int *)(*(int *)(param_1 + 0xc) + 0x30) + 0x1c),&local_20
              );
  FUN_800313c8(piVar15[3],*(undefined4 *)(*(int *)(*(int *)(param_1 + 0xc) + 0x30) + 0x1c),&local_20
              );
			  
   // set rotation variables
  *(undefined4 *)(iVar16 + 0x30) = 0x1000;
  *(undefined4 *)(iVar16 + 0x34) = 0;
  *(undefined4 *)(iVar16 + 0x38) = 0x1000;
  *(undefined4 *)(iVar16 + 0x3c) = 0;
  *(undefined2 *)(iVar16 + 0x40) = 0x1000;
  
  // set rotation variables
  *(undefined4 *)(piVar15[2] + 0x30) = 0x1000;
  *(undefined4 *)(piVar15[2] + 0x34) = 0;
  *(undefined4 *)(piVar15[2] + 0x38) = 0x1000;
  *(undefined4 *)(piVar15[2] + 0x3c) = 0;
  *(undefined2 *)(piVar15[2] + 0x40) = 0x1000;
  
   // convert 3 rotation shorts into rotation matrix
  FUN_8006c2a4(piVar15[3] + 0x30,piVar15 + 4);
  
  puVar3 = PTR_DAT_8008d2ac;
  
  // if animation is not done
  if (*piVar15 < 8) 
  {
	// set scale
    *(undefined2 *)(iVar16 + 0x1c) = *(undefined2 *)(&DAT_800b2cf4 + *piVar15 * 4);
    *(undefined2 *)(iVar16 + 0x1e) = *(undefined2 *)(&DAT_800b2cf6 + *piVar15 * 4);
    *(undefined2 *)(iVar16 + 0x20) = *(undefined2 *)(&DAT_800b2cf4 + *piVar15 * 4);
	
	// set scale
    *(undefined2 *)(piVar15[2] + 0x1c) = *(undefined2 *)(&DAT_800b2cf4 + *piVar15 * 4);
    *(undefined2 *)(piVar15[2] + 0x1e) = *(undefined2 *)(&DAT_800b2cf6 + *piVar15 * 4);
    *(undefined2 *)(piVar15[2] + 0x20) = *(undefined2 *)(&DAT_800b2cf4 + *piVar15 * 4);
    *piVar15 = *piVar15 + 1;
  }
  
  // if animation is done
  else 
  {
	// set scale
    *(undefined2 *)(iVar16 + 0x1c) =
         (&DAT_800b2d40)[(*(uint *)(PTR_DAT_8008d2ac + 0x1cec) % 6) * 2];
    *(undefined2 *)(iVar16 + 0x1e) = (&DAT_800b2d42)[(*(uint *)(puVar3 + 0x1cec) % 6) * 2];
    *(undefined2 *)(iVar16 + 0x20) = (&DAT_800b2d40)[(*(uint *)(puVar3 + 0x1cec) % 6) * 2];
	
	// set scale
    *(undefined2 *)(piVar15[2] + 0x1c) =
         (&DAT_800b2d40)[(*(uint *)(puVar3 + 0x1cec) % 6) * 2];
    *(undefined2 *)(piVar15[2] + 0x1e) =
         (&DAT_800b2d42)[(*(uint *)(puVar3 + 0x1cec) % 6) * 2];
    *(undefined2 *)(piVar15[2] + 0x20) =
         (&DAT_800b2d40)[(*(uint *)(puVar3 + 0x1cec) % 6) * 2];
		 
	// set scale
    *(undefined2 *)(piVar15[3] + 0x1c) =
         (&DAT_800b2d40)[(*(uint *)(puVar3 + 0x1cec) % 6) * 2];
    *(undefined2 *)(piVar15[3] + 0x1e) =
         (&DAT_800b2d42)[(*(uint *)(puVar3 + 0x1cec) % 6) * 2];
    *(undefined2 *)(piVar15[3] + 0x20) =
         (&DAT_800b2d40)[(*(uint *)(puVar3 + 0x1cec) % 6) * 2];
  }
  
  // if this is not a blue shield,
  if ((*(ushort *)((int)piVar15 + 6) & 4) == 0) 
  {
	// === Green Shield ===
	  
	// duration
    sVar4 = *(short *)(piVar15 + 1);
	
	// if out of time
    if (*(short *)(piVar15 + 1) == 0) 
	{
	  // erase bubble instance from driver
      *(undefined4 *)(*(int *)(*(int *)(param_1 + 0xc) + 0x30) + 0x14) = 0;
	  
      goto LAB_800b0d6c;
    }
	
	// subtract 32ms by hand, instead of using in-game timer?
    *(ushort *)(piVar15 + 1) = sVar4 - 0x20U;
    iVar8 = (uint)(ushort)(sVar4 - 0x20U) << 0x10;
    
	// last full second?
	if (iVar8 >> 0x10 < 0x780) 
	{
      sVar4 = (short)(((0x3c - (iVar8 >> 0x15)) * 0xc00) / 0x3c) + 0x400;
      
	  // transparency
	  *(short *)(iVar16 + 0x22) = sVar4;
      *(short *)(piVar15[2] + 0x22) = sVar4;
      *(short *)(piVar15[3] + 0x22) = sVar4;
    }
  }
  puVar3 = PTR_DAT_8008d2ac;
  uVar1 = *(ushort *)((int)piVar15 + 6);
  if (
		(
			(((uVar1 & 1) != 0) || ((uVar1 & 8) != 0)) ||
			(
				// thread -> parentthread -> (Driver*)object
				iVar8 = *(int *)(*(int *)(param_1 + 0xc) + 0x30), 
				
				// if race ended for this driver
				(*(uint *)(iVar8 + 0x2c8) & 0x2000000) != 0
			)
		) 
		
		// if driver is being mask grabbed
		|| (*(char *)(iVar8 + 0x376) == '\x05')
	 ) 
  {
		  
    // thread -> parentthread -> (Driver*)object
    iVar16 = *(int *)(*(int *)(param_1 + 0xc) + 0x30);
	
    if ((*(ushort *)((int)piVar15 + 6) & 8) != 0) 
	{
      *(undefined2 *)(PTR_DAT_8008d2ac + (uint)*(byte *)(iVar16 + 0x4a) * 0x110 + 0x17a) = 0x1fff;
	  
	  // pushBuffer based on...
	  // thread -> parentthread -> (Driver*)object -> index
      *(undefined2 *)
       (puVar3 + (uint)*(byte *)(*(int *)(*(int *)(param_1 + 0xc) + 0x30) + 0x4a) * 0x110 + 0x17c) =
           0x1000;
		 
	  // pushBuffer based on...
	  // thread -> parentthread -> (Driver*)object -> index
      *(undefined2 *)
       (puVar3 + (uint)*(byte *)(*(int *)(*(int *)(param_1 + 0xc) + 0x30) + 0x4a) * 0x110 + 0x17e) =
           0xff78;
    }
    *piVar15 = 0;
    *(undefined4 *)(iVar16 + 0x14) = 0;
	
	// RB_ShieldDark_ThTick_Pop is from being mask-grabbed,
	// or from colliding with another player
	
	// ThTick_SetAndExec, RB_ShieldDark_ThTick_Pop
    FUN_800716ec(param_1,FUN_800b0278);
	
    return;
  }
  
  if ((uVar1 & 2) == 0) {
    return;
  }
  
  *(undefined4 *)(iVar8 + 0x14) = 0;
  *(char *)(iVar8 + 0x55c) = *(char *)(iVar8 + 0x55c) + '\x01';
  
  // vibration
  FUN_80026440(iVar8,8,0);
  FUN_800264c0(iVar8,8,0x7f);
  
  // green shield
  uVar7 = 0x5e;
  
  if ((*(ushort *)((int)piVar15 + 6) & 4) != 0) {
	// blue shield
	uVar7 = 0x56;
  }
  
  // create a thread, get an instance
  // 0x200 flag = MediumStackPool
  // 0xd = "other" thread bucket
  iVar10 = FUN_800309a4(uVar7,s_shieldbomb_800aba04,0x200,0xd,FUN_800adb50,0x58,
                        
						// driver -> instane -> thread
						*(undefined4 *)(*(int *)(iVar8 + 0x1c) + 0x6c));

  // if driver is not an AI (human)						
  if ((*(uint *)(iVar8 + 0x2c8) & 0x100000) == 0) 
  {
	// make driver talk
    FUN_8002cbe8(0xd,(int)(short)(&DAT_80086e84)[*(byte *)(iVar8 + 0x4a)],0x10);
  }
  uVar13 = *(undefined4 *)(iVar16 + 0x34);
  uVar14 = *(undefined4 *)(iVar16 + 0x38);
  uVar7 = *(undefined4 *)(iVar16 + 0x3c);
  *(undefined4 *)(iVar10 + 0x30) = *(undefined4 *)(iVar16 + 0x30);
  *(undefined4 *)(iVar10 + 0x34) = uVar13;
  *(undefined4 *)(iVar10 + 0x38) = uVar14;
  *(undefined4 *)(iVar10 + 0x3c) = uVar7;
  uVar13 = *(undefined4 *)(iVar16 + 0x44);
  uVar14 = *(undefined4 *)(iVar16 + 0x48);
  uVar7 = *(undefined4 *)(iVar16 + 0x4c);
  *(undefined4 *)(iVar10 + 0x40) = *(undefined4 *)(iVar16 + 0x40);
  *(undefined4 *)(iVar10 + 0x44) = uVar13;
  *(undefined4 *)(iVar10 + 0x48) = uVar14;
  *(undefined4 *)(iVar10 + 0x4c) = uVar7;
  
  // set funcThDestroy to remove instance from instance pool
  *(undefined4 *)(*(int *)(iVar10 + 0x6c) + 0x24) = 0x80041dfc;
  
  // set scale (x, y, z)
  *(undefined2 *)(iVar10 + 0x1c) = 0x400;
  *(undefined2 *)(iVar10 + 0x1e) = 0x400;
  *(undefined2 *)(iVar10 + 0x20) = 0x400;
  
  // a 4th scale value???
  *(undefined2 *)(iVar10 + 0x22) = 0x400;
  
  // get TrackerWeapon object from thread
  puVar11 = *(undefined4 **)(*(int *)(iVar10 + 0x6c) + 0x30);
  
  // tw->flags
  *(undefined2 *)((int)puVar11 + 0x16) = 0;
  
  // tw->driverParent
  puVar11[1] = iVar8;
  
  // tw->driverTarget
  *puVar11 = 0;
  
  // tw->timeAlive
  puVar11[0x12] = 0;
  
  // tw->audioPtr
  puVar11[9] = 0;
  
  // angle
  uVar2 = *(undefined2 *)(iVar8 + 0x39a);
  
  // tw->dir[1]
  *(undefined2 *)((int)puVar11 + 0x12) = 0;
  
  // tw->rotY
  *(undefined2 *)((int)puVar11 + 0x1e) = uVar2;
  
  // tw->dir[0] = driver->instSelf->matrix.m[0][2]
  *(short *)(puVar11 + 4) = (short)((int)*(short *)(*(int *)(iVar8 + 0x1c) + 0x34) * 3 >> 7);
  
  // tw->dir[2] = driver->instSelf->matrix.m[2][2]
  sVar4 = *(short *)(*(int *)(iVar8 + 0x1c) + 0x40);
  
  // tw->frameCount_DontHurtParent
  *(undefined2 *)(puVar11 + 8) = 10;
  
  // tw->frameCount_Blind
  *(undefined2 *)((int)puVar11 + 0x22) = 0;
  
  // tw->dir[2]
  *(short *)(puVar11 + 5) = (short)((int)sVar4 * 3 >> 7);
  
  // tw->instParent
  puVar11[2] = *(undefined4 *)(iVar8 + 0x1c);
LAB_800b0d6c:
  
  // green shield fade away sound
  FUN_8002f0dc(0x58,iVar16);
  
  // INSTANCE_Death
  // shield and highlight
  FUN_80030aa8(piVar15[2]);
  FUN_80030aa8(piVar15[3]);
  
  // This thread is now dead
  *(uint *)(param_1 + 0x1c) = *(uint *)(param_1 + 0x1c) | 0x800;
  return;
}

// RB_Player_ToggleInvisible
void FUN_800b0dbc(void)

{
  undefined *puVar1;
  undefined *puVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  
  puVar2 = PTR_DAT_8008d2ac;
  
  // player thread
  iVar7 = *(int *)(PTR_DAT_8008d2ac + 0x1b2c);
  
  puVar1 = PTR_DAT_8008d2ac;
  
  // loop through player threads
  while (iVar7 != 0) 
  {
	// driver object
    iVar6 = *(int *)(iVar7 + 0x30);
	
    PTR_DAT_8008d2ac = puVar1;
	
    if (
			// if driver is invisible
			(*(int *)(iVar6 + 0x28) != 0) && 
			
			(uVar4 = 0, puVar2[0x1ca8] != '\0')
		) 
	{
      iVar5 = 0;
	  
	  // loop through InstanceDrawPerPlayer
      do 
	  {
		// if this is not the screen of the invisible driver
        if (uVar4 != (uint)*(byte *)(iVar6 + 0x4a)) 
		{
		  // make driver instance invisible on this screen
          iVar3 = *(int *)(iVar6 + 0x1c) + iVar5;
          *(uint *)(iVar3 + 0xb8) = *(uint *)(iVar3 + 0xb8) & 0xffffffbf;
        }
        uVar4 = uVar4 + 1;
        iVar5 = iVar5 + 0x88;
      } while ((int)uVar4 < (int)(uint)(byte)puVar1[0x1ca8]);
    }
	
	// thread -> sibling thread
    iVar7 = *(int *)(iVar7 + 0x10);
	
    puVar1 = PTR_DAT_8008d2ac;
  }
  PTR_DAT_8008d2ac = puVar1;
  return;
}

// RB_Player_ToggleFlicker (after damage in battle mode)
void FUN_800b0e68(void)

{
  undefined *puVar1;
  undefined *puVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  
  puVar2 = PTR_DAT_8008d2ac;
  
  // player thread
  iVar6 = *(int *)(PTR_DAT_8008d2ac + 0x1b2c);
  
  puVar1 = PTR_DAT_8008d2ac;
  
  while (iVar6 != 0) 
  {
	// driver object
    iVar7 = *(int *)(iVar6 + 0x30);
	
    PTR_DAT_8008d2ac = puVar1;
    
	if (
			(
				// invincible timer
				(0x2a0 < *(int *)(iVar7 + 0x24)) && 
				
				// odd number frames
				((*(uint *)(puVar2 + 0x1cec) & 1) != 0)
			) &&
       
			(iVar5 = 0, puVar2[0x1ca8] != '\0')
		) 
	{
      iVar4 = 0;
	  
	  // on all screens
      do 
	  {
		// make driver invisible
        iVar3 = *(int *)(iVar7 + 0x1c) + iVar4;
        iVar5 = iVar5 + 1;
        *(uint *)(iVar3 + 0xb8) = *(uint *)(iVar3 + 0xb8) & 0xffffffbf;
        iVar4 = iVar4 + 0x88;
      } while (iVar5 < (int)(uint)(byte)puVar1[0x1ca8]);
    }
	
	// thread -> sibling thread
    iVar6 = *(int *)(iVar6 + 0x10);
    
	puVar1 = PTR_DAT_8008d2ac;
  }
  PTR_DAT_8008d2ac = puVar1;
  return;
}

// RB_RainCloud_FadeAway
void FUN_800b0f1c(int param_1)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  
  // thread -> instance
  iVar1 = *(int *)(param_1 + 0x34);
  
  // thread -> parent -> instance
  iVar2 = *(int *)(*(int *)(param_1 + 0xc) + 0x34);
  
  // instance -> thread -> object
  piVar3 = *(int **)(*(int *)(iVar1 + 0x6c) + 0x30);
  
  // === Ghidra Fail ===
  // This should be getting the average, not adding
  
  // set X and Y
  *(int *)(iVar1 + 0x44) = *(int *)(iVar1 + 0x44) + *(int *)(iVar2 + 0x44) >> 1;
  *(int *)(iVar1 + 0x48) = *(int *)(iVar1 + 0x48) + *(int *)(iVar2 + 0x48) + 0x80 >> 1;
  
  iVar2 = *(int *)(iVar2 + 0x4c);
  
  // shrink scale (x, y, z)
  *(short *)(iVar1 + 0x1c) = *(short *)(iVar1 + 0x1c) + -0x100;
  *(short *)(iVar1 + 0x1e) = *(short *)(iVar1 + 0x1e) + -0x100;
  *(short *)(iVar1 + 0x20) = *(short *)(iVar1 + 0x20) + -0x100;
  
  // set Z
  *(int *)(iVar1 + 0x4c) = *(int *)(iVar1 + 0x4c) + iVar2 >> 1;
  
  iVar2 = *piVar3;
  
  // animation?
  *(int *)(iVar2 + 8) = *(int *)(iVar2 + 8) + -2;
  
  if (*(short *)(iVar1 + 0x1c) < 0) {
    FUN_8003112c(PTR_DAT_8008d2ac + 0x19e8,*piVar3);
	
	// This thread is now dead
    *(uint *)(param_1 + 0x1c) = *(uint *)(param_1 + 0x1c) | 0x800;
  }
  return;
}

// RB_RainCloud_ThTick
void FUN_800b1000(int param_1)

{
  short sVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  
  // get instance from thread
  iVar3 = *(int *)(param_1 + 0x34);
  
  // get object from thread
  iVar5 = *(int *)(param_1 + 0x30);
  
  // get animation frame from instance
  sVar1 = *(short *)(iVar3 + 0x54);
  
  // thread -> parentthread -> object
  iVar4 = *(int *)(*(int *)(param_1 + 0xc) + 0x30);
  
  // thread -> parentthread -> instance
  iVar6 = *(int *)(*(int *)(param_1 + 0xc) + 0x34);
  
  // INSTANCE_GetNumAnimFrames
  iVar2 = FUN_80030f58(iVar3,0);
  
  // if you have not reached the end of the animation
  if ((int)sVar1 + 1 < iVar2) 
  {
	// increment animation frame
    *(short *)(iVar3 + 0x54) = *(short *)(iVar3 + 0x54) + 1;
  }
  
  // if animation is done
  else 
  {
	// restart animation
    *(undefined2 *)(iVar3 + 0x54) = 0;
  }
  
  // === Ghidra Fail ===
  // should be averaging scale and averaging velocity
  
  *(undefined2 *)(iVar3 + 0x1c) =
       (short)((int)*(short *)(iVar3 + 0x1c) + (int)*(short *)(iVar6 + 0x1c) >> 1);
  *(undefined2 *)(iVar3 + 0x1e) =
       (short)((int)*(short *)(iVar3 + 0x1e) + (int)*(short *)(iVar6 + 0x1e) >> 1);
  *(undefined2 *)(iVar3 + 0x20) =
       (short)((int)*(short *)(iVar3 + 0x20) + (int)*(short *)(iVar6 + 0x20) >> 1);
	   
  *(int *)(iVar3 + 0x44) = *(int *)(iVar3 + 0x44) + *(int *)(iVar6 + 0x44) >> 1;
  *(int *)(iVar3 + 0x48) =
       *(int *)(iVar3 + 0x48) + *(int *)(iVar6 + 0x48) + ((int)*(short *)(iVar3 + 0x1e) * 5 >> 7) >>
       1;
  *(int *)(iVar3 + 0x4c) = *(int *)(iVar3 + 0x4c) + *(int *)(iVar6 + 0x4c) >> 1;
  
  // if driver is not using mask weapon
  if ((*(uint *)(iVar4 + 0x2c8) & 0x800000) == 0) 
  {
	// if ms remaining is not zero
    if (*(short *)(iVar5 + 4) != 0) 
	{
	  // reduce by elapsed time
      iVar2 = (uint)*(ushort *)(iVar5 + 4) - (uint)*(ushort *)(PTR_DAT_8008d2ac + 0x1d04);
      *(undefined2 *)(iVar5 + 4) = (short)iVar2;
      
	  // solve for negatives
	  if (iVar2 * 0x10000 < 0) {
        *(undefined2 *)(iVar5 + 4) = 0;
      }
	  
      if (*(short *)(iVar5 + 6) != 1) {
        return;
      }
	  
	  // If your weapon is "no weapon"
      if (*(char *)(iVar4 + 0x36) == '\x0f') {
        return;
      }
	  
	  // at this point, you must have a weapon
	  
      if (*(short *)(iVar4 + 0x3c) != 0) {
        return;
      }
	  
	  // set weapon to "weapon roulette" to make it spin
      *(undefined *)(iVar4 + 0x36) = 0x10;
	  
	  // you are always 5 frames away from new weapon,
	  // so you get weapon 5 frames after cloud dies
      *(undefined2 *)(iVar4 + 0x3a) = 5;
	  
	  // you hold zero of this item
      *(undefined *)(iVar4 + 0x37) = 0;
      return;
    }
	
	// at this point, you must not
	// have cloud above you
	
    *(undefined2 *)(iVar5 + 4) = 0;
	
	// erase cloudTh pointer
    *(undefined4 *)(iVar4 + 0x4a0) = 0;
    
	if (
			(*(short *)(iVar5 + 6) == 1) && 
			
			// If your weapon is not "no weapon"
			(*(char *)(iVar4 + 0x36) != '\x0f')
		)
	{
	  // erase item roll timer
      *(undefined2 *)(iVar4 + 0x3a) = 0;
	  
	  // pick random weapon for driver
      FUN_80060f0c(iVar4,0x800b0000);
    }
  }
  else {
    *(undefined2 *)(iVar5 + 4) = 0;
	
	// erase pointer to cloud thread
    *(undefined4 *)(iVar4 + 0x4a0) = 0;
  }
  
  // ThTick_SetAndExec RB_RainCloud_FadeAway
  FUN_800716ec(param_1,FUN_800b0f1c);
  return;
}

// RB_RainCloud_Init
void FUN_800b1220(int param_1)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  int *piVar4;
  
  // if driver -> cloudTh is invalid
  if (*(int *)(param_1 + 0x4a0) == 0) 
  {
	// make a thread for "cloud", and return an instance
	// 0x300 flag = SmallStackPool
	// 0xd = "other" thread bucket
    iVar1 = FUN_800309a4(0x42,s_cloud1_800aba10,0x300,0xd,FUN_800b1000,8,
	
						// driver -> instance -> thread
                         *(undefined4 *)(*(int *)(param_1 + 0x1c) + 0x6c));
	
	// set funcThDestroy to remove instance from instance pool	
    *(undefined4 *)(*(int *)(iVar1 + 0x6c) + 0x24) = 0x80041dfc;
	
	// Set rotation, 5 direction vectors
    *(undefined4 *)(iVar1 + 0x30) = 0x1000;
    *(undefined4 *)(iVar1 + 0x34) = 0;
    *(undefined4 *)(iVar1 + 0x38) = 0x1000;
    *(undefined4 *)(iVar1 + 0x3c) = 0;
    *(undefined2 *)(iVar1 + 0x40) = 0x1000;
	
	// cloud->posX = driver->posX
    *(undefined4 *)(iVar1 + 0x44) = *(undefined4 *)(*(int *)(param_1 + 0x1c) + 0x44);
	
	// cloud->posY = driver->posY + 0x80
    *(int *)(iVar1 + 0x48) = *(int *)(*(int *)(param_1 + 0x1c) + 0x48) + 0x80;
	
	// cloud->posZ = driver->posZ
    uVar3 = *(undefined4 *)(*(int *)(param_1 + 0x1c) + 0x4c);
	
    *(undefined2 *)(iVar1 + 0x22) = 0x800;
    *(undefined4 *)(iVar1 + 0x4c) = uVar3;
    *(undefined *)(iVar1 + 0x50) = *(undefined *)(*(int *)(param_1 + 0x1c) + 0x50);
    *(undefined *)(iVar1 + 0x51) = *(undefined *)(*(int *)(param_1 + 0x1c) + 0x51);
    
	// JitPool_Add -- Rain Pool
	iVar2 = FUN_800310d4(PTR_DAT_8008d2ac + 0x19e8);
    
	if (iVar2 != 0) {
      *(undefined4 *)(iVar2 + 8) = 0x1e;
      *(int *)(iVar2 + 0x24) = iVar1;
      *(undefined2 *)(iVar2 + 0xc) = 0;
      *(undefined2 *)(iVar2 + 0xe) = 0;
      *(undefined2 *)(iVar2 + 0x10) = 0;
      *(undefined2 *)(iVar2 + 0x14) = 0;
      *(undefined2 *)(iVar2 + 0x16) = 0xffd8;
      *(undefined2 *)(iVar2 + 0x18) = 0;
      *(undefined2 *)(iVar2 + 0x1c) = *(undefined2 *)(*(int *)(param_1 + 0x1c) + 0x44);
      *(short *)(iVar2 + 0x1e) = *(short *)(*(int *)(param_1 + 0x1c) + 0x48) + 0x80;
      *(undefined2 *)(iVar2 + 0x20) = *(undefined2 *)(*(int *)(param_1 + 0x1c) + 0x4c);
    }
    
	// raincloud instance -> thread -> object
	piVar4 = *(int **)(*(int *)(iVar1 + 0x6c) + 0x30);
	
	// set duration to about 7.68s
    *(undefined2 *)(piVar4 + 1) = 0x1e00;
	
    *piVar4 = iVar2;
    
	// used by driver 0x50a
	*(undefined2 *)((int)piVar4 + 6) = 1;
    
	if (
			// if driver has no weapon
			(*(char *)(param_1 + 0x36) == '\x0f') || 
			
			(*(short *)(param_1 + 0x3c) != 0)
		) 
	{
	  // used by driver 0x50a
      *(undefined2 *)((int)piVar4 + 6) = 0;
    }
	
	// driver -> thread = cloud -> thread
    *(undefined4 *)(param_1 + 0x4a0) = *(undefined4 *)(iVar1 + 0x6c);
  }
  
  // if cloud already exists, and 
  // driver hits another red potion
  else 
  {
	// set duration to 8 seconds
    *(undefined2 *)(*(int *)(*(int *)(param_1 + 0x4a0) + 0x30) + 4) = 0x1e00;
    
	// random number
	iVar1 = FUN_8003ea28();
	
	// random (related to driver offset 0x50a)
    *(undefined2 *)(*(int *)(*(int *)(param_1 + 0x4a0) + 0x30) + 6) = (short)((iVar1 % 400) / 100);
  }
  return;
}

// RB_Explosion_InitPotion
void FUN_800b1458(int param_1)
{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  int iVar6;
  int local_40;
  char *local_3c;
  undefined4 local_38;
  undefined4 local_34;
  code *local_30;
  undefined4 local_2c;
  undefined4 local_28;
  
  // green explosion
  local_40 = 0x45;
  
  // if instance -> model -> modelID == red beaker
  if (*(short *)(*(int *)(param_1 + 0x18) + 0x10) == 0x46) {
    
	// red explosion
	local_40 = 0x44;
  }
  
  // string
  local_3c = s_shatter1_800aba28;
  
  // 0x300 flag = SmallStackPool
  local_38 = 0x300;
  
  // 0xd = "other" thread bucket
  local_34 = 0xd;
  
  // RB_Explosion_ThTick
  local_30 = FUN_800ad92c;
  
  local_2c = 0;
  local_28 = 0;
  
  // create thread for shatter
  iVar1 = FUN_80030a50(&local_40);
  
  iVar6 = 0;
  *(uint *)(iVar1 + 0x28) = *(uint *)(iVar1 + 0x28) | 0xa00;
  
  // copy position and rotation from one instance to the other
  uVar3 = *(undefined4 *)(param_1 + 0x34);
  uVar4 = *(undefined4 *)(param_1 + 0x38);
  uVar5 = *(undefined4 *)(param_1 + 0x3c);
  *(undefined4 *)(iVar1 + 0x30) = *(undefined4 *)(param_1 + 0x30);
  *(undefined4 *)(iVar1 + 0x34) = uVar3;
  *(undefined4 *)(iVar1 + 0x38) = uVar4;
  *(undefined4 *)(iVar1 + 0x3c) = uVar5;
  uVar3 = *(undefined4 *)(param_1 + 0x44);
  uVar4 = *(undefined4 *)(param_1 + 0x48);
  uVar5 = *(undefined4 *)(param_1 + 0x4c);
  *(undefined4 *)(iVar1 + 0x40) = *(undefined4 *)(param_1 + 0x40);
  *(undefined4 *)(iVar1 + 0x44) = uVar3;
  *(undefined4 *)(iVar1 + 0x48) = uVar4;
  *(undefined4 *)(iVar1 + 0x4c) = uVar5;
  
  // set funcThDestroy to remove instance from instance pool
  *(undefined4 *)(*(int *)(iVar1 + 0x6c) + 0x24) = 0x80041dfc;
  
  // set scale
  *(undefined2 *)(iVar1 + 0x20) = 0x800;
  *(undefined2 *)(iVar1 + 0x1e) = 0x800;
  *(undefined2 *)(iVar1 + 0x1c) = 0x800;
  
  // particles for potion shatter
  do 
  {
	// DAT_800b2d58
	// unknown
	  
	// Create instance in particle pool
    iVar2 = FUN_80040308(0,*(undefined4 *)(PTR_DAT_8008d2ac + 0x2118),&DAT_800b2d58);
	
    if (iVar2 != 0) {
      *(int *)(iVar2 + 0x24) = *(int *)(iVar2 + 0x24) + *(int *)(iVar1 + 0x44) * 0x100;
      *(int *)(iVar2 + 0x2c) = *(int *)(iVar2 + 0x2c) + *(int *)(iVar1 + 0x48) * 0x100;
      *(int *)(iVar2 + 0x34) = *(int *)(iVar2 + 0x34) + *(int *)(iVar1 + 0x4c) * 0x100;
      if (local_40 == 0x45) {
        *(undefined4 *)(iVar2 + 0x5c) = 1;
        *(undefined4 *)(iVar2 + 100) = 0xc800;
      }
      else {
        *(undefined4 *)(iVar2 + 0x5c) = 0xc800;
        *(undefined4 *)(iVar2 + 100) = 1;
      }
      *(undefined4 *)(iVar2 + 0x6c) = 1;
	  
	  // Particle_FuncPtr_PotionShatter
      *(undefined4 *)(iVar2 + 0x1c) = 0x8003eae0;
      
	  *(int *)(iVar2 + 0x20) = local_40;
    }
    iVar6 = iVar6 + 1;
  } while (iVar6 < 5);
  
  // RB_Potion_OnShatter_TeethSearch
  FUN_800ac638(param_1);
  
  return;
}

// RB_Explosion_InitGeneric
void FUN_800b1630(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 local_28;
  char *local_24;
  undefined4 local_20;
  undefined4 local_1c;
  code *local_18;
  undefined4 local_14;
  undefined4 local_10;
  
  // Spawn exploded box
  local_28 = 0x26;
  
  // string
  local_24 = s_explosion1_800aba44;
  
  // 0x300 flag = SmallStackPool
  local_20 = 0x300;
  
  // 0xd = "other" thread bucket
  local_1c = 0xd;
  
  // RB_Explosion_ThTick
  local_18 = FUN_800ad92c;
  
  local_14 = 0;
  local_10 = 0;
  
  // create thread for explosion
  iVar1 = FUN_80030a50(&local_28);
  
  // copy position and rotation from one instance to the other
  uVar2 = *(undefined4 *)(param_1 + 0x34);
  uVar3 = *(undefined4 *)(param_1 + 0x38);
  uVar4 = *(undefined4 *)(param_1 + 0x3c);
  *(undefined4 *)(iVar1 + 0x30) = *(undefined4 *)(param_1 + 0x30);
  *(undefined4 *)(iVar1 + 0x34) = uVar2;
  *(undefined4 *)(iVar1 + 0x38) = uVar3;
  *(undefined4 *)(iVar1 + 0x3c) = uVar4;
  uVar2 = *(undefined4 *)(param_1 + 0x44);
  uVar3 = *(undefined4 *)(param_1 + 0x48);
  uVar4 = *(undefined4 *)(param_1 + 0x4c);
  *(undefined4 *)(iVar1 + 0x40) = *(undefined4 *)(param_1 + 0x40);
  *(undefined4 *)(iVar1 + 0x44) = uVar2;
  *(undefined4 *)(iVar1 + 0x48) = uVar3;
  *(undefined4 *)(iVar1 + 0x4c) = uVar4;
  
  // instance -> model -> modelID == TNT
  if (*(short *)(*(int *)(param_1 + 0x18) + 0x10) == 0x27) {
    
	// set color to red
	uVar2 = 0xad10000;
  }
  
  // not TNT
  else 
  {
	// set color to green
    uVar2 = 0x1eac000;
  }
  
  // set color
  *(undefined4 *)(iVar1 + 0x24) = uVar2;
  
  // set scale
  *(undefined2 *)(iVar1 + 0x22) = 0x1000;
  
  // set funcThDestroy to remove instance from instance pool
  *(undefined4 *)(*(int *)(iVar1 + 0x6c) + 0x24) = 0x80041dfc;
  return;
}

// RB_Blowup_ProcessBucket
void FUN_800b1714(int param_1)

{
  undefined *puVar1;
  undefined *puVar2;
  int iVar3;
  int iVar4;
  int *piVar5;
  int iVar6;
  
  puVar1 = PTR_DAT_8008d2ac;
  if (param_1 != 0) {
    do {
      puVar2 = PTR_DAT_8008d2ac;
      piVar5 = *(int **)(param_1 + 0x30);
      iVar6 = 0;
      if (puVar1[0x1ca8] != '\0') {
        iVar4 = 0;
        do {
          if ((*piVar5 != 0) && (iVar3 = piVar5[1] + iVar4, piVar5[1] != 0)) {
            *(uint *)(iVar3 + 0xb8) =
                 *(uint *)(iVar3 + 0xb8) & (*(uint *)(*piVar5 + iVar4 + 0xb8) | 0xffffffbf);
            *(undefined4 *)(piVar5[1] + iVar4 + 0xe4) = *(undefined4 *)(*piVar5 + iVar4 + 0xe4);
            *(undefined2 *)(piVar5[1] + iVar4 + 0xdc) = *(undefined2 *)(*piVar5 + iVar4 + 0xdc);
            *(undefined2 *)(piVar5[1] + iVar4 + 0xde) = *(undefined2 *)(*piVar5 + iVar4 + 0xde);
          }
          iVar6 = iVar6 + 1;
          iVar4 = iVar4 + 0x88;
        } while (iVar6 < (int)(uint)(byte)puVar2[0x1ca8]);
      }
      param_1 = *(int *)(param_1 + 0x10);
    } while (param_1 != 0);
  }
  return;
}

// RB_Blowup_ThTick
void FUN_800b17f0(int param_1)

{
  short sVar1;
  int iVar2;
  int *piVar3;
  
  // get object from thread
  piVar3 = *(int **)(param_1 + 0x30);
  do 
  {
	// get instance pointer
    iVar2 = piVar3[1];
	
	// if instance is valid
    if (iVar2 != 0) 
	{
	  // instance -> animFrame
      sVar1 = *(short *)(iVar2 + 0x54);
	  
	  // INSTANCE_GetNumAnimFrames
      iVar2 = FUN_80030f58(iVar2,0);
	  
	  // if animation is not done
      if ((int)sVar1 + 1 < iVar2) 
	  {
		// increment animation frame
        *(short *)(piVar3[1] + 0x54) = *(short *)(piVar3[1] + 0x54) + 1;
      }
	  
	  // if animation is done
      else 
	  {
		// INSTANCE_Death
        FUN_80030aa8(piVar3[1]);
        piVar3[1] = 0;
      }
    }
	
	// get instance pointer
    iVar2 = *piVar3;
	
	// if instance 
    if (iVar2 != 0) 
	{
	  // instance -> animFrame
      sVar1 = *(short *)(iVar2 + 0x54);
	  
	  // INSTANCE_GetNumAnimFrames
      iVar2 = FUN_80030f58(iVar2,0);
	  
	  // if animation is not over
      if ((int)sVar1 + 1 < iVar2) 
	  {
		// increment animation frame
        *(short *)(*piVar3 + 0x54) = *(short *)(*piVar3 + 0x54) + 1;
      }
	  
	  // if animation is done
      else 
	  {
		// INSTANCE_Death
        FUN_80030aa8(*piVar3);
        *piVar3 = 0;
      }
    }
	
	// if either instance has been erased
    if ((piVar3[1] == 0) && (*piVar3 == 0)) 
	{
	  // This thread is now dead
      *(uint *)(param_1 + 0x1c) = *(uint *)(param_1 + 0x1c) | 0x800;
    }
	
	// this skips $RA backup/restore, faster than JR $RA
    FUN_80071694(param_1);
	
  } while( true );
}

// RB_Blowup_Init
void FUN_800b18f8(int param_1)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  int *piVar6;
  undefined4 local_30;
  char *local_2c;
  undefined4 local_28;
  undefined4 local_24;
  code *local_20;
  undefined4 local_1c;
  undefined4 local_18;
  
  // spawn explosion
  local_30 = 0x26;
  
  // string
  local_2c = s_blowup_800aba60;
  
  // 0x300 flag = SmallStackPool
  local_28 = 0x300;
  
  // 8 = "blowup" thread bucket
  local_24 = 8;
  
  // RB_Blowup_ThTick
  local_20 = FUN_800b17f0;
  
  local_1c = 0xc;
  local_18 = 0;
  
  // initialize thread for blowup
  iVar1 = FUN_80030a50(&local_30);
  
  *(uint *)(iVar1 + 0x28) = *(uint *)(iVar1 + 0x28) | 0x2040000;
  
  // instance -> thread -> object
  piVar6 = *(int **)(*(int *)(iVar1 + 0x6c) + 0x30);
  
  // set explosion instance
  piVar6[1] = iVar1;
  
  // copy position and rotation from weapon to explosion
  uVar3 = *(undefined4 *)(param_1 + 0x34);
  uVar4 = *(undefined4 *)(param_1 + 0x38);
  uVar5 = *(undefined4 *)(param_1 + 0x3c);
  *(undefined4 *)(iVar1 + 0x30) = *(undefined4 *)(param_1 + 0x30);
  *(undefined4 *)(iVar1 + 0x34) = uVar3;
  *(undefined4 *)(iVar1 + 0x38) = uVar4;
  *(undefined4 *)(iVar1 + 0x3c) = uVar5;
  uVar3 = *(undefined4 *)(param_1 + 0x44);
  uVar4 = *(undefined4 *)(param_1 + 0x48);
  uVar5 = *(undefined4 *)(param_1 + 0x4c);
  *(undefined4 *)(iVar1 + 0x40) = *(undefined4 *)(param_1 + 0x40);
  *(undefined4 *)(iVar1 + 0x44) = uVar3;
  *(undefined4 *)(iVar1 + 0x48) = uVar4;
  *(undefined4 *)(iVar1 + 0x4c) = uVar5;
  
  // if instance -> model -> modelID == tnt
  if (*(short *)(*(int *)(param_1 + 0x18) + 0x10) == 0x27) 
  {
	// set color to red
    uVar3 = 0xad10000;
  }
  
  // if it is not tnt
  else 
  {
	// set color to green
    uVar3 = 0x1eac000;
  }
  
  // set color
  *(undefined4 *)(iVar1 + 0x24) = uVar3;
  
  // set scale
  *(undefined2 *)(iVar1 + 0x22) = 0x1000;
  
  // green shockwave
  iVar1 = 0x45;
  
  // if instance -> model -> modelID == tnt
  if (*(short *)(*(int *)(param_1 + 0x18) + 0x10) == 0x27) 
  {
	// red shockwave
    iVar1 = 0x44;
  }
  
  // INSTANCE_Birth3D -- ptrModel, name, thread
  iVar1 = FUN_8003086c(*(undefined4 *)(PTR_DAT_8008d2ac + iVar1 * 4 + 0x2160),
                       s_shockwave1_800aba78);
  
  // set shockwave instance
  *piVar6 = iVar1;
  
  // instane flags
  *(uint *)(iVar1 + 0x28) = *(uint *)(iVar1 + 0x28) | 0x200;
  
  // set showckwave position to weapon position
  *(undefined4 *)(iVar1 + 0x44) = *(undefined4 *)(param_1 + 0x44);
  *(undefined4 *)(iVar1 + 0x48) = *(undefined4 *)(param_1 + 0x48);
  *(undefined4 *)(iVar1 + 0x4c) = *(undefined4 *)(param_1 + 0x4c);
  
  // shockwaveInst -> model -> modelHeader,
  // there is only one header in this model
  iVar2 = *(int *)(*(int *)(iVar1 + 0x18) + 0x14);
  
  // modelHeader -> flags
  // set flag to always point to camera
  *(ushort *)(iVar2 + 0x16) = *(ushort *)(iVar2 + 0x16) | 2;
  
  // Do it again? Should this be explosion instance?
  iVar2 = *(int *)(*(int *)(iVar1 + 0x18) + 0x14);
  *(ushort *)(iVar2 + 0x56) = *(ushort *)(iVar2 + 0x56) | 2;
  
  // Instance -> matrix, Identity 3x3 rotation
  *(undefined4 *)(iVar1 + 0x30) = 0x1000;
  *(undefined4 *)(iVar1 + 0x34) = 0;
  *(undefined4 *)(iVar1 + 0x38) = 0x1000;
  *(undefined4 *)(iVar1 + 0x3c) = 0;
  *(undefined2 *)(iVar1 + 0x40) = 0x1000;
  
  // put weapon position on scratchpad
  DAT_1f800108 = *(undefined2 *)(param_1 + 0x44);
  DAT_1f80010a = *(undefined2 *)(param_1 + 0x48);
  DAT_1f80010c = *(undefined2 *)(param_1 + 0x4c);
  
  // if you're in boss mode
  if (*(int *)PTR_DAT_8008d2ac < 0) 
  {
	// hitRadius and hitRadiusSquared
    DAT_1f80010e = 0x100;
    _DAT_1f800110 = 0x10000;
  }
  
  // if you're not in boss mode
  else 
  {
	// hitRadius and hitRadiusSquared
    DAT_1f80010e = 0x140;
    _DAT_1f800110 = 0x19000;
  }
  
  // RB_Burst_CollThBucket
  DAT_1f800130 = FUN_800b1e90;
  
  // instance -> thread
  DAT_1f800120 = *(undefined4 *)(param_1 + 0x6c);
  
  // thread -> model -> modelID
  DAT_1f800114 = *(undefined2 *)(*(int *)(param_1 + 0x18) + 0x10);
  
  // PROC_StartSearch_Self
  FUN_80042544(&DAT_1f800108);
  
  // check collision with all robotcar thread
  FUN_800425d4(*(undefined4 *)(PTR_DAT_8008d2ac + 0x1b40),&DAT_1f800108,0);
  
  // check collision with all Mine thread
  FUN_800425d4(*(undefined4 *)(PTR_DAT_8008d2ac + 0x1b7c),&DAT_1f800108,0);
  
  // If this is TNT
  if (*(short *)(*(int *)(param_1 + 0x18) + 0x10) == 0x27) {
    
	// pointer to first player thread
	uVar3 = *(undefined4 *)(PTR_DAT_8008d2ac + 0x1b2c);
  }
  
  // if not TNT
  else 
  {
	// hitRadius and hitRadiusSquared
    DAT_1f80010e = 0x80;
    _DAT_1f800110 = 0x4000;
	
	// pointer to first player thread
    uVar3 = *(undefined4 *)(PTR_DAT_8008d2ac + 0x1b2c);
  }
  
  // check collision with player threads
  FUN_800425d4(uVar3,&DAT_1f800108,0);
  
  // RB_Burst_CollLevInst
  DAT_1f800130 = FUN_800b20a4;
  return;
}

// RB_Burst_ProcessBucket
void FUN_800b1bd8(int param_1)

{
  undefined *puVar1;
  undefined *puVar2;
  int iVar3;
  int iVar4;
  int *piVar5;
  int iVar6;
  
  puVar1 = PTR_DAT_8008d2ac;
  if (param_1 != 0) {
    do {
      puVar2 = PTR_DAT_8008d2ac;
      piVar5 = *(int **)(param_1 + 0x30);
      iVar6 = 0;
      if (puVar1[0x1ca8] != '\0') {
        iVar4 = 0;
        do {
          if (piVar5[1] != 0) {
            iVar3 = *piVar5 + iVar4;
            if (*piVar5 != 0) {
              *(uint *)(iVar3 + 0xb8) =
                   *(uint *)(iVar3 + 0xb8) & (*(uint *)(piVar5[1] + iVar4 + 0xb8) | 0xffffffbf);
              *(undefined4 *)(*piVar5 + iVar4 + 0xe4) = *(undefined4 *)(piVar5[1] + iVar4 + 0xe4);
              *(undefined2 *)(*piVar5 + iVar4 + 0xdc) = *(undefined2 *)(piVar5[1] + iVar4 + 0xdc);
              *(undefined2 *)(*piVar5 + iVar4 + 0xde) = *(undefined2 *)(piVar5[1] + iVar4 + 0xde);
            }
            iVar3 = piVar5[2] + iVar4;
            if (piVar5[2] != 0) {
              *(uint *)(iVar3 + 0xb8) =
                   *(uint *)(iVar3 + 0xb8) & (*(uint *)(piVar5[1] + iVar4 + 0xb8) | 0xffffffbf);
              *(undefined4 *)(piVar5[2] + iVar4 + 0xe4) = *(undefined4 *)(piVar5[1] + iVar4 + 0xe4);
              *(undefined2 *)(piVar5[2] + iVar4 + 0xdc) = *(undefined2 *)(piVar5[1] + iVar4 + 0xdc);
              *(undefined2 *)(piVar5[2] + iVar4 + 0xde) = *(undefined2 *)(piVar5[1] + iVar4 + 0xde);
            }
          }
          iVar6 = iVar6 + 1;
          iVar4 = iVar4 + 0x88;
        } while (iVar6 < (int)(uint)(byte)puVar2[0x1ca8]);
      }
      param_1 = *(int *)(param_1 + 0x10);
    } while (param_1 != 0);
  }
  return;
}

// RB_Burst_ThTick
void FUN_800b1d2c(int param_1)

{
  short sVar1;
  int iVar2;
  int *piVar3;
  
  // thread -> object
  piVar3 = *(int **)(param_1 + 0x30);
  
  // get instance pointer
  iVar2 = piVar3[1];
  
  // get instance pointer
  if (iVar2 != 0) 
  {
	// instance -> animFrame
    sVar1 = *(short *)(iVar2 + 0x54);
	
	// INSTANCE_GetNumAnimFrames
    iVar2 = FUN_80030f58(iVar2,0);
	
	// if animation is not done
    if ((int)sVar1 + 1 < iVar2) 
	{
	  // increment animation frame
      *(short *)(piVar3[1] + 0x54) = *(short *)(piVar3[1] + 0x54) + 1;
    }
	
	// if animation is done
    else 
	{
	  // INSTANCE_Death
      FUN_80030aa8(piVar3[1]);
      piVar3[1] = 0;
    }
  }
  
  // get instance pointer
  iVar2 = piVar3[2];
  
  // if instance is valid
  if (iVar2 != 0) 
  {
	// get animation frame
    sVar1 = *(short *)(iVar2 + 0x54);
	
	// INSTANCE_GetNumAnimFrames
    iVar2 = FUN_80030f58(iVar2,0);
	
	// if animation is not done
    if ((int)sVar1 + 1 < iVar2) 
	{
	  // increment animation frame
      *(short *)(piVar3[2] + 0x54) = *(short *)(piVar3[2] + 0x54) + 1;
    }
	
	// if animation is done
    else 
	{
	  // INSTANCE_Death
      FUN_80030aa8(piVar3[2]);
      piVar3[2] = 0;
    }
  }
  
  // get instance pointer
  iVar2 = *piVar3;
  
  // if instance is valid
  if (iVar2 != 0) 
  {
	// instance -> animationFrame
    sVar1 = *(short *)(iVar2 + 0x54);
	
	// INSTANCE_GetNumAnimFrames
    iVar2 = FUN_80030f58(iVar2,0);
	
	// if animation is not done
    if ((int)sVar1 + 1 < iVar2) 
	{
	  // increase animation frame
      *(short *)(*piVar3 + 0x54) = *(short *)(*piVar3 + 0x54) + 1;
    }
	
	// if animation is done
    else 
	{
	  // INSTANCE_Death
      FUN_80030aa8(*piVar3);
      *piVar3 = 0;
    }
  }
  
  // if instances have been erased
  if ((piVar3[1] == 0) && (piVar3[2] == 0)) 
  {
	// This thread is now dead
    *(uint *)(param_1 + 0x1c) = *(uint *)(param_1 + 0x1c) | 0x800;
  }
  return;
}

// RB_Burst_CollThBucket
// callback when searching thread buckets
void FUN_800b1e90(int param_1,int param_2)

{
  undefined *puVar1;
  code *pcVar2;
  short sVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  int iVar6;
  int iVar7;
  
  // BSP_Meta -> weaponthread -> object
  iVar7 = *(int *)(*(int *)(param_1 + 0x18) + 0x30);
  
  // get modelID from thread
  sVar3 = *(short *)(param_2 + 0x44);
  
  // if this is a player of any kind, or robotcar of any kind
  if ((sVar3 == 0x18) || (sVar3 == 0x3f)) 
  {
	// BSP_Meta -> weaponthread -> modelID
    sVar3 = *(short *)(*(int *)(param_1 + 0x18) + 0x44);
	
	// nitro, green beaker, red beaker, TNT
    if ((sVar3 == 6) || (((sVar3 == 0x46 || (sVar3 == 0x47)) || (sVar3 == 0x27)))) 
	{
	  // RB_Hazard_HurtDriver (blasted)
      FUN_800ac1b0
                (*(undefined4 *)(param_2 + 0x30),2,
                 *(undefined4 *)(*(int *)(*(int *)(iVar7 + 4) + 0x6c) + 0x30),2);
    }
    else {
      iVar6 = *(int *)(*(int *)(*(int *)(iVar7 + 8) + 0x6c) + 0x30);
	  
	  // missile
      if (sVar3 == 0x29) {
        uVar4 = *(undefined4 *)(param_2 + 0x30);
        uVar5 = 3;
      }
	  
	  // bomb
      else {
        uVar4 = *(undefined4 *)(param_2 + 0x30);
        uVar5 = 1;
      }
	  
	  // RB_Hazard_HurtDriver (blasted)
      FUN_800ac1b0(uVar4,2,iVar6,uVar5);
	  
      if ((int)*(short *)(iVar6 + 0x552) < *(int *)(iVar7 + 0x48)) {
        *(undefined2 *)(iVar6 + 0x552) = *(undefined2 *)(iVar7 + 0x48);
      }
    }
    puVar1 = PTR_DAT_8008d2ac;
	
	// thread -> driver object -> flags
	// if this driver is not an AI
    if ((*(uint *)(*(int *)(param_2 + 0x30) + 0x2c8) & 0x100000) == 0) 
	{
      *(undefined2 *)
       (PTR_DAT_8008d2ac + (uint)*(byte *)(*(int *)(param_2 + 0x30) + 0x4a) * 0x110 + 0x17a) =
           0x1fff;
      *(undefined2 *)(puVar1 + (uint)*(byte *)(*(int *)(param_2 + 0x30) + 0x4a) * 0x110 + 0x17c) =
           0x1000;
      *(undefined2 *)(puVar1 + (uint)*(byte *)(*(int *)(param_2 + 0x30) + 0x4a) * 0x110 + 0x17e) =
           0xff78;
    }
	
	// icon damage timer, draw icon as red
    *(undefined4 *)(*(int *)(param_2 + 0x30) + 0x4ac) = 0x1e;
    
	// get modelID from thread
	sVar3 = *(short *)(param_2 + 0x44);
  }
  
  // not DYNAMIC_ROCKET
  if (sVar3 != 0x29) 
  {
    if (sVar3 < 0x2a) 
	{
	  // not nitro and not STATIC_CRATE_TNT
      if ((sVar3 != 6) && (sVar3 != 0x27)) {
        return;
      }
    }
    
	else 
	{
	  // return if anything that isn't beakers
		
      if (0x47 < sVar3) {
        return;
      }
      if (sVar3 < 0x46) {
        return;
      }
    }
  }
  
  // get funcThCollide
  pcVar2 = *(code **)(param_2 + 0x28);
  
  // if function pointer is valid
  if (pcVar2 != (code *)0x0) 
  {
	// execute funcThCollide
    (*pcVar2)(param_2,*(undefined4 *)(param_1 + 0x18),pcVar2,3);
  }
  return;
}

// RB_Burst_CollLevInst (bsp callback)
// param_1 - 1f800108
// param_2 - bsp (hitbox)
void FUN_800b20a4(int param_1,int param_2)

{
  short sVar1;
  int iVar2;
  int iVar3;
  
  // bsp->hitbox.instDef
  iVar2 = *(int *)(param_2 + 0x1c);
  
  if (
		// if InstDef exists
		(iVar2 != 0) && 
		
		// InstDef -> Instance
		(iVar3 = *(int *)(iVar2 + 0x2c), iVar3 != 0)
	  ) 
  {
	// modelID
    sVar1 = *(short *)(iVar2 + 0x3c);
    
	if (6 < sVar1) 
	{
	  // check 7 and 8,
	  // 7: PU_FRUIT_CRATE
	  // 8: PU_RANDOM_CRATE (weapon box)
      if (sVar1 < 9) 
	  {
		// ThreadMeta
        iVar2 = FUN_8001d094();
		
		// if funcLevThreadsBirth is not nullptr
        if ((iVar2 != 0) && (*(code **)(iVar2 + 8) != (code *)0x0)) 
		{
		  // execute funcLevThreadsBirth, make thread for this instance
		  // upon collision with the instance, let it run thread->funcThCollide
          (**(code **)(iVar2 + 8))(iVar3,*(undefined4 *)(param_1 + 0x18),param_1);
        }
      }
      else 
	  {
		// modelID == teeth
        if (sVar1 == 0x70) 
		{
		  // RB_Teeth_OpenDoor
          FUN_800ba220(iVar3);
        }
      }
    }
  }
  return;
}

// RB_Burst_Init
void FUN_800b2154(int param_1)

{
  undefined *puVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  int iVar5;
  undefined4 local_40;
  char *local_3c;
  undefined4 local_38;
  undefined4 local_34;
  code *local_30;
  undefined4 local_2c;
  undefined4 local_28;
  
  // instance -> thread -> object
  iVar5 = *(int *)(*(int *)(param_1 + 0x6c) + 0x30);
  
  // model index of explosion
  local_40 = 0x2b;
  
  // string
  local_3c = s_explosion1_800aba44;
  
  // small stack pool
  local_38 = 0x300;
  
  // 7 = "burst" thread bucket
  local_34 = 7;
  
  // RB_Burst_ThTick
  local_30 = FUN_800b1d2c;
  
  local_2c = 0xc;
  local_28 = 0;
  
  // initialize thread for burst
  iVar2 = FUN_80030a50(&local_40);
  
  // get thread from instance
  iVar3 = *(int *)(iVar2 + 0x6c);
  
  // get object from thread
  piVar4 = *(int **)(iVar3 + 0x30);
  
  piVar4[1] = iVar2;
  *(char *)(iVar2 + 0x50) = *(char *)(iVar2 + 0x50) + -2;
  *(undefined4 *)(iVar2 + 0x44) = *(undefined4 *)(param_1 + 0x44);
  puVar1 = PTR_DAT_8008d2ac;
  *(int *)(iVar2 + 0x48) = *(int *)(param_1 + 0x48) + -0x30;
  *(undefined4 *)(iVar2 + 0x4c) = *(undefined4 *)(param_1 + 0x4c);
  
  // if more than 2 screens
  if (2 < (byte)puVar1[0x1ca8]) 
  {
	// divide scale by 2
    *(short *)(iVar2 + 0x1c) = *(short *)(iVar2 + 0x1c) >> 1;
    *(short *)(iVar2 + 0x1e) = *(short *)(iVar2 + 0x1e) >> 1;
    *(short *)(iVar2 + 0x20) = *(short *)(iVar2 + 0x20) >> 1;
  }
  
  // set rotation to identity matrix
  *(undefined4 *)(iVar2 + 0x30) = 0x1000;
  *(undefined4 *)(iVar2 + 0x34) = 0;
  *(undefined4 *)(iVar2 + 0x38) = 0x1000;
  *(undefined4 *)(iVar2 + 0x3c) = 0;
  *(undefined2 *)(iVar2 + 0x40) = 0x1000;
  
  puVar1 = PTR_DAT_8008d2ac;
  
  // instance -> model -> modelHeader
  iVar2 = *(int *)(*(int *)(iVar2 + 0x18) + 0x14);
  
  // header -> flags: always face camera
  *(ushort *)(iVar2 + 0x16) = *(ushort *)(iVar2 + 0x16) | 2;
  
  // INSTANCE_Birth3D -- ptrModel, name, thread
  iVar2 = FUN_8003086c(*(undefined4 *)(puVar1 + 0x220c),s_explosion2_800aba94,iVar3);
  
  piVar4[2] = iVar2;
  
  // instance flags
  *(uint *)(iVar2 + 0x28) = *(uint *)(iVar2 + 0x28) | 0x2000000;
  
  *(char *)(iVar2 + 0x50) = *(char *)(iVar2 + 0x50) + -2;
  
  // X position
  *(undefined4 *)(iVar2 + 0x44) = *(undefined4 *)(param_1 + 0x44);
  
  puVar1 = PTR_DAT_8008d2ac;
  
  // Y position
  *(int *)(iVar2 + 0x48) = *(int *)(param_1 + 0x48) + -0x30;
  
  // Z position
  *(undefined4 *)(iVar2 + 0x4c) = *(undefined4 *)(param_1 + 0x4c);
  
  // if more than 2 screens
  if (2 < (byte)puVar1[0x1ca8]) 
  {
	// scale (x, y, z)
    *(short *)(iVar2 + 0x1c) = *(short *)(iVar2 + 0x1c) >> 1;
    *(short *)(iVar2 + 0x1e) = *(short *)(iVar2 + 0x1e) >> 1;
    *(short *)(iVar2 + 0x20) = *(short *)(iVar2 + 0x20) >> 1;
  }
  
  *(undefined2 *)(iVar2 + 0x32) = 0xf000;
  *(undefined2 *)(iVar2 + 0x30) = 0;
  *(undefined2 *)(iVar2 + 0x34) = 0;
  *(undefined2 *)(iVar2 + 0x36) = 0x1000;
  *(undefined2 *)(iVar2 + 0x38) = 0;
  *(undefined2 *)(iVar2 + 0x3a) = 0;
  *(undefined2 *)(iVar2 + 0x3c) = 0;
  *(undefined2 *)(iVar2 + 0x3e) = 0;
  *(undefined2 *)(iVar2 + 0x40) = 0x1000;
  puVar1 = PTR_DAT_8008d2ac;
  
  // instance -> model -> modelHeader
  iVar2 = *(int *)(*(int *)(iVar2 + 0x18) + 0x14);
  
  // header -> flags: always face camera
  *(ushort *)(iVar2 + 0x16) = *(ushort *)(iVar2 + 0x16) | 2;
  
  // INSTANCE_Birth3D -- ptrModel, name, thread
  iVar2 = FUN_8003086c(*(undefined4 *)(puVar1 + 0x2270),s_shockwave1_800aba78,iVar3);
  
  *piVar4 = iVar2;
  
  // instance flags
  *(uint *)(iVar2 + 0x28) = *(uint *)(iVar2 + 0x28) | 0x2040000;
  
  *(char *)(iVar2 + 0x50) = *(char *)(iVar2 + 0x50) + -2;
  *(undefined4 *)(iVar2 + 0x44) = *(undefined4 *)(param_1 + 0x44);
  puVar1 = PTR_DAT_8008d2ac;
  *(int *)(iVar2 + 0x48) = *(int *)(param_1 + 0x48) + -0x30;
  *(undefined4 *)(iVar2 + 0x4c) = *(undefined4 *)(param_1 + 0x4c);
  
  // if more than two screens
  if (2 < (byte)puVar1[0x1ca8]) 
  {
	// set scale (x, y, z)
    *(short *)(iVar2 + 0x1c) = *(short *)(iVar2 + 0x1c) >> 1;
    *(short *)(iVar2 + 0x1e) = *(short *)(iVar2 + 0x1e) >> 1;
    *(short *)(iVar2 + 0x20) = *(short *)(iVar2 + 0x20) >> 1;
  }
  
  // identity matrix
  *(undefined4 *)(iVar2 + 0x30) = 0x1000;
  *(undefined4 *)(iVar2 + 0x34) = 0;
  *(undefined4 *)(iVar2 + 0x38) = 0x1000;
  *(undefined4 *)(iVar2 + 0x3c) = 0;
  *(undefined2 *)(iVar2 + 0x40) = 0x1000;
  
  // instance -> model -> modelHeader
  iVar3 = *(int *)(*(int *)(iVar2 + 0x18) + 0x14);
  
  // header -> flags: always face camera
  *(ushort *)(iVar3 + 0x16) = *(ushort *)(iVar3 + 0x16) | 2;
  
  iVar2 = *(int *)(*(int *)(iVar2 + 0x18) + 0x14);
  *(ushort *)(iVar2 + 0x56) = *(ushort *)(iVar2 + 0x56) | 2;
  
  // ======= End of Instance =========
  
  DAT_1f800108 = *(undefined2 *)(param_1 + 0x44);
  DAT_1f80010a = *(undefined2 *)(param_1 + 0x48);
  DAT_1f80010c = *(undefined2 *)(param_1 + 0x4c);
  
  // instance -> model -> modelID == missile
  if (*(short *)(*(int *)(param_1 + 0x18) + 0x10) == 0x29) 
  {
	// hitRadius and hitRadiusSquared
    DAT_1f80010e = 0x80;
    _DAT_1f800110 = 0x4000;
  }
  else 
  {
									// instance -> thread -> object
    if ((*(ushort *)(*(int *)(*(int *)(param_1 + 0x6c) + 0x30) + 0x16) & 1) == 0) 
	{
	  // hitRadius and hitRadiusSquared
      DAT_1f80010e = 0x140;
      _DAT_1f800110 = 0x19000;
    }
    else 
	{
	  // hitRadius and hitRadiusSquared
      DAT_1f80010e = 0x200;
      _DAT_1f800110 = 0x40000;
    }
  }
  
  // RB_Burst_CollThBucket (callback for threadbucket collision)
  DAT_1f800130 = FUN_800b1e90;
  
  // instance -> thread
  DAT_1f800120 = *(undefined4 *)(param_1 + 0x6c);
  
  // instance -> model -> modelID
  DAT_1f800114 = *(undefined2 *)(*(int *)(param_1 + 0x18) + 0x10);
  
  // check collision with all Player thread
  FUN_800425d4(*(undefined4 *)(PTR_DAT_8008d2ac + 0x1b2c),&DAT_1f800108,
               *(undefined4 *)(*(int *)(*(int *)(iVar5 + 4) + 0x1c) + 0x6c));

  // check collision with all Robotcar thread
  FUN_800425d4(*(undefined4 *)(PTR_DAT_8008d2ac + 0x1b40),&DAT_1f800108,
               *(undefined4 *)(*(int *)(*(int *)(iVar5 + 4) + 0x1c) + 0x6c));
			   
  // check collision with all Mine thread
  FUN_800425d4(*(undefined4 *)(PTR_DAT_8008d2ac + 0x1b7c),&DAT_1f800108,0);
  
  // check collision with all Tracking thread
  FUN_800425d4(*(undefined4 *)(PTR_DAT_8008d2ac + 0x1ba4),&DAT_1f800108,0);
  
  // RB_Burst_CollLevInst (callback for BSP collision)
  DAT_1f800130 = FUN_800b20a4;
  
  // PROC_StartSearch_Self
  FUN_80042544(&DAT_1f800108);
  return;
}

// RB_Burst_DrawAll
void FUN_800b25b8(int param_1)

{
  char cVar1;
  undefined4 in_zero;
  undefined4 in_at;
  int iVar2;
  int *piVar3;
  int iVar4;
  int *piVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int local_70 [4];
  int local_60 [4];
  undefined4 local_50;
  uint local_4c;
  int local_48;
  int local_44;
  int local_40;
  int local_38;
  int local_34;
  int local_30;
  
  // numPlyrCurrGame
  cVar1 = *(char *)(param_1 + 0x1ca8);
  iVar8 = 0;
  
  // if numPlyrCurrGame is not zero
  if (cVar1 != '\0') {
    piVar3 = local_60;
    piVar5 = local_70;
    iVar10 = 0x168;
    iVar9 = param_1;
    do 
	{
	  // pointer to first burst thread
      iVar7 = *(int *)(param_1 + 0x1bb8);
	  
      iVar6 = param_1 + iVar10 + 0x28;
      *piVar5 = 0x10000;
      *piVar3 = 0;
      iVar2 = *(int *)(iVar9 + 0x180);
      FUN_800718fc(iVar6);
      FUN_800718dc(iVar6);
      while (iVar7 != 0) {
        iVar6 = *(int *)(iVar7 + 0x30);
        iVar4 = *(int *)(iVar6 + 4);
        local_50 = CONCAT22(*(undefined2 *)(iVar4 + 0x48),*(undefined2 *)(iVar4 + 0x44));
        local_4c = local_4c & 0xffff0000 | (uint)*(ushort *)(iVar4 + 0x4c);
        setCopReg(2,in_zero,local_50);
        setCopReg(2,in_at,local_4c);
        
		// rtv0tr   cop2 $0480012  v0 * rotmatrix + tr vector
		copFunction(2,0x480012);
        
		local_38 = getCopReg(2,0x19);
        local_48 = local_38;
        local_34 = getCopReg(2,0x1a);
        local_44 = local_34;
        local_30 = getCopReg(2,0x1b);
        local_40 = local_30;
        if (local_38 < 0) {
          local_38 = -local_38;
        }
        if (local_34 < 0) {
          local_34 = -local_34;
        }
        if (local_30 < 0) {
          local_30 = -local_30;
        }
        if (((local_38 < 0x100) && (local_34 < 0x100)) && (local_30 < iVar2 << 1)) {
          if ((int)*(short *)(iVar4 + 0x54) < *piVar5) {
            *piVar5 = (int)*(short *)(iVar4 + 0x54);
            *piVar3 = iVar7;
          }
          if (*(short *)(*(int *)(iVar6 + 4) + 0x54) == 1) {
            *(undefined2 *)(iVar9 + 0x17c) = 0x1000;
            *(undefined2 *)(iVar9 + 0x17e) = 0xff78;
            *(short *)(iVar9 + 0x17a) = ((short)local_38 + (short)local_34) * -8 + 0x1fff;
          }
        }
		
		// thread = thread->next
        iVar7 = *(int *)(iVar7 + 0x10);
      }
      iVar9 = iVar9 + 0x110;
      piVar3 = piVar3 + 1;
      piVar5 = piVar5 + 1;
      iVar8 = iVar8 + 1;
      iVar10 = iVar10 + 0x110;
    } while (iVar8 < (int)(uint)*(byte *)(param_1 + 0x1ca8));
	
	// numPlyrCurrGame
    cVar1 = *(char *)(param_1 + 0x1ca8);
  }
  
  // iteration counter
  iVar8 = 0;
  
  // if numPlyrCurrGame is not zero
  if (cVar1 != '\0') {
    iVar10 = 0x168;
    iVar9 = 0;
    piVar5 = local_60;
	
	// for iVar8 = 0; iVar8 < numPlyrCurrGame; iVar8++
    do 
	{
	  // pointer to first burst thread
      iVar7 = *(int *)(param_1 + 0x1bb8);
	  
      if (iVar7 != 0) {
        iVar2 = param_1 + iVar10;
        do {
          piVar3 = *(int **)(iVar7 + 0x30);
          if ((*piVar5 == 0) || (*piVar5 == iVar7)) {
            if (piVar3[1] != 0) {
              *(int *)(piVar3[1] + iVar9 + 0x74) = iVar2;
            }
            if (piVar3[2] != 0) {
              *(int *)(piVar3[2] + iVar9 + 0x74) = iVar2;
            }
            if (*piVar3 != 0) {
              *(int *)(*piVar3 + iVar9 + 0x74) = iVar2;
            }
          }
          else {
            if (piVar3[1] != 0) {
              *(undefined4 *)(piVar3[1] + iVar9 + 0x74) = 0;
            }
            if (piVar3[2] != 0) {
              *(undefined4 *)(piVar3[2] + iVar9 + 0x74) = 0;
            }
            if (*piVar3 != 0) {
              *(undefined4 *)(*piVar3 + iVar9 + 0x74) = 0;
            }
          }
          iVar7 = *(int *)(iVar7 + 0x10);
        } while (iVar7 != 0);
      }
      iVar10 = iVar10 + 0x110;
      iVar9 = iVar9 + 0x88;
	  
	  // increment loop counter
      iVar8 = iVar8 + 1;
	  
      piVar5 = piVar5 + 1;
    } while (iVar8 < (int)(uint)*(byte *)(param_1 + 0x1ca8));
  }
  return;
}

// RB_GetThread_ClosestTracker (warpball or missile)
int FUN_800b28c0(int param_1)
{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  // assume farthest position
  iVar4 = 0x3fffffff;
  
  // pointer to first Tracking thread
  iVar3 = *(int *)(PTR_DAT_8008d2ac + 0x1ba4);
  
  // return thread = nullptr
  iVar5 = 0;
  
  // loop through all threads
  while (iVar3 != 0) {
    if (
			// if first item in thread's object is param_1,
			// meaning, if tracker is chasing this driver
			(**(int **)(iVar3 + 0x30) == param_1) &&
			(
				// get distance between posX and posZ of 
				// driver->instSelf->position, and tracker's position, 
				iVar1 = *(int *)(*(int *)(param_1 + 0x1c) + 0x44) - *(int *)(*(int *)(iVar3 + 0x34) + 0x44),
				iVar2 = *(int *)(*(int *)(param_1 + 0x1c) + 0x4c) - *(int *)(*(int *)(iVar3 + 0x34) + 0x4c),
				
				// if this is a new closest distance
				iVar1 = iVar1 * iVar1 + iVar2 * iVar2, iVar1 < iVar4
			)
	  ) 
	{
	  // save closest distance
      iVar4 = iVar1;
	  
	  // save thread
      iVar5 = iVar3;
    }
	
	// thread = thread->next
    iVar3 = *(int *)(iVar3 + 0x10);
  }
  
  // return thread of cloest tracker
  return iVar5;
}

// 800b2e9c LinkedList MinePool_Taken
// 800b2ea8 LinkedList MinePool_Free
// 800b2eb4 char MineData[0x32][0xC] // max 50 members, 0xC bytes each
// 800b310c char baron[0x8]
// 800b3114 char drumbuddy[0xC]
// 800b3120 next function

// RB_Baron_ThTick
void FUN_800b3120(int param_1)
{
  undefined *puVar1;
  int iVar2;
  int iVar3;
  short sVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  short sStack32;
  undefined2 uStack30;
  undefined2 uStack28;
  
  // get instance from thread
  iVar6 = *(int *)(param_1 + 0x34);
  
  // get object from thread
  iVar5 = *(int *)(param_1 + 0x30);
  
  // instance -> animFrame
  sVar4 = *(short *)(iVar6 + 0x54);
  
  // INSTANCE_GetNumAnimFrames
  iVar2 = FUN_80030f58(iVar6,0);
  
  // if animation is not over
  if ((int)sVar4 + 1 < iVar2) 
  {
	// increment animation frame
    *(short *)(iVar6 + 0x54) = *(short *)(iVar6 + 0x54) + 1;
  }
  
  // if animation is over
  else 
  {
	// restart animation
    *(undefined2 *)(iVar6 + 0x54) = 0;
  }
  
  puVar1 = PTR_DAT_8008d2ac;
  
  // LEV -> numSpawnType2_PosRot
  if (*(int *)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0x140) != 0) 
  {
	// LEV -> ptrSpawnType2_PosRot
    iVar7 = **(int **)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0x144);
	
    iVar2 = (int)*(short *)(iVar5 + 0x2c) + 1;
    if (iVar7 == 0) {
      trap(0x1c00);
    }
    if ((iVar7 == -1) && (iVar2 == -0x80000000)) {
      trap(0x1800);
    }
	
	// get frame index in animation
    sVar4 = (short)(iVar2 % iVar7);
    *(short *)(iVar5 + 0x2c) = sVar4;
	
	// instance -> model -> modelID == N Gin Labs Barrel
    if (*(short *)(*(int *)(iVar6 + 0x18) + 0x10) == 0x55) 
	{
	  // 16th frame
      if (sVar4 == 0x10) 
	  {
		// play sound of barrel hitting ground
        FUN_8002f0dc(0xc,iVar6);
      }
	  
	  // frame 0-16
      if (*(short *)(iVar5 + 0x2c) < 0x11) 
	  {
		// stop audio
        FUN_8002e724(iVar5 + 0x24);
      }
      
	  // frame 17+
	  else 
	  {
		// PlaySound3D_Flags
		// sound of barrel moving
        FUN_8002f31c(iVar5 + 0x24,0x74,iVar6);
      }
	  
	  // LEV -> ptrSpawn1 rotX
      sStack32 = *(short *)((int)*(short *)(iVar5 + 0x2c) * 0xc +
                            *(int *)(*(int *)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0x144) + 4) + 6);
      
	  // LEV -> ptrSpawn1 rotY
	  uStack30 = *(undefined2 *)
                  ((int)*(short *)(iVar5 + 0x2c) * 0xc +
                   *(int *)(*(int *)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0x144) + 4) + 8);
      
	  // LEV -> ptrSpawn1 rotZ
	  uStack28 = *(undefined2 *)
                  ((int)*(short *)(iVar5 + 0x2c) * 0xc +
                   *(int *)(*(int *)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0x144) + 4) + 10);
				   
	  // convert rotation to matrix
      FUN_8006c2a4(iVar6 + 0x30,&sStack32);
      
	  puVar1 = PTR_DAT_8008d2ac;
      
	  // LEV -> ptrSpawn1 posX
	  *(int *)(iVar6 + 0x44) =
           (int)*(short *)((int)*(short *)(iVar5 + 0x2c) * 0xc +
                          *(int *)(*(int *)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0x144) + 4));
      
	  // LEV -> ptrSpawn1 posY
	  *(int *)(iVar6 + 0x48) =
           (int)*(short *)((int)*(short *)(iVar5 + 0x2c) * 0xc +
                           *(int *)(*(int *)(*(int *)(puVar1 + 0x160) + 0x144) + 4) + 2);
      
	  // LEV -> ptrSpawn1 posZ
	  *(int *)(iVar6 + 0x4c) =
           (int)*(short *)((int)*(short *)(iVar5 + 0x2c) * 0xc +
                           *(int *)(*(int *)(*(int *)(puVar1 + 0x160) + 0x144) + 4) + 4);
      
	  // adjust posX and posZ,
	  // this centers the barrel on the nav points
	  *(int *)(iVar6 + 0x44) = *(int *)(iVar6 + 0x44) + 0x111;
      *(int *)(iVar6 + 0x4c) = *(int *)(iVar6 + 0x4c) + -0x110;
    }
    
	// [Unused, Baron plane]
	// if this is not N Gin Labs Barrel
	else 
	{
	  // LEV -> ptrSpawn1 rotX
      uStack30 = *(undefined2 *)
                  ((int)*(short *)(iVar5 + 0x2c) * 0xc +
                   *(int *)(*(int *)(*(int *)(puVar1 + 0x160) + 0x144) + 4) + 8);
	  
	  // LEV -> ptrSpawn1 rotY
      sStack32 = -*(short *)((int)sVar4 * 0xc +
                             *(int *)(*(int *)(*(int *)(puVar1 + 0x160) + 0x144) + 4) + 6);
      
	  // LEV -> ptrSpawn1 rotZ
	  uStack28 = *(undefined2 *)
                  ((int)*(short *)(iVar5 + 0x2c) * 0xc +
                   *(int *)(*(int *)(*(int *)(puVar1 + 0x160) + 0x144) + 4) + 10);
      
	  // convert rotation to matrix
	  FUN_8006c2a4(iVar6 + 0x30,&sStack32);
      
	  puVar1 = PTR_DAT_8008d2ac;
      
	  // LEV -> ptrSpawn1 posX
	  *(int *)(iVar6 + 0x44) =
           (int)*(short *)((int)*(short *)(iVar5 + 0x2c) * 0xc +
                          *(int *)(*(int *)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0x144) + 4));
      
	  // LEV -> ptrSpawn1 posY
	  *(int *)(iVar6 + 0x48) =
           (int)*(short *)((int)*(short *)(iVar5 + 0x2c) * 0xc +
                           *(int *)(*(int *)(*(int *)(puVar1 + 0x160) + 0x144) + 4) + 2);
      
	  // LEV -> ptrSpawn1 posZ
	  *(int *)(iVar6 + 0x4c) =
           (int)*(short *)((int)*(short *)(iVar5 + 0x2c) * 0xc +
                           *(int *)(*(int *)(*(int *)(puVar1 + 0x160) + 0x144) + 4) + 4);
    }
    
	// [Unused, Baron plane]
	// if "other?" instance exists, 
	// update instance position
	if (*(int *)(iVar5 + 0x28) != 0) 
	{
      iVar2 = (int)*(short *)(iVar5 + 0x2c) + 0x78;
      if (iVar7 == 0) {
        trap(0x1c00);
      }
      if ((iVar7 == -1) && (iVar2 == -0x80000000)) {
        trap(0x1800);
      }
      iVar3 = (int)*(short *)(iVar5 + 0x2c) + 0x78;
      if (iVar7 == 0) {
        trap(0x1c00);
      }
      if ((iVar7 == -1) && (iVar3 == -0x80000000)) {
        trap(0x1800);
      }
	  
	  // LEV -> ptrSpawn1
      uStack30 = *(undefined2 *)
                  ((iVar3 % iVar7) * 0xc +
                   *(int *)(*(int *)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0x144) + 4) + 8);
      
	  iVar3 = (int)*(short *)(iVar5 + 0x2c) + 0x78;
      if (iVar7 == 0) {
        trap(0x1c00);
      }
      if ((iVar7 == -1) && (iVar3 == -0x80000000)) {
        trap(0x1800);
      }
      
	  // LEV -> ptrSpawn1
	  uStack28 = *(undefined2 *)
                  ((iVar3 % iVar7) * 0xc +
                   *(int *)(*(int *)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0x144) + 4) + 10);
      
	  // LEV -> ptrSpawn1
	  sStack32 = -*(short *)((iVar2 % iVar7) * 0xc +
                             *(int *)(*(int *)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0x144) + 4) + 6)
      ;
	  
	  // new instance rotation matrix
      FUN_8006c2a4(*(int *)(iVar5 + 0x28) + 0x30,&sStack32);
	  
      puVar1 = PTR_DAT_8008d2ac;
      iVar2 = (int)*(short *)(iVar5 + 0x2c) + 0x78;
      if (iVar7 == 0) {
        trap(0x1c00);
      }
      if ((iVar7 == -1) && (iVar2 == -0x80000000)) {
        trap(0x1800);
      }
	  
	  // instance->matrix.t[0]
      *(int *)(*(int *)(iVar5 + 0x28) + 0x44) =
           (int)*(short *)((iVar2 % iVar7) * 0xc +
                          *(int *)(*(int *)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0x144) + 4));
      
	  iVar2 = (int)*(short *)(iVar5 + 0x2c) + 0x78;
      if (iVar7 == 0) {
        trap(0x1c00);
      }
      if ((iVar7 == -1) && (iVar2 == -0x80000000)) {
        trap(0x1800);
      }
	  
	  // instance->matrix.t[1]
      *(int *)(*(int *)(iVar5 + 0x28) + 0x48) =
           (int)*(short *)((iVar2 % iVar7) * 0xc +
                           *(int *)(*(int *)(*(int *)(puVar1 + 0x160) + 0x144) + 4) + 2);
      iVar2 = (int)*(short *)(iVar5 + 0x2c) + 0x78;
      if (iVar7 == 0) {
        trap(0x1c00);
      }
      if ((iVar7 == -1) && (iVar2 == -0x80000000)) {
        trap(0x1800);
      }
	  
	  // instance->matrix.t[2]
      *(int *)(*(int *)(iVar5 + 0x28) + 0x4c) =
           (int)*(short *)((iVar2 % iVar7) * 0xc +
                           *(int *)(*(int *)(*(int *)(puVar1 + 0x160) + 0x144) + 4) + 4);
	  
	  // adjust posX and posZ,
	  // this centers the baron on the nav points      
	  *(int *)(*(int *)(iVar5 + 0x28) + 0x44) = *(int *)(*(int *)(iVar5 + 0x28) + 0x44) + 0x21f;
      *(int *)(*(int *)(iVar5 + 0x28) + 0x4c) = *(int *)(*(int *)(iVar5 + 0x28) + 0x4c) + -0x21f;
    }
	
	// instance -> model -> modelID == N Gin Labs Barrel
    if ((*(short *)(*(int *)(iVar6 + 0x18) + 0x10) == 0x55) &&
       
	   // get driver who hit barrel
	   
	   // RB_Hazard_CollideWithDrivers
	   (iVar2 = FUN_800ac220(iVar6,0,0x19000,0), iVar2 != 0)) 
	{
	  // RB_Hazard_HurtDriver (squish) 
      FUN_800ac1b0(*(undefined4 *)(*(int *)(iVar2 + 0x6c) + 0x30),3,0,0);
    }
  }
  return;
}

// RB_Baron_LInB
void FUN_800b37d4(int param_1)
{
  // N Gin Labs Barrel
  // [also something else?]
	
  undefined2 uVar1;
  int iVar2;
  int iVar3;
  
  // If this Instance's thread does not exist
  if (*(int *)(param_1 + 0x6c) == 0) 
  {
	// PROC_BirthWithObject
	// 0x30 = size
	// 0 = no relation to param4
	// 0x300 = SmallStackPool
	// 0x3 = static thread bucket
    iVar2 = FUN_8004205c(0x300303,&FUN_800b3120,s_baron_800b310c,0);
	
	// Give thread to instance
    *(int *)(param_1 + 0x6c) = iVar2;
	
	// if thread is valid
    if (iVar2 != 0) 
	{
	  // Get object created by the thread
      iVar3 = *(int *)(iVar2 + 0x30);
	  
	  // Give instance to thread
      *(int *)(iVar2 + 0x34) = param_1;
	  
	  // unused for baron plane,
	  // barrel#0 does "0/2" just gets zero
      iVar2 = strlen(param_1 + 8);
      uVar1 = 1;
      if (*(char *)(iVar2 + param_1 + 7) == '0') {
        uVar1 = (undefined2)(**(int **)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0x13c) / 2);
      }
	  
	  // starting node
      *(undefined2 *)(iVar3 + 0x2c) = uVar1;
	  
	  // Set scale (x, y, z)
      *(undefined2 *)(param_1 + 0x1c) = 0x1000;
      *(undefined2 *)(param_1 + 0x1e) = 0x1000;
      *(undefined2 *)(param_1 + 0x20) = 0x1000;
	  
	  // only need to set 0x28 -> 0x0,
	  // the rest is unused for baron
      *(undefined2 *)(iVar3 + 0x1a) = 4;
      *(undefined2 *)(iVar3 + 0x22) = 0x18;
      *(undefined2 *)(iVar3 + 6) = 0;
      *(undefined4 *)(iVar3 + 0x28) = 0;
	  
	  // instance->model->modelID == DYNAMIC_VONLABASS
      if (*(short *)(*(int *)(param_1 + 0x18) + 0x10) == 0x4f) 
	  {
		// make invisible
        *(uint *)(param_1 + 0x28) = *(uint *)(param_1 + 0x28) | 0x80;
      }
      
	  *(undefined4 *)(iVar3 + 0x24) = 0;
    }
  }
  return;
}

// RB_Blade_ThTick
void FUN_800b38e4(int param_1)
{
  int iVar1;
  short *psVar2;
  
  // rotation x, y, z
  undefined2 uStack32;
  short sStack30;
  short sStack28;
  
  // get object from thread
  psVar2 = *(short **)(param_1 + 0x30);
  
  // get instance from thread
  iVar1 = *(int *)(param_1 + 0x34);
  
  do 
  {
	// get rotation data from Instance->instDef (from LEV)
	  
	// rotX
    uStack32 = *(undefined2 *)(*(int *)(iVar1 + 0x2c) + 0x36);
	
	// rotY
    sStack30 = *(short *)(*(int *)(iVar1 + 0x2c) + 0x38) + 0x400;
	
	// rotZ
    sStack28 = *psVar2;
	
	// increment rotation
    *psVar2 = *psVar2 + 0x100;
	
	// turn rotation into matrix
    FUN_8006c2a4(iVar1 + 0x30,&uStack32);
	
	// set scale
    *(undefined2 *)(iVar1 + 0x20) = 0x1000;
    *(undefined2 *)(iVar1 + 0x1e) = 0x1000;
    *(undefined2 *)(iVar1 + 0x1c) = 0x1000;
	
	// this skips $RA backup/restore, faster than JR $RA
    FUN_80071694(param_1);
	
  } while( true );
}

// RB_Blade_LInB
void FUN_800b3978(int param_1)
{
  // These "blades" are on hot air skyway blimps.
  // One "blade" is a group of three fins,
  // Four "blades" instances total, from two airship
	
  int iVar1;
  
  // if thread's instance is null
  if (*(int *)(param_1 + 0x6c) == 0) 
  {
	// PROC_BirthWithObject
	// 0x4 = size
	// 0 = no relation to param4
	// 0x300 = SmallStackPool
	// 0x3 = static thread bucket
    iVar1 = FUN_8004205c(0x40303,FUN_800b38e4,s_blade_800b38dc,0);
	
	// Give thread to instance
    *(int *)(param_1 + 0x6c) = iVar1;
	
	// if thread created correctly
    if (iVar1 != 0) 
	{
	  // give instance to thread
      *(int *)(iVar1 + 0x34) = param_1;
	  
	  // set rotation to zero
      **(undefined2 **)(iVar1 + 0x30) = 0;
    }
  }
  return;
}

// RB_Bubbles_RoosTubes
void FUN_800b39dc(void)
{
  short sVar1;
  short sVar2;
  short sVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  short *psVar11;
  int iVar12;
  int iVar13;
  
  if (
		(
			// if less than 2 screens
			((byte)PTR_DAT_8008d2ac[0x1ca8] < 2) && 
			
			// level ID == 6
			(*(int *)(PTR_DAT_8008d2ac + 0x1a10) == 6)
		) &&
		
		// LEV -> numSpawn2
		(1 < *(int *)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0x138))
	  ) 
  {
	// LEV -> ptrSpawn2
    iVar4 = *(int *)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0x13c);
	
    iVar8 = *(int *)(iVar4 + 0xc);
    psVar11 = (short *)(iVar8 + 6);
    if (psVar11 != (short *)0x0) 
	{
	  // gGT->JitPools.particle.free.count
      iVar13 = *(int *)(PTR_DAT_8008d2ac + 0x19a0);
	  
	  // pointer to player 1 address
      iVar5 = *(int *)(PTR_DAT_8008d2ac + 0x24ec);
	  
	  // timer
      iVar7 = *(int *)(PTR_DAT_8008d2ac + 0x1cec);
	  
	  // spawn positions in SpawnType2
      iVar12 = *(int *)(iVar4 + 8) + -1;
	  
	  // currentX
      iVar9 = *(int *)(iVar5 + 0x2d4);
	  
	  // currentZ
      iVar10 = *(int *)(iVar5 + 0x2dc);
	  
	  // previousX
      iVar6 = *(int *)(iVar5 + 0x2e0);
	  
	  // previousZ
      iVar4 = *(int *)(iVar5 + 0x2e8);
	  
      if (0 < iVar12) {
        do {
          if (iVar13 < 0x14) {
            return;
          }
          if ((iVar7 + iVar12 & 7U) == 0) {
            sVar1 = psVar11[0];
            sVar2 = psVar11[1];
            sVar3 = psVar11[2];
			
			// currentX - previousX
            iVar8 = ((iVar9 - iVar6 >> 4) + (iVar9 >> 8)) - (int)sVar1;
			
			// absolute value
            if (iVar8 < 0) {
              iVar8 = -iVar8;
            }
			
			// currentZ - previousZ
            iVar5 = ((iVar10 - iVar4 >> 4) + (iVar10 >> 8)) - (int)sVar3;
			
			// absolute value
            if (iVar5 < 0) {
              iVar5 = -iVar5;
            }
			
			// if velocity is low
            if (iVar8 + iVar5 < 0x1681) 
			{
			  // Spawn bubbles in Roo's Tubes if you move slowly.
			  // Otherwise, if you move fast, then dont bother
				
			  // Create instance in particle pool
              iVar8 = FUN_80040308(0,*(undefined4 *)(PTR_DAT_8008d2ac + 0x2130),
                                   &DAT_800b3bc0);
								   
              iVar13 = iVar13 + -1;
			  
			  // quit if particle fails
              if (iVar8 == 0) {
                return;
              }
              
			  *(undefined2 *)(iVar8 + 0x1a) = 0x7fff;
              *(undefined *)(iVar8 + 0x18) = 8;
              *(int *)(iVar8 + 0x24) = *(int *)(iVar8 + 0x24) + (int)sVar1 * 0x100;
              *(int *)(iVar8 + 0x2c) = *(int *)(iVar8 + 0x2c) + (int)sVar2 * 0x100;
              *(int *)(iVar8 + 0x34) = *(int *)(iVar8 + 0x34) + (int)sVar3 * 0x100;
            }
          }
          iVar12 = iVar12 + -1;
          psVar11 = psVar11 + 3;
        } while (0 < iVar12);
      }
    }
  }
  return;
}

// RB_CrateAny_ThTick_Explode
void FUN_800b3d04(int param_1)
{
  short sVar1;
  int iVar2;
  int iVar3;
  
  // thread -> instance
  iVar3 = *(int *)(param_1 + 0x34);
  do 
  {
	// instance -> animFrame
    sVar1 = *(short *)(iVar3 + 0x54);
	
	// INSTANCE_GetNumAnimFrames
    iVar2 = FUN_80030f58(iVar3,0);
	
	// if animation is not over
    if ((int)sVar1 + 1 < iVar2) 
	{
	  // increment frame counter
      *(short *)(iVar3 + 0x54) = *(short *)(iVar3 + 0x54) + 1;
    }
	
	// if animation is over
    else 
	{
	  // This thread is now dead
      *(uint *)(param_1 + 0x1c) = *(uint *)(param_1 + 0x1c) | 0x800;
	  
	  // INSTANCE_Death
      FUN_80030aa8(iVar3);
    }
	
	// this skips $RA backup/restore, faster than JR $RA
    FUN_80071694(param_1);
	
  } while( true );
}

// RB_CrateAny_ThTick_Grow
void FUN_800b3d7c(int param_1)
{
  short sVar1;
  int iVar2;
  int *piVar3;
  
  // get object from thread
  piVar3 = *(int **)(param_1 + 0x30);
  
  // get instance from thread
  iVar2 = *(int *)(param_1 + 0x34);
  
  do 
  {
	// instance -> model -> modelID
    sVar1 = *(short *)(*(int *)(iVar2 + 0x18) + 0x10);
	
	// If this is Relic 1s, 2s, or 3s crate
    if (((sVar1 == 0x5c) || (sVar1 == 100)) || (sVar1 == 0x65)) 
	{
	  // erase thread pointer
      *(undefined4 *)(iVar2 + 0x6c) = 0;
	  
	  // This thread is now dead
      *(uint *)(param_1 + 0x1c) = *(uint *)(param_1 + 0x1c) | 0x800;
    }
	
	// If cooldown timer is done
    if (*piVar3 == 0) 
	{
	  //if scale is small
      if (*(short *)(iVar2 + 0x1c) < 0x1000) 
	  {
		// slowly increase scale (x, y, z)
        *(short *)(iVar2 + 0x1c) = *(short *)(iVar2 + 0x1c) + 0x100;
        *(short *)(iVar2 + 0x1e) = *(short *)(iVar2 + 0x1e) + 0x100;
        *(short *)(iVar2 + 0x20) = *(short *)(iVar2 + 0x20) + 0x100;
      }
	  
      else 
	  {
		// set max scale (x, y, z)
        *(undefined2 *)(iVar2 + 0x1c) = 0x1000;
        *(undefined2 *)(iVar2 + 0x1e) = 0x1000;
        *(undefined2 *)(iVar2 + 0x20) = 0x1000;
		
		// erase thread
        *(undefined4 *)(iVar2 + 0x6c) = 0;
		
		// increase instance->animFrame
        *(short *)(iVar2 + 0x54) = *(short *)(iVar2 + 0x54) + 1;
		
		// This thread is now dead
        *(uint *)(param_1 + 0x1c) = *(uint *)(param_1 + 0x1c) | 0x800;
      }
    }
	
	// if cooldown timer is not done
    else 
	{
	  // if cooldown is not paused (boolPauseCooldown)
      if (*(short *)(piVar3 + 1) == 0) 
	  {
		// reduce cooldown
        *piVar3 = *piVar3 + -1;
      }
    }
    
	// this skips $RA backup/restore, faster than JR $RA
	FUN_80071694(param_1);
	
  } while( true );
}

// RB_CrateWeapon_ThCollide
// param_1 is the box thread
// param_4 is 1f800108
undefined4 FUN_800b3e7c(int param_1,int param_2,undefined4 param_3,int param_4)
{
  undefined4 uVar1;
  undefined *puVar2;
  undefined4 in_zero;
  undefined4 in_at;
  ushort uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  undefined *puVar7;
  short sVar8;
  int *piVar9;
  int iVar10;
  undefined4 uStack112;
  char *pcStack108;
  undefined4 uStack104;
  undefined4 uStack100;
  undefined *puStack96;
  undefined4 uStack92;
  undefined4 uStack88;
  undefined2 uStack80;
  short sStack78;
  undefined2 uStack76;
  undefined auStack72 [32];
  undefined4 uStack40;
  undefined4 uStack36;
  short sStack32;
  short sStack30;
  
  // get object from thread
  piVar9 = *(int **)(param_1 + 0x30);
  
  // get instance from thread
  iVar10 = *(int *)(param_1 + 0x34);
  
  if (
		// if frame timer is running
		(*piVar9 != 0) || 
		(
			// scale is not zero, and not 0x1000
			(
				*(short *)(iVar10 + 0x1c) != 0 && 
				(*(short *)(iVar10 + 0x1c) != 0x1000)
			)
		)
	 )
  {
LAB_800b420c:
    uVar3 = *(ushort *)(param_4 + 0xc) & 0x7fff;
    if (((int)*(short *)(param_4 + 0xc) & 0x8000U) != 0) {
      *(ushort *)(param_4 + 0xc) = uVar3;
	  
      if (
			(
				(
					// if modelID is not nitro
					(uVar3 != 6) && 
					
					// if modelID is not tnt
					(uVar3 != 0x27)
				) && 
				
				// if modelID is not red beaker
				(uVar3 != 0x46)
			) && 
			
			// if model is not green beaker
			(uVar3 != 0x47)
		) 
	  {
        return 0;
      }
	  
	  // if modelID is a mine of any kind,
	  // offset4 = 1, prevent crate from growing back
      *(undefined2 *)(piVar9 + 1) = 1;
    }
    return 0;
  }
  
  // At this point, this the first frame of collision
  
  // 30-frame timer
  *piVar9 = 0x1e;
  
  if (*(short *)(iVar10 + 0x1c) != 0x1000) goto LAB_800b420c;
  
  // set crate scale (x, y, z) to zero
  *(undefined2 *)(iVar10 + 0x1c) = 0;
  *(undefined2 *)(iVar10 + 0x1e) = 0;
  *(undefined2 *)(iVar10 + 0x20) = 0;
  
  // Create an instance of explosion
  
  // box exploded model
  uStack112 = 0x26;
  
  // string
  pcStack108 = s_explosion1_800b3cbc;
  
  // small stack pool
  uStack104 = 0x300;
  
  // "other" thread bucket
  uStack100 = 0xd;
  
  // RB_CrateAny_ThTick_Explode
  puStack96 = &FUN_800b3d04;
  
  uStack92 = 0;
  uStack88 = 0;
  
  // initialize thread for explosion
  iVar4 = FUN_80030a50(&uStack112);
  
  // set color
  *(undefined4 *)(iVar4 + 0x24) = 0xfafafa0;
  
  // set alpha
  *(undefined2 *)(iVar4 + 0x22) = 0x1000;
  
  // create random rotation vector 
  // {0, rand&0xfff, 0}
  uStack80 = 0;
  iVar5 = FUN_80078be8();
  iVar6 = iVar5;
  if (iVar5 < 0) {
    iVar6 = iVar5 + 0xfff;
  }
  sStack78 = (short)iVar5 + (short)(iVar6 >> 0xc) * -0x1000;
  uStack76 = 0;
  
  // copy explosion position to crate position
  *(undefined4 *)(iVar4 + 0x44) = *(undefined4 *)(iVar10 + 0x44);
  *(undefined4 *)(iVar4 + 0x48) = *(undefined4 *)(iVar10 + 0x48);
  *(undefined4 *)(iVar4 + 0x4c) = *(undefined4 *)(iVar10 + 0x4c);
  
  // make rotation matrix from rand vector
  FUN_8006c2a4(auStack72,&uStack80);
  
  // explosion = crate + rotation
  FUN_8006c3b0(iVar4 + 0x30,iVar10 + 0x30,auStack72);
  
  // play sound for breaking box
  FUN_8002f0dc(0x3c,iVar10);
  
  // get modelID from what?
  sVar8 = *(short *)(param_4 + 0xc);
  
  if (
		// if model is Bomb
		(sVar8 == 0x3b) || 
		
		// if model is Missile
		(sVar8 == 0x29)
	  ) 
  {
LAB_800b3fe4:
    
	// if this is not human player
	if (sVar8 != 0x18) 
	{
      iVar6 = *(int *)(*(int *)(param_2 + 0x30) + 4);
	  
	  // If this is an AI, not a human
      if ((*(uint *)(iVar6 + 0x2c8) & 0x100000) != 0) {
        return 1;
      }
      goto code_r0x800b4024;
    }
  }
  else 
  {
	// if this is not human player
    if (sVar8 != 0x18) {
		
	  // if model is not blue shield
      if (sVar8 != 0x56) 
	  {
		// if model is not green shield
        if (sVar8 != 0x5e) 
		{
          return 1;
        }
        sVar8 = *(short *)(param_4 + 0xc);
      }
      goto LAB_800b3fe4;
    }
  }
  
  // driver = thread -> object
  iVar6 = *(int *)(param_2 + 0x30);
  
code_r0x800b4024:

  if (
		// If your weapon is not "no weapon"
		(*(char *)(iVar6 + 0x36) != '\x0f') && 
	
		// If "no weapon" timer is zero
		(*(short *)(iVar6 + 0x3c) == 0)
	 ) 
  {
    return 1;
  }
  
  // if you have a quantity of any weapon
  if (*(char *)(iVar6 + 0x37) != '\0') {
    return 1;
  }
  
  // If you dont want to fire a weapon
  if ((*(uint *)(iVar6 + 0x2c8) & 0x8000) == 0) 
  {
    if (
		// if thread to "cloud" is valid
		(*(int *)(iVar6 + 0x4a0) != 0) &&
       
		// driver -> cloudthread -> object -> 0x6
		(*(short *)(*(int *)(*(int *)(iVar6 + 0x4a0) + 0x30) + 6) == 1)
		)
	{
      return 1;
    }
	
	// if driver has no "clock" effect on them
    if (*(short *)(iVar6 + 0xc) == 0) 
	{
	  // set weapon ID to "roulette"
      *(undefined *)(iVar6 + 0x36) = 0x10;
	  
	  // increment number of weapon boxes hit
      *(char *)(iVar6 + 0x568) = *(char *)(iVar6 + 0x568) + '\x01';
	  
      puVar2 = PTR_DAT_8008d2ac;
	  
	  // timer for weapon roulette (90 frames, 3 seconds)
      *(undefined2 *)(iVar6 + 0x3a) = 0x5a;
	  
	  // If there is no weapon roulette
      if ((*(uint *)puVar2 & 0x800000) == 0) 
	  {
		// Play weapon roulette shuffle sound
        FUN_80028468(0x5d,0);
		
		// start drawing weapon roulette
        *(uint *)PTR_DAT_8008d2ac = *(uint *)PTR_DAT_8008d2ac | 0x800000;
      }
	  
      *(undefined4 *)(iVar6 + 0x4b0) = 5;
      *(undefined2 *)(iVar6 + 0x3c) = 0;
	  
	  // if you have 10 wumpa fruit
      if (*(char *)(iVar6 + 0x30) == '\n') {
        *(undefined4 *)(iVar6 + 0x4e0) = 10;
      }
	  
      puVar2 = PTR_DAT_8008d2ac;
	  
	  // instance position from matrix
      uStack40 = CONCAT22(*(undefined2 *)(iVar10 + 0x48),*(undefined2 *)(iVar10 + 0x44));
      uStack36 = CONCAT22(uStack36._2_2_,*(undefined2 *)(iVar10 + 0x4c));
      
	  // gGT->pushBuffer[driver->driverID]
	  puVar7 = PTR_DAT_8008d2ac + (uint)*(byte *)(iVar6 + 0x4a) * 0x110;
	  
	  // pushBuffer 0x28 (matrix)
	  gte_SetRotMatrix(puVar5 + 0x168 + 0x28);
	  gte_SetTransMatrix(puVar5 + 0x168 + 0x28);
      
	  // driver position into GTE
	  setCopReg(2,in_zero,uStack40);
      setCopReg(2,in_at,uStack36);
	  
	  // Perspective Transformation (Single)
      copFunction(2,0x180001);
	  
	  // screenspace position of driver
      uVar1 = getCopReg(2,0xe);
      
	  sStack32 = (short)uVar1;
	  
	  // PushBuffer_rect.x
      *(short *)(iVar6 + 0x4b4) =					// pushBuffer variable
           sStack32 + *(short *)(PTR_DAT_8008d2ac + (uint)*(byte *)(iVar6 + 0x4a) * 0x110 + 0x184);
      
	  sStack30 = (short)((uint)uVar1 >> 0x10);
      
	  // PushBuffer_rect.y
	  *(short *)(iVar6 + 0x4b6) =					// pushBuffer variable
           sStack30 + *(short *)(puVar2 + (uint)*(byte *)(iVar6 + 0x4a) * 0x110 + 0x186);
      return 1;
    }
    return 1;
  }
  return 1;
}

// RB_CrateWeapon_LInC
undefined4 FUN_800b4278(int param_1,undefined4 param_2,undefined4 param_3)
{
  code *pcVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  int iVar4;
  
  // Get the Instance's thread
  iVar4 = *(int *)(param_1 + 0x6c);
  
  // if there is no thread
  if (iVar4 == 0) 
  {
	// PROC_BirthWithObject
	// 0x8 = size
	// 0 = no relation to param4
	// 0x300 flag = SmallStackPool
	// 0x3 = static thread bucket
    iVar4 = FUN_8004205c(0x80303,&FUN_800b3d7c,s_crate_800b3cd8,0);
	
	// give thread to instance
    *(int *)(param_1 + 0x6c) = iVar4;
	
	// if the thread failed to init
    if (iVar4 == 0) 
	{
	  // quit
      return 0;
    }
	
	// Get the Crate object that the thread built
    puVar3 = *(undefined4 **)(iVar4 + 0x30);
	
	// give instance to thread
    *(int *)(iVar4 + 0x34) = param_1;
	
	// RB_CrateWeapon_ThCollide. smash crate when hit
    *(undefined4 *)(iVar4 + 0x28) = 0x800b3e7c;
	
	// initialize crate object
    *puVar3 = 0;
    *(undefined2 *)(puVar3 + 1) = 0;
  }
  
  // Get instance's funcThCollide
  pcVar1 = *(code **)(iVar4 + 0x28);
  
  // if there is no pointer
  if (pcVar1 == (code *)0x0) 
  {
	// quit
    uVar2 = 0;
  }
  
  // if there is a pointer
  else 
  {
	// execute the function pointer
    uVar2 = (*pcVar1)(iVar4,param_2,pcVar1,param_3);
  }
  return uVar2;
}

// RB_CrateFruit_ThCollide
undefined4 FUN_800b432c(int param_1,int param_2,undefined4 param_3,int param_4)
{
  short sVar1;
  undefined *puVar2;
  undefined4 in_zero;
  undefined4 in_at;
  ushort uVar3;
  int iVar4;
  undefined *puVar5;
  int *piVar6;
  undefined4 *puVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  undefined4 uVar10;
  int iVar11;
  undefined4 local_48;
  char *local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined *local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_28;
  uint local_24;
  short local_20 [2];
  undefined4 local_1c;
  
  // get object from thread
  piVar6 = *(int **)(param_1 + 0x30);
  
  // get instance from thread
  iVar11 = *(int *)(param_1 + 0x34);
  
  if (
		// If first member of object is zero
		(*piVar6 == 0) && 
		
		(
			// scale is zero
			(*(short *)(iVar11 + 0x1c) == 0 || 
			
			// scale ix 0x1000
			(*(short *)(iVar11 + 0x1c) == 0x1000))
		)
	 )
  {
    *piVar6 = 0x1e;
	
	// if scale is 0x1000
    if (*(short *)(iVar11 + 0x1c) == 0x1000) 
	{
	  // set scale to zero (x, y, z)
      *(undefined2 *)(iVar11 + 0x1c) = 0;
      *(undefined2 *)(iVar11 + 0x1e) = 0;
      *(undefined2 *)(iVar11 + 0x20) = 0;
	  
	  // spawn an explosion
	  // 0x26 = model ID
	  // 0x300 flag = SmallStackPool
	  // 0xd = "other" thread bucket
      local_48 = 0x26;
      local_44 = s_explosion1_800b3cbc;
      local_40 = 0x300;
      local_3c = 0xd;
	  
	  // RB_CrateAny_ThTick_Explode
      local_38 = &FUN_800b3d04;
      
	  local_34 = 0;
      local_30 = 0;
	  
	  // create thread for explosion
      iVar4 = FUN_80030a50(&local_48);
	  
	  // set color
      *(undefined4 *)(iVar4 + 0x24) = 0xf2953a0;
	  
	  // set scale
      *(undefined2 *)(iVar4 + 0x22) = 0x1000;
	  
	  // explosion matrix = crate matrix
      uVar8 = *(undefined4 *)(iVar11 + 0x34);
      uVar9 = *(undefined4 *)(iVar11 + 0x38);
      uVar10 = *(undefined4 *)(iVar11 + 0x3c);
      *(undefined4 *)(iVar4 + 0x30) = *(undefined4 *)(iVar11 + 0x30);
      *(undefined4 *)(iVar4 + 0x34) = uVar8;
      *(undefined4 *)(iVar4 + 0x38) = uVar9;
      *(undefined4 *)(iVar4 + 0x3c) = uVar10;
      uVar8 = *(undefined4 *)(iVar11 + 0x44);
      uVar9 = *(undefined4 *)(iVar11 + 0x48);
      uVar10 = *(undefined4 *)(iVar11 + 0x4c);
      *(undefined4 *)(iVar4 + 0x40) = *(undefined4 *)(iVar11 + 0x40);
      *(undefined4 *)(iVar4 + 0x44) = uVar8;
      *(undefined4 *)(iVar4 + 0x48) = uVar9;
      *(undefined4 *)(iVar4 + 0x4c) = uVar10;
	  
	  // play sound for breaking box
      FUN_8002f0dc(0x3c,iVar11);
	  
	  // random number of wumpa to grab
      iVar4 = FUN_8003ea28();
	  
      iVar11 = iVar4;
      if (iVar4 < 0) {
        iVar11 = iVar4 + 3;
      }
      iVar11 = iVar4 + (iVar11 >> 2) * -4 + 5;
	  
	  // get type of object that broke fruit crate
      sVar1 = *(short *)(param_4 + 0xc);
      
	  // if this was a player
	  if (sVar1 == 0x18) 
	  {
		// get driver object
        iVar4 = *(int *)(param_2 + 0x30);
		
		// 5 frame cooldown between getting each wumpa
        *(undefined4 *)(iVar4 + 0x4b8) = 5;
		
		// set number of wumpa to pick up
        *(int *)(iVar4 + 0x4c0) = iVar11;
		
		// input vector is driver->instSelf->matrix.t[] position
        local_28 = CONCAT22(*(undefined2 *)(*(int *)(iVar4 + 0x1c) + 0x48),
                            *(undefined2 *)(*(int *)(iVar4 + 0x1c) + 0x44));
        local_24 = local_24 & 0xffff0000 | (uint)*(ushort *)(*(int *)(iVar4 + 0x1c) + 0x4c);
        
		puVar5 = PTR_DAT_8008d2ac + (uint)*(byte *)(iVar4 + 0x4a) * 0x110;
		gte_SetRotMatrix(puVar5 + 0x168 + 0x28);
		gte_SetTransMatrix(puVar5 + 0x168 + 0x28);
        setCopReg(2,in_zero,local_28);
        setCopReg(2,in_at,local_24);
        
		// Perspective Transformation (Single)
		copFunction(2,0x180001);
		
        puVar7 = (undefined4 *)local_20;
        uVar8 = getCopReg(2,0xe);
        local_20[0] = (short)uVar8;
        puVar5 = PTR_DAT_8008d2ac + (uint)*(byte *)(iVar4 + 0x4a) * 0x110;
      }
	  
	  // if this is not a player
      else 
	  {
		// If this is not:
		//	DYNAMIC_BOMB
		//	DYNAMIC_ROCKET
		//	DYNAMIC_SHIELD (blue)
		//	DYNAMIC_SHIELD_GREEN
        if (((sVar1 != 0x3b) && (sVar1 != 0x29)) && ((sVar1 != 0x56 && (sVar1 != 0x5e)))) {
          return 1;
        }
		
		// if this was an item that a player threw,
		// then give wumpa to that player
		
		// get object of driver who threw the weapon
        iVar4 = *(int *)(*(int *)(param_2 + 0x30) + 4);
		
		// 5 frame cooldown between getting each wumpa
        *(undefined4 *)(iVar4 + 0x4b8) = 5;
        
		// set number of wumpa to pick up
		*(int *)(iVar4 + 0x4c0) = iVar11;
		
		// input vector is driver->instSelf->matrix.t[] position
        local_28 = CONCAT22(*(undefined2 *)(*(int *)(iVar4 + 0x1c) + 0x48),
                            *(undefined2 *)(*(int *)(iVar4 + 0x1c) + 0x44));
        local_24 = local_24 & 0xffff0000 | (uint)*(ushort *)(*(int *)(iVar4 + 0x1c) + 0x4c);
		
		// pushBuffer of driver
        puVar5 = PTR_DAT_8008d2ac + (uint)*(byte *)(iVar4 + 0x4a) * 0x110;
		
		// gGT->pushBuffer[driver->driverID]->0x28 (matrix)
		gte_SetRotMatrix(puVar5 + 0x168 + 0x28);
		gte_SetTransMatrix(puVar5 + 0x168 + 0x28);
		
		// load driver position into GTE
        setCopReg(2,in_zero,local_28);
        setCopReg(2,in_at,local_24);
        
		// Perspective Transformation (Single)
		copFunction(2,0x180001);
		
		// get screenspace position of driver
        puVar7 = &local_1c;
        local_1c = getCopReg(2,0xe);
		
        puVar5 = PTR_DAT_8008d2ac + (uint)*(byte *)(iVar4 + 0x4a) * 0x110;
        
		// screen posX
		local_20[0] = (short)local_1c;
      }
      puVar2 = PTR_DAT_8008d2ac;
	  
	  // driver->PickupWumpaHUD.startX = screen posX + pushBuffer startX
      *(short *)(iVar4 + 0x4bc) = local_20[0] + *(short *)(puVar5 + 0x184);
	  
	  // driver->PickupWumpaHUD.startY = screen posY + pushBuffer startY - 0x14
      *(short *)(iVar4 + 0x4be) =
           *(short *)((int)puVar7 + 2) +
           *(short *)(puVar2 + (uint)*(byte *)(iVar4 + 0x4a) * 0x110 + 0x186) + -0x14;
		   
      return 1;
    }
  }
  uVar3 = *(ushort *)(param_4 + 0xc) & 0x7fff;
  if (((int)*(short *)(param_4 + 0xc) & 0x8000U) != 0) {
    *(ushort *)(param_4 + 0xc) = uVar3;
    if ((((uVar3 != 6) && (uVar3 != 0x27)) && (uVar3 != 0x46)) && (uVar3 != 0x47)) {
      return 0;
    }
	
	// offset4 = 1, prevent crate from growing back
    *(undefined2 *)(piVar6 + 1) = 1;
  }
  return 0;
}

// RB_CrateFruit_LInC
undefined4 FUN_800b471c(int param_1,undefined4 param_2,undefined4 param_3)
{
  code *pcVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  int iVar4;
  
  // Get the instance's thread
  iVar4 = *(int *)(param_1 + 0x6c);
  
  // if there is no thread
  if (iVar4 == 0) 
  {
	// PROC_BirthWithObject
	// 0x8 = size
	// 0 = no relation to param4
	// 0x300 = SmallStackPool
	// 0x3 = static thread bucket
    iVar4 = FUN_8004205c(0x80303,&FUN_800b3d7c,s_fruit_crate_800b3ce0,0);
	
	// give thread to instance
    *(int *)(param_1 + 0x6c) = iVar4;
	
	// if thread failed
    if (iVar4 == 0) 
	{
	  // quit
      return 0;
    }
	
	// get the object attached to thread
    puVar3 = *(undefined4 **)(iVar4 + 0x30);
	
	// give Instance to thread
    *(int *)(iVar4 + 0x34) = param_1;
	
	// RB_CrateFruit_ThCollide
    *(undefined4 *)(iVar4 + 0x28) = 0x800b432c;
	
	// initialize crate object
	
	// no cooldown
    *puVar3 = 0;
	
	// not smashed
    *(undefined2 *)(puVar3 + 1) = 0;
  }
  
  // get the funcThCollide
  pcVar1 = *(code **)(iVar4 + 0x28);
  
  // if there is no function
  if (pcVar1 == (code *)0x0) 
  {
	// do nothing
    uVar2 = 0;
  }
  
  // if there is a function
  else 
  {
	// execute
    uVar2 = (*pcVar1)(iVar4,param_2,pcVar1,param_3);
  }
  return uVar2;
}

// RB_CrateTime_ThCollide
undefined4 FUN_800b47d0(int param_1,int param_2,undefined4 param_3,int param_4)
{
  // is param2 is PTR_DAT_8008d2ac + 0x1b2c
  // which is pointer to first player thread
	
  int *piVar1;
  undefined4 uVar2;
  undefined4 in_zero;
  undefined4 in_at;
  ushort uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  undefined *puVar7;
  short sVar8;
  undefined *puVar9;
  int iVar10;
  int *piVar11;
  undefined4 local_78;
  char *local_74;
  undefined4 local_70;
  undefined4 local_6c;
  undefined *local_68;
  undefined4 local_64;
  undefined4 local_60;
  undefined2 local_58;
  short local_56;
  undefined2 local_54;
  undefined auStack80 [32];
  undefined4 local_30;
  undefined4 local_2c;
  short local_28;
  short sStack38;
  
  // get object from thread
  piVar11 = *(int **)(param_1 + 0x30);
  
  // get instance from thread
  iVar10 = *(int *)(param_1 + 0x34);
  
  if ((*piVar11 != 0) || ((*(short *)(iVar10 + 0x1c) != 0 && (*(short *)(iVar10 + 0x1c) != 0x1000)))
     ) {
LAB_800b4b38:
    uVar3 = *(ushort *)(param_4 + 0xc) & 0x7fff;
    if (((int)*(short *)(param_4 + 0xc) & 0x8000U) != 0) {
      *(ushort *)(param_4 + 0xc) = uVar3;
      
	  if (
			(
				(
					// PU_EXPLOSIVE_CRATE (nitro)
					(uVar3 != 6) && 
					
					// STATIC_CRATE_TNT
					(uVar3 != 0x27)
				) && 
				
				// STATIC_BEAKER_RED
				(uVar3 != 0x46)
			) && 
			
			// STATIC_BEAKER_GREEN
			(uVar3 != 0x47)
		) 
	  {
        return 0;
      }
	  
	  // offset4 = 1, prevent crate from growing back
      *(undefined2 *)(piVar11 + 1) = 1;
    }
    return 0;
  }
  
  // == assume first frame of hit ==
  *piVar11 = 0x1e;
  
  // if scale is not 0x1000
  if (*(short *)(iVar10 + 0x1c) != 0x1000) goto LAB_800b4b38;
  
  // set scale to zero (x, y, z)
  *(undefined2 *)(iVar10 + 0x1c) = 0;
  *(undefined2 *)(iVar10 + 0x1e) = 0;
  *(undefined2 *)(iVar10 + 0x20) = 0;
  
  // spawn an exploded box
  // 0x26 = model index
  // 0x300 flag = SmallStackPool
  // 0xd = "other" thread bucket
  local_78 = 0x26;
  local_74 = s_explosion1_800b3cbc;
  local_70 = 0x300;
  local_6c = 0xd;
  
  // RB_CrateAny_ThTick_Explode
  local_68 = &FUN_800b3d04;
  
  local_64 = 0;
  local_60 = 0;
  
  // create thread for explosion
  iVar4 = FUN_80030a50(&local_78);
  
  // set color
  *(undefined4 *)(iVar4 + 0x24) = 0x80ff000;
  
  // set scale[4]
  *(undefined2 *)(iVar4 + 0x22) = 0x1000;
  
  // random vector {0, rand&0xfff, 0}
  local_58 = 0;
  iVar5 = FUN_80078be8();
  iVar6 = iVar5;
  if (iVar5 < 0) {
    iVar6 = iVar5 + 0xfff;
  }
  local_56 = (short)iVar5 + (short)(iVar6 >> 0xc) * -0x1000;
  local_54 = 0;
  
  // set exploded box position to the position of the original crate
  *(undefined4 *)(iVar4 + 0x44) = *(undefined4 *)(iVar10 + 0x44);
  *(undefined4 *)(iVar4 + 0x48) = *(undefined4 *)(iVar10 + 0x48);
  *(undefined4 *)(iVar4 + 0x4c) = *(undefined4 *)(iVar10 + 0x4c);
  
   // make matrix from rand vector
  FUN_8006c2a4(auStack80,&local_58);
  
  // explosion matrix = crate matrix + random rotation
  FUN_8006c3b0(iVar4 + 0x30,iVar10 + 0x30,auStack80);
  
  // play sound for breaking box
  FUN_8002f0dc(0x3c,iVar10);
  
  // get modelID, from what kind of struct?
  sVar8 = *(short *)(param_4 + 0xc);
  
  // bomb or missle "bombtracker"
  if ((sVar8 == 0x3b) || (sVar8 == 0x29)) {
LAB_800b493c:

	// if human player of any kind
    if (sVar8 == 0x18) goto LAB_800b4974;
	
	// pointer to player object, plus 4, driver #2 ???
    iVar6 = *(int *)(*(int *)(param_2 + 0x30) + 4);
    
	// if this driver is an AI
	if ((*(uint *)(iVar6 + 0x2c8) & 0x100000) != 0) 
	{
      return 1;
    }
  }
  else 
  {
	// not DYNAMIC_PLAYER
    if (sVar8 != 0x18) 
	{
	  // not DYNAMIC_SHIELD (blue)
      if (sVar8 != 0x56) 
	  {
		// not DYNAMIC_SHIELD_GREEN
        if (sVar8 != 0x5e) goto LAB_800b4b2c;
        sVar8 = *(short *)(param_4 + 0xc);
      }
      goto LAB_800b493c;
    }
LAB_800b4974:
    iVar6 = *(int *)(param_2 + 0x30);
  }
  
  // increment amount of time crates that are broken
  *(char *)(iVar6 + 0x32) = *(char *)(iVar6 + 0x32) + '\x01';
  
  puVar9 = PTR_DAT_8008d2ac;
  
  // See model IDs in common.h, at 0x2160
  
  // instance -> model -> modelID
  sVar8 = *(short *)(*(int *)(iVar10 + 0x18) + 0x10);
  
  // if model is a 1s crate
  if (sVar8 == 0x5c) 
  {
	// Get current amount of frozen time
    piVar1 = (int *)(PTR_DAT_8008d2ac + 0x1e20);
	
	// you broke a 1s crate
    *(undefined4 *)(PTR_DAT_8008d2ac + 0x1e24) = 1;
	
	// increase amount of frozen time
	// by 0x3c0, which is 960, which is 1 second
    iVar4 = *piVar1 + 0x3c0;
  }
  
  // If model is not a 1s crate
  else 
  {
	// if model is a 2s crate
    if (sVar8 == 100) 
	{
	  // Get current amount of frozen time
      piVar1 = (int *)(PTR_DAT_8008d2ac + 0x1e20);
      
	  // you broke a 2s crate
	  *(undefined4 *)(PTR_DAT_8008d2ac + 0x1e24) = 2;
	  
	  // increase amount of frozen time
	  // by 0x780, 0x3c0*2, which is 2 seconds
      iVar4 = *piVar1 + 0x780;
    }
	
	// If model is not 1s crate or 2s crate,
	// then assume model is a 3s crate
    else 
	{
	  // make driver talk
	  FUN_8002cbe8(0x13,(int)(short)(&DAT_80086e84)[*(byte *)(iVar6 + 0x4a)],0x10);
	  
      puVar9 = PTR_DAT_8008d2ac;
	  
	  // Get current amount of frozen time
      piVar1 = (int *)(PTR_DAT_8008d2ac + 0x1e20);
	  
	  // you broke a 3s crate
      *(undefined4 *)(PTR_DAT_8008d2ac + 0x1e24) = 3;
	  
	  // increase amount of frozen time
	  // by 0xb40, 0x3c0*3, which is 3 seconds
      iVar4 = *piVar1 + 0xb40;
    }
  }
  
  // Set current amount of frozen time
  *(int *)(puVar9 + 0x1e20) = iVar4;
  
  // Main EXE uses this when drawing string with time crate number
  *(undefined4 *)(iVar6 + 0x4b0) = 10;
  
  puVar9 = PTR_DAT_8008d2ac;
  local_30 = CONCAT22(*(undefined2 *)(iVar10 + 0x48),*(undefined2 *)(iVar10 + 0x44));
  local_2c = CONCAT22(local_2c._2_2_,*(undefined2 *)(iVar10 + 0x4c));
  
  // pushBuffer of driver
  puVar7 = PTR_DAT_8008d2ac + (uint)*(byte *)(iVar6 + 0x4a) * 0x110;
  
  // pushBuffer -> 0x28 (matrix)
  r0 = (MATRIX *)(PTR_DAT_8008d2ac + (uint)*(byte *)(iVar6 + 0x4a) * 0x110 + 400);
  gte_SetRotMatrix(r0);
  gte_SetTransMatrix(r0);
  
  // 3D position
  gte_ldv0(&local_30);
  gte_rtps();
  
  // 2D position
  gte_stsxy(&uVar2);
  
  // screen posX
  local_28 = (short)uVar2;
  
  // driver->PickupHUD.startX = screen posX + pushBuffer rect.x
  *(short *)(iVar6 + 0x4b4) =
       local_28 + *(short *)(PTR_DAT_8008d2ac + (uint)*(byte *)(iVar6 + 0x4a) * 0x110 + 0x184);
  
  // screen posY
  sStack38 = (short)((uint)uVar2 >> 0x10);
  
  // driver->PickupHUD.startY = screen posY + pushBuffer rect.y
  *(short *)(iVar6 + 0x4b6) =
       sStack38 + *(short *)(puVar9 + (uint)*(byte *)(iVar6 + 0x4a) * 0x110 + 0x186);
	   
LAB_800b4b2c:
  
  // offset4 = 1, prevent crate from growing back
  *(undefined2 *)(piVar11 + 1) = 1;
  
  return 1;
}

// RB_CrateTime_LInC
undefined4 FUN_800b4ba8(int param_1,undefined4 param_2,undefined4 param_3)
{
  code *pcVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  int iVar4;
  
  // Get thread from instance
  iVar4 = *(int *)(param_1 + 0x6c);
  
  // if there is no thread
  if (iVar4 == 0) 
  {
	// Naughty Dog made a string mistake,
	// this is DEFINITELY a timebox, not fruit crate
	  
	// PROC_BirthWithObject
	// 0x8 = size
	// 0 = no relation to param4
	// 0x300 = SmallStackPool
	// 0x3 = static thread bucket
    iVar4 = FUN_8004205c(0x80303,&FUN_800b3d7c,s_fruit_crate_800b3ce0,0);
	
	// give thread to Instance
    *(int *)(param_1 + 0x6c) = iVar4;
	
	// if the thread failed
    if (iVar4 == 0) 
	{
	  // quit
      return 0;
    }
	
	// get the object attached to thread
    puVar3 = *(undefined4 **)(iVar4 + 0x30);
	
	// give instance to thread
    *(int *)(iVar4 + 0x34) = param_1;
	
	// RB_CrateTime_ThCollide, smash crate
    *(undefined4 *)(iVar4 + 0x28) = 0x800b47d0;
	
	// initialize object
    *puVar3 = 0;
    *(undefined2 *)(puVar3 + 1) = 0;
  }
  
  // get thread's funcThCollide
  pcVar1 = *(code **)(iVar4 + 0x28);
  
  // if the funcPtr does not exist
  if (pcVar1 == (code *)0x0) 
  {
	// do nothing
    uVar2 = 0;
  }
  
  // if there is a function
  else 
  {
	// execute it
    uVar2 = (*pcVar1)(iVar4,param_2,pcVar1,param_3);
  }
  return uVar2;
}

// RB_Crystal_ThCollide
undefined4 FUN_800b4c5c(int param_1,int param_2,undefined4 param_3,int param_4)
{
  short sVar1;
  undefined *puVar2;
  undefined4 in_zero;
  undefined4 in_at;
  undefined4 uVar3;
  undefined *puVar4;
  int iVar5;
  int iVar6;
  undefined4 local_18;
  uint local_14;
  short local_10;
  short sStack14;
  
  puVar2 = PTR_DAT_8008d2ac;
  
  // scratchpad modelID
  sVar1 = *(short *)(param_4 + 0xc);
  
  // get crystal instance from thread
  iVar6 = *(int *)(param_1 + 0x34);
  
  if (
		// if this is a player of any kind
		(sVar1 == 0x18) || 
		
		(
			uVar3 = 0, 
			
			// if this is a robotcar of any kind
			sVar1 == 0x3f
		)
	  ) 
  {
	// driverThread->driverObj
    iVar5 = *(int *)(param_2 + 0x30);
	
	// If this is player
    if (sVar1 == 0x18) 
	{
	  // crystal position
      local_18 = CONCAT22(*(undefined2 *)(iVar6 + 0x48),*(undefined2 *)(iVar6 + 0x44));
      local_14 = local_14 & 0xffff0000 | (uint)*(ushort *)(iVar6 + 0x4c);
	  
	  // pushBuffer -> 0x28 (matrix)
      puVar4 = PTR_DAT_8008d2ac + (uint)*(byte *)(iVar5 + 0x4a) * 0x110;
	  r0 = (MATRIX *)(PTR_DAT_8008d2ac + (uint)*(byte *)(iVar6 + 0x4a) * 0x110 + 400);
      gte_SetRotMatrix(r0);
      gte_SetTransMatrix(r0);
	  
	  // driver position
      gte_ldv0(&local_18);
      gte_rtps();
	  
	  // get screen position
      gte_stsxy(&uVar3);
	  
	  // screenX
      local_10 = (short)uVar3;
      *(short *)(iVar5 + 0x4bc) =
           local_10 + *(short *)(PTR_DAT_8008d2ac + (uint)*(byte *)(iVar5 + 0x4a) * 0x110 + 0x184);
      
	  // screenY
	  sStack14 = (short)((uint)uVar3 >> 0x10);
      sVar1 = *(short *)(puVar2 + (uint)*(byte *)(iVar5 + 0x4a) * 0x110 + 0x186);
      
	  // 5 frame cooldown between getting each wumpa
	  *(undefined4 *)(iVar5 + 0x4b8) = 5;
	  
	  // one collectable item is picked up
      *(int *)(iVar5 + 0x4c0) = *(int *)(iVar5 + 0x4c0) + 1;
      
	  *(short *)(iVar5 + 0x4be) = sStack14 + sVar1 + -0x14;
    }
	
	// set scale to zero (x, y, z)
    *(undefined2 *)(iVar6 + 0x1c) = 0;
    *(undefined2 *)(iVar6 + 0x1e) = 0;
    *(undefined2 *)(iVar6 + 0x20) = 0;
	
	// erase thread
    *(undefined4 *)(iVar6 + 0x6c) = 0;
	
	// play sound for picking up
    FUN_8002f0dc(0x43,iVar6);
    
	uVar3 = 1;
	
	// This thread is now dead
    *(uint *)(param_1 + 0x1c) = *(uint *)(param_1 + 0x1c) | 0x800;
  }
  return uVar3;
}

// RB_Crystal_ThTick
void FUN_800b4dd8(int param_1)
{
  int iVar1;
  int iVar2;
  int iVar3;
  
  // get instance from thread
  iVar3 = *(int *)(param_1 + 0x34);
  
  // get object from thread
  iVar2 = *(int *)(param_1 + 0x30);
  
  // Not sure why there's two of these?
  
  // Rotate on the Y axis
  // convert 3 rotation shorts into rotation matrix
  *(short *)(iVar2 + 2) = *(short *)(iVar2 + 2) + 0x40;
  FUN_8006c2a4(iVar3 + 0x30,iVar2);
  
  // Rotate on the Y axis
  // convert 3 rotation shorts into rotation matrix
  *(short *)(iVar2 + 2) = *(short *)(iVar2 + 2) + 0x40;
  FUN_8006c2a4(iVar3 + 0x30,iVar2);
  
  // Sine(angle)
  iVar1 = FUN_8003d184((int)*(short *)(iVar2 + 2));
  
  *(int *)(iVar3 + 0x48) =
       (int)*(short *)(*(int *)(iVar3 + 0x2c) + 0x32) + ((iVar1 << 4) >> 0xc) + 0x30;
  
  // Vector_SpecLightSpin3D
  FUN_8005741c(iVar3,iVar2,s_O_O_O_800b5968);
  
  return;
}

// RB_Crystal_LInC
undefined4 FUN_800b4e7c(int param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 uVar1;
  code *pcVar2;
  int iVar3;
  
  // Check this Instance's thread
  iVar3 = *(int *)(param_1 + 0x6c);
  
  // If there is no thread
  if (iVar3 == 0) {
    
	// PROC_BirthWithObject
	// 0x8 = size
	// 0 = no relation to param4
	// 0x300 = SmallStackPool
	// 0x3 = static thread bucket
	iVar3 = FUN_8004205c(0x80303,FUN_800b4dd8,s_crystal_800b3cec,0);
    
	// give thread to instance
	*(int *)(param_1 + 0x6c) = iVar3;
	
	// if the thread failed to build
    if (iVar3 == 0) 
	{
	  // quit
      return 0;
    }
	
	// Give instance to thread
    *(int *)(iVar3 + 0x34) = param_1;
	
	// RB_Crystal_ThCollide, collect crystal
    *(undefined4 *)(iVar3 + 0x28) = 0x800b4c5c;
	
	// Get thread from instance
    iVar3 = *(int *)(param_1 + 0x6c);
  }
  
  uVar1 = 0;
  
  if (
		// if there is a thread
		(iVar3 != 0) && 
		(
			// get the funcThCollide
			pcVar2 = *(code **)(iVar3 + 0x28),
			
			// if there is a function pointer
			pcVar2 != (code *)0x0
		)
	 ) 
  {
	  
	// if scale is zero, and object is not drawn
    if (*(short *)(param_1 + 0x1c) == 0) 
	{
	  // do nothing
      uVar1 = 0;
    }
	
	// if object is drawn
    else 
	{
	  // execute function pointer
      uVar1 = (*pcVar2)(iVar3,param_2,pcVar2,param_3);
    }
  }
  return uVar1;
}

// RB_Crystal_LInB
void FUN_800b4f48(int param_1)
{
  int iVar1;
  undefined2 *puVar2;
  
  // If this Instance has no thread
  if (*(int *)(param_1 + 0x6c) == 0) 
  {
	// PROC_BirthWithObject
	// 0x8 = size
	// 0 = no relation to param4
	// 0x300 = SmallStackPool
	// 0x3 = "static" 
    iVar1 = FUN_8004205c(0x80303,FUN_800b4dd8,s_crystal_800b3cec,0);
	
	// give thread to Instance
    *(int *)(param_1 + 0x6c) = iVar1;
	
	// If the thread failed
    if (iVar1 == 0) 
	{
	  // quit
      return;
    }
	
	// get the object that the thread created
    puVar2 = *(undefined2 **)(iVar1 + 0x30);
	
	// give instance to thread
    *(int *)(iVar1 + 0x34) = param_1;
	
	// RB_Crystal_ThCollide, collect crystal
    *(undefined4 *)(iVar1 + 0x28) = 0x800b4c5c;
	
	// set rotX, rotY, and rotZ to zero
    *puVar2 = 0;
    puVar2[1] = 0;
    puVar2[2] = 0;
	
	// set color
    *(undefined4 *)(param_1 + 0x24) = 0xd22fff0;
	
	// instance flags, specular light
    *(uint *)(param_1 + 0x28) = *(uint *)(param_1 + 0x28) | 0x20000;
  }
  
  // RB_Default_LInB
  FUN_800b4fe4(param_1);
  
  return;
}

// RB_Default_LInB
// used by wumpabox, weaponbox, timebox, as funcptr,
// or called directly from other LevInstDefBirth funcptrs
void FUN_800b4fe4(int param_1)
{
  _DAT_1f80013c = 0x3000;
  _DAT_1f800140 = 0;
  
  // high-LOD collision (8 triangles)
  DAT_1f80013a = 2;
  
  // Get pointer to LEV
  _DAT_1f800144 = **(undefined4 **)(PTR_DAT_8008d2ac + 0x160);
  
  // Make a hitbox
  DAT_1f800108 = *(undefined2 *)(param_1 + 0x44);
  DAT_1f80010a = *(short *)(param_1 + 0x48) + -0x180;
  DAT_1f80010c = *(undefined2 *)(param_1 + 0x4c);
  DAT_1f800112 = *(short *)(param_1 + 0x48) + 0x80;
  DAT_1f800110 = DAT_1f800108;
  DAT_1f800114 = DAT_1f80010c;
  
  // COLL_SearchTree_FindQuadblock_Touching
  FUN_8001eb0c(&DAT_1f800108,&DAT_1f800110,&DAT_1f800118,0);
  
  // depending on quadblock found in BSP search,
  // choose to make instance reflective
  
  // RB_MakeInstanceReflective
  FUN_800abab0(&DAT_1f800118,param_1);
  return;
}

// RB_CtrLetter_ThCollide
bool FUN_800b5090(int param_1,int param_2,undefined4 param_3,int param_4)

{
  bool bVar1;
  short sVar2;
  short sVar3;
  undefined2 uVar4;
  MATRIX *r0;
  undefined *puVar5;
  int iVar6;
  int iVar7;
  long *r0_00;
  int iVar8;
  undefined *puVar9;
  
  // puVar9+0x00
  undefined auStack40 [16];
  
  // puVar9+0x10
  undefined2 uStack24;
  undefined2 uStack22;
  
  // puVar9+0x18
  undefined2 uStack20;
  // ... (more stack variables)
  
  puVar9 = auStack40;
  
  // get instance from thread
  iVar8 = *(int *)(param_1 + 0x34);
  
  // only continue if letter was hit by a player
  bVar1 = *(short *)(param_4 + 0xc) == 0x18;
  
  if (bVar1) 
  {
	// get object from thread,
	// get position from instance matrix
    uStack24 = *(undefined2 *)(iVar8 + 0x44);
    iVar7 = *(int *)(param_2 + 0x30);
    uStack22 = *(undefined2 *)(iVar8 + 0x48);
    uStack20 = *(undefined2 *)(iVar8 + 0x4c);
	
	// 80090000
    puVar5 = &DAT_80090000;
    
	// gGT->pushBuffer[driver->driverID]->0x28 (matrix)
	r0 = (MATRIX *)(PTR_DAT_8008d2ac + 0x168 + (uint)*(byte *)(iVar7 + 0x4a) * 0x110 + 0x28);
    gte_SetRotMatrix(r0);
    gte_SetTransMatrix(r0);
	
	// load position of driver
    gte_ldv0((SVECTOR *)(puVar9 + 0x10));
	
	// perspective project
    gte_rtps();
	
	// get screenspace position of driver
    r0_00 = (long *)(puVar9 + 0x18);
    gte_stsxy(r0_00);
    
	// 8008d2ac
	iVar6 = *(int *)(puVar5 + -0x2d54);
    
	// driver->letterHUD.startX
	*(short *)(iVar7 + 0x4c8) =
	
		 // &r0_00 + 0x0 (screen posX)
         *(short *)(puVar9 + 0x18) +
		 
		 // gGT->pushBuffer[driver->driverID].rect.x
         *(short *)(iVar6 + (uint)*(byte *)(iVar7 + 0x4a) * 0x110 + 0x168 + 0x1c);
    
	// &r0_00 + 0x2 (screen posY)
	sVar2 = *(short *)((int)r0_00 + 2);
	
	// gGT->pushBuffer[driver->driverID].rect.y
    sVar3 = *(short *)(iVar6 + (uint)*(byte *)(iVar7 + 0x4a) * 0x110 + 0x168 + 0x1e);
    
	// should last 10 frames
	*(undefined2 *)(iVar7 + 0x4c4) = 10;
    
	// driver->letterHUD.startY = screenPosY + rect.y - 0x14
	*(short *)(iVar7 + 0x4ca) = sVar2 + sVar3 + -0x14;
    
	// modelID
	uVar4 = *(undefined2 *)(*(int *)(iVar8 + 0x18) + 0x10);
	
	// increment number of CTR Letters collected
    *(int *)(iVar7 + 0x4cc) = *(int *)(iVar7 + 0x4cc) + 1;
	
	// modelID of letter hit
    *(undefined2 *)(iVar7 + 0x4c6) = uVar4;
	
	// Set Scale (X, Y, Z) to zero, make the 3D letter invisible
    *(undefined2 *)(iVar8 + 0x1c) = 0;
    *(undefined2 *)(iVar8 + 0x1e) = 0;
    *(undefined2 *)(iVar8 + 0x20) = 0;
	
	// erase thread
    *(undefined4 *)(iVar8 + 0x6c) = 0;
	
	// Make it completely invisible, stop drawing letter entirely
    *(uint *)(iVar8 + 0x28) = *(uint *)(iVar8 + 0x28) | 0x80;
	
	// Play a "ding" sound
    FUN_80028468(100,1);
	
	// This thread is now dead
    *(uint *)(param_1 + 0x1c) = *(uint *)(param_1 + 0x1c) | 0x800;
  }
  return bVar1;
}

// RB_CtrLetter_LInC
undefined4 FUN_800b5210(int param_1,undefined4 param_2,undefined4 param_3)
{
  undefined4 uVar1;
  code *pcVar2;
  int iVar3;
  
  // Get the thread of this Instance
  iVar3 = *(int *)(param_1 + 0x6c);
  
  // If there is no thread
  if (iVar3 == 0) 
  {
	// This is a "world" letter, not a "hud" letter
	  
	// 800b3cf4
	// "ctr"
	
	// PROC_BirthWithObject
	// 0x4 = size
	// 0 = no relation to param4
	// 0x300 = SmallStackPool
	// 0x3 = "static" thread bucket
    iVar3 = FUN_8004205c(0x40303,FUN_800b52dc,&DAT_800b3cf4,0);
	
	// save thread pointer to Instance
    *(int *)(param_1 + 0x6c) = iVar3;
	
	// If the thread failed to initialize
    if (iVar3 == 0) 
	{
	  // return failure
      return 0;
    }
	
	// save Instance pointer to the thread
    *(int *)(iVar3 + 0x34) = param_1;
	
	// RB_CtrLetter_ThCollide
    *(undefined4 *)(iVar3 + 0x28) = 0x800b5090;
	
	// set iVar3 back to the thread pointer that 
	// it was set to originally
    iVar3 = *(int *)(param_1 + 0x6c);
  }
  
  // At this point, we must have a valid thread
  
  uVar1 = 0;
  
  if (
		// if we have a valid thread
		(iVar3 != 0) && 
		
		(
			// get funcThCollide
			pcVar2 = *(code **)(iVar3 + 0x28), 
		
			// If this is a valid funcPtr
			pcVar2 != (code *)0x0
		)
	  ) 
  {
	// If the scale of this object is not zero
    if (*(short *)(param_1 + 0x1c) == 0) 
	{
	  // No event executed
      uVar1 = 0;
    }
	
	// If this object has a scale,
	// and therefore the object is drawn
    else 
	{
	  // Execute th->funcThCollide pointer
      uVar1 = (*pcVar2)(iVar3,param_2,pcVar2,param_3);
    }
  }
  
  return uVar1;
}

// RB_CtrLetter_ThTick
void FUN_800b52dc(int param_1)
{
  int iVar1;
  int iVar2;
  
  // get instance from thread
  iVar2 = *(int *)(param_1 + 0x34);
  
  // get object from thread
  iVar1 = *(int *)(param_1 + 0x30);
  
  // Spin on the Y axis
  *(short *)(iVar1 + 2) = *(short *)(iVar1 + 2) + 0x40;
  
  // (iVar2 + 0x30) is matrix
  // (iVar1) is vec3s rotation
  
  // Convert rotations into a matrix
  FUN_8006c2a4(iVar2 + 0x30,iVar1);
  
  // Vector_SpecLightSpin3D
  FUN_8005741c(iVar2,iVar1,&DAT_800b5970);
  return;
}

// RB_CtrLetter_LInB
void FUN_800b5334(int param_1)
{
  int iVar1;
  undefined2 *puVar2;
  
  if (*(int *)(param_1 + 0x6c) == 0) 
  {
	// This is a "world" letter, not a "hud" letter
	  
	// 800b3cf4
	// "ctr"
	
	// PROC_BirthWithObject
	// 0x8 = size
	// 0 = no relation to param4
	// 0x300 = SmallStackPool
	// 0x3 = "static" thread bucket
    iVar1 = FUN_8004205c(0x80303,FUN_800b52dc,&DAT_800b3cf4,0);
	
	// Save the thread into Instance
    *(int *)(param_1 + 0x6c) = iVar1;
	
	// If the thread failed
    if (iVar1 == 0) 
	{
	  // Quit
      return;
    }
	
	// Get the pointer to the token that the thread created
    puVar2 = *(undefined2 **)(iVar1 + 0x30);
	
	// RB_CtrLetter_ThCollide
    *(undefined4 *)(iVar1 + 0x28) = 0x800b5090;
	
    *(int *)(iVar1 + 0x34) = param_1;
	
	// Initialize the CTR-Letter object
    *puVar2 = 0;
    puVar2[1] = 0;
    puVar2[2] = 0;
    
	// Set Instance's Scale of 3D letter (X, Y, Z)
	*(undefined2 *)(param_1 + 0x1c) = 0x1800;
    *(undefined2 *)(param_1 + 0x1e) = 0x1800;
    *(undefined2 *)(param_1 + 0x20) = 0x1800;
	
	// Set the color
    *(undefined4 *)(param_1 + 0x24) = 0xffc8000;
	
	// Set flags
    *(uint *)(param_1 + 0x28) = *(uint *)(param_1 + 0x28) | 0x30000;
  }
  
  // RB_Default_LInB
  FUN_800b4fe4(param_1);
  return;
}

// RB_Banner_Animate_Init
// param_1 pointer to banner modelHeader
int FUN_800b53e0(int param_1)
{
  byte bVar1;
  uint uVar2;
  uint uVar3;
  uint *puVar4;
  byte *pbVar5;
  byte *pbVar6;
  int iVar7;
  short sVar8;
  
  sVar8 = 0;
  
  // modelHeader->ptrCommands, skip 2 bytes (skip numColors)
  puVar4 = (uint *)(*(short **)(param_1 + 0x20) + 2);
  
  // modelHeader->ptrFrameData[modelHeader->ptrFrameData->vertexOffset]
  pbVar5 = (byte *)(*(int *)(param_1 + 0x24) + *(int *)(*(int *)(param_1 + 0x24) + 0x18));
  
  // if less than 64 colors found, quit
  if (**(short **)(param_1 + 0x20) < 0x40) {
    return 0;
  }
  
  if (*puVar4 != 0xffffffff) {
    uVar2 = *puVar4;
    do {
      if ((uVar2 & 0xffff0000) == 0) {
LAB_800b563c:
        puVar4 = puVar4 + 1;
      }
      else {
        if (-1 < (int)uVar2) {
          if ((uVar2 & 0x4000000) == 0) {
            _DAT_1f800300 = (uint)CONCAT12(pbVar5[2],(ushort)*pbVar5);
            _DAT_1f800304 = _DAT_1f800304 & 0xffff0000 | (uint)pbVar5[1];
            *(uint *)((uint)*(byte *)((int)puVar4 + 2) * 8 + 0x1f800000) = _DAT_1f800300;
            (&DAT_1f800004)[(uint)*(byte *)((int)puVar4 + 2) * 2] = _DAT_1f800304;
            sVar8 = sVar8 + 1;
            uVar3 = *puVar4 & 0xffff01ff;
            *puVar4 = uVar3;
            bVar1 = *pbVar5;
            pbVar5 = pbVar5 + 3;
            uVar2 = (uint)(bVar1 >> 2);
          }
          else {
            _DAT_1f800300 = *(uint *)((uVar2 >> 0xd & 0x7f8) + 0x1f800000);
            _DAT_1f800304 = (&DAT_1f800004)[(uint)*(byte *)((int)puVar4 + 2) * 2];
            uVar3 = *puVar4 & 0xf7ff01ff;
            *puVar4 = uVar3;
            uVar2 = (int)(_DAT_1f800300 << 0x10) >> 0x12;
          }
          *puVar4 = uVar3 | uVar2 << 9;
          goto LAB_800b563c;
        }
        iVar7 = 0;
        pbVar6 = pbVar5 + 1;
        do {
          if ((*puVar4 & 0x4000000) == 0) {
            _DAT_1f800300 = (uint)CONCAT12(pbVar6[1],(ushort)*pbVar5);
            sVar8 = sVar8 + 1;
            _DAT_1f800304 = _DAT_1f800304 & 0xffff0000 | (uint)*pbVar6;
            *(uint *)((uint)*(byte *)((int)puVar4 + 2) * 8 + 0x1f800000) = _DAT_1f800300;
            (&DAT_1f800004)[(uint)*(byte *)((int)puVar4 + 2) * 2] = _DAT_1f800304;
            pbVar6 = pbVar6 + 3;
            uVar3 = *puVar4 & 0xffff01ff;
            *puVar4 = uVar3;
            bVar1 = *pbVar5;
            pbVar5 = pbVar5 + 3;
            uVar2 = (uint)(bVar1 >> 2);
          }
          else {
            _DAT_1f800300 = *(uint *)((*puVar4 >> 0xd & 0x7f8) + 0x1f800000);
            _DAT_1f800304 = (&DAT_1f800004)[(uint)*(byte *)((int)puVar4 + 2) * 2];
            uVar3 = *puVar4 & 0xf7ff01ff;
            *puVar4 = uVar3;
            uVar2 = (int)(_DAT_1f800300 << 0x10) >> 0x12;
          }
          *puVar4 = uVar3 | uVar2 << 9;
          iVar7 = iVar7 + 1;
          puVar4 = puVar4 + 1;
        } while (iVar7 * 0x10000 >> 0x10 < 3);
      }
      uVar2 = *puVar4;
    } while (uVar2 != 0xffffffff);
  }
  
  // Only if there are four players,
  // do not wave the banner, leave it flat
  if (3 < (byte)PTR_DAT_8008d2ac[0x1ca8]) 
  {
	// modelHeader->ptrFrameData[modelHeader->ptrFrameData->vertexOffset]
    uVar2 = *(int *)(param_1 + 0x24) + *(int *)(*(int *)(param_1 + 0x24) + 0x18);
    
	uVar3 = uVar2 + (int)sVar8 * 3;
    while (uVar2 < uVar3) {
      *(undefined *)(uVar2 + 1) = 0x80;
      uVar2 = uVar2 + 3;
    }
  }
  return (int)sVar8;
}

// RB_Banner_Animate_Play
void FUN_800b56c4(int param_1,short param_2)
{
  byte bVar1;
  int iVar2;
  uint uVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  byte *pbVar6;
  int iVar7;
  byte *pbVar8;
  undefined4 uVar9;
  
  // modelHeader -> ptrColors
  puVar4 = *(undefined4 **)(param_1 + 0x2c);
  
  iVar7 = 0;
  uVar9 = *puVar4;
  puVar5 = puVar4;
  do {
    puVar5 = puVar5 + 1;
    iVar7 = iVar7 + 1;
    *puVar4 = *puVar5;
    puVar4 = puVar4 + 1;
  } while (iVar7 * 0x10000 >> 0x10 < 0x3f);
  *puVar4 = uVar9;
  
  // modelHeader -> ptrColors
  iVar7 = *(int *)(param_1 + 0x2c);
  
  // modelHeader->ptrFrameData[modelHeader->ptrFrameData->vertexOffset]
  pbVar6 = (byte *)(*(int *)(param_1 + 0x24) + *(int *)(*(int *)(param_1 + 0x24) + 0x18));
  
  pbVar8 = pbVar6 + (int)param_2 * 3;
  do {
    if (pbVar8 <= pbVar6) {
      return;
    }
    bVar1 = *(byte *)(((((uint)*pbVar6 << 0x10) >> 0x12) + 10 & 0x3f) * 4 + iVar7);
    uVar3 = (int)((uint)*pbVar6 << 0x10) >> 0x10;
    if (uVar3 < 0x40) {
      iVar2 = uVar3 << 2;
LAB_800b5788:
      bVar1 = (char)(((uint)bVar1 - 0x80) * iVar2 >> 8) + 0x80;
    }
    else {
      if (0xc0 < uVar3) {
        iVar2 = (0x100 - uVar3) * 4;
        goto LAB_800b5788;
      }
    }
    pbVar6[1] = bVar1;
    pbVar6 = pbVar6 + 3;
  } while( true );
}

// RB_Banner_ThTick
void FUN_800b57b4(int param_1)
{
  // thread -> object -> 2???
  
  // Basically checks if banner should wave,
  // which does not happen in 3P or 4P multiplayer
  if (*(short *)(*(int *)(param_1 + 0x30) + 2) != 0) 
  {
	// RB_Banner_Animate_Play
    FUN_800b56c4(
		
		// thread -> instance -> model -> pointerModelHeaders
		*(undefined4 *)(*(int *)(*(int *)(param_1 + 0x34) + 0x18) + 0x14),
		
		// frame index?
		*(short *)(*(int *)(param_1 + 0x30) + 2)
		
		);
  }
  return;
}

// RB_Banner_LInB
void FUN_800b57f8(int param_1)
{
  undefined *puVar1;
  int iVar2;
  uint uVar3;
  char cVar4;
  int iVar5;
  char *pcVar6;
  char *pcVar7;
  undefined2 *puVar8;
  
  // If this instance has no thread
  if (*(int *)(param_1 + 0x6c) == 0) 
  {
	// PROC_BirthWithObject
	// 0x4 = size
	// 0 = no relation to param4
	// 0x300 = SmallStackPool
	// 0x3 = "static" thread bucket
    iVar2 = FUN_8004205c(0x40303,FUN_800b57b4,s_startbanner_800b3cf8,0);
	
	// give thread to instance
    *(int *)(param_1 + 0x6c) = iVar2;
	
	// if the thread built successfully
    if (iVar2 != 0) 
	{
	  // if more than 3 screens
      if (3 < (byte)PTR_DAT_8008d2ac[0x1ca8]) 
	  {
		// there is no function per frame,
		// so the flag does not wave
        *(undefined4 *)(iVar2 + 0x2c) = 0;
      }
	  
      puVar1 = PTR_DAT_8008d2ac;
	  
	  // get the object created with the thread
      puVar8 = *(undefined2 **)(iVar2 + 0x30);
	  
	  // give Instance to thread
      *(int *)(iVar2 + 0x34) = param_1;
	  
	  // initialize the object
      *puVar8 = 0;
      puVar8[1] = 0;
	  
	  // Pointer to Startbanner model
      iVar2 = *(int *)(puVar1 + 0x23f8);
	  
	  // if startbanner model is loaded
      if (iVar2 != 0) 
	  {
		// instance -> model
        *(int *)(param_1 + 0x18) = iVar2;
		
		// RB_Banner_Animate_Init
		// pass model -> modelHeader
        uVar3 = FUN_800b53e0(*(undefined4 *)(iVar2 + 0x14));
        
		puVar8[1] = (short)uVar3;
        
		if ((uVar3 & 0xffff) != 0) 
		{
          iVar2 = 0;
		  
		  // instance -> model -> modelHeader -> ptrColors
          pcVar7 = *(char **)(*(int *)(*(int *)(param_1 + 0x18) + 0x14) + 0x2c);
          
		  pcVar6 = pcVar7 + 1;
		  
		  // iVar2 = 0; iVar4 < 0x40; iVar2++
          do {
            uVar3 = (iVar2 << 0x10) >> 9;
			
			// approximate trigonometry
            iVar5 = (&DAT_800845a0)[uVar3 & 0x3ff];
            
			if ((uVar3 & 0x400) == 0) {
              iVar5 = iVar5 << 0x10;
            }
            iVar5 = iVar5 >> 0x10;
            if ((uVar3 & 0x800) != 0) {
              iVar5 = -iVar5;
            }
            cVar4 = (char)(iVar5 >> 6) + -0x80;
			
			// if more than 3 screens
            if (3 < (byte)PTR_DAT_8008d2ac[0x1ca8]) {
              cVar4 = -0x80;
            }
            iVar2 = iVar2 + 1;
            pcVar6[1] = cVar4;
            *pcVar6 = cVar4;
            pcVar6 = pcVar6 + 4;
            *pcVar7 = cVar4;
            pcVar7 = pcVar7 + 4;
          } while (iVar2 * 0x10000 >> 0x10 < 0x40);
        }
      }
    }
  }
  return;
}

// RB_Armadillo_ThTick_TurnAround
void FUN_800b5984(int param_1)
{
  char cVar1;
  short sVar2;
  undefined2 uVar3;
  int iVar4;
  code *pcVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  
  // thread -> object
  iVar8 = *(int *)(param_1 + 0x30);
  
  // thread -> instance
  iVar7 = *(int *)(param_1 + 0x34);
  
  // infinite loop?
  do 
  {
	// if current rotation is the desired rotation, then stop spinning
    if ((int)*(short *)(iVar8 + 2) == (int)*(short *)(iVar8 + 10)) 
	{
	  // instance->animFrame
      sVar2 = *(short *)(iVar7 + 0x54);
	  
	  // INSTANCE_GetNumAnimFrames
      iVar4 = FUN_80030f58(iVar7,0);
	  
	  // if animation is not done
      if ((int)sVar2 + 1 < iVar4) goto LAB_800b5a08;
	  
	  // if animation is done
	  
	  // invert velX, to reverse armadillo direction
      *(short *)(iVar8 + 6) = -*(short *)(iVar8 + 6);
	  
	  // unused
	  // numFramesSpinning
      *(undefined2 *)(iVar8 + 0x12) = 0;
      
	  // invert velZ, to reverse armadillo direction
	  *(short *)(iVar8 + 0xe) = -*(short *)(iVar8 + 0xe);
      
	  // if direction is zero
	  if (*(short *)(iVar8 + 0x1a) == 0) 
	  {
		// play armadillo roll sound
        FUN_8002f0dc(0x70,iVar7);
		
		// go the other way, direction = 1
        *(undefined2 *)(iVar8 + 0x1a) = 1;
      }
	  
	  // if direction is 1
      else 
	  {
		// play armadillo roll sound
        FUN_8002f0dc(0x70,iVar7);
		
		// go the other way, direction = 0
        *(undefined2 *)(iVar8 + 0x1a) = 0;
      }
	  
	  // set animation to 1 (rolling)
      *(undefined *)(iVar7 + 0x52) = 1;
	  
	  // reset animation frame
      *(undefined2 *)(iVar7 + 0x54) = 0;
	  
	  // Change ThTick to RB_Armadillo_ThTick_Rolling
      FUN_800716ec(param_1,&FUN_800b5b74);
    }
    else 
	{
	  // RB_Hazard_InterpolateValue
	  
	  // rotate armadillo to desired rotation
      uVar3 = FUN_800ada90((int)*(short *)(iVar8 + 2),(int)*(short *)(iVar8 + 10),0x100);
      *(undefined2 *)(iVar8 + 2) = uVar3;
	  
	  // convert 3 rotation shorts into rotation matrix
      FUN_8006c2a4(iVar7 + 0x30,iVar8);

LAB_800b5a08:
		// increment animation frame
      *(short *)(iVar7 + 0x54) = *(short *)(iVar7 + 0x54) + 1;
    }
	
	// check for collision with human drivers
    iVar4 = FUN_800314e0(iVar7,param_1,*(undefined4 *)(PTR_DAT_8008d2ac + 0x1b2c),0x2400);
    
	// if there is no collision with human drivers
	if (iVar4 == 0) 
	{
	  // check for collision with AI drivers
      iVar4 = FUN_800314e0(iVar7,param_1,*(undefined4 *)(PTR_DAT_8008d2ac + 0x1b40),0x2400);
	  
	  // if there is no collision with AI drivers
      if (iVar4 == 0) 
	  {
		// check for collision with Mines (tnt, beaker, etc)
        iVar4 = FUN_800314e0(iVar7,param_1,*(undefined4 *)(PTR_DAT_8008d2ac + 0x1b7c),0x2400);
		
		// if there is a collision
        if (iVar4 != 0) 
		{
		  // instance -> thread -> funcThCollide
          pcVar5 = *(code **)(*(int *)(iVar4 + 0x6c) + 0x28);
		  
		  // execute funcThCollide
          (*pcVar5)(*(int *)(iVar4 + 0x6c));
        }
      }
	  
	  // if there is collision with an AI driver
      else 
	  {
		// RB_Hazard_HurtDriver (spin out)
        FUN_800ac1b0(*(undefined4 *)(*(int *)(iVar4 + 0x6c) + 0x30),1,0,0);
      }
    }
	
	// if there is collision with human drivers
    else 
	{
	  // get driver object
      iVar6 = *(int *)(*(int *)(iVar4 + 0x6c) + 0x30);
	  
	  // get kart state
      cVar1 = *(char *)(iVar6 + 0x376);
	  
	  // RB_Hazard_HurtDriver (spin out)
      iVar4 = FUN_800ac1b0(iVar6,1,0,0);
      
	  // if change state worked, and if kart was not
	  // already spinning out before this
	  if ((iVar4 != 0) && (cVar1 != '\x03')) 
	  {
		// play armadillo hit sound
        FUN_80028494(0x71,1,(uint)*(ushort *)(iVar6 + 0x2ca) & 1);
      }
    }
	
	// this skips $RA backup/restore, faster than JR $RA
    FUN_80071694(param_1);
	
  } while( true );
}

// RB_Armadillo_ThTick_Rolling
void FUN_800b5b74(int param_1)
{
  char cVar1;
  short sVar2;
  int iVar3;
  code *pcVar4;
  int iVar5;
  undefined2 *puVar6;
  int iVar7;
  undefined2 uStack40;
  undefined2 uStack38;
  undefined2 uStack36;
  
  // thread -> object
  puVar6 = *(undefined2 **)(param_1 + 0x30);
  
  // thread -> instance
  iVar7 = *(int *)(param_1 + 0x34);
  
  // infinite loop?
  do 
  {
	// if time at edge is zero
    if (puVar6[0xe] == 0) 
	{
	  // if Time Rolling < 0x500 (1.333 seconds)
      if ((short)puVar6[8] < 0x500) 
	  {
		// increase Time Rolling
		// add 32 milliseconds, assuming 30fps
        puVar6[8] = puVar6[8] + 0x20;
		
		// if direction is zero
        if (puVar6[0xd] == 0) 
		{
		  // increase distance from spawn
          sVar2 = puVar6[10] + 1;
        }
		
		// if direction is 1
        else 
		{
		  // decrease distance from spawn
          sVar2 = puVar6[10] + -1;
        }
		
		// set distance from spawn
        puVar6[10] = sVar2;
		
		// instance -> animationFrame
        sVar2 = *(short *)(iVar7 + 0x54);
		
		// instance -> posX += velX
        *(int *)(iVar7 + 0x44) = *(int *)(iVar7 + 0x44) + (int)(short)puVar6[3];
		
		// instance -> posZ += velZ
        *(int *)(iVar7 + 0x4c) = *(int *)(iVar7 + 0x4c) + (int)(short)puVar6[7];
		
		// INSTANCE_GetNumAnimFrames
        iVar3 = FUN_80030f58(iVar7);
		
		// if animation is not done
        if ((int)sVar2 + 1 < iVar3) 
		{
		  // increment animation frame
          *(short *)(iVar7 + 0x54) = *(short *)(iVar7 + 0x54) + 1;
        }
		
		// if animation is done
        else 
		{
		  // restart animation
          *(undefined2 *)(iVar7 + 0x54) = 0;
        }
		
		// Check for collision with human drivers
        iVar3 = FUN_800314e0(iVar7,param_1,*(undefined4 *)(PTR_DAT_8008d2ac + 0x1b2c),0x2400);
        
		// if armadillo did not collide with any human driver
		if (iVar3 == 0) 
		{
		  // Check for collision with AI drivers
          iVar3 = FUN_800314e0(iVar7,param_1,*(undefined4 *)(PTR_DAT_8008d2ac + 0x1b40),0x2400);
          
		  // if there is no collision with AIs
		  if (iVar3 == 0) 
		  {
            // Check for collision with Mines (tnts, beakers, etc)
			iVar3 = FUN_800314e0(iVar7,param_1,*(undefined4 *)(PTR_DAT_8008d2ac + 0x1b7c),0x2400);
            
			// if there is a collision
			if (iVar3 != 0) 
			{
			  // funcThCollide
              pcVar4 = *(code **)(*(int *)(iVar3 + 0x6c) + 0x28);
			  
			  // execute funcThCollide
              (*pcVar4)(*(int *)(iVar3 + 0x6c));
            }
          }
		  
		  // if there is collision with AIs
          else 
		  {
			// RB_Hazard_HurtDriver (spin out)
            FUN_800ac1b0(*(undefined4 *)(*(int *)(iVar3 + 0x6c) + 0x30),1,0,0);
          }
        }
		
		// if armadillo collided with a driver
        else 
		{
		  // instance -> thread -> (Driver*) object
          iVar5 = *(int *)(*(int *)(iVar3 + 0x6c) + 0x30);
          
		  // get kart state
		  cVar1 = *(char *)(iVar5 + 0x376);
          
		  // RB_Hazard_HurtDriver (spin out)
		  iVar3 = FUN_800ac1b0(iVar5,1,0,0);
		  
		  // if change state worked, and if kart was not
		  // already spinning out before this
          if ((iVar3 != 0) && (cVar1 != '\x03')) 
		  {
			// play armadillo hit sound
            FUN_80028494(0x71,1,(uint)*(ushort *)(iVar5 + 0x2ca) & 1);
          }
        }
      }
      
	  // if armadillo rolled for more than 0x500 frames
	  else 
	  {
		// CTR_MatrixToRot
		// iVar7+30 = armadillo inst->matrix
        FUN_80021edc(&uStack40,iVar7 + 0x30,0x11);
		
		// reset rotation,
		// reset timeRolling
        *puVar6 = uStack38;
        puVar6[1] = uStack40;
        puVar6[8] = 0;
        puVar6[2] = uStack36;
        
		// set animation index to zero (jumping)
		*(undefined *)(iVar7 + 0x52) = 0;
		
		// reset animation
        *(undefined2 *)(iVar7 + 0x54) = 0;
		
		// set desired rotation, 180 degrees from current
        iVar5 = (int)(short)puVar6[1] + 0x800;
        iVar3 = iVar5;
        if (iVar5 < 0) {
          iVar3 = (int)(short)puVar6[1] + 0x17ff;
        }
        puVar6[5] = (short)iVar5 + (short)(iVar3 >> 0xc) * -0x1000;
		
		// Change thread to RB_Armadillo_ThTick_TurnAround
        FUN_800716ec(param_1,&FUN_800b5984);
      }
    }
    
	// if you are waiting at edge
	// before rolling again
	else 
	{
	  // reduce by one frame
      puVar6[0xe] = puVar6[0xe] + -1;
    }
	
	// this skips $RA backup/restore, faster than JR $RA
    FUN_80071694(param_1);
  
  } while( true );
}

// RB_Armadillo_ThCollide
void FUN_800b5dbc(int param1, int param_2, int param_3, int param_4)
{ 
  // check if modelID is player
  // modelID is 0xc of BSP meta
  
  return (uint)(*(short *)(param_4 + 0xc) == 0x18);
}

// RB_Armadillo_LInB
void FUN_800b5dd0(int param_1)
{
  undefined2 uVar1;
  undefined *puVar2;
  int iVar3;
  int iVar4;
  undefined2 *puVar5;
  undefined2 local_18;
  undefined2 local_16;
  undefined2 local_14;
  
  // If this instance has no thread
  if (*(int *)(param_1 + 0x6c) == 0) 
  {
	// PROC_BirthWithObject
	// 0x20 = size
	// 0 = no relation to param4
	// 0x300 = SmallStackPool
	// 0x3 = "static" thread bucket
    iVar3 = FUN_8004205c(0x200303,&FUN_800b5b74,s_armadillo_800b5978,0);
	
	// give thread to instance
    *(int *)(param_1 + 0x6c) = iVar3;
	
	// if thread exists
    if (iVar3 != 0) 
	{
	  // Set animation to 1 (rolling)
      *(undefined *)(param_1 + 0x52) = 1;
	  
	  // get the object created by the thread
      puVar5 = *(undefined2 **)(iVar3 + 0x30);
	  
	  // give instance to thread
      *(int *)(iVar3 + 0x34) = param_1;
	  
	  // set funcThCollide to hurt the player
      *(undefined4 *)(iVar3 + 0x28) = 0x800b5dbc;
	  
	  // time rolling
      puVar5[8] = 0;
	  
	  // unused
	  // numFramesSpinning
      puVar5[9] = 0;
	  
	  // CTR_MatrixToRot
	  // param1+30 = armadillo inst->matrix
      FUN_80021edc(&local_18,param_1 + 0x30,0x11);
      
	  // rotX
	  *puVar5 = local_16;
      
	  // rotY
	  puVar5[1] = local_18;
      
	  // rotY + 180 degrees
	  iVar4 = (int)(short)puVar5[1] + 0x800;
      
	  // rotZ
	  puVar5[2] = local_14;
      
	  // set desired rotation, 180 degrees from current
	  iVar3 = iVar4;
      if (iVar4 < 0) {
        iVar3 = (int)(short)puVar5[1] + 0x17ff;
      }
      puVar5[5] = (short)iVar4 + (short)(iVar3 >> 0xc) * -0x1000;
	  
	  // posX
      puVar5[0xb] = *(undefined2 *)(param_1 + 0x44);
	  
	  // posZ
      uVar1 = *(undefined2 *)(param_1 + 0x4c);
      
	  // set direction to zero
	  // move away from spawn
	  puVar5[0xd] = 0;
	  
	  // distFromSpawn
      puVar5[10] = 0;
	  
	  // posZ
      puVar5[0xc] = uVar1;
	  
	  // velX from forward direction of Instance MATRIX
      puVar5[3] = *(short *)(param_1 + 0x34) >> 7;
	  
      puVar2 = PTR_DAT_8008d2ac;
      
	  // velZ from forward direction of Instance MATRIX
	  puVar5[7] = *(short *)(param_1 + 0x40) >> 7;
	  
	  // gGT -> Level -> ptrSpawn1 -> numPointers
      if (0 < **(int **)(*(int *)(puVar2 + 0x160) + 0x134)) 
	  {
		// get length of instance's name
        iVar3 = strlen(param_1 + 8);
		
		// time at edge
		// puts armadillos on different cycles
        puVar5[0xe] = *(undefined2 *)
                       (*(int *)(*(int *)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0x134) + 8) +
					   
					   // armadillo ID
                       ((uint)*(byte *)(iVar3 + param_1 + 7) - 0x30) * 2);
      }
    }
  }
  return;
}

// RB_Fireball_ThTick
void FUN_800b5f50(int param_1)
{
  short sVar1;
  ushort uVar2;
  ushort uVar3;
  undefined *puVar4;
  code *pcVar5;
  undefined2 uVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  short *psVar10;
  uint uVar11;
  
  // get object from thread
  psVar10 = *(short **)(param_1 + 0x30);
  
  // get instance from thread
  iVar9 = *(int *)(param_1 + 0x34);
  
  // cooldown timer
  uVar2 = psVar10[2];
  
  uVar11 = 0;
  
  // if cooldown is over
  if (psVar10[2] == 0) 
  {
	// make invisible
    *(uint *)(iVar9 + 0x28) = *(uint *)(iVar9 + 0x28) | 0x80;
	
    puVar4 = PTR_DAT_8008d2ac;
	
    if ((int)*(short *)(*(int *)(iVar9 + 0x2c) + 0x32) + -0x440 <= *(int *)(iVar9 + 0x48)) 
	{
	  // velY
      uVar11 = (uint)(ushort)psVar10[6];
	  
	  // Change height by elapsed time
      *(int *)(iVar9 + 0x48) =
           *(int *)(iVar9 + 0x48) + ((int)psVar10[6] * *(int *)(PTR_DAT_8008d2ac + 0x1d04) >> 5);
      
	  // subtract velY, which makes fireball move down
	  iVar7 = (uint)(ushort)psVar10[6] - (*(int *)(puVar4 + 0x1d04) * 10 >> 5);
	  
	  // set new velY
      psVar10[6] = (short)iVar7;
	  
	  // terminal velocity
      if (iVar7 * 0x10000 >> 0x10 < -200) 
	  {
		// cant fall faster
        psVar10[6] = -200;
      }
      
	  // Create instance in particle pool
	  iVar7 = FUN_80040308(0,*(undefined4 *)(PTR_DAT_8008d2ac + 0x213c),&DAT_800b6344);
	  
      if (iVar7 != 0) 
	  {
		// posX and posY
        *(int *)(iVar7 + 0x24) = *(int *)(iVar7 + 0x24) + *(int *)(iVar9 + 0x44) * 0x100;
        *(int *)(iVar7 + 0x2c) = *(int *)(iVar7 + 0x2c) + *(int *)(iVar9 + 0x48) * 0x100;
		
        iVar8 = *(int *)(iVar9 + 0x4c);
        *(undefined2 *)(iVar7 + 0x1a) = 0x1e00;
        
		// posZ
		*(int *)(iVar7 + 0x34) = *(int *)(iVar7 + 0x34) + iVar8 * 0x100;
        
		// velY
		iVar8 = (int)psVar10[6] * -0x180;
		
		// negative range
        if (iVar8 < -0x7fff) {
          iVar8 = -0x7fff;
        }
		
        uVar6 = (undefined2)iVar8;
        
		// positive range
		if (0x7fff < iVar8) {
          uVar6 = 0x7fff;
        }
		
		// particle velY
        *(undefined2 *)(iVar7 + 0x30) = uVar6;
      }
	  
	  // check for collision with players
      iVar7 = FUN_800314e0(iVar9,param_1,*(undefined4 *)(PTR_DAT_8008d2ac + 0x1b2c),0x10000);
      
	  // if there is no collision
	  if ((iVar7 == 0) &&
	  
			// check for collision with robotcars
         (iVar7 = FUN_800314e0(iVar9,param_1,*(undefined4 *)(PTR_DAT_8008d2ac + 0x1b40),0x10000),
         
		 // if there is no collision
		 iVar7 == 0)) 
	  {
		// check for collision with mines (tnt, beaker, etc)
        iVar7 = FUN_800314e0(iVar9,param_1,*(undefined4 *)(PTR_DAT_8008d2ac + 0x1b7c),0x10000);
        
		// if there is a collision
		if (iVar7 != 0) 
		{
		  // instance -> thread -> funcThCollide
          pcVar5 = *(code **)(*(int *)(iVar7 + 0x6c) + 0x28);
		  
		  // execute funcThCollide
          (*pcVar5)(*(int *)(iVar7 + 0x6c));
        }
      }
	  
	  // if you collide with any driver at all
      else 
	  {
		// RB_Hazard_HurtDriver (burn)
        FUN_800ac1b0(*(undefined4 *)(*(int *)(iVar7 + 0x6c) + 0x30),4,0,0);
      }
    }
    
	// cycle timer
	*psVar10 = *psVar10 - *(short *)(PTR_DAT_8008d2ac + 0x1d04);
	
    if (
			(-1 < (int)(uVar11 << 0x10)) && 
			
			// if fireball is far down
			(psVar10[6] < 0)
		) 
	{
	  // direction is now up
      psVar10[7] = 1;
    }
	
	// animation index
    sVar1 = *(short *)(iVar9 + 0x54);
	
	// INSTANCE_GetNumAnimFrames
    iVar7 = FUN_80030f58(iVar9,0);
	
	// increase frames
    if ((int)sVar1 + 1 < iVar7) {
      *(short *)(iVar9 + 0x54) = *(short *)(iVar9 + 0x54) + 1;
    }
    
	// reset animation to zero
	else {
      *(undefined2 *)(iVar9 + 0x54) = 0;
    }
	
	// if cycle is over
    if (*psVar10 < 1) 
	{
      *(int *)(iVar9 + 0x48) = (int)*(short *)(*(int *)(iVar9 + 0x2c) + 0x32) + -0x440;
      
	  // velY,
	  psVar10[6] = 200;
	  
      *(undefined2 *)(iVar9 + 0x54) = 0;
      
	  // direction is down
	  psVar10[7] = 0;
      
	  // reset cycle to 2880ms, 2.8 seconds
	  *psVar10 = 0xb40;
	  
	  // play sound
      FUN_8002f0dc(0x81, iVar9);
    }
  }
  
  // if cooldown is not over
  else 
  {
	// elapsed time per frame ~32
    uVar3 = *(ushort *)(PTR_DAT_8008d2ac + 0x1d04);
	
	// reduce timer
    psVar10[2] = (short)((uint)uVar2 - (uint)uVar3);
    
	// do not go below zero
	if ((int)(((uint)uVar2 - (uint)uVar3) * 0x10000) < 0) {
      
	  // set to zero
	  psVar10[2] = 0;
    }
  }
  return;
}

// RB_Fireball_ThCollide
void FUN_800b625c(int param1, int param_2, int param_3, int param_4)
{ 
  // check if modelID is player
  // modelID is 0xc of BSP meta
  
  return (uint)(*(short *)(param_4 + 0xc) == 0x18);
}

// RB_Fireball_LInB
void FUN_800b6270(int param_1)
{
  int iVar1;
  uint uVar2;
  undefined2 *puVar3;
  
  // If there is no thread for this instance
  if (*(int *)(param_1 + 0x6c) == 0) 
  {
	// PROC_BirthWithObject
	// 0x10 = size
	// 0 = no relation to param4
	// 0x300 = SmallStackPool
	// 0x3 = "static" thread bucket
    iVar1 = FUN_8004205c(0x100303,&FUN_800b5f50,s_fireball_800b5f44,0);
	
	// give thread to instance
    *(int *)(param_1 + 0x6c) = iVar1;
	
	// if the thread built successfully
    if (iVar1 != 0) 
	{
	  // get the object attached to the thread
      puVar3 = *(undefined2 **)(iVar1 + 0x30);
	  
	  // set funcThCollide to burn the player
      *(undefined4 *)(iVar1 + 0x28) = 0x800b625c;
	  
	  // give instance to thread
      *(int *)(iVar1 + 0x34) = param_1;
	  
	  // set scale (x, y, z) of fireball
      *(undefined2 *)(param_1 + 0x1c) = 0x4000;
      *(undefined2 *)(param_1 + 0x1e) = 0x4000;
      *(undefined2 *)(param_1 + 0x20) = 0x4000;
	  
	  // set animation to 0
      *(undefined *)(param_1 + 0x52) = 0;
	  
      iVar1 = strlen(param_1 + 8);
	  
	  // fireball ID
      uVar2 = (uint)*(byte *)(iVar1 + param_1 + 7) - 0x30;
	  
      puVar3[1] = (short)uVar2;
      puVar3[3] = 0;
	  
	  // velY (96)
      puVar3[6] = 0x60;
      
	  // direction is down
	  puVar3[7] = 0;
	  
	  // reset cycle timer
      *puVar3 = 0;
      
	  // set cooldown of fireball 
	  // depending on ID
	  
	  if ((uVar2 & 1) == 0) {
        puVar3[2] = 0;
      }
      else {
        puVar3[2] = 0x5a0;
      }
    }
  }
  return;
}

// RB_FlameJet_Particles
void FUN_800b64c0(int param_1,int param_2)
{
  undefined2 uVar1;
  undefined *puVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  // Create (ordinary) instance in particle pool
  iVar3 = FUN_80040308(0,*(undefined4 *)(PTR_DAT_8008d2ac + 0x213c),&DAT_800b6c20);
  
  puVar2 = PTR_DAT_8008d2ac;
  
  // if instance created successfully
  if (iVar3 != 0) 
  {
	// position of particles
    *(int *)(iVar3 + 0x24) = *(int *)(iVar3 + 0x24) + *(int *)(param_1 + 0x44) * 0x100;
    *(int *)(iVar3 + 0x2c) = *(int *)(iVar3 + 0x2c) + (*(int *)(param_1 + 0x48) + 0x32) * 0x100;
    *(int *)(iVar3 + 0x34) = *(int *)(iVar3 + 0x34) + *(int *)(param_1 + 0x4c) * 0x100;
    
	// dirZ
	uVar1 = *(undefined2 *)(param_2 + 4);
	
	// velY = 0
    *(undefined2 *)(iVar3 + 0x30) = 0;
	
	// velX
    *(undefined2 *)(iVar3 + 0x28) = uVar1;
	
	// velZ = dirZ
    *(undefined2 *)(iVar3 + 0x38) = *(undefined2 *)(param_2 + 8);
	
    iVar4 = FUN_8006c684(puVar2 + 0x252c);
    
	// Sine(angle)
	iVar4 = FUN_8003d184(*(int *)(PTR_DAT_8008d2ac + 0x1cec) * 0x100 + (iVar4 >> 0x18) & 0xfff);
    
	*(undefined2 *)(iVar3 + 0x32) = (short)(iVar4 >> 4);
    *(undefined2 *)(iVar3 + 0x1a) = 0x1e00;
    *(char *)(iVar3 + 0x18) = *(char *)(param_1 + 0x50) + -1;
	
	// odd-numbered frames
    if ((*(uint *)(PTR_DAT_8008d2ac + 0x1cec) & 1) != 0) {
      *(int *)(iVar3 + 0x44) = -*(int *)(iVar3 + 0x44);
      *(short *)(iVar3 + 0x48) = -*(short *)(iVar3 + 0x48);
    }
  }
  
  // if there is one player
  if (((byte)PTR_DAT_8008d2ac[0x1ca8] < 2) &&
     (
		// Create (heat) instance in particle pool
		iVar4 = FUN_80040308(0,*(undefined4 *)(PTR_DAT_8008d2ac + 0x1b24),&DAT_800b6a94),
		iVar4 != 0
	 )) 
  {
	// position
    *(int *)(iVar4 + 0x24) = *(int *)(iVar4 + 0x24) + *(int *)(iVar3 + 0x24);
    *(int *)(iVar4 + 0x2c) = *(int *)(iVar4 + 0x2c) + 0x1000 + *(int *)(iVar3 + 0x2c);
    *(int *)(iVar4 + 0x34) = *(int *)(iVar4 + 0x34) + *(int *)(iVar3 + 0x34);
	
	// dirX
    uVar1 = *(undefined2 *)(param_2 + 4);
	
	// velY
    *(undefined2 *)(iVar4 + 0x30) = 0;
	
	// velX
    *(undefined2 *)(iVar4 + 0x28) = uVar1;
	
	// velZ = dirZ
    *(undefined2 *)(iVar4 + 0x38) = *(undefined2 *)(param_2 + 8);
	
    iVar5 = *(int *)(iVar4 + 0x3c) + -0x400;
    uVar1 = *(undefined2 *)(iVar3 + 0x32);
    iVar3 = *(int *)(iVar4 + 0x3c) + -0x600;
    *(int *)(iVar4 + 0x44) = iVar5;
    *(int *)(iVar4 + 0x4c) = iVar3;
    *(undefined2 *)(iVar4 + 0x1a) = 0x1e00;
    *(undefined2 *)(iVar4 + 0x32) = uVar1;
    *(undefined2 *)(iVar4 + 0x40) = (short)((0x4a00 - *(int *)(iVar4 + 0x3c)) / 7);
    *(undefined2 *)(iVar4 + 0x48) = (short)((0x4600 - iVar5) / 7);
    *(undefined2 *)(iVar4 + 0x50) = (short)((0x4400 - iVar3) / 7);
    *(undefined *)(iVar4 + 0x18) = *(undefined *)(param_1 + 0x50);
  }
  return;
}

// RB_FlameJet_ThTick
void FUN_800b6728(int param_1)
{
  int iVar1;
  int *piVar2;
  int iVar3;
  undefined4 local_48;
  undefined4 local_44;
  int local_40;
  int local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  int local_24;
  undefined4 local_20;
  undefined4 local_1c;
  
  // specular light direction?
  local_48 = DAT_800b64ac;
  local_44 = DAT_800b64b0;
  
  // get object from thread
  piVar2 = *(int **)(param_1 + 0x30);
  
  // get instance from thread
  iVar3 = *(int *)(param_1 + 0x34);
  
  // hitbox info
  local_34 = DAT_800b6d40;
  local_30 = DAT_800b6d44;
  local_2c = DAT_800b6d48;
  local_1c = 0;
  local_40 = iVar3;
  local_3c = param_1;
  local_24 = param_1;
  
  // if cooldown exists
  while (*(short *)((int)piVar2 + 0xe) != 0) 
  {
	// reduce cooldown
    *(short *)((int)piVar2 + 0xe) = *(short *)((int)piVar2 + 0xe) + -1;
	
	// this skips $RA backup/restore, faster than JR $RA
    FUN_80071694(param_1);
  }
  
  do {
    iVar1 = *piVar2;
	
	// in first 45 frames (1.5 seconds)
    if (iVar1 < 0x2d) 
	{
	  // spawn particles and enable burn on collision
		
	  // PlaySound3D_Flags
	  // sound of fire, offset 0x10
      FUN_8002f31c(piVar2 + 4,0x68,iVar3);
	  
	  // offset 0xC (see asm)
      *(short *)(piVar2 + 3) = *(short *)(piVar2 + 3) + 0x100;
      
	  // RB_FlameJet_Particles
	  FUN_800b64c0(iVar3,piVar2);
	  
	  // get first Player thread
      local_38 = *(undefined4 *)(PTR_DAT_8008d2ac + 0x1b2c);
	  
	  // check for collision
      iVar1 = FUN_800315ac(&local_40);
	  
	  // if there is no collision
      if (iVar1 == 0) 
	  {
		// get first robotcar thread
        local_38 = *(undefined4 *)(PTR_DAT_8008d2ac + 0x1b40);
		
		// check for collision
        iVar1 = FUN_800315ac(&local_40,4);
		
		// if there is no collision
        if (iVar1 == 0) 
		{
		  // get first Mine thread
          local_38 = *(undefined4 *)(PTR_DAT_8008d2ac + 0x1b7c);
		  
		  // check for collision
          iVar1 = FUN_800315ac(&local_40,4);
		  
		  // if there is collision
          if (iVar1 != 0) 
		  {
			// instance -> thread
            local_28 = *(undefined4 *)(iVar1 + 0x6c);
			
			// instance -> thread -> funcThCollide
            local_20 = *(undefined4 *)(*(int *)(iVar1 + 0x6c) + 0x28);
			
			// RB_Hazard_ThCollide_Generic_Alt
            FUN_800ac3f8(&local_28);
          }
          goto LAB_800b6908;
        }
      }
	  
	  // RB_Hazard_HurtDriver (burn)
      FUN_800ac1b0(*(undefined4 *)(*(int *)(iVar1 + 0x6c) + 0x30),4,0,0);
    }
    else 
	{
	  // on 45th frame (after 1.5 seconds)
      if (iVar1 == 0x2d) 
	  {
		// if audioPtr is valid
        if (piVar2[4] != 0) 
		{
		  // stop audio
          FUN_8002e724(piVar2 + 4);
        }
      }
      else 
	  {
		// repeat cycle every 105 (3.5 seconds)
        if (0x69 < iVar1) {
          *piVar2 = 0;
        }
      }
    }
LAB_800b6908:

	// increment frame
    *piVar2 = *piVar2 + 1;
	
	// Vector_SpecLightNoSpin3D
	// instance, inst->instDef->rot[3], specLightDir
    FUN_800576b8(iVar3,*(int *)(iVar3 + 0x2c) + 0x36,&local_48);
	
	// this skips $RA backup/restore, faster than JR $RA
    FUN_80071694(param_1);
	
  } while( true );
}

// RB_FlameJet_LInB
void FUN_800b6938(int param_1)
{
  short sVar1;
  int iVar2;
  undefined4 *puVar3;
  
  // Instance color: Yellow
  *(undefined4 *)(param_1 + 0x24) = 0xdca6000;
  
  // specular light
  *(uint *)(param_1 + 0x28) = *(uint *)(param_1 + 0x28) | 0x30000;
  
  if (*(int *)(param_1 + 0x6c) == 0) 
  {
	// PROC_BirthWithObject
	// 0x14 = size
	// 0 = no relation to param4
	// 0x300 = SmallStackPool
	// 0x3 = static thread bucket
    iVar2 = FUN_8004205c(0x140303,FUN_800b6728,s_flamejet_800b64b4,0);
	
	// give thread to instance
    *(int *)(param_1 + 0x6c) = iVar2;
    
	// if thread built correctly
	if (iVar2 != 0) 
	{
	  // object from thread
      puVar3 = *(undefined4 **)(iVar2 + 0x30);
      
	  // give instance to thread
	  *(int *)(iVar2 + 0x34) = param_1;
      
	  // cycle timer
	  *puVar3 = 0;
	  
	  // cooldown
      *(undefined2 *)((int)puVar3 + 0xe) = 0;
      
	  // dirX
	  puVar3[1] = (int)*(short *)(param_1 + 0x34) * -0x4b >> 5;
      
	  sVar1 = *(short *)(param_1 + 0x40);
      puVar3[4] = 0;
	  
	  // dirZ
      puVar3[2] = (int)sVar1 * 0x4b >> 5;
	  
	  // hitbox
      DAT_800b6d44._2_2_ = 0x40;
      DAT_800b6d40._0_2_ = 0xffc0;
      DAT_800b6d40._2_2_ = 0xffc0;
      DAT_800b6d48._0_2_ = 0x80;
      DAT_800b6d48._2_2_ = 0x140;
      DAT_800b6d44._0_2_ = 0;
	  
	  // LEV -> ptrSpawn1 -> numPointers
      if (0 < **(int **)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0x134)) {
        
		// probably strlen
		iVar2 = FUN_80077cc8(param_1 + 8);
        
		// cooldown
		*(undefined2 *)((int)puVar3 + 0xe) =
             *(undefined2 *)
              (*(int *)(*(int *)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0x134) + 8) +
			  
			  // flamejet ID from string
              ((uint)*(byte *)(iVar2 + param_1 + 7) - 0x30) * 2);
      }
    }
  }
  return;
}

// RB_Follower_ProcessBucket
void FUN_800b6d58(int param_1)
{
  undefined *puVar1;
  undefined *puVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  
  puVar1 = PTR_DAT_8008d2ac;
  
  // if first thread exists
  if (param_1 != 0) 
  {
	// loop through all threads
    do {
      puVar2 = PTR_DAT_8008d2ac;
	  
	  // if thread is not dead
      if ((*(uint *)(param_1 + 0x1c) & 0x800) == 0) 
	  {
		// object
        iVar6 = *(int *)(param_1 + 0x30);
		
		// instance
        iVar5 = *(int *)(param_1 + 0x34);
        
		// follower->driver->driverID
		uVar4 = (uint)*(byte *)(*(int *)(iVar6 + 4) + 0x4a);
        
		uVar3 = 0;
		
		// loop for number of players
        if (puVar1[0x1ca9] != '\0') {
          do 
		  {
			// if this camera does not belong
			// to the driver that shot the weapon
            if (uVar4 != uVar3) {
              *(uint *)(iVar5 + 0xb8) = *(uint *)(iVar5 + 0xb8) & 0xffffffbf;
            }
            uVar3 = uVar3 + 1;
            iVar5 = iVar5 + 0x88;
          } while ((int)uVar3 < (int)(uint)(byte)puVar2[0x1ca9]);
        }
		
		// follower->mineTh->instance->idpp
        iVar5 = *(int *)(*(int *)(iVar6 + 8) + 0x34) + uVar4 * 0x88;
        *(uint *)(iVar5 + 0xb8) = *(uint *)(iVar5 + 0xb8) & 0xffffffbf;
      }
	
	  // follower->next
      param_1 = *(int *)(param_1 + 0x10);
    
	} while (param_1 != 0);
  }
  return;
}

// RB_Follower_ThTick
void FUN_800b6e10(int param_1)
{
  char cVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  
  // thread -> object
  piVar3 = *(int **)(param_1 + 0x30);
  
  // follower->driver
  iVar4 = piVar3[1];
  
  // frame count
  iVar2 = *piVar3;
  
  // driver state
  cVar1 = *(char *)(iVar4 + 0x376);
  
  // subtract one frame
  *piVar3 = iVar2 + -1;
  
  if (
		(
			(0 < iVar2 + -1) &&
			((
				// driver state (normal, or drifting)
				(cVar1 == '\0' || (cVar1 == '\x02')) && 
				
				// mineTh->timesDestroyed == obj->backup,
				// determines if mine was destroyed
				(*(int *)(piVar3[2] + 0x20) == piVar3[3])
			))
		) &&
		
		// if driving forward
		(-1 < *(short *)(iVar4 + 0x38e))
	  ) 
  {
	// thread -> instance
    iVar2 = *(int *)(param_1 + 0x34);
	
	// if scale is small
    if (*(short *)(iVar2 + 0x1c) < 0x800) 
	{
	  // double the scale (x, y, z)
      *(short *)(iVar2 + 0x1c) = *(short *)(iVar2 + 0x1c) << 1;
      *(short *)(iVar2 + 0x1e) = *(short *)(iVar2 + 0x1e) << 1;
      *(short *)(iVar2 + 0x20) = *(short *)(iVar2 + 0x20) << 1;
    }
	
	// Change X, Y, Z, of mine, to the 
	// midpoint between the current driver position,
	// and the "realPos" of mine. This reduces motion sickness
    *(int *)(iVar2 + 0x44) = (int)*(short *)((int)piVar3 + 0x10) + (*(int *)(iVar4 + 0x2d4) >> 8) >> 1;
    *(int *)(iVar2 + 0x48) = (int)*(short *)((int)piVar3 + 0x12) + (*(int *)(iVar4 + 0x2d8) >> 8) >> 1;
    *(int *)(iVar2 + 0x4c) = (int)*(short *)((int)piVar3 + 0x14) + (*(int *)(iVar4 + 0x2dc) >> 8) >> 1;
    return;
  }
  
  // This thread is now dead
  *(uint *)(param_1 + 0x1c) = *(uint *)(param_1 + 0x1c) | 0x800;
  
  return;
}

// RB_Follower_Init
void FUN_800b6f00(int param_1,int param_2)
{
  int iVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  
  if (
		(
			// driver->speed > 0x1e00
			(0x1e00 < *(short *)(param_1 + 0x38e)) && 
			
			// if driver is not an AI
			((*(uint *)(param_1 + 0x2c8) & 0x100000) == 0)
		) &&
     
		(
			// cameraBuffer[driver -> index]
			(*(uint *)(PTR_DAT_8008d2ac + (uint)*(byte *)(param_1 + 0x4a) * 0xdc + 0x1508) & 0x10000) == 0
		)
	) 
  {
		 
	// create a thread and an Instance
	// 0x18 - Follower size
	// 0x300 flag = SmallStackPool
	// 0xb = "follower" thread bucket
    iVar1 = FUN_800309a4((int)*(short *)(param_2 + 0x44),s_follower_800b6d4c,0x300,0xb,
                         &FUN_800b6e10,0x18,0);
    
	// if that worked successfully
	if (iVar1 != 0) 
	{
	  // set the scale
      *(undefined2 *)(iVar1 + 0x1c) = 0x200;
      *(undefined2 *)(iVar1 + 0x1e) = 0x200;
      *(undefined2 *)(iVar1 + 0x20) = 0x200;
	  
	  // get instance from thread
      iVar3 = *(int *)(param_2 + 0x34);
	  
	  // copy position and rotation from one instance to another
      uVar4 = *(undefined4 *)(iVar3 + 0x34);
      uVar5 = *(undefined4 *)(iVar3 + 0x38);
      uVar6 = *(undefined4 *)(iVar3 + 0x3c);
      *(undefined4 *)(iVar1 + 0x30) = *(undefined4 *)(iVar3 + 0x30);
      *(undefined4 *)(iVar1 + 0x34) = uVar4;
      *(undefined4 *)(iVar1 + 0x38) = uVar5;
      *(undefined4 *)(iVar1 + 0x3c) = uVar6;
      uVar4 = *(undefined4 *)(iVar3 + 0x44);
      uVar5 = *(undefined4 *)(iVar3 + 0x48);
      uVar6 = *(undefined4 *)(iVar3 + 0x4c);
      *(undefined4 *)(iVar1 + 0x40) = *(undefined4 *)(iVar3 + 0x40);
      *(undefined4 *)(iVar1 + 0x44) = uVar4;
      *(undefined4 *)(iVar1 + 0x48) = uVar5;
      *(undefined4 *)(iVar1 + 0x4c) = uVar6;
	  
	  // Get the thread
      iVar1 = *(int *)(iVar1 + 0x6c);
	  
	  // set funcThDestroy to remove instance from instance pool
      *(undefined4 *)(iVar1 + 0x24) = 0x80041dfc;
      
	  // get the object attached to the thread
	  puVar2 = *(undefined4 **)(iVar1 + 0x30);
	  
	  // obj->frameCount
      *puVar2 = 7;
	  
	  // obj->driver
      puVar2[1] = param_1;
	  
	  // obj->mineTh
      puVar2[2] = param_2;
	  
	  // obj->backup = mineTh->timesDestroyed
      puVar2[3] = *(undefined4 *)(param_2 + 0x20);
	  
	  // save "real" position of mine
      *(undefined2 *)((int)puVar2 + 0x10) = *(undefined2 *)(iVar3 + 0x44);
      *(undefined2 *)((int)puVar2 + 0x12) = *(undefined2 *)(iVar3 + 0x48);
      *(undefined2 *)((int)puVar2 + 0x14) = *(undefined2 *)(iVar3 + 0x4c);
    }
  }
  return;
}

// RB_Fruit_ThTick
// This is useless, both thread death and pointer erasing
// happen inside RB_Fruit_ThCollide anyway
void FUN_800b706c(int param_1)
{
  int iVar1;
  
  // thread -> instance
  iVar1 = *(int *)(param_1 + 0x34);
  
  // erase (instance -> thread)
  *(undefined4 *)(iVar1 + 0x6c) = 0;
  
  do 
  {
	// This thread is now dead
    *(uint *)(param_1 + 0x1c) = *(uint *)(param_1 + 0x1c) | 0x800;
    
	// this skips $RA backup/restore, faster than JR $RA
	FUN_80071694(param_1);
	
	// erase (instance -> thread)
    *(undefined4 *)(iVar1 + 0x6c) = 0;
  } while( true );
}

// RB_Fruit_ThCollide
void FUN_800b70a8(int param_1,int param_2,undefined4 param_3,int param_4)

{
  short sVar1;
  short sVar2;
  undefined4 uVar3;
  MATRIX *r0;
  int iVar5;
  long *r0_00;
  int iVar6;
  int iVar7;
  int *piVar8;
  undefined *puVar9;
  undefined auStack40 [16];
  undefined2 uStack24;
  undefined2 uStack22;
  undefined2 uStack20;
  
  puVar9 = auStack40;
  piVar8 = *(int **)(param_1 + 0x30);
  sVar1 = *(short *)(param_4 + 0xc);
  iVar7 = *(int *)(param_1 + 0x34);
  
  if ((sVar1 == 0x18) || (uVar3 = 0, sVar1 == 0x3f)) 
  {
    iVar6 = *(int *)(param_2 + 0x30);
    if (sVar1 == 0x18) {
      
	  // position 3D
	  uStack24 = *(undefined2 *)(iVar7 + 0x44);
      uStack22 = *(undefined2 *)(iVar7 + 0x48);
      uStack20 = *(undefined2 *)(iVar7 + 0x4c);
      
	  // pushBuffer -> 0x28 (matrix)
	  r0 = (MATRIX *)(PTR_DAT_8008d2ac + (uint)*(byte *)(iVar6 + 0x4a) * 0x110 + 400);
      gte_SetRotMatrix(r0);
      gte_SetTransMatrix(r0);
	  
	  // position 3D
      gte_ldv0(&uStack24);
      gte_rtps();
	  
	  // screen 2D result
      gte_stsxy(r0_00);
	  
	  // gGT
      iVar5 = PTR_DAT_8008d2ac;
      
	  // screenX
	  *(short *)(iVar6 + 0x4bc) =
           *(short *)(puVar9 + 0x18) +
           *(short *)(iVar5 + (uint)*(byte *)(iVar6 + 0x4a) * 0x110 + 0x184);
      
	  // screenY
	  sVar1 = *(short *)((int)r0_00 + 2);
      sVar2 = *(short *)(iVar5 + (uint)*(byte *)(iVar6 + 0x4a) * 0x110 + 0x186);
      
	  // frames
	  *(undefined4 *)(iVar6 + 0x4b8) = 5;
	  
	  // remaining HUD elements
      *(int *)(iVar6 + 0x4c0) = *(int *)(iVar6 + 0x4c0) + 1;
	  
	  // screenY
      *(short *)(iVar6 + 0x4be) = sVar1 + sVar2 + -0x14;
    }
	
    *piVar8 = iVar6;
	
	// set scale to 0,0,0
    *(undefined2 *)(iVar7 + 0x1c) = 0;
    *(undefined2 *)(iVar7 + 0x1e) = 0;
    *(undefined2 *)(iVar7 + 0x20) = 0;
	
	// erase instance->thread
    *(undefined4 *)(iVar7 + 0x6c) = 0;
	
	// play sound
    FUN_8002f0dc(0x43,iVar7);
    
	// return 1
	uVar3 = 1;
	
	// kill thread
    *(uint *)(param_1 + 0x1c) = *(uint *)(param_1 + 0x1c) | 0x800;
  }
  return uVar3;
}

// RB_Fruit_LInB
void FUN_800b722c(int param_1)
{
  // RB_Default_LInB
  FUN_800b4fe4(param_1);
  
  *(undefined *)(param_1 + 0x52) = 0;
  *(uint *)(param_1 + 0x28) = *(uint *)(param_1 + 0x28) | 0x10;
  return;
}

// RB_Fruit_LInC
// spawns for one frame then destroys
undefined4 FUN_800b7260(int param_1,undefined4 param_2,undefined4 param_3)
{
  undefined4 uVar1;
  code *pcVar2;
  int iVar3;
  
  // Get thread for this instance
  iVar3 = *(int *)(param_1 + 0x6c);
  
  // if there is no thread
  if (iVar3 == 0) 
  {
	// PROC_BirthWithObject
	// 0x4 = size
	// 0 = no relation to param4
	// 0x300 = SmallStackPool
	// 0x3 = "static" thread bucket
    iVar3 = FUN_8004205c(0x40303,&FUN_800b706c,s_fruit_800b7064,0);
	
	// give thread to instance
    *(int *)(param_1 + 0x6c) = iVar3;
	
	// if thread failed
    if (iVar3 == 0) 
	{
	  // quit
      return 0;
    }
	
	// give instance to thread
    *(int *)(iVar3 + 0x34) = param_1;
	
	// set funcThCollide
    *(undefined4 *)(iVar3 + 0x28) = 0x800b70a8;
	
	// set back to thread
    iVar3 = *(int *)(param_1 + 0x6c);
  }
  
  uVar1 = 0;
  
  if (
		// if thread is valid
		(iVar3 != 0) && 
		(
			// get funcThCollide
			pcVar2 = *(code **)(iVar3 + 0x28), 
			
			// if it is a function
			pcVar2 != (code *)0x0
		)
	  ) 
  {
	// if scale is zero, and object is not drawn
    if (*(short *)(param_1 + 0x1c) == 0) 
	{
	  // do nothing
      uVar1 = 0;
    }
	
	// if object is drawn
    else 
	{
	  // execute function pointer
      uVar1 = (*pcVar2)(iVar3,param_2,pcVar2,param_3);
    }
  }
  return uVar1;
}

// RB_Minecart_ThTick
void FUN_800b7338(int param_1)
{
  ushort uVar1;
  undefined *puVar2;
  short sVar3;
  int iVar4;
  int iVar5;
  undefined4 uVar6;
  short *psVar7;
  int iVar8;
  
  // thread -> instance
  iVar8 = *(int *)(param_1 + 0x34);
  
  // thread -> object
  psVar7 = *(short **)(param_1 + 0x30);
  
  // instance -> animFrame
  sVar3 = *(short *)(iVar8 + 0x54);
  
  // INSTANCE_GetNumAnimFrames
  iVar4 = FUN_80030f58(iVar8,0);
  
  // if animation is not over
  if ((int)sVar3 + 1 < iVar4) 
  {
	// increment animation frame
    *(short *)(iVar8 + 0x54) = *(short *)(iVar8 + 0x54) + 1;
  }
  
  // if animation is over
  else 
  {
	// restart animation
    *(undefined2 *)(iVar8 + 0x54) = 0;
  }
  
  puVar2 = PTR_DAT_8008d2ac;
  
  // LEV -> numSpawn2
  if (*(int *)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0x138) != 0) 
  {
	// if not reached next point
    if (psVar7[3] < psVar7[0xf]) 
	{
	  // increment interpolation to next point
      psVar7[3] = psVar7[3] + 1;
    }
	
	// if reached next point
    else 
	{
	  // reset interpolation between points
      psVar7[3] = 1;
	  
	  // position index < num positions (LEV -> ptrSpawn2)
      if ((int)psVar7[10] + 1 < **(int **)(*(int *)(puVar2 + 0x160) + 0x13c)) {
        
		// increment position index
		psVar7[10] = psVar7[10] + 1;
		
		// pos1 = pos2
        *psVar7 = psVar7[4];
        psVar7[1] = psVar7[5];
        psVar7[2] = psVar7[6];
      }
      else 
	  {
		// back to first position
        psVar7[10] = 1;
        
		// Get spawn posX in LEV
		sVar3 = **(short **)(*(int *)(*(int *)(puVar2 + 0x160) + 0x13c) + 4);
        
		// set posX in Object
		*psVar7 = sVar3;
		
		// set posX in Instance
        *(int *)(iVar8 + 0x44) = (int)sVar3;
		
		// Get spawn posY in LEV
        sVar3 = *(short *)(*(int *)(*(int *)(*(int *)(puVar2 + 0x160) + 0x13c) + 4) + 2);
		
		// set posY in Object
        psVar7[1] = sVar3;
		
		// set posZ in Instance
        *(int *)(iVar8 + 0x48) = (int)sVar3;
		
		// Get spawn posZ in LEV
        sVar3 = *(short *)(*(int *)(*(int *)(*(int *)(puVar2 + 0x160) + 0x13c) + 4) + 4);
		
		// set posZ in Object
        psVar7[2] = sVar3;
		
		// set posZ in Instance
        *(int *)(iVar8 + 0x4c) = (int)sVar3;
      }
      
	  puVar2 = PTR_DAT_8008d2ac;
	  
	  // index
      iVar4 = (int)psVar7[10];
      
	  // position
	  psVar7[4] = *(short *)(iVar4 * 6 +
                            *(int *)(*(int *)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0x13c) + 4));
      psVar7[5] = *(short *)(iVar4 * 6 + *(int *)(*(int *)(*(int *)(puVar2 + 0x160) + 0x13c) + 4) +
                            2);
      uVar1 = *(ushort *)(iVar4 * 6 + *(int *)(*(int *)(*(int *)(puVar2 + 0x160) + 0x13c) + 4) + 4);
      psVar7[7] = *psVar7 - psVar7[4];
      psVar7[6] = uVar1;
      iVar5 = (uint)(ushort)psVar7[2] - (uint)uVar1;
      iVar4 = iVar5 * 0x10000 >> 0x10;
      psVar7[9] = (short)iVar5;
      psVar7[8] = psVar7[1] - psVar7[5];
      uVar6 = FUN_8006c618((int)psVar7[7] * (int)psVar7[7] + iVar4 * iVar4);
      
	  // rotation with rtan2
	  sVar3 = FUN_8007173c((int)psVar7[8],uVar6);
      psVar7[0x10] = sVar3;
      sVar3 = FUN_8007173c((int)psVar7[7],(int)psVar7[9]);
      psVar7[0x11] = sVar3 + -0x800;
      
	  if (
			(psVar7[10] == 1) && 
			
			// if instance->model->modelID == DYNAMIC_MINE_CART
			(*(short *)(*(int *)(iVar8 + 0x18) + 0x10) == 0x21)
		) 
	  {
        psVar7[0xc] = psVar7[0x10];
        psVar7[0xd] = psVar7[0x11];
        psVar7[0xe] = psVar7[0x12];
      }
    }
	
	// from array
    *(undefined *)(iVar8 + 0x50) = (&DAT_800b7b20)[(int)psVar7[10] * 2];
    *(undefined *)(iVar8 + 0x51) = (&DAT_800b7b20)[(int)psVar7[10] * 2];
    
	// interpolate points
	iVar4 = (int)psVar7[0xf];
	
	// safety check
    if (iVar4 == 0) trap(0x1c00);
    if ((iVar4 == -1) && ((int)psVar7[3] * (int)psVar7[7] == -0x80000000)) trap(0x1800);
    
	// posX
	*(int *)(iVar8 + 0x44) = (int)*psVar7 - ((int)psVar7[3] * (int)psVar7[7]) / iVar4;
    
	// interpolate points
	iVar4 = (int)psVar7[0xf];

	// safety check
    if (iVar4 == 0) trap(0x1c00);
    if ((iVar4 == -1) && ((int)psVar7[3] * (int)psVar7[7] == -0x80000000)) trap(0x1800);
	
	// posY
    *(int *)(iVar8 + 0x48) = (int)psVar7[1] - ((int)psVar7[3] * (int)psVar7[8]) / iVar4;
	
	// interpolate points
    iVar4 = (int)psVar7[0xf];

	// safety check
    if (iVar4 == 0) trap(0x1c00);
    if ((iVar4 == -1) && ((int)psVar7[3] * (int)psVar7[7] == -0x80000000)) trap(0x1800);
	
	// posZ
    *(int *)(iVar8 + 0x4c) = (int)psVar7[2] - ((int)psVar7[3] * (int)psVar7[9]) / iVar4;
	
	// RB_Hazard_InterpolateValue x2
	// interpolate current rotation to desired rotation
	
    sVar3 = FUN_800ada90((int)psVar7[0xd],(int)psVar7[0x11],(int)psVar7[0x13]);
    psVar7[0xd] = sVar3;
	
    sVar3 = FUN_800ada90((int)psVar7[0xc],(int)psVar7[0x10],(int)psVar7[0x13]);
    psVar7[0xc] = sVar3;
    
	// make matrix
	FUN_8006c2a4(iVar8 + 0x30,psVar7 + 0xc);
	
	// PlaySound3D_Flags
	// play minecart railroad sound
    FUN_8002f31c(psVar7 + 0x14,0x72,iVar8);
	
	// check for collision with all Players
    iVar4 = FUN_800314e0(iVar8,param_1,*(undefined4 *)(PTR_DAT_8008d2ac + 0x1b2c),0x10000);
    
	// if there is collision
	if ((iVar4 != 0) ||
	
		// check for collision with all robotcars
       (iVar4 = FUN_800314e0(iVar8,param_1,*(undefined4 *)(PTR_DAT_8008d2ac + 0x1b40),0x10000),
       
	   // if there is collision
	   iVar4 != 0)) 
	{
	  // squish
      uVar6 = 3;
	  
	  // instance -> model -> modelID == DYNAMIC_SKUNK
      if (*(short *)(*(int *)(iVar8 + 0x18) + 0x10) == 0x50) 
	  {
		// spin out
        uVar6 = 1;
      }
	  
	  // RB_Hazard_HurtDriver (squish, or spinout)
      FUN_800ac1b0(*(undefined4 *)(*(int *)(iVar4 + 0x6c) + 0x30),uVar6,0,0);
    }
  }
  return;
}

// RB_Minecart_LInB
void FUN_800b7814(int param_1)
{
  undefined *puVar1;
  undefined2 uVar2;
  short sVar3;
  int iVar4;
  undefined4 uVar5;
  short *psVar6;
  
  // if there is already a thread for this instance
  if (*(int *)(param_1 + 0x6c) != 0) 
  {
	// quit
    return;
  }
  
  // PROC_BirthWithObject
  // 0x2c = size
  // 0 = no relation to param4
  // 0x300 = SmallStackPool
  // 0x3 = "static" thread bucket
  iVar4 = FUN_8004205c(0x2c0303,&FUN_800b7338,s_minecart_800b732c,0);
  
  // give thread to instance
  *(int *)(param_1 + 0x6c) = iVar4;
  
  // if thread failed
  if (iVar4 == 0) 
  {
	// quit
    return;
  }
  
  // get object that thread created
  psVar6 = *(short **)(iVar4 + 0x30);
  
  // give instance to thread
  *(int *)(iVar4 + 0x34) = param_1;
  
  // clear memory in object
  memset(psVar6,0,0x2c);
  
  // minecartID
  iVar4 = strlen(param_1 + 8);
  
  // start at beginning of path
  sVar3 = 1;
  
  // not minecart[0]
  if (*(char *)(iVar4 + param_1 + 7) != '0') 
  {
    iVar4 = strlen(param_1 + 8);
    
	// minecart[1]
	if (*(char *)(iVar4 + param_1 + 7) == '1') {
      iVar4 = **(int **)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0x13c);
    }
	
	// minecart[2]
    else {
      iVar4 = **(int **)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0x13c) << 1;
    }
	
    sVar3 = (short)(iVar4 / 3);
  }
  
  // position index
  psVar6[10] = sVar3;
  
  // set scale (x,y,z) of instance
  *(undefined2 *)(param_1 + 0x1c) = 0x1000;
  *(undefined2 *)(param_1 + 0x1e) = 0x1000;
  *(undefined2 *)(param_1 + 0x20) = 0x1000;
  
  // minecart speed (8 frames between points)
  psVar6[0xf] = 8;
  
  // rotation speed
  psVar6[0x13] = 0x20;
  
  // instance -> model -> modelID
  sVar3 = *(short *)(*(int *)(param_1 + 0x18) + 0x10);
  
  // if DYNAMIC_SKUNK
  if (sVar3 == 0x50) {
    uVar2 = 0x2000;
  }
  else 
  {
	// if not DYNAMIC_VONLABASS
    if (sVar3 != 0x4f) goto LAB_800b7980;
	
	// if DYNAMIC_VONLABASS
    uVar2 = 0x800;
  }
  
  // set scale again (x,y,z) of instance
  *(undefined2 *)(param_1 + 0x1c) = uVar2;
  *(undefined2 *)(param_1 + 0x1e) = uVar2;
  *(undefined2 *)(param_1 + 0x20) = uVar2;
  
  // speed (4 frames between points)
  psVar6[0xf] = 4;
  
  // rotation speed
  psVar6[0x13] = 0x18;
  
LAB_800b7980:
  puVar1 = PTR_DAT_8008d2ac;
  
  // desired position index
  iVar4 = (int)psVar6[10];
  
  // betweenPoints currFrame
  psVar6[3] = 0;
  
  // pos1 = points[desired-1]
  *psVar6 = *(short *)(iVar4 * 6 + *(int *)(*(int *)(*(int *)(puVar1 + 0x160) + 0x13c) + 4) + -6);
  psVar6[1] = *(short *)(iVar4 * 6 + *(int *)(*(int *)(*(int *)(puVar1 + 0x160) + 0x13c) + 4) + -4);
  psVar6[2] = *(short *)(iVar4 * 6 + *(int *)(*(int *)(*(int *)(puVar1 + 0x160) + 0x13c) + 4) + -2);
  
  // pos2 = points[desired]
  psVar6[4] = *(short *)(iVar4 * 6 + *(int *)(*(int *)(*(int *)(puVar1 + 0x160) + 0x13c) + 4));
  psVar6[5] = *(short *)(iVar4 * 6 + *(int *)(*(int *)(*(int *)(puVar1 + 0x160) + 0x13c) + 4) + 2);
  psVar6[6] = *(short *)(iVar4 * 6 + *(int *)(*(int *)(*(int *)(puVar1 + 0x160) + 0x13c) + 4) + 4);
  
  // dirX
  psVar6[7] = *psVar6 - psVar6[4];
  
  // dirZ
  iVar4 = (int)(((uint)(ushort)psVar6[2] - (uint)(ushort)psVar6[6]) * 0x10000) >> 0x10;
  psVar6[9] = (short)((uint)(ushort)psVar6[2] - (uint)(ushort)psVar6[6]);
  
  // dirY
  psVar6[8] = psVar6[1] - psVar6[5];
  
  uVar5 = SquareRoot0((int)psVar6[7] * (int)psVar6[7] + iVar4 * iVar4);
  
  // rotate X, Y, Z
  sVar3 = ratan2((int)psVar6[8],uVar5);
  psVar6[0x10] = sVar3;
  sVar3 = ratan2((int)psVar6[7],(int)psVar6[9]);
  psVar6[0x11] = sVar3 + -0x800;
  psVar6[0x12] = 0;
  
  // erase audio data
  *(undefined4 *)(psVar6 + 0x14) = 0;
  
  return;
}

// RB_Orca_ThTick
void FUN_800b7b8c(int param_1)
{
  ushort uVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  short *psVar6;
  int iVar7;
  int iVar8;
  
  // thread -> object
  psVar6 = *(short **)(param_1 + 0x30);
  
  // thread -> instance
  iVar7 = *(int *)(param_1 + 0x34);
  
  // if cooldown
  if ((int)psVar6[7] != 0) 
  {
	// subtract one frame
    uVar2 = (int)psVar6[7] - 1;
    psVar6[7] = (short)uVar2;
    
	// quit if cooldown is not done
	if ((uVar2 & 0xffff) != 0) {
      return;
    }
	
	// make orca visible (remove invisible flag)
    *(uint *)(iVar7 + 0x28) = *(uint *)(iVar7 + 0x28) & 0xffffff7f;
    
	return;
  }
  
  // number of frames in animation
  iVar3 = (int)psVar6[0x13];
  
  // animIndex
  iVar8 = (int)psVar6[0xb];
  
  // if less than 20 frames remain
  if (iVar3 + -0x14 < (int)psVar6[0xb]) 
  {
	// total frames, minus 20
    iVar8 = iVar3 + -0x14;
  }
  
  // direction
  uVar1 = psVar6[0x17];
  
  // total frames, minus 23
  iVar5 = iVar3 + -0x17;
  
  if (uVar1 == 0) 
  {
	// subtract 26 frames
    iVar3 = iVar3 + -0x1a;
    
	if ((short)iVar8 <= iVar3) goto LAB_800b7c40;
  }
  
  else 
  {
    iVar3 = iVar8 + -3;
  }
  
  iVar8 = iVar3;
LAB_800b7c40:
  iVar3 = iVar8 << 0x10;
  if (iVar8 << 0x10 < 0) {
    iVar3 = 0;
  }
  iVar3 = iVar3 >> 0x10;
  if (iVar5 == 0) {
    trap(0x1c00);
  }
  if ((iVar5 == -1) && (iVar3 * psVar6[0x14] == -0x80000000)) {
    trap(0x1800);
  }
  *(int *)(iVar7 + 0x44) = (int)*psVar6 - (iVar3 * psVar6[0x14]) / iVar5;
  if (iVar5 == 0) {
    trap(0x1c00);
  }
  if ((iVar5 == -1) && (iVar3 * psVar6[0x15] == -0x80000000)) {
    trap(0x1800);
  }
  *(int *)(iVar7 + 0x48) = (int)psVar6[1] - (iVar3 * psVar6[0x15]) / iVar5;
  if (iVar5 == 0) {
    trap(0x1c00);
  }
  if ((iVar5 == -1) && (iVar3 * psVar6[0x16] == -0x80000000)) {
    trap(0x1800);
  }
  *(int *)(iVar7 + 0x4c) = (int)psVar6[2] - (iVar3 * psVar6[0x16]) / iVar5;
  
  // increment frame
  iVar8 = (int)*(short *)(iVar7 + 0x54) + 1;
  
  // if frame is less than number of frames in animation
  if (iVar8 < psVar6[0x13]) 
  {
    if (
			// if less than 2 players (1P only)
			((byte)PTR_DAT_8008d2ac[0x1ca8] < 2) && 
			
			// create splashes on specific frames
			(
				(
					// 45 frames between entry and exit,
					// 1.5 seconds

					// frame 5, coming out of the water
					iVar8 == 5 || 
					
					// frame 49, back in water
					(iVar8 == 0x31)
				)
			)
		) 
	{
	  // amount of particles to spawn
      iVar3 = 0xf;
      
	  // splash effect in water
	  do 
	  {
		// Create instance in particle pool
        iVar5 = FUN_80040308(0,*(undefined4 *)(PTR_DAT_8008d2ac + 0x2118),&DAT_800b80e4);
        
		if (iVar5 != 0) {
          *(int *)(iVar5 + 0x24) =
               *(int *)(iVar5 + 0x24) +
               *(int *)(iVar7 + 0x44) * 0x100 + (int)*(short *)(iVar5 + 0x28) * 0x10;
          *(int *)(iVar5 + 0x2c) =
               *(int *)(iVar5 + 0x2c) +
               *(int *)(iVar7 + 0x48) * 0x100 + (int)*(short *)(iVar5 + 0x30) * 2;
          iVar4 = *(int *)(iVar7 + 0x4c);
          *(undefined2 *)(iVar5 + 0x1a) = 0x1000;
          *(int *)(iVar5 + 0x34) =
               *(int *)(iVar5 + 0x34) + iVar4 * 0x100 + (int)*(short *)(iVar5 + 0x38) * 0x10;
        }
        iVar3 = iVar3 + -1;
      } while (iVar3 != 0);
    }
	
	// increment frame
    *(undefined2 *)(iVar7 + 0x54) = (short)iVar8;
    
	// direction
	if (uVar1 == 0) 
	{
	  // return to spawn
      psVar6[0xb] = psVar6[0xb] + -1;
    }
	
	// direction
    else 
	{
	  // move away from spawn
      psVar6[0xb] = psVar6[0xb] + 1;
    }
  }
  
  // if animation is done
  else 
  {
	// make orca invisible
    *(uint *)(iVar7 + 0x28) = *(uint *)(iVar7 + 0x28) | 0x80;
	
	// 90-frame cooldown before 
	// jumping out of water
    psVar6[7] = 0x5a;
    
	// reset animation
	*(undefined2 *)(iVar7 + 0x54) = 0;
	
	// reverse the direction
    psVar6[0x17] = uVar1 ^ 1;
	
	// alter rotation 180 degrees
    psVar6[9] = psVar6[9] + 0x800;
	
	// turn rotation into matrix
    FUN_8006c2a4(iVar7 + 0x30,psVar6 + 8);
  }
  return;
}

// RB_Orca_ThCollide
void FUN_800b7eb8(int param1, int param_2, int param_3, int param_4)
{ 
  // check if modelID is player
  // modelID is 0xc of BSP meta
  
  return (uint)(*(short *)(param_4 + 0xc) == 0x18);
}

// RB_Orca_LInB
// This was the beta Whale on Polar Pass
void FUN_800b7ecc(int param_1)
{
  undefined *puVar1;
  undefined *puVar2;
  short sVar3;
  int iVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  
  // orca would be out of water for 45 frames,
  // which is 1.5 seconds, and then a 3-second cooldown
  
  // If there is no thread for this instance
  if (*(int *)(param_1 + 0x6c) == 0) 
  {
	// b7b84
	// "orca"
	// PROC_BirthWithObject
	// 0x30 = size
	// 0 = no relation to param4
	// 0x300 = SmallStackPool
    // 0x3 = "static" thread bucket
	iVar4 = FUN_8004205c(0x300303,&FUN_800b7b8c,&DAT_800b7b84,0);
	
	// give thread to instance
    *(int *)(param_1 + 0x6c) = iVar4;
	
	// If the thread built properly
    if (iVar4 != 0) 
	{
	  // get object created with thread
      puVar6 = *(undefined4 **)(iVar4 + 0x30);
	  
	  // set funcThCollide, RB_Orca_ThCollide
      *(undefined4 *)(iVar4 + 0x28) = 0x800b7eb8;
	  
	  // give instance to thread
      *(int *)(iVar4 + 0x34) = param_1;
	  
	  // set scale (x, y, z)
      *(undefined2 *)(param_1 + 0x1c) = 0xc00;
      *(undefined2 *)(param_1 + 0x1e) = 0xc00;
      *(undefined2 *)(param_1 + 0x20) = 0xc00;
	  
	  // draw huge
      *(uint *)(param_1 + 0x28) = *(uint *)(param_1 + 0x28) | 0x8000000;
	  
	  // animFrame (negative?)
      *(short *)((int)puVar6 + 0x16) = -10;
      
	  // direction, move away from spawn
	  *(short *)((int)puVar6 + 0x2e) = 1;
	  
	  // instance->instDef->rot[3]
      *(short *)(puVar6 + 4) = *(short *)(*(int *)(param_1 + 0x2c) + 0x36);
      *(short *)((int)puVar6 + 0x12) = *(short *)(*(int *)(param_1 + 0x2c) + 0x38);
      *(short *)(puVar6 + 5) = *(short *)(*(int *)(param_1 + 0x2c) + 0x3a);
      
	  // orcaID
	  iVar4 = strlen(param_1 + 8);
      puVar1 = PTR_DAT_8008d2ac;
      iVar4 = (uint)*(byte *)(iVar4 + param_1 + 7) - 0x30;
      *(short *)((int)puVar6 + 6) = (short)iVar4;
      
	  puVar2 = PTR_DAT_8008d2ac;
	  
	  // LEV -> numSpawn2
      if (*(int *)(*(int *)(puVar1 + 0x160) + 0x138) != 0) 
	  {
		// start position
        puVar5 = *(undefined4 **)(iVar4 * 8 + *(int *)(*(int *)(puVar1 + 0x160) + 0x13c) + 0x24);
        sVar3 = *(short *)(puVar5 + 1);
        *puVar6 = *puVar5;
        *(short *)(puVar6 + 1) = sVar3;
        
		// end position
		iVar4 = *(int *)((int)*(short *)((int)puVar6 + 6) * 8 +
                         *(int *)(*(int *)(puVar2 + 0x160) + 0x13c) + 0x24);
        sVar3 = *(short *)(iVar4 + 10);
        puVar6[2] = *(undefined4 *)(iVar4 + 6);
        *(short *)(puVar6 + 3) = sVar3;
      }
	  
	  // midpoint?
      *(short *)(puVar6 + 0xa) = *(short *)puVar6 - *(short *)(puVar6 + 2);
      *(short *)((int)puVar6 + 0x2a) = *(short *)((int)puVar6 + 2) - *(short *)((int)puVar6 + 10);
      *(short *)(puVar6 + 0xb) = *(short *)(puVar6 + 1) - *(short *)(puVar6 + 3);
	  
	  // INSTANCE_GetNumAnimFrames
      sVar3 = FUN_80030f58(param_1,0);
	  
      puVar1 = PTR_DAT_8008d2ac;
	  
	  // set number of frames in animation
      *(short *)((int)puVar6 + 0x26) = sVar3;
	  
      if (
			// LEV -> ptrSpawn1 -> numPointers
			(0 < **(int **)(*(int *)(puVar1 + 0x160) + 0x134)) &&
			
			// get data depending on orcaID
			(sVar3 = *(short *)((*(int **)(*(int *)(puVar1 + 0x160) + 0x134))[2] +
                            (int)*(short *)((int)puVar6 + 6) * 2),
			
			// if value is not zero, make invisible
			*(short *)((int)puVar6 + 0xe) = sVar3, sVar3 != 0)
		 ) 
	  {
		// make invisible
        *(uint *)(param_1 + 0x28) = *(uint *)(param_1 + 0x28) | 0x80;
      }
    }
  }
  return;
}

// RB_Plant_ThTick_Eat
void FUN_800b81e8(int param_1)
{
  char cVar1;
  short sVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  short *psVar7;
  
  // get object from thread
  psVar7 = *(short **)(param_1 + 0x30);
  
  // get instance from thread
  iVar6 = *(int *)(param_1 + 0x34);
  
  do 
  {
	// get animation
    cVar1 = *(char *)(iVar6 + 0x52);
    
	// if animation is 5
	if (cVar1 == '\x05') 
	{
	  // get animation frame
      sVar2 = *(short *)(iVar6 + 0x54);
	  
	  // INSTANCE_GetNumAnimFrames
      iVar3 = FUN_80030f58(iVar6,5);
      
	  // if animation is not finished
	  if ((int)sVar2 + 1 < iVar3) 
	  {
		// increment animation frame
        *(short *)(iVar6 + 0x54) = *(short *)(iVar6 + 0x54) + 1;
      }
	  
	  // if animation is finished
      else 
	  {
		// reset frame
        *(undefined2 *)(iVar6 + 0x54) = 0;
		
		// change animation to 6
        *(undefined *)(iVar6 + 0x52) = 6;
DAT_800b82bc:
        if (psVar7[3] != 0) 
		{
		  // Play PlantChew sound
          FUN_80028468(0x6e,0);
        }
      }
    }
	
	// if animation is not 5
    else {
      if (cVar1 == '\x06') 
	  {
		// get animation frame
        sVar2 = *(short *)(iVar6 + 0x54);
		
		// INSTANCE_GetNumAnimFrames
        iVar3 = FUN_80030f58(iVar6,6);
		
		// if animation is not done
        if ((int)sVar2 + 1 < iVar3) 
		{
		  // advance animation by one frame
          sVar2 = *(short *)(iVar6 + 0x54) + 1;
          *(short *)(iVar6 + 0x54) = sVar2;
		  
		  // on a particular frame, play sound???
          if (sVar2 == 0xf) goto DAT_800b82bc;
        }
		
		// if animation is done
        else 
		{
		  // reset animation frame
          *(undefined2 *)(iVar6 + 0x54) = 0;
		  
		  // increment number of times animation finished
          sVar2 = *psVar7;
          *psVar7 = sVar2 + 1;
		  
		  // if animation finished once
          if ((short)(sVar2 + 1) == 1) 
		  {
			// reset counter
            *psVar7 = 0;
			
			// reset animation
            *(undefined2 *)(iVar6 + 0x54) = 0;
			
			// change animation to 7
            *(undefined *)(iVar6 + 0x52) = 7;
          }
        }
      }
	  
	  // if anim is not 6
      else 
	  {
		// if animation is 7, spitting
        if (cVar1 == '\a') 
		{
		  // get animation frame
          sVar2 = *(short *)(iVar6 + 0x54);
		  
		  // INSTANCE_GetNumAnimFrames
          iVar3 = FUN_80030f58(iVar6,7);
          
		  // if animation is not finished
		  if ((int)sVar2 + 1 < iVar3) 
		  {
			// increase animation frame
            sVar2 = *(short *)(iVar6 + 0x54) + 1;
            *(short *)(iVar6 + 0x54) = sVar2;
			
			// on particular animation frame,
			// make the plant spit
            if (sVar2 == 0x19) 
			{
              if (psVar7[3] != 0) 
			  {
				// Play PlantSpit sound
                FUN_80028468(0x6f,0);
              }
              
			  // loop counter
			  iVar3 = 0;
			  
			  // Spawn 4 tires being spat out
			  // for iVar3 = 0; iVar3 < 4; iVar3++
              do 
			  {
				// 2114 is group of textures for tireAnim
                iVar4 = FUN_80040308(0,*(undefined4 *)(PTR_DAT_8008d2ac + 0x2114),
                                     &DAT_800b8acc);
                if (iVar4 != 0) {
                  
				  *(int *)(iVar4 + 0x24) =
                       *(int *)(iVar4 + 0x24) +
                       (*(int *)(iVar6 + 0x44) + ((int)*(short *)(iVar6 + 0x34) * 9 >> 7)) * 0x100;
                  
				  *(int *)(iVar4 + 0x2c) =
                       *(int *)(iVar4 + 0x2c) + (*(int *)(iVar6 + 0x48) + 0x20) * 0x100;
                  
				  *(int *)(iVar4 + 0x34) =
                       *(int *)(iVar4 + 0x34) +
                       (*(int *)(iVar6 + 0x4c) + ((int)*(short *)(iVar6 + 0x40) * 9 >> 7)) * 0x100;
                  
				  iVar5 = FUN_8003ea28();
                  
				  *(short *)(iVar4 + 0x28) =
                       *(short *)(iVar4 + 0x28) +
                       (short)((iVar5 % 10 + 0x10) * (int)*(short *)(iVar6 + 0x34) >> 0xc) * 0x100;
                  
				  iVar5 = FUN_8003ea28();
                  sVar2 = *(short *)(iVar6 + 0x40);
				  
				  // Particle_FuncPtr_SpitTire
                  *(undefined4 *)(iVar4 + 0x1c) = 0x8003ec18;
                  
				  *(int *)(iVar4 + 0x20) = iVar6;
                  
				  *(short *)(iVar4 + 0x38) =
                       *(short *)(iVar4 + 0x38) +
                       (short)((iVar5 % 10 + 0x10) * (int)sVar2 >> 0xc) * 0x100;
                }
                
				// next tire
				iVar3 = iVar3 + 1;
				
              } while (iVar3 < 4);
            }
          }
		  
		  // if spitting animation is done
          else {
            
			// Change animatino to rest, and reset animation
			*(undefined2 *)(iVar6 + 0x54) = 0;
            *(undefined *)(iVar6 + 0x52) = 0;
			
			// not eating anymore
            psVar7[3] = 0;
			
			// Change state to
			// RB_Plant_ThTick_Rest
            FUN_800716ec(param_1,&FUN_800b88a8);
          }
        }
      }
    }
    
	// this skips $RA backup/restore, faster than JR $RA
	FUN_80071694(param_1);
	
  } while( true );
}

// RB_Plant_ThTick_Grab
void FUN_800b84f0(int param_1)
{
  short sVar1;
  int iVar2;
  undefined *puVar3;
  int iVar4;
  int iStack56;
  int iStack52;
  undefined4 uStack48;
  undefined4 uStack44;
  undefined4 uStack40;
  undefined4 uStack36;
  undefined4 uStack32;
  int iStack28;
  undefined4 uStack24;
  undefined4 uStack20;
  
  // thread -> instance
  iVar4 = *(int *)(param_1 + 0x34);
  
  uStack44 = DAT_800b8bec;
  uStack40 = DAT_800b8bf0;
  uStack36 = DAT_800b8bf4;
  uStack20 = 0;
  
  // instance
  iStack56 = iVar4;
  
  // thread
  iStack52 = param_1;
  iStack28 = param_1;
  
  do 
  {
	// if grabbing driver
    if (*(char *)(iVar4 + 0x52) == '\x03') {
      
	  // instance -> animFrame
	  sVar1 = *(short *)(iVar4 + 0x54);
      
	  // INSTANCE_GetNumAnimFrames
	  iVar2 = FUN_80030f58(iVar4,3);
	  
      puVar3 = PTR_DAT_8008d2ac;
      if ((int)sVar1 + 1 < iVar2) {
        *(short *)(iVar4 + 0x54) = *(short *)(iVar4 + 0x54) + 1;
        
		// mine thread bucket
		uStack48 = *(undefined4 *)(puVar3 + 0x1b7c);
        
		// get collision with thread bucket
		iVar2 = FUN_800315ac(&iStack56);
        
		// if collision
		if (iVar2 != 0) 
		{
		  // instance->thread
          uStack32 = *(undefined4 *)(iVar2 + 0x6c);
		  
		  // instance->thread->funcThCollide
          uStack24 = *(undefined4 *)(*(int *)(iVar2 + 0x6c) + 0x28);
          
		  // RB_Hazard_ThCollide_Generic_Alt
		  FUN_800ac3f8(&uStack32);
        }
      }
      else 
	  {
		// RB_Plant_ThTick_Eat
        puVar3 = &DAT_800b81e8;
		
        *(undefined2 *)(iVar4 + 0x54) = 0;
        *(undefined *)(iVar4 + 0x52) = 5;
DAT_800b8638:
        FUN_800716ec(param_1,puVar3);
      }
    }
	
	// if grabbing mine (unused)
    else {
      if (*(char *)(iVar4 + 0x52) == '\x04') {
        
		// instance -> animFrame
		sVar1 = *(short *)(iVar4 + 0x54);
        
		// INSTANCE_GetNumAnimFrames
		iVar2 = FUN_80030f58(iVar4,4);
		
        if (iVar2 <= (int)sVar1 + 1) 
		{
		  // Change state to
		  // RB_Plant_ThTick_Rest
          puVar3 = &FUN_800b88a8;
		  
		  // Change animation to Rest, restart animation
          *(undefined2 *)(iVar4 + 0x54) = 0;
		  
		  // Set animation to rest
          *(undefined *)(iVar4 + 0x52) = 0;
		  
          goto DAT_800b8638;
        }
        *(short *)(iVar4 + 0x54) = *(short *)(iVar4 + 0x54) + 1;
      }
    }
    
	// this skips $RA backup/restore, faster than JR $RA
	FUN_80071694(param_1);
	
  } while( true );
}

// RB_Plant_ThTick_Transition_HungryToRest
void FUN_800b8650(int param_1)
{
  int iVar1;
  
  // get instance from thread
  iVar1 = *(int *)(param_1 + 0x34);
  do 
  {
	// If animation finished rewinding
    if ((int)*(short *)(iVar1 + 0x54) + -1 < 1) 
	{
	  // Reset animation
      *(undefined2 *)(iVar1 + 0x54) = 0;
	  
	  // Set animation to rest
      *(undefined *)(iVar1 + 0x52) = 0;
	  
	  // Change state to
	  // RB_Plant_ThTick_Rest
      FUN_800716ec(param_1,&FUN_800b88a8);
    }
	
	// if animation is not done
    else 
	{
	  // play backwards
      *(short *)(iVar1 + 0x54) = *(short *)(iVar1 + 0x54) + -1;
    }
    
	// this skips $RA backup/restore, faster than JR $RA
	FUN_80071694(param_1);
	
  } while( true );
}

// RB_Plant_ThTick_Hungry
// Mouth near ground, ready to eat
void FUN_800b86b4(int param_1)
{
  short sVar1;
  undefined2 uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  short *psVar6;
  int iStack48;
  int iStack44;
  undefined4 uStack40;
  undefined4 uStack36;
  undefined4 uStack32;
  undefined4 uStack28;
  
  psVar6 = *(short **)(param_1 + 0x30);
  iVar5 = *(int *)(param_1 + 0x34);
  uStack36 = DAT_800b8bec;
  uStack32 = DAT_800b8bf0;
  uStack28 = DAT_800b8bf4;
  iStack48 = iVar5;
  iStack44 = param_1;
  do {
    if (*(char *)(iVar5 + 0x52) == '\x02') {
      
	  // get animation frame
	  sVar1 = *(short *)(iVar5 + 0x54);
	  
	  // INSTANCE_GetNumAnimFrames
      iVar3 = FUN_80030f58(iVar5,2);
	  
	  // if animation is not done
      if ((int)sVar1 + 1 < iVar3) 
	  {
		// advance animation by one frame
        *(short *)(iVar5 + 0x54) = *(short *)(iVar5 + 0x54) + 1;
      }
	  
	  // if animation is done
      else 
	  {
		// reset animation
        *(undefined2 *)(iVar5 + 0x54) = 0;
		
		// get number of times animation finished
        sVar1 = *psVar6;
		
		// increment counter by one
        *psVar6 = sVar1 + 1;
		
		// if animation finished 4 times
        if ((short)(sVar1 + 1) == 4)
		{
		  // INSTANCE_GetNumAnimFrames
          uVar2 = FUN_80030f58(iVar5,1);
		  
		  // set animation to the last frame,
		  // the animation will play backwards
          *(undefined2 *)(iVar5 + 0x54) = uVar2;
		  
		  // change animation to TransitionRestToHungry,
		  // which will play backwards
          *(undefined *)(iVar5 + 0x52) = 1;
		  
		  // reset cycle counter
          *psVar6 = 0;
		  
		  // Change state to
		  // RB_Plant_ThTick_Transition_HungryToRest
          FUN_800716ec(param_1,&FUN_800b8650);
        }
      }
	  
	  // Check for collision with human players
      uStack40 = *(undefined4 *)(PTR_DAT_8008d2ac + 0x1b2c);
      iVar3 = FUN_800315ac(&iStack48);
      
	  // if no collision is found
	  if (iVar3 == 0) 
	  {
		// If this is not Boss mode (papu is immune)
        if (-1 < *(int *)PTR_DAT_8008d2ac) 
		{
		  // Check for collision with robot cars
          uStack40 = *(undefined4 *)(PTR_DAT_8008d2ac + 0x1b40);
          iVar3 = FUN_800315ac(&iStack48,5);
		  
		  // if there is a collision
          if (iVar3 != 0) 
		  {
			// RB_Hazard_HurtDriver (mask grab)
            FUN_800ac1b0(*(undefined4 *)(*(int *)(iVar3 + 0x6c) + 0x30),5,0,0);
			
			// driver->plantEatingMe = "this"
            *(int *)(*(int *)(*(int *)(iVar3 + 0x6c) + 0x30) + 0x4a8) = param_1;
            
			// Reset animation
			*(undefined2 *)(iVar5 + 0x54) = 0;
			
			// Change animation to GrabDriver
            *(undefined *)(iVar5 + 0x52) = 3;
			
            *psVar6 = 0;
			
			// Change plant state to EndHunger (grab)
            goto DAT_800b8890;
          }
        }
      }
	  
	  // if player collides with plant
      else 
	  {
		// get pointer to Driver object
        iVar4 = *(int *)(*(int *)(iVar3 + 0x6c) + 0x30);
		
		// RB_Hazard_HurtDriver (mask grab)
        iVar3 = FUN_800ac1b0(iVar4,5,0,0);
		
        if (iVar3 != 0) 
		{
		  // Play PlantGrab sound
          FUN_80028468(0x6d,0);
		  
          *(int *)(iVar4 + 0x4a8) = param_1;
		  
		  // Change animation to GrabDriver
          *(undefined *)(iVar5 + 0x52) = 3;
		  
		  // Reset animation
          *(undefined2 *)(iVar5 + 0x54) = 0;
		  
          *psVar6 = 0;
		  
		  // plant is now eating
          psVar6[3] = 1;
DAT_800b8890:
		  // Change plant state to 
		  // RB_Plant_ThTick_Grab (grab or rest)
          FUN_800716ec(param_1,&FUN_800b84f0);
        }
      }
    }
    
	// this skips $RA backup/restore, faster than JR $RA
	FUN_80071694(param_1);
	
  } while( true );
}

// RB_Plant_ThTick_Rest
// Standing tall, not trying to eat
void FUN_800b88a8(int param_1)
{
  short sVar1;
  int iVar2;
  int iVar3;
  short *psVar4;
  
  // get plant object from thread
  psVar4 = *(short **)(param_1 + 0x30);
  
  // get instance from thread
  iVar3 = *(int *)(param_1 + 0x34);
  
  do 
  {
	// cooldown
    if (psVar4[1] == 0) 
	{
	  // Set animation to rest
      if (*(char *)(iVar3 + 0x52) == '\0') 
	  {
		// Get animation frame
        sVar1 = *(short *)(iVar3 + 0x54);
		
		// INSTANCE_GetNumAnimFrames
        iVar2 = FUN_80030f58(iVar3,0);
		
		// if animation is not finished
        if ((int)sVar1 + 1 < iVar2) 
		{
DAT_800b8968:
		  // Advance animation by one frame
          *(short *)(iVar3 + 0x54) = *(short *)(iVar3 + 0x54) + 1;
        }
		
		// if animation is done
        else 
		{
		  // reset animation
          *(undefined2 *)(iVar3 + 0x54) = 0;
		  
		  // get number of times this animation finished
          sVar1 = *psVar4;
		  
		  // increment number of times animation finished
          *psVar4 = sVar1 + 1;
		  
		  // if animation finished 3 times
          if ((short)(sVar1 + 1) == 3) 
		  {
			// change animation to TransitionRestToHungry
            *(undefined *)(iVar3 + 0x52) = 1;
			
			// reset animation counter
            *psVar4 = 0;
          }
        }
      }
      else 
	  {
		// If animation is TransitionRestToHungry
        if (*(char *)(iVar3 + 0x52) == '\x01') 
		{
		  // get animation frame
          sVar1 = *(short *)(iVar3 + 0x54);
		  
		  // INSTANCE_GetNumAnimFrames
          iVar2 = FUN_80030f58(iVar3,1);
		  
		  // if animation is not done, advance frame
          if ((int)sVar1 + 1 < iVar2) goto DAT_800b8968;
		  
		  // When transition is over, make the plant hungry
		  
		  // Set animation frame to zero
          *(undefined2 *)(iVar3 + 0x54) = 0;
		  
		  // Set animation to Hungry
          *(undefined *)(iVar3 + 0x52) = 2;
		  
		  // Change state to
		  // RB_Plant_ThTick_Hungry
          FUN_800716ec(param_1,&FUN_800b86b4);
        }
      }
    }
    
	// cooldown
	else 
	{
      psVar4[1] = psVar4[1] + -1;
    }
    
	// this skips $RA backup/restore, faster than JR $RA
	FUN_80071694(param_1);
	
  } while( true );
}

// RB_Plant_LInB
void FUN_800b89a4(int param_1)
{
  int iVar1;
  undefined2 *puVar2;
  undefined2 *puVar3;
  
  // if instance has no thread
  if (*(int *)(param_1 + 0x6c) == 0) 
  {
	// PROC_BirthWithObject
	// 0x8 = size
	// 0 = no relation to param4
	// 0x300 = SmallStackPool
	// 0x3 = "static" thread bucket
    iVar1 = FUN_8004205c(0x80303,FUN_800b88a8,s_plant_800b81e0,0);
	
	// give thread to instance
    *(int *)(param_1 + 0x6c) = iVar1;
	
	// if thread is valid
    if (iVar1 != 0) 
	{
	  // get object attached to thread
      puVar3 = *(undefined2 **)(iVar1 + 0x30);
	  
	  // give instance to thread
      *(int *)(iVar1 + 0x34) = param_1;
	  
	  // set scale (x, y, z)
      *(undefined2 *)(param_1 + 0x1c) = 0x2800;
      *(undefined2 *)(param_1 + 0x1e) = 0x2800;
      *(undefined2 *)(param_1 + 0x20) = 0x2800;
	  
	  // initialize plant data
	  
	  // frame timer
      *puVar3 = 0;
	  
	  // not eating
      puVar3[3] = 0;
	  
	  // initialize animation to frame zero of anim zero
      *(undefined2 *)(param_1 + 0x54) = 0;
      *(undefined *)(param_1 + 0x52) = 0;
	  
      DAT_800b8bf0._2_2_ = 0x40;
      DAT_800b8bec._0_2_ = 0xffc0;
      DAT_800b8bec._2_2_ = 0xffc0;
      DAT_800b8bf4._0_2_ = 0x80;
      DAT_800b8bf4._2_2_ = 0x1e0;
      DAT_800b8bf0._0_2_ = 0;
	  
	  // LEV -> ptrSpawn1 -> numPointers
      if (0 < **(int **)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0x134)) 
	  {
		// strlen
        iVar1 = FUN_80077cc8(param_1 + 8);
		
        puVar2 = (undefined2 *)
                 (*(int *)(*(int *)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0x134) + 8) +
                 
				 // plantID from string
				 ((uint)*(byte *)(iVar1 + param_1 + 7) - 0x30) * 4);
        
		// position X and Y
		puVar3[1] = *puVar2;
        puVar3[2] = puVar2[1];
      }
    }
  }
  return;
}

// RB_Seal_ThTick_TurnAround
void FUN_800b8c00(int param_1)
{
  char cVar1;
  short sVar2;
  undefined2 uVar3;
  int iVar4;
  code *pcVar5;
  int iVar6;
  int iVar7;
  
  // thread -> instance
  iVar7 = *(int *)(param_1 + 0x34);
  
  // thread -> object
  iVar6 = *(int *)(param_1 + 0x30);
  
  // instance -> animFrame
  sVar2 = *(short *)(iVar7 + 0x54);
  
  // INSTANCE_GetNumAnimFrames
  iVar4 = FUN_80030f58(iVar7,0);
  
  // if animation is not done
  if ((int)sVar2 + 2 < iVar4) 
  {
	// increment animation
    *(short *)(iVar7 + 0x54) = *(short *)(iVar7 + 0x54) + 2;
  }
  
  // if animation is over
  else 
  {
	// restart animation
    *(undefined2 *)(iVar7 + 0x54) = 0;
	
	// play sound of seal bark
    FUN_8002f0dc(0x77,iVar7);
  }
  
  // if current rotation is desired rotation
  if ((int)*(short *)(iVar6 + 0x12) == (int)*(short *)(iVar6 + 0x22)) 
  {
	// reset numFramesSpinning
    *(undefined2 *)(iVar6 + 0x26) = 0;
	
	// set spawn rotation to desired rotation (why?)
    *(undefined2 *)(iVar6 + 0x18) = *(undefined2 *)(iVar6 + 0x10);
    *(undefined2 *)(iVar6 + 0x1a) = *(undefined2 *)(iVar6 + 0x12);
    *(undefined2 *)(iVar6 + 0x1c) = *(undefined2 *)(iVar6 + 0x14);
    
	// make a matrix
	FUN_8006c2a4(iVar7 + 0x30,iVar6 + 0x10);
	
	// ThTick_SetAndExec RB_Seal_ThTick_Move
    FUN_800716ec(param_1,FUN_800b8e1c);
  }
  
  // if desired rotation is not met yet
  else 
  {
	// RB_Hazard_InterpolateValue x3
	
	// rotCurrY to rotDesiredY
    uVar3 = FUN_800ada90((int)*(short *)(iVar6 + 0x12),(int)*(short *)(iVar6 + 0x22),0x80);
    *(undefined2 *)(iVar6 + 0x12) = uVar3;
    
	// rotCurrX to rotDesiredAltX
	uVar3 = FUN_800ada90((int)*(short *)(iVar6 + 0x10),(int)-*(short *)(iVar6 + 0x18),0x14);
    *(undefined2 *)(iVar6 + 0x10) = uVar3;
    
	// rotCurrZ to rotDesiredAltZ
	uVar3 = FUN_800ada90((int)*(short *)(iVar6 + 0x14),(int)-*(short *)(iVar6 + 0x1c),0x14);
    *(undefined2 *)(iVar6 + 0x14) = uVar3;
    
	// increase numFramesSpinning
	*(short *)(iVar6 + 0x26) = *(short *)(iVar6 + 0x26) + 1;
	
	// make a matrix
    FUN_8006c2a4(iVar7 + 0x30,iVar6 + 0x10);
  }
  
  // check for collision with all players
  iVar4 = FUN_800314e0(iVar7,param_1,*(undefined4 *)(PTR_DAT_8008d2ac + 0x1b2c),0x4000);
  
  // if no collision
  if (iVar4 == 0) 
  {  
	// check for collision with all robotcars
	iVar4 = FUN_800314e0(iVar7,param_1,*(undefined4 *)(PTR_DAT_8008d2ac + 0x1b40),0x4000);
    
	// if no collision
	if (iVar4 == 0) 
	{  
	  // check for collision with all mines (tnts, beakers, etc)
	  iVar4 = FUN_800314e0(iVar7,param_1,*(undefined4 *)(PTR_DAT_8008d2ac + 0x1b7c),0x4000);
      
	  // if there is a collision
	  if (iVar4 != 0) 
	  {
		// instance -> thread -> funcThCollide
        pcVar5 = *(code **)(*(int *)(iVar4 + 0x6c) + 0x28);
		
		// execute funcThCollide
        (*pcVar5)(*(int *)(iVar4 + 0x6c));
      }
    }
	
	// if there is a collision with robotcar
    else 
	{
	  // RB_Hazard_HurtDriver (spin out)
      FUN_800ac1b0(*(undefined4 *)(*(int *)(iVar4 + 0x6c) + 0x30),1,0,0);
    }
  }
  
  // if there is a collision with player
  else {
    iVar6 = *(int *)(*(int *)(iVar4 + 0x6c) + 0x30);
    cVar1 = *(char *)(iVar6 + 0x376);
	
	// RB_Hazard_HurtDriver (spin out)
    iVar4 = FUN_800ac1b0(iVar6,1,0,0);
    
	// if change state worked, and if kart was not
	// already spinning out before this
	if ((iVar4 != 0) && (cVar1 != '\x03')) 
	{
	  // play sound
      FUN_80028494(0x78,1,(uint)*(ushort *)(iVar6 + 0x2ca) & 1);
    }
  }
  return;
}

// RB_Seal_ThTick_Move
void FUN_800b8e1c(int param_1)
{
  char cVar1;
  short sVar2;
  int iVar3;
  code *pcVar4;
  int iVar5;
  short *psVar6;
  int iVar7;
  
  // get instance from thread
  iVar7 = *(int *)(param_1 + 0x34);
  
  // get object from thread
  psVar6 = *(short **)(param_1 + 0x30);
  
  // instance -> animationFrame
  sVar2 = *(short *)(iVar7 + 0x54);
  
  // INSTANCE_GetNumAnimFrames
  iVar3 = FUN_80030f58(iVar7,0);
  
  // if animation is not done
  if ((int)sVar2 + 2 < iVar3) 
  {
	// increase animation frame
    *(short *)(iVar7 + 0x54) = *(short *)(iVar7 + 0x54) + 2;
  }
  
  // if animation is done
  else 
  {
	// restart animation
    *(undefined2 *)(iVar7 + 0x54) = 0;
  }
  
  // Position =
  // SpawnPosition - (Distance*Velocity) >> 5
  // >> 5 is the same as / 0x2d
  *(int *)(iVar7 + 0x44) = (int)*psVar6 - ((int)psVar6[7] * (int)psVar6[0x14]) / 0x2d;
  *(int *)(iVar7 + 0x48) = (int)psVar6[1] - ((int)psVar6[7] * (int)psVar6[0x15]) / 0x2d;
  *(int *)(iVar7 + 0x4c) = (int)psVar6[2] - ((int)psVar6[7] * (int)psVar6[0x16]) / 0x2d;
  
  // If direction is zero
  if (psVar6[0xf] == 0) 
  {
	// if you have not returned to spawn
    if (0 < psVar6[7]) 
	{
	  // reduce frame counter
      psVar6[7] = psVar6[7] + -1;
	  
	  // dont turn around
      goto LAB_800b8fdc;
    }
	
	// if you have not returned to spawn, dont turn around
    if (psVar6[7] != 0) goto LAB_800b8fdc;
	
	// === end of Move state ===
	
	// rotDesiredAlt_Y
    sVar2 = psVar6[9];
	
	// change direction
    psVar6[0xf] = 1;
  }
  
  // if direction is 1
  else 
  {
	// if you have not travelled far from spawn,
	// 0x2d = 45 frames = 1.5 seconds
    if (psVar6[7] < 0x2d) 
	{
	  // keep moving away from spawn
      psVar6[7] = psVar6[7] + 1;
	  
	  // dont turn around
      goto LAB_800b8fdc;
    }
	
	// if you have not reached max distance, dont turn around,
	// 0x2d = 45 frames = 1.5 seconds
    if (psVar6[7] != 0x2d) goto LAB_800b8fdc;
	
	// === end of Move state ===
	
	// rotCurr_Y
    sVar2 = psVar6[9];
	
	// change direction
    psVar6[0xf] = 0;
  }
  
  // === end of Move state ===
  
  // turn around 180 degrees
  iVar5 = (int)sVar2 + 0x800;
  
  iVar3 = iVar5;
  if (iVar5 < 0) {
    iVar3 = (int)sVar2 + 0x17ff;
  }
  
  // 0x22, rotDesired
  psVar6[0x11] = (short)iVar5 + (short)(iVar3 >> 0xc) * -0x1000;
  
  // ThTick_SetAndExec RB_Seal_ThTick_TurnAround
  FUN_800716ec(param_1,&FUN_800b8c00);
  
LAB_800b8fdc:

  // check for collision with all Players
  iVar3 = FUN_800314e0(iVar7,param_1,*(undefined4 *)(PTR_DAT_8008d2ac + 0x1b2c),0x4000);
  
  // if there is no collision
  if (iVar3 == 0) 
  {
	// check for collision with all robotcars
    iVar3 = FUN_800314e0(iVar7,param_1,*(undefined4 *)(PTR_DAT_8008d2ac + 0x1b40),0x4000);
    
	// if there is no collision
	if (iVar3 == 0) {
      
	  // check collision with all Mines (tnt, beaker, etc)
	  iVar3 = FUN_800314e0(iVar7,param_1,*(undefined4 *)(PTR_DAT_8008d2ac + 0x1b7c),0x4000);
      
	  // if there is a collision 
	  if (iVar3 != 0) 
	  {
		// instance -> thread -> funcThCollide
        pcVar4 = *(code **)(*(int *)(iVar3 + 0x6c) + 0x28);
		
		// execute funcThCollide
        (*pcVar4)(*(int *)(iVar3 + 0x6c));
      }
    }
	
	// if there is a collision with robotcar
    else 
	{
	  // RB_Hazard_HurtDriver (spin out)
      FUN_800ac1b0(*(undefined4 *)(*(int *)(iVar3 + 0x6c) + 0x30),1,0,0);
    }
  }
  
  // if there is a collision with Player
  else 
  {
	// instance -> thread -> object
    iVar7 = *(int *)(*(int *)(iVar3 + 0x6c) + 0x30);
	
	// kart -> state
    cVar1 = *(char *)(iVar7 + 0x376);
	
	// RB_Hazard_HurtDriver (spin out)
    iVar3 = FUN_800ac1b0(iVar7,1,0,0);
	
	// if change state worked, and if kart was not
	// already spinning out before this
    if ((iVar3 != 0) && (cVar1 != '\x03')) 
	{
	  // play sound of seal collision
      FUN_80028494(0x78,1,(uint)*(ushort *)(iVar7 + 0x2ca) & 1);
    }
  }
  return;
}

// RB_Seal_ThCollide
void FUN_800b90d8(int param1, int param_2, int param_3, int param_4)
{ 
  // check if modelID is player
  // modelID is 0xc of BSP meta
  
  return (uint)(*(short *)(param_4 + 0xc) == 0x18);
}

// RB_Seal_LInB
void FUN_800b90ec(int param_1)
{
  short sVar1;
  undefined *puVar2;
  undefined *puVar3;
  int iVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  
  // If this instance has no thread
  if (*(int *)(param_1 + 0x6c) == 0) 
  {
	// b8bf8
	// "seal"
	// PROC_BirthWithObject
	// 0x30 = size
	// 0 = no relation to param4
	// 0x300 = SmallStackPool
	// 0x3 = "static" thread bucket
    iVar4 = FUN_8004205c(0x300303,FUN_800b8e1c,&DAT_800b8bf8,0);
	
	// give thread to instance
    *(int *)(param_1 + 0x6c) = iVar4;
	
	// if thread initialized successfully
    if (iVar4 != 0) 
	{
	  // Get object created with thread
      puVar6 = *(undefined4 **)(iVar4 + 0x30);
	  
	  // set funcThCollide
      *(undefined4 *)(iVar4 + 0x28) = 0x800b90d8;
	  
	  // give instance to thread
      *(int *)(iVar4 + 0x34) = param_1;
	  
	  // set scale (x,y,z)
      *(undefined2 *)(param_1 + 0x1c) = 0x2000;
      *(undefined2 *)(param_1 + 0x1e) = 0x2000;
      *(undefined2 *)(param_1 + 0x20) = 0x2000;
	  
	  // no distance from spawn
      *(short *)((int)puVar6 + 0xe) = 0;
	  
	  // direction moves away from spawn
      *(short *)((int)puVar6 + 0x1e) = 1;
	  
      iVar4 = strlen(param_1 + 8);
      puVar2 = PTR_DAT_8008d2ac;
      
	  // character minus '0', ascii index to int index
	  iVar4 = (uint)*(byte *)(iVar4 + param_1 + 7) - 0x30;
	  
	  // sealID
      *(short *)((int)puVar6 + 6) = (short)iVar4;
	  
      puVar3 = PTR_DAT_8008d2ac;
	  
	  // LEV -> numSpawn2
      if (*(int *)(*(int *)(puVar2 + 0x160) + 0x138) != 0) 
	  {
		// use sealID to get spawn position of this seal
        puVar5 = *(undefined4 **)(iVar4 * 8 + *(int *)(*(int *)(puVar2 + 0x160) + 0x13c) + 4);
        sVar1 = *(short *)(puVar5 + 1);
		
		// spawnPosX, spawnPosY
        *puVar6 = *puVar5;
		
		// spawnPosZ
        *(short *)(puVar6 + 1) = sVar1;
		
		// use sealID to get spawnPosY
        iVar4 = *(int *)((int)*(short *)((int)puVar6 + 6) * 8 +
                         *(int *)(*(int *)(puVar3 + 0x160) + 0x13c) + 4);
						 
		// endPosZ
		sVar1 = *(short *)(iVar4 + 10);
		
		// endPosX, endPosY
        puVar6[2] = *(undefined4 *)(iVar4 + 6);
		
		// endPosZ
        *(short *)(puVar6 + 3) = sVar1;
      }
	  
	  // distance between spawnPos and endPos, used for velocity
      *(short *)(puVar6 + 10) = *(short *)puVar6 - *(short *)(puVar6 + 2);
      *(short *)((int)puVar6 + 0x2a) = *(short *)((int)puVar6 + 2) - *(short *)((int)puVar6 + 10);
      *(short *)(puVar6 + 0xb) = *(short *)(puVar6 + 1) - *(short *)(puVar6 + 3);
      
	  // rotCurr (0x10) = instance->instDef->rot
	  *(short *)(puVar6 + 4) = *(short *)(*(int *)(param_1 + 0x2c) + 0x36);
      *(short *)(puVar6 + 5) = *(short *)(*(int *)(param_1 + 0x2c) + 0x3a);
      sVar1 = *(short *)(*(int *)(param_1 + 0x2c) + 0x38);
      *(short *)((int)puVar6 + 0x12) = sVar1;
	  
	  // rotDesiredAlt (0x18)
      *(short *)(puVar6 + 6) = *(short *)(puVar6 + 4);
      *(short *)((int)puVar6 + 0x26) = 0;
      *(short *)((int)puVar6 + 0x1a) = sVar1;
      *(short *)(puVar6 + 7) = *(short *)(puVar6 + 5);
	  
	   // convert 3 rotation shorts into rotation matrix
      FUN_8006c2a4(param_1 + 0x30,puVar6 + 4);
    }
  }
  return;
}

// RB_Snowball_ThTick
void FUN_800b92ac(int param_1)
{
  short sVar1;
  undefined *puVar2;
  int iVar3;
  undefined4 uVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  undefined2 uStack32;
  undefined2 uStack30;
  undefined2 uStack28;
  
  // get object from thread
  iVar6 = *(int *)(param_1 + 0x30);
  
  // get instance from thread
  iVar7 = *(int *)(param_1 + 0x34);
  
  do {
    if (*(int *)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0x140) != 0) 
	{
	  // instance -> model -> modelID
      sVar1 = *(short *)(*(int *)(iVar7 + 0x18) + 0x10);
      
	  // Naughty Dog bug, the boulder has modelID:
	  // TEMP_SNOWBALL (0x22), so the sound never plays,
	  // set 1-byte 800b9304 to 0x22 to hear the sound
	  
	  // DYNAMIC_SNOWBALL
	  if (sVar1 == 0x20) 
	  {
		// snowball roll
        uVar4 = 0x73;
DAT_800b9328:
		// PlaySound3D_Flags
        FUN_8002f31c(iVar6 + 0xc,uVar4,iVar7);
      }
      else 
	  {
		// sewer speedway barrel
        if (sVar1 == 0x4e) 
		{
		  // barrel roll
          uVar4 = 0x74;
          goto DAT_800b9328;
        }
      }
	  
	  // get position index
      iVar5 = (int)*(short *)(iVar6 + 6);
      
	  // if path is complete
	  if ((int)*(short *)(iVar6 + 8) < iVar5) 
	  {
		// go backwards on the path
        iVar5 = (int)*(short *)(iVar6 + 8) * 2 - iVar5;
      }
	  
	  // Convert index to byte index,
	  // 3 ints per position (x, y, z)
      iVar5 = iVar5 * 0xc;
	  
	  // RotX
      uStack32 = *(undefined2 *)
                  (iVar5 + *(int *)((int)*(short *)(iVar6 + 10) * 8 +
                                    *(int *)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0x144) + 4) + 6);
      // RotY
	  uStack30 = *(undefined2 *)
                  (iVar5 + *(int *)((int)*(short *)(iVar6 + 10) * 8 +
                                    *(int *)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0x144) + 4) + 8);
      // RotZ
	  uStack28 = *(undefined2 *)
                  (iVar5 + *(int *)((int)*(short *)(iVar6 + 10) * 8 +
                                    *(int *)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0x144) + 4) + 10);
      
	  // Make rotation matrix
	  FUN_8006c2a4(iVar7 + 0x30,&uStack32);
      
	  puVar2 = PTR_DAT_8008d2ac;
	  
	  // posX
      *(int *)(iVar7 + 0x44) =
           (int)*(short *)(iVar5 + *(int *)((int)*(short *)(iVar6 + 10) * 8 +
                                            *(int *)(*(int *)(puVar2 + 0x160) + 0x144) + 4) + 0);
      // posY
	  *(int *)(iVar7 + 0x48) =
           (int)*(short *)(iVar5 + *(int *)((int)*(short *)(iVar6 + 10) * 8 +
                                            *(int *)(*(int *)(puVar2 + 0x160) + 0x144) + 4) + 2);
      // posZ
	  *(int *)(iVar7 + 0x4c) =
           (int)*(short *)(iVar5 + *(int *)((int)*(short *)(iVar6 + 10) * 8 +
                                            *(int *)(*(int *)(puVar2 + 0x160) + 0x144) + 4) + 4);
	
	  // Check for collision with Human drivers
      iVar5 = FUN_800314e0(iVar7,param_1,*(undefined4 *)(puVar2 + 0x1b2c),0x10000);
      
	  if ((iVar5 != 0) ||
         
		 // Check for collision with AI drivers
		 (iVar5 = FUN_800314e0(iVar7,param_1,*(undefined4 *)(PTR_DAT_8008d2ac + 0x1b40),0x10000),
         
		 iVar5 != 0)) 
	  {
		// RB_Hazard_HurtDriver (squish)
        FUN_800ac1b0(*(undefined4 *)(*(int *)(iVar5 + 0x6c) + 0x30),3,0,0);
      }
    }
    
	// increment position index
	iVar3 = (int)*(short *)(iVar6 + 6) + 1;
    
	// double amount of points on path, which is 
	// number of points in a full cycle
	iVar5 = (int)*(short *)(iVar6 + 8) << 1;
    
	if (iVar5 == 0) {
      trap(0x1c00);
    }
    if ((iVar5 == -1) && (iVar3 == -0x80000000)) {
      trap(0x1800);
    }
	
	// get next position index
    *(undefined2 *)(iVar6 + 6) = (short)(iVar3 % iVar5);
	
	// this skips $RA backup/restore, faster than JR $RA
    FUN_80071694(param_1);
	
  } while( true );
}

// RB_Snowball_LInB
void FUN_800b950c(int param_1)
{
  short sVar1;
  undefined *puVar2;
  int iVar3;
  undefined2 *puVar4;
  
  if (*(int *)(param_1 + 0x6c) == 0) 
  {
	// PROC_BirthWithObject
	// 0x10 = size
	// 0 = no relation to param4
	// 0x300 = SmallStackPool
	// 0x3 = "static" thread bucket
    iVar3 = FUN_8004205c(0x100303,FUN_800b92ac,s_snowball_800b92a0,0);
    
	// give thread to instance
	*(int *)(param_1 + 0x6c) = iVar3;
	
	// if thread built properly
    if (iVar3 != 0) 
	{
	  // thread -> object
      puVar4 = *(undefined2 **)(iVar3 + 0x30);
	  
	  // give instance to thread
      *(int *)(iVar3 + 0x34) = param_1;
	  
	  // rotX (unused)
      *puVar4 = 0;
	  
	  // probably strlen
      iVar3 = FUN_80077cc8(param_1 + 8);
      
	  // gGT
	  puVar2 = PTR_DAT_8008d2ac;
	  
	  // snowball ID
      iVar3 = (uint)*(byte *)(iVar3 + param_1 + 7) - 0x30;
      puVar4[5] = (short)iVar3;
      
	  // number of points on path
	  puVar4[4] = *(short *)(iVar3 * 8 + *(int *)(*(int *)(puVar2 + 0x160) + 0x144)) + -1;
      
	  // Set scale (x, y, z)
	  *(undefined2 *)(param_1 + 0x1c) = 0x1000;
      *(undefined2 *)(param_1 + 0x1e) = 0x1000;
      *(undefined2 *)(param_1 + 0x20) = 0x1000;
      
	  // rotY (unused)
	  puVar4[1] = *(short *)(param_1 + 0x34) >> 2;
      
	  // rotZ (unused)
	  sVar1 = *(short *)(param_1 + 0x40);
	  
	  // reset point index, beginning of path
      *(undefined4 *)(puVar4 + 6) = 0;
      
	  // rotZ (unused)
	  puVar4[2] = sVar1 >> 2;
    }
  }
  return;
}

// RB_Spider_DrawWebs
// param_1 - threadbucket
// param_2 - ptr first pushBuffer
void FUN_800b95fc(int param_1,int param_2)
{
  short sVar1;
  ushort uVar2;
  int iVar3;
  int iVar4;
  MATRIX *r0;
  uint uVar5;
  uint *puVar6;
  int iVar7;
  uint *puVar8;
  int *piVar9;
  uint *puVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  uint uVar14;
  uint uVar15;
  int iVar16;
  uint uVar17;
  uint uVar18;
  int iVar19;
  
  // if first thread is valid
  if (param_1 != 0) 
  {
    iVar12 = 0;
    puVar10 = &DAT_1f800000;
    piVar9 = &DAT_1f800008;
	
	// all threads
    do 
	{
	  // thread -> instance -> instDef
      iVar3 = *(int *)(*(int *)(param_1 + 0x34) + 0x2c);
      
	  // count number of spiders
      iVar12 = iVar12 + 1;
	  
	  // instDef->posZ
      sVar1 = *(short *)(iVar3 + 0x34);
	  
	  // instDef->posX
      uVar2 = *(ushort *)(iVar3 + 0x30);
	  
	  // thread -> instance -> posY
      iVar4 = *(int *)(*(int *)(param_1 + 0x34) + 0x48);
	  
	  // scratchpad meta data for generating Prims
	  // puVar10 holds instDef->posY + 0x540,
	  // piVar9 holds posX, posY, and posZ
      *puVar10 = (uint)uVar2 | (*(short *)(iVar3 + 0x32) + 0x540) * 0x10000;
	  piVar9[-1] = (uint)uVar2 | (iVar4 + 0x60) * 0x10000;
      *piVar9 = (int)sVar1;
	  
	  // advance in scratchpad
      piVar9 = piVar9 + 3;
	  
	  // thread = thread -> sibling
      param_1 = *(int *)(param_1 + 0x10);
	  
	  // advance in scratchpad
      puVar10 = puVar10 + 3;
	  
    } while (param_1 != 0);
    
	// backBuffer->primMem.curr
	puVar10 = *(uint **)(*(int *)(PTR_DAT_8008d2ac + 0x10) + 0x80);
	
	// if (primMem.curr + (numSpiders * numPlyrCurrGame * 6)) < primMem.endMin100
    if (puVar10 + iVar12 * (uint)(byte)PTR_DAT_8008d2ac[0x1ca8] * 6 <
        *(uint **)(*(int *)(PTR_DAT_8008d2ac + 0x10) + 0x84)) 
	{
	  // loop through all players
      iVar3 = (byte)PTR_DAT_8008d2ac[0x1ca8] - 1;
	  
      iVar4 = 0x1200;
	  
	  // if there are players
      if (-1 < iVar3) 
	  {
        uVar17 = 0xe1000a20;
        
		// 0x40 - LineF2
		uVar15 = 0x42000000;
        
		// LineF2 length (prim header)
		uVar18 = 0x5000000;
		
		// bit mask for writing OT header
        uVar14 = 0xffffff;
		
        iVar11 = 0x1f800000;
		
		// loop through all players
        do 
		{
		  // pushBuffer->0x28 (matrix)
          r0 = (MATRIX *)(param_2 + 0x28);
		  
		  // store on GTE
          gte_SetRotMatrix(r0);
          gte_SetTransMatrix(r0);
		  
		  // loop count,  numSpiders
          iVar13 = iVar12;
		  
		  // scratchpad pointer
          iVar16 = iVar11;
		  
		  // if numSpiders != 0
          if (iVar12 != 0) 
		  {
			// primMem offset 0xC
            puVar8 = puVar10 + 3;
			
			// loop through spiders
            do 
			{
			  // point0
              gte_ldVXY0(iVar11);
              gte_ldVZ0(iVar11 + 8);
			  
			  // point1
              gte_ldVXY1(iVar11 + 4);
              gte_ldVZ1(iVar11 + 8);
              
			  // perspective projection
			  gte_rtpt();
			  
              gte_stsxy01c((long *)(puVar10 + 4));
              
			  // depth of vertex on screen
			  iVar7 = gte_stSZ1();
			  
			  // color (gray)
              uVar5 = 0x3f;
              
			  // if line is close enough to the screen 
			  // to be seen, then generate primitives
			  if (iVar7 - 1U < 0x11ff) 
			  {
                puVar8[-2] = uVar17;
                puVar8[-1] = 0;
                if (0xa00 < iVar7) {
                  iVar19 = (iVar4 - iVar7) * 0x3f;
                  uVar5 = iVar19 >> 0xb;
                  if (iVar19 < 0) {
                    uVar5 = iVar19 + 0x7ff >> 0xb;
                  }
                }
				
				// prim offset 0x4,
				// R,G,B,code(0x42) LINE_F2
                *puVar8 = uVar5 | uVar5 << 8 | uVar5 << 0x10 | uVar15;
				
                iVar7 = iVar7 >> 6;
                if (0x3ff < iVar7) {
                  iVar7 = 0x3ff;
                }
				
				// pushBuffer 0xf4, ptrOT
                puVar6 = (uint *)(*(int *)(param_2 + 0xf4) + iVar7 * 4);
				
                puVar8 = puVar8 + 6;
				
				// prim header, OT and prim len
                *puVar10 = *puVar6 | uVar18;
				
				// ot header = prim address, without top byte
                uVar5 = (uint)puVar10 & uVar14;
				
                puVar10 = puVar10 + 6;
				
				// store OT
                *puVar6 = uVar5;
              }
			  
			  // next spider
              iVar12 = iVar12 + -1;
			  
			  // advance scratchpad
              iVar11 = iVar11 + 0xc;
			  
            } while (iVar12 != 0);
          }
		  
		  // next player
          iVar3 = iVar3 + -1;
		  
		  // next pushBuffer
          param_2 = param_2 + 0x110;
		  
		  // reset spider loop count,
		  // reset scratchpad pointer
          iVar12 = iVar13;
          iVar11 = iVar16;
		  
        } while (-1 < iVar3);
      }
	  
	  // backBuffer->primMem.curr
      *(uint **)(*(int *)(PTR_DAT_8008d2ac + 0x10) + 0x80) = puVar10;
    }
  }
  return;
}

// RB_Spider_ThTick
void FUN_800b9848(int param_1)
{
  char cVar1;
  short sVar2;
  int iVar3;
  code *pcVar4;
  int iVar5;
  short *psVar6;
  
  // get object from thread
  psVar6 = *(short **)(param_1 + 0x30);
  
  // get instance from thread
  iVar5 = *(int *)(param_1 + 0x34);
  
  // delay cycle by varying frames
  if (psVar6[2] != 0) {
    psVar6[2] = psVar6[2] + -1;
    return;
  }
  
  psVar6[4] = psVar6[4] + 1;
  
  // If spider is on ground
  if (psVar6[3] == 0) 
  {
	// if animation finished more than 4 times
    if (4 < *psVar6) 
	{
	  // Play animation backwards
      sVar2 = *(short *)(iVar5 + 0x54) + -1;
	  
	  // if animation is at beginning
      if ((int)*(short *)(iVar5 + 0x54) + -1 < 1) 
	  {
		// reset animation frame
        *(undefined2 *)(iVar5 + 0x54) = 0;
        
		// reset counter
		*psVar6 = 0;
		
		// spider is now at ceiling
        psVar6[3] = 1;
        
		// set animation to WiggleLegsAndTeeth
		goto LAB_800b9a14;
      }
	  
	  // set new animation frame
      *(short *)(iVar5 + 0x54) = sVar2;
	  
	  // last frame of last animation
      if (sVar2 == 0xc) 
	  {
		// play sound: spider move up
        FUN_8002f0dc(0x79,iVar5);
      }
	  
      goto LAB_800b9a1c;
    }
	
	// instance -> animation frame
    sVar2 = *(short *)(iVar5 + 0x54);
	
	// INSTANCE_GetNumAnimFrames
    iVar3 = FUN_80030f58(iVar5);
	
	// if animation is done
    if (iVar3 <= (int)sVar2 + 1) 
	{
	  // restart animation
      *(undefined2 *)(iVar5 + 0x54) = 0;
	  
	  // increment number of times animation finishes
      sVar2 = *psVar6;
      *psVar6 = sVar2 + 1;
	  
	  // if animation finishes 5 times
      if ((short)(sVar2 + 1) == 5) 
	  {
		// set animation to zero
        *(undefined *)(iVar5 + 0x52) = 0;
      
		// INSTANCE_GetNumAnimFrames
		sVar2 = FUN_80030f58(iVar5,0);
		
		// set animation frame to last frame
        *(short *)(iVar5 + 0x54) = sVar2 + -1;
      }
      goto LAB_800b9aa8;
    }
  }
  
  // if spider is near ceiling
  else 
  {
	// if spider animation played more than 4 times
    if (4 < *psVar6) 
	{
	  // instance -> animationFrame
      sVar2 = *(short *)(iVar5 + 0x54);
	  
	  // INSTANCE_GetNumAnimFrames
      iVar3 = FUN_80030f58(iVar5,0);
	  
	  // if animation is not done
      if ((int)sVar2 + 1 < iVar3) 
	  {
		// increment number of frames
        *(short *)(iVar5 + 0x54) = *(short *)(iVar5 + 0x54) + 1;
      }
	  
	  // if animation finished
      else 
	  {
		// reset animation counter
        *psVar6 = 0;
		
		// move spider to ground
        psVar6[3] = 0;
LAB_800b9a14:

		// set animation to WiggleLegsAndTeeth
        *(undefined *)(iVar5 + 0x52) = 1;
      }
LAB_800b9a1c:

	  // set posY, based on InstDef posY
      *(int *)(iVar5 + 0x48) =
           (int)*(short *)(*(int *)(iVar5 + 0x2c) + 0x32) +
           (int)*(short *)(&DAT_800b9da4 + (int)*(short *)(iVar5 + 0x54) * 2);
		   
	  // if animation frame is less than 11
      if ((int)*(short *)(iVar5 + 0x54) < 0xb) 
	  {
		// change spider scaleX and scaleZ based on animation frame
		
		// scaleX
        *(short *)(*(int *)(psVar6 + 6) + 0x1c) =
             (short)(((int)*(short *)(iVar5 + 0x54) << 0xc) / 10) + 0x1800;
        
		// scaleZ
		*(short *)(*(int *)(psVar6 + 6) + 0x20) =
             (short)(((int)*(short *)(iVar5 + 0x54) << 0xc) / 10) + 0x1800;
      }
      goto LAB_800b9aa8;
    }
	
	// get animation frame
    sVar2 = *(short *)(iVar5 + 0x54);
	
	// INSTANCE_GetNumAnimFrames
    iVar3 = FUN_80030f58(iVar5);
	
	// if animation is finished
    if (iVar3 <= (int)sVar2 + 1) 
	{
	  // restart animation to frame zero
      *(undefined2 *)(iVar5 + 0x54) = 0;
	  
	  // increment number of times animation finishes
      sVar2 = *psVar6;
      *psVar6 = sVar2 + 1;
	  
	  // if animation finishes 5 times
      if ((short)(sVar2 + 1) == 5) 
	  {
		// set animation to ChangePosition
        *(undefined *)(iVar5 + 0x52) = 0;
		
		// set animation frame to zero
        *(undefined2 *)(iVar5 + 0x54) = 0;
		
		// play sound: spider move down
        FUN_8002f0dc(0x7a,iVar5);
      }
      goto LAB_800b9aa8;
    }
  }
  
  // increment animation frame
  *(short *)(iVar5 + 0x54) = *(short *)(iVar5 + 0x54) + 1;
  
LAB_800b9aa8:

  // check for collision with all Players
  iVar3 = FUN_800314e0(iVar5,param_1,*(undefined4 *)(PTR_DAT_8008d2ac + 0x1b2c),0x9000);
  
  // if there is no collision
  if (iVar3 == 0) 
  {
	// check for collision with all robot cars
    iVar3 = FUN_800314e0(iVar5,param_1,*(undefined4 *)(PTR_DAT_8008d2ac + 0x1b40),0x9000);
	
	// if there is no collision
    if (iVar3 == 0) 
	{
	  // check for collision with all Mines (tnts, beakers, etc)
      iVar5 = FUN_800314e0(iVar5,param_1,*(undefined4 *)(PTR_DAT_8008d2ac + 0x1b7c),0x9000);
	  
	  // if there is a collision
      if (iVar5 != 0) 
	  {
		// instance -> thread -> funcThCollide
        pcVar4 = *(code **)(*(int *)(iVar5 + 0x6c) + 0x28);
		
		// execute collison pointer
        (*pcVar4)(*(int *)(iVar5 + 0x6c));
      }
    }
	
	// if you collide with robotcar
    else 
	{
	  // RB_Hazard_HurtDriver (spin out)
      FUN_800ac1b0(*(undefined4 *)(*(int *)(iVar3 + 0x6c) + 0x30),1,0,0);
    }
  }
  
  // if you collide with player
  else 
  {
	// instance -> thread -> object
    iVar3 = *(int *)(*(int *)(iVar3 + 0x6c) + 0x30);
	
	// kart state
    cVar1 = *(char *)(iVar3 + 0x376);
	
	// RB_Hazard_HurtDriver (spin out)
    iVar5 = FUN_800ac1b0(iVar3,1,0,0);
    
	if ((iVar5 != 0) && (cVar1 != '\x03')) 
	{
	  // Play sound
      FUN_80028468(0x7b,1);
	  
	  // === Naughty Dog Bug ===
	  // voiceline is already handled in RB_Hazard_HurtDriver,
	  // which calls VehPickState_NewState, which calls Voiceline_RequestPlay.
	  // calling it here makes the driver talk twice
	  
	  // make driver talk
      FUN_8002cbe8(1,(int)(short)(&DAT_80086e84)[*(byte *)(iVar3 + 0x4a)],0x10);
    }
  }
  return;
}

// RB_Spider_ThCollide (unused?)
void FUN_800b9bc0(int param1, int param_2, int param_3, int param_4)
{ 
  // check if modelID is player
  // modelID is 0xc of BSP meta
  
  return (uint)(*(short *)(param_4 + 0xc) == 0x18);
}

// RB_Spider_LInB
void FUN_800b9bd4(int param_1)
{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined2 *puVar6;
  undefined2 local_18;
  undefined2 local_16;
  undefined2 local_14;
  
  // If this instance has no thread
  if (*(int *)(param_1 + 0x6c) == 0) 
  {
	// b95e4
	// "spider"
	// PROC_BirthWithObject
	// 0x10 = size
	// 0 = no relation to param4
	// 0x300 = SmallStackPool
	// 0xa = "spider" thread bucket
    iVar1 = FUN_8004205c(0x10030a,FUN_800b9848,0x800b95e4,0);
	
	// give thread to instance
    *(int *)(param_1 + 0x6c) = iVar1;
	
	// if thread built successfully
    if (iVar1 != 0) 
	{
	  // get object created with thread
      puVar6 = *(undefined2 **)(iVar1 + 0x30);
	  
	  // set funcThCollide, to make player spin out
      *(undefined4 *)(iVar1 + 0x28) = 0x800b9bc0;
	  
	  // give instance to thread
      *(int *)(iVar1 + 0x34) = param_1;
	  
	  // set scale (x,y,z)
      *(undefined2 *)(param_1 + 0x1c) = 0x1c00;
      *(undefined2 *)(param_1 + 0x1e) = 0x1c00;
      *(undefined2 *)(param_1 + 0x20) = 0x1c00;
	  
	  // set animation to 1
      *(undefined *)(param_1 + 0x52) = 1;
	  
	  // spiderID
      iVar2 = strlen(param_1 + 8);
      puVar6[1] = (ushort)*(byte *)(iVar2 + param_1 + 7) - 0x30;
	  
	  // spider is near roof
      puVar6[3] = 1;
	  
	  // reset animation loop counter
      *puVar6 = 0;
	  
	  // depending on spiderID, set delay,
	  // three different cycles total
	  
      if (puVar6[1] == 3) {
        puVar6[2] = 0x5b;
      }
      else {
        if (puVar6[1] == 2) {
          puVar6[2] = 0x45;
        }
        else {
          puVar6[2] = 0;
        }
      }
	  
	  // INSTANCE_Birth3D -- ptrModel, name, thread
      iVar1 = FUN_8003086c(*(undefined4 *)(PTR_DAT_8008d2ac + 0x22ac),
                           s_spidershadow_800b95ec,iVar1);
	  
	  // save instance
      *(int *)(puVar6 + 6) = iVar1;
	  
	  // copy position and rotation from one instance to another
      uVar3 = *(undefined4 *)(param_1 + 0x34);
      uVar4 = *(undefined4 *)(param_1 + 0x38);
      uVar5 = *(undefined4 *)(param_1 + 0x3c);
      *(undefined4 *)(iVar1 + 0x30) = *(undefined4 *)(param_1 + 0x30);
      *(undefined4 *)(iVar1 + 0x34) = uVar3;
      *(undefined4 *)(iVar1 + 0x38) = uVar4;
      *(undefined4 *)(iVar1 + 0x3c) = uVar5;
      uVar3 = *(undefined4 *)(param_1 + 0x44);
      uVar4 = *(undefined4 *)(param_1 + 0x48);
      uVar5 = *(undefined4 *)(param_1 + 0x4c);
      *(undefined4 *)(iVar1 + 0x40) = *(undefined4 *)(param_1 + 0x40);
	  
	  // Set position of spider shadow
      *(undefined4 *)(iVar1 + 0x44) = uVar3;
      *(undefined4 *)(iVar1 + 0x48) = uVar4;
      *(undefined4 *)(iVar1 + 0x4c) = uVar5;
	  
	  // X, Y, Z
      *(undefined4 *)(*(int *)(puVar6 + 6) + 0x44) = *(undefined4 *)(param_1 + 0x44);
      *(int *)(*(int *)(puVar6 + 6) + 0x48) = *(int *)(param_1 + 0x48) + -8;
      *(undefined4 *)(*(int *)(puVar6 + 6) + 0x4c) = *(undefined4 *)(param_1 + 0x4c);
	  
	  // Scale (x, y, z)
      *(undefined2 *)(*(int *)(puVar6 + 6) + 0x1c) = 0x2000;
      *(undefined2 *)(*(int *)(puVar6 + 6) + 0x1e) = 0x2000;
      *(undefined2 *)(*(int *)(puVar6 + 6) + 0x20) = 0x2000;
	  
      local_18 = 0;
      local_14 = 0;
      local_16 = 0x200;
	  
	   // convert 3 rotation shorts into rotation matrix
      FUN_8006c2a4(*(int *)(puVar6 + 6) + 0x30,&local_18);
	  
      *(int *)(param_1 + 0x48) = *(int *)(param_1 + 0x48) + 0x4c0;
    }
  }
  return;
}

// RB_StartText_ProcessBucket
void FUN_800b9dd8()
{
	// intentionally empty,
	// JR RA + NOP, 8 bytes large
	return;
}

// RB_StartText_LInB
void FUN_800b9de0()
{
	// intentionally empty
	// JR RA + NOP, 8 bytes large
	return;
}

// RB_Teeth_LInB
void FUN_800b9df0(undefined4 param_1,int param_2)
{
  // Do not make a thread for time trial, or relic.
  // Time Trial will be forever closed
  // Relic will be forever open
	
  *(char *)(param_2 + 0x50) = *(char *)(param_2 + 0x50) + '\x02';
  
  // If in relic race
  if ((*(uint *)PTR_DAT_8008d2ac & 0x4000000) != 0) 
  {
	// enable access through a door (disable collision)
    DAT_8008d728 = DAT_8008d728 | 1;
	
	// Make invisible
    *(uint *)(param_2 + 0x28) = *(uint *)(param_2 + 0x28) | 0x80;
  }
  return;
}

// RB_Teeth_BSP_Callback
void FUN_800b9e44(short *param_1,int param_2)
{
  short sVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  sVar1 = *(short *)(param_2 + 0x44);
  
  // if not driver
  if (sVar1 != 0x18) 
  {
    if (sVar1 < 0x19) 
	{
	  // if not nitro
      if (sVar1 != 6) {
        return;
      }
    }
    else 
	{
	  // if not potion or tnt
      if ((sVar1 != 0x1d) && (sVar1 != 0x27)) {
        return;
      }
    }
  }
  
  // thread on ScratchpadStruct
  iVar2 = *(int *)(param_1 + 0xc);
  
  // another instance
  iVar3 = *(int *)(param_2 + 0x34);
  
  // thread instance
  iVar4 = *(int *)(iVar2 + 0x34);
  
  if ((iVar3 != 0) && (iVar4 != 0)) {
    iVar2 = ((int)param_1[0] - *(int *)(iVar3 + 0x44)) * (int)*(short *)(iVar4 + 0x34) +
            ((int)param_1[2] - *(int *)(iVar3 + 0x4c)) * (int)*(short *)(iVar4 + 0x40);
			
    if (iVar2 < 0) {
      iVar2 = -iVar2;
    }
    if (0x100 < iVar2 >> 0xc) {
      return;
    }
	
	// thread (again)
    iVar2 = *(int *)(param_1 + 0xc);
  }
  
  // door is open
  **(undefined4 **)(iVar2 + 0x30) = 1;
  
  return;
}

// RB_Teeth_ThTick
void FUN_800b9f0c(int param_1)
{
  int iVar1;
  uint uVar2;
  int *piVar3;
  int iVar4;
  
  // get object from thread
  piVar3 = *(int **)(param_1 + 0x30);
  
  // get instance from thread
  iVar4 = *(int *)(param_1 + 0x34);
  
  // if door is not moving
  if (*piVar3 == 0) 
  {
	// if timer is zero
    if (piVar3[1] == 0) goto LAB_800b9ff8;
    
	// reduce timer by milliseconds
	iVar1 = piVar3[1] - *(int *)(PTR_DAT_8008d2ac + 0x1d04);
    
	// set new timer
	piVar3[1] = iVar1;
    
	// if timer is up
	if (iVar1 < 1) 
	{
	  // play sound
	  // teeth closing
      FUN_8002f0dc(0x75,iVar4);
      
	  // timer is zero
	  piVar3[1] = 0;
	  
	  // door is closing
      *piVar3 = -1;
	  
      goto LAB_800b9fe8;
    }
  }
  
  // if door is moving
  else 
  {
	// modify animation idex by direction
    *(short *)(iVar4 + 0x54) = *(short *)(iVar4 + 0x54) + *(short *)piVar3;
	
	// get number of frames in animation
    iVar1 = FUN_8005b0f4(iVar4,0);
	
	// if animation is not on last frame
    if ((int)*(short *)(iVar4 + 0x54) < iVar1) 
	{
	  // if animation when backwards past beginning
      if ((int)*(short *)(iVar4 + 0x54) < 0) 
	  {
		// set animation to beginning
        *(undefined2 *)(iVar4 + 0x54) = 0;
		
		// door is not moving
        *piVar3 = 0;
		
		// timer is zero
        piVar3[1] = 0;
		
		// remove access (enable collision)
        DAT_8008d728 = DAT_8008d728 & 0xfffffffe;
      }
    }
	
	// if animation is on last frame (or past)
    else 
	{
	  // set animation to last frame
      *(short *)(iVar4 + 0x54) = (short)iVar1 + -1;
	  
	  // door is not moving (fully open)
      *piVar3 = 0;
	  
	  // timer, 2 seconds 
      piVar3[1] = 0x780;
    }
LAB_800b9fe8:
    if (piVar3[1] == 0) {
LAB_800b9ff8:
      if (-1 < *piVar3) goto LAB_800ba084;
    }
  }
  
  // Teeth instance position
  DAT_1f800108 = *(undefined2 *)(iVar4 + 0x44);
  DAT_1f80010a = *(undefined2 *)(iVar4 + 0x48);
  DAT_1f80010c = *(undefined2 *)(iVar4 + 0x4c);
  
  // hitRadius and hitRadiusSquared
  DAT_1f80010e = 0x300;
  _DAT_1f800110 = 0x90000;
  
  // RB_Teeth_BSP_Callback
  // not a BSP callback, ThreadBucket collision callback
  DAT_1f800130 = &FUN_800b9e44;
  
  DAT_1f800114 = 0x70;
  DAT_1f800120 = param_1;
  
  // If door wants to close, but Player or Mine
  // is in the way, then do not force the doors to close
  
  // pointer to first Player thread
  FUN_800425d4(*(undefined4 *)(PTR_DAT_8008d2ac + 0x1b2c),&DAT_1f800108,0);
  
  // pointer to first Mine thread (tnt, beaker, etc)
  FUN_800425d4(*(undefined4 *)(PTR_DAT_8008d2ac + 0x1b7c),&DAT_1f800108,0);
  
LAB_800ba084:

  // if no timer exists
  // (opening, closing, or full closed)
  if (piVar3[1] == 0) 
  {
	// make visible
	uVar2 = *(uint *)(iVar4 + 0x28) & 0xffffff7f;
  }

  // if a timer is active
  // (fully open)
  else 
  {
	// make invisible
    uVar2 = *(uint *)(iVar4 + 0x28) | 0x80;
  }

  // set flags
  *(uint *)(iVar4 + 0x28) = uVar2;
  
  return;
}

// RB_Teeth_LInC
undefined4 FUN_800ba0c8(int param_1,int param_2,short *param_3)
{
  int iVar1;
  undefined4 *puVar2;
  
  // This is the door you can shoot in tiger temple
  
  // Only continue if not in relic race
  if ((*(uint *)PTR_DAT_8008d2ac & 0x4000000) == 0) 
  {
	 // get thread for this instance
    iVar1 = *(int *)(param_1 + 0x6c);
	
	// if there is no thread
    if (iVar1 == 0) 
	{
	  // PROC_BirthWithObject
	  // 0x8 = size
	  // 0 = no relation to param4
	  // 0x300 = SmallStackPool
	  // 0x3 = "static" thread bucket
      iVar1 = FUN_8004205c(0x80303,FUN_800b9f0c,s_teeth_800b9de8,0);
	  
	  // give thread to instance
      *(int *)(param_1 + 0x6c) = iVar1;
	  
	  // if thread failed
      if (iVar1 == 0) 
	  {
		// quit
        return 2;
      }
	  
	  // get object created with thread
      puVar2 = *(undefined4 **)(iVar1 + 0x30);
	  
	  // give instance to thread
      *(int *)(iVar1 + 0x34) = param_1;
	  
	  // door not moving
      *puVar2 = 0;
	  
	  // timer is zero
      puVar2[1] = 0;
    }
	
	// get object created by thread
    iVar1 = *(int *)(iVar1 + 0x30);
	
	// if collided object is a player
    if (param_3[6] == 0x18) 
	{
	  // if driver is using mask weapon
      if ((*(uint *)(*(int *)(param_2 + 0x30) + 0x2c8) & 0x800000) != 0) 
	  {
		// RB_Teeth_OpenDoor
        FUN_800ba220(param_1);
      }
	  
	  // if collided object is a player
      if (param_3[6] == 0x18) {
        return 2;
      }
    }
	
	// If collide with something
	// that is not a player
	
	// teeth->timeOpen == 0 (time to close)
    if (*(int *)(iVar1 + 4) == 0) 
	{
      iVar1 = 
				// (collObj.x - teethInst.x) * teethInst.matrix[0][2]
				((int)*param_3 - *(int *)(param_1 + 0x44)) * (int)*(short *)(param_1 + 0x34) +
				
				// (collObj.z - teethInst.z) * teethInst.matrix[2][2]
				((int)param_3[2] - *(int *)(param_1 + 0x4c)) * (int)*(short *)(param_1 + 0x40);
				
      if (iVar1 < 0) {
        iVar1 = -iVar1;
      }
      if (iVar1 >> 0xc < 0x81) 
	  {
        return 1;
      }
      return 2;
    }
  }
  return 2;
}

// RB_Teeth_OpenDoor
void FUN_800ba220(int param_1)
{
  int iVar1;
  
  // get thread for object
  iVar1 = *(int *)(param_1 + 0x6c);
  
  // if there is no thread,
  // just in case it wasn't initialized
  if (iVar1 == 0) 
  {
	// PROC_BirthWithObject
	// 0x8 = size
	// 0 = no relation to param4
	// 0x300 flag = SmallStackPool
	// 0x3 = "static" thread bucket
    iVar1 = FUN_8004205c(0x80303,FUN_800b9f0c,s_teeth_800b9de8,0);
	
	// give thread to instance
    *(int *)(param_1 + 0x6c) = iVar1;
	
	// if thread failed
    if (iVar1 == 0) 
	{
	  // quit
      return;
    }
	
	// give instance to thread
    *(int *)(iVar1 + 0x34) = param_1;
	
    *(undefined4 *)(*(int *)(iVar1 + 0x30) + 4) = 0;
  }
  
  // play sound,
  // teeth opening
  FUN_8002f0dc(0x75,param_1);
  
  // door is open
  **(undefined4 **)(iVar1 + 0x30) = 1;
  
  // enable access through a door (disable collision)
  DAT_8008d728 = DAT_8008d728 | 1;
  
  return;
}

// RB_Turtle_ThTick
void FUN_800ba2c0(int param_1)
{
  short sVar1;
  short sVar2;
  int iVar3;
  short *psVar4;
  int iVar5;
  
  // thread -> object
  psVar4 = *(short **)(param_1 + 0x30);
  
  // thread -> instance
  iVar5 = *(int *)(param_1 + 0x34);
  
  // 0 from moment it hits bottom to moment it hits top
  if (psVar4[1] == 0) {
    sVar1 = *psVar4;
	
	// if less than 1.0 seconds
	// wait for rise
    if (*psVar4 < 0x3c0) 
	{
	  // get elapsed ms per frame ~32
      sVar2 = *(short *)(PTR_DAT_8008d2ac + 0x1d04);
	  
	  // add milliseconds
      *psVar4 = sVar1 + sVar2;
	  
	  // Naughty Dog bug, should have just been:
	  // if (0x3c0 < sVar1+sVar2)
	  //	*psVar4 = 0x3c0
	  // 	play sound
	  
	  // Then the original "if < 0x3c0"
	  // goes to "else" next frame
	  
	  // if more than 1.5 seconds passed
      if (0x5a0 < (short)(sVar1 + sVar2)) 
	  {
		// lock to 1.5s
        *psVar4 = 0x5a0;
      }
	  
	  // if 1.5s passed
      if (*psVar4 == 0x5a0) 
	  {  
		// play water sound
        FUN_8002f0dc(0x7d,iVar5);
      }
    }
    
	// if more than one second has passed
	// time to rise
	else 
	{
	  // turtle not fully down,
	  // impacts jumping
      psVar4[4] = 1;
	  
	  // end of animation
      if ((int)*(short *)(iVar5 + 0x54) + -1 < 1) 
	  {
		// reset direction
        psVar4[1] = 1;
		
		// reset timer to zero
        *psVar4 = 0;
      }
	  
	  // playing animation
      else 
	  {
		// decrement frame (make turtle rise)
        *(short *)(iVar5 + 0x54) = *(short *)(iVar5 + 0x54) + -1;
      }
    }
  }
  
  // 1 from moment it hits top to moment it hits bottom
  else 
  {
	// get timer
    sVar1 = *psVar4;
	
	// if less than 1.0 seconds
	// wait for time to fall
    if (*psVar4 < 0x3c0) 
	{
      // get elaped time
	  sVar2 = *(short *)(PTR_DAT_8008d2ac + 0x1d04);
      
	  // add milliseconds
	  *psVar4 = sVar1 + sVar2;
	  
	  // Naughty Dog bug, should be 0x3c0
      
	  // if more than 1.5s
	  if (0x5a0 < (short)(sVar1 + sVar2)) 
	  {
		// lock to 1.5s
        *psVar4 = 0x5a0;
      }
    }
	
	// if more than 1.0s
	// time to fall
    else 
	{
	  // get animation frame
      sVar1 = *(short *)(iVar5 + 0x54);
      
	  // INSTANCE_GetNumAnimFrames
	  iVar3 = FUN_80030f58(iVar5,0);
	  
	  // if animation is not done
      if ((int)sVar1 + 1 < iVar3) 
	  {
		// increment frame (make turtle fall)
        *(short *)(iVar5 + 0x54) = *(short *)(iVar5 + 0x54) + 1;
      }
	  
	  // if animation is done
      else 
	  {
		// reset direction
        psVar4[1] = 0;
		
		// reset timer
        *psVar4 = 0;
		
		// turtle is fully down
        psVar4[4] = 0;
      }
    }
  }
  return;
}

// RB_Turtle_LInC
undefined4 FUN_800ba420(int param_1,int param_2)
{
  int iVar1;
  undefined uVar2;
  
  // get driver speed
  iVar1 = (int)*(short *)(*(int *)(param_2 + 0x30) + 0x38e);
  
  // absolute value
  if (iVar1 < 0) {
    iVar1 = -iVar1;
  }
  
  // if driver has high speed
  if (0x1400 < iVar1) 
  {
	// small jump
    uVar2 = 1;
	
	// if turtleInst->thread->object->state != FullyDown
    if (*(short *)(*(int *)(*(int *)(param_1 + 0x6c) + 0x30) + 8) != 0) {
      
	  // big jump
	  uVar2 = 2;
    }
    
	// make the player jump
	*(undefined *)(*(int *)(param_2 + 0x30) + 0x366) = uVar2;
    
	return 2;
  }
  return 1;
}

// RB_Turtle_LInB
void FUN_800ba470(int param_1)
{
  undefined2 uVar1;
  int iVar2;
  undefined2 *puVar3;
  
  *(uint *)(param_1 + 0x28) = *(uint *)(param_1 + 0x28) | 0x2000;
  
  // if there is no thread for this instance
  if (*(int *)(param_1 + 0x6c) == 0) 
  {
	 // PROC_BirthWithObject
	 // 0xc = size
	 // 0 = no relation to param4
	 // 0x300 flag = SmallStackPool
	 // 0x3 = "static" thread bucket
    iVar2 = FUN_8004205c(0xc0303,&FUN_800ba2c0,s_turtle_800ba2b8,0);
	
	// give thread to instance
    *(int *)(param_1 + 0x6c) = iVar2;
	
	// if the thread built successfully
    if (iVar2 != 0) 
	{
	  // get object created with thread
      puVar3 = *(undefined2 **)(iVar2 + 0x30);
	  
	  // give instance to thread
      *(int *)(iVar2 + 0x34) = param_1;
	  
	  // set scale (x,y,z)
      *(undefined2 *)(param_1 + 0x1c) = 0x1000;
      *(undefined2 *)(param_1 + 0x1e) = 0x1000;
      *(undefined2 *)(param_1 + 0x20) = 0x1000;
	  
	  // get length of string attached to instance
      iVar2 = strlen(param_1 + 8);
	  
	  // turtleID
      puVar3[2] = (ushort)*(byte *)(iVar2 + param_1 + 7) - 0x30;
      
	  // default direction (waste)
	  puVar3[1] = 1;
	  
	  // reset timer
      *puVar3 = 0;
	  
	  // restart animation, set frame to zero
      *(undefined2 *)(param_1 + 0x54) = 0;
	  
	  // put turtles on different cycles, based on turtleID
      if ((puVar3[2] & 1) == 0) 
	  {
		// turtle is fully up
        puVar3[1] = 1;
        puVar3[4] = 1;
      }
      
	  else 
	  {
		// turtle is fully down
        puVar3[1] = 0;
        puVar3[4] = 0;
		
		// INSTANCE_GetNumAnimFrames
		// last frame of fall animation
        uVar1 = FUN_80030f58(param_1,0);
        *(undefined2 *)(param_1 + 0x54) = uVar1;
      }
    }
  }
  return;
}


