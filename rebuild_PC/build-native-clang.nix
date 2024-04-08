#! /usr/bin/env nix-build
{ pkgs ? import <nixpkgs> {}
, pkgsCross ? pkgs.pkgsi686Linux
}:

pkgsCross.callPackage ./default.nix { stdenv = pkgsCross.clangStdenv; }
