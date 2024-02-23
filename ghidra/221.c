
// 221: 1/1

// CC_EndEvent_DrawMenu
void FUN_8009f710(void)
{
  bool bVar1;
  undefined *puVar2;
  undefined4 uVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  ushort uStack64;
  ushort uStack62;
  undefined4 uStack56;
  undefined4 uStack52;
  undefined4 uStack48;
  undefined2 uStack44;
  
  
  // pointer to player structure
  iVar5 = *(int *)(PTR_DAT_8008d2ac + 0x24ec);
  
  uStack56 = DAT_8009f700;
  uStack52 = DAT_8009f704;
  uStack48 = DAT_8009f708;
  uStack44 = DAT_8009f70c;
  
  // if you collected less crystals than the amount in the level
  bVar1 = (int)*(char *)(iVar5 + 0x31) < *(int *)(PTR_DAT_8008d2ac + 0x1e28);
  
  // if you lose crystal challenge
  if (bVar1) 
  {
	// TRY AGAIN
    iVar6 = 0x16c;
  }
  
  // if you win crystal challenge
  else 
  {
	// YOU WIN
    iVar6 = 0x16b;
  }
  
  // if it has been less than 900 frames 
  // since the end of the race
  if (DAT_8008d52c < 900) 
  {
	// increment frame number
    DAT_8008d52c = DAT_8008d52c + 1;
  }
  
  // Make HUD crystal invisible
  *(uint *)(DAT_8008d9bc + 0x28) = *(uint *)(DAT_8008d9bc + 0x28) | 0x80;
  
  // Fly in from left
  // StartX = 0xffffff9c = -0x63
  // EndX = 0x100
  // StartY = EndY = 0x18
  // Current frame: DAT_8008d52c
  // End on Frame: 0x14
  FUN_8004ecd4(&uStack64,0xffffff9c,0x18,0x100,0x18,DAT_8008d52c,0x14);
  
  // DAT_8008d878 + 0x5b4
  // TIME REMAINING
  FUN_80022878(*(undefined4 *)(DAT_8008d878 + 0x5b4),(int)(short)uStack64,(int)(short)uStack62,1,
               0xffff8000);
  
  // UI_DrawLimitClock
  FUN_8004f894((int)(((uint)uStack64 - 0x33) * 0x10000) >> 0x10,
               (int)(((uint)uStack62 + 0x11) * 0x10000) >> 0x10,1);
  
  // Fly in from right
  // StartX = 0x264
  // EndX = 0xcd
  // StartY = EndY = 0x56
  // Current frame: DAT_8008d52c
  // End on Frame: 0x14
  FUN_8004ecd4(&uStack64,0x264,0x56,0xcd,0x56,DAT_8008d52c,0x14);
  
  // Next variables are according to NOPing instructions
  
  // Convert X
  uVar3 = FUN_8004caa8((int)(short)uStack64,0x200);
  
  // Set X of crystal
  *(undefined4 *)(DAT_8008d9c0 + 0x44) = uVar3;
  
  // Do something with interpolated Y
  uVar3 = FUN_8004cac8((int)(short)uStack62,0x200);
  
  // Convert Y
  *(undefined4 *)(DAT_8008d9c0 + 0x48) = uVar3;
  
  
  // UI_DrawNumCrystal
  FUN_8005111c((int)(((uint)uStack64 + 0xf) * 0x10000) >> 0x10,
               (int)(((uint)uStack62 - 0x10) * 0x10000) >> 0x10,iVar5);
			   
  // Draw "You Win" or "Try Again"
  FUN_80022878(*(undefined4 *)(iVar6 * 4 + DAT_8008d878),
               (int)(((uint)uStack64 + 0x33) * 0x10000) >> 0x10,
               (int)(((uint)uStack62 + 8) * 0x10000) >> 0x10,1,0xffff8000);
			   
  if (
		// If you lost the challenge
		(bVar1) ||
		
		// If you already won the Crystal Challenge before
		(
			// flag where we see if this CTR Token is unlocked
			uVar4 = (int)*(short *)((int)&uStack56 + 
		
				// level ID - 18 = Battle Map ID (0-7)
				(*(int *)(PTR_DAT_8008d2ac + 0x1a10) + -0x12) * 2) + 0x6f, 
		
			// Check if this token has already been awarded previously
			((uint)(&DAT_8008fba4)[(int)uVar4 >> 5] >> (uVar4 & 0x1f) & 1) != 0
		)
	 ) 
  {
    
	// If you have not yet pressed X to continue
	if ((DAT_8008d4bc & 1) == 0) 
	{
	  // DAT_8008d878 + 0x324
	  // PRESS * TO CONTINUE
      FUN_80022878(*(undefined4 *)(DAT_8008d878 + 0x324),0x100,0xbe,1,0xffff8000);
	  
	  // If you tap Cross or Circle
      if ((DAT_8008d950 & 0x50) != 0) 
	  {
		// clear button input (for menus)
        FUN_80046404();
		
		// start drawing retry/exit menu,
		// with pointer to a buffer at the
		// end of 221 dll
        FUN_80046990(&DAT_8009fc00);
		
		// record that you have pressed X to continue
        DAT_8008d4bc = DAT_8008d4bc | 1;
      }
    }
  }
  
  // If you won the Crystal Challenge,
  // and you've never gotten the CTR Token
  else 
  {
	// Fly-in animation
    FUN_8004ecd4(&uStack64,0xffffff9c,0xa2,0x100,0xa2,DAT_8008d52c,0x14);
    
	// flash color, but it is broken,
	// because they checked == 0, even or odd
	
	// if timer is on frame zero (mistake)
	if (*(int *)(PTR_DAT_8008d2ac + 0x1cec) == 0) 
	{
      uVar3 = 0xffff8004;
    }
	
	// if timer is on an odd numbered frame
    else 
	{
      uVar3 = 0xffff8000;
    }
	
	// DAT_8008d878 + 0x5bc
	// CTR TOKEN AWARDED
	
	// Draw string with flashing text
    FUN_80022878(*(undefined4 *)(DAT_8008d878 + 0x5bc),(int)(short)uStack64,(int)(short)uStack62,1,
                 uVar3);
	
	// make CTR Token visible
    *(uint *)(DAT_8008d9d0 + 0x28) = *(uint *)(DAT_8008d9d0 + 0x28) & 0xffffff7f;
    
	// Convert X
	uVar3 = FUN_8004caa8((int)(short)uStack64,0x200);
	
	// Set X value of CTR Token
    *(undefined4 *)(DAT_8008d9d0 + 0x44) = uVar3;
	
	// Convert Y
    uVar3 = FUN_8004cac8((int)(short)uStack62 + -0x18,0x200);
	
	// Set Y value of CTR Token
    *(undefined4 *)(DAT_8008d9d0 + 0x48) = uVar3;
	
	// after exactly one second
    if (DAT_8008d52c == 0x1e) 
	{
	  // Play sound of unlocking token
      FUN_80028468(0x67,1);
    }
	
	// make a copy of pointer to CTR Token in HUD
    iVar5 = DAT_8008d9d0;
	
	// After the sound of unlocking token
    if (0x1e < DAT_8008d52c) 
	{
	  // Make token grow in size
	
	  // If token has not reached it's size yet
      if (*(short *)(DAT_8008d9d0 + 0x1c) < 0x2001) 
	  {
		// offset 0x1c is a vec3s for scale (x, y, z)
		  
		// Grow a little on each axis, each frame
        *(short *)(DAT_8008d9d0 + 0x1c) = *(short *)(DAT_8008d9d0 + 0x1c) + 0x200;
        *(short *)(iVar5 + 0x1e) = *(short *)(iVar5 + 0x1e) + 0x200;
        *(short *)(iVar5 + 0x20) = *(short *)(iVar5 + 0x20) + 0x200;
      }
    }
	
	// DAT_8008d878 + 0x324
	// PRESS * TO CONTINUE
    FUN_80022878(*(undefined4 *)(DAT_8008d878 + 0x324),0x100,0xbe,1,0xffff8000);
	
	// If you tap Cross or Circle
    if ((DAT_8008d950 & 0x50) != 0) 
	{
	  // clear button input (for menus)
      FUN_80046404();
	  
      puVar2 = PTR_DAT_8008d2ac;
	  
	  // Reset number of frames since race has finished
      DAT_8008d52c = 0;
	  
	  // when loading is done
	  // remove flag for Crystal Challenge
      DAT_8008d104 = DAT_8008d104 | 0x8000000;
	  
	  // flag where we see if this CTR Token is unlocked
      uVar4 = (int)*(short *)((int)&uStack56 + 
	  
				// level ID - 18 = Battle Map ID (0-7)
				(*(int *)(PTR_DAT_8008d2ac + 0x1a10) + -0x12) * 2) + 0x6f;
			  
	  // Record that you have unlocked this CTR Token
	  // 0x8fba4 is where the adventure profile (currently loaded) begins
      (&DAT_8008fba4)[(int)uVar4 >> 5] = (&DAT_8008fba4)[(int)uVar4 >> 5] | 1 << (uVar4 & 0x1f);
	  
	  // when loading is done
	  // add flag for In Adventure Arena
      DAT_8008d100 = DAT_8008d100 | 0x100000;
	  
	  // Load the levelID for Adventure Hub that you came from
      FUN_8003cfc0((int)*(short *)(puVar2 + 0x1eb4));
    }
  }
  return;
}


// This is the 0x40-byte buffer at 8009fc00

unsigned char x[0x40] = {

0x04 ,0x00, // string index "Retry"

0x00, 0x01, 0x00, 0x00, 

0x0d, 0x00, // string index "Exit To Map

0x00, 0x01, 0x01, 0x01,
	
// No clue what this is,
// could be part of hierarchy system
// that the main menu uses, to show
// "parent" selections
0xFF, 0xFF, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00,
 
// given to FUN_80046990
// Here is &DAT_8009fc00
// This all applies to the Retry/ExitToMap box

0xFF, 0xFF, // string index of title (null, with no row)
0x00, 0x01, // X position
0xB4, 0x00, // Y position
0x00, 0x00,
0x03,		// 0b11, 2 centers X, 1 centers Y, 0x80 for tiny text
0x08, 		// drawinig state, 0x10 means invisible
0x00, 0x00,

0xEC, 0xFB, 0x09, 0x80, // pointer to start of buffer
0x90, 0x5C, 0x05, 0x80, // function pointer
0x04, 0x00, // type of box, 0xF0 looks like load/save


0x00, 0x00, // Duplciate of X (0x01) value from before (set in RAM)
0x00, 0x00, // duplicate of Y (0xB4) value from before (set in RAM)
0x00, 0x00, // row index that you're highlighting (0 for retry, 1 for exit)

// the rest seems to have no impact
0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 


};