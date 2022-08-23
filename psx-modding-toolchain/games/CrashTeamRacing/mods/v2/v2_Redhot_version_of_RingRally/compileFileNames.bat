@echo off
set PSX_PATH=./../tools
set PSYQ_PATH=../../tools
"../../tools/CCPSX" -DBUILD=926 -c -G 0 fileNames.c
"../../tools/SLINK" /psx /p /c /m @linkerFileNames.link,fileNames.bin,fileNames.sym,fileNames.map