#!/bin/env bash

cmake .  -G Ninja -Dpackaging=true -DCMAKE_CXX_FLAGS="-w"

# Build flatpak
flatpak-builder --repo=getit_repo getit ./packaging/linux/getit.yml
flatpak build-bundle getit_repo getit.flatpak net.bartkessels.getit

# Zip file
zip -rT getit.zip ./bin/getit.flatpak >> /dev/null
