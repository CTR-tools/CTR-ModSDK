#include <common.h>

int DECOMP_MEMCARD_IsFile(int slotIdx, char *save_name)
{
    char name[64];

    MEMCARD_StringSet(name, slotIdx, save_name);

	// This temporary FD will not be saved,
	// The global FD will always be wiped
	int fd;
	sdata->memcard_fd = -1;

    fd = open(name, FASYNC|FWRITE);

    if (fd != -1)
	{
		close(fd);
		return MC_RETURN_IOE;
	}

	return MC_RETURN_NODATA;
}