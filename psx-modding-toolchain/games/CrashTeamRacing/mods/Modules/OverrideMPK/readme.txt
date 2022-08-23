Disable the MPKs that force certain characters. Also only
load high LOD models, instead of high+med+low+box

Can be used for graphics upgrade, OnlineCTR,
character randomization, etc

Optimized string searching can potentially be it's own module

Patching "numDrivers" is for a loop in Loading Stage 6,
that patches file pointers into model pointers

Patching "numDriversPlusOne" is for AppendLoadingQueue,
allows us to write 9 slots to the queue instead of 8,
so we can request 8 drivers + 1 MPK