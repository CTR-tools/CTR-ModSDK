
// PPTE = ProjectPointToEdge
// RW = Rewrite
// ND = Naughty Dog (original)
// STACK = $sp memory
// SCRATCH = scratchpad

void RunTest_RW_COLL_PPTE_STACK()
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
	
	// 100,000
	for(int i = 0; i < 100000; i++)
	{
		COLL_ProjectPointToEdge(&out, &v1, &v2, &point);
	}
	
	ND_printf("Done\n");
}

void RunTest_ND_COLL_PPTE_STACK()
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
	
	// 100,000
	for(int i = 0; i < 100000; i++)
	{
		ND_COLL_ProjectPointToEdge(&out, &v1, &v2, &point);
	}
	
	ND_printf("Done\n");
}

void RunTest_RW_COLL_PPTE_SCRATCH()
{
	SVec3* out = (SVec3*)0x1f800154;
	SVec3* v1 = (SVec3*)0x1f800270; //{0x0, 0x32A, 0xEDE4};
	SVec3* v2 = (SVec3*)0x1f800220; //{0xFD00, 0x2EC, 0xEA58};
	SVec3* point = (SVec3*)0x1f800164; //{0xFD6F, 0x2F5, 0xEDCE};
	
	out->v[0] = 0;
	out->v[1] = 0;
	out->v[2] = 0;
	
	v1->v[0] = 0x0;
	v1->v[1] = 0x32A;
	v1->v[2] = 0xEDE4;
	
	v2->v[0] = 0xFD00;
	v2->v[1] = 0x2EC;
	v2->v[2] = 0xEA58;
	
	point->v[0] = 0xFD6F;
	point->v[1] = 0x2F5;
	point->v[2] = 0xEDCE;
	
	// 100,000
	for(int i = 0; i < 100000; i++)
	{
		COLL_ProjectPointToEdge(out, v1, v2, point);
	}
	
	ND_printf("Done\n");
}

void RunTest_ND_COLL_PPTE_SCRATCH()
{
	SVec3* out = (SVec3*)0x1f800154;
	SVec3* v1 = (SVec3*)0x1f800270; //{0x0, 0x32A, 0xEDE4};
	SVec3* v2 = (SVec3*)0x1f800220; //{0xFD00, 0x2EC, 0xEA58};
	SVec3* point = (SVec3*)0x1f800164; //{0xFD6F, 0x2F5, 0xEDCE};
	
	out->v[0] = 0;
	out->v[1] = 0;
	out->v[2] = 0;
	
	v1->v[0] = 0x0;
	v1->v[1] = 0x32A;
	v1->v[2] = 0xEDE4;
	
	v2->v[0] = 0xFD00;
	v2->v[1] = 0x2EC;
	v2->v[2] = 0xEA58;
	
	point->v[0] = 0xFD6F;
	point->v[1] = 0x2F5;
	point->v[2] = 0xEDCE;
	
	// 100,000
	for(int i = 0; i < 100000; i++)
	{
		ND_COLL_ProjectPointToEdge(out, v1, v2, point);
	}
	
	ND_printf("Done\n");
}

// 15720 = 1 second
// Note: Every test MUST be less than 4 seconds,
// because after 65535, the counter resets itself

// Always run RW (rewrite) before OG (original)
struct BenchTest tests[] =
{
	ADDTEST(RunTest_RW_COLL_PPTE_STACK),
	ADDTEST(RunTest_ND_COLL_PPTE_STACK),
	ADDTEST(RunTest_RW_COLL_PPTE_SCRATCH),
	ADDTEST(RunTest_ND_COLL_PPTE_SCRATCH),
};