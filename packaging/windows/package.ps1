# Add extra argument to locate the vcpkg cmake location in the Github pipeline and to include the boost libraries
Invoke-Expression "cmake . -G `"Visual Studio 17 2022`" -Dpackaging=true -DCMAKE_CXX_FLAGS=`"-w`" -DCMAKE_TOOLCHAIN_FILE=C:\vcpkg\scripts\buildsystems\vcpkg.cmake -DVCPKG_TARGET_TRIPLET=x64-windows-static -DBoost_INCLUDE_DIR=C:\vcpkg\installed\x64-windows-static\include"
Invoke-Expression "devenv GetIt.sln /deploy Release"
Invoke-Expression "windeployqt ./bin/GetIt.exe"

Invoke-Expression "7z a -tzip getit.zip ./bin/GetIt.exe"
