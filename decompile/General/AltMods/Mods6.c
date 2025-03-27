
#ifdef USE_FASTANIM
void FastAnim_Start(struct GameTracker* gGT)
{	
	for(int i = 0; i < gGT->numPlyrCurrGame; i++)
	{
		struct Driver* d = gGT->drivers[i];
		
		if(d == 0)
			continue;
		
		struct Instance* inst = d->instSelf;

#ifdef REBUILD_PC
		if (inst == 0)
			continue;
#endif

		struct Model* m = inst->model;

#ifdef REBUILD_PC
		if (m == 0)
			continue;
#endif
		
		for(int j = 0; j < m->numHeaders; j++)
		{
			struct ModelHeader* h = &m->headers[j];
			
			// Just do TURN
			//for(int k = 0; k < h->numAnimations; k++)
			if(h->numAnimations != 0)
			{
				// Just do TURN
				// struct ModelAnim* ma = h->ptrAnimations[k];
				struct ModelAnim* ma = h->ptrAnimations[0];
				
				// if animation is already decompressed, skip
				if(ma->ptrDeltaArray == 0)
					continue;
				
				void FastAnim_Decompress(struct ModelAnim* ma, u_int* pCmd);
				FastAnim_Decompress(ma, h->ptrCommandList);	
			}			
		}
	}
}
#endif