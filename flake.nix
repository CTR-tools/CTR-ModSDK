{
  inputs.nixpkgs.url = https://flakehub.com/f/NixOS/nixpkgs/0.1.*.tar.gz;
  outputs = { self, nixpkgs }: rec {
    packages.x86_64-linux = with nixpkgs.legacyPackages.x86_64-linux; rec {
      native32 = with pkgsi686Linux; {
        gcc = callPackage ./rebuild_PC { ctrModSDK = self; };
        clang = callPackage ./rebuild_PC { ctrModSDK = self; stdenv = clangStdenv;  };
      };
      mingw32 = with pkgsCross.mingw32; {
        gcc = callPackage ./rebuild_PC { ctrModSDK = self; };
        clang = callPackage ./rebuild_PC { ctrModSDK = self; stdenv = clangStdenv; trustCompiler = true;  };
      };
      all = stdenvNoCC.mkDerivation {
        name = "ctr-join";
        dontUnpack = true;
        dontBuild = true;
        installPhase = ''
          mkdir $out
          ln -s ${native32.gcc} $out/native32-gcc
          ln -s ${native32.clang} $out/native32-clang
          ln -s ${mingw32.gcc} $out/mingw32-gcc
          ln -s ${mingw32.clang} $out/mingw32-clang
        '';
      };
    };
    # default
    package.x86_64-linux = packages.x86_64-linux.native32.gcc;
  };
}
