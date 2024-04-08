#!/usr/bin/env sh
set -e

if ! [ -e ./CrashTeamRacingPC.c ]; then
  echo "Wrong \$PWD!"
  exit 1
fi

if [ -e ./result ]; then
  if ! [ -e ./result/native-gcc ]; then
    echo "Cleanup first!"
    exit 2
  fi
else
  mkdir ./result
fi

for target in {native,mingw}-{gcc,clang}; do
  ./build-${target}.nix -o ./result/$target
done

echo 'Finished successfully'
