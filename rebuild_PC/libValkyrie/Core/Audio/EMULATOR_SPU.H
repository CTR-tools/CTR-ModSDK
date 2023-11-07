#ifndef EMULATOR_SPU_H
#define EMULATOR_SPU_H

#include "Core/Setup/Platform/EMULATOR_PLATFORM_SETUP.H"
#include "Core/Setup/Platform/EMULATOR_PLATFORM_INCLUDES.H"

#define SPU_MAX_CHANNELS 24
#define SPU_PLAYBACK_FREQUENCY (44100)
#define SPU_MS_PER_UPDATE 336*2
#define SPU_FPS 60
#define SPU_ADPCM_FRAME_SIZE 16
#define SPU_PCM_FRAME_SIZE 56
#define AUDIO_CHUNK_SIZE SPU_ADPCM_FRAME_SIZE * SPU_MS_PER_UPDATE
#define AUDIO_CHUNK_SIZE_PCM SPU_PCM_FRAME_SIZE * SPU_MS_PER_UPDATE
#define SPU_FINAL_BUFFER_SIZE 368*2

#define AUDIO_BUFFER_SIZE 28 * 2 * 4

#if defined(__ANDROID__)
#define SPU_USE_TIMER 1
#endif
#define OLD_SYSTEM

enum ADSRState
{
    ATTACK,
    DECAY,
    SUSTAIN,
    RELEASE
};

typedef struct ADSR
{
    int32_t state;
    int32_t attackmodeexp;
    int32_t attackrate;
    int32_t decayrate;
    int32_t sustainlevel;
    int32_t sustainmodexp;
    int32_t sustainincrease;
    int32_t sustainrate;
    int32_t releasemodeexp;
    int32_t releaserate;
    int32_t envelopevol;
    int32_t envelopevol_f;
    int32_t lvolume;
} adsr;

typedef struct Channel
{
    int32_t pitch;
    int32_t volL;
    int32_t volR;
    int32_t reverb;
    int32_t pos;
    int32_t s1, s2;
    int16_t block[28+28];
    uint8_t* data;
    uint8_t* loop;
    int32_t loop_s1, loop_s2;
    struct ADSR _adsr;
    int32_t sval;
    int32_t spos;
    int32_t iSBPos;
	int8_t silent;
	int8_t stop;
} channel;

typedef struct
{
	int StartAddr;      // reverb area start addr in samples
	int CurrAddr;       // reverb area curr addr in samples

	int VolLeft;
	int VolRight;
	int iLastRVBLeft;
	int iLastRVBRight;
	int iRVBLeft;
	int iRVBRight;

	int FB_SRC_A;       // (offset)
	int FB_SRC_B;       // (offset)
	int IIR_ALPHA;      // (coef.)
	int ACC_COEF_A;     // (coef.)
	int ACC_COEF_B;     // (coef.)
	int ACC_COEF_C;     // (coef.)
	int ACC_COEF_D;     // (coef.)
	int IIR_COEF;       // (coef.)
	int FB_ALPHA;       // (coef.)
	int FB_X;           // (coef.)
	int IIR_DEST_A0;    // (offset)
	int IIR_DEST_A1;    // (offset)
	int ACC_SRC_A0;     // (offset)
	int ACC_SRC_A1;     // (offset)
	int ACC_SRC_B0;     // (offset)
	int ACC_SRC_B1;     // (offset)
	int IIR_SRC_A0;     // (offset)
	int IIR_SRC_A1;     // (offset)
	int IIR_DEST_B0;    // (offset)
	int IIR_DEST_B1;    // (offset)
	int ACC_SRC_C0;     // (offset)
	int ACC_SRC_C1;     // (offset)
	int ACC_SRC_D0;     // (offset)
	int ACC_SRC_D1;     // (offset)
	int IIR_SRC_B1;     // (offset)
	int IIR_SRC_B0;     // (offset)
	int MIX_DEST_A0;    // (offset)
	int MIX_DEST_A1;    // (offset)
	int MIX_DEST_B0;    // (offset)
	int MIX_DEST_B1;    // (offset)
	int IN_COEF_L;      // (coef.)
	int IN_COEF_R;      // (coef.)
} REVERBInfo;

extern REVERBInfo reverb;

extern short g_spuLeftVol;
extern short g_spuRightVol;

extern struct Channel channelList[SPU_MAX_CHANNELS];

void SPU_Initialise();
void SPU_Destroy();
void SPU_ResetChannel(struct Channel* channel, uint8_t* data);

#endif