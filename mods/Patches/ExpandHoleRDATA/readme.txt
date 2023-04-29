This was originally used in Oxide Fix when we had to relocate RenderBucketInstance (RBI)
off the heap, and into RDATA. This patch increased the size of the available hole, to 
be just-over 4096 bytes. Now that oxide fix doesn't need to do this anymore (because of
thread optimizations), it is unused, but still here if anyone is desperate for extra bytes