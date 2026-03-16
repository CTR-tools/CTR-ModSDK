
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
void FastAnim_Decompress(struct Model* m, int j, int k)
{
#ifdef REBUILD_PC
	int addrArray[128];
#else
	int* addrArray = 0x1f800000;
#endif
	
	struct ModelHeader* h = &m->ptrHeadersArray[j];
	struct ModelAnim* ma = h->ptrAnimations[k];
	char* firstFrame = MODELANIM_GETFRAME(ma);
	printf("%s: %s\n", __FUNCTION__, ma->name);
	u_int* pCmd = h->ptrCommandList;
	u_int pCmd_backup = pCmd;

	// TODO: only use mempack[0],
	// beware of adventure mode
	struct Mempack* ptrMempack = &sdata->mempack[0];

	// unusual macro use, but it works,
	// 0=30fps, 1=60fps, 2=120fps, etc
	int numGenerateLerps = FPS_RIGHTSHIFT(0);
	
	int numFrames = ma->numFrames;
	if ((numFrames & 0x8000) != 0)
	{
		#ifndef USE_RAMEX
		
		return;
		
		#else
		
		// 0x8007 -> 4
		// animation interpolates between real frames,
		// part of compression to store less data

		numFrames &= 0x7fff;
		numFrames += 1;
		numFrames /= 2;
		
		// "real" frame
		// save 0x8007 -> 4
		ma->numFrames = numFrames;
		
		// Lerp from 4 -> 7
		numGenerateLerps++;
		
		#endif
	}
	
	for(int i = 0; i < numFrames; i++)
	{
		if (DECOMP_MEMPACK_GetFreeBytes() < 16)
		{
			printf("Skip Animation: %s\n", ma->name);
			return;
		}

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
	
	for(int i = 0; i < numFrames; i++)
	{	
		struct ModelFrame* mf = &firstFrame[ma->frameSize * i];
		
		mf->vertexOffset = (unsigned int)addrArray[i] - (unsigned int)mf;
	}
	
	#ifdef USE_RAMEX
	for(int i = 0; i < numGenerateLerps; i++)
	{
		void FastAnim_GenerateLerp(struct Model* m, int j, int k);
		FastAnim_GenerateLerp(m, j, k);
	}
	#endif
}


#ifdef USE_RAMEX
void FastAnim_GenerateLerp(struct Model* m, int j, int k)
{
#ifdef REBUILD_PC
	int addrArray[128];
#else
	int* addrArray = 0x1f800000;
#endif

	struct ModelHeader* h = &m->ptrHeadersArray[j];
	struct ModelAnim* ma = h->ptrAnimations[k];
	printf("%s: %s\n", __FUNCTION__, ma->name);
	u_int* pCmd = h->ptrCommandList;
	u_int pCmd_backup = pCmd;

	// TODO: only use mempack[0],
	// beware of adventure mode
	struct Mempack* ptrMempack = &sdata->mempack[0];
	
	// AlignUp
	unsigned int byte = 
		(unsigned int)ptrMempack->firstFreeByte;
	byte += 3;
	byte &= ~(3);
	ptrMempack->firstFreeByte = byte;
	
	// 4 -> 7
	int numFramesPreLerp = ma->numFrames;
	ma->numFrames = (ma->numFrames * 2) - 1;
	int numFramesPostLerp = ma->numFrames;
	
	// allocate "new" animation...
	// dont check for allocation error this time,
	// because this function only runs with RAMEX
	struct ModelAnim* newMA = byte;
	byte += sizeof(struct ModelAnim) + sizeof(struct ModelFrame)*numFramesPostLerp;
	ptrMempack->firstFreeByte = byte;
	
	// overwrite header to new animation
	h->ptrAnimations[k] = newMA;
	newMA->ptrDeltaArray = 0;
	newMA->numFrames = numFramesPostLerp;
	newMA->frameSize = sizeof(struct ModelFrame);
	
	char* firstFrame = MODELANIM_GETFRAME(ma);
	char* newFirstFrame = MODELANIM_GETFRAME(newMA);
	
	// ALL non-last FRAMES: 3->6
	for(int i = 0; i < (numFramesPreLerp-1); i++)
	{
		// old frame
		{
			// COPY old -> new
			struct ModelFrame* mf = 
				&firstFrame[ma->frameSize * i];
				
			struct ModelFrame* newMF = 
				&newFirstFrame[newMA->frameSize * ((i*2)+0)];

			newMF->pos[0] = mf->pos[0];
			newMF->pos[1] = mf->pos[1];
			newMF->pos[2] = mf->pos[2];
		
			unsigned int realAddr = MODELFRAME_GETVERT(mf);
			unsigned int offset = realAddr - (unsigned int)newMF;
			newMF->vertexOffset = offset;
			
			printf("old %08x new %08x\n", 
				MODELFRAME_GETVERT(mf),
				MODELFRAME_GETVERT(newMF)
			);
		}
		
		// new frame
		{
			// TEMPORARY
			// COPY old -> new
			
			// === NOT DONE ===
			
			// Should be lerping between two frames
			struct ModelFrame* mf = 
				&firstFrame[ma->frameSize * i];
				
			struct ModelFrame* newMF = 
				&newFirstFrame[newMA->frameSize * ((i*2)+1)];
		
			newMF->pos[0] = mf->pos[0];
			newMF->pos[1] = mf->pos[1];
			newMF->pos[2] = mf->pos[2];
		
			unsigned int realAddr = MODELFRAME_GETVERT(mf);
			unsigned int offset = realAddr - (unsigned int)newMF;
			newMF->vertexOffset = offset;
		}
	}
	
	// LAST FRAME
	
	// 4th original frame [3]
	struct ModelFrame* mf = &firstFrame[ma->frameSize * (numFramesPreLerp-1)];
	
	// 7th new frame [6]
	struct ModelFrame* newMF = &newFirstFrame[newMA->frameSize * (numFramesPostLerp-1)];
	
	newMF->pos[0] = mf->pos[0];
	newMF->pos[1] = mf->pos[1];
	newMF->pos[2] = mf->pos[2];
	
	unsigned int realAddr = MODELFRAME_GETVERT(mf);
	unsigned int offset = realAddr - (unsigned int)newMF;
	newMF->vertexOffset = offset;
}
#endif