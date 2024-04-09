#ifndef LIBSPU_H
#define LIBSPU_H

/* ----------------------------------------------------------------
 *	CONSTANT 
 * ---------------------------------------------------------------- */

#define SPU_SUCCESS	0
#define SPU_INVALID_ARGS (-3)
#define SPU_DIAG	(-2)
#define SPU_CHECK	(-1)
#define SPU_OFF		0
#define SPU_ON		1
#define SPU_CLEAR	2
#define SPU_RESET	3
#define SPU_DONT_CARE	4
#define SPU_ALL		0
#define SPU_CDONLY	5
#define SPU_VOICEONLY	6
#define SPU_CONT	7
#define SPU_BIT		8
#define SPU_NULL	0
/* Macros below will be obsoleted. */
#define SpuDiag		SPU_DIAG
#define SpuCheck	SPU_CHECK
#define SpuOff		SPU_OFF
#define SpuOn		SPU_ON
#define SpuClear	SPU_CLEAR
#define SpuReset	SPU_RESET
#define SpuDontCare	SPU_DONT_CARE
#define SpuALL		SPU_ALL
#define SpuCDOnly	SPU_CDONLY
#define SpuVoiceOnly	SPU_VOICEONLY
#define SpuCont		SPU_CONT
#define SpuNull		SPU_NULL

#define SPU_OFF_ENV_ON	2
#define SPU_ON_ENV_OFF	3
/* Macros below will be obsoleted. */
#define SpuOffEnvOn	SPU_OFF_ENV_ON
#define SpuOnEnvOff	SPU_ON_ENV_OFF

#define SPU_ERROR	(-1)
/* Macros below will be obsoleted. */
#define SpuError	SPU_ERROR

#define SPU_TRANSFER_BY_DMA 0L
#define SPU_TRANSFER_BY_IO 1L
/* Macros below will be obsoleted. */
#define SpuTransferByDMA SPU_TRANSFER_BY_DMA
#define SpuTransferByIO  SPU_TRANSFER_BY_IO
#define SpuTransByDMA SpuTransferByDMA
#define SpuTransByIO SpuTransferByIO

#define SPU_TRANSFER_WAIT 1
#define SPU_TRANSFER_PEEK 0
#define SPU_TRANSFER_GLANCE SPU_TRANSFER_PEEK

/*
 * Voice designate
 */

#ifndef __SPU_VOICE
#define __SPU_VOICE

#define SPU_00CH (0x1L<< 0)
#define SPU_01CH (0x1L<< 1)
#define SPU_02CH (0x1L<< 2)
#define SPU_03CH (0x1L<< 3)
#define SPU_04CH (0x1L<< 4)
#define SPU_05CH (0x1L<< 5)
#define SPU_06CH (0x1L<< 6)
#define SPU_07CH (0x1L<< 7)
#define SPU_08CH (0x1L<< 8)
#define SPU_09CH (0x1L<< 9)
#define SPU_10CH (0x1L<<10)
#define SPU_11CH (0x1L<<11)
#define SPU_12CH (0x1L<<12)
#define SPU_13CH (0x1L<<13)
#define SPU_14CH (0x1L<<14)
#define SPU_15CH (0x1L<<15)
#define SPU_16CH (0x1L<<16)
#define SPU_17CH (0x1L<<17)
#define SPU_18CH (0x1L<<18)
#define SPU_19CH (0x1L<<19)

#define SPU_20CH (0x1L<<20)
#define SPU_21CH (0x1L<<21)
#define SPU_22CH (0x1L<<22)
#define SPU_23CH (0x1L<<23)

#define SPU_0CH SPU_00CH
#define SPU_1CH SPU_01CH
#define SPU_2CH SPU_02CH
#define SPU_3CH SPU_03CH
#define SPU_4CH SPU_04CH
#define SPU_5CH SPU_05CH
#define SPU_6CH SPU_06CH
#define SPU_7CH SPU_07CH
#define SPU_8CH SPU_08CH
#define SPU_9CH SPU_09CH

#define SPU_ALLCH (SPU_00CH | SPU_01CH | SPU_02CH | SPU_03CH | SPU_04CH | \
		   SPU_05CH | SPU_06CH | SPU_07CH | SPU_08CH | SPU_09CH | \
		   SPU_10CH | SPU_11CH | SPU_12CH | SPU_13CH | SPU_14CH | \
		   SPU_15CH | SPU_16CH | SPU_17CH | SPU_18CH | SPU_19CH | \
		   SPU_20CH | SPU_21CH | SPU_22CH | SPU_23CH)

#define SPU_KEYCH(x) (0x1L<<(x))
#define SPU_VOICECH(x) SPU_KEYCH(x)

#endif /* __SPU_VOICE */

/* for Voice setting */

#define	SPU_VOICE_VOLL		(0x01 <<  0) /* volume (left) */
#define	SPU_VOICE_VOLR		(0x01 <<  1) /* volume (right) */
#define	SPU_VOICE_VOLMODEL	(0x01 <<  2) /* volume mode (left) */
#define	SPU_VOICE_VOLMODER	(0x01 <<  3) /* volume mode (right) */
#define	SPU_VOICE_PITCH		(0x01 <<  4) /* tone (pitch setting) */
#define	SPU_VOICE_NOTE		(0x01 <<  5) /* tone (note setting)  */
#define	SPU_VOICE_SAMPLE_NOTE	(0x01 <<  6) /* waveform data sample note */
#define	SPU_VOICE_WDSA		(0x01 <<  7) /* waveform data start address */
#define	SPU_VOICE_ADSR_AMODE	(0x01 <<  8) /* ADSR Attack rate mode */
#define	SPU_VOICE_ADSR_SMODE	(0x01 <<  9) /* ADSR Sustain rate mode */
#define	SPU_VOICE_ADSR_RMODE	(0x01 << 10) /* ADSR Release rate mode */
#define	SPU_VOICE_ADSR_AR	(0x01 << 11) /* ADSR Attack rate         */
#define	SPU_VOICE_ADSR_DR	(0x01 << 12) /* ADSR Decay rate          */
#define	SPU_VOICE_ADSR_SR	(0x01 << 13) /* ADSR Sustain rate        */
#define	SPU_VOICE_ADSR_RR	(0x01 << 14) /* ADSR Release rate        */
#define	SPU_VOICE_ADSR_SL	(0x01 << 15) /* ADSR Sustain level       */
#define	SPU_VOICE_LSAX		(0x01 << 16) /* start address for loop */
#define	SPU_VOICE_ADSR_ADSR1	(0x01 << 17) /* ADSR adsr1 for `VagAtr'  */
#define	SPU_VOICE_ADSR_ADSR2	(0x01 << 18) /* ADSR adsr2 for `VagAtr'  */

#define	SPU_VOICE_DIRECT16	0
#define	SPU_VOICE_LINEARIncN	1
#define	SPU_VOICE_LINEARIncR	2
#define	SPU_VOICE_LINEARDecN	3
#define	SPU_VOICE_LINEARDecR	4
#define	SPU_VOICE_EXPIncN	5
#define	SPU_VOICE_EXPIncR	6
#define	SPU_VOICE_EXPDec	7
#define	SPU_VOICE_EXPDecN	SPU_VOICE_EXPDec
#define	SPU_VOICE_EXPDecR	SPU_VOICE_EXPDec

#define	SPU_DECODED_FIRSTHALF	0
#define	SPU_DECODED_SECONDHALF	1
#define	SPU_DECODE_FIRSTHALF	SPU_DECODED_FIRSTHALF
#define	SPU_DECODE_SECONDHALF	SPU_DECODED_SECONDHALF


#define	SPU_COMMON_MVOLL		(0x01 <<  0) /* master volume (left) */
#define	SPU_COMMON_MVOLR		(0x01 <<  1) /* master volume (right) */
#define	SPU_COMMON_MVOLMODEL		(0x01 <<  2) /* master volume mode (left) */
#define	SPU_COMMON_MVOLMODER		(0x01 <<  3) /* master volume mode (right) */
#define	SPU_COMMON_RVOLL		(0x01 <<  4) /* reverb volume (left) */
#define	SPU_COMMON_RVOLR		(0x01 <<  5) /* reverb volume (right) */
#define	SPU_COMMON_CDVOLL		(0x01 <<  6) /* CD input volume (left) */
#define	SPU_COMMON_CDVOLR		(0x01 <<  7) /* CD input volume (right) */
#define	SPU_COMMON_CDREV		(0x01 <<  8) /* CD input reverb on/off */
#define	SPU_COMMON_CDMIX		(0x01 <<  9) /* CD input on/off */
#define	SPU_COMMON_EXTVOLL		(0x01 << 10) /* external digital input volume (left) */
#define	SPU_COMMON_EXTVOLR		(0x01 << 11) /* external digital input volume (right) */
#define	SPU_COMMON_EXTREV		(0x01 << 12) /* external digital input reverb on/off */
#define	SPU_COMMON_EXTMIX		(0x01 << 13) /* external digital input on/off */

/* for Reverb setting */

#define	SPU_REV_MODE		(0x01 <<  0) /* mode setting */
#define	SPU_REV_DEPTHL		(0x01 <<  1) /* reverb depth (left) */
#define	SPU_REV_DEPTHR		(0x01 <<  2) /* reverb depth (right) */
#define	SPU_REV_DELAYTIME	(0x01 <<  3) /* Delay Time  (ECHO, DELAY only) */
#define	SPU_REV_FEEDBACK	(0x01 <<  4) /* Feedback    (ECHO only) */

#define SPU_REV_MODE_CHECK	(-1)
#define SPU_REV_MODE_OFF	0
#define SPU_REV_MODE_ROOM	1
#define SPU_REV_MODE_STUDIO_A	2
#define SPU_REV_MODE_STUDIO_B	3
#define SPU_REV_MODE_STUDIO_C	4
#define SPU_REV_MODE_HALL	5
#define SPU_REV_MODE_SPACE	6
#define SPU_REV_MODE_ECHO	7
#define SPU_REV_MODE_DELAY	8
#define SPU_REV_MODE_PIPE	9
#define SPU_REV_MODE_MAX	10

#define SPU_REV_MODE_CLEAR_WA	0x100

/* ----------------------------------------------------------------
 *	Event flushing
 * ---------------------------------------------------------------- */

#define SPU_EVENT_KEY      (0x01 << 0)
#define SPU_EVENT_PITCHLFO (0x01 << 1)
#define SPU_EVENT_NOISE    (0x01 << 2)
#define SPU_EVENT_REVERB   (0x01 << 3)

#define SPU_EVENT_ALL 0

/* ----------------------------------------------------------------
 *	Structure
 * ---------------------------------------------------------------- */

typedef struct {
    short left;	       /* Lch */
    short right;       /* Rch */
} SpuVolume;

typedef struct {
    unsigned int	voice;		/* set voice:
                            SpuSetVoiceAttr: each voice is a bit array
                            SpuGetVoiceAttr: voice is a bit value */
    unsigned int	mask;		/* settings attribute bit (invalid with Get) */
    SpuVolume		volume;		/* volume                         */
    SpuVolume		volmode;	/* volume mode                    */
    SpuVolume		volumex;	/* current volume (invalid with Set) */
    unsigned short	pitch;		/* tone (pitch setting) */
    unsigned short	note;		/* tone (note setting) */
    unsigned short	sample_note;	/* tone (note setting) */
    short		envx;		/* current envelope value (invalid with Set) */
    unsigned int	addr;		/* waveform data start address */
    unsigned int	loop_addr;	/* loop start address */
    int		a_mode;		/* Attack rate mode			*/
    int		s_mode;		/* Sustain rate mode			*/
    int		r_mode;		/* Release rate mode			*/
    unsigned short	ar;		/* Attack rate				*/
    unsigned short	dr;		/* Decay rate				*/
    unsigned short	sr;		/* Sustain rate				*/
    unsigned short	rr;		/* Release rate				*/
    unsigned short	sl;		/* Sustain level			*/
    unsigned short	adsr1;		/* adsr1 for `VagAtr' */
    unsigned short	adsr2;		/* adsr2 for `VagAtr' */
} SpuVoiceAttr;

typedef struct {
    short	voiceNum;		/* voice number */
    short	pad;			/* padding */
    SpuVoiceAttr	attr;		/* voice attribute */
} SpuLVoiceAttr;

typedef struct {
    unsigned int	mask;	  /* settings mask */
    
    int		mode;	  /* reverb mode */
    SpuVolume		depth;	  /* reverb depth */
    int                delay;	  /* Delay Time  (ECHO, DELAY only)   */
    int                feedback; /* Feedback    (ECHO only)          */
} SpuReverbAttr;

#define SPU_DECODEDDATA_SIZE 0x200
#define SPU_DECODEDATA_SIZE SPU_DECODEDDATA_SIZE
typedef struct {
    short cd_left  [SPU_DECODEDDATA_SIZE];
    short cd_right [SPU_DECODEDDATA_SIZE];
    short voice1   [SPU_DECODEDDATA_SIZE];
    short voice3   [SPU_DECODEDDATA_SIZE];
} SpuDecodedData;
typedef SpuDecodedData SpuDecodeData;

typedef struct {
    SpuVolume	volume;		  /* volume       */
    int	reverb;		  /* reverb on/off */
    int	mix;		  /* mixing on/off */
} SpuExtAttr;

typedef struct {
    unsigned int	mask;	  /* settings mask */
    
    SpuVolume		mvol;	  /* master volume */
    SpuVolume		mvolmode; /* master volume mode */
    SpuVolume		mvolx;	  /* current master volume */
    SpuExtAttr		cd;	  /* CD input attributes */
    SpuExtAttr		ext;	  /* external digital input attributes */
} SpuCommonAttr;

#ifndef __SPU_IRQCALLBACK_PROC
#define __SPU_IRQCALLBACK_PROC
typedef void (*SpuIRQCallbackProc)(void);
#endif /* __SPU_IRQCALLBACK_PROC */
#ifndef __SPU_TRANSFERCALLBACK_PROC
#define __SPU_TRANSFERCALLBACK_PROC
typedef void (*SpuTransferCallbackProc)(void);
#endif /* __SPU_TRANSFERCALLBACK_PROC */

/* ----------------------------------------------------------------
 *	for SPU Malloc (used in SpuInitMalloc())
 * ---------------------------------------------------------------- */

#define SPU_MALLOC_RECSIZ 8

/* ----------------------------------------------------------------
 *	User specifiable global environment
 * ---------------------------------------------------------------- */

typedef struct {
    unsigned int mask;
    unsigned int queueing;
} SpuEnv;

#define SPU_ENV_EVENT_QUEUEING			(0x01 << 0)

/* ----------------------------------------------------------------
 *	prototype declaration
 * ---------------------------------------------------------------- */

#if defined(_LANGUAGE_C_PLUS_PLUS) || defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif
extern void SpuInit (void);
extern void SpuInitHot (void);
extern void SpuStart (void);
extern void SpuQuit (void);
extern int SpuSetMute (int on_off);
extern int SpuGetMute (void);
extern void SpuSetEnv (SpuEnv *env);

extern int SpuSetNoiseClock (int n_clock);
extern int SpuGetNoiseClock (void);
extern unsigned int SpuSetNoiseVoice (int on_off, unsigned int voice_bit);
extern unsigned int SpuGetNoiseVoice (void);

extern int SpuSetReverb (int on_off);
extern int SpuGetReverb (void);
extern int SpuSetReverbModeParam (SpuReverbAttr *attr);
extern void SpuGetReverbModeParam (SpuReverbAttr *attr);
extern int SpuSetReverbDepth (SpuReverbAttr *attr);
extern int SpuReserveReverbWorkArea (int on_off);
extern int SpuIsReverbWorkAreaReserved (int on_off);
extern unsigned int SpuSetReverbVoice (int on_off, unsigned int voice_bit);
extern unsigned int SpuGetReverbVoice (void);
extern int SpuClearReverbWorkArea (int mode);

extern unsigned int SpuWrite (unsigned char *addr, unsigned int size);
extern unsigned int SpuWrite0 (unsigned int size);
extern unsigned int SpuRead (unsigned char *addr, unsigned int size);
extern int SpuSetTransferMode (int mode);
#define SpuSetTransMode(mode) SpuSetTransferMode((mode))
extern int SpuGetTransferMode (void);
#define SpuGetTransMode() SpuGetTransferMode()
extern unsigned int SpuSetTransferStartAddr (unsigned int addr);
#define SpuSetTransStartAddr(addr) SpuSetTransferStartAddr((addr))
extern unsigned int SpuGetTransferStartAddr (void);
#define SpuGetTransStartAddr() SpuGetTransferStartAddr()
extern unsigned int SpuWritePartly (unsigned char *addr, unsigned int size);

extern int SpuIsTransferCompleted (int flag);
extern SpuTransferCallbackProc SpuSetTransferCallback (SpuTransferCallbackProc func);
extern int SpuReadDecodedData (SpuDecodedData *d_data, int flag);
#define SpuReadDecodeData(d_data,flag) SpuReadDecodedData((d_data), (flag))

extern int SpuSetIRQ (int on_off);
extern int SpuGetIRQ (void);
extern unsigned int SpuSetIRQAddr (unsigned int);
extern unsigned int SpuGetIRQAddr (void);
extern SpuIRQCallbackProc SpuSetIRQCallback (SpuIRQCallbackProc);

extern void SpuSetVoiceAttr (SpuVoiceAttr *arg);
extern void SpuGetVoiceAttr (SpuVoiceAttr *arg);
extern void SpuSetKey (int on_off, unsigned int voice_bit);
extern void SpuSetKeyOnWithAttr (SpuVoiceAttr *attr);
extern int SpuGetKeyStatus (unsigned int voice_bit);
extern void SpuGetAllKeysStatus (char *status);
extern unsigned int SpuFlush (unsigned int ev);

extern unsigned int SpuSetPitchLFOVoice (int on_off, unsigned int voice_bit);
extern unsigned int SpuGetPitchLFOVoice (void);

extern void SpuSetCommonAttr (SpuCommonAttr *attr);
extern void SpuGetCommonAttr (SpuCommonAttr *attr);

extern int SpuInitMalloc (int num, char *top);
extern int SpuMalloc (int size);
extern int SpuMallocWithStartAddr (unsigned int addr, int size);
extern void SpuFree (unsigned int addr);

extern int SpuRGetAllKeysStatus (int min_, int max_, char *status);
extern int SpuRSetVoiceAttr (int min_, int max_, SpuVoiceAttr *arg);

extern void SpuNSetVoiceAttr (int vNum, SpuVoiceAttr *arg);
extern void SpuNGetVoiceAttr (int vNum, SpuVoiceAttr *arg);

extern void SpuLSetVoiceAttr (int num, SpuLVoiceAttr *argList);

extern void SpuSetVoiceVolume (int vNum, short volL, short volR);
extern void SpuSetVoiceVolumeAttr (int vNum, short volL, short volR,
				   short volModeL, short volModeR);
extern void SpuSetVoicePitch (int vNum, unsigned short pitch);
extern void SpuSetVoiceNote (int vNum, unsigned short note);
extern void SpuSetVoiceSampleNote (int vNum, unsigned short sampleNote);
extern void SpuSetVoiceStartAddr (int vNum, unsigned int startAddr);
extern void SpuSetVoiceLoopStartAddr (int vNum, unsigned int lsa);
extern void SpuSetVoiceAR (int vNum, unsigned short AR);
extern void SpuSetVoiceDR (int vNum, unsigned short DR);
extern void SpuSetVoiceSR (int vNum, unsigned short SR);
extern void SpuSetVoiceRR (int vNum, unsigned short RR);
extern void SpuSetVoiceSL (int vNum, unsigned short SL);
extern void SpuSetVoiceARAttr (int vNum, unsigned short AR, int ARmode);
extern void SpuSetVoiceSRAttr (int vNum, unsigned short SR, int SRmode);
extern void SpuSetVoiceRRAttr (int vNum, unsigned short RR, int RRmode);
extern void SpuSetVoiceADSR (int vNum, unsigned short AR, unsigned short DR,
			     unsigned short SR, unsigned short RR,
			     unsigned short SL);
extern void SpuSetVoiceADSRAttr (int vNum,
				 unsigned short AR, unsigned short DR,
				 unsigned short SR, unsigned short RR,
				 unsigned short SL,
    int ARmode, int SRmode, int RRmode);

extern void SpuGetVoiceVolume (int vNum, short *volL, short *volR);
extern void SpuGetVoiceVolumeAttr (int vNum, short *volL, short *volR,
				   short *volModeL, short *volModeR);
extern void SpuGetVoiceVolumeX (int vNum, short *volXL, short *volXR);
extern void SpuGetVoicePitch (int vNum, unsigned short *pitch);
extern void SpuGetVoiceNote (int vNum, unsigned short *note);
extern void SpuGetVoiceSampleNote (int vNum, unsigned short *sampleNote);
extern void SpuGetVoiceEnvelope (int vNum, short *envx);
extern void SpuGetVoiceStartAddr (int vNum, unsigned int *startAddr);
extern void SpuGetVoiceLoopStartAddr (int vNum, unsigned int *loopStartAddr);
extern void SpuGetVoiceAR (int vNum, unsigned short *AR);
extern void SpuGetVoiceDR (int vNum, unsigned short *DR);
extern void SpuGetVoiceSR (int vNum, unsigned short *SR);
extern void SpuGetVoiceRR (int vNum, unsigned short *RR);
extern void SpuGetVoiceSL (int vNum, unsigned short *SL);
extern void SpuGetVoiceARAttr (int vNum, unsigned short *AR, int *ARmode);
extern void SpuGetVoiceSRAttr (int vNum, unsigned short *SR, int *SRmode);
extern void SpuGetVoiceRRAttr (int vNum, unsigned short *RR, int *RRmode);
extern void SpuGetVoiceADSR (int vNum,
			     unsigned short *AR, unsigned short *DR,
			     unsigned short *SR, unsigned short *RR,
			     unsigned short *SL);
extern void SpuGetVoiceADSRAttr (int vNum,
				 unsigned short *AR, unsigned short *DR,
				 unsigned short *SR, unsigned short *RR,
				 unsigned short *SL,
                 int *ARmode, int *SRmode, int *RRmode);
extern void SpuGetVoiceEnvelopeAttr (int vNum, int *keyStat, short *envx );

extern void SpuSetCommonMasterVolume (short mvol_left, short mvol_right);
extern void SpuSetCommonMasterVolumeAttr (short mvol_left, short mvol_right,
					  short mvolmode_left,
					  short mvolmode_right);
extern void SpuSetCommonCDMix (int cd_mix);
extern void SpuSetCommonCDVolume (short cd_left, short cd_right);
extern void SpuSetCommonCDReverb (int cd_reverb);

extern void SpuGetCommonMasterVolume (short *mvol_left, short *mvol_right);
extern void SpuGetCommonMasterVolumeX (short *mvolx_left, short *mvolx_right);
extern void SpuGetCommonMasterVolumeAttr (short *mvol_left, short *mvol_right,
					  short *mvolmode_left,
					  short *mvolmode_right);
extern void SpuGetCommonCDMix (int *cd_mix);
extern void SpuGetCommonCDVolume (short *cd_left, short *cd_right);
extern void SpuGetCommonCDReverb (int *cd_reverb);

extern int SpuSetReverbModeType (int mode);
extern void SpuSetReverbModeDepth (short depth_left, short depth_right);
extern void SpuSetReverbModeDelayTime (int delay);
extern void SpuSetReverbModeFeedback (int feedback);
extern void SpuGetReverbModeType (int*mode);
extern void SpuGetReverbModeDepth (short *depth_left, short *depth_right);
extern void SpuGetReverbModeDelayTime (int*delay);
extern void SpuGetReverbModeFeedback (int*feedback);
extern void SpuSetESA(int revAddr );
#if defined(_LANGUAGE_C_PLUS_PLUS) || defined(__cplusplus) || defined(c_plusplus)
}
#endif

/* ---------------------------------------------------------------- */

#define SPU_ST_NOT_AVAILABLE 0
#define SPU_ST_ACCEPT  1

#define SPU_ST_ERROR (-1)
#define SPU_ST_INVALID_ARGUMENT (-2)
#define SPU_ST_WRONG_STATUS (-3)

#define SPU_ST_STOP     2
#define SPU_ST_IDLE     3
#define SPU_ST_PREPARE  4
#define SPU_ST_START    5
#define SPU_ST_PLAY     6
#define SPU_ST_TRANSFER 7
#define SPU_ST_FINAL    8


/* VAG's header size */
#define SPU_ST_VAG_HEADER_SIZE 0x30

typedef struct {
    char status;		/* stream status */
    char pad1;			/* padding */
    char pad2;			/* padding */
    char pad3;			/* padding */
    int last_size;		/* the size of last transferring
				   (last_size <= (size / 2)) */
    unsigned int buf_addr;	/* The start address of stream buffer */
    unsigned int data_addr;	/* The start address of SPU streaming
				   data in main memory */
} SpuStVoiceAttr;

typedef struct {
    int size;			/* The size of stream buffer */
    int low_priority;		/* transfer priority */
    SpuStVoiceAttr voice [24];
} SpuStEnv;

#ifndef __SPU_ST_TRANSFERCALLBACK_PROC
#define __SPU_ST_TRANSFERCALLBACK_PROC
typedef void (*SpuStCallbackProc)(unsigned int, int);
#endif /* __SPU_TRANSFERCALLBACK_PROC */

#if defined(_LANGUAGE_C_PLUS_PLUS) || defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif
extern SpuStEnv *SpuStInit (int);
extern int SpuStQuit (void);
extern int SpuStGetStatus (void);
extern unsigned int SpuStGetVoiceStatus (void);
extern int SpuStTransfer (int flag, unsigned int voice_bit);
extern SpuStCallbackProc SpuStSetPreparationFinishedCallback (SpuStCallbackProc func);
extern SpuStCallbackProc SpuStSetTransferFinishedCallback (SpuStCallbackProc func);
extern SpuStCallbackProc SpuStSetStreamFinishedCallback (SpuStCallbackProc func);
#if defined(_LANGUAGE_C_PLUS_PLUS) || defined(__cplusplus) || defined(c_plusplus)
}
#endif

/* ----------------------------------------------------------------
 *	End on File
 * ---------------------------------------------------------------- */
#endif /* _LIBSPU_H_ */
/* DON'T ADD STUFF AFTER THIS */
