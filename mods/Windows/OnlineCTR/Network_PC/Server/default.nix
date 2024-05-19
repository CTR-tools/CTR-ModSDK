{ lib
, stdenv
, cmake
, pkg-config
, enet
, ctrModSDK ? ./../../../../..
, withDebug ? true
}:

let
  isWindows = stdenv.hostPlatform.uname.system == "Windows";

  mainProgram = if isWindows then "ctr_srv.exe" else "ctr_srv";

  path = "mods/Windows/OnlineCTR/Network_PC/Server";

  cross-enet =
    if isWindows then
      enet.overrideAttrs
        (previousAttrs: {
          nativeBuildInputs = [ cmake ];

          installPhase = ''
            runHook preInstall

            mkdir -p $out/lib
            cp libenet.a $out/lib/

            runHook postInstall
          '';

          meta = previousAttrs.meta // { platforms = lib.platforms.all; };
        })
    else enet;
in
stdenv.mkDerivation (_: {
  pname = "CTR-SRV";
  version = "0.0.1";

  src = ctrModSDK;
  sourceRoot =
    if ctrModSDK == ./../../../../.. then "CTR-ModSDK/${path}"
    else "source/${path}";

  nativeBuildInputs = [ cmake pkg-config ];
  buildInputs = [ cross-enet ];

  # Disables incompatible hardening
  hardeningDisable = [ "format" ];

  # Config
  cmakeFlags = lib.optionals withDebug [ "-DCMAKE_BUILD_TYPE=Debug" ];

  installPhase = ''
    runHook preInstall

    mkdir -p $out/bin
    cp ${mainProgram} $out/bin/

    runHook postInstall
  '';

  # Keep debug symbols
  dontStrip = withDebug;

  # Shows the proper compile date in the logs
  env.SOURCE_DATE_EPOCH = (builtins.currentTime or ctrModSDK.lastModified);

  meta = {
    description = "CTR Online Companion";
    homepage = "https://github.com/CTR-tools/CTR-ModSDK";
    license = lib.licenses.publicDomain;
    maintainers = with lib.maintainers; [ pedrohlc ];
    mainProgram = "ctr_srv";
    platforms = lib.platforms.all;
  };
})
