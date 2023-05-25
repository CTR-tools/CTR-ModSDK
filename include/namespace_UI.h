struct UiElement2D
{
	short x;
	short y;
};

struct UiElement3D
{
	// 0x0
	short rot[4];
	
	// 0x8
	MATRIX m;
	
	// 0x28
	short lightDir[4];
	
	// 0x30
	// used in 8004c914
	short rot2[4];
	
	// 0x38 bytes
};

_Static_assert(sizeof(struct UiElement2D) == 4);