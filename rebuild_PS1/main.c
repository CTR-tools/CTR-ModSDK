#define REBUILD_PS1

#include <common.h>

#include "../decompile/General/MAIN/MainMain.c"

#include "../decompile/General/CDSYS/CDSYS_c01_Init.c" 
#include "../decompile/General/CDSYS/CDSYS_c02_GetFilePosInt.c" 
#include "../decompile/General/CDSYS/CDSYS_c03_SetMode_StreamData.c" 
#include "../decompile/General/CDSYS/CDSYS_c04_SetMode_StreamAudio.c" 
#include "../decompile/General/CDSYS/CDSYS_c05_SetXAToLang.c" 
#include "../decompile/General/CDSYS/CDSYS_c06_XaCallbackCdSync.c" 
#include "../decompile/General/CDSYS/CDSYS_c07_XaCallbackCdReady.c" 
#include "../decompile/General/CDSYS/CDSYS_c08_SpuCallbackIRQ.c" 
#include "../decompile/General/CDSYS/CDSYS_c09_SpuCallbackTransfer.c" 
#include "../decompile/General/CDSYS/CDSYS_c10_SpuEnableIRQ.c" 
#include "../decompile/General/CDSYS/CDSYS_c11_SpuDisableIRQ.c" 
#include "../decompile/General/CDSYS/CDSYS_c13_XAGetNumTracks.c" 
#include "../decompile/General/CDSYS/CDSYS_c14_XASeek.c" 
#include "../decompile/General/CDSYS/CDSYS_c15_XAGetTrackLength.c" 
#include "../decompile/General/CDSYS/CDSYS_c16_XAPlay.c" 
#include "../decompile/General/CDSYS/CDSYS_c17_XAPauseRequest.c" 
#include "../decompile/General/CDSYS/CDSYS_c18_XAPauseForce.c" 
#include "../decompile/General/CDSYS/CDSYS_c19_XAPauseAtEnd.c" 

#include "../decompile/General/DecalGlobal/DecalGlobal_Clear.c"

#include "../decompile/General/GAMEPAD/GAMEPAD_Init.c"
#include "../decompile/General/GAMEPAD/GAMEPAD_GetNumConnected.c"

#include "../decompile/General/GAMEPROG/GAMEPROG_ResetHighScores.c"
// skip
#include "../decompile/General/GAMEPROG/GAMEPROG_NewProfile_OutsideAdv.c"
// skip
#include "../decompile/General/GAMEPROG/GAMEPROG_NewProfile_InsideAdv.c"
// skip
#include "../decompile/General/GAMEPROG/GAMEPROG_NewGame_OnBoot.c"
#include "../decompile/General/GAMEPROG/GAMEPROG_GetPtrHighScoreTrack.c"

#include "../decompile/General/HOWL/h31_howl_InitGlobals.c"
#include "../decompile/General/HOWL/h32_howl_ParseHeader.c"
#include "../decompile/General/HOWL/h33_howl_ParseCseqHeader.c"
#include "../decompile/General/HOWL/h34_howl_LoadHeader.c"

#include "../decompile/General/LOAD/LOAD_A01_Callback_Overlay_Generic.c"
#include "../decompile/General/LOAD/LOAD_A02_Callback_Overlay_230.c"
#include "../decompile/General/LOAD/LOAD_A03_Callback_Overlay_231.c"
#include "../decompile/General/LOAD/LOAD_A04_Callback_Overlay_232.c"
#include "../decompile/General/LOAD/LOAD_A05_Callback_Overlay_233.c"
// hole
#include "../decompile/General/LOAD/LOAD_A10_Callback_DriverModels.c"
// hole
#include "../decompile/General/LOAD/LOAD_A14_StringToUpper.c" 
#include "../decompile/General/LOAD/LOAD_A15_InitCD.c" 
#include "../decompile/General/LOAD/LOAD_A16_ReadDirectory.c" 
#include "../decompile/General/LOAD/LOAD_A17_DramFileCallback.c"
#include "../decompile/General/LOAD/LOAD_A18_DramFile.c"
#include "../decompile/General/LOAD/LOAD_A19_VramFileCallback.c"
#include "../decompile/General/LOAD/LOAD_A20_VramFile.c" 
#include "../decompile/General/LOAD/LOAD_A21_ReadFileASyncCallback.c"
#include "../decompile/General/LOAD/LOAD_A22_ReadFile.c"
#include "../decompile/General/LOAD/LOAD_A23_ReadFile_NoCallback.c"
#include "../decompile/General/LOAD/LOAD_A24_FindFile.c"
#include "../decompile/General/LOAD/LOAD_A25_HowlHeaderSectors.c"
// hole
#include "../decompile/General/LOAD/LOAD_A29_RunPtrMap.c"
#include "../decompile/General/LOAD/LOAD_A30_Robots2P.c"
#include "../decompile/General/LOAD/LOAD_A31_Robots1P.c"
#include "../decompile/General/LOAD/LOAD_A32_DriverMPK.c"
#include "../decompile/General/LOAD/LOAD_A33_LangFile.c"
// hole
#include "../decompile/General/LOAD/LOAD_A35_AppendQueue.c"
#include "../decompile/General/LOAD/LOAD_A36_CDRequestCallback.c"
#include "../decompile/General/LOAD/LOAD_A37_NextQueuedFile.c"
// hole
#include "../decompile/General/LOAD/LOAD_A41_OvrLOD.c"
#include "../decompile/General/LOAD/LOAD_A42_OvrEndRace.c"
#include "../decompile/General/LOAD/LOAD_A43_OvrThreads.c"
// hole
#include "../decompile/General/LOAD/LOAD_A45_TenStages.c"

#include "../decompile/General/MAIN/MainDB_OTMem.c"
#include "../decompile/General/MAIN/MainDB_PrimMem.c"
#include "../decompile/General/MAIN/MainDrawCb_DrawSync.c"
#include "../decompile/General/MAIN/MainInit_OTMem.c"
#include "../decompile/General/MAIN/MainInit_PrimMem.c"
#include "../decompile/General/MAIN/MainInit_VRAMClear.c" 
#include "../decompile/General/MAIN/MainInit_VRAMDisplay.c" 

#include "../decompile/General/MEMCARD/MEMCARD_InitCard.c"

#include "../decompile/General/MEMPACK/MEMPACK_Init.c" 
#include "../decompile/General/MEMPACK/MEMPACK_SwapPacks.c" 
#include "../decompile/General/MEMPACK/MEMPACK_NewPack_StartEnd.c" 
#include "../decompile/General/MEMPACK/MEMPACK_GetFreeBytes.c" 
#include "../decompile/General/MEMPACK/MEMPACK_AllocMem.c" 
#include "../decompile/General/MEMPACK/MEMPACK_AllocHighMem.c" 
#include "../decompile/General/MEMPACK/MEMPACK_ClearHighMem.c" 
#include "../decompile/General/MEMPACK/MEMPACK_ReallocMem.c" 
#include "../decompile/General/MEMPACK/MEMPACK_PushState.c" 
#include "../decompile/General/MEMPACK/MEMPACK_ClearLowMem.c" 
#include "../decompile/General/MEMPACK/MEMPACK_PopState.c" 
#include "../decompile/General/MEMPACK/MEMPACK_PopToState.c"

// skip TitleFlag_t01
#include "../decompile/General/TitleFlag/TitleFlag_t02_IsFullyOnScreen.c"
#include "../decompile/General/TitleFlag/TitleFlag_t03_IsFullyOffScreen.c"
#include "../decompile/General/TitleFlag/TitleFlag_t04_IsTransitioning.c"
#include "../decompile/General/TitleFlag/TitleFlag_t05_SetDrawOrder.c"
#include "../decompile/General/TitleFlag/TitleFlag_t06_BeginTransition.c"
#include "../decompile/General/TitleFlag/TitleFlag_t07_SetFullyOnScreen.c"
#include "../decompile/General/TitleFlag/TitleFlag_t08_SetFullyOffScreen.c"
#include "../decompile/General/TitleFlag/TitleFlag_t09_SetCanDraw.c"
#include "../decompile/General/TitleFlag/TitleFlag_t10_GetCanDraw.c"

// RCNT (watch namespace, not alphabetical)
#include "../decompile/General/RCNT/RCNT_Init.c"