#!/bin/env bash

# Compile GetIt
cmake . -Dpackaging=true -G Ninja

# Install required runtimes
flatpak install org.kde.Platform
flatpak install org.kde.Sdk

# Build flatpak
flatpak-builder --repo=getit_repo getit ./packaging/linux/getit.yml
flatpak build-bundle getit_repo getit.flatpak net.bartkessels.getit

# Zip file
zip -rT getit.zip ./bin/getit.flatpak >> /dev/null
