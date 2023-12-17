#include <common.h>

// does not really touch voiceline
void DECOMP_Voiceline_PoolInit(void)
{
  char index;

  sdata->criticalSectionCount = 0;

  sdata->numBackup_ChannelStats = 0;

  sdata->ptrCseqHeader = 0;

  DECOMP_Bank_ResetAllocator();

  DECOMP_Audio_SetDefaults();

  DECOMP_LIST_Clear(&sdata->channelFree);
  DECOMP_LIST_Clear(&sdata->channelTaken);

  DECOMP_LIST_Init(&sdata->channelFree, &sdata->channelStatsPrev[0], 0x20, 0x18);

  SpuSetReverbVoice(0, 0xffffff);

  // initialize all members in sound list
  for (index = 0; index < 24; index++)
  {
    struct ChannelStats* stats = &sdata->channelStatsPrev[index];
    sdata->ChannelUpdateFlags[index] = 0;

    SpuSetVoiceADSRAttr(index, 0, 0xf, 0x7f, 2, 0xf, 5, 1, 3);
	
    stats->flags = 0;
    stats->channelID = index;

	stats->ad = 0x80ff;
	stats->sr = 0x1fc2;

    struct ChannelAttr *curr = &sdata->channelAttrCur[index];

    curr->spuStartAddr = -1;

    curr->ad = 0x80ff;
    curr->sr = 0x1fc2;

    curr->pitch = -1;
    curr->reverb = -1;
    curr->audioL = -1;
    curr->audioR = -1;
  }

  for (index = 0; index < 2; index++)
  {
    struct Song *pool = &sdata->songPool[index];

	// not playing
	pool->flags = 0;

    pool->songPoolIndex = index;
  }

  for (index = 0; index < 24; index++)
  {
    struct SongSeq *seq = &sdata->songSeq[index];

    // not playing
    seq->flags = 0;

    seq->soundID = index;
  }
}