This was found in the June 1999 prototype,
it has been adjusted to work in any build of the game,
and we plan to improve it (menu UI, ghosts, etc)

JalHook is injected at approximately 
"Draw NPC-105 wheel" - 0x44, not same for every build

This hook overwrites JAL DrawOTag,
then parses all PrimMem and OTMem, and manipulates the
screen-space primitives to be closer to the screen's midpoint.
This allows us to view outside the frustum. At the end of the
function, DrawOTag is called, completing the JAL hook