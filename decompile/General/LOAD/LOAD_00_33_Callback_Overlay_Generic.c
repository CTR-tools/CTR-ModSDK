#include <common.h>

#include "LOAD_00_Callback_Overlay_Generic.c"
#include "LOAD_01_Callback_Overlay_230.c"
#include "LOAD_02_Callback_Overlay_231.c"
#include "LOAD_03_Callback_Overlay_232.c"
#include "LOAD_04_Callback_Overlay_233.c"
#include "LOAD_05_Callback_MaskHints3D.c"
#include "LOAD_06_Callback_Podiums.c"
#include "LOAD_07_Callback_LEV.c"
#include "LOAD_08_Callback_PatchMem.c"
#include "LOAD_09_Callback_DriverModels.c"
#include "LOAD_10_HubCallback.c"
#include "LOAD_11_GlobalModelPtrs_MPK.c"
#include "LOAD_12_HubSwapPtrs.c"
#include "LOAD_13_StringToUpper.c"
#include "LOAD_14_InitCD.c"
#include "LOAD_15_ReadDirectory.c"
#include "LOAD_16_DramFileCallback.c"
#include "LOAD_17_DramFile.c"
#include "LOAD_18_VramFileCallback.c"
#include "LOAD_19_VramFile.c"
#include "LOAD_20_ReadFileASyncCallback.c"
#include "LOAD_21_ReadFile.c"
#include "LOAD_22_XnfFile.c"
#include "LOAD_23_FindFile.c"
#include "LOAD_24_HowlHeaderSectors.c"
#include "LOAD_25_HowlCallback.c"
#include "LOAD_26_HowlSectorChainStart.c"
#include "LOAD_27_HowlSectorChainEnd.c"
#include "LOAD_28_RunPtrMap.c"
#include "LOAD_29_Robots2P.c"
#include "LOAD_30_Robots1P.c"
#include "LOAD_31_DriverMPK.c"
#include "LOAD_32_LangFile.c"
#include "LOAD_33_GetBigfileIndex.c"
#include "LOAD_34_AppendQueue.c"
#include "LOAD_35_CDRequestCallback.c"
#include "LOAD_36_NextQueuedFile.c"

#if defined (USE_ALTMODS)
#include "../AltMods/Mods4.c"

void __attribute__ ((section (".end"))) Mods4_EndOfFile()
{
	// leave empty
}
#endif