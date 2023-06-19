#define MENU_ROW(STRING_INDEX, UP, DOWN, LEFT, RIGHT) \
    {                                                 \
        .stringIndex = STRING_INDEX,                  \
        .rowOnPressUp = UP,                           \
        .rowOnPressDown = DOWN,                       \
        .rowOnPressLeft = LEFT,                       \
        .rowOnPressRight = RIGHT                      \
    }

#define FINALIZER_ROW        \
    {                        \
        .stringIndex = -1,   \
        .rowOnPressUp = 0,   \
        .rowOnPressDown = 0, \
        .rowOnPressLeft = 0, \
        .rowOnPressRight = 0 \
    }

#define ROW_EASY 0
#define ROW_MEDIUM 1
#define ROW_HARD 2
#define ROW_SUPER_HARD 3
#define ROW_ULTRA_HARD 4

#define ROW_ADV_CLASSIC 0
#define ROW_ADV_EASY 1
#define ROW_ADV_MEDIUM 2
#define ROW_ADV_HARD 3
#define ROW_ADV_SUPER_HARD 4
#define ROW_ADV_ULTRA_HARD 5