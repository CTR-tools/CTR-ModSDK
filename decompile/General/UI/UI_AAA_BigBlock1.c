#include <common.h>

#include "../prim.c"
#include "../math.c"
#include "../gte.c"

#ifndef USE_ONLINE
#include "UI_00_SaveLapTime.c"
#endif

#include "UI_01_ThTick_CountPickup.c"
#include "UI_02_ThTick_Reward.c"

#ifndef USE_ONLINE
#include "UI_03_ThTick_CtrLetters.c"
#endif

#include "UI_04_ThTick_big1.c"
#include "UI_05_ConvertX_2.c"
#include "UI_06_ConvertY_2.c"
#include "UI_07_INSTANCE_BirthWithThread.c"
#include "UI_08_INSTANCE_InitAll.c"
#include "UI_09_Map_DrawMap.c"
#include "UI_10_Map_GetIconPos.c"
#include "UI_11_Map_DrawAdvPlayer.c"
#include "UI_12_Map_DrawRawIcon.c"
#include "UI_13_Map_DrawDrivers.c"

#ifndef USE_ONLINE
#include "UI_14_Map_DrawGhosts.c"
#endif

#include "UI_15_Map_DrawTracking.c"
#include "UI_16_WeaponBG_AnimateShine.c"
#include "UI_17_WeaponBG_DrawShine.c"
#include "UI_18_TrackerBG.c"
#include "UI_19_DrawDriverIcon.c"
#include "UI_20_Lerp2D_Angular.c"
#include "UI_21_Lerp2D_HUD.c"
#include "UI_22_Lerp2D_Linear.c"
#include "UI_23_DrawRaceClock.c"
#include "UI_24_DrawLimitClock.c"
#include "UI_25_BattleDrawHeadArrows.c"
#include "UI_26_TrackerSelf.c"
#include "UI_27_DrawPosSuffix.c"
#include "UI_28_DrawLapCount.c"
#include "UI_29_DrawBattleScores.c"
#include "UI_30_Weapon_DrawSelf.c"
#include "UI_31_Weapon_DrawBG.c"
#include "UI_32_DrawNumWumpa.c"
#include "UI_33_DrawNumTimebox.c"
#include "UI_34_DrawNumRelic.c"
#include "UI_35_DrawNumKey.c"
#include "UI_36_DrawNumTrophy.c"
#include "UI_37_DrawNumCrystal.c"
#include "UI_38_DrawSpeedNeedle.c"
#include "UI_39_DrawSpeedBG.c"
#include "UI_40_JumpMeter_Update.c"
#include "UI_41_JumpMeter_Draw.c"
#include "UI_42_DrawSlideMeter.c"
#include "UI_43_DrawRankedDrivers.c"
#include "UI_44_RenderFrame_Racing.c"

#ifndef USE_ONLINE
#include "UI_45_RenderFrame_AdvHub.c"
#include "UI_46_RenderFrame_CrystChall.c"
#endif


#if defined (USE_DEFRAG)
#include "../AltMods/Mods1.c"

void __attribute__ ((section (".end"))) Mods1_EndOfFile()
{
	// leave empty
}
#endif