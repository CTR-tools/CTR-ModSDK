# 60 fps
A 60 fps conversion patch for Crash Team Racing. An overclock of at least 4x is required. Made by Niko.

## Changes
### Fully functional
* Main menu transition speed between menus
* Spinning drivers in character selection
* Transition between drivers
* Armadillo on Dingo Canyon (mostly)
* Seal on polar pass
* Minecart on Dragon Mines
* TNT Weapon duration + honking
* Hot Air Skyway blimp blades
* Tiger Temple Flamejet
* Blizz Bluff + Sewer Speedway "snowball" (mostly)
* N Gin Labs "baron" (mostly)
* Weapon Roulette (duration)
* Bomb weapon (spinning)
* Aku Aku mask weapon and grab, spinning + scale
* Shiled weapon (duration)
* Wumpa and Crystal 3D items and 2D hud
* C-T-R letters 3D items and 2D hud
* Adv Hub opening hub doors (all but one transition fixed)
* Warppads (all fixed except electric field)
* Boss garage open/close
* Adv Hub HUD 3D items spinning
* Driver physics: drift, spinout, reserves, boost
* Race start line: camera animation, engine revving, etc
* Relic Race: "tick" sound when breaking boxes is correct
* Missile beeping
* "FINAL LAP!" fly-in / fly-out text
* HUD linear interoplation (grabbing wumpa fruit, crystal, etc)
* Wumpa crate does not spam you the wumpa

### Semi-functional
* Particles are patched emitter-by-emitter, 231 emitters unpatched, should patch Particles_UpdateLists
* Texture scrolling (turbo, waterfall, etc) run at 30fps
* Bosses dont constantly spam weapons, but it's still not right
* When opening Adv Hub door with key, zoom out should take 2 sec, not 1 sec
* Blizzard Bluff + Sewer Speedway update hazards at 30fps
* N Gin Labs barrel hazard runs at 30fps
* Weapon roulette flashes too fast, but duration is correct
* Shiled weapon shakes too much
* Entering warp pad sometimes works right, and sometimes throws player upward
* Blinking map UI, partly fixed and partly abandoned
* AI animations
* Player reverse, crash, jump animation
* Spiders have a slightly-off cycle

## Known issues
* Animations are half-working, half-fix
* Flashing colors for player icons are too fast
* Demo Mode only lasts half-time (even though it "should" be fixed???)
* UI highlight (red/yellow) in menus is too fast
* Demo Mode / End-Of-Race cameras sometimes are too fast
* Adventure Garage camera is too fast
* Adventure Hub Warp pad electric field
* Lots of flashing text is flashing too fast
* At end of Time Trial / Relic, high scores disappear halfway off-screen
* AI acceleration from starting line
* Screen fade transitions (fade to black, fade to white, etc.)
* Red potion (fix disabled, freezes game)
* Bubble particles fail to be culled by water surface (hits the top of the screen)
* Still can't skip weapon roulette by pressing circle
* Wumpa gets collected too quickly (code for this is in DrawHUD_Racing)

## Changelog
### Nov 2021 changes
* Steering animation is fixed for players
* Papu Pyramid Plants fixed
* Armadillo animations fixed
* Turtle animations fixed
* Podium Prize fixed
* Tiger Temple teeth fix
* Aku Hints spawn fix
* Item roll skip 2.3s fix
* waving CTR flag
* Jump Buffers (time trial froggy)
* Fixed crashing when hitting some hazards

### Sep 2022 changes
* 7 frames of fire
* main menu track videos
* SCVert is fixed on Roo's Tubes
* OVert is fixed on Crash Cove (1P only)
* particle changes (mentioned in "need work")
* improve PatchModel so cutscenes dont break
* waving checkered flag and "loading..." text
* Intro animation of crash throwing trophy
* AdvPause spin rate of items
* armadillo spawn cooldown
* spiders are "improved", not fully fixed
* save/load scaline "improved", not perfect