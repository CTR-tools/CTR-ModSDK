#ifdef USE_ONLINE
#include "OnlineCTR/names3d.c"

typedef void (*VehicleFuncPtr)(struct Thread* thread, struct Driver* driver);

void RunVehicleThread(VehicleFuncPtr func, struct Thread* thread, struct Driver* driver)
{
    UpdateCheckpointTracker(driver->driverID);
    if (func == nullptr) { return; }

    bool restore = false;
    if ((sdata->gGT->gameMode1 & END_OF_RACE) && (checkpointTracker[driver->driverID].raceFinished == 0))
    {
        sdata->gGT->gameMode1 &= ~(END_OF_RACE);
        restore = true;
    }
    func(thread, driver);
    if (restore) { sdata->gGT->gameMode1 |= END_OF_RACE; }
}
#endif

#ifdef USE_ONLINE
Color HsvToRgb(int h, int s, int v)
{
    Color rgb;
	h = h & 0xFF; // modulo 256
    int region, remainder, p, q, t;

    if (s == 0)
    {
        rgb.r = v;
        rgb.g = v;
        rgb.b = v;
        return rgb;
    }

    region = h / 43;
    remainder = (h - (region * 43)) * 6;

    p = (v * (255 - s)) >> 8;
    q = (v * (255 - ((s * remainder) >> 8))) >> 8;
    t = (v * (255 - ((s * (255 - remainder)) >> 8))) >> 8;

    switch (region)
    {
        case 0:
            rgb.r = v; rgb.g = t; rgb.b = p;
            break;
        case 1:
            rgb.r = q; rgb.g = v; rgb.b = p;
            break;
        case 2:
            rgb.r = p; rgb.g = v; rgb.b = t;
            break;
        case 3:
            rgb.r = p; rgb.g = q; rgb.b = v;
            break;
        case 4:
            rgb.r = t; rgb.g = p; rgb.b = v;
            break;
        default:
            rgb.r = v; rgb.g = p; rgb.b = q;
            break;
    }

    return rgb;
}
#endif