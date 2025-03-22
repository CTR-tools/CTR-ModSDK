
#ifdef USE_FASTANIM
void FastAnim_Start(struct GameTracker* gGT)
{	
	for(int i = 0; i < gGT->numPlyrCurrGame; i++)
	{
		struct Driver* d = gGT->drivers[i];
		
		if(d == 0)
			continue;
		
		struct Instance* inst = d->instSelf;
		struct Model* m = inst->model;
		
		for(int j = 0; j < m->numHeaders; j++)
		{
			struct ModelHeader* h = &m->headers[j];
			
			for(int k = 0; k < h->numAnimations; k++)
			{
				struct ModelAnim* ma = h->ptrAnimations[k];
				
				void FastAnim_Decompress(struct ModelAnim* ma);
				FastAnim_Decompress(ma);	
			}			
		}
	}
}
#endif