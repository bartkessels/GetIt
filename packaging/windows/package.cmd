@ECHO OFF

cmake . -G Ninja
ninja GetIt

windeployqt ./bin/GetIt.exe
7z a -tzip getit.zip ./bin/GetIt.exe