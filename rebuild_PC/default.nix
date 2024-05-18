{ lib
, stdenv
, callPackage
, pkg-config
, cmake
, openal
, SDL2
, ctrModSDK ? ./..
, withDebug ? true
, withMods ? true
, vendoredDeps ? false
, trustCompiler ? false
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
      }).overrideAttrs
        (prevAttrs: {
          meta = prevAttrs.meta // { inherit (SDL2.meta) platforms; };
        })
    else openal;

  mainProgram = if isWindows then "CrashTeamRacingPC.exe" else "CrashTeamRacingPC";
in
stdenv.mkDerivation (finalAttrs: {
  pname = "CTR-PC";
  version = "0.0.1";

  src = ctrModSDK;
  sourceRoot =
    if ctrModSDK == ./.. then "CTR-ModSDK/rebuild_PC"
    else "source/rebuild_PC";

  nativeBuildInputs = [ pkg-config cmake ];
  buildInputs = [ openalWithWindows SDL2 ];

  # Disables incompatible hardening
  hardeningDisable = [ "format" ];

  # Config
  cmakeFlags =
    lib.optionals withDebug [ "-DCMAKE_BUILD_TYPE=Debug" ]
    ++ lib.optionals (!withMods) [
      "-DCTR_60FPS=OFF"
      "-DCTR_16BY9=OFF"
      "-DCTR_NEW2P=OFF"
      "-DCTR_OXIDE=OFF"
      "-DCTR_PENTA=OFF"
      "-DCTR_HARDER=OFF"
      "-DCTR_NEWCUPS=OFF"
      "-DCTR_BOOSTBAR=OFF"
      "-DCTR_RAMEX=OFF"
    ] ++ lib.optionals trustCompiler [ "-DCMAKE_C_COMPILER_WORKS=1" "-DCMAKE_CXX_COMPILER_WORKS=1" ]
    ++ lib.optionals vendoredDeps [ "-DCMAKE_SKIP_BUILD_RPATH=TRUE" ];

  installPhase = ''
    runHook preInstall

    mkdir -p $out/bin
  '' + lib.strings.optionalString isWindows ''
    cp ${openalWithWindows}/bin/*.dll $out/bin/
    cp ${SDL2}/bin/*.dll $out/bin/
  '' + ''
    cp ${mainProgram} $out/bin/

    runHook postInstall
  '';

  # Keep debug symbols
  dontStrip = withDebug;

  # Export openal
  passthru = { openal = openalWithWindows; };

  # Shows the proper compile date in the logs
  env.SOURCE_DATE_EPOCH = (builtins.currentTime or ctrModSDK.lastModified);

  meta = {
    description = "CTR in C";
    homepage = "https://github.com/CTR-tools/CTR-ModSDK";
    license = lib.licenses.publicDomain;
    maintainers = with lib.maintainers; [ pedrohlc ];
    inherit mainProgram;
    inherit (SDL2.meta) platforms;
  };
})
