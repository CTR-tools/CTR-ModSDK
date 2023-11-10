cd ../../../../
CMake -G "Visual Studio 17 2022" -DPLATFORM_DURANGO=1 -DCMAKE_SYSTEM_NAME=WindowsStore -DCMAKE_SYSTEM_VERSION=10.0 -B /Build/Build_Durango -A x64