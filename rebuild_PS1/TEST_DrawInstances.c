#include <common.h>

struct ModelHeader_Custom
{
	char name[16];
	int unk; // probably name is 20 bytes, idk

	// distance till next model is drawn
	short lodDistance;

	// 0 for 3D
	// 1 for 2D
	short renderMode;

	// X, Y, Z, padding
	short modelScale[4];

	unsigned int* ptrCmds;
	unsigned int* ptrVert;
	unsigned int* ptrTex;
	unsigned int* ptrColor;

	// leave these all zeros
	int unk3;
	int numAnim;
	int ptrAnim;
	int unk4;
};

// multiple headers usually means multiple LODs, but I want multiple headers for multiple models,
// that all share vertex data and command data, I am not sure if CTR ever intended this, so it
// might get messy. Also I change scale and color in the model header, not the instance, because instance
// color isn't used when I try by default, and the CTR engine fights me when I try to change instance scale

struct Model_GiveToInst
{
	char nameModel[16];
	short modelID;

	short numHeaders;
	unsigned int* ptrHeaders;

	// can be an array of headers
	struct ModelHeader_Custom h;
};

struct Model_Custom
{
	struct Model_GiveToInst mgti[4];

	// 4 bytes per command,
	// must end in 0xFFFFFFFF
	unsigned int cmd[0x16];

	// some data in
	// beginning for translation
	// each point is 3 ints
	unsigned char vert[0x58];

	// each pointer goes to 3 ints,
	// each holding VRAM coordinates,

	// if 6 pointers are all nullptr,
	// then it just uses colors
	unsigned int texPtrs[6];

	unsigned int colorsYellow[3];
	unsigned int colorsCyan[3];
};

struct Model_Custom mCheese =
{
	// four models, one for each player
	.mgti =
	{
		// team 1 - player 1
		//.[0] =
		{
			.nameModel = "team1-player1",

			// no label on this model
			.modelID = 0xFFFF,

			.numHeaders = 1,

			.ptrHeaders = (unsigned int*)(OFFSETOF(struct Model_GiveToInst, h) + sizeof(struct Model_GiveToInst) * 0),

			.h =
			{
				.name = "t1p1_low",
				.unk = 0,

				// render no matter how far away
				.lodDistance = 0xFFFF,

				.renderMode = 0,

				.modelScale = { 0x400, 0x600, 0x6D3, 0 },

				.ptrCmds = (unsigned int*)OFFSETOF(struct Model_Custom, cmd),
				.ptrVert = (unsigned int*)OFFSETOF(struct Model_Custom, vert),
				.ptrTex = (unsigned int*)OFFSETOF(struct Model_Custom, texPtrs),
				.ptrColor = (unsigned int*)OFFSETOF(struct Model_Custom, colorsYellow),
			},
		},
	},

	.cmd =
	{
		3,

		// side 1
		0x98570001,
		0x18570001,
		0x18570001,
		0x38570002,

		// side 2
		0x98570201,
		0x18570201,
		0x18570201,
		0x38570202,

		// side 3
		0x98570201,
		0x18570201,
		0x18570201,
		0x38570202,

		// side 4
		0x98570403,
		0x18570403,
		0x18570403,

		// top
		0x38570404,
		0x18570405,

		// bottom
		0x38570406,
		0x18570401,

		// end geometry
		0x38570402,
		0xFFFFFFFF,
	},

	.vert =
	{
		// offset from center of model
		0x81, 0xFF, 0x00, 0x00, // X
		0x81, 0xFF, 0x00, 0x00, // Z
		0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00,

		// 0x1c is the offset of the "vert"
		// data where the positions start
		0x1C, 0x00, 0x00, 0x00,

		// 3 bytes per point (x, y, z)

		// Z is forward, so to make arrow,
		// X needs to shrink on +Z side

		// XX, ZZ, YY
		0x00, 0x00, 0x00, // (000)
		0x80, 0xFF, 0x00, // (010)
		0xFF, 0x00, 0x00, // (100)
		0x80, 0xFF, 0x00, // (110)
		0x80, 0xFF, 0xFF, // (111)
		0xFF, 0x00, 0xFF, // (101)
		0x80, 0xFF, 0x00, // (110)
		0xFF, 0x00, 0x00, // (100)
		0x00, 0x00, 0xFF, // (001)
		0x80, 0xFF, 0xFF, // (011)
		0x00, 0x00, 0x00, // (000)
		0x80, 0xFF, 0x00, // (010)
		0x80, 0xFF, 0x00, // (110)
		0x80, 0xFF, 0x00, // (010)
		0x80, 0xFF, 0xFF, // (111)
		0x80, 0xFF, 0xFF, // (011)
		0xFF, 0x00, 0xFF, // (101)
		0x00, 0x00, 0xFF, // (001)
		0xFF, 0x00, 0x00, // (100)
		0x00, 0x00, 0x00, // (000)
	},

	//.texPtrs =
	//{
	//},

	// yellow
	.colorsYellow =
	{
		// bottom
		0x2244,

		// side
		0x4080,

		// top
		0x80FF
	},

	// cyan
	.colorsCyan =
	{
		// bottom
		0x442200,

		// side
		0x804000,

		// top
		0xFF8000
	},
};

int run = 0;

void RunEntryHook()
{
	if (run == 1) return;
	run = 1;

#define FIX_OFFSET(x) \
		x = (unsigned int*)((unsigned char*)&mCheese + (unsigned int)x)

	int i;

	for (i = 0; i < 4; i++)
	{
		// initialize models
		FIX_OFFSET(mCheese.mgti[i].ptrHeaders);
		FIX_OFFSET(mCheese.mgti[i].h.ptrCmds);
		FIX_OFFSET(mCheese.mgti[i].h.ptrVert);
		FIX_OFFSET(mCheese.mgti[i].h.ptrTex);
		FIX_OFFSET(mCheese.mgti[i].h.ptrColor);
	}
}


void TEST_DrawInstances(struct GameTracker* gGT)
{
	short posScreen1[4];
	short posWorld1[4];
	short posScreen2[4];
	short posWorld2[4];
	short posScreen3[4];
	short posWorld3[4];

	struct OTMem* otMem = &gGT->backBuffer->otMem;
	struct PrimMem* primMem = &gGT->backBuffer->primMem;
	RunEntryHook();

	for (
			struct Instance* curr = gGT->JitPools.instance.taken.first;
			curr != 0;
			curr = curr->next
		)
	{
		// temporary test
		//curr->model = &mCheese.mgti[0];

		for (int i = 0; i < gGT->numPlyrCurrGame; i++)
		{
			if ((curr->flags & 0x80) != 0) continue;

			struct InstDrawPerPlayer* idpp = INST_GETIDPP(curr);

			struct TileView* view = idpp[i].tileView;
			if (view == 0) continue;

			// reset, might be off by one frame and glitch in the top-left corner,
			// when leaving character selection back to main menu
			idpp[i].tileView = 0;

			// not this, this is identity matrix
#if 0
			MATRIX* mat1 = &view->matrix_ViewProj;
			*(int*)&mat1->m[0][0] = 0x1000;
			*(int*)&mat1->m[1][1] = 0x900; // -- temporary --
			*(int*)&mat1->m[2][2] = 0x1000;
#endif

			// copy from running CTR instance in no$psx
			MATRIX* mat2 = &curr->matrix;
			*(int*)&mat2->m[0][0] = 0xEED;
			*(int*)&mat2->m[0][2] = 0x5C2;
			*(int*)&mat2->m[1][1] = 0xF000;
			*(int*)&mat2->m[2][0] = 0x5C2;
			*(int*)&mat2->m[2][2] = 0xFFFFF113;
			mat2->t[0] = 0;
			mat2->t[1] = 0x28;
			mat2->t[2] = 0xC8;

			// how do I multiply mat1 and mat2 together?
			gte_SetRotMatrix(mat2);
			gte_SetTransMatrix(mat2);

			struct Model* m = curr->model;
			struct ModelHeader* mh = &m->headers[0];
			char* vertData = (char*)&mh->ptrFrameData[0] + mh->ptrFrameData->vertexOffset;

			// 3FF is background, 3FE is next depth slot
			void* ot = &view->ptrOT[0x3FE];

#if 1
			POLY_F3* p = primMem->curr;
			primMem->curr = p + 1;

			// set Poly_LineF3 len, code, and padding
			setPolyF3(p);

			// RGB
			setRGB0(p,
				data.ptrColor[PLAYER_BLUE + i][0],
				data.ptrColor[PLAYER_BLUE + i][0] >> 8,
				data.ptrColor[PLAYER_BLUE + i][0] >> 16
			);

			posWorld1[0] = ((mh->ptrFrameData->pos[0] + 0) * mh->scale[0]) >> 8;
			posWorld1[1] = ((mh->ptrFrameData->pos[1] + 0) * mh->scale[1]) >> 8;
			posWorld1[2] = ((mh->ptrFrameData->pos[2] - 0x200) * mh->scale[2]) >> 8;
			posWorld1[3] = 0;
			gte_ldv0(&posWorld1[0]);
			gte_rtps();
			gte_stsxy(&posScreen1[0]);

			posWorld2[0] = ((mh->ptrFrameData->pos[0] + 0x80) * mh->scale[0]) >> 8;
			posWorld2[1] = ((mh->ptrFrameData->pos[1] + 0xFF) * mh->scale[1]) >> 8;
			posWorld2[2] = ((mh->ptrFrameData->pos[2] - 0x200) * mh->scale[2]) >> 8;
			posWorld2[3] = 0;
			gte_ldv0(&posWorld2[0]);
			gte_rtps();
			gte_stsxy(&posScreen2[0]);

			posWorld3[0] = ((mh->ptrFrameData->pos[0] + 0xFF) * mh->scale[0]) >> 8;
			posWorld3[1] = ((mh->ptrFrameData->pos[1] +    0) * mh->scale[1]) >> 8;
			posWorld3[2] = ((mh->ptrFrameData->pos[2] - 0x200) * mh->scale[2]) >> 8;
			posWorld3[3] = 0;
			gte_ldv0(&posWorld3[0]);
			gte_rtps();
			gte_stsxy(&posScreen3[0]);

			// to be in viewport, coordinates must be
			// X: [0, 0x40]
			// Y: [0, 0xA0]
			setXY3(p,
				posScreen1[0], posScreen1[1],	// XY0
				posScreen2[0], posScreen2[1],	// XY1
				posScreen3[0], posScreen3[1]);	// XY2

			AddPrim(ot, p);



			// ============================

			continue;

			// ============================
#endif



			//helper type, kinda same as RGB
			//a 255 grid "compressed vertex" 0 = 0.0 and 255 = 1.0. 256 steps only.
			typedef struct CompVertex {
				u_char X;
				u_char Y;
				u_char Z;
			} CompVertex;

			//flag values and end of list
#define END_OF_LIST 0xFFFFFFFF
#define DRAW_CMD_FLAG_NEW_STRIP (1 << 7)
#define DRAW_CMD_FLAG_SWAP_VERTEX (1 << 6)
#define DRAW_CMD_FLAG_FLIP_NORMAL (1 << 5)
#define DRAW_CMD_FLAG_CULLING (1 << 4)
#define DRAW_CMD_FLAG_COLOR_SCRATCHPAD (1 << 3)
#define DRAW_CMD_FLAG_NEW_VERTEX (1 << 2)
//bits 0 and 1 assumed unused

//variables
//sequentially point to the next vertex, increases once NEW_VERTEX flag comes in
			int vertexIndex = 0;
			//current strip length
			int stripLength = 0;
			CompVertex* ptrVerts = vertData;
			u_int* pCmd = mh->ptrCommandList;

			//a "shifting window", here we update the vertices and read triangle once it's ready
			//you need same cache for both colors and texture layouts
			CompVertex tempCoords[4];

			//i believe this must be scratchpad, but it uses 4 bytes, this array is only 3 bytes (like array buffer for simplicity).
			//the idea is that it loads vertices to scratchpad and with proper sorting,
			//you can draw may trigles of the list with minimum additional loads
			//then once you don't need vertex data, you can overwrite same indices with new data
			CompVertex stack[256];

			//loop commands until we hit the end marker 
			while (*pCmd != END_OF_LIST)
			{
				//extract individual values from the command
				//refactor to a set of inline macros?
				u_short flags = (*pCmd >> (8 * 3)) & 0xFF; //8 bits
				u_short stackIndex = (*pCmd >> 16) & 0xFF; //8 bits
				u_short colorIndex = (*pCmd >> 9) & 0x7F; // 7 bits
				u_short texIndex = *pCmd & 0x1FF; //9 bits

				// if got a new vertex, load it
				if ((flags & DRAW_CMD_FLAG_NEW_VERTEX) != 0)
				{
					//copy from vertex buffer to stack index
					stack[stackIndex] = ptrVerts[vertexIndex];

					//and point to next vertex
					vertexIndex++;
				}

				//push current list back and insert value from stack
				//this code already have correct value on the stack, be aware of the order
				tempCoords[0] = tempCoords[1];
				tempCoords[1] = tempCoords[2];
				tempCoords[2] = tempCoords[3];
				tempCoords[3] = stack[stackIndex];

				//this is probably some tristrip optimization, so we can reuse vertex from the last triangle
				//and only spend 1 command
				if ((flags & DRAW_CMD_FLAG_SWAP_VERTEX) != 0)
				{
					tempCoords[1] = tempCoords[0];
				}

				//if got reset flag, reset tristrip vertex counter
				if ((flags & DRAW_CMD_FLAG_NEW_STRIP) != 0)
				{
					stripLength = 0;
				}

				//enough data to add prim
				if (stripLength >= 2)
				{
					//submit triangle vertices here

					/*
					here's the scaling formula
					but i had to flip Y first
					then scale XYZ by XZY, important
					then flip Z to -Y and Y to Z

					guess it's simpler in the actual game and i just do the negation twice
					(but could be mirrored otherwise, gotta test it again)

					//same as (pos * scale) >> 8 ?

					v.X = (short)((((float)(v.X + frame.posOffset.X) / 255.0f) * scale.X));
					v.Y = (short)(-(((float)(v.Y + frame.posOffset.Z) / 255.0f) * scale.Z));
					v.Z = (short)((((float)(v.Z + frame.posOffset.Y) / 255.0f) * scale.Y));

					//flip axis
					short zz = v.Z;
					v.Z = (short)-v.Y;
					v.Y = zz;

					then i sumbit vertices 1 2 3 from tempCoords (0 is unused)

					*/

					LINE_F3* p = primMem->curr;
					primMem->curr = p + 1;

					// set Poly_LineF3 len, code, and padding
					setLineF3(p);

					// RGB
					setRGB0(p,
						data.ptrColor[PLAYER_BLUE + i][0],
						data.ptrColor[PLAYER_BLUE + i][0] >> 8,
						data.ptrColor[PLAYER_BLUE + i][0] >> 16
					);

					posWorld1[0] = ((mh->ptrFrameData->pos[0] + tempCoords[1].X) * mh->scale[0]) >> 8;
					posWorld1[1] = ((mh->ptrFrameData->pos[1] + tempCoords[1].Y) * mh->scale[1]) >> 8;
					posWorld1[2] = ((mh->ptrFrameData->pos[2] + tempCoords[1].Z) * mh->scale[2]) >> 8;
					posWorld1[3] = 0;
					gte_ldv0(&posWorld1[0]);
					gte_rtps();
					gte_stsxy(&posScreen1[0]);

					posWorld2[0] = ((mh->ptrFrameData->pos[0] + tempCoords[2].X) * mh->scale[0]) >> 8;
					posWorld2[1] = ((mh->ptrFrameData->pos[1] + tempCoords[2].Y) * mh->scale[1]) >> 8;
					posWorld2[2] = ((mh->ptrFrameData->pos[2] + tempCoords[2].Z) * mh->scale[2]) >> 8;
					posWorld2[3] = 0;
					gte_ldv0(&posWorld2[0]);
					gte_rtps();
					gte_stsxy(&posScreen2[0]);

					posWorld3[0] = ((mh->ptrFrameData->pos[0] + tempCoords[3].X) * mh->scale[0]) >> 8;
					posWorld3[1] = ((mh->ptrFrameData->pos[1] + tempCoords[3].Y) * mh->scale[1]) >> 8;
					posWorld3[2] = ((mh->ptrFrameData->pos[2] + tempCoords[3].Z) * mh->scale[2]) >> 8;
					posWorld3[3] = 0;
					gte_ldv0(&posWorld3[0]);
					gte_rtps();
					gte_stsxy(&posScreen3[0]);

					// to be in viewport, coordinates must be
					// X: [0, 0x40]
					// Y: [0, 0xA0]
					setXY3(p,
						posScreen1[0], posScreen1[1],	// XY0
						posScreen2[0], posScreen2[1],	// XY1
						posScreen3[0], posScreen3[1]);	// XY2

					AddPrim(ot, p);

					int x = *(int*)&tempCoords[0];

					if ((flags & DRAW_CMD_FLAG_FLIP_NORMAL) != 0)
					{
						//swap 2 coords to flip the normal here or can have 2 separate sumbission branches
					}
				}

				//strip length increases
				stripLength++;

				//proceed to the next command
				pCmd++;
			}
		}
	}
}