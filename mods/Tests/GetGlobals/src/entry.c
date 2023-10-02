#include <common.h>

void RunEntryHook()
{
	printf("\n");
	printf("\n");
	printf("\n");
	
	int num = 0;
	while(num < 3*2)
	{
		//for(int i = 0; i < 16; i++)
		{
			printf("{0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%04x, 0x%04x}\n",
				data.BossWeaponPinstripe[num].trackCheckpoint,
				data.BossWeaponPinstripe[num].throwFlag,
				data.BossWeaponPinstripe[num].weaponType,
				data.BossWeaponPinstripe[num].unk1,
				data.BossWeaponPinstripe[num].weaponCooldown,
				data.BossWeaponPinstripe[num].juiceFlag
				);
		
			num++;
		}
	}
	
	printf("\n");
	printf("\n");
	printf("\n");
}