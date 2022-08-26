Disable HUD
*(char*)(CAM_FollowDriver_Normal + 0xF7C) = 0;

Addresses are hardcoded in compileList, but they're
all the same offset from that function, except for Sep3,
which is same function but different address

Made by Niko (?)