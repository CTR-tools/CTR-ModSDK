struct Tracks
{
	char *name;
	char *file;
	char id;
};

char cove_name[] = "Crash Cove";
char cove_file[] = "\\RINGRALLY\\COVE.BIN;1";
char tubes_name[] = "Roo's Tubes";
char tubes_file[] = "\\RINGRALLY\\TUBES.BIN;1";
char caves_name[] = "Mystery Caves";
char caves_file[] = "\\RINGRALLY\\CAVES.BIN;1";
char sewer_name[] = "Sewer Speedway";
char sewer_file[] = "\\RINGRALLY\\SEWER.BIN;1";
char temple_name[] = "Tiger Temple";
char temple_file[] = "\\RINGRALLY\\TEMPLE.BIN;1";
char park_name[] = "Coco Park";
char park_file[] = "\\RINGRALLY\\PARK.BIN;1";
char papu_name[] = "Papu's Pyramid";
char papu_file[] = "\\RINGRALLY\\PAPU.BIN;1";
char cayon_name[] = "Dingo Cayon";
char cayon_file[] = "\\RINGRALLY\\CAYON.BIN;1";
char bluff_name[] = "Blizzard Bluff";
char bluff_file[] = "\\RINGRALLY\\BLUFF.BIN;1";
char mines_name[] = "Dragon Mines";
char mines_file[] = "\\RINGRALLY\\MINES.BIN;1";
char pass_name[] = "Polar Pass";
char pass_file[] = "\\RINGRALLY\\PASS.BIN;1";
char tiny_name[] = "Tiny Arena";
char tiny_file[] = "\\RINGRALLY\\TINY.BIN;1";
char labs_name[] = "N. Gin Labs";
char labs_file[] = "\\RINGRALLY\\LABS.BIN;1";
char castle_name[] = "Cortex Castle";
char castle_file[] = "\\RINGRALLY\\CASTLE.BIN;1";
char has_name[] = "Hot Air Skyway";
char has_file[] = "\\RINGRALLY\\HAS.BIN;1";
char os_name[] = "Oxide Station";
char os_file[] = "\\RINGRALLY\\OS.BIN;1";
char slide_name[] = "Slide Coliseum";
char slide_file[] = "\\RINGRALLY\\SLIDE.BIN;1";
char turbo_name[] = "Turbo Track";
char turbo_file[] = "\\RINGRALLY\\TURBO.BIN;1";

struct Tracks tracks[] =
{
	[0] =
	{
		.name = cove_name,
		.file = cove_file,
		.id = 3,
	},

	[1] =
	{
		.name = tubes_name,
		.file = tubes_file,
		.id = 6,
	},

	[2] =
	{
		.name = caves_name,
		.file = caves_file,
		.id = 9,
	},

	[3] =
	{
		.name = sewer_name,
		.file = sewer_file,
		.id = 8,
	},

	[4] =
	{
		.name = temple_name,
		.file = temple_file,
		.id = 4,
	},

    [5] =
    {
        .name = park_name,
        .file = park_file,
        .id = 14,
    },

    [6] =
    {
        .name = papu_name,
        .file = papu_file,
        .id = 5,
    },

    [7] =
    {
        .name = cayon_name,
        .file = cayon_file,
        .id = 0,
    },

    [8] =
    {
        .name = bluff_name,
        .file = bluff_file,
        .id = 2,
    },

    [9] =
    {
        .name = mines_name,
        .file = mines_file,
        .id = 1,
    },

    [10] =
    {
        .name = pass_name,
        .file = pass_file,
        .id = 12,
    },

    [11] =
    {
        .name = tiny_name,
        .file = tiny_file,
        .id = 15,
    },

    [12] =
    {
        .name = labs_name,
        .file = labs_file,
        .id = 11,
    },

    [13] =
    {
        .name = castle_name,
        .file = castle_file,
        .id = 10,
    },

    [14] =
    {
        .name = has_name,
        .file = has_file,
        .id = 7,
    },

    [15] =
    {
        .name = os_name,
        .file = os_file,
        .id = 13,
    },

    [16] =
    {
        .name = slide_name,
        .file = slide_file,
        .id = 16,
    },

    [17] =
    {
        .name = turbo_name,
        .file = turbo_file,
        .id = 17,
    }
};