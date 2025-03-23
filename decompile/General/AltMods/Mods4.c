#ifdef USE_ONLINE
#include "OnlineCTR/names3d.c"
#include "OnlineCTR/vehThread.c"
#include "OnlineCTR/hsvColor.c"
#endif

#ifdef USE_PROFILER
#include "DebugMenu/MenuData.c"
#endif


#ifdef USE_FASTANIM
static int bi2 = 0;

// do NOT inline, byte budget
static int GetSignedBits2(unsigned int* vertData, int bits)
{
	int const b = bi2 >> 5;
	int const e = 32 - bits;
	int const s = e - (bi2 & 31);
	int const ret = s < 0 ?
		(vertData[b] << -s) | (vertData[b + 1] >> (s & 31)) :
		vertData[b] >> s;
	bi2 += bits;
	return (ret << e) >> e;
}

#define END_OF_LIST 0xFFFFFFFF
#define DRAW_CMD_FLAG_NEW_VERTEX (1 << 2)
void FastAnim_Decompress(struct ModelAnim* ma, u_int* pCmd)
{
#ifdef REBUILD_PC
	int addrArray[32];
#else
	int* addrArray = 0x1f800000;
#endif

	struct Mempack* ptrMempack = sdata->PtrMempack;
	
	printf("Run Animation: %s\n", ma->name);

	u_int pCmd_backup = pCmd;

	int numFrames = ma->numFrames;
	if ((numFrames & 0x8000) != 0)
	{
		// 0x8007 -> 4
		// animation interpolates between real frames,
		// part of compression to store less data

		numFrames &= 0x7fff;
		numFrames += 1;
		numFrames /= 2;
	}
	
	for(int i = 0; i < numFrames; i++)
	{
		if (DECOMP_MEMPACK_GetFreeBytes() < 16)
		{
			printf("Skip Animation: %s\n", ma->name);
			return;
		}
				
		char* firstFrame = MODELANIM_GETFRAME(ma);
		struct ModelFrame* mf = &firstFrame[ma->frameSize * i];

		// may be compressed vertData, or uncompresed
		char* vertData = MODELFRAME_GETVERT(mf);
		
		// reset
		pCmd = pCmd_backup;
		
		// pCmd[0] is number of commands
		pCmd++;

		// compression
		int x_alu = 0;
		int y_alu = 0;
		int z_alu = 0;
		bi2 = 0;
		
		int vertexIndex = 0;
		int stripLength = 0;
		
		// AlignUp
		unsigned int byte = 
			(unsigned int)ptrMempack->firstFreeByte;
		byte += 3;
		byte &= ~(3);
		ptrMempack->firstFreeByte = byte;
		
		// keep record
		addrArray[i] = ptrMempack->firstFreeByte;
		
		//loop commands until we hit the end marker 
		for (
				/* */;
				*pCmd != END_OF_LIST;
				
				pCmd++, stripLength++
			)
		{
			u_short flags = (*pCmd >> (8 * 3)) & 0xFF; //8 bits
			
			// TODO: adjust naming of NEW_VERTEX
			if ((flags & DRAW_CMD_FLAG_NEW_VERTEX) != 0)
				continue;
			
			//store temporal vertex packed uint
			u_int temporal = ma->ptrDeltaArray[vertexIndex];
			
			u_char XBits = (temporal >> 6) & 7;
			u_char YBits = (temporal >> 3) & 7;
			u_char ZBits = (temporal) & 7;

			u_char bx = (temporal >> 0x19) << 1;
			u_char by = (temporal << 7) >> 0x18;
			u_char bz = (temporal << 0xf) >> 0x18;

			// If reading a full 8 bits (7+1)
			// reset accumulator, this is an 
			// uncompressed 1-byte number
			if (XBits == 7) x_alu = 0;
			if (YBits == 7) y_alu = 0;
			if (ZBits == 7) z_alu = 0;

			// Read NumBits+1, where the first
			// extra (+1) bit, determines negative

			// convert XZY frame data
			int newX = GetSignedBits2(vertData, XBits + 1);
			int newY = GetSignedBits2(vertData, YBits + 1);
			int newZ = GetSignedBits2(vertData, ZBits + 1);

			//calculate decompressed coord value
			x_alu = (x_alu + (int)newX + bx);
			y_alu = (y_alu + (int)newY + by);
			z_alu = (z_alu + (int)newZ + bz);

			//store values to stack index, axis swap is important
			char* WRITE_PTR = ptrMempack->firstFreeByte;
			
			WRITE_PTR[0] = x_alu;
			WRITE_PTR[1] = z_alu;
			WRITE_PTR[2] = y_alu;
			
			ptrMempack->firstFreeByte = &WRITE_PTR[3];
			
			if (DECOMP_MEMPACK_GetFreeBytes() < 16)
			{
				printf("Skip Animation: %s\n", ma->name);
				return;
			}
			
			vertexIndex++;
		}
	}
	
	// if all frames are finished in this animation,
	// remove ptrDeltaArray to signify as decompressed,
	ma->ptrDeltaArray = 0;
	
	for(int i = 0; i < (ma->numFrames&0x7fff); i++)
	{	
		char* firstFrame = MODELANIM_GETFRAME(ma);
		struct ModelFrame* mf = &firstFrame[ma->frameSize * i];
		
		mf->vertexOffset = (unsigned int)addrArray[i] - (unsigned int)mf;
	}
}
#endif