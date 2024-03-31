Works in USA Retail, Japan Trial, Europe Retail, Japan Retail.
Does not work in Sep3

CustomJitPoolsNew.c overwrites the original exe function.
While the original would put all pools in mempack (heap),
the new function stores as much into kernel as possible.
In order from top to bottom:
	- Driver and Thread pools allocated by calling functions
		in the next ".c" file below
	- Japan builds move Medium Stack to overwrite anti-modchip
		functions. Even if we wanted the anti-modchip function
		to be active in the game (like Naughty Dog wanted), it
		will have already finished it's purpose before being
		overwritten

NewDriverPool.c appends the decompiled PushBuffer_Init,
which was reduced in size with logical optimizations.
The new Driver pool is not solid memory, drivers are scattered
around RAM. The game mostly-uses the linked lists, and only treats 
the pool as solid-unscattered buffer during JitPool_Clear, which 
this mod overrides, so the memory can be scattered with no problem.
The code in this file relocates every driver to kernel memory,
and rewrites the ClearAllPools function, to use custom pool
allocators.

NewThreadPool.c fully relocates thread pool, just like how the
driver pool was fully relocated, except the thread pool
is partially on lib-RDATA (debug messages of psyq libs), and 
partially overwriting function assembly. The functions overwritten 
are on-boot functions, they will never run after being erased, so it 
is free memory to steal.