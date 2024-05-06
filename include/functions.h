// included from common.h, do not include common.h

// remember to ctrl + f ctrl + r the DECOMP_ prefix

// BOTS

void BOTS_SetGlobalNavData(u_short index);
void BOTS_InitNavPath(struct GameTracker* gGT, short index);
void BOTS_EmptyFunc();
int BOTS_Adv_NumTimesLostEvent(int index);
void BOTS_Adv_AdjustDifficulty();
void BOTS_UpdateGlobals();
void BOTS_SetRotation(struct Driver* driver_perhaps, int param_2);
void BOTS_LevInstColl(int param_1);
void BOTS_ThTick_RevEngine (struct Thread * thread, u_int param_2, u_char * param_3, u_int param_4);
void BOTS_MaskGrab(int param_1);
void BOTS_Killplane(int param_1);
void BOTS_ThTick_Drive(struct Thread* thread);
u_int BOTS_ChangeState(struct Driver* d1, int param_2, struct Driver* d2, int param_4);
void BOTS_CollideWithOtherAI(int param_1, int param_2);
void BOTS_GotoStartingLine(struct Driver* driver);
struct Driver* BOTS_Driver_Init(int driverID);
void BOTS_Driver_Convert(struct Driver* driver);

// CAM

void CAM_SkyboxGlow(short* param_1, struct PushBuffer* pb, struct PrimMem* primMem, u_long* ptrOT);
void CAM_ClearScreen(struct GameTracker* gGT);
void CAM_Init(struct CameraDC* cDC, int cameraID, struct Driver* d, struct PushBuffer* pb);
void CAM_FindClosestQuadblock(short* scratchpad, struct CameraDC* cDC, struct Driver* d, short* param_4);
int CAM_Path_GetNumPoints();
u_int CAM_Path_Move(int frame, u_short* pos, u_short* rot, u_short* getPath);
void CAM_StartOfRace(struct CameraDC* cDC);
void CAM_EndOfRace_Battle(struct CameraDC* cDC, struct Driver* d);
void CAM_EndOfRace(struct CameraDC* cDC, struct Driver* d);
u_char* CAM_StartLine_FlyIn_FixY(u_short* param_1);
void CAM_ProcessTransition(short* camPosReturn, u_short* camRotReturn, short* camPosDest, short* camRotDest, short* camPosStart, short* camRotStart, int frame);
void CAM_FollowDriver_AngleAxis(struct CameraDC* cDC, struct Driver* d, int param_3, short* pushBufferPos, short* pushBufferRot);
void CAM_StartLine_FlyIn(int* param_1, short const0x96, int frame, u_short* camTransitionToPos, short* camTransitionToRot);
u_int CAM_FollowDriver_TrackPath(struct CameraDC* cDC, short* param_2, int cDCspeed, int param_4);
void CAM_LookAtPosition(int param_1, int* driverPos, short* camTransitionToPos, short* camTransitionToRot);
void CAM_FollowDriver_Spin360(struct CameraDC* cDC, u_int param_2, struct Driver* d, short* camTransitionToPos, u_int param_5);
void CAM_SetDesiredPosRot(int param_1, u_short* param_2, u_short* param_3);
void CAM_FollowDriver_Normal(struct CameraDC* cDC, struct Driver* d, short* pushBuffer, int scratchpad, short* param_5);
int CAM_MapRange_PosPoints(short* vec3sPos1, short* vec3sPos2, short* vec3iPos);
void CAM_ThTick(struct Thread* t);

// CDSYS

u_int CDSYS_Init(int useDisc);
u_int CDSYS_GetFilePosInt(char* fileString, int* filePos);
void CDSYS_SetMode_StreamData();
void CDSYS_SetMode_StreamAudio();
u_int CDSYS_SetXAToLang(int lngIndex);
void CDSYS_XaCallbackCdSync(char result);
void CDSYS_XaCallbackCdReady(char result);
void CDSYS_SpuCallbackIRQ();
void CDSYS_SpuCallbackTransfer();
void CDSYS_SpuEnableIRQ();
void CDSYS_SpuDisableIRQ();
void CDSYS_SpuGetMaxSample();
u_int CDSYS_XAGetNumTracks(int categoryID);
u_int CDSYS_XASeek(int isCdControl, int categoryID, int audioTrackID);
u_int CDSYS_XAGetTrackLength(int categoryID, int audioTrackID);
void CDSYS_XAPlay(int categoryID, int index);
void CDSYS_XAPauseRequest();
void CDSYS_XAPauseForce();
void CDSYS_XAPauseAtEnd();

// COLL

u_char* COLL_LevModelMeta(u_int index);
u_int COLL_Instance(short* param_1, struct BSP* node);
void COLL_PerBspLeaf_CheckInstances(struct BSP* node, struct ScratchpadStruct *sps);
void COLL_StartSearch_AI(short* posCurr, short* posPrev, short* param_3);
void COLL_StartSearch_Player(struct Thread* t, struct Driver* d);
void COLL_SearchTree_FindQuadblock_Touching(u_int* posTop, u_int* posBottom, u_int* param_3, int param_4);
void COLL_SearchTree_FindX(struct BSP* param_1, struct BoundingBox* bbox, u_int* callback, u_int param_4);
u_int FUN_8001ede4(u_short* param_1, short* param_2, short* param_3, short* param_4);
void FUN_8001ef1c();
void FUN_8001ef50(int param_1, short* param_2, short* param_3, short* param_4);
void FUN_8001f2dc(int param_1, short* param_2, short* param_3, short* param_4);
void COLL_PerQuadblock_CheckTriangles_Touching(struct QuadBlock* qb, struct ScratchpadStruct *sps);
void COLL_PerBspLeaf_CheckQuadblocks_Touching(struct BSP* node, struct ScratchpadStruct *sps);
void FUN_8001f67c(int param_1, int param_2);
void FUN_8001f6f0(int param_1, int param_2);
void FUN_8001f7f0(int param_1);
u_int FUN_8001f928(u_int* param_1, u_int* param_2, u_int* param_3, u_int* param_4);
void FUN_8001fc40(u_int* param_1, int param_2, u_int param_3, u_int param_4);
void COLL_PerQuadblock_CheckTriangles_NearPlayer(struct QuadBlock* qb, struct ScratchpadStruct *sps);
void COLL_PerBspLeaf_CheckQuadblocks_NearPlayer(struct BSP* node, struct ScratchpadStruct *sps);
void FUN_80020334(struct QuadBlock* qb, int triangleID, int param_3);
void COLL_StartSearch_NearPlayer(struct Thread* t, struct Driver* d);
u_int COLL_Scrub(struct Driver* d, struct Thread* t, int param_3, int param_4, int* param_5);

// CTR

void CTR_Box_DrawWirePrims(u_short x, u_short y, u_short u, u_short v, u_char r, u_char g, u_char b, u_long* otMem, struct PrimMem* primMem);
void CTR_Box_DrawWireBox(RECT* r, int* unk, u_long* ot, struct PrimMem* primMem);
void CTR_Box_DrawClearBox(RECT* r, u_int* rgb, int param_3, u_long* otMem, struct PrimMem* primMem);
void CTR_Box_DrawSolidBox(RECT* r, u_int* rgb, u_long* otMem, struct PrimMem* primMem);
void CTR_CycleTex_LEV(struct AnimTex* animtex, int timer);
void CTR_CycleTex_Model(struct AnimTex* pAnimTexArray, int timer);
void CTR_CycleTex_AllModels(unsigned int numModels, struct Model** pModelArray, int timer);
//CTR_CycleTex_2p3p4pWumpaHUD();
void CTR_ClearRenderLists_1P2P(struct GameTracker* gGT, int numPlyrCurrGame);
void CTR_ClearRenderLists_3P4P(struct GameTracker* gGT, int numPlyrCurrGame);
void CTR_EmptyFunc_MainFrame_ResetDB();
void CTR_ErrorScreen(char r, char g, char b);
void CTR_MatrixToRot(SVECTOR *rot, MATRIX *matrix, u_int flags);
//CTR_ScrambleGhostString();

// DebugFont

void DebugFont_Init(struct GameTracker* gGT);
void DebugFont_DrawNumbers(int param_1, u_int param_2, int param_3);

// DecalFont

#if BUILD == JpnRetail
	u_int DecalFont_boolRacingWheel();
#endif
int DecalFont_GetLineWidthStrlen(char* str, short len, short fontType);
int DecalFont_GetLineWidth(char* str, short fontType);
void DecalFont_DrawLineStrlen(char* str, short len, int posX, int posY, short fontType, int flags);
void DecalFont_DrawLine(char* str, int posX, int posY, short fontType, int flags);
void DecalFont_DrawLineOT(char* str, int posX, int posY, short fontType, int flags, u_long* ot);
int DecalFont_DrawMultiLineStrlen(char *str, short len, short posX, short posY, short maxPixLen, short fontType, short flags);
int DecalFont_DrawMultiLine(char* str, int posX, int posY, int maxPixLen, short fontType, int flags);

// DecalGlobal

void DecalGlobal_EmptyFunc_MainFrame_ResetDB();
void DecalGlobal_Clear(struct GameTracker* gGT);
void DecalGlobal_Store(struct GameTracker* gGT, struct Icon* icon); // second parameter might be wrong --Super
int* DecalGlobal_FindInLEV(struct Level* level, char* str);
int* DecalGlobal_FindInMPK(u_int* param_1, char* str);

// DecalHUD

void DecalHUD_DrawPolyFT4(struct Icon* icon, short posX, short posY, struct PrimMem* primMem, u_long* ot, char transparency, short scale);
void DecalHUD_DrawWeapon(struct Icon* icon, short posX, short posY, struct PrimMem* primMem, u_long* ot, char transparency, short scale, char rot);
void DecalHUD_DrawPolyGT4(struct Icon* icon, short posX, short posY, struct PrimMem* primMem, u_long* ot, u_int color0, u_int color1, u_int color2, u_int color3, char transparency, short scale);
void DecalHUD_Arrow2D(struct Icon* icon, short posX, short posY, struct PrimMem* primMem, u_long *otMemPtr, u_int color1, u_int color2, u_int color3, u_int color4, char transparency, short scale, u_short rot);

// DecalMP

void DecalMP_01(struct GameTracker* gGT);
void DecalMP_02(struct GameTracker* gGT);
void DecalMP_03(struct GameTracker* gGT);

// DISPLAY

//DISPLAY_Blur_SubFunc()
void DISPLAY_Blur_Main(struct PushBuffer* pb, int strength);
//DISPLAY_SWap()

// DotLights

//DotLights_Video()
void DotLights_AudioAndVideo(struct GameTracker* gGT);

// DropRain

void DropRain_MakeSound(struct GameTracker* gGT);
void DropRain_Reset(struct GameTracker* gGT);

// ElimBG

void ElimBG_SaveScreenshot_Chunk(void *img1,void *img2,int param_3);
void ElimBG_SaveScreenshot_Full(struct GameTracker* gGT);
void ElimBG_Activate(struct GameTracker* gGT);
void ElimBG_ToggleInstance(struct Instance* inst, int boolGameIsPaused);
void ElimBG_ToggleAllInstances(struct GameTracker* gGT, int boolGameIsPaused);
void ElimBG_HandleState(struct GameTracker* gGT);
void ElimBG_Deactivate(struct GameTracker* gGT);

// FLARE

//FLARE_ThTick()
//FLARE_Init()

// GAMEPAD

void GAMEPAD_Init(struct GamepadSystem* gGamepads);
//GAMEPAD_SetMainMode()
//GAMEPAD_ProcessState()
void GAMEPAD_PollVsync(struct GamepadSystem* gGamepads);
int GAMEPAD_GetNumConnected(struct GamepadSystem* gGamepads);
void GAMEPAD_ProcessHold(struct GamepadSystem* gGamepads);
void GAMEPAD_ProcessSticks(struct GamepadSystem* gGamepads);
void GAMEPAD_ProcessTapRelease(struct GamepadSystem* gGamepads);
void GAMEPAD_ProcessMotors(struct GamepadSystem* gGamepads);
void GAMEPAD_ProcessAnyoneVars(struct GamepadSystem* gGamepads);
void GAMEPAD_JogCon1(struct Driver* driver, char param_2, u_short param_3);
void GAMEPAD_JogCon2(struct Driver* driver, char param_2, u_short param_3);
void GAMEPAD_ShockFreq(struct Driver* driver, char param_2, u_short param_3);
void GAMEPAD_ShockForce1(struct Driver* driver, char param_2, u_short param_3);

// GAMEPROG

void GAMEPROG_AdvPercent(struct AdvProgress* adv);
void GAMEPROG_ResetHighScores(struct GameProgress* gameProg);
int GAMEPROG_CheckGhostsBeaten(int ghostID);
void GAMEPROG_NewProfile_OutsideAdv(struct GameProgress* gameProg);
void GAMEPROG_InitFullMemcard(struct MemcardProfile* mcp);
void GAMEPROG_NewProfile_InsideAdv(struct AdvProgress* adv);
void GAMEPROG_SaveCupProgress();
void GAMEPROG_SyncGameAndCard(struct GameProgress* memcardProg, struct GameProgress* currentProg);
void GAMEPROG_NewGame_OnBoot();
void GAMEPROG_GetPtrHighScoreTrack();

// GhostBuffer

//void GhostReplay_ThTick();
//GhostReplay_Init1()
//GhostTape_Start()
//GhostTape_End()
void GhostTape_WriteMoves(short param_1);
void GhostTape_WriteBoosts(int reserves, u_char type, int fireLevel);
void GhostTape_Destroy();

// OtherFX

short CountSounds();
int OtherFX_Play(unsigned int soundID, int flags);
void OtherFX_Play_Echo(unsigned int soundID, int flags, int echoFlag);
int OtherFX_Play_LowLevel(u_int soundID, u_char flags1, u_int flags2);
//OtherFX_Modify()
void OtherFX_Stop1(int soundID_count);
void OtherFX_Stop2(int soundID_count);

// EngineAudio

char EngineAudio_InitOnce(u_int soundID, u_int flags);
short EngineAudio_Recalculate(u_int soundID, u_int sfx);
void EngineAudio_Stop(u_int soundID);

// More OtherFX?

//SetReverbMode()

// CseqMusic

int CseqMusic_Start(int songID, int param_2, int param_3, int param_4, int param_5);
void CseqMusic_Pause();
void CseqMusic_Resume();
void CseqMusic_ChangeVolume(int songID, int param_2, int param_3);
void CseqMusic_Restart(int songID, int param_2);
void CseqMusic_ChangeTempo(int songID, int param_2);
//CseqMusic_AdvHubSwap()
void CseqMusic_Stop(int songID);
void CseqMusic_StopAll();

// Bank

//Bank_ResetAllocator()
//Bank_Alloc()
//Bank_AssignSpuAddrs()
//Bank_Destroy()
//Bank_ClearInRange()
//Bank_Load()
//Bank_DestroyLast()
//Bank_DestroyUntilIndex()
//Bank_DestroyAll()

// from this point onward it's an absolute mess

	// howl


	//howl_LoadHeader()
	//howl_SetSong()
	//howl_LoadSong()
	//howl_ErasePtrCseqHeader()
	//howl_GetNextNote()

	// cseq opcode

	//cseq_opcode01_noteoff()
	//cseq_opcode03()

	// more howl

	//howl_InitChannelAttr_Music()

	// more cseq opcode

	//cseq_opcode_from06and07()
	//cseq_opcode05_noteon()
	//cseq_opcode06()
	//cseq_opcode07()
	//cseq_opcode08()
	//cseq_opcode09()
	//cseq_opcode0a()

	// SongPool

	//SongPool_FindFreeChannel()
	//SongPool_CalculateTempo()
	void SongPool_ChangeTempo(struct Song* song, short p2);
	
	void SongPool_Start(
		struct Song* song, int songID, int deltaBPM,
		int boolLoopAtEnd, struct SongSet* songSet, int songSetActiveBits);

	
	void SongPool_Volume(struct Song* song, char param_2, char param_3, int param_4);
	//SongPool_AdvHub1()
	//SongPool_AdvHub2()
	//SongPool_StopCseq()
	void SongPool_StopAllCseq(struct Song* song);

	// even more howl

	//howl_Disable()

	// UpdateChannelVol

	//UpdateChannelVol_EngineFX()
	//UpdateChannelVol_OtherFX()
	//UpdateChannelVol_Music()
	//UpdateChannelVol_EngineFX_All()
	//UpdateChannelVol_Music_All()
	//UpdateChannelVol_OtherFX_All()

	// not even the last of howl


	// OptionsMenu...

	void OptionsMenu_TestSound(int param_1, int param_2);

	// Smart (?)

	void Smart_EnterCriticalSection();
	void Smart_ExitCriticalSection();

	// Channel

	void Channel_SetVolume(struct ChannelAttr* attr, int volume, int LR);
	struct ChannelStats* Channel_FindSound(int soundID);
	struct ChannelStats* Channel_AllocSlot_AntiSpam(short soundID, char boolUseAntiSpam, int flags, struct ChannelAttr* attr);
	struct ChannelStats* Channel_AllocSlot(int flags, struct ChannelAttr* attr);
	struct ChannelStats* Channel_SearchFX_EditAttr(int type, int soundID, int updateFlags, struct ChannelAttr* attr);
	void Channel_SearchFX_Destroy(int type, int soundID, int flags);
	void Channel_DestroyAll_LowLevel(int opt1, int boolKeepMusic, char type);
	//Channel_ParseSongToChannels()
	//Channel_UpdateChannels()

	// Cutscene (?)

	void Cutscene_VolumeBackup();
	void Cutscene_VolumeRestore();

	// this is the last of ho- got em

	// Voiceline

	//Voiceline_PoolInit()
	void Voiceline_ClearTimeStamp();
	//Voiceline_PoolClear()
	//Voiceline_StopAll()
	//Voiceline_ToggleEnable()
	void Voiceline_RequestPlay(int, short, int);
	//Voiceline_StartPlay()
	//Voiceline_Update()
	//Voiceline_EmptyFunc()
	//Voiceline_SetDefaults()

	// Audio

	//Audio_SetState()
	void Audio_SetState_Safe(int param_1);
	void Audio_AdvHub_SwapSong(int levelID);
	//Audio_SetMaskSong()
	void Audio_Update1();
	//Audio_SetDefaults()
	//Audio_SetReverbMode()

	// Music

	void Music_SetIntro();
	void Music_LoadBanks();
	u_int Music_AsyncParseBanks();
	//Music_SetDefaults()
	//Music_Adjust()
	//Music_LowerVolume()
	//Music_RaiseVolume()
	void Music_Restart();
	void Music_Stop();
	void Music_Start(u_short param_1);
	void Music_End();
	//Music_GetHighestSongPlayIndex()

	// GTE (?)

	//GTE_AudioLR_Inst()
	void GTE_AudioLR_Driver(MATRIX *m,struct Driver *d,u_int *param_3);
	//GTE_GetSquaredLength()

	// Even more OtherFX...

	//void OtherFX_RecycleNew(u_int* param_1, u_int param_2, u_int param_3);
	void OtherFX_RecycleMute(int* param_1);
	//OtherFX_DriverCrashing()

	// uh...

	//GTE_GetSquaredDistance()
	//CalculateVolumeFromDistance()
	void PlayWarppadSound(u_int param_1);

	// Level (?)

	//Level_SoundLoopSet()
	//Level_SoundLoopFade()
	//Level_RandomFX()
	//Level_AmbientSound()

	// PlaySound3D

	void PlaySound3D(u_int soundID, struct Instance* inst);
	void PlaySound3D_Flags(u_int* flags, u_int soundID, struct Instance* inst);

	// EngineSound

	//EngineSound_Player()
	//EngineSound_VolumeAdjust()
	//EngineSound_AI()
	//EngineSound_NearestAIs()

	// Garage

	void Garage_Init();
	void Garage_Enter(char characterID);
	void Garage_PlayFX(u_int soundID, char characterID);
	void Garage_LerpFX();
	void Garage_MoveLR(int desiredID);
	void Garage_Leave();

// okay finally we're done with that

// INSTANCE

void INSTANCE_Birth(struct Instance* inst, struct Model* model, char* name, struct Thread* th, int flags);
struct Instance* INSTANCE_Birth3D(struct Model* m, char* name, struct Thread* t);
struct Instance* INSTANCE_Birth2D(struct Model* model, char* name, struct Thread* th);
struct Instance* INSTANCE_BirthWithThread(int modelID, char* name, int poolType, int bucket, void* funcThTick, int objSize, struct Thread* parent);
struct Instance* INSTANCE_BirthWithThread_Stack(int* spArr);
void INSTANCE_Death(struct Instance* inst);
void INSTANCE_LevInitAll(struct InstDef* instDef, int num);
void INSTANCE_LevDelayedLInBs(void* instDefs, u_int numInstances);

// not really part of "INSTANCE" namespace
int VehFrameInst_GetNumAnimFrames(struct Driver* driver, int param_2);
int VehFrameInst_GetStartFrame(int midpoint, int numFrames);

// JitPool

void JitPool_Clear(struct JitPool* AP);
void JitPool_Init(struct JitPool* AP, int maxItems, int itemSize, char* name);
int JitPool_Add(struct JitPool* AP);
void JitPool_Remove(struct JitPool* AP, struct Item* item);

// LevInstDef

void LevInstDef_UnPack(struct mesh_info* mInfo);
void LevInstDef_RePack(struct mesh_info* mInfo, int param_2);

// LHMatrix?

void LHMatrix_Parent(struct Instance* inst, struct Instance* driverInst, SVECTOR* param_3);

// LibraryOfModels

void LibraryOfModels_Store(struct GameTracker* gGT, int param_2, int* param_3);
void LibraryOfModels_Clear(struct GameTracker* gGT);

// LinkedCollide

struct Instance* LinkedCollide_Radius(struct Instance* objInst, struct Thread* _objTh, struct Thread* thBucket, unsigned int hitRadius);
struct Instance* LinkedCollide_Hitbox_Desc(struct HitboxDesc* objBoxDesc);
//LinkedCollide_Hitbox()

// LIST

void LIST_Clear(struct LinkedList* L);
void LIST_AddFront(struct LinkedList* L, struct Item* I);
void LIST_AddBack(struct LinkedList* L, struct Item* I);
void* LIST_GetNextItem(struct Item* I);
void* LIST_GetFirstItem(struct LinkedList* L);
struct Item* LIST_RemoveMember(struct LinkedList* L, struct Item* I);
struct Item* LIST_RemoveFront(struct LinkedList* L);
struct Item* LIST_RemoveBack(struct LinkedList* L);
//LIST_Init()

// LOAD

void LOAD_Callback_Overlay_Generic();
void LOAD_Callback_Overlay_230();
void LOAD_Callback_Overlay_231();
void LOAD_Callback_Overlay_232();
void LOAD_Callback_Overlay_233();
void LOAD_Callback_MaskHints3D(struct LoadQueueSlot* lqs);
void LOAD_Callback_Podiums(struct LoadQueueSlot* lqs);
void LOAD_Callback_LEV(struct LoadQueueSlot* lqs);
void LOAD_Callback_LEV_Adv(struct LoadQueueSlot* lqs);
void LOAD_Callback_DriverModels(struct LoadQueueSlot* lqs);
//LOAD_HubCallback()
void LOAD_GlobalModelPtrs_MPK();
void LOAD_HubSwapPtrs(struct GameTracker* gGT);
void LOAD_StringToUpper(u_char *param_1);
void LOAD_InitCD();
void* LOAD_ReadDirectory(char* filepath);
//LOAD_DramFileCallback()
//LOAD_DramFile()
void LOAD_VramFileCallback(struct LoadQueueSlot* lqs);
u_int LOAD_VramFile(struct BigHeader* bigfile, u_int fileIndex, u_int* destination, u_int* sizePtr, int callback);
void LOAD_ReadFileASyncCallback();
u_long* LOAD_ReadFile(struct BigHeader* bigfile, u_int loadType, u_int fileIndex, u_int* destination, u_int* sizePtr, int callback);
void* LOAD_ReadFile_NoCallback(char* file, void* addr, int* size);
//LOAD_FindFile()

// these are the last howl functions ever

//LOAD_HowlHeaderSectors()
//LOAD_HowlCallback()
//LOAD_HowlSectorChainStart()
//LOAD_HowlSectorChainEnd()

// more LOAD

void LOAD_RunPtrMap(char* file, void* map, int size);
void LOAD_Robots2P(int bigfile, int p1, int p2, int callback);
void LOAD_Robots1P(int characterID);
void LOAD_DriverMPK(struct BigHeader* bigfile, int levelLOD, void* callback);
void LOAD_LangFile(int bigfilePtr, int lang);
int LOAD_GetBigfileIndex(unsigned int levelID, int lod, int fileType);
void LOAD_AppendQueue(int bigfile, int type, int fileIndex, void* destinationPtr, void* callback);
void LOAD_CDRequestCallback(struct LoadQueueSlot* lqs);
void LOAD_NextQueuedFile();
//LOAD_Hub_ReadFile()
void LOAD_Hub_SwapNow();
void LOAD_Hub_Main(struct BigHeader* bigfile);
void LOAD_OvrLOD(int param_1);
void LOAD_OvrEndRace(u_int* param_1);
void LOAD_OvrThreads(u_int param_1);
int LOAD_GetAdvPackIndex();
int LOAD_TenStages(struct GameTracker* gGT, int loadingStage, struct BigHeader* bigfile);
void LOAD_TalkingMask(int, int);
void LOAD_LevelFile(int levelID);
int LOAD_IsOpen_RacingOrBattle();
int LOAD_IsOpen_MainMenu();
int LOAD_IsOpen_AdvHub();
int LOAD_IsOpen_Podiums();

// MainDB

u_int MainDB_GetClipSize(u_int levelID, int numPlyrCurrGame);
void MainDB_PrimMem(struct PrimMem* primMem, u_int size);
void MainDB_OTMem(struct OTMem* otMem, u_int size);

// MainDrawCb

void MainDrawCb_DrawSync();
void MainDrawCb_Vsync();

// MainFrame

void MainFrame_TogglePauseAudio(int bool_pause);
//void MainFrame_ResetDB(struct GameTracker* gGT);
void MainFrame_GameLogic(struct GameTracker* gGT, struct GamepadSystem* gGamepads);
void MainFrame_VisMemFullFrame(struct GameTracker* gGT, struct Level* level);
void MainFrame_InitVideoSTR(u_int boolPlayVideoStr, RECT* r, short posX, short posY);
int MainFrame_HaveAllPads(short param_1);
void MainFrame_RequestMaskHint();
void MainFrame_RenderFrame(struct GameTracker* gGT, struct GamepadSystem* gGamepads);

// MainFreeze

void MainFreeze_ConfigDrawNPC105(short startX, short startY, short param_3, int param_4, short param_5, char *color, u_long *otMem, struct PrimMem *primMem);
void MainFreeze_ConfigDrawArrows(int posX, int posY, char* str);
void MainFreeze_ConfigSetupEntry();
void MainFreeze_MenuPtrOptions(struct RectMenu* menu);
void MainFreeze_MenuPtrQuit(struct RectMenu* menu);
void MainFreeze_SafeAdvDestroy();
void MainFreeze_MenuPtrDefault(struct RectMenu* menu);
struct RectMenu* MainFreeze_GetMenuPtr();
void MainFreeze_IfPressStart();

// MainGameEnd

//MainGameEnd_SoloRaceGetReward()
//MainGameEnd_SoloRaceSaveHighScore()
//void MainGameEnd_Initialize(short);

// MainGameStart (?)

//MainGameStart_Initialize()

// MainInit

void MainInit_VisMem(struct GameTracker* gGT);
//MainInit_RainBuffer()
void MainInit_PrimMem(u_int* param_1);
//MainInit_JitPoolsReset()
void MainInit_OTMem(u_int* param_1);
void MainInit_JitPoolsNew(u_int* param_1);
void MainInit_Drivers(struct GameTracker *gGT);
void MainInit_FinalizeInit();
int MainInit_StringToLevID(char* str);
void MainInit_VRAMClear();
void MainInit_VRAMDisplay();

// MainKillGame

//MainKillGame_StopCTR()
void MainKillGame_LaunchSpyro2();

// MainLoadVLC

//MainLoadVLC_Callback()
void MainLoadVLC();

// main

u_int main();

// MainRaceTrack

void MainRaceTrack_StartLoad(short levelID);
void MainRaceTrack_RequestLoad(short levelID);

// MainStats

void MainStats_ClearBattleVS();
void MainStats_RestartRaceCountLoss();

// MATH

int MATH_Sin(u_int angle);
int MATH_Cos(u_int angle);
int MATH_FastSqrt(int dist, int unk);
MATRIX* MATH_HitboxMatrix(MATRIX* output, MATRIX* input);
void MATH_VectorLength(VECTOR* input);
int MATH_VectorNormalize(VECTOR* input);
void MATH_MatrixMul(MATRIX* output, MATRIX* input,VECTOR* rotate);

// MEMCARD

void MEMCARD_SetIcon(int iconID);
unsigned int MEMCARD_CRC16(unsigned int crc, int nextByte);
void MEMCARD_ChecksumSave(unsigned char* saveBytes, int len);
unsigned int MEMCARD_ChecksumLoad(unsigned char* saveBytes, int len);
char *MEMCARD_StringInit(int slotIndex, char *dstString);
void MEMCARD_StringSet(char *dstString, int slotIdx, char *srcString);
void MEMCARD_InitCard();
void MEMCARD_CloseCard();
uint8_t MEMCARD_GetNextSwEvent(void);
uint8_t MEMCARD_GetNextHwEvent(void);
//MEMCARD_WaitForHwEvent()
void MEMCARD_SkipEvents(void);
int MEMCARD_NewTask(int slotIdx, char *name, uint8_t *ptrMemcard, int memcardFileSize);
void MEMCARD_CloseFile(void);
int MEMCARD_ReadFile(int start_offset, int end_offset);
uint8_t MEMCARD_WriteFile(int start_offset, const uint8_t *data, int end_offset);
void MEMCARD_GetFreeBytes(int slotIdx);
uint8_t MEMCARD_GetInfo(int slotIdx);
//MEMCARD_Load()
//MEMCARD_Save()
uint8_t MEMCARD_Format(int slotIdx);
uint8_t MEMCARD_IsFile(int slotIdx, char *save_name);
char *MEMCARD_FindFirstGhost(int slotIdx, char *srcString);
char *MEMCARD_FindNextGhost(void);
uint8_t MEMCARD_EraseFile(int slotIdx, char *srcString);

// MEMPACK

void MEMPACK_Init(int ramSize);
void MEMPACK_SwapPacks(int index);
void MEMPACK_NewPack_StartEnd(void* start, int size);
u_int MEMPACK_GetFreeBytes();
void* MEMPACK_AllocMem(int allocSize); // also has a second parameter? --Super
//void* MEMPACK_AllocHighMem(int allocSize, char*);
void MEMPACK_ClearHighMem();
void* MEMPACK_ReallocMem(int allocSize);
int MEMPACK_PushState();
void MEMPACK_ClearLowMem();
void MEMPACK_PopState();
void MEMPACK_PopToState(int id);

int MixRNG_Scramble();
int MixRNG_Particles(int numParticle);
u_int MixRNG_GetValue(int val);

// Particle

//Particle_FuncPtr_PotionShatter()
void Particle_FuncPtr_SpitTire();
//Particle_FuncPtr_ExhaustUnderwater()
//Particle_OnDestroy()
//Particle_UpdateList()
void Particle_UpdateAllParticles();
//Particle_BitwiseClampByte()
//Particle_SetColors()
void Particle_RenderList(struct PushBuffer* pb, void* particleList);
struct Particle* Particle_Init(u_int param_1, struct IconGroup* ig, struct ParticleEmitter* pe);

// PickupBots (?)

//PickupBots_Init()
void PickupBots_Update();

// PlayLevel (?)

void PlayLevel_UpdateLapStats();

// Tawna (?)

void Podium_InitModels(struct GameTracker* gGT);

// THREAD

void PROC_DestroyTracker(struct Thread* t);
void PROC_DestroyInstance(struct Thread* t);
void PROC_DestroyObject(void* object, int threadFlags);
void PROC_DestroySelf(struct Thread* t);
void PROC_DestroyBloodline(struct Thread* t);
void PROC_CheckBloodlineForDead(struct Thread** replaceSelf, struct Thread* th);
void PROC_CheckAllForDead();
struct Thread* PROC_BirthWithObject(u_int creationFlags, void* behaviorFuncPtr, char* debugName, struct Thread* threadRelative);
void PROC_CollidePointWithSelf(struct Thread* th, void* buf);
void PROC_CollidePointWithBucket(struct Thread* th, short* vec3_pos);
struct Thread* PROC_SearchForModel(struct Thread* th, int modelID);
void PROC_PerBspLeaf_CheckInstances(struct BSP* bspLeaf, struct ScratchpadStruct* param_2);
void PROC_StartSearch_Self(struct ScratchpadStruct* SPS);
void PROC_CollideHitboxWithBucket(struct Thread* param_1, struct ScratchpadStruct* param_2, struct Thread* param_3);

// PushBuffer

void PushBuffer_Init(struct PushBuffer* pb, int id, int total);
//PushBuffer_SetPsyqGeom()
void PushBuffer_SetDrawEnv_DecalMP(u_long*, struct DB*, short, short, short, short, short, short, short, short);
void PushBuffer_SetDrawEnv_Normal(u_long* ot, struct PushBuffer* pb, struct DB* backBuffer, short* param_4, u_char param_5);
void PushBuffer_SetMatrixVP(struct PushBuffer* pb);
//PushBuffer_SetFrustumPlane()
void PushBuffer_UpdateFrustum(struct PushBuffer* pb);
void PushBuffer_FadeOneWindow(struct PushBuffer* pb);
void PushBuffer_FadeAllWindows();

// QueueLoadTrack

//QueueLoadTrack_MenuProc()
//QueueLoadTrack_GetMenuPtr()

// RaceConfig

//RaceConfig_LoadGameOptions()
//RaceConfig_SaveGameOptions()

// TitleFlag

//RaceFlag_MoveModels()
u_int RaceFlag_IsFullyOnScreen();
u_int RaceFlag_IsFullyOffScreen();
u_int RaceFlag_IsTransitioning();
//RaceFlag_SetDrawOrder()
void RaceFlag_BeginTransition(int param_1);
void RaceFlag_SetFullyOnScreen();
void RaceFlag_SetFullyOffScreen();
void RaceFlag_SetCanDraw(int enable);
int RaceFlag_GetCanDraw();
u_long* RaceFlag_GetOT();
void RaceFlag_ResetTextAnim();
void RaceFlag_DrawLoadingString();
void RaceFlag_DrawSelf();

// RECTMENU
void RECTMENU_DrawOuterRect_Edge(RECT* r, u_int rgb, u_int param_3, u_long* otMem);
u_char* RECTMENU_DrawTime(int milliseconds);
void RECTMENU_DrawRwdBlueRect_Subset(short *pos, int *color, u_long *ot, struct PrimMem *primMem);
void RECTMENU_DrawRwdBlueRect(RECT *rect, char *metas, u_long *ot, struct PrimMem *primMem);
void RECTMENU_DrawRwdTriangle (short * position, char * color, u_long * otMem, struct PrimMem * primMem);
void RECTMENU_DrawOuterRect_LowLevel(RECT* r, short x, u_short y, u_int* rgb, short param_5, u_long* otMem);
void RECTMENU_DrawOuterRect_HighLevel(RECT* r, u_int* rgb, u_int param_3, u_long* otMem);
void RECTMENU_DrawQuip(char*, short, short, short, short, int, short);
void RECTMENU_DrawInnerRect(RECT* r, int flag, u_long* ot);
void RECTMENU_DrawFullRect(struct RectMenu* menu, RECT* r);
//RECTMENU_GetHeight()
void RECTMENU_GetWidth(struct RectMenu* m, RECT* r, int);
void RECTMENU_DrawSelf(struct RectMenu* m, int, int, int);
void RECTMENU_ClearInput();
void RECTMENU_CollectInput();
//void RECTMENU_ProcessInput(struct RectMenu* m);
void RECTMENU_ProcessState();
void RECTMENU_Show(struct RectMenu* m);
void RECTMENU_Hide(struct RectMenu* m);
int RECTMENU_BoolHidden(struct RectMenu* m);

// GhostData (?)

//RefreshCard_BoolGhostForLEV()
//RefreshCard_NextMemcardAction()
//RefreshCard_GhostEncodeByte()
//RefreshCard_GhostDecodeByte()
//RefreshCard_GhostEncodeProfile()
//RefreshCard_GhostDecodeProfile()
void RefreshCard_StartMemcardAction(int action);
//RefreshCard_StopMemcardAction()
//RefreshCard_GetNumGhostsTotal()

// Load...

//RefreshCard_GameProgressAndOptions()
void RefreshCard_Entry();
void SelectProfile_QueueLoadHub_MenuProc(struct RectMenu* menu);
//SelectProfile_ThTick()
//SelectProfile_PrintInteger()
//SelectProfile_UI_ConvertX()
//SelectProfile_UI_ConvertY()
//SelectProfile_DrawAdvProfile()
//SelectProfile_GetTrackID()
//SelectProfile_Init()
void SelectProfile_Destroy();
void SelectProfile_AdvPickMode_MenuProc(struct RectMenu* menu);
//SelectProfile_DrawGhostProfile()
void SelectProfile_MuteCursors();
void SelectProfile_UnMuteCursors();
void SelectProfile_ToggleMode(u_int param_1);
//SelectProfile_InitAndDestroy()
u_int SelectProfile_InputLogic(struct RectMenu* menu, short param_2, u_int confirm);
//SelectProfile_AllProfiles_MenuProc()

// SubmitName

//SubmitName_RestoreName()
short SubmitName_DrawMenu(u_short stringID);
void SubmitName_MenuProc(struct RectMenu* menu);

// PrixSaveBox (?)

//TakeCupProgress_Activate()
void TakeCupProgress_MenuProc(struct RectMenu* menu);

// RCNT

void Timer_Init();
//Timer_Destroy()
int Timer_GetTime_Total();
int Timer_GetTime_Elapsed(int time, void* param_2);

// Torch

void Torch_Main(void* particleList_heatWarp, struct PushBuffer* pb, struct PrimMem* primMem, char numPlyr, int swapchainIndex);
void Torch_Subset1();
//Torch_Subset2()
//Torch_Subset3()
void Torch_Subset4();
//Torch_Subset5()
//Torch_Subset6()
void Torch_Subset7();
//Torch_Subset8()
//Torch_Subset9()

// UI

void UI_SaveLapTime(int lapID, int time, int driverID);
void UI_ThTick_CountPickup(struct Thread*);
void UI_ThTick_Reward(struct Thread*);
void UI_ThTick_CtrLetters(struct Thread*);
void UI_ThTick_big1(struct Thread*);
int UI_ConvertX_2(int oldPosX,int newPosX);
int UI_ConvertY_2(int oldPosY,int newPosY);
//UI_INSTANCE_BirthWithThread()
void UI_INSTANCE_InitAll();
void UI_Map_DrawMap(struct Icon* mapTop, struct Icon* mapBottom, short posX, short posY, struct PrimMem* primMem, u_long* otMem, u_int colorID);
void UI_Map_GetIconPos(short* ptrMap,int* posX,int* posY);
void UI_Map_DrawAdvPlayer(int ptrMap,int *matrix,int unused1,int unused2,short param_5,short param_6);
void UI_Map_DrawRawIcon(int ptrMap,int *param_2,int iconID,int colorID,int unused,short scale);
void UI_Map_DrawDrivers(int ptrMap,struct Thread* bucket,short *param_3);
void UI_Map_DrawGhosts(int ptrMap,struct Thread* bucket);
void UI_Map_DrawTracking(int ptrMap,struct Thread* bucket);
//void UI_WeaponBG_AnimateShine();
//UI_WeaponBG_DrawShine()
//UI_TrackerBG()
void UI_DrawDriverIcon(struct Icon* icon, short posX, short posY, struct PrimMem* primMem, u_long* ot, char transparency, short scale, u_int color);
void UI_Lerp2D_Angular(short* ptrPos, short drawnPosition, short absolutePosition, short frameCounter);
void UI_Lerp2D_HUD(short* ptrPos, short startX, short startY, short endX, short endY, int curFrame, short endFrame);
void UI_Lerp2D_Linear(short* ptrPos, short startX, short startY, short endX, short endY, int curFrame, short endFrame);
void UI_DrawRaceClock(u_short paramX, u_short paramY, u_int flags, struct Driver* driver);
void UI_DrawLimitClock(short posX, short posY, short fontType);
void UI_BattleDrawHeadArrows(struct Driver*);
void UI_TrackerSelf(struct Driver*);
void UI_DrawPosSuffix(short posX,short posY,struct Driver* d,short flags);
void UI_DrawLapCount(short posX,int posY,int param_3,struct Driver* d);
void UI_DrawBattleScores(int, int, struct Driver*);
void UI_Weapon_DrawSelf(short, short, short, struct Driver*);
void UI_Weapon_DrawBG(short param_1,short param_2,short param_3,struct Driver* d);
void UI_DrawNumWumpa(int param_1,int param_2,struct Driver* d);
void UI_DrawNumTimebox(int posX, int posY, struct Driver* d);
void UI_DrawNumRelic(int posX, int posY);
void UI_DrawNumKey(int posX, int posY);
void UI_DrawNumTrophy(int posX, int posY);
void UI_DrawNumCrystal(int posX, int posY, struct Driver* d);
void UI_DrawSpeedNeedle(short posX, short posY, struct Driver * driver);
void UI_DrawSpeedBG();
void UI_JumpMeter_Update(struct Driver * d);
void UI_JumpMeter_Draw(short posX, short posY, struct Driver* driver);
void UI_DrawSlideMeter(short posX, short posY, struct Driver* driver);
void UI_DrawRankedDrivers();
void UI_RenderFrame_Racing();
void UI_RenderFrame_AdvHub();
void UI_RenderFrame_CrystChall();
void UI_RenderFrame_Wumpa3D_2P3P4P(struct GameTracker* gGT);
//UI_VsQuipReadDriver()
//UI_VsQuipAssign()
//UI_VsQuipAssignAll()
void UI_VsQuipDrawAll();
void UI_VsWaitForPressX();
//UI_RaceEnd_GetDriverClock()
void UI_RaceStart_IntroText1P();
//UI_RaceEnd_MenuProc()
//UI_CupStandings_FinalizeCupRanks()
//UI_CupStandings_UpdateCupRanks()
//UI_CupStandings_InputAndDraw()

// Vector

//Vector_SpecLightSpin2D()
//Vector_SpecLightSpin3D()
//Vector_SpecLightNoSpin3D()
void Vector_BakeMatrixTable();

// from this point onwards it's all vehicle stuff

//VehAfterColl_GetSurface()
//VehAfterColl_GetTerrain()

// VehInit

//VehBirth_TeleportSelf()
void VehBirth_TeleportAll(struct GameTracker* gGT, int flag);
//VehBirth_GetModelByName()
void VehBirth_SetConsts(struct Driver * driver);
//VehBirth_EngineAudio_AllPlayers()
//VehBirth_TireSprites()
//VehBirth_NonGhost()
struct Driver* VehBirth_Player(int index);

// uncategorized

int VehCalc_InterpBySpeed(int currentRot, int rotSpeed, int destinedRot);
int VehCalc_MapToRange(int param_1,int param_2,int param_3,int param_4,int param_5);
int VehCalc_SteerAccel(int param_1, int param_2, int param_3, u_int param_4, u_int param_5, u_int param_6);
//VehCalc_FastSqrt()

// VehParticle

//VehEmitter_Exhaust()
//VehEmitter_Sparks_Ground()
//VehEmitter_Terrain_Ground()
//VehEmitter_Sparks_Wall()
void VehEmitter_DriverMain();

// more uncategorized vehicle stuff

void VehFire_Audio(struct Driver* driver, int speed_cap);
void VehFire_Increment(struct Driver* driver, int reserves, u_int type, int fireLevel);
//VehFrameInst_GetStartFrame()
//VehFrameInst_GetNumAnimFrames()
void VehFrameProc_Driving(struct Thread* t, struct Driver* d);
void VehFrameProc_Spinning();
void VehFrameProc_LastSpin();
//VehGroundShadow_Subset1()
void VehGroundShadow_Main();
//VehGroundSkids_Subset1()
//VehGroundSkids_Subset2()
void VehGroundSkids_Main(struct Thread* thread, struct PushBuffer* pb);
//VehLap_UpdateProgress()
void VehPhysCrash_ConvertVecToSpeed(struct Driver* d, int* v);
//VehPhysCrash_BounceSelf()
//VehPhysCrash_AI()
//VehPhysCrash_Attack()
void VehPhysCrash_AnyTwoCars(struct Thread* thread, u_short* param_2, int* param_3);
//VehPhysForce_ConvertSpeedToVec()
//VehPhysForce_OnGravity()
void VehPhysForce_OnApplyForces(struct Thread* t, struct Driver* d);
void VehPhysForce_CollideDrivers(struct Thread* t, struct Driver* d);
void VehPhysForce_TranslateMatrix();
void VehPhysForce_RotAxisAngle(MATRIX* m, short* normVec, short angle);
void VehPhysForce_AccelTerrainSlope(struct Driver* d);

// "VehPtr"
void Veh_NullThread();
void VehPhysGeneral_PhysAngular(struct Thread* thread, struct Driver* driver);
//VehPhysGeneral_LerpQuarterStrength()
int VehPhysGeneral_LerpToForwards(struct Driver* driver, int param_2, int param_3, int param_4);
//VehPhysGeneral_JumpGetVelY()
void VehPhysGeneral_JumpAndFriction();
void VehPhysGeneral_SetHeldItem(struct Driver* driver);
int VehPhysGeneral_GetBaseSpeed(struct Driver* driver);
int VehPhysJoystick_ReturnToRest(int param_1, u_int param_2, struct RacingWheelData* param_3);
//void VehPhysJoystick_GetStrength()
int VehPhysJoystick_GetStrengthAbsolute(int param_1, u_int param_2, struct RacingWheelData* param_3);
void VehPhysProc_Driving_PhysLinear(struct Thread* t, struct Driver* d);
void VehPhysProc_Driving_Audio(struct Thread* t, struct Driver* d);
void VehPhysProc_Driving_Update(struct Thread* t, struct Driver* d);
void VehPhysProc_Driving_Init(struct Thread* t, struct Driver* d);
void VehPhysProc_FreezeEndEvent_PhysLinear(struct Thread* t, struct Driver* d);
void VehPhysProc_FreezeEndEvent_Init(struct Thread *, struct Driver *);
void VehPhysProc_FreezeVShift_Update(struct Thread* t, struct Driver* d);
void VehPhysProc_FreezeVShift_ReverseOneFrame(struct Thread* t, struct Driver* d);
void VehPhysProc_FreezeVShift_Init(struct Thread* t, struct Driver* d);
void VehPhysProc_PowerSlide_PhysAngular(struct Thread* th, struct Driver* driver);
void VehPhysProc_PowerSlide_Finalize(struct Thread* t, struct Driver* d);
void VehPhysProc_PowerSlide_Update(struct Thread* t, struct Driver* d);
void VehPhysProc_PowerSlide_PhysLinear(struct Thread *thread, struct Driver *driver);
void VehPhysProc_PowerSlide_InitSetUpdate(struct Thread* t, struct Driver* d);
void VehPhysProc_PowerSlide_Init(struct Thread* t, struct Driver* d);
void VehPhysProc_SlamWall_PhysAngular(struct Thread* t, struct Driver* d);
void VehPhysProc_SlamWall_Update(struct Thread* t, struct Driver* d);
void VehPhysProc_SlamWall_PhysLinear(struct Thread* t, struct Driver* d);
void VehPhysProc_SlamWall_Animate(struct Thread* t, struct Driver* d);
void VehPhysProc_SlamWall_Init(struct Thread* t, struct Driver* d);
void VehPhysProc_SpinFirst_Update(struct Thread* t, struct Driver* d);
void VehPhysProc_SpinFirst_PhysLinear(struct Thread* t, struct Driver* d);
void VehPhysProc_SpinFirst_PhysAngular(struct Thread* t, struct Driver* d);
void VehPhysProc_SpinFirst_InitSetUpdate(struct Thread* t, struct Driver* d);
void VehPhysProc_SpinFirst_Init(struct Thread* t, struct Driver* d);
void VehPhysProc_SpinLast_Update(struct Thread* t, struct Driver* d);
void VehPhysProc_SpinLast_PhysLinear(struct Thread* t, struct Driver* d);
void VehPhysProc_SpinLast_PhysAngular(struct Thread* t, struct Driver* d);
void VehPhysProc_SpinLast_Init(struct Thread* t, struct Driver* d);
void VehPhysProc_SpinStop_Update(struct Thread* t, struct Driver* d);
void VehPhysProc_SpinStop_PhysLinear(struct Thread* t, struct Driver* d);
void VehPhysProc_SpinStop_PhysAngular(struct Thread* t, struct Driver* d);
void VehPhysProc_SpinStop_Animate(struct Thread* t, struct Driver* d);
void VehPhysProc_SpinStop_Init(struct Thread* t, struct Driver* d);
//VehPickState_NewState()

// Weapon (?)

//VehPickupItem_MaskBoolGoodGuy()
void * VehPickupItem_MaskUseWeapon(int param_1,int param_2);
//VehPickupItem_MissileGetTargetDriver()
//VehPickupItem_PotionThrow()
//VehPickupItem_ShootNow()
void VehPickupItem_ShootOnCirclePress(struct Driver* driver);

// More VehPtr

void VehStuckProc_MaskGrab_FindDestPos(struct Thread* t, struct Driver* d);
void VehStuckProc_MaskGrab_Particles(struct Thread* t, struct Driver* d);
void VehStuckProc_MaskGrab_Update(struct Thread* t, struct Driver* d);
void VehStuckProc_MaskGrab_PhysLinear(struct Thread* t, struct Driver* d);
void VehStuckProc_MaskGrab_Animate(struct Thread* t, struct Driver* d);
void VehStuckProc_MaskGrab_Init(struct Thread* t, struct Driver* d);
void VehStuckProc_PlantEaten_Update(struct Thread* t, struct Driver* d);
void VehStuckProc_PlantEaten_PhysLinear(struct Thread* t, struct Driver* d);
void VehStuckProc_PlantEaten_Animate(struct Thread* t, struct Driver* d);
void VehStuckProc_PlantEaten_Init(struct Thread* t, struct Driver* d);
void VehStuckProc_RIP_Init(struct Thread* t, struct Driver* d);
void VehStuckProc_RevEngine_Update(struct Thread* t, struct Driver* d);
void VehStuckProc_RevEngine_PhysLinear(struct Thread* t, struct Driver* d);
void VehStuckProc_RevEngine_Animate(struct Thread* t, struct Driver* d);
void VehStuckProc_RevEngine_Init(struct Thread* t, struct Driver* d);
void VehStuckProc_Tumble_Update(struct Thread* t, struct Driver* d);
void VehStuckProc_Tumble_PhysLinear(struct Thread* t, struct Driver* d);
void VehStuckProc_Tumble_PhysAngular(struct Thread* t, struct Driver* d);
void VehStuckProc_Tumble_Animate(struct Thread* t, struct Driver* d);
void VehStuckProc_Tumble_Init(struct Thread* t, struct Driver* d);
void VehStuckProc_Warp_MoveDustPuff(struct Thread* t, struct Driver* d);
void VehStuckProc_Warp_AddDustPuff1(struct ScratchpadStruct *sps);
void VehStuckProc_Warp_AddDustPuff2(struct Thread* t, struct Driver* d);
void VehStuckProc_Warp_PhysAngular(struct Thread* t, struct Driver* d);
void VehStuckProc_Warp_Init(struct Thread* t, struct Driver* d);

// TalkingMask (?)

//VehTalkMask_ThTick()
//VehTalkMask_Init()
//VehTalkMask_PlayXA()
//VehTalkMask_boolNoXA()
//VehTalkMask_End()

// More Turbo...

void VehTurbo_ProcessBucket(struct Thread* turboThread);
void VehTurbo_ThDestroy();
void VehTurbo_ThTick(int param_1);

// DrawSky (?)

void DrawSky_Full(void* skybox, struct PushBuffer* pb, struct PrimMem* primMem);
//DrawSky_Piece()

// uncategorized

void AnimateQuad(int timer, int numSCVert, void* ptrSCVert, int* visSCVertList);
//AnimateQuadVertex()
//TRIG_AngleSinCos_r19r17r18()
void DrawConfetti(struct PushBuffer* pb, struct PrimMem* primMem, void* confetti, int frameTimer, int gameMode1);
//TRIG_AngleSinCos_r15r16r17()

// RenderBucket (?)

//RenderBucket_DrawFunc_Normal()
//RenderBucket_UncompressAnimationFrame()
void RenderBucket_Execute(void* param_1, struct PrimMem* param_2);
//RenderBucket_DrawInstPrim_Normal()
//RenderBucket_InitDepthGTE()
//RenderBucket_DrawInstPrim_KeyRelicToken()
//RenderBucket_DrawFunc_Split()

// more uncategorized stuff

//Draw_Uncompress2()
//Draw_KartFlames()
//Draw_KartInWaterMud()
//ConvertRotToMatrix_InverseTranspose_NoRotY()
//ConvertRotToMatrix_InverseTranspose()
void ConvertRotToMatrix(MATRIX* m, short* rot);
//ConvertRotToMatrix_Transpose()
//MatrixRotate()
//TRIG_AngleSinCos_r16r17r18_duplicate()
int SquareRoot0_stub (int param_1);
//RngDeadCoed()
//ApplyMatrixLV_stub()
//Draw_KartGhost()
//Draw_KartBodyReflection()
//RenderBucket_DrawInstPrim_Ghost()
void AnimateWater1P(int timer, int numWaterVertices, struct WaterVert* waterVert, void* waterEnvMap, int* param_5);
void AnimateWater2P(int timer, int numWaterVertices, struct WaterVert* waterVert, void* waterEnvMap, int* param_5, int* param_6);
void AnimateWater3P(int timer, int numWaterVertices, struct WaterVert* waterVert, void* waterEnvMap, int* param_5, int* param_6, int* param_7);
void AnimateWater4P(int timer, int numWaterVertices, struct WaterVert* waterVert, void* waterEnvMap, int* param_5, int* param_6, int* param_7, int* param_8);
//AnimateWaterVertex()
void RedBeaker_RenderRain(struct PushBuffer* pb, struct PrimMem* primMem, struct JitPool* rain, char numPlyr, int gameMode1);
void RenderStars(struct PushBuffer* pb, struct PrimMem* primMem, void* stars, char numPlyr);
void DrawTires_Solid(struct Thread* thread, struct PrimMem* primMem, char numPlyr);
//TRIG_AngleSinCos_r9r8r10()
void DrawTires_Reflection(struct Thread* thread, struct PrimMem* primMem, char numPlyr);
void RenderWeather(struct PushBuffer* pb, struct PrimMem* primMem, struct RainBuffer* rainBuffer, char numPlyr, int gameMode1);
//TRIG_AngleSinCos_r16r17r18()
int RenderLists_Init1P2P(struct BSP* bspRoot, int* visLeafList, struct PushBuffer* pb, u_int LevRenderList, void* bspList, char numPlyr);
void RenderLists_PreInit();
int RenderLists_Init3P4P(struct BSP* bspRoot, int* visLeafList, struct PushBuffer* pb, u_int LevRenderList, void* bspList);
void* RenderBucket_QueueLevInstances(struct CameraDC* cDC, u_long* otMem, void* rbi, char* lod, char numPlyr, int gameMode1);
void* RenderBucket_QueueNonLevInstances(struct Item* item, u_long* otMem, void* rbi, char* lod, char numPlyr, int gameMode1);
//RenderBucket_QueueDraw()
void ThTick_RunBucket(struct Thread* thread);
//ThTick_FastRET()
//ThTick_SetAndExec()
//ThTick_Set()

// PSY-Q

void* BreakDraw();

// ALL EXE FUNCTIONS ARE DECLARED ABOVE
// OVERLAY FUNCTIONS ARE BELOW
// (currently unorganized)

void RB_Bubbles_RoosTubes();
void RB_Burst_DrawAll(int param_1);
void UI_CupStandings_InputAndDraw();
void VB_EndEvent_DrawMenu();
void RR_EndEvent_DrawMenu();
void AA_EndEvent_DrawMenu();
void TT_EndEvent_DrawMenu();
void CC_EndEvent_DrawMenu();
void AH_Map_Main();
void AH_MaskHint_Start(short requestedHint, short bool_interruptWarppad);
void CS_BoxScene_InstanceSplitLines();

void RB_Player_ToggleInvisible();
void RB_Player_ToggleFlicker();

void RB_RainCloud_FadeAway(struct Thread *t);
void RB_RainCloud_ThTick(struct Thread* t);

void RB_Burst_ProcessBucket(struct Thread* thread);
void RB_Blowup_ProcessBucket(struct Thread* thread);
void RB_Spider_DrawWebs(struct Thread* thread, struct PushBuffer* pb);
void RB_Follower_ProcessBucket(struct Thread* thread);
void RB_StartText_ProcessBucket(struct Thread* thread);
void AH_WarpPad_AllWarppadNum();
void MM_Title_SetTrophyDPP();

void DrawLevelOvr1P(void* LevRenderList, struct PushBuffer* pb, struct BSP* bspList, struct PrimMem* primMem, void* VisMem10, void* waterEnvMap);
void DrawLevelOvr2P(void* LevRenderList, struct PushBuffer* pb, struct BSP* bspList, struct PrimMem* primMem, void* VisMem10, void* VisMem14, void* waterEnvMap);
void DrawLevelOvr3P(void* LevRenderList, struct PushBuffer* pb, struct BSP* bspList, struct PrimMem* primMem, void* VisMem10, void* VisMem14, void* VisMem18, void* waterEnvMap);
void DrawLevelOvr4P(void* LevRenderList, struct PushBuffer* pb, struct BSP* bspList, struct PrimMem* primMem, void* VisMem10, void* VisMem14, void* VisMem18, void* VisMem1C, void* waterEnvMap);

u_int MM_Video_CheckIfFinished(int param_1);
void AH_Pause_Update();
