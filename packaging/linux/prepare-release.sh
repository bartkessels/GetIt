#!/bin/env bash

# Download the latest release tarball
tarball = "v{project-version}.tar.gz"
tarball-uri = "https://github.com/bartkessels/{project-name}/archive/refs/tags/$tarball"
wget $tarball-uri

# Calculate SHA256 hash
tarball-hash = ($(sha256sum $tarball))

# Replace variables in getit.yml
sed -i s/{tarball-url}/$tarball-uri/ {current-dir}/packaging/linux/getit.yml
sed -i s/{tarball-hash}/$tarball-hash/ {current-dir}/packaging/linux/getit.yml