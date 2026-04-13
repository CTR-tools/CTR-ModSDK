## What do these three folders mean?

TLDR:
* `decompile` was our first attempt at decompiling CTR. It's still used for mods, but work on the `rewrite` is preferred
* `rewrite` is our second attempt at decompiling CTR. It has better code standards, and has been more rigorously tested.
* `matching` is an attempt to get C -> asm 100% matching decompile. Documentation and code quality may be poor. Mostly used as a reference.

"Not-long-enough-want-to-read-more":

* `decompile` contains our first attempt at decompiling CTR. Here are some facts:
  - As a consequence of it being around the longest, the majority of mods that exist are built on this decompile.
  - It is non-matching, and generally* uses the ship of thesius strategy.
  - It contains considerations for several builds of the game (i.e., we have multiple build targets, attempting to construct the layout of the game as it appeared in various demos of the game).
  - It contains various optimizations to attempt to cut dead code, make the game run faster, and simplify structure, whilst still behaving identically to the original game.
  - As a consequence of these changes, there are some bugs.
    * \* Some functions are patched in-place, some are stored elsewhere (like rdata). Search the codebase for "DEFRAG" if curious.
  - Contributions to the `decompile` project are welcome (and so are mods based on it, see the [CTR-ModSDK repo](https://github.com/CTR-tools/CTR-ModSDK)), but work on the `rewrite` is preferred.
* `rewrite` is our second attempt at decompiling CTR. Here are some facts:
  - In the `rewrite`, we only focus on NTSC-U, from 9/26/99 (build date). There are no considerations for other builds of the game in this decompile.
  - We focus again on matching behavior, but in addition we focus on matching api (for the most part*)
  - For functions we decompile, if they're a pure function (only input/output, no global side effects), we write unit tests that run A&B for both the original asm and our asm during runtime to ensure they behave identically.
  - For functions that don't fit this bill, we try to test them extremely thoroughly.
  - Additionally, ensuring that impure functions are based on 100% matching C -> asm (see the `matching` project) with only trivial restructuring can ensure our functions behave identically to ND's implementation.
    * \* Some parts of CTR were written in raw asm, and were not ABI-adherant. Those portions of the game are being rewritten to be fully ABI-adherhant. As a consequence, some portions of code need to be patched in "all at once"/"not at all", or else the mixture of ABI-adherant/non-ABI-adherant code will cause problems in runtime. The rewritten structure is being rewritten in a way that tries to match the original intention of the API from the original authors.
  - Contributions to the `rewrite` project are welcome!
* `matching` is an active pursuit of finding the original code structure. Here are some facts:
  - In the `matching` project, we only focus on NTSC-U, from 9/26/99 (build date). There are no considerations for other builds of the game in this decompile.
  - Documentation, clarifying comments, actual variable names etc are likely lacking in this project. The only goal is to achieve matching decomp.
  - Making mods based on this project is discouraged, it's not designed to be "user-friendly"
  - This project in it's pursuits (as well as other resources) is used as a reference for the `rewrite` project.