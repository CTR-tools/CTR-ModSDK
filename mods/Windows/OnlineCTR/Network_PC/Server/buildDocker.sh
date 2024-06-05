#!/usr/bin/env bash

cp -r ../../../../../externals/enet/ .
cp -r ../../../../../decompile/ .

#have to git add . in NixOS
git add .
rm ./enet/.git
rm -r ./enet/.github

sleep 2
docker build -t nomadics/ctrserver:latest .

sleep 2
#clean
rm -rf ./enet
rm -rf ./decompile

#reverse the first git add .
git add .
