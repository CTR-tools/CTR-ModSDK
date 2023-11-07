#include "EMULATOR_SPU.H"
#include "Core/Debug/EMULATOR_LOG.H"

#define SND_SAMPLES     1024
#define PITCH_SHIFT     12
#define VOL_SHIFT       15
#define BLOCK_END       (28 << PITCH_SHIFT)
#define REV_SAMPLES     1024*256
REVERBInfo reverb;
static int32_t reverbCounter = 0;
int32_t gSamples[SND_SAMPLES * 2];
int32_t gReverbArea[REV_SAMPLES];
int32_t sRVBStart[SND_SAMPLES * 2 * 4];
int32_t SSumL[SND_SAMPLES];
int32_t SSumR[SND_SAMPLES];
static int32_t RateTableAdd[128];
static int32_t RateTableAdd_f[128];
static int32_t RateTableSub[128];
static int32_t RateTableSub_f[128];
static const int32_t RateTable_denom = 1 << (((4 * 32) >> 2) - 11);
int32_t disableReverb = 0;
int32_t disableADSR = 0;
int32_t disableChannelVol = 0;

typedef long (*audioFunc)();
audioFunc gAudioFunc = NULL;

#if defined(SDL2)
SDL_AudioDeviceID gAudioDevice;
#endif

const int8_t SPU_POS[] = { 0, 60, 115,  98, 122 };
const int8_t SPU_NEG[] = { 0,  0, -52, -55, -60 };

const int32_t gauss[] = {
    0x172, 0x519, 0x176, 0x000, 0x16E, 0x519, 0x17A, 0x000,
    0x16A, 0x518, 0x17D, 0x000, 0x166, 0x518, 0x181, 0x000,
    0x162, 0x518, 0x185, 0x000, 0x15F, 0x518, 0x189, 0x000,
    0x15B, 0x518, 0x18D, 0x000, 0x157, 0x517, 0x191, 0x000,
    0x153, 0x517, 0x195, 0x000, 0x150, 0x517, 0x19A, 0x000,
    0x14C, 0x516, 0x19E, 0x000, 0x148, 0x516, 0x1A2, 0x000,
    0x145, 0x515, 0x1A6, 0x000, 0x141, 0x514, 0x1AA, 0x000,
    0x13E, 0x514, 0x1AE, 0x000, 0x13A, 0x513, 0x1B2, 0x000,
    0x137, 0x512, 0x1B7, 0x001, 0x133, 0x511, 0x1BB, 0x001,
    0x130, 0x511, 0x1BF, 0x001, 0x12C, 0x510, 0x1C3, 0x001,
    0x129, 0x50F, 0x1C8, 0x001, 0x125, 0x50E, 0x1CC, 0x001,
    0x122, 0x50D, 0x1D0, 0x001, 0x11E, 0x50C, 0x1D5, 0x001,
    0x11B, 0x50B, 0x1D9, 0x001, 0x118, 0x50A, 0x1DD, 0x001,
    0x114, 0x508, 0x1E2, 0x001, 0x111, 0x507, 0x1E6, 0x002,
    0x10E, 0x506, 0x1EB, 0x002, 0x10B, 0x504, 0x1EF, 0x002,
    0x107, 0x503, 0x1F3, 0x002, 0x104, 0x502, 0x1F8, 0x002,
    0x101, 0x500, 0x1FC, 0x002, 0x0FE, 0x4FF, 0x201, 0x002,
    0x0FB, 0x4FD, 0x205, 0x003, 0x0F8, 0x4FB, 0x20A, 0x003,
    0x0F5, 0x4FA, 0x20F, 0x003, 0x0F2, 0x4F8, 0x213, 0x003,
    0x0EF, 0x4F6, 0x218, 0x003, 0x0EC, 0x4F5, 0x21C, 0x004,
    0x0E9, 0x4F3, 0x221, 0x004, 0x0E6, 0x4F1, 0x226, 0x004,
    0x0E3, 0x4EF, 0x22A, 0x004, 0x0E0, 0x4ED, 0x22F, 0x004,
    0x0DD, 0x4EB, 0x233, 0x005, 0x0DA, 0x4E9, 0x238, 0x005,
    0x0D7, 0x4E7, 0x23D, 0x005, 0x0D4, 0x4E5, 0x241, 0x005,
    0x0D2, 0x4E3, 0x246, 0x006, 0x0CF, 0x4E0, 0x24B, 0x006,
    0x0CC, 0x4DE, 0x250, 0x006, 0x0C9, 0x4DC, 0x254, 0x006,
    0x0C7, 0x4D9, 0x259, 0x007, 0x0C4, 0x4D7, 0x25E, 0x007,
    0x0C1, 0x4D5, 0x263, 0x007, 0x0BF, 0x4D2, 0x267, 0x008,
    0x0BC, 0x4D0, 0x26C, 0x008, 0x0BA, 0x4CD, 0x271, 0x008,
    0x0B7, 0x4CB, 0x276, 0x009, 0x0B4, 0x4C8, 0x27B, 0x009,
    0x0B2, 0x4C5, 0x280, 0x009, 0x0AF, 0x4C3, 0x284, 0x00A,
    0x0AD, 0x4C0, 0x289, 0x00A, 0x0AB, 0x4BD, 0x28E, 0x00A,
    0x0A8, 0x4BA, 0x293, 0x00B, 0x0A6, 0x4B7, 0x298, 0x00B,
    0x0A3, 0x4B5, 0x29D, 0x00B, 0x0A1, 0x4B2, 0x2A2, 0x00C,
    0x09F, 0x4AF, 0x2A6, 0x00C, 0x09C, 0x4AC, 0x2AB, 0x00D,
    0x09A, 0x4A9, 0x2B0, 0x00D, 0x098, 0x4A6, 0x2B5, 0x00E,
    0x096, 0x4A2, 0x2BA, 0x00E, 0x093, 0x49F, 0x2BF, 0x00F,
    0x091, 0x49C, 0x2C4, 0x00F, 0x08F, 0x499, 0x2C9, 0x00F,
    0x08D, 0x496, 0x2CE, 0x010, 0x08B, 0x492, 0x2D3, 0x010,
    0x089, 0x48F, 0x2D8, 0x011, 0x086, 0x48C, 0x2DC, 0x011,
    0x084, 0x488, 0x2E1, 0x012, 0x082, 0x485, 0x2E6, 0x013,
    0x080, 0x481, 0x2EB, 0x013, 0x07E, 0x47E, 0x2F0, 0x014,
    0x07C, 0x47A, 0x2F5, 0x014, 0x07A, 0x477, 0x2FA, 0x015,
    0x078, 0x473, 0x2FF, 0x015, 0x076, 0x470, 0x304, 0x016,
    0x075, 0x46C, 0x309, 0x017, 0x073, 0x468, 0x30E, 0x017,
    0x071, 0x465, 0x313, 0x018, 0x06F, 0x461, 0x318, 0x018,
    0x06D, 0x45D, 0x31D, 0x019, 0x06B, 0x459, 0x322, 0x01A,
    0x06A, 0x455, 0x326, 0x01B, 0x068, 0x452, 0x32B, 0x01B,
    0x066, 0x44E, 0x330, 0x01C, 0x064, 0x44A, 0x335, 0x01D,
    0x063, 0x446, 0x33A, 0x01D, 0x061, 0x442, 0x33F, 0x01E,
    0x05F, 0x43E, 0x344, 0x01F, 0x05E, 0x43A, 0x349, 0x020,
    0x05C, 0x436, 0x34E, 0x020, 0x05A, 0x432, 0x353, 0x021,
    0x059, 0x42E, 0x357, 0x022, 0x057, 0x42A, 0x35C, 0x023,
    0x056, 0x425, 0x361, 0x024, 0x054, 0x421, 0x366, 0x024,
    0x053, 0x41D, 0x36B, 0x025, 0x051, 0x419, 0x370, 0x026,
    0x050, 0x415, 0x374, 0x027, 0x04E, 0x410, 0x379, 0x028,
    0x04D, 0x40C, 0x37E, 0x029, 0x04C, 0x408, 0x383, 0x02A,
    0x04A, 0x403, 0x388, 0x02B, 0x049, 0x3FF, 0x38C, 0x02C,
    0x047, 0x3FB, 0x391, 0x02D, 0x046, 0x3F6, 0x396, 0x02E,
    0x045, 0x3F2, 0x39B, 0x02F, 0x043, 0x3ED, 0x39F, 0x030,
    0x042, 0x3E9, 0x3A4, 0x031, 0x041, 0x3E5, 0x3A9, 0x032,
    0x040, 0x3E0, 0x3AD, 0x033, 0x03E, 0x3DC, 0x3B2, 0x034,
    0x03D, 0x3D7, 0x3B7, 0x035, 0x03C, 0x3D2, 0x3BB, 0x036,
    0x03B, 0x3CE, 0x3C0, 0x037, 0x03A, 0x3C9, 0x3C5, 0x038,
    0x038, 0x3C5, 0x3C9, 0x03A, 0x037, 0x3C0, 0x3CE, 0x03B,
    0x036, 0x3BB, 0x3D2, 0x03C, 0x035, 0x3B7, 0x3D7, 0x03D,
    0x034, 0x3B2, 0x3DC, 0x03E, 0x033, 0x3AD, 0x3E0, 0x040,
    0x032, 0x3A9, 0x3E5, 0x041, 0x031, 0x3A4, 0x3E9, 0x042,
    0x030, 0x39F, 0x3ED, 0x043, 0x02F, 0x39B, 0x3F2, 0x045,
    0x02E, 0x396, 0x3F6, 0x046, 0x02D, 0x391, 0x3FB, 0x047,
    0x02C, 0x38C, 0x3FF, 0x049, 0x02B, 0x388, 0x403, 0x04A,
    0x02A, 0x383, 0x408, 0x04C, 0x029, 0x37E, 0x40C, 0x04D,
    0x028, 0x379, 0x410, 0x04E, 0x027, 0x374, 0x415, 0x050,
    0x026, 0x370, 0x419, 0x051, 0x025, 0x36B, 0x41D, 0x053,
    0x024, 0x366, 0x421, 0x054, 0x024, 0x361, 0x425, 0x056,
    0x023, 0x35C, 0x42A, 0x057, 0x022, 0x357, 0x42E, 0x059,
    0x021, 0x353, 0x432, 0x05A, 0x020, 0x34E, 0x436, 0x05C,
    0x020, 0x349, 0x43A, 0x05E, 0x01F, 0x344, 0x43E, 0x05F,
    0x01E, 0x33F, 0x442, 0x061, 0x01D, 0x33A, 0x446, 0x063,
    0x01D, 0x335, 0x44A, 0x064, 0x01C, 0x330, 0x44E, 0x066,
    0x01B, 0x32B, 0x452, 0x068, 0x01B, 0x326, 0x455, 0x06A,
    0x01A, 0x322, 0x459, 0x06B, 0x019, 0x31D, 0x45D, 0x06D,
    0x018, 0x318, 0x461, 0x06F, 0x018, 0x313, 0x465, 0x071,
    0x017, 0x30E, 0x468, 0x073, 0x017, 0x309, 0x46C, 0x075,
    0x016, 0x304, 0x470, 0x076, 0x015, 0x2FF, 0x473, 0x078,
    0x015, 0x2FA, 0x477, 0x07A, 0x014, 0x2F5, 0x47A, 0x07C,
    0x014, 0x2F0, 0x47E, 0x07E, 0x013, 0x2EB, 0x481, 0x080,
    0x013, 0x2E6, 0x485, 0x082, 0x012, 0x2E1, 0x488, 0x084,
    0x011, 0x2DC, 0x48C, 0x086, 0x011, 0x2D8, 0x48F, 0x089,
    0x010, 0x2D3, 0x492, 0x08B, 0x010, 0x2CE, 0x496, 0x08D,
    0x00F, 0x2C9, 0x499, 0x08F, 0x00F, 0x2C4, 0x49C, 0x091,
    0x00F, 0x2BF, 0x49F, 0x093, 0x00E, 0x2BA, 0x4A2, 0x096,
    0x00E, 0x2B5, 0x4A6, 0x098, 0x00D, 0x2B0, 0x4A9, 0x09A,
    0x00D, 0x2AB, 0x4AC, 0x09C, 0x00C, 0x2A6, 0x4AF, 0x09F,
    0x00C, 0x2A2, 0x4B2, 0x0A1, 0x00B, 0x29D, 0x4B5, 0x0A3,
    0x00B, 0x298, 0x4B7, 0x0A6, 0x00B, 0x293, 0x4BA, 0x0A8,
    0x00A, 0x28E, 0x4BD, 0x0AB, 0x00A, 0x289, 0x4C0, 0x0AD,
    0x00A, 0x284, 0x4C3, 0x0AF, 0x009, 0x280, 0x4C5, 0x0B2,
    0x009, 0x27B, 0x4C8, 0x0B4, 0x009, 0x276, 0x4CB, 0x0B7,
    0x008, 0x271, 0x4CD, 0x0BA, 0x008, 0x26C, 0x4D0, 0x0BC,
    0x008, 0x267, 0x4D2, 0x0BF, 0x007, 0x263, 0x4D5, 0x0C1,
    0x007, 0x25E, 0x4D7, 0x0C4, 0x007, 0x259, 0x4D9, 0x0C7,
    0x006, 0x254, 0x4DC, 0x0C9, 0x006, 0x250, 0x4DE, 0x0CC,
    0x006, 0x24B, 0x4E0, 0x0CF, 0x006, 0x246, 0x4E3, 0x0D2,
    0x005, 0x241, 0x4E5, 0x0D4, 0x005, 0x23D, 0x4E7, 0x0D7,
    0x005, 0x238, 0x4E9, 0x0DA, 0x005, 0x233, 0x4EB, 0x0DD,
    0x004, 0x22F, 0x4ED, 0x0E0, 0x004, 0x22A, 0x4EF, 0x0E3,
    0x004, 0x226, 0x4F1, 0x0E6, 0x004, 0x221, 0x4F3, 0x0E9,
    0x004, 0x21C, 0x4F5, 0x0EC, 0x003, 0x218, 0x4F6, 0x0EF,
    0x003, 0x213, 0x4F8, 0x0F2, 0x003, 0x20F, 0x4FA, 0x0F5,
    0x003, 0x20A, 0x4FB, 0x0F8, 0x003, 0x205, 0x4FD, 0x0FB,
    0x002, 0x201, 0x4FF, 0x0FE, 0x002, 0x1FC, 0x500, 0x101,
    0x002, 0x1F8, 0x502, 0x104, 0x002, 0x1F3, 0x503, 0x107,
    0x002, 0x1EF, 0x504, 0x10B, 0x002, 0x1EB, 0x506, 0x10E,
    0x002, 0x1E6, 0x507, 0x111, 0x001, 0x1E2, 0x508, 0x114,
    0x001, 0x1DD, 0x50A, 0x118, 0x001, 0x1D9, 0x50B, 0x11B,
    0x001, 0x1D5, 0x50C, 0x11E, 0x001, 0x1D0, 0x50D, 0x122,
    0x001, 0x1CC, 0x50E, 0x125, 0x001, 0x1C8, 0x50F, 0x129,
    0x001, 0x1C3, 0x510, 0x12C, 0x001, 0x1BF, 0x511, 0x130,
    0x001, 0x1BB, 0x511, 0x133, 0x001, 0x1B7, 0x512, 0x137,
    0x000, 0x1B2, 0x513, 0x13A, 0x000, 0x1AE, 0x514, 0x13E,
    0x000, 0x1AA, 0x514, 0x141, 0x000, 0x1A6, 0x515, 0x145,
    0x000, 0x1A2, 0x516, 0x148, 0x000, 0x19E, 0x516, 0x14C,
    0x000, 0x19A, 0x517, 0x150, 0x000, 0x195, 0x517, 0x153,
    0x000, 0x191, 0x517, 0x157, 0x000, 0x18D, 0x518, 0x15B,
    0x000, 0x189, 0x518, 0x15F, 0x000, 0x185, 0x518, 0x162,
    0x000, 0x181, 0x518, 0x166, 0x000, 0x17D, 0x518, 0x16A,
    0x000, 0x17A, 0x519, 0x16E, 0x000, 0x176, 0x519, 0x172 };

#define gval0 (((int16_t*)(&channel->block[29]))[gpos])
#define gval(x) (((int16_t*)(&channel->block[29]))[(gpos+x)&3])

void storeInterp(struct Channel* channel, int32_t value)
{
    int gpos = channel->block[28];
    gval0 = value;
    gpos = (gpos + 1) & 3;
    channel->block[28] = gpos;
}

int32_t getInterp(struct Channel* channel)
{
    int vl, vr; int gpos;
    vl = (channel->spos >> 6) & ~3;
    gpos = channel->block[28];
    vr = (gauss[vl] * gval0) & ~2047;
    vr += (gauss[vl + 1] * gval(1)) & ~2047;
    vr += (gauss[vl + 2] * gval(2)) & ~2047;
    vr += (gauss[vl + 3] * gval(3)) & ~2047;
    return vr >> 11;
}

int32_t ADSR(struct Channel* channel)
{
    if (channel->silent == 2 && channel->stop == TRUE)
    {
        return 0;
    }

    switch (channel->_adsr.state)
    {
    case ATTACK:
    {
        if (channel->_adsr.envelopevol >= 0x6000 && channel->_adsr.attackmodeexp)
        {
            channel->_adsr.envelopevol += RateTableAdd[channel->_adsr.attackrate + 8];
            channel->_adsr.envelopevol_f += RateTableAdd_f[channel->_adsr.attackrate + 8];
        }
        else
        {
            channel->_adsr.envelopevol += RateTableAdd[channel->_adsr.attackrate + 0];
            channel->_adsr.envelopevol_f += RateTableAdd_f[channel->_adsr.attackrate + 0];
        }

        if (channel->_adsr.envelopevol_f >= RateTable_denom)
        {
            channel->_adsr.envelopevol_f -= RateTable_denom;
            channel->_adsr.envelopevol++;
        }

        if (channel->_adsr.envelopevol >= 0x8000)
        {
            channel->_adsr.envelopevol = 0x7FFF;
            channel->_adsr.envelopevol_f = RateTable_denom;
            channel->_adsr.state = DECAY;
        }

        channel->_adsr.lvolume = channel->_adsr.envelopevol >> 5;
        return channel->_adsr.lvolume;
        break;
    }
    case DECAY:
    {
        channel->_adsr.envelopevol += (RateTableSub[channel->_adsr.decayrate * 4] * channel->_adsr.envelopevol) >> 15;

        channel->_adsr.envelopevol_f += RateTableSub_f[channel->_adsr.decayrate * 4];

        if (channel->_adsr.envelopevol_f < 0)
        {
            channel->_adsr.envelopevol_f += RateTable_denom;
            channel->_adsr.envelopevol--;
        }

        if (channel->_adsr.envelopevol < 0)
        {
            channel->_adsr.envelopevol = 0;
            channel->_adsr.envelopevol_f = 0;
        }

        if (((channel->_adsr.envelopevol >> 11) & 0xF) <= channel->_adsr.sustainlevel)
        {
            channel->_adsr.state = SUSTAIN;
        }

        channel->_adsr.lvolume = channel->_adsr.envelopevol >> 5;
        return channel->_adsr.lvolume;
        break;
    }
    case SUSTAIN:
    {
        if (channel->_adsr.sustainincrease)
        {
            if (channel->_adsr.sustainmodexp && channel->_adsr.envelopevol >= 0x6000)
            {
                channel->_adsr.envelopevol += RateTableAdd[channel->_adsr.sustainrate + 8];
                channel->_adsr.envelopevol_f += RateTableAdd_f[channel->_adsr.sustainrate + 8];
            }
            else
            {
                channel->_adsr.envelopevol += RateTableAdd[channel->_adsr.sustainrate + 0];
                channel->_adsr.envelopevol_f += RateTableAdd_f[channel->_adsr.sustainrate + 0];
            }

            if (channel->_adsr.envelopevol_f >= RateTable_denom)
            {
                channel->_adsr.envelopevol_f -= RateTable_denom;
                channel->_adsr.envelopevol++;
            }

            if (channel->_adsr.envelopevol >= 0x8000)
            {
                channel->_adsr.envelopevol = 0x7FFF;
                channel->_adsr.envelopevol_f = RateTable_denom;
            }
        }
        else
        {
            if (channel->_adsr.sustainmodexp)
            {
                channel->_adsr.envelopevol += (RateTableSub[channel->_adsr.sustainrate] * channel->_adsr.envelopevol) >> 15;
            }
            else
            {
                channel->_adsr.envelopevol += RateTableSub[channel->_adsr.sustainrate];
            }

            channel->_adsr.envelopevol_f += RateTableSub_f[channel->_adsr.sustainrate];
            if (channel->_adsr.envelopevol_f < 0)
            {
                channel->_adsr.envelopevol_f += RateTable_denom;
                channel->_adsr.envelopevol--;
            }

            if (channel->_adsr.envelopevol < 0)
            {
                channel->_adsr.envelopevol = 0;
                channel->_adsr.envelopevol_f = 0;
            }
        }

        channel->_adsr.lvolume = channel->_adsr.envelopevol >> 5;
        return channel->_adsr.lvolume;
        break;
    }
    case RELEASE:
    {
        if (channel->_adsr.releasemodeexp)
        {
            channel->_adsr.envelopevol += (RateTableSub[channel->_adsr.releaserate * 4] * channel->_adsr.envelopevol) >> 15;
        }
        else
        {
            channel->_adsr.envelopevol += RateTableSub[channel->_adsr.releaserate * 4];
        }

        channel->_adsr.envelopevol_f += RateTableSub_f[channel->_adsr.releaserate * 4];

        if (channel->_adsr.envelopevol_f < 0)
        {
            channel->_adsr.envelopevol_f += RateTable_denom;
            channel->_adsr.envelopevol--;
        }

        if (channel->_adsr.envelopevol < 0)
        {
            channel->_adsr.envelopevol = 0;
            channel->_adsr.envelopevol_f = 0;
        }

        channel->_adsr.lvolume = channel->_adsr.envelopevol >> 5;
        return channel->_adsr.lvolume;
        break;
    }
    }

    return 0;
}

int32_t clamp(int32_t value)
{
    if (value < -32768)
        return -32768;
    if (value > 32767)
        return 32767;
    return value;
}

int16_t vagPredicate(int16_t value, uint8_t pred, uint8_t shift, int32_t* s1, int32_t* s2)
{
    int32_t s = ((*s1) * SPU_POS[pred] + (*s2) * SPU_NEG[pred]) >> 6;
    s += (value >> shift);
    s = clamp(s);

    *s2 = *s1;
    *s1 = s;

    return s;
}

static int g_buffer(int iOff)                          // get_buffer content helper: takes care about wraps
{
    int* p = (int*)&gReverbArea;
    iOff = (iOff * 4) + reverb.CurrAddr;
    while (iOff > 0x3FFFF)       iOff = reverb.StartAddr + (iOff - 0x40000);
    while (iOff < reverb.StartAddr) iOff = 0x3ffff - (reverb.StartAddr - iOff);
    return (int)*(p + iOff);
}

static void s_buffer(int iOff, int iVal)                // set_buffer content helper: takes care about wraps and clipping
{
    int* p = (int*)&gReverbArea;
    iOff = (iOff * 4) + reverb.CurrAddr;
    while (iOff > 0x3FFFF) iOff = reverb.StartAddr + (iOff - 0x40000);
    while (iOff < reverb.StartAddr) iOff = 0x3ffff - (reverb.StartAddr - iOff);
    if (iVal < -32768L) iVal = -32768L; if (iVal > 32767L) iVal = 32767L;
    *(p + iOff) = (int)iVal;
}

static void s_buffer1(int iOff, int iVal)                // set_buffer (+1 sample) content helper: takes care about wraps and clipping
{
    int* p = (int*)&gReverbArea;
    iOff = (iOff * 4) + reverb.CurrAddr + 1;
    while (iOff > 0x3FFFF) iOff = reverb.StartAddr + (iOff - 0x40000);
    while (iOff < reverb.StartAddr) iOff = 0x3ffff - (reverb.StartAddr - iOff);
    if (iVal < -32768L) iVal = -32768L; if (iVal > 32767L) iVal = 32767L;
    *(p + iOff) = (int)iVal;
}

int32_t ReverbR()
{
    int rvbR = reverb.iLastRVBRight + (reverb.iRVBRight - reverb.iLastRVBRight) / 2;
    reverb.iLastRVBRight = reverb.iRVBRight;
    return rvbR;
}

int32_t ReverbL(int32_t ns)
{
    if ((++reverbCounter & 1))
    {
        int ACC0, ACC1, FB_A0, FB_A1, FB_B0, FB_B1;

        const int INPUT_SAMPLE_L = *(sRVBStart + (ns << 1));
        const int INPUT_SAMPLE_R = *(sRVBStart + (ns << 1) + 1);

        const int IIR_INPUT_A0 = (g_buffer(reverb.IIR_SRC_A0) * reverb.IIR_COEF) / 32768L + (INPUT_SAMPLE_L * reverb.IN_COEF_L) / 32768L;
        const int IIR_INPUT_A1 = (g_buffer(reverb.IIR_SRC_A1) * reverb.IIR_COEF) / 32768L + (INPUT_SAMPLE_R * reverb.IN_COEF_R) / 32768L;
        const int IIR_INPUT_B0 = (g_buffer(reverb.IIR_SRC_B0) * reverb.IIR_COEF) / 32768L + (INPUT_SAMPLE_L * reverb.IN_COEF_L) / 32768L;
        const int IIR_INPUT_B1 = (g_buffer(reverb.IIR_SRC_B1) * reverb.IIR_COEF) / 32768L + (INPUT_SAMPLE_R * reverb.IN_COEF_R) / 32768L;

        const int IIR_A0 = (IIR_INPUT_A0 * reverb.IIR_ALPHA) / 32768L + (g_buffer(reverb.IIR_DEST_A0) * (32768L - reverb.IIR_ALPHA)) / 32768L;
        const int IIR_A1 = (IIR_INPUT_A1 * reverb.IIR_ALPHA) / 32768L + (g_buffer(reverb.IIR_DEST_A1) * (32768L - reverb.IIR_ALPHA)) / 32768L;
        const int IIR_B0 = (IIR_INPUT_B0 * reverb.IIR_ALPHA) / 32768L + (g_buffer(reverb.IIR_DEST_B0) * (32768L - reverb.IIR_ALPHA)) / 32768L;
        const int IIR_B1 = (IIR_INPUT_B1 * reverb.IIR_ALPHA) / 32768L + (g_buffer(reverb.IIR_DEST_B1) * (32768L - reverb.IIR_ALPHA)) / 32768L;

        s_buffer1(reverb.IIR_DEST_A0, IIR_A0);
        s_buffer1(reverb.IIR_DEST_A1, IIR_A1);
        s_buffer1(reverb.IIR_DEST_B0, IIR_B0);
        s_buffer1(reverb.IIR_DEST_B1, IIR_B1);

        ACC0 = (g_buffer(reverb.ACC_SRC_A0) * reverb.ACC_COEF_A) / 32768L +
            (g_buffer(reverb.ACC_SRC_B0) * reverb.ACC_COEF_B) / 32768L +
            (g_buffer(reverb.ACC_SRC_C0) * reverb.ACC_COEF_C) / 32768L +
            (g_buffer(reverb.ACC_SRC_D0) * reverb.ACC_COEF_D) / 32768L;
        ACC1 = (g_buffer(reverb.ACC_SRC_A1) * reverb.ACC_COEF_A) / 32768L +
            (g_buffer(reverb.ACC_SRC_B1) * reverb.ACC_COEF_B) / 32768L +
            (g_buffer(reverb.ACC_SRC_C1) * reverb.ACC_COEF_C) / 32768L +
            (g_buffer(reverb.ACC_SRC_D1) * reverb.ACC_COEF_D) / 32768L;

        FB_A0 = g_buffer(reverb.MIX_DEST_A0 - reverb.FB_SRC_A);
        FB_A1 = g_buffer(reverb.MIX_DEST_A1 - reverb.FB_SRC_A);
        FB_B0 = g_buffer(reverb.MIX_DEST_B0 - reverb.FB_SRC_B);
        FB_B1 = g_buffer(reverb.MIX_DEST_B1 - reverb.FB_SRC_B);

        s_buffer(reverb.MIX_DEST_A0, ACC0 - (FB_A0 * reverb.FB_ALPHA) / 32768L);
        s_buffer(reverb.MIX_DEST_A1, ACC1 - (FB_A1 * reverb.FB_ALPHA) / 32768L);

        s_buffer(reverb.MIX_DEST_B0, (reverb.FB_ALPHA * ACC0) / 32768L - (FB_A0 * (int)(reverb.FB_ALPHA ^ 0xFFFF8000)) / 32768L - (FB_B0 * reverb.FB_X) / 32768L);
        s_buffer(reverb.MIX_DEST_B1, (reverb.FB_ALPHA * ACC1) / 32768L - (FB_A1 * (int)(reverb.FB_ALPHA ^ 0xFFFF8000)) / 32768L - (FB_B1 * reverb.FB_X) / 32768L);

        reverb.iLastRVBLeft = reverb.iRVBLeft;
        reverb.iLastRVBRight = reverb.iRVBRight;

        reverb.iRVBLeft = (g_buffer(reverb.MIX_DEST_A0) + g_buffer(reverb.MIX_DEST_B0)) / 3;
        reverb.iRVBRight = (g_buffer(reverb.MIX_DEST_A1) + g_buffer(reverb.MIX_DEST_B1)) / 3;

        reverb.iRVBLeft = (reverb.iRVBLeft * reverb.VolLeft) / 0x4000;
        reverb.iRVBRight = (reverb.iRVBRight * reverb.VolRight) / 0x4000;

        reverb.CurrAddr++;
        if (reverb.CurrAddr > 0x3ffff) reverb.CurrAddr = reverb.StartAddr;

        return reverb.iLastRVBLeft + (reverb.iRVBLeft - reverb.iLastRVBLeft) / 2;
    } 
    else
    {
        return reverb.iLastRVBLeft;
    }
}

void storeReverb(struct Channel* channel, int32_t ns)
{
    const int iRxl = (channel->sval * channel->volL) / 0x4000;
    const int iRxr = (channel->sval * channel->volR) / 0x4000;

    *(sRVBStart + (ns << 1)) += iRxl;
    *(sRVBStart + (ns << 1) + 1) += iRxr;
}

int32_t vagProcessBlock(struct Channel* channel, int16_t* dst)
{
    int32_t i;
    uint8_t d;
    uint8_t* src = channel->data + channel->pos;
    int32_t s1 = channel->s1;
    int32_t s2 = channel->s2;

    uint8_t pred = *src++;
    uint8_t flags = *src++;
    uint8_t shift = pred & 0x0F;
    int32_t value = 0;
    int32_t ns = 0;

    pred >>= 4;

    for (i = 0; i < 14; i++)
    {
        d = *src++;
        *dst++ = vagPredicate((d & 0x0F) << 12, pred, shift, &s1, &s2);
        *dst++ = vagPredicate((d & 0xF0) << 8, pred, shift, &s1, &s2);
    }

    if (flags & 4) // set loop start
    {
        channel->loop = channel->data + channel->pos;
        channel->loop_s1 = channel->s1;
        channel->loop_s2 = channel->s2;
    }

    if (flags & 1) // end
    {
        if (channel->loop)
        {
            src = channel->loop;
            s1 = channel->loop_s1;
            s2 = channel->loop_s2;
        }

        if (!(flags & 2)) // goto loop start
        {
            return 0;
        }
    }

    channel->pos = src - channel->data;
    channel->s1 = s1;
    channel->s2 = s2;

    return 1;
}

void initADSR()
{
    memset(RateTableAdd, 0, sizeof(int32_t) * 128);
    memset(RateTableAdd_f, 0, sizeof(int32_t) * 128);
    memset(RateTableSub, 0, sizeof(int32_t) * 128);
    memset(RateTableSub_f, 0, sizeof(int32_t) * 128);

    for (int lcv = 0; lcv < 48; lcv++)
    {
        RateTableAdd[lcv] = (7 - (lcv & 3)) << (11 - (lcv >> 2));
        RateTableSub[lcv] = (-8 + (lcv & 3)) << (11 - (lcv >> 2));

        RateTableAdd_f[lcv] = 0;
        RateTableSub_f[lcv] = 0;
    }

    for (int lcv = 48; lcv < 128; lcv++)
    {
        int denom = 1 << ((lcv >> 2) - 11);

        RateTableAdd[lcv] = (7 - (lcv & 3)) / denom;
        RateTableSub[lcv] = (-8 + (lcv & 3)) / denom;

        RateTableAdd_f[lcv] = (7 - (lcv & 3)) % denom;
        RateTableSub_f[lcv] = (-8 + (lcv & 3)) % denom;

        RateTableAdd_f[lcv] *= RateTable_denom / denom;
        RateTableSub_f[lcv] *= RateTable_denom / denom;

        if (RateTableSub_f[lcv] > 0)
        {
            RateTableSub_f[lcv] = -RateTableSub_f[lcv];
        }
    }
}

void fillVAG(struct Channel* channel, int32_t count, int32_t ns)
{
    int32_t posInc = channel->pitch;
    int32_t channelIndex = channel - channelList;

    while (channel->spos >= 0x10000)
    {
        if (channel->iSBPos == 28)
        {
            if (channel->silent == 1)
            {
                channel->silent = 2;

                channel->_adsr.lvolume = 0;
                channel->_adsr.envelopevol = 0;
            }

            channel->iSBPos = 0;

            if (!vagProcessBlock(channel, channel->block))
            {
                if (channel->silent == 0)
                {
                    channel->silent = 1;
                }
                channel->_adsr.state = RELEASE;
                channel->stop = TRUE;
            }
        }
        
        storeInterp(channel, clamp(channel->block[channel->iSBPos++]));

        channel->spos -= 0x10000;
    }

    int32_t fa = getInterp(channel);

    channel->sval = disableADSR ? fa : (ADSR(channel) * fa) / 1023;

    SSumL[ns]+=(channel->sval*(disableChannelVol ? 0x3FFF : channel->volL))/0x4000L;
    SSumR[ns]+=(channel->sval*(disableChannelVol ? 0x3FFF : channel->volR))/0x4000L;

    if (channel->reverb && !disableReverb)
    {
        storeReverb(channel,  ns);
    }

    channel->spos += channel->pitch << 4;
}

void convertSamples(int16_t* dst, int32_t* src, int32_t count)
{
    int32_t i;

    for (i = 0; i < count; i++)
    {
        *dst++ = clamp(*src++);
        *dst++ = clamp(*src++);
    }
}

void fillSamples(int16_t* buffer, int32_t count)
{
    int32_t i, ns;
    struct Channel* channel = NULL;

    memset(buffer, 0, count*sizeof(int32_t));
    memset(&gSamples, 0, sizeof(gSamples));
    memset(&sRVBStart, 0, sizeof(sRVBStart));

    for(ns = 0; ns < SND_SAMPLES; ns++)
    {
        SSumL[ns] = 0;
        SSumR[ns] = 0;

        for (i = 0, channel = &channelList[i]; i < SPU_MAX_CHANNELS; i++, channel++)
        {
            if (!channel->data)
                continue;

            fillVAG(channel, count, ns);
        }
    }

    memcpy(&gReverbArea, &gSamples, sizeof(gSamples));//?

    int32_t* samples = gSamples;

    for (ns = 0; ns < SND_SAMPLES; ns++)
    {
        *samples++ = (SSumL[ns] + ReverbL(ns));
        *samples++ = (SSumR[ns] + ReverbR());

        SSumL[ns] = 0;
        SSumR[ns] = 0;
    }

    convertSamples(buffer, gSamples, SND_SAMPLES);
}

void SPU_PrintChannelVolumes()
{
    for (int i = 0; i < 24; i++)
    {
        eprinterr("Channel: %x - VolL: %x - VolR: %x\n", i, channelList[i].volL, channelList[i].volR);
    }
}

void sndFill(void* udata, uint8_t* stream, int32_t len)
{
    if (gAudioFunc != NULL)
    {
        gAudioFunc();
    }

    fillSamples((int16_t*)stream, SND_SAMPLES);
}

void SPU_Initialise()
{
    int32_t i;
#if defined(SDL2)
    SDL_AudioSpec desired, obtained;
#endif

    for (i = 0; i < SPU_MAX_CHANNELS; i++)
    {
        channelList[i]._adsr.sustainlevel = 1024;
    }

    initADSR();

#if defined(SDL2)
    desired.freq = 44100;
    desired.format = AUDIO_S16SYS;
    desired.channels = 2;
    desired.samples = SND_SAMPLES;
    desired.callback = sndFill;
    desired.userdata = NULL;

    gAudioDevice = SDL_OpenAudioDevice(NULL, 0, &desired, &obtained, 0);
    SDL_PauseAudioDevice(gAudioDevice, 0);
#endif
}

void SPU_Destroy()
{
#if defined(SDL2)
    SDL_PauseAudioDevice(gAudioDevice, 1);
    SDL_CloseAudioDevice(gAudioDevice);
#endif
}

void SPU_StartADSR(struct Channel* channel)
{
    if (channel != NULL)
    {
        channel->_adsr.lvolume = 1;
        channel->_adsr.state = ATTACK;
        channel->_adsr.envelopevol = 0;
        channel->_adsr.envelopevol_f = 0;
    }
}

void SPU_ResetChannel(struct Channel* channel, uint8_t* data)
{
    channel->pos = 0;
    channel->s1 = 0;
    channel->s2 = 0;
    channel->data = data;
    channel->loop = NULL;
    channel->block[28] = 0;
    channel->block[29] = 0;
    channel->block[30] = 0;
    channel->spos = 0x30000;
    channel->iSBPos = 28;
    channel->reverb = 0;
    channel->silent = 0;
    channel->stop = FALSE;

    SPU_StartADSR(channel);
}

void Emulator_SetAudioUpdateFunction(long(*func))
{
    gAudioFunc =(audioFunc)func;
}