#include <common.h>

void DECOMP_PickupBots_Update(void)
{
	// handles which weapons bosses use
	char *meta;
	char i;
	u_char backupWumpa;
	char numPlyrCurrGame;
	short sVar2;
	u_short uVar3;
	int iVar4;
	uint uVar5;
	int iVar6;
	int iVar7;
	char bVar8;
	u_char uVar9;
	u_int uVar10;
	short sVar11;
	struct Driver *currDriver;
	struct Driver *nextDriver;
	struct GameTracker* gGT = sdata->gGT;

	// pointer to boss meta
	// sdata->bossWeaponMeta
	meta = (int *)0x8008d8e8;

	// If number of AIs is zero,			or		time on clock is less than 4b00
	if ((gGT->numBotsNextGame == 0) || (gGT->elapsedEventTime < 0x4b00))
	{
		if (-1 < gGT->gameMode1)
		{
			return;
		}

		// quit if event started less than 4800ms ago (4.8s)
		if (gGT->elapsedEventTime < 0x12c0)
		{
			return;
		}
	}

	// if this is NOT an unfinished boss race
	if ((gGT->gameMode1 & (ADVENTURE_BOSS | END_OF_RACE)) != ADVENTURE_BOSS)
	{
		// This whole block handles Arcade/Adv weapons
		// RNG for firing the weapons
		// RNG for choosing wumpa (change tnt/nitro)
		// RNG for which weaopn shoots (oxide)
		// etc

		for (i = 0; i < gGT->numPlyrCurrGame; i++)
		{
			// get the player structure of each human player
			currDriver = gGT.drivers[i];

			// if racer is not in first place
			if (currDriver->driverRank != 0)
			{
				// driver in front of the player
				nextDriver = gGT->driversInRaceOrder[currDriver->driverRank - 1];

				if (
					(
						(
							(
								// If this is an AI and not a human
								(nextDriver->actionsFlagSet & 0x100000) != 0) &&

							(
								// if AI is not blasted or spinning out
								(nextDriver->botFlags & 2) == 0)) &&
						(
							// if racer hasn't finished the race
							(nextDriver->actionsFlagSet & 0x2000000) == 0)) &&
					((
						(
							// If there is no AI weapon cooldown
							nextDriver->weaponCooldown == 0 &&

							// If you dont have a tnt on your head
							(nextDriver->instTntRecv == 0)
						) &&
						
						((
							// if there is no clock weapon in effect
							nextDriver->clockReceive == 0 &&
							(
								// driver1x - driver2x
								iVar6 = *(int *)(currDriver->instSelf->matrix.t[0]) -
										*(int *)(nextDriver->instSelf->matrix.t[0]),

								// driver1z - driver2z
								iVar7 = *(int *)(currDriver->instSelf->matrix.t[2]) -
										*(int *)(nextDriver->instSelf->matrix.t[2]),

								// check if distance between drivers is small
								(iVar6 * iVar6 + iVar7 * iVar7) - 0x90001U < 0x13affff
							)
						))
					 ))
					)
				{
					// Get random number
					iVar6 = MixRNG_Scramble();

					// Get remainder when divided by 200
					iVar6 = iVar6 % 200;

					// If RNG is 0, (1/200 chance)
					if (iVar6 == 0)
					{
						if (
							(*(char *)(nextDriver->matrix.t[0]) != 0) &&

							(
								// Get random number
								iVar6 = MixRNG_Scramble(),

								// 50% chance this will happen
								iVar6 % 100 < 0x32))
						{
							// Set number of wumpa to 10
							nextDriver->numWumpas = 10;
						}

						// if time on the clock is an even number
						if ((gGT->elapsedEventTime & 1) == 0)
						{
							// Set weapon to potion
							nextDriver->heldItemID = 4;

							// If this is human and not AI
							if ((currDriver->actionsFlagSet & 0x100000) == 0)
							{
								// Make driver talk
								Voiceline_RequestPlay(0xf, 
								data.characterIDs[nextDriver->driverID],
								data.characterIDs[currDriver->driverID]);
							}

							// potion
							uVar10 = 4;
						}

						// if time on the clock is an odd number
						else
						{
							// Set weapon to tnt/nitro
							nextDriver->heldItemID = 3;

							// If this is human and not AI
							if ((currDriver->actionsFlagSet & 0x100000) == 0)
							{
								// Make driver talk
								Voiceline_RequestPlay(0xf, (int)(short)data.characterIDs[nextDriver->driverID],
													  (int)(short)data.characterIDs[currDriver->driverID]);
							}

							// tnt/nitro
							uVar10 = 3;
						}

						// VehPickupItem_ShootNow (Arcade/Adv)
						VehPickupItem_ShootNow(nextDriver, uVar10, 0);

						// set wumpa to zero
						nextDriver->numWumpas = 0;

					LAB_800412a4:

						// Get random number
						uVar3 = MixRNG_Scramble();

						// weapon cooldown
						nextDriver->weaponCooldown = (uVar3 & 0xff) + 0xf0;
					}
					else
					{
						// If RNG is 1, (1/200 chance)
						if (iVar6 == 1)
						{
							// Set weapon to bomb
							nextDriver->heldItemID = (char)iVar6;

							// If this is human and not AI
							if ((currDriver->actionsFlagSet & 0x100000) == 0)
							{
								// Player / AI structure + 0x4a shows driver index (0-7)

								// Get character ID of two player/AI structures: iVar4 and iVar14

								sVar11 = data.characterIDs[nextDriver->driverID];
								sVar2 = data.characterIDs[currDriver->driverID];
								uVar10 = 10;
							LAB_8004128c:
								// Make driver talk
								Voiceline_RequestPlay(uVar10, (int)sVar11, (int)sVar2);
							}
						LAB_80041298:
							VehPickupItem_ShootNow(nextDriver, 2, 0);
							goto LAB_800412a4;
						}

						// If RNG is 2, (1/200 chance)
						if (iVar6 == 2)
						{
							// Set weapon to 2
							nextDriver->heldItemID = (char)iVar6;

							// if this is human and not AI
							if ((currDriver->actionsFlagSet & 0x100000) == 0)
							{

								// Player / AI structure + 0x4a shows driver index (0-7)

								// Get character ID of two player/AI structures: iVar4 and iVar14

								sVar11 = data.characterIDs[nextDriver->driverID];
								sVar2 = data.characterIDs[currDriver->driverID];
								uVar10 = 0xb;
								goto LAB_8004128c;
							}
							goto LAB_80041298;
						}
					}

					// You have no weapon
					nextDriver->heldItemID = 0xf;
				}
			}

			// If racer is in the top 3 places of the race (1st, 2nd, 3rd)
			if (currDriver->driverRank < 3)
			{
				// driver in the position behind player
				nextDriver = gGT->driversInRaceOrder[currDriver->driverRank + 1];
				if (
					(
						(
							(
								// If this is an AI, and not human
								((nextDriver->actionsFlagSet & 0x100000) != 0) &&

								// if AI is not blasted or spinning out
								((nextDriver->botFlags & 2) == 0)) &&

							// if racer hasn't finished the race
							((nextDriver->actionsFlagSet & 0x2000000) == 0)) &&
						((
							(
								// If there is no AI weapon cooldown
								nextDriver->weaponCooldown == 0 &&

								// If there is no TNT on your head
								(nextDriver->instTntRecv == 0)) &&
							((
								// If there is no clock weapon in effect
								nextDriver->clockReceive == 0 &&
								((
									// this driver's lap count less than number of laps in race,
									// (this is false if you finish race)
									currDriver->lapIndex < gGT->numLaps ||

									// distToFinish more than 16000
									(16000 < currDriver->distanceToFinish_curr))))))) &&
						(
							// driver1x - driver2x
							iVar6 = currDriver->instSelf->matrix.t[0] - nextDriver->instSelf->matrix.t[0],

							// driver1z - driver2z
							iVar7 = currDriver->instSelf->matrix.t[2] - nextDriver->instSelf->matrix.t[2],

							// check if distance between drivers is small
							(iVar6 * iVar6 + iVar7 * iVar7) - 0x90001U < 0x13affff)))
				{
					// Get random number
					iVar6 = MixRNG_Scramble();

					if (
						(
							// 2 in 800 chance (1 in 400)
							(iVar6 % 800 < 2) &&
							(
								// override weapon to missile
								uVar9 = 2,

								// if driver's lap is not last lap
								nextDriver->matrix.t[0] != gGT->numLaps - 1U)) ||
						(
							// override weapon to bomb
							uVar9 = 1,

							// 4 in 800 chance (1 in 200)
							iVar6 % 800 < 4))
					{
						// set weapon
						nextDriver->heldItemID = uVar9;

						// If this is an AI and not human
						if ((currDriver->actionsFlagSet & 0x100000) == 0)
						{
							// Make driver talk
							Voiceline_RequestPlay(0xb,
							data.characterIDs[nextDriver->driverID],
							data.characterIDs[currDriver->driverID]);
						}

						//  (Arcade/Adv) Missile
						VehPickupItem_ShootNow(nextDriver, 2, 0);

						// Get random number
						uVar3 = MixRNG_Scramble();

						// cooldown before next weapon
						nextDriver->weaponCooldown = (uVar3 & 0xff) + 0xf0;
					}

					// You have no weapon
					nextDriver->heldItemID = 0xf;
				}
			}
		}
	}

	// =============================

	// Everything beyond this line is for Boss weapons

	// =============================

	// pointer to player structure (P2 or boss)
	nextDriver = gGT->drivers[1];

	// pointer to player structure (P1)
	currDriver = gGT.drivers[0];

	if (
		(
			((nextDriver->botFlags & 2) != 0) ||

			// if racer finished this race
			((nextDriver->actionsFlagSet & 0x2000000) != 0)) ||
		((
			// if boss has tnt on their head
			nextDriver->instTntRecv != 0 ||
			((
				// victim of clock weapon
				nextDriver->clockReceive != 0 ||

				// if boss has not reached high speed
				(*(int *)(nextDriver + 0x5d4) < 0x1f41))))))
	{
		// some kind of RNG with 0xdeadc0ed
		uVar3 = RngDeadCoed(&bss);

		// new cooldown
		*(int *)0x8008d8e4 =

			// random [0 to 16] +
			(uVar3 & 0x10) +

			// min cooldown for boss
			*(short *)(meta + 4) + 0xc +

			// number of times you lost the event
			sdata->advProgress.timesLostBossRace[gGT->bossID] * 4;

		return;
	}

	// if this is the last weapon set (next is nullptr)
	if ((meta)[9] == 0)
	{
		if (
			// track progress of NEXT set
			// percentage of track length
			(gGT.level1.ptr_restart_points[(meta)[8]].distToFinish << 3))
		{
			uVar3 = 0xffff;
			if (
				(
					((meta)[2] == 0x66) ||
					((meta)[2] == 100)) &&
				(sdata->unk_8008d42C == 5))
			{
				uVar3 = (meta)[1];
			}
			meta = data.bossWeaponMetaPtr[0];

			// if levelID is not oxide station
			if (gGT->levelID != 0xd)
			{
				// set boss weapon meta to the one type it can be on this hub
				meta = data.bossWeaponMetaPtr[data.metaDataLEV[gGT->levelID].hubID];
			}
			if (uVar3 != 0xffff)
			{
				meta[1] = (char)uVar3;
			}
		}
	}

	// if not last weapon set
	else
	{
		// distToFinish less than...
		if (nextDriver->distanceToFinish_curr <

			// track progress of NEXT set
			// percentage of track length
			(gGT.level1.ptr_restart_points[(meta)[8]].distToFinish) << 3)
		{
			bVar8 = 0xff;
			if (
				(
					((meta)[2] == 0x66) ||
					(iVar4 = -0x10000, (meta)[2] == 100)) &&

				(iVar4 = -0x10000, sdata->unk_8008d42C == 5))
			{
				bVar8 = (meta)[1];
				iVar4 = (uint)bVar8 << 0x10;
			}

			// next set
			meta = (meta)[8];

			if (iVar4 >> 0x10 != -1)
			{
				(meta)[9] = bVar8;
			}
		}
	}

	// set new boss meta
	(meta)[0] = meta;

	if (meta[3] == 0)
	{
		// run this once per second
		if (sdata->unk_8008d428 == 0x1e)
		{
			if ((nextDriver->botFlags & 0x80) == 0)
			{
				if (*(short*)0x8008d42a == 0)
				{
					sVar11 = *(short *)(nextDriver + 0x5b8);
					if (sVar11 == 2)
						goto LAB_80040ba0;
					if (sVar11 == 1)
					{
						*(char *)(nextDriver + 0x627) = 0;
						sdata->unk_8008d428 = 0;
						*(short*)0x8008d42a = sVar11;
						nextDriver->botFlags |= 0x40;
					}
				}
				else
				{
					if (*(short *)(nextDriver + 0x5b8) == 0)
					{
					LAB_80040ba0:
						uVar5 = nextDriver->botFlags;
						*(char *)(nextDriver + 0x627) = 1;
					}
					else
					{
						if (*(short *)(nextDriver + 0x5b8) != 1)
							goto LAB_80040bf8;
						uVar5 = nextDriver->botFlags;
						*(char *)(nextDriver + 0x627) = 2;
						*(short*)0x8008d42a = 0;
					}
					sdata->unk_8008d428 = 0;
					nextDriver->botFlags = uVar5 | 0x40;
				}
			}
		}

		// count up
		else
		{
			if ((nextDriver->botFlags & 0x40) == 0)
			{
				sdata->unk_8008d428 += 1;
			}
		}
	}
LAB_80040bf8:

	// cooldown, cant shoot weapons till finished
	if (0 < *(int *)0x8008d8e4)
	{
		*(int *)0x8008d8e4 -= 1;
		return;
	}

	// some kind of RNG with 0xdeadc0ed
	uVar3 = RngDeadCoed(&bss);

	// new cooldown
	*(int *)0x8008d8e4 =

		// random [0 to 16] +
		(uVar3 & 0x10) +

		// min cooldown for boss
		*(short *)(meta + 4) + 0xc +

		// number of times you lost the event
		sdata->advProgress.timesLostBossRace[gGT->bossID] * 4;

	bVar8 = meta[2];
	uVar5 = bVar8;
	if (bVar8 == 100)
	{
		// weapon (tnt)
		uVar5 = 3;
	}
	else
	{
		if (bVar8 == 0x65)
		{
			// weapon (bomb)
			uVar5 = 1;
		}
		else
		{
			if (bVar8 == 0x66)
			{
				// weapon (potion)
				uVar5 = 4;
			}
			else
			{
				if (bVar8 == 0xf)
				{
					uVar5 = 0xffffffff;
				}
			}
		}
	}
	uVar3 = *(u_short *)(meta + 6);
	if ((uVar3 & 2) == 0)
	{
	LAB_80040d9c:
		sdata->unk_8008d42C = 0;
		sVar11 = sdata->unk_8008d42C;
	}
	else
	{
		sVar11 = sdata->unk_8008d42C + 1;
		if (sdata->unk_8008d42C < 5)
			goto LAB_80040da0;
		bVar8 = meta[2];
		if (bVar8 == 100)
		{
			// weapon (tnt)
			uVar5 = 3;

			if (meta[1] != 3)
			{
				meta[1] = 3;
				sdata->unk_8008d42C = 5;
				*(u_short *)(meta + 6) = uVar3 | 1;
				sVar11 = sdata->unk_8008d42C;
				goto LAB_80040da0;
			}
		}
		else
		{
			if (bVar8 == 0x65)
			{
				// weapon (bomb)
				uVar5 = 1;

				// swap each frame between juiced and not juiced

				// not juiced, then juiced up
				if ((uVar3 & 1) == 0)
				{
					*(u_short *)(meta + 6) = uVar3 | 1;
					sdata->unk_8008d42C = 5;

					// weapon (tnt)
					uVar5 = 3;

					sVar11 = sdata->unk_8008d42C;
					goto LAB_80040da0;
				}

				// already juiced, unjuice
				*(u_short *)(meta + 6) = uVar3 & 0xfffe;
				goto LAB_80040d9c;
			}
			sVar11 = sdata->unk_8008d42C;
			if (bVar8 != 0x66)
				goto LAB_80040da0;

			// weapon (potion)
			uVar5 = 4;

			if (meta[1] != 3)
			{
				meta[1] = 3;
				sdata->unk_8008d42C = 5;

				// give 10 wumpa
				*(u_short *)(meta + 6) |= 1;

				sVar11 = sdata->unk_8008d42C;
				goto LAB_80040da0;
			}
		}

		meta[1] = 2;
		sdata->unk_8008d42C = 0;

		// dont use 10 wumpa
		*(u_short *)(meta + 6) &= 0xfffe;

		sVar11 = sdata->unk_8008d42C;
	}
LAB_80040da0:

	sdata->unk_8008d42C = sVar11;
	bVar8 = meta[1];
	uVar3 = (u_short)(bVar8 == 2);
	uVar9 = 0;
	if (-1 < (int)(uVar5 << 0x10))
	{
		// backup numWumpa
		backupWumpa = nextDriver->numWumpas;

		if ((*(u_short *)(meta + 6) & 1) != 0)
		{
			// 10 wumpa
			uVar9 = 10;
		}

		// wumpa
		nextDriver->numWumpas = uVar9;

		// weaponID
		nextDriver->heldItemID = uVar5;

		if ((uVar5 - 3 & 0xffff) < 2)
		{
			// Player / AI structure + 0x4a shows driver index (0-7)

			// get the character ID of P1 and P2 (or boss)
			sVar11 = data.characterIDs[nextDriver->driverID];
			sVar2 = data.characterIDs[currDriver->driverID];

			uVar10 = 0xf;
		}
		else
		{
			// Player / AI structure + 0x4a shows driver index (0-7)

			uVar10 = 10;

			// get the character ID of P1 and P2 (or boss)
			sVar11 = data.characterIDs[nextDriver->driverID];
			sVar2 = data.characterIDs[currDriver->driverID];

			uVar3 = (u_short)(bVar8 == 2) | 2;
		}

		// Make driver talk
		Voiceline_RequestPlay(uVar10, sVar11, sVar2);

		// If weapon is bomb
		if (nextDriver->heldItemID == 1)
		{
			// Pinstripe or Oxide

			// VehPickupItem_ShootNow (boss)
			VehPickupItem_ShootNow(nextDriver, 2, uVar3);
		}

		else
		{
			sVar11 =uVar5;
			if (
				(
					// Papu or Oxide
					// If your weapon is potion
					(nextDriver->heldItemID == 4) &&

					(uVar3 == 1)) &&

				// If you are on oxide station
				(gGT->levelID == 0xd))
			{
				// VehPickupItem_ShootNow (boss)
				// Fire two potions (see oxide boss challenge)
				VehPickupItem_ShootNow(nextDriver, sVar11, 1);
				VehPickupItem_ShootNow(nextDriver,sVar11, 1);
			}
			else
			{
				// VehPickupItem_ShootNow (boss)
				VehPickupItem_ShootNow(nextDriver, sVar11, uVar3);

				if (// Roo, Joe, Oxide
					(
						// If your weapon is TNT or Nitro
						(nextDriver->heldItemID == 3) &&

						(meta[1] == 3)) &&

					(sdata->unk_8008d42C != 5))
				{
					sdata->unk_8008d42C = 5;
				}
			}
		}

		// You have no weapon
		nextDriver->heldItemID = 0xf;

		// Set number of wumpa fruit
		nextDriver->numWumpas = backupWumpa;
	}
	return;
}
 