![CTR-tools](ctr-tools-logo.png)

[![GPLv2 License](https://img.shields.io/badge/License-GPL%20v2-green.svg)](https://opensource.org/licenses/GPL-2.0)
[![Discord Chat](https://img.shields.io/discord/527135227546435584.svg)](https://discord.gg/WHkuh2n)

Various tools to operate Crash Team Racing (PS1) game files.

Download latest release here: https://github.com/CTR-tools/CTR-tools/releases/latest \
Tools description: https://github.com/CTR-tools/CTR-tools/wiki/Tools-description

Join the CTR-tools Discord server: https://discord.gg/WHkuh2n

## Features
* fly around the original CTR levels in a 3D viewer, including a stereoscopic 3d mode
* extract and rebuild BIGFILE.BIG, human readable filenames and folder structure included
* extract levels in OBJ format featuring medium texture quality
* extract static models and import untextured models back in the game
* extract samples in VAG/WAV formats and music tracks in MIDI format from KART.HWL
* edit level vram textures
* edit localization files
* minor Crash Bash support: unpack CRASHBSH.DAT from various CB builds and extract textures

![CTR-tools](ctr-tools-banner.jpg)

## Building
CTR-tools is being developed in Visual Studio Community 2019.\
Target platform is .NET Framework 4.6.2 (ctrviewer is targeting .NET Core 3.1).\
It should be enough to install VS and add dependencies via NuGet.

Project dependencies:
* NAudio - https://github.com/naudio/NAudio (used to export MIDI files)
* Json.NET - https://github.com/JamesNK/Newtonsoft.Json (used for json parsing support)
* MonoGame - https://github.com/MonoGame/MonoGame (used for viewer)

## Contribution
Game research is welcome, for starters please check:
* CTR-tools wiki: https://github.com/CTR-tools/CTR-tools/wiki
* Open issues: https://github.com/CTR-tools/CTR-tools/issues

2016-2022, DCxDemo*.
