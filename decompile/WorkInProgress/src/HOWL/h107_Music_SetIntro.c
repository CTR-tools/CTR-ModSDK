#include <common.h>

void Music_SetIntro(void)
{
    u_int boolSuccess;
    struct Bank thisBank;

    DAT_8008d834 = 0;

    Bank_Load(33, &thisBank);

    do
    {
        boolSuccess = Bank_AssignSpuAddrs();
    } while (boolSuccess == 0);
    howl_SetSong(28);
    do
    {
        boolSuccess = howl_LoadSong();
    } while (boolSuccess == 0);
}