#!/bin/env zsh

# Compile GetIt
echo 'Compiling GetIt...'
cmake . -Dpackaging=true -G Ninja
ninja GetIt

# Libraries
frameworksLocation="./bin/GetIt.app/Contents/Frameworks"
mkdir -p "$frameworksLocation"

# Link Qt libraries
echo 'Linking Qt libraries'
qtLibraryLocation="/usr/local/opt/qt/Frameworks"
cp "$qtLibraryLocation/QtWidgets.framework" \
   "$frameworksLocation"

cp "$qtLibraryLocation/QtGui.framework" \
   "$frameworksLocation"


# Link CppRestSdk libraries
echo 'Linking CppRestSdk libraries'
cppRestLibraryLocation=""

#
## Link Boost libraries
#echo 'Linking Boost libraries'
