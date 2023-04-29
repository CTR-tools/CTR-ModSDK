Flying camera mode with no visible drivers

Supports all builds

Works best in 1P modes, not designed for multiplayer
This will break "Oxide Intro" cutscene, but that can be fixed

Tried to save performance by wiping player threads in Init instead
of Update, but if player gets blasted then you need to restart the 
race, might put that back in Update later

The mod makes the driver invisible, then moves the driver, which
automatically updates the frustum, when a quadblock is under the
driver that contains visibility information. Might make a smarter
solution later

Made by Niko.