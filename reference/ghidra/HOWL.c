
// called "HOWL" for the confirmed names
// "howl_VolumeGet" and "howl_VolumeSet"

// CountSounds
uint FUN_8002843c(void)

{
  // watch it increase when scrolling in main menu

  DAT_8008d75c = DAT_8008d75c + 1;
  if (DAT_8008d75c == 0) {
    DAT_8008d75c = 1;
  }
  return (uint)DAT_8008d75c;
}


// Play sound from (not XA, kart hwl???)

// DCxDemo found most sounds
// https://discord.com/channels/527135227546435584/637616020177289236/927642939528740874

// Menu sounds
// 0x00 - Move up or down
// 0x01 - Go Forward
// 0x02 - Go Back
// 0x03 - Erase Character

// 0x04 - old weapon roulette sound, or old "erase character" sound from demo
// 0x05 - Can't "Go Forward", like entering 3P mode with 2 gamepads

// 0x06 - Crash into wall
// 0x07 - Land on ground after jump
// 0x08 - Jump
// 0x09 - Spring weapon sound
// 0x0A -
// 0x0B -
// 0x0C - N Gin Lab barrel hitting ground
// 0x0D - Boost sound
// 0x0E -
// 0x0F -
// 0x10 - driving while squished
// 0x11 - breaks
// 0x12 - drive while burn? or rain?
// 0x13
// 0x14 - driving on grass?
// 0x15 -
// 0x16 -
// 0x17 -
// 0x18 - driving on ???
// 0x19 -

// 0x1C - Garage_Select_Crash
// 0x1D - Garage_Select_Cortex
// 0x1E - Garage_Select_Tiny
// 0x1F - Garage_Select_Coco
// 0x20 - Garage_Select_NGin
// 0x21 - Garage_Select_Dingo
// 0x22 - Garage_Select_Polar
// 0x23 - Garage_Select_Pura

// 0x3b - bomb
// 0x3c - Break weapon box
// 0x3d - TNT Explosion
// 0x3e - TNT "honk"
// 0x3f - glass shattering
// 0x40 - relic race "tick" sound
// 0x41 - "ka-ching" get 10 wumpas
// 0x42 - Get one wumpa from crate
// 0x43 - Get one wumpa from ground
// 0x44 - Time clock weapon
// 0x45 - Red Light
// 0x46 - Green Light
// 0x47 - Bomb Shoot
// 0x48 - Bomb Move (also FX options menu sound)
// 0x49 - Bomb Death
// 0x4A - Missile Shoot
// 0x4B - Missile Move
// 0x4C - Missile Death
// 0x4D - Warpball Shoot
// 0x4E - Warpball Move
// 0x4F - Warpball Death
// 0x50 - Hit TNT "bounce"
// 0x51 - Hit TNT "bounce" -- old, unused
// 0x52 - Activate Potion weapon
// 0x53 - Activate Aku weapon
// 0x54 - Activate Uka weapon
// 0x55 - Falling "whistle" sound when aku grabs you
// 0x56 - Missile homing in
// 0x57 - Activate Shield weapon
// 0x58 - Green Shield fade away
// 0x59 - Shield shoot
// 0x5A - squished?
// 0x5B -
// 0x5C -
// 0x5D - Weapon Roulette shuffle
// 0x5E - Get Weapon "Ding"
// 0x5F - ??
// 0x60 - Activate Super Engine -- removed
// 0x61 - Activate Invisible
// 0x62 - Become Visible again
// 0x63 - Deduct time in Relic end-of-race
// 0x64 - Collect C, T, R, letters
// 0x65 - Menu transition "swoosh" sound
// 0x66 - Finish Lap
// 0x67 - Unlock Token
// 0x68 - FlameJet_SpitFire
// 0x69 - FlameJet_Burn

// 0x6a - MainMenu_CrashTrophySound_Extra
// 0x6b ???
// 0x6c

// 0x6d - plant grab
// 0x6e - plant chew	-- papu pyramid
// 0x6f - plant spit
// 0x70 - armadillo roll
// 0x71 - armadillo hit
// 0x72 - minecard railroad
// 0x73 - snowball roll
// 0x74 - barrel roll
// 0x75 - teeth opening

// 0x76 ???

// 0x77 - seal bark
// 0x78 - seal collide
// 0x79 - spider move up
// 0x7a - spider move down

// 0x7d - turtle splash

// 0x81 - fireball

// 0x93 - Sounds like exhaling, after key is shown and before doors open
// 0x94 - Open Hub doors
// 0x95 - Open Boss Garage Door
// 0x96 - open Oxide ship door
// 0x97 - Enter Warp Pad
// 0x98 - Warp Pad ambient noise
// 0x99 - Save/Load screen ambient noise
// 0x9A - "Boing boing" -- when adding to trophy counter
// 0x9B - MainMenu_CrashTrophySound0
// 0x9C - MainMenu_CrashTrophySound1
// 0x9D - MainMenu_CrashTrophySound2
// 0x9E - MainMenu_CrashTrophySound3
// 0x9F - MainMenu_CrashTrophySound4
// 0xA1 - MainMenu_CrashTrophySound5
// 0xA2 - MainMenu_CrashTrophySound6

// 0xD9 - Garage_Crash_Yoyo1
// 0xDA - Garage_Crash_Yoyo2
// 0xDB - Garage_Crash_Yoyo3
// 0xDC - Garage_Crash_Yoyo4
// 0xDD - Garage_Crash_Yoyo5

// 0xDE - Garage_Cortex_Computer

// 0xE0 - Garage_Tiny_0
// 0xE1 - Garage_Tiny_1
// 0xE2 - Garage_Tiny_2 (unused?)
// 0xE3 - Garage_Tiny_3
// 0xE4 - Garage_Tiny_4
// 0xE5 - Garage_Coco_Computer1
// 0xE6 - Garage_Coco_Computer2

// 0xE8 - Garage_NGin_???
// 0xE9 - Garage_NGin_HitMetal

// 0xEE - Garage_Dingo_Fire
// 0xEF - Garage_Polar_Bark

// 0xF2 - Garage_Pura_Walk1
// 0xF3 - Garage_Pura_Walk2
// 0xF4 - Garage_Pura_Walk3
// 0xF5 - Garage_Pura_Bird

// 0xF7 - ND_BOX_Sound0
// 0xF8 - ND_BOX_Sound1
// 0xF9 - ND_BOX_Sound2
// 0xFA - ND_BOX_Sound3
// 0xFB - ND_BOX_Sound4
// 0xFC - ND_BOX_Sound5
// 0xFD - ND_BOX_Sound6
// 0xFE - ND_BOX_Sound7
// 0xFF - ND_BOX_Sound8
// 0x100 - ADV_MASK_ENTER (whoosh)
// 0x101 - ADV_MASK_EXIT (poof)
// 0x102 - NUM_SOUNDS (no more, that's it)

// OtherFX_Play
// param1 - soundID
// param2:
// 0 - play with no duplicates (dont recycle old)
// 1 - play with no duplicates (recycle old)
// 2 - play with duplicates
void FUN_80028468(uint param_1,uint param_2)
{
  // OtherFX_Play_LowLevel
  // 0x00 - no echo
  // 0xff - volume
  // 0x80 - distortion (none)
  // 0x80 - LR (center of left and right)
  FUN_800284d0(param_1 & 0xffff,param_2 & 0xff,0xff8080);
  return;
}


// param_3:
// 0 - normal
// 1 - echo
// OtherFX_Play_Echo
void FUN_80028494(uint param_1,uint param_2,int param_3)

{
  undefined4 uVar1;

  // 0x00 - no echo
  // 0xff - volume
  // 0x80 - distortion (none)
  // 0x80 - LR (center of left and right)
  uVar1 = 0xff8080;

  // if echo (driver on echo quadblock)
  if (param_3 != 0)
  {
	// 0x01 - no echo
	// 0xff - volume
	// 0x80 - distortion (none)
	// 0x80 - LR (center of left and right)
    uVar1 = 0x1ff8080;
  }

  // OtherFX_Play_LowLevel
  FUN_800284d0(param_1 & 0xffff,param_2 & 0xff,uVar1);

  return;
}


// OtherFX_Play_LowLevel
undefined4 FUN_800284d0(uint param_1,byte param_2,uint param_3)

{
  undefined *puVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  byte *pbVar5;
  uint uVar6;
  uint uVar7;

  // // ChannelAttr (0x10)
  undefined auStack56 [10];
  ushort local_2e;

  // if audio is enabled
  if (DAT_8008d05c != '\0')
  {
	// cast to short
    uVar4 = param_1 & 0xffff;

	if (
			// if not out of bounds
			(uVar4 < *(uint *)(DAT_8008d7c0 + 0x14)) &&
			(
				// metaOtherFX
				// get pointer to cseq audio, given soundID from param1
				pbVar5 = (byte *)(DAT_8008d7d8 + uVar4 * 8),

				// howl_spuAddrs[otherFX->spuIndex] != 0
				*(short *)((uint)*(ushort *)(pbVar5 + 4) * 4 + DAT_8008d7dc) != 0
			)
		)
	{
	  // volume
      uVar7 = param_3 >> 0x10 & 0xff;

	  // distortion
      uVar6 = param_3 >> 8 & 0xff;

	  // howl_InitChannelAttr_OtherFX
      FUN_8002c424(

	    // metaOtherFX
		pbVar5,

		// &ChannelAttr
		auStack56,

		// volume
		uVar7,

		// Left/Right
		param_3 & 0xff,

		// distortion
		uVar6
	  );

	  // echo effect (0 or 1)
      local_2e = (ushort)(param_3 >> 0x18);

	  // enter critical section
      FUN_8002b4d0();

      if (
			// if play with duplicates
			(param_2 != 2) ||

			(
				// Channel_FindSound
				iVar2 = FUN_8002b5b4(uVar4),

				// if sound is not playing
				iVar2 == 0
			)
		  )
	  {
		// Channel_AllocSlot_AntiSpam
        iVar2 = FUN_8002b608(param_1 & 0xffff,(uint)param_2,0x7c,auStack56);

		// if free channel slot was found
		if (iVar2 != 0)
		{
          if ((*pbVar5 & 2) != 0) {
            *(byte *)(iVar2 + 8) = *(byte *)(iVar2 + 8) | 4;
          }

		  // type otherFX
		  *(undefined *)(iVar2 + 0xb) = 1;

          *(undefined *)(iVar2 + 0xc) = 0;

		  // echo effect (0 or 1)
          *(undefined *)(iVar2 + 0xe) = (char)(param_3 >> 0x18);

		  // volume
          *(undefined *)(iVar2 + 0xf) = (char)uVar7;

		  // distortion
          *(undefined *)(iVar2 + 0x10) = (char)uVar6;

		  // Left/Right
          *(undefined *)(iVar2 + 0x11) = (char)(param_3 & 0xff);

		  // duration
          *(undefined2 *)(iVar2 + 0x16) = *(undefined2 *)(pbVar5 + 6);

		  // CountSounds
          iVar3 = FUN_8002843c();

		  puVar1 = PTR_DAT_8008d2ac;

		  // soundID with CountSounds shifted in
          *(uint *)(iVar2 + 0x18) = iVar3 << 0x10 | param_1 & 0xffff;

		  // save the frame that the channel started, frameTimer_MainFrame_ResetDB
          *(undefined4 *)(iVar2 + 0x1c) = *(undefined4 *)(puVar1 + 0x1cf8);
        }

		// exit critical section
        FUN_8002b508();

		// soundID
        return *(undefined4 *)(iVar2 + 0x18);
      }

	  // exit critical section
      FUN_8002b508();
    }
  }
  return 0;
}


// OtherFX_Modify
undefined4 FUN_80028690(uint param_1,uint param_2)

{
  byte bVar1;
  undefined4 uVar2;
  int iVar3;
  byte *pbVar4;
  uint uVar5;
  uint uVar6;
  ushort uVar7;

  struct ChannelAttr channelAttr;

  if (
		// if audio is disabled
		(DAT_8008d05c == '\0') ||
		(*(uint *)(DAT_8008d7c0 + 0x14) <= (param_1 & 0xffff))
	 )
  {
	// return failure
    uVar2 = 0;
  }

  else {

	// metaOtherFX
	pbVar4 = (byte *)(DAT_8008d7d8 + (param_1 & 0xffff) * 8);

    uVar6 = param_2 >> 0x10 & 0xff;
    uVar5 = param_2 >> 8 & 0xff;

	// volume of FX
    bVar1 = DAT_8008d7ac;
    if ((*pbVar4 & 4) != 0)
	{
	  // volume of Voice
      bVar1 = DAT_8008d7bc;
    }
	
	// no distortion
    if (uVar5 == 0x80)
	{
	  // channelAttr offset 0x8
      channelAttr.pitch = *(undefined2 *)(pbVar4 + 2);
    }
	
	// distortion
    else
	{
	  // channelAttr offset 0x8
      channelAttr.pitch = (undefined2)
                 ((uint)*(ushort *)(pbVar4 + 2) * *(int *)(&DAT_800829ac + uVar5 * 4) >> 0x10);
    }

    uVar7 = (ushort)(param_2 >> 0x18);

	// channelAttr offset 0xA
	channelAttr.reverb = uVar7;

	// Channel_SetVolume
    FUN_8002b540(&channelAttr,(uint)bVar1 * (uint)pbVar4[1] * uVar6 >> 10,param_2 & 0xff);

	// channelAttr offset 0xA
	channelAttr.reverb = uVar7;

	// enter critical section
    FUN_8002b4d0();

	// Channel_SearchFX_EditAttr
	// 1 - otherFX
    iVar3 = FUN_8002b898(1,param_1,0x70,&channelAttr);

    if (iVar3 != 0)
	{
	  // echo
      *(undefined *)(iVar3 + 0xe) = (char)(param_2 >> 0x18);

	  // volume
      *(undefined *)(iVar3 + 0xf) = (char)uVar6;

	  // distortion
      *(undefined *)(iVar3 + 0x10) = (char)uVar5;

	  // left/right
      *(undefined *)(iVar3 + 0x11) = (char)(param_2 & 0xff);
    }

	// exit critical section
    FUN_8002b508();

    uVar2 = 1;
  }
  return uVar2;
}


// OtherFX_Stop1 (specific instance of sound)
void FUN_80028808(undefined4 param_1)

{
  // enter critical section
  FUN_8002b4d0();

  // Channel_SearchFX_Destroy
  // 1 - otherFX
  FUN_8002b9b8(1,param_1,0xffffffff);

  // exit critical section
  FUN_8002b508();

  return;
}


// OtherFX_Stop2 (all of this kind of sound)
void FUN_80028844(uint param_1)

{
  // enter critical section
  FUN_8002b4d0();

  // Channel_SearchFX_Destroy
  // 1 - otherFX
  FUN_8002b9b8(1,param_1 & 0xffff,0xffff);

  // exit critical section
  FUN_8002b508();

  return;
}


// EngineAudio_InitOnce
uint FUN_80028880(uint param_1,uint param_2)

{
  int iVar1;
  uint uVar2;
  uint uVar3;

  // ChannelAttr
  undefined auStack48 [10];
  ushort local_26;

  // if audio is enabled
  if (DAT_8008d05c != '\0') {
    param_1 = param_1 & 0xffff;

	if (param_1 < *(uint *)(DAT_8008d7c0 + 0x18))
	{
	  // metaEngineFX
      iVar1 = DAT_8008d7d0 + param_1 * 8;

	  // ChannelAttr->spuStartAddr = howl_spuAddrs[engineFX->spuIndex] << 3
      if (*(short *)((uint)*(ushort *)(iVar1 + 6) * 4 + DAT_8008d7dc) != 0)
	  {
		// distort
        uVar3 = param_2 >> 8 & 0xff;

		// volume
        uVar2 = param_2 >> 0x10 & 0xff;

		// param_2 & 0xff = LR

		// howl_InitChannelAttr_EngineFX
		// make ChannelAttr from howl pointer somehow
		FUN_8002c34c(iVar1,auStack48,uVar2,param_2 & 0xff,uVar3);

		local_26 = (ushort)(param_2 >> 0x18);

		// enter critical section
        FUN_8002b4d0();

		// Channel_AllocSlot
        iVar1 = FUN_8002b7d0(0x7c,auStack48);

		// if channel was found
        if (iVar1 != 0)
		{
		  // type = engineFX
          *(undefined *)(iVar1 + 0xb) = 0;

          *(undefined *)(iVar1 + 0xc) = 0;

		  // echo effect (0 or 1)
          *(undefined *)(iVar1 + 0xe) = (char)(param_2 >> 0x18);

		  // volume
          *(undefined *)(iVar1 + 0xf) = (char)uVar2;

		  // distortion
          *(undefined *)(iVar1 + 0x10) = (char)uVar3;

		  // Left/Right
          *(undefined *)(iVar1 + 0x11) = (char)(param_2 & 0xff);

		  // duration
          *(undefined2 *)(iVar1 + 0x16) = 0;

          *(uint *)(iVar1 + 0x18) = param_1;
          *(byte *)(iVar1 + 8) = *(byte *)(iVar1 + 8) | 4;
        }

		// exit critical section
        FUN_8002b508();

		return (uint)(iVar1 != 0);
      }
    }
  }
  return 0;
}


// EngineAudio_Recalculate
undefined4 FUN_800289b0(uint param_1,uint param_2)

{
  // 0x10 bytes here
  int iVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;

  // 0x10 bytes here
  struct ChanneAttr channelAttr;

  // if audio is disabled
  if (DAT_8008d05c == '\0') {
    return 0;
  }
  if (*(uint *)(DAT_8008d7c0 + 0x18) <= (param_1 & 0xffff)) {
    return 0;
  }

  uVar2 = param_2 >> 0x10 & 0xff;

  // metaEngineFX
  iVar3 = DAT_8008d7d0 + (param_1 & 0xffff) * 8;

  uVar4 = param_2 >> 8 & 0xff;

  // if numPlyrCurrGame is 2
  if (PTR_DAT_8008d2ac[0x1ca8] == 2) {
    iVar1 = uVar2 * 0x37;
  }

  // if numPlyrCurrGame is not 2
  else
  {
	// if numPlyrCurrGame is less than 3
	// which would only be for 1P mode
    if ((byte)PTR_DAT_8008d2ac[0x1ca8] < 3) goto LAB_80028a78;

	// this line \/ only happens in 3P or 4P
	// cause 1P will use GOTO on the line above ^^^
	iVar1 = uVar2 * 0x2d;
  }
  uVar2 = (uint)(iVar1 << 2) >> 8;
LAB_80028a78:

  // Channel_SetVolume
						// volume of FX
  FUN_8002b540(&channelAttr,(uint)DAT_8008d7ac * (uint)*(byte *)(iVar3 + 1) * uVar2 >> 10,
               param_2 & 0xff);

  if (uVar4 == 0x80)
  {
	// channelAttr->0x8
    channelAttr.pitch = *(undefined2 *)(iVar3 + 2);
  }

  else
  {
	// channelAttr->0x8
    channelAttr.pitch = (undefined2)
               ((uint)*(ushort *)(iVar3 + 2) * *(int *)(&DAT_800825ac + uVar4 * 4) >> 0x10);
  }

  // channelAttr->0xA
  channelAttr.reverb = (ushort)(param_2 >> 0x18);

  // enter critical section
  FUN_8002b4d0();

  // Channel_SearchFX_EditAttr
  // 0 - engineFX
  iVar3 = FUN_8002b898(0,param_1 & 0xffff,0x70,&channelAttr);

  // if slot found
  if (iVar3 != 0)
  {
	// echo
    *(undefined *)(iVar3 + 0xe) = (char)(param_2 >> 0x18);

	// volume
    *(undefined *)(iVar3 + 0xf) = (char)uVar2;

	// distortion
    *(undefined *)(iVar3 + 0x10) = (char)uVar4;

	// Left/Right
    *(undefined *)(iVar3 + 0x11) = (char)(param_2 & 0xff);
  }

  // exit critical section
  FUN_8002b508();

  return 1;
}


// EngineAudio_Stop
void FUN_80028b54(uint param_1)

{
  if (
		// if audio is enabled
		(DAT_8008d05c != '\0') &&
		((param_1 & 0xffff) < *(uint *)(DAT_8008d7c0 + 0x18))
	  )
  {
	// enter critical section
    FUN_8002b4d0();

	// Channel_SearchFX_Destroy
	// 0 - engineFX
    FUN_8002b9b8(0,param_1 & 0xffff,0xffffffff);

	// exit critical section
    FUN_8002b508();
  }
  return;
}



// Changes reverb mode
// DAT_8008d760 is currently set reverb mode. 5 disables reverb.
// reverb params: 0x80082548 - array[5] of SpuReverbAttr, 0x14 * 5 (refer sony spec in libref46.pdf)

// SpuReverbAttr[] reverbParams = new SpuReverbAttr[5] { ... } ;
// at address 80082548

// uint currentReverbMode = 5;
// at address DAT_8008d760

//void SetReverbMode(ushort newReverbMode)
void FUN_80028bbc(ushort param_1)
{
  int iVar1;

  // if newReverbMode < 5
  if (param_1 < 5)
  {
	// if currentReverbMode != newReverbMode
    if ((uint)DAT_8008d760 != (uint)param_1)
	{
	  // update reverb setting if mode has changed
      SpuSetReverbModeDepth(0,0);
      SpuSetReverb(1);
      iVar1 = (uint)param_1 * 0x14;

								// reverbParams[newReverbMode]
      SpuSetReverbModeParam((SpuReverbAttr *)(&DAT_80082548 + iVar1));

					// reverbParams[newReverbMode]->depth->left, reverbParams[newReverbMode]->depth->right
      SpuSetReverbModeDepth(*(short *)(&DAT_80082550 + iVar1),*(short *)(&DAT_80082552 + iVar1));

	  // currentReverbMode = newReverbMode;
	  DAT_8008d760 = param_1;
    }
  }

  // currentReverbMode != 5
  else if (DAT_8008d760 != 5)
  {
	// disable reverb and reset mode to 5
    SpuSetReverbModeDepth(0,0);
    SpuSetReverb(0);
    DAT_8008d760 = 5;
  }

  return;
}


// CseqMusic_Start
// param_1 - SongID (playing)
// param_2 - deltaBPM
// param_3 - 8008d068 for AdvHub
// param_4 - songSetActiveBits
// param_5 - boolLoopAtEnd
undefined4 FUN_80028c78(ushort param_1,undefined4 param_2,
			undefined4 param_3,undefined4 param_4,
            undefined4 param_5)

{
  int iVar1;
  byte *pbVar2;
  undefined4 uVar3;

  uVar3 = 0;

  // if audio is enabled
  if (DAT_8008d05c != '\0')
  {
    if (
			// ptrCseqHeader is invalid
			(DAT_8008d7b0 == 0) ||

			// sequence ID out of range
			(*(ushort *)(DAT_8008d7b0 + 6) <= param_1)
		)
	{
      uVar3 = 0;
    }

    else
	{
	  // enter critical section
      FUN_8002b4d0();

	  // loop counter
      iVar1 = 0;

	  // song pool
      pbVar2 = &DAT_80095d84;

	  // for iVar1 = 0; iVar1 < 2; iVar1++
      do
	  {
		// increment loop counter
        iVar1 = iVar1 + 1;

		// if song is not playing,
        if ((*pbVar2 & 1) == 0)
		{
		  // start song in this slot

		  // SongPool_Start
          FUN_8002a730(pbVar2,(uint)param_1,param_2,param_5,param_3,param_4);

		  // success
          uVar3 = 1;

          break;
        }
        pbVar2 = pbVar2 + 0x7c;
      } while (iVar1 < 2);

	  // exit critical section
      FUN_8002b508();
    }
  }
  return uVar3;
}


// CseqMusic_Pause
void FUN_80028d64(void)

{
  byte *pbVar1;
  int iVar2;

  if (
		// if audio is enabled
		(DAT_8008d05c != '\0') &&

		// ptrCseqHeader is valid
		(DAT_8008d7b0 != 0)
	 )
  {
	// enter critical section
    FUN_8002b4d0();

	// loop counter
    iVar2 = 0;
    pbVar1 = &DAT_80095d84;

	// for iVar2 = 0; iVar2 < 2; iVar2++
    do {
      if ((*pbVar1 & 1) != 0) {
        *pbVar1 = *pbVar1 | 2;
      }

	  // increment loop counter
	  iVar2 = iVar2 + 1;
      pbVar1 = pbVar1 + 0x7c;
    } while (iVar2 < 2);

	// exit critical section
    FUN_8002b508();
  }
  return;
}


// CseqMusic_Resume
void FUN_80028de0(void)

{
  byte *pbVar1;
  int iVar2;

  if (
		// if audio is enabled
		(DAT_8008d05c != '\0') &&

		// ptrCseqHeader is valid
		(DAT_8008d7b0 != 0)
	  )
  {
	// enter critical section
    FUN_8002b4d0();

	// loop counter
    iVar2 = 0;
    pbVar1 = &DAT_80095d84;

	// for iVar2 = 0; iVar2 < 2; iVar2++
    do {
      if ((*pbVar1 & 1) != 0) {
        *pbVar1 = *pbVar1 & 0xfd;
      }

	  // increment loop counter
      iVar2 = iVar2 + 1;
      pbVar1 = pbVar1 + 0x7c;
    } while (iVar2 < 2);

	// exit critical section
    FUN_8002b508();
  }
  return;
}


// CseqMusic_ChangeVolume
void FUN_80028e5c(ushort param_1,uint param_2,uint param_3)

{
  byte *pbVar1;
  int iVar2;

  if (
		(
			// if audio is enabled
			(DAT_8008d05c != '\0') &&

			// ptrCseqHeader is valid
			(DAT_8008d7b0 != 0)
		) &&

		// sequenceID is not out of range
		(param_1 < *(ushort *)(DAT_8008d7b0 + 6))
	 )
  {
	// loop counter
    iVar2 = 0;

	// enter critical section
    FUN_8002b4d0();

    pbVar1 = &DAT_80095d84;

	// for iVar2 = 0; iVar2 < 2; iVar2++
    do
	{
      if (
			// if song is playing
			((*pbVar1 & 1) != 0) &&

			// if this is the right song
			(*(ushort *)(pbVar1 + 2) == param_1)
		  )
	  {
		// SongPool_Volume
        FUN_8002a9d8(pbVar1,param_2 & 0xff,param_3 & 0xff,0);
      }

	  // increment loop counter
      iVar2 = iVar2 + 1;

      pbVar1 = pbVar1 + 0x7c;
    } while (iVar2 < 2);

	// exit critical section
    FUN_8002b508();
  }
  return;
}


// CseqMusic_Restart
void FUN_80028f34(ushort param_1,uint param_2)

{
  byte *pbVar1;
  int iVar2;

  if (
		(
			// if audio is enabled
			(DAT_8008d05c != '\0') &&

			// ptrCseqHeader is valid
			(DAT_8008d7b0 != 0)

		) &&

		// sequenceID is not out of range
		(param_1 < *(ushort *)(DAT_8008d7b0 + 6))
	  )
  {
	// loop counter
    iVar2 = 0;

	// enter critical section
    FUN_8002b4d0();

    pbVar1 = &DAT_80095d84;

	// for iVar2 = 0; iVar2 < 2; iVar2++
	do
	{
      if (
			// if song is playing
			((*pbVar1 & 1) != 0) &&

			// if this is the right song
			(*(ushort *)(pbVar1 + 2) == param_1)
		  )
	  {
		// flag for restart?
        *pbVar1 = *pbVar1 | 4;

		// SongPool_Volume,
		// fade from zero to desired volume (param_2)
        FUN_8002a9d8(pbVar1,0,param_2 & 0xff,0);
      }

	  // increment loop counter
      iVar2 = iVar2 + 1;
      pbVar1 = pbVar1 + 0x7c;
    } while (iVar2 < 2);

	// exit critical section
    FUN_8002b508();
  }
  return;
}


// CseqMusic_ChangeTempo
// param_1 song index to change
// param_2 tempo
void FUN_80029008(ushort param_1,undefined4 param_2)

{
  byte *pbVar1;
  int iVar2;

  // if audio is enabled
  if (DAT_8008d05c != '\0')
  {
    if (
			// ptrCseqHeader
			(DAT_8008d7b0 != 0) &&

			// sequence ID not out of range
			(param_1 < *(ushort *)(DAT_8008d7b0 + 6))
		)
	{

	  // loop counter
	  iVar2 = 0;

	  // enter critical section
      FUN_8002b4d0();

      pbVar1 = &DAT_80095d84;

	  // for iVar2 = 0; iVar2 < 2; iVar2++
	  do
	  {
        if (
				// if song is playing
				((*pbVar1 & 1) != 0) &&

				// if this is the song we want to change
				(*(ushort *)(pbVar1 + 2) == param_1)
			)
		{
		  // SongPool_ChangeTempo
          FUN_8002a6cc(pbVar1,param_2);
        }

		// increment loop counter
        iVar2 = iVar2 + 1;

        pbVar1 = pbVar1 + 0x7c;
      } while (iVar2 < 2);

	  // exit critical section
      FUN_8002b508();
    }
  }
  return;
}


// CseqMusic_AdvHubSwap
// param1 - songID
// param2 - songSet
// param3 - songSetActiveBits
void FUN_800290cc(ushort param_1,undefined4 param_2,undefined4 param_3)

{
  byte *pbVar1;
  int iVar2;

  // if audio is enabled
  if (DAT_8008d05c != '\0')
  {
    if (
			// ptrCseqHeader
			(DAT_8008d7b0 != 0) &&

			// sequenceID out of range
			(param_1 < *(ushort *)(DAT_8008d7b0 + 6))
		)
	{

	  // loop counter
      iVar2 = 0;

	  // enter critical section
      FUN_8002b4d0();

      pbVar1 = &DAT_80095d84;

	  // for iVar2 = 0; iVar2 < 2; iVar2++
      do {
        if (
				// if song is playing
				((*pbVar1 & 1) != 0) &&

				// if this song is the right song
				(*(ushort *)(pbVar1 + 2) == param_1)
			)
		{
		  // SongPool_AdvHub2
          FUN_8002aa44(pbVar1,param_2,param_3);
        }

		// increment loop counter
        iVar2 = iVar2 + 1;
        pbVar1 = pbVar1 + 0x7c;
      } while (iVar2 < 2);

	  // exit critical section
      FUN_8002b508();
    }
  }
  return;
}


// CseqMusic_Stop (one song)
void FUN_800291a0(ushort param_1)

{
  byte *pbVar1;
  int iVar2;

  // if audio is enabled
  if (DAT_8008d05c != '\0')
  {
    if (
			// ptrCseqHeader is valid
			(DAT_8008d7b0 != 0) &&

			// sequenceID not out of range
			(param_1 < *(ushort *)(DAT_8008d7b0 + 6))
		)
	{

	  // loop counter
      iVar2 = 0;

	  // enter critical section
      FUN_8002b4d0();

      pbVar1 = &DAT_80095d84;

	  // for iVar2 = 0; iVar2 < 2; iVar2++
	  do {
        if (
				// if song is playing
				((*pbVar1 & 1) != 0) &&

				// if song type matches parameter
				(*(ushort *)(pbVar1 + 2) == param_1)
			)
		{
		  // SongPool_StopAllCseq
          FUN_8002ac0c(pbVar1);
        }

		// increment loop counter
        iVar2 = iVar2 + 1;
        pbVar1 = pbVar1 + 0x7c;
      } while (iVar2 < 2);

	  // exit critical section
      FUN_8002b508();
    }
  }
  return;
}


// CseqMusic_StopAll (all songs)
void FUN_80029258(void)

{
  byte *pbVar1;
  int iVar2;

  if (
		// if audio is enabled
		(DAT_8008d05c != '\0') &&

		// if ptrCseqHeader
		(DAT_8008d7b0 != 0))
  {

	// loop counter
    iVar2 = 0;

	// enter critical section
    FUN_8002b4d0();

    pbVar1 = &DAT_80095d84;

	// for iVar2 = 0; iVar2 < 2; iVar2++
    do {

	  // if song is playing
      if ((*pbVar1 & 1) != 0)
	  {
		// SongPool_StopAllCseq
        FUN_8002ac0c(pbVar1);
      }

	  // increment loop counter
      iVar2 = iVar2 + 1;

      pbVar1 = pbVar1 + 0x7c;
    } while (iVar2 < 2);

	// exit critical section
    FUN_8002b508();
  }
  return;
}


// Bank_ResetAllocator
void FUN_800292e0(void)

{
  // set number of banks to zero
  DAT_8008d76c = 0;

  // set address
  DAT_8008d770 = 0x202;

  // Stage 4: Finished,
  // resets to stage 0 when Bank_Alloc is called
  DAT_8008d774 = 4;
  return;
}


// Bank_Alloc
// param1 - bankID
undefined4 FUN_800292fc(uint param_1,int param_2)

{
  undefined4 uVar1;

  // if audio is disabled
  if (DAT_8008d05c == '\0') {
    DAT_8008d774 = 4;
    uVar1 = 1;
  }

  // if audio is enabled
  else {
    DAT_8008d77c = (uint)((*(ushort *)(param_2 + 2) & 1) != 0);
    DAT_8008d778 = (uint)*(ushort *)((param_1 & 0xffff) * 2 + DAT_8008d7e4);
    DAT_8008d780 = param_2;

	// add a bookmark
    FUN_8003e978();

	// one iso sector is 0x800 bytes, same for all PS1 games,
	// all sample blocks are aligned to the size of an iso
	// sector, that's why 0x800 is always used for these blocks

	// MEMPACK_AllocMem
	// "SampleBlock" = "Bank"
    DAT_8008d788 = FUN_8003e874(0x800,"_LoadSampleBlock");

	// function works
	uVar1 = 1;

	// if allocation failed
	if (DAT_8008d788 == 0)
	{
	  // MEMPACK_PopState
      FUN_8003e9d0();

	  // function failed
      uVar1 = 0;
    }
    else {
      DAT_8008d774 = 0;
      DAT_8008d784 = DAT_8008d788;
    }
  }
  return uVar1;
}


// Bank_AssignSpuAddrs
// designed to be called over 40+ frames in a row,
// dividing a long job to prevent stutters in loading
uint FUN_800293b8(void)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  long lVar4;
  short *psVar5;
  ulong addr;

  // Stage 0: Load To RAM (first half)
  // Stage 1: Load To RAM (second half), and assign SpuEntry
  // Stage 2: Spu Transfer Start
  // Stage 3: Spu Transfer Complete
  // Stage 4: Finish


  // Stage 4: Finish
  if (DAT_8008d774 == 4) {
    uVar1 = 1;
  }
  else 
  {
	// bankLoadStage 1: load to RAM, and assign SpuEntry
    if (DAT_8008d774 == 1)
	{
	  // LOAD_HowlSectorChainEnd
      iVar2 = FUN_8003266c();
      if (iVar2 != 0)
	  {
		// reset audioAllocSize
        DAT_8008d764 = 0;

        iVar2 = 0;

		// sampleBlock->numSamples
        if (*DAT_8008d784 != 0)
		{
          iVar3 = 0;

		  // loop through all samples,
		  // recalculate audioAllocSize for all "loaded" samples
          do
		  {
			// index
            iVar2 = iVar2 + 1;

			// increment audioAllocSize by...
            DAT_8008d764 = DAT_8008d764 +

                           (uint)*(ushort *)

							  // howl_spuAddrs[sampleBlockHeader->spuIndexArr[iVar3]].size
							  (
								// sampleBlock->???->size?
								(uint)*(ushort *)((int)DAT_8008d784 + iVar3 + 2) * 4 +

								// howl_spuAddrs[ ^^^ ].size
								DAT_8008d7dc + 2
							  )

							  // correct bitshifted-byte-count to real-byte-count
							  * 8;

            // byte offset, short array
			iVar3 = iVar2 * 2;

          } while (iVar2 < (int)(uint)*DAT_8008d784);
        }
        
		if (DAT_8008d77c == 0) 
		{
		  // ptrLastBank.max
          *(undefined2 *)(DAT_8008d780 + 6) = (short)(DAT_8008d764 >> 3);
        }
        else 
		{
		  // ptrLastBank.max
          if (*(ushort *)(DAT_8008d780 + 6) < DAT_8008d764) {
            DAT_8008d774 = 4;
            return 1;
          }
        }
		
		// align up allocation
        DAT_8008d768 = DAT_8008d764 + 0x7ff >> 0xb;

		// MEMPACK_ReallocMem
        FUN_8003e94c((DAT_8008d764 + 0x7ff & 0xfffff800) + 0x800);

		// LOAD_HowlSectorChainStart
		// read new SampleBlock #2 to RAM
		// DAT_80095e7c is CdlFile for Kart.HWL,
		// DAT_8008d788+0x800 is the destination to load to
		// DAT_8008d778 is offset of HWL where bank is
		// DAT_8008d768 is numSectors to load
        iVar2 = FUN_80032594(&DAT_80095e7c,DAT_8008d788 + 0x800,DAT_8008d778 + 1,DAT_8008d768);

		if (iVar2 == 0) {
          return 0;
        }
        if (DAT_8008d77c == 0) {
          *(short *)(DAT_8008d780 + 4) = (short)DAT_8008d770;
        }
        else {
          DAT_8008d770._0_2_ = *(short *)(DAT_8008d780 + 4);
        }

		// howl_spuAddrs
        iVar2 = DAT_8008d7dc;

        iVar3 = 0;

		// === Assign SpuEntry for all "new" samples ===

		// if there are samples in the block
        if (*DAT_8008d784 != 0)
		{
		  // loop through all samples in the block
          do
		  {
			// howl_spuAddrs[sampleBlock->spuIndexArr[iVar3]]
            psVar5 = (short *)((uint)DAT_8008d784[iVar3 + 1] * 4 + iVar2);

			// if not specified
            if (*psVar5 == 0)
			{
			  // spuAddrs->spuAddr = alloc
              *psVar5 = (short)DAT_8008d770;
            }

			// index
			iVar3 = iVar3 + 1;

			// increment allocator by spuAddrs->size
            DAT_8008d770._0_2_ = (short)DAT_8008d770 + psVar5[1];

          } while (iVar3 < (int)(uint)*DAT_8008d784);
        }
        DAT_8008d774 = 2;
      }
    }
    else 
	{
      if (DAT_8008d774 < 2) {
        if (
				// Stage 0: Load to RAM
				(DAT_8008d774 == 0) &&
				(
					// LOAD_HowlSectorChainStart
					// read new SampleBlock #1 to RAM
					// DAT_80095e7c is CdlFile for Kart.HWL
					// DAT_8008d788 is the destination to load to
					// DAT_8008d778 is offset of HWL where bank is
					// load just 1 sector
					iVar2 = FUN_80032594(&DAT_80095e7c,DAT_8008d788,DAT_8008d778,1),

					iVar2 != 0
				)
			)
		{
		  // go to Stage 1
          DAT_8008d774 = 1;
        }
      }
      else 
	  {
		// Stage 2: Spu Transfer Start
        if (DAT_8008d774 == 2)
		{
		  // LOAD_HowlSectorChainEnd
          iVar2 = FUN_8003266c();
          if (iVar2 != 0) 
		  {
			// ptrLastBank->min
            addr = (uint)*(ushort *)(DAT_8008d780 + 4) * 8;

			// addr+audioAllocSize (start + size) < spu 512kb memory
            if (addr + DAT_8008d764 < 0x7e000) 
			{
			  // send RAM to SPU
              SpuSetTransferStartAddr(addr);
              SpuWrite((uchar *)(DAT_8008d788 + 0x800),DAT_8008d764);
            }
            DAT_8008d774 = 3;
          }
        }
        else 
		{
          if (
				// Stage 3: Spu Transfer Complete
				(DAT_8008d774 == 3) &&

				// (0) = SPU_TRANSFER_PEEK
				(lVar4 = SpuIsTransferCompleted(0), lVar4 != 0)
			 )
		  {
            if (DAT_8008d77c == 0)
			{
			  // increment spu allocator by size
              DAT_8008d770 = DAT_8008d770 + (DAT_8008d764 >> 3);
            }

			// bank -> flags
            *(ushort *)(DAT_8008d780 + 2) = *(ushort *)(DAT_8008d780 + 2) | 2;

			// MEMPACK_PopState
            FUN_8003e9d0();

            DAT_8008d774 = 4;
          }
        }
      }
    }
    uVar1 = (uint)(DAT_8008d774 == 4);
  }
  return uVar1;
}


// Bank_Destroy
// param_1 - pointer to last bank
void FUN_800296c4(int param_1)

{
  ushort uVar1;

  // if audio is enabled
  if (DAT_8008d05c != '\0')
  {
	// bank->flags
    uVar1 = *(ushort *)(param_1 + 2);

	// Bank_ClearInRange bank.min, bank.max
    FUN_80029730((uint)*(ushort *)(param_1 + 4),(uint)*(ushort *)(param_1 + 6));

    if ((uVar1 & 1) == 0)
	{
	  // move SPU allocator back to bank->min,
	  // this works cause Bank_Destroy is always used on "last" bank
      DAT_8008d770 = (uint)*(ushort *)(param_1 + 4);
    }

    *(ushort *)(param_1 + 2) = *(ushort *)(param_1 + 2) & 0xfffd;
  }
  return;
}


// Bank_ClearInRange
// param_1 start
// param_2 end
void FUN_80029730(ushort param_1,short param_2)

{
  int iVar1;
  ushort *puVar2;
  uint uVar3;

  // pointer howl header
  iVar1 = DAT_8008d7c0;

  uVar3 = 0;

  // howl_spuAddrs
  puVar2 = DAT_8008d7dc;

  // howlHeader->numSpuAddrs
  if (*(int *)(DAT_8008d7c0 + 0x10) != 0)
  {
	// loop through spu addresses,
    do
	{
      if (
			// if spuAddr > param_1
			(param_1 <= *puVar2) &&

			// if spuAddr < param_1+param_2
			(*puVar2 < (ushort)(param_1 + param_2))
		 )
	  {
		// SpuAddrEntry->spuAddr
        *puVar2 = 0;
      }

	  // next address
      uVar3 = uVar3 + 1;
      puVar2 = puVar2 + 2;

    } while (uVar3 < *(uint *)(iVar1 + 0x10));
  }
  return;
}


// Bank_Load
// param_1 - bankID
undefined4 FUN_800297a0(ushort param_1,byte *param_2)

{
  char cVar1;
  uint uVar2;
  int iVar3;

  if (
        (
                // if numAudioBanks < 8
                (DAT_8008d76c < 8) &&

                (
                    // numAudioBanks
                    uVar2 = (uint)DAT_8008d76c,

                    // bank[numBanks].bankID = param_1
                    *(ushort *)(&DAT_8008fc2c + uVar2 * 8) = param_1,

					// flags
                    (*(ushort *)(&DAT_8008fc2e + uVar2 * 8) & 3) == 0
                )
        ) &&

		// === Ghidra Fail ===
		// dont pass param_2, pass this: (&DAT_8008fc2c + uVar2 * 8),
		// ghidra misses it cause $a1 is set too early from the function call

		// Bank_Alloc
        (iVar3 = FUN_800292fc((uint)param_1, param_2), iVar3 != 0)
      )
  {
    // increment numAudioBanks
    cVar1 = DAT_8008d76c + 1;

    // set ID to bank
    *param_2 = DAT_8008d76c;

    // set new numAudioBanks
    DAT_8008d76c = cVar1;
    return 1;
  }
  return 0;
}


// Bank_DestroyLast
uint FUN_80029824(void)

{
  bool bVar1;

  // if numBanks is not zero
  bVar1 = DAT_8008d76c != 0;

  if (bVar1)
  {
    // decrease number
    DAT_8008d76c = DAT_8008d76c - 1;

	// Bank_Destroy
    FUN_800296c4(&DAT_8008fc2c + (uint)DAT_8008d76c * 8);
  }
  return (uint)bVar1;
}


// Bank_DestroyUntilIndex
void FUN_80029870(short param_1)

{
  // if numBanks is not zero
  if (DAT_8008d76c != 0) {

	// loop through all banks
	do
	{
	  // if bank is found
      if (*(short *)(&DAT_8008fc2c + ((uint)DAT_8008d76c - 1) * 8) == param_1)
	  {
		// quit
        return;
      }

	  // Bank_DestroyLast
      FUN_80029824();

    } while (DAT_8008d76c != 0);
  }
  return;
}


// Bank_DestroyAll
void FUN_800298e4(void)

{
  // if numBanks is not zero
  if (DAT_8008d76c != '\0') {

	// loop through all banks
	do
	{
	  // Bank_DestroyLast
      FUN_80029824();

    } while (DAT_8008d76c != '\0');
  }
  return;
}

// howl_InstrumentPitch(longSample->basePitch, note->pitchIndex, SongSeq->distort)
uint FUN_8002991c(int param_1,int param_2,uint param_3)

{
  uint uVar1;

  // param_3
  // (>> 0) & 0x40 - distortion
  // (>> 6) & 0xXX - pitch/octave?

  // noteFrequency
  uVar1 = (uint)*(ushort *)
			(&DAT_80082eac + (param_2 + ((int)param_3 >> 6) + -2) * 2) 
			* param_1 >> 0xc;

  if ((param_3 & 0x3f) != 0) 
  {
    uVar1 = (uVar1 & 0xffff) * ((uint)*(ushort *)(&DAT_80082f84 + (param_3 & 0x3f) * 2) + 0x100000)
            >> 0x14;
  }
  return uVar1 & 0xffff;
}


// howl_InitGlobals("\SOUNDS\KART.HWL;1")
uint FUN_80029988(undefined4 param_1)

{
  int iVar1;
  uint uVar2;

  // if audio is not enabled
  if (DAT_8008d05c == '\0')
  {
	// Set default volume for FX
    DAT_8008d7ac = 0xd7;

	// Set default volume for Music
    DAT_8008d7b8 = 0xaf;

	// Set default volume for Voice
    DAT_8008d7bc = 0xff;

	// OptionSlider_BoolPlay
    DAT_8008d794 = 0;
	
	// OptionSlider_Index
    DAT_8008d798 = 0;
	
	// OptionSlider_soundID
    DAT_8008d7a0 = 0;

	// Set Audio Mode to "Stereo" by default
    DAT_8008d7cc = 1;

	// enable the audio
    DAT_8008d05c = '\x01';

	// volume copy does not exist
    DAT_8008d79f = 0;

	// songLoadStage
    DAT_8008d7a4 = 3;

	// initialize Sound Processor,
	// with logging disabled (see function)
    SpuInit();

	// transfer by DMA
    SpuSetTransferMode(0);

	// Set Audio level for Left and Right speaker
    SpuSetCommonMasterVolume(0x3fff,0x3fff);

	// Turn Reverb off
    FUN_80028bbc(5);

    SpuSetCommonCDReverb(0);
    SpuSetCommonCDMix(1);
    SpuSetCommonCDVolume(0,0);

	// Voiceline_PoolInit
    FUN_8002c918();

	// Voiceline_SetDefaults
    FUN_8002d2b0();

	// howl_LoadHeader("\SOUNDS\KART.HWL;1")
    iVar1 = FUN_80029b2c(param_1);

    uVar2 = (uint)(iVar1 != 0);
  }

  // if audio is enabled
  else {
    uVar2 = 0;
  }
  return uVar2;
}


// howl_ParseHeader
void FUN_80029a50(int param_1)
{
    // metaOtherFX = ptrSpuAddrs + howlHeader->numSpuAddrs
    DAT_8008d7d8 = param_1 + 0x28 + *(int *)(param_1 + 0x10) * 4;

    // metaEngineFX = metaOtherFX + ...
    DAT_8008d7d0 = DAT_8008d7d8 + *(int *)(param_1 + 0x14) * 8;

    // howl_bankOffsets = metaEngineFX + ...
    DAT_8008d7e4 = DAT_8008d7d0 + *(int *)(param_1 + 0x18) * 8;

    // howl_songOffsets = howl_bankOffsets + howlHeader->cnt_banks * 2
    DAT_8008d7e0 = DAT_8008d7e4 + *(int *)(param_1 + 0x1c) * 2;

	// howl_header
    DAT_8008d7c0 = param_1;

    // howl_endOfHeader = howl_songOffsets + howlHeader->cnt_songs * 2
    DAT_8008d7d4 = DAT_8008d7e0 + *(int *)(param_1 + 0x20) * 2;

	// howl_spuAddrs = array of SPU addresses
    DAT_8008d7dc = param_1 + 0x28;

	return;
}




//parses CSEQ header
//howl_ParseCseqHeader
//param_1 - pointer to cseq
//https://github.com/CTR-tools/CTR-tools/blob/master/formats/txt_cseq.txt
void FUN_80029ab4(int param_1)

{
  /*
  //makes more sense to be moved here from the end:

  // ptrCseqHeader
  DAT_8008d7b0 = param_1;

  // ptrCseqLongSamples (instruments)
  // previous + sizeof(header)
  DAT_8008d7e8 = param_1 + 8;
  */

  // ptrCseqShortSamples (drums)
  // previous + numLongSamples * sizeof(longSample)
  DAT_8008d7c4 = param_1 + 8 + (uint)*(byte *)(param_1 + 4) * 0xc;

  // ptrCseqSongStartOffset
  //previous + numShortSamples * sizeof(shortSample)
  DAT_8008d7b4 = DAT_8008d7c4 + (uint)*(byte *)(param_1 + 5) * 8;

  // ptrCseqSongData
  //previous + numSongs * 2
  DAT_8008d7c8 = DAT_8008d7b4 + (uint)*(ushort *)(param_1 + 6) * 2;

  // align data up by 4
  if ((DAT_8008d7c8 & 1) != 0) DAT_8008d7c8 = DAT_8008d7c8 + 1;
  if ((DAT_8008d7c8 & 2) != 0) DAT_8008d7c8 = DAT_8008d7c8 + 2;

  //pointer to cseq start
  DAT_8008d7b0 = param_1;

  //pointer to long samples array (instruments)
  DAT_8008d7e8 = param_1 + 8;
  return;
}


// Loads howl header from disk
// param_1 is \SOUNDS\KART.HWL;1
// howl_LoadHeader
undefined4 FUN_80029b2c(undefined4 param_1)

{
  int iVar1;
  int *piVar2;
  int iVar3;

  // DAT_80095e7c is the first byte of Kart.HWL CdlFile
  // File \SOUNDS\KART.HWL;1 on disc and make CdlFile struct
  iVar1 = FUN_80032438(param_1,&DAT_80095e7c);

  // if kart.hwl was found
  if (iVar1 != 0) {

	// add a bookmark
    FUN_8003e978();

	// allocate single sector
	// MEMPACK_AllocMem
    piVar2 = (int *)FUN_8003e874(0x800,param_1);

    if (
			(
				(
					// if memory allocated successfully
					(piVar2 != (int *)0x0) &&
					(
						// load 1st sector of HWL to ram
						// Give CdlFile of Kart.HWL,
						// Give pointer of 0x800 allocation

						// LOAD_HowlHeaderSectors
						iVar1 = FUN_80032498(&DAT_80095e7c,piVar2,0,1),
						iVar1 != 0
					)
				) &&
				//if header reads "HOWL" magic value
				(*piVar2 == DAT_8008d060)

			//and this value is hardcoded, different in various releases
			) && (piVar2[1] == 0x80)
		)
	{
      //get size of howl header data
      iVar1 = piVar2[9];
	  
      // calculate number of sectors occupied by header
      iVar3 = iVar1 + 0x827 >> 0xb;

	  //reallocate for new size
	  // MEMPACK_ReallocMem
      FUN_8003e94c(iVar3 << 0xb);

      if (
        // if we only need 1 sector
			(iVar3 < 2) ||
			(
				// 0x200 is pointer incrementation, 0x200 * 4 is 0x800,
				// so it loads after the last byte of sector
				// asm - addiu      a1,s1,0x800

				// LOAD_HowlHeaderSectors
				iVar3 = FUN_80032498(&DAT_80095e7c,piVar2 + 0x200,1,iVar3 + -1),
				iVar3 != 0
			)
		  )
	  {
        // howl_ParseHeader
        FUN_80029a50(piVar2);

        // MEMPACK_ReallocMem for full howl header size
        FUN_8003e94c(iVar1 + 0x28);
        return 1;
      }
    }

    // if loading failed
	// MEMPACK_PopState
    FUN_8003e9d0();
  }
  return 0;
}


// howl_SetSong
undefined4 FUN_80029c40(uint param_1)

{
  // If audio is not enabled
  if (DAT_8008d05c == '\0') {
    //set loading state = done (don't load anything)
    DAT_8008d7a4 = 3;
  }

  // If audio is enabled
  else 
  {  
	// howl_ErasePtrCseqHeader,
	// song can not play anymore, loading next song
    FUN_80029dc0();
	
    //set loading state = 0 (start loading cseq)
    DAT_8008d7a4 = 0;

	// howl_songOffsets[songID]
    DAT_8008d7a8 = (uint)*(ushort *)((param_1 & 0xffff) * 2 + DAT_8008d7e0);
  }
  return 1;
}


//howl_LoadSong
uint FUN_80029ca4(void)

{
  //result var
  uint uVar1;

  //temp var that stores cd loading funcs results
  int iVar2;

  /*
  switch (DAT_8008d7a4)
  {
    case 0: load header from CD, return false;
	  case 1: load remaining data from CD, return false;
	  case (2, default): parse header, return false;
	  case 3: we're done, return true;
  }
  */

  //if we're done, return true
  if (DAT_8008d7a4 == 3) {
    uVar1 = 1;
  }
  else {
    //case state 1 - load cseq data (loads filesize / 0x800 - 1 sector)
    if (DAT_8008d7a4 == 1)
	{
	  // LOAD_HowlSectorChainEnd
      iVar2 = FUN_8003266c();
      if (
			(iVar2 != 0) &&
			(
				// LOAD_HowlSectorChainStart
				// DAT_80095e7c is CdlFile for Kart.HWL
				// DAT_8008d7a8 is sectorOffset
				iVar2 = FUN_80032594(&DAT_80095e7c,&DAT_80090d84,DAT_8008d7a8 + 1,
                               (DAT_80090584 + 0x7ffU >> 0xb) - 1),

				iVar2 != 0
			)
		 ) {
        DAT_8008d7a4 = 2;
      }
    }
    else {
      if (DAT_8008d7a4 < 2) {

	  	//case state 0 - load header from CD (1st sector)
        if (
				(DAT_8008d7a4 == 0) &&
				(
					// DAT_80095e7c is CdlFile for Kart.HWL
					// DAT_80090584 cseq data
					// DAT_8008d7a8 sectorOffset
					iVar2 = FUN_80032594(&DAT_80095e7c,&DAT_80090584,DAT_8008d7a8,1),

					iVar2 != 0
				)
			) {
          DAT_8008d7a4 = 1;
        }
      }
      else {

	    //case state = 2 - parse header
		//(or anything greater than 3, basically case default)
		// LOAD_HowlSectorChainEnd
        if ((DAT_8008d7a4 == 2) && (iVar2 = FUN_8003266c(), iVar2 != 0))
		{
		  // parse cseq header
          FUN_80029ab4(&DAT_80090584);

          DAT_8008d7a4 = 3;
        }
      }
    }

	//are we done loading?
    uVar1 = (uint)(DAT_8008d7a4 == 3);
  }
  return uVar1;
}



// howl_ErasePtrCseqHeader
void FUN_80029dc0(void)

{
  // sdata->ptrCseqHeader,
  // now song can't play anymore
  DAT_8008d7b0 = 0;
  return;
}

// howl_GetNextNote
// currNote, note->elapsedNoteLength
byte * FUN_80029dcc(byte *param_1,uint *param_2)

{
  byte bVar1;
  uint uVar2;
  byte *pbVar3;

  // SongNote offset 0x0
  uVar2 = (uint)*param_1;
  
  // loop until... what?
  pbVar3 = param_1 + 1;
  if ((*param_1 & 0x80) != 0)
  {
    uVar2 = uVar2 & 0x7f;
    do {
      bVar1 = *pbVar3;
      pbVar3 = pbVar3 + 1;
      uVar2 = uVar2 * 0x80 + ((uint)bVar1 & 0x7f);
    } while ((bVar1 & 0x80) != 0);
  }
  
  // update elapsedNoteLength
  *param_2 = uVar2;
  
  return pbVar3;
}

// exists, but empty, see array at 80083004
void cseq_opcode00()
{
	return;
}

// cseq_opcode01_noteoff
void FUN_80029e18(int param_1)

{
  int *piVar1;
  int *piVar2;
  int iVar3;

  // sequence->currNote
  iVar3 = *(int *)(param_1 + 0x18);

  // channel taken
  piVar1 = DAT_8009056c;

  // if channel slots are taken
  if (DAT_8009056c != (int *)0x0)
  {
	// loop through all slots
    do
	{

      piVar2 = (int *)*piVar1;

	  // if note is found that needs to be off
      if (
			(
				// channelStats->type == music
				(*(char *)((int)piVar1 + 0xb) == '\x02') &&

				// channelStats->soundID == sequence->soundID
				(piVar1[6] == (uint)*(byte *)(param_1 + 1))
			)
			&&
			
			// sequence->index == note->index
			(*(char *)((int)piVar1 + 0xd) == *(char *)(iVar3 + 1))
		  )
	 {
        // set channel to OFF
		(&DAT_8008fc6c)[*(byte *)((int)piVar1 + 9)] =
		(&DAT_8008fc6c)[*(byte *)((int)piVar1 + 9)] | 1;

		// remove "playing" flag
		(&DAT_8008fc6c)[*(byte *)((int)piVar1 + 9)] =
		(&DAT_8008fc6c)[*(byte *)((int)piVar1 + 9)] & 0xfffffffd;

		*(byte *)(piVar1 + 2) = *(byte *)(piVar1 + 2) & 0xfe;

		// recycle

		// LIST_RemoveMember taken
        FUN_800317e4(&DAT_8009056c,piVar1);

		// LIST_AddBack free
        FUN_80031788(&DAT_80090578,piVar1);
      }
      piVar1 = piVar2;
    } while (piVar2 != (int *)0x0);
  }
  return;
}

// exists, but empty, see array at 80083004
void cseq_opcode02()
{
	return;
}

// cseq_opcode03
void FUN_80029f24(byte *param_1)

{
  // if this is the last cseq in the song
  if ((*param_1 & 2) == 0)
  {
	// cseq offset 0xb = songPoolID

	// SongPool_StopAllCseq,
	// in the song, of the song pool, that this cseq belongs to
    FUN_8002ac0c(&DAT_80095d84 + (uint)param_1[0xb] * 0x7c);
  }

  else {
    *param_1 = *param_1 | 8;
  }
  return;
}

// exists, but empty, see array at 80083004
void cseq_opcode04()
{
	return;
}

// howl_InitChannelAttr_Music
// param1 - SongSeq
// param2 - ChannelAttr
// param3 - note->pitchIndex, or note->drumsIndex
// param4 - channel volume
void FUN_80029f80(byte *param_1,int *param_2,int param_3,int param_4)

{
  byte bVar1;
  ushort uVar2;
  undefined2 uVar3;
  int iVar4;
  uint uVar5;

  // songPoolIndex
  bVar1 = param_1[0xb];

  // instrument
  if ((*param_1 & 4) == 0)
  {
	// ptrCseqLongSamples[SongSeq->instrumentID]
    iVar4 = DAT_8008d7e8 + (uint)param_1[3] * 0xc;

	// howl_InstrumentPitch(longSample->basePitch, note->pitchIndex, SongSeq->distort)
	uVar3 = FUN_8002991c((uint)*(ushort *)(iVar4 + 4),param_3,(uint)param_1[8]);

	// volume of Music
    uVar5 = (uint)DAT_8008d7b8;

	// ChannelAttr->spuStartAddr = howl_spuAddrs[longSample->spuIndex] << 3
    *param_2 = (uint)*(ushort *)((uint)*(ushort *)(iVar4 + 6) * 4 + DAT_8008d7dc) << 3;

	// channelAttr->ADSR = sample->ADSR
	// https://en.wikipedia.org/wiki/Envelope_(music)
    *(undefined2 *)(param_2 + 1) = *(undefined2 *)(iVar4 + 8);
    *(undefined2 *)((int)param_2 + 6) = *(undefined2 *)(iVar4 + 10);

	// 80095D84 - song pool

	iVar4 = ((int)(

				// music volume (from options menu)
				uVar5 *

				// song[index].vol_curr
				(byte)(&DAT_80095d9c)[(uint)bVar1 * 0x7c] *

				// song seq volume
				(uint)param_1[5]

			) >> 10 )

			// instrument volume
			 * (uint)*(byte *)(iVar4 + 1);
  }
  
  // drums
  else
  {
	// drums sequence (0x8 each)
    iVar4 = DAT_8008d7c4 + param_3 * 8;

	// no distortion
    if (param_1[8] == 0x80)
	{
	  // drums -> pitch
      uVar3 = *(undefined2 *)(iVar4 + 2);
    }
	
	// distortion
    else
	{
	  // drums -> pitch ...

      uVar3 = (undefined2)
              ((uint)*(ushort *)(iVar4 + 2) * *(int *)(&DAT_800829ac + (uint)param_1[8] * 4) >> 0x10
              );
    }

	// ChannelAttr->spuStartAddr = howl_spuAddrs[shortSample->spuIndex] << 3
    uVar2 = *(ushort *)((uint)*(ushort *)(iVar4 + 4) * 4 + DAT_8008d7dc);

	// ADSR
    *(undefined2 *)(param_2 + 1) = 0x80ff;
    *(undefined2 *)((int)param_2 + 6) = 0x1fc2;

	// multiply 8
    *param_2 = (uint)uVar2 << 3;

    iVar4 = (
				(int)
				 (
					// volume of Music
					(uint)DAT_8008d7b8 *

					// song[index].vol_curr
					(uint)(byte)(&DAT_80095d9c)[(uint)bVar1 * 0x7c] *

					// song seq volume
					(uint)param_1[5]
				  ) >> 10)

				  // drums -> volume
				  * (uint)*(byte *)(iVar4 + 1);
  }

  // Channel_SetVolume
  FUN_8002b540(param_2,(uint)(iVar4 * param_4) >> 0xf,(uint)param_1[9]);

  // pitch
  // offset 0x8 (2*4 = 8)
  *(undefined2 *)(param_2 + 2) = uVar3;

  // reverb
  *(ushort *)((int)param_2 + 10) = (ushort)param_1[4];

  return;
}


// cseq_opcode_from06and07
// param1 - SongSeq
void FUN_8002a170(int param_1)

{
  int *piVar1;

  // channel taken
  piVar1 = DAT_8009056c;

  // if channel slots are taken
  if (DAT_8009056c != (int *)0x0)
  {
	// loop through all channel slots
    do
	{
	  // if channel is found
      if (
			// if channel type is 2 MUSIC
			(*(char *)((int)piVar1 + 0xb) == '\x02') &&

			// channelStats->soundID == SongSeq->soundID
			(piVar1[6] == (uint)*(byte *)(param_1 + 1))
		 )
	  {

		// modification of existing note?

		// Channel_SetVolume
		FUN_8002b540(&DAT_8008fccc + (uint)*(byte *)((int)piVar1 + 9) * 4,

					// volume of Music
                     (int)((uint)DAT_8008d7b8 *

							// volume of song (in song pool) that this opcode is from
                           (uint)(byte)(&DAT_80095d9c)[(uint)*(byte *)(param_1 + 0xb) * 0x7c] *

						   // songSeq->volume
                           (uint)*(byte *)(param_1 + 5) *

						   // channelStats->volume
						   (uint)*(byte *)((int)piVar1 + 0xf)) >> 0x12,

					(uint)*(byte *)(param_1 + 9));

		// update volume
		(&DAT_8008fc6c)[*(byte *)((int)piVar1 + 9)] =
        (&DAT_8008fc6c)[*(byte *)((int)piVar1 + 9)] | 0x40;
      }

	  // next slot
      piVar1 = (int *)*piVar1;

    } while (piVar1 != (int *)0x0);
  }
  return;
}

// cseq_opcode05_noteon
// param1 - SongSeq
void FUN_8002a28c(int param_1)

{
  undefined uVar1;
  int iVar2;
  int iVar3;
  undefined auStack32 [16];

  if (
		// gp->84c
		// 8008d7b8
		// if volume of music is on
		((cGp0000084c != '\0') && (*(char *)(param_1 + 5) != '\0')) &&

		// volume of song (in song pool) that this opcode is from, != 0
		((&DAT_80095d9c)[(uint)*(byte *)(param_1 + 0xb) * 0x7c] != '\0')
	 )
  {
	// sequence->currNote
    iVar3 = *(int *)(param_1 + 0x18);

	// howl_InitChannelAttr_Music
	FUN_80029f80(

			// SongSeq
			param_1,

			// ChannelAttr
			auStack32,

			// note->pitchIndex
			*(undefined *)(iVar3 + 1),

			// note->volume
			*(undefined *)(iVar3 + 2)
		);

	// Channel_AllocSlot,
	// returns ChannelStats struct
	iVar2 = FUN_8002b7d0(0x7c,auStack32);

	// if slot was found
    if (iVar2 != 0)
	{
      *(byte *)(iVar2 + 8) = *(byte *)(iVar2 + 8) | 0xe;
      uVar1 = *(undefined *)(param_1 + 2);

	  // set channel type to 2 MUSIC
      *(undefined *)(iVar2 + 0xb) = 2;

      *(undefined *)(iVar2 + 0xc) = 0;		// ???
      *(undefined *)(iVar2 + 10) = uVar1;	// ???

	  // echo
      *(undefined *)(iVar2 + 0xe) = *(undefined *)(param_1 + 4);

	  // volume
      *(undefined *)(iVar2 + 0xf) = *(undefined *)(iVar3 + 2);

	  // distortion
      *(undefined *)(iVar2 + 0x10) = *(undefined *)(param_1 + 8);

	  // LR
      *(undefined *)(iVar2 + 0x11) = *(undefined *)(param_1 + 9);

	  // shortSampleIndex (drums)
      uVar1 = *(undefined *)(iVar3 + 1);

	  // duration
      *(undefined2 *)(iVar2 + 0x16) = 0;

	  // shortSampleIndex (drums)
      *(undefined *)(iVar2 + 0xd) = uVar1;

	  // soundID (from OtherFX_play)
	  *(uint *)(iVar2 + 0x18) = (uint)*(byte *)(param_1 + 1);

      *(char *)(param_1 + 10) = *(char *)(param_1 + 10) + '\x01';
    }
  }
  return;
}

// cseq_opcode06
void FUN_8002a3a8(int param_1)

{
  // sequence->volume = note->volume
  *(undefined *)(param_1 + 5) = *(undefined *)(*(int *)(param_1 + 0x18) + 1);
  FUN_8002a170(param_1);
  return;
}

// cseq_opcode07
void FUN_8002a3d4(int param_1)

{
  // sequence->distort = note->distort
  *(undefined *)(param_1 + 9) = *(undefined *)(*(int *)(param_1 + 0x18) + 1);
  FUN_8002a170(param_1);
  return;
}

// cseq_opcode08
void FUN_8002a400(int param_1)

{
  int *piVar1;
  int iVar2;

  // sequence->currNote
  iVar2 = *(int *)(param_1 + 0x18);

  // channel taken
  piVar1 = DAT_8009056c;

  // if channel slots are taken
  if (DAT_8009056c != (int *)0x0)
  {
	// loop through channel slots
    do
	{
	  // if channel is found
      if (
			// if channel type is MUSIC
			(*(char *)((int)piVar1 + 0xb) == '\x02') &&

			(piVar1[6] == (uint)*(byte *)(param_1 + 1))
		 )
	 {
		// set reverb
		(&DAT_8008fcd6)[(uint)*(byte *)((int)piVar1 + 9) * 8] =
			(ushort)*(byte *)(iVar2 + 1);

		// change reverb
		(&DAT_8008fc6c)[*(byte *)((int)piVar1 + 9)] =
        (&DAT_8008fc6c)[*(byte *)((int)piVar1 + 9)] | 0x20;
      }

	  // next slot
      piVar1 = (int *)*piVar1;

    } while (piVar1 != (int *)0x0);
  }
  return;
}

// cseq_opcode09
void FUN_8002a494(int param_1)

{
  // SongSeq->instrumentID = SongSeq->currNote->instrumentID
  *(undefined *)(param_1 + 3) = *(undefined *)(*(int *)(param_1 + 0x18) + 1);
  return;
}


// cseq_opcode0a
void FUN_8002a4a8(byte *param_1)

{
  undefined2 uVar1;
  int iVar2;
  int *piVar3;

  // distortion
  param_1[8] = *(byte *)(*(int *)(param_1 + 0x18) + 1);

  // channel taken
  piVar3 = (int *)DAT_8009056c;

  // loop through all slots in use
  while (piVar3 != (int *)0x0)
  {
	// if channel is type MUSIC
    if ((*(char *)((int)piVar3 + 0xb) == '\x02') && (piVar3[6] == (uint)param_1[1]))
	{

	  if ((*param_1 & 4) == 0)
	  {
		// howl_InstrumentPitch
        uVar1 = FUN_8002991c(

			// SampleInstrument[seq->instrumentID].basePitch
			(uint)*(ushort *)(DAT_8008d7e8 + (uint)param_1[3] * 0xc + 4),

			// stats->pitchIndex
			(uint)*(byte *)((int)piVar3 + 0xd),

			// distortion
			(uint)param_1[8]
		);

		// 8008fccc is ChannelAttr

		// ChannelAttr[channel->ID].pitch = uVar1
		(&DAT_8008fcd4)[(uint)*(byte *)((int)piVar3 + 9) * 8] = uVar1;
      }

	  else
	  {
		// drum samples (0x8 bytes each)
        iVar2 = DAT_8008d7c4 + (uint)*(byte *)((int)piVar3 + 0xd) * 8;

		// no distortion
		if (param_1[8] == 0x80) 
		{
		  // ChannelAttr[channel->ID].pitch
          (&DAT_8008fcd4)[(uint)*(byte *)((int)piVar3 + 9) * 8] = *(undefined2 *)(iVar2 + 2);
        }
		
		// distortion
        else 
		{
		  // ChannelAttr[channel->ID].pitch
          (&DAT_8008fcd4)[(uint)*(byte *)((int)piVar3 + 9) * 8] =
               (short)((uint)*(ushort *)(iVar2 + 2) * *(int *)(&DAT_800829ac + (uint)param_1[8] * 4)
                      >> 0x10);
        }
      }

	  // update channel pitch
	  (&DAT_8008fc6c)[*(byte *)((int)piVar3 + 9)] =
      (&DAT_8008fc6c)[*(byte *)((int)piVar3 + 9)] | 0x10;
    }

	// next slot
	piVar3 = (int *)*piVar3;
  }
  return;
}


// SongPool_FindFreeChannel
byte * FUN_8002a63c(void)

{
  byte *pbVar1;
  int iVar2;

  // loop counter is zero
  iVar2 = 0;

  // song seqs
  pbVar1 = &DAT_800902cc;

  // for iVar2 = 0; iVar2 < 0x18 (24); iVar2++
  do
  {
	// increment loop counter
    iVar2 = iVar2 + 1;

	// if channel is not playing
    if ((*pbVar1 & 1) == 0)
	{
	  // return
      return pbVar1;
    }

	// next member
    pbVar1 = pbVar1 + 0x1c;

  } while (iVar2 < 0x18);
  return (byte *)0;
}


// SongPool_CalculateTempo
// const (dec)60, tpqn, bpm
uint FUN_8002a678(short param_1,short param_2,short param_3)
{
  if ((int)param_1 == 0) {
    trap(0x1c00);
  }

  return ((uint)((int)param_3 * (int)param_2) / 0x3c << 0x10) / (uint)(int)param_1;
}


// SongPool_ChangeTempo
// song, and tempo
void FUN_8002a6cc(int param_1,short param_2)

{
  undefined4 uVar1;

  // ptrCseqSongData[ptrCseqSongStartOffset[song->id]]
  param_2 = *(short *)(DAT_8008d7c8 +
                       (uint)*(ushort *)((uint)*(ushort *)(param_1 + 2) * 2 + DAT_8008d7b4) + 2) +
            param_2;

  // beats per minute (bpm)
  *(short *)(param_1 + 10) = param_2;

  // SongPool_CalculateTempo
  uVar1 = FUN_8002a678(0x3c,(int)*(short *)(param_1 + 8),(int)param_2);
  
  // new tempo
  *(undefined4 *)(param_1 + 0xc) = uVar1;
  
  return;
}


// SongPool_Start
// param_1 - songPool pointer
// param_2 - SongID (playing)
// param_3 - deltaBPM
// param_4 - boolLoopAtEnd
// param_5 - 8008D068 for AdvHub
// param_6 - songSetActiveBits
void FUN_8002a730(undefined *param_1,ushort param_2,short param_3,int param_4,uint *param_5,
                 undefined4 param_6)

{
  byte bVar1;
  undefined uVar2;
  undefined4 uVar3;
  byte *pbVar4;
  byte *pbVar5;
  int iVar6;
  ushort *puVar7;
  ushort *puVar8;
  int iVar9;

  // song->flags, now playing
  *param_1 = 1;

  // ptrCseqSongStartOffset
  iVar9 = DAT_8008d7b4;

  // song->id
  *(ushort *)(param_1 + 2) = param_2;

  // ptrCseqSongData[ptrCseqSongStartOffset[song->id]]
  iVar9 = DAT_8008d7c8 + (uint)*(ushort *)((uint)param_2 * 2 + iVar9);

  // if AdvHub
  if (param_5 != (uint *)0x0) {
    
	// CseqSongHeader->numSeqs
	if (*param_5 != (uint)*(byte *)(iVar9 + 1)) 
	{
      return;
    }
	
	// songSetActiveBits
    *(undefined4 *)(param_1 + 4) = param_6;
  }
  
  // iVar9 = CseqSongHeader
  
  // song->0x8 = iVar9->4 (tpqn)
  *(undefined2 *)(param_1 + 8) = *(undefined2 *)(iVar9 + 4);
  
  // song->0xA = iVar9->2 (bpm) + deltaBPM
  param_3 = *(short *)(iVar9 + 2) + param_3;
  *(short *)(param_1 + 10) = param_3;

  // SongPool_CalculateTempo
  uVar3 = FUN_8002a678(0x3c,(int)*(short *)(param_1 + 8),(int)param_3);
  *(undefined4 *)(param_1 + 0xc) = uVar3;

  // song->0x10, song->timeSpentPlaying
  *(undefined4 *)(param_1 + 0x10) = 0;
  *(undefined4 *)(param_1 + 0x14) = 0;

  if ((ushort)(param_2 - 1) < 2)
  {
	// full volume
    uVar2 = 0xff;
  }
  else
  {
	// partial volume
    uVar2 = 0xbe;
  }

  // song volume
  param_1[0x18] = uVar2;
  param_1[0x19] = uVar2;

  // if Level ID == Naughty Dog Box
  if (*(int *)(PTR_DAT_8008d2ac + 0x1a10) == 0x29)
  {
	// lower volume for ND Box Scene
    param_1[0x18] = 0xbe;
    param_1[0x19] = 0xbe;
  }

  // vol_StepRate
  param_1[0x1a] = 1;
  
  // numSequences
  param_1[0x1b] = 0;
  
  // &CseqSongHeader->seqOffsetArr[0]
  puVar8 = (ushort *)(iVar9 + 6);
  
  // &CseqSongHeader->seqOffsetArr[CseqSongHeader->numSeqs]
  puVar7 = puVar8 + *(byte *)(iVar9 + 1);
  
  // align up by 2
  if (((uint)puVar7 & 1) != 0) {
    puVar7 = (ushort *)((int)puVar7 + 1);
  }
  
  // align up by 4
  if (((uint)puVar7 & 2) != 0) {
    puVar7 = puVar7 + 1;
  }
  
  
  // puVar7 is now the first byte after
  // the seqOffsetArr, so all offsets are
  // relative to this address
  
  
  iVar6 = 0;
  
  // add new SongSeqs to song playing
  if (*(byte *)(iVar9 + 1) != 0) {
    do 
	{
	  // songNoteHeader = puVar7[CseqSongHeader->seqOffsetArr[iVar6]]
      pbVar5 = (byte *)((int)puVar7 + (uint)*puVar8);

	  // SongSeq* pbVar4 = SongPool_FindFreeChannel
      pbVar4 = (byte *)FUN_8002a63c();

	  // if a free channel was found
      if (pbVar4 != (byte *)0x0)
	  {
		// seq is now playing
        *pbVar4 = 1;
		
		// songNoteHeader->0x0
        if ((*pbVar5 & 1) != 0) 
		{
		  // seq now playing, and (instrument/drums)
          *pbVar4 = 5;
        }
        
		if (param_4 != 0) 
		{
		  // song loops at the end
          *pbVar4 = *pbVar4 | 2;
        }
        
		// songNoteHeader->0x1
		bVar1 = pbVar5[1];
        
		// instrumentID and reverb
		pbVar4[3] = 0;
        pbVar4[4] = 0;
		
        pbVar4[2] = bVar1;
		
		// volume
        if ((param_5 == (uint *)0x0) ||
           (((uint)*(byte *)(param_5[1] + iVar6) & *(uint *)(param_1 + 4)) != 0)) {
          pbVar4[5] = 0xff;
          pbVar4[6] = 0xff;
        }
		
		// volume
        else {
          pbVar4[5] = 0;
          pbVar4[6] = 0;
        }
		
        pbVar4[7] = 1;
		
		// distortion and LR
        pbVar4[8] = 0x80;
        pbVar4[9] = 0x80;
		
        pbVar4[10] = 0;
        
		// song->songPoolIndex
		bVar1 = param_1[1];
		
		// noteLength and elapsedNoteTime
        *(undefined4 *)(pbVar4 + 0xc) = 0;
        *(undefined4 *)(pbVar4 + 0x10) = 0;
		
		// void* firstNote = &SongNoteHeader->notes[0]
        *(byte **)(pbVar4 + 0x14) = pbVar5 + 2;
        
		// note->songPoolIndex
		pbVar4[0xb] = bVar1;

		// howl_GetNextNote
		// firstNote, note->elapsedNoteLength
        uVar3 = FUN_80029dcc(pbVar5 + 2,pbVar4 + 0xc);

		// void* currNote
		*(undefined4 *)(pbVar4 + 0x18) = uVar3;
		
		// save pointer to songSeq in songPool->CseqSequences
        *(byte **)(param_1 + (uint)(byte)param_1[0x1b] * 4 + 0x1c) = pbVar4;
		
		// increment number of sequences playing
        param_1[0x1b] = param_1[0x1b] + '\x01';
      }
      iVar6 = iVar6 + 1;
      puVar8 = puVar8 + 1;
    } while (iVar6 < (int)(uint)*(byte *)(iVar9 + 1));
  }
  return;
}


// SongPool_Volume
void FUN_8002a9d8(int param_1,undefined param_2,undefined param_3,int param_4)

{
  // never?
  if (param_4 != 0) 
  {
	// change curr volume "immediately" without fade
    *(undefined *)(param_1 + 0x18) = param_2;
  }

  // desired volume
  *(undefined *)(param_1 + 0x19) = param_2;
  
  // stepRate
  *(undefined *)(param_1 + 0x1a) = param_3;
  
  return;
}


// SongPool_AdvHub1
// param1 - song pool member
// param2 - cseqID
// param3 - volume of cseq
// param4 - boolImm
void FUN_8002a9f0(int param_1,int param_2,undefined param_3,int param_4)

{
  int iVar1;

  // ptrCseqSongData[ptrCseqSongStartOffset[song->id]] -> numSeqs
  if (param_2 < (int)(uint)*(byte *)(DAT_8008d7c8 +
                                     (uint)*(ushort *)
                                            ((uint)*(ushort *)(param_1 + 2) * 2 + DAT_8008d7b4) + 1)
     )
  {
	// SongPool[song].cseq[id]
    iVar1 = *(int *)(param_1 + param_2 * 4 + 0x1c);

	// never?
	if (param_4 != 0)
	{
	  // vol_Curr
      *(undefined *)(iVar1 + 5) = param_3;
    }

	// vol_New
    *(undefined *)(iVar1 + 6) = param_3;
  }
  return;
}


// SongPool_AdvHub2
// param1 - Song* member
// param2 - songSet
// param3 - songSetActiveBits
void FUN_8002aa44(int param_1,uint *param_2,undefined4 param_3)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;

  // ptrCseqSongData[ptrCseqSongStartOffset[song->id]]
  iVar3 = DAT_8008d7c8 + (uint)*(ushort *)((uint)*(ushort *)(param_1 + 2) * 2 + DAT_8008d7b4);

  if (param_2 != (uint *)0x0) 
  {
	// if(songSet->numSeqs != csh->numSeqs)
    if (*param_2 != (uint)*(byte *)(iVar3 + 1)) {
      return;
    }
	
	// song->songSetActiveBits = songSetActiveBits;
    *(undefined4 *)(param_1 + 4) = param_3;
  }
  iVar2 = 0;

  // if csh->numSeqs != 0
  if (*(char *)(iVar3 + 1) != '\0')
  {
	// loop through all Cseq music on all adv hub tracks
    do {

	  // if this cseq does not belong to the hub
	  if (((uint)*(byte *)(param_2[1] + iVar2) & *(uint *)(param_1 + 4)) == 0) {

		// volume = 0
		uVar1 = 0;
      }

	  // if this cseq belongs to this hub
      else
	  {
		// play it
        uVar1 = 0xff;
      }

	  // SongPool_AdvHub1
	  FUN_8002a9f0(param_1,iVar2,uVar1,0);

	  // next cseq in array
      iVar2 = iVar2 + 1;

    } while (iVar2 < (int)(uint)*(byte *)(iVar3 + 1));
  }
  return;
}


// SongPool_StopCseq
void FUN_8002ab18(byte *param_1)

{
  int *piVar1;
  int *piVar2;

  // channel taken
  piVar1 = DAT_8009056c;

  // if channel are taken
  if (DAT_8009056c != (int *)0x0)
  {
	// loop through all taken
    do {
      piVar2 = (int *)*piVar1;

	  // all channels type (2) MUSIC
      if ((*(char *)((int)piVar1 + 0xb) == '\x02') && (piVar1[6] == (uint)param_1[1]))
	  {
		// set channel to OFF
		(&DAT_8008fc6c)[*(byte *)((int)piVar1 + 9)] =
		(&DAT_8008fc6c)[*(byte *)((int)piVar1 + 9)] | 1;

		// remove "playing" flag
        (&DAT_8008fc6c)[*(byte *)((int)piVar1 + 9)] =
        (&DAT_8008fc6c)[*(byte *)((int)piVar1 + 9)] & 0xfffffffd;

		*(byte *)(piVar1 + 2) = *(byte *)(piVar1 + 2) & 0xfe;

		// LIST_RemoveMember taken
        FUN_800317e4(&DAT_8009056c,piVar1);

		// LIST_AddBack free
        FUN_80031788(&DAT_80090578,piVar1);
      }
      piVar1 = piVar2;
    } while (piVar2 != (int *)0x0);
  }
  *param_1 = *param_1 & 0xfe;
  return;
}


// SongPool_StopAllCseq
void FUN_8002ac0c(byte *param_1)

{
  int iVar1;
  byte *pbVar2;

  // if song is playing
  if ((*param_1 & 1) != 0)
  {
    iVar1 = 0;
    pbVar2 = param_1;

	// if there are sequences in the song
	if (param_1[0x1b] != 0)
	{
	  // stop all cseq sequences in song
      do
	  {
		// SongPool_StopCseq
        FUN_8002ab18(*(undefined4 *)(pbVar2 + 0x1c));

        iVar1 = iVar1 + 1;
        pbVar2 = pbVar2 + 4;
      } while (iVar1 < (int)(uint)param_1[0x1b]);
    }

	// stop playing song
    *param_1 = *param_1 & 0xfe;
  }
  return;
}


// howl_Disable
undefined4 FUN_8002ac94(void)

{
  // If audio is enabled
  if (DAT_8008d05c != '\0')
  {
	// Disable the audio
    DAT_8008d05c = 0;
    return 1;
  }
  return 0;
}


// UpdateChannelVol_EngineFX
// EngineFX*, ChannelAttr*, vol, LR
void FUN_8002acb8(int param_1,undefined4 param_2,int param_3,undefined4 param_4)

{
  // Channel_SetVolume
  FUN_8002b540(
	
	// channelAttr
	param_2,

	// volume of FX
	(uint)DAT_8008d7ac *
	
		// engineFX->vol
		(uint)*(byte *)(param_1 + 1) *
		
		// vol
		param_3 >> 10,

		// LR
		param_4);
		
  return;
}


// UpdateChannelVol_OtherFX
// param_1 - OtherFX*
// param_2 - ChannelAttr*
// param_3 - volume
// param_4 - LR
void FUN_8002ad04(byte *param_1,undefined4 param_2,int param_3,undefined4 param_4)

{
  byte bVar1;

  // volume of FX
  bVar1 = DAT_8008d7ac;

  if ((*param_1 & 4) != 0)
  {
	// volume of Voice
    bVar1 = DAT_8008d7bc;
  }

  // Channel_SetVolume
  FUN_8002b540(param_2,(uint)bVar1 * (uint)param_1[1] * param_3 >> 10,param_4);
  return;
}


// UpdateChannelVol_Music
// SongSeq* ChanneAttr* vol LR
void FUN_8002ad70(byte *param_1,undefined4 param_2,int param_3,int param_4)

{
  byte bVar1;
  int iVar2;

  if ((*param_1 & 4) == 0)
  {
			// volume of Music *
    iVar2 = (uint)DAT_8008d7b8 *

			// songPool[param1->songID].vol_curr *
			(uint)(byte)(&DAT_80095d9c)[(uint)param_1[0xb] * 0x7c] *

            (uint)param_1[5];

	// pointer to instrument samples (0xc each)
    bVar1 = *(byte *)(DAT_8008d7e8 + (uint)param_1[3] * 0xc + 1);
  }
  else
  {
			// volume of Music
    iVar2 = (uint)DAT_8008d7b8 *

			// songPool[param1->songID].vol_curr *
			(uint)(byte)(&DAT_80095d9c)[(uint)param_1[0xb] * 0x7c] *

            (uint)param_1[5];

	// pointer to drum samples (0xc each)
    bVar1 = *(byte *)(DAT_8008d7c4 + param_3 * 8 + 1);
  }

  // Channel_SetVolume
  FUN_8002b540(param_2,(iVar2 >> 10) * (uint)bVar1 * param_4 >> 0xf,(uint)param_1[9]);
  return;
}


// UpdateChannelVol_EngineFX_All
void FUN_8002ae64(void)

{
  int *piVar1;

  // channel taken
  piVar1 = DAT_8009056c;

  // if channels are taken
  if (DAT_8009056c != (int *)0x0)
  {
	// loop through taken
    do
	{
	  // if type == 0 (engine fx)
      if (*(char *)((int)piVar1 + 0xb) == '\0')
	  {
		// update channel volume
        (&DAT_8008fc6c)[*(byte *)((int)piVar1 + 9)] =
        (&DAT_8008fc6c)[*(byte *)((int)piVar1 + 9)] | 0x40;

		// UpdateChannelVol_EngineFX
        FUN_8002acb8(
		
			// howl_metaEngineFX[channelStats->soundID]
			DAT_8008d7d0 + (uint)*(ushort *)(piVar1 + 6) * 8,
            
			// channelAttrNew[channelStats->channelID]
			&DAT_8008fccc + (uint)*(byte *)((int)piVar1 + 9) * 4,
			
			// channelStats->vol
			(uint)*(byte *)((int)piVar1 + 0xf),
			
			// channelStats->LR
			(uint)*(byte *)((int)piVar1 + 0x11));
      }
      else
	  {
		// if type == 1 (other fx)
        if (*(char *)((int)piVar1 + 0xb) == '\x01')
		{
		  // update channel volume
          (&DAT_8008fc6c)[*(byte *)((int)piVar1 + 9)] =
          (&DAT_8008fc6c)[*(byte *)((int)piVar1 + 9)] | 0x40;

		  // UpdateChannelVol_OtherFX
		  FUN_8002ad04(DAT_8008d7d8 + (uint)*(ushort *)(piVar1 + 6) * 8,
                       &DAT_8008fccc + (uint)*(byte *)((int)piVar1 + 9) * 4,
                       (uint)*(byte *)((int)piVar1 + 0xf),(uint)*(byte *)((int)piVar1 + 0x11));
        }
      }
      piVar1 = (int *)*piVar1;
    } while (piVar1 != (int *)0x0);
  }
  return;
}


// UpdateChannelVol_Music_All
// called from SetVolume and Channel_ParseSongToChannels
void FUN_8002af6c(void)

{
  int *piVar1;

  // channel taken
  piVar1 = DAT_8009056c;

  // if channels are taken
  if (DAT_8009056c != (int *)0x0)
  {
	// loop through channels
    do
	{
	  // if type == 2 (music)
      if (*(char *)((int)piVar1 + 0xb) == '\x02')
	  {
		// update channel volume
        (&DAT_8008fc6c)[*(byte *)((int)piVar1 + 9)] =
        (&DAT_8008fc6c)[*(byte *)((int)piVar1 + 9)] | 0x40;

		// UpdateChannelVol_Music
        FUN_8002ad70(&DAT_800902cc + piVar1[6] * 0x1c,
                     &DAT_8008fccc + (uint)*(byte *)((int)piVar1 + 9) * 4,
                     (uint)*(byte *)((int)piVar1 + 0xd),(uint)*(byte *)((int)piVar1 + 0xf));
      }
      piVar1 = (int *)*piVar1;
    } while (piVar1 != (int *)0x0);
  }
  return;
}


// UpdateChannelVol_OtherFX_All
void FUN_8002b030(void)

{
  int *piVar1;

  // channel sound
  piVar1 = DAT_8009056c;

  // if channels are taken
  if (DAT_8009056c != (int *)0x0)
  {
	// loop through all taken channels
    do
	{
	  // if type == 1 (otherFX)
      if (*(char *)((int)piVar1 + 0xb) == '\x01')
	  {
		// update channel volume
        (&DAT_8008fc6c)[*(byte *)((int)piVar1 + 9)] =
        (&DAT_8008fc6c)[*(byte *)((int)piVar1 + 9)] | 0x40;

		// UpdateChannelVol_OtherFX
		FUN_8002ad04(DAT_8008d7d8 + (uint)*(ushort *)(piVar1 + 6) * 8,
                     &DAT_8008fccc + (uint)*(byte *)((int)piVar1 + 9) * 4,
                     (uint)*(byte *)((int)piVar1 + 0xf),(uint)*(byte *)((int)piVar1 + 0x11));
      }

	  // next slot
      piVar1 = (int *)*piVar1;

    } while (piVar1 != (int *)0x0);
  }
  return;
}


// Naughty Dog name: howl_VolumeGet
uint FUN_8002b0e0(int param_1)

{
  if (param_1 == 1) {

	// volume of Music
    return (uint)DAT_8008d7b8;
  }

  if (param_1 != 0) {
    if (param_1 != 2) {
      return 0;
    }

	// volume of Voice
    return (uint)DAT_8008d7bc;
  }

  // volume of FX
  return (uint)DAT_8008d7ac;
}

// three function names were found in Spyro 2 demo
// howl_VolumeGet
// howl_VolumeSet
// howl_VolumeFadeTo   --   Still undiscovered in 94426

// Naughty Dog name: howl_VolumeSet
void FUN_8002b130(int param_1,char param_2)

{
  if (param_1 == 1)
  {
	// volume of Music
    if (DAT_8008d7b8 == param_2) {
      return;
    }

	// volume of Music
    DAT_8008d7b8 = param_2;

	// enter critical section
    FUN_8002b4d0();

	// UpdateChannelVol_Music_All
    FUN_8002af6c();
  }
  else {
    if (param_1 == 0) {

	  // volume of FX
      if (DAT_8008d7ac == param_2) {
        return;
      }

	  // volume of FX
      DAT_8008d7ac = param_2;

	  // enter critical section
      FUN_8002b4d0();

	  // UpdateChannelVol_EngineFX_All
      FUN_8002ae64();
    }
    else {
      if (param_1 != 2) {
        return;
      }

	  // volume of Voice
      if (DAT_8008d7bc == param_2) {
        return;
      }

	  // volume of Voice
      DAT_8008d7bc = param_2;

	  // enter critical section
      FUN_8002b4d0();

	  // UpdateChannelVol_OtherFX_All
      FUN_8002b030();
    }
  }

  // exit critical section
  FUN_8002b508();
  return;
}


// howl_ModeGet
uint FUN_8002b1f0(void)

{
  // Mono or Stereo
  return (uint)DAT_8008d7cc;
}


// howl_ModeSet
void FUN_8002b1fc(undefined param_1)

{
  // Mono or Stereo
  DAT_8008d7cc = param_1;
  return;
}


// OptionsMenu_TestSound
void FUN_8002b208(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  uint uVar4;

  if (
		// OptionSlider_BoolPlay
		(DAT_8008d794 != 0) &&

		// if new row != old OptionSlider_Index
		(param_1 != DAT_8008d798)
	  )
  {

	// if old row is 1 (music slider)
	if (DAT_8008d798 == 1)
	{
	  // Music_GetHighestSongPlayIndex
      iVar2 = FUN_8002e550();

	  // if aku music already playing in-game,
	  // three cseq songs exist (level, game aku, menu aku)
      if (iVar2 == 1)
	  {
		// CseqMusic_Stop [2]
        FUN_800291a0(2);
      }

	  // if no aku music in-game,
	  // two songs exist (level, menu aku)
      else
	  {
		// CseqMusic_Stop [1]
        FUN_800291a0(1);
      }
    }
    else 
	{
	  // row index
      if (DAT_8008d798 < 2) {
        if (DAT_8008d798 == 0)
		{
		  // OtherFX_Stop2
          FUN_80028844(0x48);
        }
      }
      else {
        if ((DAT_8008d798 == 2) && (DAT_8008d7a0 != 0))
		{
		  // OtherFX_Stop1 (specific instance of soundID)
          FUN_80028808(DAT_8008d7a0);
          DAT_8008d7a0 = 0;
        }
      }
    }
  }
  
  // change in OptionSlider_BoolPlay
  if ((param_2 != DAT_8008d794) ||
     (iVar2 = DAT_8008d794, iVar1 = DAT_8008d798, param_1 != DAT_8008d798)) {

	// if sound is stopping
	if (param_2 == 0)
	{
	  // music row
      if (DAT_8008d798 == 1)
	  {
		// Music_GetHighestSongPlayIndex
        iVar2 = FUN_8002e550();

        if (iVar2 == 1)
		{
		  // CseqMusic_Stop
          FUN_800291a0(2);

          iVar2 = param_2;
          iVar1 = param_1;
        }
        else
		{
		  // CseqMusic_Stop
          FUN_800291a0(1);

          iVar2 = param_2;
          iVar1 = param_1;
        }
      }
      else {
        if (DAT_8008d798 < 2) {
          iVar2 = param_2;
          iVar1 = param_1;
		  
		  // FX row
          if (DAT_8008d798 == 0)
		  {
			// OtherFX_Stop2
            FUN_80028844(0x48);
            iVar2 = param_2;
            iVar1 = param_1;
          }
        }
        else {
          iVar2 = param_2;
          iVar1 = param_1;
		  
		  // voice row
          if ((DAT_8008d798 == 2) && (iVar2 = param_2, iVar1 = param_1, DAT_8008d7a0 != 0))
		  {
			// OtherFX_Stop2
            FUN_80028808();

			// OptionSlider_soundID
            DAT_8008d7a0 = 0;
			
            iVar2 = param_2;
            iVar1 = param_1;
          }
        }
      }
    }

	// if sound is starting
    else
	{
	  // row 0 (fx)
      if (param_1 == 0)
	  {
		// OtherFX_Play
        FUN_80028468(0x48,0);
        iVar2 = param_2;
        iVar1 = param_1;
      }

	  // not row 0
      else {
        iVar2 = param_2;
        iVar1 = param_1;

		// row 1 (music)
		if (param_1 == 1)
		{
		  // Music_GetHighestSongPlayIndex
          iVar2 = FUN_8002e550();

          uVar3 = 1;
          if (iVar2 == 1) {
            uVar3 = 2;
          }

		  // CseqMusic_Start (loopAtEnd)
          FUN_80028c78(uVar3,0,0,0,1);

          iVar2 = param_2;
          iVar1 = param_1;
        }
      }
    }
  }
  
  // OptionSlider_Index
  DAT_8008d798 = iVar1;
  
  // OptionSlider_BoolPlay
  DAT_8008d794 = iVar2;

  // If you are hovering over the "Voice" slider
  if ((DAT_8008d794 != 0) && (DAT_8008d798 == 2))
  {
	// frameTimer_MainFrame_ResetDB
    uVar4 = *(uint *)(PTR_DAT_8008d2ac + 0x1cf8);

	// every 25th frame
    if (uVar4 == (uVar4 / 0x19) * 0x19) {

	  // every 50th frame (0, 50, 100, 150...)
      if (uVar4 == (uVar4 / 0x32) * 0x32)
	  {
		// Player / AI structure + 0x4a shows driver index (0-7)

		// Play one of the character voices
        uVar4 = (uint)(ushort)(&DAT_80086e84)[*(byte *)(*(int *)(PTR_DAT_8008d2ac + 0x14dc) + 0x4a)]
                + 0x1c;
      }

	  // every 50th frame (25, 75, 125, 175)
      else
	  {
		// Player / AI structure + 0x4a shows driver index (0-7)

		// Play another one of the character voices
        uVar4 = (uint)(ushort)(&DAT_80086e84)[*(byte *)(*(int *)(PTR_DAT_8008d2ac + 0x14dc) + 0x4a)]
                + 0x2c;
      }

	  // OtherFX_Play, save OptionSlider_soundID
      DAT_8008d7a0 = FUN_80028468(uVar4 & 0xffff,0);
    }
  }
  return;
}


// Smart_EnterCriticalSection
void FUN_8002b4d0(void)

{
  bool bVar1;
  int iVar2;

  // Add 1 to the number of times you've
  // tried to enter a critical section
  iVar2 = DAT_8008d78c + 1;

  // Check if you're already in a critical section
  bVar1 = DAT_8008d78c == 0;

  // Set the number of times you've
  // tried to enter a critical section
  DAT_8008d78c = iVar2;

  // if you are not already in critical section
  if (bVar1)
  {
	// enter the critical section
    EnterCriticalSection();
  }
  return;
}


// Smart_ExitCriticalSection
void FUN_8002b508(void)

{
  if (
		// if you're already in a critical section
		(DAT_8008d78c != 0) &&

		// reduce the number of times you've treid to exit, by 1
		(DAT_8008d78c = DAT_8008d78c + -1,

		// if you have no more active needs to be in a critical section
		DAT_8008d78c == 0))
  {
	// You are no longer in a critical section
    ExitCriticalSection();
  }
  return;
}


// Channel_SetVolume
// param_1 - ChannelAttr
// param_2 - volume
// param_3 - LR
void FUN_8002b540(int param_1,uint param_2,int param_3)

{
  if (0x3fff < param_2) {
    param_2 = 0x3fff;
  }

  // If mode is Stereo
  if (DAT_8008d7cc == '\x01')
  {
	// adjust volume for left and right speaker
    *(undefined2 *)(param_1 + 0xc) = (short)( (param_2 * (byte)(&DAT_80082dac)[0x00+param_3]) >> 8);
    *(undefined2 *)(param_1 + 0xe) = (short)( (param_2 * (byte)(&DAT_80082dac)[0xff-param_3]) >> 8);
    return;
  }

  // if mode is Mono
  *(undefined2 *)(param_1 + 0xc) = (short)param_2;
  *(undefined2 *)(param_1 + 0xe) = (short)param_2;
  return;
}


// Channel_FindSound
undefined4 FUN_8002b5b4(short param_1)

{
  int *piVar1;
  int *piVar2;

  // channelTaken
  piVar1 = DAT_8009056c;

  // if channel slots are taken
  if (DAT_8009056c != (int *)0x0)
  {
	// loop through all, look for duplicates
    do
	{
      piVar2 = (int *)*piVar1;

	  if (
			// if ChannelStats type is otherFX
			(*(char *)((int)piVar1 + 0xb) == '\x01') &&

			// if soundID matches parameter
			(*(short *)(piVar1 + 6) == param_1)
		  )
	  {
		// duplicate found
        return 1;
      }
      piVar1 = piVar2;
    } while (piVar2 != (int *)0x0);
  }

  // duplicate not found
  return 0;
}


// Channel_AllocSlot_AntiSpam
// param_1 - soundID
// param_2 - boolUseAntiSpam (always true except one Aku "whoosh" in Adv Hub)
// param_3 - flags
// param_4 - ChannelAttr
int FUN_8002b608(short param_1,char param_2,uint param_3,undefined4 *param_4)

{
  uint uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  int *piVar5;
  int *piVar6;
  int iVar7;

  // if there can only be one instance of this audio
  if ((param_2 == '\x01') &&
     (
		// frameTimer_MainFrame_ResetDB
		iVar7 = *(int *)(PTR_DAT_8008d2ac + 0x1cf8),

		// channel linked list taken
		piVar5 = DAT_8009056c,

		// taken channels exist
		DAT_8009056c != (int *)0x0
     ))
  {
	// check for duplicates
    do
	{
      piVar6 = (int *)*piVar5;

      if (
			// if type is otherFX
			(*(char *)((int)piVar5 + 0xb) == '\x01') &&

			(
				// if soundID matches parameter
				(*(short *)(piVar5 + 6) == param_1 &&

				// if started playing less than 10 frames ago
				((uint)(iVar7 - piVar5[7]) < 10))
			)
		 )
	  {
		// set channel to OFF
        (&DAT_8008fc6c)[*(byte *)((int)piVar5 + 9)] =
        (&DAT_8008fc6c)[*(byte *)((int)piVar5 + 9)] | 1;

		// remove "playing" flag
        (&DAT_8008fc6c)[*(byte *)((int)piVar5 + 9)] =
        (&DAT_8008fc6c)[*(byte *)((int)piVar5 + 9)] & 0xfffffffd;

		*(byte *)(piVar5 + 2) = *(byte *)(piVar5 + 2) & 0xfe;

		// remove from taken list, recycle slot

		// LIST_RemoveMember channelTaken
        FUN_800317e4(&DAT_8009056c,piVar5);

		// LIST_AddBack channelFree
        FUN_80031788(&DAT_80090578,piVar5);
      }
      piVar5 = piVar6;
    } while (piVar6 != (int *)0x0);
  }

  // channelFree
  iVar7 = DAT_80090578;

  // if no channel slots free
  if (DAT_80090578 == 0)
  {
	// set zero
    iVar7 = 0;
  }

  // if channel slots free
  else
  {
	// grab a slot and start the channel

	// LIST_RemoveMember channelFree (first)
    FUN_800317e4(&DAT_80090578,DAT_80090578);

    // LIST_AddBack channelTaken
	FUN_80031788(&DAT_8009056c,iVar7);

	// set channel to ON + param_3 (0x7c) for all update flags
	(&DAT_8008fc6c)[*(byte *)(iVar7 + 9)] =
	(&DAT_8008fc6c)[*(byte *)(iVar7 + 9)] | 2 | param_3;

	// ChannelStats->channelID
    uVar1 = (uint)*(byte *)(iVar7 + 9);

	// copy ChannelAttr from
	// stack into global array
	uVar2 = param_4[1];
    uVar3 = param_4[2];
    uVar4 = param_4[3];

	// spuStartAddr
    (&DAT_8008fccc)[uVar1 * 4] = *param_4;

	// ADSR
	(&DAT_8008fcd0)[uVar1 * 4] = uVar2;

	// pitch ( and 0xa?)
	*(undefined4 *)(&DAT_8008fcd4 + uVar1 * 8) = uVar3;

	// audioLR
	(&DAT_8008fcd8)[uVar1 * 4] = uVar4;

	*(undefined *)(iVar7 + 8) = 1;
  }
  return iVar7;
}


// Channel_AllocSlot
int FUN_8002b7d0(uint param_1,undefined4 *param_2)

{
  int iVar1;
  uint uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;

  // channel free
  iVar1 = DAT_80090578;

  // if no free channels
  if (DAT_80090578 == 0)
  {
	// quit
    iVar1 = 0;
  }

  // if free channels are found
  else
  {
	// LIST_RemoveMember free
    FUN_800317e4(&DAT_80090578,DAT_80090578);

	// LIST_AddBack taken
    FUN_80031788(&DAT_8009056c,iVar1);

	// set channel update flags to ON + param_1 (0x7c) for all update flags
	(&DAT_8008fc6c)[*(byte *)(iVar1 + 9)] =
	(&DAT_8008fc6c)[*(byte *)(iVar1 + 9)] | 2 | param_1;

	uVar2 = (uint)*(byte *)(iVar1 + 9);
    uVar3 = param_2[1];
    uVar4 = param_2[2];
    uVar5 = param_2[3];

	// spuStartAddr
    (&DAT_8008fccc)[uVar2 * 4] = *param_2;

	// ADSR
    (&DAT_8008fcd0)[uVar2 * 4] = uVar3;

	// pitch ( and 0xa?)
    *(undefined4 *)(&DAT_8008fcd4 + uVar2 * 8) = uVar4;

	// audioLR
    (&DAT_8008fcd8)[uVar2 * 4] = uVar5;

    *(undefined *)(iVar1 + 8) = 1;
  }
  return iVar1;
}


// Channel_SearchFX_EditAttr
// param_1 - type
// param_2 - id
// param_3 - updateFlags
// param_4 - channelAttr
int * FUN_8002b898(char param_1,int param_2,uint param_3,undefined4 *param_4)

{
  uint uVar1;
  int *piVar2;

  // taken list
  piVar2 = DAT_8009056c;

  // if channel slots are taken
  if (DAT_8009056c != (int *)0x0)
  {
	// search all slots
    do
	{
	  // if slot is found with matching parameters
      if (
			// type (music, engine, otherFX)
			(*(char *)((int)piVar2 + 0xb) == param_1) &&

			// soundID
			(piVar2[6] == param_2)
		 )
	  {
		// enable update flags in param_3
        (&DAT_8008fc6c)[*(byte *)((int)piVar2 + 9)] =
        (&DAT_8008fc6c)[*(byte *)((int)piVar2 + 9)] | param_3;

		uVar1 = (uint)*(byte *)((int)piVar2 + 9);

		// if new startAddr
        if ((param_3 & 4) != 0)
		{
          (&DAT_8008fccc)[uVar1 * 4] = *param_4;
        }

		// if new ADSR
        if ((param_3 & 8) != 0)
		{
          *(undefined2 *)(&DAT_8008fcd0 + uVar1 * 4) = *(undefined2 *)(param_4 + 1);
          *(undefined2 *)((int)&DAT_8008fcd0 + uVar1 * 0x10 + 2) = *(undefined2 *)((int)param_4 + 6)
          ;
        }

		// if new pitch
        if ((param_3 & 0x10) != 0) {
          (&DAT_8008fcd4)[uVar1 * 8] = *(undefined2 *)(param_4 + 2);
        }

		// if new reverb
        if ((param_3 & 0x20) != 0) {
          (&DAT_8008fcd6)[uVar1 * 8] = *(undefined2 *)((int)param_4 + 10);
        }

		// if new volume
        if ((param_3 & 0x40) != 0) {
          (&DAT_8008fcd8)[uVar1 * 4] = param_4[3];
        }

        return piVar2;
      }
      piVar2 = (int *)*piVar2;
    } while (piVar2 != (int *)0x0);
  }
  return (int *)0;
}


// Channel_SearchFX_Destroy
int * FUN_8002b9b8(char param_1,uint param_2,uint param_3)

{
  int *piVar1;
  int *piVar2;

  // taken
  piVar2 = DAT_8009056c;

  // if taken slots exist
  if (DAT_8009056c != (int *)0x0)
  {
	// loop through slots
    do
	{
      piVar1 = (int *)*piVar2;

	  // if parameters match
      if (
			// type (engineFX, otherFX, music)
			(*(char *)((int)piVar2 + 0xb) == param_1) &&

			((piVar2[6] & param_3) == (param_2 & param_3))
		 )
	  {
        // set channel to OFF
		(&DAT_8008fc6c)[*(byte *)((int)piVar2 + 9)] =
        (&DAT_8008fc6c)[*(byte *)((int)piVar2 + 9)] | 1;

		// remove "playing" flag
		(&DAT_8008fc6c)[*(byte *)((int)piVar2 + 9)] =
        (&DAT_8008fc6c)[*(byte *)((int)piVar2 + 9)] & 0xfffffffd;

		*(byte *)(piVar2 + 2) = *(byte *)(piVar2 + 2) & 0xfe;

		// LIST_RemoveMember taken
        FUN_800317e4(&DAT_8009056c,piVar2);

		// LIST_AddBack free
        FUN_80031788(&DAT_80090578,piVar2);

        return piVar2;
      }
      piVar2 = piVar1;
    } while (piVar1 != (int *)0x0);
  }

  return (int *)0;
}


// Channel_DestroyAll_LowLevel
// param_1 0: keep menu fx, 1: destroy all fx
// param_2 0: destroy music, 1: keep music
void FUN_8002ba90(int param_1,int param_2,char param_3)

{
  int *piVar1;
  int *piVar2;

  // taken
  piVar1 = DAT_8009056c;

  // if taken slots exist
  if (DAT_8009056c != (int *)0x0)
  {
	// loop through slots
    do
	{
      piVar2 = (int *)*piVar1;

      if (
			(
				(param_2 == 0) ||

				// type is not param_3 (not music)
				(*(char *)((int)piVar1 + 0xb) != param_3)
			) &&
			(
				(
					param_1 != 0 ||

					(
						(
							// if not otherFX
							*(char *)((int)piVar1 + 0xb) != '\x01' ||

							// soundID > 5 (not menus sounds)
							(5 < *(ushort *)(piVar1 + 6))
						)
					)
				)
			)
		)
	  {
		// set channel to OFF
		(&DAT_8008fc6c)[*(byte *)((int)piVar1 + 9)] =
        (&DAT_8008fc6c)[*(byte *)((int)piVar1 + 9)] | 1;

		// remove "playing" flag
		(&DAT_8008fc6c)[*(byte *)((int)piVar1 + 9)] =
        (&DAT_8008fc6c)[*(byte *)((int)piVar1 + 9)] & 0xfffffffd;

		*(byte *)(piVar1 + 2) = *(byte *)(piVar1 + 2) & 0xfe;

		// LIST_RemoveMember taken
        FUN_800317e4(&DAT_8009056c,piVar1);

		// LIST_AddBack free
        FUN_80031788(&DAT_80090578,piVar1);
      }
      piVar1 = piVar2;
    } while (piVar2 != (int *)0x0);
  }
  return;
}


// Channel_ParseSongToChannels
void FUN_8002bbac(void)

{
  bool bVar1;
  int iVar2;
  undefined4 uVar3;
  uint uVar4;
  uint uVar5;
  byte *pbVar6;
  byte bVar7;
  byte bVar8;
  byte *pbVar9;
  int iVar10;
  uint uVar11;
  int iVar12;
  int iVar13;

  if (
		// if audio is enabled
		(DAT_8008d05c != '\0') &&
		(
			bVar1 = false,

			// ptrCseqHeader is valid
			DAT_8008d7b0 != 0
		)
	  )
  {

	// loop counter
    iVar13 = 0;
    iVar12 = 0;

	// loop through both song pools
	// for iVar13 = 0; iVar13 < 2; iVar13++
    do {

	  // song in song pool
	  pbVar9 = &DAT_80095d84 + iVar12;

      if (
			// if song is playing
			((*pbVar9 & 1) != 0) &&

			// if song is not paused
			((*pbVar9 & 2) == 0)
		  )
	  {
		// vol_Curr
        uVar5 = (uint)(byte)(&DAT_80095d9c)[iVar12];

		// songPool->0x10 + songPool->tempo
        uVar4 = *(int *)((int)&DAT_80095d94 + iVar12) + *(int *)((int)&DAT_80095d90 + iVar12);
        uVar11 = uVar4 >> 0x10;

		// songPool->0x10
		*(uint *)((int)&DAT_80095d94 + iVar12) = uVar4;
		
		// vol_New
        bVar8 = (&DAT_80095d9d)[iVar12];
        uVar4 = (uint)bVar8;

		// increment timeSpentPlaying ([something] + tempo)
        *(int *)((int)&DAT_80095d98 + iVar12) =
		*(int *)((int)&DAT_80095d98 + iVar12) + uVar11;

		// self = (unsigned short)self
        *(uint *)((int)&DAT_80095d94 + iVar12) = (uint)*(ushort *)((int)&DAT_80095d94 + iVar12);
        
		// vol_Curr != vol_New
		if (uVar5 != uVar4) 
		{
		  // vol_Curr < vol_New
          if (uVar5 < uVar4) 
		  {
			// increase
            bVar7 = (byte)(uVar5 + (byte)(&DAT_80095d9e)[iVar12]);
            bVar1 = uVar4 < uVar5 + (byte)(&DAT_80095d9e)[iVar12];
          }
		  
		  // vol_Curr > vol_New
          else 
		  {
			// decrease
            bVar7 = (byte)(uVar5 - (byte)(&DAT_80095d9e)[iVar12]);
            bVar1 = (int)(uVar5 - (byte)(&DAT_80095d9e)[iVar12]) < (int)uVar4;
          }
		  
		  // reached desired volume, and if song over
          if ((bVar1) && (bVar7 = bVar8, (*pbVar9 & 4) != 0))
		  {
			// SongPool_StopAllCseq
            FUN_8002ac0c(pbVar9);

			// Music_End
            FUN_8002e53c();

            *pbVar9 = *pbVar9 & 0xfb;
          }
		  
		  // new vol_Curr
          (&DAT_80095d9c)[iVar12] = bVar7;
		  
		  // volumeChanged
          bVar1 = true;
        }
		
        iVar10 = 0;

		// song numSequences
        if ((&DAT_80095d9f)[iVar12] != '\0')
		{
          iVar2 = 0;
          do
		  {
			// songPool.CseqSequences[iVar2]
            pbVar6 = *(byte **)(pbVar9 + iVar2 + 0x1c);

            uVar5 = (uint)pbVar6[5];
            uVar4 = (uint)pbVar6[6];
			
			// if current != desired, lerp by stepRate
            if (uVar5 != uVar4) {
              if (uVar5 < uVar4) {
                bVar8 = (byte)(uVar5 + pbVar6[7]);
                bVar1 = uVar4 < uVar5 + pbVar6[7];
              }
              else {
                bVar8 = (byte)(uVar5 - pbVar6[7]);
                bVar1 = (int)(uVar5 - pbVar6[7]) < (int)uVar4;
              }
              if (bVar1) {
                bVar8 = pbVar6[6];
              }
              pbVar6[5] = bVar8;
              bVar1 = true;
            }

			// if sequence is playing
			if ((*pbVar6 & 1) != 0)
			{
			  // sequence->noteLength
              uVar5 = *(uint *)(pbVar6 + 0xc);

			  // sequence->noteTimeElapsed
              uVar4 = *(int *)(pbVar6 + 0x10) + uVar11;
              *(uint *)(pbVar6 + 0x10) = uVar4;

			  // while noteLength < noteTimeElapsed
              if (uVar5 <= uVar4) {
                do 
				{
                  if ((*pbVar6 & 1) == 0) break;
				  
				  // sequence->noteTimeElapsed
                  *(uint *)(pbVar6 + 0x10) = *(int *)(pbVar6 + 0x10) - uVar5;

				  // pbVar6 is the cseq struct

				  // sequence->currNote->opcode
                  bVar8 = **(byte **)(pbVar6 + 0x18);

				  // if opcode is valid
                  if (bVar8 < 0xb)
				  {
					// use opcode value to execute function,
					// pass cseq structure as parameter
                    (*(code *)(&PTR_LAB_80083004)[(uint)bVar8])(pbVar6);

					// seq->flags
                    bVar7 = *pbVar6;
					
                    if ((bVar7 & 1) != 0) 
					{
					  // if song not restarting (opcode03)
                      if ((bVar7 & 8) == 0)
					  {
						// sequence->currNote += noteSize[noteType]
                        iVar2 = *(int *)(pbVar6 + 0x18) + *(int *)(&DAT_80083030 + (uint)bVar8 * 4);
                        *(int *)(pbVar6 + 0x18) = iVar2;
                      }
                      
					  // if song restarting (opcode03)
					  else 
					  {
						// sequence->firstNote
                        iVar2 = *(int *)(pbVar6 + 0x14);
						
						// remove flag
                        *pbVar6 = bVar7 & 0xf7;
                      }

					  // howl_GetNextNote
					  // currNote, sequence->NoteLength
                      uVar3 = FUN_80029dcc(iVar2,pbVar6 + 0xc);

					  // update currNote
					  *(undefined4 *)(pbVar6 + 0x18) = uVar3;
                    }
                  }
				  
				  // sequence->NoteLength
                  uVar5 = *(uint *)(pbVar6 + 0xc);
				
				// while noteLength < noteTimeElapsed
                } while (uVar5 <= *(uint *)(pbVar6 + 0x10));
              }
            }
            iVar10 = iVar10 + 1;
            iVar2 = iVar10 * 4;
          } while (iVar10 < (int)(uint)(byte)(&DAT_80095d9f)[iVar12]);
        }
      }

	  // increment loop counter
      iVar13 = iVar13 + 1;

      iVar12 = iVar12 + 0x7c;
    } while (iVar13 < 2);

    if (bVar1)
	{
	  // UpdateChannelVol_Music_All
      FUN_8002af6c();
    }
  }
  return;
}


// Channel_UpdateChannels
void FUN_8002be9c(void)

{
  ushort pitch;
  ushort uVar1;
  short volR;
  int iVar2;
  long RRmode;
  uint *puVar3;
  ulong startAddr;
  uint vNum;
  uint uVar4;
  ulong voice_bit;
  long local_38;
  long local_34;

  // actually "channel_bit"
  // psyq calls it "voice" but that's confusing to voiceline
  voice_bit = 0;

  // loop counter
  vNum = 0;

  puVar3 = &DAT_8008fc6c;

  // get all active channel bits
  // for vNum = 0; vNum < 0x18 (24); vNum++
  do
  {
    uVar4 = *puVar3;

    if (
			(uVar4 != 0) &&

			// if channel needs to turn off
			((uVar4 & 1) != 0)
		)
	{
	  // add to OFF channels
      voice_bit = voice_bit | 1 << (vNum & 0x1f);

      if ((uVar4 & 2) == 0) {
        *puVar3 = 0;
      }
      else {
        *puVar3 = uVar4 & 0xfffffffe;
      }
    }

	// increment loop counter
    vNum = vNum + 1;
    puVar3 = puVar3 + 1;
  } while ((int)vNum < 0x18);

  // turn all channel bits off
  SpuSetKey(0,voice_bit);

  // reset channel bits
  voice_bit = 0;

  // loop counter
  vNum = 0;

  // pointer offset
  iVar2 = 0;

  // get all channel bits needed this frame
  // for vNum = 0; vNum < 0x18 (24); vNum++
  do {

	// ChannelUpdateFlags[channelID]
	uVar4 = *(uint *)((int)&DAT_8008fc6c + iVar2);

	// if channel needs updating
    if (uVar4 != 0)
	{
	  // if this channel is now ON
      if ((uVar4 & 2) != 0)
	  {
		// set status to ON
        voice_bit = voice_bit | 1 << (vNum & 0x1f);
      }

      if (
			// channel startAddr needs to change
			((uVar4 & 4) != 0) &&

			(
				// current
				startAddr = (&DAT_8008fccc)[vNum * 4],

				// previous != current
				(&DAT_8008fe4c)[vNum * 4] != startAddr
			)
		  )
	  {
		// set new previous
        (&DAT_8008fe4c)[vNum * 4] = startAddr;

		// start address is an address in spu ram, not cpu ram
		SpuSetVoiceStartAddr(vNum,startAddr);
	  }

      if (
			// ADSR needs to change
			((uVar4 & 8) != 0) &&

			// change in adsr
			(*(int *)(&DAT_8008fe50 + vNum * 8) != (&DAT_8008fcd0)[vNum * 4])
		  )
	  {
		// set new adsr
        pitch = *(ushort *)(&DAT_8008fcd0 + vNum * 4);
        (&DAT_8008fe50)[vNum * 8] = pitch;
        uVar1 = *(ushort *)((int)&DAT_8008fcd0 + vNum * 0x10 + 2);
        (&DAT_8008fe52)[vNum * 8] = uVar1;
		
        if ((short)pitch < 0) {
          local_38 = 5;
        }
        else {
          local_38 = 1;
        }
        if ((short)uVar1 < 0) {
          if ((uVar1 >> 0xe & 1) == 0) {
            local_34 = 5;
          }
          else {
            local_34 = 7;
          }
        }
        else {
          if ((uVar1 >> 0xe & 1) == 0) {
            local_34 = 1;
          }
          else {
            local_34 = 3;
          }
        }
        RRmode = 7;
        if ((uVar1 >> 5 & 1) == 0) {
          RRmode = 3;
        }

		// these are SPU Channels, not a voiceline
        SpuSetVoiceADSRAttr(vNum,pitch >> 8 & 0x7f,pitch >> 4 & 0xf,uVar1 >> 6 & 0x7f,uVar1 & 0x1f,
                            pitch & 0xf,local_38,local_34,RRmode);
	  }

      if (
			// if pitch needs to change
			((uVar4 & 0x10) != 0) &&

			(pitch = (&DAT_8008fcd4)[vNum * 8], (&DAT_8008fe54)[vNum * 8] != pitch)
		 )
	  {
        (&DAT_8008fe54)[vNum * 8] = pitch;

		SpuSetVoicePitch(vNum,pitch);
      }

	  if (
			// if reverb needs to change
			((uVar4 & 0x20) != 0) &&

			(volR = (&DAT_8008fcd6)[vNum * 8], (&DAT_8008fe56)[vNum * 8] != volR)
		 )
	  {
        (&DAT_8008fe56)[vNum * 8] = volR;

		SpuSetReverbVoice((uint)(volR != 0),1 << (vNum & 0x1f));
      }

      if (
			// if volume needs to change
			((uVar4 & 0x40) != 0) &&

			(*(int *)(&DAT_8008fe58 + vNum * 8) != (&DAT_8008fcd8)[vNum * 4])
         )
	  {
        (&DAT_8008fe58)[vNum * 8] = *(undefined2 *)(&DAT_8008fcd8 + vNum * 4);
        volR = *(short *)((int)&DAT_8008fcd8 + vNum * 0x10 + 2);
        (&DAT_8008fe5a)[vNum * 8] = volR;

		SpuSetVoiceVolume(vNum,(&DAT_8008fe58)[vNum * 8],volR);
      }

      *(uint *)((int)&DAT_8008fc6c + iVar2) = 0;
    }

	// increment loop counter
    vNum = vNum + 1;

	// increment pointer
    iVar2 = vNum * 4;
  } while ((int)vNum < 0x18);

  // turn on voice bits
  SpuSetKey(1,voice_bit);

  return;
}


// Cutscene_VolumeBackup
void FUN_8002c18c(void)

{
  // enter critical section
  FUN_8002b4d0();

  // make a copy of FX volume
  DAT_8008d79c = howl_VolumeGet(0);

  // make another copy volume of FX and clamp to 0x100
  DAT_8008d79e = (undefined)DAT_8008d79c;
  DAT_8008d79c = DAT_8008d79c & 0xff;

  // copy exists
  DAT_8008d79f = 1;

  // exit critical section
  FUN_8002b508();

  return;
}


// Cutscene_VolumeRestore
void FUN_8002c1d0(void)

{
  // enter critical section
  FUN_8002b4d0();

  // copy does not exist
  DAT_8008d79f = 0;

  // Set volume of FX
  howl_VolumeSet(0,(uint)DAT_8008d79e);

  // exit critical section
  FUN_8002b508();

  return;
}


// howl_PlayAudio_Update
void FUN_8002c208(void)
{
  // plays all non-xa audio

  int **ppiVar1;
  ushort uVar2;
  int **ppiVar3;

  // if audio is enabled
  if (DAT_8008d05c != '\0')
  {
	// ChannelStats taken
    ppiVar3 = (int **)DAT_8009056c;

	// if volume copy exists,
	// make audio slowly fade
	if (DAT_8008d79f != '\0')
	{
	  // Subtract value from a copy of FX volume
      DAT_8008d79c = DAT_8008d79c - 2;

	  // clamp to zero if you go below zero
      if ((int)((uint)DAT_8008d79c << 0x10) < 0)
	  {
		// set to zero
        DAT_8008d79c = 0;
      }

      DAT_8008d78c = 1;

	  // Set main volume of FX to the modified copy
      howl_VolumeSet(0,(uint)(byte)DAT_8008d79c);

      DAT_8008d78c = 0;

	  // ChannelStats taken
      ppiVar3 = (int **)DAT_8009056c;
    }

	// loop through all ChannelStats
    while (ppiVar1 = ppiVar3, ppiVar1 != (int **)0x0)
	{
      ppiVar3 = (int **)*ppiVar1;

      if (
			// if sound is on a timer (not stacatto)
			((*(byte *)(ppiVar1 + 2) & 4) == 0) &&

			(
				// decrement
				uVar2 = *(short *)((int)ppiVar1 + 0x16) - 5,
				*(ushort *)((int)ppiVar1 + 0x16) = uVar2,

				// if time is up
				(int)((uint)uVar2 << 0x10) < 1
			)
		 )
	  {
		// set channel to OFF
        (&DAT_8008fc6c)[*(byte *)((int)ppiVar1 + 9)] =
        (&DAT_8008fc6c)[*(byte *)((int)ppiVar1 + 9)] | 1;

		// remove "playing" flag
        (&DAT_8008fc6c)[*(byte *)((int)ppiVar1 + 9)] =
        (&DAT_8008fc6c)[*(byte *)((int)ppiVar1 + 9)] & 0xfffffffd;

        *(byte *)(ppiVar1 + 2) = *(byte *)(ppiVar1 + 2) & 0xfe;

		// LIST_RemoveMember taken
        FUN_800317e4(&DAT_8009056c,ppiVar1);

		// LIST_AddBack free
        FUN_80031788(&DAT_80090578,ppiVar1);
      }
    }

	// Channel_ParseSongToChannels
    FUN_8002bbac();
  }

  // Channel_UpdateChannels
  FUN_8002be9c();

  return;
}


// howl_InitChannelAttr_EngineFX
// param_1 EngineFX*
// param_2 ChannelAttr
// param_3 volume
// param_4 LR
// param_5 distort
void FUN_8002c34c(int param_1,int *param_2,int param_3,undefined4 param_4,int param_5)

{
  ushort uVar1;
  undefined2 uVar2;

  // Channel_SetVolume
  FUN_8002b540(

	// ChannelAttr
	param_2,

	// volume of FX
	(uint)DAT_8008d7ac * (uint)*(byte *)(param_1 + 1) * param_3 >> 10,

	param_4
  );

  if (param_5 == 0x80)
  {
	// pitch data
    uVar2 = *(undefined2 *)(param_1 + 2);
  }

  else
  {
	// pitch data
    uVar2 = (undefined2)
            ((uint)*(ushort *)(param_1 + 2) * *(int *)(&DAT_800825ac + param_5 * 4) >> 0x10);
  }

  // channelAttr 0x8, pitch
  *(undefined2 *)(param_2 + 2) = uVar2;

  // ChannelAttr->spuStartAddr = howl_spuAddrs[engineFX->spuIndex] << 3
  uVar1 = *(ushort *)((uint)*(ushort *)(param_1 + 6) * 4 + DAT_8008d7dc);

  // ADSR
  *(undefined2 *)(param_2 + 1) = 0x80ff;
  *(undefined2 *)((int)param_2 + 6) = 0x1fc2;

  // multiply spuAddr by 8
  *param_2 = (uint)uVar1 << 3;

  return;
}

// howl_InitChannelAttr_OtherFX
// param_1 OtherFX*
// param_2 ChannelAttr
// param_5 distortion
void FUN_8002c424(byte *param_1,int *param_2,int param_3,undefined4 param_4,int param_5)

{
  byte bVar1;
  ushort uVar2;
  undefined2 uVar3;

  // volume of FX
  bVar1 = DAT_8008d7ac;
  if ((*param_1 & 4) != 0)
  {
	  // volume of Voice
    bVar1 = DAT_8008d7bc;
  }
  
  // no distortion
  if (param_5 == 0x80)
  {
	// pitch
    uVar3 = *(undefined2 *)(param_1 + 2);
  }
  
  // distortion
  else
  {
	// pitch
    uVar3 = (undefined2)
            ((uint)*(ushort *)(param_1 + 2) * *(int *)(&DAT_800829ac + param_5 * 4) >> 0x10);
  }

  // Channel_SetVolume
  FUN_8002b540(param_2,(uint)bVar1 * (uint)param_1[1] * param_3 >> 10,param_4);

  // pitch
  *(undefined2 *)(param_2 + 2) = uVar3;

  // ChannelAttr->spuStartAddr = howl_spuAddrs[otherFX->spuIndex] << 3
  uVar2 = *(ushort *)((uint)*(ushort *)(param_1 + 4) * 4 + DAT_8008d7dc);

  // ADSR
  *(undefined2 *)(param_2 + 1) = 0x80ff;
  *(undefined2 *)((int)param_2 + 6) = 0x1fc2;

  // multiply 8
  *param_2 = (uint)uVar2 << 3;

  return;
}


//howl_PauseAudio
void FUN_8002c510(void)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  int iVar7;

  // CDSYS_XAPauseRequest
  FUN_8001cf98();

  if (DAT_8008d790 == 0)
  {
	// CseqMusic_Pause
    FUN_80028d64();

	// enter critical section
    FUN_8002b4d0();

	// channel taken list
	piVar2 = (int *)DAT_8009056c;

    while (piVar2 != (int *)0x0) {
      iVar7 = *piVar2;

	  // ChannelID (of what struct)
	  // (int)piVar2 + 9

	  // turn all channels off
      (&DAT_8008fc6c)[*(byte *)((int)piVar2 + 9)] =
	  (&DAT_8008fc6c)[*(byte *)((int)piVar2 + 9)] | 1;

	  iVar3 = DAT_8008d790;
      iVar1 = DAT_8008d790 * 8;

	  // increment numBackup_ChannelStats
      DAT_8008d790 = DAT_8008d790 + 1;

	  // remove "playing" flag
      (&DAT_8008fc6c)[*(byte *)((int)piVar2 + 9)] =
      (&DAT_8008fc6c)[*(byte *)((int)piVar2 + 9)] & 0xfffffffd;

	  // copy channel data to backup
	  uVar4 = piVar2[1];
      uVar5 = piVar2[2];
      uVar6 = piVar2[3];
      (&DAT_8008ffcc)[iVar1] = *piVar2;
      (&DAT_8008ffd0)[iVar3 * 8] = uVar4;
      (&DAT_8008ffd4)[iVar3 * 8] = uVar5;
      (&DAT_8008ffd8)[iVar3 * 8] = uVar6;
      uVar4 = piVar2[5];
      uVar5 = piVar2[6];
      uVar6 = piVar2[7];
      (&DAT_8008ffdc)[iVar3 * 8] = piVar2[4];
      (&DAT_8008ffe0)[iVar3 * 8] = uVar4;
      (&DAT_8008ffe4)[iVar3 * 8] = uVar5;
      (&DAT_8008ffe8)[iVar3 * 8] = uVar6;

	  // LIST_RemoveMember taken
      FUN_800317e4(&DAT_8009056c,piVar2);

	  // LIST_AddBack free
      FUN_80031788(&DAT_80090578,piVar2);

	  // next member
	  piVar2 = (int *)iVar7;
    }

	// exit critical section
    FUN_8002b508();
  }
  return;
}


// howl_UnPauseChannel
// param_1 is ChannelStats
void FUN_8002c64c(int param_1)

{
  byte bVar1;
  uint uVar2;

  // ChannelAttr (0x10)
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;

  // type
  bVar1 = *(byte *)(param_1 + 0xb);

  // otherFX
  if (bVar1 == 1)
  {
	// if == 1

	// howl_InitChannelAttr_OtherFX
    FUN_8002c424(
					// metaOtherFX stats -> soundID
					DAT_8008d7d8 + (uint)*(ushort *)(param_1 + 0x18) * 8,

					// ChannelAttr (func Output)
					&local_18,

					// volume
					(uint)*(byte *)(param_1 + 0xf),

					// left-right
					(uint)*(byte *)(param_1 + 0x11),

					// distort
					(uint)*(byte *)(param_1 + 0x10)
				);
  }
  else {
    if (bVar1 < 2)
	{
	  // if not engineFX
      if (bVar1 != 0) {
        return;
      }

	  // if == 0

	  // howl_InitChannelAttr_EngineFX
      FUN_8002c34c(
					// metaEngineFX [ stats -> soundID ]
					DAT_8008d7d0 + (uint)*(ushort *)(param_1 + 0x18) * 8,

					// ChannelAttr (func Output)
					&local_18,

					// volume
					(uint)*(byte *)(param_1 + 0xf),

					// left-right
					(uint)*(byte *)(param_1 + 0x11),

					// distort
					(uint)*(byte *)(param_1 + 0x10));
    }
    else {
      if (bVar1 != 2) {
        return;
      }

	  // if == 2

	  // music

	  // howl_InitChannelAttr_Music
      FUN_80029f80(

									// sound ID
					&DAT_800902cc + *(int *)(param_1 + 0x18) * 0x1c,

					// ChannelAttr
					&local_18,

					// ChannelStats ->
					// shortIndexSample (drums)
					(uint)*(byte *)(param_1 + 0xd),

					// ChannelStats ->
					// volume
					(uint)*(byte *)(param_1 + 0xf));
    }
  }

  // enable all bits in ChannelUpdate flag
  (&DAT_8008fc6c)[*(byte *)(param_1 + 9)] =
  (&DAT_8008fc6c)[*(byte *)(param_1 + 9)] | 0x7e;

  // channelID
  uVar2 = (uint)*(byte *)(param_1 + 9);

  // spuStartAddr
  (&DAT_8008fccc)[uVar2 * 4] = local_18;

  // ADSR
  (&DAT_8008fcd0)[uVar2 * 4] = local_14;

  // pitch
  *(undefined4 *)(&DAT_8008fcd4 + uVar2 * 8) = local_10;

  // LR
  (&DAT_8008fcd8)[uVar2 * 4] = local_c;
  return;
}


//howl_UnPauseAudio
void FUN_8002c784(void)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  int iVar8;
  undefined4 *puVar9;

  if (DAT_8008d790 != 0) {
    iVar8 = 0;

	// enter critical section
    FUN_8002b4d0();

	// number of ChannelStats collected during pause,
    if (0 < DAT_8008d790)
	{
	  // backup channelStats data
      puVar9 = &DAT_8008ffcc;

	  // sound free
      puVar7 = DAT_80090578;
      do {
        if (puVar7 == (undefined4 *)0x0) break;
        puVar6 = (undefined4 *)*puVar7;
        uVar1 = *puVar7;
        uVar2 = puVar7[1];
        uVar3 = puVar9[1];
        uVar4 = puVar9[2];
        uVar5 = puVar9[3];
        *puVar7 = *puVar9;
        puVar7[1] = uVar3;
        puVar7[2] = uVar4;
        puVar7[3] = uVar5;
        uVar3 = puVar9[5];
        uVar4 = puVar9[6];
        uVar5 = puVar9[7];
        puVar7[4] = puVar9[4];
        puVar7[5] = uVar3;
        puVar7[6] = uVar4;
        puVar7[7] = uVar5;
        puVar9 = puVar9 + 8;
        *(undefined *)((int)puVar7 + 9) = *(undefined *)((int)puVar7 + 9);
        *puVar7 = uVar1;
        puVar7[1] = uVar2;
        iVar8 = iVar8 + 1;

		// LIST_RemoveMember free
        FUN_800317e4(&DAT_80090578,puVar7);

		// LIST_AddBack taken
        FUN_80031788(&DAT_8009056c,puVar7);

		// howl_UnPauseChannel
		// pass ChannelStats
        FUN_8002c64c(puVar7);

        puVar7 = puVar6;
      } while (iVar8 < DAT_8008d790);
    }

	// exit critical section
    FUN_8002b508();

	// CseqMusic_Resume
    FUN_80028de0();

	// erase numBackup_ChannelStats
    DAT_8008d790 = 0;
  }
  return;
}


// howl_StopAudio
// param_1: clear backup stats too
// param_2: bool destroy music
// param_3: bool destroyAllFX (or just most)
void FUN_8002c8a8(int param_1,int param_2,undefined4 param_3)
{

  // if not only stopping engineFX,
  // if stopping all audio
  if (param_2 != 0)
  {
	// CseqMusic_StopAll
    FUN_80029258();
  }

  // enter critical section
  FUN_8002b4d0();

  // Channel_DestroyAll_LowLevel
  // param_3 -> param1
  // invert param2
  // '2' means skip music "sometimes"
  FUN_8002ba90(param_3,(uint)(param_2 == 0),2);

  // exit critical section
  FUN_8002b508();

  if (param_1 != 0)
  {
	// numBackup_ChannelStats
    DAT_8008d790 = 0;
  }
  return;
}


// Voiceline_PoolInit
// does not really touch voiceline
void FUN_8002c918(void)

{
  undefined *puVar1;
  undefined4 *puVar2;
  int vNum;
  undefined4 *puVar3;

  // reset criticalSectionCount
  DAT_8008d78c = 0;

  // numBackup_ChannelStats
  DAT_8008d790 = 0;

  // reset ptrCseqHeader
  DAT_8008d7b0 = 0;

  // Bank_ResetAllocator
  FUN_800292e0();

  // Audio_SetDefaults
  FUN_8002dc4c();

  // LIST_Clear channelFree
  FUN_80031734(&DAT_80090578);

  // LIST_Clear channelTaken
  FUN_80031734(&DAT_8009056c);

  // first member in list
  puVar1 = &DAT_80095e94;

  // LIST_Init
  FUN_8003197c(&DAT_80090578,&DAT_80095e94,0x20,0x18);

  SpuSetReverbVoice(0,0xffffff);

  // loop counter
  vNum = 0;

  puVar2 = &DAT_8008fe4c;
  puVar3 = &DAT_8008fc6c;

  // initialize all members in sound list
  // for vNum = 0; vNum < 0x18 (24); vNum++
  do
  {
    SpuSetVoiceADSRAttr(vNum,0,0xf,0x7f,2,0xf,5,1,3);
	
    puVar1[8] = 0;
    puVar1[9] = (char)vNum;

	// ADSR
	*(undefined2 *)(puVar1 + 0x12) = 0x80ff;
    *(undefined2 *)(puVar1 + 0x14) = 0x1fc2;

	*puVar3 = 0;
    *puVar2 = 0xffffffff;

	// ADSR
    *(undefined2 *)(puVar2 + 1) = 0x80ff;
    *(undefined2 *)((int)puVar2 + 6) = 0x1fc2;

	// clear rest of channelAttr to 0xFFFF
	*(undefined2 *)(puVar2 + 2) = 0xffff;
    *(undefined2 *)((int)puVar2 + 10) = 0xffff;
    *(undefined2 *)(puVar2 + 3) = 0xffff;
    *(undefined2 *)((int)puVar2 + 0xe) = 0xffff;
	
    puVar2 = puVar2 + 4;
    puVar3 = puVar3 + 1;

	// increment loop counter
    vNum = vNum + 1;

    puVar1 = puVar1 + 0x20;
  } while (vNum < 0x18);

  // loop counter
  vNum = 0;

  // song pool
  puVar1 = &DAT_80095d84;

  // for vNum = 0; vNum < 2; vNum++
  do
  {
	// not playing
    *puVar1 = 0;

	// id
    puVar1[1] = (char)vNum;

	// increment loop counter
    vNum = vNum + 1;

	// next slot
    puVar1 = puVar1 + 0x7c;

  } while (vNum < 2);

  // loop counter
  vNum = 0;

  // song seqs
  puVar1 = &DAT_800902cc;

  // for vNum = 0; vNum < 0x18 (24); vNum++
  do
  {
	// not playing
    *puVar1 = 0;

	// id
    puVar1[1] = (char)vNum;

	// increment loop counter
    vNum = vNum + 1;

	// next slot
    puVar1 = puVar1 + 0x1c;

  } while (vNum < 0x18);
  return;
}


// Voiceline_ClearTimeStamp
void FUN_8002caa8(void)

{
  undefined4 *puVar1;
  undefined4 *puVar2;

  // loop counter
  int iVar3;
  iVar3 = 0;

  // audio timestamps
  puVar2 = &DAT_80096284;
  puVar1 = &DAT_80096244;

  // for iVar3 = 0; iVar3 < 0x10 (16); iVar3++
  do
  {
    *puVar1 = 0;
    *puVar2 = 0;
    puVar2 = puVar2 + 1;

	// increment loop counter
	iVar3 = iVar3 + 1;

	puVar1 = puVar1 + 1;
  } while (iVar3 < 0x10);
  return;
}


// Voiceline_PoolClear
void FUN_8002cae0(void)

{

  // boolCanPlayWrongWaySFX = False
  DAT_8008d7ed = 0;

  // voicelineCooldown = 0
  DAT_8008d7ee = 0;

  // boolCanPlayVoicelines = False
  DAT_8008d7ec = 0;

  // LIST_Clear free
  FUN_80031734(&DAT_800961a4);

  // LIST_Clear taken
  FUN_80031734(&DAT_800961b4);

  // LIST_Init
  // put them all on free list
  FUN_8003197c(&DAT_800961a4,&DAT_800961c4,0x10,8);

  // Voiceline_ClearTimeStamp
  FUN_8002caa8();
  return;
}


// Voiceline_StopAll
void FUN_8002cb44(void)

{
  int iVar1;

  // if taken->last exists
  if (DAT_800961b8 != 0)
  {
	// loop until all voicelines removed
    do
	{
	  // taken->last
      iVar1 = DAT_800961b8;

	  // LIST_RemoveMember taken
      FUN_800317e4(&DAT_800961b4,DAT_800961b8);

	  // LIST_AddFront free
      FUN_80031744(&DAT_800961a4,iVar1);

	} while (DAT_800961b8 != 0);
  }
  return;
}


// Voiceline_ToggleEnable
void FUN_8002cbb4(int param_1)
{
  // if this is disabling
  if (param_1 == 0)
  {
	// erase voicelineCooldown
    DAT_8008d7ee = 0;

	// Voiceline_StopAll
    FUN_8002cb44();
  }

  // set new boolCanPlayVoicelines
  DAT_8008d7ec = (char)param_1;

  return;
}


// Play Driver Voice
// param1 - voiceID
// param2 - characterID
// param3 - characterID
void FUN_8002cbe8(uint param_1,uint param_2,uint param_3)

{
  byte bVar1;
  bool bVar2;
  bool bVar3;
  bool bVar4;
  bool bVar5;
  undefined *puVar6;
  int iVar7;
  uint uVar8;
  int *piVar9;
  int iVar10;

  // voiceID
  // Final game has 0x13 total,
  // but 0x18 were planned
  if (0x17 < param_1) {
    return;
  }

  // param_2 is character ID,
  if (0xf < param_2) {
    return;
  }

  // param_3 is character ID (or 0x10 for null)
  if (0x10 < param_3) {
    return;
  }

  // If you're in End-Of-Race menu
  if ((*(uint *)PTR_DAT_8008d2ac & 0x200000) != 0) {
    return;
  }

  bVar1 = (&DAT_800838dc)[param_1];
  if (7 < (int)param_1) {
    if (((&DAT_80096244)[param_2] & 1 << (param_1 & 0x1f)) == 0) 
	{
	  // inline audioRNG scramble
      DAT_8008d058 = ((DAT_8008d058 >> 3) + DAT_8008d058 * 0x20000000) * 5 + 1;
	  
      uVar8 = DAT_8008d058 & 3;
    }
    else 
	{
	  // inline audioRNG scramble
      DAT_8008d058 = ((DAT_8008d058 >> 3) + DAT_8008d058 * 0x20000000) * 5 + 1;
      
	  uVar8 = DAT_8008d058 & 7;
    }
    if (uVar8 != 0) {
      return;
    }
  }

  // If player spoke more than two seconds ago
  bVar2 = 0x3c < (uint)(*(int *)(PTR_DAT_8008d2ac + 0x1cf8) - (&DAT_80096284)[param_2]);

  bVar5 = bVar1 < 2;

  bVar4 = bVar2 && bVar5;

  if (
		// if !boolCanPlayVoicelines
		(DAT_8008d7ec == '\0') ||
		(
			(
				(
					// if voicelineCooldown is not done
					DAT_8008d7ee != 0 &&

					((uint)DAT_8009619e == param_2)
				) ||
				(
					bVar3 = true,

					// If player spoke less than two seconds ago
					(uint)(*(int *)(PTR_DAT_8008d2ac + 0x1cf8) - (&DAT_80096284)[param_2]) < 0x3c
				)
			)
		)
	 )
  {
    bVar3 = false;
  }
  if (bVar3) {
    if (!bVar2 || !bVar5) goto LAB_8002ce20;
	
	// inline audioRNG scramble
    DAT_8008d058 = ((DAT_8008d058 >> 3) + DAT_8008d058 * 0x20000000) * 5 + 1;
    
	bVar4 = false;
    if ((DAT_8008d058 & 1) == 0) goto LAB_8002cdcc;
  }
  else {
    if (!bVar2 || !bVar5) {
      return;
    }
LAB_8002cdcc:
    if (!bVar4) {
LAB_8002ce20:
      if (!bVar3) {
        return;
      }
      (&DAT_80096244)[param_2] = (&DAT_80096244)[param_2] | 1 << (param_1 & 0x1f);

	  // voiceline list taken last
	  iVar10 = DAT_800961b8;

	  // voiceline list free first
      iVar7 = DAT_800961a4;

	  // voiceline list taken first
	  piVar9 = (int *)DAT_800961b4;

	  // check all voicelines
      while (piVar9 != (int *)0x0)
	  {
		// if this voiceline is already playing
        if ((param_1 == (int)*(short *)(piVar9 + 2)) &&
           (param_2 == (uint)*(byte *)((int)piVar9 + 10)))
		{
		  // quit
          return;
        }

		// next voiceline
        piVar9 = (int *)*piVar9;
      }

	  // if voiceline free->first is null
      if (DAT_800961a4 == 0)
	  {
		// if voiceline taken->back is null
        if (DAT_800961b8 == 0) goto LAB_8002cee4;

		// LIST_RemoveMember taken->back
        FUN_800317e4(&DAT_800961b4,DAT_800961b8);
      }

	  // if free voicelines are available
      else
	  {
		// LIST_RemoveMember free->first
        FUN_800317e4(&DAT_800961a4,DAT_800961a4);

		iVar10 = iVar7;
      }

	  // LIST_AddFront taken
      FUN_80031744(&DAT_800961b4,iVar10);

LAB_8002cee4:

	  // save voiceline parameters
      *(undefined *)(iVar10 + 10) = (char)param_2;
      *(undefined *)(iVar10 + 0xb) = (char)param_3;
      puVar6 = PTR_DAT_8008d2ac;
      *(undefined2 *)(iVar10 + 8) = (short)param_1;

	  // voiceline -> startFrame
      *(undefined4 *)(iVar10 + 0xc) = *(undefined4 *)(puVar6 + 0x1cec);
      return;
    }
  }
  if (bVar1 == 0) {
    uVar8 = param_2 + 0x1c;
  }
  else {
    if (bVar1 != 1) goto LAB_8002ce00;
    uVar8 = param_2 + 0x2c;
  }

  // OtherFX_Play
  FUN_80028468(uVar8 & 0xffff,2);

LAB_8002ce00:

  // store time stamp, with frameTimer_MainFrame_ResetDB
  (&DAT_80096284)[param_2] = *(undefined4 *)(PTR_DAT_8008d2ac + 0x1cf8);

  return;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address

// Voiceline_StartPlay
void FUN_8002cf28(undefined4 *param_1)

{
  ushort uVar1;
  int iVar2;
  uint uVar3;
  int *piVar4;
  int iVar5;

  DAT_80096194 = *param_1;
  DAT_80096198 = param_1[1];
  _DAT_8009619c = param_1[2];
  DAT_800961a0 = param_1[3];

  if (
		(
			// If you're in a Boss Race
			// 0x80000000
			(*(int *)PTR_DAT_8008d2ac < 0) &&
			((uint)*(ushort *)(param_1 + 2) - 10 < 6)
		) &&
		(
			(
				// if character is 8,9, 10, 11
				// pinstripe, papu, roo, or k-joe
				(uint)*(byte *)((int)param_1 + 10) - 8 < 4 ||

				// if character is 15 - Oxide
				(*(byte *)((int)param_1 + 10) == 0xf)
			)
		)
	)
  {
	// inline audioRNG scramble
    DAT_8008d058 = ((DAT_8008d058 >> 3) + DAT_8008d058 * 0x20000000) * 5 + 1;
    
	uVar3 = (DAT_8008d058 & 3) + 4;
  }

  else
  {
    uVar3 = (uint)(byte)(&DAT_800838dc)[*(short *)(param_1 + 2)];
  }

												// boss character ID
  piVar4 = (int *)((&PTR_PTR_DAT_8008389c)[*(byte *)((int)param_1 + 10)] + uVar3 * 8);
  uVar1 = *(ushort *)(piVar4 + 1);
  if (uVar1 == 0)
  {
	// Voiceline_StopAll
    FUN_8002cb44();
  }
  else 
  {
	// inline audioRNG scramble
    DAT_8008d058 = ((DAT_8008d058 >> 3) + DAT_8008d058 * 0x20000000) * 5 + 1;
    
	if (uVar1 == 0) {
      trap(0x1c00);
    }
    iVar5 = (DAT_8008d058 % (uint)uVar1) * 2;

	// CDSYS_XAPlay(CDSYS_XA_TYPE_GAME, number);
    iVar2 = FUN_8001cdb4(2,(uint)*(ushort *)(iVar5 + *piVar4));

	// if audio failed to play
    if (iVar2 == 0)
	{
	  /*
	  From Aug 5
FUN_8006fbac("CDSYS_XAPlay( CDSYS_XA_TYPE_GAME, %d ) Failed\n",
                   (uint)*(ushort *)(iVar3 + *piVar4));
	  */

	  // try again in 30 frames (1 second)
      DAT_8008d7ee = 0x1e;
    }

    // if audio can play
    else 
    {
      // CDSYS_XAGetTrackLength
      iVar2 = FUN_8001cd20(2,(uint)*(ushort *)(iVar5 + *piVar4));
			= (short)(iVar2 / 5) + 0x1e;
    }
  }
  return;
}

// Voiceline_Update
void FUN_8002d0f8(void)

{
  bool bVar1;
  short sVar2;
  uint uVar3;
  int iVar4;
  undefined4 uVar5;

  // voiceline list taken->first
  iVar4 = DAT_800961b4;

  // if !boolCanPlayVoicelines
  if (DAT_8008d7ec == '\0') {
    return;
  }

  // cooldown timer
  // This prevents "wrong way", and character voice effects,
  // from happening within one full second of each other (0x1e frames)
  sVar2 = DAT_8008d7ee + -1;
  if ((DAT_8008d7ee != 0) && (bVar1 = DAT_8008d7ee != 1, DAT_8008d7ee = sVar2, bVar1)) {
    return;
  }

  if (DAT_8008d708 != 0) {
    return;
  }

  // if (canPlayWrongWaySFX)
  if (DAT_8008d7ed != '\0')
  {

    // if ((WrongWay_bool == True) && (framesDrivingSameDirection > 0x1E)) AND
    if (
    (
			(DAT_8008d9dc != '\0') &&
			(0x1e < DAT_8008d9e4)
		) &&

    // AND
    (
			// canPlayWrongWaySFX = False
			DAT_8008d7ed = '\0',

			// if numPlyrCurrGame is 1
			PTR_DAT_8008d2ac[0x1ca8] == '\x01')
	   )
	{
	  // VehPickupItem_MaskBoolGoodGuy
      uVar3 = FUN_80064be4(*(undefined4 *)(PTR_DAT_8008d2ac + 0x24ec));

	  // if you use uka
      if ((uVar3 & 0xffff) == 0)
	  {
		// CDSYS_XAPlay(CDSYS_XA_TYPE_EXTRA, SPEAK_UKA_39);
        iVar4 = FUN_8001cdb4(1,0x3d);

		// if audio failed to play
        if (iVar4 == 0)
		{
		  // sep 3
		  // fmt = "CDSYS_XAPlay( CDSYS_XA_TYPE_EXTRA, SPEAK_UKA_39 (wrong way) ) Failed\n";

		  // try again in 30 frames (1 second)
          DAT_8008d7ee = 0x1e;
          return;
        }

		// use ID (0x3d) to get audio length
        uVar5 = 0x3d;
      }

	  // if you use aku
      else
	  {
		// CDSYS_XAPlay(CDSYS_XA_TYPE_EXTRA, 0x1e);
        iVar4 = FUN_8001cdb4(1,0x1e);

		// if audio failed to play
        if (iVar4 == 0)
		{
		  // sep 3
		  // fmt = "CDSYS_XAPlay( CDSYS_XA_TYPE_EXTRA, SPEAK_AKU_39 (wrong way) ) Failed\n";

		  // try again in 30 frames (1 second)
          DAT_8008d7ee = 0x1e;
          return;
        }

		// use ID (0x1e) to get audio length
        uVar5 = 0x1e;
      }

      iVar4 = FUN_8001cd20(1,uVar5);

	  // voicelineCooldown is length + 30 frames
      DAT_8008d7ee = (short)(iVar4 / 5) + 0x1e;

      return;
    }

    // if (canPlayWrongWaySFX == True) goto ???
    if (DAT_8008d7ed != '\0') goto LAB_8002d268;
  }

  // if (WrongWay_bool == False) && (framesDrivingSameDirection > 0x1E)
  if ((DAT_8008d9dc == '\0') && (0x1e < DAT_8008d9e4)) {

    // canPlayWrongWaySFX = True
    DAT_8008d7ed = '\x01';
  }

LAB_8002d268:
  if (DAT_800961b4 != 0)
  {
	// LIST_RemoveMember taken
    FUN_800317e4(&DAT_800961b4,DAT_800961b4);

	// LIST_AddBack free
    FUN_80031788(&DAT_800961a4,iVar4);

	// Voiceline_StartPlay
    FUN_8002cf28(iVar4);
  }

  return;
}


// Intentionally empty by naughty dog
// Pure 8-byte empty function
// Voiceline_EmptyFunc
void FUN_8002d2a8(void)

{
  return;
}


// Voiceline_SetDefaults
void FUN_8002d2b0(void)

{
  DAT_8008d7f0 = 0;
  DAT_8008d7f4 = 0;
  DAT_8008d7f2 = 0;

  // WrongWay_bool = False
  DAT_8008d9dc = 0;

  // framesDrivingSameDirection = 0
  DAT_8008d9e4 = 0;
  DAT_8008d7fa = 0;
  DAT_8008d7fc = 0;

  // Music_SetDefaults
  FUN_8002e338();
  return;
}


// Audio_SetState
void FUN_8002d2f4(undefined4 param_1)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;

  switch(param_1)
  {
	// stop/pause cseq music (main: case 2)
  case 1:
    DAT_8008d7fc = 0;

	// CDSYS_XAPauseRequest
    FUN_8001cf98();

	// Music_Restart
	FUN_8002e4c0();

	// howl_StopAudio
	// erase backup, keep music, stop all fx
    FUN_8002c8a8(1,0,1);
    break;

  case 2:
  case 7:

	// CseqMusic_StopAll
	FUN_80029258();

	// Music_Adjust
    FUN_8002e350(0,0,0,0);

    break;
  case 5:

    // CseqMusic_StopAll
    FUN_80029258();

	// Level ID on Adventure Arena
    if (*(int *)(PTR_DAT_8008d2ac + 0x1a10) - 0x19U < 5) {

	  // Music_Adjust, convert levelID to a bitshifted flag
      FUN_8002e350(0,0,&DAT_8008d068,1 << (*(int *)(PTR_DAT_8008d2ac + 0x1a10) - 0x19U & 0x1f));
    }
    break;
  case 9:

	// CDSYS_XAPlay(CDSYS_XA_TYPE_MUSIC, x)
    FUN_8001cdb4(0,(int)DAT_8008d7f2);

    iVar1 = (int)DAT_8008d7f2 + 1;
    iVar3 = iVar1;
    if (iVar1 < 0) {
      iVar3 = (int)DAT_8008d7f2 + 4;
    }
    DAT_8008d7f2 = (short)iVar1 + (short)(iVar3 >> 2) * -4;
    break;
  case 10:

	// Music_Stop
    FUN_8002e4ec();

	// CseqMusic_StopAll
    FUN_80029258();
    break;
  case 0xb:

    // WrongWay_bool = False
    DAT_8008d9dc = 0;

    // framesDrivingSameDirection = 0
    DAT_8008d9e4 = 0;

	// Voiceline_ToggleEnable
    FUN_8002cbb4(1);
    break;

  case 0xc:

  // last lap, distToFinish < 9000
  case 0xf:

    // Voiceline_ToggleEnable
	FUN_8002cbb4(0);

    DAT_8008d7fc = 1;
    break;

  // if you are on last lap
  case 0xd:
    DAT_8008d7fc = 0;

	// Music_LowerVolume
    FUN_8002e418();

	// CDSYS_XA_TYPE_MUSIC
    uVar2 = 0;

	// MUSIC_LAST_LAP
    iVar3 = 6;

    goto LAB_8002d4b4;
  case 0xe:

    // WrongWay_bool = False
    DAT_8008d9dc = 0;

    // framesDrivingSameDirection = 0
    DAT_8008d9e4 = 0;

	// Music_RaiseVolume
    FUN_8002e46c();

	// Voiceline_ToggleEnable
    FUN_8002cbb4(1);

    break;
  case 0x10:
    DAT_8008d7fc = 0;

	// Music_Restart
    FUN_8002e4c0();

	// set XA
    iVar3 = (int)DAT_8008d7f8;

	// CDSYS_XA_TYPE_MUSIC
    uVar2 = 0;

    if (0x3d < iVar3)
	{
	  // CDSYS_XA_TYPE_EXTRA
      uVar2 = 1;
    }
LAB_8002d4b4:

	// CDSYS_XAPlay
    FUN_8001cdb4(uVar2,iVar3);
  }
  return;
}


// Audio_SetState_Safe
void FUN_8002d4cc(int param_1)

{
  // If this sound isn't already playing
  if (param_1 != (int)DAT_8008d7f0)
  {
	// Voiceline_EmptyFunc
    FUN_8002d2a8();

	// Audio_SetState
    FUN_8002d2f4(param_1);

	// set which sound is playing
    DAT_8008d7f0 = (short)param_1;
  }
  return;
}


// Audio_AdvHub_SwapSong
void FUN_8002d50c(int param_1)

{
  if (
		(DAT_8008d7f0 == 5) &&

		// If you're on a map in the Adventure Arena
		(param_1 - 0x19U < 5)
	  )
  {
	// CseqMusic_AdvHubSwap
    FUN_800290cc(0,&DAT_8008d068,1 << (param_1 - 0x19U & 0x1f));
  }
  return;
}


// Audio_SetMaskSong
void FUN_8002d554(undefined4 param_1)

{
  bool bVar1;
  int iVar2;
  uint uVar3;
  undefined *puVar4;
  undefined4 uVar5;

  // Assume no player is using a mask
  bVar1 = false;

  // loop counter
  iVar2 = 0;

  puVar4 = PTR_DAT_8008d2ac;

  // if numPlyrCurrGame is not zero
  if (PTR_DAT_8008d2ac[0x1ca8] != 0) {

  // for(int iVar2 = 0; iVar2 < numPlyrCurrGame; iVar2++)
	do
	{
      //if player is using mask weapon
      if ((*(uint *)(*(int *)(puVar4 + 0x24ec) + 0x2c8) & 0x800000) != 0)
	  {
		// There is at least one player using a mask
        bVar1 = true;
      }

	  // increment iteration counter
      iVar2 = iVar2 + 1;

	  // increment pointer
      puVar4 = puVar4 + 4;

	  //               numPlyrCurrGame
    } while (iVar2 < (int)(uint)(byte)PTR_DAT_8008d2ac[0x1ca8]);
  }

  // If any player is using a mask
  if (bVar1)
  {
	// Uka song is playing
    uVar5 = 2;

    if (
		// If Uka song is playing
		((*(uint *)PTR_DAT_8008d2ac & 0x2000000) != 0) ||

		(
			// Aku song is playing
			uVar5 = 1,

			// If Aku song is playing
			(*(uint *)PTR_DAT_8008d2ac & 0x1000000) != 0
		)
	  )
	{
	  // Music_Adjust
      FUN_8002e350(uVar5,param_1,0,0);
    }
  }

  // If no players are using mask
  else
  {
	// Music_Adjust
    FUN_8002e350(0,param_1,0,0);

	// Copy game state into uVar3
    uVar3 = *(uint *)PTR_DAT_8008d2ac;

	// If you're in End-Of-Race menu
	if ((uVar3 & 0x2000000) != 0) {

	  // Leave End-Of-Menu, leave Adventure Arena
      *(uint *)PTR_DAT_8008d2ac = uVar3 & 0xfdffffff;

	  // Copy game state into uVar3
      uVar3 = *(uint *)PTR_DAT_8008d2ac;
    }

	// If you're in Adventure Arena wouldn't happen
	// if you just left End-Of-Race menu
    if ((uVar3 & 0x1000000) != 0) {
	  // Leave Adventure Arena
      *(uint *)PTR_DAT_8008d2ac = uVar3 & 0xfeffffff;
    }
  }
  return;
}


// Audio_Update1
void FUN_8002d67c(void)

{
  undefined2 uVar1;
  uint uVar2;
  int iVar3;
  undefined4 uVar4;
  int iVar5;
  undefined *puVar6;
  int iVar7;
  int iVar8;

  iVar7 = 0;
  switch((int)(((uint)DAT_8008d7f0 - 1) * 0x10000) >> 0x10) {
  case 5:
    if ((DAT_8008d708 == 0) || (DAT_8008d6e4 != 0))
	{
	  // Audio_SetState_Safe
      FUN_8002d4cc(5);
    }
    break;
  case 7:
	// Garage_LerpFX
    FUN_800304b8();
    break;
  case 8:
    if (DAT_8008d708 == 0)
	{
      // 9 means intro cutscene
	  // 10 means traffic lights
	  // 11 means racing

	  // Change state to traffic lights
	  // Audio_SetState_Safe
      FUN_8002d4cc(10);
    }
    break;
  case 9:
    // If traffic lights finish counting down
	// from 0x3840 to zero
    if (*(int *)(PTR_DAT_8008d2ac + 0x1d0c) < 1)
	{
    // 9 means intro cutscene
	// 10 means traffic lights
	// 11 means racing

	  // Change State to 11, which means racing
	  // Audio_SetState_Safe
      FUN_8002d4cc(0xb);
    }
    break;
  case 10:

    // Audio_SetMaskSong
    FUN_8002d554(0);

	// loop counter
    iVar5 = 0;

	puVar6 = PTR_DAT_8008d2ac;

	// for iVar5 = 0; iVar5 < 8; iVar5++
	do
	{
	  // Get driver, in order of their race rank (1st place, 2nd, etc)
      iVar3 = *(int *)(puVar6 + 0x250c);


      if (
			// If the driver pointer is not nullptr
			(iVar3 != 0) &&

			// If this driver is human, and not AI
			((*(uint *)(iVar3 + 0x2c8) & 0x100000) == 0)
		 ) break;

	  // increment loop counter
      iVar5 = iVar5 + 1;

      puVar6 = puVar6 + 4;
      iVar3 = iVar7;

    } while (iVar5 < 8);

	// Voiceline_Update
    FUN_8002d0f8();

	// Level_AmbientSound
    FUN_8002ebe4();

    if (
			(
				// if race has more than 2 laps
				(2 < (int)(char)PTR_DAT_8008d2ac[0x1d33]) &&
				(
					// if you are on 2nd to last lap
					(uint)*(byte *)(iVar3 + 0x44) == (int)(char)PTR_DAT_8008d2ac[0x1d33] - 2U)
				) &&

				// distToFinish is small
				(*(int *)(iVar3 + 0x488) < 9000)
		)
	{
	  // Audio_SetState_Safe
      FUN_8002d4cc(0xc);
    }
    break;
  case 0xb:

    // Audio_SetMaskSong
    FUN_8002d554(0);

	// loop counter
    iVar5 = 0;
    puVar6 = PTR_DAT_8008d2ac;

	// for iVar5 = 0; iVar5 < 8; iVar5++
	do
	{
	  // Get driver, in order of their race rank (1st place, 2nd, etc)
      iVar3 = *(int *)(puVar6 + 0x250c);

      if (
			// If the driver pointer is not nullptr
			(iVar3 != 0) &&

			// If this driver is human, and not AI
			((*(uint *)(iVar3 + 0x2c8) & 0x100000) == 0)
		  ) break;

	  // increment loop counter
	  iVar5 = iVar5 + 1;

      puVar6 = puVar6 + 4;
      iVar3 = iVar7;
    } while (iVar5 < 8);

    if (((DAT_8008d7fc != '\0') && (DAT_8008d708 == 0)) &&
       (9 < (uint)(*(int *)(PTR_DAT_8008d2ac + 0x1cf8) - DAT_8008d6ec)))
	{
	  // high distToFinish
      if (2000 < *(int *)(iVar3 + 0x488))
	  {
		// CDSYS_XASeek (FINAL LAP! music)
        FUN_8001cc18(1,0,6);
      }
      DAT_8008d7fc = '\0';
    }

	// Level_AmbientSound
    FUN_8002ebe4();

	// if driver is on final lap
    if ((uint)*(byte *)(iVar3 + 0x44) == (int)(char)PTR_DAT_8008d2ac[0x1d33] - 1U)
	{
	  // Play final lap sound
	  // Audio_SetState_Safe
      FUN_8002d4cc(0xd);
    }
    break;
  case 0xc:
    uVar4 = 0;

	// if XA has been playing more than a second
    if (0xe1 < DAT_8008d6f8)
	{
	  // Music_RaiseVolume
      FUN_8002e46c(0);

      uVar4 = 0x14;
    }

	// Audio_SetMaskSong
	FUN_8002d554(uVar4);

	// Level_AmbientSound
    FUN_8002ebe4();

    if (DAT_8008d708 == 0)
	{
	  // Audio_SetState_Safe
      FUN_8002d4cc(0xe);
    }
    break;
  case 0xd:

    // Audio_SetMaskSong
    FUN_8002d554(0x14);

	// loop counter
    iVar5 = 0;
    puVar6 = PTR_DAT_8008d2ac;

	// for iVar5 = 0; iVar5 < 8; iVar5++
	do
	{
	  // Get driver, in order of their race rank (1st place, 2nd, etc)
      iVar3 = *(int *)(puVar6 + 0x250c);

      if (
			// If the driver pointer is not nullptr
			(iVar3 != 0) &&

			// If this driver is human, and not AI
			((*(uint *)(iVar3 + 0x2c8) & 0x100000) == 0)
		 ) break;

	  // increment loop counter
      iVar5 = iVar5 + 1;

	  puVar6 = puVar6 + 4;
      iVar3 = iVar7;
    } while (iVar5 < 8);

	// Voiceline_Update
    FUN_8002d0f8();

	// Level_AmbientSound
    FUN_8002ebe4();

	// if driver's lap is the last lap
	if (((uint)*(byte *)(iVar3 + 0x44) == (int)(char)PTR_DAT_8008d2ac[0x1d33] - 1U) &&

	   // if distToFinish is less than 9000
	   (*(int *)(iVar3 + 0x488) < 9000))
	{
	  // Audio_SetState_Safe
      FUN_8002d4cc(0xf);
    }

    break;
  case 0xe:

    // loop counter
    iVar5 = 0;
    puVar6 = PTR_DAT_8008d2ac;

	// for iVar5 = 0; iVar5 < 8; iVar5++
	do
	{
	  // get drivers in order of 1st, 2nd, 3rd, etc
      iVar3 = *(int *)(puVar6 + 0x250c);

      if (
			// if the driver is valid
			(iVar3 != 0) &&
			(
				// copy loop iteration
				iVar8 = iVar5,

				// driver -> instance -> thread -> modelIndex
				*(short *)(*(int *)(*(int *)(iVar3 + 0x1c) + 0x6c) + 0x44) == 0x18
			)
		) break;

	  // increment loop counter
	  iVar5 = iVar5 + 1;

	  puVar6 = puVar6 + 4;
      iVar3 = iVar7;
      iVar8 = -1;
    } while (iVar5 < 8);

    if (((DAT_8008d7fc != '\0') && (DAT_8008d708 == 0)) &&
       (9 < (uint)(*(int *)(PTR_DAT_8008d2ac + 0x1cf8) - DAT_8008d6ec)))
	{
	  // high distToFinish
      if (2000 < *(int *)(iVar3 + 0x488))
	  {
		// CDSYS_XASeek (Victory Fanfare music)
        FUN_8001cc18(1,0,4);
      }
      DAT_8008d7fc = '\0';
    }

	// Level_AmbientSound
    FUN_8002ebe4();

    //if the race is over for this racer
    if ((*(uint *)(iVar3 + 0x2c8) & 0x2000000) != 0) 
	{
	  // if did not just open N Tropy
      if ((*(uint *)(PTR_DAT_8008d2ac + 0x1d44) & 0x8000) == 0) 
	  {

		// If you did not just beat N Tropy in Time Trial
        if ((*(uint *)(PTR_DAT_8008d2ac + 0x1d44) & 0x10000000) == 0)
		{
		  // If you ended a race of a cup
          if (
				(
					(iVar8 == 0) ||

					// If you are in Adventure cup
					((*(uint *)PTR_DAT_8008d2ac & 0x10000000) != 0)
				) ||

				(uVar1 = 5,

				// If you are in Arcade or VS cup
				(*(uint *)(PTR_DAT_8008d2ac + 8) & 0x10) != 0)
			 )
		  {
			// OtherFX_Play
            FUN_80028468(0x5f,0);

            uVar1 = 4;
          }
        }

		// If you just beat N Tropy in Time Trial
        else
		{
		  // GAMEPROG_CheckGhostsBeaten(ntropy)
          uVar2 = FUN_80026ae4(1);

		  // If there is a track where N Tropy has not been beaten
          if ((uVar2 & 0xffff) == 0)
		  {
			// OtherFX_Play
            FUN_80028468(0x5f,0);

			// count how many times N Tropy has been beaten
			// during this playthrough
            iVar7 = (int)DAT_8008d7fa;
            DAT_8008d7fa = DAT_8008d7fa + 1;
			
			// pick an N Tropy XA voiceline
            uVar1 = *(undefined2 *)(&DAT_80083908 + iVar7 * 2);
            
			// if beaten more than 5 times
			if (5 < DAT_8008d7fa) 
			{
			  // go back to 0
              DAT_8008d7fa = 0;
            }
          }

		  // If N Tropy has been beaten on all tracks
          else
		  {
			// OtherFX_Play
            FUN_80028468(0x5f,0);

			// N Tropy Unlocked XA
			// "you've earned the right to choose me in character selection"
            uVar1 = 0x43;
          }
        }
      }
	  
	  // if n tropy just opened
      else
	  {
		// OtherFX_Play
        FUN_80028468(0x5f,0);

		// N Tropy opened
		// "Think your fast eh, well, lets see if you can beat my fastest time"
        uVar1 = 0x46;
      }

	  // desired XA
      DAT_8008d7f8 = uVar1;

	  // Audio_SetState_Safe
      FUN_8002d4cc(0x10);
    }
    break;
  case 0xf:

	// Level_AmbientSound
    FUN_8002ebe4();

    if (DAT_8008d708 == 0)
	{
	  // Audio_SetMaskSong
      FUN_8002d554(0);
    }
  }
  return;
}


// Audio_SetDefaults
void FUN_8002dc4c(void)

{
  // AI Engine Sounds?
  DAT_8008d818 = 0;
  DAT_8008d81c = 0;
  DAT_8008d820 = 0;
  DAT_8008d824 = 0;

  DAT_8008d828 = 0x80;
  DAT_8008d82c = 0x80;
  DAT_8008d830 = 0;
  DAT_8008d834 = 0;
  DAT_8008d838 = 0;
  
  // erase both SoundFadeInput
  DAT_800962c4 = 0;
  DAT_800962c8 = 0;
  DAT_800962cc = 0;
  DAT_800962d0 = 0;
  DAT_800962d4 = 0;
  DAT_800962d8 = 0;
  DAT_800962dc = 0;
  DAT_800962e0 = 0;
  
  return;
}


// param1 = levelID
// param2 = isBossLevel boolean
// param3 = bossID
// Audio_SetReverbMode
void FUN_8002dcac(int param_1,int param_2,int param_3)

{
  uint uVar1;

  // if audio is enabled
  if (DAT_8008d05c != '\0')
  {
	// If this is not a boss race
    if (param_2 == 0) {

	  // Level ID < 30
	  // If Level ID is any level you can drive on,
	  // including adventure maps
      if (param_1 < 0x1e)
	  {
		// get reverb based on level ID
        uVar1 = (uint)(byte)(&DAT_80083914)[param_1];
      }

	  // If this is not a level you can drive on:
	  // menu, cutscene, etc
      else {
        uVar1 = 4;
      }
    }

	// If this is a boss race
	else
	{
	  // if invalid bossID
      if (5 < param_3)
	  {
		// quit
        return;
      }

	  // get reverb based on boss
      uVar1 = (uint)(byte)(&DAT_8008d070)[param_3];
    }

	// SetReverbMode
    FUN_80028bbc(uVar1);
  }
  return;
}


// Music_SetIntro
void FUN_8002dd24(void)

{
  int iVar1;
  undefined auStack16 [8];

  DAT_8008d834 = 0;

  // Bank_Load
  FUN_800297a0(0x21,auStack16);

  do
  {
	// Bank_AssignSpuAddrs
    iVar1 = FUN_800293b8();

  } while (iVar1 == 0);

  // howl_SetSong
  FUN_80029c40(0x1c);

  do 
  {
	// howl_LoadSong
    iVar1 = FUN_80029ca4();
  } while (iVar1 == 0);
  return;
}


// Music_LoadBanks
void FUN_8002dd74(void)

{
  undefined4 uVar1;
  undefined auStack16 [8];

  // Audio_SetReverbMode
  FUN_8002dcac(
				// Level ID
				*(undefined4 *)(PTR_DAT_8008d2ac + 0x1a10),

				// Check to see if this is a boss race
				*(uint *)PTR_DAT_8008d2ac & 0x80000000,

				// Boss ID
               *(undefined4 *)(PTR_DAT_8008d2ac + 0x1eb8));

  // if LevelID == 30
  // Intro Cutscene Coco+Pura
  if (*(int *)(PTR_DAT_8008d2ac + 0x1a10) == 0x1e)
  {
	// Bank_DestroyAll
    FUN_800298e4();

    uVar1 = 0x22;
  }

  else
  {
	// if level ID is not 41
	// if not Naughty Dog Box
    if (*(int *)(PTR_DAT_8008d2ac + 0x1a10) != 0x29)
	{
      if (DAT_8008d834 == '\0')
	  {
		// Bank_DestroyAll
        FUN_800298e4();

		// Bank_Load
        FUN_800297a0(0,auStack16);

        DAT_8008d834 = '\x01';
      }

      else
	  {
		// Bank_DestroyUntilIndex(0)
        FUN_80029870(0);
      }

	  // loading state of song (one byte)
      DAT_8008d835 = 0;
      return;
    }

	// if it is naughty dog box scene

	// Bank_DestroyAll
    FUN_800298e4();

    uVar1 = 0x21;
  }

  DAT_8008d834 = 0;

  // Bank_Load
  FUN_800297a0(uVar1,auStack16);

  // loading state of song (one byte)
  DAT_8008d835 = 3;
  return;
}


// Music_AsyncParseBanks
uint FUN_8002de48(void)

{
  byte bVar1;
  char cVar2;
  int iVar3;
  uint uVar4;
  undefined auStack16 [8];

  // loading state of song (one byte)
  switch(DAT_8008d835)
  {
  case '\0':

	// Bank_AssignSpuAddrs
	iVar3 = FUN_800293b8();

    if (iVar3 == 0) goto switchD_8002de8c_caseD_5;

	// If you're in a Boss Race
	// 0x80000000
    if (*(int *)PTR_DAT_8008d2ac < 0)
	{
      cVar2 = '\x01';
      if (5 < *(int *)(PTR_DAT_8008d2ac + 0x1eb8)) break;

	  // song bank based on Boss ID
      uVar4 = (uint)(byte)(&DAT_8008d078)[*(int *)(PTR_DAT_8008d2ac + 0x1eb8)];
    }

    else
	{
	  // Level ID
      iVar3 = *(int *)(PTR_DAT_8008d2ac + 0x1a10);

	  // if Level ID < 30
	  // any level that can be driven on (Arcade, Battle, Adventure)
	  if (iVar3 < 0x1e) {

						// Get index from array
        uVar4 = (uint)(byte)(&DAT_8008394c)[iVar3];
      }

      else {
		// If you're drawing main menu
        if (iVar3 == 0x27) {
          uVar4 = 0x20;
        }
        else {

		  // If you're drawing Any% ending cutscene
          if (iVar3 == 0x2a) {
            uVar4 = 0x23;
          }

		  // If you're drawing 100% ending cutscene
          else {
            if (iVar3 == 0x2b) {
              uVar4 = 0x24;
            }

			// if you're drawing anything else
            else {
              cVar2 = '\x01';
              if (iVar3 != 0x2c) break;
              uVar4 = 0x25;
            }
          }
        }
      }
    }

	// Bank_Load
	FUN_800297a0(uVar4,auStack16);

    cVar2 = '\x01';
    break;
  case '\x01':

	// Bank_AssignSpuAddrs
	iVar3 = FUN_800293b8();

    if (iVar3 == 0) goto switchD_8002de8c_caseD_5;
    DAT_8008d800 = 0;
    DAT_8008d804 = 0;
    DAT_8008d808 = '\0';

    if (

		// If you're drawing any Arcade or Battle maps
	   (*(int *)(PTR_DAT_8008d2ac + 0x1a10) < 0x19) &&
       ((
		(
			// Basically:
			// If you're in Trophy Race, CTR Challenge Race,
			// Or non-purple cup (red, green, blue, yellow)
			// Or if you're in Arcade Mode

			(
				// This will always be true
				uVar4 = *(uint *)PTR_DAT_8008d2ac,

				// If you're in Adventure Mode
				(uVar4 & 0x80000) != 0 &&

				// Not in any of these...
				// Boss Race or Adventure Arena
				// Or Crystal Challenge or Relic Race
				((uVar4 & 0x8c100000) == 0)
			) &&

			(
				(
					// If you are not in Adventure cup
					(uVar4 & 0x10000000) == 0 ||

					// If this is not the purple gem cup
					(*(int *)(PTR_DAT_8008d2ac + 0x1e58) != 4)
				)
			)
		) ||

		// If you're in Arcade Mode
        ((*(uint *)PTR_DAT_8008d2ac & 0x400000) != 0)
		))
	  )
	{
	  // Bank_Load
      FUN_800297a0(0x36,auStack16);

      DAT_8008d808 = '\x01';
    }
    cVar2 = '\x02';
    break;
  case '\x02':

	// Bank_AssignSpuAddrs
    iVar3 = FUN_800293b8();

	if (iVar3 == 0) goto switchD_8002de8c_caseD_5;

	// If you're on any Arcade or Battle map
    if (*(int *)(PTR_DAT_8008d2ac + 0x1a10) < 0x19) 
	{
	  // not adventure mode, not adventure cup
      if (
			(
				// If you're not in Adventure Mode
				((*(uint *)PTR_DAT_8008d2ac & 0x80000) == 0) ||

				// If you are not in Adventure cup
				((*(uint *)PTR_DAT_8008d2ac & 0x10000000) == 0)
			) ||

			// If this is not the purple gem cup
			(*(int *)(PTR_DAT_8008d2ac + 0x1e58) != 4))

	  {
        cVar2 = '\x03';

							// numPlyrCurrGame
        if (DAT_8008d800 < (int)(uint)(byte)PTR_DAT_8008d2ac[0x1ca8]) {

          if (
				(DAT_8008d808 == '\0') || 
				
				// if characterID is secret character
				(7 < (short)(&DAT_80086e84)[DAT_8008d800])
			) 
		  {
			// bank = characterID + 0x37
            uVar4 = (uint)(ushort)(&DAT_80086e84)[DAT_8008d800] + 0x37 & 0xffff;
            
			// load bank
			goto LAB_8002e170;
          }
		  
		  // skip load bank
          goto LAB_8002e178;
        }
      }
	  
	  // if purple gem cup, or some other modes
      else 
	  {
		// load 5 banks, one for each driver
        if (DAT_8008d800 < 5) 
		{
          uVar4 = (uint)(ushort)(&DAT_80086e84)[DAT_8008d800] + 0x37 & 0xffff;
LAB_8002e170:
		  // Bank_Load
          FUN_800297a0(uVar4,auStack16);
LAB_8002e178:
          DAT_8008d800 = DAT_8008d800 + 1;
          goto switchD_8002de8c_caseD_5;
        }
        cVar2 = '\x03';
      }
    }
    else {
      cVar2 = '\x03';

	  // Level ID in the Adventure Arena
      if (*(int *)(PTR_DAT_8008d2ac + 0x1a10) - 0x19U < 5) {
        if (DAT_8008d800 == 0) 
		{
          if (
				(DAT_8008d808 != '\0') || 
		  
				// characterID is special character
				(7 < (short)DAT_80086e84)
			) 
		  {
			  goto LAB_8002e178;
          }
		  
		  // bank = characterID + 0x37
		  uVar4 = (uint)DAT_80086e84 + 0x37 & 0xffff;
		  
		  // load bank
          goto LAB_8002e170;
        }
        cVar2 = '\x03';

		// podium reward
        if (*(short *)(PTR_DAT_8008d2ac + 0x2572) != 0)
		{
          if (DAT_8008d804 == 0)
		  {
			// podium_modelIndex_First
            bVar1 = PTR_DAT_8008d2ac[0x2575];
LAB_8002e204:

			// Bank_Load
            FUN_800297a0((uint)bVar1 - 0x58 & 0xffff,auStack16);
          }
          else {
            if (DAT_8008d804 == 1)
			{
			  // podium_modelIndex_Second
              if (PTR_DAT_8008d2ac[0x2576] != '\0')
			  {
				// podium_modelIndex_Second
                bVar1 = PTR_DAT_8008d2ac[0x2576];
                goto LAB_8002e204;
              }
            }
            else {
              cVar2 = '\x03';
              if (DAT_8008d804 != 2) break;

			  // podium_modelIndex_Third
              if (PTR_DAT_8008d2ac[0x2577] != '\0')
			  {
				// podium_modelIndex_Third
                bVar1 = PTR_DAT_8008d2ac[0x2577];
                goto LAB_8002e204;
              }
            }
          }
          DAT_8008d804 = DAT_8008d804 + 1;
          goto switchD_8002de8c_caseD_5;
        }
      }
    }
    break;
  case '\x03':

	// Bank_AssignSpuAddrs
    iVar3 = FUN_800293b8();

    if (iVar3 == 0) goto switchD_8002de8c_caseD_5;

	// If you're in a Boss Race
	// 0x80000000
    if (*(int *)PTR_DAT_8008d2ac < 0) {
      uVar4 = 0x19;
      if (*(int *)(PTR_DAT_8008d2ac + 0x1eb8) < 6) goto LAB_8002e2f4;
    }
    else {

	  // Level ID
      iVar3 = *(int *)(PTR_DAT_8008d2ac + 0x1a10);

	  // if Level ID < 30
	  // any level that can be driven on (Arcade, Battle, Adventure)
	  if (iVar3 < 0x1e)
	  {
		// Set Song ID depending on track
        uVar4 = (uint)(byte)(&DAT_8008396c)[iVar3];
      }
      else {

		// Main Menu
        if (iVar3 == 0x27) {
          uVar4 = 0x1b;
        }
        else {

		  // intro
          if (iVar3 == 0x1e) {
            uVar4 = 0x1d;
          }
          else {

			// Naughty Dog Box
            if (iVar3 == 0x29) {
              uVar4 = 0x1c;
            }
            else {
			  // Any% ending
              if (iVar3 == 0x2a) {
                uVar4 = 0x1e;
              }
              else {
				// 100% ending
                if (iVar3 == 0x2b) {
                  uVar4 = 0x1f;
                }
                else {
                  cVar2 = '\x04';

				  // If not in credits, quit
                  if (iVar3 != 0x2c) break;

				  // credits
                  uVar4 = 0x20;
                }
              }
            }
          }
        }
      }
LAB_8002e2f4:
	  // Set Song ID
      FUN_80029c40(uVar4);
    }
    cVar2 = '\x04';
    break;
	
  case '\x04':
    
	// howl_LoadSong
	iVar3 = FUN_80029ca4();
	
    cVar2 = '\x05';
    if (iVar3 == 0) goto switchD_8002de8c_caseD_5;
    break;
  
  default:
    return 1;
  
  case -0xbad1ab1f:
    goto switchD_8002de8c_caseD_5;
  }

  // loading state of song (one byte)
  DAT_8008d835 = cVar2;
switchD_8002de8c_caseD_5:
  return (uint)(DAT_8008d835 == '\x05');
}


// Music_SetDefaults
void FUN_8002e338(void)
{
  // bool playCseqMusic = false
  DAT_8008d80c = 0;

  // no music playing
  DAT_8008d810 = 0xffffffff;

  // tempo
  DAT_8008d814 = 0;
  
  return;
}


// Music_Adjust
// param_1 - SongID (playing)
// param_2 - deltaBPM
// param_3 - 8008d068 for AdvHub
// param_4 - songSetActiveBits
void FUN_8002e350(uint param_1,int param_2,undefined4 param_3,undefined4 param_4)
{
  // if cseq music can play
  if (DAT_8008d80c != 0) 
  {
	// SongID
	if (DAT_8008d810 == (param_1 & 0xffff))
	{
	  // if tempo has changed
      if (DAT_8008d814 != param_2)
	  {
		// CseqMusic_ChangeTempo
        FUN_80029008(DAT_8008d810,param_2);

		// set new tempo
        DAT_8008d814 = param_2;
      }
    }
    else
	{
	  // CseqMusic_Stop
      FUN_800291a0(DAT_8008d810 & 0xffff);
    }
  }
  param_1 = param_1 & 0xffff;
  
  // if new SongID
  if (DAT_8008d810 != param_1)
  {
	// CseqMusic_Start (loopAtEnd)
    FUN_80028c78(param_1,param_2,param_3,param_4,1);

	// cseqBoolPlay = true
    DAT_8008d80c = 1;

	// set active SongID and tempo
    DAT_8008d810 = param_1;
    DAT_8008d814 = param_2;
  }
  return;
}


// Music_LowerVolume
// happens during "FINAL LAP!"
void FUN_8002e418(void)

{
  undefined4 uVar1;

  if (DAT_8008d80c != 0)
  {
	// 50% volume
    uVar1 = 0x96;

    if (1 < DAT_8008d810 - 1)
	{
	  // 25% volume
      uVar1 = 0x5a;
    }

	// CseqMusic_ChangeVolume
    FUN_80028e5c(DAT_8008d810 & 0xffff,uVar1,8);
  }
  return;
}


// Music_RaiseVolume
// after "FINAL LAP!" is done
void FUN_8002e46c(void)

{
  undefined4 uVar1;

  if (DAT_8008d80c != 0)
  {
	// 100% volume
    uVar1 = 0xff;
    if (1 < DAT_8008d810 - 1)
	{
	  // 75% volume
      uVar1 = 0xbe;
    }

	// CseqMusic_ChangeVolume
    FUN_80028e5c(DAT_8008d810 & 0xffff,uVar1,8);
  }
  return;
}


// Music_Restart
void FUN_8002e4c0(void)
{
  // if cseq music is playing
  if (DAT_8008d80c != 0)
  {
	// CseqMusic_Restart
    FUN_80028f34((uint)(ushort)DAT_8008d810,8);
  }
  return;
}


// Music_Stop
void FUN_8002e4ec(void)
{
  // if music is playing
  if (DAT_8008d80c != 0)
  {
	// CseqMusic_Stop
    FUN_800291a0(DAT_8008d810 & 0xffff);

    DAT_8008d80c = 0;
    DAT_8008d810 = 0xffffffff;
  }
  return;
}


// Music_Start
void FUN_8002e524(uint param_1)
{
  // cseqBoolPlay = true
  DAT_8008d80c = 1;

  // set highest song index
  DAT_8008d810 = param_1 & 0xffff;

  return;
}


// Music_End
void FUN_8002e53c(void)

{
  // cseqBoolPlay = false
  DAT_8008d80c = 0;

  // no songs are playing
  DAT_8008d810 = 0xffffffff;

  return;
}


// Music_GetHighestSongPlayIndex
undefined4 FUN_8002e550(void)
{
  // 0xffff - no cseq music
  // 0x0000 - song[0] (level music)
  // 0x0001 - song[1] (game aku)

  // "could" be 2 from [2] (menu aku),
  // but the game never sets it

  return DAT_8008d810;
}


// GTE_AudioLR_Inst
// 0x1d0 (offset 0x68) = CameraMatrix
// local_68, dir InstancePos - CameraPos
// param_2 is both the input, and output
void FUN_8002e55c(MATRIX *param_1,undefined4 *param_2)
{
  SVECTOR local_10;

  local_10.vx = *(short *)param_2;
  local_10.vy = *(short *)(param_2 + 1);
  local_10.vz = *(short *)(param_2 + 2);
  SetRotMatrix(param_1);
  gte_ldv0(&local_10);
  gte_rtv0();
  gte_stlvnl0(param_2);
  gte_stlvnl1(param_2 + 1);
  gte_stlvnl2(param_2 + 2);
  return;
}



// GTE_AudioLR_Driver
// param1 - matrix (pushBuffer)
// param2 - driver
// param3 - return vector
void FUN_8002e5cc(MATRIX *param_1,int param_2,undefined4 *param_3)
{
  SVECTOR local_10;

  // (PlayerX >> 8) - Matrix->t[0]
  // (PlayerY >> 8) - Matrix->t[0]
  // (PlayerZ >> 8) - Matrix->t[0]
  local_10.vx = (short)((uint)*(undefined4 *)(param_2 + 0x2d4) >> 8) - *(short *)param_1->t;
  local_10.vy = (short)((uint)*(undefined4 *)(param_2 + 0x2d8) >> 8) - *(short *)(param_1->t + 1);
  local_10.vz = (short)((uint)*(undefined4 *)(param_2 + 0x2dc) >> 8) - *(short *)(param_1->t + 2);

  SetRotMatrix(param_1);
  gte_ldv0(&local_10);
  gte_rtv0();
  gte_stlvnl0(param_3);
  gte_stlvnl1(param_3 + 1);
  gte_stlvnl2(param_3 + 2);
  return;
}



// in: vec3, out: squared length
// GTE_GetSquaredLength
int FUN_8002e658(undefined4 *param_1)
{
  int r2;
  int r3;
  int r4; // param_1
  
  // vectorX
  gte_ldIR1(param_1[0]);
  
  // vectorY
  gte_ldIR2(param_1[1]);
  
  // vectorZ
  gte_ldIR3(param_1[2]);
  
  // square root
  gte_sqr0(0);
  
  // readback
  read_mt(r2,r3,r4);
  
  return r2 + r3 + r4;
}


// OtherFX_RecycleNew
// param1 - soundID_countCount
// param2 - newSoundID
// param3 - modify
void FUN_8002e690(uint *param_1,uint param_2,undefined4 param_3)

{
  uint uVar1;

  if (
		// if soundID_soundCount is playing
		(*param_1 != 0) &&

		// if soundID doesn't match new ID
		((*param_1 & 0xffff) != param_2)
	  )
  {
	// OtherFX_Stop1
    FUN_80028808(*param_1);
    *param_1 = 0;
  }

  // if newSound != -1
  if (param_2 != 0xffffffff)
  {
	// if this is a new sound
    if (*param_1 == 0)
	{
	  // OtherFX_Play_LowLevel
      uVar1 = FUN_800284d0(param_2 & 0xffff,0,param_3);
      *param_1 = uVar1;
    }
	
	// if not a new sound,
	// modification of old sound
    else
	{
	  // OtherFX_Modify
      FUN_80028690(*param_1,param_3);
    }
  }
  return;
}


// OtherFX_RecycleMute
void FUN_8002e724(int *param_1)

{
  if (*param_1 != 0)
  {
	// OtherFX_Stop1
    FUN_80028808(*param_1);
    *param_1 = 0;
  }
  return;
}

// OtherFX_DriverCrashing
// param_1 - echo bool
// param_2 - 00-FF
void FUN_8002e760(int param_1,uint param_2)

{
  undefined4 uVar1;

  // three different collision sounds (0xA, 0xB, 0xC)
  // based on param_2 < 0xdd or < 0xa0

  if (param_2 < 0xdd)
  {
    uVar1 = 0xb;

	if (0xa0 < param_2)
	{
      uVar1 = 0xc;
    }
  }

  else
  {
    uVar1 = 10;
  }

  // three different crashing FXs

  // OtherFX_Play_LowLevel
  FUN_800284d0(

	// sound ID
	uVar1,

	0,

	// echo
	param_1 << 0x18 |

	// volume
	(param_2 & 0xff) << 0x10 |

	// no distortion, balance L/R
	0x8080
  );

  return;
}


// param1: vec3 pos1
// param2: vec3 pos2
// returns squared distance
// GTE_GetSquaredDistance
int FUN_8002e7bc(short *param_1,short *param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined4 in_t1;
  undefined4 in_t2;
  undefined4 in_t3;

  // distX
  setCopReg(2,in_t1,(int)*param_1 - (int)*param_2);

  // distY
  setCopReg(2,in_t2,(int)param_1[1] - (int)param_2[1]);

  // distZ
  setCopReg(2,in_t3,(int)param_1[2] - (int)param_2[2]);

  // SQR(sf) - Square vector
  copFunction(2,0xa00428);

  // x*x
  iVar1 = getCopReg(2,0xc800);

  // y*y
  iVar2 = getCopReg(2,0xd000);

  // z*z
  iVar3 = getCopReg(2,0xd800);

  // (x*x) + (y*y) + (z*z)
  // squared distance
  return iVar1 + iVar2 + iVar3;
}


// CalculateVolumeFromDistance
void FUN_8002e84c(uint *param_1,uint param_2,int param_3)

{
  uint uVar1;
  int iVar2;

  // if distance is less than 3000
  if (param_3 < 6000)
  {
    if ((*param_1 != 0) && ((*param_1 & 0xffff) != param_2))
	{
	  // OtherFX_Stop1
      FUN_80028808(*param_1);
      *param_1 = 0;
    }

	// if distance is less than 300
    if (param_3 < 0x12d)
	{
	  // full volume
      uVar1 = 0xff;
    }

    else
	{
      // Map distance from [close, far] to [loud, quiet]
      uVar1 = FUN_80058f9c(param_3,300,6000,0xff,0);
    }

    if (param_2 != 0xffffffff)
	{
      if (*param_1 == 0)
	  {
		// OtherFX_Play_LowLevel
        uVar1 = FUN_800284d0(
					param_2 & 0xffff,0,

					// volume
					(uVar1 & 0xff) << 0x10 |

					// no distortion, balance L/R
					0x8080);

		*param_1 = uVar1;
      }

      else {
        if (param_2 == 0x89)
		{
          iVar2 = (*(uint *)(PTR_DAT_8008d2ac + 0x1ce4) >> 2 & 0x7f) - 0x40;
          if (iVar2 < 0) {
            iVar2 = -iVar2;
          }
          uVar1 =

			// volume
			(uVar1 & 0xff) << 0x10 |

			// distortion
			(iVar2 + 100U & 0xff) << 8 |

			// balance L/R
			0x80;
        }
        else
		{
          uVar1 =

			// volume
			(uVar1 & 0xff) << 0x10 |

			// no distortion, balance L/R
			0x8080;
        }

		// OtherFX_Modify
        FUN_80028690(*param_1,uVar1);
      }
    }
  }

  // if distance is farther than 6000
  else
  {
    if (*param_1 != 0)
	{
	  // OtherFX_Stop1
      FUN_80028808(*param_1);
      *param_1 = 0;
    }
  }
  return;
}


// PlayWarppadSound
void FUN_8002e994(undefined4 param_1)

{
  // CalculateVolumeFromDistance
  FUN_8002e84c(&DAT_800962d0,0x98,param_1);

  return;
}


// Level_SoundLoopSet
// param_1 - slot
// param_2 - soundID
// param_3 - currVolume
void FUN_8002e9c0(int *param_1,uint param_2,uint param_3)

{
  int iVar1;

  if (param_3 == 0) {
    if (*param_1 != 0)
	{
	  // OtherFX_Stop1
      FUN_80028808(*param_1);
      *param_1 = 0;
    }
  }
  else {
    if (*param_1 == 0)
	{
	  // OtherFX_Play_LowLevel
      iVar1 = FUN_800284d0(

				// sound ID
				param_2 & 0xffff,0,

				// volume
				(param_3 & 0xff) << 0x10 |

				// no distort, balance LR
				0x8080
			);

	  // save soundID with soundCount
      *param_1 = iVar1;
    }
    else
	{
	  // OtherFX_Modify
      FUN_80028690(*param_1,(param_3 & 0xff) << 0x10 | 0x8080);
    }
  }
  return;
}


// Level_SoundLoopFade
// running water in sewer speedway
// param_1 is slot
// param_2 is soundID
// param_3 is desired volume
// param_4 is fade rate
void FUN_8002ea44(int param_1,undefined4 param_2,int param_3,int param_4)

{
  bool bVar1;
  int iVar2;

  // current volume
  iVar2 = *(int *)(param_1 + 8);
  
  // if current volume = desired
  if (iVar2 == param_3) 
  {
	// quit, leave audio loop alone,
	// regardless if lerping to 0x0, or 0xFF
    return;
  }
  
  // desired volume
  *(int *)(param_1 + 4) = param_3;
  
  // if current < desired
  if (iVar2 < param_3) 
  {
	// increase at desired rate [param_4]
    *(int *)(param_1 + 8) = iVar2 + param_4;
	
	// if increased too far...
    bVar1 = param_3 < iVar2 + param_4;
  }
  
  // if current > desired
  else 
  {
	// if equal, skip
    if (iVar2 <= param_3) goto LAB_8002ea9c;
	
	// decrease at desired rate [param_4]
    *(int *)(param_1 + 8) = iVar2 - param_4;
	
	// if decreased too far...
    bVar1 = iVar2 - param_4 < param_3;
  }
  
  // gone to far...
  if (bVar1) 
  {
	// set current to desired
    *(int *)(param_1 + 8) = param_3;
  }
  
LAB_8002ea9c:

  // Level_SoundLoopSet
  FUN_8002e9c0(

		param_1 + 0xc,

		// sound ID
		param_2,

		// current volume
		*(undefined4 *)(param_1 + 8)
	);

  return;
}


// Level_RandomFX
// water droplets in Roo's Tubes
void FUN_8002eab8(int *param_1,uint param_2,int param_3,uint param_4,int param_5)

{
  int iVar1;

  // deref
  iVar1 = *param_1;

  // if cooldown remains
  if (0 < iVar1)
  {
	// reduce cooldown
    *param_1 = iVar1 + -1;
    iVar1 = *param_1;
  }

  // if no cooldown
  if (iVar1 == 0)
  {
	// inline audioRNG scramble
    DAT_8008d058 = ((DAT_8008d058 >> 3) + DAT_8008d058 * 0x20000000) * 5 + 1;

	// OtherFX_Play_LowLevel
	// 1000000 = echo
	// 0008080 = no distortion, and balance L/R
    FUN_800284d0(

		param_2 & 0xffff,0,

	   // random volume
	   ((DAT_8008d058 % 100 + 100) * param_5 >> 8 & 0xff) << 0x10 |

	   // echo, no distort, balance LR
	   0x1008080
	);

	// inline audioRNG scramble
	DAT_8008d058 = ((DAT_8008d058 >> 3) + DAT_8008d058 * 0x20000000) * 5 + 1;

    if (param_4 == 0) {
      trap(0x1c00);
    }

	// set random cooldown to next sfx
    *param_1 = DAT_8008d058 % param_4 + param_3;
  }
  return;
}


// Level_AmbientSound
void FUN_8002ebe4(void)

{
  char cVar1;
  short sVar2;
  bool bVar3;
  bool bVar4;
  int iVar5;
  undefined4 uVar6;
  int *piVar7;
  undefined *puVar8;
  int *piVar9;
  undefined4 *puVar10;
  undefined4 uVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  int iVar15;
  int iVar16;
  int iVar17;
  int *piVar18;
  int iVar19;
  int local_58 [6];
  uint local_40;
  int *local_3c;
  int *local_38;
  int local_34;
  int *local_30;
  int local_2c;

  // Level ID
  local_40 = *(uint *)(PTR_DAT_8008d2ac + 0x1a10);

  // pointer to LEV
  local_58[4] = *(int *)(PTR_DAT_8008d2ac + 0x160);

  if (
		// if ordinary racing track
		(local_40 < 0x19) &&

		// if numPlyrCurrGame is less than 3
		((byte)PTR_DAT_8008d2ac[0x1ca8] < 3)
	 )
   {

	// levID is roo's tubes,
	// play sfx connected to the level
	// (water droplets, ocean sounds, etc)
	if (local_40 == 6) {
      bVar3 = false;
      bVar4 = false;

	  // loop counter
      iVar16 = 0;

      puVar8 = PTR_DAT_8008d2ac;

	  // if numPlyrCurrGame is not zero
      if (PTR_DAT_8008d2ac[0x1ca8] != 0) {

		// for(int iVar16 = 0; iVar16 < numPlyrCurrGame; iVar16++)
		do {

		  // driver->0xc2 (current terrain)
          cVar1 = *(char *)(*(int *)(puVar8 + 0x24ec) + 0xc2);

          if (cVar1 == '\0') {
            bVar3 = true;
          }
          if (cVar1 == '\x01') {
            bVar3 = true;
          }
          if (cVar1 == '\v') {
            bVar3 = true;
          }

		  // driver -> terrain -> sound
          sVar2 = *(short *)(*(int *)(*(int *)(puVar8 + 0x24ec) + 0x35c) + 0x34);
          
		  // dont call the Fade function here,
		  // or else it fades 2x speed in 2P mode
		  
		  // if soundID
		  if ((sVar2 != -1) && (sVar2 == 0x87)) 
		  {
            bVar4 = true;
          }

		  // iteration counter
          iVar16 = iVar16 + 1;

		  // pointer incrementation
          puVar8 = puVar8 + 4;

		  //                  numPlyrCurrGame
        } while (iVar16 < (int)(uint)(byte)PTR_DAT_8008d2ac[0x1ca8]);
      }
	  
      if (bVar3)
	  {
		// Level_RandomFX (water drops)
        FUN_8002eab8(&DAT_800962c4,0x86,6,0x5a,0xff);
      }
	  
      if (bVar4) 
	  {
		// fade to 100% volume
        uVar6 = 0xff;
      }
	  
      else 
	  {
		// fade to 0% volume
        uVar6 = 0;
      }

	  // Level_SoundLoopFade
      FUN_8002ea44(&DAT_800962d4,0x87,uVar6,8);
    }
	
	// not roo's tubes
    else 
	{
      iVar16 = 0;

	  // if levID is sewer speedway
	  // play sfx connected to the level
	  // (flowing water, etc)
      if (local_40 == 8) 
	  {
        bVar3 = false;
        bVar4 = false;

		// loop counter
		iVar16 = 0;

        puVar8 = PTR_DAT_8008d2ac;

		// if numPlyrCurrGame is not zero
        if (PTR_DAT_8008d2ac[0x1ca8] != 0) {

		  // for(int iVar16 = 0; iVar16 < numPlyrCurrGame; iVar16++)
		  do
		  {
			// driver -> terrain -> sound
            sVar2 = *(short *)(*(int *)(*(int *)(puVar8 + 0x24ec) + 0x35c) + 0x34);
            if (sVar2 != -1) {
              
			  // dont call the Fade function here,
			  // or else it fades 2x speed in 2P mode
			  
			  // if soundID
			  if (sVar2 == 0x88) 
			  {
                bVar3 = true;
              }
              
			  // if soundID
			  if (sVar2 == 0x8b) 
			  {
                bVar4 = true;
              }
            }

			// increment iteration counter
            iVar16 = iVar16 + 1;

			// increment pointer
            puVar8 = puVar8 + 4;

								// numPlyrCurrGame
          } while (iVar16 < (int)(uint)(byte)PTR_DAT_8008d2ac[0x1ca8]);
        }
        
		if (bVar3) 
		{
		  // fade to 100% volume
          uVar6 = 0xff;
        }
		
        else 
		{
		  // fade to 0% volume
          uVar6 = 0;
        }

		// Level_SoundLoopFade
        FUN_8002ea44(&DAT_800962c4,0x88,uVar6,8);

        if (bVar4) 
		{
		  // fade to 100% volume
          uVar6 = 0xff;
        }
		
        else 
		{
		  // fade to 0% volume
          uVar6 = 0;
        }

		// Level_SoundLoopFade
        FUN_8002ea44(&DAT_800962d4,0x8b,uVar6,4);
      }
	  
	  // if not roo's tubes or sewer speedway
      else 
	  {
        piVar9 = local_58 + 2;
        piVar7 = local_58;

		// for iVar16 = 0; iVar16 < 2; iVar16++
        do {
          *piVar7 = 0x7fffffff;
          *piVar9 = -1;
          piVar9 = piVar9 + 1;

		  // increment loop counter
          iVar16 = iVar16 + 1;

          piVar7 = piVar7 + 1;
        } while (iVar16 < 2);

        iVar16 = 0;
        local_3c = local_58 + 2;
        local_38 = local_58;
        local_34 = 0;

		// for iVar16 = 0; iVar16 < 2; iVar16++
        do {
          piVar7 = local_38;
		  
		  // levAmbientSound
          local_58[5] = (uint)(byte)(&DAT_8008398c)[iVar16 + local_40 * 2];
          if ((&DAT_8008398c)[iVar16 + local_40 * 2] == 0) goto LAB_8002f088;
		  
          iVar19 = iVar16 + 5;

		  // iVar19 < cnt_spawn_arrays2
          if (iVar19 < *(int *)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0x138))
		  {
			// piVar9 = ptr_spawn_arrays2[xxxxxx]
            piVar9 = (int *)(*(int *)(local_58[4] + 0x13c) + iVar19 * 8);

			if (9 < *piVar9) goto LAB_8002f074;
            iVar15 = 0;
            if (0 < *piVar9) {
              iVar17 = 0;
              iVar12 = local_34;
              do {
                iVar13 = 0;

				// if numPlyrCurrGame is not zero
                if (PTR_DAT_8008d2ac[0x1ca8] != '\0')
				{
				  // offset of 8008d2ac where pushBuffer structs are held
				  // for each player (posX, posY, width, height, etc)
                  iVar14 = 0x168;

                  piVar18 = (int *)((int)local_3c + iVar12);

				  // for(int iVar13 = 0; iVar13 < numPlyrCurrGame; iVar13++)
                  do {
                    local_30 = piVar9;
                    local_2c = iVar12;

					// get squared distance between two positions
                    iVar5 = FUN_8002e7bc(

						// pushBuffer (camera pos)
						PTR_DAT_8008d2ac + iVar14,

						*(int *)(iVar19 * 8 + *(int *)(local_58[4] + 0x13c) + 4) + iVar17
										 );
                    iVar12 = local_2c;
                    piVar9 = local_30;
                    if (iVar5 < *piVar7) {
                      *piVar7 = iVar5;
                      *piVar18 = iVar15;
                    }

					// increment loop counter
                    iVar13 = iVar13 + 1;

					// increment pointer to next pushBuffer struct
                    iVar14 = iVar14 + 0x110;

									// numPlyrCurrGame
                  } while (iVar13 < (int)(uint)(byte)PTR_DAT_8008d2ac[0x1ca8]);
                }
                iVar15 = iVar15 + 1;
                iVar17 = iVar17 + 6;
              } while (iVar15 < *piVar9);
            }
            uVar6 = SquareRoot0(*local_38);
            if (iVar16 == 0) {
              if (local_40 == 9) {

                // Map value from [oldMin, oldMax] to [newMin, newMax]
                // inverting newMin and newMax will give an inverse range mapping
                uVar6 = FUN_80058f9c(uVar6,300,6000,0xff,0);
                puVar10 = &DAT_800962c4;
                uVar11 = 0x86;
LAB_8002f048:
				// Level_RandomFX
                FUN_8002eab8(puVar10,uVar11,6,0x5a,uVar6);
              }
              else
			  {
				// CalculateVolumeFromDistance
                FUN_8002e84c(&DAT_800962d0,local_58[5]);
              }
            }
            else {
              if (local_40 == 3) {

                // Map value from [oldMin, oldMax] to [newMin, newMax]
                // inverting newMin and newMax will give an inverse range mapping
                uVar6 = FUN_80058f9c(uVar6,300,6000,0xff,0);
                puVar10 = &DAT_800962d4;
                uVar11 = 0x85;
                goto LAB_8002f048;
              }

			  // CalculateVolumeFromDistance
              FUN_8002e84c(&DAT_800962e0,local_58[5],uVar6);
            }
          }
          else {
LAB_8002f074:
            if (DAT_8008d830 == 0) {
              DAT_8008d830 = 1;
            }
          }
LAB_8002f088:

		  // increment loop counter
          iVar16 = iVar16 + 1;
          local_38 = local_38 + 1;
          local_34 = local_34 + 4;
        } while (iVar16 < 2);
      }
    }
  }
  return;
}


// PlaySound3D
// param1 - sound effect
// param2 - instance creating sound
// volume depends on distance from Instance
// to the nearest player's camera
void FUN_8002f0dc(uint param_1,int param_2)

{
  uint uVar1;
  long lVar2;
  undefined *puVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  long local_68;
  int local_64 [11];
  uint local_38 [4];

  uVar8 = 9000;

  // loop counter
  iVar4 = 0;

  iVar7 = 0;

  // if numPlyrCurrGame is not zero
  if (PTR_DAT_8008d2ac[0x1ca8] != '\0') {
    iVar6 = 0;
    iVar5 = 0;

	// for(int iVar4 = 0; iVar4 < numPlyrCurrGame; iVar4++)
    do
	{
	  // use iVar6 to imcrement pointer
      puVar3 = PTR_DAT_8008d2ac + iVar6;

	  // Get distance from Instance and each Camera position (pushBuffer)
	  *(int *)((int)&local_68 + iVar5) = *(int *)(param_2 + 0x44) - (int)*(short *)(puVar3 + 0x168);
      *(int *)((int)local_64 + iVar5) = *(int *)(param_2 + 0x48) - (int)*(short *)(puVar3 + 0x16a);
      *(int *)((int)local_64 + iVar5 + 4) = *(int *)(param_2 + 0x4c) - (int)*(short *)(puVar3 + 0x16c);

	  // in: vec3, out: squared length
      uVar1 = FUN_8002e658();

      local_38[iVar4] = uVar1;

	  // square root of squared length,
	  // get "true" length of vector
	  uVar1 = SquareRoot0();

	  local_38[iVar4] = uVar1;

	  if (uVar1 < uVar8) {
        iVar7 = iVar4;
        uVar8 = uVar1;
      }

	  // go to next pushBuffer
      iVar6 = iVar6 + 0x110;

	  // increment loop counter
      iVar4 = iVar4 + 1;

      iVar5 = iVar5 + 0xc;

					// numPlyrCurrGame
    } while (iVar4 < (int)(uint)(byte)PTR_DAT_8008d2ac[0x1ca8]);
  }
  if (uVar8 == 9000) {
    return;
  }

  // GTE_AudioLR_Inst
  // 0x1d0 (offset 0x68) = CameraMatrix
  // local_68, dir InstancePos - CameraPos
  FUN_8002e55c(PTR_DAT_8008d2ac + iVar7 * 0x110 + 0x1d0,&local_68 + iVar7 * 3);

  // parameters calculated from previous function
  lVar2 = ratan2((&local_68)[iVar7 * 3],-local_64[iVar7 * 3 + 1]);

  iVar4 = (lVar2 + 0x800) * -0x100000 >> 0x17;
  if (iVar4 < 0x81) {
    iVar5 = -0x100;
    if (-0x81 < iVar4) goto LAB_8002f250;
  }
  else {
    iVar5 = 0x100;
  }
  iVar4 = iVar5 - iVar4;
LAB_8002f250:
  uVar1 = iVar4 + 0x80;
  if ((int)uVar1 < 0) {
    uVar1 = 0;
  }
  else {
    if (0xff < (int)uVar1) {
      uVar1 = 0xff;
    }
  }
  if (uVar8 < 0x12d) {
    uVar8 = 0xff;
  }
  else {

    // Map value from [oldMin, oldMax] to [newMin, newMax]
    // inverting newMin and newMax will give an inverse range mapping
    uVar8 = FUN_80058f9c(uVar8,300,9000,0xff,0);
  }

  // OtherFX_Play_LowLevel
  FUN_800284d0(param_1 & 0xffff,1,

				// if quadblock under camera is able to make an echo
               ((uint)*(ushort *)(*(int *)(PTR_DAT_8008d2ac + iVar7 * 0xdc + 0x14b4) + 0x12) & 0x80)
				<< 0x18

				// volume
				| (uVar8 & 0xff) << 0x10

				// Left/Right
				| uVar1 & 0xff

				// distortion
				| 0x8000);
  return;
}


// Play 3D Audio with flags
// audio changes in Left and Right speakers
void FUN_8002f31c(uint *param_1,uint param_2,int param_3)

{
  uint uVar1;
  long lVar2;
  undefined *puVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  uint uVar8;

  // vec3 dir[4], 3*4 = 12 ints
  int local_64 [12];

  // distance of each pushBuffer to instance
  uint local_38 [4];

  iVar7 = 0;
  if ((*param_1 != 0) && ((*param_1 & 0xffff) != param_2))
  {
	// OtherFX_Stop1
    FUN_80028808(*param_1);

    *param_1 = 0;
  }

  // maximum distance a 3D sound
  // can be heard from, 9000 units
  uVar8 = 9000;

  if (param_2 == 0xffffffff) {
    return;
  }

  // loop counter
  iVar4 = 0;

  // if numPlyrCurrGame is not zero
  if (PTR_DAT_8008d2ac[0x1ca8] != '\0') {
    iVar6 = 0;

	// find closest camera to the instance
	// for(int iVar4 = 0; iVar4 < numPlyrCurrGame; iVar4++)
	do {
      puVar3 = PTR_DAT_8008d2ac + iVar6;

	  // direction vector, InstancePos - CameraPos
	  local_68[iVar4 * 3 + 0] = *(int *)(param_3 + 0x44) - (int)*(short *)(puVar3 + 0x168);
      local_68[iVar4 * 3 + 1] = *(int *)(param_3 + 0x48) - (int)*(short *)(puVar3 + 0x16a);
      local_68[iVar4 * 3 + 2] = *(int *)(param_3 + 0x4c) - (int)*(short *)(puVar3 + 0x16c);

	  // in: vec3 dir, out: squared length
	  uVar1 = FUN_8002e658();

	  // save length in array
	  // (waste, never used)
      local_38[iVar4] = uVar1;

	  // square root of squared length,
	  // get "true" length of vector
	  uVar1 = SquareRoot0();

	  // save length in array
	  // (waste, never used)
      local_38[iVar4] = uVar1;

	  // if this camera is closer to the instance
	  // than the closest known camera
	  if (uVar1 < uVar8)
	  {
		// save new camera index
        iVar7 = iVar4;

		// set new shortest distance
        uVar8 = uVar1;
      }

	  // next pushBuffer
      iVar6 = iVar6 + 0x110;

	  // increment loop counter
      iVar4 = iVar4 + 1;

					// numPlyrCurrGame
    } while (iVar4 < (int)(uint)(byte)PTR_DAT_8008d2ac[0x1ca8]);
  }

  // if no camera is close enough to hear the sound,
  // then return, and do not play the sound
  if (uVar8 == 9000) {
    return;
  }

  // GTE_AudioLR_Inst
  // 0x1d0 (offset 0x68) = CameraMatrix
  // local_68, dir InstancePos - CameraPos
  FUN_8002e55c(PTR_DAT_8008d2ac + iVar7 * 0x110 + 0x1d0,&local_68[iVar7 * 3]);

  // parameters calculated from previous function
  lVar2 = ratan2(

	// dirX
	local_68[iVar7 * 3],

	// -dirZ
	-local_68[iVar7 * 3 + 2]
  );

  iVar4 = (lVar2 + 0x800) * -0x100000 >> 0x17;

  if (iVar4 < 0x81) {
    iVar5 = -0x100;
    if (-0x81 < iVar4) goto LAB_8002f4c8;
  }
  else {
    iVar5 = 0x100;
  }
  iVar4 = iVar5 - iVar4;
LAB_8002f4c8:

  // convert range of:
		// left: negative
		// mid: zero
		// right: positive

  // to range of:
		// left: 0x0
		// mid: 0x80
		// right: 0xff
  uVar1 = iVar4 + 0x80;

  // if L/R is less than 0.0
  if ((int)uVar1 < 0)
  {
	// can't go lower than 0.0
    uVar1 = 0;
  }

  else
  {
	// If L/R is more than 1.0
    if (0xff < (int)uVar1)
	{
	  // cap at 1.0
      uVar1 = 0xff;
    }
  }

  if (uVar8 < 0x12d) {
    uVar8 = 0xff;
  }

  else {

    // Map value from [oldMin, oldMax] to [newMin, newMax]
    // inverting newMin and newMax will give an inverse range mapping
    uVar8 = FUN_80058f9c(uVar8,300,9000,0xff,0);
  }

  if (*param_1 == 0)
  {
	// OtherFX_Play_LowLevel
    uVar8 = FUN_800284d0(param_2 & 0xffff,0,

						// if quadblock under camera is able to make an echo
                         ((uint)*(ushort *)
                                 (*(int *)(PTR_DAT_8008d2ac + iVar7 * 0xdc + 0x14b4) + 0x12) & 0x80)
						<< 0x18

						// volume
						| (uVar8 & 0xff) << 0x10

						// left/right
						| uVar1 & 0xff

						// distortion
						| 0x8000);
    *param_1 = uVar8;
  }
  else
  {
	// OtherFX_Modify
    FUN_80028690(*param_1,

							// if quadblock under camera is able to make an echo
							((uint)*(ushort *)
                                  (*(int *)(PTR_DAT_8008d2ac + iVar7 * 0xdc + 0x14b4) + 0x12) & 0x80
                          ) << 0x18

						  // volume
						  | (uVar8 & 0xff) << 0x10

						  // left/right
						  | uVar1 & 0xff

						  // distortion
						  | 0x8000);
  }
  return;
}


// EngineSound_Player
// param_1 - ptr to driver struct
void FUN_8002f5f4(int param_1)

{
  byte bVar1;
  short sVar2;
  short sVar3;
  short sVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  int iVar8;
  undefined4 uVar9;
  uint uVar10;
  ushort uVar11;
  int iVar12;

  // Player / AI structure + 0x4a shows driver index (0-7)
  bVar1 = *(byte *)(param_1 + 0x4a);

  // engineID from metadata, given characterID
  iVar5 = *(int *)(&DAT_80086d90 + (int)(short)(&DAT_80086e84)[(uint)bVar1] * 0x10);

  // === Unused Code ===
  // This variable is always 2
  if (*(char *)(param_1 + 0x47b) == '\0') 
  {
    *(undefined2 *)(param_1 + 0x3b6) = (short)((int)*(short *)(param_1 + 0x3b6) * 0x177 >> 9);
    *(undefined2 *)(param_1 + 0x3b8) =
         (short)((int)*(short *)(param_1 + 0x3b8) * 3000 + 0x22400 >> 0xc);

    // Map value from [oldMin, oldMax] to [newMin, newMax]
    // inverting newMin and newMax will give an inverse range mapping
    uVar6 = FUN_80058f9c((int)*(short *)(param_1 + 0x3b6),0,(int)*(short *)(param_1 + 0x42e),0,0xe6)
    ;

    // Map value from [oldMin, oldMax] to [newMin, newMax]
    // inverting newMin and newMax will give an inverse range mapping
    uVar7 = FUN_80058f9c((int)*(short *)(param_1 + 0x3b8),0,(int)*(short *)(param_1 + 0x42e),0x3c,
                         200);

	// Left/Right
	uVar10 = 0x80 - ((int)((uint)*(ushort *)(param_1 + 6) << 0x10) >> 0x13);

	// farthest to the left possible
	if ((int)uVar10 < 0x40) {
      uVar10 = 0x40;
    }

	// farthest to the right possible
    else {
      if (0xc0 < (int)uVar10) {
        uVar10 = 0xc0;
      }
    }

	// volume
    uVar6 = (uVar6 & 0xff) << 0x10;

	// distortion
	uVar7 = (uVar7 & 0xff) << 8;

	// balance L/R
	uVar10 = uVar10 & 0xff;

	// if echo required
    if ((*(uint *)(param_1 + 0x2c8) & 0x10000) != 0)
	{
	  // add echo
      uVar6 = uVar6 | uVar7 | 0x1000000;
      goto LAB_8002fc04;
    }
  }
  else 
  {
	// === Unused Code ===
	// This variable is always 2
    if (*(char *)(param_1 + 0x47b) == '\x01') 
	{
      *(undefined2 *)(param_1 + 0x3b6) =
           (short)((int)*(short *)(param_1 + 0x3b6) * 3000 + 0x322bc0 >> 0xc);
      *(undefined2 *)(param_1 + 0x3b8) =
           (short)((int)*(short *)(param_1 + 0x3b8) * 3000 + 0x22400 >> 0xc);

      // Map value from [oldMin, oldMax] to [newMin, newMax]
      // inverting newMin and newMax will give an inverse range mapping
      uVar6 = FUN_80058f9c((int)*(short *)(param_1 + 0x3b6),0,(int)*(short *)(param_1 + 0x42e),0x82,
                           0xe6);

      // Map value from [oldMin, oldMax] to [newMin, newMax]
      // inverting newMin and newMax will give an inverse range mapping
      uVar7 = FUN_80058f9c((int)*(short *)(param_1 + 0x3b8),0,(int)*(short *)(param_1 + 0x42e),0x3c,
                           200);

	  // left/right
      uVar10 = 0x80 - ((int)((uint)*(ushort *)(param_1 + 6) << 0x10) >> 0x13);

	  // farthest left you can go
	  if ((int)uVar10 < 0x40) {
        uVar10 = 0x40;
      }

	  // farthest right you can go
      else {
        if (0xc0 < (int)uVar10) {
          uVar10 = 0xc0;
        }
      }

	  // volume
      uVar6 = (uVar6 & 0xff) << 0x10;

	  // distortion
	  uVar7 = (uVar7 & 0xff) << 8;

	  // balance L/R
	  uVar10 = uVar10 & 0xff;

	  // if echo effect is required
      if ((*(uint *)(param_1 + 0x2c8) & 0x10000) != 0)
	  {
		// add echo effect
        uVar6 = uVar6 | uVar7 | 0x1000000;
        goto LAB_8002fc04;
      }
    }
    
	// If == 2
	else {
      if (*(char *)(param_1 + 0x376) == '\x04') {
        iVar12 = 0;
        if (0 < *(short *)(param_1 + 0x39e)) {
          iVar12 = 0x3000;
        }
        iVar12 = (int)*(short *)(param_1 + 0x3b8) * 0x40 + iVar12 * 0x30 +
                 (int)*(short *)(param_1 + 0x36e) * 0x90 >> 8;
        if (0 < *(short *)(param_1 + 0x39e)) {
          iVar12 = iVar12 + 0x1000;
        }
      }
      else {
        iVar12 = (int)*(short *)(param_1 + 0x39e);
        if (iVar12 < 0) {
          iVar12 = -iVar12;
        }
        if (((*(uint *)(param_1 + 0x2cc) & 1) == 0) || (*(char *)(param_1 + 0x376) == '\x02')) {
          iVar12 = iVar12 + 0xf00;
        }
        else {
          iVar8 = (int)*(short *)(param_1 + 0x38e);
          if (iVar8 < 0) {
            iVar8 = -iVar8;
          }
          iVar12 = iVar12 + iVar8 >> 1;
        }
      }
      iVar8 = iVar12 - *(short *)(param_1 + 0x3b8);
      if (iVar8 < 0) {
        iVar8 = -iVar8;
      }
      if (iVar8 < 0x601) {
        uVar11 = *(short *)(param_1 + 0x3b6) - 500;
        *(ushort *)(param_1 + 0x3b6) = uVar11;
        if (*(char *)(param_1 + 0x376) == '\x02') {
          if ((short)uVar11 < 2000) {
            *(undefined2 *)(param_1 + 0x3b6) = 2000;
          }
        }
        else {
          if ((int)((uint)uVar11 << 0x10) < 0) {
            *(undefined2 *)(param_1 + 0x3b6) = 0;
          }
        }
      }
      else {
        sVar4 = *(short *)(param_1 + 0x3b6) + 2000;
        *(short *)(param_1 + 0x3b6) = sVar4;
        if (14000 < sVar4) {
          *(undefined2 *)(param_1 + 0x3b6) = 14000;
        }
      }
      iVar8 = (int)*(short *)(param_1 + 6);
      *(undefined2 *)(param_1 + 0x3b8) =
           (short)((uint)(iVar12 * 0x89 + (int)*(short *)(param_1 + 0x3b8) * 0x177) >> 9);
      if (iVar8 < 0) {
        iVar8 = -iVar8;
      }

	  // If this is human and not AI
      if ((*(uint *)(param_1 + 0x2c8) & 0x100000) == 0) {
        sVar4 = *(short *)(param_1 + 0x3b6);
        sVar2 = *(short *)(param_1 + 0x42e);
        uVar9 = 0xe6;
      }

	  // If this is AI
      else {
        sVar4 = *(short *)(param_1 + 0x3b6);
        sVar2 = *(short *)(param_1 + 0x42e);
        uVar9 = 0xbe;
      }

      // Map value from [oldMin, oldMax] to [newMin, newMax]
      // inverting newMin and newMax will give an inverse range mapping
      uVar6 = FUN_80058f9c((int)sVar4,0,(int)sVar2,0x82,uVar9);
	  
      //if racer is not drifting and not in accel prevention
      if ((*(char *)(param_1 + 0x376) != '\x02') && ((*(uint *)(param_1 + 0x2c8) & 8) == 0)) {
        uVar6 = uVar6 + (iVar8 >> 3);
      }

	  // If this is human and not AI
      if ((*(uint *)(param_1 + 0x2c8) & 0x100000) == 0) {
        sVar4 = *(short *)(param_1 + 0x3b8);
        sVar2 = *(short *)(param_1 + 0x42e);
        sVar3 = *(short *)(param_1 + 0x432);
        uVar9 = 200;
      }

	  // If this is AI
      else {
        sVar4 = *(short *)(param_1 + 0x3b8);
        sVar2 = *(short *)(param_1 + 0x42e);
        sVar3 = *(short *)(param_1 + 0x432);
        uVar9 = 0xbe;
      }


    // Map value from [oldMin, oldMax] to [newMin, newMax]
    // inverting newMin and newMax will give an inverse range mapping
	  iVar12 = FUN_80058f9c((int)sVar4,0,(int)sVar2 + (int)sVar3 + 0xf00,0x3c,uVar9);

	  // If this is human and not AI
	  if ((*(uint *)(param_1 + 0x2c8) & 0x100000) == 0)
	  {
		// if kart state == drifting
        if (*(char *)(param_1 + 0x376) == '\x02')
		{
		  // if turbo meter has no room left
          if (*(short *)(param_1 + 0x3dc) == 0)
		  {
            sVar4 = *(short *)(param_1 + 0x2fc) + -1;
            if (*(short *)(param_1 + 0x2fc) != 0) goto LAB_8002fb48;
          }

		  // if turbo meter has room left
          else
		  {
			// (max room / 2) - (remaining room >> 6)
            sVar4 = (ushort)(*(byte *)(param_1 + 0x476) >> 1) - (*(short *)(param_1 + 0x3dc) >> 6);
LAB_8002fb48:
            *(short *)(param_1 + 0x2fc) = sVar4;
          }

          iVar8 = (int)((uint)*(ushort *)(param_1 + 0x3d4) << 0x10) >> 0x13;
          if (iVar8 < 0) {
            iVar8 = -iVar8;
          }
          iVar12 = iVar12 - iVar8;
          if (iVar12 < 0) {
            iVar12 = 0;
          }
        }
        uVar7 = iVar12 + *(short *)(param_1 + 0x2fc);
      }

	  // If this is an AI
      else {
        iVar8 = (int)((uint)*(ushort *)(param_1 + 0x3d4) << 0x10) >> 0x13;
        if (iVar8 < 0) {
          iVar8 = -iVar8;
        }
        uVar7 = iVar12 - iVar8;
        if ((int)uVar7 < 0) {
          uVar7 = 0;
        }
      }
      if (0xff < (int)uVar7) {
        uVar7 = 0xff;
      }

	  // balance L/R
      uVar10 = 0x80 - ((int)((uint)*(ushort *)(param_1 + 6) << 0x10) >> 0x13);

	  // farthest possible left
	  if ((int)uVar10 < 0x40) {
        uVar10 = 0x40;
      }

	  // farthest possible right
      else {
        if (0xc0 < (int)uVar10) {
          uVar10 = 0xc0;
        }
      }

	  // volume
      uVar6 = (uVar6 & 0xff) << 0x10;

	  // distortion
	  uVar7 = (uVar7 & 0xff) << 8;

	  // L/R
	  uVar10 = uVar10 & 0xff;

	  // if echo effect is requierd
      if ((*(uint *)(param_1 + 0x2c8) & 0x10000) != 0)
	  {
		// add echo
        uVar6 = uVar6 | uVar7 | 0x1000000;
        goto LAB_8002fc04;
      }
    }
  }
  uVar6 = uVar6 | uVar7;
LAB_8002fc04:

  // EngineAudio_Recalculate
  FUN_800289b0(iVar5 * 4 + (uint)bVar1 & 0xffff,uVar6 | uVar10);
  return;
}


// EngineSound_VolumeAdjust
int FUN_8002fc28(int param_1,int param_2,int param_3)

{
  int iVar1;
  int iVar2;

  iVar2 = param_1 - param_2;
  iVar1 = iVar2;
  if (iVar2 < 0) {
    iVar1 = -iVar2;
  }

  // param_3 less than gap between
  // "current" and "desired"
  if (param_3 < iVar1)
  {
	// param_2 > param_1
    if (iVar2 < 1) {
      return param_2 - param_3;
    }

	// param_1 > param_2
    return param_2 + param_3;
  }
  return param_1;
}


// EngineSound_AI
void FUN_8002fc64(int param_1,int param_2,int param_3,int param_4,int param_5,uint param_6)

{
  short sVar1;
  int iVar2;
  undefined4 uVar3;
  uint uVar4;
  int iVar5;
  ushort uVar6;
  uint uVar7;

  iVar5 = (int)*(short *)(param_1 + 0x42e);
  if (iVar5 < 0) {
    iVar5 = -iVar5;
  }
  if (((*(uint *)(param_1 + 0x2cc) & 1) == 0) || (*(char *)(param_1 + 0x376) == '\x02')) {
    iVar5 = iVar5 + 0xf00;
  }
  else {
    iVar2 = (int)*(short *)(param_1 + 0x38e);
    if (iVar2 < 0) {
      iVar2 = -iVar2;
    }
    iVar5 = iVar5 + iVar2 >> 1;
  }
  iVar2 = iVar5 - *(short *)(param_1 + 0x3b8);
  if (iVar2 < 0) {
    iVar2 = -iVar2;
  }
  if (iVar2 < 0x601) {
    uVar6 = *(short *)(param_1 + 0x3b6) - 500;
    *(ushort *)(param_1 + 0x3b6) = uVar6;
    if (*(char *)(param_1 + 0x376) == '\x02') {
      if ((short)uVar6 < 2000) {
        *(undefined2 *)(param_1 + 0x3b6) = 2000;
      }
    }
    else {
      if ((int)((uint)uVar6 << 0x10) < 0) {
        *(undefined2 *)(param_1 + 0x3b6) = 0;
      }
    }
  }
  else {
    sVar1 = *(short *)(param_1 + 0x3b6) + 2000;
    *(short *)(param_1 + 0x3b6) = sVar1;
    if (14000 < sVar1) {
      *(undefined2 *)(param_1 + 0x3b6) = 14000;
    }
  }
  *(undefined2 *)(param_1 + 0x3b8) =
       (short)((uint)(iVar5 * 0x89 + (int)*(short *)(param_1 + 0x3b8) * 0x177) >> 9);

  // Map value from [oldMin, oldMax] to [newMin, newMax]
  // inverting newMin and newMax will give an inverse range mapping
  uVar3 = FUN_80058f9c((int)*(short *)(param_1 + 0x3b6),0,(int)*(short *)(param_1 + 0x42e),0x82,0xe6
                      );
  if (param_4 < 2000) {
    if (200 < param_4) {

      // Map value from [oldMin, oldMax] to [newMin, newMax]
      // inverting newMin and newMax will give an inverse range mapping
      uVar3 = FUN_80058f9c(param_4,200,2000,uVar3,0);
    }
  }
  else {
    uVar3 = 0;
  }

  // EngineSound_VolumeAdjust
  uVar4 = FUN_8002fc28(uVar3,(&DAT_8008d818)[param_3],10);
  (&DAT_8008d818)[param_3] = uVar4;

  // Map value from [oldMin, oldMax] to [newMin, newMax]
  // inverting newMin and newMax will give an inverse range mapping
  iVar5 = FUN_80058f9c((int)*(short *)(param_1 + 0x3b8),0,(int)*(short *)(param_1 + 0x42e),0x3c,0xaa
                      );
  param_5 = param_5 >> 3;
  if (param_5 < -0x14) {
    param_5 = -0x14;
  }
  else {
    if (0x14 < param_5) {
      param_5 = 0x14;
    }
  }
  uVar7 = iVar5 - param_5;
  if ((int)uVar7 < 0) {
    uVar7 = 0;
  }
  else {
    if (0xff < (int)uVar7) {
      uVar7 = 0xff;
    }
  }

  // L/R min
  if ((int)param_6 < 0) {
    param_6 = 0;
  }

  else
  {
    // L/R max
	if (0xff < (int)param_6) {
      param_6 = 0xff;
    }
  }

  // distortion
  uVar7 = (uVar7 & 0xff) << 8;

  // if echo is required
  if ((*(uint *)(param_2 + 0x2c8) & 0x10000) != 0)
  {
	// add echo
    uVar7 = uVar7 | 0x1000000;
  }

  // EngineAudio_Recalculate
  FUN_800289b0(param_3 + 0x10U & 0xffff,

	// volume
	(uVar4 & 0xff) << 0x10 |

	// distortion
	uVar7 |

	// L/R
	param_6 & 0xff);

  return;
}


// EngineSound_NearestAIs
void FUN_8002ff28(void)

{
  short sVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  long lVar5;
  undefined4 uVar6;
  undefined *puVar7;
  int iVar8;
  int *piVar9;
  int iVar10;
  int iVar11;
  undefined4 uVar12;
  int local_48 [4];
  short local_38 [4];
  long local_30 [2];
  int local_28;

  // This function is only executed if number
  // of AIs is not zero, so this check here
  // is mildly redundant

  // If number of AIs is not zero
  if (PTR_DAT_8008d2ac[0x1cab] != '\0')
  {

	local_48[0] = 0;
    local_48[1] = 0;
    local_48[2] = 0x7fffffff;
    local_48[3] = 0x7fffffff;

	// pointer to first robotcar thread
    iVar11 = *(int *)(PTR_DAT_8008d2ac + 0x1b40);

	// loop through all robotcars
    while (iVar11 != 0)
	{
	  // thread -> object
	  iVar8 = *(int *)(iVar11 + 0x30);

	  // loop counter
	  iVar10 = 0;

	  // if numPlyrCurrGame is not zero
      if (PTR_DAT_8008d2ac[0x1ca8] != '\0')
	  {
		// pointer incrementer
        iVar2 = 0;

		// loop for number of players (max 2)
        do
		{
		  // pushBuffer
          puVar7 = PTR_DAT_8008d2ac + (iVar2 >> 0x10) * 0x110;

		  // Subtract robotcar position from pushBuffer position
          iVar2 = (int)*(short *)(puVar7 + 0x168) - (*(int *)(iVar8 + 0x2d4) >> 8);
          iVar3 = (int)*(short *)(puVar7 + 0x16a) - (*(int *)(iVar8 + 0x2d8) >> 8);
          iVar4 = (int)*(short *)(puVar7 + 0x16c) - (*(int *)(iVar8 + 0x2dc) >> 8);

		  // Distance formula in 3D
          iVar3 = SquareRoot0(iVar2 * iVar2 + iVar3 * iVar3 + iVar4 * iVar4);

		  // find which robotcar is closest and farthest?

          sVar1 = local_38[0];
          iVar2 = local_48[0];

          if (iVar3 < local_48[2])
		  {
			// set loop index
            local_38[0] = (short)iVar10;
            local_48[3] = local_48[2];
            local_48[2] = iVar3;

			// robotcar Driver object
            local_48[0] = iVar8;

			local_38[1] = sVar1;
            local_48[1] = iVar2;
          }
          else {
            if (iVar3 < local_48[3]) {
              local_38[1] = (short)iVar10;
              local_48[3] = iVar3;

			  // robotcar Driver object
              local_48[1] = iVar8;
            }
          }

		  // loop counter
          iVar10 = iVar10 + 1;

		  // pointer incrementer
          iVar2 = iVar10 * 0x10000;

											// numPlyrCurrGame
        } while (iVar10 * 0x10000 >> 0x10 < (int)(uint)(byte)PTR_DAT_8008d2ac[0x1ca8]);
      }

	  // robotcar->next
      iVar11 = *(int *)(iVar11 + 0x10);
    }

    iVar11 = 0;

	// loop twice, max of 2 players
	// can hear AI audio
    do {
      sVar1 = (short)iVar11;
      iVar10 = local_48[sVar1];
      if (iVar10 != 0)
	  {
		// CameraDC -> 0x44 (Driver)
        uVar12 = *(undefined4 *)(PTR_DAT_8008d2ac + (int)local_38[sVar1] * 0xdc + 0x14dc);

		// GTE_AudioLR_Driver
		// param1 - matrix
		// param2 - driver
		// param3 - return vector
        FUN_8002e5cc(PTR_DAT_8008d2ac + (int)local_38[sVar1] * 0x110 + 0x1d0,iVar10,local_30);

		// direction X and Z from previous function
		lVar5 = ratan2(local_30[0],-local_28);

		iVar8 = (lVar5 + 0x800) * -0x100000 >> 0x17;
        if (iVar8 < 0x81) {
          iVar2 = -0x100;
          if (iVar8 < -0x80) goto LAB_8003014c;
        }
        else {
          iVar2 = 0x100;
LAB_8003014c:
          iVar8 = iVar2 - iVar8;
        }
        iVar2 = (int)sVar1;

		// Audio L/R
		// EngineSound_VolumeAdjust
		uVar6 = FUN_8002fc28(iVar8 + 0x80,(&DAT_8008d828)[iVar2],10);
        (&DAT_8008d828)[iVar2] = uVar6;

        piVar9 = local_48 + iVar2 + 2;

		// EngineSound_AI
        FUN_8002fc64(iVar10,uVar12,iVar2,*piVar9,*piVar9 - (&DAT_8008d820)[iVar2],uVar6);

		(&DAT_8008d820)[iVar2] = *piVar9;
      }
      iVar11 = iVar11 + 1;
    } while (iVar11 * 0x10000 >> 0x10 < 2);
  }
  return;
}


// Garage_Init
void FUN_80030208(void)

{
  undefined1 *puVar1;
  int iVar2;

  // howl_StopAudio
  // erase backup, keep music, stop all fx
  FUN_8002c8a8(1,0,1);

  // loop counter
  iVar2 = 0;

  puVar1 = &DAT_800962e4;

  // for iVar2 = 0; iVar2 < 8; iVar2++
  do {
    *puVar1 = 3;
    puVar1[1] = 3;
    *(undefined2 *)(puVar1 + 2) = 0;
    *(undefined2 *)(puVar1 + 4) = 0;
    *(undefined4 *)(puVar1 + 8) = 0;

	// increment loop counter
    iVar2 = iVar2 + 1;
    puVar1 = puVar1 + 0xc;
  } while (iVar2 < 8);
  return;
}



// Garage_Enter
void FUN_80030264(int param_1)

{
  undefined *puVar1;
  byte *pbVar2;
  int iVar3;
  undefined4 *puVar4;
  int iVar5;
  int iVar6;

  // param_1 is the characterID you
  // are focused on, same pattern as 80086e84

  // if characterID is valid
  if (param_1 < 8)
  {
	// characterID to the left
    iVar6 = param_1 + -1;

	// characterID to the right
    iVar5 = param_1 + 1;

	// if left of Crash
    if (iVar6 < 0)
	{
	  // go to pura
      iVar6 = 7;
    }

	// loop counter
    iVar3 = 0;

	// if right of pura
    if (7 < iVar5)
	{
	  // go to Crash
      iVar5 = 0;
    }
    puVar1 = &DAT_800962e4;
    pbVar2 = &DAT_8008d080;
    puVar4 = &DAT_800962ec;

	// loop through all characters in garage
	// for iVar3 = 0; iVar3 < 8; iVar3++
	do
	{
	  // if this character is in focus
      if (iVar3 == param_1)
	  {
        *puVar1 = 0;
        puVar1[1] = 3;
        *(undefined2 *)(puVar1 + 2) = 0;

		// Balance Left/Right
        *(undefined2 *)(puVar1 + 4) = 0x80;

		if (*pbVar2 == 0) goto LAB_800303bc;
        FUN_8002e690(puVar4,(uint)*pbVar2,(int)*(short *)(puVar1 + 2) << 0x10 | 0x8080);
      }

	  else
	  {
		// if this character is to the left
        if (iVar3 == iVar6)
		{
          *puVar1 = 1;
          puVar1[1] = 3;
          *(undefined2 *)(puVar1 + 2) = 0;

		  // 75% left, 25% right
          *(undefined2 *)(puVar1 + 4) = 0x3c;

		  if (*pbVar2 != 0) {
            FUN_8002e690(puVar4,(uint)*pbVar2,(int)*(short *)(puVar1 + 2) << 0x10 | 0x803c);
            goto LAB_800303c4;
          }
        }
        else
		{
		  // if this character is to the right
          if (iVar3 == iVar5)
		  {
            *puVar1 = 2;
            puVar1[1] = 3;
            *(undefined2 *)(puVar1 + 2) = 0;

			// 25% left, 75% right
            *(undefined2 *)(puVar1 + 4) = 0xc3;

			if (*pbVar2 != 0) {
              FUN_8002e690(puVar4,(uint)*pbVar2,(int)*(short *)(puVar1 + 2) << 0x10 | 0x80c3);
              goto LAB_800303c4;
            }
          }

		  // if this character is too far away
		  // to make any sound at all
          else
		  {
            *puVar1 = 3;
            puVar1[1] = 3;
            *(undefined2 *)(puVar1 + 2) = 0;
            *(undefined2 *)(puVar1 + 4) = 0x80;
          }
        }
LAB_800303bc:
        *(undefined4 *)(puVar1 + 8) = 0;
      }
LAB_800303c4:
      puVar1 = puVar1 + 0xc;
      pbVar2 = pbVar2 + 1;

	  // increment loop counter
      iVar3 = iVar3 + 1;

      puVar4 = puVar4 + 3;
    } while (iVar3 < 8);
  }
  return;
}


// Garage_PlayFX
void FUN_80030404(uint param_1,int param_2)

{
  if (param_2 < 8) 
  {
	// if sound == BIRD_RANDOM
    if (param_1 == 0xf6)
	{
	  // pick a new sound, 0xF3, 0xF4, or 0xF5,
	  // one of three different bird noises near Pura
		
	  // inline audioRNG scramble
      DAT_8008d058 = ((DAT_8008d058 >> 3) + DAT_8008d058 * 0x20000000) * 5 + 1;

	  // soundId = (random%3) + 0xf3;
	  param_1 =
				(
					// 100%
					DAT_8008d058 -

					// 99%
					(
						// 66%
						((uint)((ulonglong)DAT_8008d058 * 0xaaaaaaab >> 0x20) & 0xfffffffe) +

						// 33%
						DAT_8008d058 / 3
					)
				) + 0xf3;
    }

	// OtherFX_Play_LowLevel
    FUN_800284d0(param_1 & 0xffff,1,

				 // volume
                 (uint)*(byte *)(&DAT_800962e6 + param_2 * 6) << 0x10 |

				 // left/right
                 (uint)*(byte *)(&DAT_800962e8 + param_2 * 6)

				 // distortion
				 | 0x8000);
  }
  return;
}


// Garage_LerpFX
void FUN_800304b8(void)

{
  char cVar1;
  bool bVar2;
  short sVar3;
  char *pcVar4;
  short sVar5;
  short sVar6;
  undefined4 *puVar7;

  // loop counter
  int iVar8;
  iVar8 = 0;

  pcVar4 = &DAT_800962e4;
  puVar7 = &DAT_800962ec;

  // for iVar8 = 0; iVar8 < 8; iVar8++
  do {
    cVar1 = *pcVar4;
	
	// center
    if (cVar1 == '\0') {
      sVar6 = 0xff;
      sVar5 = 0x80;
    }
    else 
	{
	  // left
      if (cVar1 == '\x01') {
        sVar6 = 100;
        sVar5 = 0x3c;
      }
      else 
	  {
        sVar6 = 0;
        
		// right
		if (cVar1 == '\x02') {
          sVar6 = 100;
          sVar5 = 0xc3;
        }

		// too far
        else 
		{
          sVar5 = *(short *)(pcVar4 + 4);
        }
      }
    }
	
	// desired change
    if ((sVar5 != *(short *)(pcVar4 + 4)) || (sVar6 != *(short *)(pcVar4 + 2))) 
	{
      if (sVar6 != *(short *)(pcVar4 + 2)) {
        sVar3 = *(short *)(pcVar4 + 2) + 8;
        if (*(short *)(pcVar4 + 2) < sVar6) {
          *(short *)(pcVar4 + 2) = sVar3;
          bVar2 = sVar6 < sVar3;
        }
        else {
          sVar3 = *(short *)(pcVar4 + 2) + -8;
          *(short *)(pcVar4 + 2) = sVar3;
          bVar2 = sVar3 < sVar6;
        }
        if (bVar2) {
          *(short *)(pcVar4 + 2) = sVar6;
        }
      }
      if (sVar5 != *(short *)(pcVar4 + 4)) {
        sVar3 = *(short *)(pcVar4 + 4) + 2;
        if (*(short *)(pcVar4 + 4) < sVar5) {
          *(short *)(pcVar4 + 4) = sVar3;
          bVar2 = sVar5 < sVar3;
        }
        else {
          sVar3 = *(short *)(pcVar4 + 4) + -2;
          *(short *)(pcVar4 + 4) = sVar3;
          bVar2 = sVar3 < sVar5;
        }
        if (bVar2) {
          *(short *)(pcVar4 + 4) = sVar5;
        }
      }
      if ((&DAT_8008d080)[iVar8] != 0) {
        FUN_8002e690(puVar7,(uint)(byte)(&DAT_8008d080)[iVar8],
                     (int)*(short *)(pcVar4 + 2) << 0x10 | (int)*(short *)(pcVar4 + 4) | 0x8000U);
      }
	  
	  // change is finished
      if (((sVar5 == *(short *)(pcVar4 + 4)) && (sVar6 == *(short *)(pcVar4 + 2))) &&
         (pcVar4[1] = *pcVar4, *pcVar4 == '\x03'))
	  {
		// OtherFX_RecycleMute
        FUN_8002e724(puVar7);
      }
    }
    puVar7 = puVar7 + 3;

	// increment loop counter
    iVar8 = iVar8 + 1;

    pcVar4 = pcVar4 + 0xc;
  } while (iVar8 < 8);
  return;
}


// Garage_MoveLR
// param_1 = desired characterID
void FUN_80030694(int param_1)

{
  char *pcVar1;
  int iVar2;
  int iVar3;
  int iVar4;

  // left ID
  iVar4 = param_1 + -1;

  // if desired is valid
  if (param_1 < 8)
  {
	// right ID
    iVar3 = param_1 + 1;

	// if left ID is to the left of Crash
    if (iVar4 < 0)
	{
	  // use Pura
      iVar4 = 7;
    }

    iVar2 = 0;

	// if right ID is to the right of Pura
	if (7 < iVar3)
	{
	  // use Crash
      iVar3 = 0;
    }

	pcVar1 = &DAT_800962e4;

	// loop through 8 characters
    do
	{
	  // character in focus
      if (iVar2 == param_1) {
        *pcVar1 = '\0';
      }
      else
	  {
		// left ID
        if (iVar2 == iVar4)
		{
          if (*pcVar1 == '\x03')
		  {
			// 75% left, 25% right
            *(undefined2 *)(pcVar1 + 4) = 0x3c;
          }
          *pcVar1 = '\x01';
        }
        else
		{
		  // right ID
          if (iVar2 == iVar3)
		  {
            if (*pcVar1 == '\x03')
			{
			  // 25% left, 75% right
              *(undefined2 *)(pcVar1 + 4) = 0xc3;
            }
            *pcVar1 = '\x02';
          }
          else {
            *pcVar1 = '\x03';
          }
        }
      }
      iVar2 = iVar2 + 1;
      pcVar1 = pcVar1 + 0xc;
    } while (iVar2 < 8);
  }
  return;
}



// Garage_Leave
void FUN_8003074c(void)

{
  undefined1 *puVar1;
  int iVar2;

  // loop 7 times
  iVar2 = 7;

  // reset 800962E4 to 80096338
  puVar1 = &DAT_80096338;

  do
  {
	// write
    *puVar1 = 3;

	// loop index
    iVar2 = iVar2 + -1;

	// go backwards
    puVar1 = puVar1 + -0xc;
  } while (-1 < iVar2);

  return;
}

