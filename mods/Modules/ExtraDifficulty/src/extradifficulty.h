#define MENU_ROW(NAME, STRING_INDEX, UP, DOWN, LEFT, RIGHT) \
    [NAME] = { \
        .stringIndex = STRING_INDEX, \
        .rowOnPressUp = UP, \
        .rowOnPressDown = DOWN, \
        .rowOnPressLeft = LEFT, \
        .rowOnPressRight = RIGHT \
    }

#define FINALIZER_ROW \
    { \
        .stringIndex = -1, \
        .rowOnPressUp = 0, \
        .rowOnPressDown = 0, \
        .rowOnPressLeft = 0, \
        .rowOnPressRight = 0 \
    }

#define ROW_EASY 0
#define ROW_MEDIUM 1
#define ROW_HARD 2
#define ROW_SUPER_HARD 3
#define ROW_ULTRA_HARD 4
#define EXD_VALID_ROWS 5

struct MenuRow rows_extraDifficulty[] =
{
    MENU_ROW(ROW_EASY, 346, ROW_EASY, ROW_MEDIUM, ROW_EASY, ROW_EASY),
    MENU_ROW(ROW_MEDIUM, 347, ROW_EASY, ROW_HARD, ROW_MEDIUM, ROW_MEDIUM),
    MENU_ROW(ROW_HARD, 348, ROW_MEDIUM, ROW_SUPER_HARD, ROW_HARD, ROW_HARD),
    MENU_ROW(ROW_SUPER_HARD, 588, ROW_HARD, ROW_ULTRA_HARD, ROW_SUPER_HARD, ROW_SUPER_HARD),
    MENU_ROW(ROW_ULTRA_HARD, 589, ROW_SUPER_HARD, ROW_ULTRA_HARD, ROW_ULTRA_HARD, ROW_ULTRA_HARD),
    FINALIZER_ROW
};

struct MenuBox extra_difficulty =
{
    .stringIndexTitle = 345,
    .posX_curr = 0,
    .posY_curr = 0,
    .unk1 = 0,
    .state = CENTER_ON_X | USE_SMALL_FONT | BIG_TEXT_IN_TITLE,
    .rows = rows_extraDifficulty,
    .funcPtr = MM_ExtraDifficulty,
    .width = 171,
    .height = 86
};