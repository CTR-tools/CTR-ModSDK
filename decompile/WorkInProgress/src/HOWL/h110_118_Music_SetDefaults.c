#include <common.h>

void Music_SetDefaults(void)
{
    sdata->boolPlayCseqMusic = false;
    // no music playing
    sdata->CseqSongID = -1;
    sdata->CseqSongTempo = 0;
}

// param_1 - SongID (playing)
// param_2 - deltaBPM
// param_3 - 8008d068 for AdvHub
// param_4 - songSetActiveBits
void Music_Adjust(u_int songID, int newTempo, struct SongSet *set, u_int songSetActiveBits)
{
    songID &= 0xffff;

    // if cseq music can play
    if (sdata->boolPlayCseqMusic != 0)
    {
        if (sdata->CseqSongID == songID)
        {
            // if tempo has changed
            if (sdata->CseqSongTempo != newTempo)
            {
                CseqMusic_ChangeTempo(sdata->CseqSongID, newTempo);
                sdata->CseqSongTempo = newTempo;
            }
        }
        else
        {
            CseqMusic_Stop(sdata->CseqSongID);
        }
    }

    // if new SongID
    if (sdata->CseqSongID != songID)
    {
        //  (loopAtEnd)
        CseqMusic_Start(songID, newTempo, set, songSetActiveBits, 1);

        sdata->boolPlayCseqMusic = true;

        // set active SongID and tempo
        sdata->CseqSongID = songID;
        sdata->CseqSongTempo = newTempo;
    }
}

// Music_LowerVolume
// happens during "FINAL LAP!"
void Music_LowerVolume(void)
{
    u_int setVolume;

    if (sdata->boolPlayCseqMusic != 0)
    {
        // 50% volume
        setVolume = 150;

        if (1 < sdata->CseqSongID - 1)
        {
            // 25% volume
            setVolume = 90;
        }

        CseqMusic_ChangeVolume(sdata->CseqSongID & 0xffff, setVolume, 8);
    }
}

// after "FINAL LAP!" is done
void Music_RaiseVolume(void)
{
    u_int setVolume;

    if (sdata->boolPlayCseqMusic != 0)
    {
        // 100% volume
        setVolume = 255;
        if (1 < sdata->CseqSongID - 1)
        {
            // 75% volume
            setVolume = 190;
        }
        CseqMusic_ChangeVolume(sdata->CseqSongID & 0xffff, setVolume, 8);
    }
}

void Music_Restart(void)
{
    // if cseq music is playing
    if (sdata->boolPlayCseqMusic)
    {
        CseqMusic_Restart(sdata->CseqSongID, 8);
    }
}

void Music_Stop(void)
{
    // if music is playing
    if (sdata->boolPlayCseqMusic)
    {
        CseqMusic_Stop(sdata->CseqSongID & 0xffff);

        sdata->boolPlayCseqMusic = 0;
        sdata->CseqSongID = -1;
    }
}

void Music_Start(u_int songID)
{
    sdata->boolPlayCseqMusic = true;

    // set highest song index
    sdata->CseqSongID = songID & 0xffff;
}

void Music_End(void)
{
    sdata->boolPlayCseqMusic = false;

    // no songs are playing
    sdata->CseqSongID = -1;
}

u_int Music_GetHighestSongPlayIndex(void)
{
    // 0xffff - no cseq music
    // 0x0000 - song[0] (level music)
    // 0x0001 - song[1] (game aku)

    // "could" be 2 from [2] (menu aku),
    // but the game never sets it

    return sdata->CseqSongID;
}