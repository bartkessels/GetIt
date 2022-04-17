#!/bin/env zsh

# Compile GetIt
# Disable warnings as error
cmake . -Dpackaging=true -G Ninja -D CMAKE_CXX_FLAGS="-w"
ninja GetIt

# Build flatpak
flatpak-builder --repo=getit_repo getit ./packaging/linux/getit.yml
flatpak build-bundle getit_repo getit.flatpak net.bartkessels.getit

# Zip file
zip -rT getit.zip ./bin/getit.flatpak >> /dev/null