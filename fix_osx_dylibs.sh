#!/bin/bash

BIN_DIR=bin/openicp.app/Contents/MacOS/
BIN_FILE="${BIN_DIR}/openicp"
LIBS=(
	/usr/lib/libz.1.dylib
	/usr/local/opt/jpeg/lib/libjpeg.9.dylib
	/usr/local/opt/libpng/lib/libpng16.16.dylib
	/usr/local/opt/libtiff/lib/libtiff.5.dylib
	/usr/local/opt/wxmac/lib/libwx_baseu-3.0.dylib
	/usr/local/opt/wxmac/lib/libwx_baseu_net-3.0.dylib
	/usr/local/opt/wxmac/lib/libwx_baseu_xml-3.0.dylib
	/usr/local/opt/wxmac/lib/libwx_osx_cocoau_adv-3.0.dylib
	/usr/local/opt/wxmac/lib/libwx_osx_cocoau_aui-3.0.dylib
	/usr/local/opt/wxmac/lib/libwx_osx_cocoau_core-3.0.dylib
	/usr/local/opt/wxmac/lib/libwx_osx_cocoau_gl-3.0.dylib
	/usr/local/opt/wxmac/lib/libwx_osx_cocoau_html-3.0.dylib
	/usr/local/opt/wxmac/lib/libwx_osx_cocoau_propgrid-3.0.dylib
	/usr/local/opt/wxmac/lib/libwx_osx_cocoau_qa-3.0.dylib
	/usr/local/opt/wxmac/lib/libwx_osx_cocoau_ribbon-3.0.dylib
	/usr/local/opt/wxmac/lib/libwx_osx_cocoau_richtext-3.0.dylib
	/usr/local/opt/wxmac/lib/libwx_osx_cocoau_stc-3.0.dylib
	/usr/local/opt/wxmac/lib/libwx_osx_cocoau_webview-3.0.dylib
	/usr/local/opt/wxmac/lib/libwx_osx_cocoau_xrc-3.0.dylib
)

# Copy libraries
for OLD_LIB in "${LIBS[@]}"; do
	NEW_LIB=$(basename $OLD_LIB)
	cp --no-preserve=mode "${OLD_LIB}" "${BIN_DIR}/${NEW_LIB}"
	chmod +x "${BIN_DIR}/${NEW_LIB}"
	install_name_tool -change "${OLD_LIB}" "@loader_path/${NEW_LIB}" "${BIN_FILE}"
done
# Update libraries path
for filename in "${BIN_DIR}/"*.dylib; do
	for OLD_LIB in "${LIBS[@]}"; do
		NEW_LIB=$(basename $OLD_LIB)
		install_name_tool -change "${OLD_LIB}" "@loader_path/${NEW_LIB}" "${filename}"
	done
	# Some hacks
	install_name_tool -change "/usr/local/Cellar/wxmac/3.0.4/lib/libwx_osx_cocoau_html-3.0.0.4.0.dylib" "@loader_path/libwx_osx_cocoau_html-3.0.dylib" "${filename}"
	install_name_tool -change "/usr/local/Cellar/wxmac/3.0.4/lib/libwx_baseu_xml-3.0.0.4.0.dylib" "@loader_path/libwx_baseu_xml-3.0.dylib" "${filename}"
done



echo "Final external dylibs for ${BIN_FILE}"
otool -L ${BIN_FILE} | grep -v @executable_path