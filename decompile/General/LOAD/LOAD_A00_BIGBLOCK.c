#include <common.h>

#include "LOAD_A01_Callback_Overlay_Generic.c"
#include "LOAD_A02_Callback_Overlay_230.c"
#include "LOAD_A03_Callback_Overlay_231.c"
#include "LOAD_A04_Callback_Overlay_232.c"
#include "LOAD_A05_Callback_Overlay_233.c"
#include "LOAD_A06_Callback_MaskHints3D.c"
#include "LOAD_A07_Callback_Podiums.c"
#include "LOAD_A08_Callback_LEV.c"
#include "LOAD_A09_Callback_LEV_Adv.c"
#include "LOAD_A10_Callback_DriverModels.c"
#include "LOAD_A11_HubCallback.c"
#include "LOAD_A12_GlobalModelPtrs_MPK.c"
#include "LOAD_A13_HubSwapPtrs.c"
#include "LOAD_A14_StringToUpper.c"
#include "LOAD_A15_InitCD.c"
#include "LOAD_A16_ReadDirectory.c"
#include "LOAD_A17_DramFileCallback.c"
#include "LOAD_A18_DramFile.c"
#include "LOAD_A19_VramFileCallback.c"
#include "LOAD_A20_VramFile.c"
#include "LOAD_A21_ReadFileASyncCallback.c"
#include "LOAD_A22_ReadFile.c"
#include "LOAD_A23_ReadFile_NoCallback.c"
#include "LOAD_A24_FindFile.c"
#include "LOAD_A25_HowlHeaderSectors.c"
#include "LOAD_A26_HowlCallback.c"
#include "LOAD_A27_HowlSectorChainStart.c"
#include "LOAD_A28_HowlSectorChainEnd.c"
#include "LOAD_A29_RunPtrMap.c"
#include "LOAD_A30_Robots2P.c"
#include "LOAD_A31_Robots1P.c"
#include "LOAD_A32_DriverMPK.c"
#include "LOAD_A33_LangFile.c"
#include "LOAD_A34_GetBigfileIndex.c"

#include "../AltMods/Mods4.c"

void __attribute__ ((section (".end"))) Mods4_EndOfFile()
{
	// leave empty
}