# check_scores.ps1 — PowerShell version of check_scores.sh.
#
# Surveys every per-function directory under src/matching/tools/ and
# reports each one's current base score. Run with no args to scan all,
# or pass a filter:
#   .\check_scores.ps1 'Veh*'
#
# Output: "<func_name>: <score>" lines as per the .sh version.

param(
    [Parameter(Position=0)][string]$Filter = '*'
)

$ErrorActionPreference = 'Stop'

# Locate the repo root by walking up looking for src/matching/tools/.
$scriptDir = Split-Path -Parent $MyInvocation.MyCommand.Path
$repoRoot = $scriptDir
while ($repoRoot -and -not (Test-Path (Join-Path $repoRoot 'src\matching\tools'))) {
    $parent = Split-Path -Parent $repoRoot
    if ($parent -eq $repoRoot) { break }
    $repoRoot = $parent
}
if (-not (Test-Path (Join-Path $repoRoot 'src\matching\tools'))) {
    Write-Error "Couldn't find src/matching/tools/ above this script"
    exit 1
}

$tools    = Join-Path $repoRoot 'src\matching\tools'
$permuter = Join-Path $tools    'permuter\permuter.py'

# Pick a Python.
$py = if ($env:PYEXE) { $env:PYEXE } else {
    $cand = Join-Path $env:LOCALAPPDATA 'Programs\Python\Python312\python.exe'
    if (Test-Path $cand) { $cand } else { 'python' }
}

$found = 0
Get-ChildItem -Path $tools -Directory -Filter $Filter | ForEach-Object {
    $name = $_.Name
    # Skip submodules and templates.
    if ($name -in @('permuter','maspsx','windows-gcc-psx','gcc')) { return }
    if ($name -like 'compile.*.template')                        { return }

    $base   = Join-Path $_.FullName 'base.c'
    $target = Join-Path $_.FullName 'target.o'
    if (-not (Test-Path $base))   { Write-Output "${name}: NO_BASE.C";   return }
    if (-not (Test-Path $target)) { Write-Output "${name}: NO_TARGET.O"; return }
    $script:found = $script:found + 1

    $out = & $py $permuter $_.FullName --debug 2>&1 | Out-String
    $m = [regex]::Match($out, "base score = (\d+)")
    if (-not $m.Success) {
        $err = ([regex]::Match($out, "(?im)^.*(error|fail|undeclared|undefined|unable).*$").Value)
        if ($err.Length -gt 80) { $err = $err.Substring(0, 80) }
        Write-Output "${name}: FAIL $err"
        return
    }

    $score = [int]$m.Groups[1].Value
    if ($score -eq 0) {
        Write-Output "${name}: 0 ✓"
        return
    }

    # Best score across output-*/ subdirs.
    $outputs = Get-ChildItem -Path $_.FullName -Directory -Filter 'output-*' -ErrorAction SilentlyContinue
    if ($outputs) {
        $best = ($outputs | ForEach-Object {
            $m2 = [regex]::Match($_.Name, '^output-(\d+)')
            if ($m2.Success) { [int]$m2.Groups[1].Value }
        } | Sort-Object | Select-Object -First 1)
        if ($null -ne $best) {
            Write-Output "${name}: $score best=$best"
            return
        }
    }
    Write-Output "${name}: $score"
}

if ($found -eq 0) {
    Write-Error "(no function dirs matched filter: $Filter)"
    exit 1
}
