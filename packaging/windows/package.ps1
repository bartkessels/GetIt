Invoke-Expression "cmake . -G Ninja"
Invoke-Expression "ninja GetIt"
Invoke-Expression "windeployqt ./bin/GetIt.exe"

Invoke-Expression "7z a -tzip getit.zip ./bin/GetIt.exe"