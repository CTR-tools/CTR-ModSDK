
void DECOMP_CAM_ClearScreen(struct GameTracker* gGT);
void DECOMP_CAM_Init(struct CameraDC* cDC, int cameraID, struct Driver* d, struct PushBuffer* pb);
int DECOMP_CAM_Path_GetNumPoints(void);
u_char DECOMP_CAM_Path_Move(int frameIndex, short *position, short *rotation, short *getPath);
void DECOMP_CAM_SetDesiredPosRot(struct CameraDC* cDC, short* pos, short* rot);

void DECOMP_CDSYS_Init(int boolUseDisc);
u_int DECOMP_CDSYS_GetFilePosInt(char* fileString, int* filePos);
void DECOMP_CDSYS_SetMode_StreamData();
void DECOMP_CDSYS_SetMode_StreamAudio();
void DECOMP_CDSYS_SetXAToLang(int lang);
void DECOMP_CDSYS_XaCallbackCdSync(char result);
void DECOMP_CDSYS_XaCallbackCdReady(char result);
void DECOMP_CDSYS_SpuCallbackIRQ();
void DECOMP_CDSYS_SpuCallbackTransfer();
void DECOMP_CDSYS_SpuEnableIRQ();
void DECOMP_CDSYS_SpuDisableIRQ();
void DECOMP_CDSYS_SpuGetMaxSample(void);
u_int DECOMP_CDSYS_XAGetNumTracks(int categoryID);

void DECOMP_CDSYS_XAPlay(int categoryID, int xaID);
void DECOMP_CDSYS_XAPauseRequest();
void DECOMP_CDSYS_XAPauseForce();
void DECOMP_CDSYS_XAPauseAtEnd();

void* DECOMP_COLL_LevModelMeta(unsigned int id);

void DECOMP_CTR_CycleTex_AllModels(unsigned int numModels, struct Model** pModelArray, int timer);
void DECOMP_CTR_CycleTex_LEV(struct AnimTex* animtex, int timer);
void DECOMP_CTR_ErrorScreen(char r, char g, char b);
void DECOMP_CTR_CycleTex_Model(struct AnimTex* animtex, int timer);

void DECOMP_CTR_Box_DrawWireBox(RECT * r, Color color, void * ot);
void DECOMP_CTR_Box_DrawClearBox(RECT * r, Color color, int transparency, u_long * ot);
void DECOMP_CTR_Box_DrawSolidBox(RECT * r, Color color, u_long * ot);

// decal
void DECOMP_DecalFont_DrawLine(char* str, int posX, int posY, short fontType, int flags);
void DECOMP_DecalFont_DrawLineStrlen(u_char* str, short len, int posX, short posY, short fontType, int flags);
int DECOMP_DecalFont_DrawMultiLine(char* str, int posX, int posY, int maxPixLen, short fontType, int flags);
void DECOMP_DecalGlobal_Clear(struct GameTracker* gGT);
void DECOMP_DecalHUD_DrawPolyFT4(struct Icon* icon, short posX, short posY, struct PrimMem* primMem, u_long* ot, char transparency, short scale);
void DECOMP_DecalHUD_DrawPolyGT4(struct Icon* icon, short posX, short posY, struct PrimMem* primMem, u_long* ot, u_int color0, u_int color1, u_int color2, u_int color3, char transparency, short scale);

void DECOMP_DISPLAY_Swap(void);

void DECOMP_DotLights(struct GameTracker* gGT);

void DECOMP_DropRain_MakeSound(struct GameTracker *gGT);
void DECOMP_DropRain_Reset(struct GameTracker *gGT);

// ElimBG
void DECOMP_ElimBG_Activate(struct GameTracker* gGT);
void DECOMP_ElimBG_Deactivate(struct GameTracker *gGT);
void DECOMP_ElimBG_HandleState(struct GameTracker *gGT);
void DECOMP_ElimBG_SaveScreenshot_Full(struct GameTracker* gGT);

// gamepad
void DECOMP_GAMEPAD_Init(struct GamepadSystem* gGamepads);
void DECOMP_GAMEPAD_PollVsync(struct GamepadSystem* gGamepads);
int DECOMP_GAMEPAD_GetNumConnected(struct GamepadSystem* gGamepads);
void DECOMP_GAMEPAD_ProcessHold(struct GamepadSystem* gGamepads);
void DECOMP_GAMEPAD_ProcessSticks(struct GamepadSystem* gGamepads);
void DECOMP_GAMEPAD_ProcessTapRelease(struct GamepadSystem* gGamepads);
void DECOMP_GAMEPAD_ProcessMotors(struct GamepadSystem* gGamepads);
void DECOMP_GAMEPAD_ProcessAnyoneVars(struct GamepadSystem* gGamepads);
void DECOMP_GAMEPAD_ProcessState(struct GamepadBuffer* pad, int padState, short id);

int DECOMP_GAMEPROG_CheckGhostsBeaten(int ghostID);
void DECOMP_GAMEPROG_NewGame_OnBoot();
void DECOMP_GAMEPROG_GetPtrHighScoreTrack();

// ghost
void DECOMP_GhostReplay_Init1(void);
void DECOMP_GhostReplay_Init2();
void DECOMP_GhostReplay_ThTick(struct Thread *t);
void DECOMP_GhostTape_Destroy();
void DECOMP_GhostTape_End(void);
void DECOMP_GhostTape_Start(void);
void DECOMP_GhostTape_WriteBoosts(int addReserve,u_char type,int speedCap);
void DECOMP_GhostTape_WriteMoves(short raceFinished);

// howl
int DECOMP_CountSounds();
int DECOMP_OtherFX_Play(unsigned int soundID, int flags);
void DECOMP_OtherFX_Play_Echo(unsigned int soundID, int flags, int echoFlag);
int DECOMP_OtherFX_Play_LowLevel(u_int soundID, char boolAntiSpam, u_int flags);
u_int DECOMP_OtherFX_Modify(u_int soundId, u_int flags);
void DECOMP_OtherFX_Stop1(int soundID_count);
void DECOMP_OtherFX_Stop2(int soundID_count);
char DECOMP_EngineAudio_InitOnce(u_int soundID,u_int flags);
short DECOMP_EngineAudio_Recalculate(u_int soundID,u_int sfx);
void DECOMP_EngineAudio_Stop(u_int soundID);
void DECOMP_SetReverbMode(u_short newReverbMode);
int DECOMP_CseqMusic_Start(int songID, int p2, int p3, int p4, int p5);
void DECOMP_CseqMusic_Pause();
void DECOMP_CseqMusic_Resume();
void DECOMP_CseqMusic_ChangeVolume(int songID, int p2, int p3);
void DECOMP_CseqMusic_Restart(int songID, int p2);
void DECOMP_CseqMusic_ChangeTempo(int songID, int p2);
void DECOMP_CseqMusic_AdvHubSwap(
	u_short songId, struct SongSet* songSet, int songSetActiveBits);
void DECOMP_CseqMusic_Stop(int songID);
void DECOMP_CseqMusic_StopAll();
void DECOMP_Bank_ResetAllocator();
int DECOMP_Bank_Alloc(int bankID, struct Bank* ptrBank);
int DECOMP_Bank_AssignSpuAddrs();
void DECOMP_Bank_Destroy(struct Bank* ptrLastBank);
void DECOMP_Bank_ClearInRange(unsigned short min, unsigned short max);
int DECOMP_Bank_Load(int bankID, struct Bank* ptrBank);
int DECOMP_Bank_DestroyLast();
void DECOMP_Bank_DestroyUntilIndex(int index);
void DECOMP_Bank_DestroyAll();
unsigned int DECOMP_howl_InstrumentPitch(
	int basePitch, int pitchIndex, unsigned int distort);
void DECOMP_howl_InitGlobals(char* filename);
void DECOMP_howl_ParseHeader(struct HowlHeader* hh);
void DECOMP_howl_ParseCseqHeader(struct CseqHeader* ch);
void DECOMP_howl_LoadHeader(char* filename);
void DECOMP_howl_SetSong(int songID);
int DECOMP_howl_LoadSong();
void DECOMP_howl_ErasePtrCseqHeader();
char* DECOMP_howl_GetNextNote(char* currNote, int* noteLen);
void DECOMP_cseq_opcode00_empty();
void DECOMP_cseq_opcode01_noteoff(struct SongSeq* seq);
void DECOMP_cseq_opcode02_empty();
void DECOMP_cseq_opcode03(struct SongSeq* seq);
void DECOMP_cseq_opcode04_empty();
void DECOMP_howl_InitChannelAttr_Music(
	struct SongSeq* seq, struct ChannelAttr* attr, int index, int channelVol);
void DECOMP_cseq_opcode_from06and07(struct SongSeq* seq);
void DECOMP_cseq_opcode05_noteon(struct SongSeq* seq);
void DECOMP_cseq_opcode06(struct SongSeq* seq);
void DECOMP_cseq_opcode07(struct SongSeq* seq);
void DECOMP_cseq_opcode08(struct SongSeq* seq);
void DECOMP_cseq_opcode09(struct SongSeq* seq);
void DECOMP_cseq_opcode0a(struct SongSeq* seq);
struct SongSeq* DECOMP_SongPool_FindFreeChannel();
int DECOMP_SongPool_CalculateTempo(int const60, int tpqn, int bpm);
void DECOMP_SongPool_ChangeTempo(struct Song* song, short deltaBPM);
void DECOMP_SongPool_Start(
	struct Song* song, int songID, int deltaBPM,
	int boolLoopAtEnd, struct SongSet* songSet, int songSetActiveBits);
void DECOMP_SongPool_Volume(struct Song* song, int newVol, int newStep, int boolImm);
void DECOMP_SongPool_AdvHub1(struct Song* song, int seqID, int vol, int boolImm);
void DECOMP_SongPool_AdvHub2(struct Song* song, struct SongSet* songSet, int songSetActiveBits);
void DECOMP_SongPool_StopCseq(struct SongSeq* seq);
void DECOMP_SongPool_StopAllCseq(struct Song* song);
void DECOMP_howl_Disable();
void DECOMP_UpdateChannelVol_EngineFX(
	struct EngineFX* engineFX, struct ChannelAttr* attr, int vol, int LR);
void DECOMP_UpdateChannelVol_OtherFX(
	struct OtherFX* otherFX, struct ChannelAttr* attr, int vol, int LR);
void DECOMP_UpdateChannelVol_Music(
	struct SongSeq* songSeq, struct ChannelAttr* attr, int index, int vol);
void DECOMP_UpdateChannelVol_EngineFX_All();
void DECOMP_UpdateChannelVol_Music_All();
void DECOMP_UpdateChannelVol_OtherFX_All();
int DECOMP_howl_VolumeGet(int type);
void DECOMP_howl_VolumeSet(int type, unsigned char vol);
int DECOMP_howl_ModeGet();
void DECOMP_howl_ModeSet(int newMode);
void DECOMP_OptionsMenu_TestSound(int newRow, int newBoolPlay);
void DECOMP_Smart_EnterCriticalSection(void);
void DECOMP_Smart_ExitCriticalSection(void);
void DECOMP_Channel_SetVolume(
	struct ChannelAttr* attr,
	int volume, int LR);
struct ChannelStats* DECOMP_Channel_FindSound(int soundID);
struct ChannelStats* DECOMP_Channel_AllocSlot_AntiSpam(
	short soundID,
	char boolUseAntiSpam,
	int flags,
	struct ChannelAttr* attr);
struct ChannelStats* DECOMP_Channel_AllocSlot(
	int flags,
	struct ChannelAttr* attr);
struct ChannelStats* DECOMP_Channel_SearchFX_EditAttr(
	int type, int soundID, int updateFlags,
	struct ChannelAttr* attr);
void DECOMP_Channel_SearchFX_Destroy(
	int type, int soundID, int flags);
void DECOMP_Channel_DestroyAll_LowLevel(int opt1, int boolKeepMusic, char type);
void DECOMP_Channel_ParseSongToChannels();
void DECOMP_Channel_UpdateChannels();
void DECOMP_Cutscene_VolumeBackup(void);
void DECOMP_Cutscene_VolumeRestore(void);
void DECOMP_howl_PlayAudio_Update();
void DECOMP_howl_InitChannelAttr_EngineFX(
		struct EngineFX* engineFX, struct ChannelAttr* attr,
		int vol, int LR, int distort);
void DECOMP_howl_InitChannelAttr_OtherFX(
		struct OtherFX* otherFX, struct ChannelAttr* attr,
		int vol, int LR, int distort);
void DECOMP_howl_PauseAudio();
void DECOMP_howl_UnPauseChannel(struct ChannelStats* stats);
void DECOMP_howl_UnPauseAudio();
void DECOMP_howl_StopAudio(int boolErasePauseBackup, int boolEraseMusic, int boolDestroyAllFX);
void DECOMP_Voiceline_PoolInit(void);
void DECOMP_Voiceline_ClearTimeStamp(void);
void DECOMP_Voiceline_PoolClear(void);
void DECOMP_Voiceline_StopAll(void);
void DECOMP_Voiceline_ToggleEnable(int toggle);
// skip 95, 96, 97, 98
void DECOMP_Voiceline_SetDefaults(void);
void DECOMP_Audio_SetState(u_int state);
void DECOMP_Audio_SetState_Safe(int state);
void DECOMP_Audio_AdvHub_SwapSong(int levelID);
void DECOMP_Audio_SetMaskSong(u_int tempo);
void DECOMP_Audio_Update1(void);
void DECOMP_Audio_SetDefaults(void);
void DECOMP_Audio_SetReverbMode(int levelID, u_int isBossRace, int bossID);
void DECOMP_Music_SetIntro(void);
void DECOMP_Music_LoadBanks(void);
u_int DECOMP_Music_AsyncParseBanks(void);
void DECOMP_Music_SetDefaults(void);
void DECOMP_Music_Adjust(u_int songID, int newTempo, struct SongSet *set, u_int songSetActiveBits);
void DECOMP_Music_LowerVolume(void);
void DECOMP_Music_RaiseVolume(void);
void DECOMP_Music_Restart(void);
void DECOMP_Music_Stop(void);
void DECOMP_Music_Start(u_int songID);
void DECOMP_Music_End(void);
u_int DECOMP_Music_GetHighestSongPlayIndex(void);

// INSTANCE
void DECOMP_INSTANCE_Birth(
	struct Instance* inst, struct Model* model, char* name,
	struct Thread* th, int flags);
struct Instance* DECOMP_INSTANCE_Birth2D(
	struct Model* model, char* name, struct Thread* th);
struct Instance* DECOMP_INSTANCE_Birth3D(
	struct Model* model, char* name, struct Thread* th);
struct Instance* DECOMP_INSTANCE_BirthWithThread(
	int modelID, char* name, int poolType, int bucket,
	void* funcThTick, int objSize, struct Thread* parent);
struct Instance* DECOMP_INSTANCE_BirthWithThread_Stack(int* spArr);
void DECOMP_INSTANCE_Death(struct Instance* inst);
u_short DECOMP_INSTANCE_GetNumAnimFrames(struct Instance* pInstance, int animIndex);
void DECOMP_INSTANCE_LevInitAll(struct InstDef *levInstDef, int numInst);

// JitPool
int DECOMP_JitPool_Add(struct JitPool* AP);
void DECOMP_JitPool_Clear(struct JitPool* AP);
void DECOMP_JitPool_Init(struct JitPool* AP,
	int maxItems, int itemSize, char* name);
void DECOMP_JitPool_Remove(struct JitPool* AP, struct Item* item);

// LevInstDef
void DECOMP_LevInstDef_UnPack(struct mesh_info* ptr_mesh_info);
void DECOMP_LevInstDef_RePack(struct mesh_info* ptr_mesh_info, int boolAdvHub);

struct Instance* DECOMP_LinkedCollide_Hitbox_Desc(struct HitboxDesc* objBoxDesc);

// LIST
void DECOMP_LIST_AddBack(struct LinkedList* L, struct Item* I);
void DECOMP_LIST_AddFront(struct LinkedList* L, struct Item* I);
void DECOMP_LIST_Clear(struct LinkedList* L);
void* DECOMP_LIST_GetFirstItem(struct LinkedList* L);
void* DECOMP_LIST_GetNextItem(struct Item* I);
void DECOMP_LIST_Init(struct LinkedList* L, struct Item* item, int itemSize, int numItems);
struct Item* DECOMP_LIST_RemoveBack(struct LinkedList* L);
struct Item* DECOMP_LIST_RemoveFront(struct LinkedList* L);
struct Item* DECOMP_LIST_RemoveMember(struct LinkedList* L, struct Item* I);

void DECOMP_LOAD_Callback_Overlay_Generic();
void DECOMP_LOAD_Callback_Overlay_230();
void DECOMP_LOAD_Callback_Overlay_231();
void DECOMP_LOAD_Callback_Overlay_232();
void DECOMP_LOAD_Callback_Overlay_233();
void DECOMP_LOAD_Callback_DriverModels();
void DECOMP_LOAD_Callback_Podiums();
void DECOMP_LOAD_Callback_LEV();
void DECOMP_LOAD_Callback_LEV_Adv();
void DECOMP_LOAD_VramFileCallback();
void DECOMP_LOAD_ReadFileASyncCallback(char result);
void* DECOMP_LOAD_ReadFile(struct BigHeader* bigfile, u_int loadType, int subfileIndex, void* destination, int *size, void * callback);
void* DECOMP_LOAD_VramFile(void* bigfilePtr, int subfileIndex, int* ptrDestination, int* size, int callbackOrFlags);
void* DECOMP_LOAD_ReadDirectory(char* filename);
void* DECOMP_LOAD_ReadFile_NoCallback(char* filename, void* ptrDestination, int* size);
int DECOMP_LOAD_TenStages(struct GameTracker* gGT, int loadingStage, struct BigHeader* bigfile);
void DECOMP_LOAD_LevelFile(int levelID);

void DECOMP_LOAD_HowlCallback(char result);
int DECOMP_LOAD_HowlSectorChainStart(CdlFILE* cdlFileHWL, void* ptrDestination, int firstSector, int numSector);
int DECOMP_LOAD_HowlSectorChainEnd();

void DECOMP_LOAD_InitCD();
void DECOMP_LOAD_RunPtrMap(int origin, int* patchArr, int numPtrs);
void DECOMP_LOAD_LangFile(int bigfilePtr, int lang);
void DECOMP_LOAD_AppendQueue(int bigfile, int type, int fileIndex, void* destinationPtr, void* callback);
void DECOMP_LOAD_NextQueuedFile();

void DECOMP_MainDB_OTMem(struct OTMem* otMem, u_int size);
void DECOMP_MainDB_PrimMem(struct PrimMem* primMem, u_int size);

void DECOMP_MainDrawCb_Vsync();
void DECOMP_MainDrawCb_DrawSync();

void DECOMP_MainFrame_GameLogic(struct GameTracker* gGT, struct GamepadSystem* gGamepads);
void DECOMP_MainFrame_RenderFrame(struct GameTracker* gGT, struct GamepadSystem* gGamepads);
void DECOMP_MainFrame_ResetDB(struct GameTracker* gGT);
void DECOMP_MainFrame_RequestMaskHint(short hintId, char interruptWarpPad);
void DECOMP_MainFrame_TogglePauseAudio(int bool_pause);

void DECOMP_MainFreeze_SafeAdvDestroy();
void DECOMP_MainFreeze_MenuPtrQuit(struct RectMenu* menu);
void DECOMP_MainFreeze_MenuPtrDefault(struct RectMenu* menu);
void DECOMP_MainFreeze_IfPressStart(void);

void DECOMP_MainGameStart_Initialize(struct GameTracker* gGT, char boolStopAudio);

void DECOMP_MainInit_Drivers(struct GameTracker *gGT);
void DECOMP_MainInit_JitPoolsNew(struct GameTracker *gGT);
void DECOMP_MainInit_JitPoolsReset(struct GameTracker* gGT);
void DECOMP_MainInit_PrimMem(struct GameTracker* gGT, int force);
void DECOMP_MainInit_OTMem(struct GameTracker* gGT);
void DECOMP_MainInit_FinalizeInit(struct GameTracker* gGT);
void DECOMP_MainInit_VRAMClear();
void DECOMP_MainInit_VRAMDisplay();

void DECOMP_MainRaceTrack_StartLoad(short levelID);
void DECOMP_MainRaceTrack_RequestLoad(short levelID);

int DECOMP_MATH_Sin(u_int angle);
int DECOMP_MATH_Cos(u_int angle);

void DECOMP_MEMCARD_InitCard(void);

void DECOMP_MEMPACK_Init(int ramSize);
void DECOMP_MEMPACK_SwapPacks(int index);
void DECOMP_MEMPACK_NewPack_StartEnd(void* start,int size);
int DECOMP_MEMPACK_GetFreeBytes();
void* DECOMP_MEMPACK_AllocMem(int size);
void* DECOMP_MEMPACK_AllocHighMem(int allocSize);
void DECOMP_MEMPACK_ClearHighMem();
void* DECOMP_MEMPACK_ReallocMem(int size);
int DECOMP_MEMPACK_PushState();
void DECOMP_MEMPACK_ClearLowMem();
void DECOMP_MEMPACK_PopState();
void DECOMP_MEMPACK_PopToState(int id);

void DECOMP_RECTMENU_DrawQuip(char *comment, short startX, int startY, u_int sizeX, short fontType,
                             int textFlag, short boxFlag);
void DECOMP_RECTMENU_DrawInnerRect(RECT* r, int x, void* ot);
void DECOMP_RECTMENU_DrawSelf(struct RectMenu* menu, int param_2, short param_3, short width);
void DECOMP_RECTMENU_DrawPolyGT4(struct Icon* icon, short posX, short posY, struct PrimMem* primMem, u_long* ot, u_int color0, u_int color1, u_int color2, u_int color3, char transparency, short scale);
int DECOMP_RECTMENU_BoolHidden(struct RectMenu* m);
void DECOMP_RECTMENU_ClearInput();
void DECOMP_RECTMENU_CollectInput();
void DECOMP_RECTMENU_ProcessState();
int DECOMP_RECTMENU_ProcessInput(struct RectMenu *m);
void DECOMP_RECTMENU_DrawOuterRect_Edge(RECT * r, Color color, u_int param_3, u_long * otMem);
void DECOMP_RECTMENU_DrawOuterRect_HighLevel(RECT* r, Color color, short param_3, u_long* otMem);
void DECOMP_RECTMENU_DrawOuterRect_LowLevel(RECT* p, short xOffset, u_short yOffset, Color color, short param_5, u_long* otMem);
u_char* DECOMP_RECTMENU_DrawTime(int milliseconds);
void DECOMP_RECTMENU_DrawRwdBlueRect_Subset(short *pos, int *color, u_long *ot, struct PrimMem *primMem);
void DECOMP_RECTMENU_DrawRwdBlueRect(RECT *rect, char *metas, u_long *ot, struct PrimMem *primMem);
void DECOMP_RECTMENU_DrawRwdTriangle(short* position,char* color,u_long* otMem,struct PrimMem* primMem);
void DECOMP_RECTMENU_GetHeight(struct RectMenu* m, short* height, int boolCheckSubmenu);
void DECOMP_RECTMENU_GetWidth(struct RectMenu* m, short* width, int boolCheckSubmenu);
void DECOMP_RECTMENU_Hide(struct RectMenu* m);
void DECOMP_RECTMENU_Show(struct RectMenu* m);

int DECOMP_MixRNG_Scramble();

struct Thread* DECOMP_PROC_BirthWithObject(
	int flags, void* funcThTick,
	char* name, struct Thread* relativeTh);
void DECOMP_PROC_CheckAllForDead();
void DECOMP_PROC_CheckBloodlineForDead(struct Thread** replaceSelf, struct Thread* th);
void DECOMP_PROC_CollidePointWithBucket(struct Thread* th, short* vec3_pos);
void DECOMP_PROC_CollidePointWithSelf(struct Thread* th, struct Need_New_Name* buf);
void DECOMP_PROC_DestroyInstance(struct Thread* t);
void DECOMP_PROC_DestroyObject(void* object, int threadFlags);
void DECOMP_PROC_DestroySelf(struct Thread* t);
void DECOMP_PROC_DestroyTracker(struct Thread* t);
struct Thread* DECOMP_PROC_SearchForModel(struct Thread* th, int modelID);

void DECOMP_PushBuffer_Init(struct PushBuffer* pb, int id, int total);
void DECOMP_PushBuffer_SetPsyqGeom(struct PushBuffer* pb);
void DECOMP_PushBuffer_SetMatrixVP(struct PushBuffer* pb);

void DECOMP_PushBuffer_SetDrawEnv_Normal(
		void* ot, struct PushBuffer* pb, struct DB* backBuffer,
		DRAWENV* copyDrawEnvNULL, int isbg);

void DECOMP_PushBuffer_FadeOneWindow(struct PushBuffer* pb);
void DECOMP_PushBuffer_FadeAllWindows();

void DECOMP_QueueLoadTrack_MenuProc(struct RectMenu* menu);
struct RectMenu* DECOMP_QueueLoadTrack_GetMenuPtr();

void DECOMP_RaceFlag_SetCanDraw(short param_1);
void DECOMP_RaceFlag_BeginTransition(int direction);
void DECOMP_RaceFlag_SetFullyOnScreen();
void DECOMP_RaceFlag_SetFullyOffScreen();
void DECOMP_RaceFlag_ResetTextAnim();
void DECOMP_RaceFlag_DrawSelf();

short DECOMP_SubmitName_DrawMenu(u_short string);
void DECOMP_SubmitName_MenuProc(struct RectMenu* menu);
void DECOMP_SubmitName_RestoreName(short param_1);

void DECOMP_Timer_Init();
void DECOMP_Timer_Destroy();

// UI
void DECOMP_UI_ThTick_CountPickup(struct Thread * bucket);
void DECOMP_UI_ThTick_Reward(struct Thread * bucket);
void DECOMP_UI_ThTick_CtrLetters(struct Thread * bucket);
void DECOMP_UI_ThTick_big1(struct Thread * bucket);

int DECOMP_UI_ConvertX_2(int oldPosX,int newPosX);
int DECOMP_UI_ConvertY_2(int oldPosY,int newPosY);

void DECOMP_UI_INSTANCE_InitAll(void);
int DECOMP_UI_INSTANCE_BirthWithThread(int param_1,int param_2,int param_3,int param_4,int param_5,int param_6);

void DECOMP_UI_DrawBattleScores(int posX, int posY, struct Driver * d);
void DECOMP_UI_Weapon_DrawSelf(short posX,short posY,short scale,struct Driver* d);
void DECOMP_UI_Weapon_DrawBG(short param_1,short param_2,short param_3,struct Driver* d);
void DECOMP_UI_DrawNumWumpa(short param_1, short param_2, struct Driver* d);
void DECOMP_UI_DrawNumKey(short posX, short posY);
void DECOMP_UI_DrawNumRelic(short posX, short posY);
void DECOMP_UI_DrawNumTrophy(short posX, short posY);
void DECOMP_UI_DrawNumCrystal(short posX, short posY, struct Driver* d);
void DECOMP_UI_DrawNumTimebox(short posX, short posY, struct Driver* d);
void DECOMP_UI_DrawSpeedBG(void);
void DECOMP_UI_DrawSpeedNeedle(short posX, short posY, struct Driver * driver);
void DECOMP_UI_JumpMeter_Draw(short posX, short posY, struct Driver* driver);
void DECOMP_UI_JumpMeter_Update(struct Driver * d);
void DECOMP_UI_DrawSlideMeter(short posX, short posY, struct Driver* driver);
void DECOMP_UI_DrawRankedDrivers(void);
void DECOMP_UI_DrawDriverIcon(struct Icon* icon, Point point, u_long* ot, unsigned transparency, int scale, Color color);
void DECOMP_UI_RenderFrame_AdvHub(void);
void DECOMP_UI_RenderFrame_Racing();

void DECOMP_UI_SaveLapTime(int numLaps, int lapTime, short driverID);

void DECOMP_UI_Map_GetIconPos(short* m,int* posX,int* posY);
void DECOMP_UI_Map_DrawMap(struct Icon* mapTop, struct Icon* mapBottom, short posX, short posY, struct PrimMem* primMem, u_long* otMem, u_int colorID);

void DECOMP_UI_Lerp2D_Linear(short* ptrPos, short startX, short startY, short endX, short endY, int curFrame, short endFrame);

void DECOMP_UI_RaceEnd_MenuProc(struct RectMenu*);

// VEH
void DECOMP_VehBirth_TeleportSelf(struct Driver *d, u_char spawnFlag, int spawnPosY);
void DECOMP_VehBirth_TeleportAll(struct GameTracker *gGT, u_int spawnFlags);
void DECOMP_VehBirth_SetConsts(struct Driver* driver);
void DECOMP_VehBirth_EngineAudio_AllPlayers(void);
void DECOMP_VehBirth_TireSprites(struct Thread *t);
void DECOMP_VehBirth_NonGhost(struct Thread* t, int index);
struct Driver* DECOMP_VehBirth_Player(int index);

void DECOMP_VehPhysGeneral_PhysAngular(struct Thread *t, struct Driver *d);

void DECOMP_VehPhysProc_Driving_PhysLinear(struct Thread *t, struct Driver *d);
void DECOMP_VehPhysProc_Driving_Audio(struct Thread *t, struct Driver *d);
void DECOMP_VehPhysProc_Driving_Update(struct Thread *t, struct Driver *d);
void DECOMP_VehPhysProc_Driving_Init(struct Thread *t, struct Driver *d);

void DECOMP_VehPhysProc_FreezeEndEvent_PhysLinear(struct Thread *t, struct Driver *d);
void DECOMP_VehPhysProc_FreezeEndEvent_Init(struct Thread *t, struct Driver *d);

void DECOMP_VehPhysProc_FreezeVShift_Update(struct Thread *t, struct Driver *d);
void DECOMP_VehPhysProc_FreezeVShift_ReverseOneFrame(struct Thread *t, struct Driver *d);
void DECOMP_VehPhysProc_FreezeVShift_Init(struct Thread *t, struct Driver *d);

void DECOMP_VehPhysProc_PowerSlide_PhysAngular(struct Thread *t, struct Driver *d);
void DECOMP_VehPhysProc_PowerSlide_Finalize(struct Thread *t, struct Driver *d);
void DECOMP_VehPhysProc_PowerSlide_Update(struct Thread *t, struct Driver *d);
void DECOMP_VehPhysProc_PowerSlide_PhysLinear(struct Thread *t, struct Driver *d);
void DECOMP_VehPhysProc_PowerSlide_InitSetUpdate(struct Thread *t, struct Driver *d);
void DECOMP_VehPhysProc_PowerSlide_Init(struct Thread *t, struct Driver *d);

void DECOMP_VehPhysProc_SlamWall_PhysAngular(struct Thread *t, struct Driver *d);
void DECOMP_VehPhysProc_SlamWall_Update(struct Thread *t, struct Driver *d);
void DECOMP_VehPhysProc_SlamWall_PhysLinear(struct Thread *t, struct Driver *d);
void DECOMP_VehPhysProc_SlamWall_Animate(struct Thread *t, struct Driver *d);
void DECOMP_VehPhysProc_SlamWall_Init(struct Thread *t, struct Driver *d);

void DECOMP_VehPhysProc_SpinFirst_Update(struct Thread *t, struct Driver *d);
void DECOMP_VehPhysProc_SpinFirst_PhysLinear(struct Thread *t, struct Driver *d);
void DECOMP_VehPhysProc_SpinFirst_PhysAngular(struct Thread *t, struct Driver *d);
void DECOMP_VehPhysProc_SpinFirst_InitSetUpdate(struct Thread *t, struct Driver *d);
void DECOMP_VehPhysProc_SpinFirst_Init(struct Thread *t, struct Driver *d);

void DECOMP_VehPhysProc_SpinLast_Update(struct Thread *t, struct Driver *d);
void DECOMP_VehPhysProc_SpinLast_PhysLinear(struct Thread *t, struct Driver *d);
void DECOMP_VehPhysProc_SpinLast_PhysAngular(struct Thread *t, struct Driver *d);
void DECOMP_VehPhysProc_SpinLast_Init(struct Thread *t, struct Driver *d);

void DECOMP_VehPhysProc_SpinStop_Update(struct Thread *t, struct Driver *d);
void DECOMP_VehPhysProc_SpinStop_PhysLinear(struct Thread *t, struct Driver *d);
void DECOMP_VehPhysProc_SpinStop_PhysAngular(struct Thread *t, struct Driver *d);
void DECOMP_VehPhysProc_SpinStop_Animate(struct Thread *t, struct Driver *d);
void DECOMP_VehPhysProc_SpinStop_Init(struct Thread *t, struct Driver *d);

void DECOMP_VehStuckProc_RevEngine_Update(struct Thread *t, struct Driver *d);
void DECOMP_VehStuckProc_RevEngine_PhysLinear(struct Thread *t, struct Driver *d);
void DECOMP_VehStuckProc_RevEngine_Animate(struct Thread *t, struct Driver *d);
void DECOMP_VehStuckProc_RevEngine_Init(struct Thread *t, struct Driver *d);

void DECOMP_VehStuckProc_Warp_Init(struct Thread *t, struct Driver *d);

void DECOMP_VehPhysForce_ConvertSpeedToVec(struct Driver* driver);
void DECOMP_VehPhysForce_AccelTerrainSlope(struct Driver *driver);
void DECOMP_VehPhysForce_OnApplyForces(struct Thread *t, struct Driver *d);
void DECOMP_VehPhysGeneral_SetHeldItem(struct Driver* driver);
void DECOMP_VehPickupItem_ShootOnCirclePress(struct Driver *d);
void DECOMP_VehFire_Audio(struct Driver* driver, int speed_cap);
void DECOMP_VehFire_Increment(struct Driver* driver, int reserves, u_int type, int fireLevel);
void DECOMP_VehTurbo_ThTick(struct Thread* t);
void DECOMP_VehTurbo_ThDestroy(struct Thread* t);

void DECOMP_VehStuckProc_Tumble_Update(struct Thread *thread, struct Driver *driver);
void DECOMP_VehStuckProc_Tumble_PhysLinear(struct Thread *thread, struct Driver *driver);
void DECOMP_VehStuckProc_Tumble_PhysAngular(struct Thread *thread, struct Driver *driver);
void DECOMP_VehStuckProc_Tumble_Animate(struct Thread *thread,struct Driver *driver);

// 230
void DECOMP_MM_Battle_DrawIcon_Character(struct Icon* icon, int posX, int posY, struct PrimMem* primMem, u_long* ot, char transparency, short scale);
unsigned char DECOMP_MM_TransitionInOut(struct TransitionMeta* meta, int framesPassed, int numFrames);
void DECOMP_MM_Title_MenuUpdate(void);
void DECOMP_MM_Title_SetTrophyDPP(void);
void DECOMP_MM_Title_CameraMove(struct Title* title, int frameIndex);
void DECOMP_MM_Title_ThTick(struct Thread *title);
void DECOMP_MM_Title_Init(void);
void DECOMP_MM_Title_CameraReset(void);
void DECOMP_MM_Title_KillThread(void);
void DECOMP_MM_ParseCheatCodes();
void DECOMP_MM_MenuProc_Main(struct RectMenu *mainMenu);
void DECOMP_MM_ToggleRows_PlayerCount();
void DECOMP_MM_MenuProc_1p2p(struct RectMenu* menu);
void DECOMP_MM_MenuProc_2p3p4p(struct RectMenu * menu);
void DECOMP_MM_ToggleRows_Difficulty(void);
void DECOMP_MM_MenuProc_Difficulty(struct RectMenu* menu);
void DECOMP_MM_MenuProc_SingleCup(struct RectMenu* menu);
void DECOMP_MM_MenuProc_NewLoad(struct RectMenu* menu);
struct RectMenu* DECOMP_MM_AdvNewLoad_GetMenuPtr(void);
void DECOMP_MM_Characters_AnimateColors(unsigned char *colorData, short playerID, short flag);
int DECOMP_MM_Characters_GetNextDriver(short dpad, char characterID);
u_int DECOMP_MM_Characters_boolIsInvalid(short* globalIconPerPlayer, short characterID, short player);
struct Model* DECOMP_MM_Characters_GetModelByName(int *name);
void DECOMP_MM_Characters_DrawWindows(int boolShowDrivers);
void DECOMP_MM_Characters_SetMenuLayout(void);
void DECOMP_MM_Characters_BackupIDs(void);
void DECOMP_MM_Characters_PreventOverlap(void);
void DECOMP_MM_Characters_RestoreIDs(void);
void DECOMP_MM_Characters_HideDrivers(void);
void DECOMP_MM_Characters_MenuProc(struct RectMenu* unused);
void DECOMP_MM_TrackSelect_Video_SetDefaults(void);
void DECOMP_MM_TrackSelect_Video_State(int state);
void DECOMP_MM_TrackSelect_Video_Draw(RECT *r, struct MainMenu_LevelRow *selectMenu, int trackIndex, int param_4, u_short param_5);
char DECOMP_MM_TrackSelect_boolTrackOpen(struct MainMenu_LevelRow* menuSelect);
void DECOMP_MM_TrackSelect_Init();
void DECOMP_MM_TrackSelect_MenuProc(struct RectMenu* menu);
void* DECOMP_MM_TrackSelect_GetMenuPtr();
void DECOMP_MM_CupSelect_Init(void);
void DECOMP_MM_CupSelect_MenuProc(struct RectMenu* menu);
void DECOMP_MM_Battle_CloseSubMenu(struct RectMenu* menu);
void DECOMP_MM_Battle_DrawIcon_Weapon(struct Icon *icon,
		u_int posX, int posY, struct PrimMem *primMem, u_int *ot,
        char transparency, short param_7, u_short param_8, u_int *color);
void DECOMP_MM_Battle_Init(void);
void DECOMP_MM_Battle_MenuProc(struct RectMenu* unused);
void DECOMP_MM_HighScore_Text3D(char *string, int posX, int posY, short font, u_int flags);
void DECOMP_MM_HighScore_Draw(u_short trackIndex, u_int rowIndex, u_int posX, u_int posY);
void DECOMP_MM_HighScore_Init(void);
void DECOMP_MM_HighScore_MenuProc(struct RectMenu* unused);
void DECOMP_MM_Scrapbook_Init(void);
void DECOMP_MM_Scrapbook_PlayMovie(struct RectMenu* menu);
void DECOMP_MM_ResetAllMenus(void);
void DECOMP_MM_JumpTo_Title_Returning(void);
void DECOMP_MM_JumpTo_Title_FirstTime(void);
void DECOMP_MM_JumpTo_BattleSetup(void);
void DECOMP_MM_JumpTo_TrackSelect(void);
void DECOMP_MM_JumpTo_Characters(void);
void DECOMP_MM_JumpTo_Scrapbook(void);

// soon to have DECOMP prefix
void MM_Video_DecDCToutCallbackFunc(void);
void MM_Video_KickCD(CdlLOC *location);
void MM_Video_VLC_Decode(void);
void MM_Video_StartStream(int param_1, int numFrames);
void MM_Video_StopStream(void);
void MM_Video_AllocMem(u_int width, u_short height, u_int flags, int size, int param_5);
void MM_Video_ClearMem(void);
u_int MM_Video_DecodeFrame(short offsetX, short offsetY);
u_int MM_Video_CheckIfFinished(int param_1);

// 231 (undone)
void DECOMP_RB_Player_ModifyWumpa(struct Driver* driver, int wumpaDelta);
void DECOMP_RB_MinePool_Init(void);
void DECOMP_RB_MinePool_Remove(struct MineWeapon* mw);
void DECOMP_RB_MinePool_Add(struct MineWeapon* mw);

void DECOMP_RB_MaskWeapon_FadeAway(struct Thread* t);
void DECOMP_RB_MaskWeapon_ThTick(struct Thread* maskTh);

struct Instance* DECOMP_RB_Hazard_CollideWithDrivers(
	struct Instance* weaponInst, char boolCanSkipParent,
	int hitRadius, struct Instance* mineDriverInst
);

struct Instance* DECOMP_RB_Hazard_CollideWithBucket(
	struct Instance* weaponInst,
	struct Thread* weaponTh, struct Thread* bucket,
	char boolCanSkipParent, int hitRadius, struct Instance* mineDriverInst
);

int DECOMP_RB_Hazard_ThCollide_Missile(struct Thread* thread);
int DECOMP_RB_Hazard_ThCollide_Generic(struct Thread* thread);

int DECOMP_RB_Hazard_InterpolateValue(short currRot, short desiredRot, short rotSpeed);

void DECOMP_RB_MovingExplosive_ThTick(struct Thread* t);

void DECOMP_RB_MovingExplosive_Explode(
	struct Thread* t,
	struct Instance* inst,
	struct TrackerWeapon* tw);

void DECOMP_RB_RainCloud_FadeAway(struct Thread* t);
void DECOMP_RB_RainCloud_ThTick(struct Thread* t);
void DECOMP_RB_RainCloud_Init(struct Driver* d);

struct Thread* DECOMP_RB_GetThread_ClosestTracker(struct Driver* d);
void DECOMP_RB_Baron_LInB(struct Instance* inst);

void DECOMP_RB_Blade_ThTick(struct Thread* t);
void DECOMP_RB_Blade_LInB(struct Instance* inst);

void DECOMP_RB_Armadillo_ThTick_TurnAround(struct Thread* t);
void DECOMP_RB_Armadillo_ThTick_Rolling(struct Thread* t);
void DECOMP_RB_Armadillo_LInB(struct Instance* inst);

void DECOMP_RB_Fireball_ThTick(struct Thread* t);
void DECOMP_RB_Fireball_LInB(struct Instance* inst);

void DECOMP_RB_Minecart_ThTick(struct Thread* t);
void DECOMP_RB_Minecart_LInB(struct Instance* inst);

void DECOMP_RB_Plant_LInB(struct Instance* inst);

void DECOMP_RB_Seal_ThTick_Move(struct Thread* t);
void DECOMP_RB_Seal_ThTick_TurnAround(struct Thread* t);
void DECOMP_RB_Seal_LInB(struct Instance* inst);

void DECOMP_RB_Snowball_ThTick(struct Thread* t);
void DECOMP_RB_Snowball_LInB(struct Instance* inst);

void DECOMP_RB_Spider_LInB(struct Instance* inst);

void DECOMP_RB_Turtle_ThTick(struct Thread* t);
int DECOMP_RB_Turtle_LInC(struct Instance* inst, struct Thread* driverTh);
void DECOMP_RB_Turtle_LInB(struct Instance* inst);

// 232
short* DECOMP_AH_WarpPad_GetSpawnPosRot(short* posData);
void DECOMP_AH_WarpPad_AllWarppadNum();
void DECOMP_AH_WarpPad_MenuProc(struct RectMenu* menu);

void DECOMP_AH_WarpPad_SpinRewards(
	struct Instance* prizeInst,
	struct WarpPad* warppadObj,
	int index,
	int x, int y, int z);

void DECOMP_AH_WarpPad_ThTick(struct Thread* t);
void DECOMP_AH_WarpPad_ThDestroy(struct Thread* t);
void DECOMP_AH_WarpPad_LInB(struct Instance* inst);
void DECOMP_AH_Garage_ThDestroy(struct Thread* t);
void DECOMP_AH_Garage_Open(struct ScratchpadStruct* sps,struct Thread* otherTh);
void DECOMP_AH_Garage_ThTick(struct Thread *t);
void DECOMP_AH_Garage_LInB(struct Instance *inst);
void DECOMP_AH_SaveObj_ThDestroy(struct Thread* t);
void DECOMP_AH_SaveObj_ThTick(struct Thread* t);
void DECOMP_AH_SaveObj_LInB(struct Instance* savInst);
void DECOMP_AH_Door_ThDestroy(struct Thread* t);
void DECOMP_AH_Door_ThTick(struct Thread* t);
void DECOMP_AH_Door_LInB(struct Instance *inst);

void DECOMP_AH_Map_LoadSave_Prim(
	short* vertPos, char* vertCol,
	void* ot, struct PrimMem* primMem);

void DECOMP_AH_Map_LoadSave_Full(
	int posX, int posY,
	short* vertPos, char* vertCol,
	int unk800, int angle);

void DECOMP_AH_Map_HubArrow(
	int posX, int posY,
	short* vertPos, char* vertCol,
	int unk800, int angle);

void DECOMP_AH_Map_HubArrowOutter(
	void* hubPtrs, int arrowIndex,
	int posX, int posY,
	int inputAngle, int type);

void DECOMP_AH_Map_HubItems(void* hubPtrs, short *param_2);
void DECOMP_AH_Map_Warppads(short* ptrMap, struct Thread* warppadThread, short *param_3);
void DECOMP_AH_Map_Main(void);
void DECOMP_AH_Pause_Destroy(void);
void DECOMP_AH_Pause_Draw(int pageID, int posX);
void DECOMP_AH_Pause_Update();
void DECOMP_AH_HintMenu_FiveArrows(int param_1,short rotation);
void DECOMP_AH_HintMenu_MaskPosRot(void);
void DECOMP_AH_HintMenu_MenuProc(struct RectMenu* menu);
void DECOMP_AH_MaskHint_Start(short hintId, u_short bool_interruptWarppad);
int DECOMP_AH_MaskHint_boolCanSpawn();
void DECOMP_AH_MaskHint_SetAnim(int scale);

void DECOMP_AH_MaskHint_SpawnParticles(
	short numParticles,struct ParticleEmitter* emSet,int maskAnim);

void DECOMP_AH_MaskHint_LerpVol(int param_1);
void DECOMP_AH_MaskHint_Update();

// 233
void DECOMP_CS_Garage_ZoomOut(char zoomState);
void DECOMP_CS_Garage_MenuProc(void);
void DECOMP_CS_Garage_Init(void);
struct RectMenu* DECOMP_CS_Garage_GetMenuPtr(void);