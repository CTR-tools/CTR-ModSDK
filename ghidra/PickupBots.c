// PickupBots_Init
void FUN_80040850(void)

{
  int iVar1;

  // get hubID of level
  iVar1 = (uint)*(ushort *)(&DAT_80083a80 + *(int *)(PTR_DAT_8008d2ac + 0x1a10) * 0x18) << 0x10;

  // If Level ID == 13
  // If Level ID is Oxide Station
  if (*(int *)(PTR_DAT_8008d2ac + 0x1a10) == 0xd) {
    iVar1 = 0;
  }

  if (-1 < iVar1 >> 0x10)
  {
	// set pointer to boss weapon meta
    DAT_8008d8e8 = (&PTR_DAT_800859d0)[iVar1 >> 0x10];
  }

  return;
}


// PickupBots_Update
void FUN_800408b8(void)
{
  // handles which weapons bosses use

  undefined uVar1;
  short sVar2;
  ushort uVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  byte bVar8;
  undefined uVar9;
  undefined4 uVar10;
  short sVar11;
  byte *pbVar12;
  int iVar13;
  int iVar14;

  // pointer to boss meta
  pbVar12 = DAT_8008d8e8;

  // If number of AIs is zero,			or		time on clock is less than 4b00
  if ((PTR_DAT_8008d2ac[0x1cab] == '\0') || (*(int *)(PTR_DAT_8008d2ac + 0x1d10) < 0x4b00)) {
    if (-1 < *(int *)PTR_DAT_8008d2ac) {
      return;
    }

	// quit if event started less than 4800ms ago (4.8s)
    if (*(int *)(PTR_DAT_8008d2ac + 0x1d10) < 0x12c0) {
      return;
    }
  }

  // if this is NOT an unfinished boss race
  if ((*(uint *)PTR_DAT_8008d2ac & 0x80200000) != 0x80000000)
  {
	// This whole block handles Arcade/Adv weapons
	// RNG for firing the weapons
	// RNG for choosing wumpa (change tnt/nitro)
	// RNG for which weaopn shoots (oxide)
	// etc

    iVar13 = 0;

	// if numPlyrCurrGame is 0
    if (PTR_DAT_8008d2ac[0x1ca8] == '\0') {
      return;
    }

	// if numPlyrCurrGame is not zero

	// for(int iVar13 = 0; iVar13 < numPlyrCurrGame; iVar13++)
    do
	{
	  // get the player structure of each human player
      iVar14 = *(int *)(PTR_DAT_8008d2ac + iVar13 * 4 + 0x24ec);

	  // if racer is not in first place
      if ((int)*(short *)(iVar14 + 0x482) != 0)
	  {
		// driver in front of the player
        iVar4 = *(int *)(PTR_DAT_8008d2ac + ((int)*(short *)(iVar14 + 0x482) + -1) * 4 + 0x250c);

		if (
				(
					(
						(
							// If this is an AI and not a human
							(*(uint *)(iVar4 + 0x2c8) & 0x100000) != 0
						) &&

						(
							// if AI is not blasted or spinning out
							(*(uint *)(iVar4 + 0x5b0) & 2) == 0
						)
					) &&
					(
						//if racer hasn't finished the race
						(*(uint *)(iVar4 + 0x2c8) & 0x2000000) == 0
					)
				) &&
				(
					(
						(
							// If there is no AI weapon cooldown
							*(short *)(iVar4 + 0x624) == 0 &&

							// If you dont have a tnt on your head
							(*(int *)(iVar4 + 0x18) == 0)
						) &&
						(
							(
								// if there is no clock weapon in effect
								*(short *)(iVar4 + 0xc) == 0 &&
								(
									// driver1x - driver2x
									iVar6 = *(int *)(*(int *)(iVar14 + 0x1c) + 0x44) -
											*(int *)(*(int *)(iVar4 + 0x1c) + 0x44),

									// driver1z - driver2z
									iVar7 = *(int *)(*(int *)(iVar14 + 0x1c) + 0x4c) -
											*(int *)(*(int *)(iVar4 + 0x1c) + 0x4c),

									// check if distance between drivers is small
									(iVar6 * iVar6 + iVar7 * iVar7) - 0x90001U < 0x13affff
								)
							)

						)
					)
				)
			)
		{
		  // Get random number
          iVar6 = FUN_8003ea28();

		  // Get remainder when divided by 200
          iVar6 = iVar6 % 200;

		  // If RNG is 0, (1/200 chance)
		  if (iVar6 == 0)
		  {
            if (
					(*(char *)(iVar4 + 0x44) != '\0') &&

					(
						// Get random number
						iVar6 = FUN_8003ea28(),

						// 50% chance this will happen
						iVar6 % 100 < 0x32
					)
				)
			{
			  // Set number of wumpa to 10
              *(undefined *)(iVar4 + 0x30) = 10;
            }

			// if time on the clock is an even number
            if ((*(uint *)(PTR_DAT_8008d2ac + 0x1d10) & 1) == 0)
			{
			  // Set weapon to potion
              *(undefined *)(iVar4 + 0x36) = 4;

			  // If this is human and not AI
              if ((*(uint *)(iVar14 + 0x2c8) & 0x100000) == 0)
			  {
				// Make driver talk
                FUN_8002cbe8(0xf,(int)(short)(&DAT_80086e84)[*(byte *)(iVar4 + 0x4a)],
                             (int)(short)(&DAT_80086e84)[*(byte *)(iVar14 + 0x4a)]);
              }

			  // potion
              uVar10 = 4;
            }

			// if time on the clock is an odd number
            else
			{
			  // Set weapon to tnt/nitro
              *(undefined *)(iVar4 + 0x36) = 3;

			  // If this is human and not AI
              if ((*(uint *)(iVar14 + 0x2c8) & 0x100000) == 0)
			  {
				// Make driver talk
                FUN_8002cbe8(0xf,(int)(short)(&DAT_80086e84)[*(byte *)(iVar4 + 0x4a)],
                             (int)(short)(&DAT_80086e84)[*(byte *)(iVar14 + 0x4a)]);
              }

			  // tnt/nitro
              uVar10 = 3;
            }

			// VehPickupItem_ShootNow (Arcade/Adv)
            FUN_8006540c(iVar4,uVar10,0);

			// set wumpa to zero
            *(undefined *)(iVar4 + 0x30) = 0;

LAB_800412a4:

			// Get random number
            uVar3 = FUN_8003ea28();

			// weapon cooldown
            *(short *)(iVar4 + 0x624) = (uVar3 & 0xff) + 0xf0;
          }
          else
		  {
			// If RNG is 1, (1/200 chance)
            if (iVar6 == 1)
			{
			  // Set weapon to bomb
              *(undefined *)(iVar4 + 0x36) = (char)iVar6;

			  // If this is human and not AI
              if ((*(uint *)(iVar14 + 0x2c8) & 0x100000) == 0)
			  {
				// Player / AI structure + 0x4a shows driver index (0-7)

				// Get character ID of two player/AI structures: iVar4 and iVar14

                sVar11 = (&DAT_80086e84)[*(byte *)(iVar4 + 0x4a)];
                sVar2 = (&DAT_80086e84)[*(byte *)(iVar14 + 0x4a)];
                uVar10 = 10;
LAB_8004128c:
				// Make driver talk
                FUN_8002cbe8(uVar10,(int)sVar11,(int)sVar2);
              }
LAB_80041298:
			  // VehPickupItem_ShootNow (Arcade/Adv), Missile
              FUN_8006540c(iVar4,2,0);
              goto LAB_800412a4;
            }

			// If RNG is 2, (1/200 chance)
            if (iVar6 == 2)
			{
			  // Set weapon to 2
              *(undefined *)(iVar4 + 0x36) = (char)iVar6;

              // if this is human and not AI
              if ((*(uint *)(iVar14 + 0x2c8) & 0x100000) == 0)
			  {

				// Player / AI structure + 0x4a shows driver index (0-7)

				// Get character ID of two player/AI structures: iVar4 and iVar14

                sVar11 = (&DAT_80086e84)[*(byte *)(iVar4 + 0x4a)];
                sVar2 = (&DAT_80086e84)[*(byte *)(iVar14 + 0x4a)];
                uVar10 = 0xb;
                goto LAB_8004128c;
              }
              goto LAB_80041298;
            }
          }

		  // You have no weapon
          *(undefined *)(iVar4 + 0x36) = 0xf;
        }
      }

	  // If racer is in the top 3 places of the race (1st, 2nd, 3rd)
      if ((int)*(short *)(iVar14 + 0x482) < 3)
	  {
		// driver in the position behind player
        iVar4 = *(int *)(PTR_DAT_8008d2ac + ((int)*(short *)(iVar14 + 0x482) + 1) * 4 + 0x250c);

        if (
				(
					(
						(
							// If this is an AI, and not human
							((*(uint *)(iVar4 + 0x2c8) & 0x100000) != 0) &&

							// if AI is not blasted or spinning out
							((*(uint *)(iVar4 + 0x5b0) & 2) == 0)
						) &&

						//if racer hasn't finished the race
						((*(uint *)(iVar4 + 0x2c8) & 0x2000000) == 0)
					) &&
					(
						(
							(
								// If there is no AI weapon cooldown
								*(short *)(iVar4 + 0x624) == 0 &&

								// If there is no TNT on your head
								(*(int *)(iVar4 + 0x18) == 0)
							) &&
							(
								(
									// If there is no clock weapon in effect
									*(short *)(iVar4 + 0xc) == 0 &&
									(
										(
											// this driver's lap count less than number of laps in race,
											// (this is false if you finish race)
											(int)(uint)*(byte *)(iVar14 + 0x44) < (int)(char)PTR_DAT_8008d2ac[0x1d33] ||

											// distToFinish more than 16000
											(16000 < *(int *)(iVar14 + 0x488))
										)
									)
								)
							)
						)
					) &&
					(
						// driver1x - driver2x
						iVar6 = *(int *)(*(int *)(iVar14 + 0x1c) + 0x44) -
								*(int *)(*(int *)(iVar4 + 0x1c) + 0x44),

						// driver1z - driver2z
						iVar7 = *(int *)(*(int *)(iVar14 + 0x1c) + 0x4c) -
								*(int *)(*(int *)(iVar4 + 0x1c) + 0x4c),

						// check if distance between drivers is small
						(iVar6 * iVar6 + iVar7 * iVar7) - 0x90001U < 0x13affff
					)
				)
			)
		{
		  // Get random number
          iVar6 = FUN_8003ea28();

		  if (
				(
					// 2 in 800 chance (1 in 400)
					(iVar6 % 800 < 2) &&
					(
						// override weapon to missile
						uVar9 = 2,

						// if driver's lap is not last lap
						(uint)*(byte *)(iVar4 + 0x44) != (int)(char)PTR_DAT_8008d2ac[0x1d33] - 1U
					)
				) ||
				(
					// override weapon to bomb
					uVar9 = 1,

					// 4 in 800 chance (1 in 200)
					iVar6 % 800 < 4
				)
			 )
		  {
			// set weapon
            *(undefined *)(iVar4 + 0x36) = uVar9;

			// If this is an AI and not human
            if ((*(uint *)(iVar14 + 0x2c8) & 0x100000) == 0)
			{
			  // Make driver talk
              FUN_8002cbe8(0xb,(int)(short)(&DAT_80086e84)[*(byte *)(iVar4 + 0x4a)],
                           (int)(short)(&DAT_80086e84)[*(byte *)(iVar14 + 0x4a)]);
            }

			// VehPickupItem_ShootNow (Arcade/Adv) Missile
            FUN_8006540c(iVar4,2,0);

			// Get random number
            uVar3 = FUN_8003ea28();

			// cooldown before next weapon
            *(short *)(iVar4 + 0x624) = (uVar3 & 0xff) + 0xf0;
          }

		  // You have no weapon
          *(undefined *)(iVar4 + 0x36) = 0xf;
        }
      }

      // increment loop counter
      iVar13 = iVar13 + 1;

	  // for(int iVar13 = 0; iVar13 < numPlyrCurrGame; iVar13++)
      if ((int)(uint)(byte)PTR_DAT_8008d2ac[0x1ca8] <= iVar13)
	  {
		// when the loop is finished, quit the function
        return;
      }
    } while( true );
  }

  // =============================

  // Everything beyond this line is for Boss weapons

  // =============================

  // pointer to player structure (P2 or boss)
  iVar13 = *(int *)(PTR_DAT_8008d2ac + 0x24f0);

  // pointer to player structure (P1)
  iVar14 = *(int *)(PTR_DAT_8008d2ac + 0x24ec);

  if (
		(
			((*(uint *)(iVar13 + 0x5b0) & 2) != 0) ||

			//if racer finished this race
			((*(uint *)(iVar13 + 0x2c8) & 0x2000000) != 0)
		) ||
		(
			(
				// if boss has tnt on their head
				*(int *)(iVar13 + 0x18) != 0 ||
				(
					(
						// victim of clock weapon
						*(short *)(iVar13 + 0xc) != 0 ||

						// if boss has not reached high speed
						(*(int *)(iVar13 + 0x5d4) < 0x1f41)
					)
				)
			)
		)
	)
  {
	// some kind of RNG with 0xdeadc0ed
    uVar3 = FUN_8006c684(&DAT_8008d668);

	// new cooldown
    DAT_8008d8e4 =

		// random [0 to 16] +
		(uVar3 & 0x10) +

		// min cooldown for boss
		*(short *)(pbVar12 + 4) + 0xc +

			// number of times you lost the event
			(short)(char)(&DAT_8008fbeb)[*(int *)(PTR_DAT_8008d2ac + 0x1eb8)] * 4;

    return;
  }

  // if this is the last weapon set (next is nullptr)
  if (DAT_8008d8e8[9] == 0) 
  {
    if (
		// track progress of THIS set
		(int)((uint)*(ushort *)
        ((uint)*DAT_8008d8e8 * 0xc +
        
		// plus percentage of track length
		*(int *)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0x14c) + 6) << 3) <
		
		// distToFinish
        *(int *)(iVar13 + 0x488))
	{
      uVar3 = 0xffff;
      if (
			(
				(DAT_8008d8e8[2] == 0x66) || 
				(DAT_8008d8e8[2] == 100)
			) && 
			(DAT_8008d42c == 5)
		  ) 
	  {
        uVar3 = (ushort)DAT_8008d8e8[1];
      }
      pbVar12 = PTR_DAT_800859d0;

	  // if levelID is not oxide station
      if (*(int *)(PTR_DAT_8008d2ac + 0x1a10) != 0xd)
	  {
		// set boss weapon meta to the one type it can be on this hub
        pbVar12 = (&PTR_DAT_800859d0)
                  [*(short *)(&DAT_80083a80 + *(int *)(PTR_DAT_8008d2ac + 0x1a10) * 0x18)];
      }
      if (uVar3 != 0xffff) {
        pbVar12[1] = (byte)uVar3;
      }
    }
  }
  
  // if not last weapon set
  else
  {
	// distToFinish less than...
    if (*(int *)(iVar13 + 0x488) <
	
		// track progress of NEXT set
        (int)((uint)*(ushort *)			 
        ((uint)DAT_8008d8e8[8] * 0xc +
        
		// percentage of track length
		*(int *)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0x14c) + 6) << 3)) 
	{
      bVar8 = 0xff;
      if (
			(
				(DAT_8008d8e8[2] == 0x66) || 
				(iVar4 = -0x10000, DAT_8008d8e8[2] == 100)
			) &&
         
			(iVar4 = -0x10000, DAT_8008d42c == 5)
		) 
	  {
        bVar8 = DAT_8008d8e8[1];
        iVar4 = (uint)bVar8 << 0x10;
      }
	  
	  // next set
      pbVar12 = DAT_8008d8e8 + 8;
	  
      if (iVar4 >> 0x10 != -1) {
        DAT_8008d8e8[9] = bVar8;
      }
    }
  }

  // set new boss meta
  DAT_8008d8e8 = pbVar12;

  if (pbVar12[3] == 0) 
  {
	// run this once per second
    if (DAT_8008d428 == 0x1e) {
      if ((*(uint *)(iVar13 + 0x5b0) & 0x80) == 0) {
        if (DAT_8008d42a == 0) {
          sVar11 = *(short *)(iVar13 + 0x5b8);
          if (sVar11 == 2) goto LAB_80040ba0;
          if (sVar11 == 1) {
            *(undefined *)(iVar13 + 0x627) = 0;
            DAT_8008d428 = 0;
            DAT_8008d42a = sVar11;
            *(uint *)(iVar13 + 0x5b0) = *(uint *)(iVar13 + 0x5b0) | 0x40;
          }
        }
        else {
          if (*(short *)(iVar13 + 0x5b8) == 0) {
LAB_80040ba0:
            uVar5 = *(uint *)(iVar13 + 0x5b0);
            *(undefined *)(iVar13 + 0x627) = 1;
          }
          else {
            if (*(short *)(iVar13 + 0x5b8) != 1) goto LAB_80040bf8;
            uVar5 = *(uint *)(iVar13 + 0x5b0);
            *(undefined *)(iVar13 + 0x627) = 2;
            DAT_8008d42a = 0;
          }
          DAT_8008d428 = 0;
          *(uint *)(iVar13 + 0x5b0) = uVar5 | 0x40;
        }
      }
    }
    
	// count up
	else {
      if ((*(uint *)(iVar13 + 0x5b0) & 0x40) == 0) {
        DAT_8008d428 = DAT_8008d428 + 1;
      }
    }
  }
LAB_80040bf8:

  // cooldown, cant shoot weapons till finished
  if (0 < DAT_8008d8e4) {
    DAT_8008d8e4 = DAT_8008d8e4 + -1;
    return;
  }

  // some kind of RNG with 0xdeadc0ed
  uVar3 = FUN_8006c684(&DAT_8008d668);

  // new cooldown
  DAT_8008d8e4 =

	// random [0 to 16] +
	(uVar3 & 0x10) +

	// min cooldown for boss
	*(short *)(pbVar12 + 4) + 0xc +

		// number of times you lost the event
		(short)(char)(&DAT_8008fbeb)[*(int *)(PTR_DAT_8008d2ac + 0x1eb8)] * 4;

  bVar8 = pbVar12[2];
  uVar5 = (uint)bVar8;
  if (bVar8 == 100) 
  {
	// weapon (tnt)
    uVar5 = 3;
  }
  else {
    if (bVar8 == 0x65) 
	{
	  // weapon (bomb)
      uVar5 = 1;
    }
    else {
      if (bVar8 == 0x66) 
	  {
		// weapon (potion)
        uVar5 = 4;
      }
      else {
        if (bVar8 == 0xf) {
          uVar5 = 0xffffffff;
        }
      }
    }
  }
  uVar3 = *(ushort *)(pbVar12 + 6);
  if ((uVar3 & 2) == 0) {
LAB_80040d9c:
    DAT_8008d42c = 0;
    sVar11 = DAT_8008d42c;
  }
  else {
    sVar11 = DAT_8008d42c + 1;
    if (DAT_8008d42c < 5) goto LAB_80040da0;
    bVar8 = pbVar12[2];
    if (bVar8 == 100) 
	{
	  // weapon (tnt)
      uVar5 = 3;
	  
      if (pbVar12[1] != 3) {
        pbVar12[1] = 3;
        DAT_8008d42c = 5;
        *(ushort *)(pbVar12 + 6) = uVar3 | 1;
        sVar11 = DAT_8008d42c;
        goto LAB_80040da0;
      }
    }
    else {
      if (bVar8 == 0x65) 
	  {
		// weapon (bomb)
        uVar5 = 1;
		
		// swap each frame between juiced and not juiced
        
		
		// not juiced, then juiced up
		if ((uVar3 & 1) == 0) 
		{
          *(ushort *)(pbVar12 + 6) = uVar3 | 1;
          DAT_8008d42c = 5;
		  
		  // weapon (tnt)
          uVar5 = 3;
          
		  sVar11 = DAT_8008d42c;
          goto LAB_80040da0;
        }
        
		// already juiced, unjuice
		*(ushort *)(pbVar12 + 6) = uVar3 & 0xfffe;
        goto LAB_80040d9c;
      }
      sVar11 = DAT_8008d42c;
      if (bVar8 != 0x66) goto LAB_80040da0;
	  
	  // weapon (potion)
      uVar5 = 4;
      
	  if (pbVar12[1] != 3) {
        pbVar12[1] = 3;
        DAT_8008d42c = 5;
        
		// give 10 wumpa
		*(ushort *)(pbVar12 + 6) = *(ushort *)(pbVar12 + 6) | 1;
        
		sVar11 = DAT_8008d42c;
        goto LAB_80040da0;
      }
    }
	
    pbVar12[1] = 2;
    DAT_8008d42c = 0;
    
	// dont use 10 wumpa
	*(ushort *)(pbVar12 + 6) = *(ushort *)(pbVar12 + 6) & 0xfffe;
    
	sVar11 = DAT_8008d42c;
  }
  
LAB_80040da0:
  DAT_8008d42c = sVar11;
  bVar8 = pbVar12[1];
  uVar3 = (ushort)(bVar8 == 2);
  uVar9 = 0;
  if (-1 < (int)(uVar5 << 0x10)) 
  {
	// backup numWumpa
    uVar1 = *(undefined *)(iVar13 + 0x30);
    
	if ((*(ushort *)(pbVar12 + 6) & 1) != 0) 
	{
	  // 10 wumpa
      uVar9 = 10;
    }
	
	// wumpa
    *(undefined *)(iVar13 + 0x30) = uVar9;
    
	// weaponID
	*(undefined *)(iVar13 + 0x36) = (char)uVar5;
    
	if ((uVar5 - 3 & 0xffff) < 2)
	{
	  // Player / AI structure + 0x4a shows driver index (0-7)

	  // get the character ID of P1 and P2 (or boss)
      sVar11 = (&DAT_80086e84)[*(byte *)(iVar13 + 0x4a)];
      sVar2 = (&DAT_80086e84)[*(byte *)(iVar14 + 0x4a)];

      uVar10 = 0xf;
    }
    else
	{
	  // Player / AI structure + 0x4a shows driver index (0-7)

      uVar10 = 10;

	  // get the character ID of P1 and P2 (or boss)
      sVar11 = (&DAT_80086e84)[*(byte *)(iVar13 + 0x4a)];
      sVar2 = (&DAT_80086e84)[*(byte *)(iVar14 + 0x4a)];

      uVar3 = (ushort)(bVar8 == 2) | 2;
    }

	// Make driver talk
    FUN_8002cbe8(uVar10,(int)sVar11,(int)sVar2);

	// If weapon is bomb
	if (*(char *)(iVar13 + 0x36) == '\x01')
	{
	  // Pinstripe or Oxide

	  // VehPickupItem_ShootNow (boss)
      FUN_8006540c(iVar13,2,(int)(short)uVar3);
    }

	else
	{
      sVar11 = (short)uVar5;
      if (

			(
				// Papu or Oxide

				// If your weapon is potion
				(*(char *)(iVar13 + 0x36) == '\x04') &&

				(uVar3 == 1)
			) &&

			// If you are on oxide station
			(*(int *)(PTR_DAT_8008d2ac + 0x1a10) == 0xd)
		 )
	  {
		// VehPickupItem_ShootNow (boss)
		// Fire two potions (see oxide boss challenge)
        FUN_8006540c(iVar13,(int)sVar11,1);
        FUN_8006540c(iVar13,(int)sVar11,1);
      }
      else
	  {
		// VehPickupItem_ShootNow (boss)
        FUN_8006540c(iVar13,(int)sVar11,(int)(short)uVar3);

		if (
				// Roo, Joe, Oxide

				(
					// If your weapon is TNT or Nitro
					(*(char *)(iVar13 + 0x36) == '\x03') &&

					(pbVar12[1] == 3)
				) &&

				(DAT_8008d42c != 5)
			)
		{
          DAT_8008d42c = 5;
        }
      }
    }

	// You have no weapon
    *(undefined *)(iVar13 + 0x36) = 0xf;

	// Set number of wumpa fruit
    *(undefined *)(iVar13 + 0x30) = uVar1;
  }
  return;
}
