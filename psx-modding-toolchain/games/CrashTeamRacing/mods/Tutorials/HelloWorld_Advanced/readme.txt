Draws a "Hello World" line of text on the bottom left corner of the screen.

Supports all builds

Unlike previous Hello World, this sample works
in the LOADING... screen, and prints on every 
frame, as long as text is valid in memory. For
invalid frames, the text flickers in LOADING...
screen for half a second

The OT trickery is copy/paste from the game's
"LOADING..." text, which asserts that our text
is always on top of every other draw. Otherwise
our text draws behind the checkered flag