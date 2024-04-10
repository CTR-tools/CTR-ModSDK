#! /usr/bin/env nix-build
{ pkgs ? import <nixpkgs> {}
, pkgsCross ? pkgs.pkgsCross.mingw32
}:

pkgsCross.callPackage ./default.nix {}
