@echo off
for %%f in (*.txt) do (
    ..\..\..\..\plugins\ctr-tools\lng2txt.exe "%%f"
)