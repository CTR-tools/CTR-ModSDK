#include <common.h>

void DECOMP_howl_ParseCseqHeader(struct CseqHeader* ch)
{
	unsigned int addr = ch;
	
	sdata->ptrCseqHeader = addr;
	addr += sizeof(struct CseqHeader);
	
	sdata->ptrCseqLongSamples = addr;
	addr += sizeof(struct SampleInstrument) * ch->numLongSamples;
	
	sdata->ptrCseqShortSamples = addr;
	addr += sizeof(struct SampleDrums) * ch->numShortSamples;
	
	sdata->ptrCseqSongStartOffset = addr;
	addr += sizeof(short) * ch->numSongs;
	
	// align up by 4
	addr += 2;
	
	sdata->ptrCseqSongData = addr;
}