{ lib
, stdenv
, pkg-config
, cmake
, SDL2
, openal
, fetchFromGitHub
, psyCrossDebug ? false
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
        inherit stdenv;
      }).overrideAttrs (prevAttrs: {
        meta = prevAttrs.meta // { inherit (SDL2.meta) platforms; };
      })
    else openal.override { inherit stdenv; };
in
stdenv.mkDerivation (finalAttrs:  {
  pname = "PsyCross";
  version = "unstable-2024-02-14-0ce306d6c";

  src = fetchFromGitHub {
    owner = "OpenDriver2";
    repo = "PsyCross";
    rev = "0ce306d6c32412986037e7e5e1dbdc1bf72e066a";
    hash = "sha256-c57xyzM7GkL9SazUUxAM4DVXxb7cTcjJxgJpZ7UMBVQ=";
  };

  # Shows the proper compile date in the logs (taken from commit date)
  env.SOURCE_DATE_EPOCH = "1712578640";

  nativeBuildInputs = [ pkg-config cmake ];
  propagatedBuildInputs = [ (SDL2.override { inherit stdenv; }) openalWithWindows ];

  hardeningDisable = [ "format" ];

  CFLAGS = "-Wno-implicit-function-declaration" + lib.strings.optionalString psyCrossDebug "-D_DEBUG=1 -g -gdwarf-2 -O0";
  CXXFLAGS = lib.strings.optionalString psyCrossDebug "-D_DEBUG=1 -g -gdwarf-2 -O0";
  dontStrip = psyCrossDebug;

  postPatch = ''
    substituteInPlace 'include/PsyX/PsyX_config.h' \
      --replace-fail 'USE_EXTENDED_PRIM_POINTERS 1' 'USE_EXTENDED_PRIM_POINTERS 0'
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
