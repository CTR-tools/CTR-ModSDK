# Notes
This page is dedicated for notes/facts about the PSX, which may help you in your hacking journey.

## Retail Bios/Kernel
The first `0x10000` bytes in memory is reserved to the kernel. However, the kernel doesn't use all of its memory, so you could use some of its space to load your own code in it. Here's a table with the three biggest memory holes which are generally safe to play with:

| Start | End | Size |
| :- | :- | :- |
| 0x8000A000 | 0x8000B900 | 0x1900 |
| 0x8000C000 | 0x8000DF00 | 0x1F00 |
| 0x8000E400 | 0x80010000 | 0x1C00 |

Unirom uses a bit of the `0x8000C000` section. In my personal experience, injecting data starting at about `0x8000C400` is enough to make the mod compatible with unirom.

## ps-exe header
The playstation executable has a `0x800` bytes header, which is loaded in the retail bios/kernel at address `0x8000B070` (or `0x8000A8D0` on PS2 via backwards compatibility). However, only the first `0x4C` bytes of the header [are actually used](https://github.com/pcsx-redux/nugget/blob/main/ps-exe.ld#L53-L95), so you could exploit that fact and overwrite most of the header with your own custom code, which will be automatically installed in the kernel when the PSX tries to load the game executable. The [spyro mod example](../games/Example_SpyroRiptosRage/mods/Speedometer/) uses this exploit.