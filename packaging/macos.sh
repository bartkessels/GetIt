#!/bin/env bash

MACOS_DIR=${PWD}/packaging/macos
INFO_PLIST=${MACOS_DIR}/Info.plist
ICON=${PWD}/resources/icons/main.svg

cmake \
    -DCMAKE_MACOSX_BUNDLE=ON \
    -DMACOSX_BUNDLE_INFO_PLIST=$INFO_PLIST \
    -DMACOSX_BUNDLE_ICON_FILE=$ICON \
    .

make getit

# Run Qt deploy
macdeployqt ./bin/getit.app -dmg
