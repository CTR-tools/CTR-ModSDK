@echo off
cd %~dp0
copy .\output\Lev221c.bin ..\..\..\..\..\..\ctrviewer-r15prev\levels\lap_test\test.lev
copy .\src\dataVRAM.bin ..\..\..\..\..\..\ctrviewer-r15prev\levels\lap_test\test.vrm
pause