#!/usr/bin/env bash

# Copy files needed for server
cp -r ../../../../../externals/enet .
cp -r ../../../../../decompile .

# Check if the OS is NixOS
if [ "$(uname -s)" == "Linux" ] && grep -q 'NixOS' /etc/issue; then
    # NixOS-specific commands
    git add enet decompile
    rm ./enet/.git
    rm -r ./enet/.github
fi

# Build Docker image
docker build -t ctr-psx-server:latest .

# Clean up
rm -rf ./enet
rm -rf ./decompile

# Reverse the git add (only on NixOS)
if [ "$(uname -s)" == "Linux" ] && grep -q 'NixOS' /etc/issue; then
    git reset HEAD enet decompile
fi
