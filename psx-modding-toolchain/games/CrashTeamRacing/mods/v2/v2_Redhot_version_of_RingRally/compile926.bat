@echo off
set PSX_PATH=./../tools
set PSYQ_PATH=../../tools
"../../tools/CCPSX" -DBUILD=926 -c -O -G 0 main.c
"../../tools/SLINK" /psx /p /c /m @linker926.link,main.bin,main.sym,main.map