#include <common.h>

void DECOMP_CDSYS_SetXAToLang(int lang);
void DECOMP_CDSYS_XAPlay(int categoryID, int xaID);
void DECOMP_CDSYS_XAPauseAtEnd();
void DECOMP_CDSYS_XaCallbackCdSync(char result);
void DECOMP_CDSYS_XaCallbackCdReady(char result);
void DECOMP_CDSYS_SetMode_StreamData();

void DECOMP_CTR_ErrorScreen(char r, char g, char b);

// decal
void DECOMP_DecalFont_DrawLine(char* str, int posX, int posY, short fontType, int flags);
int DECOMP_DecalFont_DrawMultiLine(char* str, int posX, int posY, int maxPixLen, short fontType, int flags);
void DECOMP_DecalGlobal_Clear(struct GameTracker* gGT);
void DECOMP_DecalHUD_DrawPolyGT4(struct Icon* icon, short posX, short posY, struct PrimMem* primMem, u_long* ot, u_int color0, u_int color1, u_int color2, u_int color3, char transparency, short scale);

void DECOMP_DISPLAY_Swap(void);

// gamepad
void DECOMP_GAMEPAD_Init(struct GamepadSystem* gGamepads);
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

void DECOMP_MainFrame_RenderFrame(struct GameTracker* gGT, struct GamepadSystem* gGamepads);
void DECOMP_MainFrame_ResetDB(struct GameTracker* gGT);

void DECOMP_MainInit_PrimMem(struct GameTracker* gGT);
void DECOMP_MainInit_OTMem(struct GameTracker* gGT);
void DECOMP_MainInit_FinalizeInit(struct GameTracker* gGT);
void DECOMP_MainInit_VRAMClear();
void DECOMP_MainInit_VRAMDisplay();

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

void DECOMP_TileView_Init(struct TileView* tileView, int id, int total);
void DECOMP_TileView_SetPsyqGeom(struct TileView* tileView);

void DECOMP_TileView_SetDrawEnv_Normal(
		void* ot, struct TileView* tileView, struct DB* backBuffer,
		DRAWENV* copyDrawEnvNULL, int isbg);
		
void DECOMP_TitleFlag_BeginTransition(int direction);
void DECOMP_TitleFlag_SetFullyOnScreen();
void DECOMP_TitleFlag_SetFullyOffScreen();
void DECOMP_RCNT_Init();
void DECOMP_DecalFont_DrawLineStrlen(u_char* str, short len, int posX, short posY, short fontType, int flags);