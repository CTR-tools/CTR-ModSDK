#include <common.h>

// menu variables
#if BUILD == UsaRetail
#define menuPointer 0x800B4540
#endif
#if BUILD == EurRetail
#define menuPointer 0x800B4CB4
#endif
#if BUILD == JpnRetail
#define menuPointer 0x800B7FC4
#endif

// constants
#define driverSize 0x19C
#define instanceSize 0x3F
#define soundSize 0xC0
#define numEngines 5
#define USA_NumEngines 4
#define numCharacters 16
#define numMetaphys 65
#define numSlots 5
#define saffi 0x8001
#define textDuration 3 * 30
#define numSpeedColor 10
#define jump 0x2500
#if BUILD == EurRetail
#define msFrame 38
#else
#define msFrame 32
#endif

struct P_ROM
{

int engine;
u_char swappedEngine;

// Save state variables
int * firstInstance;
int * firstSound;
int numSounds[numSlots];
int clock[numSlots][4];
void ** ghostBufferPointer[numSlots];

// Audio variables
int fxVol;
char waitFrame;

// Control flow variables
int slot;
char isSlot;
char hasSaved[numSlots];
char isFlying;
char isGhost;
int maskInstructions[3];
short lagFrames;
unsigned short lagTime;
short lagDuration;
short jumpBackup;
int currlevel;
char flagFrame;

// String variables
int drawDuration;

// Engine swap strings flow
char * currEngine;
char * slotString;
};

// Strings positions
// x
#define x_speed 0x190 - 15
#define x_reserves 0x1AA - 15
#define x_checkpointStr 0x14
#define x_checkpoint 0x50
#define x_progressStr 0x14
#define x_progress 0x50
#define x_engine 0x14
#define x_frames 196
#define x_numFrames 196 + 0x3C + 15
#define x_total 171
#define x_lag 171 + 0x3C

// y
#if BUILD == EurRetail
#define y_speed 0x8C + 0x14
#define y_reserves 0xBF + 0x14
#define y_checkpointStr 0xC8 + 0x14
#define y_checkpoint 0xC8 + 0x14
#define y_progressStr 0xBF + 0x14
#define y_progress 0xBF + 0x14
#define y_engine 0xB6 + 0x14
#else
#define y_speed 0xAD
#define y_reserves 0xBF
#define y_checkpointStr 0xC8
#define y_checkpoint 0xC8
#define y_progressStr 0xBF
#define y_progress 0xBF
#define y_engine 0xB6
#endif
#define y_frames 17
#define y_numFrames 17
#define y_total 26
#define y_lag 26

register struct P_ROM* p_rom asm("k1");