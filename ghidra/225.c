
// 225: 1/1

// VB_EndEvent_DrawMenu
void FUN_8009f718(void)

{
  short sVar1;
  int iVar2;
  uint uVar3;
  undefined *puVar4;
  short sVar5;
  int iVar6;
  undefined4 uVar7;
  short *psVar8;
  short sVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  uint uVar13;
  int iVar14;
  char acStack160 [24];
  ushort uStack136;
  ushort uStack134;
  short asStack128 [4];
  short sStack120;
  short sStack118;
  short sStack116;
  short sStack114;
  ushort uStack112;
  short sStack104;
  ushort uStack96;
  ushort uStack88;
  short sStack80;
  short sStack72;
  int iStack60;
  int iStack56;
  uint uStack52;
  int iStack48;
  int iStack44;
  
  sStack104 = 0;
  uStack88 = 1;
  sStack80 = 0;
  memset();
  sStack72 = 0;
  if (DAT_8008d52c < 0xf0) {
    DAT_8008d52c = DAT_8008d52c + 1;
  }
  
  // lng index for BATTLE
  iVar10 = 0x50;
  
  // if you are not in battle mode
  if ((*(uint *)PTR_DAT_8008d2ac & 0x20) == 0) 
  {
	// lng index for VERSUS
    iVar10 = 0x14f;
  
	// number of battle teams
	uStack96 = (ushort)(byte)PTR_DAT_8008d2ac[0x1ca8];
	
    uVar13 = (uint)*(ushort *)
                    (&DAT_800a01e0 + ((uint)(byte)PTR_DAT_8008d2ac[0x1ca8] - 2) * 10);
  }
  
  // if you are in battle mode
  else {
    iVar11 = 0;
	
	// number of battle teams
    uStack96 = *(ushort *)(PTR_DAT_8008d2ac + 0x1ddc);
    
	puVar4 = PTR_DAT_8008d2ac;
    
	// if you don't have zero players
	if (PTR_DAT_8008d2ac[0x1ca8] != '\0') 
	{
	  // for iVar11 = 0; iVar11 < numPlyrCurrGame; iVar11++
      do 
	  {
			// increment something based on which team each player is on
			asStack128[*(int *)(*(int *)(puVar4 + 0x24ec) + 0x4e8)] =
            asStack128[*(int *)(*(int *)(puVar4 + 0x24ec) + 0x4e8)] + 1;
			
        iVar11 = iVar11 + 1;
        puVar4 = puVar4 + 4;
      } while (iVar11 < (int)(uint)(byte)PTR_DAT_8008d2ac[0x1ca8]);
    }
	
    uVar13 = 0xd8 - ((*(int *)(PTR_DAT_8008d2ac + 0x1ddc) + -1) * 10 +
                    (uint)(byte)PTR_DAT_8008d2ac[0x1ca8] * 0x1a + 0x28) >> 1;
  }
  
  // Disable drawing lines between multiplayer screens
  *(uint *)(PTR_DAT_8008d2ac + 0x256c) = *(uint *)(PTR_DAT_8008d2ac + 0x256c) & 0xffff7fff;
  
  // RaceFlag_SetFullyOnScreen
  FUN_8004402c();
  
  if (DAT_8008d52c < 0x1a) {
    uVar7 = 0x296;
    iVar11 = DAT_8008d52c;
  }
  
  else {
    uVar7 = 0x180;
    iVar11 = DAT_8008d52c + -0x19;
  }
  
  // fly-in interpolation
  FUN_8004ecd4(&uStack136,0x296,(int)(short)uVar13,uVar7,(int)(short)uVar13,iVar11,5);
  
  iVar14 = uVar13 + 0x28;
  
  // "Versus" or "Battle"
  FUN_80022878(*(undefined4 *)(iVar10 * 4 + DAT_8008d878),(int)(short)uStack136,
               (int)(short)uStack134,1,0xffff8000);
  
  // String 0x328 = STANDINGS
  FUN_80022878(*(undefined4 *)(DAT_8008d878 + 0x328),(int)(short)uStack136,
               (int)(((uint)uStack134 + 0x11) * 0x10000) >> 0x10,1,0xffff8000);
  
  iVar10 = (int)(short)uStack96;
  iVar11 = 0;
  if (0 < iVar10) {
    iStack60 = iVar10;
    iStack56 = iVar10 + -2;
    iVar12 = 0;
    uStack52 = (uint)(iVar10 < 3);
    iStack48 = 0x1e;
    iStack44 = 5;
    do {
      sVar1 = asStack128[*(int *)(PTR_DAT_8008d2ac + iVar12 + 0x1dc8)];
      sVar5 = (short)iVar14;
      if (iStack48 < DAT_8008d52c) {
        uVar7 = 0x165;
        iVar10 = (DAT_8008d52c + -0x19) - iStack44;
      }
      else {
        uVar7 = 0x296;
        iVar10 = DAT_8008d52c;
      }
	  
	  // fly-in interpolation
      FUN_8004ecd4(&uStack136,0x296,(int)sVar5,uVar7,(int)sVar5,iVar10,5);
      
	  sVar9 = 0;
	  
	  // If you are not in battle mode
      if ((*(uint *)PTR_DAT_8008d2ac & 0x20) == 0) 
	  {
        uStack112 = *(ushort *)
                     (&DAT_800a01e0 + ((int)((uint)uStack88 << 0x10) >> 0xf) + iStack56 * 10);
        
		// Draw character icon
		// DecalHUD_DrawPolyFT4
		FUN_80022db0(
					  // Icon Pointer
					  *(undefined4 *)
                      (PTR_DAT_8008d2ac +
                      (int)*(short *)(&DAT_80086d8c +
                                     (int)(short)(&DAT_80086e84)
                                                 [*(int *)(PTR_DAT_8008d2ac + iVar12 + 0x1dc8)] *
                                     0x10) * 4 + 0x1eec),
					
					// Position X and Position Y
					(int)(short)uStack136,(int)(short)uStack112,
					
					// pointer to PrimMem struct
					*(int *)(PTR_DAT_8008d2ac + 0x10) + 0x74,
					
					// pointer to OT mem
                    *(undefined4 *)(PTR_DAT_8008d2ac + 0x147c),
					
					1,0x1000);
      }
	  
	  // if battle mode
      else 
	  {
        iVar10 = (int)sVar1 * 0x1b0000;
        uStack112 = (sVar5 + (short)((iVar10 >> 0x10) - (iVar10 >> 0x1f) >> 1)) - 0xd;
        iVar10 = 0;
		
		// if there are players
        if (PTR_DAT_8008d2ac[0x1ca8] != '\0') 
		{
		  // pointer to character IDs
          psVar8 = &DAT_80086e84;
		  
		  // loop through all players
          do 
		  {
			  // player -> battleTeam == (teamID)
            if (*(int *)(*(int *)(PTR_DAT_8008d2ac + iVar10 * 4 + 0x24ec) + 0x4e8) ==
                *(int *)(PTR_DAT_8008d2ac + iVar12 + 0x1dc8)) 
			{
              iVar6 = (int)sVar9;
              sVar9 = sVar9 + 1;
			  
			  // DecalHUD_DrawPolyFT4
              FUN_80022db0(*(undefined4 *)
                            (PTR_DAT_8008d2ac +
                            (int)*(short *)(&DAT_80086d8c + (int)*psVar8 * 0x10) * 4 + 0x1eec),
                           (int)(short)uStack136,(int)sVar5 + iVar6 * 0x1b,
						   
						    // pointer to PrimMem struct
                           *(int *)(PTR_DAT_8008d2ac + 0x10) + 0x74,
						   
						   // pointer to OT mem
                           *(undefined4 *)(PTR_DAT_8008d2ac + 0x147c),
						   
						   1,0x1000);
            }
			
			// loop counter
            iVar10 = iVar10 + 1;
			
			// increment pointer to next characterID
            psVar8 = psVar8 + 1;
			
          } while (iVar10 < (int)(uint)(byte)PTR_DAT_8008d2ac[0x1ca8]);
        }
        iVar14 = (int)sVar1 * 0x1b + iVar14 + 10;
      }
      uStack88 = uStack88 + 1;
      sVar1 = 2;
      if (uStack52 == 0) {
        sVar1 = uStack96 - 1;
      }
      iVar6 = (int)sVar1;
      iVar10 = 0;
      if (0 < iVar6) 
	  {
		
        do 
		{
		  // If you are not in Battle Mode
          if ((*(uint *)PTR_DAT_8008d2ac & 0x20) == 0) 
		  {
			// get position player finished in race
            iVar2 = (int)*(short *)(*(int *)(PTR_DAT_8008d2ac +
                                            *(int *)(PTR_DAT_8008d2ac + iVar12 + 0x1dc8) * 4 +
                                            0x24ec) + 0x482);
          }
          
		  // If you are in Battle Mode
		  else 
		  {
			// get position of the team in battle
            iVar2 = *(int *)(PTR_DAT_8008d2ac +
                            *(int *)(PTR_DAT_8008d2ac + iVar12 + 0x1dc8) * 4 + 0x1da8);
          }
		  
          uVar7 = 0x4003;
          if (
				(iVar10 == iVar2) && 
				(
					uVar7 = 0x4004, 
				
					// odd number frames
					(*(uint *)(PTR_DAT_8008d2ac + 0x1cec) & 1) != 0
				)
             ) 
		  {
            uVar7 = 0x4003;
          }
		  
          iVar2 = iVar10 + 1;
          
		  // string for each player rank and count from standings (0x1e80)
		  sprintf(acStack160,s_%d%s-%2.02ld_8009f700,iVar2,
                  *(undefined4 *)((int)(short)(&DAT_800a0200)[iVar10] * 4 + DAT_8008d878),
                  *(undefined4 *)
                   (PTR_DAT_8008d2ac +
                   (*(int *)(PTR_DAT_8008d2ac + iVar12 + 0x1dc8) * 3 + iVar10) * 4 + 0x1e80));
          
		  // Draw string
		  FUN_80022878(acStack160,(int)(((uint)uStack136 + 0x79) * 0x10000) >> 0x10,
                       (int)((((uint)uStack112 - (iVar6 * 4 + -0xd)) + iVar10 * 8) * 0x10000) >>
                       0x10,2,uVar7);
					   
          iVar10 = iVar2;
        } while (iVar2 < iVar6);
      
	  }
      
	  if (*(int *)(PTR_DAT_8008d2ac + *(int *)(PTR_DAT_8008d2ac + iVar12 + 0x1dc8) * 4 + 0x1de0) ==
          (int)sStack80) {
        sStack72 = sStack72 + 1;
      }
      else {
        sStack72 = 0;
      }
      sVar1 = (short)iVar11 - sStack72;
      if (sStack72 == 0) {
        sVar1 = (short)iVar11;
      }
      iStack48 = iStack48 + 5;
      iStack44 = iStack44 + 5;
      sStack80 = *(short *)(PTR_DAT_8008d2ac +
                           *(int *)(PTR_DAT_8008d2ac + iVar12 + 0x1dc8) * 4 + 0x1de0);
      iVar11 = iVar11 + 1;
      sprintf(acStack160,&DAT_8009f710,(int)sVar1 + 1,
              *(undefined4 *)((int)(short)(&DAT_800a0200)[(int)sVar1] * 4 + DAT_8008d878));
			  
	  // Draw String
      FUN_80022878(acStack160,(int)(((uint)uStack136 - 0x24) * 0x10000) >> 0x10,
                   (int)(((uint)uStack112 + 5) * 0x10000) >> 0x10,1,0xffff8000);
				   
      iVar12 = iVar12 + 4;
    } while (iVar11 < iStack60);
  }
  uVar13 = 0;
  if (PTR_DAT_8008d2ac[0x1ca8] != '\0') {
    iVar10 = 0;
    do 
	{
	  // get pointer to instance of Big Number in HUD
      iVar11 = *(int *)(*(int *)(PTR_DAT_8008d2ac + uVar13 * 4 + 0x24ec) + 0x498);
      
	  // if the pointer is valid
	  if (iVar11 != 0) 
	  {
		// clear the scale
        *(undefined2 *)(iVar11 + 0x20) = 0;
        *(undefined2 *)(iVar11 + 0x1e) = 0;
        *(undefined2 *)(iVar11 + 0x1c) = 0;
      }
	  
      if (sStack104 == 0) 
	  {
		// if this is not battle mode
        if ((*(uint *)PTR_DAT_8008d2ac & 0x20) == 0) 
		{
		  // Get which player finished the race first
          uVar3 = (uint)*(byte *)(*(int *)(PTR_DAT_8008d2ac + 0x250c) + 0x4a);
        }
		
		// if this is battle mode
        else 
		{
          uVar3 = *(uint *)(PTR_DAT_8008d2ac + 0x2558);
        }
		
        if (uVar3 != uVar13) goto LAB_8009ff4c;
        sStack104 = 1;
        puVar4 = PTR_DAT_8008d2ac + iVar10;
        
		if (
				// If there are two players
				(PTR_DAT_8008d2ac[0x1ca8] == '\x02') && 
				
				// something in camera buffer
				(0x100 < *(short *)(puVar4 + 0x188))
			) 
		{
          *(short *)(puVar4 + 0x188) = *(short *)(puVar4 + 0x188) + -0xc;
          *(undefined4 *)(puVar4 + 0x274) = 0x80;
        }
		
		// fly-in interpolation
        FUN_8004ecd4(&uStack136,(int)*(short *)(PTR_DAT_8008d2ac + iVar10 + 0x184),
                     (int)*(short *)(PTR_DAT_8008d2ac + iVar10 + 0x186),0x14,0xc,DAT_8008d52c,0x19);
        
		sStack120 = uStack136 - 3;
        sStack118 = uStack134 - 2;
        sStack116 = *(short *)(PTR_DAT_8008d2ac + iVar10 + 0x188) + 6;
        sStack114 = *(short *)(PTR_DAT_8008d2ac + iVar10 + 0x18a) + 4;
        
		// RECTMENU_DrawOuterRect_HighLevel (solid)
		FUN_80045650(&sStack120,&DAT_8008d438,0,
                     *(undefined4 *)(*(int *)(PTR_DAT_8008d2ac + 0x10) + 0xa0));
        
		puVar4 = PTR_DAT_8008d2ac + iVar10;
		
		*(ushort *)(puVar4 + 0x184) = uStack136;
        *(ushort *)(puVar4 + 0x186) = uStack134;
      }
      else {
LAB_8009ff4c:
        puVar4 = PTR_DAT_8008d2ac + iVar10;
		
        if (0 < *(short *)(puVar4 + 0x188)) {
          *(short *)(puVar4 + 0x184) = *(short *)(puVar4 + 0x184) + 5;
          *(short *)(puVar4 + 0x186) = *(short *)(puVar4 + 0x186) + 3;
          *(short *)(puVar4 + 0x188) = *(short *)(puVar4 + 0x188) + -10;
          *(short *)(puVar4 + 0x18a) = *(short *)(puVar4 + 0x18a) + -6;
        }
      }
      uVar13 = uVar13 + 1;
	  
	  // pushBuffer buffer, one for each player
      iVar10 = iVar10 + 0x110;
	  
    } while ((int)uVar13 < (int)(uint)(byte)PTR_DAT_8008d2ac[0x1ca8]);
  }
  if (((DAT_8008d4bc & 1) == 0) && (0x19 < DAT_8008d52c)) 
  {
	// If this is not Battle Mode
    if ((*(uint *)PTR_DAT_8008d2ac & 0x20) == 0) 
	{
      puVar4 = &DAT_800a0164;
    }
	
	// If this is Battle Mode
    else {
      puVar4 = &DAT_800a01b4;
    }
	
	// Make Menu Box appear (just like 221 overlay)
    FUN_80046990(puVar4);
	
    DAT_8008d4bc = DAT_8008d4bc | 1;
  }
  return;
}

