# PSX Modding Toolchain
The goal of this project is to provide a set of tools for PSX developers in order to make modding and reverse engineering games easier, while using modern non-proprietary software.

Watch the demo:
[![video](https://imgur.com/Mdqs9JH.jpg)](https://www.youtube.com/watch?v=-AE4QKrx5uY)

## Features
* Compile, playtest and build an ISO in just a few clicks;
* Compile C code into multiple overlays, targetting any PSX RAM address;
* Test your changes in game during runtime;
* Replace game textures using custom images;
* Automatic rebuild a PSX iso with your own modifications.
* Generate xdelta patches to easily distribute your ROM hacks. You can apply xdelta patches using this [web application](https://kotcrab.github.io/xdelta-wasm/)

To discuss PSX development, hacking, and reverse engineering in general, please join the PSXDev Network Discord server: [![Discord](https://img.shields.io/discord/642647820683444236)](https://discord.gg/QByKPpH)

## Pre requisites
```
python 3+
```
Note: some python instalations might be incomplete. Make sure that you have installed `python`, `pip` and add them to your `PATH`.

Open the command prompt and install the dependencies:
```
pip install requests
pip install opencv-python
```

## Getting Started
#### Clone this repository:
```
$ git clone https://github.com/mateusfavarin/psx-modding-toolchain.git
```
Note: don't use whitespaces in the folder names. This will break the `make` script.
#### Install the mipsel GCC toolchain:
##### Windows:
Copy-paste the following into a command prompt:
```
powershell -c "& { iwr -UseBasicParsing https://raw.githubusercontent.com/grumpycoders/pcsx-redux/main/mips.ps1 | iex }"
```
Then, open a new command prompt, and type the following:
```
mips install 12.1.0
```
As an alternative, you can download the toolchain directly [here](https://static.grumpycoder.net/pixel/mips/g++-mipsel-none-elf-12.1.0.zip), and then add the `bin/` folder to your `PATH`.

##### Linux
Compile the latest version of gcc `mipsel-none-elf` using [this script](https://github.com/grumpycoders/pcsx-redux/tree/main/tools/linux-mips), or download the pre-compiled binaries [here](https://drive.google.com/file/d/1VTCPRpriwPS5wkLVeDfx5dAXzUB1gAoa/view?usp=share_link). Make sure that you added the `bin/` folder to your `$PATH`.

##### MacOS
You'll need [brew](https://brew.sh/), and then run:
```
brew install ./tools/macos-mips/mipsel-none-elf-binutils.rb
brew install ./tools/macos-mips/mipsel-none-elf-gcc.rb
```

#### PCSX-Redux
PCSX-Redux is a PSX emulator heavily focused on development, debuggability, and reverse engineering. This project uses Redux's web server in order to connect the PSX modding toolchain to the emulator, allowing the developer to seamlessly hot-reload code while playing the game and update the emulator debugger symbols during runtime.

In order to setup the emulator, you'll need to download [PCSX-Redux](https://github.com/grumpycoders/pcsx-redux/#where) and change the following settings under the `configuration/emulation` tab:

```
[ ] Dynarec CPU # Leave this unchecked
[ ] 8MB # Optional
[x] Enable Debugger
[x] Enable GDB Server
[x] Enable Web Server
```

#### Mkpsxiso
Mkpsxiso is an ISO disc image maker written specifically for PlayStation development. This project uses Mkpsxiso in order to automate the process of overwriting existing data and adding new game files to the disc.

You can download the latest release [here](https://github.com/Lameguy64/mkpsxiso/releases), and then set the `bin/` folder to your `PATH`.

#### NoPS
NotPSXSerial, or NoPS for short, is a Serial/TTY suite for Unirom 8 featuring kernel-resident debugging, cart/EEPROM flasher, .exe/.elf upload, memcard tools, peeks, pokes, dumps and bugs. This project is integrates NoPS in order to hot-reload code directly in your PS1.

You can download the latest release of Unirom [here](https://github.com/JonathanDotCel/unirom8_bootdisc_and_firmware_for_ps1/releases), and then set the NoPS folder to your `PATH`.

#### Usage
Check the [docs](docs/) for information about configuring and using the tools.

If you're interested in decompiling a game, you might be interested in checking out [this](games/Example_CrashTeamRacing/mods/DecompUnitTester/README.md) real time function unit tester.