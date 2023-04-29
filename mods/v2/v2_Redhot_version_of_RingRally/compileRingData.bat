@echo off
set PSX_PATH=./../tools
set PSYQ_PATH=../../tools
"../../tools/CCPSX" -DBUILD=926 -c -G 0 RingRallyData_CocoPark.c
"../../tools/SLINK" /psx /p /c /m @linkerRingData.link,RingRallyData_CocoPark.bin,RingRallyData_CocoPark.sym,RingRallyData_CocoPark.map