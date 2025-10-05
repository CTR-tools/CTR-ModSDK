#include <common.h>

int DECOMP_RB_Hazard_HurtDriver(
	struct Driver* driverVictim, 
	int damageType,
	struct Driver* driverAttacker,
	int reason)
{
	struct GameTracker* gGT = sdata->gGT;
	int result=0;

	if ((driverVictim->actionsFlagSet & 0x100000) == 0)
	{
		#ifndef REBUILD_PS1 //this ifndef should be removed at some point?
		result = VehPickState_NewState(driverVictim, damageType, driverAttacker, reason);
		#endif
	}
	else
	{
		//decomp attempt 1 had the second condition of this if statement as: ((gGT->gameMode1 & ADVENTURE_BOSS) != 0)
		//currently using ((int)gGT->gameMode1 < 0) bc that's what ghidra says (it might be equivalent idk)
		//if this was really < 0 then i will reconsider if gameMode 1 should really be a signed int
		if ((gGT->levelID == OXIDE_STATION) && ((gGT->gameMode1 & ADVENTURE_BOSS) != 0))
			damageType = 1;

		#ifndef REBUILD_PS1 //this ifndef should be removed at some point?
		result = (int)BOTS_ChangeState(driverVictim, damageType, driverAttacker, reason);
		#endif
	}
	return result;
}