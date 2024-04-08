{ lib
, stdenv
, pkg-config
, cmake
, SDL2
, openal
, fetchFromGitHub
}:

let
  isWindows = stdenv.hostPlatform.uname.system == "Windows";

  openalWithWindows =
    if isWindows then
      (openal.override {
        alsaSupport = false;
        dbusSupport = false;
        pipewireSupport = false;
        pulseSupport = false;
      }).overrideAttrs (prevAttrs: {
        meta = prevAttrs.meta // { inherit (SDL2.meta) platforms; };
      })
    else openal;
in
stdenv.mkDerivation (finalAttrs:  {
  pname = "PsyCross";
  version = "unstable-2024-02-14-603475326";

  src = fetchFromGitHub {
    owner = "OpenDriver2";
    repo = "PsyCross";
    rev = "603475326dfa546cb47a6cc338c32053cca56022";
    hash = "sha256-1FW0U/XE+4WBrcgvOAaLSdU/GlR2S3Av8UiZla5rybI=";
  };

  # Shows the proper compile date in the logs (taken from commit date)
  env.SOURCE_DATE_EPOCH = "1707912179";

  nativeBuildInputs = [ pkg-config cmake ];
  propagatedBuildInputs = [ SDL2 openalWithWindows ];

  CFLAGS = [ "-Wno-narrowing" ];
  CXXFLAGS = [ "-Wno-narrowing" ];
  hardeningDisable = [ "format" ];

  postPatch = ''
    substituteInPlace CMakeLists.txt \
      --replace-fail 'OPENAL' 'OpenAL' \
      --replace-fail '"*.c"' '"*.c" "*.C"'

    substituteInPlace 'src/psx/LIBGTE.C' \
      --replace-fail 'RotTransPers(SVECTOR* v0, int* sxy' 'RotTransPers(SVECTOR* v0, long* sxy'

    substituteInPlace 'src/psx/LIBGPU.C' \
      --replace-fail 'u_short LoadTPage(u_int*' 'u_short LoadTPage(u_long*'

    substituteInPlace 'include/psx/kernel.h' \
      --replace-fail '#if 0' "#if 1"

    substituteInPlace 'include/PsyX/PsyX_config.h' \
      --replace-fail 'USE_EXTENDED_PRIM_POINTERS 1' 'USE_EXTENDED_PRIM_POINTERS 0'

    sed -i"" \
      's/#ifdef _WIN32/#ifdef _WIN32\n#include <windows.h>\n/;/^#define _stricmp/d;s/_stricmp/strcmp/' \
      src/PsyX_main.cpp

    sed -i"" '1s/^/cmake_minimum_required(VERSION 3.28)\n/' CMakeLists.txt
  '';

  installPhase = ''
    runHook preInstall

    mkdir "$out"
    cp -r ../include "$out/include"
    cp libpsycross.a "$out/libpsycross.a"

    runHook postInstall
  '';

  passthru = {
    inherit SDL2;
    openal = openalWithWindows;
  };

  meta = {
    description = "Compatibility framework for building and running Psy-Q SDK";
    homepage = "https://github.com/OpenDriver2/PsyCross";
    license = lib.licenses.mit;
    maintainers = with lib.maintainers; [ pedrohlc ];
    inherit (SDL2.meta) platforms;
  };
})
