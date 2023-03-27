#include <common.h>

// This is not a mod,
// this tests addresses
// in ovr3.h to see if
// we make mistakes

struct x
{
	int a,b,c,d;
};

#define TEST16(x) { (int)x, 0,0,0 }

// by aligning everything to 16 bytes,
// it makes the binary easier to read
// in hex editors like ImHex

struct x y[] =
{
	TEST16(&OVR_233.CutsceneManipulatesAudio),
	TEST16(&OVR_233.whateverThisMeans[0]),
	TEST16(&OVR_233.pointerToWhateverThisMeans[0]),
	TEST16(&OVR_233.FXVolumeBackup),
	TEST16(&OVR_233.MusicVolumeBackup),
	TEST16(&OVR_233.VoiceVolumeBackup),
	TEST16(&OVR_233.isCutsceneOver),
	TEST16(&OVR_233.cutsceneState),
	TEST16(&OVR_233.PodiumInitUnk3),
	TEST16(&OVR_233.PodiumInitUnk2)
};