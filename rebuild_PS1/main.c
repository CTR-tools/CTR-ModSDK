#define REBUILD_PS1

#include <common.h>

#include "../decompile/General/MAIN/MainMain.c"

#include "../decompile/General/CAMERA/CAM_ClearScreen.c"

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

#include "../decompile/General/CTR_CycleTex_LEV.c"
#include "../decompile/General/CTR_ErrorScreen.c"
#include "../decompile/General/CTR_CycleTex_AllModels.c"
#include "../decompile/General/CTR_CycleTex_Model.c"

#include "../decompile/General/DecalFont/DecalFont_GetLineWidth.c"
#include "../decompile/General/DecalFont/DecalFont_DrawLineStrlen.c"
#include "../decompile/General/DecalFont/DecalFont_DrawLine.c"
#include "../decompile/General/DecalFont/DecalFont_DrawLineOT.c"
#include "../decompile/General/DecalFont/DecalFont_DrawMultiLineStrlen.c"
#include "../decompile/General/DecalFont/DecalFont_DrawMultiLine.c"
#include "../decompile/General/DecalFont/DecalFont_GetLineWidthStrlen.c"

#include "../decompile/General/DecalGlobal/DecalGlobal_Clear.c"
#include "../decompile/General/DecalGlobal/DecalGlobal_Store.c"

#include "../decompile/General/DecalHUD/DecalHUD_DrawPolyFT4.c"
#include "../decompile/General/DecalHUD/DecalHUD_DrawPolyGT4.c"
#include "../decompile/General/DecalHUD/DecalHUD_Arrow2D.c"

#include "../decompile/General/DISPLAY/DISPLAY_Swap.c"

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

#include "../decompile/General/HOWL/h11_SetReverbMode.c"
#include "../decompile/General/HOWL/h31_howl_InitGlobals.c"
#include "../decompile/General/HOWL/h32_howl_ParseHeader.c"
#include "../decompile/General/HOWL/h33_howl_ParseCseqHeader.c"
#include "../decompile/General/HOWL/h34_howl_LoadHeader.c"

#include "../decompile/General/INSTANCE/INSTANCE_Birth.c"
#include "../decompile/General/INSTANCE/INSTANCE_Birth3D.c"
#include "../decompile/General/INSTANCE/INSTANCE_Birth2D.c"
#include "../decompile/General/INSTANCE/INSTANCE_BirthWithThread.c"
#include "../decompile/General/INSTANCE/INSTANCE_BirthWithThread_Stack.c"
#include "../decompile/General/INSTANCE/INSTANCE_Death.c"
#include "../decompile/General/INSTANCE/INSTANCE_GetNumAnimFrames.c"

#include "../decompile/General/JitPool/JitPool_Clear.c"
#include "../decompile/General/JitPool/JitPool_Init.c"
#include "../decompile/General/JitPool/JitPool_Add.c"
#include "../decompile/General/JitPool/JitPool_Remove.c"

#include "../decompile/General/LevInstDef/LevInstDef_UnPack.c"
#include "../decompile/General/LevInstDef/LevInstDef_RePack.c"

#include "../decompile/General/LibraryOfModels/LibraryOfModels_Clear.c"
#include "../decompile/General/LibraryOfModels/LibraryOfModels_Store.c"

#include "../decompile/General/LIST/LIST_Clear.c"
#include "../decompile/General/LIST/LIST_AddFront.c"
#include "../decompile/General/LIST/LIST_AddBack.c"
#include "../decompile/General/LIST/LIST_GetNextItem.c"
#include "../decompile/General/LIST/LIST_GetFirstItem.c"
#include "../decompile/General/LIST/LIST_RemoveMember.c"
#include "../decompile/General/LIST/LIST_RemoveFront.c"
#include "../decompile/General/LIST/LIST_RemoveBack.c"
#include "../decompile/General/LIST/LIST_Init.c"

#include "../decompile/General/LOAD/LOAD_A01_Callback_Overlay_Generic.c"
#include "../decompile/General/LOAD/LOAD_A02_Callback_Overlay_230.c"
#include "../decompile/General/LOAD/LOAD_A03_Callback_Overlay_231.c"
#include "../decompile/General/LOAD/LOAD_A04_Callback_Overlay_232.c"
#include "../decompile/General/LOAD/LOAD_A05_Callback_Overlay_233.c"
// hole
#include "../decompile/General/LOAD/LOAD_A07_Callback_Podiums.c"
#include "../decompile/General/LOAD/LOAD_A08_Callback_LEV.c"
#include "../decompile/General/LOAD/LOAD_A09_Callback_LEV_Adv.c"
#include "../decompile/General/LOAD/LOAD_A10_Callback_DriverModels.c"
// hole
#include "../decompile/General/LOAD/LOAD_A12_GlobalModelPtrs_MPK.c"
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
#include "../decompile/General/LOAD/LOAD_A34_GetBigfileIndex.c"
#include "../decompile/General/LOAD/LOAD_A35_AppendQueue.c"
#include "../decompile/General/LOAD/LOAD_A36_CDRequestCallback.c"
#include "../decompile/General/LOAD/LOAD_A37_NextQueuedFile.c"
// hole
#include "../decompile/General/LOAD/LOAD_A41_OvrLOD.c"
#include "../decompile/General/LOAD/LOAD_A42_OvrEndRace.c"
#include "../decompile/General/LOAD/LOAD_A43_OvrThreads.c"
#include "../decompile/General/LOAD/LOAD_A44_GetAdvPackIndex.c"
#include "../decompile/General/LOAD/LOAD_A45_TenStages.c"

#include "../decompile/General/MAIN/MainDB_GetClipSize.c"
#include "../decompile/General/MAIN/MainDB_OTMem.c"
#include "../decompile/General/MAIN/MainDB_PrimMem.c"
#include "../decompile/General/MAIN/MainDrawCb_DrawSync.c"
#include "../decompile/General/MAIN/MainDrawCb_Vsync.c"
#include "../decompile/General/MAIN/MainFrame_RenderFrame.c"
#include "../decompile/General/MAIN/MainFrame_ResetDB.c"
#include "../decompile/General/MAIN/MainInit_JitPoolsNew.c"
#include "../decompile/General/MAIN/MainInit_JitPoolsReset.c"
#include "../decompile/General/MAIN/MainInit_OTMem.c"
#include "../decompile/General/MAIN/MainInit_PrimMem.c"
#include "../decompile/General/MAIN/MainInit_FinalizeInit.c"
#include "../decompile/General/MAIN/MainInit_VRAMClear.c" 
#include "../decompile/General/MAIN/MainInit_VRAMDisplay.c" 

#include "../decompile/General/MATH/MATH_Sin.c"
#include "../decompile/General/MATH/MATH_Cos.c"

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

// skip MENUBOX_DrawPolyGT4
#include "../decompile/General/MenuBox/MENUBOX_DrawOuterRect_Edge.c"
#include "../decompile/General/MenuBox/MENUBOX_DrawTime.c"
// skip MENUBOX_RWD
#include "../decompile/General/MenuBox/MENUBOX_DrawOuterRect_LowLevel.c"
#include "../decompile/General/MenuBox/MENUBOX_DrawOuterRect_HighLevel.c"
// MENUBOX_DrawQuip.c (wip)
// MENUBOX_DrawInnerRect
// MENUBOX_DrawFullRect
#include "../decompile/General/MenuBox/MENUBOX_GetHeight.c"
#include "../decompile/General/MenuBox/MENUBOX_GetWidth.c"
// MENUBOX_DrawSelf.c (wip)
#include "../decompile/General/MenuBox/MENUBOX_ClearInput.c"
#include "../decompile/General/MenuBox/MENUBOX_CollectInput.c"
// MENUBOX_ProcessInput.c (wip)
// MENUBOX_ProcessState.c (wip)
#include "../decompile/General/MenuBox/MENUBOX_Show.c"
#include "../decompile/General/MenuBox/MENUBOX_Hide.c"
#include "../decompile/General/MenuBox/MENUBOX_BoolHidden.c"

#include "../decompile/General/TileView/TileView_Init.c"
#include "../decompile/General/TileView/TileView_SetPsyqGeom.c"
#include "../decompile/General/TileView/TileView_SetDrawEnv_Normal.c"

#include "../decompile/General/THREAD/THREAD_DestroyTracker.c"
#include "../decompile/General/THREAD/THREAD_DestroyInstance.c"
#include "../decompile/General/THREAD/THREAD_DestroyObject.c"
#include "../decompile/General/THREAD/THREAD_DestroySelf_AndBloodline.c"
#include "../decompile/General/THREAD/THREAD_CheckBloodlineForDead.c"
#include "../decompile/General/THREAD/THREAD_CheckAllForDead.c"
#include "../decompile/General/THREAD/THREAD_BirthWithObject.c"
#include "../decompile/General/THREAD/THREAD_CollidePointWithSelf.c"
#include "../decompile/General/THREAD/THREAD_CollidePointWithBucket.c"
#include "../decompile/General/THREAD/THREAD_SearchForModel.c"

#include "../decompile/General/TitleFlag/TitleFlag_t01_MoveModels.c"
#include "../decompile/General/TitleFlag/TitleFlag_t02_IsFullyOnScreen.c"
#include "../decompile/General/TitleFlag/TitleFlag_t03_IsFullyOffScreen.c"
#include "../decompile/General/TitleFlag/TitleFlag_t04_IsTransitioning.c"
#include "../decompile/General/TitleFlag/TitleFlag_t05_SetDrawOrder.c"
#include "../decompile/General/TitleFlag/TitleFlag_t06_BeginTransition.c"
#include "../decompile/General/TitleFlag/TitleFlag_t07_SetFullyOnScreen.c"
#include "../decompile/General/TitleFlag/TitleFlag_t08_SetFullyOffScreen.c"
#include "../decompile/General/TitleFlag/TitleFlag_t09_SetCanDraw.c"
#include "../decompile/General/TitleFlag/TitleFlag_t10_GetCanDraw.c"
#include "../decompile/General/TitleFlag/TitleFlag_t11_GetOT.c"
#include "../decompile/General/TitleFlag/TitleFlag_t12_ResetTextAnim.c"
#include "../decompile/General/TitleFlag/TitleFlag_t13_DrawLoadingString.c"
#include "../decompile/General/TitleFlag/TitleFlag_t14_DrawSelf.c"

// RCNT (watch namespace, not alphabetical)
#include "../decompile/General/RCNT/RCNT_Init.c"

// UI
#include "../decompile/General/UI/UI_Map_DrawMap.c"

// 230
#include "../decompile/General/230/R230.c"
#include "../decompile/General/230/D230.c"
#include "../decompile/General/230/1_Block1.c"
#include "../decompile/General/230/230_39_MM_AdvNewLoad_GetMenuBox.c"
#include "../decompile/General/230/1_Block2.c"
#include "../decompile/General/230/230_57_MM_TrackSelect_GetMenuBox.c"
#include "../decompile/General/230/1_Block3.c"