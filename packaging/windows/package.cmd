@ECHO OFF

# Compile GetIt
cmake . -G Ninja
ninja GetIt

# Link Qt
windeployqt ./bin/GetIt.exe

# Zip file
7z a -tzip getit.zip ./bin/GetIt.exe