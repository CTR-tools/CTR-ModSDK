@echo off
cd %~dp0
.\vrmtool.exe .\data.vram
copy .\data.vram ..\src\dataVRAM.bin
pause