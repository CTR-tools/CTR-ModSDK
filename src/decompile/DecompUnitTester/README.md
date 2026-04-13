# What is this?
This is a real time unit tester for decompiled functions. The idea of this mod is to use `PCSX-Redux` 8MB memory expansion in order to call both the decompiled function and the original function, and then compare their outputs.

## Why?
Reverse engineering is the process of understanding how a piece of software accomplishes a task, without having the access to its original source code. Once you understand what the software does, you can re-write it in your own way, producing code which may not be identical to the original source, but will be functioning in the same way.

There are multiple advantages of re-writing the software on your own. You will:
* Gain a fundamental understanding of how the software works;
* Be able to modify the software as you please;
* Be able to fix bugs and optimize the code;

The code generation is most likely going to be much better than the original progran since you could use modern compilers with your code.

## How?
The idea behind comparing two functions is simple. In the PSX, a function can:
* Return a value;
* Write to the RAM;
* Write to the scratchpad;
* Modify the COP2 registers;

If we want to tell whether two functions share the same behavior, we first need to create a backup of the current state of the program, and de-activate all the system interrupts. This will ensure that only our functions will be writing to memory, so we have full control of the function workflow. Then, we need to compare whether the RAM, scratchpad, COP2 regs and return value remains the same for both functions.