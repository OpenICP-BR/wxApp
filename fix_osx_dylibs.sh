#!/bin/bash

BIN_FILE=bin/openicp.app/Contents/MacOS/openicp
LIBS=(/usr/lib/libc++.1.dylib /usr/local/opt/wxmac/lib/libwx_osx_cocoau_xrc-3.0.dylib /usr/local/opt/wxmac/lib/libwx_osx_cocoau_adv-3.0.dylib /usr/local/opt/wxmac/lib/libwx_baseu-3.0.dylib /usr/local/opt/wxmac/lib/libwx_osx_cocoau_core-3.0.dylib /usr/local/opt/wxmac/lib/libwx_baseu_net-3.0.dylib)
for OLD_LIB in "${LIBS[@]}"
do
	NEW_LIB=$(basename $OLD_LIB)
	install_name_tool -change ${OLD_LIB} @executable_path/${NEW_LIB} ${BIN_FILE}
done
echo "Final external dylibs for ${BIN_FILE}"
otool -L ${BIN_FILE} | grep -v @executable_path