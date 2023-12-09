#include <common.h>

void DECOMP_CDSYS_SetXAToLang(int lang);
void DECOMP_CDSYS_XAPlay(int categoryID, int xaID);
void DECOMP_CDSYS_XAPauseAtEnd();
void DECOMP_CDSYS_XaCallbackCdSync(char result);
void DECOMP_CDSYS_XaCallbackCdReady(char result);
void DECOMP_CDSYS_SetMode_StreamData();

void DECOMP_CTR_CycleTex_AllModels(unsigned int numModels, struct Model** pModelArray, int timer);
void DECOMP_CTR_CycleTex_LEV(struct AnimTex* animtex, int timer);
void DECOMP_CTR_ErrorScreen(char r, char g, char b);
void CTR_CycleTex_AllModels(unsigned int numModels, struct Model** pModelArray, int timer);
void DECOMP_CTR_CycleTex_Model(struct AnimTex* animtex, int timer);

void DECOMP_CTR_Box_DrawClearBox(RECT* r, u_int* colorPtr, int transparency, u_long* ot, struct PrimMem* primMem);
void DECOMP_CTR_Box_DrawSolidBox(RECT* r, u_int* colorPtr, u_long* otMem, struct PrimMem* primMem);

// decal
void DECOMP_DecalFont_DrawLine(char* str, int posX, int posY, short fontType, int flags);
int DECOMP_DecalFont_DrawMultiLine(char* str, int posX, int posY, int maxPixLen, short fontType, int flags);
void DECOMP_DecalGlobal_Clear(struct GameTracker* gGT);
void DECOMP_DecalHUD_DrawPolyFT4(struct Icon* icon, short posX, short posY, struct PrimMem* primMem, u_long* ot, char transparency, short scale);
void DECOMP_DecalHUD_DrawPolyGT4(struct Icon* icon, short posX, short posY, struct PrimMem* primMem, u_long* ot, u_int color0, u_int color1, u_int color2, u_int color3, char transparency, short scale);

void DECOMP_DISPLAY_Swap(void);

// gamepad
void DECOMP_GAMEPAD_Init(struct GamepadSystem* gGamepads);
void DECOMP_GAMEPAD_PollVsync(struct GamepadSystem* gGamepads);
int DECOMP_GAMEPAD_GetNumConnected(struct GamepadSystem* gGamepads);
void DECOMP_GAMEPAD_ProcessHold(struct GamepadSystem* gGamepads);
void DECOMP_GAMEPAD_ProcessSticks(struct GamepadSystem* gGamepads);
void DECOMP_GAMEPAD_ProcessTapRelease(struct GamepadSystem* gGamepads);
void DECOMP_GAMEPAD_ProcessForceFeedback(struct GamepadSystem* gGamepads);
void DECOMP_GAMEPAD_ProcessAnyoneVars(struct GamepadSystem* gGamepads);

void DECOMP_GAMEPROG_NewGame_OnBoot();
void DECOMP_GAMEPROG_GetPtrHighScoreTrack();

// howl
void DECOMP_cseq_opcode00_empty(); // should remove
void DECOMP_cseq_opcode01_noteoff();
void DECOMP_cseq_opcode02_empty(); // should remove
void DECOMP_cseq_opcode03();
void DECOMP_cseq_opcode04_empty(); // should remove
void DECOMP_cseq_opcode05_noteon();
void DECOMP_cseq_opcode06();
void DECOMP_cseq_opcode07();
void DECOMP_cseq_opcode08();
void DECOMP_cseq_opcode09();
void DECOMP_cseq_opcode0a();
void DECOMP_howl_InitGlobals(char* filename);
void DECOMP_howl_LoadHeader(char* filename);

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

// JitPool
int DECOMP_JitPool_Add(struct JitPool* AP);
void DECOMP_JitPool_Clear(struct JitPool* AP);
void DECOMP_JitPool_Init(struct JitPool* AP, 
	int maxItems, int itemSize, char* name);
void DECOMP_JitPool_Remove(struct JitPool* AP, struct Item* item);

// LevInstDef
void DECOMP_LevInstDef_UnPack(struct mesh_info* ptr_mesh_info);
void DECOMP_LevInstDef_RePack(struct mesh_info* ptr_mesh_info, int boolAdvHub);

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

void DECOMP_LOAD_InitCD();
void DECOMP_LOAD_RunPtrMap(int origin, int* patchArr, int numPtrs);
void DECOMP_LOAD_LangFile(int bigfilePtr, int lang);
void DECOMP_LOAD_AppendQueue(int bigfile, int type, int fileIndex, void* destinationPtr, void* callback);
void DECOMP_LOAD_NextQueuedFile();

void DECOMP_MainDrawCb_Vsync();
void DECOMP_MainDrawCb_DrawSync();

void DECOMP_MainFrame_GameLogic(struct GameTracker* gGT, struct GamepadSystem* gGamepads);
void DECOMP_MainFrame_RenderFrame(struct GameTracker* gGT, struct GamepadSystem* gGamepads);
void DECOMP_MainFrame_ResetDB(struct GameTracker* gGT);

void DECOMP_MainInit_Drivers(struct GameTracker *gGT);
void DECOMP_MainInit_JitPoolsNew(struct GameTracker *gGT);
void DECOMP_MainInit_JitPoolsReset(struct GameTracker* gGT);
void DECOMP_MainInit_PrimMem(struct GameTracker* gGT);
void DECOMP_MainInit_OTMem(struct GameTracker* gGT);
void DECOMP_MainInit_FinalizeInit(struct GameTracker* gGT);
void DECOMP_MainInit_VRAMClear();
void DECOMP_MainInit_VRAMDisplay();

int DECOMP_MATH_Sin(u_int angle);
int DECOMP_MATH_Cos(u_int angle);

void DECOMP_MEMCARD_InitCard(void);
void DECOMP_MEMPACK_Init(int ramSize);
void DECOMP_MEMPACK_SwapPacks(int index);
void DECOMP_MEMPACK_NewPack_StartEnd(void* start,int size);
void DECOMP_MEMPACK_ClearHighMem();
void DECOMP_MEMPACK_PopToState(int id);

void* DECOMP_MEMPACK_AllocMem(int size);
void* DECOMP_MEMPACK_ReallocMem(int size);
void* DECOMP_MEMPACK_AllocHighMem(int allocSize);
int DECOMP_MEMPACK_GetFreeBytes();
void DECOMP_MEMPACK_PopState();
int DECOMP_MEMPACK_PushState();

void DECOMP_MENUBOX_DrawQuip(char *comment, short startX, int startY, u_int sizeX, short fontType,
                             int textFlag, short boxFlag);
void DECOMP_MENUBOX_DrawInnerRect(RECT* r, int x, void* ot);
void DECOMP_MENUBOX_DrawSelf(struct MenuBox* mb, int param_2, short param_3, short width);
void DECOMP_MENUBOX_DrawPolyGT4(struct Icon* icon, short posX, short posY, struct PrimMem* primMem, u_long* ot, u_int color0, u_int color1, u_int color2, u_int color3, char transparency, short scale);
int DECOMP_MENUBOX_BoolHidden(struct MenuBox* m);
void DECOMP_MENUBOX_ClearInput();
void DECOMP_MENUBOX_CollectInput();
void DECOMP_MENUBOX_ProcessState();
int DECOMP_MENUBOX_ProcessInput(struct MenuBox *m);
void DECOMP_MENUBOX_DrawOuterRect_Edge(RECT* r, u_int* rgb, u_int param_3, u_long* otMem);
void DECOMP_MENUBOX_DrawOuterRect_HighLevel(RECT* r, u_int* rgb, short param_3, u_long* otMem);
void DECOMP_MENUBOX_DrawOuterRect_LowLevel(RECT* p, short xOffset, u_short yOffset, u_int* rgb, short param_5, u_long* otMem);
u_char* DECOMP_MENUBOX_DrawTime(int milliseconds);
void DECOMP_MENUBOX_DrawRwdBlueRect_Subset(short *pos, int *color, u_long *ot, struct PrimMem *primMem);
void DECOMP_MENUBOX_DrawRwdBlueRect(RECT *rect, char *metas, u_long *ot, struct PrimMem *primMem);
void DECOMP_MENUBOX_DrawRwdTriangle(short* position,char* color,u_long* otMem,struct PrimMem* primMem);
void DECOMP_MENUBOX_GetHeight(struct MenuBox* m, short* height, int boolCheckSubmenu);
void DECOMP_MENUBOX_GetWidth(struct MenuBox* m, short* width, int boolCheckSubmenu);
void DECOMP_MENUBOX_Hide(struct MenuBox* m);
void DECOMP_MENUBOX_Show(struct MenuBox* m);

struct Thread* DECOMP_THREAD_BirthWithObject(
	int flags, void* funcThTick, 
	char* name, struct Thread* relativeTh);
void DECOMP_THREAD_CheckAllForDead();
void DECOMP_THREAD_CheckBloodlineForDead(struct Thread** replaceSelf, struct Thread* th);
void DECOMP_THREAD_CollidePointWithBucket(struct Thread* th, short* vec3_pos);
void DECOMP_THREAD_CollidePointWithSelf(struct Thread* th, struct Need_New_Name* buf);
void DECOMP_THREAD_DestroyInstance(struct Thread* t);
void DECOMP_THREAD_DestroyObject(void* object, int threadFlags);
void DECOMP_THREAD_DestroySelf(struct Thread* t);
void DECOMP_THREAD_DestroyTracker(struct Thread* t);
struct Thread* DECOMP_THREAD_SearchForModel(struct Thread* th, int modelID);

void DECOMP_TileView_Init(struct TileView* tileView, int id, int total);
void DECOMP_TileView_SetPsyqGeom(struct TileView* tileView);
void DECOMP_TileView_SetMatrixVP(struct TileView* tileView);

void DECOMP_TileView_SetDrawEnv_Normal(
		void* ot, struct TileView* tileView, struct DB* backBuffer,
		DRAWENV* copyDrawEnvNULL, int isbg);

void DECOMP_TitleFlag_SetCanDraw(short param_1);
void DECOMP_TitleFlag_BeginTransition(int direction);
void DECOMP_TitleFlag_SetFullyOnScreen();
void DECOMP_TitleFlag_SetFullyOffScreen();
void DECOMP_RCNT_Init();
void DECOMP_DecalFont_DrawLineStrlen(u_char* str, short len, int posX, short posY, short fontType, int flags);

void DECOMP_TitleFlag_DrawSelf();

void DECOMP_UI_Map_DrawMap(struct Icon* mapTop, struct Icon* mapBottom, short posX, short posY, struct PrimMem* primMem, u_long* otMem, u_int colorID);

struct Driver* DECOMP_VehInit_Player(int index);
void DECOMP_VehInit_NonGhost(struct Thread* t, int index);

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
void DECOMP_MM_MENUBOX_Main(struct MenuBox *mainMenu);
void DECOMP_MM_ToggleRows_PlayerCount();
void DECOMP_MM_MENUBOX_1p2p(struct MenuBox* mb);
void DECOMP_MM_MENUBOX_2p3p4p(struct MenuBox * mb);
void DECOMP_MM_ToggleRows_Difficulty(void);
void DECOMP_MM_MENUBOX_Difficulty(struct MenuBox* mb);
void DECOMP_MM_MENUBOX_SingleCup(struct MenuBox* mb);
void DECOMP_MM_MENUBOX_NewLoad(struct MenuBox* mb);
struct MenuBox* DECOMP_MM_AdvNewLoad_GetMenuBox(void);
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
void DECOMP_MM_Characters_MenuBox(struct MenuBox* unused);
void DECOMP_MM_TrackSelect_Video_SetDefaults(void);
void DECOMP_MM_TrackSelect_Video_State(int state);
void DECOMP_MM_TrackSelect_Video_Draw(RECT *r, struct MainMenu_LevelRow *selectMenu, int trackIndex, int param_4, u_short param_5);
char DECOMP_MM_TrackSelect_boolTrackOpen(struct MainMenu_LevelRow* menuSelect);
void DECOMP_MM_TrackSelect_Init();
void DECOMP_MM_TrackSelect_MenuBox(struct MenuBox *mb);
void* DECOMP_MM_TrackSelect_GetMenuBox();
void DECOMP_MM_CupSelect_Init(void);
void DECOMP_MM_CupSelect_MenuBox(struct MenuBox *mb);
void DECOMP_MM_Battle_CloseSubMenu(struct MenuBox *mb);
void DECOMP_MM_Battle_DrawIcon_Weapon(struct Icon *icon, 
		u_int posX, int posY, struct PrimMem *primMem, u_int *ot,
        char transparency, short param_7, u_short param_8, u_int *color);
void DECOMP_MM_Battle_Init(void);
void DECOMP_MM_Battle_MenuBox(struct MenuBox* unused);
void DECOMP_MM_HighScore_Text3D(char *string, int posX, int posY, short font, u_int flags);
void DECOMP_MM_HighScore_Draw(u_short trackIndex, u_int rowIndex, u_int posX, u_int posY);
void DECOMP_MM_HighScore_Init(void);
void DECOMP_MM_HighScore_MenuBox(struct MenuBox* unused);
void DECOMP_MM_Scrapbook_Init(void);
void DECOMP_MM_Scrapbook_PlayMovie(struct MenuBox *mb);
void DECOMP_MM_ResetAllMenus(void);
void DECOMP_MM_JumpTo_Title_Returning(void);
void DECOMP_MM_JumpTo_Title_FirstTime(void);
void DECOMP_MM_JumpTo_BattleSetup(void);
void DECOMP_MM_JumpTo_TrackSelect(void);
void DECOMP_MM_JumpTo_Characters(void);
void DECOMP_MM_JumpTo_Scrapbook(void);