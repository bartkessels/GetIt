#!/bin/env zsh

# Compile GetIt
cmake . -G Ninja -Dpackaging=true -DUseQt6=true
ninja GetIt

# Link Qt
echo 'Linking Qt to the app bundle'
macdeployqt ./bin/GetIt.app -timestamp -libpath=./_deps

# Copy icon file
cp ./packaging/macos/icons/getit.icns ./bin/GetIt.app/Contents/Resources

# Zip file
zip -rT getit.zip ./bin/GetIt.app >> /dev/null