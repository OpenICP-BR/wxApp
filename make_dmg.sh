#!/bin/bash

BIN_DIR=bin/
DMG_DIR="${BIN_DIR}/dmg/"
DMG_NAME="OpenICP-BR"
DMG_FILE="${BIN_DIR}/OpenICP-BR.dmg"

rm -rf "${DMG_DIR}"
rm "${DMG_FILE}"
mkdir "${DMG_DIR}"
mkdir "${DMG_DIR}/OpenICP-BR.app"

ln -s /Applications "${DMG_DIR}/Aplicativos"
cp -r "${BIN_DIR}/openicp.app/"* "${DMG_DIR}/OpenICP-BR.app"
hdiutil create -fs HFS+ -srcfolder "${DMG_DIR}" -volname "${DMG_NAME}" "${DMG_FILE}"
rm "${DMG_DIR}/Aplicativos"
echo "Created DMG file on ${DMG_FILE}"