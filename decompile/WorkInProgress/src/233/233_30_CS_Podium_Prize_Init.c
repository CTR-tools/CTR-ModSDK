#include <common.h>

#define gte_ldVXY0(r0) __asm__ volatile("mtc2   %0, $0" \
                                        :               \
                                        : "r"(r0))
#define gte_ldVZ0(r0) __asm__ volatile("mtc2   %0, $1" \
                                       :               \
                                       : "r"(r0))

#define read_mt(r0, r1, r2) __asm__ volatile( \
    "mfc2   %0, $25;"                         \
    "mfc2   %1, $26;"                         \
    "mfc2   %2, $27;"                         \
    :                                         \
    : "r"(r0), "r"(r1), "r"(r2))

void CS_Podium_Prize_Init(int prizeModel, char* prizeName, short *posOnScreen)
{
    u_int relicColor;
    u_int prizeFlag;
    int tx;
    int ty;
    int tz;

    short *prize;

    struct GameTracker *gGT = sdata->gGT;

    // create thread, get instance
    // 0x200 flag = MediumStackPool
    // 0xd = "other" thread bucket
    struct Instance *inst = INSTANCE_BirthWithThread(prizeModel, prizeName, MEDIUM, OTHER, CS_Podium_Prize_ThTick1, 0x2c, 0);

    if (inst == NULL)
    {
        if (OVR_233.cutsceneState < 1)
        {
            OVR_233.cutsceneState = 1;
        }

        // driver now can move
        gGT->gameMode2 &= ~(4);
        return;
    }

    // set scale (x, y, z)
    inst->scale[0] = 0x2000;
    inst->scale[1] = 0x2000;
    inst->scale[2] = 0x2000;

    // make invisible
    inst->flags |= HIDE_MODEL;

    // get object from thread
    prize = inst->thread->object;

    inst->thread->funcThDestroy = CS_Podium_Prize_ThDestroy;

    prize[0x11] = 0x40;
    prize[0x12] = 0x200;

    prize[4] = 0;
    prize[5] = 0;
    prize[6] = 0;

    gte_ldVXY0(0);
    gte_ldVZ0(0x40);
    gte_llv0();

    read_mt(tx, ty, tz);

    // pos x, y and z
    prize[0] = posOnScreen[0] + (short)tx;
    prize[1] = posOnScreen[1] + (short)ty + 0x1c0;
    prize[2] = posOnScreen[2] + (short)tz;

    prize[10] = -0x200;

    struct UiElement2D *hud = data.hudStructPtr[0];

    switch (prizeModel)
    {

    // if reward is [empty], used for Oxide Podium
    case STATIC_BIG1:

        // make invisible
        inst->flags |= HIDE_MODEL;

        goto GEMS_OR_NOTHING;

    // if reward is gem
    case STATIC_GEM:

        // get color of the gem based off the cup ID
        short *gemColor = &data.AdvCups[gGT->cup.cupID].color;

        inst->colorRGBA = (gemColor[0] << 20 | gemColor[1] << 12 | gemColor[2] << 4);

        prize[12] = 0x5d3;
        prize[13] = 0x718;
        prize[14] = 0x590;
        prize[15] = 0x609;

        // specular lighting
        inst->flags |= USE_SPECULAR_LIGHT;

    default:
    GEMS_OR_NOTHING:
        prize[8] = 0x100;
        prize[9] = 0x6c;
        return;

    // if reward is relic
    case STATIC_RELIC:

        prize[8] = *(short *)(hud + 0x70);
        prize[9] = *(short *)(hud + 0x72) - 60;

        // previous levID, + 0x3a (0x3a is first bit of platinum relic)
        u_int bitIndex = gGT->prevLEV + 0x3a;
        u_int * rewards = &sdata->advProgress.rewards[0];

        // if you have not earned a platinum relic on this track
        if (CHECK_ADV_BIT(rewards,bitIndex) == 0)
        {
            // previous levID, + 0x28 (0x2a is the first bit of gold relic)
            bitIndex = gGT->prevLEV + 0x28;

            // if you have not earned a gold relic on this track
            if (CHECK_ADV_BIT(rewards,bitIndex) == 0)
            {
                // sapphire color
                relicColor = 0x20a5ff0;
            }

            // if you earned a gold relic on this track
            else
            {
                // gold color
                relicColor = 0xd8d2090;
            }
        }

        // if you earned a platinum relic on this track
        else
        {
            // platinum color
            relicColor = 0xffede90;
        }

        // set color of relic
        inst->colorRGBA = relicColor;

        prize[12] = 0x2ab;
        prize[13] = 0x436;
        prize[14] = 0x1eb;
        prize[15] = 0x670;

        // specular lighting
        inst->flags |= USE_SPECULAR_LIGHT;

        prizeFlag = INC_RELIC;
        break;

    // if reward is trophy
    case STATIC_TROPHY:
        prize[8] = *(short *)(hud + 0x80);
        prize[9] = *(short *)(hud + 0x82) - 60;
        prize[10] = -200;

        // set scale (x, y, z)
        inst->scale[0] = 0x4000;
        inst->scale[1] = 0x4000;
        inst->scale[2] = 0x4000;

        prizeFlag = INC_TROPHY;
        break;

    // if reward is key
    case STATIC_KEY:
        prize[8] = *(short *)(hud + 0x78);
        prize[9] = *(short *)(hud + 0x7a) - 60;

        inst->colorRGBA = 0xdca6000;
        prize[12] = 0x1d9;
        prize[13] = 0x5db;
        prize[14] = 0x2da;
        prize[15] = 0x54b;

        // specular lighting
        inst->flags |= USE_SPECULAR_LIGHT;
        prizeFlag = INC_KEY;
    }

    gGT->gameMode2 |= prizeFlag;
}