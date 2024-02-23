
// 222: 2/2

// AA_EndEvent_DrawMenu
void FUN_8009f704(void)

{
  short *psVar1;
  byte bVar2;
  byte bVar3;
  bool bVar4;
  uint uVar5;
  undefined *puVar6;
  uint uVar7;
  int iVar8;
  int iVar9;
  undefined4 uVar10;
  int iVar11;
  int iVar12;
  undefined *puVar13;
  int iVar14;
  int iVar15;
  int iVar16;
  ushort uStack56;
  short sStack54;
  ushort uStack48;
  
  // main game struct
  puVar6 = PTR_DAT_8008d2ac;
  
  iVar15 = 0;
  uStack48 = 0;
  
  // pointer to P1
  iVar16 = *(int *)(PTR_DAT_8008d2ac + 0x24ec);
  
									// numPlyrCurrGame - 1
  puVar13 = (&PTR_DAT_8008625c)[(uint)(byte)PTR_DAT_8008d2ac[0x1ca8] - 1];
  
  // if race ended less than 30 second ago,
  // 30fps, 30 secs, 900 frames
  if ((int)DAT_8008d52c < 900) 
  {
	// keep adding to the frame counter
    DAT_8008d52c = DAT_8008d52c + 1;
  }
  
  // if Big Number is not a certain scale
  if (*(short *)(*(int *)(iVar16 + 0x498) + 0x1c) != 0x1e00) 
  {
	// set scale to zero, stop drawing it
    *(undefined2 *)(*(int *)(iVar16 + 0x49c) + 0x1c) = 0;
    *(undefined2 *)(*(int *)(iVar16 + 0x49c) + 0x1e) = 0;
    *(undefined2 *)(*(int *)(iVar16 + 0x49c) + 0x20) = 0;
  }
  iVar14 = DAT_8008d9cc;
  
  // If you're in Adventure Mode
  if ((*(uint *)PTR_DAT_8008d2ac & 0x80000) != 0) 
  {
	// If you won the race, and you have all 3 letters (C, T, and R)
    if ((*(short *)(iVar16 + 0x482) == 0) && (*(int *)(iVar16 + 0x4cc) == 3)) 
	{
	  // If you have not unlocked this CTR Token
      if (((uint)(&DAT_8008fba4)[(int)(*(int *)(PTR_DAT_8008d2ac + 0x1a10) + 0x4cU) >> 5] >>
           (*(int *)(PTR_DAT_8008d2ac + 0x1a10) + 0x4cU & 0x1f) & 1) == 0) 
	  {
        iVar15 = (int)*(short *)(DAT_8008d9cc + 0x1c) + -0x800;
        if (iVar15 < 0) {
          iVar15 = (int)*(short *)(DAT_8008d9cc + 0x1c) + -0x401;
        }
        uStack56 = *(ushort *)(puVar13 + 0x90);
        sStack54 = *(short *)(puVar13 + 0x92);
        
		// frames since race ended
		if ((int)DAT_8008d52c < 0xe7) {
          if ((int)DAT_8008d52c < 0x8d) {
            iVar8 = (int)*(short *)(puVar13 + 0x90);
            iVar11 = (int)*(short *)(puVar13 + 0x92);
            uVar10 = 8;
            iVar9 = (int)(((uint)*(ushort *)(puVar13 + 0x90) + 0x10) * 0x10000) >> 0x10;
            iVar14 = (int)(((uint)*(ushort *)(puVar13 + 0x92) + 0x10) * 0x10000) >> 0x10;
            uVar5 = DAT_8008d52c;
            goto LAB_OVR1__8009fd28;
          }
		  
		  // interpolate fly-in
          FUN_8004ecd4(&uStack56,(int)(((uint)*(ushort *)(puVar13 + 0x90) + 0x10) * 0x10000) >> 0x10
                       ,(int)(((uint)*(ushort *)(puVar13 + 0x92) + 0x10) * 0x10000) >> 0x10,
                       (int)(((uint)*(ushort *)(puVar13 + 0x90) - 0x10) * 0x10000) >> 0x10,
                       (int)(((uint)*(ushort *)(puVar13 + 0x92) + 0x50) * 0x10000) >> 0x10,
                       DAT_8008d52c - 0x8c,8);
          
		  // if "hudc" scale has fully grown, 
		  if (*(short *)(DAT_8008d9cc + 0x1c) == 0x800) 
		  {
			// play sound of unlocking token
            FUN_80028468(0x67,1);
          }
		  
		  // "hudc"
          iVar14 = DAT_8008d9cc;
          if ((int)(short)uStack56 != (int)*(short *)(puVar13 + 0x90) + -0x10) {
            
			// get scale of "hudc"
			psVar1 = (short *)(DAT_8008d9cc + 0x1c);
			
			// scale "hudc" y
            *(short *)(DAT_8008d9cc + 0x1e) = *(short *)(DAT_8008d9cc + 0x1e) + 0x400;
            
			// scale "hudc" x
			*(short *)(iVar14 + 0x1c) = *psVar1 + 0x400;
            
			// "hudt"
			iVar8 = DAT_8008d9c4;
			
			// Scale "hudc" z
            *(short *)(iVar14 + 0x20) = *(short *)(iVar14 + 0x20) + 0x400;
            
			// scale "hudt" x, y
			*(short *)(iVar8 + 0x1e) = *(short *)(iVar8 + 0x1e) + 0x400;
            *(short *)(iVar8 + 0x1c) = *(short *)(iVar8 + 0x1c) + 0x400;
			
			// "hudr"
            iVar14 = DAT_8008d9c8;
			
			// scale "hudt" z
			*(short *)(iVar8 + 0x20) = *(short *)(iVar8 + 0x20) + 0x400;
            
			// Scale "hudr" (x, y, z)
			*(short *)(iVar14 + 0x1c) = *(short *)(iVar14 + 0x1c) + 0x400;
            *(short *)(iVar14 + 0x20) = *(short *)(iVar14 + 0x20) + 0x400;
            *(short *)(iVar14 + 0x1e) = *(short *)(iVar14 + 0x1e) + 0x400;
          }
        }
        else {
          iVar9 = -400;
          uVar10 = 10;
          iVar8 = (int)(((uint)*(ushort *)(puVar13 + 0x90) + 0x10) * 0x10000) >> 0x10;
          iVar11 = (int)(((uint)*(ushort *)(puVar13 + 0x92) + 0x50) * 0x10000) >> 0x10;
          iVar14 = iVar11;
          uVar5 = DAT_8008d52c - 0xe6;
LAB_OVR1__8009fd28:

		  // interpolate fly-in
          FUN_8004ecd4(&uStack56,iVar8,iVar11,iVar9,iVar14,uVar5,uVar10);
        }
		
		// DAT_8008d9cc = "hudc"
		// Convert X and Y pos
        uVar10 = FUN_8004caa8((int)(short)uStack56,0x200);
        *(undefined4 *)(DAT_8008d9cc + 0x44) = uVar10;	// X pos
        uVar10 = FUN_8004cac8((int)sStack54,0x200);
        *(undefined4 *)(DAT_8008d9cc + 0x48) = uVar10;	// Y pos
		
		// DAT_8008d9c4 = "hudt"
		// Convert X and Y pos
        iVar8 = ((iVar15 >> 10) * 0xc0000 >> 0x10) + 0x1d;
        uVar10 = FUN_8004caa8((short)uStack56 + iVar8,0x200);
        *(undefined4 *)(DAT_8008d9c4 + 0x44) = uVar10;	// X pos
        uVar10 = FUN_8004cac8((int)sStack54 + -1,0x200);
        *(undefined4 *)(DAT_8008d9c4 + 0x48) = uVar10;	// Y pos
		
		// DAT_8008d9c8 = "hudr"
		// Convert X and Y pos
        uVar10 = FUN_8004caa8((int)(short)uStack56 + ((iVar15 >> 10) * 0x180000 >> 0x10) + 0x3a,
                              0x200);					  
        *(undefined4 *)(DAT_8008d9c8 + 0x44) = uVar10;
        uVar10 = FUN_8004cac8((int)sStack54,0x200);
        iVar15 = DAT_8008d9c8;
        *(undefined *)(DAT_8008d9c8 + 0x50) = 1;
		
		// DAT_8008d9d0 = "token"
        iVar14 = DAT_8008d9d0;
        *(undefined4 *)(iVar15 + 0x48) = uVar10;	// Y pos of "hudr"
		
		// Make token visible
        *(uint *)(iVar14 + 0x28) = *(uint *)(iVar14 + 0x28) & 0xffffff7f;
        uVar10 = FUN_8004caa8((short)uStack56 + iVar8,0x200);
        *(undefined4 *)(DAT_8008d9d0 + 0x44) = uVar10;	// X pos
        uVar10 = FUN_8004cac8((int)sStack54 + 0x18,0x200);
		
		// Still CTR Token, same pointer
		
        iVar15 = DAT_8008d9d0;
        bVar4 = 0x8c < (int)DAT_8008d52c;
        *(undefined4 *)(DAT_8008d9d0 + 0x48) = uVar10;	// Y pos
		
		// if time has passed, and token is not full scale
        if ((bVar4) && (*(short *)(iVar15 + 0x1c) < 0x2001)) 
		{
		  // vec3s
		  // make token grow on all 3 axis
          *(short *)(iVar15 + 0x1c) = *(short *)(iVar15 + 0x1c) + 0x200;
          *(short *)(iVar15 + 0x1e) = *(short *)(iVar15 + 0x1e) + 0x200;
          *(short *)(iVar15 + 0x20) = *(short *)(iVar15 + 0x20) + 0x200;
        }
		
		// frames since race ended
        if ((int)DAT_8008d52c < 0xe7) {
          if (0x8c < (int)DAT_8008d52c) 
		  {
			// interpolate fly-inn
            FUN_8004ecd4(&uStack56,0x264,0xa6,0x100,0xa6,DAT_8008d52c - 0x8c,8);
            
			iVar15 = (int)(short)uStack56;
            iVar14 = (int)sStack54;
            uVar10 = 0xffff8003;
            if ((*(uint *)(PTR_DAT_8008d2ac + 0x1cec) & 1) == 0) goto LAB_OVR1__8009ff58;
            goto LAB_OVR1__8009ff60;
          }
        }
        else 
		{
		  // interpolate fly-in
          FUN_8004ecd4(&uStack56,0x100,0xa6,0xffffff6a,0xa6,DAT_8008d52c - 0x32,8);
          
		  iVar15 = (int)(short)uStack56;
          iVar14 = (int)sStack54;
		  
		  // Flash colors depending on even or odd frame
		  
		  // odd frame
          if ((*(uint *)(PTR_DAT_8008d2ac + 0x1cec) & 1) == 0) {
LAB_OVR1__8009ff58:
            uVar10 = 0xffff8004;
          }
		  
		  // even frame
          else {
            uVar10 = 0xffff8003;
          }
		  
		  // DAT_8008d878 + 0x5bc
		  // CTR Token
		  
LAB_OVR1__8009ff60:
          FUN_80022878(*(undefined4 *)(DAT_8008d878 + 0x5bc),iVar15,iVar14,1,uVar10);
        }
        uStack48 = 0x78;
        iVar15 = 0xa0;
      }
      
	  // If you already have this CTR Token unlocked
	  else {
        if ((int)DAT_8008d52c < 0x12d) {
          iVar8 = (int)*(short *)(puVar13 + 0x90);
          iVar11 = (int)*(short *)(puVar13 + 0x92);
          uVar10 = 8;
          iVar9 = (int)(((uint)*(ushort *)(puVar13 + 0x90) + 0x10) * 0x10000) >> 0x10;
          iVar14 = (int)(((uint)*(ushort *)(puVar13 + 0x92) + 0x10) * 0x10000) >> 0x10;
          uVar5 = DAT_8008d52c;
        }
        else {
          iVar9 = -400;
          uVar10 = 10;
          iVar8 = (int)(((uint)*(ushort *)(puVar13 + 0x90) + 0x10) * 0x10000) >> 0x10;
          iVar11 = (int)(((uint)*(ushort *)(puVar13 + 0x92) + 0x10) * 0x10000) >> 0x10;
          iVar14 = iVar11;
          uVar5 = DAT_8008d52c - 300;
        }
		
		// interpolate fly-in
        FUN_8004ecd4(&uStack56,iVar8,iVar11,iVar9,iVar14,uVar5,uVar10);
        
		// DAT_8008d9cc = "hudc"
		// Convert X and Y pos
		uVar10 = FUN_8004caa8((int)(short)uStack56,0x200);
        *(undefined4 *)(DAT_8008d9cc + 0x44) = uVar10;	// x pos
        uVar10 = FUN_8004cac8((int)sStack54,0x200);
        *(undefined4 *)(DAT_8008d9cc + 0x48) = uVar10;	// y pos
		
		// DAT_8008d9c4 = "hudt"
		// Convert X and Y pos
        uVar10 = FUN_8004caa8((int)(short)uStack56 + 0x1d,0x200);
        *(undefined4 *)(DAT_8008d9c4 + 0x44) = uVar10;	// x pos
        uVar10 = FUN_8004cac8((int)sStack54 + -1,0x200);
        *(undefined4 *)(DAT_8008d9c4 + 0x48) = uVar10;	// y pos
		
		// DAT_8008d9c8 = "hudr"
		// Convert X and Y pos
        uVar10 = FUN_8004caa8((int)(short)uStack56 + 0x3a,0x200);
        *(undefined4 *)(DAT_8008d9c8 + 0x44) = uVar10;	// x pos
        uVar10 = FUN_8004cac8((int)sStack54,0x200);
        *(undefined4 *)(DAT_8008d9c8 + 0x48) = uVar10;	// y pos
      }
    }
	
	// If you did not collect all 3 letters (C, T, and R), or you lost the race
    else 
	{
	  // if race ended less than 30 seconds ago
      if ((int)DAT_8008d52c < 900) 
	  {
		// If hudc is visible, and if posY > -300
        if (((*(uint *)(DAT_8008d9cc + 0x28) & 0x80) == 0) && (-300 < *(int *)(DAT_8008d9cc + 0x48))
           ) 
		{
					// instance -> thread -> object
          iVar8 = *(int *)(*(int *)(DAT_8008d9cc + 0x6c) + 0x30);
		  
		  // move X position
          *(int *)(DAT_8008d9cc + 0x44) =
               *(int *)(DAT_8008d9cc + 0x44) + (int)*(short *)(iVar8 + 0x30);
		  
		  // make the letter fall off the screen
          *(int *)(iVar14 + 0x48) = *(int *)(iVar14 + 0x48) - (int)*(short *)(iVar8 + 0x32);
          
		  if (-0x14 < *(short *)(iVar8 + 0x32)) {
            *(short *)(iVar8 + 0x32) = *(short *)(iVar8 + 0x32) + -2;
          }
        }
		
        iVar14 = DAT_8008d9c4;
        
		// if hudt is visible, and if posY > -300 (with 6-frame delay)
		if ((((*(uint *)(DAT_8008d9c4 + 0x28) & 0x80) == 0) && (6 < (int)DAT_8008d52c)) &&
           (-300 < *(int *)(DAT_8008d9c4 + 0x48))) 
		{
					// instance -> thread -> object
          iVar8 = *(int *)(*(int *)(DAT_8008d9c4 + 0x6c) + 0x30);
		  
		  // move X position
          *(int *)(DAT_8008d9cc + 0x44) =
               *(int *)(DAT_8008d9cc + 0x44) + (int)*(short *)(iVar8 + 0x30);
		  
		  // make the letter fall off the screen
          *(int *)(iVar14 + 0x48) = *(int *)(iVar14 + 0x48) - (int)*(short *)(iVar8 + 0x32);
          
		  if (-0x14 < *(short *)(iVar8 + 0x32)) {
            *(short *)(iVar8 + 0x32) = *(short *)(iVar8 + 0x32) + -2;
          }
        }
		
        iVar14 = DAT_8008d9c8;
        
		// if 'hudr' is visible, and if posY > -300 (with 12-frame delay)
		if ((((*(uint *)(DAT_8008d9c8 + 0x28) & 0x80) == 0) && (0xc < (int)DAT_8008d52c)) &&
           (-300 < *(int *)(DAT_8008d9c8 + 0x48))) 
		{
					// instance -> thread -> object
          iVar8 = *(int *)(*(int *)(DAT_8008d9c8 + 0x6c) + 0x30);
		  
		  // move posX
          *(int *)(DAT_8008d9cc + 0x44) =
               *(int *)(DAT_8008d9cc + 0x44) + (int)*(short *)(iVar8 + 0x30);
			   
		  // make the letter fall off the screen
          *(int *)(iVar14 + 0x48) = *(int *)(iVar14 + 0x48) - (int)*(short *)(iVar8 + 0x32);
		  
          if (-0x14 < *(short *)(iVar8 + 0x32)) {
            *(short *)(iVar8 + 0x32) = *(short *)(iVar8 + 0x32) + -2;
          }
        }
      }
      
	  // you have now collected zero letters
	  *(undefined4 *)(iVar16 + 0x4cc) = 0;
    }
  }
  
  // The rest of the function happens regardless 
  // if you are in Adventure or Arcade 1P mode
  
  // loop counter
  iVar14 = 0;
  
  // if there are not zero players
  if (PTR_DAT_8008d2ac[0x1ca8] != '\0') {
    
	iVar8 = 0;
    
	// for iVar14 = 0; iVar14 < numPlyrCurrGame; iVar14++
	do 
	{
	  // Draw how much time it took to finish laps and race
      FUN_800a06f8(iVar8 >> 0x10,(int)(short)iVar15);
	  
	  // increment iteration counter
      iVar14 = iVar14 + 1;
	  
	  // pointless???
      iVar8 = iVar14 * 0x10000;
	  
    } while (iVar14 < (int)(uint)(byte)PTR_DAT_8008d2ac[0x1ca8]);
  }
  
  if (
		// If race ended more 1 second ago
		(0x1d < (int)DAT_8008d52c) && 
		
		// If there is one player
		(PTR_DAT_8008d2ac[0x1ca8] == '\x01')
	 ) 
  {
	// start counting time 1 second after race ends
    iVar14 = (DAT_8008d52c & 0xffff) - 0x1e;
    
	// get number of humans
	bVar2 = PTR_DAT_8008d2ac[0x1ca8];
	
	// get number of AIs
    bVar3 = PTR_DAT_8008d2ac[0x1cab];
	
	
    if (
		// Every 0.5 seconds or so
		(((iVar14 * 0x10000 >> 0x10) % 10 & 0xffffU) == 0) &&
		
		// DAT_8008d570 is the number of icons being 
		// drawn on the end-of-race menu in 1P mode
		
		// If you have not drawn all drivers yet
		((int)DAT_8008d570 < (int)((uint)bVar2 + (uint)bVar3))
		) 
	{
	  // add an icon to draw
      DAT_8008d570 = DAT_8008d570 + 1;
    }
	
	// loop counter
    iVar8 = 0;
    
	// if you are drawing any player icons
	if (0 < DAT_8008d570) 
	{
		
      iVar14 = (int)(short)iVar14;
      
	  // loop through all the driver icons
	  // for iVar8 = 0; iVar8 < numDrivers; iVar8++
	  do 
	  {  
        iVar11 = (uint)*(ushort *)(puVar6 + 0x184) +
                 (int)((int)*(short *)(puVar6 + 0x188) + ((uint)bVar2 + (uint)bVar3) * -0x38 + 0xc)
                 / 2 + iVar8 * 0x38;
				 
        if (300 - iVar15 < (int)DAT_8008d52c) {
          iVar9 = iVar11 * 0x10000 >> 0x10;
          iVar12 = -100;
          iVar11 = (DAT_8008d52c - 300) + iVar15;
        }
        else {
          iVar9 = 0x218;
          iVar12 = iVar11 * 0x10000 >> 0x10;
          iVar11 = iVar14;
        }
		
		// interpolate fly-in
        FUN_8004ecd4(&uStack56,iVar9,0x60,iVar12,0x60,iVar11,10);
        
		iVar14 = iVar14 + -10;
		
		// print a single character, a number 1-8,
        cRam8009f700 = (char)iVar8 + '1';
        FUN_80022878(0x8009f700,(int)(((uint)uStack56 + 0x20) * 0x10000) >> 0x10,0x5f,2,4);
        
		// Draw the driver's character icon
		FUN_8004e8d8(*(undefined4 *)
                      (PTR_DAT_8008d2ac +
                      (int)*(short *)(&DAT_80086d8c +
					  
									 // character ID array
                                     (int)(short)(&DAT_80086e84)
												
												 // order in which drivers finished the race
                                                 [*(byte *)(*(int *)(PTR_DAT_8008d2ac +
                                                                    iVar8 * 4 + 0x250c) + 
																	
																		// driver's index in ID array
																		0x4a)] *
											
										// index in array of icon pointers
                                     0x10) * 4 + 0x1eec),
					
					 (int)(short)uStack56,0x60,
					 
					 // pointer to PrimMem struct
                     *(int *)(PTR_DAT_8008d2ac + 0x10) + 0x74,
                     
					 // pointer to OT mem
					 *(undefined4 *)(PTR_DAT_8008d2ac + 0x147c),
					 
					 1,0x1000,0x808080);
        
		// increment iteration counter
		iVar8 = iVar8 + 1;
		
      } while (iVar8 < DAT_8008d570);
    }
  }
  
  if ((int)DAT_8008d52c < (int)((uint)uStack48 + 0x6e)) {
    return;
  }
 
  if (
		// If you are in Adventure cup
		((*(uint *)PTR_DAT_8008d2ac & 0x10000000) != 0) ||
     
		// If you are in Arcade or VS cup
		((*(uint *)(PTR_DAT_8008d2ac + 8) & 0x10) != 0)
	 ) {
    
	// if you are in 2P mode
	if (PTR_DAT_8008d2ac[0x1ca8] == '\x02') 
	{
	  // but text near middle of screen
      uVar10 = 100;
    }
	
	// if you are in 1P mode
    else 
	{
	  // put text near bottom of screen
      uVar10 = 0xbe;
    }
	
	// DAT_8008d878 + 0x324
	// PRESS * TO CONTINUE
    FUN_80022878(*(undefined4 *)(DAT_8008d878 + 0x324),0x100,uVar10,1,0xffff8000);
    
	// If you do not "Press X to continue"
	if ((DAT_8008d950 & 0x50) == 0) 
	{
	  // Quit the function
      return;
    }
	
	// If you are here, it means you pressed X to continue
	
	// clear gamepad input
    FUN_80046404();
	
    DAT_8008d4bc = 0;
    DAT_8008d52c = 0;
    DAT_8008d570 = 1;
	
	// Disable HUD
    PTR_DAT_8008d2ac[0x1d31] = PTR_DAT_8008d2ac[0x1d31] & 0xfe;
	
	// Enable Cup Standings
    PTR_DAT_8008d2ac[0x1d31] = PTR_DAT_8008d2ac[0x1d31] | 4;
    return;
  }
  
  // If you're in Arcade mode
  if ((*(uint *)PTR_DAT_8008d2ac & 0x400000) != 0) 
  {
	// if the menu is already drawing
    if ((DAT_8008d4bc & 1) != 0) 
	{
	  // dont make it draw twice
      return;
    }
	
	// If you are in 1P Arcade
    if (PTR_DAT_8008d2ac[0x1ca8] == '\x01') 
	{
	  // give pointer to end-of-race menu buffer,
	  // this one is near bottom of screen
      puVar6 = &DAT_OVR1__800a0b58;
    }
	
	// If you are in 2P Arcade
    else 
	{
	  // give pointer to end-of-race menu buffer,
	  // this one is near middle of screen
      puVar6 = &DAT_OVR1__800a0b84;
    }
	
	// pass the menu buffer pointer to the render
	// system, so it can draw the menu, both box and rows
    FUN_80046990(puVar6);
	
	// record that the menu is drawing
    DAT_8008d4bc = DAT_8008d4bc | 1;
    return;
  }
  
  // If you are not in CTR Token race
  if ((*(uint *)(PTR_DAT_8008d2ac + 8) & 8) == 0) 
  {
	// If you won the race
    if (*(short *)(iVar16 + 0x482) == 0) 
	{
LAB_OVR1__800a03b8:

	  // DAT_8008d878 + 0x324
	  // PRESS * TO CONTINUE
      FUN_80022878(*(undefined4 *)(DAT_8008d878 + 0x324),0x100,0xbe,1,0xffff8000);
	  
	  // If you have not pressed X
      if ((DAT_8008d950 & 0x50) == 0) 
	  {
		// Quit the function
        return;
      }
	  
	  // If you have pressed X to continue...
	  
	  // clear gamepad input
      FUN_80046404();
	  
      puVar6 = PTR_DAT_8008d2ac;
      DAT_8008d52c = 0;
      DAT_8008d570 = 1;
	  
	  // when loading is done, add flag for "In Adventure Arena"
      DAT_8008d100 = DAT_8008d100 | 0x100000;
	  
	  // If you are in boss mode
      if (*(int *)PTR_DAT_8008d2ac < 0) 
	  {
		// when loading is done, add flag for "spawn near boss door"
        DAT_8008d108 = DAT_8008d108 | 1;
       
		iVar15 = *(int *)(PTR_DAT_8008d2ac + 0x1eb8);
		
		// when loading is done, remove flag for Boss Mode
        DAT_8008d104 = DAT_8008d104 | 0x80000000;
        
		// If the number of keys you have is less than 4
		if (iVar15 < 4) 
		{
		  // bit offset 0x5e is where progress holds keys
			
		  // This checks if you've unlocked a key,
		  // by getting bit offset, converting that
		  // to integer offset, and remainder
          uVar5 = (&DAT_8008fba4)[(int)(iVar15 + 0x5eU) >> 5];
          uVar7 = iVar15 + 0x5eU & 0x1f;
		  
		  // If you dont have this key
          if ((uVar5 >> uVar7 & 1) == 0) 
		  {
			// Unlock the key
            (&DAT_8008fba4)[(int)(iVar15 + 0x5eU) >> 5] = uVar5 | 1 << uVar7;
			
			// Go to Podium after returning to Adventure Hub
            *(undefined2 *)(puVar6 + 0x2572) = 99;
          }
        }
		
		// If you have 4 keys (only here if you beat oxide)
        else 
		{
		  // Same bit location as keys, but right after
          uVar7 = (&DAT_8008fba4)[(int)(iVar15 + 0x5eU) >> 5];
          uVar5 = iVar15 + 0x5eU & 0x1f;
		  
		  // If you have not beaten Oxide yet
          if ((uVar7 >> uVar5 & 1) == 0) 
		  {
			// Record that you have now beaten Oxide
            (&DAT_8008fba4)[(int)(iVar15 + 0x5eU) >> 5] = uVar7 | 1 << uVar5;
			
			// goes to bits after purple gem, cause bossID is 5 or 6
            (&DAT_8008fba4)[(int)(*(int *)(puVar6 + 0x1eb8) + 0x6fU) >> 5] =
                 (&DAT_8008fba4)[(int)(*(int *)(puVar6 + 0x1eb8) + 0x6fU) >> 5] |
                 1 << (*(int *)(puVar6 + 0x1eb8) + 0x6fU & 0x1f);
          }
		  
		  // Go to podium, with no key (0x38 = empty)
          *(undefined2 *)(PTR_DAT_8008d2ac + 0x2572) = 0x38;
		  
          if ((DAT_8008fbb0 & 4) == 0) {
            DAT_8008fbb0 = DAT_8008fbb0 | 0x80004;
          }
        }
        if (
			// If Level ID is Hot Air Skyway
			(*(int *)(PTR_DAT_8008d2ac + 0x1a10) == 7) &&
		
			// If you are at podium after winning a Key
           (*(short *)(PTR_DAT_8008d2ac + 0x2572) == 99)
		   ) 
		{
		  // If you just beat Pinstripe
			
		  // Load gemstone valley
          FUN_8003cfc0(0x19);
          return;
        }
		
		// Load the levelID for Adventure Hub that you came from
        FUN_8003cfc0((int)*(short *)(PTR_DAT_8008d2ac + 0x1eb4));
        return;
      }
	  
	  // 6th bit of adventure profile is where trophies start
	  // These two lines get the bit index of the trophy for this track,
	  // then convert that to byte index (uvar7) and remainder (uVar5)
      uVar7 = (&DAT_8008fba4)[(int)(*(int *)(PTR_DAT_8008d2ac + 0x1a10) + 6U) >> 5];
      uVar5 = *(int *)(PTR_DAT_8008d2ac + 0x1a10) + 6U & 0x1f;
	  
	  // If this trophy has not been unlocked
      if ((uVar7 >> uVar5 & 1) == 0) 
	  {
		// Unlock the trophy
        (&DAT_8008fba4)[(int)(*(int *)(PTR_DAT_8008d2ac + 0x1a10) + 6U) >> 5] = uVar7 | 1 << uVar5;
        
		// Setting this makes you go to Podium cutscene
		// after you return to the adventure arena
		*(undefined2 *)(puVar6 + 0x2572) = 0x62;
      }
	  
	  // If you have collected 3 letters (C, T, and R)
      if (*(int *)(iVar16 + 0x4cc) == 3) 
	  {
		// 0x4c bit of adventure unlocks is where CTR Tokens start
		
		// This unlocks a CTR Token
        (&DAT_8008fba4)[(int)(*(int *)(PTR_DAT_8008d2ac + 0x1a10) + 0x4cU) >> 5] =
             (&DAT_8008fba4)[(int)(*(int *)(PTR_DAT_8008d2ac + 0x1a10) + 0x4cU) >> 5] |
             1 << (*(int *)(PTR_DAT_8008d2ac + 0x1a10) + 0x4cU & 0x1f);
      }
	  
	  // when loading is done, remove flag for CTR Challenge
      DAT_8008d10c = DAT_8008d10c | 8;
	  
	  // Load the levelID for Adventure Hub that you came from
      FUN_8003cfc0((int)*(short *)(PTR_DAT_8008d2ac + 0x1eb4));
      return;
    }
  }
  
  // If you are in CTR Token race
  else 
  {
	// If you won the race and you have all 3 C,T,R letters
    if ((*(short *)(iVar16 + 0x482) == 0) && (*(int *)(iVar16 + 0x4cc) == 3))
    goto LAB_OVR1__800a03b8;
  }
  
  if (
		// if the menu is not showing
		((DAT_8008d4bc & 1) == 0) &&
     
		// DAT_8008d878 + 0x324
		// PRESS * TO CONTINUE
		(FUN_80022878(*(undefined4 *)(DAT_8008d878 + 0x324),0x100,0xbe,1,0xffff8000),
		
		// If you "Press X to continue"
		(DAT_8008d950 & 0x50) != 0)) {
    
	// clear gamepad input
	FUN_80046404();
	
	// pass pointer to menu buffer that shows Retry / Exit To Map,
	// identical to buffer in 221 dll, except this one in EXE space
    FUN_80046990(&DAT_80086314);
	
	// record that the menu is now showing
    DAT_8008d4bc = DAT_8008d4bc | 1;
  }
  return;
}

// AA_EndEvent_DisplayTime
void FUN_800a06f8(ushort param_1,short param_2)
{
  // param_1 is driver index (0-7)
  // Player / AI structure + 0x4a
	
  short sVar1;
  short sVar2;
  int local_44;
  int iVar3;
  int iVar4;
  undefined *puVar5;
  int iVar6;
  undefined *puVar7;
  int iVar8;
  undefined4 uVar9;
  undefined4 local_40;
  undefined4 uVar10;
  undefined4 uVar11;
  short local_38;
  short local_36;
  short local_34;
  short local_32;
  short local_30;
  short local_2e;
  
  puVar5 = PTR_DAT_8008d2ac;
											// numPlyrCurrGame - 1
  puVar7 = (&PTR_DAT_8008625c)[(uint)(byte)PTR_DAT_8008d2ac[0x1ca8] - 1];
  
  // default size of box with 3 laps
  local_32 = 0x49;
  
  if (
		// if numLaps is not 7
		(PTR_DAT_8008d2ac[0x1d33] != '\a') && 
		(
			// size of box with 7 laps
			local_32 = 0x44, 
			
			// if number of laps is equal to 5
			PTR_DAT_8008d2ac[0x1d33] == '\x05'
		)
	) 
  {
	// size of box with 5 laps
    local_32 = 0x39;
  }
  
  // If this is player 2
  sVar2 = 0x41;
  iVar8 = 0x89;
  uVar9 = 0xc3;
  
  // If this is player 1
  if (param_1 == 0) {
    sVar2 = -0x3d;
    iVar8 = 9;
    uVar9 = 0x3e;
  }
  
  // *(PTR_DAT_8008d2ac + 0x24ec) is 9900C, pointer to first player structure
  // pointer to player structure, given param_1
  iVar6 = *(int *)(PTR_DAT_8008d2ac + ((int)((uint)param_1 << 0x10) >> 0xe) + 0x24ec);
  
  // increment counter for number of frames since the player ended the race
  local_44 = *(int *)(iVar6 + 0x4ec) + 1;
  *(int *)(iVar6 + 0x4ec) = local_44;
  
  if (
		(
			// if player ended race less than 110 frames ago
			(local_44 < 0x6e) && 
			
			// If you press Cross or Circle
			((DAT_8008d950 & 0x50) != 0)
		) && 
		
		// If numPlyrCurrGame is one
		(puVar5[0x1ca8] == '\x01')
	 ) 
  {
	// Assume race ended 110 frames ago
    *(undefined4 *)(iVar6 + 0x4ec) = 0x6e;
	
    DAT_8008d52c = 0x6e;
	
	// Number of drivers =   numPlyrCurrGame  +    number of AIs
    DAT_8008d570 = (ushort)(byte)puVar5[0x1ca8] + (ushort)(byte)puVar5[0x1cab];
	
	// clear gamepad input (for menus)
    FUN_80046404();
  }
  
  // What is param2???
  
  // Prior to 300 frames,
  // Big number, Lap times, and Icons are all on screen
  
  // After 300 frames
  // They are all gone
  
  // If race ended more than 300 frames ago
  if (300 - (int)param_2 < *(int *)(iVar6 + 0x4ec)) 
  { 
	// Convert X 
    sVar1 = FUN_8004caa8(0xffffff9c,(int)*(short *)(puVar7 + (int)(short)param_1 * 0xa0 + 0x14));
    
	iVar3 = -0xae;
    iVar4 = (int)sVar1;
    local_40 = 0xf;
    local_44 = *(int *)(iVar6 + 0x4ec) + -300 + (int)param_2;
    sVar1 = sVar2;
  }
  
  // If race ended less than 300 frames ago
  else 
  {  
    puVar5 = puVar7 + (int)(short)param_1 * 0xa0;
	
	// Convert X
    sVar1 = FUN_8004caa8((int)*(short *)(puVar5 + 0x10),(int)*(short *)(puVar5 + 0x14));
    
	iVar3 = (int)sVar1;
    
	// Convert Y
	sVar1 = FUN_8004cac8((int)*(short *)(puVar5 + 0x12),(int)*(short *)(puVar5 + 0x14));
    
	iVar4 = -0xae;
    local_44 = *(int *)(iVar6 + 0x4ec);
    local_40 = 0x1e;
  }
  
  // interpolate fly-in
  FUN_8004ecd4(&local_30,iVar3,(int)sVar1,iVar4,(int)sVar2,local_44,local_40);
  
  // Set X and Y position of Big Number
  *(int *)(*(int *)(iVar6 + 0x498) + 0x44) = (int)local_30;
  *(int *)(*(int *)(iVar6 + 0x498) + 0x48) = (int)local_2e;
  
  puVar7 = puVar7 + (int)(short)param_1 * 0xa0;
  
  // interpolate fly-in
  FUN_8004ecd4(&local_30,(int)*(short *)(puVar7 + 0x16),0,0x1e00,0,*(undefined4 *)(iVar6 + 0x4ec),
               0x1e);
  
  // Set scale of Big Number in HUD
  *(short *)(*(int *)(iVar6 + 0x498) + 0x1c) = local_30;
  *(short *)(*(int *)(iVar6 + 0x498) + 0x1e) = local_30;
  *(short *)(*(int *)(iVar6 + 0x498) + 0x20) = local_30;
  
  // If race ended more than 300 frames ago
  if (300 - (int)param_2 < *(int *)(iVar6 + 0x4ec)) {
    iVar4 = 0x78;
    local_40 = 0xffffffc4;
    uVar10 = 0xf;
    iVar3 = *(int *)(iVar6 + 0x4ec) + -300 + (int)param_2;
    local_44 = iVar8;
  }
  
  // If race ended less than 300 frames ago
  else {
    iVar4 = (int)*(short *)(puVar7 + 0x28);
    local_44 = (int)*(short *)(puVar7 + 0x2a);
    iVar3 = *(int *)(iVar6 + 0x4ec);
    local_40 = 0x78;
    uVar10 = 0x1e;
  }
  
  // interoplate fly-in
  FUN_8004ecd4(&local_30,iVar4,local_44,local_40,iVar8,iVar3,uVar10);
  
  // UI_DrawPosSuffix
  FUN_8005045c((int)local_30,(int)local_2e,iVar6,0);
  
  // If race ended more than 300 frames ago
  if (300 - (int)param_2 < *(int *)(iVar6 + 0x4ec)) {
    local_40 = 0x150;
    uVar10 = 0x27c;
    uVar11 = 0xf;
    iVar8 = *(int *)(iVar6 + 0x4ec) + -300 + (int)param_2;
  }
  
  // If race ended less than 300 frames ago
  else {
    local_40 = 0x218;
    uVar10 = 0x150;
    iVar8 = *(int *)(iVar6 + 0x4ec);
    uVar11 = 0x1e;
  }
  
  // interpolate fly-in or fly-out
  FUN_8004ecd4(&local_30,local_40,uVar9,uVar10,uVar9,iVar8,uVar11);
  
  // UI_DrawRaceClock
  FUN_8004edac((int)local_30,(int)local_2e,1,iVar6);
  
  // DAT_8008d878 + 0x310
  // "TOTAL"
  
  // DecalFont_GetLineWidth
  sVar2 = FUN_800224d0(*(undefined4 *)(DAT_8008d878 + 0x310),1);
  
  // calculate top left corner position
  local_38 = (local_30 - sVar2) + -6;
  local_36 = (local_2e - local_32) + 0xd;
  
  // DAT_8008d878 + 0x310
  // "TOTAL"
  
  // DecalFont_GetLineWidth
  local_34 = FUN_800224d0(*(undefined4 *)(DAT_8008d878 + 0x310),1);
  
  // calculate size of box
  local_34 = local_34 + 0x94;
  local_32 = local_32 + 6;
  
  // Draw 2D Menu rectangle background
  FUN_800457b0(&local_38,4,*(undefined4 *)(*(int *)(PTR_DAT_8008d2ac + 0x10) + 0xa0));
  return;
}

