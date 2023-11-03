@echo off
cd %~dp0

:: Get Newest Level File
copy ..\output\Lev221c.bin .\data.lev

:: Get Blank VRAM File
copy ..\..\Automate\blankVRAM_dontErase.vrm .\data.vrm

:: Patch Level with Automation
..\..\Automate\LevelPatcher\Debug\LevelPatcher.exe %cd%\data.lev

:: Generate Layout
..\..\Automate\model_reader.exe .\data.lev

:: Generate VRAM
..\..\Automate\vrmtool.exe .\data.vrm

:: Submit Level File
copy .\data.lev ..\output\Lev221c.bin

:: Submit VRAM File
copy .\data.vrm ..\src\dataVRAM.bin

pause