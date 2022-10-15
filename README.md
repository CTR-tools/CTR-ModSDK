# CTR-ModSDK

*ModSDK*. *(noun)* A toolkit that allows you to create mods for Crash Team Racing (1999) in C.

[![Contributors][contributors-badge]][contributors-link] [![Discord Server][discord-badge]][discord]

[contributors-link]: https://github.com/CTR-Tools/CTR-ModSDK/graphs/contributors
[contributors-badge]: https://img.shields.io/github/contributors/CTR-Tools/CTR-ModSDK

[discord]: https://discord.gg/WHkuh2n
[discord-badge]: https://img.shields.io/discord/527135227546435584?color=%237289DA&logo=discord&logoColor=ffffff

This repository also houses an effort to fully decompile and reverse-engineer [CTR in C.](https://github.com/CTR-tools/CTR-ModSDK#CTR-in-C)

# 📃 Features

- Extract and build ISO in few steps
- Supports all retail versions and two prototypes
- Compile C code into any address and overlay
- Integrated Xdelta patch generation
- Hot Swap: Load code replacements while the game is running

# 🏁 How to Start Modding

## Requirements

- [python 3+](https://github.com/PackeTsar/Install-Python)
- Open command prompt (CMD/Terminal) and install the dependencies:
```
pip install requests
pip install opencv-python
```

## Downloading the SDK

Clone this repository:

```
$ git clone https://github.com/CTR-Tools/CTR-ModSDK.git
```

- You can find [example mods](https://github.com/CTR-tools/CTR-ModSDK/tree/main/psx-modding-toolchain/games/CrashTeamRacing/mods) in our repo.
- Each mod folder includes a `readme.txt` file on what the mod does and how to use it. 
- To build a mod, simply run `build.bat` in the mod folder.

# CTR-in-C

Work-in-progress project to decompile Crash Team Racing into human-readable C code.

[![Decompile Overview](https://img.youtube.com/vi/V9QlFzSVDAU/hqdefault.jpg)](https://www.youtube.com/watch?v=V9QlFzSVDAU)

## 📊 Progress
### Research and Decompilation

Decompiling the assembly assisted by Ghidra, researching how it works and adding comments for guidelines.

![](https://progress-bar.dev/97/?width=300&title=USA&suffix=%%20done)

### Code Rewrite

Rewriting Ghidra output to human-readable C Code and testing if it matches.
Most of the source code are shared between versions.

- ![](https://progress-bar.dev/92/?scale=1171&width=300&title=USA&suffix=%20functions%20out%20of%201171*)
- ![](https://progress-bar.dev/22/?scale=1171&width=300&title=PAL&suffix=%20functions%20out%20of%201200*)
- ![](https://progress-bar.dev/94/?scale=1171&width=300&title=JPN&suffix=%20functions%20out%20of%201200*)

\* These are not accurate numbers and subject to change.

## 🤝 Contributing

Are you interested in contributing? Have any experience in C programming language? You're welcome to join!

Get in touch with us through our [Discord server](https://discord.gg/WHkuh2n) or you can directly look at our [decompile directory](https://github.com/CTR-tools/CTR-ModSDK/tree/main/psx-modding-toolchain/games/CrashTeamRacing/decompile). 
