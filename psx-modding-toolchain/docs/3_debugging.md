# Debugging: GDB Setup for VSCode
This page is a tutorial on how to setup your VSCode to debug your code using a GDB bridge with PCSX-Redux.

Note: this method of debugging is only useful for the code that you compiled. If you want to debug the game assembly that you haven't decompiled, then you'll have to fallback to Redux's interval MIPS debugger.

# Redux Configuration
In `Configuration -> Emulation`, make sure to select `Enable GDB Server`. Reboot the emulator if it's your first time enabling it.

# GDB Setup

### Windows
Download the pre-compiled binaries [here](https://static.grumpycoder.net/pixel/gdb-multiarch-windows/), then add `gdb-multiarch/bin` to your `PATH`.

### GNU/Linux
Download `gdb-multiarch` using your preferred package manager.

# VSCode Setup
* Download the `Native debug` extension
![image](https://pcsx-redux.consoledev.net/images/vscode_native_debug.png)

* Copy the sample [launch.json](../tools/vscode/launch.json) to your `.vscode` folder.
* Change the `executable` parameter in the `launch.json` to be the path of your mod elf file.

# Run
Inject your mod in redux, then simply run your GDB configuration in VSCode. You should be able to place breakpoints in your mod code and debug your program.
![image](https://i.imgur.com/rRDFfDe.png)