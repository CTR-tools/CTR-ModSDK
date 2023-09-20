#include <common.h>

void DECOMP_CDSYS_XaCallbackCdSync(char result);
void DECOMP_CDSYS_XaCallbackCdReady(char result);
void DECOMP_CDSYS_SetMode_StreamData();

void DECOMP_MEMPACK_PopState();
int DECOMP_MEMPACK_PushState();

void DECOMP_LOAD_VramFileCallback();
void DECOMP_LOAD_ReadFileASyncCallback(char result);
void* DECOMP_LOAD_ReadFile(struct BigHeader* bigfile, u_int loadType, int subfileIndex, void* destination, int *size, void * callback);
void* DECOMP_LOAD_VramFile(void* bigfilePtr, int subfileIndex, int* ptrDestination, int* size, int callbackOrFlags);
void* DECOMP_LOAD_ReadDirectory(char* filename);
void* DECOMP_LOAD_ReadFile_NoCallback(char* filename, void* ptrDestination, int* size);