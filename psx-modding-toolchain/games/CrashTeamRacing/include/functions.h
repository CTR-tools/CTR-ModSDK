// included from common.h, do not include common.h

// remember to ctrl + f ctrl + r the DECOMP_ prefix

// BOTS

void BOTS_SetGlobalNavData(short index);
void BOTS_InitNavPath(struct GameTracker* gGT, short index);
void BOTS_EmptyFunc();
int BOTS_Adv_NumTimesLostEvent(int index);
void BOTS_Adv_AdjustDifficulty();
void BOTS_UpdateGlobals();
void BOTS_SetRotation(int param_1, int param_2);
void BOTS_LevInstColl(int param_1);
void BOTS_ThTick_EngineRevving(int param_1);
void BOTS_MaskGrab(int param_1);
void BOTS_Killplane(int param_1);
void BOTS_ThTick_Drive(struct Thread* thread);
u_int BOTS_ChangeState(int param_1, int param_2, int param_3, int param_4);
void BOTS_CollideWithOtherAI(int param_1, int param_2);
void BOTS_GotoStartingLine(struct Driver* driver);
struct Driver* BOTS_Driver_Init(int slot);
void BOTS_Driver_Convert(struct Driver* driver);

// CAM

void CAM_SkyboxGlow(short* param_1, struct Camera110* camera, struct PrimMem* primMem, u_long* ptrOT);
void CAM_ClearScreen(struct GameTracker* gGT);
void CAM_Init(struct CameraDC* cDC, int cameraID, struct Driver* d, struct Camera110* c110);
void CAM_FindClosestQuadblock(short* scratchpad, struct CameraDC* cDC, struct Driver* d, short* param_4);
int CAM_Path_GetNumPoints();
u_int CAM_Path_Move(int frame, u_short* param_2, u_short* param_3, u_short* param_4);
void CAM_StartOfRace(struct CameraDC* cDC);
void CAM_EndOfRace_Battle(struct CameraDC* cDC, struct Driver* d);
void CAM_EndOfRace(struct CameraDC* cDC, struct Driver* d);
u_char* CAM_StartLine_FlyIn_FixY(u_short* param_1);
void CAM_ProcessTransition(short* camPosReturn, u_short* camRotReturn, short* camPosDest, short* camRotDest, short* camPosStart, short* camRotStart, int frame);
void CAM_FollowDriver_AngleAxis(struct CameraDC* cDC, struct Driver* d, int param_3, short* cam110Pos, short* cam110Rot);
void CAM_StartLine_FlyIn(int* param_1, short const0x96, int frame, u_short* camTransitionToPos, short* camTransitionToRot);
u_int CAM_FollowDriver_TrackPath(struct CameraDC* cDC, short* param_2, int cDCspeed, int param_4);
void CAM_LookAtPosition(int param_1, int* driverPos, short* camTransitionToPos, short* camTransitionToRot);
void CAM_FollowDriver_Spin360(struct CameraDC* cDC, u_int param_2, struct Driver* d, short* camTransitionToPos, u_int param_5);
void CAM_SetDesiredPosRot(int param_1, u_short* param_2, u_short* param_3);
void CAM_FollowDriver_Normal(struct CameraDC* cDC, struct Driver* d, short* camera110, short scratchpad, short* param_5);
int CAM_MapRange_PosPoints(short* vec3sPos1, short* vec3sPos2, short* vec3iPos);
void CAM_ThTick(struct Thread* t);

// CDSYS

u_int CDSYS_Init(int useDisc);
u_int CDSYS_GetFilePosInt(char* fileString, int* filePos);
void CDSYS_SetMode_StreamData();
void CDSYS_SetMode_StreamAudio();
u_int CDSYS_SetXAToLang(int lngIndex);
void CDSYS_CdSyncCallback(char result);
void CDSYS_CdReadyCallback(char result);
void CDSYS_IRQ_Callback();
void CDSYS_Transfer_Callback();
void CDSYS_IRQ_Enable();
void CDSYS_IRQ_Disable();
void CDSYS_ParseSpuData();
u_int CDSYS_XAGetNumTracks(int categoryID);
u_int CDSYS_XASeek(int isCdControl, int categoryID, int audioTrackID);
u_int CDSYS_XAGetTrackLength(int categoryID, int audioTrackID);
void CDSYS_XAPlay(int categoryID, int index);
void CDSYS_XAPauseRequest();
void CDSYS_XAPauseForce();
void CDSYS_XAPauseAtEnd();

// COLL

u_char* COLL_LevModelMeta(u_int index);
u_int COLL_Instance(short* param_1, struct VisData* instanceHitbox);
void COLL_PerVisData_CheckInstances(struct VisData* node, int param_2);
void COLL_StartSearch_AI(short* posCurr, short* posPrev, short* param_3);
void COLL_StartSearch_Player(struct Thread* t, struct Driver* d);
void COLL_SearchTree_FindQuadblock_Touching(u_int* posTop, u_int* posBottom, u_int* param_3, int param_4);
void COLL_SearchTree_FindX(struct VisData* param_1, struct BoundingBox* bbox, u_int* callback, u_int param_4);
u_int FUN_8001ede4(u_short* param_1, short* param_2, short* param_3, short* param_4);
void FUN_8001ef1c();
void FUN_8001ef50(int param_1, short* param_2, short* param_3, short* param_4);
void FUN_8001f2dc(int param_1, short* param_2, short* param_3, short* param_4);
void COLL_PerQuadblock_CheckTriangles_Touching(struct QuadBlock* qb, int param_2);
void COLL_PerVisData_CheckQuadblocks_Touching(struct VisData* node, int param_2);
void FUN_8001f67c(int param_1, int param_2);
void FUN_8001f6f0(int param_1, int param_2);
void FUN_8001f7f0(int param_1);
u_int FUN_8001f928(u_int* param_1, u_int* param_2, u_int* param_3, u_int* param_4);
void FUN_8001fc40(u_int* param_1, int param_2, u_int param_3, u_int param_4);
void COLL_PerQuadblock_CheckTriangles_NearPlayer(struct QuadBlock* qb, int param_2);
void COLL_PerVisData_CheckQuadblocks_NearPlayer(struct VisData* node, int param_2);
void FUN_80020334(struct QuadBlock* qb, int triangleID, int param_3);
void COLL_StartSearch_NearPlayer(struct Thread* t, struct Driver* d);
u_int COLL_Scrub(struct Driver* d, struct Thread* t, int param_3, int param_4, int* param_5);

// CTR

void CTR_Box_DrawWirePrims(u_short x, u_short y, u_short u, u_short v, u_char r, u_char g, u_char b, u_long* otMem, struct PrimMem* primMem);
void CTR_Box_DrawWireBox(RECT* r, int* unk, u_long* ot, struct PrimMem* primMem);
void CTR_Box_DrawClearBox(RECT* r, u_int rgb, int param_3, u_long* otMem, struct PrimMem* primMem);
void CTR_Box_DrawSolidBox(RECT* r, u_int rgb, u_long* otMem, struct PrimMem* primMem);
void CTR_CycleTex_LEV(struct AnimTex* animtex, int timer);
//void CTR_CycleTex_Model(void* animtex, int timer);
void CTR_CycleTex_AllModels(int param_1, struct Model* model, u_int param_3);
//CTR_CycleTex_2p3p4pWumpaHUD();
void CTR_ClearRenderLists_1P2P(struct GameTracker* gGT, int numPlyrCurrGame);
void CTR_ClearRenderLists_3P4P(struct GameTracker* gGT, int numPlyrCurrGame);
void CTR_EmptyFunc_MainFrame_ResetDB();
void CTR_ErrorScreen(char r, char g, char b);
//CTR_MatrixToRot();
//CTR_ScrambleGhostString();

// unorganized

void JitPool_Clear(struct JitPool* AP);
void JitPool_Init(struct JitPool* AP, int maxItems, int itemSize, char* name);
int JitPool_Add(struct JitPool* AP);
void JitPool_Remove(struct JitPool* AP, struct Item* item);

void LIST_Clear(struct LinkedList* L);
void LIST_AddFront(struct LinkedList* L, struct Item* I);
void LIST_AddBack(struct LinkedList* L, struct Item* I);
// two more
struct Item* LIST_RemoveMember(struct LinkedList* L, struct Item* I);
struct Item* LIST_RemoveFront(struct LinkedList* L);
struct Item* LIST_RemoveBack(struct LinkedList* L);

void* MEMPACK_AllocMem(int allocSize);
void* MEMPACK_ReallocMem(int allocSize);

void Player_Driving_PhysLinear(struct Thread* thread, struct Driver* driver);

void howl_StopAudio(int clearBackupStats, int bool_DestroyMusic, int bool_DestroyAllSFX);
void howl_UnPauseAudio();
void OtherFX_Stop2(int soundID_count);
void howl_PauseAudio();
void LOAD_Hub_Main(struct BigHeader* bigfile);
void DecalGlobal_EmptyFunc_MainFrame_ResetDB();
u_int OtherFX_Play_LowLevel(u_int param_1, u_char param_2, u_int param_3);
void DISPLAY_Blur_Main(struct Camera110* c110, int strength);
void ThreadBucketTickAll(struct Thread* thread);
void GhostBuffer_RecordStats(short param_1);
void Particle_UpdateAllParticles();
void RB_Bubbles_RoosTubes();
void RB_Burst_DrawAll(int param_1);
void THREAD_CheckAllForDead();
void Audio_Update1();
u_int GAMEPAD_GetNumConnected(struct GamepadSystem* gGamepads);
void Weapon_Shoot_OnCirclePress(struct Driver* driver);
void MenuBox_ClearInput();
void ElimBG_Deactivate(int param_1);
void MenuBox_Hide(struct MenuBox* mb);
u_int CheckeredFlag_IsFullyOnScreen();
void MainFreeze_IfPressStart();
short OSK_DrawMenu(u_short param_1);
void LoadSave_ToggleMode(u_int param_1);
void EndOfRace_DrawAllComments();
void EndOfRace_Battle();







u_int LOAD_IsOpen_MainMenu();
int MainFrame_HaveAllPads(short param_1);
void DecalFont_DrawLine(char* str, int posX, int posY, short fontType, int flags);
void DrawTextBackground(RECT* r, int flag, u_long* ot);
void InterpolatePosition2D_Linear(short* ptrPos, short startX, short startY, short endX, short endY, int curFrame, short endFrame);
void DecalFont_DrawLineOT(char* str, int posX, int posY, short fontType, int flags, u_long* ot);
void ElimBG_HandleState(struct GameTracker* gGT);
void MainFrame_VisMemFullFrame(struct GameTracker* gGT, struct Level* level);
void CTR_CycleTex_LEV(struct AnimTex* animtex, int timer);
void MenuBox_CollectInput();
void MenuBox_ProcessState();
void Camera110_UpdateFrustum(struct Camera110* c110);
void EffectSfxRain_MakeSound(struct GameTracker* gGT);
void RenderWeather(struct Camera110* c110, struct PrimMem* primMem, struct RainBuffer* rainBuffer, char numPlyr, int gameMode1);
void DrawConfetti(struct Camera110* c110, struct PrimMem* primMem, void* confetti, int frameTimer, int gameMode1);
void RenderStars(struct Camera110* c110, struct PrimMem* primMem, void* stars, char numPlyr);
void DecalMP_01(struct GameTracker* gGT);
void CupStandings_InputAndDraw();
void DrawHUD_Racing();
void DrawHUD_CrystalChallenge();
void VB_EndEvent_DrawMenu();
void RR_EndEvent_DrawMenu();
void AA_EndEvent_DrawMenu();
void TT_EndEvent_DrawMenu();
void CC_EndEvent_DrawMenu();
void LOAD_OvrThreads(u_int param_1);
u_int LOAD_IsOpen_AdvHub();
void DrawHUD_AdvStrings();
void AH_Map_Main();
void AH_MaskHint_Start(short requestedHint, short bool_interruptWarppad);
void INSTANCE_LevRestartLInBs(void* instDefs, u_int numInstances);
void DrawIntroRaceText_1P();
void RedBeaker_RenderRain(struct Camera110* c110, struct PrimMem* primMem, struct JitPool* rain, char numPlyr, int gameMode1);
u_int LOAD_IsOpen_Podiums();
void CS_BoxScene_InstanceSplitLines();
void* RenderBucket_QueueLevInstances(struct CameraDC* cDC, u_long* otMem, void* rbi, char* lod, char numPlyr, int gameMode1);
void* RenderBucket_QueueNonLevInstances(struct Item* item, u_long* otMem, void* rbi, char* lod, char numPlyr, int gameMode1);
void Particle_RenderList(struct Camera110* c110, void* particleList);
void Camera110_SetDrawEnv_Normal(u_long* ot, struct Camera110* c110, struct DB* backBuffer, short* param_4, u_char param_5);
void DecalMP_02(struct GameTracker* gGT);
void RB_Player_ToggleInvisible();
void RB_Player_ToggleFlicker();
void RB_Burst_ProcessBucket(struct Thread* thread);
void RB_Blowup_ProcessBucket(struct Thread* thread);
void RB_Spider_DrawWebs(struct Thread* thread, struct Camera110* c110);
void RB_Follower_ProcessBucket(struct Thread* thread);
void RB_StartText_ProcessBucket(struct Thread* thread);
void AH_WarpPad_AllWarppadNum();
void Turbo_ProcessBucket(struct Thread* turboThread);
void DrawSkidMarks_Main(struct Thread* thread, struct Camera110* c110);
void MM_Title_SetTrophyDPP();
void RenderBucket_Execute(void* param_1, struct PrimMem* param_2);
void DrawTires_Solid(struct Thread* thread, struct PrimMem* primMem, char numPlyr);
void DrawTires_Reflection(struct Thread* thread, struct PrimMem* primMem, char numPlyr);
void DrawShadows_Main();
void DrawHeat_Main(void* particleList_heatWarp, struct Camera110* c110, struct PrimMem* primMem, char numPlyr, int swapchainIndex);
void Camera110_FadeAllWindows();
void AnimateWater2P(int timer, int count_water, struct WaterVert* waterVert, void* waterEnvMap, int* param_5, int* param_6);
void VisData_CopyJMPsToScratchpad();
int CreateRenderLists_1P2P(struct VisData* visData, int* visLeafList, struct Camera110* c110, u_int LevRenderList, void* bspList, char numPlyr);
void DrawLevelPrims_EntryFunc(void* LevRenderList, struct Camera110* c110, struct VisData* visData, struct PrimMem* primMem, int* param_5, int* param_6, void* waterEnvMap);
void AnimateWater1P(int timer, int count_water, struct WaterVert* waterVert, void* waterEnvMap, int* param_5);
void AnimateQuad(int timer, int numSCVert, void* ptrSCVert, int* visSCVertList);
void DrawSky_Full(void* skybox, struct Camera110* c110, struct PrimMem* primMem);
void AnimateWater3P(int timer, int count_water, struct WaterVert* waterVert, void* waterEnvMap, int* param_5, int* param_6, int* param_7);
void AnimateWater4P(int timer, int count_water, struct WaterVert* waterVert, void* waterEnvMap, int* param_5, int* param_6, int* param_7, int* param_8);
int CreateRenderLists_3P4P(struct VisData* visData, int* visLeafList, struct Camera110* c110, u_int LevRenderList, void* bspList);
void DrawHUD_Wumpa3D_2P3P4P(struct GameTracker* gGT);
void DecalMP_03(struct GameTracker* gGT);
void DotLights_AudioAndVideo(struct GameTracker* gGT);
void DrawBoxOutline_LowLevel(RECT* r, short x, u_short y, int* ptrColor, short param_5, u_long* ptrOT);
void RivalWeapons_Update();
void StartLine_Update();
void unk80047d64();
void CheckeredFlag_DrawSelf();
int RCNT_GetTime_Total();
void BreakDraw();
u_int MM_Video_CheckIfFinished(int param_1);
int RCNT_GetTime_Elapsed(int time, void* param_2);