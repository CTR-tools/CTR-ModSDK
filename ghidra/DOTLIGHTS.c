
// called "DotLights" because of how the lights
// looked in early prototypes, up to Sep3 Beta

// DotLights_Video
// param1 gGT
// param2 bool lightOn1
// param3 bool lightOn2
// param4 bool lightOn3
// param5 bool lightOn4
// param6 posY
void FUN_8002406c(int param_1,int param_2,int param_3,int param_4,int param_5,int param_6)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;

  iVar6 = 0;

  // if num screens is not zero
  if (*(char *)(param_1 + 0x1ca8) != '\0')
  {
	// offset of 8008d2ac where pushBuffer info is stored,
	// position of each player's screen, with, height, etc
    iVar7 = 0x168;

	// for iVar6 = 0; iVar6 < numPlyrCurrGame; iVar6++
    do {

	  // pointer to pushBuffer info
      iVar5 = param_1 + iVar7;

	  // if nubmer of screens is less than 3
      if ((byte)PTR_DAT_8008d2ac[0x1ca8] < 3)
	  {
		// icon scale in 2P mode
        iVar4 = 0xaaa;

		// if numPlyrCurrGame is 1
		if (PTR_DAT_8008d2ac[0x1ca8] == 1)
		{
		  // icon scale in 1P mode
          iVar4 = 0x1000;
        }
      }

	  // if numPlyrCurrGame is 3 or 4
      else
	  {
		// icon scale in 3P/4P mode
        iVar4 = 0x800;
      }

	  // pointer to first traffic light icon
      iVar1 = *(int *)(param_1 + 0x1ecc);

	  // increment pointer to next pushBuffer struct
      iVar7 = iVar7 + 0x110;

	  // distance between each light,
	  // adjusted sizeX,
	  // (icon endX - icon startX) * scale / 0x1000
      iVar3 = (int)(((uint)*(byte *)(iVar1 + 0x18) - (uint)*(byte *)(iVar1 + 0x14)) * iVar4) >> 0xc;

	  // posX of first light
	  // (window sizeX/2) - (light sizeX*2)
	  iVar2 = ((int)*(short *)(iVar5 + 0x20) + iVar3 * -4) / 2;

	  // posY
	  iVar1 =
				// screen sizeY is used to scale original posY
				((((int)*(short *)(iVar5 + 0x22) / 3) * 0x10000 >> 0x10) * param_6 >> 0xc) -

			    // adjusted icon sizeY,
				(

					(int)(
							// icon bottomY - icon topY
							((uint)*(byte *)(iVar1 + 0x1d) - (uint)*(byte *)(iVar1 + 0x15))

							// scale / 0x1000
							* iVar4) >> 0xc
				);

	  // Draw first traffic light (red)
	  // DecalHUD_DrawPolyFT4
      FUN_80022db0(*(undefined4 *)(param_1 + param_2 * 4 + 0x1ecc),

				  // posX
				  iVar2,

				  // posY
				  iVar1,

				   // pointer to PrimMem struct
				   *(int *)(param_1 + 0x10) + 0x74,

				   // pointer to OT memory
				   *(undefined4 *)(iVar5 + 0xf4),

				   0,iVar4);

	  // Draw second traffic light (red)
	  // DecalHUD_DrawPolyFT4
      FUN_80022db0(*(undefined4 *)(param_1 + param_3 * 4 + 0x1ecc),

				  // posX
				  iVar2 + iVar3,

				  // posY
				  iVar1,

				   // pointer to PrimMem struct
				   *(int *)(param_1 + 0x10) + 0x74,

				   // pointer to OT memory
				   *(undefined4 *)(iVar5 + 0xf4),

				   0,iVar4);

	  // Draw third traffic light (red)
	  // DecalHUD_DrawPolyFT4
	  FUN_80022db0(*(undefined4 *)(param_1 + param_4 * 4 + 0x1ecc),

				  // posX
				  iVar2 + iVar3 * 2,

				  // posY
				  iVar1,

				   // pointer to PrimMem struct
				   *(int *)(param_1 + 0x10) + 0x74,

				   // pointer to OT memory
				   *(undefined4 *)(iVar5 + 0xf4),

				   0,iVar4);

	  // Draw fourth traffic light (green)
	  // DecalHUD_DrawPolyFT4
	  FUN_80022db0(*(undefined4 *)(param_1 + param_5 * 4 + 0x1ed4),

				  // posX
				  iVar2 + iVar3 * 3,

				  // posY
				  iVar1,

				   // pointer to PrimMem struct
				   *(int *)(param_1 + 0x10) + 0x74,

				   // pointer to OT memory
				   *(undefined4 *)(iVar5 + 0xf4),

				   0,iVar4);

	  // loop counter
	  iVar6 = iVar6 + 1;

    } while (iVar6 < (int)(uint)*(byte *)(param_1 + 0x1ca8));
  }
  return;
}


// DotLights_AudioAndVideo
// param_1 - gGT
void FUN_800242b8(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  int iVar5;
  undefined4 local_10;

  // time on traffic light counter
  iVar1 = *(int *)(PTR_DAT_8008d2ac + 0x1d0c);

  // if timer is negative, skip the whole function
  if (iVar1 < -0x3bf) goto LAB_8002444c;

  // if timer has ended
  if (iVar1 < 1)
  {
	// if previous frame's timer had not
	// ended, then this is the first frame
	// that the countdown timer is over
    if (0 < DAT_8008d014)
	{
	  // OtherFX_Play
	  // Play "green light" Sound
      FUN_80028468(0x46,0);
    }

	// green light on
	local_10 = 1;

	// use time on traffic light counter to transition
	// lights upward, add full second to treat negative as possitive
	iVar1 = (*(int *)(PTR_DAT_8008d2ac + 0x1d0c) + 0x3c0) * 0x1000;

	// iVar5 = -1 * iVar1 / 2
	iVar5 = (int)((ulonglong)((longlong)iVar1 * -0x77777777) >> 0x20);

	// three red lights on
    uVar2 = 1;
    uVar3 = 1;
    uVar4 = 1;

LAB_8002442c:
    iVar1 = (iVar5 + iVar1 >> 9) - (iVar1 >> 0x1f);
  }

  // if timer has not ended
  else
  {
	// if timer is less than 961ms (1 second)
    if (iVar1 < 0x3c1)
	{
	  // if previous frame's timer is more than 1 second
      if (0x3c0 < DAT_8008d014)
	  {
		// OtherFX_Play
		// Play "red light" Sound
        FUN_80028468(0x45,0);
      }

	  // three red lights on
      uVar2 = 1;
      uVar3 = 1;
      uVar4 = 1;

      iVar1 = 0x1000;

	  // green light off
	  local_10 = 0;
    }

	// if timer has more than 1 second
    else
	{
	  // if timer has less than 1921ms (2 seconds)
      if (iVar1 < 0x781)
	  {
		// if previous frame's timer is more than 2 seconds
        if (0x780 < DAT_8008d014)
		{
		  // OtherFX_Play
		  // Play "red light" Sound
          FUN_80028468(0x45,0);
        }

		// two red lights on
        uVar2 = 1;
        uVar3 = 1;

		// one red light off
        uVar4 = 0;

        iVar1 = 0x1000;

		// green light off
		local_10 = 0;
      }

	  // if timer has more than 2 seconds
	  else
	  {
		// if timer is more than 2880ms (3 seconds)
        if (0xb40 < iVar1) {

		  // green light is off
		  local_10 = 0;

		  // use time on traffic light counter to transition posY downward
          iVar1 = (0xf00 - *(int *)(PTR_DAT_8008d2ac + 0x1d0c)) * 0x1000;

		  // iVar5 = -1 * iVar1 / 2
		  iVar5 = (int)((ulonglong)((longlong)iVar1 * -0x77777777) >> 0x20);

		  // three red lights are off
          uVar2 = 0;
          uVar3 = 0;
          uVar4 = 0;

          goto LAB_8002442c;
        }

		// if previous frame's timer is more than 3 seconds
        if (0xb40 < DAT_8008d014)
		{
		  // OtherFX_Play
		  // Play "red light" Sound
          FUN_80028468(0x45,0);
        }

		// one red light on
        uVar2 = 1;

		// two red lights off
        uVar3 = 0;
        uVar4 = 0;

		// posY is top of screen
        iVar1 = 0x1000;

		// green light off
		local_10 = 0;
      }
    }
  }

  // draw all traffic lights on all screens
  FUN_8002406c(param_1,uVar2,uVar3,uVar4,local_10,iVar1);

LAB_8002444c:

  // keep record of previous frame's countdown timer
  DAT_8008d014 = *(undefined4 *)(param_1 + 0x1d0c);

  return;
}
