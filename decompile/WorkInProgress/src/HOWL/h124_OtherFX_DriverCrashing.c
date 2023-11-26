#include <common.h>

void OtherFX_DriverCrashing(u_int boolEcho, u_int volume)
{
    u_int crashID;

    // three different collision sounds (10, 11, 12)
    // based on volume

    if (volume < 221) {

        crashID = (volume > 160) ? 12 : 11;
        
    } else {
        crashID = 10;
    }

    // three different crashing FXs

    OtherFX_Play_LowLevel
    (
        // sound ID
        crashID, 0,

        // echo
        boolEcho << 0x18 |

        (volume & 0xff) << 0x10 |

        // no distortion, balance L/R
        0x8080
    );
}