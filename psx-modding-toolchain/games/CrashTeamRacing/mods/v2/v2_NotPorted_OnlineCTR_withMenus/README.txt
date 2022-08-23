For a project this insane, we need
an entirely custom environment that
builds off the main environment

SYSTEM.CNF is rigged to set $sp
807FFFF0, 8mb RAM required for this,

In the end, just throw all code in EXE
	
	BL_Injections is temporary
	Loads at 80600000

	OV_GameCode is temporary
	Loads at 80700000

221-225 and 230-233 do not load,
this is an empty hole of data

"tools" is needed for new psyq ini

OV loaded from BL, rigged to 0x80000 bytes max,
this hurts performance, fine-tune it later

apploader.c, should be moved from BL loader to BL code
apploader.c is also hard-coded to SCUS_944.26;1

MenuBox_Show called from BL