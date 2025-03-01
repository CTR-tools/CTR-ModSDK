#include <common.h>

u_int DECOMP_BOTS_ChangeState(struct Driver* driverVictim, int damageType, struct Driver* driverAttacker, int reason)
{
	driverVictim->ChangeState_param2 = 0;

	if (driverVictim->kartState == KS_MASK_GRABBED)
	{
		return 0;
	}

	driverVictim->kartState = KS_NORMAL;

	switch (damageType)
	{
	case 0:
		if ((driverVictim->botData.botFlags & 2) != 0)
		{
			return 0;
		}
		break;
	case 1:
	case 4:
		if ((driverVictim->botData.botFlags & 2) == 0)
		{
			driverVictim->botData.unk5ba = 1;
			*((short*)&driverVictim->botData.unk5bc[0x8]) = 0;

			if ((data.characterIDs[driverVictim->driverID] != 0xf) || ((driverVictim->actionsFlagSet & 1) != 0))
			{
				driverVictim->reserves = 0;
				driverVictim->turbo_outsideTimer = 0;
				driverVictim->botData.unk5bc[0x10] = 0;

				int newSpeed;

				if (data.characterIDs[driverVictim->driverID] == 0xf)
				{
					newSpeed = (*(int*)(&driverVictim->botData.unk5bc[0x18])) >> 1;
				}
				else
				{
					newSpeed = (*(int*)(&driverVictim->botData.unk5bc[0x18])) >> 2;
				}

				*(int*)(&driverVictim->botData.unk5bc[0x18]) = newSpeed;
			}

			*(int*)(&driverVictim->botData.unk5bc[0xc]) = 0x300;
			driverVictim->botData.ai_progress_cooldown = 0;

			driverVictim->botData.botFlags |= 2;
		}

		if (damageType == 4)
		{
			if (driverVictim->instSelf->thread->modelIndex == 0x18 && driverVictim->burnTimer == 0)
			{
				OtherFX_Play(0x69, 1);
			}

			driverVictim->burnTimer = 0xf00;
		}
		break;
	case 2:
		driverVictim->botData.unk626 = 0; //OG code just assigns 0 to 1 byte at +0x626, not 2 bytes
		(*(short*)&driverVictim->botData.unk5bc[0x8]) = 0;
		driverVictim->botData.unk5ba = 2;
		driverVictim->reserves = 0;
		driverVictim->turbo_outsideTimer = 0;
		(*(int*)&driverVictim->botData.unk5bc[0x10]) = 0;
		(*(int*)&driverVictim->botData.unk5bc[0x14]) = sdata->AI_VelY_WhenBlasted_0x3000;

		if ((driverVictim->botData.botFlags & 2) == 0)
		{
			(*(int*)&driverVictim->botData.unk5bc[0x18]) >>= 3;
			driverVictim->botData.ai_posBackup[1] += 0x4000;
		}

		driverVictim->botData.ai_progress_cooldown = 0;
		driverVictim->matrixArray = 0;
		driverVictim->botData.botFlags |= 2;

		if (driverAttacker == NULL)
		{
			return 1;
		}

		if ((driverAttacker->actionsFlagSet & 0x100000) == 0)
		{
			Voiceline_RequestPlay(1, data.characterIDs[driverVictim->driverID], 0x10);
		}
		break;
	case 3:
		*(short*)&driverVictim->botData.unk5bc[0x8] = 0;

		if (driverVictim->instSelf->thread->modelIndex == 0x18 && (*(int*)&driverVictim->botData.unk5bc[0xC]) == 0)
		{
			OtherFX_Play(0x5a, 1);
		}

		driverVictim->botData.unk5ba = 3;
		*(int*)&driverVictim->botData.unk5bc[0xC] = 0x300;
		*(short*)&driverVictim->botData.unk5bc[0x0] = 0xf00;
		driverVictim->squishTimer = 0xf00;
		driverVictim->reserves = 0;
		driverVictim->turbo_outsideTimer = 0;
		*(int*)&driverVictim->botData.unk5bc[0x10] = 0;
		*(int*)&driverVictim->botData.unk5bc[0x14] = 0;
		driverVictim->botData.ai_progress_cooldown = 0;
		*(int*)&driverVictim->botData.unk5bc[0x18] >>= 1;
		driverVictim->botData.botFlags |= 6;
		break;
	case 5:
		*(short*)&driverVictim->botData.unk5bc[0x8] = 0;
		*(int*)&driverVictim->botData.unk5bc[0x18] = 0;
		*(int*)&driverVictim->botData.unk5bc[0x14] = 0;
		*(int*)&driverVictim->botData.unk5bc[0x10] = 0;
		driverVictim->instSelf->flags |= 0x80;
		*(short*)&driverVictim->botData.unk5bc[0x0] = 0xd20;
		driverVictim->botData.unk5ba = 5;
		driverVictim->kartState = KS_MASK_GRABBED;
		driverVictim->botData.botFlags |= 6;
		driverVictim->instSelf->thread->flags |= 0x1000;
		break;
	default:
		driverVictim->botData.ai_progress_cooldown = 0x3c;
	}

	if (damageType)
	{
		driverAttacker->numTimesAttacked++;
		switch (damageType) {
		case 1:
			driverAttacker->numTimesBombsHitSomeone++;
			break;
		case 3:
			driverAttacker->numTimesMissileHitSomeone++;
			break;
		case 4:
			driverAttacker->numTimesMovingPotionHitSomeone++;
			break;
		}
	}
	return 1;
}