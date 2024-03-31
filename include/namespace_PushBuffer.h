// named after TILE primitive used in DrawEnv/DispEnv,
// attempting to flip that in my MirrorMode mod killed the screens
struct PushBuffer
{
	// 0x0
	short pos[3];

	// 0x6
	short rot[3];

	// 0xc
	// set at bottom of Camera_UpdateFrustum,
	// used in 226-229 overlays for LEV
	char data6[6];

	// 0x12
	// 0 for black,
	// 0x1000 for normal light
	// 0x2000 for white
	short fadeFromBlack_currentValue;

	// 0x14
	short fadeFromBlack_desiredResult;

	//0x16 controls speed of fade in effect
	//if negative then it's fading to black.
	//in this case 0x12 should be positive and 0x14 should be 0
	short fade_step;

	// 0x18
	// this value is passed to SetGeomScreen,
	// used for perspective projection math
	// 256 in 1P, 128 in 4P
	int distanceToScreen_PREV;

	// 0x1c
	// position and dimensions
	RECT rect;

	// 0x24
	short aspectX;

	// 0x26
	short aspectY;

	// 0x28
	MATRIX matrix_ViewProj;

	// 0x48 (Warppad Lightning during Driver Warp effect)
	MATRIX matrix_CameraTranspose;

	// 0x68 (GTE_AudioLR_Inst, Vector_SpecLightSpin3D)
	MATRIX matrix_Camera;

	// 0x88 (built in PushBuffer_Init, never used)
	MATRIX matrix_Proj;

	// Frustum Planes
	// given to FUN_80042e50
	// 0xA8 - plane1
	// 0xB0 - plane2
	// 0xB8 - plane3
	// 0xC0 - plane4

	// 0xA8
	char frustumData[0x28];
	
	// 0xD0
	int RenderListJmpIndex[6];
	
	// 0xE8
	struct BoundingBox bbox;

	// 0xF4
	// u_long* is the type in the psn00b header
	u_long* ptrOT;

	// 0xF8 also OT,
	// only pixel LOD, what's the difference
	// between 0xF4 OT and 0xF8 OT?

	// 0xF8
	// all of filler2 is for pixelLOD only
	char filler2[0x10];

	// 0x108
	int cameraID;

	// 0x10c
	int distanceToScreen_CURR;

	// 0x110 - end of struct
};

_Static_assert(sizeof(struct PushBuffer) == 0x110);