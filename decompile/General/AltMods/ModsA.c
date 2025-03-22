
#ifdef USE_FASTANIM
static int bi = 0;

// do NOT inline, byte budget
int GetSignedBits(unsigned int* vertData, int bits)
{
	int const b = bi >> 5;
	int const e = 32 - bits;
	int const s = e - (bi & 31);
	int const ret = s < 0 ?
		(vertData[b] << -s) | (vertData[b + 1] >> (s & 31)) :
		vertData[b] >> s;
	bi += bits;
	return (ret << e) >> e;
}

#define END_OF_LIST 0xFFFFFFFF
void FastAnim_Decompress(struct ModelAnim* ma, u_int* pCmd)
{
	for(int i = 0; i < (ma->numFrames&0x7fff); i++)
	{
		char* firstFrame = MODELANIM_GETFRAME(ma);
		struct ModelFrame* mf = &firstFrame[ma->frameSize * i];
		
		// may be compressed vertData, or uncompresed
		char* vertData = MODELFRAME_GETVERT(mf);
		
		printf("%s: %d\n", ma->name, i);
		
		// pCmd[0] is number of commands
		pCmd++;

		// compression
		int x_alu = 0;
		int y_alu = 0;
		int z_alu = 0;
		bi = 0;
		
		int vertexIndex = 0;
		int stripLength = 0;
		
		//loop commands until we hit the end marker 
		for (
				/* */;
				*pCmd != END_OF_LIST;
				
				pCmd++, stripLength++
			)
		{
			//store temporal vertex packed uint
			u_int temporal = ma->ptrDeltaArray[vertexIndex];
			
			u_char XBits = (temporal >> 6) & 7;
			u_char YBits = (temporal >> 3) & 7;
			u_char ZBits = (temporal) & 7;
			
			int newX = GetSignedBits(vertData, XBits + 1);
		}
	}
}
#endif

#if 0
  
  // temporary solution, plays animations
  // at 30fps while rest of the game is 60fps
  int frameIndex = FPS_HALF(curr->animFrame);
  
  // Get first frame, then current frame
  char* firstFrame = MODELANIM_GETFRAME(ma);
  mf = &firstFrame[ma->frameSize * frameIndex];
  
  char* vertData = MODELFRAME_GETVERT(mf);

	Decompressed
	
		// Copy uncompressed vertices to scratchpad
		CompVertex* ptrVerts = (CompVertex*)vertData;
		
		stack[stackIndex].X = ptrVerts[vertexIndex].X;
		stack[stackIndex].Y = ptrVerts[vertexIndex].Y;
		stack[stackIndex].Z = ptrVerts[vertexIndex].Z;

	Compressed
	
		//store temporal vertex packed uint
		u_int temporal = ma->ptrDeltaArray[vertexIndex];

		//printf("temporal: %08x\n", temporal);

		//extract data from packed uint
		//deltaArray bits: 0bXXXXXXXZZZZZZZZYYYYYYYYAAABBBCCC

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
		int newX = GetSignedBits(vertData, XBits + 1);
		int newY = GetSignedBits(vertData, YBits + 1);
		int newZ = GetSignedBits(vertData, ZBits + 1);

		//calculate decompressed coord value
		x_alu = (x_alu + (int)newX + bx);
		y_alu = (y_alu + (int)newY + by);
		z_alu = (z_alu + (int)newZ + bz);

		//store values to stack index, axis swap is important
		stack[stackIndex].X = x_alu;
		stack[stackIndex].Y = z_alu;
		stack[stackIndex].Z = y_alu;
	
#endif