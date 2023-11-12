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

#define ROW_ENGLISH 0
#define ROW_FRENCH 1 
#define ROW_GERMAN 2
#define ROW_ITALIAN 3
#define ROW_SPANISH 4
#define ROW_DUTCH 5
