
/*
I'll just dump notes here, copy/paste from discord:

Alternatively, we can overwrite 231, everything from ShieldDark to the 
last byte of ClosestTracker, giving us 0x2EA8 bytes, 

which is 995 rings (55 per track) without any compression by using 12-byte rings
or 1327 rings (73 per track) with manual bit compression (9-byte rings) 

We can also replace the 232 overlay with a 231-replica that has different ring data
Then we put half in 231, half in 232, half the rings in one, half in the other

then we get 2000 rings (110 per track) with 0xC-byte rings, 
or 2600 rings (140 per track) with 9-byte rings
*/

// 0x9 bytes per ring
struct RingData
{
	int posX;
	int posY;
	int posZ;
	
	// compressed, divide every rotation by four,
	// (00 - 100) * 4 = (00 - 400) (0 - 90 degrees),
	short rot;
	
	// 3 bits, 8 possible models to choose from
	unsigned char modelIndex;
};


enum RingIndex
{
	CocoPark_BASE=0,
	CocoPark_NUM=9,
	
	// continue pattern like this
	NextTrack_BASE=	CocoPark_BASE + CocoPark_NUM,
};