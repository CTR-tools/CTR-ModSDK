{
  inputs.nixpkgs.url = https://flakehub.com/f/NixOS/nixpkgs/0.1.*.tar.gz;
  outputs = { self, nixpkgs }: {
    packages.x86_64-linux = with nixpkgs.legacyPackages.x86_64-linux; {
      native32 = with pkgsi686Linux; {
        gcc = callPackage ./rebuild_PC { ctrModSDK = self; };
        clang = callPackage ./rebuild_PC { ctrModSDK = self; stdenv = clangStdenv;  };
      };
      mingw32 = with mingw32; {
        gcc = callPackage ./rebuild_PC { ctrModSDK = self; };
        clang = callPackage ./rebuild_PC { ctrModSDK = self; stdenv = clangStdenv;  };
      };
    };
  };
}
