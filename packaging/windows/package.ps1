# Add extra argument to locate the vcpkg cmake location in the Github pipeline and to include the boost libraries
Invoke-Expression "cmake -B . -S -G Ninja -DCMAKE_TOOLCHAIN_FILE=C:\vcpkg\scripts\buildsystems\vcpkg.cmake -DVCPKG_TARGET_TRIPLET=x86-windows-static -DBoost_INCLUDE_DIR=C:\vcpkg\x64-windows-static\include"
Invoke-Expression "cmake --build ."
Invoke-Expression "ninja GetIt"
Invoke-Expression "windeployqt ./bin/GetIt.exe"

Invoke-Expression "7z a -tzip getit.zip ./bin/GetIt.exe"
