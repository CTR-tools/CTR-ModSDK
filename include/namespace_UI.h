struct UiElement2D
{
	short x;
	short y;
	short z;
	short scale;
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
	short vel[4];
	
	// 0x38 bytes
};

_Static_assert(sizeof(struct UiElement2D) == 0x8);
_Static_assert(sizeof(struct UiElement3D) == 0x38);