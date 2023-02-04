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
void COLL_SearchCallback_Instances(struct VisData* node, int param_2);
void COLL_StartSearch_AI(short* posCurr, short* posPrev, short* param_3);
void COLL_StartSearch_Player(struct Thread* t, struct Driver* d);
void COLL_SearchTree_NoCallback(u_int* posTop, u_int* posBottom, u_int* param_3, int param_4);
void COLL_SearchTree_WithCallback(struct VisData* param_1, struct BoundingBox* bbox, u_int* callback, u_int param_4);
u_int FUN_8001ede4(u_short* param_1, short* param_2, short* param_3, short* param_4);
void FUN_8001ef1c();
void FUN_8001ef50(int param_1, short* param_2, short* param_3, short* param_4);
void FUN_8001f2dc(int param_1, short* param_2, short* param_3, short* param_4);
void COLL_Quadblock_Graphics(struct QuadBlock* qb, int param_2);
void COLL_SearchCallback_QuadBlocks_Graphics(struct VisData* node, int param_2);
void FUN_8001f67c(int param_1, int param_2);
void FUN_8001f6f0(int param_1, int param_2);
void FUN_8001f7f0(int param_1);
u_int FUN_8001f928(u_int* param_1, u_int* param_2, u_int* param_3, u_int* param_4);
void FUN_8001fc40(u_int* param_1, int param_2, u_int param_3, u_int param_4);
void COLL_Quadblock_Physics(struct QuadBlock* qb, int param_2);
void COLL_SearchCallback_QuadBlocks_Physics(struct VisData* node, int param_2);
void FUN_80020334(struct QuadBlock* qb, int triangleID, int param_3);
void COLL_StartSearch_NearPlayer(struct Thread* t, struct Driver* d);
u_int COLL_Scrub(struct Driver* d, struct Thread* t, int param_3, int param_4, int* param_5);

// CTR

void CTR_Box_DrawWirePrims(u_short x, u_short y, u_short u, u_short v, u_char r, u_char g, u_char b, u_long* otMem, struct PrimMem* primMem);
void CTR_Box_DrawWireBox(RECT* r, int* unk, u_long* ot, struct PrimMem* primMem);
void CTR_Box_DrawClearBox(RECT* r, u_int rgb, int param_3, u_long* otMem, struct PrimMem* primMem);
void CTR_Box_DrawSolidBox(RECT* r, u_int rgb, u_long* otMem, struct PrimMem* primMem);
void CTR_CycleTex_LEV(void* animtex, int timer);
//CTR_CycleTex_Model();
//CTR_CycleTex_AllModels();
//CTR_CycleTex_2p3p4pWumpaHUD();
void CTR_ClearRenderLists_1P2P(struct GameTracker* gGT, int numPlyrCurrGame);
void CTR_ClearRenderLists_3P4P(struct GameTracker* gGT, int numPlyrCurrGame);
//CTR_EmptyFunc_MainFrame_ResetDB();
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