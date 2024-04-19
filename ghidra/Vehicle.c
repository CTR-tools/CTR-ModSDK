
// VehAfterColl_GetSurface
int FUN_80057c44(uint param_1)

{
  int iVar1;

  iVar1 = param_1 << 4;
  if (6 < param_1) {
    iVar1 = 0;
  }
  return (int)&PTR_s_SOLID_80087f94 + iVar1;
}


// VehAfterColl_GetTerrain
int FUN_80057c68(uint param_1)

{
  int iVar1;

  iVar1 = param_1 << 6;
  if (0x14 < param_1) {
    iVar1 = 0;
  }
  return (int)&PTR_s_asphalt_800884cc + iVar1;
}


// VehBirth_TeleportSelf
void FUN_80057c8c(int param_1,uint param_2,int param_3)

{
  byte bVar1;
  short sVar2;
  bool bVar3;
  undefined *puVar4;
  undefined uVar5;
  undefined2 uVar6;
  undefined4 uVar7;
  code *pcVar8;
  int iVar9;
  undefined *puVar10;
  uint uVar11;
  int *piVar12;
  ushort uVar13;
  int iVar14;
  int *piVar15;
  undefined2 *puVar16;
  short local_40;
  short local_3e;
  short local_3c;
  short local_38;
  short local_36;
  short local_34;
  short local_30;
  short local_2e;
  short local_2c;

  puVar4 = PTR_DAT_8008d2ac;
  puVar16 = (undefined2 *)0x0;
  bVar3 = false;
  
  // by default, dont spawn by a hub door
  piVar15 = (int *)0x0;

  // Check LEV data for nullptr
  if (*(int **)(PTR_DAT_8008d2ac + 0x160) == (int *)0x0) {
    return;
  }
  if (**(int **)(PTR_DAT_8008d2ac + 0x160) == 0) {
    return;
  }

  // ground and wall quadblock flags
  DAT_1f80012c = 0x3000;

  DAT_1f800130 = 0;
  
  // low-LOD collision (2 triangles)
  DAT_1f80012a = 0;

  // if numPlyrCurrGame is less than 3
  if ((byte)PTR_DAT_8008d2ac[0x1ca8] < 3) 
  {
	// high-LOD collision (8 triangles)
    DAT_1f80012a = 2;
  }
  
  DAT_1f800134 = **(undefined4 **)(PTR_DAT_8008d2ac + 0x160);
  *(uint *)(PTR_DAT_8008d2ac + 8) = *(uint *)(PTR_DAT_8008d2ac + 8) & 0xffffbfff;
  puVar10 = PTR_DAT_8008d2ac;

  // if you are mask grabbed
  if ((param_2 & 1) == 0)
  {
	// Ordinary player position
    local_38 = (short)((uint)*(undefined4 *)(param_1 + 0x2d4) >> 8);
    local_36 = (short)((uint)*(undefined4 *)(param_1 + 0x2d8) >> 8) + 0x80;
    local_34 = (short)((uint)*(undefined4 *)(param_1 + 0x2dc) >> 8);
  }

  // if you are spawning into the world for the first time,
  // could be startline, or adv hub spawn in several places
  else
  {
	// spawn in front of hub door, beach-to-gemstone
    if (
			// If you are at podium after winning a Key
			(*(short *)(puVar4 + 0x2572) == 99) &&

			// If you have one boss key
			(*(int *)(puVar4 + 0x1e38) == 1)
		)
	{
      // lev number instDef
	  iVar9 = *(int *)(*(int *)(puVar4 + 0x160) + 0xc);
	  
	  // lev instDefs
      piVar15 = *(int **)(*(int *)(puVar4 + 0x160) + 0x10);
      
	  iVar14 = 0;
	  
	  // if there are instDefs
      if (0 < iVar9) 
	  {
		// waste of addition
        piVar12 = piVar15 + 3;
        
		// loop through instDefs
		do 
		{
		  // if door is found
          if (
				(
					(
						// InstDef+0xC+0xC (modelID) == 0x7a (STATIC_DOOR)
						(*(short *)(piVar12 + 0xc) == 0x7a) && 
						
						// if name == "door"
						(*piVar15 == 0x726f6f64)
					) &&
              
					// InstDef+0xC-0x8 (name) == "#5"
					(piVar12[-2] == 0x3523)
				) && 
				
				// last 8 bytes of 16-byte name, all zeros
				((piVar12[-1] == 0 && (*piVar12 == 0)))
			 
			 // then leave loop
			 ) break;
			  
		  // next InstDef
          piVar12 = piVar12 + 0x10;
          
		  // loop counter
		  iVar14 = iVar14 + 1;
		  
		  // next InstDef (0x10*4)
          piVar15 = piVar15 + 0x10;
        
		} while (iVar14 < iVar9);
		
		// if the hub door was found, because not all instDefs were checked, then go to spawn
        if (iVar14 < *(int *)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0xc)) goto code_r0x80057f18;
      }
	  
	  // no InstDef found with "door" title,
	  // so spawn outside boss door instead
      piVar15 = (int *)0x0;
    }

	// If you not at hub-door after beating Roo
    else
	{
	  // if you are at podium for winning a trophy
      if (*(short *)(PTR_DAT_8008d2ac + 0x2572) == 0x62)
	  {
		// By default, you have all 4 trophies on a hub,
		// but we are about to determine if that's true
        bVar3 = true;

		// loop counter
        iVar14 = 0;
								// Level ID
        iVar9 = (*(int *)(PTR_DAT_8008d2ac + 0x1a10) + -0x1a) * 8;

		// for iVar14 = 0; iVar14 < 4; iVar14++
		do
		{
		  // increment loop counter
          iVar14 = iVar14 + 1;

		  // 0x8fba4 is where the adventure profile (currently loaded) begins

		  // if you do not have a trophy on this track
          if (((uint)(&DAT_8008fba4)[(int)((int)*(short *)(&DAT_800840f4 + iVar9) + 6U) >> 5] >>
               ((int)*(short *)(&DAT_800840f4 + iVar9) + 6U & 0x1f) & 1) == 0)
		  {
			// record that not all 4 trophies are collected on this hub
            bVar3 = false;
            break;
          }
          iVar9 = iVar9 + 2;
        } while (iVar14 < 4);

		// if you have all 4 trophies on a hub
        if ((bVar3) &&

			// 0x8fba4 is where the adventure profile (currently loaded) begins
													// Level ID
           (((uint)(&DAT_8008fba4)[(int)(*(int *)(PTR_DAT_8008d2ac + 0x1a10) + 0x44U) >> 5] >>
             (*(int *)(PTR_DAT_8008d2ac + 0x1a10) + 0x44U & 0x1f) & 1) != 0)) {

		  // dont spawn outside boss garage
		  bVar3 = false;
        }
      }
    }
code_r0x80057f18:

	// if you just exited boss race
    if ((*(uint *)(PTR_DAT_8008d2ac + 8) & 1) != 0)
	{
	  // spawn outside boss door
      bVar3 = true;
    }

	// if not spawning at hub door
    if (piVar15 == (int *)0x0)
	{
	  // if you want to spawn outside boss door
      if (bVar3)
	  {
		// position outside boss door
        local_38 = *(short *)(*(int *)(*(int *)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0x144) + 0xc) +
                             0xc);
        local_36 = *(short *)(*(int *)(*(int *)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0x144) + 0xc) +
                             0xe) + 0x80;
        local_34 = *(short *)(*(int *)(*(int *)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0x144) + 0xc) +
                             0x10);
      }

	  // If spawning anywhere else
      else {

		 // If you're not in Adventure Arena,
		 // Therefore, if spawning at startline of race track
        if ((*(uint *)PTR_DAT_8008d2ac & 0x100000) == 0) {
LAB_80058158:
		  // get index where driver should spawn (0-7)
          bVar1 = (&DAT_8008d69c)[*(byte *)(param_1 + 0x4a)];

          // racer crossed the start line backwards,
		  // so lap doesn't count when race starts
          *(uint *)(param_1 + 0x2c8) = *(uint *)(param_1 + 0x2c8) | 0x1000000;

		  // set distToFinish_checkpoint = level -> distSpawnToFinish
          *(int *)(param_1 + 0x48c) =
               (uint)*(ushort *)(*(int *)(*(int *)(puVar10 + 0x160) + 0x14c) + 6) << 3;

		  // convert spawn index to byte index,
		  // each spawn position is 3 ints (x,y,z)
          iVar9 = (uint)bVar1 * 0xc;

		  // get position where each of the 8 drivers should spawn, from LEV
          local_38 = *(short *)(*(int *)(puVar10 + 0x160) + iVar9 + 0x6c);
          local_36 = *(short *)(*(int *)(puVar10 + 0x160) + iVar9 + 0x6e) + 0x80;
          local_34 = *(short *)(*(int *)(puVar10 + 0x160) + iVar9 + 0x70);
        }

		// if you are in adventure arena
        else
		{
		  // if no podium reward
          if (*(short *)(PTR_DAT_8008d2ac + 0x2572) == 0) {

			// ivar9 = level you were in previously
            iVar9 = *(int *)(PTR_DAT_8008d2ac + 0x1eb4);

			// if you just came from any of these...
            if (

				// main menu, or adv character garage
				((iVar9 == 0x27) || (iVar9 == 0x28)) ||

			   // nowhere?, or cutscene?
			   ((iVar9 == -1 || ((iVar9 == 0x40 || (iVar9 - 0x2cU < 0x14)))))) goto LAB_80058158;

			// get position where driver should spawn on map,
			// outside warppad they previously entered

			// AH_WarpPad_GetSpawnPosRot
			puVar16 = (undefined2 *)FUN_800abafc(&local_30);
            local_38 = local_30;
            local_36 = local_2e + 0x80;
            local_34 = local_2c;
          }

		  // if you have a podium reward
          else
		  {
			// spawn on the podium in the adv hub
            local_38 = **(short **)(*(int *)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0x144) + 0xc);
            local_36 = *(short *)(*(int *)(*(int *)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0x144) +
                                          0xc) + 2) + 0x80;
            local_34 = *(short *)(*(int *)(*(int *)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0x144) +
                                          0xc) + 4);
          }
        }
      }
    }
    
	// if spawning at hub door
	else 
	{
	  // do trigonometry to take hub door 
		
      *(uint *)(PTR_DAT_8008d2ac + 8) = *(uint *)(PTR_DAT_8008d2ac + 8) | 0x4000;

	  // Cosine(angle)
	  // instDef rotY
	  iVar9 = FUN_8003d1c0((int)*(short *)(piVar15 + 0xe));

	  // Cosine(angle)
	  // instDef rotY+400 (perpendicular)
	  iVar14 = FUN_8003d1c0((int)*(short *)(piVar15 + 0xe) + 0x400);

	  // posX = 
			// instDef posX + (where door starts)
			// doorLengthX + (to get to midpoint between two doors)
			// perpendicularX (to spawn away from door)
	  local_38 = *(short *)(piVar15 + 0xc) + (short)(iVar9 * 800 >> 0xc) +
                 (short)((iVar14 << 9) >> 0xc);
				 
	  // posY = instDef posY + random height offset
      local_36 = *(short *)((int)piVar15 + 0x32) + 0x17a;

	  // Sine(angle)
	  // instDef rotY
	  iVar9 = FUN_8003d184((int)*(short *)(piVar15 + 0xe));

	  // Sine(angle)
	  // instDef rotY+400 (perpendicular)
      iVar14 = FUN_8003d184((int)*(short *)(piVar15 + 0xe) + 0x400);

	  // posZ = 
			// instDef posZ + (where door starts)
			// doorLengthZ + (to get to midpoint between two doors)
			// perpendicularZ (to spawn away from door)
	  local_34 = *(short *)(piVar15 + 0xd) + (short)(iVar9 * 800 >> 0xc) +
                 (short)((iVar14 << 9) >> 0xc);
    }
  }
  local_40 = local_38;
  local_3c = local_34;
  local_3e = local_36 + -0x100;

  // COLL_SearchTree_FindQuadblock_Touching
  FUN_8001eb0c(&local_40,&local_38,&DAT_1f800108,0);

  // if collision was not found
  if (DAT_1f800146 == 0) {
    *(undefined2 *)(param_1 + 0x370) = 0;
    *(undefined2 *)(param_1 + 0x372) = 0x1000;
    *(undefined2 *)(param_1 + 0x374) = 0;
  }

  // if it was found
  else {
    *(undefined2 *)(param_1 + 0x370) = DAT_1f800178;
    *(undefined2 *)(param_1 + 0x372) = DAT_1f80017a;
    *(undefined2 *)(param_1 + 0x374) = DAT_1f80017c;
    *(undefined4 *)(param_1 + 0x354) = DAT_1f800188;
  }

  // loop counter
  iVar14 = 0;

  // set all normal vectors to spawn
  *(undefined2 *)(param_1 + 0x360) = *(undefined2 *)(param_1 + 0x370);
  *(undefined2 *)(param_1 + 0x368) = *(undefined2 *)(param_1 + 0x370);
  *(undefined2 *)(param_1 + 0x362) = *(undefined2 *)(param_1 + 0x372);
  *(undefined2 *)(param_1 + 0x36a) = *(undefined2 *)(param_1 + 0x372);
  *(undefined2 *)(param_1 + 0x364) = *(undefined2 *)(param_1 + 0x374);
  *(undefined2 *)(param_1 + 0x36c) = *(undefined2 *)(param_1 + 0x374);
  
  iVar9 = param_1;

  // for iVar14 = 0; iVar14 < 1; iVar14++
  do
  {
	// set normal vector to spawn
    *(undefined2 *)(iVar9 + 0x378) = *(undefined2 *)(param_1 + 0x368);
    *(undefined2 *)(iVar9 + 0x37a) = *(undefined2 *)(param_1 + 0x36a);
	iVar14 = iVar14 + 1; // increment loop counter
	*(undefined2 *)(iVar9 + 0x37c) = *(undefined2 *)(param_1 + 0x36c);
    
	iVar9 = iVar9 + 8;
  
  } while (iVar14 < 1);

  // player structure X, Y, Z
  *(int *)(param_1 + 0x2d4) = (int)(short)DAT_1f800124 << 8;
  *(int *)(param_1 + 0x2d8) = (DAT_1f800124._2_2_ + param_3) * 0x100;
  *(int *)(param_1 + 0x2dc) = (int)((uint)DAT_1f800128 << 0x10) >> 8;

  // duplicate of coordinate variables
  *(undefined4 *)(param_1 + 0x2e4) = *(undefined4 *)(param_1 + 0x2d8);
  *(undefined4 *)(param_1 + 0x2e0) = *(undefined4 *)(param_1 + 0x2d4);
  *(undefined4 *)(param_1 + 0x2e8) = *(undefined4 *)(param_1 + 0x2dc);

  // save quadblock height
  *(int *)(param_1 + 0x2d0) = (int)DAT_1f800124._2_2_ << 8;

  puVar4 = PTR_DAT_8008d2ac;

  // if you are spawning into the world for the first time,
  // could be startline, or adv hub spawn in several places
  if ((param_2 & 1) != 0)
  {
    if (piVar15 == (int *)0x0)
	{
	  // if spawning outside boss door
      if (bVar3)
	  {
		// get desired rotation of driver when leaving portal, or spawning at startline
        uVar13 = *(short *)(*(int *)(*(int *)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0x144) + 0xc) +
                           0x14) + 0x400U & 0xfff;

        *(ushort *)(param_1 + 0x2ee) = uVar13;

		// if just finished a boss race
        if ((*(uint *)(puVar4 + 8) & 1) != 0) {

		  // Level ID is citadel city
          if (*(int *)(puVar4 + 0x1a10) == 0x1d)
		  {
			// rotate 90 degrees to the right,
			// so you dont have a wall in your face
            uVar13 = uVar13 + 0x400;
          }

		  // if not...
          else
		  {
			// Level ID == 25
			// Level ID == GemStone Valley
            if ((*(int *)(puVar4 + 0x1a10) == 0x19) &&

				// If you just exited hot air skyway,
				// just finished pinstripe boss,
				// spawned by oxide's door
				(*(int *)(puVar4 + 0x1eb4) == 7)
			   )
			{
			  // use default rotation, face oxide's door
              *(ushort *)(param_1 + 0x2ee) = uVar13;

              goto LAB_80058438;
            }

			// If driver spawned to any other boss,
			// for any other reason

			// rotate 180 degrees, facing away from boss door
            uVar13 = *(short *)(param_1 + 0x2ee) + 0x800;
          }

		  // bitwise AND, do not go over 0x1000 (360 degrees)
          *(ushort *)(param_1 + 0x2ee) = uVar13 & 0xfff;
        }
LAB_80058438:
        *(uint *)(PTR_DAT_8008d2ac + 8) = *(uint *)(PTR_DAT_8008d2ac + 8) & 0xfffffffc;
      }

	  // if not outside boss door
	  else {

		// If you're not in Adventure Arena
        if ((*(uint *)PTR_DAT_8008d2ac & 0x100000) == 0)
		{
LAB_800584f8:

		  // position index on starting line
          iVar9 = (uint)(byte)(&DAT_8008d69c)[*(byte *)(param_1 + 0x4a)] * 0xc;

		  // rotation data of all 8 drivers on starting line
          *(undefined2 *)(param_1 + 0x2ec) =
               *(undefined2 *)(*(int *)(PTR_DAT_8008d2ac + 0x160) + iVar9 + 0x72);
          sVar2 = *(short *)(*(int *)(puVar4 + 0x160) + iVar9 + 0x74);
          *(short *)(param_1 + 0x2ee) = sVar2;
          uVar6 = *(undefined2 *)(*(int *)(puVar4 + 0x160) + iVar9 + 0x76);
        }

		// if on adv hub
        else
		{
		  // podium reward
          if (*(short *)(PTR_DAT_8008d2ac + 0x2572) != 0)
		  {
			// set rotation, expecting driver to spawn on podium
            *(ushort *)(param_1 + 0x2ee) =
                 *(ushort *)
                  (*(int *)(*(int *)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0x144) + 0xc) + 8) & 0xfff
            ;
            goto LAB_80058568;
          }


          if (
				(
					// If you just came from the main menu
					(*(int *)(PTR_DAT_8008d2ac + 0x1eb4) == 0x27) ||

					// If you just came from "nothing"
					(*(int *)(PTR_DAT_8008d2ac + 0x1eb4) == -1)

				// if WarpPad_ReturnToMap failed to find a matching portal
				) || (puVar16 == (undefined2 *)0x0))

		  // skip
		  goto LAB_800584f8;

		  // rotation data from spawning near hub warppad,
		  // after leaving a race or event
          *(undefined2 *)(param_1 + 0x2ec) = *puVar16;
          sVar2 = puVar16[1];
          *(short *)(param_1 + 0x2ee) = sVar2;
          uVar6 = puVar16[2];
        }
        *(ushort *)(param_1 + 0x2ee) = sVar2 + 0x400U & 0xfff;
        *(undefined2 *)(param_1 + 0x2f0) = uVar6;
      }
    }
    else {
      *(ushort *)(param_1 + 0x2ee) = *(short *)(piVar15 + 0xe) + 0x800U & 0xfff;
      *(uint *)(puVar4 + 8) = *(uint *)(puVar4 + 8) & 0xfffffffc;
    }
  }
LAB_80058568:

  // set speed to zero
  *(undefined2 *)(param_1 + 0x38c) = 0;

  *(undefined2 *)(param_1 + 0x38e) = 0;
  *(undefined2 *)(param_1 + 0x390) = 0;
  *(undefined2 *)(param_1 + 0x392) = 0;
  *(undefined2 *)(param_1 + 0x3b2) = 0;
  *(undefined2 *)(param_1 + 0x39a) = *(undefined2 *)(param_1 + 0x2ee);
  *(undefined2 *)(param_1 + 0x2f4) = *(undefined2 *)(param_1 + 0x2ec);
  *(undefined2 *)(param_1 + 0x2f6) = *(undefined2 *)(param_1 + 0x2ee);
  *(undefined2 *)(param_1 + 0x2f8) = *(undefined2 *)(param_1 + 0x2f0);

  if (
		(piVar15 != (int *)0x0) &&

		// if spawning into world (not mask grab)
		((param_2 & 1) != 0)
	 )
  {
	// spawn with speed (what? when does that ever happen?)
    *(undefined2 *)(param_1 + 0x38c) = 0xa00;
  }

  // set animation to zero
  *(undefined *)(*(int *)(param_1 + 0x1c) + 0x52) = 0;

  // get number of frames in animation
  uVar7 = FUN_8005b0f4(*(undefined4 *)(param_1 + 0x1c),0);

  // VehFrameInst_GetStartFrame
  uVar6 = FUN_8005b0c4(0,uVar7);

  // Animation frame
  *(undefined2 *)(*(int *)(param_1 + 0x1c) + 0x54) = uVar6;

  // Set Scale (x, y, z)
  *(undefined2 *)(*(int *)(param_1 + 0x1c) + 0x1c) = 0xccc;
  *(undefined2 *)(*(int *)(param_1 + 0x1c) + 0x1e) = 0xccc;
  *(undefined2 *)(*(int *)(param_1 + 0x1c) + 0x20) = 0xccc;

  *(undefined *)(param_1 + 0x4c) = 0;
  *(undefined *)(param_1 + 0x4d) = 0;
  *(undefined2 *)(param_1 + 0x3fc) = 0;
  *(undefined2 *)(param_1 + 0x46) = 0;
  *(undefined2 *)(param_1 + 0x48) = 0;
  *(undefined2 *)(param_1 + 0x3c6) = 0;
  *(undefined2 *)(param_1 + 0x3d2) = 0;
  *(undefined2 *)(param_1 + 0x3c8) = 0;
  *(undefined2 *)(param_1 + 0x2f2) = 0;
  *(undefined2 *)(param_1 + 0x2fa) = 0;
  *(undefined *)(param_1 + 0x4ff) = 0;
  *(undefined2 *)(param_1 + 0x40c) = 0;
  *(undefined4 *)(param_1 + 0x350) = 0;
  *(undefined4 *)(param_1 + 0x490) = 0;
  *(undefined2 *)(param_1 + 0xc) = 0;
  *(undefined *)(param_1 + 0x4fe) = 0;

  //turn off 7th and 20th bits of Actions Flag set (means ? (7) and racer is not in the air (20))
  *(uint *)(param_1 + 0x2c8) = *(uint *)(param_1 + 0x2c8) & 0xfff7ffbf;
  if ((param_2 & 2) == 0) {
    return;
  }
  iVar9 = 0xc;

  // driver -> instane -> thread -> modelIndex == "player" of any kind
  if (*(short *)(*(int *)(*(int *)(param_1 + 0x1c) + 0x6c) + 0x44) == 0x18)
  {
	// This erases all driver funcPtrs, 12 funcPtrs, 0x30 bytes total,
	// it is the strangest way to do it, but that's what it does

	// pointer = driver + 0x30
    iVar14 = param_1 + 0x30;

	// erase 12 (0xC) function pointers from
	// driver struct, 0x54 - 0x84 (0x30 bytes),
	// but erase them backwards
    do {
      *(undefined4 *)(iVar14 + 0x54) = 0;
      iVar9 = iVar9 + -1;
      iVar14 = iVar14 + -4;
    } while (-1 < iVar9);

	// CAM_StartOfRace
    FUN_80018d20(PTR_DAT_8008d2ac + (uint)*(byte *)(param_1 + 0x4a) * 0xdc + 0x1498);

    puVar4 = PTR_DAT_8008d2ac;

	// if you are not in cutscene and not in main menu
    if ((*(uint *)PTR_DAT_8008d2ac & 0x20002000) == 0) {
      puVar10 = (undefined *)0x0;
    }

	// if you are in cutscene or main menu
    else
	{
	  // 0x80058c44 is an empty function that does nothing
      puVar10 = &FUN_80058c44;
    }

	// driver -> instance -> thread -> funcThTick = puVar10
    *(undefined **)(*(int *)(*(int *)(param_1 + 0x1c) + 0x6c) + 0x2c) = puVar10;


	// If you're not in Adventure Arena
	if ((*(uint *)puVar4 & 0x100000) == 0)
	{
	  // VehStuckProc_RevEngine_Init
      pcVar8 = FUN_80067f4c;
    }

	// If you're in Adventure Arena
    else
	{
	  // VehPhysProc_Driving_Init
      pcVar8 = FUN_80062b74;
    }

	// set OnInit function
    *(code **)(param_1 + 0x54) = pcVar8;
  }

  // lapIndex = 0
  *(undefined *)(param_1 + 0x44) = 0;

  // numWumpa = 0
  *(undefined *)(param_1 + 0x30) = 0;

  puVar4 = PTR_DAT_8008d2ac;

  // lapTime = 0
  *(undefined4 *)(param_1 + 0x40) = 0;

  // no lap progress
  *(undefined4 *)(param_1 + 0x488) = 0;

  //turn off 21th and 26th flags of Actions Flag set
  //(means ? (21) and racer hasn't finished the race)
  *(uint *)(param_1 + 0x2c8) = *(uint *)(param_1 + 0x2c8) & 0xfdefffff;

  // If unlimited wumpa cheat is enabled
  if ((*(uint *)(puVar4 + 8) & 0x200) != 0)
  {
	// Set wumpa to 99
    *(undefined *)(param_1 + 0x30) = 99;
  }

  //set Held item to none
  *(undefined *)(param_1 + 0x36) = 0xf;

  //set Held item Quantity to 0
  *(undefined *)(param_1 + 0x37) = 0;

  puVar4 = PTR_DAT_8008d2ac;

  // collected zero C-T-R letters
  *(undefined4 *)(param_1 + 0x4cc) = 0;

  // cheat flags
  uVar11 = *(uint *)(puVar4 + 8);

  // set weaponID to mask
  uVar5 = 7;

  // if unlimited masks is disabled
  if ((uVar11 & 0x400) == 0)
  {
	// if unlimited turbos is disabled
    if ((uVar11 & 0x800) == 0)
	{
	  // set weaponID to bomb
      uVar5 = 1;

	  // if infinite bombs is disabled
      if ((uVar11 & 0x400000) == 0) goto LAB_800587cc;

	  goto LAB_800587c0;
    }

	// set weaponID to turbo
    *(undefined *)(param_1 + 0x36) = 0;
  }
  else
  {
LAB_800587c0:
	// set weaponID
    *(undefined *)(param_1 + 0x36) = uVar5;
  }

  //set Held item Quantity to 9 (Cheat related)
  *(undefined *)(param_1 + 0x37) = 9;

LAB_800587cc:
  puVar4 = PTR_DAT_8008d2ac;

  // set driver's life limit to the global life limit
  *(undefined4 *)(param_1 + 0x4e4) = *(undefined4 *)(PTR_DAT_8008d2ac + 0x1d88);

  if (
		// If Permanent Invisibility Cheat is Enabled
		((*(uint *)(puVar4 + 8) & 0x8000) != 0) &&

		// Player / AI structure + 0x4a shows driver index (0-7)

		// driver ID must be less than numPlyrCurrGame,
		// which makes the cheat apply to players and not AIs
		(*(byte *)(param_1 + 0x4a) < (byte)puVar4[0x1ca8]))
  {
	// instance flags
    *(uint *)(*(int *)(param_1 + 0x1c) + 0x28) =
         *(uint *)(*(int *)(param_1 + 0x1c) + 0x28) & 0xfff8ffff;

	// instance flags
    *(uint *)(*(int *)(param_1 + 0x1c) + 0x28) =
         *(uint *)(*(int *)(param_1 + 0x1c) + 0x28) | 0x60000;

	// invisible timer
    *(undefined4 *)(param_1 + 0x28) = 0x2d00;
  }


  // If Super Engine Cheat is enabled
  if ((*(uint *)(PTR_DAT_8008d2ac + 8) & 0x10000) != 0) {
    *(undefined2 *)(param_1 + 0x38) = 0x2d00;
  }
  return;
}


// VehBirth_TeleportAll
void FUN_80058898(undefined4 param_1,uint param_2)

{
  // pointer to player address
  int iVar1;

  // iteration counter
  int iVar2;
  iVar2 = 0;

  do
  {
	// address of player structure, idk which
    iVar1 = *(int *)(PTR_DAT_8008d2ac + ((iVar2 << 0x10) >> 0xe) + 0x24ec);

	// if player structure is not nullptr
    if (iVar1 != 0)
	{
	  // driver -> instance -> thread -> modelIndex == "robotcar" of any kind
      if (*(short *)(*(int *)(*(int *)(iVar1 + 0x1c) + 0x6c) + 0x44) == 0x3f)
	  {
		// BOTS_GotoStartingLine
        FUN_8001702c();
      }
      else
	  {
		// VehBirth_TeleportSelf (startline)
        FUN_80057c8c(iVar1,param_2 | 1,0);
      }
    }

	// increment loop iteration counter
    iVar2 = iVar2 + 1;

  } while (iVar2 * 0x10000 >> 0x10 < 8);
  return;
}


// VehBirth_GetModelByName
int * FUN_80058948(int *param_1)

{
  int *piVar1;
  int **ppiVar2;
  int *piVar3;
  int iVar4;

  piVar3 = (int *)0x0;

  // loop counter
  iVar4 = 0;

  // array to character models loaded,
  // maximum of 4, used in VS mode
  ppiVar2 = (int **)&DAT_80083a10;

  // for iVar4 = 0; iVar4 < 3; iVar4++
  do {

	// dereference model pointer
    piVar1 = *ppiVar2;

	// if model pointer exists,
	// check first 16 bytes of model
	// for a matching string
    if (
			(
				(
					// if model pointer exists
					(piVar1 != (int *)0x0) &&

					// 0-3
					(*piVar1 == *param_1)
				) &&

				// 4-7
				(piVar1[1] == param_1[1])
			) &&
			(
				(
					// 8-11
					piVar1[2] == param_1[2] &&

					// 12-15
					(piVar1[3] == param_1[3])
				)
			)
		)
	{
	  // character found, return pointer
      return piVar1;
    }

	// loop counter
    iVar4 = iVar4 + 1;

	// pointer to next model
    ppiVar2 = ppiVar2 + 1;

  } while (iVar4 < 3);

  if (
		// if PLYROBJECTLIST is not nullptr
		(DAT_8008d870 != (int **)0x0) &&

		// make sure elements of PLYROBJECTLIST are valid
		(piVar3 = *DAT_8008d870, piVar3 != (int *)0x0)

		)
  {
	// PLYROBJECTLIST, used for arcade (6-8 players)
    ppiVar2 = DAT_8008d870;

	// loop until all strings are checked (until current is not nullptr)
    do
	{
	  // if model pointer exists,
	  // check first 16 bytes of model
	  // for a matching string
	  if (
			(
				(
					// if model exists
					(*piVar3 == *param_1) &&

					// 0-3
					(piVar3[1] == param_1[1])
				) &&

				// 4-7
				(piVar3[2] == param_1[2])
			) &&

			// 8-11
			(piVar3[3] == param_1[3])
		 )
	  {
	    // character found, return pointer
        return piVar3;
      }

	  // increment pointer
      ppiVar2 = ppiVar2 + 1;

	  // set to pointer
      piVar3 = *ppiVar2;

    } while (piVar3 != (int *)0x0);
  }
  return piVar3;
}



// VehBirth_SetConsts(driver*), based on driver class
void FUN_80058a60(int param_1)
{

  uint uVar1;
  int iVar2;
  uint uVar3;
  int iVar4;

  // loop counter
  uVar3 = 0;

  // array of structure indexes
  // 0x80088A0C
  iVar4 = -0x7ff775f4;

  // 0x1c * loop counter
  iVar2 = 0;

  // for uVar3 = 0; uVar3 < 0x41 (65); uVar3++
  do {

	// Get the size of the variable
    uVar1 = *(uint *)(iVar4 + 8);

	// If variable size == 2 bytes
    if (uVar1 == 2) {

      // *(2 bytes *) (driver + metaPhys[i]->driverOffset) =
      *(undefined2 *)(param_1 + *(int *)(iVar4 + 4)) =

         // *(2 bytes *) (metaPhys[i]->value[meta[charID].engineID])
        *(undefined2 *)(&DAT_80088a18 + *(int *)(&DAT_80086d90 + (int)(short)(&DAT_80086e84)[*(byte *)(param_1 + 0x4a)] * 0x10) * 4 + iVar2);
    }

    // if variable size != 2 bytes
    else {

      // if variable size < 3 bytes
      if (uVar1 < 3) {


		    // If variable size == 1 byte
        if (uVar1 == 1) {

          // *(1 byte *) (driver + metaPhys[i]->driverOffset) =
          *(undefined *)(param_1 + *(int *)(iVar4 + 4)) =

            // *(byte *) (metaPhys[i]->value[meta[charID].engineID])
            (&DAT_80088a18)[*(int *)(&DAT_80086d90 + (int)(short)(&DAT_80086e84)[*(byte *)(param_1 + 0x4a)] * 0x10) * 4 + iVar2];
        }

		/*
		Sep3
		else
			printf("**error** invalid phys size \'%s\' %ld\n",*puVar3,puVar3[2]);
		*/

      }

      // if variable size >= 3 bytes
      else {

        // if variable size == 4 bytes
        if (uVar1 == 4) {

          // *(4 bytes *) (driver + metaPhys[i]->driverOffset) =
          *(undefined4 *)(param_1 + *(int *)(iVar4 + 4)) =

            // *(4 bytes *) (metaPhys[i]->value[meta[charID].engineID])
            *(undefined4 *) (&DAT_80088a18 + *(int *)(&DAT_80086d90 + (int)(short)(&DAT_80086e84)[*(byte *)(param_1 + 0x4a)] * 0x10) * 4 + iVar2);
        }
      }
    }

	// array of structure indexes += 0x1C
	iVar4 = iVar4 + 0x1c;

	// loop counter
	uVar3 = uVar3 + 1;

	iVar2 = iVar2 + 0x1c;

  } while (uVar3 < 0x41);

  return;
}

// VehBirth_EngineAudio_AllPlayers
void FUN_80058ba4(void)

{
  uint uVar1;
  int iVar2;

  // pointer to first Player thread
  iVar2 = *(int *)(PTR_DAT_8008d2ac + 0x1b2c);

  // while pointer is valid
  while (iVar2 != 0)
  {
	// Player / AI structure + 0x4a shows driver index (0-7)

	// thread -> driver -> driverID
    uVar1 = (uint)*(byte *)(*(int *)(iVar2 + 0x30) + 0x4a);

	// EngineAudio_InitOnce
    FUN_80028880(

		// engineID from metadata, given characterID
		*(int *)(&DAT_80086d90 + (int)(short)(&DAT_80086e84)[uVar1] * 0x10) * 4 + uVar1 &
        0xffff,0x8080);

	// go to next Player in linked list
	iVar2 = *(int *)(iVar2 + 0x10);
  }
  return;
}

// Veh_NullThread
void FUN_80058c44()
{
	return;
}

// VehBirth_TireSprites
void FUN_80058c4c(int param_1)

{
  undefined *puVar1;
  int iVar2;
  int *piVar3;

  puVar1 = PTR_DAT_8008d2ac;

  // thread -> driver object
  piVar3 = *(int **)(param_1 + 0x30);

  // IconGroup* tireAnim
  iVar2 = *(int *)(PTR_DAT_8008d2ac + 0x2114);

  // wheel scale
  *(undefined2 *)(piVar3 + 1) = 0xccc;

  // wheelSprites = tireAnim->icons
  *piVar3 = iVar2 + 0x14;

  if (
		// Player / AI structure + 0x4a shows driver index (0-7)

		// if character ID is oxide
		((&DAT_80086e84)[*(byte *)((int)piVar3 + 0x4a)] == 0xf) &&

		// Level ID != 39
		// Not in Main Menu
		(*(int *)(puVar1 + 0x1a10) != 0x27)
     )
  {
    *(undefined2 *)(piVar3 + 1) = 0;
  }

  piVar3[2] = 0x2e808080;
  *(undefined2 *)(piVar3 + 0xef) = 0xa00;

  // item held to 0xF (nothing)
  *(undefined *)((int)piVar3 + 0x36) = 0xf;

  // related to engine sound
  *(undefined *)((int)piVar3 + 0x47b) = 2;

  *(undefined2 *)((int)piVar3 + 0x362) = 0x1000;
  *(undefined2 *)((int)piVar3 + 0x36a) = 0x1000;
  *(undefined2 *)((int)piVar3 + 0x412) = 0x600;
  *(undefined2 *)((int)piVar3 + 0x3e6) = 10000;

  // VehAfterColl_GetTerrain (air)
  iVar2 = FUN_80057c68(10);
  piVar3[0xd6] = iVar2;

  // get number of lives in battle
  iVar2 = *(int *)(PTR_DAT_8008d2ac + 0x1d80);

  // 0x4e8
  // team in battle mode
  piVar3[0x13a] = (uint)*(byte *)((int)piVar3 + 0x4a);

  *(undefined2 *)(piVar3 + 0x13c) = 0xffff;
  *(undefined2 *)(piVar3 + 0x13d) = 0xffff;

  // 0x4e4
  // player lives in battle mode
  piVar3[0x139] = iVar2;

  return;
}

// VehBirth_NonGhost
// param1 is thread
// param2 is driverID (0-7)
void FUN_80058d2c(int param_1,int param_2)

{
  short sVar1;
  undefined *puVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;

  // model index = DYNAMIC_PLAYER,
  // AI will override this right after
  // the end of the function
  *(undefined2 *)(param_1 + 0x44) = 0x18;

  // unknown thread variables?
  *(undefined2 *)(param_1 + 0x42) = 0x40;
  *(undefined4 *)(param_1 + 0x38) = 0x1000;
  *(undefined2 *)(param_1 + 0x3e) = 0x40;

  // get pointer to game config
  puVar2 = PTR_DAT_8008d2ac;

  // unknown thread variables?
  *(undefined2 *)(param_1 + 0x3c) = 0;
  *(undefined2 *)(param_1 + 0x40) = 0;

  // get object from thread
  iVar5 = *(int *)(param_1 + 0x30);

  // by default, get ID of first character
  sVar1 = DAT_80086e84;

  // if you are not in the main menu
  if ((*(uint *)puVar2 & 0x2000) == 0)
  {
	// get ID of character, given param2
    sVar1 = (&DAT_80086e84)[param_2];
  }

  // VehBirth_GetModelByName
  uVar3 = FUN_80058948((&PTR_s_crash_80086d84)[(int)sVar1 * 4]);

  // INSTANCE_Birth3D -- ptrModel, name, thread
  uVar3 = FUN_8003086c(uVar3,uVar3,param_1);

  // get pointer to game config
  puVar2 = PTR_DAT_8008d2ac;

  // give instance to thread
  *(undefined4 *)(param_1 + 0x34) = uVar3;

  // Ptr Model "Wake"
  iVar4 = *(int *)(puVar2 + 0x226c);

  // if "Wake" exists
  if (iVar4 != 0)
  {
	// INSTANCE_Birth3D -- ptrModel, name, thread
    iVar4 = FUN_8003086c(iVar4,iVar4,0);

	// pointer to "Wake" instance
    *(int *)(iVar5 + 0x4f8) = iVar4;

	// instance flags
	if (iVar4 != 0)
	{
	  // make invisible, set to anim 1
      *(uint *)(iVar4 + 0x28) = *(uint *)(iVar4 + 0x28) | 0x90;
    }

	// sep 3
	// else
    // player %d wake create failed
  }

  /*
  sep 3
  else
  printf("wake not in level\n");
  */

  // get instance from thread
  iVar4 = *(int *)(param_1 + 0x34);

  // if driverID is less than numPlyrCurrGame,
  // "If driver belongs to human player"
  if (param_2 < (int)(uint)(byte)PTR_DAT_8008d2ac[0x1ca8])
  {
	// instance flag
    *(uint *)(iVar4 + 0x28) = *(uint *)(iVar4 + 0x28) | 0x4000000;
  }

  // give driverID to driver
  *(undefined *)(iVar5 + 0x4a) = (char)param_2;

  // give instance to driver
  *(int *)(iVar5 + 0x1c) = iVar4;

  // VehBirth_TireSprites
  FUN_80058c4c(param_1);

  // VehBirth_SetConsts(driver*), based on driver class
  FUN_80058a60(iVar5);

  // if you are in cutscene or in main menu
  if ((*(uint *)PTR_DAT_8008d2ac & 0x20002000) != 0)
  {
	// funcThTick
	// 0x80058c44 is an empty function that does nothing
    *(undefined4 *)(param_1 + 0x2c) = 0x80058c44;

	// make invisible
    *(uint *)(iVar4 + 0x28) = *(uint *)(iVar4 + 0x28) | 0x80;
  }
  return;
}

// VehBirth_Player
struct Driver* FUN_80058ec0(int param_1)

{
  char cVar1;
  int iVar2;
  struct Driver* iVar3;

  // s_player_8008d614
  // "player"

  // PROC_BirthWithObject
  // 0x62c = size
  // 0 = no relation to param4
  // 0x100 flag = LargeStackPool
  // 0 = player thread bucket
  iVar2 = FUN_8004205c(0x62c0100,0,s_player_8008d614,0);

  // Get player pointer from the thread
  iVar3 = *(int *)(iVar2 + 0x30);

  // player Driver is 0x62C bytes large
  memset(iVar3,0,0x62c);

  // VehBirth_NonGhost
  FUN_80058d2c(iVar2,param_1);

  // Get Team that player chose from Battle Setup menu
  cVar1 = PTR_DAT_8008d2ac[param_1 + 0x1da4];

  // VehPhysProc_Driving_Init
  *(undefined4 *)(iVar3 + 0x54) = 0x80062b74;

  // Battle Team that the player is on
  *(int *)(iVar3 + 0x4e8) = (int)cVar1;

  return iVar3;
}


// VehCalc_InterpBySpeed
// param1 is current rotation
// param2 is speed of rotation
// param3 is desired rotation
int FUN_80058f54(int param_1,int param_2,int param_3)

{
  int iVar1;
  int iVar2;

  // if desired rotation is less than current
  if (param_3 < param_1)
  {
	// subtract current by a rate of "speed"
    iVar2 = param_1 - param_2;

	// if new rotation is less than desired
    if (param_1 - param_2 < param_3)
	{
	  // Just use desired rotation
      return param_3;
    }
  }

  // if desired rotation is not less than current
  else
  {
	// make a copy of current
    iVar1 = param_1;
    if (
		// desired <= current,
		// we know desired is not less than current,
		// so this really checks if it is current
		(param_3 <= param_1) ||
		(
			// copy desired
			iVar2 = param_3,

			// add to rotation at rate of "speed"
			iVar1 = param_1 + param_2,

			// if new rotation overshoots desired,
			// probably should say >=
			param_1 + param_2 <= param_3)
		)
	{
	  // if current = desired
	  // if current is overshot past desired

	  // current = desired
      iVar2 = iVar1;
    }
  }

  // return new current
  return iVar2;
}

// VehCalc_MapToRange
// Map value from [oldMin, oldMax] to [newMin, newMax]
// inverting newMin and newMax will give an inverse range mapping
int FUN_80058f9c(int param_1,int param_2,int param_3,int param_4,int param_5)
{
  int iVar1;

  // if value is lessor equal than oldMin, return newMin
  if (param_1 <= param_2) {
    return param_4;
  }

  // if value is less than old Max
  if (param_1 < param_3)
  {

	// distance from old min, multiplied by new range
    iVar1 = (param_1 - param_2) * (param_5 - param_4);

	// get range of first min and max
    param_3 = param_3 - param_2;

	// if min === max, crash
	if (param_3 == 0) {
      trap(0x1c00);
    }

	// if min is less than max, crash
    if ((param_3 == -1) && (iVar1 == -0x80000000)) {
      trap(0x1800);
    }

	// new min, plus [...] / old range
    return param_4 + iVar1 / param_3;
  }

  // return new max
  return param_5;
}


// VehCalc_SteerAccel
undefined4
FUN_8005900c(int param_1,int param_2,int param_3,undefined4 param_4,undefined4 param_5,
            undefined4 param_6)

{
  // Crash Bandicoot:
  // param_2: 0x4	SteerAccel_Stage2_FirstFrame
  // param_3: 0x8	SteerAccel_Stage2_FrameLength
  // param_4: 0x40	SteerAccel_Stage4_FirstFrame
  // param_5: 0x800	SteerAccel_Stage1_MinSteer
  // param_6: 0xC00	SteerAccel_Stage1_MaxSteer
	
  // Steering Stage 1,
  // if first 4 frames of steering
  // increase steer acceleration as time passes
  if (param_1 < param_2) 
  {

	// map "frame" from [0,4] -> [0x800,0xC00]

    // Map value from [oldMin, oldMax] to [newMin, newMax]
    // inverting newMin and newMax will give an inverse range mapping
    param_6 = FUN_80058f9c(param_1, 0,param_2, param_5,param_6);
  }
  
  else 
  {
	// Steering Stage 3
	// frames 12+
	// decrease steer acceleration as time passes
    if (param_2 + param_3 < param_1) 
	{
	  // map "frame" from [12,64] -> [0xC00,0]

      // Map value from [oldMin, oldMax] to [newMin, newMax]
      // inverting newMin and newMax will give an inverse range mapping
      param_6 = FUN_80058f9c(param_1, param_2 + param_3,param_4, param_6,0);
    }
  }
  
  // Steering Stage 2,
  // next 0x8 frames (frame 4 to 12)
  // max steer accel of 0xC00
  return param_6;
  
  // Steering Stage 4,
  // part of Stage 3's mapping,
  // for all steering after frame 64,
  // steer acceleration is zero, so 
  // angular velocity is constant
}


// if you're interested in learning about the algorithm:
// https://en.wikipedia.org/wiki/Integer_square_root#Digit-by-digit_algorithm

// f(n, i) = sqrt(n<<i)
// VehCalc_FastSqrt(n, i)
uint FUN_80059070(uint param_1,uint param_2)
/*
  f(n, 0) will always output the sqrt(n)

  the idea for this function is to first computer the length of the square root in numbers of bits,
  and then test each bit and see if it belongs to the square root. if so, keep the bit, otherwise discard.
*/


{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;

  // result
  uVar5 = 0;

  // uVar4 = x + 1
  uVar4 = 1;

  // last_approximation = 0
  uVar6 = 0;

  uVar3 = 1 << (param_2 & 0x1f);

  /* what this is doing is picking the least x that 4^x >= n
    notice that:
      4^x = n
      log_4(n) = x
      log_2(n) / log_2(4) = x
      log_2(n) / 2 = x
      x = log_2(sqrt(n))

      in order words, x is the length in bits of the square root of n
  */
  while ((uVar3 < param_1 && (uVar3 << 2 != 0))) {
    uVar4 = uVar4 + 1;
    uVar3 = uVar3 << 2;
  }

  uVar1 = 1 << (uVar4 + (param_2 - 1) & 0x1f);

  // while 4^x != 0
  while (uVar3 != 0) {

    // current_approximation = result << x + 1
    uVar2 = uVar5 << (uVar4 & 0x1f);

    if ((int)uVar4 < 0) {
      uVar2 = uVar5 >> (-uVar4 & 0x1f);
    }

    // current_approximation = (result << x + 1) + last_approximation + current_bit_squared
    uVar2 = uVar2 + uVar6 + uVar3;

    // if current_approximation <= n
    if (uVar2 <= param_1) {

      // result += current_bit
      uVar5 = uVar5 + uVar1;

      // last_approximation = current_approximation
      uVar6 = uVar2;
    }

    // current_bit /= 2
    uVar1 = uVar1 >> 1;

    // current_bit_squared /= 4
    uVar3 = uVar3 >> 2;

    // (x + 1) -= 1
    uVar4 = uVar4 - 1;
  }
  return uVar5;
}


// VehEmitter_Exhaust
int FUN_80059100(int param_1,int *param_2,int *param_3)

{
  int iVar1;
  undefined *puVar2;
  int iVar3;

  if (
		// if driver is not using invisibility powerup
		(*(int *)(param_1 + 0x28) == 0) &&

		// if driver -> instSelf -> instFlags & INVISIBLE is false
		((*(uint *)(*(int *)(param_1 + 0x1c) + 0x28) & 0x80) == 0)
	 )
  {
	// If you're in 1P mode
	// high LOD exhaust
    puVar2 = (undefined *)0x80089224;

	// if numPlyrCurrGame is less than 3
    if ((byte)PTR_DAT_8008d2ac[0x1ca8] < 3) {

	  // if numPlyrCurrGame is more than 1
      if (1 < (byte)PTR_DAT_8008d2ac[0x1ca8]) {

		// really only happens if numPlyrCurrGame is 2
		// med LOD exhaust
        puVar2 = (undefined *)0x80089344;
      }
    }

	// if numPlyrCurrGame is 3 or 4
    else
	{
	  // low LOD exhaust
      puVar2 = &DAT_80089464;
    }

	// driver -> instance -> thread -> modelIndex == "robotcar" of any kind
    if (*(short *)(*(int *)(*(int *)(param_1 + 0x1c) + 0x6c) + 0x44) == 0x3f)
	{
	  // low LOD exhaust
      puVar2 = &DAT_80089464;
    }
    iVar3 = 1;

	// driver -> instance -> flags
    if (((*(uint *)(*(int *)(param_1 + 0x1c) + 0x28) & 0x2000) != 0) &&
       ((param_2[1] - param_3[1]) + *(int *)(param_1 + 0x2d8) < 0x100))
	{
      iVar3 = 7;

	  // exhaust when you're underwater,
	  // which makes bubbles comes out
      puVar2 = &DAT_80089128;
    }

	// Create instance in particle pool
    iVar1 = FUN_80040308(0,*(undefined4 *)(PTR_DAT_8008d2ac + iVar3 * 4 + 0x2114),puVar2);

	// if particle exists
    if (iVar1 != 0)
	{
	  // posX
      *(int *)(iVar1 + 0x24) = *(int *)(iVar1 + 0x24) + (*param_2 - *param_3);

	  // velX
	  *(undefined2 *)(iVar1 + 0x28) = *(undefined2 *)param_3;

	  // posY
	  *(int *)(iVar1 + 0x2c) = *(int *)(iVar1 + 0x2c) + (param_2[1] - param_3[1]);

	  // velY
	  *(undefined2 *)(iVar1 + 0x30) = *(undefined2 *)(param_3 + 1);

	  // posZ
      *(int *)(iVar1 + 0x34) = *(int *)(iVar1 + 0x34) + (param_2[2] - param_3[2]);

	  // velZ
	  *(undefined2 *)(iVar1 + 0x38) = *(undefined2 *)(param_3 + 2);

	  *(undefined *)(iVar1 + 0x18) = *(undefined *)(*(int *)(param_1 + 0x1c) + 0x50);

	  // driver->instSelf
      *(undefined4 *)(iVar1 + 0x20) = *(undefined4 *)(param_1 + 0x1c);

	  if (iVar3 == 7)
	  {
		// Particle_FuncPtr_ExhaustUnderwater
        *(undefined4 *)(iVar1 + 0x1c) = 0x8003ee20;
      }

	  // if engine revving
	  if (*(char *)(param_1 + 0x376) == '\x04')
	  {
        if (*(char *)(param_1 + 0x4fe) != '\x01') {
          return iVar1;
        }
      }

	  // if not engine revving
	  else {
        if ((int)*(short *)(param_1 + 0x3dc) < 0x81) {
          return iVar1;
        }
        if ((int)(((uint)*(byte *)(param_1 + 0x477) + 2) * 0x20) < (int)*(short *)(param_1 + 0x3dc))
        {
          return iVar1;
        }
      }
      *(ushort *)(iVar1 + 0x12) = *(ushort *)(iVar1 + 0x12) & 0xff9f | 0x40;
    }
  }
  else {
    iVar1 = 0;
  }
  return iVar1;
}


// VehEmitter_Sparks_Ground
void FUN_80059344(int param_1,undefined4 param_2)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  undefined4 uVar10;
  int iVar11;
  int iVar12;
  int iVar13;

  gte_ldVXY0(0);
  gte_ldVZ0(0xffffe800);
  gte_rtv0();
  iVar4 = gte_stMAC1();
  iVar5 = gte_stMAC2();
  iVar6 = gte_stMAC3();
  
  gte_ldVXY0(0x1800);
  gte_ldVZ0(0);
  gte_rtv0();
  read_mt(iVar13,iVar12,iVar11);
  
  gte_ldVXY0(0);
  gte_ldVZ0(0xfffffe00);
  gte_rtv0();
  read_mt(uVar10,uVar9,uVar8);
  
  iVar7 = 10;
  do
  {
	// Create instance in particle pool
    iVar1 = FUN_80040308(0,*(undefined4 *)(PTR_DAT_8008d2ac + 0x2114),param_2);

    if (iVar1 != 0)
	{
	  // RNG
      uVar2 = FUN_8006c684(PTR_DAT_8008d2ac + 0x252c);
      uVar3 = uVar2 & 0x7ff;
      if ((uVar2 & 1) != 0) {
        uVar3 = -uVar3;
      }

	  // velocity variables
      *(short *)(iVar1 + 0x28) =
           *(short *)(iVar1 + 0x28) + (short)uVar10 + (short)((int)(uVar3 * iVar13) >> 0xc);
      *(short *)(iVar1 + 0x30) =
           *(short *)(iVar1 + 0x30) + (short)uVar9 + (short)((int)(uVar3 * iVar12) >> 0xc);
      *(short *)(iVar1 + 0x38) =
           *(short *)(iVar1 + 0x38) + (short)uVar8 + (short)((int)(uVar3 * iVar11) >> 0xc);

	  // position variables
	  *(int *)(iVar1 + 0x24) = *(int *)(iVar1 + 0x24) + iVar4 + *(short *)(iVar1 + 0x28);
      *(int *)(iVar1 + 0x2c) = *(int *)(iVar1 + 0x2c) + iVar5 + *(short *)(iVar1 + 0x30);
      *(int *)(iVar1 + 0x34) = *(int *)(iVar1 + 0x34) + iVar6 + *(short *)(iVar1 + 0x38);

	  // driver -> instSelf
      *(undefined4 *)(iVar1 + 0x20) = *(undefined4 *)(param_1 + 0x1c);

	  *(undefined *)(iVar1 + 0x18) = *(undefined *)(*(int *)(param_1 + 0x1c) + 0x50);
    }
    iVar7 = iVar7 + -1;
  } while (iVar7 != 0);
  return;
}


// VehEmitter_Terrain_Ground
void FUN_80059558(int param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  int unaff_s0;
  int unaff_s1;
  int unaff_s2;
  
  if (
		// touching quadblock
		((*(uint *)(param_1 + 0x2c8) & 1) != 0) && 
		
		// not in accel prevention (not holding square)
		((*(uint *)(param_1 + 0x2c8) & 8) == 0)
	 ) 
  {
	// abs fireSpeed
    iVar1 = (int)*(short *)(param_1 + 0x39e);
    if (iVar1 < 0) {
      iVar1 = -iVar1;
    }
	
    if (iVar1 < 0x300) 
	{
	  // abs speedApprox
      iVar1 = (int)*(short *)(param_1 + 0x38e);
      if (iVar1 < 0) {
         iVar1 = -iVar1;
      }
	  
      if (iVar1 < 0x300) {
         return;
      }
    }
	
	// if moving quickly
	
	// 2 wheels spawn particles
    iVar1 = 2;
	
	// if sliding
    if (*(char *)(param_1 + 0x376) == '\x02') 
	{
	  // 4 wheels spawn particles
      iVar1 = 4;
    }
	
	// spawn particles on wheels
    for (; iVar1 != 0; iVar1 = iVar1 + -1) 
	{
	  // front tire
      if (iVar1 == 3) 
	  {
		 // 0x1E, 0xA, 0x28
         gte_ldVXY0(0xa001e);
         uVar3 = 0x28;
         gte_ldVZ0(0x28);
      }
	  
	  // back wheels
      else if (iVar1 < 4) {
         if (iVar1 == 2) 
		 {
		   // -0x1E, 0xA, -0x28
           gte_ldVXY0(0xaffe2);
           uVar3 = 0xffffffec;
           gte_ldVZ0(0xffffffec);
         }
         else 
		 {
LAB_80059674:
		   // 0x1E, 0xA, -0x28
           gte_ldVXY0(0xa001e);
           uVar3 = 0xffffffec;
           gte_ldVZ0(0xffffffec);
         }
      }
      
	  // == 4, (front tire)
	  else 
	  {
         if (iVar1 != 4) goto LAB_80059674;
         
		 // -0x1E, 0xA, 0x28
		 gte_ldVXY0(0xaffe2);
         uVar3 = 0x28;
         gte_ldVZ0(0x28);
      }
      gte_rtv0();
      read_mt(unaff_s0,unaff_s1,unaff_s2);
	  
	  // spawn particle
      iVar2 = FUN_80040308(0,*(undefined4 *)(PTR_DAT_8008d2ac + 0x2114),param_2,uVar3);
      
	  if (iVar2 != 0) 
	  {
		 // edit positions
         *(int *)(iVar2 + 0x24) = *(int *)(iVar2 + 0x24) + unaff_s0 * 0x100;
         *(int *)(iVar2 + 0x2c) = *(int *)(iVar2 + 0x2c) + unaff_s1 * 0x100;
         *(int *)(iVar2 + 0x34) = *(int *)(iVar2 + 0x34) + unaff_s2 * 0x100;
         
		 gte_ldVXY0(CONCAT22(*(undefined2 *)(iVar2 + 0x30),*(undefined2 *)(iVar2 + 0x28)));
         gte_ldVZ0((uint)*(ushort *)(iVar2 + 0x38));
         gte_rtv0();
         read_mt(unaff_s0,unaff_s1,unaff_s2);
         
		 // edit velocity
		 *(short *)(iVar2 + 0x28) = (short)unaff_s0;
         *(short *)(iVar2 + 0x30) = (short)unaff_s1;
         *(short *)(iVar2 + 0x38) = (short)unaff_s2;
		 
		// driver -> instSelf
         *(undefined4 *)(iVar2 + 0x20) = *(undefined4 *)(param_1 + 0x1c);
		 
         *(undefined *)(iVar2 + 0x18) = *(undefined *)(*(int *)(param_1 + 0x1c) + 0x50);
      }
    }
  }
  return;
}

// VehEmitter_Sparks_Wall
// param_1 is driver struct
// param_2 is always 0x800896c8, particle data for sparks
void FUN_80059780(int param_1,undefined4 param_2)
{
  int iVar1;
  int iVar2;
  uint uVar3;
  uint unaff_s1;
  uint unaff_s2;
  uint unaff_s3;
  
  // no fire speed
  if (*(short *)(param_1 + 0x39e) == 0) 
  {
    iVar1 = (int)*(short *)(param_1 + 0x38e);
    if (iVar1 < 0) {
      iVar1 = -iVar1;
    }
    if (0x200 < iVar1) goto LAB_800597d0;
  }
  
  // fire speed
  else 
  {
LAB_800597d0:

	// if time against wall is less than 15 seconds
    if (*(short *)(param_1 + 0x50) < 0x1c2) 
	{
	  // GAMEPAD_ShockFreq and GAMEPAD_ShockForce1
      FUN_80026440(param_1, 8, 0);
      FUN_800264c0(param_1, 8, 0x7f);
	  
	  // increment time against wall
      *(short *)(param_1 + 0x50) = *(short *)(param_1 + 0x50) + 1;
      goto LAB_80059818;
    }
  }
  
  // reset time against wall to zero
  *(undefined2 *)(param_1 + 0x50) = 0;
  uVar3 = param_2;
  
LAB_80059818:
  
  if (*(short *)(param_1 + 0x38e) < 0x201) {
    if (-0x201 < *(short *)(param_1 + 0x38e)) {
      return;
    }
	
	// -0x2200, 0xa00, -0x1400
    gte_ldVXY0(0xa00de00);
    gte_ldVZ0(0xffffec00);
	
	// 0x2200, 0xa00, -0x1400
    gte_ldVXY1(0xa002200);
    gte_ldVZ1(0xffffec00);
  }
  
  else 
  {
	// -0x2200, 0xa00, 0x2800
    gte_ldVXY0(0xa00de00);
    gte_ldVZ0(0x2800);
	
	// 0x2200, 0xa00, 0x2800
    gte_ldVXY1(0xa002200);
    gte_ldVZ1(0x2800);
  }
  
  gte_rtv0();
  read_mt(unaff_s1,unaff_s2,unaff_s3);
  gte_rtv1();
  read_mt(uVar3,newVar1,newVar2);
  
  // matrix
  gte_ldL11L12(unaff_s1 & 0xffff | unaff_s2 << 0x10);
  gte_ldL13L21(unaff_s3 & 0xffff | uVar3 << 0x10);
  gte_ldL22L23(newVar1 & 0xffff | newVar2 << 0x10);
  
  // driver->posWallColl - driver->posCurr
  gte_ldVXY0(*(short *)(param_1 + 900) * 0x100 - *(int *)(param_1 + 0x2d4) & 0xffffU |
              (*(short *)(param_1 + 0x386) * 0x100 - *(int *)(param_1 + 0x2d8)) * 0x10000);
  gte_ldVZ0(*(short *)(param_1 + 0x388) * 0x100 - *(int *)(param_1 + 0x2dc));
  
  gte_llv0();
  
  iVar1 = gte_stMAC1();
  iVar2 = gte_stMAC2();
  if (iVar1 < iVar2) {
    unaff_s1 = uVar3;
    unaff_s2 = newVar1;
    unaff_s3 = newVar2;
  }
  
  // Create instance in particle pool
  iVar1 = FUN_80040308(0,*(undefined4 *)(PTR_DAT_8008d2ac + 0x2114),param_2);
  if (iVar1 != 0) 
  {
	// position variables
    *(uint *)(iVar1 + 0x24) = *(int *)(iVar1 + 0x24) + unaff_s1;
    *(uint *)(iVar1 + 0x34) = *(int *)(iVar1 + 0x34) + unaff_s3;
    *(uint *)(iVar1 + 0x2c) = *(int *)(iVar1 + 0x2c) + unaff_s2;
    
	gte_ldVXY0(CONCAT22(*(undefined2 *)(iVar1 + 0x30),*(undefined2 *)(iVar1 + 0x28)));
    gte_ldVZ0((uint)*(ushort *)(iVar1 + 0x38));
    gte_rtv0();
    read_mt(unaff_s1,unaff_s2,unaff_s3);
    
	// edit velocity
	*(short *)(iVar1 + 0x28) = (short)unaff_s1;
    *(short *)(iVar1 + 0x30) = (short)unaff_s2;
    *(short *)(iVar1 + 0x38) = (short)unaff_s3;
    
	// driver -> instSelf
	*(undefined4 *)(iVar1 + 0x20) = *(undefined4 *)(param_1 + 0x1c);
  }
  return;
}

// VehEmitter_DriverMain (calls all other SpawnParticle functions)
void FUN_80059a18(int param_1,int param_2,undefined *param_3,uint param_4)

{
  byte bVar1;
  short sVar2;
  short sVar3;
  short sVar4;
  short sVar5;
  short sVar6;
  short sVar7;
  ushort uVar8;
  int iVar9;
  MATRIX *pMVar10;
  int iVar11;
  undefined *puVar12;
  uint uVar13;
  undefined4 uVar14;
  undefined2 uVar15;
  undefined4 in_t1;
  int iVar16;
  int iVar17;
  VECTOR *r0;
  int iVar18;
  undefined4 uVar19;
  int iVar20;
  undefined *puVar21;
  int iVar22;
  int iVar23;
  int iVar24;
  char cVar25;
  byte bVar26;
  int iVar27;
  undefined *puVar28;
  undefined8 uVar29;
  undefined auStack_68 [16];
  undefined4 local_58;
  uint local_30;
  
  puVar28 = auStack_68;
  
  // driver -> terrain meta
  iVar22 = *(int *)(param_2 + 0x358);
  
  // get instance from thread
  iVar27 = *(int *)(param_1 + 0x34);
  
  // backup previous frame's skidmark flags, in the upper bits of itself
  *(uint *)(param_2 + 0x2c4) = (*(uint *)(param_2 + 0x2c4) & 0xfffff) << 4;
  
  // next slot (8-frame cycle)
  *(byte *)(param_2 + 0xc3) = *(char *)(param_2 + 0xc3) - 1U & 7;
  
  // terrain variables
  local_30 = *(uint *)(iVar22 + 4);
  iVar23 = (int)*(short *)(iVar22 + 0x30);
  
  // thread -> modelIndex == "player" of any kind
  if (*(short *)(param_1 + 0x44) == 0x18) 
  {
    iVar18 = -1;
    
    //if racer is on the ground and (?)
	if (((*(uint *)(param_2 + 0x2c8) & 1) != 0) && ((*(uint *)(iVar22 + 4) & 0x20) == 0)) {
      iVar18 = (int)*(short *)(iVar22 + 0x32);
    }
	
	// absolute value speedApprox
    iVar11 = (int)*(short *)(param_2 + 0x38e);
    if (iVar11 < 0) {
      iVar11 = -iVar11;
    }
    
	// volume
    // Map value from [minSpeed, maxSpeed] to [minVol, maxVol]
	iVar9 = FUN_80058f9c(iVar11,0,5000,0,200);
	
	// absolute value speedApprox
    iVar11 = (int)*(short *)(param_2 + 0x38e);
    if (iVar11 < 0) {
      iVar11 = -iVar11;
    }
    
	// distortion
    // Map value from [minSpeed, maxSpeed] to [minDistort, maxDistort]
	iVar11 = FUN_80058f9c(iVar11,0,12000,0x6c,0xd2);
	uVar13 = iVar11 << 8;

	// if echo is required
	if ((*(uint *)(param_2 + 0x2c8) & 0x10000) != 0) 
	{
	  // add echo
      uVar13 = uVar13 | 0x1000000;
    }
    
	// driver audio
	FUN_8002e690(param_2 + 0x304,iVar18,
	
		// volume
		iVar9 << 0x10 | 
		
		// distortion
		uVar13 | 
		
		// L/R
		0x80);
	
	// If this is human and not an AI
    if ((*(uint *)(param_2 + 0x2c8) & 0x100000) == 0) 
	{
	  // absolute value speedApprox
      iVar18 = (int)*(short *)(param_2 + 0x38e);
      if (iVar18 < 0) {
         iVar18 = -iVar18;
      }
	  
	  // if speed high enough
      if (0x200 < iVar18) 
	  {
		// GAMEPAD_ShockFreq and GAMEPAD_ShockForce2
        FUN_80026440(param_2,(uint)*(byte *)(iVar22 + 0x2c),(uint)*(byte *)(iVar22 + 0x2d));
        FUN_80026540(param_2,(uint)*(byte *)(iVar22 + 0x2e),(uint)*(byte *)(iVar22 + 0x2f));
      }
      
      //if racer started touching the ground in this frame
	  if ((*(uint *)(param_2 + 0x2c8) & 2) != 0) 
	  {
		// jumpHeightPrev
        iVar18 = (int)*(short *)(param_2 + 0x392);
        if (iVar18 < 0) {
          iVar18 = -iVar18;
        }
        
		// jumpHeightPrev
		if (0x1600 < iVar18) 
		{
		  // GAMEPAD_ShockForce1
          FUN_800264c0(param_2,3,0xFF);
        }
      }
    }
  }
  
  // if numPlyrCurrGame is less than 2
  if ((byte)PTR_DAT_8008d2ac[0x1ca8] < 2) 
  {
	// absolute value
    iVar18 = (int)*(short *)(param_2 + 0x38c);
    if (iVar18 < 0) {
      iVar18 = -iVar18;
    }
	
    if (
			// high speed
			(0x500 < iVar18) && 
			
			// current terrain
			(*(char *)(param_2 + 0xc2) == '\x0e')
		) 
	{
	  // number of particles
	  iVar20 = 10;

	  //if racer didn't start touching the ground in this frame
      if ((*(uint *)(param_2 + 0x2c8) & 2) == 0)
	  {
		// Create instance in particle pool (land jump in mud)
        iVar18 = FUN_80040308(0,*(undefined4 *)(PTR_DAT_8008d2ac + 0x2148),&DAT_8008980c);

		if (iVar18 != 0) {
          *(undefined *)(iVar18 + 0x18) = *(undefined *)(*(int *)(param_2 + 0x1c) + 0x50);

		  // driver -> instSelf
          *(undefined4 *)(iVar18 + 0x20) = *(undefined4 *)(param_2 + 0x1c);

		  // driverID
          uVar1 = *(undefined *)(param_2 + 0x4a);

          *(int *)(iVar18 + 0x24) = *(int *)(iVar18 + 0x24) + (int)*(short *)(iVar18 + 0x28) * 0x10;

		  // driverID
		  *(undefined *)(iVar18 + 0x19) = uVar1;

          *(int *)(iVar18 + 0x34) = *(int *)(iVar18 + 0x34) + (int)*(short *)(iVar18 + 0x38) * 0x10;
          *(short *)(iVar18 + 0x2a) = *(short *)(iVar18 + 0x2a) - (*(short *)(iVar18 + 0x28) >> 4);
          *(short *)(iVar18 + 0x3a) = *(short *)(iVar18 + 0x3a) - (*(short *)(iVar18 + 0x38) >> 4);
        }
      }

      else
	  {
        do
		{
		  // Create instance in particle pool (mud)
          iVar15 = FUN_80040308(0,*(undefined4 *)(PTR_DAT_8008d2ac + 0x2148),&DAT_8008980c);
          if (iVar15 != 0) {
            *(undefined *)(iVar15 + 0x18) = *(undefined *)(*(int *)(param_2 + 0x1c) + 0x50);

			// driver -> instSelf
            *(undefined4 *)(iVar15 + 0x20) = *(undefined4 *)(param_2 + 0x1c);

			// driverID
            uVar1 = *(undefined *)(param_2 + 0x4a);
            *(undefined *)(iVar15 + 0x19) = uVar1;
			
            *(int *)(iVar15 + 0x24) = *(int *)(iVar15 + 0x24) + (int)*(short *)(iVar15 + 0x28) * 0x10;
            *(int *)(iVar15 + 0x34) = *(int *)(iVar15 + 0x34) + (int)*(short *)(iVar15 + 0x38) * 0x10;
            *(short *)(iVar15 + 0x2a) = *(short *)(iVar15 + 0x2a) - (*(short *)(iVar15 + 0x28) >> 4);
            *(short *)(iVar15 + 0x3a) = *(short *)(iVar15 + 0x3a) - (*(short *)(iVar15 + 0x38) >> 4);
          }

		  // loop count
          iVar18 = iVar18 + -1;

        } while (iVar18 != 0);
      }
    }
	
	// if numPlyrCurrGame is less than 2 (useless if?)
    if ((byte)PTR_DAT_8008d2ac[0x1ca8] < 2) 
	{ 
      //if racer started touching the ground in this frame
	  if (((local_30 & 0x40) != 0) && ((*(uint *)(param_2 + 0x2c8) & 2) != 0))
      {
		 // absolute value speedApprox
         iVar18 = (int)*(short *)(param_2 + 0x38e);
         if (iVar18 < 0) {
           iVar18 = -iVar18;
         }
		 
		 // if speed is high enough
         if (0x600 < iVar18) 
		 {
		   // absolute value
           iVar18 = (int)*(short *)(param_2 + 0x392);
           if (iVar18 < 0) {
             iVar18 = -iVar18;
           }
		   
           if (0x1600 < iVar18) 
		   {
			 // instance -> matrix
             pMVar10 = (MATRIX *)(iVar27 + 0x30);
             gte_SetRotMatrix(pMVar10);
             gte_SetTransMatrix(pMVar10);
			 
			 // VehEmitter_Sparks_Ground
             FUN_80059344(param_2,&DAT_80089584);
           }
         }
      }
	  
	  // if terrain  has particle data
      if (*(int *)(iVar22 + 0x18) != 0) 
	  {
		 // instance -> matrix
		 pMVar10 = (MATRIX *)(iVar27 + 0x30);
         gte_SetRotMatrix(pMVar10);
         gte_SetTransMatrix(pMVar10);
		 
		 // particles even frame
         iVar18 = *(int *)(iVar22 + 0x1c);
		 
		 // if data is invalid, or odd-number frame
         if ((iVar18 == 0) || ((*(uint *)(PTR_DAT_8008d2ac + 0x1cec) & 1) == 0)) 
		 {
		   // particles odd frame
           iVar18 = *(int *)(iVar22 + 0x18);
         }
		 
		 // VehEmitter_Terrain_Ground
         FUN_80059558(param_2,iVar18);
      }
	  
      if (
			// if wall rubbing right now
			(*(short *)(param_2 + 0x3fe) == 0xf0) &&
			
			// if you are not being mask grabbed
			(*(char *)(param_2 + 0x376) != '\x05')
		 ) 
	  {
		 // instance -> matrix
		 pMVar10 = (MATRIX *)(iVar27 + 0x30)
		 gte_SetRotMatrix(pMVar10);
         gte_SetTransMatrix(pMVar10);
		 
		 // VehEmitter_Sparks_Wall
         FUN_80059780(param_2,&DAT_800896c8);
		 
         uVar19 = 0x14;
         
		 // increase engine volume
		 sVar7 = *(short *)(param_2 + 0x496) + 0x14;
         *(short *)(param_2 + 0x496) = sVar7;
         
		 // max engine volume
		 if (0xff < sVar7) {
           *(undefined2 *)(param_2 + 0x496) = 0xff;
         }
      }
	  
	  // if being mask grabbed
      else 
	  {
         if (*(short *)(param_2 + 0x3fe) == 0) 
		 {
		   // reset time against wall
           *(undefined2 *)(param_2 + 0x50) = 0;
         }
		 
		 // decrease engine volume
         uVar8 = *(short *)(param_2 + 0x496) - 0x14;
         *(ushort *)(param_2 + 0x496) = uVar8;
         
		 // minimum engine volume
		 if ((int)((uint)uVar8 << 0x10) < 0) {
           *(undefined2 *)(param_2 + 0x496) = 0;
         }
		 
         uVar19 = 0x14;
         if (*(short *)(param_2 + 0x496) == 0) {
           uVar19 = 0xffffffff;
         }
      }
	  
	  // thread -> modelIndex == "player" of any kind
      if (*(short *)(*(int *)(param_1 + 0x68) + 0x44) == 0x18) 
	  {
		 // volume
         uVar13 = (int)*(short *)(param_2 + 0x496) << 0x10;
         
		 // if echo is not requierd
		 if ((*(uint *)(param_2 + 0x2c8) & 0x10000) == 0) 
		 {
		   // volume, distortion, left/right
           param_3 = (undefined *)(uVar13 | 0x8080);
         }
		 
		 // if echo
         else 
		 {
		   // add echo, volume, distortion, left/right
           param_3 = (undefined *)(uVar13 | 0x1008080);
         }
		 
		 // driver audio
         FUN_8002e690(param_2 + 0x308,uVar19);
      }
    }
  }
  
  if ((local_30 & 8) != 0) 
  {
	// skid with front wheels, and back wheels
    *(uint *)(param_2 + 0x2c8) = *(uint *)(param_2 + 0x2c8) | 0x1800;
  }
  
  // matrixArr
  bVar26 = *(byte *)(param_2 + 0x4c);
  
  // matArr02 (wheelie)
  if (bVar26 == 1) 
  {
	// back wheel skid
    *(uint *)(param_2 + 0x2c8) = *(uint *)(param_2 + 0x2c8) | 0x800;
LAB_8005a094:

	// no front wheel skid
    *(uint *)(param_2 + 0x2c8) = *(uint *)(param_2 + 0x2c8) & 0xffffefff;
  }
  
  // if wheelie of any kind
  else if ((bVar26 != 0) && (bVar26 < 4)) goto LAB_8005a094;
  
  //if racer is not on the ground, not leaving skid marks on front or back tires
  if (((*(uint *)(param_2 + 0x2c8) & 1) == 0) || ((*(uint *)(param_2 + 0x2c8) & 0x1800) == 0)) 
  {
LAB_8005a73c:
    
	// if driver sound exists
	puVar12 = *(undefined **)(param_2 + 0x300);
    if (puVar12 != (undefined *)0x0) 
	{
	  // OtherFX_Stop1
      FUN_80028808();
	  
	  // erase sound
      *(undefined4 *)(param_2 + 0x300) = 0;
    }
  }
  
  // if driver is on ground, and leaving skidmarks (or drift)
  else 
  {
	// absolute value speedApprox
    iVar22 = (int)*(short *)(param_2 + 0x38e);
    if (iVar22 < 0) {
      iVar22 = -iVar22;
    }
	
	// if speed is low
    if (iVar22 < 0x201) goto LAB_8005a73c;
    
	// if speed is high
	
	bVar26 = 0;
	
	// thread -> modelIndex == "player" of any kind
    if (*(short *)(param_1 + 0x44) == 0x18) 
	{
	  // absolute value
      iVar18 = (int)*(char *)(param_2 + 0x4b);
      if (iVar18 < 0) {
         iVar18 = -iVar18;
      }

      // Map value from [oldMin, oldMax] to [newMin, newMax]
      // inverting newMin and newMax will give an inverse range mapping
      iVar11 = FUN_80058f9c(iVar22,2000,12000,0x14,0xaa);
      
	  // absolute value speedApprox
	  iVar22 = (int)*(short *)(param_2 + 0x38e);
      if (iVar22 < 0) {
         iVar22 = -iVar22;
      }
      
      // Map value from [oldMin, oldMax] to [newMin, newMax]
      // inverting newMin and newMax will give an inverse range mapping
	  iVar22 = FUN_80058f9c(iVar22,2000,12000,0x92,0x78);
      
	  // or you are sliding
	  if (*(char *)(param_2 + 0x376) == '\x02') {
         iVar9 = (int)*(short *)(param_2 + 0x3d4);
         if (iVar9 < 0) {
           iVar9 = -iVar9;
         }
         iVar22 = iVar22 - iVar9;
         if (iVar22 < 0) {
           iVar22 = 0;
         }
      }
      iVar22 = iVar22 + iVar18;
      if (0x92 < iVar22) {
         iVar22 = 0x92;
      }
      
	  // distortion
	  uVar13 = iVar22 << 8;
      
	  // if echo is required
	  if ((*(uint *)(param_2 + 0x2c8) & 0x10000) != 0) 
	  {
		 // add echo
         uVar13 = uVar13 | 0x1000000;
      }
	  
	  // driver audio
	  FUN_8002e690(

			// driver audio
			param_2 + 0x300,

			(int)iVar23,

			// volume
			(iVar11 + (iVar18 >> 1)) * 0x10000 |

			// echo + distort
			uVar13 |

			// L/R with no safeguard
			0x80U - ((int)((uint)*(byte *)(param_2 + 0x4b) << 0x18) >> 0x1a));
	  
	  
    }
    if ((*(uint *)(iVar27 + 0x28) & 0x2000) == 0) {
      cVar25 = *(char *)(iVar27 + 0x50);
    }
    else {
      cVar25 = *(char *)(iVar27 + 0x51);
    }
    cVar25 = cVar25 + '\x02';
	
	// Cosine(angle)
    FUN_8003d1c0((int)*(short *)(param_2 + 0x396));
	
	// Sine(angle)
    iVar22 = FUN_8003d184((int)*(short *)(param_2 + 0x396));
    iVar22 = iVar22 * 0xf;
	
	// Cosine(angle)
    iVar23 = FUN_8003d1c0((int)*(short *)(param_2 + 0x396));
	
	// Sine(angle)
    FUN_8003d184((int)*(short *)(param_2 + 0x396));
	
	// Cosine(angle)
    iVar18 = FUN_8003d1c0((int)*(short *)(param_2 + 0x396));
	
	// Sine(angle)
    FUN_8003d184((int)*(short *)(param_2 + 0x396));
    iVar23 = iVar23 * 0xf;
    iVar17 = iVar18 * 10 >> 0xc;
	
	// Cosine(angle)
    FUN_8003d1c0((int)*(short *)(param_2 + 0x396));
    puVar12 = (undefined *)(int)*(short *)(param_2 + 0x396);
    iVar24 = iVar23 >> 0xc;
	
	// Sine(angle)
    iVar18 = FUN_8003d184();
    iVar20 = iVar22 >> 0xc;
    iVar16 = iVar18 * -10 >> 0xc;
	
	// instance -> matrix
    pMVar10 = (MATRIX *)(iVar27 + 0x30);
    gte_SetRotMatrix(pMVar10);
    gte_SetTransMatrix(pMVar10);
	
    iVar11 = iVar20 >> 1;
    iVar18 = iVar24 >> 1;
    uVar15 = (undefined2)in_t1;
    iVar9 = iVar17 >> 1;
    sVar5 = (short)iVar9;
    sVar7 = (short)iVar17;
    sVar3 = (short)iVar16;
    sVar4 = (short)(iVar16 >> 1);
	
    // back wheel skids
    if ((*(uint *)(param_2 + 0x2c8) & 0x800) != 0) 
	{
	  // enable skidmarks for first tire
      *(uint *)(param_2 + 0x2c4) = *(uint *)(param_2 + 0x2c4) | 1;
	  
      gte_ldVXY0(0xffe2);
      gte_ldVZ0(0xffffffec);
      gte_rt();
      read_mt(param_3,in_t1,param_4);
      
	  iVar16 = (int)param_3 - (iVar22 >> 0xd);
      
	  // skidmark index (0-7)
	  bVar1 = *(byte *)(param_2 + 0xc3);
	  
      iVar23 = param_4 - (iVar23 >> 0xd);
      iVar22 = param_2 + (uint)bVar1 * 0x40;
      sVar6 = (short)iVar16;
      
	  // store to skidmark buffer
	  *(short *)(iVar22 + 0xc4) = sVar6 + sVar7;
	  
      sVar2 = (short)iVar23;
      *(short *)(iVar22 + 200) = sVar2 + sVar3;
      *(short *)(iVar22 + 0xcc) = sVar6 - sVar7;
      *(undefined2 *)(iVar22 + 0xc6) = uVar15;
      *(undefined2 *)(iVar22 + 0xce) = uVar15;
      *(short *)(iVar22 + 0xd0) = sVar2 - sVar3;
      *(char *)(iVar22 + 0xca) = cVar25;
      
	  if ((local_30 & 8) == 0) {
         *(byte *)(iVar22 + 0xcb) = bVar26;
      }
      else {
         *(byte *)(iVar22 + 0xcb) = bVar26 | 1;
      }
	  
      iVar16 = iVar16 + iVar20;
      iVar23 = iVar23 + iVar24;
	  
	  // previous skidmark index
      uVar13 = bVar1 - 1 & 7;
      iVar22 = param_2 + uVar13 * 0x40;
	  
	  // record skidmark buffer
      *(short *)(iVar22 + 0xc4) = (short)iVar16 + sVar5;
      *(undefined2 *)(iVar22 + 0xc6) = uVar15;
      *(short *)(iVar22 + 200) = (short)iVar23 + sVar4;
      *(short *)(iVar22 + 0xcc) = (short)iVar16 - sVar5;
      *(undefined2 *)(iVar22 + 0xce) = uVar15;
      *(short *)(iVar22 + 0xd0) = (short)iVar23 - sVar4;
      *(char *)(iVar22 + 0xca) = cVar25;
	  
      if ((local_30 & 8) == 0) {
         *(byte *)(iVar22 + 0xcb) = bVar26;
      }
      else {
         *(byte *)(iVar22 + 0xcb) = bVar26 | 1;
      }
	  
	  // enable skidmarks for second tire
      *(uint *)(param_2 + 0x2c4) = *(uint *)(param_2 + 0x2c4) | 2;
	  
      gte_ldVXY0(0x1e);
      gte_ldVZ0(0xffffffec);
      gte_rt();
      read_mt(iVar16,in_t1,iVar23);
      
	  // next skidmark index
	  uVar13 = uVar13 + 1 & 7;
      iVar22 = param_2 + uVar13 * 0x40;
	  
	  // skidmark data
      sVar6 = (short)(iVar16 - iVar11);
      *(short *)(iVar22 + 0xd4) = sVar6 + sVar7;
      sVar2 = (short)(iVar23 - iVar18);
      *(short *)(iVar22 + 0xd8) = sVar2 + sVar3;
      *(short *)(iVar22 + 0xdc) = sVar6 - sVar7;
      *(undefined2 *)(iVar22 + 0xd6) = uVar15;
      *(undefined2 *)(iVar22 + 0xde) = uVar15;
      *(short *)(iVar22 + 0xe0) = sVar2 - sVar3;
      *(char *)(iVar22 + 0xda) = cVar25;
      if ((*(uint *)(puVar21 + 0x38) & 8) == 0) {
         *(byte *)(iVar22 + 0xdb) = bVar26;
      }
      else {
         *(byte *)(iVar22 + 0xdb) = bVar26 | 1;
      }
      param_3 = (undefined *)((iVar16 - iVar11) + iVar20);
      param_4 = (iVar23 - iVar18) + iVar24;
      
	  // previous skidmark index
	  iVar22 = param_2 + (uVar13 - 1 & 7) * 0x40;
      
	  *(short *)(iVar22 + 0xd4) = (short)param_3 + sVar5;
      puVar12 = param_3 + -iVar9;
      *(undefined2 *)(iVar22 + 0xd6) = uVar15;
      *(short *)(iVar22 + 0xd8) = (short)param_4 + sVar4;
      *(short *)(iVar22 + 0xdc) = (short)puVar12;
      *(undefined2 *)(iVar22 + 0xde) = uVar15;
      *(short *)(iVar22 + 0xe0) = (short)param_4 - sVar4;
      *(char *)(iVar22 + 0xda) = cVar25;
      if ((*(uint *)(puVar21 + 0x38) & 8) == 0) {
         *(byte *)(iVar22 + 0xdb) = bVar26;
      }
      else {
         *(byte *)(iVar22 + 0xdb) = bVar26 | 1;
      }
    }
	
    // front wheel skids
    if ((*(uint *)(param_2 + 0x2c8) & 0x1000) != 0) 
	{
	  // enable skidmarks for third tire
      *(uint *)(param_2 + 0x2c4) = *(uint *)(param_2 + 0x2c4) | 4;
	  
      gte_ldVXY0(0xffe2);
      gte_ldVZ0(0x28);
      gte_rt();
      read_mt(param_3,in_t1,param_4);
      bVar1 = *(byte *)(param_2 + 0xc3);
      iVar22 = param_2 + (uint)bVar1 * 0x40;
      sVar6 = (short)((int)param_3 - iVar11);
      *(short *)(iVar22 + 0xe4) = sVar6 + sVar7;
      sVar2 = (short)(param_4 - iVar18);
      *(short *)(iVar22 + 0xe8) = sVar2 + sVar3;
      *(short *)(iVar22 + 0xec) = sVar6 - sVar7;
      *(undefined2 *)(iVar22 + 0xe6) = uVar15;
      *(undefined2 *)(iVar22 + 0xee) = uVar15;
      *(short *)(iVar22 + 0xf0) = sVar2 - sVar3;
      *(char *)(iVar22 + 0xea) = cVar25;
      if ((*(uint *)(puVar21 + 0x38) & 8) == 0) {
         *(byte *)(iVar22 + 0xeb) = bVar26;
      }
      else {
         *(byte *)(iVar22 + 0xeb) = bVar26 | 1;
      }
      iVar23 = ((int)param_3 - iVar11) + iVar20;
      iVar16 = (param_4 - iVar18) + iVar24;
	  
	  // next skidmark buffer
      uVar13 = bVar1 - 1 & 7;
      iVar22 = param_2 + uVar13 * 0x40;
      
	  *(short *)(iVar22 + 0xe4) = (short)iVar23 + sVar5;
      sVar6 = (short)iVar16;
      *(undefined2 *)(iVar22 + 0xe6) = uVar15;
      *(short *)(iVar22 + 0xe8) = sVar6 + sVar4;
      *(short *)(iVar22 + 0xec) = (short)iVar23 - sVar5;
      *(undefined2 *)(iVar22 + 0xee) = uVar15;
      *(short *)(iVar22 + 0xf0) = sVar6 - sVar4;
      *(char *)(iVar22 + 0xea) = cVar25;
      if ((*(uint *)(puVar21 + 0x38) & 8) == 0) {
         *(byte *)(iVar22 + 0xeb) = bVar26;
      }
      else {
         *(byte *)(iVar22 + 0xeb) = bVar26 | 1;
      }
	  
	  // enable skidmarks for fourth tire
      *(uint *)(param_2 + 0x2c4) = *(uint *)(param_2 + 0x2c4) | 8;
	  
      gte_ldVXY0(0x1e);
      gte_ldVZ0(0x28);
      gte_rt();
      read_mt(iVar23,in_t1,iVar16);
      
	  // next skidmark buffer
	  uVar13 = uVar13 + 1 & 7;
	  
      sVar6 = sVar6 - (short)iVar18;
      iVar22 = param_2 + uVar13 * 0x40;
      sVar2 = (short)(iVar23 - iVar11);
      *(short *)(iVar22 + 0xf4) = sVar2 + sVar7;
      *(short *)(iVar22 + 0xf8) = sVar6 + sVar3;
      *(short *)(iVar22 + 0xfc) = sVar2 - sVar7;
      *(undefined2 *)(iVar22 + 0xf6) = uVar15;
      *(undefined2 *)(iVar22 + 0xfe) = uVar15;
      *(short *)(iVar22 + 0x100) = sVar6 - sVar3;
      *(char *)(iVar22 + 0xfa) = cVar25;
      if ((*(uint *)(puVar21 + 0x38) & 8) == 0) {
         *(byte *)(iVar22 + 0xfb) = bVar26;
      }
      else {
         *(byte *)(iVar22 + 0xfb) = bVar26 | 1;
      }
      iVar20 = (iVar23 - iVar11) + iVar20;
      sVar6 = sVar6 + (short)iVar24;
      iVar22 = param_2 + (uVar13 - 1 & 7) * 0x40;
      *(short *)(iVar22 + 0xf4) = (short)iVar20 + sVar5;
      puVar12 = (undefined *)(iVar20 - iVar9);
      *(undefined2 *)(iVar22 + 0xf6) = uVar15;
      *(short *)(iVar22 + 0xf8) = sVar6 + sVar4;
      *(short *)(iVar22 + 0xfc) = (short)puVar12;
      *(undefined2 *)(iVar22 + 0xfe) = uVar15;
      *(short *)(iVar22 + 0x100) = sVar6 - sVar4;
      *(char *)(iVar22 + 0xfa) = cVar25;
      if ((*(uint *)(puVar21 + 0x38) & 8) == 0) {
         *(byte *)(iVar22 + 0xfb) = bVar26;
      }
      else {
         *(byte *)(iVar22 + 0xfb) = bVar26 | 1;
      }
    }
  }

  // thread -> modelIndex == "robotcar" of any kind
  if (*(short *)(*(int *)(puVar21 + 0x68) + 0x44) == 0x3f) 
  {
	// put each driver on alternates frames of 4 (0,1,2,3)
    uVar13 = *(uint *)(PTR_DAT_8008d2ac + 0x1cec) & 3;
    if (uVar13 != (*(byte *)(param_2 + 0x4a) & 3)) goto LAB_8005a9d8;

LAB_8005a858:
    if (*(char *)(param_2 + 0x381) != '\0') goto LAB_8005a868;
  }
  
  // else if "player"???
  else 
  {
    if (
			// revEngineState
			(*(char *)(param_2 + 0x4fe) == '\x02') ||
			
			(
				(
					// do not use GOTO in 1P mode
					uVar13 = (uint)(byte)PTR_DAT_8008d2ac[0x1ca8], 1 < uVar13 &&
         
					(
						(
							(
								// in 2P, alternate on every 2 frames
								uVar13 != 2 ||
								(
									uVar13 = (uint)*(byte *)(param_2 + 0x4a),
           
									(*(uint *)(PTR_DAT_8008d2ac + 0x1cec) & 1) != uVar13
								)
							) &&
          
							// in 4P, alternate on every 4 frames
							(
								uVar13 = (uint)*(byte *)(param_2 + 0x4a),
								(*(uint *)(PTR_DAT_8008d2ac + 0x1cec) & 3) != uVar13
							)
						)
					)
				)
			)
		) goto LAB_8005a9d8;
		
    puVar12 = PTR_DAT_8008d2ac;
    if (*(char *)(param_2 + 0x381) == '\0') 
	{
      uVar13 = (uint)*(short *)(param_2 + 0x3dc);
      
	  if (((int)uVar13 < 0x81) || ((int)((*(byte *)(param_2 + 0x477) + 2) * 0x20) < (int)uVar13)) 
	  {
         puVar12 = *(undefined **)(*(int *)(puVar21 + 0x68) + 0x14);
		 
		 // PROC_SearchForModel (turbo)
         uVar29 = FUN_80042394(puVar12,0x2c);
         uVar13 = (uint)((ulonglong)uVar29 >> 0x20);
         if ((int)uVar29 != 0) goto LAB_8005a9d8;
      }
      
	  goto LAB_8005a858;
    }
LAB_8005a868:
    *(char *)(param_2 + 0x381) = *(char *)(param_2 + 0x381) + -1;
  }
  
  // instance->matrix
  pMVar10 = (MATRIX *)(iVar27 + 0x30);
  gte_SetRotMatrix(pMVar10);
  gte_ldVXY0(0x4000000);
  gte_ldVZ0(0xfffffc00);
  gte_rtv0();
  read_mt(pMVar10,uVar13,puVar12);
  
  *(MATRIX **)(puVar21 + 0x28) = pMVar10;
  *(uint *)(puVar21 + 0x2c) = uVar13;
  *(undefined **)(puVar21 + 0x30) = puVar12;
  
  // instance scale (x,y,z)
  gte_ldVXY0(*(short *)(iVar27 + 0x1c) * 9 >> 3 & 0xffffU |
              (*(short *)(iVar27 + 0x1e) * 7 >> 1) << 0x10);
  
  gte_ldVZ0(*(short *)(iVar27 + 0x20) * -0x38 >> 4);
  gte_rtv0();
  
  r0 = (VECTOR *)(puVar21 + 0x18);
  gte_stlvnl(r0);
  
  puVar21 = puVar21 + 0x28;
  
  // VehEmitter_Exhaust
  FUN_80059100(param_2,r0,puVar21);
  
  // instance scale (x,y,z)
  gte_ldVXY0(*(short *)(iVar27 + 0x1c) * -0x12 >> 4 & 0xffffU |
              (*(short *)(iVar27 + 0x1e) * 7 >> 1) << 0x10);
  gte_ldVZ0(*(short *)(iVar27 + 0x20) * -0x38 >> 4);
  gte_rtv0();
  
  gte_stlvnl(r0);
  
  // VehEmitter_Exhaust
  FUN_80059100(param_2,r0,puVar21);

LAB_8005a9d8:

  // if driver is burnt
  if (*(short *)(param_2 + 0x402) != 0) 
  {
    *(undefined2 *)(param_2 + 0x508) = 0x1000;
	
	// set alpha to max (draws black)
    *(undefined2 *)(*(int *)(param_2 + 0x1c) + 0x22) = 0x1000;
  }
  
  // if driver is invisible
  if (*(int *)(param_2 + 0x28) != 0) 
  {
	// set transparency to max
    *(undefined2 *)(iVar27 + 0x22) = 0x1000;
  }
  
  //if racer is not driving normally and not drifting
  if ((*(char *)(param_2 + 0x376) != '\0') && (*(char *)(param_2 + 0x376) != '\x02')) 
  {
    //turn off 20th bit of Actions Flag set (means racer is not in the air)
    *(uint *)(param_2 + 0x2c8) = *(uint *)(param_2 + 0x2c8) & 0xfff7ffff;
  }
  
  //if racer is being mask grabbed or repositioned, or is on the ground
  if ((*(byte *)(param_2 + 0x376) - 4 < 2) || ((*(uint *)(param_2 + 0x2c8) & 1) != 0)) 
  {
	// GAMEPAD_JogCon2
    FUN_800263fc(param_2,0x27,0);
	
    if (*(short *)(param_2 + 0x3d4) == 0) {
      return;
    }
    if ((*(uint *)(PTR_DAT_8008d2ac + 0x1cec) & 3) == 0) {
      uVar19 = 0x27;
    }
    else {
      uVar19 = 0xf0;
    }
    uVar14 = 0x100;
  }
  else 
  {
    // low jump landing boost
	if (*(short *)(param_2 + 0x3fc) < 0x80) 
	{
      uVar19 = 0x12;
      if (
			// steer left
			(*(char *)(param_2 + 0x4b) < '\0') || 
			
			(
				// steer right
				uVar19 = 0x22, 
				'\0' < *(char *)(param_2 + 0x4b)
			)
		) 
	  {
		 // GAMEPAD_JogCon1
         FUN_800263a0(param_2,uVar19,0x20);
      }
    }
    uVar19 = 0;
    uVar14 = uVar19;
  }
 
  // GAMEPAD_JogCon2
  FUN_800263fc(param_2,uVar19,uVar14);
  return;
}

// VehFire_Audio
// param1 - driver
// param2 - speed cap
void FUN_8005ab24(int param_1,int param_2)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  int iVar4;

  // if turbo audio cooldown is not done
  if (*(short *)(param_1 + 0x3e0) != 0) {
    return;
  }

  // half volume
  iVar4 = 0x80;

  if (param_2 < 0x40)
  {
	// distort
    iVar3 = 0x94;
  }

  else
  {
	// 3/4 volume
    iVar4 = 0xc0;

	if (0x7f < param_2)
	{
	  // distort
      iVar3 = 0x6c;

	  // Make driver talk
      FUN_8002cbe8(0x10,(int)(short)(&DAT_80086e84)[*(byte *)(param_1 + 0x4a)],0x10);

	  // max volume
	  uVar2 = 0xff0000;

	  goto LAB_8005aba4;
    }

	// no distort
    iVar3 = 0x80;
  }

  // volume
  uVar2 = iVar4 << 0x10;

LAB_8005aba4:

  // distortion
  uVar1 = iVar3 << 8;

  // if echo is requierd
  if ((*(uint *)(param_1 + 0x2c8) & 0x10000) != 0)
  {
	// add echo
    uVar1 = uVar1 | 0x1000000;
  }

  // OtherFX_Play_LowLevel
  // 0xD = Turbo Boost Sound
  // 0x80 = balance L/R
  FUN_800284d0(0xd,1,uVar2 | uVar1 | 0x80);

  // turbo audio cooldown 0.24s
  *(undefined2 *)(param_1 + 0x3e0) = 0xf0;

  return;
}

// VehFire_Increment
// param1 - driver
// param2 - reserves to add
// param3 - add type
// param4 - fire level
void FUN_8005abfc(int param_1,int param_2,uint param_3,int param_4)

{
  char cVar1;
  short sVar2;
  undefined *puVar3;
  undefined uVar4;
  int iVar5;
  uint uVar6;
  int *piVar7;
  int iVar8;
  short sVar9;

  if (
		//if pointer is not null and
		((param_3 & 4) != 0) &&
		
		//racer is in accel prevention
		((*(uint *)(param_1 + 0x2c8) & 8) != 0)
	)
  {
    return;
  }

  if (
	// Player / AI structure + 0x4a shows driver index (0-7)

    // If this is the first driver (P1) and
		(*(char *)(param_1 + 0x4a) == '\0') &&

		// driver -> instance -> thread -> modelIndex == "player" of any kind
		(*(short *)(*(int *)(*(int *)(param_1 + 0x1c) + 0x6c) + 0x44) == 0x18)
	 )
  {
    // Add Reserves to ghost buffer
    FUN_8002838c(param_2,param_3,param_4);
  }

  //puVar3 = 0x96B20
  puVar3 = PTR_DAT_8008d2ac;
  //cVar1 = Kart state
  cVar1 = *(char *)(param_1 + 0x376);

  //if player is spinning, blasted, or mask grabbed, quit the function
  if (cVar1 == '\x03') {
    return;
  }
  if (cVar1 == '\x06') {
    return;
  }
  if (cVar1 == '\x05') {
    return;
  }

  //turn off 8th flag, turn on 22nd flag of actions flag set
  //means ? (!(8)) and racer just got an outside turbo (22)
  *(uint *)(param_1 + 0x2c8) = *(uint *)(param_1 + 0x2c8) & 0xffffff7f | 0x200000;

  // turbo thread bucket
  iVar5 = *(int *)(puVar3 + 0x1be0);

  // turbo thread bucket exists
  if (iVar5 != 0)
  {
    // check all turbo threads
    do
	{
      // if this turbo thread is owned by this driver
	  // turboThread->object->offset0x4 == driver
      if (*(int *)(*(int *)(iVar5 + 0x30) + 4) == param_1)
	  {
		  // quit, iVar5 is now this driver's turbo thread
		  break;
	  }

	  // next turbo thread in bucket
      iVar5 = *(int *)(iVar5 + 0x10);

    } while (iVar5 != 0);

    // if this driver's turbo thread was found
    if (iVar5 != 0)
	{
	  // get the turbo's object
      piVar7 = *(int **)(iVar5 + 0x30);

      // get the turbo's instance
      iVar8 = *(int *)(iVar5 + 0x34);

	  // thread flags
      *(uint *)(iVar5 + 0x1c) = *(uint *)(iVar5 + 0x1c) & 0xfffff7ff;

	  // manipulate how turbo draws, depending on Add Type flag
      if ((param_3 & 4) == 0)
	  {

        // turbo instance (1/2) attached to thread, edit instance draw flags
        *(uint *)(iVar8 + 0x28) = *(uint *)(iVar8 + 0x28) | 0x1000080;

        // turbo instance (2/2) in thread's object, edit instance draw flags
        *(uint *)(*piVar7 + 0x28) = *(uint *)(*piVar7 + 0x28) | 0x1000080;

        *(undefined2 *)((int)piVar7 + 0xe) = 0x60;

LAB_8005ad6c:

        //increase Turbo counter by 1
        *(short *)(param_1 + 0x4e) = *(short *)(param_1 + 0x4e) + 1;
      }

	  // if AddType is different
      else
	  {
        //if racer got an Outside turbo, add it to the Turbo counter
        if ((*(uint *)(param_1 + 0x2cc) & 0x200000) == 0) goto LAB_8005ad6c;
      }

      *(undefined *)(piVar7 + 3) = 0xff;
      *(undefined2 *)(iVar8 + 0x22) = 0;
      *(undefined2 *)(*piVar7 + 0x22) = 0;

      if (
			// driver -> instance -> thread -> modelIndex == "player" of any kind
			(*(short *)(*(int *)(*(int *)(param_1 + 0x1c) + 0x6c) + 0x44) == 0x18) &&
			(
				(
					//if racer is not getting a new boost this frame
					(*(uint *)(param_1 + 0x2c8) & 0x200000) == 0 ||

					//racer was not getting a new boost previous frame
					((*(uint *)(param_1 + 0x2cc) & 0x200000) == 0)
				)
			)
		)
      {
        *(undefined *)((int)piVar7 + 0xd) = 0;

		// VehFire_Audio
        FUN_8005ab24(param_1,param_4);
      }

      // skip code, do not re-initialize turbo thread,
	  // because it already exists
      goto LAB_8005af38;
    }
  }

  // If the program reaches this point,
  // it means a boost was added to the driver,
  // and a thread does not already exist, so
  // a turbo thread is created

  //Turbo counter = 1
  *(undefined2 *)(param_1 + 0x4e) = 1;

  // definitely related to turbo display counter,
  // because it is in the HUD thread bucket...

  // s_turbo1_8008d61c
  // "turbo1"
  // 0x300 flag = SmallStackPool
  // 0x10 = HUD thread bucket
  iVar5 = FUN_800309a4(0x2c,s_turbo1_8008d61c,0x300,9,FUN_800693c8,0x10,0);

  // piVar7 = nullptr
  piVar7 = (int *)0x0;

  //if iVar5 != nullptr
  if (iVar5 != 0)
  {
    // turboInstance->thread->object
    piVar7 = *(int **)(*(int *)(iVar5 + 0x6c) + 0x30);

    // store Driver pointer inside Turbo object
    piVar7[1] = param_1;

    *(undefined2 *)((int)piVar7 + 0xe) = 0;

    // allow this thread to ignore all collisions
    *(uint *)(*(int *)(iVar5 + 0x6c) + 0x1c) = *(uint *)(*(int *)(iVar5 + 0x6c) + 0x1c) | 0x1000;

    if (

	  // driver -> instance -> thread -> modelIndex == "player" of any kind
      (*(short *)(*(int *)(*(int *)(param_1 + 0x1c) + 0x6c) + 0x44) == 0x18) &&
      (
		*(undefined *)((int)piVar7 + 0xd) = 0,

		//racer is not crashing
		*(char *)(param_1 + 0x376) != '\x01'
	  )
    )
    {
	  // VehFire_Audio
      FUN_8005ab24(param_1,param_4);
    }

    //puVar3 = 0x96B20
    puVar3 = PTR_DAT_8008d2ac;

	// turbo thread OnDestroy
    *(undefined4 *)(*(int *)(iVar5 + 0x6c) + 0x24) = 0x80069370;

    // s_turbo2_8008d624
    // "turbo2"

	// INSTANCE_Birth3D -- ptrModel, name, thread,
	// model 0x2c, first turbo_effect
    iVar8 = FUN_8003086c(*(undefined4 *)(puVar3 + 0x2210),
			s_turbo2_8008d624,

			// turbo thread
      *(undefined4 *)(iVar5 + 0x6c));

    //puVar3 = 0x96B20 (again)
    puVar3 = PTR_DAT_8008d2ac;

	// store pointer to 2nd turbo
	// inside Turbo object
    *piVar7 = iVar8;

    // if numPlyrCurrGame is not 1
    uVar6 = 0x1040000;

    // if numPlyrCurrGame is 1
    if (puVar3[0x1ca8] == '\x01')
	{
      uVar6 = 0x3040000;
    }

	// turbo (1/2) instance flag (attached to thread)
    *(uint *)(iVar5 + 0x28) =
	*(uint *)(iVar5 + 0x28) | uVar6 | 0x80;

	// turbo (2/2) instance flag (attached to object)
    *(uint *)(*piVar7 + 0x28) =
	*(uint *)(*piVar7 + 0x28) | uVar6 | 0x80;

    *(undefined2 *)(piVar7 + 2) = 0;
    if ((param_3 & 2) == 0) {
      uVar4 = 0xff;
    }
    else {
      uVar4 = 2;
    }
    *(undefined *)(piVar7 + 3) = uVar4;
  }

// This code only seem to run when you either are on a turbo pad/super turbo pad or you get any sort of boost
LAB_8005af38:

  // param_4 = multiplier that represents the level of fire of your boost
  // Constant values:
  // sacred fire speed cap = 0x1000
  // single turbo speed cap = 0x800

  // iVar5 = (param_4 * sacred fire speed cap) - (single turbo speed cap >> 8) + (single turbo speed cap)
  // iVar5 = ground speed cap represented by your multiplier

  iVar5 = (param_4 * ((int)*(short *)(param_1 + 0x432) - (int)*(short *)(param_1 + 0x430)) >> 8) +
          (int)*(short *)(param_1 + 0x430);

  if (
      (
		(
			// Reserves are equal to zero
			(*(short *)(param_1 + 0x3e2) == 0) ||

			// OR

			// Current ground speed cap is less than iVar5
			((int)*(short *)(param_1 + 0x3e4) < iVar5)
		) ||

		// OR

		(
			(
				// Current speed cap is greater than 0x1000
				(int)*(short *)(param_1 + 0x432) < (int)*(short *)(param_1 + 0x3e4) &&

				// AND

				// You are not on a super turbo pad
				((*(uint *)(param_1 + 0xbc) & 2) == 0)
			)
		)
	  ) &&

    // AND

	  (
		(
			// Current speed cap = iVar5
			*(undefined2 *)(param_1 + 0x3e4) = (short)iVar5,

			// Compare !=
			piVar7 != (int *)0x0 &&

			// AND

			(
				// Assignment
				iVar5 = (param_4 >> 6) + 5,

				// Assignment
				*(undefined2 *)((int)piVar7 + 10) = (short)iVar5,

				// Compoare <
				8 < iVar5 * 0x10000 >> 0x10
			)
		)
	  )
	 )
  {
    *(undefined2 *)((int)piVar7 + 10) = 8;
  }

  if ((param_3 & 8) != 0)
  {
	// driver is using turbo weapon
    *(uint *)(param_1 + 0x2c8) = *(uint *)(param_1 + 0x2c8) | 0x200;
  }

  sVar9 = (short)param_2;
  if ((param_3 & 1) == 0)
  {
    if ((param_3 & 0x10) == 0)
	{
	  // increase reserves BY param2
      *(short *)(param_1 + 0x3e2) = *(short *)(param_1 + 0x3e2) + sVar9;
    }
    else
	{
	  // increase reserves TO param2
      if (*(short *)(param_1 + 0x3e2) < param_2)
	  {
        *(short *)(param_1 + 0x3e2) = sVar9;
      }
    }
  }
  else {
    sVar2 = *(short *)(param_1 + 0x3de);
    if (*(short *)(param_1 + 0x3de) < param_2) {
      *(short *)(param_1 + 0x3de) = sVar9;
      *(short *)(param_1 + 0x3e2) = *(short *)(param_1 + 0x3e2) + (sVar9 - sVar2);
    }
  }

  // driver -> instance -> thread -> modelIndex == "player" of any kind
  if (*(short *)(*(int *)(*(int *)(param_1 + 0x1c) + 0x6c) + 0x44) == 0x18) {

	// CameraDC flag
    *(uint *)(PTR_DAT_8008d2ac + (uint)*(byte *)(param_1 + 0x4a) * 0xdc + 0x1508) =
         *(uint *)(PTR_DAT_8008d2ac + (uint)*(byte *)(param_1 + 0x4a) * 0xdc + 0x1508) | 0x80;

	// GAMEPAD_ShockForce1
    FUN_800264c0(param_1,8,0x7f);
  }
  return;
}


// animation index, and number of frames
// 0 - midpoint (steering should start at midpoint)
// 1 - start
// 2 - start
// 3 - start
// 4 - end

// VehFrameInst_GetStartFrame
int FUN_8005b0c4(int param_1,int param_2)
{
  if (param_1 == 0) {
    return param_2 >> 1;
  }
  if (param_1 != 4) {
    return 0;
  }
  return param_2 + -1;
}


// get number of frames in animation
// param1 - instance
// param2 - animIndex

// VehFrameInst_GetNumAnimFrames
uint FUN_8005b0f4(int param_1,int param_2)
{
  int iVar1;

  // instance -> model
  iVar1 = *(int *)(param_1 + 0x18);

  // if model is valid, and if numHeaders is more than zero
  if ((((iVar1 != 0) && (0 < *(short *)(iVar1 + 0x12))) &&

	  // get header, check for nullptr
      (iVar1 = *(int *)(iVar1 + 0x14), iVar1 != 0)) &&

	  // animIndex < numAnimations in model
	  (param_2 < *(int *)(iVar1 + 0x34)))
  {
	// if pointer to animation data is valid
    if (*(int *)(iVar1 + 0x38) != 0)
	{
	  // get pointer to animation, given animIndex
      iVar1 = *(int *)(param_2 * 4 + *(int *)(iVar1 + 0x38));
      if (iVar1 != 0)
	  {
		// return number of animation frames
        return (uint)*(ushort *)(iVar1 + 0x10) & 0x7fff;
      }
      return 0;
    }
  }
  return 0;
}


// VehFrameProc_Driving
// param1 = thread, param2 = driver
void FUN_8005b178(int param_1,int param_2)
{
  byte bVar1;
  undefined *puVar2;
  char cVar3;
  undefined2 uVar4;
  int iVar5;
  short sVar6;
  int iVar7;
  undefined4 uVar8;
  int iVar9;
  int iVar10;
  uint uVar11;

  // Get instance from thread
  iVar10 = *(int *)(param_1 + 0x34);

  // animation is drive forwards
  uVar11 = 0;

  //if you don't have a TNT over you and state of kart is not in a warp pad
  if ((*(int *)(param_2 + 0x18) == 0) && (*(char *)(param_2 + 0x376) != '\n'))
  {
    if (*(short *)(param_2 + 0x39e) < 0)
	{
      // check if you are driving backwards
	  // (0) forwards
	  // (1) backwards
      uVar11 = (uint)(*(short *)(param_2 + 0x38e) < 1);
    }
    if (
		((0x600 < *(short *)(param_2 + 0x390)) || (*(char *)(iVar10 + 0x52) == '\x03')) &&

		// if player height is far from quadblock height
		(0x8000 < *(int *)(param_2 + 0x2d8) - *(int *)(param_2 + 0x2d0))
		)
	{
	  // jumping animation
      uVar11 = 3;
    }
  }

  // get number of frames in animation
  iVar5 = FUN_8005b0f4(iVar10,(uint)*(byte *)(iVar10 + 0x52));

  // if animation has frames
  if (0 < iVar5)
  {
	// get animation frame currently
    bVar1 = *(byte *)(iVar10 + 0x52);

	// if animation changes
    if (uVar11 != (uint)bVar1)
	{
	  // if crashing animation
      if (bVar1 == 2)
	  {
		// get number of frames in animation
        iVar5 = FUN_8005b0f4(iVar10);

		// start on last frame
        iVar5 = iVar5 + -1;
      }

      else
	  {
		// VehFrameInst_GetStartFrame
        iVar5 = FUN_8005b0c4((uint)bVar1,iVar5);
      }

	  // if animation frame has changed
	  if ((int)*(short *)(iVar10 + 0x54) != iVar5) 
	  {
		// if steering animation
        if (*(char *)(iVar10 + 0x52) == '\0') {
          uVar8 = 6;
        }
		
        else 
		{
		  // jump or reverse?
          uVar8 = 2;
          
		  // crashing
		  if (*(char *)(iVar10 + 0x52) == '\x02') 
		  {
            uVar8 = 1;
            
			// matrixIndex = animFrame
            *(undefined *)(param_2 + 0x4d) = *(undefined *)(iVar10 + 0x54);
          }
        }

		// Interpolate animation by speed
        uVar4 = FUN_80058f54((int)*(short *)(iVar10 + 0x54),uVar8,iVar5);
        *(undefined2 *)(iVar10 + 0x54) = uVar4;

        if (1 < (uint)*(byte *)(iVar10 + 0x52) - 2) {
          return;
        }

		// get animation frame from Instance
        cVar3 = *(char *)(iVar10 + 0x54);

        // Give it to driver
        *(char *)(param_2 + 0x4d) = cVar3;

		if (cVar3 != '\0') {
          return;
        }
        //kart animation Index
        *(undefined *)(param_2 + 0x4c) = 0;

        //kart animation frame
        *(undefined *)(param_2 + 0x4d) = 0;
        return;
      }

	  // get number of frames in animation
      iVar5 = FUN_8005b0f4(iVar10,uVar11);
      if (iVar5 < 1) {
        return;
      }

	  // set animation
      *(undefined *)(iVar10 + 0x52) = (char)uVar11;

	  // VehFrameInst_GetStartFrame
      uVar4 = FUN_8005b0c4(uVar11,iVar5);

	  // set animation frame
      *(undefined2 *)(iVar10 + 0x54) = uVar4;

	  // animation index
      *(undefined *)(param_2 + 0x4c) = 0;

	  // animation frame
	  *(undefined *)(param_2 + 0x4d) = 0;
    }
    //puVar2 = 0x96B20
    puVar2 = PTR_DAT_8008d2ac;

	// steering animation
	if (uVar11 == 0)
	{
      iVar9 = iVar5 >> 1;

	  //if you don't have a TNT over you
      if (*(int *)(param_2 + 0x18) == 0)
	  {
        //sVar6 = time burnt left
        sVar6 = *(short *)(param_2 + 0x402);

		//if you're not burnt or your time burnt left is bigger than 0x1df
        if ((sVar6 == 0) || (0x1df < sVar6))
		{
		  //iVar9 = negative turning stat while braking
          iVar9 = -0x40;

		  //if you're not in accel prevention
          if ((*(uint *)(param_2 + 0x2c8) & 8) == 0) 
		  {
            //iVar7 = simplified turning state
            iVar7 = (int)*(char *)(param_2 + 0x4b);

			//uVar11 = character's turn stat
            uVar11 = (uint)*(byte *)(param_2 + 0x43a);

			//iVar9 = negative character's turn stat
            iVar9 = -uVar11;
          }
          //if you're braking or being mask grabbed
          else {
            //uVar11 = positive turning stat while braking
            uVar11 = 0x40;

			//iVar7 = amplified turning state
            iVar7 = (int)*(short *)(param_2 + 0xc0);
          }

          //seems like iVar9 gets set to 0 if you're turning, or to iVar5 - 1 if you're not
          // Map value from [oldMin, oldMax] to [newMin, newMax]
          // inverting newMin and newMax will give an inverse range mapping
          iVar9 = FUN_80058f9c(-iVar7,iVar9,uVar11,0,iVar5 + -1);
        }

        //if your time burnt left is between (0x0, 0x1df)
        else {
          iVar9 = (((int)(sVar6 >> 5) % 5) * 0x10000 >> 0xe) + -8 + iVar9;
          *(undefined2 *)(iVar10 + 0x54) = (short)iVar9;

		  // Create instance in particle pool
          iVar5 = FUN_80040308(0,*(undefined4 *)(puVar2 + 0x2118),&DAT_80089974);

          if (iVar5 != 0) {
            *(undefined *)(iVar5 + 0x18) = *(undefined *)(*(int *)(param_2 + 0x1c) + 0x50);

			// driver -> instSelf
            *(undefined4 *)(iVar5 + 0x20) = *(undefined4 *)(param_2 + 0x1c);

			// driverID
            *(undefined *)(iVar5 + 0x19) = *(undefined *)(param_2 + 0x4a);
          }
        }
      }
      sVar6 = *(short *)(iVar10 + 0x54);
    }
    
	else 
	{
	  // jump animation
      if (uVar11 == 3)
	  {
		// Interpolate animation frame by speed
        uVar4 = FUN_80058f54((int)*(short *)(iVar10 + 0x54),1,iVar5 + -1);

		// set animation frame
        *(undefined2 *)(iVar10 + 0x54) = uVar4;

		    //if you're getting mask grabbed
        if (*(char *)(param_2 + 0x376) == '\x05') {
          return;
        }

		//player / AI structure + 0x4a shows driver index (0-7)

		//get character ID
        sVar6 = (&DAT_80086e84)[*(byte *)(param_2 + 0x4a)];

		//if this is penta
        if (sVar6 == 0xd) {
          sVar6 = 3;
        }

		//if this is fake crash
        if (sVar6 == 0xe) {
          sVar6 = 0;
        }

        cVar3 = (char)sVar6 + 7;

		//if this is oxide
        if (sVar6 == 0xf) 
		{
          cVar3 = 7;
        }

		// set matrixArr for jump
        *(char *)(param_2 + 0x4c) = cVar3;

        // set matrixIndex to animation frame
        *(undefined *)(param_2 + 0x4d) = *(undefined *)(iVar10 + 0x54);
        return;
      }
      iVar9 = iVar5 + -1;

	  // set animation frame
      sVar6 = *(short *)(iVar10 + 0x54);
    }

	// Interpolate rotation by speed
    uVar4 = FUN_80058f54((int)sVar6,1,iVar9);

	  // set animation frame
    *(undefined2 *)(iVar10 + 0x54) = uVar4;
    return;
  }
  return;
}

// VehFrameProc_Spinning
// param1 = thread, param2 = driver
void FUN_8005b510(int param_1,int param_2)

{
  undefined2 uVar1;
  int iVar2;
  int iVar3;
  int iVar4;

  // get instance from thread
  iVar4 = *(int *)(param_1 + 0x34);

  // Instance_GetNumAnimFrames(instance, animIndex)
  iVar2 = FUN_8005b0f4(iVar4,(uint)*(byte *)(iVar4 + 0x52));

  // if there are no frames
  if (iVar2 < 1)
  {
	// quit
    return;
  }

  // if animation is not zero
  if (*(byte *)(iVar4 + 0x52) != 0)
  {
	// VehFrameInst_GetStartFrame
    iVar3 = FUN_8005b0c4((uint)*(byte *)(iVar4 + 0x52),iVar2);

	// If animation is negative
    if ((uint)*(byte *)(iVar4 + 0x52) - 2 < 2)
	{
	  // reset animation id and frame
      *(undefined *)(param_2 + 0x4c) = 0;
      *(undefined *)(param_2 + 0x4d) = 0;
    }

    if ((int)*(short *)(iVar4 + 0x54) == iVar3)
	{
	  // get number of frames in animation
      iVar2 = FUN_8005b0f4(iVar4,0);
      if (iVar2 < 1) {
        return;
      }

	  // set animation
      *(undefined *)(iVar4 + 0x52) = 0;
    }
    if (*(char *)(iVar4 + 0x52) != '\0') goto LAB_8005b5d0;
  }
  iVar3 = 0;
  if (-1 < *(short *)(param_2 + 0x582)) {
    iVar3 = iVar2 + -1;
  }
LAB_8005b5d0:

  // Interpolate animation frame by speed
  uVar1 = FUN_80058f54((int)*(short *)(iVar4 + 0x54),4,iVar3);

  // set animation frame
  *(undefined2 *)(iVar4 + 0x54) = uVar1;

  return;
}

// VehFrameProc_LastSpin
// param1 = thread, param2 = driver
void FUN_8005b5fc(int param_1,int param_2)

{
  short sVar1;
  undefined2 uVar2;
  int iVar3;
  int iVar4;
  int iVar5;

  // get instance from thread
  iVar5 = *(int *)(param_1 + 0x34);

  // if animation is zero
  if (*(char *)(iVar5 + 0x52) == '\0')
  {
	// get number of frames in animation
    iVar3 = FUN_8005b0f4(iVar5,0);

    if (0 < iVar3) {
      sVar1 = *(short *)(param_2 + 0x3c6);

	  // get animation frame
      iVar4 = (int)*(short *)(iVar5 + 0x54);

      if (0 < sVar1)
	  {
        if (*(short *)(param_2 + 0x3d2) < 0) {
          iVar4 = iVar3 + -1;
        }
        sVar1 = *(short *)(param_2 + 0x3c6);
      }

      if ((sVar1 < 0) && (0 < *(short *)(param_2 + 0x3d2))) {
        iVar4 = 0;
      }

	  // Interpolate animation frame by speed
      uVar2 = FUN_80058f54((int)*(short *)(iVar5 + 0x54),3,iVar4);

	  // set animation frame
      *(undefined2 *)(iVar5 + 0x54) = uVar2;
    }
  }
  else
  {
	// VehFrameProc_Spinning
    FUN_8005b510();
  }
  return;
}


// without this, all shadows are solid rectangles
// VehGroundShadow_Subset1
undefined4 FUN_8005b6b8(undefined4 *param_1,int param_2)

{
  int iVar1;

  // get pointer to icon
  iVar1 = *(int *)(PTR_DAT_8008d2ac + param_2 * 4 + 0x1eec);

  // if icon is valid
  if (iVar1 != 0) {
    *param_1 = *(undefined4 *)(iVar1 + 0x14);
    param_1[1] = *(uint *)(iVar1 + 0x18) & 0xff9fffff | 0x400000;
    *(undefined2 *)(param_1 + 2) = *(undefined2 *)(iVar1 + 0x1c);
    *(undefined2 *)((int)param_1 + 10) = *(undefined2 *)(iVar1 + 0x1e);
    return 1;
  }
  return 0;
}


// VehGroundShadow_Main
void FUN_8005b720(void)

{
  undefined *puVar1;
  char cVar2;
  ushort uVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  short sVar8;
  int iVar9;
  MATRIX *pMVar10;
  int iVar11;
  uint *puVar12;
  uint uVar13;
  short sVar14;
  undefined *puVar15;
  uint *puVar16;
  int iVar17;
  short sVar18;
  int iVar19;
  int iVar20;
  uint uVar21;
  MATRIX *r0;
  uint *puVar22;
  uint *puVar23;
  uint *puVar24;
  uint *puVar25;
  undefined2 *puVar26;
  SVECTOR *r0_00;
  undefined *puVar27;
  uint *puVar28;
  undefined auStack72 [32];
  
  puVar27 = auStack72;
  puVar23 = &DAT_1f800000;
  
  // without this, all shadows are solid rectangles
  iVar4 = FUN_8005b6b8(&DAT_1f800224,0);
  
  if (
		(
			(iVar4 != 0) && 
			(
				// without this, all shadows are solid rectangles
				iVar4 = FUN_8005b6b8(&DAT_1f800230,1), 
				iVar4 != 0
			)
		) &&
     
		(
			// backBuffer->primMem.curr
			puVar28 = *(uint **)(*(int *)(PTR_DAT_8008d2ac + 0x10) + 0x80),
		
			// if enough primMem remains to draw shadows
			puVar28 + 0x140 < *(uint **)(*(int *)(PTR_DAT_8008d2ac + 0x10) + 0x84)
		)
	  ) 
  {
	// set transformation vector to (0,0,0)
    _DAT_1f800090 = 0;
    DAT_1f800094 = 0;
    DAT_1f800098 = 0;
    gte_SetTransVector((VECTOR *)&DAT_1f800090);
	
	// loop counter
    iVar4 = 0;
	
    puVar15 = (undefined *)((uint)puVar23 | 0xb6);
    uVar21 = (uint)puVar23 | 0xa4;
	
	// for iVar4 = 0; iVar4 < 8; iVar4++
    do 
	{
      uVar6 = uVar21;
      puVar1 = PTR_DAT_8008d2ac;
	  
	  // pointer to each player structure
      iVar11 = *(int *)(PTR_DAT_8008d2ac + iVar4 * 4 + 0x24ec);
	  
	  // if player pointer is invalid
      if (iVar11 == 0) {
        *(undefined4 *)(puVar15 + 2) = 0;
      }
	  
	  // if player pointer is valid
      else 
	  {
        *(int *)(puVar15 + 2) = iVar11;
        
		// get instance
		iVar19 = *(int *)(iVar11 + 0x1c);
        
		*(int *)(puVar15 + 6) = iVar19;
        
											// instance flags
		*(undefined2 *)(puVar15 + 0x14) = *(undefined2 *)(iVar19 + 0x28);
        
		// numPlyrCurrGame - 1
		iVar17 = (byte)puVar1[0x1ca8] - 1;
        
		// numPlyrCurrGame > 0
		if (-1 < iVar17) 
		{
		  // InstDrawPerPlayer = Instance -> InstDrawPerPlayer[iVar17]
          iVar9 = iVar17 * 0x88 + iVar19;
          
		  // loop for all players
		  do 
		  {
			// flags?
            puVar1 = (undefined *)(iVar9 + 0xb8);
			
			// next InstDrawPerPlayer
            iVar9 = iVar9 + -0x88;
			
            iVar5 = uVar6 + iVar17;
            iVar17 = iVar17 + -1;
            *(undefined *)(iVar5 + 0x1c) = *puVar1;
          } while (-1 < iVar17);
        }
		
		// PlayerX, quadblockHeight+3, PlayerZ
        *(short *)(puVar15 + 0xe) = (short)((uint)*(undefined4 *)(iVar11 + 0x2d4) >> 8);
        *(short *)(puVar15 + 0x10) = (short)((uint)*(undefined4 *)(iVar11 + 0x2d0) >> 8) + 3;
        *(short *)(puVar15 + 0x12) = (short)((uint)*(undefined4 *)(iVar11 + 0x2dc) >> 8);
        
		if ((*(ushort *)(puVar15 + 0x14) & 0x2000) == 0) {
          cVar2 = *(char *)(iVar19 + 0x50);
        }
        else {
          cVar2 = *(char *)(iVar19 + 0x51);
        }
        puVar15[1] = cVar2 + '\x01';
      }
      *puVar15 = 0;
      puVar1 = PTR_DAT_8008d2ac;
	  
	  // increment loop iteration counter
      iVar4 = iVar4 + 1;
	  
      puVar15 = puVar15 + 0x28;
      uVar21 = uVar6 + 0x28;
    } while (iVar4 < 8);
    
	*(undefined4 *)(uVar6 + 0x3c) = 0;
	
	// numPlyrCurrGame - 1
    iVar4 = (byte)puVar1[0x1ca8] - 1;
	
	// loop through all player screens
    if (-1 < iVar4) 
	{
      iVar11 = -1;
      r0_00 = (SVECTOR *)(puVar23 + 0x12);
      uVar21 = 1;
	  
	  // pushBuffer offset 0x38
      puVar26 = (undefined2 *)(puVar1 + iVar4 * 0x110 + 0x1a0);
	  
      do {
        puVar23[0x90] = *(uint *)(puVar26 + -0x10);
        puVar23[0x8f] = *(uint *)(puVar26 + 0x5e);
		
		// screen dimensions
        gte_SetGeomOffset((int)((uint)(ushort)puVar26[-0xc] << 0x10) >> 0x11,
                          (int)((uint)(ushort)puVar26[-0xb] << 0x10) >> 0x11);
						  
		// distToScreen
        gte_ldH(puVar23[0x90]);
		
        puVar23[0x24] = *(uint *)(puVar26 + 0x22);
        puVar23[0x25] = *(uint *)(puVar26 + 0x24);
        puVar23[0x26] = *(uint *)(puVar26 + 0x26);
        puVar23[0x14] = *(uint *)(puVar26 + -8);
        puVar23[0x15] = *(uint *)(puVar26 + -6);
        puVar23[0x16] = *(uint *)(puVar26 + -4);
        uVar6 = *(uint *)(puVar26 + -2);
        *(undefined2 *)(puVar23 + 0x18) = *puVar26;
        puVar23[0x17] = uVar6;
		
        gte_SetRotMatrix((MATRIX *)(puVar23 + 0x14));
        
		puVar12 = puVar23 + 0x29;
        uVar6 = puVar23[0x2e];
        if (uVar6 != 0) {
          puVar22 = puVar23 + 0x2e;
          do {
            if (*(char *)((int)puVar22 + -2) != iVar11) {
              if ((*(ushort *)((int)puVar22 + 0x12) & 0x80) == 0) {
                if ((*(byte *)((int)puVar12 + iVar4 + 0x1c) & 0x40) != 0) {
                  uVar3 = *(ushort *)(puVar22 + 3);
                  *(short *)(puVar23 + 0x27) =
                       (short)((uint)uVar3 - (uint)*(ushort *)(puVar23 + 0x24)) * 4;
                  iVar9 = (int)(((uint)uVar3 - (uint)*(ushort *)(puVar23 + 0x24)) * 0x40000) >> 0x10
                  ;
                  iVar17 = (uint)*(ushort *)((int)puVar22 + 0xe) - (uint)*(ushort *)(puVar23 + 0x25)
                  ;
                  *(short *)((int)puVar23 + 0x9e) = (short)iVar17 * 4;
                  iVar19 = iVar17 * 0x40000 >> 0x10;
                  iVar17 = (int)(((uint)*(ushort *)(puVar22 + 4) - (uint)*(ushort *)(puVar23 + 0x26)
                                 ) * 0x40000) >> 0x10;
                  *(short *)(puVar23 + 0x28) =
                       (short)((uint)*(ushort *)(puVar22 + 4) - (uint)*(ushort *)(puVar23 + 0x26)) *
                       4;
                  uVar7 = (uint)((int)puVar23[0x90] < 0x101);
                  if ((uVar7 == 0) ||
                     ((((iVar9 < 0x1771 && (iVar19 < 0x1771)) &&
                       ((iVar17 < 0x1771 && ((-0x1771 < iVar9 && (-0x1771 < iVar19)))))) &&
                      (-0x1771 < iVar17)))) {
                    gte_ldv0((SVECTOR *)(puVar23 + 0x27));
                    gte_rtv0();
                    iVar5 = gte_stMAC3();
                    iVar5 = iVar5 >> 2;
                    if (-0x35 < iVar5) {
                      if (uVar7 == 0) {
                        uVar7 = 0x2e1f1f1f;
                      }
                      else {
                        if (iVar5 < 0x180) {
                          uVar7 = 0x1f;
                        }
                        else 
						{
						  // asm address 8005bb04,
						  // changing 0x200 to 0x800, increases
						  // the render distance of shadows
                          iVar5 = (0x200 - iVar5) * 0x1f;
						  
                          if (iVar5 < 0) {
                            iVar5 = iVar5 + 0x7f;
                          }
                          
						  uVar7 = iVar5 >> 7;
                          
						  // skip shadow draw
						  if ((int)uVar7 < 1) goto LAB_8005c0b8;
                        }
                        uVar7 = uVar7 | uVar7 << 8 | 0x2e000000 | uVar7 << 0x10;
                      }
                      puVar25 = puVar12;
                      if (*(char *)((int)puVar22 + -2) == '\0') 
					  {
						// player height, minus quadblock height
                        iVar17 = 0x100 - (*(int *)(uVar6 + 0x2d8) - *(int *)(uVar6 + 0x2d0) >> 8);
                        
						// if driver is too far from ground, skip shadow draw
						if ((iVar17 < 1) || (0x109 < iVar17)) goto LAB_8005bb94;
						
                        r0 = (MATRIX *)(puVar23 + 0x1c);
                        if (0x100 < iVar17) {
                          iVar17 = 0x100;
                        }
                        iVar19 = (int)*(short *)(uVar6 + 0x2ee);
                        *(int *)(puVar27 + 0x10) = iVar11;
                        *(uint *)(puVar27 + 0x14) = uVar21;
                        *(SVECTOR **)(puVar27 + 0x18) = r0_00;
                        pMVar10 = r0;
						
						// VehPhysForce_RotAxisAngle
                        FUN_8005f89c(r0,uVar6 + 0x370);
						
                        gte_SetLightMatrix(r0);
                        
						// loop counter
						uVar6 = 0;
						
                        iVar20 = iVar17 * 0x29 >> 6;
                        iVar5 = iVar17 * 0x34 >> 6;
                        *(short *)(puVar23 + 0x12) = (short)(iVar17 * 0x28 >> 6);
                        *(undefined2 *)((int)puVar23 + 0x4a) = 0;
                        *(undefined2 *)(puVar23 + 0x13) = 0;
                        r0_00 = *(SVECTOR **)(puVar27 + 0x18);
                        uVar21 = *(uint *)(puVar27 + 0x14);
                        iVar11 = *(int *)(puVar27 + 0x10);
                        puVar25 = puVar12;
						
						// for uVar6 = 0; uVar6 < 3; uVar6++
                        do 
						{
                          gte_ldv0(r0_00);
                          gte_llv0();
                          if (uVar6 == 0) {
                            *(undefined2 *)(puVar23 + 0x12) = 0;
                            *(short *)(puVar23 + 0x13) = (short)iVar20;
                          }
                          else if (uVar6 == uVar21) {
                            *(short *)(puVar23 + 0x13) = (short)iVar5;
                          }
                          read_mt(iVar9,iVar19,pMVar10);
                          *(short *)puVar12 = (short)iVar9;
                          *(short *)((int)puVar12 + 2) = (short)iVar19;
                          *(short *)(puVar12 + 1) = (short)pMVar10;
						  
						  // increment loop counter
                          uVar6 = uVar6 + 1;
						  
                          puVar12 = (uint *)((int)puVar12 + 6);
                        
						} while ((int)uVar6 < 3);
						
                        gte_SetRotMatrix((MATRIX *)(puVar23 + 0x14));
						
                        sVar8 = *(short *)(puVar23 + 0x27);
                        sVar14 = *(short *)((int)puVar23 + 0x9e);
                        sVar18 = *(short *)(puVar23 + 0x28);
                        *(char *)((int)puVar22 + -2) = (char)uVar21;
                        iVar9 = (int)sVar8;
                        iVar19 = (int)sVar14;
                        iVar17 = (int)sVar18;
                      }
                      sVar18 = (short)iVar9;
                      *(short *)(puVar23 + 0x83) = sVar18;
                      sVar14 = (short)iVar19;
                      *(short *)((int)puVar23 + 0x20e) = sVar14;
                      sVar8 = (short)iVar17;
                      *(short *)(puVar23 + 0x84) = sVar8;
                      *(short *)(puVar23 + 0x85) =
                           (sVar18 - *(short *)puVar25) - *(short *)((int)puVar22 + -0xe);
                      *(short *)((int)puVar23 + 0x216) =
                           (sVar14 - *(short *)((int)puVar22 + -0x12)) - *(short *)(puVar22 + -3);
                      *(short *)(puVar23 + 0x86) =
                           (sVar8 - *(short *)(puVar22 + -4)) - *(short *)((int)puVar22 + -10);
                      iVar5 = 0;
                      *(short *)(puVar23 + 0x87) = sVar18 - *(short *)((int)puVar22 + -0xe);
                      iVar20 = 0x24;
                      *(short *)((int)puVar23 + 0x21e) = sVar14 - *(short *)(puVar22 + -3);
                      *(short *)(puVar23 + 0x88) = sVar8 - *(short *)((int)puVar22 + -10);
                      puVar24 = puVar23;
                      do {
                        gte_ldv3c((SVECTOR *)(puVar24 + 0x83));
                        gte_rtpt();
                        sVar8 = (short)iVar9;
                        sVar14 = (short)iVar19;
                        sVar18 = (short)iVar17;
                        if (iVar5 == 0) {
                          *(short *)(puVar24 + 0x83) =
                               (*(short *)puVar25 + sVar8) - *(short *)((int)puVar22 + -0xe);
                          *(short *)((int)puVar24 + 0x20e) =
                               (*(short *)((int)puVar22 + -0x12) + sVar14) -
                               *(short *)(puVar22 + -3);
                          *(short *)(puVar24 + 0x84) =
                               (*(short *)(puVar22 + -4) + sVar18) - *(short *)((int)puVar22 + -10);
                          *(short *)(puVar24 + 0x85) = *(short *)puVar25 + sVar8;
                          *(short *)((int)puVar24 + 0x216) =
                               *(short *)((int)puVar22 + -0x12) + sVar14;
                          *(short *)(puVar24 + 0x86) = *(short *)(puVar22 + -4) + sVar18;
                          *(short *)(puVar24 + 0x87) =
                               *(short *)(puVar22 + -2) + *(short *)puVar25 + sVar8;
                          *(short *)((int)puVar24 + 0x21e) =
                               *(short *)((int)puVar22 + -6) +
                               *(short *)((int)puVar22 + -0x12) + sVar14;
                          *(short *)(puVar24 + 0x88) =
                               *(short *)(puVar22 + -1) + *(short *)(puVar22 + -4) + sVar18;
                        }
                        else if (iVar5 == 3) {
                          *(short *)(puVar24 + 0x83) = *(short *)(puVar22 + -2) + sVar8;
                          *(short *)((int)puVar24 + 0x20e) = *(short *)((int)puVar22 + -6) + sVar14;
                          *(short *)(puVar24 + 0x84) = *(short *)(puVar22 + -1) + sVar18;
                          *(short *)(puVar24 + 0x85) =
                               *(short *)(puVar22 + -2) + (sVar8 - *(short *)puVar25);
                          *(short *)((int)puVar24 + 0x216) =
                               *(short *)((int)puVar22 + -6) +
                               (sVar14 - *(short *)((int)puVar22 + -0x12));
                          *(short *)(puVar24 + 0x86) =
                               *(short *)(puVar22 + -1) + (sVar18 - *(short *)(puVar22 + -4));
                          *(short *)(puVar24 + 0x87) = sVar8 - *(short *)puVar25;
                          *(short *)((int)puVar24 + 0x21e) =
                               sVar14 - *(short *)((int)puVar22 + -0x12);
                          *(short *)(puVar24 + 0x88) = sVar18 - *(short *)(puVar22 + -4);
                        }
                        gte_stsxy3c((long *)puVar23);
                        gte_stsz3c((long *)((int)puVar24 + iVar20));
                        iVar20 = iVar20 + 0xc;
                        iVar5 = iVar5 + 3;
                        puVar23 = puVar23 + 3;
                      } while (iVar5 < 9);
                      uVar6 = 0;
                      puVar16 = puVar28 + 8;
                      do {
                        puVar23 = puVar24 + 0x89;
                        if ((uVar6 & 1) != 0) {
                          puVar23 = puVar24 + 0x8c;
                        }
                        puVar16[-7] = uVar7;
                        puVar16[-5] = *puVar23;
                        puVar16[-3] = puVar23[1];
                        *(undefined2 *)(puVar16 + -1) = *(undefined2 *)(puVar23 + 2);
                        *(undefined2 *)(puVar16 + 1) = *(undefined2 *)((int)puVar23 + 10);
                        if (uVar6 == uVar21) {
                          puVar16[-6] = puVar24[8];
                          puVar16[-4] = *puVar24;
                          puVar16[-2] = puVar24[7];
LAB_8005c044:
                          *puVar16 = puVar24[6];
                        }
                        else if ((int)uVar6 < 2) {
                          if (uVar6 == 0) {
                            puVar16[-6] = puVar24[8];
                            puVar16[-4] = *puVar24;
                            puVar16[-2] = puVar24[1];
                            *puVar16 = puVar24[2];
                          }
                        }
                        else if (uVar6 == 2) {
                          puVar16[-6] = puVar24[4];
                          puVar16[-4] = *puVar24;
                          puVar16[-2] = puVar24[3];
                          *puVar16 = puVar24[2];
                        }
                        else if (uVar6 == 3) {
                          puVar16[-6] = puVar24[4];
                          puVar16[-4] = *puVar24;
                          puVar16[-2] = puVar24[5];
                          goto LAB_8005c044;
                        }
                        iVar19 = ((int)puVar24[9] >> 8) + (int)*(char *)((int)puVar22 + -1);
                        iVar17 = iVar19;
                        if (iVar19 < 0) {
                          iVar17 = 0;
                        }
                        if (0x3ff < iVar19) {
                          iVar17 = 0x3ff;
                        }
                        puVar16 = puVar16 + 10;
                        uVar6 = uVar6 + 1;
                        uVar13 = (uint)puVar28 & 0xffffff;
                        puVar23 = (uint *)(puVar24[0x8f] + iVar17 * 4);
                        *puVar28 = *puVar23 | 0x9000000;
                        puVar28 = puVar28 + 10;
                        *puVar23 = uVar13;
                        puVar23 = puVar24;
                        puVar12 = puVar25;
                      } while ((int)uVar6 < 4);
                    }
                  }
                }
              }
              else {
LAB_8005bb94:
                *(char *)((int)puVar22 + -2) = (char)iVar11;
              }
            }
LAB_8005c0b8:
            puVar22 = puVar22 + 10;
            uVar6 = *puVar22;
            puVar12 = puVar12 + 10;
          } while (uVar6 != 0);
        }
        iVar4 = iVar4 + -1;
        puVar26 = puVar26 + -0x88;
      } while (-1 < iVar4);
    }
	
	// backBuffer->primMem.curr
    *(uint **)(*(int *)(PTR_DAT_8008d2ac + 0x10) + 0x80) = puVar28;
  }
  return;
}


// VehGroundSkids_Subset1
void FUN_8005c120(uint *param_1,uint *param_2,int param_3,int param_4)

{
  undefined *puVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  uint *puVar5;
  uint *puVar6;

  puVar1 = PTR_DAT_8008d2ac;

  // gGT->backDB
  iVar3 = *(int *)(PTR_DAT_8008d2ac + 0x10);

  // primMem.curr
  puVar6 = *(uint **)(iVar3 + 0x80);

  // if there is room to draw
  if (puVar6 + 0xd <= *(uint **)(iVar3 + 0x84))
  {
    
	// primMem.curr += 0x34
	*(uint **)(iVar3 + 0x80) = puVar6 + 0xd;
	
    puVar6[1] = *(uint *)(param_4 + 0x1c);
    puVar6[4] = *(uint *)(param_4 + 0x1c);
    puVar6[7] = *(uint *)(param_4 + 0x20);
    puVar6[10] = *(uint *)(param_4 + 0x20);
    puVar6[2] = *param_1;
    puVar6[5] = param_1[1];
    puVar6[8] = *param_2;
    puVar6[0xb] = param_2[1];
	
	// gGT->0x1fa8 = gGT->0x1eec[0x2f*4] = skidmark
	
    puVar6[3] = *(uint *)(*(int *)(puVar1 + 0x1fa8) + 0x14);
    if ((*(uint *)(param_4 + 0x24) & 1) == 0) {
      uVar2 = *(uint *)(*(int *)(puVar1 + 0x1fa8) + 0x18);
      uVar4 = 0x400000;
    }
    else {
      uVar2 = *(uint *)(*(int *)(puVar1 + 0x1fa8) + 0x18);
      uVar4 = 0x600000;
    }
    puVar6[6] = uVar2 & 0xff9fffff | uVar4;
    puVar1 = PTR_DAT_8008d2ac;
    *(undefined2 *)(puVar6 + 9) = *(undefined2 *)(*(int *)(PTR_DAT_8008d2ac + 0x1fa8) + 0x1c);
    *(undefined2 *)(puVar6 + 0xc) = *(undefined2 *)(*(int *)(puVar1 + 0x1fa8) + 0x1e);
    puVar5 = (uint *)(*(int *)(*(int *)(param_4 + 0x18) + 0xf4) + (param_3 >> 6) * 4);
    *puVar6 = *puVar5 | 0xc000000;
    *puVar5 = (uint)puVar6 & 0xffffff;
  }
  return;
}


// VehGroundSkids_Subset2
void FUN_8005c278(short *param_1,short *param_2,short *param_3,short *param_4)

{
  *param_1 = (*param_2 - param_1[0x5c]) * 4;
  param_1[1] = (param_2[1] - param_1[0x5e]) * 4;
  param_1[2] = (param_2[2] - param_1[0x60]) * 4;
  param_1[4] = (*param_3 - param_1[0x5c]) * 4;
  param_1[5] = (param_3[1] - param_1[0x5e]) * 4;
  param_1[6] = (param_3[2] - param_1[0x60]) * 4;
  param_1[8] = (*param_4 - param_1[0x5c]) * 4;
  param_1[9] = (param_4[1] - param_1[0x5e]) * 4;
  param_1[10] = (param_4[2] - param_1[0x60]) * 4;
  return;
}


// VehGroundSkids_Main
// param_1 - thread pointer (player or robot)
// param_2 - pushBuffer pointer
void FUN_8005c354(undefined4 param_1,int param_2)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  SVECTOR *pSVar6;
  SVECTOR *pSVar7;
  SVECTOR *r0;
  SVECTOR *pSVar8;
  SVECTOR *r0_00;
  uint uVar9;
  SVECTOR *pSVar10;
  undefined *puVar11;
  uint uVar12;
  undefined auStack64 [24];
  
  puVar11 = auStack64;
  
  // window dimensions
  gte_SetGeomOffset((int)((uint)*(ushort *)(param_2 + 0x20) << 0x10) >> 0x11,
                    (int)((uint)*(ushort *)(param_2 + 0x22) << 0x10) >> 0x11);
	
  // distance to screen	
  gte_ldH(*(undefined4 *)(param_2 + 0x18));
  
  r0 = (SVECTOR *)&DAT_1f800000;
  DAT_1f8000b8 = 0;
  DAT_1f8000bc = 0;
  DAT_1f8000c0 = 0;
  DAT_1f800018 = param_2;
  
  // pushBuffer offset 0x28, ViewProj
  gte_SetRotMatrix((MATRIX *)(param_2 + 0x28));
  gte_SetTransVector((VECTOR *)&DAT_1f8000b8);
  
  *(undefined4 *)(r0 + 0x17) = *(undefined4 *)(param_2 + 0x7c);
  *(undefined4 *)&r0[0x17].vz = *(undefined4 *)(param_2 + 0x80);
  *(undefined4 *)(r0 + 0x18) = *(undefined4 *)(param_2 + 0x84);
  
  // this is "somehow" param_1 (thread)
  iVar5 = *(int *)(puVar11 + 0x40);
  
  do {
    if (iVar5 == 0) {
      return;
    }
	
	// thread -> object
    iVar5 = *(int *)(*(int *)(puVar11 + 0x40) + 0x30);
	
    *(int *)(puVar11 + 0x10) = iVar5;
	
	// if skidmarks are enabled...
	// will be enabled for 7 frames after drift stops,
	// because of how the bit shifting works
    uVar9 = *(uint *)(iVar5 + 0x2c4);
	
	// if skidmarks are enabled
    if (0xf < uVar9) {
      uVar12 = 0;
      pSVar7 = r0 + 5;
      pSVar6 = r0 + 0xe;
      pSVar10 = (SVECTOR *)&r0[9].vz;
      uVar1 = *(byte *)(iVar5 + 0xc3) - 1 & 7;
      *(uint *)(puVar11 + 0x14) = uVar1;
      iVar5 = iVar5 + uVar1 * 0x40;
      iVar2 = (int)*(short *)(iVar5 + 0xc4) - *(int *)(r0 + 0x17);
      iVar4 = iVar2 * 4;
      iVar3 = iVar4;
      if (iVar4 < 0) {
        iVar3 = iVar2 * -4;
      }
      pSVar8 = (SVECTOR *)&r0[0x12].vz;
      if (iVar3 < 0x1771) {
        r0->vx = (short)iVar4;
        iVar2 = (int)*(short *)(iVar5 + 0xc6) - *(int *)&r0[0x17].vz;
        iVar4 = iVar2 * 4;
        iVar3 = iVar4;
        if (iVar4 < 0) {
          iVar3 = iVar2 * -4;
        }
        if (iVar3 < 0x1771) {
          r0->vy = (short)iVar4;
          iVar3 = (int)*(short *)(iVar5 + 200) - *(int *)(r0 + 0x18);
          iVar2 = iVar3 * 4;
          iVar5 = iVar2;
          if (iVar2 < 0) {
            iVar5 = iVar3 * -4;
          }
          if (iVar5 < 0x1771) {
            r0->vz = (short)iVar2;
            gte_ldv0(r0);
            gte_rtv0();
            iVar5 = gte_stMAC3();
            if (iVar5 >> 2 < 0x180) {
              uVar1 = 0x7f;
            }
            else {
              gte_ldLZCS((iVar5 >> 2) + -0x180);
              iVar5 = gte_stLZCR();
              uVar1 = 0x1a - iVar5;
              if ((int)uVar1 < 0) {
                uVar1 = 0;
              }
              uVar1 = 0x7f >> (uVar1 & 0x1f);
              if ((int)uVar1 < 0x10) goto LAB_8005c9dc;
            }
            *(uint *)&r0[3].vz = uVar1 | uVar1 << 8 | 0x3e000000 | uVar1 << 0x10;
            *(undefined4 *)(r0 + 4) = 0xffffffff;
            do {
              uVar1 = uVar9;
              r0_00 = pSVar7;
              pSVar7 = pSVar6;
              if (uVar1 == 0) break;
              if ((uVar1 & 0xf) != 0) 
			  {
                iVar3 = *(int *)(puVar11 + 0x14) * 0x40;
                iVar5 = *(int *)(puVar11 + 0x10) + iVar3 + 0xc4;
                
				FUN_8005c278(r0,iVar5,iVar5 + 8,iVar5 + 0x10);
                gte_ldv3c(r0);
                gte_rtpt();
				
                FUN_8005c278(r0,iVar5 + 0x18,iVar5 + 0x20,iVar5 + 0x28);
                gte_stsxy3c((long *)r0_00);
                gte_stsz3c((long *)pSVar7);
                gte_ldv3c(r0);
                gte_rtpt();
                
				FUN_8005c278(r0,iVar5 + 0x30,iVar5 + 0x38,iVar5);
                gte_stsxy3c((long *)&r0_00[1].vz);
                gte_stsz3c((long *)&pSVar7[1].vz);
                gte_ldv3c(r0);
                gte_rtpt();
                
				gte_stsxy3c((long *)(r0_00 + 3));
                gte_stsz3c((long *)(pSVar7 + 3));
                
				// skidmark primitive 1/4
				if (((((uVar1 & uVar12 & 1) != 0) && (0x20 < *(int *)pSVar7)) &&
                    (0x20 < *(int *)&pSVar7->vz)) &&
                   ((0x20 < *(int *)pSVar8 && (0x20 < *(int *)&pSVar8->vz)))) 
				{
                  iVar5 = *(int *)(puVar11 + 0x10);
                  *(uint *)&r0[4].vz = (uint)*(byte *)(iVar5 + iVar3 + 0xcb);
                  
				  // draw prim
				  FUN_8005c120(r0_00,pSVar10,
                               (*(int *)pSVar7 >> 2) + (uint)*(byte *)(iVar5 + iVar3 + 0xca) * 0x40,
                               r0);
                }
				
				// skidmark primitive 2/4
                if ((((uVar1 & uVar12 & 2) != 0) && (0x20 < *(int *)(pSVar7 + 1))) &&
                   ((0x20 < *(int *)&pSVar7[1].vz &&
                    ((0x20 < *(int *)(pSVar8 + 1) && (0x20 < *(int *)&pSVar8[1].vz)))))) 
				{
                  iVar5 = *(int *)(puVar11 + 0x14);
                  iVar3 = *(int *)(puVar11 + 0x10);
                  *(uint *)&r0[4].vz = (uint)*(byte *)(iVar3 + iVar5 * 0x40 + 0xdb);
                  
				  // draw prim
				  FUN_8005c120(r0_00 + 1,pSVar10 + 1,
                               (*(int *)(pSVar7 + 1) >> 2) +
                               (uint)*(byte *)(iVar3 + iVar5 * 0x40 + 0xda) * 0x40,r0);
                }
				
				// skidmark primitive 3/4
                if (((((uVar1 & uVar12 & 4) != 0) && (0x20 < *(int *)(pSVar7 + 2))) &&
                    (0x20 < *(int *)&pSVar7[2].vz)) &&
                   ((0x20 < *(int *)(pSVar8 + 2) && (0x20 < *(int *)&pSVar8[2].vz)))) 
				{
                  iVar5 = *(int *)(puVar11 + 0x14);
                  iVar3 = *(int *)(puVar11 + 0x10);
                  *(uint *)&r0[4].vz = (uint)*(byte *)(iVar3 + iVar5 * 0x40 + 0xeb);
                  
				  // draw prim
				  FUN_8005c120(r0_00 + 2,pSVar10 + 2,
                               (*(int *)(pSVar7 + 2) >> 2) +
                               (uint)*(byte *)(iVar3 + iVar5 * 0x40 + 0xea) * 0x40,r0);
                }
				
				// skidmark primitive 4/4
                if ((((uVar1 & uVar12 & 8) != 0) && (0x20 < *(int *)(pSVar7 + 3))) &&
                   ((0x20 < *(int *)&pSVar7[3].vz &&
                    ((0x20 < *(int *)(pSVar8 + 3) && (0x20 < *(int *)&pSVar8[3].vz)))))) 
				{
                  iVar5 = *(int *)(puVar11 + 0x14);
                  iVar3 = *(int *)(puVar11 + 0x10);
                  *(uint *)&r0[4].vz = (uint)*(byte *)(iVar3 + iVar5 * 0x40 + 0xfb);
				  
				  // draw prim
                  FUN_8005c120(r0_00 + 3,pSVar10 + 3,
                               (*(int *)(pSVar7 + 3) >> 2) +
                               (uint)*(byte *)(iVar3 + iVar5 * 0x40 + 0xfa) * 0x40,r0);
                }
              }
              *(uint *)(puVar11 + 0x14) = *(int *)(puVar11 + 0x14) + 1U & 7;
              if (*(int *)(r0 + 4) == -1) {
                *(undefined4 *)(r0 + 4) = *(undefined4 *)&r0[3].vz;
                uVar9 = uVar1;
                uVar1 = 0xf;
              }
              else {
                uVar9 = uVar1 >> 4;
                uVar12 = (int)(*(uint *)&r0[3].vz & 0xff) >> 1;
                *(undefined4 *)(r0 + 4) = *(undefined4 *)&r0[3].vz;
                *(uint *)&r0[3].vz = uVar12 | uVar12 << 8 | 0x3e000000 | uVar12 << 0x10;
              }
              pSVar6 = pSVar8;
              pSVar8 = pSVar7;
              pSVar7 = pSVar10;
              pSVar10 = r0_00;
              uVar12 = uVar1;
            } while (*(int *)(r0 + 4) != 0);
          }
        }
      }
    }
LAB_8005c9dc:

	// thread = thread -> next
    iVar5 = *(int *)(*(int *)(puVar11 + 0x40) + 0x10);
    *(int *)(puVar11 + 0x40) = iVar5;
	
  } while( true );
}


// VehLap_UpdateProgress (param1=driver)
void FUN_8005ca24(int param_1)

{
  ushort uVar1;
  undefined *puVar2;
  undefined4 in_zero;
  undefined4 in_at;
  undefined4 uVar3;
  undefined4 uVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  short *psVar8;
  int iVar9;
  short *psVar10;
  ushort uVar11;
  int iVar12;
  undefined4 local_30;
  undefined4 local_20;
  uint local_1c;

  // if player structure is not nullptr
  if (param_1 != 0)
  {
    uVar11 = 0xffff;

	// If this is human and not an AI
    if ((*(uint *)(param_1 + 0x2c8) & 0x100000) == 0)
	{
	  // quadblock (last valid)
      iVar7 = *(int *)(param_1 + 0x354);

      if (
			// if quadblock exists
			(iVar7 != 0) &&

			// quadBlock -> checkpointIndex is valid
			(*(char *)(iVar7 + 0x3e) != -1)
		 )
	  {
		// quadblock -> checkpointIndex
        uVar11 = (ushort)*(byte *)(iVar7 + 0x3e);
      }
    }

	// If this is an AI
    else
	{
	  // duplicate of quadblock checkpointIndex (AI-exclusive)
      uVar11 = (ushort)*(byte *)(param_1 + 0x60a);
    }

	// if level has respawn points
    if ((*(int *)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0x148) - 1U < 0xff) &&

	   // checkpointIndex is valid
	   (-1 < (int)(short)uVar11))
	{
	  // array of respawn points
      iVar7 = *(int *)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0x14c);

	  // byte offset of respawn point from last-valid quadblock
      iVar12 = iVar7 + (int)(short)uVar11 * 0xc;

	  // pointer to desired respawn point
	  psVar10 = (short *)(iVar7 + (uint)*(byte *)(iVar12 + 8) * 0xc);

	  // Player X, Y, and Z
      uVar3 = *(undefined4 *)(param_1 + 0x2d4);
      uVar4 = *(undefined4 *)(param_1 + 0x2d8);
      uVar5 = *(uint *)(param_1 + 0x2dc);

      psVar8 = (short *)(iVar7 + (uint)*(byte *)(psVar10 + 4) * 0xc);
      local_20 = CONCAT22(psVar10[1] - psVar8[1],*psVar10 - *psVar8);
      local_1c = local_1c & 0xffff0000 | (uint)(ushort)(psVar10[2] - psVar8[2]);

	  // MATH_VectorNormalize
	  FUN_8003d378(&local_20);

      local_30 = CONCAT22((short)((uint)uVar4 >> 8) - psVar10[1],
                          (short)((uint)uVar3 >> 8) - *psVar10);
      gte_ldR11R12(local_30);
      gte_ldR13R21((uint)(ushort)((short)((uint)uVar5 >> 8) - psVar10[2]) |
                     ((int)((uint)*(ushort *)(param_1 + 0x314) << 0x10) >> 0x15) << 0x10);
      gte_ldR22R23((int)((uint)*(ushort *)(param_1 + 0x31a) << 0x10) >> 0x15 & 0xffffU |
                     ((int)((uint)*(ushort *)(param_1 + 800) << 0x10) >> 0x15) << 0x10);
      gte_ldv0(&local_20);
      gte_mvmva(0,0,0,3,0);

      iVar7 = gte_stMAC1();
      iVar9 = gte_stMAC2();
      iVar6 = (uint)(ushort)psVar10[3] * 8 + (iVar7 >> 0xc);

	  // set new progress
      *(int *)(param_1 + 0x488) = iVar6;

	  puVar2 = PTR_DAT_8008d2ac;
	  uVar1 = *(ushort *)(*(int *)(*(int *)(puVar2 + 0x160) + 0x14c) + 6);
      iVar7 = (uint)uVar1 << 3;
      if (uVar1 == 0) {
        trap(0x1c00);
      }
      if ((iVar7 == -1) && (iVar6 == -0x80000000)) {
        trap(0x1800);
      }

	  // set new progress
      *(int *)(param_1 + 0x488) = iVar6 % iVar7;

	  if (iVar9 < 0x5a801) {
        //uVar5 = Actions Flag set with 9th bit off
        uVar5 = *(uint *)(param_1 + 0x2c8) & 0xfffffeff;
      }
      else {
        //uVar5 = Actions Flag set with 9th bit on
        uVar5 = *(uint *)(param_1 + 0x2c8) | 0x100;
      }

	  //manage 9th bit of Actions Flag set
      *(uint *)(param_1 + 0x2c8) = uVar5;

      //if 28th bit of Actions Flag set is on (means ?) and
      if (((*(uint *)(param_1 + 0x2c8) & 0x8000000) != 0) &&
         ((uint)*(byte *)(param_1 + 0x495) != (int)(short)uVar11))
	  {
		// save respawn index
        *(undefined *)(param_1 + 0x494) = (char)uVar11;

		//turn off 28th bit of Actions Flag set (means ?)
        *(uint *)(param_1 + 0x2c8) = *(uint *)(param_1 + 0x2c8) & 0xf7ffffff;
      }
      if (*(char *)(iVar12 + 9) != -1) {
        //turn on 28th bit of Actions Flag set (means ?)
        *(uint *)(param_1 + 0x2c8) = *(uint *)(param_1 + 0x2c8) | 0x8000000;
      }

	  // checkpointIndex
      *(undefined *)(param_1 + 0x495) = (char)uVar11;
    }
  }
  return;
}

// VehPhysCrash_ConvertVecToSpeed
// param_1: &driver
// param_2: velocityXYZs
void FUN_8005cd1c(int param_1,int *param_2)

{
  undefined2 extraout_var;
  short extraout_var_00;
  short extraout_var_01;
  long x;
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;

  // 2D movement
  // x = sqrt(x2+z2 << 0x10)
  x = FUN_80059070(*param_2 * *param_2 + param_2[2] * param_2[2], 0x10);

  // 3D movement
  // sqrt(x2+y2+z2 << 0x10)
  FUN_80059070(*param_2 * *param_2 + param_2[1] * param_2[1] + param_2[2] * param_2[2],0x10);

  // Ghidra missed this!
  // extraout_var = FUN_80059070(*param_2 * *param_2 + param_2[1] * param_2[1] + param_2[2] * param_2[2],0x10);
  // extraout_var = extraout_var << 0x8;

  // 3D speed
  *(undefined2 *)(param_1 + 0x38c) = extraout_var;
  
  // X speed
  x = ratan2(param_2[1] << 8,x);
  *(undefined2 *)(param_1 + 0x394) = (short)x;
  
  // Z speed
  x = ratan2(*param_2,param_2[2]);
  *(undefined2 *)(param_1 + 0x396) = (short)x;
  
  iVar4 = *param_2 * (int)*(short *)(param_1 + 0x312) +
          param_2[1] * (int)*(short *)(param_1 + 0x318) +
          param_2[2] * (int)*(short *)(param_1 + 0x31e) >> 0xc;
		  
  iVar1 = (int)*(short *)(param_1 + 0x312) * iVar4 >> 0xc;
  iVar2 = (int)*(short *)(param_1 + 0x318) * iVar4 >> 0xc;
  iVar3 = (int)*(short *)(param_1 + 0x31e) * iVar4 >> 0xc;

  // sqrt(x2+y2+z2 << 0x10)
  FUN_80059070(iVar1 * iVar1 + iVar2 * iVar2 + iVar3 * iVar3,0x10);

  // Ghidra missed this!
  // extraout_var_00 = FUN_80059070(iVar1 * iVar1 + iVar2 * iVar2 + iVar3 * iVar3,0x10);
  // extraout_var_00 = extraout_var_00 << 0x8;

  *(short *)(param_1 + 0x390) = extraout_var_00;
  if (iVar4 < 0) {
    *(short *)(param_1 + 0x390) = -extraout_var_00;
  }
  iVar1 = *param_2 - iVar1;
  iVar2 = param_2[1] - iVar2;
  iVar3 = param_2[2] - iVar3;

  // sqrt(x2+y2+z2 << 0x10)
  FUN_80059070(iVar1 * iVar1 + iVar2 * iVar2 + iVar3 * iVar3,0x10);

  // Ghidra missed this!
  // extraout_var_01 = FUN_80059070(iVar1 * iVar1 + iVar2 * iVar2 + iVar3 * iVar3,0x10);
  // extraout_var_01 = extraout_var_01 << 0x8;

  *(short *)(param_1 + 0x38e) = extraout_var_01;
  if (
		iVar1 * *(short *)(param_1 + 0x314) + 
		iVar2 * *(short *)(param_1 + 0x31a) +
		iVar3 * *(short *)(param_1 + 0x320) 
		< 0
	  ) {
    *(short *)(param_1 + 0x38e) = -extraout_var_01;
  }
  return;
}


// VehPhysCrash_BounceSelf
undefined4 FUN_8005cf64(short *param_1,int *param_2,int *param_3,int param_4)

{
  short sVar1;
  short sVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;

  iVar5 = param_2[1];
  iVar6 = param_2[2];
  iVar8 = (*param_3 - *param_2) * (int)*param_1 + (param_3[1] - iVar5) * (int)param_1[1] +
          (param_3[2] - iVar6) * (int)param_1[2] >> 0xc;
  if (param_4 == 0) {
    if (iVar8 < 0) goto LAB_8005cfdc;
  }
  else {
    if (0 < iVar8) {
LAB_8005cfdc:
      iVar7 = iVar8;
      if (iVar8 < 0) {
        iVar7 = -iVar8;
      }
      if (DAT_8008d9f4 < iVar7) {
        DAT_8008d9f4 = iVar7;
      }
      iVar7 = iVar8 * *param_1 >> 0x1f;
      sVar1 = param_1[1];
      sVar2 = param_1[2];
      iVar3 = iVar8 * sVar1 >> 0x1f;
      iVar4 = iVar8 * sVar2 >> 0x1f;
      *param_3 = ((*param_3 - *param_2) - (((iVar8 * *param_1) / 6 + iVar7 >> 9) - iVar7)) +
                 *param_2;
      iVar5 = ((param_3[1] - iVar5) - (((iVar8 * sVar1) / 6 + iVar3 >> 9) - iVar3)) + param_2[1];
      if ((param_3[1] < iVar5) && (0x3200 < iVar5)) {
        iVar5 = 0x3200;
      }
      param_3[1] = iVar5;
      param_3[2] = ((param_3[2] - iVar6) - (((iVar8 * sVar2) / 6 + iVar4 >> 9) - iVar4)) +
                   param_2[2];
      return 0;
    }
  }
  return 0;
}


// VehPhysCrash_AI
void FUN_8005d0d0(int param_1,int *param_2)

{
  int iVar1;
  int iVar2;

  DAT_8008d9ec = (ushort)*(byte *)(*(int *)(param_1 + 0x5a4) + 6) << 4;
  DAT_8008d9ee = (ushort)*(byte *)(*(int *)(param_1 + 0x5a4) + 7) << 4;
  DAT_8008d9f0 = (ushort)*(byte *)(*(int *)(param_1 + 0x5a4) + 8) << 4;

   // convert 3 rotation shorts into rotation matrix
  FUN_8006c2a4(&DAT_8009ae38,&DAT_8008d9ec);

  DAT_8009ae28 = (int)((uint)DAT_8009ae3c << 0x10) >> 0x14;
  DAT_8009ae2c = (int)((uint)DAT_8009ae42 << 0x10) >> 0x14;
  DAT_8009ae30 = (int)((uint)DAT_8009ae48 << 0x10) >> 0x14;
  iVar1 = DAT_8009ae28 * *param_2 + DAT_8009ae2c * param_2[1] + DAT_8009ae30 * param_2[2] >> 8;
  *(int *)(param_1 + 0x5d4) = iVar1;
  *(int *)(param_1 + 0x5d8) = *param_2 - (DAT_8009ae28 * iVar1 >> 8);
  iVar1 = DAT_8009ae30 * iVar1;
  iVar2 = param_2[2];
  *(uint *)(param_1 + 0x5b0) = *(uint *)(param_1 + 0x5b0) | 8;
  *(int *)(param_1 + 0x5e0) = iVar2 - (iVar1 >> 8);
  return;
}

// VehPhysCrash_Attack
//param_1 = driver pointer
//param_2 = driver pointer
int FUN_8005d218(int param_1,int param_2,int param_3,int param_4)
{
  int iVar1;

  //if driver (1) is not using mask weapon
  if ((*(uint *)(param_1 + 0x2c8) & 0x800000) == 0)
  {
	//if driver (2) is using mask weapon
    if ((*(uint *)(param_2 + 0x2c8) & 0x800000) != 0)
	{
	  // param_1 was hit with a mask weapon
      *(undefined *)(param_1 + 0x4ff) = 2;
      *(undefined *)(param_1 + 0x504) = 6;
      *(int *)(param_1 + 0x500) = param_2;

	  if (((param_3 != 0) && (*(char *)(param_1 + 0x376) != '\x06')) &&
         (*(int *)(param_1 + 0x24) == 0))
	  {
		// OtherFX_DriverCrashing
        FUN_8002e760(

			// if driver is supposed to echo
			(uint)*(ushort *)(param_1 + 0x2ca) & 1,

			0xff
		);

		// Make driver talk
        FUN_8002cbe8(1,(int)(short)(&DAT_80086e84)[*(byte *)(param_1 + 0x4a)],0x10);
      }
    }

	// if one driver has a bubble, and the other does not
	if ((*(int *)(param_2 + 0x14) != 0) && (*(int *)(param_1 + 0x14) == 0))
	{
		// driver -> bubbleInst -> thread -> object
      iVar1 = *(int *)(*(int *)(*(int *)(param_2 + 0x14) + 0x6c) + 0x30);

      *(ushort *)(iVar1 + 6) = *(ushort *)(iVar1 + 6) | 8;

	  // clear bubbleInst pointer
      *(undefined4 *)(param_2 + 0x14) = 0;

      *(undefined *)(param_1 + 0x4ff) = 2;
      *(undefined *)(param_1 + 0x504) = 0;
      *(int *)(param_1 + 0x500) = param_2;

	  if (
			(param_3 != 0) &&

			(
				(
					// if driver is not blasted
					*(char *)(param_1 + 0x376) != '\x06' &&

					// if driver is not invincible
					(*(int *)(param_1 + 0x24) == 0)
				)
			)
		 )
	  {
		// OtherFX_DriverCrashing
        FUN_8002e760(

			// if driver is supposed to echo
			(uint)*(ushort *)(param_1 + 0x2ca) & 1,

			0xff
		);

		if (param_4 != 0)
		{
		  // OtherFX_Play
          FUN_80028468(0x4f,1);
        }

		// Make driver talk
        FUN_8002cbe8(1,(int)(short)(&DAT_80086e84)[*(byte *)(param_1 + 0x4a)],0x10);
      }
    }

	// if one driver squished the other with turbo
    if (
		(
			(
				// force that the drivers collided is high
				(0xa00 < DAT_8008d9f4) && 
				
				// attacking driver has reserves
				(*(short *)(param_2 + 0x3e2) != 0)
			) &&
      
			// attacking driver is using turbo weapon
			((*(uint *)(param_2 + 0x2c8) & 0x200) != 0)
		) && 
		
		// attacked driver has no reserves
		(*(short *)(param_1 + 0x3e2) == 0)
	  ) 
	{
	  // set forcedJump_trampoline on attacking driver
      *(undefined *)(param_2 + 0x366) = 2;
	  
	  // attacked driver has been squished by attacking driver,
	  // this happens when one driver uses turbo weapon on another
      *(undefined *)(param_1 + 0x4ff) = 3;
      *(undefined *)(param_1 + 0x504) = 5;
      *(int *)(param_1 + 0x500) = param_2;
    }
  }
  return param_3;
}

// VehPhysCrash_AnyTwoCars
// pass the thread, collision data, and driver->88 velocityXYZ[] (x, y, z)
// calls Crash_AI and Crash_HumanToHuman
void FUN_8005d404(int param_1,int param_2,int *param_3)

{
  undefined2 uVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  undefined4 uVar9;
  uint uVar10;
  int local_48;
  int local_44;
  int local_40;
  int local_38;
  int local_34;
  int local_30;

  // fast sqrt
  iVar2 = FUN_8003d214(*(undefined4 *)(param_2 + 0xc),0);

  uVar1 = 0x1000;
  if (iVar2 == 0) {
    *(undefined2 *)(param_2 + 0x18) = 0;
    *(undefined2 *)(param_2 + 0x1a) = 0;
  }
  else 
  {
	// distX
    iVar8 = (int)*(short *)(param_2 + 0x10) << 0xc;
    
	// safety check
	if (iVar2 == 0) { trap(0x1c00); }
    if ((iVar2 == -1) && (iVar8 == -0x80000000)) { trap(0x1800); }
	
	// distY
    iVar5 = (int)*(short *)(param_2 + 0x12) << 0xc;
	
	// safety check
    if (iVar2 == 0) { trap(0x1c00); }
    if ((iVar2 == -1) && (iVar5 == -0x80000000)) { trap(0x1800); }
    
	// distZ
	iVar3 = (int)*(short *)(param_2 + 0x14) << 0xc;
    
	// safety check
	if (iVar2 == 0) { trap(0x1c00); }
    if ((iVar2 == -1) && (iVar3 == -0x80000000)) { trap(0x1800); }
	
	// hit direction vector,
	// divide each direction by distance
    uVar1 = (undefined2)(iVar3 / iVar2);
    *(undefined2 *)(param_2 + 0x18) = (short)(iVar8 / iVar2);
    *(undefined2 *)(param_2 + 0x1a) = (short)(iVar5 / iVar2);
  }
  
  // hit direction vector
  *(undefined2 *)(param_2 + 0x1c) = uVar1;
  
  // two driver objects
  iVar8 = *(int *)(*(int *)(param_2 + 8) + 0x30);
  iVar5 = *(int *)(param_1 + 0x30);

  // hit strength
  iVar2 = 
			(
				// driver1 radius
				(int)*(short *)(param_1 + 0x42) +
				
				// driver2 radius
				(int)*(short *)(*(int *)(*(int *)(iVar8 + 0x1c) + 0x6c) + 0x42)
			) 
			
			// minus distance between them
			- iVar2;

  // if hitStrength < 0, drivers dont collide,
  // if hitStrength == 0, drivers touch, but with no force
  // if hitStrength > 0, drivers touch with force
  
  // if drivers hit each other
  if (0 < iVar2)
  {
    DAT_8008d9f4 = 0;

	// If this is human and not AI
    if ((*(uint *)(iVar5 + 0x2c8) & 0x100000) == 0) {
      iVar3 = param_2 + 0x18;

	  // If this (other driver) is human and not AI
      if ((*(uint *)(iVar8 + 0x2c8) & 0x100000) == 0) {
        iVar7 = (int)*(short *)(iVar5 + 0x47c) + (int)*(short *)(iVar8 + 0x47c);
        iVar6 = *param_3 * (int)*(short *)(iVar5 + 0x47c) +
                *(int *)(iVar8 + 0x88) * (int)*(short *)(iVar8 + 0x47c);
        local_38 = iVar6 / iVar7;
        if (iVar7 == 0) {
          trap(0x1c00);
        }
        if ((iVar7 == -1) && (iVar6 == -0x80000000)) {
          trap(0x1800);
        }
        iVar7 = (int)*(short *)(iVar5 + 0x47c) + (int)*(short *)(iVar8 + 0x47c);
        iVar6 = param_3[1] * (int)*(short *)(iVar5 + 0x47c) +
                *(int *)(iVar8 + 0x8c) * (int)*(short *)(iVar8 + 0x47c);
        local_34 = iVar6 / iVar7;
        if (iVar7 == 0) {
          trap(0x1c00);
        }
        if ((iVar7 == -1) && (iVar6 == -0x80000000)) {
          trap(0x1800);
        }
        iVar7 = (int)*(short *)(iVar5 + 0x47c) + (int)*(short *)(iVar8 + 0x47c);
        iVar6 = param_3[2] * (int)*(short *)(iVar5 + 0x47c) +
                *(int *)(iVar8 + 0x90) * (int)*(short *)(iVar8 + 0x47c);
        local_30 = iVar6 / iVar7;
        if (iVar7 == 0) {
          trap(0x1c00);
        }
        if ((iVar7 == -1) && (iVar6 == -0x80000000)) {
          trap(0x1800);
        }

		// VehPhysCrash_BounceSelf
        iVar6 = FUN_8005cf64(iVar3,&local_38,iVar8 + 0x88,1);

        if (iVar6 < 0) {
          DAT_8008d9f4 = 0;
        }

		// VehPhysCrash_BounceSelf
		iVar3 = FUN_8005cf64(iVar3,&local_38,param_3,0);

        if (0 < iVar3) {
          DAT_8008d9f4 = 0;
        }
        *param_3 = *param_3 + (*(short *)(param_2 + 0x18) * iVar2 >> 8);
        param_3[1] = param_3[1] + (*(short *)(param_2 + 0x1a) * iVar2 >> 8);
        param_3[2] = param_3[2] + (*(short *)(param_2 + 0x1c) * iVar2 >> 8);
		
		// deduct speed by (dirVec * hitStrength)
        *(int *)(iVar8 + 0x88) = *(int *)(iVar8 + 0x88) - (*(short *)(param_2 + 0x18) * iVar2 >> 8);
        *(int *)(iVar8 + 0x8c) = *(int *)(iVar8 + 0x8c) - (*(short *)(param_2 + 0x1a) * iVar2 >> 8);
        *(int *)(iVar8 + 0x90) = *(int *)(iVar8 + 0x90) - (*(short *)(param_2 + 0x1c) * iVar2 >> 8);
      }

	  // If this (other driver) is an AI
	  else {
        local_48 = *(int *)(iVar8 + 0x3a0) + *(int *)(iVar8 + 0x5d8);
        local_44 = *(int *)(iVar8 + 0x3a4) + *(int *)(iVar8 + 0x5dc);
        local_40 = *(int *)(iVar8 + 0x3a8) + *(int *)(iVar8 + 0x5e0);
        iVar7 = (int)*(short *)(iVar5 + 0x47c) + (int)*(short *)(iVar8 + 0x47c);
        iVar6 = *param_3 * (int)*(short *)(iVar5 + 0x47c) +
                local_48 * (int)*(short *)(iVar8 + 0x47c);
        local_38 = iVar6 / iVar7;
        if (iVar7 == 0) {
          trap(0x1c00);
        }
        if ((iVar7 == -1) && (iVar6 == -0x80000000)) {
          trap(0x1800);
        }
        iVar7 = (int)*(short *)(iVar5 + 0x47c) + (int)*(short *)(iVar8 + 0x47c);
        iVar6 = param_3[1] * (int)*(short *)(iVar5 + 0x47c) +
                local_44 * (int)*(short *)(iVar8 + 0x47c);
        local_34 = iVar6 / iVar7;
        if (iVar7 == 0) {
          trap(0x1c00);
        }
        if ((iVar7 == -1) && (iVar6 == -0x80000000)) {
          trap(0x1800);
        }
        iVar7 = (int)*(short *)(iVar5 + 0x47c) + (int)*(short *)(iVar8 + 0x47c);
        iVar6 = param_3[2] * (int)*(short *)(iVar5 + 0x47c) +
                local_40 * (int)*(short *)(iVar8 + 0x47c);
        local_30 = iVar6 / iVar7;
        if (iVar7 == 0) {
          trap(0x1c00);
        }
        if ((iVar7 == -1) && (iVar6 == -0x80000000)) {
          trap(0x1800);
        }

		// VehPhysCrash_BounceSelf
        iVar6 = FUN_8005cf64(iVar3,&local_38,&local_48,1);

		if (iVar6 < 0) {
          DAT_8008d9f4 = 0;
        }

		// VehPhysCrash_BounceSelf
		iVar3 = FUN_8005cf64(iVar3,&local_38,param_3,0);

		if (0 < iVar3) {
          DAT_8008d9f4 = 0;
        }

		*param_3 = *param_3 + (*(short *)(param_2 + 0x18) * iVar2 >> 8);
        param_3[1] = param_3[1] + (*(short *)(param_2 + 0x1a) * iVar2 >> 8);
        param_3[2] = param_3[2] + (*(short *)(param_2 + 0x1c) * iVar2 >> 8);

        local_48 = local_48 - (*(short *)(param_2 + 0x18) * iVar2 >> 8);
        local_44 = local_44 - (*(short *)(param_2 + 0x1a) * iVar2 >> 8);
        local_40 = local_40 - (*(short *)(param_2 + 0x1c) * iVar2 >> 8);

		// VehPhysCrash_AI
        FUN_8005d0d0(iVar8,&local_48);
      }
      uVar10 = (uint)((uint)(*(int *)(PTR_DAT_8008d2ac + 0x1cf8) - DAT_8008d838) < 3) ^ 1;
      if (0x200 < DAT_8008d9f4)
	  {
		  // thread -> modelIndex == "player" of any kind
        if ((((*(short *)(param_1 + 0x44) == 0x18) ||

			// modelIndex == "player" of any kind
            (*(short *)(*(int *)(param_2 + 8) + 0x44) == 0x18)) &&

            // Map value from [oldMin, oldMax] to [newMin, newMax]
            // inverting newMin and newMax will give an inverse range mapping
            (uVar4 = FUN_80058f9c(DAT_8008d9f4,0,0x1900,0x3f,0xff), uVar10 != 0)) &&
             (
				// if both drivers are not blasted and not invincible
				((*(char *)(iVar5 + 0x376) != '\x06' && (*(int *)(iVar5 + 0x24) == 0)) &&
				((*(char *)(iVar8 + 0x376) != '\x06' && (*(int *)(iVar8 + 0x24) == 0))))
			  )
			)
		{
		  // OtherFX_DriverCrashing
          FUN_8002e760(

				// if driver is supposed to echo
				(uint)*(ushort *)(iVar5 + 0x2ca) & 1,

				uVar4
			);

		  DAT_8008d838 = *(int *)(PTR_DAT_8008d2ac + 0x1cf8);
          if (0xdc < uVar4)
		  {
			// Make driver talk
            FUN_8002cbe8(5,(int)(short)(&DAT_80086e84)[*(byte *)(iVar5 + 0x4a)],0x10);
          }
        }

		// GAMEPAD_ShockFreq and GAMEPAD_ShockForce1
		FUN_80026440(iVar8,8,0);
        FUN_800264c0(iVar8,8,0x7f);

        if (*(char *)(iVar8 + 0x4b) < '\x01') {
          uVar9 = 0x19;
        }
        else {
          uVar9 = 0x29;
        }

		// GAMEPAD_JogCon1
        FUN_800263a0(iVar8,uVar9,0x60);
		
		// GAMEPAD_ShockFreq and GAMEPAD_ShockForce1
        FUN_80026440(iVar5,8,0);
        FUN_800264c0(iVar5,8,0x7f);

        if (*(char *)(iVar5 + 0x4b) < '\x01') {
          uVar9 = 0x19;
        }
        else {
          uVar9 = 0x29;
        }

		// GAMEPAD_JogCon1
        FUN_800263a0(iVar5,uVar9,0x60);

		// flag used in 80062e04
		// Let both human drivers know, they are in a human-human collision
        *(uint *)(iVar5 + 0x2c8) = *(uint *)(iVar5 + 0x2c8) | 0x10000000;
        *(uint *)(iVar8 + 0x2c8) = *(uint *)(iVar8 + 0x2c8) | 0x10000000;
      }
	  
	  // VehPhysCrash_Attack
      uVar9 = FUN_8005d218(iVar5,iVar8,uVar10,0);
      FUN_8005d218(iVar8,iVar5,uVar9,1);
    }

	// If this is an AI
	else
	{
	  // If this (other driver) is human and not AI
      if ((*(uint *)(iVar8 + 0x2c8) & 0x100000) == 0)
	  {
		// VehPhysForce_ConvertSpeedToVec
        FUN_8005e104(iVar8,&local_48);

        iVar6 = (int)*(short *)(iVar5 + 0x47c) + (int)*(short *)(iVar8 + 0x47c);
        iVar3 = *param_3 * (int)*(short *)(iVar5 + 0x47c) +
                local_48 * (int)*(short *)(iVar8 + 0x47c);
        local_38 = iVar3 / iVar6;
        if (iVar6 == 0) {
          trap(0x1c00);
        }
        if ((iVar6 == -1) && (iVar3 == -0x80000000)) {
          trap(0x1800);
        }
        iVar6 = (int)*(short *)(iVar5 + 0x47c) + (int)*(short *)(iVar8 + 0x47c);
        iVar3 = param_3[1] * (int)*(short *)(iVar5 + 0x47c) +
                local_44 * (int)*(short *)(iVar8 + 0x47c);
        local_34 = iVar3 / iVar6;
        if (iVar6 == 0) {
          trap(0x1c00);
        }
        if ((iVar6 == -1) && (iVar3 == -0x80000000)) {
          trap(0x1800);
        }
        iVar6 = (int)*(short *)(iVar5 + 0x47c) + (int)*(short *)(iVar8 + 0x47c);
        iVar3 = param_3[2] * (int)*(short *)(iVar5 + 0x47c) +
                local_40 * (int)*(short *)(iVar8 + 0x47c);
        local_30 = iVar3 / iVar6;
        if (iVar6 == 0) {
          trap(0x1c00);
        }
        if ((iVar6 == -1) && (iVar3 == -0x80000000)) {
          trap(0x1800);
        }

		// VehPhysCrash_BounceSelf
        iVar3 = FUN_8005cf64(param_2 + 0x18,&local_38,&local_48,1);

		if (iVar3 < 0) {
          DAT_8008d9f4 = 0;
        }

		// VehPhysCrash_BounceSelf
		iVar3 = FUN_8005cf64(param_2 + 0x18,&local_38,param_3,0);

		if (0 < iVar3) {
          DAT_8008d9f4 = 0;
        }

		*param_3 = *param_3 + (*(short *)(param_2 + 0x18) * iVar2 >> 8);
        param_3[1] = param_3[1] + (*(short *)(param_2 + 0x1a) * iVar2 >> 8);
        param_3[2] = param_3[2] + (*(short *)(param_2 + 0x1c) * iVar2 >> 8);

		local_48 = local_48 - (*(short *)(param_2 + 0x18) * iVar2 >> 8);
        local_44 = local_44 - (*(short *)(param_2 + 0x1a) * iVar2 >> 8);
        local_40 = local_40 - (*(short *)(param_2 + 0x1c) * iVar2 >> 8);

		// VehPhysCrash_AI
        FUN_8005d0d0(iVar5,param_3);

		// VehPhysCrash_ConvertVecToSpeed
        FUN_8005cd1c(iVar8,&local_48,0);
      }

	   // If this (other driver) is an AI
	  else {
        local_48 = *(int *)(iVar8 + 0x3a0) + *(int *)(iVar8 + 0x5d8);
        local_44 = *(int *)(iVar8 + 0x3a4) + *(int *)(iVar8 + 0x5dc);
        local_40 = *(int *)(iVar8 + 0x3a8) + *(int *)(iVar8 + 0x5e0);
        iVar6 = (int)*(short *)(iVar5 + 0x47c) + (int)*(short *)(iVar8 + 0x47c);
        iVar3 = *param_3 * (int)*(short *)(iVar5 + 0x47c) +
                local_48 * (int)*(short *)(iVar8 + 0x47c);
        local_38 = iVar3 / iVar6;
        if (iVar6 == 0) {
          trap(0x1c00);
        }
        if ((iVar6 == -1) && (iVar3 == -0x80000000)) {
          trap(0x1800);
        }
        iVar6 = (int)*(short *)(iVar5 + 0x47c) + (int)*(short *)(iVar8 + 0x47c);
        iVar3 = param_3[1] * (int)*(short *)(iVar5 + 0x47c) +
                local_44 * (int)*(short *)(iVar8 + 0x47c);
        local_34 = iVar3 / iVar6;
        if (iVar6 == 0) {
          trap(0x1c00);
        }
        if ((iVar6 == -1) && (iVar3 == -0x80000000)) {
          trap(0x1800);
        }
        iVar6 = (int)*(short *)(iVar5 + 0x47c) + (int)*(short *)(iVar8 + 0x47c);
        iVar3 = param_3[2] * (int)*(short *)(iVar5 + 0x47c) +
                local_40 * (int)*(short *)(iVar8 + 0x47c);
        local_30 = iVar3 / iVar6;
        if (iVar6 == 0) {
          trap(0x1c00);
        }
        if ((iVar6 == -1) && (iVar3 == -0x80000000)) {
          trap(0x1800);
        }

		// VehPhysCrash_BounceSelf
        iVar3 = FUN_8005cf64(param_2 + 0x18,&local_38,&local_48,1);

		if (iVar3 < 0) {
          DAT_8008d9f4 = 0;
        }

		// VehPhysCrash_BounceSelf
		iVar3 = FUN_8005cf64(param_2 + 0x18,&local_38,param_3,0);

		if (0 < iVar3) {
          DAT_8008d9f4 = 0;
        }

		*param_3 = *param_3 + (*(short *)(param_2 + 0x18) * iVar2 >> 8);
        param_3[1] = param_3[1] + (*(short *)(param_2 + 0x1a) * iVar2 >> 8);
        param_3[2] = param_3[2] + (*(short *)(param_2 + 0x1c) * iVar2 >> 8);

        local_48 = local_48 - (*(short *)(param_2 + 0x18) * iVar2 >> 8);
        local_44 = local_44 - (*(short *)(param_2 + 0x1a) * iVar2 >> 8);
        local_40 = local_40 - (*(short *)(param_2 + 0x1c) * iVar2 >> 8);

		// VehPhysCrash_AI (twice)
        FUN_8005d0d0(iVar8,&local_48);
        FUN_8005d0d0(iVar5,param_3);

		// pass pointer to two drivers,
		// this is AI-on-AI collision
        FUN_80016ec8(iVar5,iVar8);
      }
    }
  }
  return;
}

// VehPhysForce_ConvertSpeedToVec
// param_1 = &driver
// param_2 = &driver.velocityXYZ
void FUN_8005e104(int param_1,int *param_2)

{
  short sVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  uint uVar6;

  // angle = axisRotationY
  uVar6 = SEXT24(*(short *)(param_1 + 0x394));

  // approximate trigonometry
  // sVar1 = sin(angle)
  sVar1 = (short)*(int *)(&DAT_800845a0 + (uVar6 & 0x3ff) * 4);
  // iVar5 = cos(angle)
  iVar5 = *(int *)(&DAT_800845a0 + (uVar6 & 0x3ff) * 4) >> 0x10;

  if ((uVar6 & 0x400) == 0) {
    iVar2 = (int)sVar1;
    if ((uVar6 & 0x800) != 0) {
      iVar3 = -iVar5;
      goto LAB_8005e15c;
    }
  }
  else {
    iVar3 = (int)sVar1;
    iVar2 = iVar5;
    if ((uVar6 & 0x800) == 0) {
      iVar5 = -iVar3;
    }
    else {
LAB_8005e15c:
      iVar2 = -iVar2;
      iVar5 = iVar3;
    }
  }

  // velocityXYZ[y] = (driver.speed * ???) >> 0xC
  param_2[1] = *(short *)(param_1 + 0x38c) * iVar2 >> 0xc;

  // angle = axisRotationX
  uVar6 = SEXT24(*(short *)(param_1 + 0x396));
  iVar2 = *(short *)(param_1 + 0x38c) * iVar5 >> 0xc;

  // approximate trigonometry
  iVar5 = *(int *)(&DAT_800845a0 + (uVar6 & 0x3ff) * 4) >> 0x10;
  sVar1 = (short)*(int *)(&DAT_800845a0 + (uVar6 & 0x3ff) * 4);

  if ((uVar6 & 0x400) == 0) {
    iVar3 = (int)sVar1;
    if ((uVar6 & 0x800) == 0) goto LAB_8005e1e8;
    iVar4 = -iVar5;
  }
  else {
    iVar4 = (int)sVar1;
    iVar3 = iVar5;
    if ((uVar6 & 0x800) == 0) {
      iVar5 = -iVar4;
      goto LAB_8005e1e8;
    }
  }
  iVar3 = -iVar3;
  iVar5 = iVar4;

LAB_8005e1e8:
  
  // velocityXYZ[x] and velocityXYZ[z]
  *param_2 = iVar2 * iVar3 >> 0xc;
  param_2[2] = iVar2 * iVar5 >> 0xc;
  return;
}


// VehPhysForce_OnGravity (for humans only)
// param1 - driver, param2 - velocityXYZ
void FUN_8005e214(int param_1,VECTOR *param_2)

{
  char cVar1;
  undefined2 uVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  uint uVar12;
  int iVar13;
  uint unaff_s3;
  uint unaff_s5;
  undefined *puVar14;
  int unaff_s8;
  int iVar15;
  int iVar16;
  undefined auStack72 [16];
  
  puVar14 = auStack72;
  
  // driver -> 0x310 matrix
  uVar8 = *(uint *)(param_1 + 0x310);
  uVar7 = *(uint *)(param_1 + 0x314);
  uVar10 = *(uint *)(param_1 + 0x318);
  uVar9 = *(uint *)(param_1 + 0x31c);
  
  // load matrix into GTE
  gte_ldR11R12(uVar8);
  gte_ldR13R21(uVar7);
  gte_ldR22R23(uVar10);
  gte_ldR31R32(uVar9);
  gte_ldR33((int)*(short *)(param_1 + 800)); // 0x320
  
  // transpose matrix
  gte_ldL11L12(uVar8 & 0xffff | uVar7 & 0xffff0000);
  uVar8 = uVar8 & 0xffff0000;
  gte_ldL13L21(uVar9 & 0xffff | uVar8);
  gte_ldL22L23(uVar10 & 0xffff | uVar9 & 0xffff0000);
  uVar7 = uVar7 & 0xffff | uVar10 & 0xffff0000;
  gte_ldL31L32(uVar7);
  gte_ldL33((int)*(short *)(param_1 + 800)); // 0x320
  
  // load vector from param_2
  gte_ldVXY0((uint)*(ushort *)&param_2->vx | param_2->vy << 0x10);
  gte_ldVZ0(param_2->vz);
  gte_llv0();
  
  // these registers hold movement vector,
  // but why does that need driver matrix?
  read_mt(unaff_s5,unaff_s8,unaff_s3);
  
  // driver gravity constant
  iVar3 = -(int)*(short *)(param_1 + 0x416);

  // elapsed milliseconds per frame, ~32
  iVar5 = *(int *)(PTR_DAT_8008d2ac + 0x1d04);
  iVar6 = iVar5;
  
  // If the driver's under-quadblock has moon gravity
  if ((*(ushort *)(*(int *)(param_1 + 0x350) + 0x12) & 2) != 0) 
  {
	// 41% gravity (41 / 100)
    iVar6 = *(short *)(param_1 + 0x416) * -0x29;
    iVar3 = iVar6 >> 0x1f;
    iVar6 = iVar6 / 100 + iVar3;
    iVar3 = iVar6 - iVar3;
  }
  
  // vector = {0, gravity*elapsedMS, 0}
  // matrix = driver orientation (driver->0x310)
  gte_ldVXY0((iVar3 * iVar5 >> 5) << 0x10);
  gte_ldVZ0(0);
  gte_llv0();
  
  // gravity is a vector, not straight down,
  // this causes road grip, and halfpipe physics
  read_mt(uVar7,uVar8,iVar6);
  
  if (((iVar6 < 0) && (0 < *(short *)(param_1 + 0x3b2))) ||
     ((0 < iVar6 && (*(short *)(param_1 + 0x3b2) < 0)))) {
    iVar6 = 0;
  }
  
  // driver flags
  uVar10 = *(uint *)(param_1 + 0x2c8);
  
  iVar3 = (int)*(short *)(param_1 + 0x38e);     // speed approximate magnitude
  uVar9 = (uint)*(short *)(param_1 + 0x39c);	// baseSpeed
  
  if ((((uVar10 & 8) != 0) || ((0 < (int)uVar9 && (iVar3 < 0)))) ||
     (((int)uVar9 < 0 && (0 < iVar3)))) {
    uVar7 = 0;
    iVar6 = 0;
  }
  
  // movementY + gravityY
  iVar15 = unaff_s8 + uVar8;
  
  uVar11 = (int)*(short *)(param_1 + 0x39e) + (int)*(short *)(param_1 + 0x47e);
  uVar8 = unaff_s3 + iVar6;
  if (((int)uVar11 < (int)(unaff_s3 + iVar6)) && (uVar8 = unaff_s3, (int)unaff_s3 < (int)uVar11)) {
    uVar8 = uVar11;
  }
  uVar11 = (int)*(short *)(param_1 + 0x39e) - ((int)*(short *)(param_1 + 0x47e) >> 1);
  if (((int)uVar8 < (int)uVar11) && (uVar8 = unaff_s3, (int)uVar11 < (int)unaff_s3)) {
    uVar8 = uVar11;
  }
  
  uVar12 = (uint)*(short *)(param_1 + 0x480);
  
  // terrainMeta1
  uVar4 = *(uint *)(*(int *)(param_1 + 0x358) + 4);
  
  uVar11 = unaff_s5 + uVar7;
  if (((int)(unaff_s5 + uVar7) <= (int)uVar12) ||
     (uVar11 = uVar12, uVar7 = unaff_s5, (int)unaff_s5 < (int)uVar12)) {
    uVar7 = uVar11;
  }
  uVar12 = -uVar12;
  if (((int)uVar7 < (int)uVar12) && (uVar7 = unaff_s5, (int)uVar12 < (int)unaff_s5)) {
    uVar7 = uVar12;
  }
  
  // const_TerminalVelocity
  iVar6 = (int)*(short *)(param_1 + 0x442);
  
  if (
		(
			// if falling
			(iVar15 < 0) && 
			
			// terrain = zero-gravity
			// in oxide station
			((uVar4 & 0x80) != 0)
			
		) && 
		
		(
			// terminalVelocity
			iVar6 = 0x100, 
			
			// if movementY is less
			unaff_s8 < -0x100)
	 ) 
  {
	// dont let movementY go 
	// below terminalVelocity
    unaff_s8 = -0x100;
  }
  
  if (
		// if totalY is less than terminalVelocity
		(iVar15 <= iVar6) || 
		
		(
			// copy of terminalVelocity
			iVar15 = iVar6, 
			
			// movementY
			iVar16 = unaff_s8, 
			
			// movementY is less than terminalVelocity
			unaff_s8 < iVar6
		)
	) 
  {
	// movementY = terminalVelocity
    iVar16 = iVar15;
  }
  
  // negate terminal velocity and check again,
  // just in case gravity is upside down (scrapped feature)?
  // that or just make sure you dont go upward too fast
  iVar6 = -iVar6;
  if ((iVar16 < iVar6) && (iVar16 = unaff_s8, iVar6 < unaff_s8)) 
  {
	// movementY = max upward terminalVelocity
    iVar16 = iVar6;
  }
  
  // kart state
  cVar1 = *(char *)(param_1 + 0x376);
  
  // if mask grab
  if (cVar1 == '\x05') {
    uVar7 = 0;
    uVar8 = 0;
  }
  
  // if not mask grab
  else if (
			(
				((*(uint *)(param_1 + 0x2cc) & 1) != 0) || 
				
				// blasted
				(cVar1 == '\x06')
			) ||
			(
				(
					*(short *)(param_1 + 0x3c4) < *(short *)(param_1 + 0x38e) &&
					
					// terrainMeta2
					(*(int *)(*(int *)(param_1 + 0x35c) + 8) < 0x100)
				)
			)
		  ) 
  {
	// 2c8 & 8
	// not in accel-prevention,
	// not holding square, etc...
    if ((uVar10 & 8) == 0) 
	{
	  // current baseSpeed is zero,
	  // which includes kart rolling on hill
	  // without gas pedal or reserves
      if (uVar9 == 0) 
	  {
		// const_NoPedalFriction_Perpendicular
        iVar15 = (int)*(short *)(param_1 + 0x41e);
		
		// const_NoPedalFriction_Forward
        iVar6 = (int)*(short *)(param_1 + 0x420);
		
		// driverRankItemValue
        if (*(short *)(param_1 + 0x50a) == 5) 
		{
		  // const_BrakeFriction
          iVar15 = (int)*(short *)(param_1 + 0x422) << 4;
          iVar6 = iVar15;
        }
      }
	  
	  // baseSpeed > 0,
	  // driving in some way
      else {
        iVar6 = iVar3;
        if (iVar3 < 0) {
          iVar6 = -iVar3;
        }
        if (
				(iVar6 < 0x301) ||
				(
					(
						((int)uVar9 < 1 || (-1 < iVar3)) && 
						((-1 < (int)uVar9 || (iVar3 < 1)))
					)
				)
			) 
		{
		  // kartState drifting
          if (cVar1 == '\x02') 
		  {
			// const_DriftCurve
            iVar15 = (int)*(short *)(param_1 + 0x424);
			
			// const_DriftFriction
            iVar6 = (int)*(short *)(param_1 + 0x426);
          }
		  
		  // driving straight
          else {
            if (iVar3 < 0) {
              iVar3 = -iVar3;
            }
			
			// const_PedalFriction_Perpendicular
            iVar15 = (int)*(short *)(param_1 + 0x41a);
			
			// const_PedalFriction_Forward
            iVar6 = (int)*(short *)(param_1 + 0x41c);
			
            if (0x300 < iVar3) {
              uVar11 = uVar9;
              if ((int)uVar9 < 0) {
                uVar11 = -uVar9;
              }
              if (iVar3 < (int)uVar11 >> 1) {
                uVar10 = uVar10 | 0x800;
              }
            }
          }
        }
        else {
          if (iVar3 < 0) {
            iVar3 = -iVar3;
          }
		  
		  // const_PedalFriction_Perpendicular
          iVar15 = (int)*(short *)(param_1 + 0x41a);
		  
		  // const_BrakeFriction
          iVar6 = (int)*(short *)(param_1 + 0x422);
		  
          if (0x300 < iVar3) {
            uVar10 = uVar10 | 0x800;
          }
        }
      }
    }
    
	// if in accel-prevention
	else {
      if (iVar3 < 0) {
        iVar3 = -iVar3;
      }
      if (0x300 < iVar3) {
        uVar10 = uVar10 | 0x800;
      }
	  
	  // const_BrakeFriction
      iVar3 = (uint)*(ushort *)(param_1 + 0x422) << 0x10;
	  
      iVar15 = iVar3 >> 0x10;
	  
	  // driverRankItemValue
      if (*(short *)(param_1 + 0x50a) == 5) {
        iVar15 = iVar15 << 4;
        iVar6 = iVar15;
      }
	  
	  // blasted kartState
      else if (cVar1 == '\x06') {
        iVar15 = iVar15 * 3 >> 2;
        iVar6 = iVar15;
      }
	  
      else {
        iVar6 = iVar15;
		
		// If you're spinning: if you hit a glass 
		// or spun out from drifting
        if (cVar1 == '\x03') {
          iVar15 = iVar3 >> 0x11;
          iVar6 = iVar15;
        }
      }
    }
	
	// terrainMeta1
    iVar13 = *(int *)(*(int *)(param_1 + 0x358) + 0x20);
	
    iVar3 = iVar15 * iVar5 >> 5;
    iVar6 = iVar6 * iVar5 >> 5;
    if (iVar13 != 0x100) {
      iVar3 = iVar13 * iVar3 >> 8;
      iVar6 = iVar13 * iVar6 >> 8;
    }
    
	iVar15 = (int)*(short *)(param_1 + 0x414);
    
	if (iVar15 < 0) {
      uVar11 = uVar7;
      if (iVar15 == -0x140) {
        if ((int)uVar7 < 0) {
          uVar11 = -uVar7;
        }
        iVar3 = (int)uVar11 >> 1;
      }
      else {
        iVar3 = iVar3 + (iVar3 * *(short *)(param_1 + 0x444) >> 8);
        if (iVar3 < 0) {
          iVar3 = 0;
        }
        if ((int)uVar7 < 0) {
          uVar11 = -uVar7;
        }
      }
      if (0 < (int)uVar11) {
        uVar10 = uVar10 | 0x1800;
		
		// GAMEPAD_ShockFreq and GAMEPAD_ShockForce1
        FUN_800264c0(param_1,4,0x7f);
        FUN_80026440(param_1,4,0);
      }
      iVar15 = iVar15 + iVar5;
      if (0 < iVar15) {
        iVar15 = 0;
      }
      *(short *)(param_1 + 0x414) = (short)iVar15;
    }
    else if (0 < iVar15) {
      iVar15 = iVar15 - iVar5;
      if (iVar15 < 0) {
        iVar15 = 0;
      }
      iVar3 = iVar3 + (iVar3 * *(short *)(param_1 + 0x444) >> 8);
      *(short *)(param_1 + 0x414) = (short)iVar15;
      if (iVar3 < 0) {
        iVar3 = 0;
      }
    }
    if (((uVar10 & 0x800000) == 0) && (iVar5 = (int)uVar7 >> 3, (uVar4 & 0x80) != 0)) {
      if (iVar5 < 0) {
        iVar5 = -iVar5;
      }
      if (iVar3 < iVar5) {
        iVar3 = iVar5;
      }
      if (((uVar8 == 0) || (uVar9 == 0)) || (-1 < (int)(uVar8 ^ uVar9))) {
        if ((((int)uVar9 <= (int)uVar8) || (0 < (int)uVar8)) &&
           (((int)uVar8 <= (int)uVar9 || ((int)uVar8 < 0)))) goto LAB_8005e8d8;
        iVar5 = uVar8 - uVar9;
        if (iVar5 < 0) {
          iVar5 = -iVar5;
        }
        iVar5 = iVar5 >> 1;
      }
      else {
        iVar5 = (int)uVar8 >> 1;
        if (iVar5 < 0) {
          iVar5 = -iVar5;
        }
      }
      if (iVar6 < iVar5) {
        iVar6 = iVar5;
      }
    }
LAB_8005e8d8:
    if (((uVar4 & 0x100) == 0) || (iVar5 = iVar3 * 3 >> 2, iVar3 = iVar6, iVar5 < iVar6)) {
      iVar5 = iVar3;
    }
	
	// Interpolate rotation by speed
    uVar7 = FUN_80058f54(uVar7,iVar5,0);
    uVar8 = FUN_80058f54(uVar8,iVar6,0);
  }
  
  // load new movement vector
  gte_ldVXY0(uVar7 & 0xffff | iVar16 << 0x10);
  gte_ldVZ0(uVar8);
  gte_rtv0();
  
  // save new movement vector
  gte_stlvnl(param_2);
  
  // set flag
  *(uint *)(param_1 + 0x2c8) = uVar10;
  
  // if driver is not in air
  if ((uVar10 & 0x80000) == 0) 
  {
    if (
			// firstFrameSinceRevEngine
			(*(char *)(param_1 + 0x449) != '\0') && 
			
			(uVar8 != 0)
		) 
	{
	  // move forward
      uVar2 = 1;
	  
	  // move backward
      if ((int)uVar8 < 0) {
        uVar2 = 0xffff;
      }
	  
	  // forwardDir (0x3e8)
      *(undefined2 *)(param_1 + 1000) = uVar2;
	  
	  // firstFrameSinceRevEngine
      *(undefined *)(param_1 + 0x449) = 0;
	  
      goto LAB_8005e9d8;
    }
	
    if (*(int *)(puVar14 + 0x10) < 0) 
	{

LAB_8005e9cc:

	  // moving forward
      if (-1 < (int)uVar8) 
	  {
		// forwardDir (0x3e8)
        *(undefined2 *)(param_1 + 1000) = 1;
      }
      goto LAB_8005e9d8;
    }
    
	// moving backward
	if ((int)uVar8 < 0) 
	{
	  // forwardDir (0x3e8)
      *(undefined2 *)(param_1 + 1000) = 0xffff;
    }
	
    if (*(int *)(puVar14 + 0x10) < 1) goto LAB_8005e9cc;

LAB_8005e9e8:
    
	// moving backward
	if ((int)uVar8 < 0) goto LAB_8005ea08;
    
	if (0 < *(int *)(puVar14 + 0x10)) {
      return;
    }
  }
  
  // if driver is in air
  else {
LAB_8005e9d8:
    if (-1 < *(int *)(puVar14 + 0x10)) goto LAB_8005e9e8;
  }
  if ((int)uVar8 < 1) {
    return;
  }
  
// start Rollback
LAB_8005ea08:


  // if rollback is starting, but in the last 0.64s
  // the driver started rollback already, then rolled 
  // forward, and is now rolling back AGAIN, count
  // V_Shift, inside two quadblocks in the shape of a V
  if (*(short *)(param_1 + 0x408) != 0) 
  {
	// increment number of V_Shifts
    *(short *)(param_1 + 0x40a) = *(short *)(param_1 + 0x40a) + 1;
  }

  // reset timer, rolling backward
  *(undefined2 *)(param_1 + 0x408) = 0x280;
  
  return;
}


// VehPhysForce_OnApplyForces
void FUN_8005ea60(undefined4 param_1,int param_2)

{
  undefined4 uVar1;
  int iVar2;

  // if speed is more than top speed
  if (0x6400 < *(short *)(param_2 + 0x38c))
  {
	// set top speed
    *(undefined2 *)(param_2 + 0x38c) = 0x6400;
  }

  // vec3_originToCenter
  // origin of driver model is center-bottom of kart,
  // 0x19 is the half-radius of the model,
  // calculate normalVec with magnitude 0x19 of driver,
  // then we can find the "true center" of the model
  gte_SetColorMatrix((MATRIX *)(param_2 + 0x330));
  gte_ldVXY0(0x190000);
  gte_ldVZ0(0);
  gte_lcv0();
  gte_stlvnl0((long *)(param_2 + 0x94));
  gte_stlvnl1((long *)(param_2 + 0x98));
  gte_stlvnl2((long *)(param_2 + 0x9c));

  // VehPhysForce_ConvertSpeedToVec
  FUN_8005e104(param_2,param_2 + 0x88,0);

  if (
		(
			// if under-quadblock exists
			(*(int *)(param_2 + 0x350) != 0) &&

			// if quadblock terrain is mud
			(*(char *)(*(int *)(param_2 + 0x350) + 0x38) == '\x0e')
		)
	 )
  {
	// if you have not sinked to the mud's bottom (-0x1000)
	if(-0x1000 < *(int *)(param_2 + 0x2d8))
	{
		// sink slower as you approach the mud's bottom
		iVar2 = -0x1000 - *(int *)(param_2 + 0x2d8)
	
		// set driver velY
		if(*(int *)(param_2 + 0x8c) < iVar2)
		{
			*(int *)(param_2 + 0x8c) = iVar2;
		}
	}
  }

  // VehPhysForce_OnGravity
  FUN_8005e214(param_2,param_2 + 0x88);

  // normalVec = {0, 0x1000, ...}
  *(undefined4 *)(param_2 + 0xa4) = 0x10000000;
  
  // normalVec = {0, 0x1000, ...}
  *(undefined4 *)(param_2 + 0x360) = 0x10000000;

  // driver is not touching quadblock
  *(undefined4 *)(param_2 + 0xa0) = 0;

  // normalVec = {... ..., 0}
  *(undefined2 *)(param_2 + 0xa8) = 0;
  
  // normalVec = {... ..., 0}
  *(undefined2 *)(param_2 + 0x364) = 0;
  
  *(undefined2 *)(param_2 + 0xaa) = 0;

  // increase velocity by acceleration
  *(int *)(param_2 + 0x88) = *(int *)(param_2 + 0x88) + (int)*(short *)(param_2 + 0x3cc);
  *(int *)(param_2 + 0x90) = *(int *)(param_2 + 0x90) + (int)*(short *)(param_2 + 0x3d0);
  *(int *)(param_2 + 0x8c) = *(int *)(param_2 + 0x8c) + (int)*(short *)(param_2 + 0x3ce);
  
  return;
}

// VehPhysForce_CollideDrivers
// handle collision with turbo pads and robotcars
void FUN_8005ebac(int param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 uVar4;
  uint uVar5;
  undefined2 local_40;
  undefined2 local_3e;
  undefined2 local_3c;
  int local_38;
  int local_34;

  // decrease velocity by acceleration
  *(int *)(param_2 + 0x8c) = *(int *)(param_2 + 0x8c) - (int)*(short *)(param_2 + 0x3ce);
  *(int *)(param_2 + 0x88) = *(int *)(param_2 + 0x88) - (int)*(short *)(param_2 + 0x3cc);
  uVar5 = *(uint *)(param_2 + 0xbc);
  *(int *)(param_2 + 0x90) = *(int *)(param_2 + 0x90) - (int)*(short *)(param_2 + 0x3d0);

  if ((uVar5 & 0x4000) != 0) {
    *(ushort *)(param_2 + 0xaa) = *(ushort *)(param_2 + 0xaa) | 1;
  }

  // If this is not a super turbo pad
  if ((uVar5 & 2) == 0) {

	// If this is not an ordinary turbo pad
    if ((uVar5 & 1) == 0) goto LAB_8005ec70;

	// add one second reserves
    uVar2 = 0x3c0;

	// If Super Turbo Pads is enabled
    if ((*(uint *)(PTR_DAT_8008d2ac + 8) & 0x100000) != 0)
	{
		// Skip a few lines
		goto LAB_8005ec50;
	}

	// set speed of turbo to normal speed
    uVar4 = 0x100;
  }

  // If this is a super turbo pad (only on some tracks)
  else {
LAB_8005ec50:

	// add 0.12s reserves
    uVar2 = 0x78;

	// Set speed of turbo to big speed
    uVar4 = 0x800;
  }

  // VehFire_Increment
  // add reserves and speed of turbo pad
  FUN_8005abfc(param_2,uVar2,5,uVar4);

LAB_8005ec70:
  if ((uVar5 & 0x8000) == 0)
  {
	// thread -> instance -> flags
	// instance is not in water or mud
    *(uint *)(*(int *)(param_1 + 0x34) + 0x28) =
         *(uint *)(*(int *)(param_1 + 0x34) + 0x28) & 0xffffdfff;
  }

  // if instance is in water or mud
  else
  {
	// thread -> instance
    iVar1 = *(int *)(param_1 + 0x34);

	// set vertical split height
	// (Y=0 for all water and mud)
    *(undefined2 *)(iVar1 + 0x56) = 0;

	// instance -> flags
	// split the instance
	*(uint *)(iVar1 + 0x28) = *(uint *)(iVar1 + 0x28) | 0x2000;
  }

  // if collision is not disabled for this thread
  if ((*(uint *)(param_1 + 0x1c) & 0x1000) == 0)
  {
	// 40, 3e, 3c, 38, 34, allocated in that order

	// position X and Y
    local_40 = (undefined2)((uint)*(undefined4 *)(param_2 + 0x2d4) >> 8);
    local_3e = (undefined2)((uint)*(undefined4 *)(param_2 + 0x2d8) >> 8);

	// distance between two objects
	local_34 = 0x7fffffff;

	// thread you collide with
	local_38 = 0;

	// position Z
    local_3c = (undefined2)((uint)*(undefined4 *)(param_2 + 0x2dc) >> 8);

	// check for collision with all sibling threads
	// PROC_CollidePointWithBucket
    FUN_80042348(*(undefined4 *)(param_1 + 0x10),&local_40);

	// pointer to first robotcar thread
	// PROC_CollidePointWithBucket
    FUN_80042348(*(undefined4 *)(PTR_DAT_8008d2ac + 0x1b40),&local_40);

	if (
			// if there was a collision
			(local_38 != 0) &&
			(
				// thread offset 0x42?
				iVar1 = (int)*(short *)(param_1 + 0x42) + (int)*(short *)(local_38 + 0x42),

				local_34 < iVar1 * iVar1
			)
	    )
	{
	  // pass the thread, collision data, and driver->88 is velocity?
      FUN_8005d404(param_1,&local_40,param_2 + 0x88);
    }
  }
  if ((*(ushort *)(param_2 + 0xaa) & 2) != 0) 
  {
	// driverPos - spsHitPos
    iVar3 = (*(int *)(param_2 + 0x2d4) >> 8) - (int)*(short *)(param_2 + 0xac);
    iVar1 = (*(int *)(param_2 + 0x2dc) >> 8) - (int)*(short *)(param_2 + 0xb0);
    
	if (
		// spsNormVec
		*(short *)(param_2 + 0xb4) * iVar3 +
        *(short *)(param_2 + 0xb6) * (((*(int *)(param_2 + 0x2d0) >> 8) - (int)*(short *)(param_2 + 0xae)) + 4) +
        *(short *)(param_2 + 0xb8) * iVar1 < 0) 
	{
	  // calculate speed vector
      *(int *)(param_2 + 0x88) = *(int *)(param_2 + 0x88) + iVar3 * 0x40;
      *(int *)(param_2 + 0x8c) = *(int *)(param_2 + 0x8c) + ((*(int *)(param_2 + 0x2d8) >> 8) - (int)*(short *)(param_2 + 0xae)) * 0x40;
      *(int *)(param_2 + 0x90) = *(int *)(param_2 + 0x90) + iVar1 * 0x40;
    }
  }
  return;
}

// VehPhysForce_TranslateMatrix -- move position to instance matrix
// param1 = thread, param2 = driver
void FUN_8005ee34(int param_1,int param_2)

{
  bool bVar1;
  undefined *puVar2;
  byte bVar3;
  undefined2 uVar4;
  short sVar5;
  int iVar6;
  undefined4 uVar7;
  int iVar8;
  int iVar9;
  MATRIX *pMVar10;
  int iVar11;
  int *piVar12;
  uint uVar13;
  MATRIX *r0;
  int iVar14;
  undefined uVar15;
  
  // get instance from thread
  iVar14 = *(int *)(param_1 + 0x34);
  
  // If you are not in a warp pad
  if (*(char *)(param_2 + 0x376) != '\n') 
  {
	// if you're being mask grabbed and you're not on the ground
    if ((*(char *)(param_2 + 0x376) == '\x05') && ((*(uint *)(param_2 + 0x2c8) & 1) == 0)) 
	{
	  // set Y scale
      *(short *)(iVar14 + 0x1e) = *(short *)(param_2 + 0x40c) + 0xccc;
	  
      iVar6 = *(short *)(param_2 + 0x40c) * 0x28;
      if (iVar6 < 0) {
        iVar6 = iVar6 + 0xff;
      }
	  
	  // X and Z
      iVar6 = 0xccc - (iVar6 >> 8);
      if (iVar6 < 0x400) {
        iVar6 = 0x400;
      }
	  
	  // Set X and Z scale
      *(short *)(iVar14 + 0x1c) = (short)iVar6;
      *(short *)(iVar14 + 0x20) = (short)iVar6;
    }
	
	// on ground, or mid-air without a mask-grab
    else 
	{
      sVar5 = *(short *)(param_2 + 0x390);
      iVar8 = (int)sVar5;
      iVar6 = -800;
	  
	  // if player did not start jumping this frame
      if ((*(uint *)(param_2 + 0x2c8) & 0x400) == 0) 
	  {
        iVar11 = (int)*(short *)(param_2 + 0x410) -
                 (*(short *)(param_2 + 0x410) * 9 + iVar8 * 7 >> 4);
        iVar6 = iVar11 * 4;
        iVar9 = iVar6;
        if (iVar6 < 0) {
          iVar9 = iVar11 * -4;
        }
        if (iVar9 < 0x960) {
          iVar6 = 0;
        }
		
		// if racer did not just touch ground this frame or last
        if (((*(uint *)(param_2 + 0x2c8) | *(uint *)(param_2 + 0x2cc)) & 2) == 0) {
          bVar1 = iVar6 < 0x321;
          if (iVar6 < -800) {
            iVar6 = -800;
            goto LAB_8005ef64;
          }
        }
		
		// if racer just touched ground this frame or last
        else {
          bVar1 = iVar6 < 0x321;
          if (iVar6 < -0x640) {
            iVar6 = -0x640;
LAB_8005ef64:
            bVar1 = iVar6 < 0x321;
          }
        }
        if (!bVar1) {
          iVar6 = 800;
        }
      }
	  
      //if Hazard Timer > 0 and Hazard Timer & 80 = 0 and (?)
      if (((0 < *(short *)(param_2 + 0xe)) && ((*(ushort *)(param_2 + 0xe) & 0x80) == 0)) &&
         (-800 < iVar6)) {
        iVar6 = -800;
      }
	  
	  // if racer is not on the ground
      if (((*(uint *)(param_2 + 0x2c8) & 1) == 0) && (iVar8 < 0)) 
	  {
        // Map value from [oldMin, oldMax] to [newMin, newMax]
        // inverting newMin and newMax will give an inverse range mapping
        iVar9 = FUN_80058f9c(-iVar8,0,0xa00,0x280);
		
        if (iVar6 < iVar9) {
          iVar6 = iVar9;
        }
        *(short *)(param_2 + 0x410) = sVar5;
      }
	  
      if (
		  // driver->instTntRecv
		  (*(int *)(param_2 + 0x18) != 0) &&
		
		   // driver->instTntRecv->scale[1] < 2500
           (
			iVar9 = (int)*(short *)(*(int *)(param_2 + 0x18) + 0x1e), 
			iVar9 < 2500
		   )
		 ) 
	  {
        iVar6 = iVar6 + (iVar9 + -0x800) * 2;
      }
	  
      iVar11 = (int)*(short *)(param_2 + 0x40c);
      iVar9 = iVar6;
      if (iVar6 < 0) {
        iVar9 = -iVar6;
      }
      if (iVar11 < 0) {
        iVar11 = -iVar11;
      }
      if (iVar11 < iVar9) {
        *(short *)(param_2 + 0x40c) = (short)iVar6;
      }
	  
	  // Interpolate rotation by speed
      uVar4 = FUN_80058f54((int)*(short *)(param_2 + 0x40c),300,0);
      *(undefined2 *)(param_2 + 0x40c) = uVar4;
	  
      *(short *)(param_2 + 0x410) = (short)(*(short *)(param_2 + 0x410) * 9 + iVar8 * 7 >> 4);
      
	  if (*(short *)(param_2 + 0x404) == 0) 
	  {
        if (*(short *)(iVar14 + 0x1e) == 0) 
		{
		  // driver -> instance -> thread -> modelIndex == "player" of any kind
          if (*(short *)(*(int *)(*(int *)(param_2 + 0x1c) + 0x6c) + 0x44) == 0x18) 
		  {
			// OtherFX_Play_Echo
			// 0x5b?
            FUN_80028494(0x5b,1,*(ushort *)(param_2 + 0x2ca) & 1);
          }
		  
          *(short *)(iVar14 + 0x1e) = *(short *)(param_2 + 0x40c) + 0xccc;
          
		  // matrixArr for blasted
		  *(undefined *)(param_2 + 0x4c) = 5;
          *(undefined *)(param_2 + 0x4d) = 0;
        }
		
        else 
		{
		  // Interpolate scale by speed
          uVar4 = FUN_80058f54((int)*(short *)(iVar14 + 0x1e),0xa0,
                               *(short *)(param_2 + 0x40c) + 0xccc);
          *(undefined2 *)(iVar14 + 0x1e) = uVar4;
        }
      }
      else {
        *(undefined2 *)(iVar14 + 0x1e) = 0;
      }
      iVar6 = *(short *)(param_2 + 0x40c) * 0xa0;
      if (iVar6 < 0) {
        iVar6 = iVar6 + 0xff;
      }
	  
	  // Interpolate scale by speed
      uVar4 = FUN_80058f54((int)*(short *)(iVar14 + 0x1c),0xa0,0xccc - (iVar6 >> 8));
      *(undefined2 *)(iVar14 + 0x1c) = uVar4;
      iVar6 = *(short *)(param_2 + 0x40c) * 0xa0;
      if (iVar6 < 0) {
        iVar6 = iVar6 + 0xff;
      }
	  
	  // Interpolate rotation by speed
      uVar4 = FUN_80058f54((int)*(short *)(iVar14 + 0x20),0xa0,0xccc - (iVar6 >> 8));
      *(undefined2 *)(iVar14 + 0x20) = uVar4;
    }
  }
  
  // VehPhysForce_RotAxisAngle (matrixFacingDir)
  FUN_8005f89c(param_2 + 0x330,param_2 + 0x368,(int)*(short *)(param_2 + 0x2ee));
  
  if (
		(
			(*(short *)(param_2 + 0x3e2) == 0) ||
			(*(short *)(param_2 + 0x39e) < *(short *)(param_2 + 0x42c))
		) ||
     
		((*(uint *)(param_2 + 0x2c8) & 0x80) != 0)
	 ) 
  {
	// matrixArr
    bVar3 = *(byte *)(param_2 + 0x4c);
    if (bVar3 != 0) {
      if (bVar3 == 2) 
	  {
		// matrixArr
        *(undefined *)(param_2 + 0x4c) = 3;
LAB_8005f398:
        *(undefined *)(param_2 + 0x4d) = 0;
      }
      else if (bVar3 < 3) {
        if (bVar3 == 1) {
          iVar6 = DAT_80087f00 + -1;
          if (iVar6 == 0) {
            trap(0x1c00);
          }
          if ((iVar6 == -1) && (*(byte *)(param_2 + 0x4d) == 0x800000)) {
            trap(0x1800);
          }
          iVar8 = 0x100 - (int)((uint)*(byte *)(param_2 + 0x4d) << 8) / iVar6;
          iVar6 = iVar8;
          if (iVar8 < 0) {
            iVar6 = 0;
          }
          if (0x100 < iVar8) {
            iVar6 = 0x100;
          }
          uVar15 = (undefined)((uint)(iVar6 * (DAT_80087f10 + -1)) >> 8);
		  
		  // matrixArr
          *(undefined *)(param_2 + 0x4c) = 3;
		  
          goto LAB_8005f354;
        }
      }
      else if ((bVar3 == 3) &&
              (bVar3 = *(char *)(param_2 + 0x4d) + 1, *(byte *)(param_2 + 0x4d) = bVar3,
              DAT_80087f10 <= (int)(uint)bVar3)) {
        *(undefined *)(param_2 + 0x4c) = 0;
        goto LAB_8005f398;
      }
    }
LAB_8005f39c:
    bVar3 = *(byte *)(param_2 + 0x4c);
  }
  else {
    bVar3 = *(byte *)(param_2 + 0x4c);
    if (bVar3 == 1) {
      bVar3 = *(char *)(param_2 + 0x4d) + 1;
      *(byte *)(param_2 + 0x4d) = bVar3;
      if (DAT_80087f00 <= (int)(uint)bVar3) 
	  {
		// matrixArr
        *(undefined *)(param_2 + 0x4c) = 2;
        goto LAB_8005f398;
      }
      goto LAB_8005f39c;
    }
    if (1 < bVar3) {
      if ((bVar3 != 2) && (bVar3 == 3)) {
        iVar6 = DAT_80087f10 + -1;
        if (iVar6 == 0) {
          trap(0x1c00);
        }
        if ((iVar6 == -1) && (*(byte *)(param_2 + 0x4d) == 0x800000)) {
          trap(0x1800);
        }
        iVar8 = 0x100 - (int)((uint)*(byte *)(param_2 + 0x4d) << 8) / iVar6;
        iVar6 = iVar8;
        if (iVar8 < 0) {
          iVar6 = 0;
        }
        if (0x100 < iVar8) {
          iVar6 = 0x100;
        }
        uVar15 = (undefined)((uint)(iVar6 * (DAT_80087f00 + -1)) >> 8);
		
		// matrixArr
        *(undefined *)(param_2 + 0x4c) = 1;
LAB_8005f354:
        *(undefined *)(param_2 + 0x4d) = uVar15;
      }
      goto LAB_8005f39c;
    }
    if (bVar3 == 0) 
	{
	  // matrixArr
      *(undefined *)(param_2 + 0x4c) = 1;
      goto LAB_8005f398;
    }
  }
  if ((bVar3 == 5) &&
     (bVar3 = *(char *)(param_2 + 0x4d) + 1, *(byte *)(param_2 + 0x4d) = bVar3,
     DAT_80087f20 <= (int)(uint)bVar3)) {
    *(undefined *)(param_2 + 0x4c) = 0;
    *(undefined *)(param_2 + 0x4d) = 0;
  }
  
  // animation index
  if (*(byte *)(param_2 + 0x4c) == 0) 
  {
	// copy matrix from driver to instance?
    *(undefined4 *)(iVar14 + 0x30) = *(undefined4 *)(param_2 + 0x330);
    *(undefined4 *)(iVar14 + 0x34) = *(undefined4 *)(param_2 + 0x334);
    *(undefined4 *)(iVar14 + 0x38) = *(undefined4 *)(param_2 + 0x338);
    *(undefined4 *)(iVar14 + 0x3c) = *(undefined4 *)(param_2 + 0x33c);
    *(undefined2 *)(iVar14 + 0x40) = *(undefined2 *)(param_2 + 0x340);
	
	// position (xyz)
    *(int *)(iVar14 + 0x44) = *(int *)(param_2 + 0x2d4) >> 8;
    *(int *)(iVar14 + 0x48) = (*(int *)(param_2 + 0x2d8) >> 8) + (*(char *)(param_2 + 0x377) * 3 >> 3);
    iVar6 = *(int *)(param_2 + 0x2dc);
  }
  
  // different animation index
  else 
  {
	// driver -> 0x330 matrix
    r0 = (MATRIX *)(param_2 + 0x330);
    
	// 0x4C - which matrix array
	// 0x4D - which matrix index
	piVar12 = (int *)((&DAT_80087ef4)[(uint)*(byte *)(param_2 + 0x4c) * 2] +
                     (uint)*(byte *)(param_2 + 0x4d) * 0x20);
    
	pMVar10 = r0;
    
	// MatrixRotate(
	//	output = instMatrix, 
	//	input1 = driver->matrixFacingDir
	//	input2 = animated matrix orientation set);
	FUN_8006c3b0(iVar14 + 0x30,r0,piVar12 + 2);
	
	// load matrix
    gte_SetRotMatrix(r0);
    
	// load vector
	iVar6 = *piVar12;
	gte_ldVXY0(iVar6);
    gte_ldVZ0((uint)*(ushort *)(piVar12 + 1));
    
	gte_rtv0();
	
	// x shares register with iVar6
	// y shares register with r0
	// z shares register with pMVar10
    read_mt(iVar6,r0,pMVar10);
    
	// position (xyz)
	*(int *)(iVar14 + 0x44) = *(int *)(param_2 + 0x2d4) + iVar6 >> 8;
    *(int *)(iVar14 + 0x48) = ((int)r0->m + *(int *)(param_2 + 0x2d8) >> 8) + (*(char *)(param_2 + 0x377) * 3 >> 3);
    iVar6 = (int)pMVar10->m + *(int *)(param_2 + 0x2dc);
  }
  
  // matrix -> 0x4C (posZ)
  *(int *)(iVar14 + 0x4c) = iVar6 >> 8;
  
  // if driver is squished
  if (*(short *)(param_2 + 0x404) != 0) 
  {
	// increment position by AngleAxis_NormalVec
    *(int *)(iVar14 + 0x44) = *(int *)(iVar14 + 0x44) + (*(short *)(param_2 + 0x368) * 0x13 >> 0xc);
    *(int *)(iVar14 + 0x48) = *(int *)(iVar14 + 0x48) + (*(short *)(param_2 + 0x36a) * 0x13 >> 0xc);
    *(int *)(iVar14 + 0x4c) = *(int *)(iVar14 + 0x4c) + (*(short *)(param_2 + 0x36c) * 0x13 >> 0xc);
  }
  
  iVar6 = *(int *)(iVar14 + 0x48);
  if (-1 < iVar6) {
code_r0x8005f834:
    if (0 < iVar6) {
      *(uint *)(iVar14 + 0x28) = *(uint *)(iVar14 + 0x28) & 0xffffdfff;
    }
	
	// wakeInst
    iVar14 = *(int *)(param_2 + 0x4f8);
    
	// if valid
	if (iVar14 != 0) 
	{
	  // make invisible
      *(uint *)(iVar14 + 0x28) = *(uint *)(iVar14 + 0x28) | 0x80;
	  
	  // clear driver->wakeScale, and wakeInst->scale
      *(undefined2 *)(param_2 + 0x4fc) = 0;
      *(undefined2 *)(iVar14 + 0x1c) = 0;
      *(undefined2 *)(iVar14 + 0x20) = *(undefined2 *)(param_2 + 0x4fc);
    }
    return;
  }
  
  // touching wall so???? or is it water?
  if ((iVar6 < -0x4f) || ((*(uint *)(iVar14 + 0x28) & 0x2000) == 0)) {
    iVar6 = *(int *)(iVar14 + 0x48);
    goto code_r0x8005f834;
  }
  iVar6 = *(int *)(param_2 + 0x4f8);
  if (iVar6 == 0) {
    return;
  }
  
  // make visible
  *(uint *)(iVar6 + 0x28) = *(uint *)(iVar6 + 0x28) & 0xffffff7f;
  
  // animation data
  *(char *)(iVar6 + 0x50) = *(char *)(iVar14 + 0x50) + '\x01';
  *(char *)(iVar6 + 0x51) = *(char *)(iVar14 + 0x51) + -1;
  
  // instance posX, posY, posZ
  uVar7 = *(undefined4 *)(iVar14 + 0x44);
  *(undefined4 *)(iVar6 + 0x48) = 0;
  *(undefined4 *)(iVar6 + 0x44) = uVar7;
  *(undefined4 *)(iVar6 + 0x4c) = *(undefined4 *)(iVar14 + 0x4c);
  
  // driver -> rotation
  uVar13 = (uint)*(short *)(param_2 + 0x39a);

  // approximate trigonometry

  // Sin(angle)
  sVar5 = (short)*(int *)(&DAT_800845a0 + (uVar13 & 0x3ff) * 4);

  // Cos(angle)
  iVar14 = *(int *)(&DAT_800845a0 + (uVar13 & 0x3ff) * 4) >> 0x10;

  // if (0 < angle < 90) or (180 < angle < 270)
  if ((uVar13 & 0x400) == 0) {
    iVar8 = (int)sVar5;
    if ((uVar13 & 0x800) == 0) goto LAB_8005f6a4;
    iVar9 = -iVar14;
  }

  // if (90 < angle < 180) or (270 < angle < 360)
  else {
    iVar9 = (int)sVar5;
    iVar8 = iVar14;
    if ((uVar13 & 0x800) == 0) {
      iVar14 = -iVar9;
      goto LAB_8005f6a4;
    }
  }
  iVar8 = -iVar8;
  iVar14 = iVar9;
LAB_8005f6a4:

  // instance rotation
  // looks like 5 int variables, but it's really
  // 9 short variables, 3x3 rotation matrix
  *(int *)(iVar6 + 0x30) = iVar14;
  *(int *)(iVar6 + 0x34) = iVar8;
  *(undefined4 *)(iVar6 + 0x38) = 0x1000;
  *(int *)(iVar6 + 0x3c) = -iVar8;
  *(short *)(iVar6 + 0x40) = (short)iVar14;
  
  puVar2 = PTR_DAT_8008d2ac;
  
  // if wake is not visible,
  // then do this for first frame of wake,
  // which sets scale, and makes a splash
  if (*(short *)(param_2 + 0x4fc) == 0) 
  {
	// wake is now visible (set scale)
    *(undefined2 *)(param_2 + 0x4fc) = 0x1000;
	
	// if less than 2 screens
    if ((byte)puVar2[0x1ca8] < 2) 
	{
	  // get speed
      iVar14 = (int)*(short *)(param_2 + 0x38c);
	  
	  // absolute value
      if (iVar14 < 0) {
        iVar14 = -iVar14;
      }
	  
      if (
			// if speed is high
			(0xc00 < iVar14) && 
			
			(
				// spawn 10 particles
				iVar14 = 10, 

				// racerY position is more than -0x200
				-0x200 < *(int *)(param_2 + 0x2e4)
			)
		  ) 
	  {
		// spawn particles till counter runs out
        do 
		{
		  // 0x2138 = "falling"
		  // like splashing in water on coco park

		  // Create instance in particle pool
          iVar8 = FUN_80040308(0,*(undefined4 *)(PTR_DAT_8008d2ac + 0x2138),&DAT_80089a94);
          
		  // if particle was made properly
		  if (iVar8 != 0) 
		  {
            *(undefined *)(iVar8 + 0x18) = *(undefined *)(*(int *)(param_2 + 0x1c) + 0x50);

			// driver->instSelf
			*(undefined4 *)(iVar8 + 0x20) = *(undefined4 *)(param_2 + 0x1c);

			// driverID
            *(undefined *)(iVar8 + 0x19) = *(undefined *)(param_2 + 0x4a);
          }

		  // reduce counter
          iVar14 = iVar14 + -1;
		  
        } while (iVar14 != 0);
      }
    }
  }
  
  // if numPlyrCurrGame is less than 2
  else if ((byte)PTR_DAT_8008d2ac[0x1ca8] < 2) 
  {
	// get speed
    iVar14 = (int)*(short *)(param_2 + 0x38c);
	
	// absolute value
    if (iVar14 < 0) {
      iVar14 = -iVar14;
    }
	
    if (
			// if speed is high
			(0xc00 < iVar14) &&
			
			// spawn one particle
			(
				// 0x2138 = "falling"
				// like splashing in water on coco park

				// Create instance in particle pool
				iVar14 = FUN_80040308(0,*(undefined4 *)(PTR_DAT_8008d2ac + 0x2138),&DAT_80089a94),
				iVar14 != 0
			)
		) 
	{
      *(undefined *)(iVar14 + 0x18) = *(undefined *)(*(int *)(param_2 + 0x1c) + 0x50);
      
	  // driver -> instSelf
	  *(undefined4 *)(iVar14 + 0x20) = *(undefined4 *)(param_2 + 0x1c);
      
	  // driverID
	  *(undefined *)(iVar14 + 0x19) = *(undefined *)(param_2 + 0x4a);
    }
  }

  // instance -> scale (x, z)
  *(undefined2 *)(iVar6 + 0x1c) = *(undefined2 *)(param_2 + 0x4fc);
  *(undefined2 *)(iVar6 + 0x20) = *(undefined2 *)(param_2 + 0x4fc);
  return;
}


// VehPhysForce_RotAxisAngle
// param1 - matrix
// param2 - normal axis
// param3 - angle
// equivalent to glm::AngleAxis, Unity Quaternion.AngleAxis, UE4 FVector AngleAxis
void FUN_8005f89c(undefined2 *param_1,short *param_2,uint param_3)

{
  short sVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  short sVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  short sVar9;
  int iVar10;
  int iVar11;
  undefined4 uVar12;
  int iVar13;
  undefined4 uVar14;
  undefined4 uVar15;
  int iVar16;
  int iVar17;
  int iVar18;

  // normalX
  sVar1 = *param_2;
  param_1[1] = sVar1;

  // normalY
  sVar9 = param_2[1];
  iVar11 = (int)sVar1;
  param_1[4] = sVar9;

  // normalZ
  iVar10 = (int)param_2[2];
  param_1[7] = param_2[2];

  // approximate trigonometry
  sVar1 = (short)*(int *)(&DAT_800845a0 + (param_3 & 0x3ff) * 4);
  iVar2 = *(int *)(&DAT_800845a0 + (param_3 & 0x3ff) * 4) >> 0x10;

  // if (0 < angle < 90) or (180 < angle < 270)
  if ((param_3 & 0x400) == 0)
  {
    iVar7 = (int)sVar1;

	// if (0 < angle < 90)
    if ((param_3 & 0x800) == 0) goto LAB_8005f934;

	// if (180 < angle < 270)
	// make X and Y values negative
	iVar8 = -iVar2;
  }

  // if (90 < angle < 180) or (270 < angle < 360)
  else
  {
    iVar8 = (int)sVar1;
    iVar7 = iVar2;

	// if (90 < angle < 180)
    if ((param_3 & 0x800) == 0) {
      iVar2 = -iVar8;
      goto LAB_8005f934;
    }

	// if (270 < angle < 360)
		// proceed without "goto"
  }

  iVar7 = -iVar7;
  iVar2 = iVar8;

  LAB_8005f934:
  iVar16 = iVar11 * iVar11;
  iVar17 = iVar10 * iVar10;
  iVar18 = iVar11 * -iVar10;
  iVar6 = iVar16 + iVar17;
  iVar13 = iVar7 * sVar9 >> 0xc;
  sVar1 = (short)iVar13;
  iVar8 = iVar2 * sVar9 >> 0xc;
  sVar9 = (short)iVar8;
  
  gte_ldLZCS(iVar6);
  iVar3 = gte_stLZCR();

  if (iVar6 == 0)
  {
    iVar2 = iVar7 * iVar11 + iVar2 * iVar10;

	// if normalY is negative
	if (param_2[1] < 0)
	{
	  // flip
      sVar1 = -sVar1;
    }
  }
  else {
    uVar4 = 0x14 - iVar3;
    if (0 < (int)uVar4) {
      iVar16 = iVar16 >> (uVar4 & 0x1f);
      iVar17 = iVar17 >> (uVar4 & 0x1f);
      iVar18 = iVar18 >> (uVar4 & 0x1f);
      iVar6 = iVar6 >> (uVar4 & 0x1f);
    }
    iVar13 = iVar7 - iVar13;
    iVar8 = iVar2 - iVar8;
    iVar3 = iVar13 * iVar17 + iVar8 * iVar18;
    if (iVar6 == 0) {
      trap(0x1c00);
    }
    if ((iVar6 == -1) && (iVar3 == -0x80000000)) {
      trap(0x1800);
    }
    iVar8 = iVar13 * iVar18 + iVar8 * iVar16;
    if (iVar6 == 0) {
      trap(0x1c00);
    }
    if ((iVar6 == -1) && (iVar8 == -0x80000000)) {
      trap(0x1800);
    }
    sVar1 = sVar1 + (short)(iVar3 / iVar6);
    iVar2 = iVar7 * iVar11 + iVar2 * iVar10;
    sVar9 = sVar9 + (short)(iVar8 / iVar6);
  }

  // write to matrix
  param_1[2] = sVar1;
  sVar5 = (short)(-iVar2 >> 0xc);
  param_1[5] = sVar5;
  param_1[8] = sVar9;

  // axis to rotate on
  gte_ldopv1SV(param_2);


  // new GTE calls this 
  // gte_ldopv2SV(r0);
  setCopReg(2,0x4800,(int)sVar1);
  setCopReg(2,0x5000,(int)sVar5);
  setCopReg(2,0x5800,(int)sVar9);


  gte_op12();
  read_mt(uVar12,uVar14,uVar15);
  

  // write to matrix
  *param_1 = (short)uVar12;
  param_1[3] = (short)uVar14;
  param_1[6] = (short)uVar15;

  return;
}


// VehPhysForce_AccelTerrainSlope
// param1 - driver object
// called from:
//		VehPhysGeneral_PhysAngular
//		VehPhysProc_PowerSlide_PhysAngular
uint FUN_8005fb4c(int param_1)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  undefined4 uVar5;

  // speed
  iVar1 = (int)*(short *)(param_1 + 0x38e);

  // erase accel X,Y,Z
  *(undefined2 *)(param_1 + 0x3cc) = 0;
  *(undefined2 *)(param_1 + 0x3ce) = 0;
  *(undefined2 *)(param_1 + 0x3d0) = 0;
  
  if (iVar1 < 0) {
    iVar1 = -iVar1;
  }

  // low speed (useless? shoould just be '= 0;')
  uVar2 = (uint)(iVar1 < 0x301);

  if (
		// high speed
		(iVar1 >= 0x301) &&

		(
			// high speed
			uVar2 = 1,

			// if not crashing
			*(char *)(param_1 + 0x376) != '\x01'
		)
	  )
  {
	// check if driver is in warppad
    uVar2 = *(uint *)(param_1 + 0x2c8) & 0x4000;

	if (
		// if driver is not being warped
		(uVar2 == 0) &&
		(
			(
				(
					// if driver is on quadblock
					uVar2 = *(uint *)(param_1 + 0x2c8) & 1,

					*(short *)(param_1 + 0x3fe) == 0 &&

					// if driver is on quadblock
					(uVar2 != 0)
				)
				&&
				(
					// driver -> terrain meta -> ???
					// 0x100 for everything except:
					// 0x000 for "ice" and "none" (mid-air)
					uVar2 = *(uint *)(*(int *)(param_1 + 0x358) + 0x10),

					// not on ice, not mid-air
					uVar2 != 0
				)
			)
		)
	   )
	{

	  // angleCurr - anglePrev
	  uVar4 = (int)*(short *)(param_1 + 0x3c6) - (int)*(short *)(param_1 + 0x3c8);

	  // set 0x457 to zero, to remove all camera slack,
	  // with no slack, steering locks camera to driver
	  
	  // kart angle cap from 'straight to camera'
	  uVar3 = (uint)*(byte *)(param_1 + 0x457);

	  // clamp to min cap or max cap
	  if ((int)uVar3 < (int)uVar4) uVar4 = uVar3;
      if ((int)uVar4 < (int)-uVar3) uVar4 = -uVar3;

	  // approximate trigonometry
      iVar1 = *(int *)(&DAT_800845a0 + (uVar4 & 0x3ff) * 4);

	  if ((uVar4 & 0x400) == 0) {
        iVar1 = iVar1 << 0x10;
      }
      iVar1 = iVar1 >> 0x10;
      if ((uVar4 & 0x800) != 0) {
        iVar1 = -iVar1;
      }

	  // before this function is called, there is always
	  // gte_SetRotMatrix, AxisAngle, driver -> 0x310

      uVar2 = ((int)(uVar2 * -8000) >> 8) * iVar1 >> 0xc & 0xffff;
      gte_ldVXY0(uVar2);
      gte_ldVZ0(0);
      gte_rtv0();
	  
	  // new acceleration vector
	  
      uVar5 = gte_stMAC1();
      *(short *)(param_1 + 0x3cc) = (short)uVar5;
      uVar5 = gte_stMAC2();
      *(short *)(param_1 + 0x3ce) = (short)uVar5;
      uVar5 = gte_stMAC3();
      *(short *)(param_1 + 0x3d0) = (short)uVar5;
    }
  }

  // does not really "return" anything, it just
  // sees something in r2 and assumes. Stupid ghidra
  return uVar2;
}


// VehPhysGeneral_PhysAngular
void FUN_8005fc8c(undefined4 param_1,int param_2)

{
  bool bVar1;
  bool bVar2;
  undefined2 uVar3;
  short sVar4;
  int iVar5;
  int iVar6;
  undefined4 uVar7;
  int iVar8;
  int iVar9;
  uint uVar10;
  int iVar11;
  int iVar12;
  short sVar13;
  int iVar14;
  int iVar15;
  int iVar16;
  short sVar17;
  int iVar18;
  int iVar19;
  uint local_38;

  // get camera rotation
  iVar14 = (int)*(short *)(param_2 + 0x2f2);

  // copy the variable
  iVar5 = iVar14;

  // make sure the camera is not negative; ie. get camera angle absolute
  if (iVar14 < 0) {
    iVar5 = -iVar14;
  }

  // elapsed milliseconds per frame, ~32
  iVar8 = *(int *)(PTR_DAT_8008d2ac + 0x1d04);

  uVar10 = iVar5 >> 3;
  if (uVar10 == 0) {
    uVar10 = 1;
  }
   // meta behaviour
  if ((int)(uint)*(byte *)(param_2 + 0x46a) < (int)uVar10) {
    uVar10 = (uint)*(byte *)(param_2 + 0x46a);
  }

  // Interpolate rotation by speed 
  // Rotation_Interpolation(rotPrev.w, 8, uVar10)
  iVar5 = FUN_80058f54((int)*(short *)(param_2 + 0x2fa),8,uVar10);

  // rotPrev.w = iVar5
  *(undefined2 *)(param_2 + 0x2fa) = (short)iVar5;

  // Interpolate rotation by speed
  // Rotation_Interpolation( abs(camerarotation), rotPrev.w * elapsedTimeInMS >> 5, 0)
  uVar3 = FUN_80058f54(iVar14,iVar5 * iVar8 >> 5,0);

  local_38 = *(uint *)(param_2 + 0x2c8);
  // sVar4 = numFramesSpentSteering
  sVar4 = *(short *)(param_2 + 1000);

  // set camera rotation (rotCurr.W)
  *(undefined2 *)(param_2 + 0x2f2) = uVar3;

  // speedApprox
  iVar14 = (int)*(short *)(param_2 + 0x38e);
  
  // int simpTurnState256 = simpTurnState * 0x100
  iVar5 = (int)*(char *)(param_2 + 0x4b) * 0x100;
  
  // if speedApprox is negative
  if (iVar14 < 1) 
  {
	// baseSpeed is negative
    if (*(short *)(param_2 + 0x39c) < 0) 
	{
	  // forwardDir (0x3e8)
      sVar4 = -1;
      *(undefined2 *)(param_2 + 1000) = 0xffff; // -1
    }
    if (-1 < iVar14) goto LAB_8005fd74;
  }
  
  // if speedApprox is positive
  else {
	  
LAB_8005fd74:
    
	// baseSpeed is positive
	if (-1 < *(short *)(param_2 + 0x39c)) 
	{
	  // forwardDir (0x3e8)
      sVar4 = 1;
      *(undefined2 *)(param_2 + 1000) = 1;
    }
  }
  if (sVar4 < 0) {
    // simpTurnState256 = simpTurnState * -0x100;
    iVar5 = (int)*(char *)(param_2 + 0x4b) * -0x100;
    // ActionsFlagSet = ActionsFlagSet ^ 0x10
    local_38 = local_38 ^ 0x10;
  }
  if (iVar14 < 0) {
    iVar14 = -iVar14;
  }
  if (
		((local_38 & 1) != 0) &&

		// if you're not on any turbo pad
		((*(uint *)(param_2 + 0xbc) & 3) == 0)
	  )
  {

    // Map value from [oldMin, oldMax] to [newMin, newMax]
    // inverting newMin and newMax will give an inverse range mapping
    iVar5 = FUN_80058f9c(iVar14,0x10,0x300,0,iVar5);
  }
  
  //terrainMeta1
  iVar12 = *(int *)(param_2 + 0x358);
  
  // rotationSpinRate = driver.rotationSpinRate;
  iVar9 = (int)*(short *)(param_2 + 0x3b4);
  
  if (iVar5 == 0)
  {
	// Interpolate rotation by speed
    //
    sVar4 = FUN_80058f54(iVar9,((int)*(short *)(param_2 + 0x43e) +
                               (int)*(char *)(param_2 + 0x34) * 0x32) * *(int *)(iVar12 + 0x28) >> 8
                         ,0);
  }
  else {
    bVar1 = iVar5 < 0;
    if (bVar1) {
      iVar5 = -iVar5;
      iVar9 = -iVar9;
    }
    sVar4 = (short)iVar9;
    //if (rotationSpinRate < simpTurnState256) {
    if (iVar9 < iVar5) {
      //rotationSpinRate = rotationSpinRate + ((TurningInputResponseStat + TurnConst * 100) * (terrainMeta1 + 0x28) >> 8);
        // 100%
      iVar9 = iVar9 + (((int)*(short *)(param_2 + 0x43e) + (int)*(char *)(param_2 + 0x34) * 100) *
                       *(int *)(iVar12 + 0x28) >> 8);
      //rotationSpinRateS16 = (short)rotationSpinRate;
      sVar4 = (short)iVar9;

      /*if (simpTurnState256 < rotationSpinRate) {
         rotationSpinRateS16 = (short)simpTurnState256;
      }*/
      bVar2 = iVar5 < iVar9;
LAB_8005fee4:
      if (bVar2) {
        sVar4 = (short)iVar5;
      }
    }
    else {
      //if (simpTurnState256 < rotationSpinRate)
      if (iVar5 < iVar9) {
        //rotationSpinRate = rotationSpinRate - ((TurningInputResponseStat + TurnConst * 0x32) * (terrainMeta1 + 0x28) >> 8)
        // 50%
        iVar9 = iVar9 - (((int)*(short *)(param_2 + 0x43e) + (int)*(char *)(param_2 + 0x34) * 0x32)
                         * *(int *)(iVar12 + 0x28) >> 8);
        //rotationSpinRateS16 = (short)rotationSpinRate;
        sVar4 = (short)iVar9;

        /*if (rotationSpinRate < simpTurnState256) {
            rotationSpinRateS16 = (short)simpTurnState256;
        }*/
        bVar2 = iVar9 < iVar5;
        goto LAB_8005fee4;
      }
    }
    //if (isforwardDirNegative)
    if (bVar1) {
        //rotationSpinRateS16 = -rotationSpinRateS16
      sVar4 = -sVar4;
    }
  }
  
  iVar5 = (int)*(short *)(param_2 + 0x3ec);

  //rotationSpinRate = rotationSpinRateS16;
  iVar9 = (int)sVar4;
  
  // driver.rotationSpinRate = rotationSpinRateS16
  *(short *)(param_2 + 0x3b4) = sVar4;

  if (iVar5 != 0) 
  {  
    uVar3 = (undefined2)(iVar5 - iVar8);

    // map [0-0x140] to [0-???]
    // deltaRotation = VehCalc_MapToRange(timeUntilDriftSpinout,0,0x140,0,previousFrameMultDrift);
    iVar6 = FUN_80058f9c(iVar5,0,0x140,0,(int)*(short *)(param_2 + 0x3ea));
    
	// rotationSpinRate = rotationSpinRate + deltaRotation;
    iVar9 = iVar9 + iVar6;
    
	// if (deltaTime < 0)
    if (iVar5 - iVar8 < 0) {
      uVar3 = 0;
    }
	
    *(undefined2 *)(param_2 + 0x3ec) = uVar3;
  }
  
  // character_Speed
  iVar11 = (uint)*(ushort *)(param_2 + 0x42c) << 0x10;
  iVar6 = iVar11 >> 0x10;
  
  // turnResistMax = MetaPhys.turnResistMax * iVar6
  iVar19 = (uint)*(byte *)(param_2 + 0x45d) * iVar6;
  
  // turnResistMin = MetaPhys.turnResistMin * iVar6
  iVar6 = (uint)*(byte *)(param_2 + 0x45c) * iVar6;
  
  sVar4 = *(short *)(param_2 + 0x3d2);
  
  // const_ModelRotationSpeed
  iVar5 = (int)*(short *)(param_2 + 0x452);
  
  iVar18 = iVar19 >> 8;
  iVar16 = iVar6 >> 8;
  
  // gas and break together
  if ((local_38 & 0x20) != 0) 
  {
    iVar18 = iVar19 >> 9;
	
    if (0x300 < iVar14)
	{
	  // driver is leaving skids
      *(uint *)(param_2 + 0x2c8) = *(uint *)(param_2 + 0x2c8) | 0x800;
    }
    iVar16 = iVar6 >> 9;
    if (*(short *)(param_2 + 0x39c) == 0) {
      iVar5 = (int)*(short *)(param_2 + 0x454);
    }
    else 
	{
	  // speed
      iVar6 = (int)*(short *)(param_2 + 0x38c);
      
	  if (iVar6 < 0) {
        iVar6 = -iVar6;
      }

      // Map "speed" from 
	  //	- [0x300, characterSpeed] 
	  //	to 
	  //	- [const_modelRotVelMin, const_modelRotVelMax]
	  
	  // Rotating the model to exaggerate the steering animation,
	  // only do this if driver speed is more than 0x300
      iVar5 = FUN_80058f9c(iVar6,0x300,iVar11 >> 0x11,(int)*(short *)(param_2 + 0x454),iVar5);
    }
  }
  
  // speed
  iVar6 = (int)*(short *)(param_2 + 0x38c);
  
  if (iVar6 < 0) {
    iVar6 = -iVar6;
  }
  iVar19 = ((uint)*(byte *)(param_2 + 0x43a) + ((int)*(char *)(param_2 + 0x34) << 1) / 5) * 0x100;

  // Map "speed" from 
  //	- [turnResistMin*iVar6>>8(or9), turnResistMax*iVar6>>8(or9)] 
  //	to 
  //	- [turnResistMax*iVar6, 0]
  
  // if iVar11 is zero, no turn-resist
  // if iVar11 is 0x7FFF, high turn-resist
  // this prevents you from steering sharp at low speeds
  
  // get turn resistance, given speed, and range maps
  iVar11 = FUN_80058f9c(iVar6,iVar16,iVar18,iVar19,0);
  
  iVar6 = 0;
  if (iVar16 <= iVar14) {
    iVar15 = iVar9;
    if (iVar9 < 0) {
      iVar15 = -iVar9;
    }
    if (iVar11 < iVar15) 
	{
	  // fire speed
      iVar6 = (int)*(short *)(param_2 + 0x39e);
      if (iVar6 < 0) {
        iVar6 = -iVar6;
      }

	  // same input-range as the previous map

	  // Map "fire speed" from 
	  //	- [turnResistMin*iVar6>>8(or9), turnResistMax*iVar6>>8(or9)] 
	  //	to 
	  //	- [0, ???]
      uVar7 = FUN_80058f9c(iVar6,iVar16,iVar18,0,iVar5);

      // Map "rotation rate" from
	  //	- [unk to unk]
	  //	to
	  //	- [0, mappedFireSpeed]
      iVar6 = FUN_80058f9c(iVar15,iVar11,iVar19,0,uVar7);
	  
	  // absolute value,
	  // then use this for LerpToForwards
      if (iVar9 < 0) {
        iVar6 = -iVar6;
      }
    }
  }
  sVar13 = *(short *)(param_2 + 0x3c6);

  // VehPhysGeneral_LerpToForwards
  sVar4 = FUN_80060488(param_2,(int)sVar13,(int)sVar4,iVar6);
  *(short *)(param_2 + 0x3d2) = sVar4;
  
  iVar6 = (int)sVar4;
  
  // terrain related
  if (*(int *)(iVar12 + 0x24) != 0x100) {
    iVar6 = *(int *)(iVar12 + 0x24) * iVar6 >> 8;
  }
  
  iVar16 = (int)sVar13 + (iVar6 * iVar8 >> 5);
  *(short *)(param_2 + 0x3c6) = (short)iVar16;
  iVar11 = iVar9;
  
  // if [???] && touching quadblock
  if ((0x2ff < iVar14) && ((local_38 & 1) != 0))
  {
	// number of frames spent steering
    sVar4 = *(short *)(param_2 + 0x3e6);

	// VehCalc_SteerAccel
	// all these offsets are MetaPhys, and each one is only used here
    iVar18 = FUN_8005900c(

		// frames spent steering
		(int)sVar4,

		// SteerAccel_Stage2_FirstFrame
		(int)*(char *)(param_2 + 0x447),
		
		// SteerAccel_Stage2_FrameLength
		(int)*(char *)(param_2 + 0x448),
		
		// SteerAccel_Stage4_FirstFrame
		(int)*(char *)(param_2 + 0x446),

		// SteerAccel_Stage1_MinSteer
		(int)*(short *)(param_2 + 0x44c),

		// SteerAccel_Stage1_MaxSteer
        (int)*(short *)(param_2 + 0x44a)
	);

    if (iVar9 < 0) {
      iVar11 = -iVar9;
    }
	
	// 0x44e is const val 0x80
    iVar11 = *(short *)(param_2 + 0x44e) * iVar11 >> 8;

	// increment frame counter
    *(short *)(param_2 + 0x3e6) = sVar4 + 1;

	// the higher the value of iVar18,
	// the more steering is "locked up",
	// try setting mov r3, xxxx at 80060170 for proof

    if (iVar11 < iVar18) {
      iVar18 = iVar11;
    }
	
	// steering left or right
    if ((local_38 & 0x10) != 0) {
      iVar18 = -iVar18;
    }
	
	// constant value zero, for all classes
    iVar19 = (int)*(short *)(param_2 + 0x450);
	
    if ((iVar9 < 1) || (iVar11 = -iVar19, iVar11 <= iVar9 + iVar18)) {
      if (iVar9 < 0) {
        iVar11 = iVar9 + iVar18;
        if (iVar19 < iVar9 + iVar18) {
          iVar11 = iVar19;
        }
      }
      else {
        iVar11 = iVar9 + iVar18;
      }
    }
  }
  iVar9 = (int)*(short *)(param_2 + 0x3d4);
  sVar4 = *(short *)(param_2 + 0x3d8);
  sVar13 = *(short *)(param_2 + 0x3d6);
  
  // terrain related, and touching quadblock
  if (((*(uint *)(iVar12 + 4) & 0x10) == 0) && ((local_38 & 1) != 0)) {
    iVar18 = iVar16;
    if (iVar16 < 0) {
      iVar18 = -iVar16;
    }
    if (iVar5 * 3 >> 2 < iVar18) {
      iVar5 = iVar6;
      if (iVar6 < 0) {
        iVar5 = -iVar6;
      }
      if (iVar5 < 3) {
        iVar5 = iVar9;
        if (iVar9 < 0) {
          iVar5 = -iVar9;
        }
        if (iVar5 < 10) {
          sVar4 = 8;
          sVar13 = 0x14;
          if (iVar16 < 0) {
            sVar13 = -0x14;
          }
        }
      }
      goto LAB_80060284;
    }
  }
  sVar4 = 0;
LAB_80060284:
  iVar5 = iVar9;
  if (iVar9 < 0) {
    iVar5 = -iVar9;
  }
  if (0x32 < iVar5) {
    sVar4 = 0;
  }
  if (sVar4 == 0) {
    iVar5 = 10;
    if (0 < iVar9) {
      iVar5 = -10;
    }
    sVar13 = (short)iVar5;
    if (iVar5 < 0) {
      iVar5 = -iVar5;
    }

	// Interpolate rotation by speed
    sVar17 = FUN_80058f54(iVar9,iVar5,0);
  }
  else {
    sVar4 = sVar4 + -1;
    sVar17 = *(short *)(param_2 + 0x3d4) + sVar13;
  }
  uVar10 = SEXT24(*(short *)(param_2 + 0x39a));
  *(short *)(param_2 + 0x3d8) = sVar4;
  *(short *)(param_2 + 0x3d4) = sVar17;
  *(short *)(param_2 + 0x3d6) = sVar13;

  // Map value from [oldMin, oldMax] to [newMin, newMax]
  // inverting newMin and newMax will give an inverse range mapping
  iVar5 = FUN_80058f9c(iVar14,0,0x600,iVar6,0);
  iVar14 = iVar5 * iVar8 >> 5;
  iVar5 = iVar14;
  if (iVar14 < 0) {
    iVar5 = -iVar14;
  }
  if (1 < iVar5) {
    uVar10 = uVar10 - iVar14 & 0xfff;
  }
  *(undefined2 *)(param_2 + 0xc0) = (short)iVar11;
  uVar10 = uVar10 + (iVar11 * iVar8 >> 0xd) & 0xfff;
  sVar4 = (short)uVar10;
  *(short *)(param_2 + 0x39a) = sVar4;
  *(short *)(param_2 + 0x2ee) = sVar4 + (short)iVar16 + sVar17;
  
  // if not holding break, and not mashing X
  if (((local_38 & 8) == 0) && (*(short *)(param_2 + 0x3c2) < 7)) 
  {
	// terrain related
    if (*(int *)(iVar12 + 0x14) != 0x100) 
	{
      iVar11 = iVar11 * *(int *)(iVar12 + 0x14) >> 8;
    }
  }
  
  // holding break, or mashing X
  else {
    iVar11 = iVar11 * 10 >> 8;
  }
  
  // axisRotationX
  *(ushort *)(param_2 + 0x396) =
       *(short *)(param_2 + 0x396) + (short)(iVar11 * iVar8 >> 0xd) & 0xfff;

  // VehPhysForce_RotAxisAngle
  FUN_8005f89c((undefined4 *)(param_2 + 0x310),param_2 + 0x360,uVar10);
  gte_SetRotMatrix((MATRIX *)(param_2 + 0x310));

  // VehPhysForce_AccelTerrainSlope
  FUN_8005fb4c(param_2);
  return;
}


// VehPhysGeneral_LerpQuarterStrength
int FUN_80060458(int param_1,int param_2)

{
  // desired != 0
  if (param_2 != 0)
  {	
	// desired /= 4
	param_2 = param_2 >> 2,

	// if desired == 0
	if (param_2 == 0)
	{
		// desired = 1
		param_2 = 1;
	}
  }

  // if current >= desired/4
  if (param_2 <= param_1)
  {
	// current = desired/4
    param_1 = param_2;
  }

  return param_1;
}


// VehPhysGeneral_LerpToForwards
// "return 0;" will make car stay in "drift steer" rotation,
// and not interpolate to rotate a forwards direction
int FUN_80060488(int param_1,int param_2,int param_3,int param_4)

{
  bool bVar1;
  uint uVar2;
  int iVar3;

  bVar1 = false;
  *(undefined2 *)(param_1 + 0x3ca) = 0;
  if ((param_4 < 0) || ((param_4 == 0 && (param_2 < 0)))) {
    bVar1 = true;
    param_2 = -param_2;
    param_3 = -param_3;
    param_4 = -param_4;
  }
  iVar3 = 0;
  
  // if not rubbing on wall
  if (*(short *)(param_1 + 0x3fe) != 0xf0) 
  {
    if (param_4 < param_2) {
      if (*(short *)(param_1 + 0x452) < param_2) {
        uVar2 = (uint)*(byte *)(param_1 + 0x458) * 0xf;
      }
      else {
        uVar2 = (uint)*(byte *)(param_1 + 0x458);
      }
      iVar3 = FUN_80060458(uVar2,param_2 - param_4,0);
      iVar3 = -iVar3;
    }
    else {
      if (param_2 < param_4) {
        if (param_2 < 0) {
          iVar3 = FUN_80060458((uint)*(byte *)(param_1 + 0x459),param_4 - param_2,0);
        }
        else {
          iVar3 = FUN_80060458((uint)*(byte *)(param_1 + 0x457),param_4 - param_2,0);
          *(undefined2 *)(param_1 + 0x3ca) = (short)param_4;
        }
      }
    }
  }

  // Interpolate rotation by speed
  iVar3 = FUN_80058f54(param_3,(uint)*(byte *)(param_1 + 0x45a),iVar3);
  if (bVar1) {
    iVar3 = -iVar3;
  }
  return iVar3;
}


// VehPhysGeneral_JumpGetVelY
// param_1: normalVec (driver 0x360, 0x368, 0x378)
// param_2: speedCoord (driver 0x88)
// if "return 0;" then you jump off a ramp and get no height
int FUN_800605a0(short *param_1,int *param_2)

{
  int iVar1;
  int iVar2;

  // y1 (normal vector Y)
  iVar2 = (int)param_1[1];

  iVar1 = iVar2;
  if (iVar2 < 0) {
    iVar1 = -iVar2;
  }

  if (0x14 < iVar1)
  {
	// this determines if you fly off a ramp or not,
	// regardless if you press L1 or R1
	
	// if quadblock is flat, normalvec x and z are zero,
	// causing the multiply product to also be zero (no fly)
	
	// if X points up, and you drive along the X,
	// then you get a high number to fly off the ramp

    iVar1 =

		// x2 * x1
		*param_2 * (int)*param_1 +

		// z2 * z1
		param_2[2] * (int)param_1[2];

	// alert debugger on error
	if (iVar2 == 0) trap(0x1c00);
    if ((iVar2 == -1) && (iVar1 == -0x80000000)) trap(0x1800);

    return iVar1 / iVar2;
  }
  return 0;
}


 // VehPhysGeneral_JumpAndFriction
void FUN_80060630(undefined4 param_1,int param_2)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  short sVar6;
  int iVar7;
  short sVar8;
  short sVar9;
  int iVar10;
  uint uVar11;
  uint uVar12;
  uint uVar13;
  int local_28;
  uint local_24;
  int local_20;

  // driver -> 0x310
  gte_SetRotMatrix((MATRIX *)(param_2 + 0x310));

  if (
		(
			// if driver is not drifting
			(*(char *)(param_2 + 0x376) != '\x02') &&

			//if driver is not using mask weapon
			((*(uint *)(param_2 + 0x2c8) & 0x800000) == 0)
		) &&

		// no reserves
		(*(short *)(param_2 + 0x3e2) == 0)
	 )
  {
    iVar7 = (int)((uint)*(ushort *)(param_2 + 0xc0) << 0x10) >> 0x18;
    if (iVar7 < 0) {
      iVar7 = -iVar7;
    }

    // Map value from [oldMin, oldMax] to [newMin, newMax]
    // inverting newMin and newMax will give an inverse range mapping
    iVar2 = FUN_80058f9c(iVar7,0,(uint)*(byte *)(param_2 + 0x43b),0,(int)*(short *)(param_2 + 0x43c)
                        );
    iVar10 = (int)*(short *)(param_2 + 0x39c);
    iVar7 = iVar10;
    if (iVar10 < 0) {
      iVar7 = -iVar10;
    }
    sVar6 = (short)iVar2;
    if (iVar7 < iVar2) {
      sVar6 = (short)iVar7;
    }
    sVar8 = -sVar6;
    if (iVar10 < 0) {
      sVar8 = sVar6;
    }
    *(short *)(param_2 + 0x39c) = *(short *)(param_2 + 0x39c) + sVar8;
  }
  
  // if rubbing on wall now, or recenlty
  if (*(short *)(param_2 + 0x3fe) != 0) 
  {
    if (*(short *)(param_2 + 0x38a) < *(short *)(param_2 + 0x39c)) {
      *(undefined2 *)(param_2 + 0x39c) = *(undefined2 *)(param_2 + 0x38a);
    }
    if ((int)*(short *)(param_2 + 0x39c) < -(int)*(short *)(param_2 + 0x38a)) {
      *(short *)(param_2 + 0x39c) = -*(short *)(param_2 + 0x38a);
    }
  }
  local_28 = *(int *)(param_2 + 0x88);
  local_24 = *(uint *)(param_2 + 0x8c);
  local_20 = *(int *)(param_2 + 0x90);
  uVar13 = 0;
  iVar7 = 0;

  // if driver is not on quadblock, or if not forced to jump (via GOTO)
  if ((*(uint *)(param_2 + 0x2c8) & 1) == 0) {
LAB_80060ab0:

	if (
			// If you want to fire a weapon
			((*(uint *)(param_2 + 0x2c8) & 0x8000) != 0) &&

			// If that weapon is a spring
			(*(char *)(param_2 + 0x36) == '\x05')
		)
	{
		// Remove the request to fire a weapon, since we will use it now
      *(uint *)(param_2 + 0x2c8) = *(uint *)(param_2 + 0x2c8) & 0xffff7fff;

	  // if coyoteTimerMS has not expired, and cooldownMS is over
      if ((*(short *)(param_2 + 0x3f4) != 0) && (*(short *)(param_2 + 0x3f2) == 0))
	  {
		// driver is now forced to jump
        *(undefined2 *)(param_2 + 0x3f6) = 0xa0;

		// const_Jump * 9
        iVar7 = (int)*(short *)(param_2 + 0x418) * 9;

		// always true
        if (iVar7 < 0)
		{
		  // add 3
          iVar7 = iVar7 + 3;
        }

		// jump_InitialVelY = big jump from spring
        *(undefined2 *)(param_2 + 0x3f8) = (short)(iVar7 >> 2);

		// OtherFX_Play_Echo
		// spring weapon sound
        FUN_80028494(9,1,(uint)*(ushort *)(param_2 + 0x2ca) & 1);

        *(undefined2 *)(param_2 + 0x3fa) = 0x180;
        goto LAB_80060c30;
      }
      *(undefined2 *)(param_2 + 0x3c) = 0;
    }

	// if not being forced to jump (turtles), this should cause the tiny jumps on top of walls.
	if (*(char *)(param_2 + 0x366) == '\0')
	{
      if (
			(
				// if driver left quadblock more than 0.16s ago
				(*(short *)(param_2 + 0x3f4) == 0) ||

				// if haven't jumped in last 10 frames
				(*(short *)(param_2 + 0x3f0) == 0)
			) ||

			// jump_CooldownMS not over (so can't jump again)
			(*(short *)(param_2 + 0x3f2) != 0)
		 )
	  {
        if (
			(
			 // if player is touching ground
			 ((*(uint *)(param_2 + 0x2c8) & 1) != 0) &&

			 // if player is over a quadblock
			 (*(int *)(param_2 + 0x350) != 0)
			) &&
            (
			 // unknown quadblock variable
			 iVar7 = (int)*(char *)(*(int *)(param_2 + 0x350) + 0x3b),
			 iVar7 != 0
			)
		   )
		{
		  // player speed
          iVar2 = (int)*(short *)(param_2 + 0x38e);
          if (iVar2 < 0) { // change sign of player speed
            iVar2 = -iVar2;
          }
		  
          gte_ldVXY0((iVar7 * iVar2 >> 8) << 0x10);
          gte_ldVZ0(0);
          gte_rtv0();
          read_mt(iVar7,iVar2,iVar10);

          local_28 = local_28 + iVar7;
          local_20 = local_20 + iVar10;
          local_24 = local_24 + iVar2;
        }
        goto LAB_80060e1c;
      }
      
	  // implied "else",
	  // if (jump_cooldownMS is over) &&
	  // 	(haven't left quadblock || no jump in over 10 frames)
	  
	  // force driver to jump
	  *(undefined2 *)(param_2 + 0x3f6) = 0xa0;
	  
	  // increment jump counter
      *(short *)(param_2 + 0x554) = *(short *)(param_2 + 0x554) + 1;

	  // jump_InitialVelY = const_Jump
      *(undefined2 *)(param_2 + 0x3f8) = *(undefined2 *)(param_2 + 0x418);

	  // OtherFX_Play_Echo
	  // play jump sound
      FUN_80028494(8,1,(uint)*(ushort *)(param_2 + 0x2ca) & 1);
    }

	// if being forced to jump (by turtles)
    else
	{
	  // if first frame (basically)
      if (
			// if not currently airborne from forced jump
			(*(short *)(param_2 + 0x3f6) == 0) ||

		 // if jump_InitialVelY was just now set to const_jump
         (*(short *)(param_2 + 0x3f8) == *(short *)(param_2 + 0x418)))
	  {
		// OtherFX_Play
        FUN_80028468(0x7e,1);
      }

	  // currently forced airborne
      *(undefined2 *)(param_2 + 0x3f6) = 0xa0;

	  // if big force jump (turtles)
      if (*(char *)(param_2 + 0x366) == '\x02')
	  {
        *(undefined2 *)(param_2 + 0x3fa) = 0x180;

		// const_Jump * 3
        *(short *)(param_2 + 0x3f8) = *(short *)(param_2 + 0x418) * 3;
      }

	  // if small force jump (turtles)
      else
	  {
		// jump_InitialVelY = const_Jump * 1.5
        *(undefined2 *)(param_2 + 0x3f8) = (short)(((int)*(short *)(param_2 + 0x418) * 3) / 2);
      }

	  // remove force jump (turtles)
      *(undefined *)(param_2 + 0x366) = 0;
    }
  }

  // if driver is on a quadblock
  else
  {
    if (
			// if driver is not on any turbo pad
			((*(uint *)(param_2 + 0xbc) & 3) == 0) ||

			(*(short *)(param_2 + 0x39c) < 1)
		)
	{
      if (*(short *)(param_2 + 0x39c) != 0) 
	  {
		// terrain related
        if ((((*(uint *)(*(int *)(param_2 + 0x358) + 4) & 4) == 0) ||
            (*(short *)(param_2 + 0x39c) < 1)) || (-1 < *(short *)(param_2 + 0x38e))) 
		{
          iVar10 = (int)*(short *)(param_2 + 0x38e);
          iVar2 = iVar10;
          if (iVar10 < 0) {
            iVar2 = -iVar10;
          }
          if (((0x2ff < iVar2) && ((*(short *)(param_2 + 0x39c) < 1 || (iVar10 < 1)))) &&
             ((-1 < *(short *)(param_2 + 0x39c) || (-1 < iVar10)))) goto LAB_800608fc;
        }

		// const_accel_noReserves + driver-specific acceleration
        iVar7 = (int)*(short *)(param_2 + 0x428) + ((int)*(char *)(param_2 + 0x33) << 5) / 5;

		// if you're not on any turbo pad
        if ((*(uint *)(param_2 + 0xbc) & 3) == 0)
		{
          if (
				// if reserves are not zero
				(*(short *)(param_2 + 0x3e2) != 0) &&

				(0 < *(short *)(param_2 + 0x39c))
			  )
		  {
			// const_Accel_Reserves
            iVar7 = (int)*(short *)(param_2 + 0x42a);
          }

		  // driver -> terrain meta -> slowUntilSpeed,
		  // if 0, driver will slow down until completely stuck
		  iVar2 = *(int *)(*(int *)(param_2 + 0x358) + 0xc);

          if (
				(iVar2 != 0x100) &&

				// if driver is not using mask weapon
				((*(uint *)(param_2 + 0x2c8) & 0x800000) == 0)
			 )
		  {
            iVar7 = iVar2 * iVar7 >> 8;
          }
        }
        else {
          if (0 < *(short *)(param_2 + 0x39c)) goto LAB_8006089c;
        }
      }
    }

	// if driver is on a turbo pad
	else
	{
LAB_8006089c:

	  // high acceleration
      iVar7 = 8000;
    }
LAB_800608fc:
						// elapsed milliseconds per frame, ~32
    uVar11 = iVar7 * *(int *)(PTR_DAT_8008d2ac + 0x1d04) >> 5;
	
    gte_ldVXY0(0);
    gte_ldVZ0(uVar11 & 0xffff);
    gte_rtv0();
    read_mt(sVar6,sVar8,sVar9);
	
    if (*(short *)(param_2 + 0x39c) < 0) {
      *(short *)(param_2 + 0x3b2) = -(short)uVar11;
      iVar7 = -iVar7;
      iVar2 = -iVar2;
      iVar10 = -iVar10;
      *(short *)(param_2 + 0x3ac) = -sVar6;
      *(short *)(param_2 + 0x3ae) = -sVar8;
      *(short *)(param_2 + 0x3b0) = -sVar9;
    }
    else {
      *(short *)(param_2 + 0x3b2) = (short)uVar11;
      *(short *)(param_2 + 0x3ac) = sVar6;
      *(short *)(param_2 + 0x3ae) = sVar8;
      *(short *)(param_2 + 0x3b0) = sVar9;
    }
    local_20 = local_20 + iVar2;
    local_24 = local_24 + iVar10;
    local_28 = local_28 + iVar7;

    // uVar13 = sqrt(x2+y2+z2 << 0x10)
    uVar13 = FUN_80059070(local_28 * local_28 + local_24 * local_24 + local_20 * local_20,0x10);

    iVar7 = (int)*(short *)(param_2 + 0x39c);
    if (iVar7 < 0) {
      iVar7 = -iVar7;
    }
    uVar13 = (uVar13 >> 8) - iVar7;
    bVar1 = (int)uVar11 < (int)uVar13;
    if ((int)uVar13 < 0) {
      uVar13 = 0;
      bVar1 = (int)uVar11 < 0;
    }
    if (bVar1) {
      uVar13 = uVar11;
    }

	// if not on quadblock, or if not forced to jump
    if (((*(uint *)(param_2 + 0x2c8) & 1) == 0) || (*(short *)(param_2 + 0x3f6) == 0))
    goto LAB_80060ab0;

    if (*(short *)(param_2 + 0x3fa) != 0) {
      *(undefined2 *)(param_2 + 0x3fa) = 0x180;
    }

	// If you're "blasted", flipping around after hit by missile, bomb, etc
    if (*(char *)(param_2 + 0x376) == '\x06')
	{
	  // GAMEPAD_ShockFreq and GAMEPAD_ShockForce1
      FUN_80026440(param_2,8,0);
      FUN_800264c0(param_2,8,0x7f);
    }
  }
LAB_80060c30:
  iVar7 = 0;
  iVar10 = 0x378;

  // jump timer
  *(undefined2 *)(param_2 + 0x3f2) = 0x180;

  *(undefined2 *)(param_2 + 0x3f0) = 0;
  *(uint *)(param_2 + 0x2c8) = *(uint *)(param_2 + 0x2c8) | 0x480;

  // this loop has one iteration
  iVar2 = iVar7;
  do
  {
	// Driver_RampVelY
    iVar3 = FUN_800605a0(param_2 + iVar10,&local_28);

    iVar5 = iVar3;
    if (iVar3 < 0) {
      iVar5 = -iVar3;
    }
    iVar4 = iVar7;
    if (iVar7 < 0) {
      iVar4 = -iVar7;
    }
    if (iVar4 < iVar5) {
      iVar7 = iVar3;
    }
    iVar2 = iVar2 + 1;
    iVar10 = iVar10 + 8;
  } while (iVar2 < 1);

  iVar2 = param_2 + 0x360;
  if ((*(uint *)(param_2 + 0x2c8) & 1) == 0) {
    iVar2 = param_2 + 0x368;
  }

  // Driver_RampVelY
  iVar10 = FUN_800605a0(iVar2,&local_28);

  iVar2 = iVar10;
  if (iVar10 < 0) {
    iVar2 = -iVar10;
  }
  iVar5 = iVar7;
  if (iVar7 < 0) {
    iVar5 = -iVar7;
  }
  iVar3 = iVar7 * iVar7;
  if (iVar5 < iVar2) {
    iVar3 = iVar10 * iVar10;
    iVar7 = iVar10;
  }

  // iVar2 = sqrt( (ramp+jump*jump>>8) << 8),
  // iVar2 = sqrt( "basically" ramp+jump*jump )
  // last byte is cleared cause only 3 bytes in driver->0x2D4
  // are rendered, and the last byte is sub-pixel percision
  
  // iVar2 = sqrt(ramp+jump*jump)
  iVar2 = FUN_80059070(
							// param_1
							iVar3 + 
							(int)*(short *)(param_2 + 0x3f8) * 
							(int)*(short *)(param_2 + 0x3f8) >> 8,
							
							// param_2
							8);

  // zero in all arcade maps, idk adv, battle, cutscene, or credits
  uVar11 = (uint)*(byte *)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0x18c) << 8;
  
  if (*(byte *)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0x18c) == 0) 
  {
    uVar11 = 0x3700;
  }
  else 
  {
    if (0x5000 < uVar11) 
	{
      uVar11 = 0x5000;
    }
  }
  
  uVar12 = iVar2 - iVar7;
  if ((int)uVar11 < iVar2 - iVar7) {
    uVar12 = uVar11;
  }
  
  // max value for movementY (on stack)
  if ((int)local_24 < (int)uVar12) 
  {
	// set movementY to the speed that 
	// you should have, on first frame of jump
    local_24 = uVar12;
  }

// [end of the first frame of jump]
  
// skip here if not jumping
LAB_80060e1c:
  
  // VehPhysCrash_ConvertVecToSpeed
  FUN_8005cd1c(param_2,&local_28,0);
  
  // decrease speed
  iVar7 = *(ushort *)(param_2 + 0x38c) - uVar13;
  *(undefined2 *)(param_2 + 0x38c) = (short)iVar7;
  if (iVar7 * 0x10000 < 0) {
    *(undefined2 *)(param_2 + 0x38c) = 0;
  }
  
  iVar7 = (int)*(short *)(param_2 + 0x38e);
  
  if (iVar7 < 0) {
    if (iVar7 < 0) {
      iVar7 = -iVar7;
    }
    if (iVar7 < 0x100) {
      sVar6 = *(short *)(param_2 + 0x36e) - (*(short *)(param_2 + 0x36e) >> 3);
    }
    else {
      sVar6 = (short)((int)*(short *)(param_2 + 0x36e) * 0xd +
                      (*(uint *)(PTR_DAT_8008d2ac + 0x1cec) & 7) * 0x300 >> 4);
    }
  }
  else {
    sVar6 = (short)((int)*(short *)(param_2 + 0x36e) * 0xd + iVar7 * 3 >> 4);
  }
  *(short *)(param_2 + 0x36e) = sVar6;
  return;
}


// VehPhysGeneral_SetHeldItem
void FUN_80060f0c(int param_1)
{
  char cVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  
  // refer to chart
  // https://media.discordapp.net/attachments/637616020177289236/982513721354092564/unknown.png?width=602&height=431

  //iVar4 = Place division
  iVar4 = -1;

  // If you're not in Battle Mode
  if ((*(uint *)PTR_DAT_8008d2ac & 0x20) == 0) {
    // If you're not in Crystal Challenge (in adventure mode)
    if ((*(uint *)PTR_DAT_8008d2ac & 0x8000000) == 0) {
      // number of Drivers + number of AIs
      switch((uint)(byte)PTR_DAT_8008d2ac[0x1ca8] + (uint)(byte)PTR_DAT_8008d2ac[0x1cab]) {
      // 2P VS
      // 1P Boss Race
      case 2:
        //if racer is 2nd, give 7th Place division
        iVar4 = 7;

        //if racer is 1st, give 1st Place division
        if (*(short *)(param_1 + 0x482) == 0) {
LAB_80061060:
          iVar4 = 0;
        }
        break;

      // 3P Splitscreen
      // 3 Players
      case 3:
        //if driver is 1st, give 1st Place division
        if (*(short *)(param_1 + 0x482) == 0) goto LAB_80061060;

        //if driver is 3rd, give 4th Place division
        iVar4 = 3;

        //if driver is 2nd, give 2nd or 3rd Place division (~50% chance)
        if (*(short *)(param_1 + 0x482) == 1) {
          //iVar4 = 3rd Place division
          iVar4 = 2;

          //Get random number to decide Place division
          uVar3 = FUN_8003ea28();

          //if the number is odd (~50% chance)
          if ((uVar3 & 1) != 0)
		      {
            //iVar4 = 2nd Place division
            goto LAB_80061040;
          }
        }
        break;

      // 4P Splitscreen
      // 4 Players
      case 4:
        //give (place in race)th Place division
        iVar4 = (int)*(short *)(param_1 + 0x482);
        break;

      // Purple Gem Cup
      // 1 player, 4 AIs
      case 5:
        //give (place in race)th Place division
        iVar4 = (int)*(short *)(param_1 + 0x482);

        //if racer is 5th
        if (iVar4 == 4) {
          //make 5th count in 4th Place division
          iVar4 = 3;
        }
        break;

      // 2P Splitscreen
      // 2 players, 4 AIs
      case 6:
        //give (place in race)th Place division
        iVar4 = (int)*(short *)(param_1 + 0x482);

        //if racer is in 1st place, give 1st Place division
        if (iVar4 == 0) goto LAB_80061060;

        //if racer is 6th
        if (iVar4 == 5) {
          //make it count in 4th Place division
          iVar4 = 3;
        }
        // if racer is not 1st or 6th
        else {
          //give Place division 2nd / 3rd
          iVar4 = (iVar4 + -1) / 2 + 1;
        }
        break;

      // 1P Arcade, Adventure
      // 1 player, 7 AIs
      case 8:
        //iVar2 = place in race * 0x10000
        iVar2 = (uint)*(ushort *)(param_1 + 0x482) << 0x10;
        //iVar4 = place in race
        iVar4 = iVar2 >> 0x10;
        //if racer is second
        if (iVar4 == 1) {
LAB_80061040:
          //give 2nd Place division
          iVar4 = 1;
        }
        else {
          //give Place division 1st to 4th
          iVar4 = iVar4 - (iVar2 >> 0x1f) >> 1;
        }
      }
    }
    // if you are in Crystal Challenge
    else {
      iVar4 = 6;
    }
  }
  // If you are in Battle Mode
  else
  {
	// battle, custom weapon set
    iVar4 = 5;

	// battle, default set
    if (*(int *)(PTR_DAT_8008d2ac + 0x1da0) == 0x34de) {
      iVar4 = 4;
    }
  }

  //simulate you're in 3rd Place division instead of 4th in first lap
  if ((iVar4 == 3) && (*(char *)(param_1 + 0x44) == '\0')) {
    iVar4 = 2;
  }

  // Get random number to decide item
  iVar2 = FUN_8003ea28();
  // Reduce random number to a range of 0 - 199
  uVar3 = (iVar2 >> 3) % 200;

  //based on Place division and a 1-200 number, give item
  switch(iVar4)
  {

  //if you're in 1st Place division
  case 0:
	// weapon = RNG/10 (range of 0 - 19)
    *(undefined *)(param_1 + 0x36) = (&DAT_80089b6c)[uVar3 / 10];
    break;

  //if you're in 2nd Place division
  case 1:
	// weapon = (range of 0 - 52)
    *(undefined *)(param_1 + 0x36) = (&DAT_80089b80)[(uVar3 * 0x34) / 200];
    break;

  //if you're in 3rd Place division
  case 2:
    // weapon = RNG/10 (range of 0 - 19)
    *(undefined *)(param_1 + 0x36) = (&DAT_80089bb4)[uVar3 / 10];
    break;

  //if you're in 4th Place division (last place: arcade, VS, not Boss, etc)
  case 3:
    // weapon = (range of 0 - 18)
    *(undefined *)(param_1 + 0x36) = (&DAT_80089bc8)[(uVar3 * 0x13) / 200];
    break;

  // Battle, default set
  case 4:
	// weapon = RNG/10 (range of 0 - 19)
    *(undefined *)(param_1 + 0x36) = (&DAT_80089bf0)[uVar3 / 10];
    break;

  // Battle, custom set
  case 5:
	// weapon = RNG out of custom (int) array
    *(undefined *)(param_1 + 0x36) =
         PTR_DAT_8008d2ac[((int)(uVar3 * *(int *)(PTR_DAT_8008d2ac + 0x1df0)) / 200) * 4 + 0x1df4];
    break;

  // If you are in Crystal Challenge
  case 6:
		// Only true at Rocky Road and Nitro Court
    if (
			// if Level ID is not 21 (Skull Rock)
			(*(int *)(PTR_DAT_8008d2ac + 0x1a10) != 0x15) &&
			(
				// Item = Bomb
				cVar1 = '\x01',
				// if Level ID is not 19 (Rampage Ruins)
				*(int *)(PTR_DAT_8008d2ac + 0x1a10) != 0x13
			)
		) goto LAB_800612c4;
    // Only true at Skull Rock and Rampage Ruins
    //set held Item to Turbo
    *(undefined *)(param_1 + 0x36) = 0;
    break;

  //if racer is 2nd in a 2 racer race
  //7th Place division
  case 7:
    *(undefined *)(param_1 + 0x36) = (&DAT_80089bdc)[uVar3 / 10];
    break;

  //-1st Place division (place in race is 0xFFFF when not decided)
  default:
    // Get random number
    iVar4 = FUN_8003ea28();
    // Pick a random Item
    cVar1 = (char)iVar4 + ((char)(iVar4 / 6 + (iVar4 >> 0x1f) >> 1) - (char)(iVar4 >> 0x1f)) * -0xc;
LAB_800612c4:
  	// Give racer said Item
    *(char *)(param_1 + 0x36) = cVar1;
  }

  // If you're in a Boss Race
  // 0x80000000
  if (*(int *)PTR_DAT_8008d2ac < 0)
  {
    //cVar1 = Times lost against boss
    cVar1 = (&DAT_8008fbeb)[*(int *)(PTR_DAT_8008d2ac + 0x1eb8)];

    if (cVar1 < '\x03')
    {
      //if Held item is Mask, Clock or Warpball
      if ((uint)*(byte *)(param_1 + 0x36) - 7 < 3)
      {
        //replace Held item with 3 Missiles
        *(undefined *)(param_1 + 0x36) = 0xb;
      }
    }
    else
    {
      if (cVar1 < '\x04')
      {
        //if Held item is Mask or Clock
        if ((uint)*(byte *)(param_1 + 0x36) - 7 < 2)
        {
		      //replace Held item with 3 Missiles
          *(undefined *)(param_1 + 0x36) = 0xb;
        }
      }
      else
      {
        if (
				  (cVar1 < '\x05') &&
				  //if Held item is Clock (\b = Backspace, 0x8 in ASCII)
				  (*(char *)(param_1 + 0x36) == '\b')
        )
        {
		      //replace Held item with 3 Missiles
          *(undefined *)(param_1 + 0x36) = 0xb;
        }
      }
    }

    // If Level ID is 1
    // If you're at Dragon Mines
    if (*(int *)(PTR_DAT_8008d2ac + 0x1a10) == 1)
    {
      // Get your current Item
      cVar1 = *(char *)(param_1 + 0x36);

      //if Held item is not 3 Missiles
      //skip next 2 lines of code
      if (cVar1 != '\v') goto LAB_800613a4;
      //if Held item is 3 Missiles
      //replace it with 1 Missile
      *(undefined *)(param_1 + 0x36) = 2;
    }
  }

  // Get your current Item
  cVar1 = *(char *)(param_1 + 0x36);
LAB_800613a4:

  // If Item ID is unused Spring powerup
  if (cVar1 == '\x05')
  {
    // Change Item to Turbo
    *(undefined *)(param_1 + 0x36) = 0;
  }

  // if Item is warpball
  // Make sure Warpball is only used once per race
  if (*(char *)(param_1 + 0x36) == '\t')
  {
    //if 13th flag of 0x96B20 is off (means there isn't a warpball held / waddling around)
    if ((*(uint *)PTR_DAT_8008d2ac & 0x1000) == 0)
    {
      //turn 13th flag of 0x96B20 on (means warpball is active)
      *(uint *)PTR_DAT_8008d2ac = *(uint *)PTR_DAT_8008d2ac | 0x1000;
    }
    // if warpball is held or waddling around
    else
    {
      //change Item to 3 missiles to prevent having two warpballs waddling around at once
      *(undefined *)(param_1 + 0x36) = 0xb;
    }
  }

  // To prevent having too many missiles,
  // If you are in 3P or 4P mode, make it
  // so a maximum of 2 players can have
  // multiple missiles, during "normal race"

  if (
		(
			// If numPlyrCurrGame is more than 2 and
			(2 < (byte)PTR_DAT_8008d2ac[0x1ca8]) &&

			// you're not in Battle Mode, and
			((*(uint *)PTR_DAT_8008d2ac & 0x20) == 0)
		) &&
		// racer has 3 missiles
		(*(char *)(param_1 + 0x36) == '\v')
	)
	{
		// If there aren't already 2 players with 3 missiles
		if (*(int *)(PTR_DAT_8008d2ac + 0x1ec4) < 2)
		{
			// increment number of players with 3 missiles
			*(int *)(PTR_DAT_8008d2ac + 0x1ec4) = *(int *)(PTR_DAT_8008d2ac + 0x1ec4) + 1;
		}

		// if 2 players already have 3 missiles
		else
		{
			// Change Item to one missile
			*(undefined *)(param_1 + 0x36) = 2;
		}
  }

  //if Held item is either 3 Bombs or 3 Missiles
  //- 10 < 2 is intended in the formula because unsigned negatives are not < 2
  //(Items available excluding Invisibility and Super Engine)
  if ((uint)*(byte *)(param_1 + 0x36) - 10 < 2) {
    //set Held item Quantity to 3
    *(undefined *)(param_1 + 0x37) = 3;
  }
  return;
}



// VehPhysGeneral_GetBaseSpeed
int FUN_80061488(int param_1)
{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;

  //iVar3 = Wumpa count, assume max of 9
  iVar3 = (int)*(char *)(param_1 + 0x30);
  if (9 < iVar3) {
    iVar3 = 9;
  }

  // Turbo multiplier, limit to 5,
  // part of Super Engine from beta builds
  // still used?
  iVar4 = (int)*(char *)(param_1 + 0x35);
  if (5 < iVar4) {
    iVar4 = 5;
  }

  //iVar2 = Character's Speed stat
  iVar2 = (int)*(short *)(param_1 + 0x42c);

  //iVar1 = Net Speed stat
  //iVar1 = (((Negative Speedometer offset - Character's Speed stat) * 0x1000) / 5) - 1
  iVar1 = ((*(short *)(param_1 + 0x42e) - iVar2) * 0x1000) / 5 + -1;

  //iVar3 = Speed Additional
  //iVar3 = ((Wumpa count * Net Speed stat) / 10) + (Speed multiplier * Net Speed stat) >> 0xC
  iVar3 = (iVar3 * iVar1) / 10 + iVar4 * iVar1 >> 0xc;

  //if racer is using mask weapon
  if ((*(uint *)(param_1 + 0x2c8) & 0x800000) != 0) {
    //add Mask speed Constant to Speed Additional
    iVar3 = iVar3 + *(short *)(param_1 + 0x436);
  }

  //if racer has reserves
  if (*(short *)(param_1 + 0x3e2) != 0) {
    //iVar4 = Net Speed cap
    //iVar4 = (Sacred fire Cap * 2 - Single turbo Cap) - Current Speed cap
    iVar4 = ((int)*(short *)(param_1 + 0x432) * 2 - (int)*(short *)(param_1 + 0x430)) -
            (int)*(short *)(param_1 + 0x3e4);

    //iVar2 = Stat Additional
    //iVar2 = Gross Speed stat + Current Speed cap
    iVar2 = iVar2 + (int)*(short *)(param_1 + 0x3e4);

    //prevent Net Speed cap from going negative
    if (iVar4 < 0) {
      iVar4 = 0;
    }

    //prevent Speed from going above Speed cap
    //if Speed Additional > Net Speed cap
    if (iVar4 < iVar3) {
      //Speed Additional = Net Speed cap
      iVar3 = iVar4;
    }
  }
  //iVar4 is not Net Speed cap anymore
  //iVar4 will now be some form of Damaged speed Constant
  iVar4 = 0;

  //if racer has TNT over them
  if (*(int *)(param_1 + 0x18) != 0) {
    //iVar4 = Damaged speed Constant/2
    iVar4 = (int)((uint)*(ushort *)(param_1 + 0x438) << 0x10) >> 0x11;
  }

  //if racer is burnt or squished, or 0x50A = 0
  if (((*(short *)(param_1 + 0x402) != 0) || (*(short *)(param_1 + 0x404) != 0)) ||
     (*(short *)(param_1 + 0x50a) == 0)) {
    //iVar4 = Damaged speed Constant
    //iVar4 = 0x1000
    iVar4 = (int)*(short *)(param_1 + 0x438);
  }

  //if racer is affected by Clock item and
    //definition: iVar1 = Damaged speed Constant * ((0x14 - Place in race) >> 4)
    //(iVar1 = Damaged speed Constant (0x1000) when racer is 1st to 5th, iVar1 = 0 when 6th to 8th),
  //iVar4 < iVar1 (if racer has a TNT over them)
  if ((*(short *)(param_1 + 0xc) != 0) && (iVar1 = (int)*(short *)(param_1 + 0x438) *
    (0x14 - (int)*(short *)(param_1 + 0x482)) >> 4, iVar4 < iVar1)) {
    //correct 0x800 to 0x1000
    iVar4 = iVar1;
  }

  //iVar4 = Net Speed
  //iVar4 = (Stat Additional + Speed Additional) - Damaged speed Constant
  iVar4 = (iVar2 + iVar3) - iVar4;

  //if Net Speed is higher than USF Speed
  if (0x6400 < iVar4) {
    //prevent Speed from going over USF Speed
    iVar4 = 0x6400;
  }
  //return Net Speed for racer
  return iVar4;
}


// VehPhysJoystick_ReturnToRest
int FUN_8006163c(int param_1,undefined4 param_2,short *param_3)

{
  int iVar1;
  int iVar2;
  int iVar3;

  // if not using racing wheel
  if (param_3 == (short *)0x0)
  {
	// deadzone
    iVar2 = 0x30;

	// range
    iVar3 = 0x7f;

	// center of wheel
    iVar1 = 0x80;
  }

  // if using racing wheel
  else
  {
	// deadzone
    iVar2 = (int)param_3[1];

	// range
    iVar3 = (int)param_3[2];

	// center of wheel
    iVar1 = (int)*param_3;
  }

  // convert from [0,0xff] to [-0x7f,0x7f]
  param_1 = param_1 - iVar1;

  // negative strength
  if (param_1 < 0) 
  {
	// map value
    iVar1 = FUN_80058f9c(
				-param_1, 		// [stickVal]
				iVar2, iVar3,	// [deadzone, range]
				0, param_2		// [0, const 0x80 (halfway lerp)]
			);
    iVar1 = -iVar1;
  }
  
  // positive strength
  else 
  {
	// map value
    iVar1 = FUN_80058f9c(
				param_1, 		// [stickVal]
				iVar2,iVar3,	// [deadzone, range]
				0, param_2		// [0, const 0x80 (halfway lerp)]
			);
  }
  return iVar1;
}


// param_1 is desired steer strength
// param_2 is max possible steer
// param_3 RacingWheelData struct

// VehPhysJoystick_GetStrength
// can only be positive (negated elsewhere)
int FUN_800616b0(int param_1,int param_2,int param_3)

{
  int iVar1;
  int iVar2;
  int iVar3;

  // dead zone
  iVar1 = 0x30;

  // if not using a racing wheel
  if (param_3 == 0)
  {
	// range of steering
    iVar2 = 0x7f;

	// RangeMinusDeadzone
    iVar3 = 0x5e;
  }

  // if using a racing wheel
  else
  {
	// dead zone
    iVar1 = (int)*(short *)(param_3 + 2);

	// range
	iVar2 = (int)*(short *)(param_3 + 4);

	// RangeMinusDeadzone
	iVar3 = iVar2 - iVar1;
  }

  // if desired steer < Deadzone
  if (param_1 < iVar1)
  {
	// dont steer
    return 0;
  }

  // SteerMinusDeadzone
  iVar1 = param_1 - iVar1;

  // if desired steer > Range
  if (iVar2 <= param_1)
  {
	// default to max desired steer
    return param_2;
  }

  // if SteerMinusDeadzone >= Half RangeMinusDeadzone
  if (iVar3 / 2 <= iVar1) 
  {
    iVar1 = (iVar1 - iVar3 / 2) * (param_2 - param_2 / 5) * 2;
    
	// check error
	if (iVar3 == 0) trap(0x1c00);
    if ((iVar3 == -1) && (iVar1 == -0x80000000)) trap(0x1800);
    
    return iVar1 / iVar3 + param_2 / 5;
  }
  
  // if SteerMinusDeadzone < Half RangeMinusDeadzone
  
  iVar1 = iVar1 * (param_2 / 5) * 2;
  
  // check error
  if (iVar3 == 0) trap(0x1c00);
  if ((iVar3 == -1) && (iVar1 == -0x80000000)) trap(0x1800);
  
  // xxx / RangeMinusDeadzone
  return iVar1 / iVar3;
}


// param_1 is steer
//		DPAD: 00 for left, 80 for neutral, FF for right
//		Analog: anything 00 - FF
// param_2 is max possible steer
// param_3 RacingWheelData struct

// VehPhysJoystick_GetStrengthAbsolute
// can be positive or negative
int FUN_800617cc(int param_1,undefined4 param_2,short *param_3)

{
  int iVar1;

  // center steering
  iVar1 = 0x80;

  // if racing wheel data exists
  if (param_3 != (short *)0x0)
  {
	// get center of wheel
    iVar1 = (int)*param_3;
  }

  // if steering right
  if (param_1 - iVar1 < 0)
  {
	// VehPhysJoystick_GetStrength
    iVar1 = FUN_800616b0(-(param_1 - iVar1), param_2, param_3);

	// negate result to steer right
	iVar1 = -iVar1;
  }

  // if steer left
  else
  {
	// VehPhysJoystick_GetStrength
    iVar1 = FUN_800616b0(param_1 - iVar1, param_2, param_3);
  }

  // steer result
  return iVar1;
}



// VehPhysProc_Driving_PhysLinear
void FUN_8006181c(int param_1,int param_2)
{
  char cVar1;
  char cVar2;
  short sVar3;
  bool bVar4;
  undefined *puVar5;
  ushort uVar6;
  undefined2 uVar7;
  int iVar8;
  uint uVar9;
  int iVar10;
  int iVar11;
  undefined4 *puVar12;
  short sVar13;
  int iVar14;
  uint uVar15;
  undefined4 uVar16;
  undefined uVar17;
  ushort uVar18;
  int iVar19;
  uint uVar20;
  int iVar21;
  uint uVar22;
  int iVar23;
  undefined *puVar24;
  uint local_38;
  uint local_34;

  // If race timer is not supposed to stop for this racer
  if ((*(uint *)(param_2 + 0x2c8) & 0x40000) == 0)
  {
	// set racer's timer to the time on the clock
    *(undefined4 *)(param_2 + 0x514) = *(undefined4 *)(PTR_DAT_8008d2ac + 0x1d10);
  }

  // elapsed milliseconds per frame, ~32
  iVar14 = *(int *)(PTR_DAT_8008d2ac + 0x1d04);

  // negative elapsed milliseconds per frame
  iVar8 = -iVar14;

  if (
		// time on the clock
		(*(int *)(PTR_DAT_8008d2ac + 0x1d10) < 0x8ca00) &&

		// race timer is not frozen for this player
		((*(uint *)(param_2 + 0x2c8) & 0x40000) == 0)
	  )
  {
	// increment timer by (speed * time)
    *(int *)(param_2 + 0x518) =
    *(int *)(param_2 + 0x518) + 
		(*(short *)(param_2 + 0x38e) * iVar14 >> 8);
  }

  // Next 7 lines are repetitive, this time for Reserves (0x3e2)
  // Make "desired" amount by subtracting elapsed time from "current" amount,
  // store desired into iVar11, then copy it into iVar7. If current is more than 0,
  // then handle subtraction. In subtraction, make sure desired is not negative,
  // then set current to desired

  iVar11 = (int)*(short *)(param_2 + 0x3e2) + iVar8;
  uVar7 = (undefined2)iVar11;
  if (0 < (int)*(short *)(param_2 + 0x3e2)) {
    if (iVar11 < 0) {
      uVar7 = 0;
    }
    *(undefined2 *)(param_2 + 0x3e2) = uVar7;

    //adds *spent* Reserves to cumulative counter
    *(int *)(param_2 + 0x534) = *(int *)(param_2 + 0x534) + iVar14;
  }

  // Next 7 lines are repetitive, this time for Outside Turbo Timer (0x3de)
  // Make "desired" amount by subtracting elapsed time from "current" amount,
  // store desired into iVar11, then copy it into iVar7. If current is more than 0,
  // then handle subtraction. In subtraction, make sure desired is not negative,
  // then set current to desired

  iVar11 = (int)*(short *)(param_2 + 0x3de) + iVar8;
  uVar7 = (undefined2)iVar11;
  if (0 < (int)*(short *)(param_2 + 0x3de)) {
    if (iVar11 < 0) {
      uVar7 = 0;
    }
    *(undefined2 *)(param_2 + 0x3de) = uVar7;
  }

  // Next 7 lines are repetitive, this time for Outside Turbo Sound (0x3e0)
  // Make "desired" amount by subtracting elapsed time from "current" amount,
  // store desired into iVar11, then copy it into iVar7. If current is more than 0,
  // then handle subtraction. In subtraction, make sure desired is not negative,
  // then set current to desired

  iVar11 = (int)*(short *)(param_2 + 0x3e0) + iVar8;
  uVar7 = (undefined2)iVar11;
  if (0 < (int)*(short *)(param_2 + 0x3e0)) {
    if (iVar11 < 0) {
      uVar7 = 0;
    }
    *(undefined2 *)(param_2 + 0x3e0) = uVar7;
  }

  // Next 7 lines are repetitive, this time for Collision (0x3fe)
  // Make "desired" amount by subtracting elapsed time from "current" amount,
  // store desired into iVar11, then copy it into iVar7. If current is more than 0,
  // then handle subtraction. In subtraction, make sure desired is not negative,
  // then set current to desired

  iVar11 = (int)*(short *)(param_2 + 0x3fe) + iVar8;
  uVar7 = (undefined2)iVar11;
  if (0 < (int)*(short *)(param_2 + 0x3fe)) {
    if (iVar11 < 0) {
      uVar7 = 0;
    }
    *(undefined2 *)(param_2 + 0x3fe) = uVar7;

	// Add elapsed time to a counter for how long you've driven against a wall
    *(int *)(param_2 + 0x530) = *(int *)(param_2 + 0x530) + iVar14;
  }

  // Next 7 lines are repetitive, this time for Jump Animation (0x3f6)
  // Make "desired" amount by subtracting elapsed time from "current" amount,
  // store desired into iVar11, then copy it into iVar7. If current is more than 0,
  // then handle subtraction. In subtraction, make sure desired is not negative,
  // then set current to desired

  iVar11 = (int)*(short *)(param_2 + 0x3f6) + iVar8;
  uVar7 = (undefined2)iVar11;
  if (0 < (int)*(short *)(param_2 + 0x3f6)) {
    if (iVar11 < 0) {
      uVar7 = 0;
    }
    *(undefined2 *)(param_2 + 0x3f6) = uVar7;
  }

  // Next 7 lines are repetitive, this time for Unknown (0x3f2)
  // Make "desired" amount by subtracting elapsed time from "current" amount,
  // store desired into iVar11, then copy it into iVar7. If current is more than 0,
  // then handle subtraction. In subtraction, make sure desired is not negative,
  // then set current to desired

  iVar11 = (int)*(short *)(param_2 + 0x3f2) + iVar8;
  uVar7 = (undefined2)iVar11;
  if (0 < (int)*(short *)(param_2 + 0x3f2)) {
    if (iVar11 < 0) {
      uVar7 = 0;
    }
    *(undefined2 *)(param_2 + 0x3f2) = uVar7;
  }

  // Next 7 lines are repetitive, this time for Unknown (0x3fa)
  // Make "desired" amount by subtracting elapsed time from "current" amount,
  // store desired into iVar11, then copy it into iVar7. If current is more than 0,
  // then handle subtraction. In subtraction, make sure desired is not negative,
  // then set current to desired

  iVar11 = (int)*(short *)(param_2 + 0x3fa) + iVar8;
  uVar7 = (undefined2)iVar11;
  if (0 < (int)*(short *)(param_2 + 0x3fa)) {
    if (iVar11 < 0) {
      uVar7 = 0;
    }
    *(undefined2 *)(param_2 + 0x3fa) = uVar7;
  }

  // Next 7 lines are repetitive, this time for Burnt Effect Timer (0x402)
  // Make "desired" amount by subtracting elapsed time from "current" amount,
  // store desired into iVar11, then copy it into iVar7. If current is more than 0,
  // then handle subtraction. In subtraction, make sure desired is not negative,
  // then set current to desired

  iVar11 = (int)*(short *)(param_2 + 0x402) + iVar8;
  uVar7 = (undefined2)iVar11;
  if (0 < (int)*(short *)(param_2 + 0x402)) {
    if (iVar11 < 0) {
      uVar7 = 0;
    }
    *(undefined2 *)(param_2 + 0x402) = uVar7;

	// increment timer for total frames burnt
    *(int *)(param_2 + 0x54c) = *(int *)(param_2 + 0x54c) + iVar14;
  }

  // Next 7 lines are repetitive, this time for Squished Effect Timer (0x404)
  // Make "desired" amount by subtracting elapsed time from "current" amount,
  // store desired into iVar11, then copy it into iVar7. If current is more than 0,
  // then handle subtraction. In subtraction, make sure desired is not negative,
  // then set current to desired

  iVar11 = (int)*(short *)(param_2 + 0x404) + iVar8;
  uVar7 = (undefined2)iVar11;
  if (0 < (int)*(short *)(param_2 + 0x404)) {
    if (iVar11 < 0) {
      uVar7 = 0;
    }
    *(undefined2 *)(param_2 + 0x404) = uVar7;

	// increment timer for total frames squished
    *(int *)(param_2 + 0x544) = *(int *)(param_2 + 0x544) + iVar14;
  }

  // Next 7 lines are repetitive, this time for Unknown (0x406)
  // Make "desired" amount by subtracting elapsed time from "current" amount,
  // store desired into iVar11, then copy it into iVar7. If current is more than 0,
  // then handle subtraction. In subtraction, make sure desired is not negative,
  // then set current to desired

  iVar11 = (int)*(short *)(param_2 + 0x406) + iVar8;
  uVar7 = (undefined2)iVar11;
  if (0 < (int)*(short *)(param_2 + 0x406)) {
    if (iVar11 < 0) {
      uVar7 = 0;
    }
    *(undefined2 *)(param_2 + 0x406) = uVar7;
  }

  // Next 7 lines are repetitive, this time for Unknown (0x408)
  // Make "desired" amount by subtracting elapsed time from "current" amount,
  // store desired into iVar11, then copy it into iVar7. If current is more than 0,
  // then handle subtraction. In subtraction, make sure desired is not negative,
  // then set current to desired

  iVar11 = (int)*(short *)(param_2 + 0x408) + iVar8;
  uVar7 = (undefined2)iVar11;
  if (0 < (int)*(short *)(param_2 + 0x408)) {
    if (iVar11 < 0) {
      uVar7 = 0;
    }
    *(undefined2 *)(param_2 + 0x408) = uVar7;
  }

  // If Super Engine Cheat is not enabled
  if ((*(uint *)(PTR_DAT_8008d2ac + 8) & 0x10000) == 0)
  {
	// Next 7 lines are repetitive, this time for Super Engine Timer (0x38)
	// Make "desired" amount by subtracting elapsed time from "current" amount,
	// store desired into iVar11, then copy it into iVar7. If current is more than 0,
	// then handle subtraction. In subtraction, make sure desired is not negative,
	// then set current to desired

    iVar11 = (int)*(short *)(param_2 + 0x38) + iVar8;
    uVar7 = (undefined2)iVar11;
    if (0 < (int)*(short *)(param_2 + 0x38)) {
      if (iVar11 < 0) {
        uVar7 = 0;
      }
      *(undefined2 *)(param_2 + 0x38) = uVar7;
    }
  }

  // Next 7 lines are repetitive, this time for Clock Weapon Timer (0xC)
  // Make "desired" amount by subtracting elapsed time from "current" amount,
  // store desired into iVar11, then copy it into iVar7. If current is more than 0,
  // then handle subtraction. In subtraction, make sure desired is not negative,
  // then set current to desired

  iVar11 = (int)*(short *)(param_2 + 0xc) + iVar8;
  uVar7 = (undefined2)iVar11;
  if (0 < (int)*(short *)(param_2 + 0xc)) {
    if (iVar11 < 0) {
      uVar7 = 0;
    }
    *(undefined2 *)(param_2 + 0xc) = uVar7;
  }

  // Next 7 lines are repetitive, this time for "Mashing X makes it big" (0x3c0)
  // Make "desired" amount by subtracting elapsed time from "current" amount,
  // store desired into iVar11, then copy it into iVar7. If current is more than 0,
  // then handle subtraction. In subtraction, make sure desired is not negative,
  // then set current to desired

  iVar11 = (int)*(short *)(param_2 + 0x3c0) + iVar8;
  uVar7 = (undefined2)iVar11;
  if (0 < (int)*(short *)(param_2 + 0x3c0)) {
    if (iVar11 < 0) {
      uVar7 = 0;
    }
    *(undefined2 *)(param_2 + 0x3c0) = uVar7;
  }

  // This one is a frame timer, not a millisecond timer,
  // Decrease one frame from Jump Buffering as long as timer is more than zero
  if (0 < *(short *)(param_2 + 0x3f0)) {
    *(short *)(param_2 + 0x3f0) = *(short *)(param_2 + 0x3f0) + -1;
  }

  //keep track of time spent with full wumpa
  if ('\t' < *(char *)(param_2 + 0x30)) {
    *(int *)(param_2 + 0x52c) = *(int *)(param_2 + 0x52c) + iVar14;
  }

  //keep track of time spent in mud
  if (*(char *)(param_2 + 0xc2) == '\x0e') {
    *(int *)(param_2 + 0x524) = *(int *)(param_2 + 0x524) + iVar14;
  }

  // Get placement of racer (1st place, 2nd, 3rd, etc)
  sVar13 = *(short *)(param_2 + 0x482);

  // Basically, if racer is in last place in any possible race scenario
  if (
		(
			(
				(
					// If racer is in 8th place
					(sVar13 == 7) &&

					// If numPlyrCurrGame is 1
					(PTR_DAT_8008d2ac[0x1ca8] == '\x01')
				) ||

				(
					(
						// If racer is in 6th place
						sVar13 == 5 &&

						// if numPlyrCurrGame is 2
						(PTR_DAT_8008d2ac[0x1ca8] == '\x02')
					)
				)
			) ||
			(
				(
					// if racer is in 4th place
					sVar13 == 3 &&

					// if numPlyrCurrGame is more than 2
					(2 < (byte)PTR_DAT_8008d2ac[0x1ca8])
				)
			)
		) &&
		(
			// race timer is not frozen for this player
			(*(uint *)(param_2 + 0x2c8) & 0x40000) == 0)
		)
  {
	// Increase the time racer has been in last place by elapsed milliseconds
    *(int *)(param_2 + 0x528) = *(int *)(param_2 + 0x528) + iVar14;
  }

  sVar13 = 4;

  // if you have a raincloud over your head from potion
  if (*(int *)(param_2 + 0x4a0) != 0) {
    sVar13 = *(short *)(*(int *)(*(int *)(param_2 + 0x4a0) + 0x30) + 6);
  }

  // get approximate speed
  iVar11 = (int)*(short *)(param_2 + 0x38e);

  // Action flags (isRaceOver, isTimeFrozen, etc)
  uVar22 = *(uint *)(param_2 + 0x2c8);

  // driver->clockReceive
  iVar19 = (int)*(short *)(param_2 + 0xc);

  *(short *)(param_2 + 0x50a) = sVar13;

  // absolute value of speed
  if (iVar11 < 0) {
    iVar11 = -iVar11;
  }

  if (
		(
			// if you are not impacted by clock weapon
			(iVar19 == 0) &&
			(
				// get squished timer
				iVar19 = (int)*(short *)(param_2 + 0x404),

				// if you are not squished
				iVar19 == 0
			)
		) &&
		(
			(
				sVar13 != 0 ||
				(
					// if time on the clock is zero
					iVar19 = *(int *)(PTR_DAT_8008d2ac + 0x1d10),
					iVar19 == 0
				)
			)
		)
	  )
  {
  	//uVar20 = Hazard Timer (sign extended 2 to 4 bytes)
    uVar20 = SEXT24(*(short *)(param_2 + 0xe));

	// hazard timer will not go
	// down unless you keep moving,
	// is this for red potion raincloud?

	// if you have high speed
    if (0x100 < iVar11)
	{
	  // decrease hazard by elapsed time
      uVar20 = uVar20 + iVar8;
    }

    uVar7 = (undefined2)(uVar20 & 0xfffffffe);
    if (-1 < (int)(uVar20 & 0xfffffffe)) {
      uVar7 = 0xfffe;
    }

    //Hazard Timer = uVar7
    *(undefined2 *)(param_2 + 0xe) = uVar7;
  }

  // if you are not impacted by hazard (other than clock)
  else {
    uVar18 = (ushort)iVar19;

	// if you are not touching the ground
    if ((uVar22 & 1) == 0)
	{
	  // if speed is low
      if (iVar11 < 0x101) goto LAB_80061cf8;

	  // if speed is high...

	  // absolute value of clock hazard
      if (iVar19 < 0) {
        uVar18 = -uVar18;
      }

LAB_80061d0c:
      uVar6 = -uVar18 | 1;
    }

	// if you are touching the ground
    else
	{
	  // if speed is low
      if (iVar11 < 0x101)
	  {
LAB_80061cf8:
				//uVar18 = Hazard Timer
        uVar18 = *(ushort *)(param_2 + 0xe);
        uVar6 = uVar18 | 1;
        if (0 < (short)uVar18) goto LAB_80061d0c;
      }

	  // if speed is high
      else
	  {
	    // absolute value of clock hazard
        if (iVar19 < 0) {
          uVar18 = -uVar18;
        }

		// Use trigonometry with speed and
		// clock timer to make the car waddle

        //iVar8 = Clock Item (Receive) Timer << 0x10
        iVar8 = (uint)*(ushort *)(param_2 + 0xc) << 0x10;

        iVar19 = iVar8 >> 0x16;
        if (0x40 < iVar19) {
          iVar19 = 0x40;
        }

        uVar20 = (iVar8 >> 0x10) << 4;

		// approximate trigonometry
        iVar8 = *(int *)(&DAT_800845a0 + (uVar20 & 0x3ff) * 4);

        if ((uVar20 & 0x400) == 0) {
          iVar8 = iVar8 << 0x10;
        }
        iVar8 = iVar8 >> 0x10;
        if ((uVar20 & 0x800) != 0) {
          iVar8 = -iVar8;
        }
        iVar21 = iVar11 >> 8;
        if (0x20 < iVar21) {
          iVar21 = 0x20;
        }

		// GAMEPAD_ShockForce1
		FUN_800264c0(param_2,4,iVar19 + (iVar8 >> 5) + iVar21 + 0x18);

        uVar6 = uVar18 | 1;
      }
    }
    //Hazard Timer = uVar6
    *(ushort *)(param_2 + 0xe) = uVar6;
  }

  //trigger Item roll / selection
  //if Held Item = None
  if (*(char *)(param_2 + 0x36) == '\x10') {

	//if Item roll is done
    if (*(short *)(param_2 + 0x3a) == 0)
		{
	  // Select a random weapon for driver
      FUN_80060f0c(param_2);

	  	// if 9 < number of wumpa
	  	// if wumpa is 10
      bVar4 = '\t' < *(char *)(param_2 + 0x30);

	  // if you have less than 10 wumpa

	  // "ding" sound
      uVar16 = 0x5e;

	  // if you have 10 wumpa
      if (bVar4)
	  {
		// "ka-ching" sound
        uVar16 = 0x41;
      }

      // OtherFX_Play of getting weapon
      FUN_80028468(uVar16,(uint)bVar4);
    }

	//if Item roll is not done
    else
	{
    	//Item roll Timer--
      *(short *)(param_2 + 0x3a) = *(short *)(param_2 + 0x3a) + -1;
    }
  }

  //sVar3 = No Item Timer
  sVar3 = *(short *)(param_2 + 0x3c);

  //if Item is going away
  if (sVar3 != 0) {

	//if Item is about to be gone and Number of Items = 0
    if ((sVar3 == 1) && (*(char *)(param_2 + 0x37) == '\0')) {

	  // if numPlyrCurrGame is > 2
	  if ((2 < (byte)PTR_DAT_8008d2ac[0x1ca8]) &&

		  // If you're not in Battle Mode
         ((((*(uint *)PTR_DAT_8008d2ac & 0x20) == 0 &&

		 // your weapon is 3 missiles
		 (*(char *)(param_2 + 0x36) == '\v')) &&

		  // If there are racers that had 3 missiles
          (0 < *(int *)(PTR_DAT_8008d2ac + 0x1ec4)))))
	  {
		// decrement the number of players that had 3 missiles
        *(int *)(PTR_DAT_8008d2ac + 0x1ec4) = *(int *)(PTR_DAT_8008d2ac + 0x1ec4) + -1;
      }

	  // take away weapon
      *(undefined *)(param_2 + 0x36) = 0xf;
    }

    //No Item Timer--
    *(short *)(param_2 + 0x3c) = sVar3 + -1;
  }

  // If Invinsibility effect is active (timer at 0x24)
  // Make "desired" timer by subtracting elapsed time from "current",
  // set "current" to "desired", then set "current" to zero if "desired" is negative

  if ((*(int *)(param_2 + 0x24) != 0) &&
     (iVar8 = *(int *)(param_2 + 0x24) - *(int *)(PTR_DAT_8008d2ac + 0x1d04),
     *(int *)(param_2 + 0x24) = iVar8, iVar8 < 0)) {
    *(undefined4 *)(param_2 + 0x24) = 0;
  }

  // If Invincibility effect is active (timer at 0x28) and if Cheat Code is Disabled
  // Make "desired" timer by subtracting elapsed time from "current",
  // set "current" to "desired", then set "current" to zero if "desired" is negative

  if (
		// if driver is invisible
		(*(int *)(param_2 + 0x28) != 0) &&

		// If Permanent Invisibility Cheat is Disabled
		((*(uint *)(PTR_DAT_8008d2ac + 8) & 0x8000) == 0)
	)
  {
	// decrease invisibility timer,
	// can not go below zero
    iVar8 = *(int *)(param_2 + 0x28) - *(int *)(PTR_DAT_8008d2ac + 0x1d04);
    *(int *)(param_2 + 0x28) = iVar8;
    if (iVar8 < 0) {
      *(undefined4 *)(param_2 + 0x28) = 0;
    }

	// If the timer expires, make yourself visible
    if (*(int *)(param_2 + 0x28) == 0)
	{
	  // restore backup of instance flags
      *(undefined4 *)(*(int *)(param_2 + 0x1c) + 0x28) = *(undefined4 *)(param_2 + 0x2c);

	  // set instance transparency to zero
      *(undefined2 *)(*(int *)(param_2 + 0x1c) + 0x22) = 0;

	  // OtherFX_Play
      FUN_80028468(0x62,1);
    }
  }

  // Random guess, this next block is probably for making a backup
  // of current position and rotation, to calculate linear + angular
  // velocity by comparing two frames

  *(undefined4 *)(param_2 + 0x2f4) = *(undefined4 *)(param_2 + 0x2ec);
  puVar24 = PTR_DAT_8008d2ac;
  
  // action flags
  *(uint *)(param_2 + 0x2cc) = uVar22;
  
  *(undefined4 *)(param_2 + 0x2e4) = *(undefined4 *)(param_2 + 0x2d8);
  *(undefined4 *)(param_2 + 0x2e8) = *(undefined4 *)(param_2 + 0x2dc);
  *(undefined2 *)(param_2 + 0x2f8) = *(undefined2 *)(param_2 + 0x2f0);
  *(undefined2 *)(param_2 + 0x392) = *(undefined2 *)(param_2 + 0x390);
  *(undefined2 *)(param_2 + 0x3c8) = *(undefined2 *)(param_2 + 0x3c6);
  *(undefined4 *)(param_2 + 0x2e0) = *(undefined4 *)(param_2 + 0x2d4);

  uVar20 = uVar22 & 0x7f1f83d5;
  
  // disable input if opening adv hub door with key
  if ((*(uint *)(puVar24 + 8) & 0x4004) != 0) goto LAB_800629f8;
  
  iVar19 = (uint)*(byte *)(param_2 + 0x380) + 1;
  uVar17 = (undefined)iVar19;
  
  // this is always zero, there's no possible
  // way for it not to be, so AxisAngle4
  iVar8 = iVar19 * 8;
  
  if (iVar19 != 0) {
    uVar17 = 0;
    iVar8 = 0;
  }
  
  // always AxisAngle4
  puVar12 = (undefined4 *)(param_2 + iVar8 + 0x378);
  
  // if not touching ground
  if ((uVar22 & 1) == 0) 
  {
	// AngleAxis2_NormalVec
    *puVar12 = *(undefined4 *)(param_2 + 0x368);
    *(undefined2 *)(puVar12 + 1) = *(undefined2 *)(param_2 + 0x36c);
  }
  
  // if touching ground
  else 
  {
	// AngleAxis1_NormalVec
    *puVar12 = *(undefined4 *)(param_2 + 0x360);
    *(undefined2 *)(puVar12 + 1) = *(undefined2 *)(param_2 + 0x364);
  }
  
  *(undefined *)(param_2 + 0x380) = uVar17;

  // driver -> instBubble
  iVar8 = *(int *)(param_1 + 0x14);

  uVar22 = uVar20;

  // loop through all, find mask if it exists
  while (iVar8 != 0)
  {
	// If thread->modelIndex is Aku or Uka
    if ((*(short *)(iVar8 + 0x44) == 0x3a) || (*(short *)(iVar8 + 0x44) == 0x39)) {
      uVar22 = uVar20 | 0x800000;
      break;
    }

	// check next bubble in linked list
    iVar8 = *(int *)(iVar8 + 0x10);
  }

  // pointer to gamepad input of current player (param_2)
  puVar24 = PTR_DAT_8008d2b0 + (uint)*(byte *)(param_2 + 0x4a) * 0x50;

  // by default, hold no buttons
  uVar20 = 0;

  // If you're not in End-Of-Race menu
  if ((*(uint *)PTR_DAT_8008d2ac & 0x200000) == 0)
  {
	// Get which button is held
    uVar20 = *(uint *)(puVar24 + 0x10);
  }

  // by default, tap no buttons
  uVar15 = 0;

  // If you're not in End-Of-Race menu
  if ((*(uint *)PTR_DAT_8008d2ac & 0x200000) == 0)
  {
	// Get which button is tapped
    uVar15 = *(uint *)(puVar24 + 0x14);
  }

  // If you hold Cross
  local_38 = uVar20 & 0x10;

  // If you hold Square
  local_34 = uVar20 & 0x20;

  // state of kart
  cVar1 = *(char *)(param_2 + 0x376);

  if (
		(
			// If you press circle
			((uVar15 & 0x40) != 0) &&


			(
				// if neutral driving
				((cVar1 == '\0' ||

				// or sliding
				(cVar1 == '\x02')) ||

				// or ???
				(cVar1 == '\t'))
			)
		) &&

		// if there is no tnt on your head
		(*(int *)(param_2 + 0x18) == 0)
	  )
  {
	// If there is no Bomb pointer
    if (*(int *)(param_2 + 0x10) == 0) {

	  // If there is no Bubble pointer
      if (*(int *)(param_2 + 0x14) == 0) {

		// If there is no "weapon roulette" animation
        sVar3 = *(short *)(param_2 + 0x3a);
        if (sVar3 == 0) {

		  // If you dont have "roulette" weapon (0x10), and if you dont have "no weapon" (0xf)
		  // and if you did not have a weapon last frame (0x3c->0),
		  // and if (unknown sVar13 related to 0x4a0),
		  // and if you are not being effected by Clock Weapon
          cVar2 = *(char *)(param_2 + 0x36);
          if (((cVar2 != '\x0f') && (cVar2 != '\x10')) &&
             ((*(short *)(param_2 + 0x3c) == 0 &&
              ((sVar13 != 1 && (*(short *)(param_2 + 0xc) == 0))))))
		  {
			// This driver wants to fire a weapon (0x2c8 flags)
            uVar22 = uVar22 | 0x8000;

			// If "held item quantity" is zero
            if (*(char *)(param_2 + 0x37) == '\0') 
			{
              *(undefined2 *)(param_2 + 0x3c) = 0x1e;
              goto LAB_800621cc;
            }

			// If you have the Spring weapon
            if (cVar2 == '\x05') 
			{
              if (*(short *)(param_2 + 0x3f4) != 0) {
                uVar9 = SEXT24(*(short *)(param_2 + 0x3f2));
                goto LAB_80062188;
              }
            }
            
			// any other weapon
			else 
			{
			  // CHEAT_MASK, CHEAT_TURBO, or CHEAT_BOMBS
              uVar9 = *(uint *)(PTR_DAT_8008d2ac + 8) & 0x400c00;
LAB_80062188:
			  // if cheats aren't enabled
              if (uVar9 == 0) 
			  {
				// reduce number of items held
                *(char *)(param_2 + 0x37) = *(char *)(param_2 + 0x37) + -1;
              }
            }
			
			// 5-frame cooldown before next weapon
            *(undefined2 *)(param_2 + 0x3c) = 5;
			
            goto LAB_800621cc;
          }
          sVar3 = *(short *)(param_2 + 0x3a);
        }

		// if there are less than 70 frames (2.3 sec remaining)
        if (sVar3 < 0x46)
		{
		  // skip to the end of the countdown
          *(undefined2 *)(param_2 + 0x3a) = 0;
        }
      }

	  // If there is a Bubble Pointer
      else
	  {
		// Shoot the bubble

		// We can see the bubble pointer (driver + 0x14)

		// instance -> thread -> object
        iVar8 = *(int *)(*(int *)(*(int *)(param_2 + 0x14) + 0x6c) + 0x30);

        *(ushort *)(iVar8 + 6) = *(ushort *)(iVar8 + 6) | 2;

		// Reset to nullptr
	   *(undefined4 *)(param_2 + 0x14) = 0;
      }
    }

	// If there is a Bomb Pointer
    else
	{
	  // Detonate the bomb

	  // We can see the bomb pointer (driver + 0x10)

	  // instance -> thread -> object
      iVar8 = *(int *)(*(int *)(*(int *)(param_2 + 0x10) + 0x6c) + 0x30);

	  // always face camera
	  *(ushort *)(iVar8 + 0x16) = *(ushort *)(iVar8 + 0x16) | 2;

	  // Reset to nullptr
      *(undefined4 *)(param_2 + 0x10) = 0;
    }
  }
LAB_800621cc:

  // Check for Tapping L1 and R1
  uVar15 = uVar15 & 0xc00;

  if (
		//if you're not pressing L1 or R1
		(uVar15 == 0) ||
		
		// or you are sliding
		(*(char *)(param_2 + 0x376) == '\x02')
	)
  {
    if (
			// If you are holding L1 or R1 and
			((uVar20 & 0xc00) != 0) &&
			(sVar13 != 3)
	  )
    {
      if ((uVar22 & 4) == 0)
	  {
		// 10 frame jump buffer
        *(undefined2 *)(param_2 + 0x3f0) = 10;
      }
      goto LAB_8006222c;
    }
    uVar22 = uVar22 & 0xfffffffb;
    if (0 < *(short *)(param_2 + 0x3f0)) {
      *(undefined2 *)(param_2 + 0x3f0) = 0;
    }
  }

  //if you're pressing jump buttons and not sliding
  else
  {
    //if L1 and R1 were being tapped at once
    if (uVar15 == 0xc00)
	{
      //set Last Jump button pressed to R1
      *(undefined2 *)(param_2 + 0x382) = 0x400;
    }

    //if you're not tapping L1 and R1 at once
    else
	{
      //Last Jump button pressed = uVar15
      *(undefined2 *)(param_2 + 0x382) = (short)uVar15;
    }

    if (sVar13 != 3)
	{
	  // 10 frame jump buffer
      *(undefined2 *)(param_2 + 0x3f0) = 10;
LAB_8006222c:
      uVar22 = uVar22 | 4;
    }
  }

  if (
		// If you are holding Square
		(local_34 != 0) &&

		// if you're not on any turbo pad
		((*(uint *)(param_2 + 0xbc) & 3) == 0)
	)
  {
	// Set Reserves to zero
    *(undefined2 *)(param_2 + 0x3e2) = 0;
  }

  // assume normal gas pedal
  iVar8 = 0x80;

  // If you're not in End-Of-Race menu
  if ((*(uint *)PTR_DAT_8008d2ac & 0x200000) == 0)
  {
	// gamepadBuffer -> stickRY (for gas or reverse)
    iVar8 = (int)*(short *)(puVar24 + 0xe);
  }

  if (
		// If Reserves are not zero
		(*(short *)(param_2 + 0x3e2) != 0) ||

		(sVar13 == 6)
	 )
  {
    if (
			// If you are not holding Cross
			(local_38 == 0) &&

			// VehPhysJoystick_ReturnToRest
			(iVar19 = FUN_8006163c(iVar8,0x80,0), -1 < iVar19)
		)
	{
      uVar22 = uVar22 | 0x400000;
    }


    if (
			// If are holding Square
			(local_34 != 0) &&

			(0x300 < iVar11)
		)
	{
      uVar22 = uVar22 | 0x800;
    }

	// if you're on any turbo pad
    if ((*(uint *)(param_2 + 0xbc) & 3) != 0)
	{
	  // assume not holding square until boost is over
      local_34 = 0;
    }

	// Assume you're holding Cross, because
	// you have Reserves and you aren't slowing down
    local_38 = 0x10;
  }

  iVar19 = 0x80;

  // If you're not in End-Of-Race menu
  if ((*(uint *)PTR_DAT_8008d2ac & 0x200000) == 0) 
  {
	// gamepadBuffer -> stickLY
    iVar19 = (int)*(short *)(puVar24 + 6);
  }

  if ((*(char *)(param_2 + 0x4b) < '\0') ||
     (uVar22 = uVar22 & 0xdfffffff, *(char *)(param_2 + 0x4b) < '\x01')) {
    uVar22 = uVar22 & 0xbfffffff;
  }
  iVar21 = (int)*(short *)(param_2 + 0x38e);
  if (iVar21 < 0) {
    iVar21 = -iVar21;
  }
  if (iVar21 < 0x300) {
    uVar22 = uVar22 & 0x9fffffff;
  }
  
  iVar21 = 0;
  
  // VehPhysGeneral_GetBaseSpeed
  iVar10 = FUN_80061488(param_2);
  uVar7 = (undefined2)iVar10;

  // If you are not holding Square
  if (local_34 == 0) {
    //iVar23 = Racer's Base Speed
    iVar23 = iVar10;

    // If you are holding Cross, or if you have Reserves
    if (local_38 != 0) {
LAB_8006253c:
      uVar22 = uVar22 & 0xfffdffff;
      goto LAB_80062548;
    }

    // if you are not holding cross, or have no Reserves...
    //iVar23 is replaced

	// VehPhysJoystick_ReturnToRest
    iVar23 = FUN_8006163c(iVar8,0x80,0);

	iVar8 = -iVar23;
    if (iVar23 < 1) {
      if ((iVar8 == 0) &&

		  // VehPhysJoystick_ReturnToRest
         ((iVar19 = FUN_8006163c(iVar19,0x80,0), 99 < iVar19 ||

		  ((0 < iVar19 && ((uVar22 & 0x20000) != 0))))))
	  {
		// driver is steering?
        uVar22 = uVar22 | 0x20000;
		
        iVar23 = -(int)*(short *)(param_2 + 0x434);
        goto LAB_80062548;
      }
      iVar8 = iVar10 * iVar8;
      iVar23 = iVar8 >> 7;
      if (iVar8 < 0) {
        iVar23 = iVar8 + 0x7f >> 7;
      }
      goto LAB_8006253c;
    }
    if ((*(short *)(param_2 + 0x38e) < 0x301) && ((uVar22 & 0x60000000) == 0)) {
      iVar8 = *(short *)(param_2 + 0x434) * iVar8;
      if (iVar8 < 0) {
        iVar8 = iVar8 + 0x7f;
      }
      iVar21 = iVar8 >> 7;
      uVar15 = 0x20000;
LAB_800625c4:
      uVar20 = uVar22 | uVar15;
    }
    else {
      uVar20 = uVar22 | 8;
      if ('\0' < *(char *)(param_2 + 0x4b)) {
        uVar20 = uVar22 | 0x40000008;
      }
      if (*(char *)(param_2 + 0x4b) < '\0') {
        uVar15 = 0x20000000;
        uVar22 = uVar20;
        goto LAB_800625c4;
      }
    }
  }
  // If you are holding Square
  else
  {
	// VehPhysJoystick_ReturnToRest
    iVar19 = FUN_8006163c(iVar19,0x80,0);

	if ((iVar19 < 100) && ((iVar19 < 1 || ((uVar22 & 0x20000) == 0))))
	{
	  // if you are not holding cross, and you have no Reserves
      if (local_38 == 0)
	  {
        // VehPhysJoystick_ReturnToRest
		iVar8 = FUN_8006163c(iVar8,0x80,0);

		iVar23 = iVar10 * -iVar8;
        if (iVar8 < 0) {
          if (iVar23 < 0) {
            iVar23 = iVar23 + 0xff;
          }
          iVar23 = iVar23 >> 8;
		  
		  // gas and breaks together
          uVar22 = uVar22 | 0x20;
		  
          goto LAB_80062548;
        }
		
        if (0 < iVar8) {
          iVar8 = (int)*(short *)(param_2 + 0x434) * -iVar8;
          iVar23 = iVar8 >> 8;
          if (iVar8 < 0) {
            iVar23 = iVar8 + 0xff >> 8;
          }
		  
		  // reversing, and gas+break
          goto LAB_8006248c;
        }
        uVar22 = uVar22 | 8;
        iVar23 = iVar21;
      }
      // If you are holding cross, or you have Reserves
      else {
        uVar22 = uVar22 | 0x20;
        iVar23 = iVar10 / 2;
      }
      goto LAB_8006253c;
    }
    iVar8 = (int)*(short *)(param_2 + 0x434) * -3;
    iVar23 = iVar8 >> 2;
    if (iVar8 < 0) {
      iVar23 = iVar8 + 3 >> 2;
    }
LAB_8006248c:
    uVar22 = uVar22 | 0x20020;
LAB_80062548:
    uVar20 = uVar22 & 0x9fffffff;
    //iVar21 = Racer's Base Speed
    iVar21 = iVar23;
  }
  
  if ((uVar20 & 0x20000) == 0) 
  {
    uVar22 = uVar20 & 8;
    if (*(short *)(param_2 + 0x38) != 0) {
      //if Racer is moving
      if (0 < iVar21) {
        uVar22 = uVar20 & 8;
        if ((uVar20 & 0x400020) != 0) goto LAB_80062648;

        // if you have less than 10 wumpa
        uVar16 = 0x80;

        *(uint *)(param_2 + 0x2c8) = uVar20;

		// if 9 < number of wumpa
        // if wumpa is 10
        if ('\t' < *(char *)(param_2 + 0x30)) {
          uVar16 = 0x100;
        }

		// VehFire_Increment
		// add 0.12s reserves
		FUN_8005abfc(param_2,0x78,0x14,uVar16);

        uVar20 = *(uint *)(param_2 + 0x2c8);
      }
      goto code_r0x80062644;
    }
  }

  else
  {
	// Increase amount of time reversing,
	// counts whenever holding "down" on d-pad
    *(int *)(param_2 + 0x520) = *(int *)(param_2 + 0x520) + iVar14;
code_r0x80062644:
    uVar22 = uVar20 & 8;
  }

LAB_80062648:
  if (uVar22 != 0) {
    iVar8 = (int)*(short *)(param_2 + 0x38e);
    if (iVar8 < 0) {
      iVar8 = -iVar8;
    }
    
	if (0x300 < iVar8) 
	{
	  // record amount of time with high speed
      *(int *)(param_2 + 0x51c) = *(int *)(param_2 + 0x51c) + iVar14;
    }
  }

  if ((*(short *)(param_2 + 0x3c0) == 0) ||

	  // kart state not 0, and kart state not 9
     ((*(char *)(param_2 + 0x376) != '\0' && (*(char *)(param_2 + 0x376) != '\t'))))
  {
	*(undefined2 *)(param_2 + 0x3c2) = 0;
  }

  if (*(short *)(param_2 + 0x39e) < 1) {
    //if Racer is moving, skip next 4 lines of code
    if (0 < iVar21) goto LAB_800626d4;
LAB_800626fc:
    //Racer struct + 0x39E = Racer's Base Speed
    *(undefined2 *)(param_2 + 0x39e) = (short)iVar21;
  }
  else {
    //if Racer is not moving
    if (iVar21 < 1) {
LAB_800626d4:
      if (*(short *)(param_2 + 0x3c0) != 0) {
        *(short *)(param_2 + 0x3c2) = *(short *)(param_2 + 0x3c2) + 1;
      }
      *(undefined2 *)(param_2 + 0x3c0) = 0x100;
      goto LAB_800626fc;
    }
    //Racer struct + 0x39E = Racer's Base Speed
    *(undefined2 *)(param_2 + 0x39e) = (short)iVar21;
  }
  if ((uVar20 & 0x800020) == 0) {
    iVar8 = *(int *)(*(int *)(param_2 + 0x35c) + 8);
    //if racer is out of normal driving conditions?
    //for example, 0x35C[0x8] is 0xB4 when in water at Cove
    //and the value of 0x39C fits the result perfectly
    if (iVar8 != 0x100) {
      //Base Speed = 0xB4 (at Cove water) * Base Speed >> 8
      iVar21 = iVar8 * iVar21 >> 8;
      uVar7 = (undefined2)((uint)(iVar8 * iVar10) >> 8);
    }
  }
  *(undefined2 *)(param_2 + 0x3c4) = uVar7;
  //Basic Speed = iVar21
  *(undefined2 *)(param_2 + 0x39c) = (short)iVar21;

  // assume neutral steer (drive straight)
  iVar8 = 0x80;

  puVar5 = PTR_DAT_8008d2ac;

  // If you're not in End-Of-Race menu
  if ((*(uint *)puVar5 & 0x200000) == 0)
  {
	// gamepadBuffer -> stickLX
    iVar8 = (int)*(short *)(puVar24 + 4);
  }

  iVar14 = (uint)*(byte *)(param_2 + 0x43a) + ((int)*(char *)(param_2 + 0x34) << 1) / 5;
  if ((*(short *)(param_2 + 0x3c2) < 7) || (0x25ff < iVar11)) {
    if (*(short *)(param_2 + 0x3fe) == 0) {
      if ((uVar20 & 0x28) == 0)
	  {
		// gamepadBuffer -> racingWheelData
        uVar16 = *(undefined4 *)(puVar24 + 0x4c);
      }
      else
	  {
		// if you are not holding cross
        if (local_38 == 0)
		{
          // gamepadBuffer -> racingWheelData
		  uVar16 = *(undefined4 *)(puVar24 + 0x4c);

		  iVar14 = 0x40;
        }

		// if you are holding cross
        else
		{
		  // get speed
          iVar19 = (int)*(short *)(param_2 + 0x38c);

		  // set speed to absolute value
          if (iVar19 < 0) {
            iVar19 = -iVar19;
          }

          // Map value from [oldMin, oldMax] to [newMin, newMax]
          // inverting newMin and newMax will give an inverse range mapping
          iVar14 = FUN_80058f9c(iVar19,0x300,
                                (int)((uint)*(ushort *)(param_2 + 0x42c) << 0x10) >> 0x11,0x40,
                                iVar14);

		  // gamepadBuffer -> racingWheelData
		  uVar16 = *(undefined4 *)(puVar24 + 0x4c);
        }
      }
    }
    else
	{
	  // gamepadBuffer -> racingWheelData
      uVar16 = *(undefined4 *)(puVar24 + 0x4c);
      iVar14 = 0x30;
    }
  }
  else
  {
	// gamepadBuffer -> racingWheelData
    uVar16 = *(undefined4 *)(puVar24 + 0x4c);

    iVar14 = 0x5a;
  }

  // Steer
  iVar14 = FUN_800617cc(iVar8,iVar14,uVar16);

  if (-iVar14 == 0) {
    *(undefined2 *)(param_2 + 0x3e6) = 10000;
  }
  else {
    if ((iVar14 < 1) || (*(char *)(param_2 + 0x4b) < '\0')) {
      if ((-1 < iVar14) || ('\0' < *(char *)(param_2 + 0x4b))) goto LAB_800628b0;
      uVar20 = uVar20 | 0x10;
    }
    else {
      uVar20 = uVar20 & 0xffffffef;
    }
    *(undefined2 *)(param_2 + 0x3e6) = 0;
  }
LAB_800628b0:
  *(undefined *)(param_2 + 0x4b) = (char)-iVar14;

  // Steer
  iVar8 = FUN_800617cc(iVar8,0x40,*(undefined4 *)(puVar24 + 0x4c));

  // Interpolate rotation by speed
  uVar7 = FUN_80058f54((int)*(short *)(param_2 + 6),0x18,-iVar8);

  iVar8 = (int)*(short *)(param_2 + 0x39e);
  *(undefined2 *)(param_2 + 6) = uVar7;
  if (iVar8 < 0) {
    iVar8 = -iVar8;
  }
  if (((*(uint *)(param_2 + 0x2cc) & 1) == 0) || (cVar1 == '\x02')) {
    iVar8 = iVar8 + 0xf00;
  }
  else {
    iVar8 = iVar8 + iVar11 >> 1;
  }
  sVar13 = (short)((iVar8 * 0x89 + (int)*(short *)(param_2 + 0x3be) * 0x177) * 8 >> 0xc);
  *(short *)(param_2 + 0x3be) = sVar13;
  if ((*(uint *)(param_2 + 0x2cc) & 8) == 0) {
    //prevent Basic Speed from being negative
    if (iVar21 < 0) {
      iVar21 = -iVar21;
    }
    //if Base Speed > 0x200 or iVar11 = 0x200 (?)
    if ((0x200 < iVar21) || (0x200 < iVar11)) {
      *(short *)(param_2 + 0x3bc) = *(short *)(param_2 + 0x3bc) - sVar13;
    }
  }
  //if 0x3BC <= 0 and last bit of jittery number 2 is off and
  if (((*(short *)(param_2 + 0x3bc) < 1) && ((*(uint *)(param_2 + 8) & 1) == 0)) &&
     (cVar1 != '\x04')) {
  	//reset 0x3BC
    *(undefined2 *)(param_2 + 0x3bc) = 0x1e00;
    //Jittery number 1
    *(undefined4 *)(param_2 + 8) = 0x2e606061;
  }
  else {
  	//jittery number 2
    *(undefined4 *)(param_2 + 8) = 0x2e808080;
  }
LAB_800629f8:
  *(uint *)(param_2 + 0x2c8) = uVar20;
  return;
}


// VehPhysProc_Driving_Audio (universal)
// param1 = thread, param2 = driver
void FUN_80062a2c(undefined4 param_1,undefined4 param_2)
{
  // EngineSound_Player
  FUN_8002f5f4(param_2);
  return;
}


// VehPhysProc_Driving_Update
// param1 = thread, param2 = driver
void FUN_80062a4c(undefined4 param_1,int param_2)
{
  int iVar1;

  //if racer touched the ground in this frame
  if ((*(uint *)(param_2 + 0x2c8) & 2) != 0) 
  {
    //iVar1 = Simplified Turning state
    iVar1 = (int)*(char *)(param_2 + 0x4b);

    //set Simplified Turning state to its own absolute value
    if (iVar1 < 0) {
      iVar1 = -iVar1;
    }

    if (
		(
			(
				// if steering hard enough to start a drift
				(
					// (Character's Turn stat + (Turning multiplier? << 1) / 5) >> 1)
					(int)((uint)*(byte *)(param_2 + 0x43a) +
					((int)*(char *)(param_2 + 0x34) << 1) / 5) >> 1
					
					// < Simplified turning state
					< iVar1
				) &&

				(
					//player has jump buttons held
					(*(uint *)(PTR_DAT_8008d2b0 + (uint)*(byte *)(param_2 + 0x4a) * 0x50 + 0x10) &
					(int)*(short *)(param_2 + 0x382)) != 0
				)
			) &&

			//player is not in accel prevention or braking and
			((*(uint *)(param_2 + 0x2c8) & 8) == 0)
		) &&

		//Character's Speed stat (divided by 2?) <= Speed Approximate
		(
			(int)((uint)*(ushort *)(param_2 + 0x42c) << 0x10) >> 0x11 <=
			(int)*(short *)(param_2 + 0x38e)
		)
	   )
    {
      // VehPhysProc_PowerSlide_Init
      FUN_80063934(param_1);

      //exit the function
      return;
    }
  }

  // at this point, assume driver is not touching ground

  if (
		// if driver has been "Player_Driving" more than 0.1 seconds?
		(*(short *)(param_2 + 0x406) == 0) &&

		// if V_Shift happened too many times,
		// meaning you jitter between two quadblocks
		// in a "V" shape
		(4 < *(short *)(param_2 + 0x40a))
	 )
  {

	// Stop driving, until you press X, prevents jitters
	  
    // VehPhysProc_FreezeVShift_Init
    FUN_80062e94(param_1);
  }

  else {

	// if driver has been "rolling backwards" more than 0.64 seconds
    if (*(short *)(param_2 + 0x408) == 0)
	{
      // wipe
      *(undefined2 *)(param_2 + 0x40a) = 0;
    }
  }
  return;
}



// VehPhysProc_Driving_Init
// param1 = thread, param2 = driver
void FUN_80062b74(undefined4 param_1,int param_2)
{
	// spawn function that gives you immediate control,
	// used for adventure spawn, and dropping a mask-grab

  int iVar1;

  // This if-statement prevents driving in Main Menu,
  // Cutscenes, Naughty Dog Box Scene, etc

  if (
		// if Level ID is not an adv hub
		(4 < *(int *)(PTR_DAT_8008d2ac + 0x1a10) - 0x19U) ||
		(
			// or, this is an adv hub, and 232 is loaded

			//if 232 dll is loaded
		    iVar1 = FUN_80034920(),
			iVar1 != 0
		)
	)
  {
    if (
			// If you're in Battle Mode and
			((*(uint *)PTR_DAT_8008d2ac & 0x20) != 0) &&

			//player is blasted
			(*(char *)(param_2 + 0x376) == '\x06')
		)
    {
      //set Invincibility Timer to 0xB40
      *(undefined4 *)(param_2 + 0x24) = 0xb40;
    }

    *(undefined2 *)(param_2 + 0x406) = 0x60;
    *(undefined2 *)(param_2 + 0x408) = 0x280;

	// VehPhysProc_Driving_Update
    *(undefined4 *)(param_2 + 0x58) = 0x80062a4c;

	// VehPhysProc_Driving_PhysLinear
    *(undefined4 *)(param_2 + 0x5c) = 0x8006181c;

	*(undefined4 *)(param_2 + 0x60) = 0x80062a2c; // OnAudio
    *(undefined4 *)(param_2 + 100) = 0x8005fc8c; // OnPhysAngular
    *(undefined4 *)(param_2 + 0x68) = 0x8005ea60; // VehPhysForce_OnApplyForces
	*(undefined4 *)(param_2 + 0x6c) = 0x80020410; // COLL_StartSearch_NearPlayer
	*(undefined4 *)(param_2 + 0x70) = 0x8005ebac; // VehPhysForce_CollideDrivers
	*(undefined4 *)(param_2 + 0x74) = 0x8001d944; // COLL_StartSearch_Player
    *(undefined4 *)(param_2 + 0x78) = 0x80060630; // JumpAndFriction
    *(undefined4 *)(param_2 + 0x7c) = 0x8005ee34; // VehPhysForce_TranslateMatrix -- move position to instance matrix
    *(undefined4 *)(param_2 + 0x80) = 0x8005b178; // VehFrameProc_Driving

    //Kart state = normal
    *(undefined *)(param_2 + 0x376) = 0;

	//Turbo meter = full
    *(undefined2 *)(param_2 + 0x3dc) = 0;

	*(undefined2 *)(param_2 + 0x40a) = 0;
    *(undefined4 *)(param_2 + 0x54) = 0;

	// VehEmitter_DriverMain
    *(undefined4 *)(param_2 + 0x84) = 0x80059a18;
  }
  return;
}


// VehPhysProc_FreezeEndEvent_PhysLinear
void FUN_80062ca8(undefined4 param_1,int param_2)
{
  uint uVar1;

  // VehPhysProc_Driving_PhysLinear
  FUN_8006181c();

  // get flags
  uVar1 = *(uint *)(param_2 + 0x2c8);

  // reset two speed variables
  *(undefined2 *)(param_2 + 0x39c) = 0;
  *(undefined2 *)(param_2 + 0x39e) = 0;

  // reset amplified turn state
  *(undefined2 *)(param_2 + 0xc0) = 0;

  // reset turn state
  *(undefined *)(param_2 + 0x4b) = 0;

  // reset wheel Y rotation
  *(undefined2 *)(param_2 + 6) = 0;

  // edit flags
  *(uint *)(param_2 + 0x2c8) = uVar1 | 8;
  *(uint *)(param_2 + 0x2c8) = uVar1 & 0xfffffffb | 8;

  if (0 < *(short *)(param_2 + 0x3f0)) {
    *(undefined2 *)(param_2 + 0x3f0) = 0;
  }
  return;
}

// VehPhysProc_FreezeEndEvent_Init
// param1 = thread, param2 = driver
void FUN_80062d04(undefined4 param_1,int param_2)

{
  if (*(char *)(param_2 + 0x376) != 0xb)
  {
	// VehPhysProc_FreezeEndEvent_PhysLinear
    *(undefined4 *)(param_2 + 0x5c) = 0x80062ca8;

	*(undefined4 *)(param_2 + 0x60) = 0x80062a2c; // OnAudio
    *(undefined4 *)(param_2 + 100) = 0x8005fc8c; // OnPhysAngular
    *(undefined4 *)(param_2 + 0x68) = 0x8005ea60; // VehPhysForce_OnApplyForces
	*(undefined4 *)(param_2 + 0x6c) = 0x80020410; // COLL_StartSearch_NearPlayer
	*(undefined4 *)(param_2 + 0x70) = 0x8005ebac; // VehPhysForce_CollideDrivers
	*(undefined4 *)(param_2 + 0x74) = 0x8001d944; // COLL_StartSearch_Player
    *(undefined4 *)(param_2 + 0x78) = 0x80060630; // JumpAndFriction
    *(undefined4 *)(param_2 + 0x7c) = 0x8005ee34; // VehPhysForce_TranslateMatrix -- move position to instance matrix
    *(undefined4 *)(param_2 + 0x80) = 0x8005b178; // VehFrameProc_Driving

	// kart state = 11
    *(undefined *)(param_2 + 0x376) = 0xb;

    *(undefined2 *)(param_2 + 0x38c) = 0;
    *(undefined2 *)(param_2 + 0x38e) = 0;
    *(undefined4 *)(param_2 + 0x54) = 0;
    *(undefined4 *)(param_2 + 0x58) = 0;

	// VehEmitter_DriverMain
    *(undefined4 *)(param_2 + 0x84) = 0x80059a18;
  }
  return;
}

// VehPhysProc_FreezeVShift_Update
// param1 = thread, param2 = driver
void FUN_80062db0(undefined4 param_1,int param_2)
//seems to handle end of blasted effect
{
  //if 0x39E of player struct = 0 and
  //(player is not in accel prevention (4),
  //not pressing Square (4, 6),
  if (
		(*(short *)(param_2 + 0x39e) == 0) &&

		// not in player-on-player collision
		((*(uint *)(param_2 + 0x2c8) & 0x10000028) == 0)
	 )
  {
    //player's speed = 0
    *(undefined2 *)(param_2 + 0x38c) = 0;

    //player's speed approximate = 0
    *(undefined2 *)(param_2 + 0x38e) = 0;
  }
  else
  {
	// VehPhysProc_Driving_Init
    FUN_80062b74();
  }
  return;
}


// VehPhysProc_FreezeVShift_ReverseOneFrame
// param1 = thread, param2 = driver
// reverse one frame of position
void FUN_80062e04(undefined4 param_1,int param_2)

{
   // VehPhysGeneral_JumpAndFriction
  FUN_80060630();

  // if player did not start jumping this frame
  if ((*(uint *)(param_2 + 0x2c8) & 0x400) == 0)
  {
	// if there are not two humans colliding
    if ((*(uint *)(param_2 + 0x2c8) & 0x10000000) == 0)
	{
	  // remove speed (x, y, z)
      *(undefined4 *)(param_2 + 0x3a0) = 0;
      *(undefined4 *)(param_2 + 0x3a4) = 0;
      *(undefined4 *)(param_2 + 0x3a8) = 0;

	  // remove speed and speedApprox
      *(undefined2 *)(param_2 + 0x38c) = 0;
      *(undefined2 *)(param_2 + 0x38e) = 0;

	  // set position to previous position
      *(undefined4 *)(param_2 + 0x2d4) = *(undefined4 *)(param_2 + 0x2e0);
      *(undefined4 *)(param_2 + 0x2d8) = *(undefined4 *)(param_2 + 0x2e4);
      *(undefined4 *)(param_2 + 0x2dc) = *(undefined4 *)(param_2 + 0x2e8);
    }
  }

  // if player did start jumping this frame
  else
  {
	// VehPhysProc_Driving_Init
    FUN_80062b74(param_1,param_2);
  }

  return;
}


// VehPhysProc_FreezeVShift_Init
// param1 = thread, param2 = driver
void FUN_80062e94(undefined4 param_1,int param_2)
{
  // kart state 9
  *(undefined *)(param_2 + 0x376) = 9;

  // OnUpdate
  *(undefined4 *)(param_2 + 0x58) = 0x80062db0;

  // VehPhysProc_Driving_PhysLinear
  *(undefined4 *)(param_2 + 0x5c) = 0x8006181c;

  *(undefined4 *)(param_2 + 0x60) = 0x80062a2c; // OnAudio
  *(undefined4 *)(param_2 + 100) = 0x8005fc8c; // OnPhysAngular
  *(undefined4 *)(param_2 + 0x68) = 0x8005ea60; // VehPhysForce_OnApplyForces
  *(undefined4 *)(param_2 + 0x6c) = 0x80020410; // COLL_StartSearch_NearPlayer
  *(undefined4 *)(param_2 + 0x70) = 0x8005ebac; // VehPhysForce_CollideDrivers
  *(undefined4 *)(param_2 + 0x74) = 0x8001d944; // COLL_StartSearch_Player
  *(undefined4 *)(param_2 + 0x78) = 0x80062e04; // alter jump mechanics
  *(undefined4 *)(param_2 + 0x7c) = 0x8005ee34; // VehPhysForce_TranslateMatrix -- move position to instance matrix
  *(undefined4 *)(param_2 + 0x80) = 0x8005b178; // VehFrameProc_Driving

  //Turbo meter = full
  *(undefined2 *)(param_2 + 0x3dc) = 0;

  *(undefined4 *)(param_2 + 0x54) = 0;

	// VehEmitter_DriverMain
  *(undefined4 *)(param_2 + 0x84) = 0x80059a18;

  //turn off 29th flag of actions flag set (means players dont collide anymore)
  *(uint *)(param_2 + 0x2c8) = *(uint *)(param_2 + 0x2c8) & 0xefffffff;
  return;
}

// VehPhysProc_PowerSlide_PhysAngular
// param1 = thread, param2 = driver
void FUN_80062f4c(undefined4 param_1,int param_2)

{
  char cVar1;
  bool bVar2;
  bool bVar3;
  undefined *puVar4;
  short sVar5;
  undefined2 uVar6;
  ushort uVar7;
  int iVar8;
  int iVar9;
  uint uVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  uint uVar14;
  int iVar15;

  iVar12 = (((int)*(short *)(param_2 + 0x396) - (int)*(short *)(param_2 + 0x39a)) + 0x800U & 0xfff)
           - 0x800;
  iVar13 = iVar12 >> 3;
  if (iVar12 != 0) {
    if (iVar13 == 0) {
      iVar13 = 1;
    }

				// elapsed milliseconds per frame, ~32
    iVar12 = (*(int *)(PTR_DAT_8008d2ac + 0x1d04) << 6) >> 5;

    if (iVar12 < iVar13) {
      iVar13 = iVar12;
    }
    sVar5 = (short)iVar13;
    if (iVar13 < -iVar12) {
      sVar5 = (short)-iVar12;
    }

	// change player rotation
    *(short *)(param_2 + 0x39a) = *(short *)(param_2 + 0x39a) + sVar5;

	*(ushort *)(param_2 + 0x396) = *(short *)(param_2 + 0x396) - sVar5 & 0xfff;
  }
  
  if (*(short *)(param_2 + 0x3da) < 0) 
  {
	// negative cam spin rate
    iVar13 = -(int)*(short *)(param_2 + 0x468);
  }
  else 
  {
	// positive cam spin rate
    iVar13 = (int)*(short *)(param_2 + 0x468);
  }

  // get camera rotation
  iVar12 = *(short *)(param_2 + 0x2f2) - iVar13;

  // make sure it's not negative
  if (iVar12 < 0) {
    iVar12 = -iVar12;
  }

  uVar14 = iVar12 >> 3;
  if (uVar14 == 0) {
    uVar14 = 1;
  }
  uVar10 = (uint)*(byte *)(param_2 + 0x46a);
  if ((int)uVar14 < (int)(uint)*(byte *)(param_2 + 0x46a)) {
    uVar10 = uVar14;
  }

  // Interpolate rotation by speed
  sVar5 = FUN_80058f54((int)*(short *)(param_2 + 0x2fa),8,uVar10);
  puVar4 = PTR_DAT_8008d2ac;
  *(short *)(param_2 + 0x2fa) = sVar5;

  // Interpolate rotation by speed
  uVar6 = FUN_80058f54((int)*(short *)(param_2 + 0x2f2),(int)sVar5 * *(int *)(puVar4 + 0x1d04) >> 5,
                       iVar13);

  // turning rate
  iVar12 = (int)*(short *)(param_2 + 0x3b4);
  
  // drift direction
  iVar15 = (int)*(short *)(param_2 + 0x3da);
  
  bVar3 = false;

  // set new rotation variable
  *(undefined2 *)(param_2 + 0x2f2) = uVar6;

  // simpTurningState
  iVar9 = (int)*(char *)(param_2 + 0x4b);
  
  iVar13 = iVar9 * 0x100;
  
  // if drifting to the right
  if (iVar15 < 0) 
  {
	// if steering to the right
    if (iVar13 < 1) 
	{
      iVar13 = iVar9 * -0x100;
	  
	  // const_SteerVel_DriftStandard
      iVar9 = -(int)*(char *)(param_2 + 0x45f);
    }
	
	// if steering to the left
    else 
	{
	  // const_SteerVel_DriftSwitchWay
      iVar9 = -(int)*(char *)(param_2 + 0x45e);
    }
  }
  
  // if drifting to the left
  else 
  {
	// if steering to the right
    if (iVar13 < 0) 
	{
      iVar13 = iVar9 * -0x100;
      
	  // const_SteerVel_DriftSwitchWay
	  cVar1 = *(char *)(param_2 + 0x45e);
    }
	
	// if steering to the left
    else 
	{
	  // const_SteerVel_DriftStandard
      cVar1 = *(char *)(param_2 + 0x45f);
    }
	
    iVar9 = (int)cVar1;
  }

  // Map "simpTurnState" from [0, const_TurnRate] to [0, driftDirection]
  iVar13 = FUN_80058f9c(iVar13,0,((uint)*(byte *)(param_2 + 0x43a) +
                                 ((int)*(char *)(param_2 + 0x34) << 1) / 5) * 0x100,0,iVar9 << 8);
								 
  if (
		(iVar13 < 0) || 
		(
			(
				// compare two turning rates
				bVar2 = iVar13 < iVar12,
				
				iVar13 == 0 && (iVar12 < 0)
			)
		)
	) 
  {
    bVar3 = true;
    iVar13 = -iVar13;
    iVar12 = -iVar12;
    iVar15 = -iVar15;
    bVar2 = iVar13 < iVar12;
  }

  // 0x464 and 0x466 impact turning somehow

  if (bVar2)
  {
														// elapsed milliseconds per frame, ~32
    iVar12 = iVar12 - ((int)*(short *)(param_2 + 0x466) * *(int *)(PTR_DAT_8008d2ac + 0x1d04) >> 5);
    bVar2 = iVar12 < iVar13;
  }
  else
  {
														// elapsed milliseconds per frame, ~32
    iVar12 = iVar12 + ((int)*(short *)(param_2 + 0x464) * *(int *)(PTR_DAT_8008d2ac + 0x1d04) >> 5);
    bVar2 = iVar13 < iVar12;
  }
  
  if (bVar2) {
    iVar12 = iVar13;
  }
  
  // if not steering,
  // then interpolate to "neutral" drift
  if (iVar13 == 0) 
  {
LAB_80063244:

	// Interpolate by 1 unit, until zero
    uVar6 = FUN_80058f54((int)*(short *)(param_2 + 0x580),1,0);
    *(undefined2 *)(param_2 + 0x580) = uVar6;
  }
  
  // if steering
  else 
  {
	// if drifting right
    if (iVar15 < 1) 
	{
	  // if less than zero, reset to zero
      if (-1 < iVar15) goto LAB_80063244;
	  
	  // decrease positive number
      uVar7 = *(short *)(param_2 + 0x580) - 1;
      *(ushort *)(param_2 + 0x580) = uVar7;
	  
	  // skip to zero if already positive
      if (0 < (int)((uint)uVar7 << 0x10)) {
        *(undefined2 *)(param_2 + 0x580) = 0;
      }
    }
    
	// if drifting left
	else 
	{
	  // increase number
      uVar7 = *(short *)(param_2 + 0x580) + 1;
      *(ushort *)(param_2 + 0x580) = uVar7;
	  
	  // skip to zero if already negative
      if ((int)((uint)uVar7 << 0x10) < 0) {
        *(undefined2 *)(param_2 + 0x580) = 0;
      }
    }
  }
  if (bVar3) {
    iVar12 = -iVar12;
    iVar15 = -iVar15;
  }

  // Map value from [oldMin, oldMax] to [newMin, newMax]
  // inverting newMin and newMax will give an inverse range mapping
  iVar13 = FUN_80058f9c((int)*(short *)(param_2 + 0x584),0,(uint)*(byte *)(param_2 + 0x462) << 5,
                        (int)*(char *)(param_2 + 0x461) * (int)*(short *)(param_2 + 0x3da) >> 8,
                        iVar15);
  if (-1 < iVar13) {
    if (iVar12 < -iVar13) {
      iVar12 = -iVar13;
    }
    sVar5 = (short)iVar12;
    if (0 < iVar13) goto LAB_800632cc;
  }
  sVar5 = (short)iVar12;
  if (-iVar13 < iVar12) {
    sVar5 = (short)-iVar13;
  }
LAB_800632cc:
  iVar12 = iVar13;
  if (iVar13 < 0) {
    iVar12 = -iVar13;
  }
  *(short *)(param_2 + 0x3b4) = sVar5;
  iVar9 = (int)sVar5;

  // Map value from [oldMin, oldMax] to [newMin, newMax]
  // inverting newMin and newMax will give an inverse range mapping
  iVar12 = FUN_80058f9c(iVar12,0,(int)*(char *)(param_2 + 0x460) +
                                 ((int)*(char *)(param_2 + 0x34) << 2) / 5,0,
                        (int)*(short *)(param_2 + 0x474));
  
  iVar15 = iVar9;
  
  if (iVar13 < 0) 
  {
    iVar12 = -iVar12;
    
	if (iVar9 < 0) 
	{
      if (iVar9 < 0) {
        iVar15 = -iVar9;
      }
	  
	  // const_SteerVel_DriftStandard
      iVar11 = (int)*(char *)(param_2 + 0x45f) << 8;
	  
      iVar8 = -(int)*(short *)(param_2 + 0x470);
    }
	
    else 
	{
	  // const_SteerVel_DriftSwitchWay
      iVar11 = (int)*(char *)(param_2 + 0x45e) << 8;
	  
      iVar8 = -(int)*(short *)(param_2 + 0x472);
    }
  }
  
  else 
  {
    if (iVar9 < 0) 
	{
      if (iVar9 < 0) 
	  {
        iVar15 = -iVar9;
      }
	  
	  // const_SteerVel_DriftSwitchWay
      cVar1 = *(char *)(param_2 + 0x45e);
	  
      sVar5 = *(short *)(param_2 + 0x472);
    }
    
	else 
	{
	  // const_SteerVel_DriftStandard
      cVar1 = *(char *)(param_2 + 0x45f);
	  
      sVar5 = *(short *)(param_2 + 0x470);
    }
    iVar8 = (int)sVar5;
    iVar11 = (int)cVar1 << 8;
  }

  // Map value from [oldMin, oldMax] to [newMin, newMax]
  // inverting newMin and newMax will give an inverse range mapping
  iVar15 = FUN_80058f9c(iVar15,0,iVar11,0,iVar8);
  iVar12 = (iVar12 + iVar15) - (int)*(short *)(param_2 + 0x3c6);
  iVar15 = iVar12 >> 3;
  sVar5 = (short)iVar15;
  if (iVar12 != 0) {
    if (iVar15 == 0) {
      sVar5 = 1;
    }
    *(short *)(param_2 + 0x3c6) = *(short *)(param_2 + 0x3c6) + sVar5;
  }
  
  // numFramesDrifting (negative if switchway)
  iVar12 = (int)*(short *)(param_2 + 0x580);
  if (iVar12 < 0) {
    iVar12 = -iVar12;
  }

  // get half of spin-out constant, this determines
  // when to start making tire sound effects, after the
  // turbo meter finishes filling past it's max capacity

  // if you drift beyond the limit of the turbo meter
  if ((int)(uint)(*(byte *)(param_2 + 0x463) >> 1) < iVar12)
  {
    iVar12 = (int)*(short *)(param_2 + 0x3d4);
    if (iVar12 < 0) {
      iVar12 = -iVar12;
    }
    if (iVar12 < 10) {
      *(undefined2 *)(param_2 + 0x3d8) = 8;
      *(undefined2 *)(param_2 + 0x3d6) = 0x14;
      if (iVar13 < 0) {
        *(undefined2 *)(param_2 + 0x3d6) = 0xffec;
      }
    }
  }
  else {
    *(undefined2 *)(param_2 + 0x3d8) = 0;
  }
  
  iVar12 = (int)*(short *)(param_2 + 0x3d4);
  if (iVar12 < 0) {
    iVar12 = -iVar12;
  }
  
  if (0x32 < iVar12) {
    *(undefined2 *)(param_2 + 0x3d8) = 0;
  }
  
  if (*(short *)(param_2 + 0x3d8) == 0) {
    *(undefined2 *)(param_2 + 0x3d6) = 10;
    if (0 < *(short *)(param_2 + 0x3d4)) {
      *(undefined2 *)(param_2 + 0x3d6) = 0xfff6;
    }
    iVar12 = (int)*(short *)(param_2 + 0x3d6);
    if (iVar12 < 0) {
      iVar12 = -iVar12;
    }

	// Interpolate rotation by speed
    sVar5 = FUN_80058f54((int)*(short *)(param_2 + 0x3d4),iVar12,0);
  }
  else {
    *(short *)(param_2 + 0x3d8) = *(short *)(param_2 + 0x3d8) + -1;
    sVar5 = *(short *)(param_2 + 0x3d4) + *(short *)(param_2 + 0x3d6);
  }
  *(short *)(param_2 + 0x3d4) = sVar5;
  puVar4 = PTR_DAT_8008d2ac;
  *(undefined2 *)(param_2 + 0xc0) = (short)(iVar9 + iVar13);
  *(ushort *)(param_2 + 0x39a) =
       *(short *)(param_2 + 0x39a) + (short)((iVar9 + iVar13) * *(int *)(puVar4 + 0x1d04) >> 0xd) &
       0xfff;
  
  if (*(short *)(param_2 + 0x582) != 0) 
  {  
	// decrease by elpased time
	iVar13 = (uint)*(ushort *)(param_2 + 0x582) - (uint)*(ushort *)(puVar4 + 0x1d04);
    *(undefined2 *)(param_2 + 0x582) = (short)iVar13;
    if (iVar13 * 0x10000 < 0) {
      *(undefined2 *)(param_2 + 0x582) = 0;
    }
															
    sVar5 = (short)((int)((uint)*(byte *)(param_2 + 0x47a) * 
				
				// elapsed milliseconds per frame, ~32
				*(int *)(PTR_DAT_8008d2ac + 0x1d04)) >> 5);
				
    if (*(short *)(param_2 + 0x3c6) < 0) {
      sVar5 = -sVar5;
    }
    *(ushort *)(param_2 + 0x396) = *(short *)(param_2 + 0x396) + sVar5 & 0xfff;
  }
  
  puVar4 = PTR_DAT_8008d2ac;
  *(short *)(param_2 + 0x2ee) =
       *(short *)(param_2 + 0x3d4) + *(short *)(param_2 + 0x39a) + *(short *)(param_2 + 0x3c6);

  // increment this by milliseconds
  sVar5 = *(short *)(param_2 + 0x584) + *(short *)(puVar4 + 0x1d04);
  *(short *)(param_2 + 0x584) = sVar5;

  if ((int)((uint)*(byte *)(param_2 + 0x462) << 5) < (int)sVar5) {
    *(short *)(param_2 + 0x584) = (ushort)*(byte *)(param_2 + 0x462) << 5;
  }

  // VehPhysForce_RotAxisAngle
  FUN_8005f89c((undefined4 *)(param_2 + 0x310),param_2 + 0x360,(int)*(short *)(param_2 + 0x39a));
  gte_SetRotMatrix((MATRIX *)(param_2 + 0x310));

  // VehPhysForce_AccelTerrainSlope
  FUN_8005fb4c(param_2);
  return;
}


// VehPhysProc_PowerSlide_Finalize
void FUN_80063634(int param_1)

{
  *(undefined2 *)(param_1 + 0x3ea) = *(undefined2 *)(param_1 + 0x3da);
  *(short *)(param_1 + 0x3ec) = (ushort)*(byte *)(param_1 + 0x46b) << 5;
  return;
}


// VehPhysProc_PowerSlide_Update
// param1 = thread, param2 = driver
void FUN_8006364c(undefined4 param_1,int param_2)

{
  char cVar1;
  undefined2 uVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;

  // If you do not press L1 or R1
  if ((*(uint *)(PTR_DAT_8008d2b0 + (uint)*(byte *)(param_2 + 0x4a) * 0x50 + 0x14) & 0xc00) == 0) {

	// If there is no room in the turbo meter left to fill
	if (*(short *)(param_2 + 0x3dc) == 0) {

	  // If you have not attempted to boost 3 times in a row
      if (*(char *)(param_2 + 0x586) < '\x03')
	  {
		// set turbo meter to empty
        *(short *)(param_2 + 0x3dc) = (ushort)*(byte *)(param_2 + 0x476) << 5;
      }
    }

	// If the turbo meter is not full
	else
	{
	  // decreaes the amoutn of room remaining, by elapsed milliseconds per frame, ~32
      iVar4 = (uint)*(ushort *)(param_2 + 0x3dc) - (uint)*(ushort *)(PTR_DAT_8008d2ac + 0x1d04);
      *(undefined2 *)(param_2 + 0x3dc) = (short)iVar4;

	  // if the bar goes beyond full
      if (iVar4 * 0x10000 < 0)
	  {
		// set bar to full
        *(undefined2 *)(param_2 + 0x3dc) = 0;
      }

	  // If bar is full
      if (*(short *)(param_2 + 0x3dc) == 0)
	  {
		// Make a sound
        FUN_80028494(0xf,1,(uint)*(ushort *)(param_2 + 0x2ca) & 1);

		// Add to your number of boost attempts, this makes it
		// so you can't attempt to boost again until you release L1 + R1
        *(char *)(param_2 + 0x586) = *(char *)(param_2 + 0x586) + '\x03';
      }
    }
  }

  // If you do press L1 or R1
  else {

	// Get P1's turbo meter
	// This is the distance remaining that can be filled
    iVar4 = (int)*(short *)(param_2 + 0x3dc);

	// Set drift timer to zero, start the drift
    *(undefined2 *)(param_2 + 0x580) = 0;

	// If turbo meter is not empty
	if (iVar4 != 0) {

	  // const_turboLowRoomWarning
	  // get length where turbo turns from green to red
      iVar5 = (uint)*(byte *)(param_2 + 0x477) << 5;

	  // If distance remaining to be filled in turbo bar, is less than,
	  // the distance remaining from the red/green "turning point" to the end,

	  // If meter is in the red
	  if (iVar4 < iVar5)
	  {
		// reserves_gain = map from old range to new range,
		// the more room remaining to fill, the less boost you get
		// old minMax: [zero -> const_turboLowRoomWarning]
		// new minMax: [const_turboFullBarReserveGain, -> zero]
        uVar3 = FUN_80058f9c(iVar4,0,iVar5,(uint)*(byte *)(param_2 + 0x478) << 5,0);

		// VehFire_Increment
		FUN_8005abfc(

			// driver
			param_2,

			// amount of reserves
			uVar3,

			2,

			// fire level, bigger boost for attempt number (1,2, or 3)
			(int)*(char *)(param_2 + 0x587) << 6);


		// increase the counter for number of times you've boosted in a row (0-3)
		cVar1 = *(char *)(param_2 + 0x587) + '\x01';
        *(char *)(param_2 + 0x587) = cVar1;

		// if you've boosted less than 3 times in a row
        if (cVar1 < '\x03')
		{
			// give a chance to boost again
          *(uint *)(param_2 + 0x2c8) = *(uint *)(param_2 + 0x2c8) | 0x80;
        }

		// drift boost meter = constant
        *(short *)(param_2 + 0x582) = (ushort)*(byte *)(param_2 + 0x479) << 5;
      }

	  // If meter is in the green
      else
	  {
		  // reset meter to beginning
        *(undefined *)(param_2 + 0x381) = 8;
      }

      *(undefined2 *)(param_2 + 0x3dc) = 0;

	  // increase number of boost attempts (both success and failure)
      *(char *)(param_2 + 0x586) = *(char *)(param_2 + 0x586) + '\x01';
    }
  }

  // 1.0 seconds
  uVar2 = 0x3c0;

  if (
		// If the "spin-out" constant is less than your drift counter
		((int)(uint)*(byte *)(param_2 + 0x463) < (int)*(short *)(param_2 + 0x580)) ||

		(
			(
				*(short *)(param_2 + 0x38e) < 0 &&
				(
					// 2.0 seconds
					uVar2 = 0x780,

					// if you're not on any turbo pad
					(*(uint *)(param_2 + 0xbc) & 3) == 0
				)
			)
		)
	 )
  {
	// Make the character spin out from too much drifting

	// Set amount of NoInput
    *(undefined2 *)(param_2 + 0x400) = uVar2;

	// VehPhysProc_SpinFirst_Init
    FUN_80063ec0(param_1,param_2);
  }

  // if you aren't spinning out
  else {

    if (
			// drift counter counts backwards during switchway drift: did switchway too long?
			((int)*(short *)(param_2 + 0x580) < (int)-(uint)*(byte *)(param_2 + 0x463)) ||

			((
				// speed is less than half the driver's speed classStat
				((int)*(short *)(param_2 + 0x38c) < (int)((uint)*(ushort *)(param_2 + 0x42c) << 0x10) >> 0x11 ||
				
				((*(uint *)(param_2 + 0x2c8) & 0x2028) != 0)) ||

				// If the gamepad input is...
				((*(uint *)(PTR_DAT_8008d2b0 + (uint)*(byte *)(param_2 + 0x4a) * 0x50 + 0x10) &

				// does not include the jump button that you used to start drifting
				(int)*(short *)(param_2 + 0x382)) == 0)
			))
		)
	{
	  // Stop drifting, just drive

	  // VehPhysProc_PowerSlide_Finalize
      FUN_80063634(param_2);

	  // VehPhysProc_Driving_Init
      FUN_80062b74(param_1,param_2);
    }
  }
  return;
}


// VehPhysProc_PowerSlide_PhysLinear
void FUN_800638d4(undefined4 param_1,int param_2)

{
  undefined *puVar1;

  // VehPhysProc_Driving_PhysLinear
  FUN_8006181c();

  puVar1 = PTR_DAT_8008d2ac;

  // driver is drifting (0x1000)
  // driver is skidding (0x800)
  *(uint *)(param_2 + 0x2c8) = *(uint *)(param_2 + 0x2c8) | 0x1800;

  // drift timer += elapsed time
  *(int *)(param_2 + 0x538) = *(int *)(param_2 + 0x538) + *(int *)(puVar1 + 0x1d04);
  return;
}

// VehPhysProc_PowerSlide_InitSetUpdate
// param1 = thread, param2 = driver
void FUN_80063920(undefined4 param_1,int param_2)
{
  // This is so the update function
  // is not called on the first frame,
  // just like spinning

  *(undefined4 *)(param_2 + 0x54) = 0;

  // VehPhysProc_PowerSlide_Update
  *(undefined4 *)(param_2 + 0x58) = 0x8006364c;
  return;
}

// VehPhysProc_PowerSlide_Init
// param1 = thread, param2 = driver
void FUN_80063934(undefined4 param_1,int param_2)
//seems to handle start of drifts
{
  short sVar1;
  
  //kart is drifting
  *(undefined *)(param_2 + 0x376) = 2;
  
  //sVar1 = Character's Drift stat + ((Turning multiplier? << 2) / 5)
  sVar1 = (short)*(char *)(param_2 + 0x460) + (short)(((int)*(char *)(param_2 + 0x34) << 2) / 5);
  
  //Multiplied drift = sVar1 * 100
  *(short *)(param_2 + 0x3da) = sVar1 * 0x100;
  
  //if simplified turning state is negative (means you're turning right)
  if (*(char *)(param_2 + 0x4b) < '\0') 
  {
    //also make Multiplied drift negative
    *(short *)(param_2 + 0x3da) = sVar1 * -0x100;
  }

  // VehPhysProc_PowerSlide_InitSetUpdate
  *(undefined4 *)(param_2 + 0x54) = 0x80063920;

  // VehPhysProc_PowerSlide_PhysLinear
  *(undefined4 *)(param_2 + 0x5c) = 0x800638d4;

  *(undefined4 *)(param_2 + 0x60) = 0x80062a2c; // OnAudio
  *(undefined4 *)(param_2 + 100) = 0x80062f4c; // OnPhysAngular
  *(undefined4 *)(param_2 + 0x68) = 0x8005ea60; // VehPhysForce_OnApplyForces
  *(undefined4 *)(param_2 + 0x6c) = 0x80020410; // COLL_StartSearch_NearPlayer
  *(undefined4 *)(param_2 + 0x70) = 0x8005ebac; // VehPhysForce_CollideDrivers
  *(undefined4 *)(param_2 + 0x74) = 0x8001d944; // COLL_StartSearch_Player
  *(undefined4 *)(param_2 + 0x78) = 0x80060630; // JumpAndFriction
  *(undefined4 *)(param_2 + 0x7c) = 0x8005ee34; // VehPhysForce_TranslateMatrix -- move position to instance matrix
  *(undefined4 *)(param_2 + 0x80) = 0x8005b178; // VehFrameProc_Driving

  // erase union in driver struct
  *(undefined2 *)(param_2 + 0x580) = 0;
  *(undefined2 *)(param_2 + 0x584) = 0;
  *(undefined2 *)(param_2 + 0x582) = 0;
  *(undefined *)(param_2 + 0x586) = 0;
  *(undefined *)(param_2 + 0x587) = 0;
  
  *(undefined2 *)(param_2 + 0x3b4) = 0;
  *(undefined2 *)(param_2 + 0x3d2) = 0;
  *(undefined2 *)(param_2 + 0x3ec) = 0;
  *(undefined4 *)(param_2 + 0x58) = 0;

  // VehEmitter_DriverMain
  *(undefined4 *)(param_2 + 0x84) = 0x80059a18;

  //Turbo meter space left to fill = Length of Turbo meter << 5
  *(short *)(param_2 + 0x3dc) = (ushort)*(byte *)(param_2 + 0x476) << 5;
  return;
}

// VehPhysProc_SlamWall_PhysAngular
// param1 = thread, param2 = driver
void FUN_80063a44(undefined4 param_1,int param_2)
{
  undefined *puVar1;
  ushort uVar2;
  undefined2 uVar3;

  puVar1 = PTR_DAT_8008d2ac;

  // increase spin by (lastFrameSpinRate * elapsedTime)
  uVar2 = *(short *)(param_2 + 0x39a) +				// elapsed milliseconds per frame, ~32
          (short)((int)*(short *)(param_2 + 0xc0) * *(int *)(PTR_DAT_8008d2ac + 0x1d04) >> 0xd) &
          0xfff;
		  
  *(ushort *)(param_2 + 0x39a) = uVar2;
  
  // cameraRotY = spinRate + kart angle + drift angle,
  // spin rate is added so you're one frame ahead
  *(short *)(param_2 + 0x2ee) = *(short *)(param_2 + 0x3d4) + uVar2 + *(short *)(param_2 + 0x3c6);

  // Interpolate rotation by speed
  uVar3 = FUN_80058f54((int)*(short *)(param_2 + 0x2f2),(*(int *)(puVar1 + 0x1d04) << 5) >> 5,0);
  
  puVar1 = PTR_DAT_8008d2ac;

  // set camera rotation angle around player
  *(undefined2 *)(param_2 + 0x2f2) = uVar3;

  // Interpolate rotation by speed
  uVar3 = FUN_80058f54((int)*(short *)(param_2 + 0x3c6),(*(int *)(puVar1 + 0x1d04) << 7) >> 5,0);
  *(undefined2 *)(param_2 + 0x3c6) = uVar3;

  // VehPhysForce_RotAxisAngle
  FUN_8005f89c(param_2 + 0x310,param_2 + 0x360,(int)*(short *)(param_2 + 0x39a));
  return;
}

// VehPhysProc_SlamWall_Update
void FUN_80063af8(void)

{
  return;
}

// VehPhysProc_SlamWall_PhysLinear
// param1 = thread, param2 = driver
void FUN_80063b00(undefined4 param_1,int param_2)

{
  // VehPhysProc_Driving_PhysLinear
  FUN_8006181c();

  // reset two speed variables
  *(undefined2 *)(param_2 + 0x39c) = 0;
  *(undefined2 *)(param_2 + 0x39e) = 0;

  return;
}

// VehPhysProc_SlamWall_Animate
// param1 = thread, param2 = driver
void FUN_80063b2c(int param_1,int param_2)

{
  short sVar1;
  undefined2 uVar2;
  int iVar3;
  int iVar4;

  // get instance from thread
  iVar4 = *(int *)(param_1 + 0x34);

  // increase animation frame
  *(short *)(iVar4 + 0x54) = *(short *)(iVar4 + 0x54) + 1;

  *(char *)(param_2 + 0x4d) = *(char *)(param_2 + 0x4d) + '\x01';

  // get animation frame
  sVar1 = *(short *)(iVar4 + 0x54);

  // get number of frames in animation
  iVar3 = FUN_8005b0f4(iVar4,(uint)*(byte *)(iVar4 + 0x52));

  // if animation is finished
  if (iVar3 + -1 <= (int)sVar1)
  {
	// get number of frames in anim #0
    iVar3 = FUN_8005b0f4(iVar4,0);

	// if it has frames
    if (0 < iVar3)
	{
	  // reset animation
      *(undefined *)(iVar4 + 0x52) = 0;

	  // VehFrameInst_GetStartFrame(midpoint, numFrames)
      uVar2 = FUN_8005b0c4(0,iVar3);

	  // set animation
      *(undefined2 *)(iVar4 + 0x54) = uVar2;

      *(undefined *)(param_2 + 0x4c) = 0;
      *(undefined *)(param_2 + 0x4d) = 0;
    }

	// VehPhysProc_Driving_Init
    *(undefined4 *)(param_2 + 0x54) = 0x80062b74;
  }
  return;
}


// VehPhysProc_SlamWall_Init
// param1 = thread, param2 = driver
void FUN_80063bd4(int param_1,int param_2)

{
  int iVar1;

  // get instance from thread
  iVar1 = *(int *)(param_1 + 0x34);

  // Set state to crashing
  *(undefined *)(param_2 + 0x376) = 1;

  *(undefined2 *)(param_2 + 0x3e6) = 10000;
  *(undefined2 *)(param_2 + 0x3dc) = 0;
  *(undefined2 *)(param_2 + 0x3b4) = 0;
  *(undefined2 *)(param_2 + 0x3d2) = 0;
  *(undefined2 *)(param_2 + 0x3d4) = 0;
  *(undefined2 *)(param_2 + 0x3d6) = 0;
  *(undefined2 *)(param_2 + 0x3d8) = 0;
  *(undefined2 *)(param_2 + 0xc0) = 0;
  *(undefined2 *)(param_2 + 0x38c) = 0;
  *(undefined2 *)(param_2 + 0x38e) = 0;
  *(undefined4 *)(param_2 + 0x3a0) = 0;
  *(undefined4 *)(param_2 + 0x3a4) = 0;
  *(undefined4 *)(param_2 + 0x3a8) = 0;
  *(undefined4 *)(param_2 + 0x88) = 0;
  *(undefined4 *)(param_2 + 0x8c) = 0;
  *(undefined4 *)(param_2 + 0x90) = 0;
  *(undefined2 *)(param_2 + 0x36e) = 0;
  *(undefined2 *)(param_2 + 0x3e2) = 0;
  *(undefined2 *)(param_2 + 0x3de) = 0;
  *(undefined2 *)(param_2 + 0x3e0) = 0;
  *(undefined *)(param_2 + 0x377) = 0;
  *(undefined2 *)(param_2 + 0x3ee) = 0;
  *(undefined2 *)(param_2 + 0x40e) = 0;
  *(undefined2 *)(param_2 + 0x410) = 0;
  *(undefined2 *)(param_2 + 0x40c) = 0;
  *(undefined2 *)(param_2 + 0x39c) = 0;
  *(undefined2 *)(param_2 + 0x39e) = 0;

  // Set driver scale
  *(undefined2 *)(iVar1 + 0x1e) = 0xccc;
  *(undefined2 *)(iVar1 + 0x1c) = 0xccc;

  // VehPhysProc_SlamWall_Update
  *(undefined4 *)(param_2 + 0x58) = 0x80063af8;

  // OnInit
  *(undefined4 *)(param_2 + 0x54) = 0;

  // VehPhysProc_SlamWall_PhysLinear
  *(undefined4 *)(param_2 + 0x5c) = 0x80063b00;

  *(undefined4 *)(param_2 + 0x60) = 0x80062a2c; // OnAudio
  *(undefined4 *)(param_2 + 100) = 0x80063a44; // OnPhysAngular
  *(undefined4 *)(param_2 + 0x68) = 0x8005ea60; // VehPhysForce_OnApplyForces
  *(undefined4 *)(param_2 + 0x6c) = 0x80020410; // COLL_StartSearch_NearPlayer
  *(undefined4 *)(param_2 + 0x70) = 0x8005ebac; // VehPhysForce_CollideDrivers
  *(undefined4 *)(param_2 + 0x74) = 0x8001d944; // COLL_StartSearch_Player
  *(undefined4 *)(param_2 + 0x78) = 0x80060630; // JumpAndFriction
  *(undefined4 *)(param_2 + 0x7c) = 0x8005ee34; // VehPhysForce_TranslateMatrix -- move position to instance matrix

  // VehPhysProc_SlamWall_Animate
  *(undefined4 *)(param_2 + 0x80) = 0x80063b2c;


  // VehEmitter_DriverMain
  *(undefined4 *)(param_2 + 0x84) = 0x80059a18;

  return;
}


// VehPhysProc_SpinFirst_Update
// param1 = thread, param2 = driver
void FUN_80063cf4(undefined4 param_1,int param_2)

{
  int iVar1;

  // If you are not done spinning out
  if (*(short *)(param_2 + 0x400) != 0)
  {
	// Get approximate speed
    iVar1 = (int)*(short *)(param_2 + 0x38e);

	// If your speed somehow goes negative
    if (iVar1 < 0)
	{
	  // Make it positive
      iVar1 = -iVar1;
    }

	// If you have not slown down from spinning
    if (0x2ff < iVar1)
	{
	  // End the function
      return;
    }
  }

  // If you have slown down enough

  // VehPhysProc_SpinLast_Init
  FUN_80064254(param_1, param_2);
  return;
}

// VehPhysProc_SpinFirst_PhysLinear
// param1 = thread, param2 = driver
void FUN_80063d44(undefined4 param_1,int param_2)

{
  undefined *puVar1;
  int iVar2;

  // NoInput timer = NoInput timer  -  elapsed milliseconds per frame, ~32
  iVar2 = (uint)*(ushort *)(param_2 + 0x400) - (uint)*(ushort *)(PTR_DAT_8008d2ac + 0x1d04);
  *(undefined2 *)(param_2 + 0x400) = (short)iVar2;

  // If timer is less than zero
  if (iVar2 * 0x10000 < 0)
  {
	// Set to zero
    *(undefined2 *)(param_2 + 0x400) = 0;
  }

  // VehPhysProc_Driving_PhysLinear
  FUN_8006181c(param_1,param_2);

  puVar1 = PTR_DAT_8008d2ac;

  // reset two speed variables
  *(undefined2 *)(param_2 + 0x39c) = 0;
  *(undefined2 *)(param_2 + 0x39e) = 0;

  // Driver flags
  *(uint *)(param_2 + 0x2c8) = *(uint *)(param_2 + 0x2c8) | 0x5808;

  // Increment amount of time spent spinning out
  *(int *)(param_2 + 0x540) = *(int *)(param_2 + 0x540) + *(int *)(puVar1 + 0x1d04);

  return;
}


// VehPhysProc_SpinFirst_PhysAngular
// param1 = thread, param2 = driver
void FUN_80063dc8(undefined4 param_1,int param_2)

{
  undefined *puVar1;
  ushort uVar2;
  undefined2 uVar3;

  *(undefined2 *)(param_2 + 0x3e6) = 10000;
  
  // decrease turn rate by 1/8 of itself
  *(short *)(param_2 + 0x3b4) = *(short *)(param_2 + 0x3b4) - (*(short *)(param_2 + 0x3b4) >> 3);
  
  puVar1 = PTR_DAT_8008d2ac;

  // Drift angle = (Drift angle + spinRate + 180 degrees) & 0xfff - 180 degrees
  *(short *)(param_2 + 0x3c6) =
       (*(short *)(param_2 + 0x3c6) + *(short *)(param_2 + 0x580) + 0x800U & 0xfff) - 0x800;

  *(short *)(param_2 + 0xc0) = *(short *)(param_2 + 0x3b4);
  *(short *)(param_2 + 0x3d4) = *(short *)(param_2 + 0x3d4) - (*(short *)(param_2 + 0x3d4) >> 3);

  // kart angle = (kart angle + (rotationSpinRate * time lapsed between frames)) & 0xFFF
  uVar2 = *(short *)(param_2 + 0x39a) +
          (short)((int)*(short *)(param_2 + 0x3b4) * *(int *)(puVar1 + 0x1d04) >> 0xd) & 0xfff;
  *(ushort *)(param_2 + 0x39a) = uVar2;
  
  // cameraRotY = ??? + kart angle + drift angle
  *(short *)(param_2 + 0x2ee) = *(short *)(param_2 + 0x3d4) + uVar2 + *(short *)(param_2 + 0x3c6);

  // Interpolate rotation by speed
  uVar3 = FUN_80058f54((int)*(short *)(param_2 + 0x2f2),(*(int *)(puVar1 + 0x1d04) << 5) >> 5,0);

  // set new rotation around player
  *(undefined2 *)(param_2 + 0x2f2) = uVar3;

  // VehPhysForce_RotAxisAngle
  FUN_8005f89c(param_2 + 0x310,param_2 + 0x360,(int)*(short *)(param_2 + 0x39a));
  return;
}

// VehPhysProc_SpinFirst_InitSetUpdate
// param1 = thread, param2 = driver
void FUN_80063eac(undefined4 param_1,int param_2)

{
  // This delays setting the
  // update function, by one frame

  // OnInit
  *(undefined4 *)(param_2 + 0x54) = 0;

  // VehPhysProc_SpinFirst_Update
  *(undefined4 *)(param_2 + 0x58) = 0x80063cf4;
  return;
}

// VehPhysProc_SpinFirst_Init
// param1 = thread, param2 = driver
void FUN_80063ec0(undefined4 param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;

  // Kart is now spinning out
  *(undefined *)(param_2 + 0x376) = 3;

  *(undefined2 *)(param_2 + 0x3d2) = 0;
  *(undefined2 *)(param_2 + 0x3dc) = 0;

  // Check if 231 dll is loaded
  iVar1 = FUN_800348e8();

  if (
		// if it is loaded
		(iVar1 != 0) &&

		// If you're not in Adventure Arena
		((*(uint *)PTR_DAT_8008d2ac & 0x100000) == 0)
	 )
  {
	// RB_Player_ModifyWumpa, -1
    FUN_800abefc(param_2,0xffffffff);
  }

  // Make driver talk
  FUN_8002cbe8(3,(int)(short)(&DAT_80086e84)[*(byte *)(param_2 + 0x4a)],0x10);

  // spin left
  *(undefined2 *)(param_2 + 0x582) = 1;

  // spin rate = 300
  *(undefined2 *)(param_2 + 0x580) = 300;

  // if you're spinning to the right
  if (*(short *)(param_2 + 0xc0) < 0)
  {
	// spin rate = -300
    *(undefined2 *)(param_2 + 0x580) = 0xfed4;
	
	// spin right (-1)
    *(undefined2 *)(param_2 + 0x582) = 0xffff;
  }

  // Set function pointers for spinning out
  *(undefined4 *)(param_2 + 0x54) = 0x80063eac // VehPhysProc_SpinFirst_InitSetUpdate
  *(undefined4 *)(param_2 + 0x5c) = 0x80063d44; // VehPhysProc_SpinFirst_PhysLinear
  *(undefined4 *)(param_2 + 0x60) = 0x80062a2c; // OnAudio
  *(undefined4 *)(param_2 + 100) = 0x80063dc8;
  *(undefined4 *)(param_2 + 0x68) = 0x8005ea60; // VehPhysForce_OnApplyForces
  *(undefined4 *)(param_2 + 0x6c) = 0x80020410; // COLL_StartSearch_NearPlayer
  *(undefined4 *)(param_2 + 0x70) = 0x8005ebac; // VehPhysForce_CollideDrivers
  *(undefined4 *)(param_2 + 0x74) = 0x8001d944; // COLL_StartSearch_Player
  *(undefined4 *)(param_2 + 0x78) = 0x80060630; // JumpAndFriction
  *(undefined4 *)(param_2 + 0x7c) = 0x8005ee34; // VehPhysForce_TranslateMatrix -- move position to instance matrix

  // VehFrameProc_Spinning
  *(undefined4 *)(param_2 + 0x80) = 0x8005b510;

  *(undefined4 *)(param_2 + 0x58) = 0;

  // VehEmitter_DriverMain
  *(undefined4 *)(param_2 + 0x84) = 0x80059a18;

  if (*(char *)(param_2 + 0x4b) < '\x01') {
    uVar2 = 0x19;
  }
  else {
    uVar2 = 0x29;
  }

  // GAMEPAD_JogCon1
  FUN_800263a0(param_2,uVar2,0x60);

  return;
}


// VehPhysProc_SpinLast_Update
// param1 = thread, param2 = driver
void FUN_8006402c(undefined4 param_1,int param_2)
{
  // Transition from spinning to driving

  int iVar1;

  // Get Drift Angle
  iVar1 = (int)*(short *)(param_2 + 0x3c6);

  // Get absolute value
  if (iVar1 < 0) {
    iVar1 = -iVar1;
  }

  // If you're almost fully facing forward
  if (iVar1 < 0x10)
  {
	// Change all funcPtrs to transition
	// from LastSpin to Driving
	// VehPhysProc_SpinStop_Init
    FUN_800644d0(param_1, param_2);
  }
  return;
}

// VehPhysProc_SpinLast_PhysLinear
// param1 = thread, param2 = driver
void FUN_8006406c(undefined4 param_1,int param_2)

{
  // VehPhysProc_Driving_PhysLinear
  FUN_8006181c();

  // reset two speed variables
  *(undefined2 *)(param_2 + 0x39c) = 0;
  *(undefined2 *)(param_2 + 0x39e) = 0;

  *(uint *)(param_2 + 0x2c8) = *(uint *)(param_2 + 0x2c8) | 0x4008;
  return;
}

// VehPhysProc_SpinLast_PhysAngular
// param1 = thread, param2 = driver
void FUN_800640a4(undefined4 param_1,int param_2)

{
  undefined *puVar1;
  ushort uVar2;
  undefined2 uVar3;
  short sVar4;
  int iVar5;

  // Get drifting angle
  iVar5 = (int)*(short *)(param_2 + 0x3c6);

  // Set drift angle (temporarily)
  *(undefined2 *)(param_2 + 0x3e6) = 10000;

  // decrease rotationSpinRate by 1/8 of itself
  sVar4 = *(short *)(param_2 + 0x3b4) - (*(short *)(param_2 + 0x3b4) >> 3);
  *(short *)(param_2 + 0x3b4) = sVar4;
  
  // decrease [what]?
  *(short *)(param_2 + 0x3d4) = *(short *)(param_2 + 0x3d4) - (*(short *)(param_2 + 0x3d4) >> 3);
  
  *(short *)(param_2 + 0xc0) = sVar4;
  
  if (iVar5 < 1) 
  {
	// drifting right,
	// spinning out clockwise
    if (iVar5 < 0) 
	{
      if (
			(
				// if spinning hasn't stopped
				(0 < *(short *)(param_2 + 0x580)) && 
				(-400 < iVar5)
			) &&
			(
				// decrease spin rate
				iVar5 = iVar5 * -4 >> 3, 
				*(undefined2 *)(param_2 + 0x580) = (short)iVar5, 
				
				// if spin rate is too low
				iVar5 < 0x20
			)
		  ) 
	  {
		// set minimum spin rate if drops below minimum
        *(undefined2 *)(param_2 + 0x580) = 0x20;
      }

	  // Drift angle = (drift angle + spin rate + 180 degrees) & 0xfff - 180 degrees
      uVar2 = (*(short *)(param_2 + 0x3c6) + *(short *)(param_2 + 0x580) + 0x800U & 0xfff) - 0x800;
	  *(ushort *)(param_2 + 0x3c6) = uVar2;

	  // if you're almost facing forward while spinning at a slow rate
      if ((0 < *(short *)(param_2 + 0x580)) && (0 < (int)((uint)uVar2 << 0x10))) 
	  {
		// reset drift angle (but still spin until StopSpin)
        *(undefined2 *)(param_2 + 0x3c6) = 0;
      }
    }
  }
  
  // spinning the other way
  else 
  {
    if (
			(
				// if spinning hasn't stopped
				(*(short *)(param_2 + 0x580) < 0) && 
				(iVar5 < 400)
			) &&
       
			(
				// decrease spin rate
				iVar5 = iVar5 * -4 >> 3, 
				*(undefined2 *)(param_2 + 0x580) = (short)iVar5,
				
				// if spin rate is too low
				-0x20 < iVar5
			)
		) 
	{
	  // set minimum spin rate if drops below minimum (-0x20)
      *(undefined2 *)(param_2 + 0x580) = 0xffe0;
    }
	
	// Drift angle = (drift angle + spin rate + 180 degrees) & 0xfff - 180 degrees
    uVar2 = (*(short *)(param_2 + 0x3c6) + *(short *)(param_2 + 0x580) + 0x800U & 0xfff) - 0x800;
    *(ushort *)(param_2 + 0x3c6) = uVar2;
	
	// if you're almost facing forward while spinning at a slow rate
    if ((*(short *)(param_2 + 0x580) < 0) && ((int)((uint)uVar2 << 0x10) < 0)) 
	{
		// reset drift angle (but still spin until StopSpin)
      *(undefined2 *)(param_2 + 0x3c6) = 0;
    }
  }
  
  puVar1 = PTR_DAT_8008d2ac;
  
  // kart angle = (kart angle + 
  uVar2 = *(short *)(param_2 + 0x39a) +
			(short)
			(
				// ampTurnState
				(int)*(short *)(param_2 + 0xc0) * 
				
				// elapsed milliseconds per frame, ~32
			*(int *)(PTR_DAT_8008d2ac + 0x1d04) >> 0xd
			
			// clamp to [0x000-0xfff]
			) & 0xfff;

  // save
  *(ushort *)(param_2 + 0x39a) = uVar2;
  
  // cameraRotY = ??? + kart angle + drift angle
  *(short *)(param_2 + 0x2ee) = *(short *)(param_2 + 0x3d4) + uVar2 + *(short *)(param_2 + 0x3c6);

  // Interpolate rotation by speed
  uVar3 = FUN_80058f54((int)*(short *)(param_2 + 0x2f2),(*(int *)(puVar1 + 0x1d04) << 5) >> 5,0);

  // set new camera rotation around player
  *(undefined2 *)(param_2 + 0x2f2) = uVar3;

  // VehPhysForce_RotAxisAngle
  FUN_8005f89c(param_2 + 0x310,param_2 + 0x360,(int)*(short *)(param_2 + 0x39a));
  return;
}


// param1 = thread, param2 = driver
// VehPhysProc_SpinLast_Init
void FUN_80064254(undefined4 param_1,int param_2)
{
	// Transition out of spinning

  // VehPhysProc_SpinLast_Update
  *(undefined4 *)(param_2 + 0x58) = 0x8006402c;

  // VehPhysProc_SpinLast_PhysLinear
  *(undefined4 *)(param_2 + 0x5c) = 0x8006406c;

  *(undefined4 *)(param_2 + 0x60) = 0x80062a2c; // OnAudio
  *(undefined4 *)(param_2 + 100) = 0x800640a4; // OnPhysAngular
  *(undefined4 *)(param_2 + 0x68) = 0x8005ea60; // VehPhysForce_OnApplyForces
  *(undefined4 *)(param_2 + 0x6c) = 0x80020410; // COLL_StartSearch_NearPlayer
  *(undefined4 *)(param_2 + 0x70) = 0x8005ebac; // VehPhysForce_CollideDrivers
  *(undefined4 *)(param_2 + 0x74) = 0x8001d944; // COLL_StartSearch_Player
  *(undefined4 *)(param_2 + 0x78) = 0x80060630; // JumpAndFriction
  *(undefined4 *)(param_2 + 0x7c) = 0x8005ee34; // VehPhysForce_TranslateMatrix -- move position to instance matrix

  // VehFrameProc_LastSpin
  *(undefined4 *)(param_2 + 0x80) = 0x8005b5fc;

  *(undefined4 *)(param_2 + 0x54) = 0;

  // VehEmitter_DriverMain
  *(undefined4 *)(param_2 + 0x84) = 0x80059a18;

  return;
}

// VehPhysProc_SpinStop_Update
void FUN_800642ec(void)
{
  return;
}

// VehPhysProc_SpinStop_PhysLinear
// param1 = thread, param2 = driver
void FUN_800642f4(undefined4 param_1,int param_2)
{
  // VehPhysProc_Driving_PhysLinear
  FUN_8006181c();

  // reset two speed variables
  *(undefined2 *)(param_2 + 0x39c) = 0;
  *(undefined2 *)(param_2 + 0x39e) = 0;

  return;
}

// VehPhysProc_SpinStop_PhysAngular
// param1 = thread, param2 = driver
void FUN_80064320(undefined4 param_1,int param_2)
{
  undefined *puVar1;
  ushort uVar2;
  undefined2 uVar3;

  puVar1 = PTR_DAT_8008d2ac;

  // increase spin by (lastFrameSpinRate * elapsedTime)
  uVar2 = *(short *)(param_2 + 0x39a) +
          (short)((int)*(short *)(param_2 + 0xc0) * *(int *)(PTR_DAT_8008d2ac + 0x1d04) >> 0xd) &
          0xfff;

  *(ushort *)(param_2 + 0x39a) = uVar2;
  
  // cameraRotY = spinRate + kart angle + drift angle,
  // spin rate is added so you're one frame ahead
  *(short *)(param_2 + 0x2ee) = *(short *)(param_2 + 0x3d4) + uVar2 + *(short *)(param_2 + 0x3c6);

  // Interpolate rotation by speed
  uVar3 = FUN_80058f54((int)*(short *)(param_2 + 0x2f2),(*(int *)(puVar1 + 0x1d04) << 5) >> 5,0);

  puVar1 = PTR_DAT_8008d2ac;

  // set new camera rotation around player
  *(undefined2 *)(param_2 + 0x2f2) = uVar3;

  // Interpolate rotation by speed
  uVar3 = FUN_80058f54((int)*(short *)(param_2 + 0x3c6),(*(int *)(puVar1 + 0x1d04) << 7) >> 5,0);
  *(undefined2 *)(param_2 + 0x3c6) = uVar3;

  // VehPhysForce_RotAxisAngle
  FUN_8005f89c(param_2 + 0x310,param_2 + 0x360,(int)*(short *)(param_2 + 0x39a));
  return;
}


// param1 = thread, param2 = driver
// VehPhysProc_SpinStop_Animate
void FUN_800643d4(int param_1,int param_2)

{
  ushort uVar1;
  short sVar2;
  int iVar3;
  int iVar4;

  // get instance from thread
  iVar4 = *(int *)(param_1 + 0x34);

  // get number of frames in animation
  iVar3 = FUN_8005b0f4(iVar4,(uint)*(byte *)(iVar4 + 0x52));

  // if there are frames
  if (0 < iVar3)
  {
	// if you are spinning right
    if (*(short *)(param_2 + 0x582) == -1) 
	{
	  // steer from left to right, to exaggerate
	  // the force when steering stops abruptly
      sVar2 = *(short *)(iVar4 + 0x54) + 5;
      *(short *)(iVar4 + 0x54) = sVar2;
	  
	  // if not finished, quit function
      if (sVar2 < iVar3) {
        return;
      }
	  
	  // last frame
      *(short *)(iVar4 + 0x54) = (short)iVar3 + -1;
      
	  // no spinDir anymore
	  *(undefined2 *)(param_2 + 0x582) = 0;
      
	  return;
    }

	// if you are spinning left
    if (*(short *)(param_2 + 0x582) == 1) 
	{
	  // steer from right to left, to exaggerate
	  // the force when steering stops abruptly
      uVar1 = *(short *)(iVar4 + 0x54) - 5;
      *(ushort *)(iVar4 + 0x54) = uVar1;
	  
	  // if not finished, quit function
      if (-1 < (int)((uint)uVar1 << 0x10)) {
        return;
      }
	  
	  // first frame
      *(undefined2 *)(iVar4 + 0x54) = 0;
	  
	  // no spinDir anymore
      *(undefined2 *)(param_2 + 0x582) = 0;
	  
      return;
    }

	// === spinning has stopped ===
	
	// return driver to center steering 
	// animation frame

	// VehFrameInst_GetStartFrame(midpoint, numFrames)
    iVar3 = FUN_8005b0c4(0,iVar3);

	// Interpolate rotation by speed
    sVar2 = FUN_80058f54((int)*(short *)(iVar4 + 0x54),2,iVar3);

	// set animation frame
    *(short *)(iVar4 + 0x54) = sVar2;

	// if you are not facing forward
    if ((int)sVar2 != iVar3)
	{
	  // keep spinning till you face forward
      return;
    }
  }

  // if you are facing forward

  // VehPhysProc_Driving_Init
  *(undefined4 *)(param_2 + 0x54) = 0x80062b74;
  return;
}

// param1 = thread, param2 = driver
// VehPhysProc_SpinStop_Init
void FUN_800644d0(undefined4 param_1,int param_2)

{
  // Transition from
  // LastSpin to Driving

  // VehPhysProc_SpinStop_Update,
  // "updating" happens in OnAnimate
  *(undefined4 *)(param_2 + 0x58) = 0x800642ec;

  // VehPhysProc_SpinStop_PhysLinear
  *(undefined4 *)(param_2 + 0x5c) = 0x800642f4;

  *(undefined4 *)(param_2 + 0x60) = 0x80062a2c; // OnAudio
  *(undefined4 *)(param_2 + 100) = 0x80064320; // OnPhysAngular
  *(undefined4 *)(param_2 + 0x68) = 0x8005ea60; // VehPhysForce_OnApplyForces
  *(undefined4 *)(param_2 + 0x6c) = 0x80020410; // COLL_StartSearch_NearPlayer
  *(undefined4 *)(param_2 + 0x70) = 0x8005ebac; // VehPhysForce_CollideDrivers
  *(undefined4 *)(param_2 + 0x74) = 0x8001d944; // COLL_StartSearch_Player
  *(undefined4 *)(param_2 + 0x78) = 0x80060630; // JumpAndFriction
  *(undefined4 *)(param_2 + 0x7c) = 0x8005ee34; // VehPhysForce_TranslateMatrix -- move position to instance matrix

  // VehPhysProc_SpinStop_Animate, calls VehPhysProc_Driving_Init
  *(undefined4 *)(param_2 + 0x80) = 0x800643d4;

  *(undefined4 *)(param_2 + 0x54) = 0;

  // VehEmitter_DriverMain
  *(undefined4 *)(param_2 + 0x84) = 0x80059a18;

  return;
}


// VehPickState_NewState
// param1 - driverVictim
// param2 - damageType
// param3 - driverAttacker
// param4 - reason
undefined4 FUN_80064568(int param_1,int param_2,int param_3,undefined4 param_4)

{
  char cVar1;
  byte bVar2;
  undefined4 uVar3;
  undefined *puVar4;
  undefined4 in_zero;
  undefined4 in_at;
  undefined *puVar5;
  int iVar6;
  int iVar7;
  undefined4 local_30;
  uint local_2c;
  short local_28;
  short sStack38;

  // get kart state
  cVar1 = *(char *)(param_1 + 0x376);
  *(undefined *)(param_1 + 0x4ff) = 0;

  // if kart is being mask-grabbed
  if (cVar1 == '\x05') {
    return 0;
  }

  if (
		// If player is using mask weapon
		((*(uint *)(param_1 + 0x2c8) & 0x800000) != 0) ||

		// If player invincibility timer is active
		(*(int *)(param_1 + 0x24) != 0)
	 )
  {
	// Player / AI structure + 0x4a shows driver index (0-7)

	// which driver this is (0-7)
	bVar2 = *(byte *)(param_1 + 0x4a);

LAB_8006462c:

	// Theory
	// Play sound of character laughing because they
	// were hit by weapon while invincible, and therefore
	// they take no damage

	// Voiceline_RequestPlay
    FUN_8002cbe8(2,(int)(short)(&DAT_80086e84)[bVar2],0x10);
    return 0;
  }

  // if you have a shield weapon
  if (*(int *)(param_1 + 0x14) != 0)
  {
	// driver -> shield -> thread -> object
    iVar6 = *(int *)(*(int *)(*(int *)(param_1 + 0x14) + 0x6c) + 0x30);

    *(ushort *)(iVar6 + 6) = *(ushort *)(iVar6 + 6) | 1;

	// give invincibility
    *(undefined4 *)(param_1 + 0x24) = 0x2a0;

    bVar2 = *(byte *)(param_1 + 0x4a);

	// you no-longer have a shield
    *(undefined4 *)(param_1 + 0x14) = 0;

    goto LAB_8006462c;
  }

  // driving
  if (param_2 == 0) {
    return 1;
  }

  // driver -> instance -> thread
  iVar6 = *(int *)(*(int *)(param_1 + 0x1c) + 0x6c);

  // Squish
  if (param_2 == 3) {
    if (cVar1 != '\x03')
	{
	  // OtherFX_Play_Echo
	  // squish sound
      FUN_80028494(0x5a,1,*(uint *)(param_1 + 0x2c8) >> 0x10 & 1);

	  // Voiceline_RequestPlay
      FUN_8002cbe8(4,(int)(short)(&DAT_80086e84)[*(byte *)(param_1 + 0x4a)],0x10);
    }

	// squish the character, put them into squished
	// animation for 0xF00 amount of time (frames?)
    *(undefined2 *)(param_1 + 0x404) = 0xf00;

	// NoInput = 0.25s
    *(undefined2 *)(param_1 + 0x400) = 0xf0;
  }
  else {
    if (param_2 < 4) {

	  // Blast
      if (param_2 == 2) {

		// if kart is already being "blasted"
        if (cVar1 == '\x06') {
          return 0;
        }

		// if function pointer is already set to make the kart "blasted"
        if (*(code **)(param_1 + 0x54) == FUN_800682a4) {
          return 0;
        }

		// You are only here if the player is not being
		// blasted, but needs to be blasted after being hit

		// NoInput = 2.4 seconds
        *(undefined2 *)(param_1 + 0x400) = 0x960;

		// Player / AI structure + 0x4a shows driver index (0-7)


		// which driver this is (0-7)
        bVar2 = *(byte *)(param_1 + 0x4a);

		// Undo the "Squish" effect
		*(undefined2 *)(param_1 + 0x404) = 0;

		// VehStuckProc_Tumble_Init
        *(undefined4 *)(param_1 + 0x54) = 0x800682a4;

LAB_800646f0:

		// Voiceline_RequestPlay
		FUN_8002cbe8(1,(int)(short)(&DAT_80086e84)[bVar2],0x10);
        goto LAB_800647d8;
      }
    }
    else {

	  // Burn
      if (param_2 == 4) {

		// If player is not currently burned
        if (*(short *)(param_1 + 0x402) == 0)
		{
		  // OtherFX_Play "Just got Burned" sound
          FUN_80028468(0x69,1);

		  // Make driver talk
          FUN_8002cbe8(1,(int)(short)(&DAT_80086e84)[*(byte *)(param_1 + 0x4a)],0x10);
        }

		// Add to player's Burned timer
        *(undefined2 *)(param_1 + 0x402) = 0xf00;

		// NoInput set to 2.0 seconds
        *(undefined2 *)(param_1 + 0x400) = 0x780;

        goto LAB_800647c8;
      }

	  // mask grab
      if (param_2 == 5)
	  {
		// NoInput set to 3.36 seconds
        *(undefined2 *)(param_1 + 0x400) = 0xd20;

		// VehStuckProc_PlantEaten_Init
        *(undefined4 *)(param_1 + 0x54) = 0x800677d0;

        bVar2 = *(byte *)(param_1 + 0x4a);
        goto LAB_800646f0;
      }
    }

	// NoInput set to 1.0 seconds
    *(undefined2 *)(param_1 + 0x400) = 0x3c0;

	// If you're spinning: if you hit a glass or spun out from drifting
    if (*(char *)(param_1 + 0x376) == '\x03') goto LAB_800647d8;
  }
LAB_800647c8:

  // VehPhysProc_SpinFirst_Init
  *(undefined4 *)(param_1 + 0x54) = 0x80063ec0;

LAB_800647d8:
  switch(param_4) {
  case 1:
  
	// number of times bomb hit you
    *(char *)(param_1 + 0x55e) = *(char *)(param_1 + 0x55e) + '\x01';
	
    if ((param_3 != 0) && (param_3 != param_1)) 
	{
      // number of times your bomb hit someone
	  *(char *)(param_3 + 0x55a) = *(char *)(param_3 + 0x55a) + '\x01';
      *(ushort *)(param_3 + 0x4f6) = *(ushort *)(param_3 + 0x4f6) | 1;
    }
    break;
	
  // hit by motionless potion
  case 2:
	// number of times motionless potion hit you
    *(char *)(param_1 + 0x55f) = *(char *)(param_1 + 0x55f) + '\x01';
    break;
  
  case 3:
    
	// number of times missile hit you
	*(char *)(param_1 + 0x55d) = *(char *)(param_1 + 0x55d) + '\x01';
    
	if ((param_3 != 0) && (param_3 != param_1)) {
      
	  // number of times you hit someone with missile
	  *(char *)(param_3 + 0x557) = *(char *)(param_3 + 0x557) + '\x01';
	  *(ushort *)(param_3 + 0x4f6) = *(ushort *)(param_3 + 0x4f6) | 2;
    }
    break;
	
  // hit by moving potion
  case 4:
    if ((param_3 != 0) && (param_3 != param_1)) 
	{
	  // number of times you hit someone with potion moving potion
      *(char *)(param_3 + 0x556) = *(char *)(param_3 + 0x556) + '\x01';
      *(ushort *)(param_3 + 0x4f6) = *(ushort *)(param_3 + 0x4f6) | 4;
    }
    break;
	
  // squished by other driver's turbo
  case 5:
    if ((param_3 != 0) && (param_3 != param_1)) 
	{
	  // number of times you squished someone
      *(char *)(param_3 + 0x55b) = *(char *)(param_3 + 0x55b) + '\x01';
    }
    break;
	
  // hit by a mask weapon
  case 6:
    if ((param_3 != 0) && (param_3 != param_1)) 
	{
	  // set flag to the driver that did the attacking with mask weapon
      *(ushort *)(param_3 + 0x4f6) = *(ushort *)(param_3 + 0x4f6) | 8;
    }
  }
  *(undefined *)(param_1 + 0x376) = 0;
  *(undefined2 *)(param_1 + 0x3e2) = 0;
  *(undefined2 *)(param_1 + 0x3de) = 0;
  *(undefined *)(param_1 + 0x4c) = 0;
  *(undefined *)(param_1 + 0x4d) = 0;

  // GAMEPAD_ShockFreq and GAMEPAD_ShockForce1
  FUN_80026440(param_1,8,0);
  FUN_800264c0(param_1,8,0x7f);

  puVar4 = PTR_DAT_8008d2ac;

  // If you're not in End-Of-Race menu
  if ((param_3 != 0) && ((*(uint *)PTR_DAT_8008d2ac & 0x200000) == 0))
  {
    local_30 = CONCAT22(*(undefined2 *)(*(int *)(param_3 + 0x1c) + 0x48),
                        *(undefined2 *)(*(int *)(param_3 + 0x1c) + 0x44));

    local_2c = local_2c & 0xffff0000 | (uint)*(ushort *)(*(int *)(param_3 + 0x1c) + 0x4c);

	// camera index depending on player
    puVar5 = PTR_DAT_8008d2ac + (uint)*(byte *)(param_3 + 0x4a) * 0x110;

	// pushBuffer ViewProj
	gte_SetRotMatrix(puVar5 + 0x168 + 0x28);
	gte_SetTransMatrix(puVar5 + 0x168 + 0x28);
    
	// instance position on GTE
	gte_ldv0(&local_30);

	// RTPS - Perspective Transformation (single)
	gte_rtps();

	// get screenspace pos of driver
	gte_stsxy(&uVar3);
	
	// X
    local_28 = (short)uVar3;

	// set position of HUD element to position of driver (on screen)
	*(short *)(param_3 + 0x4d4) =
         local_28 + *(short *)(PTR_DAT_8008d2ac + (uint)*(byte *)(param_3 + 0x4a) * 0x110 + 0x184);
    
	// Y
	sStack38 = (short)((uint)uVar3 >> 0x10);
    *(short *)(param_3 + 0x4d6) =
         sStack38 + *(short *)(puVar4 + (uint)*(byte *)(param_3 + 0x4a) * 0x110 + 0x186) + -0x14;

	// loop counter
	iVar7 = 0;

	// for iVar7 = 0; iVar7 < 1; iVar7++
    do
	{
	  // this only happens once

	  // RB_Player_KillPlayer
      FUN_800abbb4(param_3,param_1);

	  // === Naughty Dog Bug ===
	  // If you're in End-Of-Race menu (impossible)
      if ((*(uint *)PTR_DAT_8008d2ac & 0x200000) != 0) 
	  {
		// save something in the player that got the kill,
		// and the player that got killed
        *(undefined2 *)(param_3 + 0x4f0) = (short)param_4;
        *(undefined2 *)(param_1 + 0x4f4) = (short)param_4;
      }

	  // increment loop counter
      iVar7 = iVar7 + 1;
    } while (iVar7 < 1);

    if (
			// if attacked yourself
			(param_3 == param_1) &&

			// If you have a point limit (battle)
			((*(uint *)PTR_DAT_8008d2ac & 0x4000) != 0)
		)
	{
      if (*(int *)(param_1 + 0x4d0) == 5)
	  {
		// scoreDelta
        *(int *)(param_1 + 0x4dc) = *(int *)(param_1 + 0x4dc) + -1;
      }
      else
	  {
		// scoreDelta
        *(undefined4 *)(param_1 + 0x4dc) = 0xffffffff;
      }
    }
    
	// did not attack self
	else
	{
      if (*(int *)(param_3 + 0x4d0) == 5)
	  {
		// scoreDelta
        *(int *)(param_3 + 0x4dc) = *(int *)(param_3 + 0x4dc) + 1;
      }

      else
	  {
		// scoreDelta
        *(undefined4 *)(param_3 + 0x4dc) = 1;
      }
    }
	
	// cooldown
    *(undefined4 *)(param_3 + 0x4d0) = 5;
	
	// param_3 is attacker,
	// param_1 is attacked
    
	// count number of times attacked by this player
	// param_1->0x560[param_3->driverID]++
	iVar7 = param_1 + (uint)*(byte *)(param_3 + 0x4a);
    *(char *)(iVar7 + 0x560) = *(char *)(iVar7 + 0x560) + '\x01';
	
	// count number of times attacking this player
	// param_1->0x50c[param_3->driverID]++
    iVar7 = param_3 + (uint)*(byte *)(param_1 + 0x4a);
    *(char *)(iVar7 + 0x50c) = *(char *)(iVar7 + 0x50c) + '\x01';
    
	// if did not attack yourself
	if (param_3 != param_1) 
	{
	  // count number of times attacking
      *(char *)(param_3 + 0x559) = *(char *)(param_3 + 0x559) + '\x01';
    }
  }

  // enable collision for this thread
  *(uint *)(iVar6 + 0x1c) = *(uint *)(iVar6 + 0x1c) & 0xffffefff;

  // make visible
  *(uint *)(*(int *)(param_1 + 0x1c) + 0x28) =
  *(uint *)(*(int *)(param_1 + 0x1c) + 0x28) & 0xffffff7f;

  return 1;
}


// VehPickupItem_MaskBoolGoodGuy
undefined4 FUN_80064be4(int param_1)

{
  // character ID (0 for crash, 1 for cortex, 2 for tiny, etc)
  short sVar1;

  // return (0 for uka, 1 for aku)
  undefined4 uVar2;

  // Player / AI structure + 0x4a shows driver index (0-7)


  // get character ID of current player (p1, p2, p3, etc)
  sVar1 = (&DAT_80086e84)[*(byte *)(param_1 + 0x4a)];

  // by default, player is bad guy and uses uka uka
  uVar2 = 0;

  // if you are crash, 		coco				polar			pura	or		penta
  if ((((sVar1 == 0) || (sVar1 == 3)) || (sVar1 == 6)) || ((sVar1 == 7 || (sVar1 == 0xd))))
  {
	// you are a good guy, use aku aku
    uVar2 = 1;
  }

  // return whether you use aku or uka
  return uVar2;
}


// VehPickupItem_MaskUseWeapon
// param1 is driver
// param2 (0 for mask grab, 1 for weapon)
undefined2 * FUN_80064c38(int param_1,int param_2)

{
  undefined2 uVar1;
  int iVar2;
  undefined2 *puVar3;
  uint uVar4;
  undefined4 uVar5;
  int iVar6;

  // Check if 231 dll is loaded
  iVar2 = FUN_800348e8();

  if (
		// if it is not loaded
		(iVar2 == 0) ||

		// If you're in Adventure Arena
		((*(uint *)PTR_DAT_8008d2ac & 0x100000) != 0)
	)
  {
	// return nullptr
	// no mask object in adv arena
    puVar3 = (undefined2 *)0x0;
  }
  else
  {
	// driver -> instance -> thread
    iVar6 = *(int *)(*(int *)(param_1 + 0x1c) + 0x6c);

	// thread -> childThread,
	// which gets mask thread from driver
    iVar2 = *(int *)(iVar6 + 0x14);

	// while pointer is not nullptr
    while (iVar2 != 0)
	{
	  // if thread->modelIndex is Aku or Uka
      if ((uint)*(ushort *)(iVar2 + 0x44) - 0x39 < 2)
	  {
		// RB_MaskWeapon_ThTick
        *(undefined4 *)(iVar2 + 0x2c) = 0x800afdbc;

		// short duration
        uVar1 = 0x1e00;

		// if wumpa is less than 10
        if (*(char *)(param_1 + 0x30) < '\n') {
          iVar6 = *(int *)(iVar2 + 0x30);
        }

		// if wumpa is 10
        else {
          iVar6 = *(int *)(iVar2 + 0x30);

		  // long duration
          uVar1 = 0x2d00;
        }

		// duration
        *(undefined2 *)(iVar6 + 6) = uVar1;

        if (
				// If this is human and not AI
				((*(uint *)(param_1 + 0x2c8) & 0x100000) == 0) &&

				// if this is not a mask grab
				(param_2 != 0)
			)
		{
		  // if thread->modelIndex == Uka
          if (*(short *)(iVar2 + 0x44) == 0x3a) {
            uVar5 = 0x54;
          }

		  // if it is not aku
          else
		  {
			// if thread->modelIndex == Aku
            if (*(short *)(iVar2 + 0x44) != 0x39) goto LAB_80064d4c;
            uVar5 = 0x53;
          }

		  // OtherFX_Play_Echo
		  // activate mask weapon
          FUN_80028494(uVar5,1,*(uint *)(param_1 + 0x2c8) >> 0x10 & 1);
        }
LAB_80064d4c:

		// thread -> flags
        *(uint *)(iVar2 + 0x1c) = *(uint *)(iVar2 + 0x1c) & 0xfffff7ff;

		// return object attached to thread
        return (undefined2 *)*(undefined4 *)(iVar2 + 0x30);
      }

	  // go to next pointer
      iVar2 = *(int *)(iVar2 + 0x10);
    }

	// VehPickupItem_MaskBoolGoodGuy
    uVar4 = FUN_80064be4(param_1);

	// If player uses Uka weapon
    if ((uVar4 & 0xffff) == 0)
	{
	  // s_doctor1_8008d62c
	  // "doctor1"

	  // 0x3a is index of model pointer array
	  // for uka head model

	  // 0x300 flag = SmallStackPool
	  // 0xd = "other" thread bucket
      iVar2 = FUN_800309a4(0x3a,s_doctor1_8008d62c,0x300,0xd,&DAT_800afdbc,0x14,iVar6);

	  // If this is human and not AI
      if (((*(uint *)(param_1 + 0x2c8) & 0x100000) == 0) &&

		  // OtherFX_Play_Echo
		  // uka activate
         (FUN_80028494(0x54,1,*(uint *)(param_1 + 0x2c8) >> 0x10 & 1),

         1 < (uint)*(byte *)(param_1 + 0x376) - 4))
	  {
		// Start playing uka uka mask song
        *(uint *)PTR_DAT_8008d2ac = *(uint *)PTR_DAT_8008d2ac & 0xfeffffff | 0x2000000;
      }

	  // get thread
      iVar6 = *(int *)(iVar2 + 0x6c);

	  // model pointer to uka beam
      uVar5 = *(undefined4 *)(PTR_DAT_8008d2ac + 0x2260);
    }

	// If player uses Aku weapon
    else
	{
	  // s_doctor1_8008d62c
	  // "doctor1"

	  // 0x3a is index of model pointer array
	  // for aku head model

	  // 0x300 flag = SmallStackPool
	  // 0xd = "other" thread bucket
      iVar2 = FUN_800309a4(0x39,s_doctor1_8008d62c,0x300,0xd,&DAT_800afdbc,0x14,iVar6);

	  // If this is human and not AI
      if (((*(uint *)(param_1 + 0x2c8) & 0x100000) == 0) &&

		  // OtherFX_Play_Echo
		  // aku mask grab
         (FUN_80028494(0x53,1,*(uint *)(param_1 + 0x2c8) >> 0x10 & 1),
         1 < (uint)*(byte *)(param_1 + 0x376) - 4))
	  {
		// Start playing aku aku mask song
        *(uint *)PTR_DAT_8008d2ac = *(uint *)PTR_DAT_8008d2ac & 0xfdffffff | 0x1000000;
      }

	  // get thread from instance
      iVar6 = *(int *)(iVar2 + 0x6c);

	  // model pointer for aku beam
      uVar5 = *(undefined4 *)(PTR_DAT_8008d2ac + 0x2258);
    }

	// get mask head object from thread
    puVar3 = *(undefined2 **)(iVar6 + 0x30);

	// INSTANCE_Birth3D -- ptrModel, name, thread
    uVar5 = FUN_8003086c(uVar5,"akubeam1",iVar6);

	// give beam instance to mask head object
    *(undefined4 *)(puVar3 + 4) = uVar5;

	// set funcThDestroy to remove instance from instance pool
    *(undefined4 *)(iVar6 + 0x24) = 0x80041dfc;

	// allow this thread to ignore all collisions
    *(uint *)(iVar6 + 0x1c) = *(uint *)(iVar6 + 0x1c) | 0x1000;

	// make mask head invisible
    *(uint *)(iVar2 + 0x28) = *(uint *)(iVar2 + 0x28) | 0x80;

	// make mask beam invisible
    *(uint *)(*(int *)(puVar3 + 4) + 0x28) = *(uint *)(*(int *)(puVar3 + 4) + 0x28) | 0x80;

	// mask duration without 10 wumpa
	uVar1 = 0x1e00;

	// if 9 < number of wumpa
	// if wumpa is 10
	if ('\t' < *(char *)(param_1 + 0x30))
	{
	  // increased mask duration
      uVar1 = 0x2d00;
    }

	// duration
    puVar3[3] = uVar1;

	// rotX
    *puVar3 = 0x40;

	// rotY
    puVar3[1] = 0;

	// scale
    puVar3[9] = 0x1000;

	// rotZ
    puVar3[2] = 0;
  }

  // return mask object
  return puVar3;
}


// VehPickupItem_MissileGetTargetDriver
// param_1 driver who shot weapon
// return driver who will be chased
int FUN_80064f94(int param_1)

{
  int iVar1;
  int iVar2;
  MATRIX *pMVar3;
  int iVar4;
  int iVar5;
  long *r0;
  int iVar6;
  int iVar7;
  undefined *puVar8;
  undefined *puVar9;
  undefined auStack128 [16];
  undefined2 local_70;
  undefined2 local_6e;
  undefined2 local_6c;
  MATRIX MStack104;
  undefined auStack72 [48];

  puVar9 = auStack128;
  puVar8 = auStack128;

  // the ID of the player that the missile will chase
  iVar7 = 0;

  // set minimum distance from P1 to max possible distance
  iVar6 = 0x7fffffff;

  // if player shot missile
  // driver -> instance -> thread -> modelIndex == "player" of any kind
  if (*(short *)(*(int *)(*(int *)(param_1 + 0x1c) + 0x6c) + 0x44) == 0x18)
  {
	// pushBuffer ViewProj
    pMVar3 = (MATRIX *)(PTR_DAT_8008d2ac + (uint)*(byte *)(param_1 + 0x4a) * 0x110 + 0x168 + 0x28);
    gte_SetRotMatrix(pMVar3);
    gte_SetTransMatrix(pMVar3);
    puVar9 = puVar8;
  }

  // if robotcar shot missile
  else
  {
	// get rotation of AI
    local_70 = *(undefined2 *)(param_1 + 0x2ec);
    pMVar3 = &MStack104;
    local_6e = *(undefined2 *)(param_1 + 0x2ee);
    local_6c = *(undefined2 *)(param_1 + 0x2f0);

	// convert 3 rotation shorts into rotation matrix
    FUN_8006c2a4(pMVar3,&local_70);

	// get position of AI
    MStack104.t[0] = *(int *)(param_1 + 0x2d4) >> 8;
    MStack104.t[1] = *(int *)(param_1 + 0x2d8) >> 8;
    MStack104.t[2] = *(int *)(param_1 + 0x2dc) >> 8;

	// output: matrix ???
	// input: missile matrix
	// MATH_HitboxMatrix
    FUN_8003d264(auStack72,pMVar3);

    gte_SetRotMatrix(pMVar3);
    gte_SetTransMatrix(pMVar3);
  }

  // loop counter
  iVar5 = 0;

  r0 = (long *)(puVar9 + 0x60);

  // for iVar6 = 0; iVar6 < 8; iVar6++
  do
  {
	// get pointer to current player's structure
    iVar4 = *(int *)(PTR_DAT_8008d2ac + iVar5 * 4 + 0x24ec);

    if (
			(
				// if you hit a player with a weapon that is not yourself
				(
					// if pointer is not nullptr
					(iVar4 != 0) &&

					// if pointer is not the same as param1
					(iVar4 != param_1)
				) &&

				// if player hit, is not being picked up by mask
				(*(char *)(iVar4 + 0x376) != '\x05')
			) &&

			(
				(
					(
						// If you're not in Battle Mode
						(*(uint *)PTR_DAT_8008d2ac & 0x20) == 0 ||

						// if you are in battle mode,
						// if one player hit another that is on a different team
						(*(int *)(iVar4 + 0x4e8) != *(int *)(param_1 + 0x4e8))
					) &&

					// if player is not invisible
					(*(int *)(iVar4 + 0x28) == 0)
				)
			)
		)

	// If you hard-code iVar5 + 0x376 to be 5,
	// player can't be hit, weapons go right through them

	// however, if player hits another player on the same team,
	// and if this block still does not execute, the player hit still
	// gets animated like any other player getting hit

    {
	  // set position to driver -> instSelf -> position
      *(undefined2 *)(puVar9 + 0x58) = *(undefined2 *)(*(int *)(iVar4 + 0x1c) + 0x44);
      *(undefined2 *)(puVar9 + 0x5a) = *(undefined2 *)(*(int *)(iVar4 + 0x1c) + 0x48);
      *(undefined2 *)(puVar9 + 0x5c) = *(undefined2 *)(*(int *)(iVar4 + 0x1c) + 0x4c);
      gte_ldv0((SVECTOR *)(puVar9 + 0x58));

	  // RTPS - Perspective Transformation (single)
      gte_rtps();

      gte_stsxy(r0);
      gte_stflg((long *)(puVar9 + 0x64));

      if (
			(
				// if driver is in front of camera view?
				((*(uint *)(puVar9 + 0x64) & 0x40000) == 0) &&
			
				// pixW > 30
				(0x1e < *(short *)(puVar9 + 0x60))
			) &&
			(
				(
					// pixW < pushBuffer[driverID]->rect.w - 30
					(int)*(short *)(puVar9 + 0x60) <
					*(short *)(PTR_DAT_8008d2ac + (uint)*(byte *)(param_1 + 0x4a) * 0x110 + 0x188) + -0x1e &&

					(
						(
							(
								// pixH > 20
								0x14 < *(short *)((int)r0 + 2) &&

								(
									// pixH < pushBuffer[driverID]->rect.h - 20
									(int)*(short *)((int)r0 + 2) <
									*(short *)(PTR_DAT_8008d2ac + (uint)*(byte *)(param_1 + 0x4a) * 0x110 + 0x18a) + -0x14
								)
							) &&

							(
								// get X distance between two players
								iVar1 = *(int *)(iVar4 + 0x2d4) - *(int *)(param_1 + 0x2d4) >> 8,

								// get Z distance between two players
								iVar2 = *(int *)(iVar4 + 0x2dc) - *(int *)(param_1 + 0x2dc) >> 8,

								// if player is closer to missile than previous closest player
								iVar1 = iVar1 * iVar1 + iVar2 * iVar2, iVar1 < iVar6
							)
						)
					)
				)
			)
		)
	  {
		// set smallest distance to current distance
        iVar6 = iVar1;

		// set closest player to this player
        iVar7 = iVar4;
      }
    }

	// increment loop counter
    iVar5 = iVar5 + 1;

  } while (iVar5 < 8);

  // return address of player that missile will chase
  return iVar7;
}


// VehPickupItem_PotionThrow
// param1 is object
// param2 is instance
// param3 is flags (like throw forward potion)
undefined4 FUN_800652c8(int param_1,int param_2,uint param_3)

{
  short sVar1;
  uint uVar2;
  int iVar3;
  undefined2 uVar4;

  // For TNTs param3 != 0 shoots tnt up into air,
  // direction does not change (komodo joe)

  // For Potions
  // param3 & 1 shoots back a short distance
  // param3 & 2 shoots back a long distance
  // param3 & 4 shoots forward (hold up on d-pad)

  // if you dont want to throw forward
  if ((param_3 & 4) == 0)
  {
	// if you dont want to throw back long
    if ((param_3 & 2) == 0)
	{
	  // if you dont want to throw back short
      if ((param_3 & 1) == 0)
	  {
		// just quit and drop weapon as-is
        return 0;
      }

	  // if you want to throw back short

      uVar2 = FUN_8006c684(&DAT_8008d668);
      iVar3 = (uVar2 & 0x1f) - 0x10;
      *(undefined2 *)(param_1 + 0xc) = (short)(*(short *)(param_2 + 0x34) * iVar3 >> 0xc);
      sVar1 = *(short *)(param_2 + 0x40);
      *(undefined2 *)(param_1 + 0xe) = 0x30;
      *(undefined4 *)(param_1 + 8) = 0;
      *(ushort *)(param_1 + 0x28) = *(ushort *)(param_1 + 0x28) | 2;
      uVar4 = (undefined2)(sVar1 * iVar3 >> 0xc);
    }

	// if you want to throw back long
    else {
      *(undefined2 *)(param_1 + 0xc) = (short)((int)*(short *)(param_2 + 0x34) * -0x78 >> 0xc);
      sVar1 = *(short *)(param_2 + 0x40);
      *(undefined2 *)(param_1 + 0xe) = 0x30;
      *(undefined4 *)(param_1 + 8) = 0;
      *(ushort *)(param_1 + 0x28) = *(ushort *)(param_1 + 0x28) | 2;
      uVar4 = (undefined2)((int)sVar1 * -0x78 >> 0xc);
    }
  }

  // if you want to throw forward
  else {
    *(undefined2 *)(param_1 + 0xc) = (short)((int)*(short *)(param_2 + 0x34) * 0xf >> 9);
    sVar1 = *(short *)(param_2 + 0x40);
    *(undefined2 *)(param_1 + 0xe) = 0x30;
    *(undefined4 *)(param_1 + 8) = 0;
    *(ushort *)(param_1 + 0x28) = *(ushort *)(param_1 + 0x28) | 2;
    uVar4 = (undefined2)((int)sVar1 * 0xf >> 9);
  }
  *(undefined2 *)(param_1 + 0x10) = uVar4;
  return 1;
}


// VehPickupItem_ShootNow
void FUN_8006540c(int param_1,undefined4 param_2,uint param_3)
// param1 is the address of the player/AI structure that fired the weapon
// param2 is weaponID
// param3 is "special" like throwing potions backward, or TNTs airborne
{
  undefined2 uVar1;
  short sVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  undefined4 uVar7;
  int iVar8;
  int iVar9;
  char *pcVar10;
  undefined2 *puVar11;
  undefined *puVar12;
  undefined4 local_48;
  undefined4 uVar13;
  int iVar14;
  int *piVar15;
  undefined4 *puVar16;
  undefined2 local_40;
  short local_3e;
  undefined2 local_3c;
  undefined2 local_38;
  short local_36;
  undefined2 local_34;
  undefined2 local_30;
  short local_2e;
  undefined2 local_2c;
  undefined2 local_28;
  short local_26;
  undefined2 local_24;

  // param1 is weapon ID
  switch(param_2)
  {

  // If your weapon is Turbo
  case 0:

	// small boost
    uVar7 = 0x80;

	// if 9 < number of wumpa
	// basically if wumpa < 10
    if ('\t' < *(char *)(param_1 + 0x30))
	{
	  // bigger boost
      uVar7 = 0x100;
    }

	// VehFire_Increment
	// 2.4 seconds reserve
    FUN_8005abfc(param_1,0x960,9,uVar7);

	break;

  // Shared code for Bomb and Missile
  case 2:

	// If there are more than 11 missiles on screen
    if (0xb < *(int *)(PTR_DAT_8008d2ac + 0x1ec0))
	{
	  // Quit, dont shoot more missiles
      return;
    }

	// set closest distance from missile-shooter to player, to max value,
	// so that we can loop through other players to find smaller distance
    iVar5 = 0x7fffffff;

	// number of missiles launched by player
    *(char *)(param_1 + 0x55c) = *(char *)(param_1 + 0x55c) + '\x01';

	// increment number of missiles that are on screen
    *(int *)(PTR_DAT_8008d2ac + 0x1ec0) = *(int *)(PTR_DAT_8008d2ac + 0x1ec0) + 1;

	// GAMEPAD_ShockFreq and GAMEPAD_ShockForce1
    FUN_80026440(param_1,8,0);
    FUN_800264c0(param_1,8,0x7f);

	// VehPickupItem_MissileGetTargetDriver
    iVar8 = FUN_80064f94(param_1);

	// if a player was not found to chase
    if (iVar8 == 0)
	{
      iVar14 = 0;
      puVar12 = PTR_DAT_8008d2ac;

	  // If you're not in Battle Mode
      if ((*(uint *)PTR_DAT_8008d2ac & 0x20) == 0)
	  {
        if (
			(
				// driver -> instance -> thread -> modelIndex
				(*(short *)(*(int *)(*(int *)(param_1 + 0x1c) + 0x6c) + 0x44) != 0x18) &&

				// if racer is not in first place
				((int)*(short *)(param_1 + 0x482) != 0)
			) &&

			// if time on clock is an odd number
			((*(uint *)(PTR_DAT_8008d2ac + 0x1d10) & 1) != 0)
		  )
		{
			// the missile chases the driver, one place ahead of the driver that fired the weapon
			iVar8 = *(int *)(PTR_DAT_8008d2ac + ((int)*(short *)(param_1 + 0x482) + -1) * 4 + 0x250c);
        }
      }

	  // if you are in battle
      else
	  {
		// loop through all players to find
		// the closest player that the missile can seek

		// for iVar14 = 0; iVar14 < 8; iVar14++
        do
		{
		  // get address of player structure
          iVar9 = *(int *)(puVar12 + 0x24ec);

          if (
				(
					(
						// if pointer is not nullptr
						(iVar9 != 0) &&

						// if player is not the missile shooter
						(iVar9 != param_1)
					) &&

					(
						(
							// if enemy player is being picked up by mask
							*(char *)(iVar9 + 0x376) != '\x05' &&

							(
								(
									// if two players are not on same team in battle mode
									*(int *)(iVar9 + 0x4e8) != *(int *)(param_1 + 0x4e8) &&

									// if player is not invisible
									(*(int *)(iVar9 + 0x28) == 0)
								)
							)
						)
					)
				) &&
				(
					// Get the X distance between two players
					iVar3 = *(int *)(iVar9 + 0x2d4) - *(int *)(param_1 + 0x2d4) >> 8,

					// Get the Z distance between two players
					iVar4 = *(int *)(iVar9 + 0x2dc) - *(int *)(param_1 + 0x2dc) >> 8,

					// Get the distance between two players
					iVar3 = iVar3 * iVar3 + iVar4 * iVar4,

					// if player is closer to missile shooter than previous closest player
					iVar3 < iVar5
				)
			  )
		  {
			// set smallest distance to current distance
            iVar5 = iVar3;

			// set closest player to this player
            iVar8 = iVar9;
          }

		  // increment loop iteration counter
          iVar14 = iVar14 + 1;

		  // increment pointer
          puVar12 = puVar12 + 4;
        } while (iVar14 < 8);

		// when this loop ends, iVar8 is the player that the missile is tracking

      }
    }

    if (
			// if weapon is 1 missile
			(*(char *)(param_1 + 0x36) == 2) ||
			(
				// not missile, use bomb model
				uVar7 = 0x3b,

				// if weapon is three missiles
				*(char *)(param_1 + 0x36) == 11
			)
		)
    {
	  // missile model
      uVar7 = 0x29;

      pcVar10 = "bombtracker1";

	  // 6 = "tracking" thread bucket
      uVar13 = 6;

      local_48 = 0;
    }
    else
	{
	  // s_bomb1_8008d634
	  // "bomb1"
      pcVar10 = s_bomb1_8008d634;

	  // driver -> instance -> thread
      local_48 = *(undefined4 *)(*(int *)(param_1 + 0x1c) + 0x6c);

	  // 0xd = "other" thread bucket
      uVar13 = 0xd;
    }

	// make thread for bomb or missile
	// 0x200 flag = MediumStackPool
    iVar5 = FUN_800309a4(uVar7,pcVar10,0x200,uVar13,FUN_800adb50,0x58,local_48);

	// driver instance
	iVar14 = *(int *)(param_1 + 0x1c);

	// copy driver position, rotation, and scale
	// into missile position, rotation, and scale
    uVar7 = *(undefined4 *)(iVar14 + 0x34);
    local_48 = *(undefined4 *)(iVar14 + 0x38);
    uVar13 = *(undefined4 *)(iVar14 + 0x3c);
    *(undefined4 *)(iVar5 + 0x30) = *(undefined4 *)(iVar14 + 0x30);
    *(undefined4 *)(iVar5 + 0x34) = uVar7;
    *(undefined4 *)(iVar5 + 0x38) = local_48;
    *(undefined4 *)(iVar5 + 0x3c) = uVar13;
    uVar7 = *(undefined4 *)(iVar14 + 0x44);
    local_48 = *(undefined4 *)(iVar14 + 0x48);
    uVar13 = *(undefined4 *)(iVar14 + 0x4c);
    *(undefined4 *)(iVar5 + 0x40) = *(undefined4 *)(iVar14 + 0x40);
    *(undefined4 *)(iVar5 + 0x44) = uVar7;
    *(undefined4 *)(iVar5 + 0x48) = local_48;
    *(undefined4 *)(iVar5 + 0x4c) = uVar13;

	// VehPhysForce_RotAxisAngle
	// rotation matrix of weapon,
	// face direction of driver facing, even with drift applied
    FUN_8005f89c(iVar5 + 0x30,param_1 + 0x360,(int)*(short *)(param_1 + 0x2ee));

	// PROC_DestroyTracker
	// when missile needs to be destroyed,
	// decrease number of missiles,
    *(undefined4 *)(*(int *)(iVar5 + 0x6c) + 0x24) = 0x80041dc0;

	// RB_Hazard_ThCollide_Missile, remove 2D target being drawn on them
    *(undefined4 *)(*(int *)(iVar5 + 0x6c) + 0x28) = 0x800ac42c;

	// instance -> thread -> object
    piVar15 = *(int **)(*(int *)(iVar5 + 0x6c) + 0x30);

    *(undefined2 *)((int)piVar15 + 0x16) = 0;

	// record pointer that shot the missile
    piVar15[1] = param_1;

    piVar15[0x12] = 0;
    piVar15[0x15] = 0;
    piVar15[9] = 0;

	// if weapon is one bowling bomb or three bowling bombs
    if ((*(char *)(param_1 + 0x36) == 1) || (*(char *)(param_1 + 0x36) == 10))
	{
	  // CTR_MatrixToRot
	  // iVar5+0x30 is weapon inst->matrix
      FUN_80021edc(&local_40,iVar5 + 0x30,0x11);

	  // 6*4 = 0x18, missile->dir[x]
	  *(short *)(piVar15 + 6) = local_3e;

	  // missile->dir[y]
      *(undefined2 *)((int)piVar15 + 0x1a) = local_40;

	  // tw->driverTarget
	  *piVar15 = iVar8;

	  // 7*4 = 0x1C, missile->dir[z]
      *(undefined2 *)(piVar15 + 7) = local_3c;

	  // d->instBombThrow
      *(int *)(param_1 + 0x10) = iVar5;

	  // PlaySound3D
      FUN_8002f0dc(0x47,iVar5);

	  // get flags of driver that shot bombs
	  uVar6 = *(uint *)(param_1 + 0x2c8);

	  uVar7 = 10;
    }

	// if weapon is missile
    else
	{
	  // RB_Hazard_ThCollide_Missile
      *(undefined4 *)(*(int *)(iVar5 + 0x6c) + 0x28) = 0x800ac42c;

	  // if missile does not have a target
	  if (iVar8 == 0)
	  {
		// set target to nullptr,
        *piVar15 = 0;
      }

	  // if missile has a target
      else
	  {
		// save address of player structure of target
        *piVar15 = iVar8;

		// if player is not aware a missile is chasing them
        if (*(int *)(iVar8 + 0x4a4) == 0)
		{
		  // RB_GetThread_ClosestTracker (missile or warpball)
          uVar7 = FUN_800b28c0(iVar8);

		  // Give the player a pointer to the missile chasing them
          *(undefined4 *)(iVar8 + 0x4a4) = uVar7;
        }
      }

	  // PlaySound3D
	  FUN_8002f0dc(0x4a,iVar5);

	  // get flags of the driver who shot the missile
      uVar6 = *(uint *)(param_1 + 0x2c8);

      uVar7 = 0xb;
    }

	// If driver shooting is human and not AI
    if ((uVar6 & 0x100000) == 0)
	{
	  // Make driver talk
      FUN_8002cbe8(uVar7,(int)(short)(&DAT_80086e84)[*(byte *)(param_1 + 0x4a)],0x10);
    }

    uVar1 = *(undefined2 *)(param_1 + 0x2ee);
    *(undefined2 *)((int)piVar15 + 0x12) = 0;
    *(undefined2 *)((int)piVar15 + 0x1e) = uVar1;

	// if weapon is one bowling bomb, or three bowling bombs
    if ((*(char *)(param_1 + 0x36) == '\x01') || (*(char *)(param_1 + 0x36) == '\n'))
	{
      *(short *)(piVar15 + 4) = (short)((int)*(short *)(iVar5 + 0x34) * 3 >> 7);
      *(short *)(piVar15 + 5) = (short)((int)*(short *)(iVar5 + 0x40) * 3 >> 7);

	  // if 9 < number of wumpa
	  // if wumpa is 10
      if ('\t' < *(char *)(param_1 + 0x30))
	  {
        *(ushort *)((int)piVar15 + 0x16) = *(ushort *)((int)piVar15 + 0x16) | 1;
      }

	  // If you press Down on D-Pad
      if (((*(uint *)(PTR_DAT_8008d2b0 + (uint)*(byte *)(param_1 + 0x4a) * 0x50 + 0x10) & 2) != 0)

		// or if you are pinstripe boss, I assume???
         || ((param_3 & 2) != 0))
	  {
		// roll bomb backwards
        *(ushort *)((int)piVar15 + 0x16) = *(ushort *)((int)piVar15 + 0x16) | 0x20;

		*(short *)(piVar15 + 4) =
             -(short)((((int)((uint)*(ushort *)(piVar15 + 4) << 0x10) >> 0x11) * 3) / 5);
        sVar2 = -(short)((((int)((uint)*(ushort *)(piVar15 + 5) << 0x10) >> 0x11) * 3) / 5);
        goto LAB_800659ec;
      }
    }

	// if weapon is not bowling bomb
    else
	{
	  // if wumpa < 10
      if (*(char *)(param_1 + 0x30) < '\n') {
        *(short *)(piVar15 + 4) = (short)((uint)((int)*(short *)(iVar5 + 0x34) * 5) >> 8);
        sVar2 = (short)((uint)((int)*(short *)(iVar5 + 0x40) * 5) >> 8);
      }

	  // if wumpa is 10
	  else
	  {
        *(short *)(piVar15 + 4) = (short)((int)*(short *)(iVar5 + 0x34) * 3 >> 7);
        sVar2 = *(short *)(iVar5 + 0x40);
        *(ushort *)((int)piVar15 + 0x16) = *(ushort *)((int)piVar15 + 0x16) | 1;
        sVar2 = (short)((int)sVar2 * 3 >> 7);
      }
LAB_800659ec:
      *(short *)(piVar15 + 5) = sVar2;
    }
    *(undefined2 *)(piVar15 + 8) = 0x3c;
    *(undefined2 *)((int)piVar15 + 0x22) = 0;

	// record the driver who shot the tracker
    piVar15[2] = *(int *)(param_1 + 0x1c);

    break;

  // if weapon ID is TNT / Nitro
  case 3:

	// If number of wumpa fruit is less than 10
	if (*(char *)(param_1 + 0x30) < '\n')
	{
      uVar7 = 0x27;

	  // DAT_8008d64c
	  // "tnt1"
      pcVar10 = &DAT_8008d64c;
    }

	// if you have 10 wumpa fruit
    else
	{
      uVar7 = 6;

	  // s_nitro1_8008d644
	  // "nitro1"
      pcVar10 = s_nitro1_8008d644;
    }

	// make TNT or Nitro thread
	// 0x300 flag = SmallStackPool
	// 4 = "mine" thread bucket
    iVar5 = FUN_800309a4(uVar7,pcVar10,0x300,4,&DAT_800acb60,0x2c,0);

	// get instance from driver
    iVar8 = *(int *)(param_1 + 0x1c);

	// copy rotation from driver, into weapon
    uVar7 = *(undefined4 *)(iVar8 + 0x34);
    local_48 = *(undefined4 *)(iVar8 + 0x38);
    uVar13 = *(undefined4 *)(iVar8 + 0x3c);
    *(undefined4 *)(iVar5 + 0x30) = *(undefined4 *)(iVar8 + 0x30);
    *(undefined4 *)(iVar5 + 0x34) = uVar7;
    *(undefined4 *)(iVar5 + 0x38) = local_48;
    *(undefined4 *)(iVar5 + 0x3c) = uVar13;

	// get position from player
    uVar7 = *(undefined4 *)(iVar8 + 0x44);
    local_48 = *(undefined4 *)(iVar8 + 0x48);
    uVar13 = *(undefined4 *)(iVar8 + 0x4c);

	// one more rotation variable
    *(undefined4 *)(iVar5 + 0x40) = *(undefined4 *)(iVar8 + 0x40);

	// set position of weapon
    *(undefined4 *)(iVar5 + 0x44) = uVar7;
    *(undefined4 *)(iVar5 + 0x48) = local_48;
    *(undefined4 *)(iVar5 + 0x4c) = uVar13;

	// set scale (x, y, z)
    *(undefined2 *)(iVar5 + 0x1c) = 0;
    *(undefined2 *)(iVar5 + 0x1e) = 0;
    *(undefined2 *)(iVar5 + 0x20) = 0;

	// set funcThDestroy to remove instance from instance pool
    *(undefined4 *)(*(int *)(iVar5 + 0x6c) + 0x24) = 0x80041dfc;

	// set funcThCollide function
    *(undefined4 *)(*(int *)(iVar5 + 0x6c) + 0x28) = 0x800ac4b8;

	// PlaySound3D
    FUN_8002f0dc(0x52,iVar5);

	// If this is human and not AI
    if ((*(uint *)(param_1 + 0x2c8) & 0x100000) == 0)
	{
	  // Make driver talk
      FUN_8002cbe8(0xf,(int)(short)(&DAT_80086e84)[*(byte *)(param_1 + 0x4a)],0x10);
    }

	// instance -> thread -> object (mw)
    puVar16 = *(undefined4 **)(*(int *)(iVar5 + 0x6c) + 0x30);

	// mw->instParent
    puVar16[1] = *(undefined4 *)(param_1 + 0x1c);

	// mw->velocity (x,y,z)
    *(undefined2 *)(puVar16 + 3) = 0;
    *(undefined2 *)((int)puVar16 + 0xe) = 0;
    *(undefined2 *)(puVar16 + 4) = 0;
    
	// mw->frameCount_DontHurtParent
	*(undefined2 *)(puVar16 + 9) = 10;
    
	*(undefined2 *)(puVar16 + 5) = 0;
    *(undefined2 *)((int)puVar16 + 0x26) = 0;
    *puVar16 = 0;
    puVar16[2] = 0;
    *(undefined2 *)(puVar16 + 10) = 0;

	// RB_MinePool_Add
	FUN_800ac13c(puVar16);

	// VehPickupItem_PotionThrow
    FUN_800652c8(puVar16,iVar5,param_3);

	// instancePos - Y
    local_40 = *(undefined2 *)(iVar5 + 0x44);
    local_3e = *(short *)(iVar5 + 0x48) + -400;
    local_3c = *(undefined2 *)(iVar5 + 0x4c);

	// instancePos + Y
    local_38 = *(undefined2 *)(iVar5 + 0x44);
    local_36 = *(short *)(iVar5 + 0x48) + 0x40;
    local_34 = *(undefined2 *)(iVar5 + 0x4c);

	// ground quadblock flags
    DAT_1f80012c = 0x1000;

	DAT_1f800130 = 0;
	
	// low-LOD collision (2 triangles)
    DAT_1f80012a = 1;

	// if numPlyrCurrGame is less than 3
    if ((byte)PTR_DAT_8008d2ac[0x1ca8] < 3) 
	{
	  // high-LOD collision (8 triangles)
      DAT_1f80012a = 3;
    }

    DAT_1f800134 = **(undefined4 **)(PTR_DAT_8008d2ac + 0x160);

	// COLL_SearchTree_FindQuadblock_Touching
    FUN_8001eb0c(&local_40,&local_38,&DAT_1f800108,0x40);

	if (DAT_1f80014a == 0) {
      puVar16[2] = 0;
    }
    else {
      DAT_1f800114 = *(ushort *)(*(int *)(iVar5 + 0x18) + 0x10) | 0x8000;

	  // RB_Hazard_CollLevInst
      FUN_800ad9ac(&DAT_1f800108,*(undefined4 *)(iVar5 + 0x6c));

	  // InstDef -> modelID
	  sVar2 = *(short *)(*(int *)(DAT_1f800150 + 0x1c) + 0x3c);

	  // fruit crate or weapon crate
	  if ((sVar2 == 7) || (sVar2 == 8)) 
	  {
		// save mineWeapon->crateInst as...
		// InstDef -> ptrInstance
        puVar16[2] = *(undefined4 *)(*(int *)(DAT_1f800150 + 0x1c) + 0x2c);
      }
      else
	  {
		// RB_GenericMine_ThDestroy
        FUN_800ad250(*(undefined4 *)(iVar5 + 0x6c),iVar5,puVar16);
      }
	  
	  // low-LOD collision (2 triangles)
      DAT_1f80012a = 0;

	  // COLL_SearchTree_FindQuadblock_Touching
      FUN_8001eb0c(&local_40,&local_38,&DAT_1f800108,0);
    }

	// RB_MakeInstanceReflective
    FUN_800abab0(&DAT_1f800108,iVar5);

	// if quadblock was not found
	if (DAT_1f800146 == 0)
	{
      *(undefined2 *)((int)puVar16 + 0x12) = *(undefined2 *)(iVar5 + 0x48);

	  local_40 = 0;
      local_3e = 0x1000;
      local_3c = 0;

	  sVar2 = *(short *)(param_1 + 0x39a);
      puVar11 = &local_40;
    }

	// if quadblock was found
    else {
      *(undefined2 *)((int)puVar16 + 0x12) = DAT_1f800124._2_2_;
      sVar2 = *(short *)(param_1 + 0x39a);
      puVar11 = &DAT_1f800178;
    }

	// VehPhysForce_RotAxisAngle
	// generate TNT/Nitro rotation matrix,
	// with driver rotation, and quadblock rotation
    FUN_8005f89c(iVar5 + 0x30,puVar11,(int)sVar2);

	// instTntSend
	*(int *)(param_1 + 0x20) = iVar5;
	
    *(uint *)(param_1 + 0x2c8) = *(uint *)(param_1 + 0x2c8) | 0x80000000;

	if (param_3 == 0)
	{
	  // RB_Follower_Init
      FUN_800b6f00(param_1,*(undefined4 *)(iVar5 + 0x6c));
    }

	break;

  // if Weapon ID is beaker
  case 4:

    // if you have less than 10 wumpa fruit
    if (*(char *)(param_1 + 0x30) < '\n')
	{
	  // "beaker1"
	  // 0x47 = green beaker

	  // 0x300 flag = SmallStackPool
	  // 4 = "mine" thread bucket
      iVar5 = FUN_800309a4(0x47,s_beaker1_8008d654,0x300,4,&FUN_800acb60,0x2c,0);

	  // if thread failed, then quit
      if (iVar5 == 0) {
        return;
      }

	  // instance -> thread -> object
      iVar8 = *(int *)(*(int *)(iVar5 + 0x6c) + 0x30);

	  // green beaker, not red
      *(undefined2 *)(iVar8 + 0x28) = 0;
    }

	// if you have 10 wumpa fruit
    else
	{
	  // "beaker1"
	  // 0x46 = red beaker

	  // 0x300 flag = SmallStackPool
	  // 4 = "mine" thread bucket
      iVar5 = FUN_800309a4(0x46,s_beaker1_8008d654,0x300,4,&FUN_800acb60,0x2c,0);

	  // instance->thread->object
      iVar8 = *(int *)(*(int *)(iVar5 + 0x6c) + 0x30);

	  // red beaker
      *(undefined2 *)(iVar8 + 0x28) = 1;
    }

	// get instance from player
    iVar14 = *(int *)(param_1 + 0x1c);

	// get player rotation
    uVar7 = *(undefined4 *)(iVar14 + 0x34);
    local_48 = *(undefined4 *)(iVar14 + 0x38);
    uVar13 = *(undefined4 *)(iVar14 + 0x3c);

	// set potion rotation to player rotation (4 of 5)
    *(undefined4 *)(iVar5 + 0x30) = *(undefined4 *)(iVar14 + 0x30);
    *(undefined4 *)(iVar5 + 0x34) = uVar7;
    *(undefined4 *)(iVar5 + 0x38) = local_48;
    *(undefined4 *)(iVar5 + 0x3c) = uVar13;

	// get player position
    uVar7 = *(undefined4 *)(iVar14 + 0x44);
    local_48 = *(undefined4 *)(iVar14 + 0x48);
    uVar13 = *(undefined4 *)(iVar14 + 0x4c);

	// rotation (last of 5)
    *(undefined4 *)(iVar5 + 0x40) = *(undefined4 *)(iVar14 + 0x40);

	// set potion position to player position
    *(undefined4 *)(iVar5 + 0x44) = uVar7;
    *(undefined4 *)(iVar5 + 0x48) = local_48;
    *(undefined4 *)(iVar5 + 0x4c) = uVar13;

	// beakerInst -> model -> header
    iVar14 = *(int *)(*(int *)(iVar5 + 0x18) + 0x14);

	// header -> flag: always face camera
    *(ushort *)(iVar14 + 0x16) = *(ushort *)(iVar14 + 0x16) | 2;

	// set funcThDestroy to remove instance from instance pool
    *(undefined4 *)(*(int *)(iVar5 + 0x6c) + 0x24) = 0x80041dfc;

	// set funcThCollide
	*(undefined4 *)(*(int *)(iVar5 + 0x6c) + 0x28) = 0x800ac4b8;

	// get instance of driver
	uVar7 = *(undefined4 *)(param_1 + 0x1c);

    *(undefined2 *)(iVar8 + 0x24) = 10;
    *(undefined2 *)(iVar8 + 0x14) = 0;
    *(undefined4 *)(iVar8 + 8) = 0;

	// save the driver who placed the weapon
    *(undefined4 *)(iVar8 + 4) = uVar7;

	// PlaySound3D
    FUN_8002f0dc(0x52,iVar5);

	// If this is human and not AI
    if ((*(uint *)(param_1 + 0x2c8) & 0x100000) == 0)
	{
	  // Make driver talk
      FUN_8002cbe8(0xf,(int)(short)(&DAT_80086e84)[*(byte *)(param_1 + 0x4a)],0x10);
    }

	// RB_MinePool_Add
    FUN_800ac13c(iVar8);

	// If you hold Up on D-Pad
    if ((*(uint *)(PTR_DAT_8008d2b0 + (uint)*(byte *)(param_1 + 0x4a) * 0x50 + 0x10) & 1) != 0)
	{
	  // Shoot potion forward
      param_3 = param_3 | 4;
    }

	// VehPickupItem_PotionThrow
    uVar6 = FUN_800652c8(iVar8,iVar5,param_3);

	// if mine is not "thrown", just "dropped"
    if ((uVar6 & 0xffff) == 0)
	{
	  // set scale to zero, thread will make it grow
      *(undefined2 *)(iVar5 + 0x1c) = 0;
      *(undefined2 *)(iVar5 + 0x1e) = 0;
      *(undefined2 *)(iVar5 + 0x20) = 0;

      *(undefined2 *)(iVar8 + 0xc) = 0;
      *(undefined2 *)(iVar8 + 0xe) = 0;
      *(undefined2 *)(iVar8 + 0x10) = 0;

	  // hit top
      local_30 = *(undefined2 *)(iVar5 + 0x44);
      local_2e = *(short *)(iVar5 + 0x48) + -400;
      local_2c = *(undefined2 *)(iVar5 + 0x4c);

	  // hit bottom
      local_28 = *(undefined2 *)(iVar5 + 0x44);
      local_26 = *(short *)(iVar5 + 0x48) + 0x40;
      local_24 = *(undefined2 *)(iVar5 + 0x4c);

	  // ground quadblock flags
      DAT_1f80012c = 0x1000;

	  DAT_1f800130 = 0;
	  
	  // low-LOD collision (2 triangles)
      DAT_1f80012a = 1;

	  // if numPlyrCurrGame is less than 3
      if ((byte)PTR_DAT_8008d2ac[0x1ca8] < 3) 
	  {
		// high-LOD collision (8 triangles)
        DAT_1f80012a = 3;
      }

      DAT_1f800134 = **(undefined4 **)(PTR_DAT_8008d2ac + 0x160);

	  // COLL_SearchTree_FindQuadblock_Touching
	  FUN_8001eb0c(&local_30,&local_28,&DAT_1f800108,0x40);

      if (DAT_1f80014a == 0) {
        *(undefined4 *)(iVar8 + 8) = 0;
      }
      else {
        DAT_1f800114 = *(ushort *)(*(int *)(iVar5 + 0x18) + 0x10);

		// RB_Hazard_CollLevInst
        FUN_800ad9ac(&DAT_1f800108,*(undefined4 *)(iVar5 + 0x6c));

		sVar2 = *(short *)(*(int *)(DAT_1f800150 + 0x1c) + 0x3c);
        if ((sVar2 == 7) || (sVar2 == 8)) {
          *(undefined4 *)(iVar8 + 8) = *(undefined4 *)(*(int *)(DAT_1f800150 + 0x1c) + 0x2c);
        }
        else
		{
		  // RB_GenericMine_ThDestroy
          FUN_800ad250(*(undefined4 *)(iVar5 + 0x6c),iVar5,iVar8);
        }
		
		// low-LOD collision (2 triangles)
        DAT_1f80012a = 0;

		// COLL_SearchTree_FindQuadblock_Touching
        FUN_8001eb0c(&local_30,&local_28,&DAT_1f800108,0);
      }

	  // RB_MakeInstanceReflective
      FUN_800abab0(&DAT_1f800108,iVar5);

	  // if no collision,
	  if (DAT_1f800146 == 0)
	  {
        *(undefined2 *)(iVar8 + 0x12) = *(undefined2 *)(iVar5 + 0x48);

		// rotate on Y axis
		local_30 = 0;
        local_2e = 0x1000;
        local_2c = 0;

		// driver rotation
		sVar2 = *(short *)(param_1 + 0x39a);

		puVar11 = &local_30;
      }

	  else
	  {
        *(undefined2 *)(iVar8 + 0x12) = DAT_1f800124._2_2_;

		// driver rotation
		sVar2 = *(short *)(param_1 + 0x39a);

		// rotate on slanted axis from quadblock
		puVar11 = &DAT_1f800178;
      }

	  // VehPhysForce_RotAxisAngle
	  // rotation matrix of beaker, given driver rotation and quadblock
	  FUN_8005f89c(iVar5 + 0x30,puVar11,(int)sVar2);

	  // RB_Follower_Init
      FUN_800b6f00(param_1,*(undefined4 *)(iVar5 + 0x6c));

      *(uint *)(param_1 + 0x2c8) = *(uint *)(param_1 + 0x2c8) | 0x80000000;
    }
    break;

  // if weapon ID is Shield Bubble
  case 6:

	// 0x200 flag = MediumStackPool
	// 0xd = "other" thread bucket
	// 0x5a = shieldDark (darkens edges of 2nd shield instance)
	// 0x18 = sizeof(struct Shield)
	// 800b0454 - RB_ShieldDark_ThTick_Grow
    iVar5 = FUN_800309a4(0x5a,"shielddark",0x200,0xd,&DAT_800b0454,0x18,

										// driver -> instance -> thread
                         *(undefined4 *)(*(int *)(param_1 + 0x1c) + 0x6c));

	// set scale (x, y, z)
    *(undefined2 *)(iVar5 + 0x1c) = 0x700;
    *(undefined2 *)(iVar5 + 0x1e) = 0x700;
    *(undefined2 *)(iVar5 + 0x20) = 0x700;

	// set funcThDestroy to remove instance from instance pool
    *(undefined4 *)(*(int *)(iVar5 + 0x6c) + 0x24) = 0x80041dfc;

	// OtherFX_Play Activate Shield sound
    FUN_80028468(0x57,1);

	// get object created with thread
    puVar16 = *(undefined4 **)(*(int *)(iVar5 + 0x6c) + 0x30);

	// if number of wumpa is less than 10
    if (*(char *)(param_1 + 0x30) < '\n')
	{
	  // Green (0x5e) shield model pointer (in instance)
      uVar7 = *(undefined4 *)(PTR_DAT_8008d2ac + 0x22d8);
    }

	// if number of wumpa is 10
	else
	{
	  // Blue (0x56) shield model pointer (in instance)
      uVar7 = *(undefined4 *)(PTR_DAT_8008d2ac + 0x22b8);
    }

	// s_shield_8008d63c
	// "shield"

	// INSTANCE_Birth3D -- ptrModel, name, thread
	uVar7 = FUN_8003086c(uVar7,s_shield_8008d63c);

	// give instance to object
	puVar16[2] = uVar7;

    puVar12 = PTR_DAT_8008d2ac;

	// scale (x, y, z)
    *(undefined2 *)(puVar16[2] + 0x1c) = 0x700;
    *(undefined2 *)(puVar16[2] + 0x1e) = 0x700;
    *(undefined2 *)(puVar16[2] + 0x20) = 0x700;

	// INSTANCE_Birth3D -- ptrModel, name, thread
    iVar8 = FUN_8003086c(*(undefined4 *)(puVar12 + 0x22d4),"highlight",*(undefined4 *)(iVar5 + 0x6c));

	// give instance to object
	puVar16[3] = iVar8;

	// scale (x, y, z)
    *(undefined2 *)(iVar8 + 0x1c) = 0x700;
    *(undefined2 *)(puVar16[3] + 0x1e) = 0x700;
    *(undefined2 *)(puVar16[3] + 0x20) = 0x700;

    *(undefined2 *)((int)puVar16 + 6) = 0;
    *(undefined2 *)(puVar16 + 4) = 0;
    *(undefined2 *)((int)puVar16 + 0x12) = 0xc00;
    *(undefined2 *)(puVar16 + 5) = 0;
    *(undefined2 *)((int)puVar16 + 0x16) = 0;

	// if wumpa < 10
    if (*(char *)(param_1 + 0x30) < '\n')
	{
	  // 12 seconds,
	  // 12 * 30 * 32
      *(undefined2 *)(puVar16 + 1) = 0x2d00;
    }

	// if weapon is 10
    else
	{
	  // use a flag to disable the countdown timer (in 231)
      *(ushort *)((int)puVar16 + 6) = *(ushort *)((int)puVar16 + 6) | 4;
    }

    *(undefined2 *)(iVar5 + 0x22) = 0x400;
    *puVar16 = 0;
    *(int *)(param_1 + 0x14) = iVar5;
    break;

  // if weapon ID is mask
  case 7:
    // VehPickupItem_MaskUseWeapon
    FUN_80064c38(param_1,1);
    break;

  // if weapon ID is clock
  case 8:
    *(char *)(param_1 + 0x558) = *(char *)(param_1 + 0x558) + '\x01';

	// OtherFX_Play
    FUN_80028468(0x44);

	// loop iteration counter
    iVar5 = 0;

	// If this is human and not AI
    if ((*(uint *)(param_1 + 0x2c8) & 0x100000) == 0)
	{
	  // Make driver talk
      FUN_8002cbe8(0xe,(int)(short)(&DAT_80086e84)[*(byte *)(param_1 + 0x4a)],0x10);
      iVar5 = 0;
    }

	// for iVar5 = 0; iVar5 < 8; iVar5++
	do
	{
	  // pointer incrementer, for each player structure
      iVar14 = iVar5 * 4;

	  // driver->clockFlash
      *(undefined *)(*(int *)(PTR_DAT_8008d2ac + iVar14 + 0x24ec) + 0x367) = 4;

	  // get pointer to each player structure
      iVar8 = *(int *)(PTR_DAT_8008d2ac + iVar14 + 0x24ec);

	  // if pointer is not nullptr
      if (iVar8 != 0)
	  {
		// do not put weapon effect on the player that used it
        if (iVar8 == param_1) {
          *(undefined *)(param_1 + 0x45) = 0x1e;
        }
        else
		{
		  // RB_Hazard_HurtDriver (spinout)
          iVar8 = FUN_800ac1b0(iVar8,1,0,0);

          if (iVar8 != 0)
		  {
			// if wumpa < 10
            if (*(char *)(param_1 + 0x30) < '\n')
			{
			  // little time
              *(undefined2 *)(*(int *)(PTR_DAT_8008d2ac + iVar14 + 0x24ec) + 0xc) = 0x1e00;
            }

			// if wumpa is 10
            else
			{
			  // long time
              *(undefined2 *)(*(int *)(PTR_DAT_8008d2ac + iVar14 + 0x24ec) + 0xc) = 0x2d00;
            }
          }
        }
      }

	  // increment loop counter
      iVar5 = iVar5 + 1;
    } while (iVar5 < 8);
    break;

  // if weapon ID is warp ball
  case 9:

    // GAMEPAD_ShockFreq and GAMEPAD_ShockForce1
    FUN_80026440(param_1,8,0);
    FUN_800264c0(param_1,8,0x7f);

	// 0x200 flag = MediumStackPool
	// 6 = "tracking" thread bucket
    iVar5 = FUN_800309a4(0x36,"warpball",0x200,6,&DAT_800aef9c,0x58,0);

	// copy position from player to warpball
    *(int *)(iVar5 + 0x44) = *(int *)(param_1 + 0x2d4) >> 8;
    *(int *)(iVar5 + 0x48) = *(int *)(param_1 + 0x2d8) >> 8;
    iVar8 = *(int *)(param_1 + 0x2dc);

	// set scale
    *(undefined4 *)(iVar5 + 0x30) = 0x1000;
    *(undefined4 *)(iVar5 + 0x38) = 0x1000;
    *(undefined2 *)(iVar5 + 0x40) = 0x1000;

	// one more position variable
    *(int *)(iVar5 + 0x4c) = iVar8 >> 8;

	// rotation variables
    *(undefined4 *)(iVar5 + 0x34) = 0;
    *(undefined4 *)(iVar5 + 0x3c) = 0;

	// set funcThDestroy to remove instance from instance pool
    *(undefined4 *)(*(int *)(iVar5 + 0x6c) + 0x24) = 0x80041dfc;

	// PlaySound3D
    FUN_8002f0dc(0x4d,iVar5);

	// If this is human and not AI
    if ((*(uint *)(param_1 + 0x2c8) & 0x100000) == 0)
	{
	  // Make driver talk
      FUN_8002cbe8(0xc,(int)(short)(&DAT_80086e84)[*(byte *)(param_1 + 0x4a)],0x10);
    }

	// warpball instance -> thread -> object
    piVar15 = *(int **)(*(int *)(iVar5 + 0x6c) + 0x30);

    piVar15[1] = param_1;

	// set animation to zero
    *(undefined2 *)((int)piVar15 + 0x52) = 0;

    piVar15[0x10] = 0;

	// by default, chase nobody
    iVar8 = 0;

	// If player is not in first place
    if ((int)*(short *)(param_1 + 0x482) != 0)
	{
	  // start chasing the player in front of you
      iVar8 = *(int *)(PTR_DAT_8008d2ac + ((int)*(short *)(param_1 + 0x482) + -1) * 4 + 0x250c);
    }

	// store target driver in warpball object
    *piVar15 = iVar8;

	// RB_Warpball_SeekDriver
    FUN_800aece0(piVar15,(uint)*(byte *)(param_1 + 0x495),param_1);

    iVar8 = *(int *)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0x14c);
    *(byte *)((int)piVar15 + 0x45) = *(byte *)(piVar15 + 0x11);

	// if wumpa < 10
    *(undefined2 *)((int)piVar15 + 0x16) = 0;

	// respawnPointIndex
    piVar15[0xb] = 0;
	
	// ptrNodeCurr = lev->respawnPoint[pathIndexStart]
    piVar15[0xf] = iVar8 + (uint)*(byte *)(piVar15 + 0x11) * 0xc;

	// if 9 < wumpa
	// if wumpa is 10
	if ('\t' < *(char *)(param_1 + 0x30))
	{
	  // use flag to remember that 10 wumpa were used
      *(ushort *)((int)piVar15 + 0x16) = *(ushort *)((int)piVar15 + 0x16) | 1;
    }

	*(ushort *)((int)piVar15 + 0x16) = *(ushort *)((int)piVar15 + 0x16) | 8;
	
	// one flag for each driver
    piVar15[0xd] = 1 << ((uint)*(byte *)(param_1 + 0x4a) & 0x1f);

	// if driver is in first
	if (*(short *)(param_1 + 0x482) == 0)
	{
	  // warp ball will not chase any driver
      *piVar15 = 0;
    }

	// if driver is not in first
    else
	{
	  // Find a target driver to chase

	  // piVar15 is WarpBall object,
	  // iVar5 is WarpBall instance
	  
	  // RB_Warpball_GetDriverTarget
      iVar5 = FUN_800ae7dc(piVar15,iVar5);

	  // store pointer to driver that will be chased
	  *piVar15 = iVar5;
    }

	// if driver is in first (again?)
    if (*(short *)(param_1 + 0x482) == 0)
	{
	  // warp ball will not chase any driver
      *piVar15 = 0;
    }

	// if driver is being chased
    if (*piVar15 != 0)
	{
	  // RB_Warpball_SetTargetDriver
      FUN_800aeaac(piVar15);
    }

    if ((*(ushort *)((int)piVar15 + 0x16) & 4) == 0)
	{
	  // RB_Warpball_Start
      FUN_800ae778(piVar15);
    }
    else {
      *(ushort *)((int)piVar15 + 0x16) = *(ushort *)((int)piVar15 + 0x16) & 0xfff7;
    }

	// RB_Warpball_NewPathNode
    iVar5 = FUN_800ae668(piVar15[0xf],*piVar15);
    piVar15[0x10] = iVar5;

	// clear audio pointer
    piVar15[9] = 0;

	// get rotation of driver inst
    sVar2 = *(short *)(*(int *)(param_1 + 0x1c) + 0x34);

	// velY
    *(undefined2 *)((int)piVar15 + 0x12) = 0;

	// velX
	*(short *)(piVar15 + 4) = (short)((uint)((int)sVar2 * 7) >> 8);

	// get rotation of driver inst
	sVar2 = *(short *)(*(int *)(param_1 + 0x1c) + 0x40);

	// frameCount_DontHurtParent (useless)
	*(undefined2 *)(piVar15 + 8) = 10;

	// velZ
	*(short *)(piVar15 + 5) = (short)((uint)((int)sVar2 * 7) >> 8);

	// gGT
	puVar12 = PTR_DAT_8008d2ac;

	// rotation
	*(undefined2 *)((int)piVar15 + 0x1a) = *(undefined2 *)(param_1 + 0x39a);

	// instance who shot the warpball
	piVar15[2] = *(int *)(param_1 + 0x1c);

	// Create instance in particle pool
    iVar5 = FUN_80040308(0,*(undefined4 *)(puVar12 + 0x2114),&DAT_80089c04);

	// offset 0xC
    piVar15[3] = iVar5;

    if (iVar5 != 0) {
      *(undefined *)(iVar5 + 0x18) = 0xfa;
    }
    break;

  // if weapon ID is Invisibility
  case 0xc:

	// if not already invisible
    if (*(int *)(param_1 + 0x28) == 0)
	{
	  // backup instance flags before invisible
      *(undefined4 *)(param_1 + 0x2c) = *(undefined4 *)(*(int *)(param_1 + 0x1c) + 0x28);

	  // instance flags
	  *(uint *)(*(int *)(param_1 + 0x1c) + 0x28) =
           *(uint *)(*(int *)(param_1 + 0x1c) + 0x28) & 0xfff8ffff;

	  // instance flags
      *(uint *)(*(int *)(param_1 + 0x1c) + 0x28) =
           *(uint *)(*(int *)(param_1 + 0x1c) + 0x28) | 0x60000;

	  // OtherFX_Play
      FUN_80028468(0x61,1);
    }

	// if wumpa is 10
    uVar7 = 0x1e00;

	// if 9 < wumpa
	// if wumpa is 10
    if ('\t' < *(char *)(param_1 + 0x30)) {
      uVar7 = 0x2d00;
    }

	// set invisible timer
    *(undefined4 *)(param_1 + 0x28) = uVar7;

    break;

  // if weapn ID is Super Engine
  case 0xd:

	// if wumpa is less than 10
    if (*(char *)(param_1 + 0x30) < '\n')
	{
	  // Set super engine powerup timer
      *(undefined2 *)(param_1 + 0x38) = 0x1e00;
    }

	// if wumpa is 10
    else
	{
	  // Set super engine powerup timer
      *(undefined2 *)(param_1 + 0x38) = 0x2d00;
    }
  }
  return;
}


// VehPickupItem_ShootOnCirclePress
void FUN_800666e4(int param_1)

{
  uint uVar1;

  if (*(byte *)(param_1 + 0x4ff) != 0)
  {
	// VehPickState_NewState
    FUN_80064568(param_1,(uint)*(byte *)(param_1 + 0x4ff),*(undefined4 *)(param_1 + 0x500),
                 (uint)*(byte *)(param_1 + 0x504));
  }

  // If you want to fire a weapon
  if ((*(uint *)(param_1 + 0x2c8) & 0x8000) != 0)
  {
	// Remove the request to fire a weapon, since we will fire it now
    *(uint *)(param_1 + 0x2c8) = *(uint *)(param_1 + 0x2c8) & 0xffff7fff;

	// Set weapon to one bomb
    uVar1 = 1;

    if (
			// If this weapon is not 3 bombs
			(*(char *)(param_1 + 0x36) != '\n') &&

			(
				// Set weapon to missile
				uVar1 = 2,

				// if this weapon is not 3 missiles
				*(char *)(param_1 + 0x36) != '\v'
			)
		)
	{
	  // Set to the original weapon the player has
      uVar1 = (uint)*(byte *)(param_1 + 0x36);
    }

	// If weapon is bomb, change to missile,
	// this is because bomb and missile share code
    if (uVar1 == 1) {
      uVar1 = 2;
    }

	// VehPickupItem_ShootNow (player)
    FUN_8006540c(param_1,uVar1,0);
  }
  return;
}



// WARNING: Removing unreachable block (ram,0x80066894)
// WARNING: Globals starting with '_' overlap smaller symbols at the same address

// VehStuckProc_MaskGrab_FindDestPos (destination position)
void FUN_8006677c(int param_1,short *param_2)

{
  byte bVar1;
  short sVar2;
  undefined *puVar3;
  long lVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  short *psVar8;
  short *psVar9;

  puVar3 = PTR_DAT_8008d2ac;

  if (
		(
			// if no respawn positions are found in the LEV file
			(*(int *)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0x148) < 1) ||
			(*(int *)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0x14c) == 0)
		) ||

		// quadblock checkpointIndex (0x3e)
		(*(char *)(param_2 + 0x1f) == -1))
  {
	// respawn driver on the last "valid" quadblock they touched

	// posX =
    *(int *)(param_1 + 0x2d4) =
	
		  // lev->mesh_info->ptrVertexArray[(Quadblock*)param_2->index[0]].pos[0]
         ((int)*(short *)((int)*param_2 * 0x10 +
                         *(int *)(**(int **)(PTR_DAT_8008d2ac + 0x160) + 0x10)) +
						 
		  // lev->mesh_info->ptrVertexArray[(Quadblock*)param_2->index[3]].pos[0]
         (int)*(short *)((int)param_2[3] * 0x10 +
                        *(int *)(**(int **)(PTR_DAT_8008d2ac + 0x160) + 0x10))) 
			
		  // midpoint between
		  * 0x80;
    
	// lev->mesh_info->ptrVertexArray
	iVar6 = *(int *)(**(int **)(puVar3 + 0x160) + 0x10);
	
	// posY = 
    *(int *)(param_1 + 0x2d8) =
	
		 // ptrVertexArray[(Quadblock*)param_2->index[0]].pos[1]
         ((int)*(short *)((int)*param_2 * 0x10 + iVar6 + 2) +
		 
		   // ptrVertexArray[(Quadblock*)param_2->index[3]].pos[1]
          (int)*(short *)((int)param_2[3] * 0x10 + iVar6 + 2) + 0x80) 
		  
		  // midpoint between
		  * 0x80;
		  
    iVar6 = *(int *)(**(int **)(puVar3 + 0x160) + 0x10);
	
	// posZ
    *(int *)(param_1 + 0x2dc) =
	
		  
		   // ptrVertexArray[(Quadblock*)param_2->index[0]].pos[2]
         ((int)*(short *)((int)*param_2 * 0x10 + iVar6 + 4) +
		 
		   // ptrVertexArray[(Quadblock*)param_2->index[3]].pos[2]
         (int)*(short *)((int)param_2[3] * 0x10 + iVar6 + 4)) 
		 
		 // midpiont between
		 * 0x80;
  }

  // if checkpointIndex is not -1,
  // and respawn points exist on LEV
  else
  {
	// search BSP for valid quadblock near the point, and spawn there

	// thread offset 0x42?

	// a bunch of driver -> instance -> thread -> xxx
	DAT_1f80010e = *(undefined2 *)(*(int *)(*(int *)(param_1 + 0x1c) + 0x6c) + 0x42);
    _DAT_1f800110 = *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x1c) + 0x6c) + 0x38);
    DAT_1f80011c._2_2_ = *(undefined2 *)(*(int *)(*(int *)(param_1 + 0x1c) + 0x6c) + 0x42);
    DAT_1f800120 = *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x1c) + 0x6c) + 0x38);

	DAT_1f800134 = **(int **)(PTR_DAT_8008d2ac + 0x160);
    DAT_1f800130 = 0x4010;

	// ground quadblock flags
    DAT_1f80012c = 0x1000;

	// quadblock checkpointIndex (0x3e)
	bVar1 = *(byte *)(param_2 + 0x1f);
	
	// lev -> respawn_points
    iVar6 = *(int *)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0x14c);
	
    *(undefined4 *)(param_1 + 0x490) = 0;
	
	// respawn data
    psVar8 = (short *)(iVar6 + (uint)bVar1 * 0xc);
	
    do {
      do {
		  
		// next respawn data after the one being spawned on
        psVar9 = (short *)(*(int *)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0x14c) +
                          (uint)*(byte *)(psVar8 + 4) * 0xc);
		
		// posX
        *(int *)(param_1 + 0x2d4) = (int)*psVar8 << 8;
		
		// posY (+ offset for mask in air)
        *(int *)(param_1 + 0x2d8) = ((int)psVar8[1] + 0x80) * 0x100;
        
		// posZ
		sVar2 = psVar8[2];
        
		// rotX = 0 (not on slant)
		*(undefined2 *)(param_1 + 0x2ec) = 0;
        
		// posZ
		*(int *)(param_1 + 0x2dc) = (int)sVar2 << 8;
        
		// get rotY by comparing positions of cur respawn and next respawn
		lVar4 = ratan2((int)*psVar9 - (int)*psVar8,(int)psVar9[2] - (int)psVar8[2]);
        *(undefined2 *)(param_1 + 0x2ee) = (short)lVar4;
		
		// rotZ = 0 (not on slant)
        *(undefined2 *)(param_1 + 0x2f0) = 0;
        
		// build hitbox for driver
		DAT_1f800118._0_2_ = (short)((uint)*(undefined4 *)(param_1 + 0x2d4) >> 8);
        DAT_1f800118._2_2_ = (ushort)((uint)*(undefined4 *)(param_1 + 0x2d8) >> 8);
        DAT_1f80011c._0_2_ = (ushort)((uint)*(undefined4 *)(param_1 + 0x2dc) >> 8);
        DAT_1f800108 = (short)((uint)*(undefined4 *)(param_1 + 0x2d4) >> 8);
        DAT_1f80010a = (short)((uint)*(undefined4 *)(param_1 + 0x2d8) >> 8) - 0x100;
        
		// low-LOD collision (2 triangles)
		DAT_1f80012a = 0;
		
        DAT_1f80010c = (ushort)((uint)*(undefined4 *)(param_1 + 0x2dc) >> 8);

		// if numPlyrCurrGame is less than 3
        if ((byte)PTR_DAT_8008d2ac[0x1ca8] < 3) 
		{
		  // high-LOD collision (8 triangles)
          DAT_1f80012a = 2;
        }

        DAT_1f800146 = 0;
        DAT_1f800144 = 0;
        DAT_1f80018c = 0x1000;
        DAT_1f8002ac = 0;
        DAT_1f800138 = (short)DAT_1f800118;
        if (DAT_1f800108 < (short)DAT_1f800118) {
          DAT_1f800138 = DAT_1f800108;
        }
        DAT_1f80013a = DAT_1f800118._2_2_;
        if ((int)((uint)DAT_1f80010a << 0x10) < (int)((uint)DAT_1f800118._2_2_ << 0x10)) {
          DAT_1f80013a = DAT_1f80010a;
        }
        DAT_1f80013c = (ushort)DAT_1f80011c;
        if ((int)((uint)DAT_1f80010c << 0x10) < (int)((uint)(ushort)DAT_1f80011c << 0x10)) {
          DAT_1f80013c = DAT_1f80010c;
        }
        DAT_1f80013e = (short)DAT_1f800118;
        if ((short)DAT_1f800118 < DAT_1f800108) {
          DAT_1f80013e = DAT_1f800108;
        }
        DAT_1f800140 = DAT_1f800118._2_2_;
        if ((int)((uint)DAT_1f800118._2_2_ << 0x10) < (int)((uint)DAT_1f80010a << 0x10)) {
          DAT_1f800140 = DAT_1f80010a;
        }
        DAT_1f800142 = (ushort)DAT_1f80011c;
        if ((int)((uint)(ushort)DAT_1f80011c << 0x10) < (int)((uint)DAT_1f80010c << 0x10)) {
          DAT_1f800142 = DAT_1f80010c;
        }
        DAT_1f800124._0_2_ = DAT_1f800108;
        DAT_1f800124._2_2_ = DAT_1f80010a;
        DAT_1f800128 = DAT_1f80010c;

		// COLL_SearchTree_FindX, callback for touching quadblocks,
		// COLL_PerBspLeaf_CheckQuadblocks_Touching
        FUN_8001ebec(*(undefined4 *)(DAT_1f800134 + 0x18),&DAT_1f800138,FUN_8001f5f0,&DAT_1f800108);

		// cur respawn = next respawn
        psVar8 = psVar9;
		
		// loop again if no quadblock is found under the driver
      } while ((DAT_1f800146 == 0) || ((DAT_1f8002ac & 0x4000) != 0));

	  // pointer to first Player thread
      iVar6 = *(int *)(PTR_DAT_8008d2ac + 0x1b2c);

	  // if player does not exist, quit
      if (iVar6 == 0) break;

	  // loop through all players
      do
	  {
		// player object
        iVar7 = *(int *)(iVar6 + 0x30);

		// dont check for collision against yourself
        if (iVar7 != param_1) 
		{
		  // compare X
          iVar5 = *(int *)(param_1 + 0x2d4) - *(int *)(iVar7 + 0x2d4);
          
		  // absolute value
		  if (iVar5 < 0) {
            iVar5 = -iVar5;
          }
		  
		  // if distance too close, go to next respawn point
          if (iVar5 < 0x2000) break;
		  
		  // compare Z
          iVar7 = *(int *)(param_1 + 0x2dc) - *(int *)(iVar7 + 0x2dc);
		  
		  // absolute value
          if (iVar7 < 0) {
            iVar7 = -iVar7;
          }
		  
		  // if distance too close, go to next respawn point
          if (iVar7 < 0x2000) break;
        }

		// next player
        iVar6 = *(int *)(iVar6 + 0x10);

	  // if == 0, player does not spawn on top of another,
	  // else, check next driver
      } while (iVar6 != 0);
	 
	// if == 0, player does not spawn on top of another,
	// else, spawn player on the next respawn point
    } while (iVar6 != 0);
  }

  // CameraDC flag
  *(uint *)(PTR_DAT_8008d2ac + (uint)*(byte *)(param_1 + 0x4a) * 0xdc + 0x1508) =
       *(uint *)(PTR_DAT_8008d2ac + (uint)*(byte *)(param_1 + 0x4a) * 0xdc + 0x1508) | 1;
  return;
}


// VehStuckProc_MaskGrab_Particles
void FUN_80066cb0(int param_1)

{
  int iVar1;
  int iVar2;

  iVar2 = 10;
  do
  {
	// Create instance in particle pool
    iVar1 = FUN_80040308(0,*(undefined4 *)(PTR_DAT_8008d2ac + 0x2114),&DAT_80089d90);

	iVar2 = iVar2 + -1;
    if (iVar1 == 0) {
      return;
    }

	// position variables
    *(int *)(iVar1 + 0x24) = *(int *)(iVar1 + 0x24) + *(int *)(param_1 + 0x2d4);
    *(int *)(iVar1 + 0x2c) = *(int *)(iVar1 + 0x2c) + *(int *)(param_1 + 0x2d8);
    *(int *)(iVar1 + 0x34) = *(int *)(iVar1 + 0x34) + *(int *)(param_1 + 0x2dc);

  } while (iVar2 != 0);
  return;
}


// VehStuckProc_MaskGrab_Update
// param1 = thread, param2 = driver
void FUN_80066d4c(undefined4 param_1,int param_2)

{
  int iVar1;

  // NoInput timer = NoInput timer - elapsed milliseconds per frame, ~32
  iVar1 = (uint)*(ushort *)(param_2 + 0x400) - (uint)*(ushort *)(PTR_DAT_8008d2ac + 0x1d04);
  *(undefined2 *)(param_2 + 0x400) = (short)iVar1;

  // if negative
  if (iVar1 * 0x10000 < 0)
  {
	// set to zero
    *(undefined2 *)(param_2 + 0x400) = 0;
  }

  // when input is allowed,
  // which is when driver is spawned back over track
  if (*(short *)(param_2 + 0x400) == 0)
  {
	// maskObj
    iVar1 = *(int *)(param_2 + 0x580);
    
	if (iVar1 != 0) 
	{
	  // mask rotY
      *(ushort *)(iVar1 + 4) = *(ushort *)(iVar1 + 4) & 0xfffe;
      
	  // scale = 100%
	  *(undefined2 *)(*(int *)(param_2 + 0x580) + 0x12) = 0x1000;
    }

	// CameraDC flag
    *(uint *)(PTR_DAT_8008d2ac + (uint)*(byte *)(param_2 + 0x4a) * 0xdc + 0x1508) =
         *(uint *)(PTR_DAT_8008d2ac + (uint)*(byte *)(param_2 + 0x4a) * 0xdc + 0x1508) | 8;

	// VehStuckProc_MaskGrab_FindDestPos
	// driver, and quadblock (last valid)
    FUN_8006677c(param_2,*(undefined4 *)(param_2 + 0x354));

	// VehBirth_TeleportSelf (back onto track)
    FUN_80057c8c(param_2,0,0x80);

	// VehStuckProc_RevEngine_Init
    FUN_80067f4c(param_1,param_2);
  }
  return;
}

// VehStuckProc_MaskGrab_PhysLinear
// param1 = thread, param2 = driver
void FUN_80066e3c(undefined4 param_1,int param_2)

{
  // VehPhysProc_Driving_PhysLinear
  FUN_8006181c(param_1, param_2);

  // reset base speed
  *(undefined2 *)(param_2 + 0x39e) = 0;

  //reset Jump buffer Timer
  *(undefined2 *)(param_2 + 0x3f0) = 0;

  // reset base speed (again?)
  *(undefined2 *)(param_2 + 0x39e) = 0;

  // reset "basic" speed
  *(undefined2 *)(param_2 + 0x39c) = 0;

  // reset turning state
  *(undefined *)(param_2 + 0x4b) = 0;

  *(uint *)(param_2 + 0x2c8) = *(uint *)(param_2 + 0x2c8) & 0xfffdffdb | 8;
  return;
}

// VehStuckProc_MaskGrab_Animate
// param1 = thread, param2 = driver
void FUN_80066e8c(int param_1,int param_2)
{
  char cVar1;
  short sVar2;
  ushort uVar3;
  undefined2 uVar4;
  undefined4 uVar5;
  int iVar6;

  // get instance from thread
  iVar6 = *(int *)(param_1 + 0x34);

  // if driver touched ground before mask grab
  if (*(char *)(param_2 + 0x58d) == '\0') {

	// MatrixArr and MatrixIndex
    *(undefined *)(param_2 + 0x4c) = 0;
    *(undefined *)(param_2 + 0x4d) = 0;

	// set animation
    *(undefined *)(iVar6 + 0x52) = 0;

	// Instance_GetNumAnimFrames(instance, anim#0)
    uVar5 = FUN_8005b0f4(iVar6,0);

	// VehFrameInst_GetStartFrame(midpoint, numFrames)
    uVar4 = FUN_8005b0c4(0,uVar5);

    *(undefined2 *)(iVar6 + 0x54) = uVar4;
    *(undefined2 *)(param_2 + 0x368) = *(undefined2 *)(param_2 + 0x584);
    *(undefined2 *)(param_2 + 0x36a) = *(undefined2 *)(param_2 + 0x586);
    *(undefined2 *)(param_2 + 0x36c) = *(undefined2 *)(param_2 + 0x588);
  }

  // if driver did not touch ground (and is falling)
  else
  {
    if (
			// if whistle sound has not played
			(*(char *)(param_2 + 0x58f) == '\0') &&

			(*(short *)(param_2 + 0x400) < 0x3c0)
		)
	{
	  // OtherFX_Play "falling" sound, like a whistle
      FUN_80028468(0x55,1);

	  // whistle sound has played
      *(undefined *)(param_2 + 0x58f) = 1;
    }

    // MatrixArr = Crashing
    *(undefined *)(param_2 + 0x4c) = 4;

	if (*(short *)(param_2 + 0x58a) < 3)
	{
      cVar1 = '\a';
    }

	else {
      cVar1 = *(char *)(param_2 + 0x58a) + '\x05';
    }
    //Crashing frame = cVar1
    *(char *)(param_2 + 0x4d) = cVar1;

	// change animation
    *(undefined *)(iVar6 + 0x52) = 2;

    sVar2 = 7;
    if (2 < *(short *)(param_2 + 0x58a)) {
      sVar2 = *(short *)(param_2 + 0x58a) + 5;
    }
    *(short *)(iVar6 + 0x54) = sVar2;
    sVar2 = *(short *)(param_2 + 0x58a) + 1;
    *(short *)(param_2 + 0x58a) = sVar2;
    if (7 < sVar2) {
      *(undefined2 *)(param_2 + 0x58a) = 7;
    }
    if (*(short *)(param_2 + 0x400) < 0x510) 
	{
      // MatrixArr Crashing
      *(undefined *)(param_2 + 0x4c) = 4;
      
	  // MatrixIndex = 12
      *(undefined *)(param_2 + 0x4d) = 0xc;

	  // set animation
      *(undefined *)(iVar6 + 0x52) = 2;

	  // set animation frame
      *(undefined2 *)(iVar6 + 0x54) = 0xc;

      if (*(short *)(param_2 + 0x400) < 0x3c1) {
        uVar3 = *(short *)(param_2 + 0x40c) - 800;
        *(ushort *)(param_2 + 0x40c) = uVar3;
        if ((int)((uint)uVar3 << 0x10) < 0) {
          *(undefined2 *)(param_2 + 0x40c) = 0;
        }
      }
      else 
	  {
		// if particles are not spawned
        if (*(char *)(param_2 + 0x58c) == '\0')
		{
		  // VehStuckProc_MaskGrab_Particles
          FUN_80066cb0(param_2);

		  // now they are spawned
          *(undefined *)(param_2 + 0x58c) = 1;
        }
        sVar2 = *(short *)(param_2 + 0x40c) + 0x2d0;
        *(short *)(param_2 + 0x40c) = sVar2;
        if (8000 < sVar2) {
          *(undefined2 *)(param_2 + 0x40c) = 8000;
        }
      }
    }
    else {
    	//reset Speed and Speed Approximate
      *(undefined2 *)(param_2 + 0x38c) = 0;
      *(undefined2 *)(param_2 + 0x38e) = 0;

      //position backups
      *(undefined4 *)(param_2 + 0x2d4) = *(undefined4 *)(param_2 + 0x2e0);
      *(undefined4 *)(param_2 + 0x2d8) = *(undefined4 *)(param_2 + 0x2e4);
      *(undefined4 *)(param_2 + 0x2dc) = *(undefined4 *)(param_2 + 0x2e8);
    }
  }
  
  // if maskObj
  if (*(int *)(param_2 + 0x580) != 0) 
  {
	// set mask duration
    *(undefined2 *)(*(int *)(param_2 + 0x580) + 6) = 0x1e00;
	
	// if more than 0.5s after player fell
    if (*(short *)(param_2 + 0x400) < 0x3c1) {
      
	  // if not lifting player
	  if (*(char *)(param_2 + 0x58e) == '\0') 
	  {
		// decrease mask posY by elapsed time
        *(short *)(*(int *)(param_2 + 0x580) + 0xe) =
		*(short *)(*(int *)(param_2 + 0x580) + 0xe) - *(short *)(PTR_DAT_8008d2ac + 0x1d04);
      }
	  
	  // if lifting player (if driver isn't falling infinitely)
      else
	  {
		// elapsed milliseconds per frame, ~32
        iVar6 = *(int *)(PTR_DAT_8008d2ac + 0x1d04);

		// speed = 0
        *(undefined2 *)(param_2 + 0x38c) = 0;
		
		// increase driver height, both posCurr and posPrev
        iVar6 = *(int *)(param_2 + 0x2d8) + iVar6 * 0x80;
        *(int *)(param_2 + 0x2d8) = iVar6;
		*(int *)(param_2 + 0x2e4) = iVar6;
      }
	  
	  // set mask posZ
      *(undefined2 *)(*(int *)(param_2 + 0x580) + 0x10) =
           (short)((uint)*(undefined4 *)(param_2 + 0x2dc) >> 8);
		   
	  // if mask posY < driver posY
      if ((int)*(short *)(*(int *)(param_2 + 0x580) + 0xe) < *(int *)(param_2 + 0x2d8) >> 8) 
	  {
		// mask posY = driver posY
        *(undefined2 *)(*(int *)(param_2 + 0x580) + 0xe) =
             (short)((uint)*(int *)(param_2 + 0x2d8) >> 8);
			 
		// boolLiftingPlayer = 1
        *(undefined *)(param_2 + 0x58e) = 1;
      }
	  
	  // maskPosX = driverPosX
      *(undefined2 *)(*(int *)(param_2 + 0x580) + 0xc) =
           (short)((uint)*(undefined4 *)(param_2 + 0x2d4) >> 8);
	
	  // if more than halfway through mask pickup
      if ((int)*(short *)(param_2 + 0x400) < 0x2d1) 
	  {
		// scale = 100%
        *(undefined2 *)(*(int *)(param_2 + 0x580) + 0x12) = 0x1000;
      }
      
	  // if less than half
	  else 
	  {
		// interpolate scale
        *(undefined2 *)(*(int *)(param_2 + 0x580) + 0x12) =
             (short)(((0x3c0 - (int)*(short *)(param_2 + 0x400)) * 0x1000) / 0xf0);
      }
    }
    
	// less than 0.5s after player fell
	else 
	{
	  // scale = 0%
      *(undefined2 *)(*(int *)(param_2 + 0x580) + 0x12) = 0;
    }
  }
  return;
}


// VehStuckProc_MaskGrab_Init
// when falling off track
// param1 = thread, param2 = driver
void FUN_800671b0(int param_1,int param_2)
{
  // When this function executes,
  // mask comes down to catch you

  undefined4 uVar1;
  int iVar2;
  int iVar3;
  int iVar4;

  // get instance from thread
  iVar4 = *(int *)(param_1 + 0x34);

  // now being mask grabbed
  *(undefined *)(param_2 + 0x376) = 5;

  *(undefined *)(param_2 + 0x58c) = 0;
  *(undefined2 *)(param_2 + 0x58a) = 0;
  *(undefined *)(param_2 + 0x58e) = 0;

  // reset whistle bool
  *(undefined *)(param_2 + 0x58f) = 0;

  // reset stillFalling bool
  *(undefined *)(param_2 + 0x58d) = 0;

  // VehPickupItem_MaskUseWeapon
  uVar1 = FUN_80064c38(param_2,1);

  // Mask Object
  *(undefined4 *)(param_2 + 0x580) = uVar1;

  *(undefined2 *)(param_2 + 0x3dc) = 0;
  *(undefined2 *)(param_2 + 0x3e2) = 0;
  *(undefined2 *)(param_2 + 0x3de) = 0;
  *(undefined *)(param_2 + 0x4c) = 0;
  *(undefined *)(param_2 + 0x4d) = 0;

  // 1.44s until spawned back over track
  *(undefined2 *)(param_2 + 0x400) = 0x5a0;

  *(uint *)(param_2 + 0x2c8) = *(uint *)(param_2 + 0x2c8) & 0xfff7ffbf;

  // Check if 231 dll is loaded
  iVar2 = FUN_800348e8();

  if (
		// If it is loaded
		(iVar2 != 0) &&

		// If you're not in Adventure Arena
		((*(uint *)PTR_DAT_8008d2ac & 0x100000) == 0)
	  )
  {
	// RB_Player_ModifyWumpa, -2
    FUN_800abefc(param_2,0xfffffffe);
  }
  // if stored quadblock height + 0x8000 < posCurr.y
  if (*(int *)(param_2 + 0x2d0) + 0x8000 < *(int *)(param_2 + 0x2d8)) 
  {
	// mask grab count (for end of race comments)
    *(char *)(param_2 + 0x56a) = *(char *)(param_2 + 0x56a) + '\x01';

	// if driver touched surface before mask grab
	if (
			// if height is low
			// like splashing water on coco park happens on low height,
			// not high height when you're on the grass
			(*(int *)(param_2 + 0x2d8) < -0x8000) &&
			(
				// 10 particles
				iVar2 = 10,

				// if mask should grab you when underwater
				(*(uint *)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0xdc) & 2) != 0
			)
		)
	{
	  // AngleAxis normalVec
      *(undefined2 *)(param_2 + 0x584) = *(undefined2 *)(param_2 + 0x368);
      *(undefined2 *)(param_2 + 0x586) = *(undefined2 *)(param_2 + 0x36a);
      *(undefined2 *)(param_2 + 0x588) = *(undefined2 *)(param_2 + 0x36c);

	  // spawn particles
      do
	  {
		// 0x2138 = "falling",
		// like splashing in water on coco park

		// Create instance in particle pool
        iVar3 = FUN_80040308(0,*(undefined4 *)(PTR_DAT_8008d2ac + 0x2138),&DAT_80089a94);

		// if particle exists
		if (iVar3 != 0) {
          *(undefined *)(iVar3 + 0x18) = *(undefined *)(*(int *)(param_2 + 0x1c) + 0x50);

		  // driver -> instSelf
          *(undefined4 *)(iVar3 + 0x20) = *(undefined4 *)(param_2 + 0x1c);

		  // driverID
          *(undefined *)(iVar3 + 0x19) = *(undefined *)(param_2 + 0x4a);
        }

		// loop counter
        iVar2 = iVar2 + -1;

      } while (iVar2 != 0);
    }

	// if driver did not touch surface (and is still falling)
    else
	{
	  // save result in a bool
      *(undefined *)(param_2 + 0x58d) = 1;
    }
  }
  else 
  {
	// AngleAxis normalVec
    *(undefined2 *)(param_2 + 0x584) = *(undefined2 *)(param_2 + 0x368);
    *(undefined2 *)(param_2 + 0x586) = *(undefined2 *)(param_2 + 0x36a);
    *(undefined2 *)(param_2 + 0x588) = *(undefined2 *)(param_2 + 0x36c);
  }
  
  // edits position
  *(int *)(param_2 + 0x2d4) = *(int *)(iVar4 + 0x44) << 8;
  iVar2 = *(int *)(param_2 + 0x580);
  *(int *)(param_2 + 0x2d8) = *(int *)(iVar4 + 0x48) << 8;
  *(int *)(param_2 + 0x2dc) = *(int *)(iVar4 + 0x4c) << 8;
  
  //set previous frame velocity to the same as current frame velocity
  *(undefined4 *)(param_2 + 0x2e4) = *(undefined4 *)(param_2 + 0x2d8);
  *(undefined4 *)(param_2 + 0x2e0) = *(undefined4 *)(param_2 + 0x2d4);
  *(undefined4 *)(param_2 + 0x2e8) = *(undefined4 *)(param_2 + 0x2dc);
  
  // if maskObj
  if (iVar2 != 0) 
  {
    *(ushort *)(iVar2 + 4) = *(ushort *)(iVar2 + 4) | 1;
	
	// maskX = driverX
    *(undefined2 *)(*(int *)(param_2 + 0x580) + 0xc) =
         (short)((uint)*(undefined4 *)(param_2 + 0x2d4) >> 8);
		 
	// maskY = driverY
    *(short *)(*(int *)(param_2 + 0x580) + 0xe) =
         (short)((uint)*(undefined4 *)(param_2 + 0x2d8) >> 8) + 0x140;
		 
	// maskZ = driverZ
    *(undefined2 *)(*(int *)(param_2 + 0x580) + 0x10) =
         (short)((uint)*(undefined4 *)(param_2 + 0x2dc) >> 8);
  }

  // VehStuckProc_MaskGrab_Update
  *(undefined4 *)(param_2 + 0x58) = 0x80066d4c;

  // VehStuckProc_MaskGrab_PhysLinear
  *(undefined4 *)(param_2 + 0x5c) = 0x80066e3c;

  *(undefined4 *)(param_2 + 0x60) = 0x80062a2c; // OnAudio
  *(undefined4 *)(param_2 + 100) = 0x8005fc8c; // OnPhysAngular
  *(undefined4 *)(param_2 + 0x68) = 0x8005ea60; // VehPhysForce_OnApplyForces
  *(undefined4 *)(param_2 + 0x6c) = 0x80020410; // COLL_StartSearch_NearPlayer
  *(undefined4 *)(param_2 + 0x70) = 0x8005ebac; // VehPhysForce_CollideDrivers
  *(undefined4 *)(param_2 + 0x74) = 0x8001d944; // COLL_StartSearch_Player
  *(undefined4 *)(param_2 + 0x78) = 0x80060630; // JumpAndFriction
  *(undefined4 *)(param_2 + 0x7c) = 0x8005ee34; // VehPhysForce_TranslateMatrix -- move position to instance matrix

  // VehStuckProc_MaskGrab_Animate
  *(undefined4 *)(param_2 + 0x80) = 0x80066e8c;

  *(undefined4 *)(param_2 + 0x54) = 0;

  // VehEmitter_DriverMain
  *(undefined4 *)(param_2 + 0x84) = 0x80059a18;

  return;
}


// VehStuckProc_PlantEaten_Update
void FUN_8006749c(int param_1,int param_2)

{
  int iVar1;
  int iVar2;

  // get instance from thread
  iVar2 = *(int *)(param_1 + 0x34);

  // NoInput timer = NoInput timer - elapsed milliseconds per frame, ~32
  iVar1 = (uint)*(ushort *)(param_2 + 0x400) - (uint)*(ushort *)(PTR_DAT_8008d2ac + 0x1d04);
  *(undefined2 *)(param_2 + 0x400) = (short)iVar1;

  // if negative
  if (iVar1 * 0x10000 < 0)
  {
	// set to zero
    *(undefined2 *)(param_2 + 0x400) = 0;
  }

  // when input is now allowed
  if (*(short *)(param_2 + 0x400) == 0)
  {
	// VehStuckProc_MaskGrab_FindDestPos
	// driver, and quadblock previously touched by driver
    FUN_8006677c(param_2,*(undefined4 *)(param_2 + 0x354));

	// VehBirth_TeleportSelf (back onto track)
    FUN_80057c8c(param_2,0,0x80);

	// enable collision for this thread
    *(uint *)(param_1 + 0x1c) = *(uint *)(param_1 + 0x1c) & 0xffffefff;

	// make visible
	*(uint *)(iVar2 + 0x28) = *(uint *)(iVar2 + 0x28) & 0xffffff7f;

	// VehStuckProc_RevEngine_Init
	// this lets you rev engine while falling
	FUN_80067f4c(param_1,param_2);
  }
  return;
}


// VehStuckProc_PlantEaten_PhysLinear
void FUN_80067554(undefined4 param_1,int param_2)

{
  undefined *puVar1;

  // VehPhysProc_Driving_PhysLinear
  FUN_8006181c();

  // reset speed
  *(undefined2 *)(param_2 + 0x39e) = 0;

  // reset jump variable
  *(undefined2 *)(param_2 + 0x3f0) = 0;

  // reset two speed variables
  *(undefined2 *)(param_2 + 0x39e) = 0;
  *(undefined2 *)(param_2 + 0x39c) = 0;

  *(undefined *)(param_2 + 0x4b) = 0;
  puVar1 = PTR_DAT_8008d2ac;
  
  // acceleration prevention,
  // drop bits for jump button, 0x20?, reversing engine
  *(uint *)(param_2 + 0x2c8) = *(uint *)(param_2 + 0x2c8) & 0xfffdffdb | 8;
  
  // increment time spent in mask grab
  *(int *)(param_2 + 0x548) = *(int *)(param_2 + 0x548) + *(int *)(puVar1 + 0x1d04);
  
  return;
}


// VehStuckProc_PlantEaten_Animate
// param1 = thread, param2 = driver
void FUN_800675c0(undefined4 param_1,int param_2)

{
  short sVar1;
  undefined *puVar2;
  long x;
  int iVar3;
  int iVar4;
  SVECTOR local_38;
  int local_30;
  int local_28;
  long alStack32 [2];

  // plantEatingMe
  iVar3 = *(int *)(param_2 + 0x4a8);
  
  if (
		(
			// if plant is eating me
			(iVar3 != 0) && 
			
			// if not initialized
			(*(char *)(param_2 + 0x580) == '\0')
		) &&
		
		// if more than 0.5s since player death
		(*(short *)(param_2 + 0x400) < 0xb40))
  {
	// get instance from thread
    iVar4 = *(int *)(iVar3 + 0x34);

	// initialized, player eaten
    *(undefined *)(param_2 + 0x580) = 1;
	
    local_38.vx = -0xfa;
    if (*(short *)(*(int *)(iVar3 + 0x30) + 4) == 0) {
      local_38.vx = 0xfa;
    }
    local_38.vy = 0;
    local_38.vz = 0x2ee;

	// driver -> instance -> matrix
    SetRotMatrix((MATRIX *)(iVar4 + 0x30));

	// driver -> instance -> matrix
    SetTransMatrix((MATRIX *)(iVar4 + 0x30));

    RotTrans(&local_38,(VECTOR *)&local_30,alStack32);
    puVar2 = PTR_DAT_8008d2ac;

	// pushBuffer->posX
    *(undefined2 *)(PTR_DAT_8008d2ac + (uint)*(byte *)(param_2 + 0x4a) * 0x110 + 0x168) =
         (undefined2)local_30;

	// pushBuffer->posY
	*(short *)(puVar2 + (uint)*(byte *)(param_2 + 0x4a) * 0x110 + 0x16a) =

		// driverY + 0xc0
         *(short *)(iVar4 + 0x48) + 0xc0;

	// pushBuffer->posZ
    *(undefined2 *)(puVar2 + (uint)*(byte *)(param_2 + 0x4a) * 0x110 + 0x16c) =
		(undefined2)local_28;

	// cameraX = cameraX - driverX
    local_30 = local_30 - *(int *)(iVar4 + 0x44);

	// get pushBuffer->posY
    sVar1 = *(short *)(puVar2 + (uint)*(byte *)(param_2 + 0x4a) * 0x110 + 0x16a);

	// driverY
	iVar3 = *(int *)(iVar4 + 0x48);

	// cameraZ = cameraZ - driverZ
    local_28 = local_28 - *(int *)(iVar4 + 0x4c);

	// get direction from camera to driver
    x = ratan2(local_30,local_28);

	// pushBuffer-> ??? right after rotZ
    *(short *)(PTR_DAT_8008d2ac + (uint)*(byte *)(param_2 + 0x4a) * 0x110 + 0x170) = (short)x;

	// get distance between car and camera
	x = SquareRoot0(local_30 * local_30 + local_28 * local_28);

	// camPosY - driverY
    x = ratan2(sVar1 - iVar3,x);

    puVar2 = PTR_DAT_8008d2ac;

	// camera->rotZ
    *(short *)(PTR_DAT_8008d2ac + (uint)*(byte *)(param_2 + 0x4a) * 0x110 + 0x16e) =
         0x800 - (short)x;

	// camera-> ???
	*(undefined2 *)(puVar2 + (uint)*(byte *)(param_2 + 0x4a) * 0x110 + 0x172) = 0;
  }
  return;
}


// VehStuckProc_PlantEaten_Init
// when eaten by plant on papu pyramid
// param1 = thread, param2 = driver
void FUN_800677d0(int param_1,int param_2)
{
  // when this function executes, you are lifted
  // above the track by the mask, where you respawn

  int iVar1;
  int iVar2;

  iVar2 = *(int *)(param_1 + 0x34);
  
  // set state to mask grab, so nobody hits you with weapon
  *(undefined *)(param_2 + 0x376) = 5;
  
  // boolInited = false
  *(undefined *)(param_2 + 0x580) = 0;
  
  *(undefined2 *)(param_2 + 0x3dc) = 0;
  *(undefined2 *)(param_2 + 0x3e2) = 0;
  *(undefined2 *)(param_2 + 0x3de) = 0;
  
  // drop bits for airborne (and another?)
  *(uint *)(param_2 + 0x2c8) = *(uint *)(param_2 + 0x2c8) & 0xfff7ffbf;

  // "cloud" is the raincloud after hitting red potion

  // if thread of "cloud" exists
  if (*(int *)(param_2 + 0x4a0) != 0)
  {
    *(undefined2 *)(*(int *)(*(int *)(param_2 + 0x4a0) + 0x30) + 4) = 0;

	// Set driver->cloudTh->funcThTick to destroy thread
    *(undefined4 *)(*(int *)(param_2 + 0x4a0) + 0x2c) = 0x800b0f1c;

	// erase pointer to "cloud" thread
    *(undefined4 *)(param_2 + 0x4a0) = 0;
  }

  // Check if 231 dll is loaded
  iVar1 = FUN_800348e8();

  if (
		// If it is loaded
		(iVar1 != 0) &&

		// If you're not in Adventure Arena
		((*(uint *)PTR_DAT_8008d2ac & 0x100000) == 0)
	)
  {
	// RB_Player_ModifyWumpa, -2
    FUN_800abefc(param_2,0xfffffffe);
  }

  // allow this thread to ignore all collisions
  *(uint *)(param_1 + 0x1c) = *(uint *)(param_1 + 0x1c) | 0x1000;

  // make invisible
  *(uint *)(iVar2 + 0x28) = *(uint *)(iVar2 + 0x28) | 0x80;

  // OtherFX_Stop1 (three sounds)
  FUN_80028808(*(undefined4 *)(param_2 + 0x304));
  *(undefined4 *)(param_2 + 0x304) = 0;
  FUN_80028808(*(undefined4 *)(param_2 + 0x308));
  *(undefined4 *)(param_2 + 0x308) = 0;
  FUN_80028808(*(undefined4 *)(param_2 + 0x300));

  // VehStuckProc_PlantEaten_Update
  *(undefined4 *)(param_2 + 0x58) = 0x8006749c;

  // VehStuckProc_PlantEaten_PhysLinear
  *(undefined4 *)(param_2 + 0x5c) = 0x80067554;

  *(undefined4 *)(param_2 + 0x60) = 0x80062a2c; // OnAudio
  *(undefined4 *)(param_2 + 0x300) = 0;
  *(undefined4 *)(param_2 + 0x54) = 0;
  *(undefined4 *)(param_2 + 100) = 0;
  *(undefined4 *)(param_2 + 0x68) = 0;
  *(undefined4 *)(param_2 + 0x6c) = 0; // COLL_StartSearch_NearPlayer
  *(undefined4 *)(param_2 + 0x70) = 0; // VehPhysForce_CollideDrivers
  *(undefined4 *)(param_2 + 0x74) = 0; // COLL_StartSearch_Player
  *(undefined4 *)(param_2 + 0x78) = 0; // cant move anymore
  *(undefined4 *)(param_2 + 0x7c) = 0;

  // VehStuckProc_PlantEaten_Animate
  *(undefined4 *)(param_2 + 0x80) = 0x800675c0;

  // no particles
  *(undefined4 *)(param_2 + 0x84) = 0;
  return;
}

// VehStuckProc_RIP_Init
// param1 = thread, param2 = driver
void FUN_80067930(undefined4 param_1,int param_2)
{
  // VehStuckProc_PlantEaten_Init
  FUN_800677d0(param_1, param_2);

  // erase OnUpdate
  *(undefined4 *)(param_2 + 0x58) = 0;

  // erase OnAnimate
  *(undefined4 *)(param_2 + 0x80) = 0;

  // erase invisibleTimer
  *(undefined4 *)(param_2 + 0x28) = 0;

  return;
}


// VehStuckProc_RevEngine_Update
// param1 = thread, param2 = driver
void FUN_80067960(undefined4 param_1,int param_2)

{
  undefined4 uVar1;

  // If race has not started
  if (*(char *)(param_2 + 0x594) == '\0')
  {
	// If Traffic Lights are not done counting down
    if (0 < *(int *)(PTR_DAT_8008d2ac + 0x1d0c))
	{
	  // Dont continue with the function,
	  // let your kart stay in a revving state
      return;
    }
  }

  // If race has started
  else
  {

	// If mask grab has not lowered you close
	// enough to the track to let you go
    if (*(int *)(param_2 + 0x2d0) + 0x4000 <= *(int *)(param_2 + 0x2d8))
	{
	  // Dont continue with the function,
	  // let your kart stay in a revving state
      return;
    }
  }

  // Assume it's time to transition out of being
  // frozen, and into driving, last iteration of
  // this function

  if (
		// if reason for revving is mask grab
		(*(char *)(param_2 + 0x594) != '\0') &&

		// if maskObj exists
		(*(int *)(param_2 + 0x580) != 0)
	  )
  {
	// end duration
    *(undefined2 *)(*(int *)(param_2 + 0x580) + 6) = 0;
  }

  if (
		// If sacred fire constant is less than 				???
		((int)*(short *)(param_2 + 0x42e) < *(int *)(param_2 + 0x588)) &&
		((*(byte *)(param_2 + 0x593) & 3) == 0)
	 )
  {

    if (
		// While not moving, if you rev'd your engine less than...
		*(int *)(param_2 + 0x584) <

        (int)*(short *)(param_2 + 0x42e) + (int)*(short *)(param_2 + 0x432))
	{
	  // You get a small boost
      uVar1 = 0x20;
    }

	// if you rev'd your engine high
    else
	{
	  // you get a big boost
      uVar1 = 0x80;
    }

	// VehFire_Increment
	// one full second of reserves
    FUN_8005abfc(param_2,0x3c0,0,uVar1);
  }
  *(undefined2 *)(param_2 + 0x3dc) = 0;
  *(undefined *)(param_2 + 0x4fe) = 0;

  // VehPhysProc_Driving_Init
  FUN_80062b74(param_1);
  return;
}


// VehStuckProc_RevEngine_PhysLinear
// param1 = thread, param2 = driver
void FUN_80067a74(undefined4 param_1,int param_2)

{
  undefined *puVar1;
  int iVar2;

												// elapsed milliseconds per frame, ~32
  iVar2 = (uint)*(ushort *)(param_2 + 0x58e) - (uint)*(ushort *)(PTR_DAT_8008d2ac + 0x1d04);

  *(undefined2 *)(param_2 + 0x58e) = (short)iVar2;
  if (iVar2 * 0x10000 < 0) {
    *(undefined2 *)(param_2 + 0x58e) = 0;
  }
												// elapsed milliseconds per frame, ~32
  iVar2 = (uint)*(ushort *)(param_2 + 0x590) - (uint)*(ushort *)(PTR_DAT_8008d2ac + 0x1d04);
  *(undefined2 *)(param_2 + 0x590) = (short)iVar2;
  if (iVar2 * 0x10000 < 0) {
    *(undefined2 *)(param_2 + 0x590) = 0;
  }

  // VehPhysProc_Driving_PhysLinear
  FUN_8006181c(param_1,param_2);

  puVar1 = PTR_DAT_8008d2ac;

  // if race already started
  if (*(char *)(param_2 + 0x594) != '\0')
  {
	// cameraDC flag
    *(uint *)(PTR_DAT_8008d2ac + (uint)*(byte *)(param_2 + 0x4a) * 0xdc + 0x1508) =
         *(uint *)(PTR_DAT_8008d2ac + (uint)*(byte *)(param_2 + 0x4a) * 0xdc + 0x1508) | 0x10;

    *(undefined2 *)(puVar1 + (uint)*(byte *)(param_2 + 0x4a) * 0xdc + 0x1530) = 0x40;

    // Y pos -= 0x200
    *(int *)(param_2 + 0x2d8) = *(int *)(param_2 + 0x2d8) + -0x200;
    
	// if maskObj exists
	if (*(int *)(param_2 + 0x580) != 0) 
	{
	  // set mask duration
      *(undefined2 *)(*(int *)(param_2 + 0x580) + 6) = 0x1e00;
    }
  }
  return;
}


// VehStuckProc_RevEngine_Animate
// param1 = thread, param2 = driver
void FUN_80067b7c(int param_1,int param_2)

{
  byte bVar1;
  bool bVar2;
  undefined2 uVar3;
  int iVar4;
  int local_18;
  short sVar5;
  undefined4 uVar6;
  int iVar7;
  uint uVar8;
  int iVar9;
  int iVar10;

  // thread -> instance
  iVar10 = *(int *)(param_1 + 0x34);

  if (((0 < *(short *)(param_2 + 0x39e)) && (*(short *)(param_2 + 0x58e) == 0)) &&
     ((*(byte *)(param_2 + 0x593) & 3) == 0)) {

	// Curr revving meter   -   Max revving meter
	iVar4 = *(int *)(param_2 + 0x588) - *(int *)(param_2 + 0x584);

	// absolute value
	if (iVar4 < 0) {
      iVar4 = -iVar4;
    }

	// NOPing will fill meter in
	// slow motion, showing how it works
	iVar4 = iVar4 >> 1;

	iVar7 = iVar4;

	// Speed of filling the meter changes
	// depending on how full the meter is,
	// there are two speeds

	if (5000 < iVar4) {
      iVar7 = 5000;
    }

	if (iVar4 < 0x100) {
      iVar7 = 0x100;
    }

	// Interpolate turboMeter by speed
	// parameters: curr revving meter and meter filling speed
    iVar4 = FUN_80058f54(*(int *)(param_2 + 0x588),iVar7);

	// Set new curr rev
    *(int *)(param_2 + 0x588) = iVar4;

    *(undefined *)(param_2 + 0x592) = 2;

    // if max revv > filling speed
    if (iVar4 < *(int *)(param_2 + 0x584)) {
      *(undefined2 *)(param_2 + 0x58c) = 0;
    }

    else
    {
	  // elapsed milliseconds per frame, ~32
      sVar5 = *(short *)(param_2 + 0x58c) + *(short *)(PTR_DAT_8008d2ac + 0x1d04);
      *(short *)(param_2 + 0x58c) = sVar5;

	  // if more than 0.192s
	  if (0xc0 < sVar5) 
	  {
        *(undefined *)(param_2 + 0x592) = 0;
        *(byte *)(param_2 + 0x593) = *(byte *)(param_2 + 0x593) | 3;

		// OtherFX_Play_Echo
        FUN_80028494(0xf,1,(uint)*(ushort *)(param_2 + 0x2ca) & 1);
      }
    }
    goto LAB_80067dec;
  }
  *(undefined2 *)(param_2 + 0x58c) = 0;
  if (*(char *)(param_2 + 0x592) == '\x02') {
    *(undefined2 *)(param_2 + 0x58e) = 0x100;
    *(undefined *)(param_2 + 0x592) = 0;

    // if curr rev > ???
    if ((int)*(short *)(param_2 + 0x42e) < *(int *)(param_2 + 0x588)) {
      *(undefined *)(param_2 + 0x592) = 1;
    }
  }
  if ((*(char *)(param_2 + 0x592) != '\0') &&

    // curr rev < ???
     (*(int *)(param_2 + 0x588) < (int)*(short *)(param_2 + 0x42e))) {
    *(undefined *)(param_2 + 0x592) = 0;

	  // Interpolate rotation by speed
    // params: max revv, ???
    uVar6 = FUN_80058f54(*(undefined4 *)(param_2 + 0x584),(int)*(short *)(param_2 + 0x432) / 3 + 3);

    // max rev = ???
    *(undefined4 *)(param_2 + 0x584) = uVar6;
  }

  // if curr rev < 1
  if (*(int *)(param_2 + 0x588) < 1) {
    *(byte *)(param_2 + 0x593) = *(byte *)(param_2 + 0x593) & 0xfd;

    // max rev = ???
    *(int *)(param_2 + 0x584) =
         (int)*(short *)(param_2 + 0x42e) + (int)*(short *)(param_2 + 0x432) / 3;
  }

  // if curr rev >= 1
  else {

    // rev deacceleration rate = curr rev / 2
    uVar8 = *(int *)(param_2 + 0x588) >> 1;

    if ((*(byte *)(param_2 + 0x593) & 2) == 0) {
      bVar2 = (int)uVar8 < 0x100;

      // if rev deacceleration rate > 1000
      if (1000 < (int)uVar8) {

        // rev deacceleration rate = 1000
        uVar8 = 1000;
        goto LAB_80067d64;
      }
    }

    else {
      bVar2 = (int)uVar8 < 0x100;

      // if rev deacceleration rate > 3000
      if (3000 < (int)uVar8) {

        // rev deacceleration rate = 3000
        uVar8 = 3000;
LAB_80067d64:
        bVar2 = uVar8 < 0x100;
      }
    }
    if (bVar2) {

      // rev deacceleration rate = 0x100
      uVar8 = 0x100;
    }

    // new rev = curr rev - rev deacceleration rate
    iVar4 = *(int *)(param_2 + 0x588) - uVar8;

    // curr rev = new rev
    *(int *)(param_2 + 0x588) = iVar4;

    // if new rev < 1
    if (iVar4 < 1) {

      *(undefined2 *)(param_2 + 0x590) = 0xc0;

      // curr rev = 0
      *(undefined4 *)(param_2 + 0x588) = 0;
    }
  }
  if (*(short *)(param_2 + 0x39e) < 1) {
    *(byte *)(param_2 + 0x593) = *(byte *)(param_2 + 0x593) & 0xfe;
  }
LAB_80067dec:
  if ((*(uint *)(param_2 + 0x590) & 0x200ffff) == 0) {

    // if curr rev < ???
    if (*(int *)(param_2 + 0x588) < (int)*(short *)(param_2 + 0x42e)) {
      *(undefined *)(param_2 + 0x4fe) = 0;
    }
    else {
      *(undefined *)(param_2 + 0x4fe) = 1;
    }
  }
  else {
    *(undefined *)(param_2 + 0x4fe) = 2;
  }
  iVar4 = (int)*(short *)(param_2 + 0x42e);

  // ??? = curr rev
  *(undefined2 *)(param_2 + 0x36e) = *(undefined2 *)(param_2 + 0x588);

  // if curr rev < ???
  if (*(int *)(param_2 + 0x588) < iVar4)
  {

	// 476 and 447 can be absolutely any value,
	// by default they are 15 and 30, but as long as
	// they are proportional (1 and 2, 4 and 8), they
	// behave the same as 15 and 30

    bVar1 = *(byte *)(param_2 + 0x476);

	// 477 changes when meter turns red
    local_18 = (uint)*(byte *)(param_2 + 0x477) * 0x20 + 1;

	  // curr rev
    uVar6 = *(undefined4 *)(param_2 + 0x588);
    iVar7 = 0;
    iVar9 = iVar4;
  }
  else
  {
	// 477 changes when meter turns red
    bVar1 = *(byte *)(param_2 + 0x477);

    local_18 = 1;

	// curr rev
	uVar6 = *(undefined4 *)(param_2 + 0x588);
    iVar9 = iVar4 + *(short *)(param_2 + 0x432);
    iVar7 = iVar4;
  }

  // Get percentage of uVar6 between iVar7 and iVar9,
  // then return that same percentage between bVar1<<5 and local18
  // Map value from [oldMin, oldMax] to [newMin, newMax]
  // inverting newMin and newMax will give an inverse range mapping
  uVar3 = FUN_80058f9c(uVar6,iVar7,iVar9,(uint)bVar1 << 5,local_18);

  *(undefined2 *)(param_2 + 0x3dc) = uVar3;
  *(undefined4 *)(param_2 + 0x490) = 0;
  iVar4 = (int)((uint)*(ushort *)(param_2 + 0x36e) << 0x10) >> 0x16;

  *(short *)(param_2 + 0x40c) = (short)*(ushort *)(param_2 + 0x36e) >> 6;

  if (iVar4 < 0x401) {
    if (iVar4 < 0) {
      *(undefined2 *)(param_2 + 0x40c) = 0;
    }
  }

  else {
    *(undefined2 *)(param_2 + 0x40c) = 0x400;
  }

  // Set the scale of the car while revving the engine,
  // this is a basic "squash and stretch" concept of animation, before motion

  // Reduce height a little
  *(short *)(iVar10 + 0x1e) = 0xccc - *(short *)(param_2 + 0x40c);

  // Increase X and Z a little
  *(short *)(iVar10 + 0x1c) = (short)(((int)*(short *)(param_2 + 0x40c) * 6) / 10) + 0xccc;
  *(short *)(iVar10 + 0x20) = (short)(((int)*(short *)(param_2 + 0x40c) * 6) / 10) + 0xccc;

  return;
}

// VehStuckProc_RevEngine_Init
// param1 = thread, param2 = driver
void FUN_80067f4c(undefined4 param_1,int param_2)

{
  // spawn function that waits for traffic lights

  undefined4 uVar1;

  // kart state to rev
  *(undefined *)(param_2 + 0x376) = 4;

  *(undefined *)(param_2 + 0x4fe) = 0;
  *(undefined4 *)(param_2 + 0x588) = 0;

  // assume reason for revving is: start of race
  *(undefined *)(param_2 + 0x594) = 0;

  // clear maskObj
  *(undefined4 *)(param_2 + 0x580) = 0;

  // if this is a mask grab
  if (*(int *)(param_2 + 0x2d0) + 0x1000 < *(int *)(param_2 + 0x2d8))
  {
	// assume reason for revving is: mask grab
    *(undefined *)(param_2 + 0x594) = 1;

	// VehPickupItem_MaskUseWeapon
    uVar1 = FUN_80064c38(param_2,0);

	// Mask Object
    *(undefined4 *)(param_2 + 0x580) = uVar1;

	// Driver flag
    *(uint *)(param_2 + 0x2c8) = *(uint *)(param_2 + 0x2c8) & 0xfffffffe;

	// CameraDC flag
    *(uint *)(PTR_DAT_8008d2ac + (uint)*(byte *)(param_2 + 0x4a) * 0xdc + 0x1508) =
         *(uint *)(PTR_DAT_8008d2ac + (uint)*(byte *)(param_2 + 0x4a) * 0xdc + 0x1508) | 8;
  }
  
  // firstFrameSinceRevEngine
  *(undefined *)(param_2 + 0x449) = 1;

  // VehStuckProc_RevEngine_Update
  *(undefined4 *)(param_2 + 0x58) = 0x80067960;

  // VehStuckProc_RevEngine_PhysLinear
  *(undefined4 *)(param_2 + 0x5c) = 0x80067a74;

  *(undefined4 *)(param_2 + 0x60) = 0x80062a2c; // OnAudio
  *(undefined4 *)(param_2 + 0x7c) = 0x8005ee34; // VehPhysForce_TranslateMatrix -- move position to instance matrix

  // VehStuckProc_RevEngine_Animate
  *(undefined4 *)(param_2 + 0x80) = 0x80067b7c;

  // VehEmitter_DriverMain
  *(undefined4 *)(param_2 + 0x84) = 0x80059a18;

  *(undefined2 *)(param_2 + 0x58c) = 0;
  *(undefined2 *)(param_2 + 0x58e) = 0;
  *(undefined *)(param_2 + 0x592) = 0;
  *(undefined *)(param_2 + 0x593) = 0;
  *(undefined2 *)(param_2 + 0x590) = 0;
  *(undefined4 *)(param_2 + 0x54) = 0;
  *(undefined4 *)(param_2 + 100) = 0;
  *(undefined4 *)(param_2 + 0x68) = 0;
  *(undefined4 *)(param_2 + 0x6c) = 0; // COLL_StartSearch_NearPlayer
  *(undefined4 *)(param_2 + 0x70) = 0; // VehPhysForce_CollideDrivers
  *(undefined4 *)(param_2 + 0x74) = 0; // COLL_StartSearch_Player
  *(undefined4 *)(param_2 + 0x78) = 0; // cant move anymore
  *(int *)(param_2 + 0x584) =
       (int)*(short *)(param_2 + 0x42e) + (int)*(short *)(param_2 + 0x432) / 3;
  return;
}


// VehStuckProc_Tumble_Update
// param1 = thread, param2 = driver
void FUN_8006809c(undefined4 param_1,int param_2)

{
  // if you are done being blasted, NoInput ended
  if (*(short *)(param_2 + 0x400) == 0) {
    *(undefined *)(param_2 + 0x4c) = 0;
    *(undefined *)(param_2 + 0x4d) = 0;

	// VehPhysProc_Driving_Init
    FUN_80062b74();
  }
  return;
}

// VehStuckProc_Tumble_PhysLinear
// param1 = thread, param2 = driver
void FUN_800680d0(undefined4 param_1,int param_2)

{
  int iVar1;

  // NoInput timer = NoInput timer -  elapsed milliseconds per frame, ~32
  iVar1 = (uint)*(ushort *)(param_2 + 0x400) - (uint)*(ushort *)(PTR_DAT_8008d2ac + 0x1d04);
  *(undefined2 *)(param_2 + 0x400) = (short)iVar1;

  // if negative
  if (iVar1 * 0x10000 < 0)
  {
	// set to zero
    *(undefined2 *)(param_2 + 0x400) = 0;
  }

  // VehPhysProc_Driving_PhysLinear
  FUN_8006181c(param_1,param_2);

  // force to jump when hit the ground,
  // lock to 96ms (0.1s) until blasted state is over
  *(undefined2 *)(param_2 + 0x3f6) = 0x60;

  // reset two speed variables
  *(undefined2 *)(param_2 + 0x39c) = 0;
  *(undefined2 *)(param_2 + 0x39e) = 0;

  // wheels skidding, blasted, accel prevention
  *(uint *)(param_2 + 0x2c8) = *(uint *)(param_2 + 0x2c8) | 0x5808;
  
  // jump_InitialVelY to throw driver in air
  *(short *)(param_2 + 0x3f8) = *(short *)(param_2 + 0x400) * 2 + 6000;
  
  return;
}


// VehStuckProc_Tumble_PhysAngular
// param1 = thread, param2 = driver
void FUN_80068150(undefined4 param_1,int param_2)

{
  undefined *puVar1;
  ushort uVar2;
  undefined2 uVar3;
  short sVar4;

  puVar1 = PTR_DAT_8008d2ac;
  *(undefined2 *)(param_2 + 0x3e6) = 10000;
  
  // decrease turn rate by 1/8 of itself
  *(short *)(param_2 + 0x3b4) = *(short *)(param_2 + 0x3b4) - (*(short *)(param_2 + 0x3b4) >> 3);
  
  sVar4 = *(short *)(param_2 + 0x3d2) - (*(short *)(param_2 + 0x3d2) >> 3);
  *(short *)(param_2 + 0x3d2) = sVar4;
  
  *(short *)(param_2 + 0xc0) = *(short *)(param_2 + 0x3b4);
  *(short *)(param_2 + 0x3c6) = (*(short *)(param_2 + 0x3c6) + sVar4 + 0x800U & 0xfff) - 0x800;
  *(short *)(param_2 + 0x3d4) = *(short *)(param_2 + 0x3d4) - (*(short *)(param_2 + 0x3d4) >> 3);

  // angle change = angle + (spinRate * time lapsed between frames) & 0xFFF
  uVar2 = *(short *)(param_2 + 0x39a) +
          (short)((int)*(short *)(param_2 + 0x3b4) * *(int *)(puVar1 + 0x1d04) >> 0xd) & 0xfff;

  // angle = angle change
  *(ushort *)(param_2 + 0x39a) = uVar2;
  
  // cameraRotY = ??? + kart angle + drift angle
  *(short *)(param_2 + 0x2ee) = *(short *)(param_2 + 0x3d4) + uVar2 + *(short *)(param_2 + 0x3c6);

  // Interpolate rotation by speed
  uVar3 = FUN_80058f54((int)*(short *)(param_2 + 0x2f2),(*(int *)(puVar1 + 0x1d04) << 5) >> 5,0);

  // set new camera rotation
  *(undefined2 *)(param_2 + 0x2f2) = uVar3;

  // VehPhysForce_RotAxisAngle
  FUN_8005f89c(param_2 + 0x310,param_2 + 0x360,(int)*(short *)(param_2 + 0x39a));
  return;
}

// VehStuckProc_Tumble_Animate
// param1 = thread, param2 = driver
void FUN_80068244(undefined4 param_1,int param_2)

{
  char cVar1;
  int iVar2;

  // set animation index
  *(undefined *)(param_2 + 0x4c) = 6;

  // get amount of time remaining before you can move (while blasted),
  // use that to determine animation frame of bouncing around
  iVar2 = (int)((uint)*(ushort *)(param_2 + 0x400) << 0x10) >> 0x15;

  // DAT_80087f28 is a constant for how many frames are in "blasted" anim

  // Just a stupid fail-safe to alert the debugger
  if (DAT_80087f28 == 0) trap(0x1c00);
  if ((DAT_80087f28 == -1) && (iVar2 == -0x80000000)) trap(0x1800);

  // get animation frame of blasted
  cVar1 = (char)(iVar2 % DAT_80087f28);

  if (*(char *)(param_2 + 0x580) != '\0')
  {
	// play animation backwards???
    cVar1 = (char)DAT_80087f28 - (cVar1 + '\x01');
  }

  // set animation frame
  *(char *)(param_2 + 0x4d) = cVar1;

  return;
}

// VehStuckProc_Tumble_Init
// param1 = thread, param2 = driver
void FUN_800682a4(undefined4 param_1,int param_2)

{
  byte bVar1;
  undefined2 uVar2;
  int iVar3;
  undefined4 uVar4;

  // put player in flipping animation after being hit
  *(undefined *)(param_2 + 0x376) = 6;

  *(undefined2 *)(param_2 + 0x3dc) = 0;

  // Check if 231 dll is loaded
  iVar3 = FUN_800348e8();
  if (
		// if it is loaded
		(iVar3 != 0) &&

		// If you're not in Adventure Arena
		((*(uint *)PTR_DAT_8008d2ac & 0x100000) == 0)
	)
  {
	// RB_Player_ModifyWumpa, -3
    FUN_800abefc(param_2,0xfffffffd);
  }

  // set animation to zero
  *(undefined *)(*(int *)(param_2 + 0x1c) + 0x52) = 0;

  // Instance_GetNumAnimFrames(instance, anim#0)
  uVar4 = FUN_8005b0f4(*(undefined4 *)(param_2 + 0x1c),0);

  // VehFrameInst_GetStartFrame(midpoint, numFrames)
  uVar2 = FUN_8005b0c4(0,uVar4);

  // set animation frame
  *(undefined2 *)(*(int *)(param_2 + 0x1c) + 0x54) = uVar2;

  // Get random number
  bVar1 = FUN_8003ea28();

  // randomly play blasted backwards
  *(byte *)(param_2 + 0x580) = bVar1 & 4;

  // VehStuckProc_Tumble_Update
  *(undefined4 *)(param_2 + 0x58) = 0x8006809c;

  // VehStuckProc_Tumble_PhysLinear
  *(undefined4 *)(param_2 + 0x5c) = 0x800680d0;

  *(undefined4 *)(param_2 + 0x60) = 0x80062a2c; // OnAudio
  *(undefined4 *)(param_2 + 100) = 0x80068150; // OnPhysAngular
  *(undefined4 *)(param_2 + 0x68) = 0x8005ea60; // VehPhysForce_OnApplyForces
  *(undefined4 *)(param_2 + 0x6c) = 0x80020410; // COLL_StartSearch_NearPlayer
  *(undefined4 *)(param_2 + 0x70) = 0x8005ebac; // VehPhysForce_CollideDrivers
  *(undefined4 *)(param_2 + 0x74) = 0x8001d944; // COLL_StartSearch_Player
  *(undefined4 *)(param_2 + 0x78) = 0x80060630; // JumpAndFriction
  *(undefined4 *)(param_2 + 0x7c) = 0x8005ee34; // VehPhysForce_TranslateMatrix -- move position to instance matrix

  // VehStuckProc_Tumble_Animate
  *(undefined4 *)(param_2 + 0x80) = 0x80068244;

  // Erase OnInit, now that it has executed
  *(undefined4 *)(param_2 + 0x54) = 0;

  // VehEmitter_DriverMain
  *(undefined4 *)(param_2 + 0x84) = 0x80059a18;

  if (*(char *)(param_2 + 0x4b) < '\x01') {
    uVar4 = 0x19;
  }
  else {
    uVar4 = 0x29;
  }

  // GAMEPAD_JogCon1
  FUN_800263a0(param_2,uVar4,0x60);

  return;
}


// VehStuckProc_Warp_MoveDustPuff
// "dustpuff" is really lightning under the player,
// without this, lightning is half-stuck under the player
void FUN_800683f4(short *param_1,int param_2,int param_3,short *param_4)

{
  uint uVar1;
  short *psVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  short *psVar6;
  int iVar7;

  // Get random number
  uVar1 = FUN_8003ea28();

  iVar4 = param_3 >> 1;
  iVar5 = (int)((uVar1 & 0xfff) * param_3) >> 0xc;
  if (iVar5 < iVar4) {
    iVar5 = iVar5 - param_3;
  }

  // Get random number
  uVar1 = FUN_8003ea28();

  iVar7 = (int)((uVar1 & 0xfff) * param_3) >> 0xc;
  if (iVar7 < iVar4) {
    iVar7 = iVar7 - param_3;
  }

  // Get random number
  uVar1 = FUN_8003ea28();

  iVar3 = (int)((uVar1 & 0xfff) * param_3) >> 0xc;
  if (iVar3 < iVar4) {
    iVar3 = iVar3 - param_3;
  }
  psVar2 = param_1 + param_2 * 4;
  iVar4 = param_2 >> 1;
  psVar6 = param_1 + iVar4 * 4;
  *psVar6 = (short)((int)*param_1 + (int)*psVar2 >> 1) + (short)(*param_4 * iVar5 >> 0xc);
  psVar6[1] = (short)((int)param_1[1] + (int)psVar2[1] >> 1) + (short)(param_4[1] * iVar7 >> 0xc);
  psVar6[2] = (short)((int)param_1[2] + (int)psVar2[2] >> 1) + (short)(param_4[2] * iVar3 >> 0xc);
  if (2 < param_2) {
    iVar5 = param_3 * 0xc00 >> 0xc;

	// VehStuckProc_Warp_MoveDustPuff
    FUN_800683f4(param_1,iVar4,iVar5,param_4);

	// VehStuckProc_Warp_MoveDustPuff
    FUN_800683f4(psVar6,iVar4,iVar5,param_4);
  }
  return;
}


// VehStuckProc_Warp_AddDustPuff1
void FUN_800685b0(short *param_1)

{
  int iVar1;

  if (((*(uint *)(PTR_DAT_8008d2ac + 0x1cec) & 1) == 0) &&
     (
		// Create instance in particle pool
		iVar1 = FUN_80040308(0,*(undefined4 *)(PTR_DAT_8008d2ac + 0x2118),&DAT_8008a180),
		iVar1 != 0
	 ))
  {
	// position variables
    *(int *)(iVar1 + 0x24) = *(int *)(iVar1 + 0x24) + (int)*param_1 * 0x100;
    *(int *)(iVar1 + 0x2c) = *(int *)(iVar1 + 0x2c) + (int)param_1[1] * 0x100;
    *(int *)(iVar1 + 0x34) = *(int *)(iVar1 + 0x34) + (int)param_1[2] * 0x100;
  }
  return;
}


// VehStuckProc_Warp_AddDustPuff2
void FUN_80068644(int param_1,int param_2)

{
  short sVar1;
  short sVar2;
  ushort uVar3;
  short sVar4;
  short sVar5;
  short sVar6;
  uint *puVar7;
  undefined4 in_zero;
  undefined4 in_at;
  short extraout_var;
  short extraout_var_00;
  int iVar8;
  uint uVar9;
  uint *puVar10;
  undefined4 uVar11;
  uint *puVar12;
  uint *puVar13;
  short *psVar14;
  short *psVar15;
  uint *puVar16;
  undefined4 *puVar17;
  int iVar18;
  uint *puVar19;
  undefined *puVar20;
  int local_30;

  // pointer to each player's pushBuffer buffer
  puVar20 = PTR_DAT_8008d2ac + (uint)*(byte *)(param_1 + 0x4a) * 0x110 + 0x168;

  // set several pushBuffer buffer variables to coprocessor
  gte_SetRotMatrix(puVar20 + 0x28);
  gte_SetTransMatrix(puVar20 + 0x28);

  // handle some pushBuffer buffer variables in RAM
  sVar1 = *(short *)(puVar20 + 0x48);
  sVar2 = *(short *)(puVar20 + 0x4e);
  uVar3 = *(ushort *)(puVar20 + 0x54);

  // handle some pushBuffer buffer variables in scratchpad
  DAT_1f8001c0 = (undefined2)((int)sVar1 + (int)*(short *)(puVar20 + 0x4a) >> 5);
  DAT_1f8001c2 = (undefined2)
                 ((int)*(short *)(puVar20 + 0x4e) + (int)*(short *)(puVar20 + 0x50) >> 5);
  DAT_1f8001c4 = (undefined2)
                 ((int)*(short *)(puVar20 + 0x54) + (int)*(short *)(puVar20 + 0x56) >> 5);

  // backBuffer->primMem.curr
  puVar19 = *(uint **)(*(int *)(PTR_DAT_8008d2ac + 0x10) + 0x80);

  // if driver -> instance -> flags & INVISIBLE is true
  if ((*(uint *)(*(int *)(param_1 + 0x1c) + 0x28) & 0x80) != 0)
  {
    DAT_1f800188._0_2_ = (short)((uint)*(undefined4 *)(param_1 + 0x2d4) >> 8);
    DAT_1f800188._2_2_ = (undefined2)((uint)*(undefined4 *)(param_2 + 0x10) >> 8);
    DAT_1f80018c._0_2_ = (short)((uint)*(undefined4 *)(param_1 + 0x2dc) >> 8);

	// add dust puff
    FUN_800685b0(&DAT_1f800188);
  }

  local_30 = 0;
  do {
    iVar18 = (local_30 << 0xc) / 6;

	// Sine(angle)
    iVar8 = FUN_8003d184(iVar18 + *(int *)(param_2 + 0xc));

	_DAT_1f800108 =
         CONCAT22((short)((uint)*(undefined4 *)(param_2 + 8) >> 8),
                  (short)((uint)*(undefined4 *)(param_1 + 0x2d4) >> 8) - (short)(iVar8 >> 5));

	// Cosine(angle)
	iVar8 = FUN_8003d1c0(iVar18 + *(int *)(param_2 + 0xc));

	_DAT_1f80010c =
         _DAT_1f80010c & 0xffff0000 |
         (uint)(ushort)((short)((uint)*(undefined4 *)(param_1 + 0x2dc) >> 8) - (short)(iVar8 >> 5));
    DAT_1f800188._0_2_ = (short)((uint)*(undefined4 *)(param_1 + 0x2d4) >> 8);
    DAT_1f800188._2_2_ = (undefined2)((uint)*(undefined4 *)(param_2 + 0x10) >> 8);
    DAT_1f80018c._0_2_ = (short)((uint)*(undefined4 *)(param_1 + 0x2dc) >> 8);

	// driver -> instSelf -> flags -> INVISIBLE is false
    if ((*(uint *)(*(int *)(param_1 + 0x1c) + 0x28) & 0x80) == 0) {

	  // Sine(angle)
	  iVar8 = FUN_8003d184(iVar18 + *(int *)(param_2 + 0xc));

	  _DAT_1f800108 =
           _DAT_1f800108 & 0xffff0000 | (uint)(ushort)(DAT_1f800108 - (short)(iVar8 >> 6));

	  // Cosine(angle)
	  iVar8 = FUN_8003d1c0(iVar18 + *(int *)(param_2 + 0xc));

	  _DAT_1f80010c =
           _DAT_1f80010c & 0xffff0000 | (uint)(ushort)(DAT_1f80010c - (short)(iVar8 >> 6));

	  // Sine(angle)
	  FUN_8003d184(iVar18 + *(int *)(param_2 + 0xc));

	  DAT_1f800188._0_2_ = (short)DAT_1f800188 + extraout_var;

	  // Cosine(angle)
	  FUN_8003d1c0(iVar18 + *(int *)(param_2 + 0xc));

	  DAT_1f80018c._0_2_ = (short)DAT_1f80018c + extraout_var_00;
    }

	// if driver is visible
    else
	{
	  // add dust puff
      FUN_800685b0(&DAT_1f800108);
    }

    uVar11 = 0x10;

	// VehStuckProc_Warp_MoveDustPuff
	FUN_800683f4(&DAT_1f800108,0x10,0x100,&DAT_1f8001c0);

    iVar18 = 1;
    puVar17 = (undefined4 *)&DAT_1f800108;
    do {
      puVar10 = (uint *)(iVar18 << 7);

	  // Sine(angle)
      iVar8 = FUN_8003d184(puVar10);

	  iVar18 = iVar18 + 1;
      *(short *)((int)puVar17 + 10) = *(short *)((int)puVar17 + 10) + (short)(iVar8 >> 7);
      puVar17 = puVar17 + 2;
    } while (iVar18 < 0x10);
    sVar4 = sVar1 >> 10;
    sVar5 = sVar2 >> 10;
    DAT_1f800190 = CONCAT22(DAT_1f80010a + sVar5,DAT_1f800108 + sVar4);
    sVar6 = (short)uVar3 >> 10;
    DAT_1f800194 = DAT_1f800194 & 0xffff0000 | (uint)(ushort)(DAT_1f80010c + sVar6);
    uVar9 = (_DAT_1f80010c & 0xffff) - ((int)((uint)uVar3 << 0x10) >> 0x1a);
    DAT_1f800198 = CONCAT22(DAT_1f80010a - sVar5,DAT_1f800108 - sVar4);
    DAT_1f80019c = DAT_1f80019c & 0xffff0000 | uVar9 & 0xffff;
    
#if 0
	setCopReg(2,in_zero,DAT_1f800190);
    setCopReg(2,in_at,DAT_1f800194);
    setCopReg(2,0x1f800190,_DAT_1f800108);
    setCopReg(2,uVar9,_DAT_1f80010c);
    setCopReg(2,puVar10,DAT_1f800198);
    setCopReg(2,uVar11,DAT_1f80019c);

	// RTPT - Perspective Transformation (triple)
	gte_rtpt();

    DAT_1f8001a0 = getCopReg(2,0xc);
    DAT_1f8001a4 = getCopReg(2,0xd);
    DAT_1f8001a8 = getCopReg(2,0xe);
    DAT_1f8001ac = getCopReg(2,0x11);
#else
    gte_ldv01();
    gte_ldv2();
    gte_rtpt();
    gte_stsxy3c();
    gte_stSZ1();
#endif
	
	iVar18 = 0;
    puVar12 = puVar19 + 0x11;
    puVar7 = &DAT_1f8001a0;
    psVar14 = &DAT_1f80010c;
    puVar16 = &DAT_1f8001b0;
    puVar17 = (undefined4 *)&DAT_1f800108;
    do {
      puVar13 = puVar7;
      puVar17 = puVar17 + 2;
      psVar15 = psVar14 + 4;
      DAT_1f800190 = CONCAT22(psVar14[3] + sVar5,*(short *)puVar17 + sVar4);
      DAT_1f800194 = DAT_1f800194 & 0xffff0000 | (uint)(ushort)(*psVar15 + sVar6);
      DAT_1f800198 = CONCAT22(psVar14[3] - sVar5,*(short *)puVar17 - sVar4);
      DAT_1f80019c = DAT_1f80019c & 0xffff0000 | (uint)(ushort)(*psVar15 - sVar6);
      
#if 0
	  setCopReg(2,in_zero,DAT_1f800190);
      setCopReg(2,in_at,DAT_1f800194);
      setCopReg(2,0x1f800190,*puVar17);
      setCopReg(2,puVar16,puVar17[3]);
      setCopReg(2,puVar10,DAT_1f800198);
      setCopReg(2,puVar12,DAT_1f80019c);

	  gte_rtpt();

	  uVar9 = getCopReg(2,0xc);
      *puVar16 = uVar9;
      uVar9 = getCopReg(2,0xd);
      puVar16[1] = uVar9;
      uVar9 = getCopReg(2,0xe);
      puVar16[2] = uVar9;
      uVar9 = getCopReg(2,0x11);
      puVar16[3] = uVar9;
#else
      gte_ldv01();
      gte_ldv2();
      gte_rtpt();
      gte_stsxy3c();
      gte_stSZ1();
#endnif	  

      puVar12[-0x10] = 0xe1000a20;
      puVar12[-0xf] = 0x3a000000;
      puVar12[-0xd] = 0x7f1f3f;
      puVar12[-0xb] = 0;
      puVar12[-9] = 0x7f1f3f;
      puVar12[-0xe] = *puVar16;
      puVar12[-0xc] = puVar16[1];
      puVar12[-10] = *puVar13;
      uVar9 = puVar13[1];
      puVar12[-7] = 0x3a000000;
      puVar12[-5] = 0x7f1f3f;
      puVar12[-3] = 0;
      puVar12[-1] = 0x7f1f3f;
      puVar12[-8] = uVar9;
      puVar12[-6] = puVar16[2];
      puVar12[-4] = puVar16[1];
      iVar18 = iVar18 + 1;
      puVar12[-2] = puVar13[2];
      *puVar12 = puVar13[1];
      puVar10 = (uint *)(*(int *)(puVar20 + 0xf4) + ((int)puVar16[3] >> 6) * 4);
      puVar12 = puVar12 + 0x12;
      *puVar19 = *puVar10 | 0x11000000;
      *puVar10 = (uint)puVar19 & 0xffffff;
      puVar19 = puVar19 + 0x12;
      puVar7 = puVar16;
      psVar14 = psVar15;
      puVar16 = puVar13;
      puVar17 = puVar17;
    } while (iVar18 < 0x10);
    local_30 = local_30 + 1;
  } while (local_30 < 6);

  // backBuffer->primMem.curr
  *(uint **)(*(int *)(PTR_DAT_8008d2ac + 0x10) + 0x80) = puVar19;

  return;
}


// VehStuckProc_Warp_PhysAngular
// param1 = thread, param2 = driver
// animate rotation and scale in warppad
void FUN_80068be8(undefined4 param_1,int param_2)

{
  undefined2 uVar1;
  short sVar2;
  int iVar3;
  int iVar4;
  int *piVar5;
  undefined2 local_18;
  short local_16;
  undefined2 local_14;

  // get instance from driver object
  iVar4 = *(int *)(param_2 + 0x1c);

  piVar5 = (int *)(param_2 + 0x580);

  // if driver is visible
  if ((*(uint *)(iVar4 + 0x28) & 0x80) == 0)
  {
	// height + 0x100
    iVar3 = *(int *)(param_2 + 0x2d8) + 0x100;

    *(int *)(param_2 + 0x590) = iVar3;
    if (iVar3 < *(int *)(param_2 + 0x588)) {
      *(int *)(param_2 + 0x590) = *(int *)(param_2 + 0x588);
    }

	// if driver is visible
    if ((*(uint *)(iVar4 + 0x28) & 0x80) == 0) 
	{
	  // stop particle spawning
      *(int *)(param_2 + 0x58c) = *(int *)(param_2 + 0x58c) + -100;
    }

	// add dust puff
    FUN_80068644(param_2,piVar5);
  }

  // timer
  iVar3 = *piVar5;
  *piVar5 = iVar3 + 0x1a;

  // timer < 801
  if (iVar3 + 0x1a < 0x321)
  {
	// interpolate until scale is [0x12c0, 0x960, 0x12c0],
	// car is wide and short

	// Interpolate scale by speed
    uVar1 = FUN_80058f54((int)*(short *)(iVar4 + 0x1c),0x78,0x12c0);
    *(undefined2 *)(iVar4 + 0x1c) = uVar1;

	// Interpolate scale by speed
    uVar1 = FUN_80058f54((int)*(short *)(iVar4 + 0x1e),0x78,0x960);
    *(undefined2 *)(iVar4 + 0x1e) = uVar1;

	// Interpolate scale by speed
    uVar1 = FUN_80058f54((int)*(short *)(iVar4 + 0x20),0x78,0x12c0);
	*(undefined2 *)(iVar4 + 0x20) = uVar1;
	
    iVar4 = *(int *)(param_2 + 0x2d8) + 0x800;
    if (*(int *)(param_2 + 0x2d0) + 0x8000 <= *(int *)(param_2 + 0x2d8)) goto LAB_80068db0;
  }
  else
  {
	// cap to 800
    *piVar5 = 800;

    *(undefined *)(param_2 + 0x4fe) = 2;

	// interpolate until scale is [0, 24000, 0],
	// car is tall and thin

	// Interpolate scale by speed
    uVar1 = FUN_80058f54((int)*(short *)(iVar4 + 0x1c),600,0);
    *(undefined2 *)(iVar4 + 0x1c) = uVar1;

	// Interpolate scale by speed
    uVar1 = FUN_80058f54((int)*(short *)(iVar4 + 0x1e),0xc80,24000);
    *(undefined2 *)(iVar4 + 0x1e) = uVar1;

	// Interpolate scale by speed
    uVar1 = FUN_80058f54((int)*(short *)(iVar4 + 0x20),600,0);
    *(undefined2 *)(iVar4 + 0x20) = uVar1;

	// if scale shrinks to zero
    if (*(short *)(iVar4 + 0x1c) == 0)
	{
	  // if car is visible
      if ((*(uint *)(iVar4 + 0x28) & 0x80) == 0) 
	  {
		// position above kart
        local_18 = (undefined2)((uint)*(undefined4 *)(param_2 + 0x2d4) >> 8);
        local_16 = (short)((uint)*(undefined4 *)(param_2 + 0x588) >> 8) + 0x40;
        local_14 = (undefined2)((uint)*(undefined4 *)(param_2 + 0x2dc) >> 8);
        
		// FLARE_Init
		FUN_80025138(&local_18);
      }

	  // make invisible
      *(uint *)(iVar4 + 0x28) = *(uint *)(iVar4 + 0x28) | 0x80;

      goto LAB_80068db0;
    }

	iVar4 = *(int *)(param_2 + 0x584) + -0x1800;
    *(int *)(param_2 + 0x584) = iVar4;

    iVar4 = *(int *)(param_2 + 0x2d8) + iVar4;
  }
  *(int *)(param_2 + 0x2d8) = iVar4;
LAB_80068db0:

  // drift angle = ((drift angle + warp timer + 0x800) & 0xfff) - 0x800
  sVar2 = (*(short *)(param_2 + 0x3c6) + *(short *)piVar5 + 0x800U & 0xfff) - 0x800;
  *(short *)(param_2 + 0x3c6) = sVar2;
  
  // cameraRotY = ??? + kart angle + drift angle
  *(short *)(param_2 + 0x2ee) = *(short *)(param_2 + 0x3d4) + *(short *)(param_2 + 0x39a) + sVar2;

  // driver is warping
  *(uint *)(param_2 + 0x2c8) = *(uint *)(param_2 + 0x2c8) | 0x4000;
  return;
}


// VehStuckProc_Warp_Init
// param1 = thread, param2 = driver
void FUN_80068e04(undefined4 param_1,int param_2)

{
  int iVar1;

  // If you are not in a warp pad
  if (*(char *)(param_2 + 0x376) != '\n')
  {
    *(undefined4 *)(param_2 + 0x580) = 0x3c;
    *(undefined4 *)(param_2 + 0x584) = 0;
    *(undefined4 *)(param_2 + 0x588) = *(undefined4 *)(param_2 + 0x2d0);

	// OtherFX_Play
    FUN_80028468(0x97,1);

	// OtherFX_Stop1 (three sounds)
    FUN_80028808(*(undefined4 *)(param_2 + 0x304));
    *(undefined4 *)(param_2 + 0x304) = 0;
    FUN_80028808(*(undefined4 *)(param_2 + 0x308));
    *(undefined4 *)(param_2 + 0x308) = 0;
    FUN_80028808(*(undefined4 *)(param_2 + 0x300));
    *(undefined4 *)(param_2 + 0x300) = 0;

	// EngineAudio_Stop (driverID + engineID*4)
    FUN_80028b54((uint)*(byte *)(param_2 + 0x4a) +
                 *(int *)(&DAT_80086d90 +
                         (int)(short)(&DAT_80086e84)[*(byte *)(param_2 + 0x4a)] * 0x10) * 4 & 0xffff
                );

	// driver -> instSelf
	iVar1 = *(int *)(param_2 + 0x1c);

	// instance flags, now reflective
    *(uint *)(iVar1 + 0x28) = *(uint *)(iVar1 + 0x28) | 0x4000;

	// vertical line for split or reflection
    *(undefined2 *)(iVar1 + 0x56) = (short)((uint)*(undefined4 *)(param_2 + 0x2d0) >> 8);

	// CameraDC, freecam mode
    *(undefined2 *)(PTR_DAT_8008d2ac + (uint)*(byte *)(param_2 + 0x4a) * 0xdc + 0x1532) = 3;

    *(undefined4 *)(param_2 + 0x60) = 0x80062a2c; // OnAudio

	// eventually calls AddDustPuff
    *(undefined4 *)(param_2 + 100) = 0x80068be8;  // OnPhysAngular

	*(undefined4 *)(param_2 + 0x7c) = 0x8005ee34; // VehPhysForce_TranslateMatrix -- move position to instance matrix

    *(undefined4 *)(param_2 + 0x80) = 0x8005b178; // VehFrameProc_Driving

	// you are now in a warp pad
    *(undefined *)(param_2 + 0x376) = 10;

    *(undefined2 *)(param_2 + 0x38c) = 0;
    *(undefined2 *)(param_2 + 0x38e) = 0;

    *(undefined4 *)(param_2 + 0x54) = 0; // OnInit
    *(undefined4 *)(param_2 + 0x58) = 0; // OnUpdate
	*(undefined4 *)(param_2 + 0x5c) = 0; // OnPhysLinear -- disable input, timers, and effects

    *(undefined4 *)(param_2 + 0x68) = 0;
    *(undefined4 *)(param_2 + 0x6c) = 0; // COLL_StartSearch_NearPlayer
    *(undefined4 *)(param_2 + 0x70) = 0; // VehPhysForce_CollideDrivers
    *(undefined4 *)(param_2 + 0x74) = 0; // COLL_StartSearch_Player
    *(undefined4 *)(param_2 + 0x78) = 0; // cant move anymore

	// VehEmitter_DriverMain
    *(undefined4 *)(param_2 + 0x84) = 0x80059a18;

	// driver is warping
    *(uint *)(param_2 + 0x2c8) = *(uint *)(param_2 + 0x2c8) | 0x4000;
  }
  return;
}


// VehTalkMask_ThTick
void FUN_80068f90(int param_1)

{
  undefined *puVar1;
  undefined2 uVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;

  puVar1 = PTR_DAT_8008d2ac;

  // get object attached to thread
  iVar8 = *(int *)(param_1 + 0x30);

  // get instance attached to thread
  iVar7 = *(int *)(param_1 + 0x34);

  iVar4 = 0x2000;

  // if mask model is nullptr
  if (DAT_8008d0f0 == 0) {
    iVar4 = 0x1000;

	// Check if P1 is valid
    if (*(int *)(PTR_DAT_8008d2ac + 0x24ec) != 0)
	{
	  // VehPickupItem_MaskBoolGoodGuy
      uVar3 = FUN_80064be4();

	  // If you use Uka mask,
	  // uka model
      iVar4 = 0xe8;

	  // If you use Aku mask
      if ((uVar3 & 0xffff) != 0)
	  {
		// aku model
        iVar4 = 0xe4;
      }

	  // set instance's model pointer
      *(undefined4 *)(iVar7 + 0x18) = *(undefined4 *)(puVar1 + iVar4 + 0x2160);

      iVar4 = 0x1000;
    }
  }

  else
  {
	// set model of talking mask
    *(int *)(iVar7 + 0x18) = DAT_8008d0f0;
  }

  // max value in some SPU data
  DAT_8008d9f8 = DAT_8008d6f4;

  uVar2 = (undefined2)(*(short *)(iVar8 + 4) * iVar4 >> 0xc);

  // scale
  *(undefined2 *)(iVar7 + 0x20) = uVar2;
  *(undefined2 *)(iVar7 + 0x1e) = uVar2;
  *(undefined2 *)(iVar7 + 0x1c) = uVar2;

  // number of animFrames
  iVar8 = FUN_8005b0f4(iVar7,0);

  // multiply by 7
  iVar4 = DAT_8008d9f8 * 7;

  if (iVar4 < 0) {
    iVar4 = iVar4 + 0x3fff;
  }

  iVar4 = iVar4 >> 0xe;

  if (DAT_8008d9fc < iVar4) {
    DAT_8008d9fc = iVar4;
  }

  iVar6 = iVar4;
  if (iVar4 < 2) {
    iVar6 = 0;
  }
  if (iVar4 < 4)
  {
	// animFrame
    iVar5 = (int)*(short *)(iVar7 + 0x54);
  }

  else
  {
	// animFrame
	iVar5 = (int)*(short *)(iVar7 + 0x54);

	iVar4 = iVar5 - iVar6;

	if (iVar4 < 0) {
      iVar4 = -iVar4;
    }

    if (3 < iVar4)
	{
	  // animFrame
	  *(undefined2 *)(iVar7 + 0x54) = (short)iVar6;

      goto LAB_800690dc;
    }
  }

  // EngineSound_VolumeAdjust
  uVar2 = FUN_8002fc28(iVar6,iVar5,1);

  // animFrame
  *(undefined2 *)(iVar7 + 0x54) = uVar2;

LAB_800690dc:

  // animFrame
  iVar4 = (int)*(short *)(iVar7 + 0x54) - iVar6;

  if (iVar4 < 0) {
    iVar4 = -iVar4;
  }

  if (iVar4 < 6)
  {
	// EngineSound_VolumeAdjust
    uVar2 = FUN_8002fc28(iVar6,(int)*(short *)(iVar7 + 0x54),1);

	// animFrame
    *(undefined2 *)(iVar7 + 0x54) = uVar2;
  }
  else
  {
	// animFrame
    *(undefined2 *)(iVar7 + 0x54) = (short)iVar6;
  }

  // animation frame goes back and forth
  // 0x00: mouth close
  // 0x0C: mouth open

  // if frame is less than zero, set to zero
  if ((int)*(short *)(iVar7 + 0x54) < 0) {
    *(undefined2 *)(iVar7 + 0x54) = 0;
  }

  // if frame is positive
  else
  {
	// if animation frame goes beyond number of frames
    if (iVar8 + -1 < (int)*(short *)(iVar7 + 0x54))
	{
	  // set animation frame to last frame
      *(undefined2 *)(iVar7 + 0x54) = (short)(iVar8 + -1);
    }
  }

  // If mask should disappear
  if (DAT_8008da00 != '\0')
  {
	// dont need this variable anymore,
	// so set it from one to zero
    DAT_8008da00 = '\0';

	// 0x800 = this thread needs to be deleted
    *(uint *)(param_1 + 0x1c) = *(uint *)(param_1 + 0x1c) | 0x800;
  }
  return;
}


// VehTalkMask_Init
void FUN_80069178(void)

{
  int iVar1;

  // mask is now talking (I think)
  DAT_8008d65c = 1;

  // talking mask does not
  // need to go away
  DAT_8008da00 = 0;

  // DAT_8008d660
  // "head"

  // 0x39 = aku aku model pointer
  // it changes in FUN_80068f90

  // INSTANCE_BirthWithThread
  // 0x300 flag = SmallStackPool
  // 0xe = "aku aku" thread bucket
  // 0x6 = sizeof(struct MaskHint)
  iVar1 = FUN_800309a4(0x39,&DAT_8008d660,0x300,0xe,FUN_80068f90,6,0);

  // get thread from instance
  iVar1 = *(int *)(iVar1 + 0x6c);

  // set funcThDestroy to remove instance from instance pool
  *(undefined4 *)(iVar1 + 0x24) = 0x80041dfc;

  // object -> 4
  *(undefined2 *)(*(int *)(iVar1 + 0x30) + 4) = 0;
  
  return instance;
}


// VehTalkMask_PlayXA
void FUN_800691e4(undefined4 param_1,short param_2)

{
  uint uVar1;

  if (
		// If Player Structure pointer is not nullptr
		(*(int *)(PTR_DAT_8008d2ac + 0x24ec) != 0) &&
		(
			// VehPickupItem_MaskBoolGoodGuy
			uVar1 = FUN_80064be4(),

			// if player uses uka
			(uVar1 & 0xffff) == 0
		)
	  )
  {
	// if you use uka, increment parameter
    param_2 = param_2 + 0x1f;
  }

  // if you use aku, leave parameter alone

  // CDSYS_XAPlay(CDSYS_XA_TYPE_EXTRA, (int)param_2);
  FUN_8001cdb4(1,(int)param_2);

  return;
}

// VehTalkMask_boolNoXA
bool FUN_8006924c(void)

{
  return DAT_8008d708 == 0;
}

// VehTalkMask_End
void FUN_8006925c(void)

{
  // CDSYS_XAPauseRequest
  FUN_8001cf98();

  // sdata->boolIsMaskThreadAlive
  DAT_8008d65c = 0;

  // sdata->talkMask_boolDead
  DAT_8008da00 = 1;

  return;
}


// VehTurbo_ProcessBucket
void FUN_80069284(int param_1)

{
  undefined2 uVar1;
  undefined *puVar2;
  undefined *puVar3;
  int iVar4;
  undefined4 uVar5;
  int iVar6;
  int iVar7;
  int iVar8;

  puVar2 = PTR_DAT_8008d2ac;

  // if first thread is valid
  if (param_1 != 0)
  {
	// loop through all threads
    do
	{
      puVar3 = PTR_DAT_8008d2ac;

	  // get instance from thread
      iVar6 = *(int *)(param_1 + 0x34);

	  // get object from thread
      iVar7 = **(int **)(param_1 + 0x30);

	  // object -> driver -> instSelf
      iVar4 = *(int *)((*(int **)(param_1 + 0x30))[1] + 0x1c);

      iVar8 = 0;

	  // numPlyrCurrGame is not zero
      if (puVar2[0x1ca8] != '\0') 
	  {
		// each InstDrawPerPlayer
		// for iVar8 = 0; iVar8 < numPlyrCurrGame; iVar8++
        do
		{
		  // if pushBuffer does not exist ?
		  // judging by 0x28 being copied to 0xb8 ?
          if ((*(uint *)(iVar4 + 0xb8) & 0x100) == 0)
		  {
			// flags
            *(uint *)(iVar7 + 0xb8) =
                 *(uint *)(iVar7 + 0xb8) & (*(uint *)(iVar4 + 0xb8) | 0xffffffbf);
            *(uint *)(iVar6 + 0xb8) =
                 *(uint *)(iVar6 + 0xb8) & (*(uint *)(iVar4 + 0xb8) | 0xffffffbf);
				 
            uVar5 = *(undefined4 *)(iVar4 + 0xe4);
            *(undefined4 *)(iVar6 + 0xe4) = uVar5;
            *(undefined4 *)(iVar7 + 0xe4) = uVar5;
            uVar5 = *(undefined4 *)(iVar4 + 0xe8);
            *(undefined4 *)(iVar6 + 0xe8) = uVar5;
            *(undefined4 *)(iVar7 + 0xe8) = uVar5;
            uVar1 = *(undefined2 *)(iVar4 + 0xdc);
            *(undefined2 *)(iVar6 + 0xdc) = uVar1;
            *(undefined2 *)(iVar7 + 0xdc) = uVar1;
            uVar1 = *(undefined2 *)(iVar4 + 0xde);
            *(undefined2 *)(iVar6 + 0xde) = uVar1;
            *(undefined2 *)(iVar7 + 0xde) = uVar1;
          }
		  
		  // InstDrawPerPlayer
          iVar6 = iVar6 + 0x88;
          iVar7 = iVar7 + 0x88;
          iVar8 = iVar8 + 1;
          iVar4 = iVar4 + 0x88;
		  
        } while (iVar8 < (int)(uint)(byte)puVar3[0x1ca8]);
      }

	  // go to next thread

	  // thread = thread->sibling
      param_1 = *(int *)(param_1 + 0x10);

    } while (param_1 != 0);
  }
  return;
}


// VehTurbo_ThDestroy
void FUN_80069370(int param_1)

{
  int iVar1;
  undefined4 *puVar2;

  // thread -> object
  puVar2 = *(undefined4 **)(param_1 + 0x30);

  // get Driver object from Turbo object
  iVar1 = puVar2[1];

  // remove flags for boosting
  *(uint *)(iVar1 + 0x2c8) = *(uint *)(iVar1 + 0x2c8) & 0xfffffdff;

  // INSTANCE_Death
  FUN_80030aa8(*puVar2);
  FUN_80030aa8(*(undefined4 *)(param_1 + 0x34));

  return;
}


// VehTurbo_ThTick
void FUN_800693c8(int param_1)

{
  char cVar1;
  short sVar2;
  ushort uVar3;
  undefined *puVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  undefined4 uVar8;
  int *piVar9;
  int iVar10;
  int iVar11;
  int iVar12;

  // get object attached to thread
  piVar9 = *(int **)(param_1 + 0x30);

  // turbo -> driver
  iVar12 = piVar9[1];

  // get instance
  iVar11 = *(int *)(param_1 + 0x34);

  // driver -> instSelf
  iVar10 = *(int *)(iVar12 + 0x1c);

  do {
    if (
		(
			// if not burnt
			(*(short *)(iVar12 + 0x402) == 0) &&

			// if alpha of turbo is zero
			(*(short *)(iVar11 + 0x22) == 0)) &&

		// instance -> thread -> modelID == DYNAMIC_GHOST
		(*(short *)(*(int *)(iVar10 + 0x6c) + 0x44) != 0x4b)
	   )
	{
	  // cut driverInst transparency in half
      *(ushort *)(iVar10 + 0x22) = *(ushort *)(iVar10 + 0x22) >> 1;
    }

	// if instance is not split by water
    if ((*(uint *)(iVar10 + 0x28) & 0x2000) == 0)
	{
	  // instance flags
      *(uint *)(iVar11 + 0x28) = *(uint *)(iVar11 + 0x28) & 0xffffdfff;
      *(uint *)(*piVar9 + 0x28) = *(uint *)(*piVar9 + 0x28) & 0xffffdfff;
    }

	// if instance is split by water
	else
	{
	  // turbos are now split by water, set vertical split height
      *(uint *)(iVar11 + 0x28) = *(uint *)(iVar11 + 0x28) | 0x2000;
      *(undefined2 *)(iVar11 + 0x56) = *(undefined2 *)(iVar10 + 0x56);
	  *(uint *)(*piVar9 + 0x28) = *(uint *)(*piVar9 + 0x28) | 0x2000;
	  *(undefined2 *)(*piVar9 + 0x56) = *(undefined2 *)(iVar10 + 0x56);
    }

	// if driver instance is not reflective
	if ((*(uint *)(iVar10 + 0x28) & 0x4000) == 0)
	{
	  // remove reflection from turbo instances
      *(uint *)(iVar11 + 0x28) = *(uint *)(iVar11 + 0x28) & 0xffffbfff;
      *(uint *)(*piVar9 + 0x28) = *(uint *)(*piVar9 + 0x28) & 0xffffbfff;
    }

	// if driver instance is reflective
	else
	{
      // make turbo instances reflective
	  // copy reflection height axis to instance
	  *(uint *)(iVar11 + 0x28) = *(uint *)(iVar11 + 0x28) | 0x4000;
	  *(undefined2 *)(iVar11 + 0x56) = *(undefined2 *)(iVar10 + 0x56);
	  *(uint *)(*piVar9 + 0x28) = *(uint *)(*piVar9 + 0x28) | 0x4000;
	  *(undefined2 *)(*piVar9 + 0x56) = *(undefined2 *)(iVar10 + 0x56);
    }

	// matrix from instance
    gte_SetRotMatrix(iVar10 + 0x30);
    gte_SetTransMatrix(iVar10 + 0x30);

    iVar6 = (int)*(short *)((int)piVar9 + 10);
    iVar7 = iVar6;
    if (8 < iVar6) {
      iVar7 = 8;
    }
    if (iVar6 < 4) {
      iVar7 = 4;
    }
    
	// matrix of first turbo instance
	*(undefined2 *)(iVar11 + 0x30) = (short)(*(short *)(iVar10 + 0x30) * iVar7 >> 3);
    *(undefined2 *)(iVar11 + 0x32) = (short)(*(short *)(iVar10 + 0x32) * iVar7 >> 3);
    *(undefined2 *)(iVar11 + 0x34) = (short)(*(short *)(iVar10 + 0x34) * iVar7 >> 3);
    *(undefined2 *)(iVar11 + 0x36) = (short)(*(short *)(iVar10 + 0x36) * iVar7 >> 3);
    *(undefined2 *)(iVar11 + 0x38) = (short)(*(short *)(iVar10 + 0x38) * iVar7 >> 3);
    *(undefined2 *)(iVar11 + 0x3a) = (short)(*(short *)(iVar10 + 0x3a) * iVar7 >> 3);
    *(undefined2 *)(iVar11 + 0x3c) = (short)(*(short *)(iVar10 + 0x3c) * iVar7 >> 3);
    *(undefined2 *)(iVar11 + 0x3e) = (short)(*(short *)(iVar10 + 0x3e) * iVar7 >> 3);
    *(undefined2 *)(iVar11 + 0x40) = (short)(*(short *)(iVar10 + 0x40) * iVar7 >> 3);
	
	// driver -> instSelf
    iVar6 = *(int *)(iVar12 + 0x1c);
	
    gte_ldVXY0(*(short *)(iVar6 + 0x1c) * 9 >> 0xb & 0xffffU |
               (*(short *)(iVar6 + 0x1e) * 3 >> 8) << 0x10);
    gte_ldVZ0(*(short *)(iVar6 + 0x20) * -0x34 >> 0xc);
    gte_rt();
	
	// set translation vector
    gte_stlvl((VECTOR *)(iVar11 + 0x44));
	
	// matrix of second turbo instance, negate X axis
    *(undefined2 *)(*piVar9 + 0x30) = (short)(-(int)*(short *)(iVar10 + 0x30) * iVar7 >> 3);
    *(undefined2 *)(*piVar9 + 0x32) = (short)(*(short *)(iVar10 + 0x32) * iVar7 >> 3);
    *(undefined2 *)(*piVar9 + 0x34) = (short)(*(short *)(iVar10 + 0x34) * iVar7 >> 3);
    *(undefined2 *)(*piVar9 + 0x36) = (short)(-(int)*(short *)(iVar10 + 0x36) * iVar7 >> 3);
    *(undefined2 *)(*piVar9 + 0x38) = (short)(*(short *)(iVar10 + 0x38) * iVar7 >> 3);
    *(undefined2 *)(*piVar9 + 0x3a) = (short)(*(short *)(iVar10 + 0x3a) * iVar7 >> 3);
    *(undefined2 *)(*piVar9 + 0x3c) = (short)(-(int)*(short *)(iVar10 + 0x3c) * iVar7 >> 3);
    *(undefined2 *)(*piVar9 + 0x3e) = (short)(*(short *)(iVar10 + 0x3e) * iVar7 >> 3);
    *(undefined2 *)(*piVar9 + 0x40) = (short)(*(short *)(iVar10 + 0x40) * iVar7 >> 3);
	
	// driver -> instSelf
    iVar7 = *(int *)(iVar12 + 0x1c);
	
    gte_ldVXY0(*(short *)(iVar7 + 0x1c) * -0x12 >> 0xc & 0xffffU |
               (*(short *)(iVar7 + 0x1e) * 3 >> 8) << 0x10);
    gte_ldVZ0(*(short *)(iVar7 + 0x20) * -0x34 >> 0xc);
    gte_rt();
	
	// set translation vector
    gte_stlvl((VECTOR *)(*piVar9 + 0x44));

													// elapsed milliseconds per frame, ~32
    iVar7 = (uint)*(ushort *)((int)piVar9 + 0xe) - (uint)*(ushort *)(PTR_DAT_8008d2ac + 0x1d04);

    *(undefined2 *)((int)piVar9 + 0xe) = (short)iVar7;
    if (iVar7 * 0x10000 < 0) {
      *(undefined2 *)((int)piVar9 + 0xe) = 0;
    }

	if (*(short *)((int)piVar9 + 0xe) == 0)
	{
	  // make visible
      *(uint *)(iVar11 + 0x28) = *(uint *)(iVar11 + 0x28) & 0xffffff7f;
      *(uint *)(*piVar9 + 0x28) = *(uint *)(*piVar9 + 0x28) & 0xffffff7f;
    }

	if (*(ushort *)(iVar11 + 0x22) < 2500)
	{
	  // GAMEPAD_ShockFreq
      FUN_80026440(iVar12,4,4);
    }

    puVar4 = PTR_DAT_8008d2ac;

	// set new model pointer, one of seven
    *(undefined4 *)(iVar11 + 0x18) =
         *(undefined4 *)(PTR_DAT_8008d2ac + ((int)*(short *)(piVar9 + 2) + 0x2c) * 4 + 0x2160);

	// set new model pointer, one of seven
	*(undefined4 *)(*piVar9 + 0x18) =
         *(undefined4 *)(puVar4 + (((int)*(short *)(piVar9 + 2) + 3U & 7) + 0x2c) * 4 + 0x2160);

	// increment frame index
	sVar2 = *(short *)(piVar9 + 2);
    *(short *)(piVar9 + 2) = sVar2 + 1;

	// if gone past seven frames of fire
    if (7 < (short)(sVar2 + 1))
	{
	  // back to first frame of fire
      *(undefined2 *)(piVar9 + 2) = 0;
    }

    if ('\0' < *(char *)(piVar9 + 3)) {
      *(char *)(piVar9 + 3) = *(char *)(piVar9 + 3) + -1;
    }

	// instance -> thread -> modelIndex == "player" of any kind
    if (*(short *)(*(int *)(iVar10 + 0x6c) + 0x44) == 0x18) {
      iVar7 = 0x100 - (uint)(*(ushort *)(iVar11 + 0x22) >> 4);
      if (iVar7 < 0) {
        iVar7 = 0;
      }
      else {
        if (0x82 < iVar7) {
          iVar7 = 0x82;
        }
      }
      uVar5 = (uint)*(byte *)((int)piVar9 + 0xd) + 0x10;
      if ((int)uVar5 < 0) {
        uVar5 = 0;
      }
      else {
        if (0x80 < uVar5) {
          uVar5 = 0x80;
        }
      }

	  // distort
      uVar5 = uVar5 << 8;

	  // if echo is required
      if ((*(uint *)(iVar12 + 0x2c8) & 0x10000) != 0)
	  {
		// add echo
		uVar5 = uVar5 | 0x1000000;
      }

	  // driver audio
	  FUN_8002e690(iVar12 + 0x30c,0xe,iVar7 << 0x10 | uVar5 | 0x80);

      if (*(byte *)((int)piVar9 + 0xd) < 0xc0) {
        *(char *)((int)piVar9 + 0xd) = *(byte *)((int)piVar9 + 0xd) + 1;
      }
    }

    if (
			// if this is a ghost
			(*(short *)(*(int *)(iVar10 + 0x6c) + 0x44) == 0x4b) ||

			// kart state
			(((cVar1 = *(char *)(iVar12 + 0x376),

			// if not being mask grabbed, not crashing, not being warped
			cVar1 != '\x05' && (cVar1 != '\x01')) && (cVar1 != '\n')))
		)
	{
	  // if reserves are nearing zero
      if ((*(short *)(iVar12 + 0x3e2) < 0x10) || (*(char *)(piVar9 + 3) == '\0'))
	  {
		// get turboInst alpha
        uVar3 = *(ushort *)(iVar11 + 0x22);

		// if fully transparent, skip lines
        if (0xfff < uVar3) goto LAB_80069b50;

		if (*(char *)(piVar9 + 3) == '\0')
		{
		  // increase transparency
          *(short *)(iVar11 + 0x22) = uVar3 + 0x100;
          *(short *)(*piVar9 + 0x22) = *(short *)(*piVar9 + 0x22) + 0x100;
        }
        else
		{
		  // increase transparency
          *(short *)(iVar11 + 0x22) = uVar3 + 0x40;
          *(short *)(*piVar9 + 0x22) = *(short *)(*piVar9 + 0x22) + 0x40;
        }
      }
      else
	  {
		// if scale is big, skip lines
        if (0xfff < *(ushort *)(iVar11 + 0x22)) goto LAB_80069b50;
      }
    }

	// if not a ghost, and
	// kart state is mask grab, crashed, or warped
    else
	{
	  // restore backup of alpha
      *(undefined2 *)(iVar10 + 0x22) = *(undefined2 *)(iVar12 + 0x508);
LAB_80069b50:

	  // instance -> thread -> modelIndex == "player" of any kind
      if (*(short *)(*(int *)(iVar10 + 0x6c) + 0x44) == 0x18)
	  {
		// volume, distortion, left/right
        uVar8 = 0x8080;

		// if echo is required
		if ((*(uint *)(iVar12 + 0x2c8) & 0x10000) != 0)
		{
		  // add echo, volume, distortion, left/right
          uVar8 = 0x1008080;
        }

		// driver audio
        FUN_8002e690(iVar12 + 0x30c,0xffffffff,uVar8);
      }

	  // 0x800 = this thread needs to be deleted
      *(uint *)(param_1 + 0x1c) = *(uint *)(param_1 + 0x1c) | 0x800;
    }

	// this skips $RA backup/restore, faster than JR $RA
    FUN_80071694(param_1);

  } while( true );
}
