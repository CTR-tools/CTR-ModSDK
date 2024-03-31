#include <common.h>
#include "macro.h"

struct MenuRow rowsLanguage_MM[4] = 
{
    [0] = MENU_ROW(0x51,4,6,5,5), // High score
    [1] = MENU_ROW(0x52,5,6,6,6), // Language
    [2] = MENU_ROW(-1,6,7,7,7), // Scrapbook
    [3] = FINALIZER_ROW
};