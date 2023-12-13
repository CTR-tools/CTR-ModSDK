#include <common.h>

void DECOMP_Channel_ParseSongToChannels()
{
	struct Song* song;
	struct SongSeq* seq;
	struct SongSeq** seqEntry;
	int boolVolumeChange;
	
	if(sdata->boolAudioEnabled == 0) return;
	if(sdata->ptrCseqHeader == 0) return;
	
	boolVolumeChange = 0;
	
	for(
			song = &sdata->songPool[0];
			song < &sdata->songPool[2];
			song++
		)
	{	
		// if not playing, skip
		if((song->flags & 1) == 0) continue;
		
		// if paused, skip
		if((song->flags & 2) != 0) continue;
		
		// song playing offset?
		song->unk10 += song->tempo;
		int unk10_total = song->unk10;
		
		song->timeSpentPlaying += unk10_total >> 0x10;
		song->unk10 = (unsigned short)unk10_total;

		int volCurr = song->vol_Curr;
		int volNew = song->vol_New;
		int volStepRate = song->vol_StepRate;
		int volStepped;
		int boolFinalStep;
		
		// === Copy/Paste ===
		if(volCurr != volNew)
		{
			if(volCurr < volNew)
			{
				volStepped = volCurr + volStepRate;
				boolFinalStep = volStepped > volNew;
			}
			
			else // volCurr > volNew
			{
				volStepped = volCurr - volStepRate;
				boolFinalStep = volStepped < volNew;
			}
			
			if(boolFinalStep)
			{
				volStepped = volNew;
				
				// song is over
				if((song->flags & 4) != 0)
				{
					song->flags &= ~(4);
					
					DECOMP_SongPool_StopAllCseq(song);
					DECOMP_Music_End();
				}
			}
			
			song->vol_Curr = volStepped;
			boolVolumeChange = 1;
		}
		
		for(
				seqEntry = &song->CseqSequences[0];
				seqEntry < &song->CseqSequences[song->numSequences];
				seqEntry++
			)
		{
			seq = seqEntry[0];
			
			volCurr = seq->vol_Curr;
			volNew = seq->vol_New;
			volStepRate = seq->vol_StepRate;
			
			// === Copy/Paste ===
			if(volCurr != volNew)
			{
				if(volCurr < volNew)
				{
					volStepped = volCurr + volStepRate;
					boolFinalStep = volStepped > volNew;
				}
				
				else // volCurr > volNew
				{
					volStepped = volCurr - volStepRate;
					boolFinalStep = volStepped < volNew;
				}
				
				if(boolFinalStep)
				{
					volStepped = volNew;
				}
				
				seq->vol_Curr = volStepped;
				boolVolumeChange = 1;
			}
			
			// if sequence is playing
			if((seq->flags & 1) != 0)
			{
				seq->NoteTimeElapsed += unk10_total >> 0x10;
				
				// === need to work on this variable naming ===
				
				while(seq->NoteLength <= seq->NoteTimeElapsed)
				{	
					// if reached end, quit
					if((seq->flags & 1) == 0) break;
					
					seq->NoteTimeElapsed -= seq->NoteLength;
					
					// currNote->opcode
					int opcode = seq->currNote[0];
					
					#if 0
					if(opcode >= 0xb) {} // ERROR
					#endif
					
					// call opcode from funcPtr array,
					// this is OG until DATA is rewritten
					(*data.opcodeFunc[opcode])(seq);
					
					// if reached end, quit
					if((seq->flags & 1) == 0) break;
					
					// if song restarting (opcode03)
					if((seq->flags & 8) != 0)
					{
						seq->flags &= ~(8);
						
						seq->currNote = seq->firstNote;
					}
					
					// if song not restarting (opcode03)
					else
					{
						seq->currNote += data.opcodeOffset[opcode];
					}
					
					seq->currNote = 
						DECOMP_howl_GetNextNote(seq->currNote, &seq->NoteLength);
				}
			}
		}
	}
	
	if(boolVolumeChange)
	{
		DECOMP_UpdateChannelVol_Music_All();
	}
}