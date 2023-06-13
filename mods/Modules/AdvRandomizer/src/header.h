void MM_AdvDifficulty(struct MenuBox*);

struct MenuRow rows_advDifficulty[] = {
    [0] =
        {
            .stringIndex = 0x15a,
            .rowOnPressUp = 0,
            .rowOnPressDown = 1,
            .rowOnPressLeft = 0,
            .rowOnPressRight = 0},
    [1] =
        {
            .stringIndex = 0x15b,
            .rowOnPressUp = 0,
            .rowOnPressDown = 2,
            .rowOnPressLeft = 1,
            .rowOnPressRight = 1},
    [2] =
        {
            .stringIndex = 0x15c,
            .rowOnPressUp = 1,
            .rowOnPressDown = 3,
            .rowOnPressLeft = 2,
            .rowOnPressRight = 2},
    [3] =
        {
            .stringIndex = 0x17d,
            .rowOnPressUp = 2,
            .rowOnPressDown = 3,
            .rowOnPressLeft = 3,
            .rowOnPressRight = 3},
    [4] = {
        .stringIndex = -1,
        .rowOnPressUp = 0,
        .rowOnPressDown = 0,
        .rowOnPressLeft = 0,
        .rowOnPressRight = 0}};

struct MenuBox adv_difficulty = {
    .stringIndexTitle = 0x159,
    .posX_curr = 0,
    .posY_curr = 0,
    .unk1 = 0,
    .state = 1,
    .rows = rows_advDifficulty,
    .funcPtr = MM_AdvDifficulty,
    .width = 171,
    .height = 86};