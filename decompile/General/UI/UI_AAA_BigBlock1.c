#include <common.h>

#include "../prim.c"
#include "../math.c"
#include "../gte.c"

#ifndef USE_ONLINE
#include "UI_SaveLapTime.c"
#endif

#include "UI_ThTick_CountPickup.c"
#include "UI_ThTick_Reward.c"

#ifndef USE_ONLINE
#include "UI_ThTick_CtrLetters.c"
#endif

#include "UI_ThTick_big1.c"
#include "UI_ConvertX_2.c"
#include "UI_ConvertY_2.c"
#include "UI_INSTANCE_BirthWithThread.c"
#include "UI_INSTANCE_InitAll.c"
#include "UI_Map_DrawMap.c"
#include "UI_Map_GetIconPos.c"
#include "UI_Map_DrawAdvPlayer.c"
#include "UI_Map_DrawRawIcon.c"
#include "UI_Map_DrawDrivers.c"

#ifndef USE_ONLINE
#include "UI_Map_DrawGhosts.c"
#endif

#include "UI_Map_DrawTracking.c"
#include "UI_WeaponBG_AnimateShine.c"
#include "UI_WeaponBG_DrawShine.c"
#include "UI_TrackerBG.c"
#include "UI_DrawDriverIcon.c"
#include "UI_Lerp2D_Angular.c"
#include "UI_Lerp2D_HUD.c"
#include "UI_Lerp2D_Linear.c"
#include "UI_DrawRaceClock.c"
#include "UI_DrawLimitClock.c"
#include "UI_BattleDrawHeadArrows.c"
#include "UI_TrackerSelf.c"
#include "UI_DrawPosSuffix.c"
#include "UI_DrawLapCount.c"
#include "UI_DrawBattleScores.c"
#include "UI_Weapon_DrawSelf.c"
#include "UI_Weapon_DrawBG.c"
#include "UI_DrawNumWumpa.c"
#include "UI_DrawNumKey.c"
#include "UI_DrawNumRelic.c"
#include "UI_DrawNumTrophy.c"
#include "UI_DrawNumCrystal.c"
#include "UI_DrawNumTimebox.c"
#include "UI_DrawSpeedBG.c"
#include "UI_DrawSpeedNeedle.c"
#include "UI_JumpMeter_Draw.c"
#include "UI_JumpMeter_Update.c"
#include "UI_DrawSlideMeter.c"
#include "UI_DrawRankedDrivers.c"
#include "UI_RenderFrame_Racing.c"

#ifndef USE_ONLINE
#include "UI_RenderFrame_AdvHub.c"
#include "UI_RenderFrame_CrystChall.c"
#endif



#include "../AltMods/Mods1.c"

void __attribute__ ((section (".end"))) Mods1_EndOfFile()
{
	// leave empty
}