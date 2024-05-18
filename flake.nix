{
  inputs = {
    nixpkgs.url = "https://flakehub.com/f/NixOS/nixpkgs/0.1.*.tar.gz";
    systems.url = "github:nix-systems/default-linux";
    yafas = {
      url = "https://flakehub.com/f/UbiqueLambda/yafas/0.1.*.tar.gz";
      inputs.systems.follows = "systems";
    };
  };
  outputs = { self, nixpkgs, yafas, ... }: yafas.withAllSystems nixpkgs
    (_: { pkgs, system }: with pkgs; rec {
      packages =
        let
          pkgsARM32 = pkgsCross.armv7l-hf-multiplatform;
          pkgs32 = if system == "x86_64-linux" then pkgsi686Linux else pkgsARM32;

          mkCTR = withDebug: withMods: {
            native32 = with pkgs32; {
              gcc = callPackage ./rebuild_PC { ctrModSDK = self; inherit withDebug withMods; };
              clang = callPackage ./rebuild_PC { ctrModSDK = self; stdenv = clangStdenv; inherit withDebug withMods; };
            };
            mingw32 = with pkgsCross.mingw32; {
              gcc = callPackage ./rebuild_PC { ctrModSDK = self; inherit withDebug withMods; };
              clang = callPackage ./rebuild_PC { ctrModSDK = self; stdenv = clangStdenv; trustCompiler = true; inherit withDebug withMods; };
            };
          };

          mkOnline = withDebug: {
            native32 = with pkgs32; {
              gcc = callPackage ./mods/Windows/OnlineCTR/Network_PC/Server { ctrModSDK = self; inherit withDebug; };
              clang = callPackage ./mods/Windows/OnlineCTR/Network_PC/Server { ctrModSDK = self; stdenv = clangStdenv; inherit withDebug; };
            };
            arm32 = with pkgsARM32; {
              gcc = callPackage ./mods/Windows/OnlineCTR/Network_PC/Server { ctrModSDK = self; inherit withDebug; };
              clang = callPackage ./mods/Windows/OnlineCTR/Network_PC/Server { ctrModSDK = self; stdenv = clangStdenv; inherit withDebug; };
            };
            mingw32 = with pkgsCross.mingw32; {
              gcc = callPackage ./mods/Windows/OnlineCTR/Network_PC/Server { ctrModSDK = self; inherit withDebug; };
              clang = callPackage ./mods/Windows/OnlineCTR/Network_PC/Server { ctrModSDK = self; stdenv = clangStdenv; trustCompiler = true; inherit withDebug; };
            };
          };
        in
        rec {
          retail = {
            release = mkCTR false false;
            debug = mkCTR true false;
          };
          decomp = {
            release = mkCTR false true;
            debug = mkCTR true true;
          };
          online-server = {
            release = mkOnline false;
            debug = mkOnline true;
          };
        };
    })
    { };
}
