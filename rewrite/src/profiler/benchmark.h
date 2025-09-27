
void RunTest_RW_COLL_ProjectPointToEdge()
{
	// Sample input from no$psx
	// $a0: 1f800154 - 0, 0, 0
	// $a1: 1f800270 - 0000, 032A, EDE4
	// $a2: 1f800220 - FD00, 02EC, EA58
	// $a3: 1f800164 - FD6F, 02F5, EDCE
	SVec3 out = {};
	SVec3 v1 = {0x0, 0x32A, 0xEDE4};
	SVec3 v2 = {0xFD00, 0x2EC, 0xEA58};
	SVec3 point = {0xFD6F, 0x2F5, 0xEDCE};
	
	// million
	for(int i = 0; i < 1000000; i++)
	{
		COLL_ProjectPointToEdge(&out, &v1, &v2, &point);
	}
}

void RunTest_ND_COLL_ProjectPointToEdge()
{
	// Sample input from no$psx
	// $a0: 1f800154 - 0, 0, 0
	// $a1: 1f800270 - 0000, 032A, EDE4
	// $a2: 1f800220 - FD00, 02EC, EA58
	// $a3: 1f800164 - FD6F, 02F5, EDCE
	SVec3 out = {};
	SVec3 v1 = {0x0, 0x32A, 0xEDE4};
	SVec3 v2 = {0xFD00, 0x2EC, 0xEA58};
	SVec3 point = {0xFD6F, 0x2F5, 0xEDCE};
	
	// Revert the Hook from OG -> DECOMP
	PatchFunction_Beg((u32*)(&ND_COLL_ProjectPointToEdge));
	
	// million
	for(int i = 0; i < 1000000; i++)
	{
		ND_COLL_ProjectPointToEdge(&out, &v1, &v2, &point);
	}
}

// Always run RW (rewrite) before OG (original)
struct BenchTest tests[] =
{
	ADDTEST(RunTest_RW_COLL_ProjectPointToEdge),
	ADDTEST(RunTest_ND_COLL_ProjectPointToEdge)
};