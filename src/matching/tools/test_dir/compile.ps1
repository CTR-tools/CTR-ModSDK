# Windows-native compile.ps1 — PowerShell equivalent of compile.sh.
#
# Usage (matches the permuter's compile.sh contract):
#   .\compile.ps1 <input.c> -o <output.o>
#
# Pipeline:
#   gcc.exe (windows-gcc-psx submodule)
#       -> maspsx.py (Windows Python)
#       -> mipsel-none-elf-as.exe (pcsx-redux mips toolchain)
#
# Honours optional environment overrides:
#   $env:PYEXE  — full path to python.exe
#   $env:MIPSAS — full path to mipsel-none-elf-as.exe
# $args is used instead of a param() block so that the literal `-o` the
# permuter passes between input.c and output.o isn't bound as a switch.
$ErrorActionPreference = 'Stop'

if ($args.Count -ne 3 -or $args[1] -ne '-o') {
    Write-Error "Usage: compile.ps1 <input.c> -o <output.o>  (got: $args)"
    exit 1
}
$InputC   = $args[0]
$OutputO  = $args[2]

# --- Resolve repo-relative tool paths --------------------------------------

$ScriptDir = Split-Path -Parent $MyInvocation.MyCommand.Path
$ToolsDir  = Split-Path -Parent $ScriptDir
$GccDir    = Join-Path $ToolsDir 'windows-gcc-psx\gcc-2.8.1-psx'
$GccExe    = Join-Path $GccDir   'gcc.exe'
$Maspsx    = Join-Path $ToolsDir 'maspsx\maspsx.py'

$MipsAs = if ($env:MIPSAS) { $env:MIPSAS } else {
    # `%APPDATA%\mips\mips` is a Windows directory junction maintained by
    # the pcsx-redux installer pointing at the active version. Python's
    # pathlib can't see through the junction reliably, so resolve it now
    # and hand maspsx the real versioned path.
    $junctionPath = Join-Path $env:APPDATA 'mips\mips'
    if (Test-Path $junctionPath) {
        $target = (Get-Item $junctionPath).Target
        if ($target) {
            Join-Path $target[0] 'bin\mipsel-none-elf-as.exe'
        } else {
            Join-Path $junctionPath 'bin\mipsel-none-elf-as.exe'
        }
    } else {
        Join-Path $env:APPDATA 'mips\mips\bin\mipsel-none-elf-as.exe'
    }
}

$PyExe = if ($env:PYEXE) { $env:PYEXE } else {
    $cand = Join-Path $env:LOCALAPPDATA 'Programs\Python\Python312\python.exe'
    if (Test-Path $cand) { $cand } else { 'python' }
}

foreach ($t in @($GccExe, $Maspsx, $MipsAs)) {
    if (-not (Test-Path $t)) { Write-Error "Missing tool: $t"; exit 1 }
}

# --- Stage input.c + sibling .h files in a Windows temp dir ----------------

$TmpDir = Join-Path $env:TEMP ("matching-test." + [System.Guid]::NewGuid().ToString('N').Substring(0,8))
New-Item -ItemType Directory -Path $TmpDir -Force | Out-Null
try {
    $SrcDir = Split-Path -Parent (Resolve-Path $InputC).Path
    Copy-Item -Path $InputC -Destination (Join-Path $TmpDir 'input.c')
    Get-ChildItem -Path $SrcDir -Filter '*.h' -ErrorAction SilentlyContinue |
        ForEach-Object { Copy-Item $_.FullName $TmpDir }

    # --- gcc.exe: .c -> .s -------------------------------------------------

    $gccArgs = @(
        "-B${GccDir}\"
        '-I'; $TmpDir
        '-DUSE_REAL_GTE=1'
        '-S'
        '-Wa,--aspsx-version=2.77'
        '-mel'; '-g'; '-O2'
        (Join-Path $TmpDir 'input.c')
        '-o'; (Join-Path $TmpDir 'output.s')
    )
    & $GccExe @gccArgs
    if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }
    if (-not (Test-Path (Join-Path $TmpDir 'output.s'))) {
        Write-Error 'gcc produced no output.s'
        exit 1
    }

    # gcc on Windows writes CRLF; strip CR so maspsx sees LF-only.
    $sPath = Join-Path $TmpDir 'output.s'
    $bytes = [System.IO.File]::ReadAllBytes($sPath)
    $clean = New-Object System.Collections.Generic.List[byte]
    foreach ($b in $bytes) { if ($b -ne 0x0D) { $clean.Add($b) } }
    [System.IO.File]::WriteAllBytes($sPath, $clean.ToArray())

    # --- maspsx: .s -> .o --------------------------------------------------
    # maspsx's file-input mode strips PSY-Q debug directives differently
    # than its stdin path, so feed it via stdin. PowerShell's native pipe
    # adds a UTF-8 BOM, so delegate to cmd.exe (which does binary stdin
    # redirection cleanly).
    $maspsxCmd = ('"{0}" "{1}" --aspsx-version=2.77 --expand-div --run-assembler ' +
                  '--gnu-as-path "{2}" -o "{3}" < "{4}"') -f
                  $PyExe, $Maspsx, $MipsAs, $OutputO, $sPath
    cmd /c $maspsxCmd
    if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }
}
finally {
    Remove-Item -Recurse -Force $TmpDir -ErrorAction SilentlyContinue
}
