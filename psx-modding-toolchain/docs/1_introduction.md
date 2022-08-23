# Introduction
This page is designed to teach people how to install and play PSX mods, assuming you already followed all the [setup](../README.md#getting-started) process. The next pages will describe how to set up your environment for developing.

## Basic usage
Go to your desired mod folder, double click `MOD.BAT`. This invokes the main python application which is responsible for automating all the process. This project comes with 3 simple mods as examples, two for the game Crash Team Racing (cross-version mods) and one for the NTSC-U release of Spyro 2: Ripto's Rage.

## Folder structure
This project uses a specific folder structure in order to look for components during execution. You must follow this structure in order to use this toolchain.
```
.psx-modding-toolchain
├──docs/
├──games/
      ├──game1/
            ├──build/
            ├──include/
            ├──mods/
                ├──mod1/
                    ├──src/
                    ├──buildList.txt
                    ├──MOD.BAT
                ├──mod2/
                    ├──...
            ├──symbols/
            ├──config.json
            ├──disc.json
      ├──game2/
            ├──...
      ├──settings.json
      ├──common.mk
├──tools/
    ├──gcc-psyq-converted/
                ├──include/
                ├──lib/
    ...
```

## Compiling
In order to play a mod, the first thing you need to do is hit the compiler button.

The tool will look for the `buildList.txt`, which contains a declaration of what files to compile and how to compile them. During the compilation process, several files will be created. The `output/` folder will contain `.bin` files which corresponds to the code that you compiled. The `debug/` folder contains useful debugging information, such as linker map files and `.elf` files. The `backup/` folder will contain saved information for uninstalling mods which you hot-reloaded.

## Building an ISO
Place your iso in the `games/game/build/` folder, rename your iso to match the same name as the iso specified in `games/game/config.json`, then run the `Build ISO` command.

Note: during the building process, all new files will be renamed to upper case files.

## Hot Reloading
Edit the file `games/settings.json` with your redux port and/or NoPS comport, then run the hot reload command during the game. This will stop the game, inject mod code, and then resume the game running the newly injected code.

Note: you can only uninstall a mod if you select the backup option during the hot reload.
Note/NoPS: you may need to launch your game via unirom in debug mode in order to hot-reload code in your PSX.

## Texture Replacement
Edit the file `games/settings.json` with your redux port, place your images in the folder `newtex` as specified in [notes](3_notes.md), and then run the texture replacement command. This command will convert your image to the RGB5551 format, and then inject in the specified VRAM address.

## Clean Commands
* `Clean`: cleans all the files generated during the compilation process, as well as the output of texture replacement.
* `Clean Build`: cleans all the files generated during the iso building process, except the iso extraction files.
* `Clean All`: runs `Clean` and `Clean Build`, as well as cleans all the files created in the iso extraction process.