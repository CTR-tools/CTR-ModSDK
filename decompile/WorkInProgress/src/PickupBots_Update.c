#include <common.h>

void DECOMP_PickupBots_Update(void)
{
	// handles which weapons bosses use
	char i;
	u_char weaponID;
	u_char enemyID;
	u_char playerID;
	u_char throwFlag;
	char numPlyrCurrGame;
	int distX;
	int distZ;
	u_short uVar3;
	int iVar4;
	u_int uVar5;
	int rand;
	char bVar8;
	u_char rngWeapon;
	u_int voicelineID;
	short sVar11;
	struct Driver *player;
	struct Driver *botDriver;
	struct GameTracker *gGT = sdata->gGT;

	// If number of AIs is zero,			or		time on clock is less than ~20sec
	if ((gGT->numBotsNextGame == 0) || (gGT->elapsedEventTime < FPS_DOUBLE(19200)))
	{
		if (-1 < gGT->gameMode1)
		{
			return;
		}

		// quit if event started less than ~5sec ago
		if (gGT->elapsedEventTime < FPS_DOUBLE(4800))
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
			player = gGT->drivers[i];

			// if racer is not in first place
			if (player->driverRank != 0)
			{
				// driver in front of the player
				botDriver = gGT->driversInRaceOrder[player->driverRank - 1];

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
							(botDriver->instTntRecv == 0)) &&

						((
							// if there is no clock weapon in effect
							botDriver->clockReceive == 0 &&
							(
								distX = (player->instSelf->matrix.t[0] - botDriver->instSelf->matrix.t[0]),
								distZ = (player->instSelf->matrix.t[2] - botDriver->instSelf->matrix.t[2]),

								// check if distance between drivers is small
								(distX * distX + distZ * distZ) - 0x90001U < 0x13affff))))))
				{
					// Get random number
					rand = MixRNG_Scramble();

					// Get remainder when divided by 200
					rand = rand % 200;

					// If RNG is 0, (1/200 chance)
					if (rand == 0)
					{
						if ((botDriver->lapIndex != 0) &&

							(
								// Get random number
								rand = MixRNG_Scramble(),

								// 50% chance this will happen
								rand % 100 < 50))
						{
							// Set number of wumpa to 10
							botDriver->numWumpas = 10;
						}

						// if time on the clock is an even number
						if ((gGT->elapsedEventTime & FPS_DOUBLE(1)) == 0)
						{
							// Set weapon to potion
							botDriver->heldItemID = 4;

							// If this is human and not AI
							if ((player->actionsFlagSet & 0x100000) == 0)
							{
								// Make driver talk
								Voiceline_RequestPlay(0xf,
													  data.characterIDs[botDriver->driverID],
													  data.characterIDs[player->driverID]);
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
							if ((player->actionsFlagSet & 0x100000) == 0)
							{
								// Make driver talk
								Voiceline_RequestPlay(0xf, data.characterIDs[botDriver->driverID], data.characterIDs[player->driverID]);
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
						rand = MixRNG_Scramble();

						// weapon cooldown
						botDriver->weaponCooldown = (rand & 0xff) + 0xf0;
					}
					else
					{
						// If RNG is 1, (1/200 chance)
						if (rand == 1)
						{
							// Set weapon to bomb
							botDriver->heldItemID = (char)rand;

							// If this is human and not AI
							if ((player->actionsFlagSet & 0x100000) == 0)
							{
								enemyID = data.characterIDs[botDriver->driverID];
								playerID = data.characterIDs[player->driverID];
								voicelineID = 10;
							LAB_8004128c:
								// Make driver talk
								Voiceline_RequestPlay(voicelineID, enemyID, playerID);
							}
						LAB_80041298:
							VehPickupItem_ShootNow(botDriver, 2, 0);
							goto LAB_800412a4;
						}

						// If RNG is 2, (1/200 chance)
						if (rand == 2)
						{
							// Set weapon to 2
							botDriver->heldItemID = (char)rand;

							// if this is human and not AI
							if ((player->actionsFlagSet & 0x100000) == 0)
							{
								enemyID = data.characterIDs[botDriver->driverID];
								playerID = data.characterIDs[player->driverID];
								voicelineID = 11;
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
			if (player->driverRank < 3)
			{
				// driver in the position behind player
				botDriver = gGT->driversInRaceOrder[player->driverRank + 1];
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
									player->lapIndex < gGT->numLaps ||

									// distToFinish more than 16000
									(16000U < player->distanceToFinish_curr))))))) &&
						(
							distX = player->instSelf->matrix.t[0] - botDriver->instSelf->matrix.t[0],
							distZ = player->instSelf->matrix.t[2] - botDriver->instSelf->matrix.t[2],

							// check if distance between drivers is small
							(distX * distX + distZ * distZ) - 0x90001U < 0x13affff)))
				{
					// Get random number
					rand = MixRNG_Scramble();

					if (
						(
							// 2 in 800 chance (1 in 400)
							(rand % 800 < 2) &&
							(
								// override weapon to missile
								rngWeapon = 2,

								// if driver's lap is not last lap
								botDriver->lapIndex != gGT->numLaps - 1U)) ||
						(
							// override weapon to bomb
							rngWeapon = 1,

							// 4 in 800 chance (1 in 200)
							rand % 800 < 4))
					{
						// set weapon
						botDriver->heldItemID = rngWeapon;

						// If this is an AI and not human
						if ((player->actionsFlagSet & 0x100000) == 0)
						{
							// Make driver talk
							Voiceline_RequestPlay(0xb,
												  data.characterIDs[botDriver->driverID],
												  data.characterIDs[player->driverID]);
						}

						//  (Arcade/Adv) Missile
						VehPickupItem_ShootNow(botDriver, 2, 0);

						// Get random number
						rand = MixRNG_Scramble();

						// cooldown before next weapon
						botDriver->weaponCooldown = (rand & 0xff) + 0xf0;
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
	player = gGT->drivers[0];

	// pointer to boss meta
	struct MetaDataBOSS* bossMeta = *(int *)0x8008d8e8;
	struct MetaDataBOSS* nextMeta = (int)bossMeta + 8;

	if (
		(
			((botDriver->botFlags & 2) != 0) ||

			// if racer finished this race
			((botDriver->actionsFlagSet & 0x2000000) != 0)) ||
		((
			// if boss has tnt on their head
			botDriver->instTntRecv != NULL ||
			((
				// victim of clock weapon
				botDriver->clockReceive != 0 ||

				// if boss has not reached high speed
				(*(int *)((int)botDriver + 0x5d4) < 0x1f41))))))
	{
		// some kind of RNG with 0xdeadc0ed
		rand = RngDeadCoed(&bss);

		// new cooldown
		*(short *)0x8008d8e4 =

			// random [0 to 16] +
			(rand & 16) +

			// min cooldown for boss
			bossMeta->weaponCooldown + 12 +

			// number of times you lost the event
			sdata->advProgress.timesLostBossRace[gGT->bossID];

		return;
	}

	// if this is the last weapon set (next is nullptr)
	if (nextMeta->throwFlag == 0)
	{
		if (
			// track progress of THIS set
			(gGT->level1->ptr_restart_points[bossMeta->trackCheckpoint].distToFinish << 3) <

			// distToFinish
			botDriver->distanceToFinish_curr)
		{
			throwFlag = 0xff;
			if (
				(
					(bossMeta->weaponType == 0x66) ||
					(bossMeta->weaponType == 0x64)) &&
				(sdata->unk_8008d42C == 5))
			{
				throwFlag = (u_short)bossMeta->throwFlag;
			}
			bossMeta = data.bossWeaponMetaPtr[0];

			// if levelID is not oxide station
			if (gGT->levelID != OXIDE_STATION)
			{
				// set boss weapon meta to the one type it can be on this hub
				bossMeta = data.bossWeaponMetaPtr[data.metaDataLEV[gGT->levelID].hubID];
			}
			if (throwFlag != 0xff)
			{
				bossMeta->throwFlag = throwFlag;
			}
		}
	}

	// if not last weapon set
	else
	{
		// distToFinish less than...
		if (botDriver->distanceToFinish_curr <

			// track progress of NEXT set
			(gGT->level1->ptr_restart_points[nextMeta->trackCheckpoint].distToFinish << 3))
		{
			throwFlag = 0xff;
			if (
				(	
					(bossMeta->weaponType == 0x66) ||
					(bossMeta->weaponType == 0x64)) &&

				(sdata->unk_8008d42C == 5))
			{
				throwFlag = bossMeta->throwFlag;
			}

			// next set
			bossMeta = nextMeta;

			if (throwFlag != 0xff)
			{
				nextMeta->throwFlag = throwFlag;
			}
		}
	}

	// set new boss meta
	*(int*)0x8008d8e8 = bossMeta;

	if (bossMeta->unk1 == 0)
	{
		// run this once per second
		if (sdata->unk_8008d428 == 30)
		{
			if ((botDriver->botFlags & 0x80) == 0)
			{
				if (sdata->unk_8008d42a == 0)
				{
					sVar11 = botDriver->botPath;
					if (sVar11 == 2)
						goto LAB_80040ba0;
					if (sVar11 == 1)
					{
						*(u_char *)(botDriver + 0x627) = 0;
						sdata->unk_8008d428 = 0;
						sdata->unk_8008d42a = sVar11;
						botDriver->botFlags |= 0x40;
					}
				}
				else
				{
					if (botDriver->botPath == 0)
					{
					LAB_80040ba0:
						*(u_char *)((int)botDriver + 0x627) = 1;
					}
					else
					{
						if (botDriver->botPath != 1)
							goto LAB_80040bf8;
						*(u_char *)((int)botDriver + 0x627) = 2;
						sdata->unk_8008d42a = 0;
					}
					sdata->unk_8008d428 = 0;
					botDriver->botFlags |= 0x40;
				}
			}
		}
		// count up
		else
		{
			if ((botDriver->botFlags & 0x40) == 0)
			{
				sdata->unk_8008d428++;
			}
		}
	}
LAB_80040bf8:

	// cooldown, cant shoot weapons till finished
	if (0 < *(short *)0x8008d8e4)
	{
		*(short *)0x8008d8e4 = *(short *)0x8008d8e4 - 1;
		return;
	}

	// some kind of RNG with 0xdeadc0ed
	uVar3 = RngDeadCoed(&bss);

	// new cooldown
	*(short *)0x8008d8e4 =

		// random [0 to 16] +
		(uVar3 & 16) +

		// min cooldown for boss
		bossMeta->weaponCooldown + 12 +

		// number of times you lost the event
		sdata->advProgress.timesLostBossRace[gGT->bossID];

	bVar8 = bossMeta->weaponType;
	uVar5 = (u_int)bVar8;
	if (bVar8 == 0x64)
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
		bVar8 = bossMeta->weaponType;

		if (bVar8 == 0x64)
		{
			// weapon (tnt)
			uVar5 = 3;

			if (bossMeta->throwFlag != 3)
			{
				bossMeta->throwFlag = 3;
				sdata->unk_8008d42C = 5;
				bossMeta->juiceFlag|= 1;
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
					bossMeta->juiceFlag |= 1;
					sdata->unk_8008d42C = 5;

					// weapon (tnt)
					uVar5 = 3;

					sVar11 = sdata->unk_8008d42C;
					goto LAB_80040da0;
				}

				// already juiced, unjuice
				bossMeta->juiceFlag &= ~1;
				goto LAB_80040d9c;
			}
			sVar11 = sdata->unk_8008d42C;
			if (bVar8 != 0x66)
				goto LAB_80040da0;

			// weapon (potion)
			uVar5 = 4;

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
		bossMeta->juiceFlag &= ~1;

		sVar11 = sdata->unk_8008d42C;
	}

LAB_80040da0:
	sdata->unk_8008d42C = sVar11;
	bVar8 = bossMeta->throwFlag;
	uVar3 = (u_short)(bVar8 == 2);
	u_char uVar9 = 0;
	u_char backupWumpa;
	if (-1 < (int)(uVar5 << 0x10))
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
		botDriver->heldItemID = (char)uVar5;

		if ((uVar5 - 3 & 0xffff) < 2)
		{
			// Player / AI structure + 0x4a shows driver index (0-7)

			// get the character ID of P1 and P2 (or boss)
			enemyID = data.characterIDs[botDriver->driverID];
			playerID = data.characterIDs[player->driverID];

			voicelineID = 15;
		}
		else
		{
			// Player / AI structure + 0x4a shows driver index (0-7)

			voicelineID = 10;

			// get the character ID of P1 and P2 (or boss)
			enemyID = data.characterIDs[botDriver->driverID];
			playerID = data.characterIDs[player->driverID];

			uVar3 = (u_short)(bVar8 == 2) | 2;
		}

		// Make driver talk
		Voiceline_RequestPlay(voicelineID, enemyID, playerID);

		// If weapon is bomb
		if (botDriver->heldItemID == 1)
		{
			// Pinstripe or Oxide

			// VehPickupItem_ShootNow (boss)
			VehPickupItem_ShootNow(botDriver, 2, uVar3);
		}

		else
		{
			sVar11 = (short)uVar5;
			if (

				(
					// Papu or Oxide

					// If your weapon is potion
					(botDriver->heldItemID == 4) &&

					(uVar3 == 1)) &&

				// If you are on oxide station
				(gGT->levelID == OXIDE_STATION))
			{
				// VehPickupItem_ShootNow (boss)
				// Fire two potions (see oxide boss challenge)
				VehPickupItem_ShootNow(botDriver, sVar11, 1);
				VehPickupItem_ShootNow(botDriver, sVar11, 1);
			}
			else
			{
				// VehPickupItem_ShootNow (boss)
				VehPickupItem_ShootNow(botDriver, sVar11, uVar3);

				if (
					// Roo, Joe, Oxide

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
}
