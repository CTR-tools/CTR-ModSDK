{
  inputs.nixpkgs.url = https://flakehub.com/f/NixOS/nixpkgs/0.1.*.tar.gz;
  outputs = { self, nixpkgs }: with nixpkgs.legacyPackages.x86_64-linux; rec {
    packages.x86_64-linux =
      let
        mkCTR = withDebug: withMods: {
          native32 = with pkgsi686Linux; {
            gcc = callPackage ./rebuild_PC { ctrModSDK = self; inherit withDebug withMods; };
            clang = callPackage ./rebuild_PC { ctrModSDK = self; stdenv = clangStdenv; inherit withDebug withMods; };
          };
          mingw32 = with pkgsCross.mingw32; {
            gcc = callPackage ./rebuild_PC { ctrModSDK = self; inherit withDebug withMods; };
            clang = callPackage ./rebuild_PC { ctrModSDK = self; stdenv = clangStdenv; trustCompiler = true; inherit withDebug withMods; };
          };
          msvc = throw "TODO";
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
      };
    # default
    defaultPackage.x86_64-linux = stdenvNoCC.mkDerivation {
      name = "ctr-join";
      dontUnpack = true;
      dontBuild = true;
      installPhase = with packages.x86_64-linux; ''
        mkdir $out
        ln -s ${decomp.debug.native32.gcc} $out/native32-gcc
        ln -s ${decomp.debug.native32.clang} $out/native32-clang
        ln -s ${decomp.debug.mingw32.gcc} $out/mingw32-gcc
        ln -s ${decomp.debug.mingw32.clang} $out/mingw32-clang
        ln -s ${retail.release.mingw32.clang} $out/retail-release-mingw32-clang
      '';
    };
  };
}
