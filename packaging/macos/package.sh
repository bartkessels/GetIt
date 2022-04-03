#!/bin/env zsh

# Compile GetIt
echo 'Compiling GetIt...'
# Disable warnings as error
cmake . -Dpackaging=true -G Ninja -D CMAKE_CXX_FLAGS="-w"
ninja GetIt

# Link Qt
echo 'Linking Qt to the app bundle'
macdeployqt ./bin/GetIt.app -timestamp -always-overwrite -libpath=./_deps
