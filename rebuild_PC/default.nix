{ lib
, stdenv
, callPackage
, pkg-config
, cmake
, openal
, SDL2
, ctrModSDK ? ./..
, withDebug ? true
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

  mainProgram = if isWindows then "CrashTeamRacingPC.exe" else "CrashTeamRacingPC";
in
stdenv.mkDerivation (finalAttrs:  {
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

  # If you need vendored deps
  #cmakeFlags = [ "-DCMAKE_SKIP_BUILD_RPATH=TRUE" ];

  # Debug
  cmakeFlags = lib.optionals withDebug [ "-DCMAKE_BUILD_TYPE=Debug" ];
  dontStrip = withDebug;
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
