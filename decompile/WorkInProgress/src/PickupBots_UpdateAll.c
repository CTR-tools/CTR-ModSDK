#include <common.h>

void DECOMP_PickupBots_Update(void)
{
	// handles which weapons bosses use
	char i;
	u_char backupWumpa;
	u_char weaponID;
	u_char enemyID;
	u_char playerID;
	char numPlyrCurrGame;
	u_short uVar3;
	int iVar4;
	uint uVar5;
	int iVar6;
	int iVar7;
	char bVar8;
	u_char uVar9;
	u_int voiceID;
	short sVar11;
	struct Driver *thisDriver;
	struct Driver *botDriver;
	struct GameTracker* gGT = sdata->gGT;

	// pointer to boss meta
	struct MetaDataBOSS* bossMeta = sdata->ptrBossMeta;

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
			thisDriver = gGT.drivers[i];

			// if racer is not in first place
			if (thisDriver->driverRank != 0)
			{
				// driver in front of the player
				botDriver = gGT->driversInRaceOrder[thisDriver->driverRank - 1];

				if (
					(
						(
							(
								// If this is an AI and not a human
								(botDriver->actionsFlagSet & 0x100000) != 0) &&

							(
								// if AI is not blasted or spinning out
								(botDriver->botFlags & 2) == 0)) &&
						(
							// if racer hasn't finished the race
							(botDriver->actionsFlagSet & 0x2000000) == 0)) &&
					((
						(
							// If there is no AI weapon cooldown
							botDriver->weaponCooldown == 0 &&

							// If you dont have a tnt on your head
							(botDriver->instTntRecv == 0)
						) &&
						
						((
							// if there is no clock weapon in effect
							botDriver->clockReceive == 0 &&
							(
								// driver1x - driver2x
								iVar6 = *(int *)(thisDriver->instSelf->matrix.t[0]) -
										*(int *)(botDriver->instSelf->matrix.t[0]),

								// driver1z - driver2z
								iVar7 = *(int *)(thisDriver->instSelf->matrix.t[2]) -
										*(int *)(botDriver->instSelf->matrix.t[2]),

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
							(*(char *)(botDriver->matrix.t[0]) != 0) &&

							(
								// Get random number
								iVar6 = MixRNG_Scramble(),

								// 50% chance this will happen
								iVar6 % 100 < 0x32))
						{
							// Set number of wumpa to 10
							botDriver->numWumpas = 10;
						}

						// if time on the clock is an even number
						if ((gGT->elapsedEventTime & 1) == 0)
						{
							// Set weapon to potion
							botDriver->heldItemID = 4;

							// If this is human and not AI
							if ((thisDriver->actionsFlagSet & 0x100000) == 0)
							{
								// Make driver talk
								Voiceline_RequestPlay(0xf, 
								data.characterIDs[botDriver->driverID],
								data.characterIDs[thisDriver->driverID]);
							}

							// potion
							weaponID = 4;
						}

						// if time on the clock is an odd number
						else
						{
							// Set weapon to tnt/nitro
							botDriver->heldItemID = 3;

							// If this is human and not AI
							if ((thisDriver->actionsFlagSet & 0x100000) == 0)
							{
								// Make driver talk
								Voiceline_RequestPlay(0xf, (int)(short)data.characterIDs[botDriver->driverID],
													  (int)(short)data.characterIDs[thisDriver->driverID]);
							}

							// tnt/nitro
							weaponID = 3;
						}

						// VehPickupItem_ShootNow (Arcade/Adv)
						VehPickupItem_ShootNow(botDriver, weaponID, 0);

						// set wumpa to zero
						botDriver->numWumpas = 0;

					LAB_800412a4:

						// Get random number
						uVar3 = MixRNG_Scramble();

						// weapon cooldown
						botDriver->weaponCooldown = (uVar3 & 0xff) + 0xf0;
					}
					else
					{
						// If RNG is 1, (1/200 chance)
						if (iVar6 == 1)
						{
							// Set weapon to bomb
							botDriver->heldItemID = (char)iVar6;

							// If this is human and not AI
							if ((thisDriver->actionsFlagSet & 0x100000) == 0)
							{
								// Player / AI structure + 0x4a shows driver index (0-7)

								// Get character ID of two player/AI structures: iVar4 and iVar14

								enemyID = data.characterIDs[botDriver->driverID];
								playerID = data.characterIDs[thisDriver->driverID];
								voiceID = 10;
							LAB_8004128c:
								// Make driver talk
								Voiceline_RequestPlay(voiceID, enemyID, playerID);
							}
						LAB_80041298:
							VehPickupItem_ShootNow(botDriver, 2, 0);
							goto LAB_800412a4;
						}

						// If RNG is 2, (1/200 chance)
						if (iVar6 == 2)
						{
							// Set weapon to 2
							botDriver->heldItemID = (char)iVar6;

							// if this is human and not AI
							if ((thisDriver->actionsFlagSet & 0x100000) == 0)
							{

								// Player / AI structure + 0x4a shows driver index (0-7)

								// Get character ID of two player/AI structures: iVar4 and iVar14

								enemyID = data.characterIDs[botDriver->driverID];
								playerID = data.characterIDs[thisDriver->driverID];
								voiceID = 11;
								goto LAB_8004128c;
							}
							goto LAB_80041298;
						}
					}

					// You have no weapon
					botDriver->heldItemID = 0xf;
				}
			}

			// If racer is in the top 3 places of the race (1st, 2nd, 3rd)
			if (thisDriver->driverRank < 3)
			{
				// driver in the position behind player
				botDriver = gGT->driversInRaceOrder[thisDriver->driverRank + 1];
				if (
					(
						(
							(
								// If this is an AI, and not human
								((botDriver->actionsFlagSet & 0x100000) != 0) &&

								// if AI is not blasted or spinning out
								((botDriver->botFlags & 2) == 0)) &&

							// if racer hasn't finished the race
							((botDriver->actionsFlagSet & 0x2000000) == 0)) &&
						((
							(
								// If there is no AI weapon cooldown
								botDriver->weaponCooldown == 0 &&

								// If there is no TNT on your head
								(botDriver->instTntRecv == 0)) &&
							((
								// If there is no clock weapon in effect
								botDriver->clockReceive == 0 &&
								((
									// this driver's lap count less than number of laps in race,
									// (this is false if you finish race)
									thisDriver->lapIndex < gGT->numLaps ||

									// distToFinish more than 16000
									(16000 < thisDriver->distanceToFinish_curr))))))) &&
						(
							// driver1x - driver2x
							iVar6 = thisDriver->instSelf->matrix.t[0] - botDriver->instSelf->matrix.t[0],

							// driver1z - driver2z
							iVar7 = thisDriver->instSelf->matrix.t[2] - botDriver->instSelf->matrix.t[2],

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
								botDriver->matrix.t[0] != gGT->numLaps - 1U)) ||
						(
							// override weapon to bomb
							uVar9 = 1,

							// 4 in 800 chance (1 in 200)
							iVar6 % 800 < 4))
					{
						// set weapon
						botDriver->heldItemID = uVar9;

						// If this is an AI and not human
						if ((thisDriver->actionsFlagSet & 0x100000) == 0)
						{
							// Make driver talk
							Voiceline_RequestPlay(0xb,
							data.characterIDs[botDriver->driverID],
							data.characterIDs[thisDriver->driverID]);
						}

						//  (Arcade/Adv) Missile
						VehPickupItem_ShootNow(botDriver, 2, 0);

						// Get random number
						uVar3 = MixRNG_Scramble();

						// cooldown before next weapon
						botDriver->weaponCooldown = (uVar3 & 0xff) + 0xf0;
					}

					// You have no weapon
					botDriver->heldItemID = 0xf;
				}
			}
		}
	}

	// =============================

	// Everything beyond this line is for Boss weapons

	// =============================

	// pointer to player structure (P2 or boss)
	botDriver = gGT->drivers[1];

	// pointer to player structure (P1)
	thisDriver = gGT.drivers[0];

	if (
		(
			((botDriver->botFlags & 2) != 0) ||

			// if racer finished this race
			((botDriver->actionsFlagSet & 0x2000000) != 0)) ||
		((
			// if boss has tnt on their head
			botDriver->instTntRecv != 0 ||
			((
				// victim of clock weapon
				botDriver->clockReceive != 0 ||

				// if boss has not reached high speed
				(*(int *)(botDriver + 0x5d4) < 0x1f41))))))
	{
		// new cooldown
		sdata->bossCooldown =

			// random [0 to 16] +
			(RngDeadCoed(&bss) & 0x10) +

			// min cooldown for boss
			bossMeta->weaponCooldown + 12 +

			// number of times you lost the event
			sdata->advProgress.timesLostBossRace[gGT->bossID];

		return;
	}

	// if this is the last weapon set (next is nullptr)
	if (((struct MetaDataBOSS*)(int)bossMeta + sizeof(struct MetaDataBOSS))->throwFlag == NULL)
	{
		if (
			// track progress of NEXT set
			// percentage of track length
			(gGT.level1.ptr_restart_points[((struct MetaDataBOSS*)(int)bossMeta + sizeof(struct MetaDataBOSS))->trackCheckpoint].distToFinish << 3))
		{
			uVar3 = 0xffff;
			if (
				(
					((bossMeta)[2] == 0x66) ||
					((bossMeta)[2] == 100)) &&
				(sdata->unk_8008d42C == 5))
			{
				uVar3 = (bossMeta)[1];
			}
			bossMeta = data.bossWeaponMetaPtr[0];

			// if levelID is not oxide station
			if (gGT->levelID != 0xd)
			{
				// set boss weapon meta to the one type it can be on this hub
				bossMeta = data.bossWeaponMetaPtr[data.metaDataLEV[gGT->levelID].hubID];
			}
			if (uVar3 != 0xffff)
			{
				bossMeta->throwFlag = (char)uVar3;
			}
		}
	}

	// if not last weapon set
	else
	{
		// distToFinish less than...
		if (botDriver->distanceToFinish_curr <

			// track progress of NEXT set
			// percentage of track length
			(gGT.level1.ptr_restart_points[((struct MetaDataBOSS*)(int)bossMeta + 8)->trackCheckpoint].distToFinish) << 3)
		{
			bVar8 = 0xff;
			if (
				(
					((bossMeta)[2] == 0x66) ||
					(iVar4 = -0x10000, (bossMeta)[2] == 100)) &&

				(iVar4 = -0x10000, sdata->unk_8008d42C == 5))
			{
				bVar8 = (bossMeta)[1];
				iVar4 = (uint)bVar8 << 0x10;
			}

			// next set
			bossMeta = ((struct MetaDataBOSS*)(int)bossMeta + 8);

			if (iVar4 >> 0x10 != -1)
			{
				(bossMeta)[9] = bVar8;
			}
		}
	}

	// set new boss meta
	(bossMeta)[0] = bossMeta;

	if (bossMeta[3] == 0)
	{
		// run this once per second
		if (sdata->unk_8008d428 == 0x1e)
		{
			if ((botDriver->botFlags & 0x80) == 0)
			{
				if (*(short*)0x8008d42a == 0)
				{
					sVar11 = botDriver->botPath;
					if (sVar11 == 2)
						goto LAB_80040ba0;
					if (sVar11 == 1)
					{
						*(char *)(botDriver + 0x627) = 0;
						sdata->unk_8008d428 = 0;
						*(short*)0x8008d42a = sVar11;
						botDriver->botFlags |= 0x40;
					}
				}
				else
				{
					if (botDriver->botPath == NULL)
					{
					LAB_80040ba0:
						uVar5 = botDriver->botFlags;
						*(char *)(botDriver + 0x627) = 1;
					}
					else
					{
						if (botDriver->botPath != 1)
							goto LAB_80040bf8;
						uVar5 = botDriver->botFlags;
						*(char *)(botDriver + 0x627) = 2;
						*(short*)0x8008d42a = 0;
					}
					sdata->unk_8008d428 = 0;
					botDriver->botFlags = uVar5 | 0x40;
				}
			}
		}

		// count up
		else
		{
			if ((botDriver->botFlags & 0x40) == 0)
			{
				sdata->unk_8008d428 += 1;
			}
		}
	}
LAB_80040bf8:

	// cooldown, cant shoot weapons till finished
	if (0 < sdata->bossCooldown)
	{
		sdata->bossCooldown -= 1;
		return;
	}

	// some kind of RNG with 0xdeadc0ed
	uVar3 = RngDeadCoed(&bss);

	// new cooldown
	sdata->bossCooldown =

		// random [0 to 16] +
		(uVar3 & 0x10) +

		// min cooldown for boss
		bossMeta->weaponCooldown

		// number of times you lost the event
		sdata->advProgress.timesLostBossRace[gGT->bossID]];

	u_char weaponType = bossMeta->weaponType;
	weaponID = weaponType;
	if (weaponType == 0x64)
	{
		// weapon (tnt)
		weaponID = 3;
	}
	else
	{
		if (weaponType == 0x65)
		{
			// weapon (bomb)
			weaponID = 1;
		}
		else
		{
			if (weaponType == 0x66)
			{
				// weapon (potion)
				weaponID = 4;
			}
			else
			{
				if (weaponType == 0xf)
				{
					weaponID = 0xffffffff;
				}
			}
		}
	}
	uVar3 = bossMeta->juiceFlag;
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
		weaponType = bossMeta->weaponType;
		if (weaponType == 0x64)
		{
			// weapon (tnt)
			weaponID = 3;

			if (bossMeta->throwFlag != 3)
			{
				bossMeta->throwFlag = 3;
				sdata->unk_8008d42C = 5;
				bossMeta->juiceFlag = uVar3 | 1;
				sVar11 = sdata->unk_8008d42C;
				goto LAB_80040da0;
			}
		}
		else
		{
			if (weaponType == 0x65)
			{
				// weapon (bomb)
				weaponID = 1;

				// swap each frame between juiced and not juiced

				// not juiced, then juiced up
				if ((uVar3 & 1) == 0)
				{
					bossMeta->juiceFlag = uVar3 | 1;
					sdata->unk_8008d42C = 5;

					// weapon (tnt)
					weaponID = 3;

					sVar11 = sdata->unk_8008d42C;
					goto LAB_80040da0;
				}

				// already juiced, unjuice
				bossMeta->juiceFlag = uVar3 & ~1;
				goto LAB_80040d9c;
			}
			sVar11 = sdata->unk_8008d42C;
			if (weaponType != 0x66)
				goto LAB_80040da0;

			// weapon (potion)
			weaponID = 4;

			if (bossMeta->throwFlag != 3)
			{
				bossMeta->throwFlag = 3;
				sdata->unk_8008d42C = 5;

				// give 10 wumpa
				bossMeta->juiceFlag |= 1;

				sVar11 = sdata->unk_8008d42C;
				goto LAB_80040da0;
			}
		}

		bossMeta->throwFlag = 2;
		sdata->unk_8008d42C = 0;

		// dont use 10 wumpa
		bossMeta->juiceFlag &= 0xfffe;

		sVar11 = sdata->unk_8008d42C;
	}
LAB_80040da0:

	sdata->unk_8008d42C = sVar11;
	u_char throwFlag = bossMeta->throwFlag;
	u_short weaponFlags = (throwFlag == 2);
	uVar9 = 0;

	// if weapon ID is valid
	if (-1 < (int)(weaponID << 0x10))
	{
		// backup numWumpa
		backupWumpa = botDriver->numWumpas;

		if ((bossMeta->juiceFlag & 1) != 0)
		{
			// 10 wumpa
			uVar9 = 10;
		}

		// wumpa
		botDriver->numWumpas = uVar9;

		// weaponID
		botDriver->heldItemID = weaponID;

		if ((weaponID - 3 & 0xffff) < 2)
		{
			// Player / AI structure + 0x4a shows driver index (0-7)

			// get the character ID of P1 and P2 (or boss)
			enemyID = data.characterIDs[botDriver->driverID];
			playerID = data.characterIDs[thisDriver->driverID];

			voiceID = 15;
		}
		else
		{
			// Player / AI structure + 0x4a shows driver index (0-7)

			voiceID = 10;

			// get the character ID of P1 and P2 (or boss)
			enemyID = data.characterIDs[botDriver->driverID];
			playerID = data.characterIDs[thisDriver->driverID];

			// shoot backwards
			weaponFlags = (u_short)(throwFlag == 2) | 2;
		}

		// Make driver talk
		Voiceline_RequestPlay(voiceID, enemyID, playerID);

		// If weapon is bomb
		if (bossDrivers->heldItemID == 1)
		{
			// Pinstripe or Oxide

			// VehPickupItem_ShootNow (boss)
			VehPickupItem_ShootNow(botDriver, 2, weaponFlags);
		}

		else
		{
			if (
				(
					// Papu or Oxide
					// If your weapon is potion
					(botDriver->heldItemID == 4) &&

					(weaponFlags == 1)) &&

				// If you are on oxide station
				(gGT->levelID == 0xd))
			{
				// VehPickupItem_ShootNow (boss)
				// Fire two potions (see oxide boss challenge)
				VehPickupItem_ShootNow(botDriver, weaponID, 1);
				VehPickupItem_ShootNow(botDriver, weaponID, 1);
			}
			else
			{
				// VehPickupItem_ShootNow (boss)
				VehPickupItem_ShootNow(botDriver, weaponID, weaponFlags);

				if (// Roo, Joe, Oxide
					(
						// If your weapon is TNT or Nitro
						(botDriver->heldItemID == 3) &&

						(bossMeta->throwFlag == 3)) &&

					(sdata->unk_8008d42C != 5))
				{
					sdata->unk_8008d42C = 5;
				}
			}
		}

		// You have no weapon
		botDriver->heldItemID = 0xf;

		// Set number of wumpa fruit
		botDriver->numWumpas = backupWumpa;
	}
	return;
}
 