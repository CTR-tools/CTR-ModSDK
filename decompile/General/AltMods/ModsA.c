
#ifdef USE_FASTANIM
void FastAnim_Decompress(struct ModelAnim* ma)
{
	
}
#endif

#if 0

  // animation
  ma = m->headers[0].ptrAnimations[curr->animIndex];
  
  // temporary solution, plays animations
  // at 30fps while rest of the game is 60fps
  int frameIndex = FPS_HALF(curr->animFrame);
  
  // cast
  char* maByte = (char*)ma;
  maByte = MODELANIM_GETFRAME(maByte);
  maByte = &maByte[ma->frameSize * frameIndex];
  
  // frame data
  mf = maByte;
  
  char* vertData = (char*)&mf[0] + mf->vertexOffset;

	Decompressed
	
		//copy from vertex buffer to stack index
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