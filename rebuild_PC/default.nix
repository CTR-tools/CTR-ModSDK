{ lib
, stdenv
, callPackage
, pkg-config
, ctrModSDK ? ./..
, psyCross ? callPackage ./PsyCross.nix { inherit psyCrossDebug; }
, psyCrossDebug ? false
}:

let
  isWindows = stdenv.hostPlatform.uname.system == "Windows";

  mainProgram = if isWindows then "CrashTeamRacingPC.exe" else "CrashTeamRacingPC";
in
stdenv.mkDerivation (finalAttrs:  {
  pname = "CTR-PC";
  version = "0.0.1";

  src = ctrModSDK;
  sourceRoot =
    if ctrModSDK == ./.. then "CTR-ModSDK/rebuild_PC"
    else "source/rebuild_PC";

  nativeBuildInputs = [ pkg-config ];
  buildInputs = psyCross.propagatedBuildInputs;

  LDLIBS = "-L./PsyCross";

  # Disables incompatible hardening
  hardeningDisable = [ "format" ];

  postPatch = ''
    rm -r PsyCross
    ln -s ${psyCross} PsyCross
  '';

  installPhase = ''
    runHook preInstall

    mkdir -p $out/bin
  '' + lib.strings.optionalString isWindows ''
    cp ${psyCross.openal}/bin/*.dll $out/bin/
    cp ${psyCross.SDL2}/bin/*.dll $out/bin/
  '' + ''
    cp ${mainProgram} $out/bin/

    runHook postInstall
  '';

  # Debug
  CFLAGS = "-g -gdwarf-2";
  dontStrip = true;
  passthru = { inherit psyCross; };

  # Shows the proper compile date in the logs
  env.SOURCE_DATE_EPOCH = (builtins.currentTime or ctrModSDK.lastModified);

  meta = {
    description = "CTR in C";
    homepage = "https://github.com/CTR-tools/CTR-ModSDK";
    license = lib.licenses.publicDomain;
    maintainers = with lib.maintainers; [ pedrohlc ];
    inherit mainProgram;
    inherit (psyCross.meta) platforms;
  };
})
