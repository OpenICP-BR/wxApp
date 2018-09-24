#!/bin/bash

GREEN='\033[0;32m'
NC='\033[0m' # No Color

DST_DIR=$1
WX_LIB_DIR=/c/wxWidgets-3.0.4/lib/gcc_dll/
WX_LIBS=(
	wxbase30u_gcc_custom.dll
	wxbase30u_net_gcc_custom.dll
	wxbase30u_xml_gcc_custom.dll
	wxmsw30u_adv_gcc_custom.dll
	wxmsw30u_aui_gcc_custom.dll
	wxmsw30u_core_gcc_custom.dll
	wxmsw30u_gl_gcc_custom.dll
	wxmsw30u_html_gcc_custom.dll
	wxmsw30u_propgrid_gcc_custom.dll
	wxmsw30u_qa_gcc_custom.dll
	wxmsw30u_ribbon_gcc_custom.dll
	wxmsw30u_richtext_gcc_custom.dll
	wxmsw30u_stc_gcc_custom.dll
	wxmsw30u_webview_gcc_custom.dll
	wxmsw30u_xrc_gcc_custom.dll
)

for lib in ${WX_LIBS[@]}; do
	echo cp "${WX_LIB_DIR}/$lib" "${DST_DIR}"
	cp "${WX_LIB_DIR}/$lib" "${DST_DIR}"
done

LIB_DIR=/c/mingw32/i686-w64-mingw32/lib/
LIBS=(
	libexpat-1.dll
	libgcc_s_dw2-1.dll
	libjpeg-8.dll
	liblzma-5.dll
	libpng16-16.dll
	libstdc++-6.dll
	libtiff-5.dll
	libwinpthread-1.dll
	zlib1.dll
)

for lib in ${LIBS[@]}; do
	echo cp "${LIB_DIR}/$lib" "${DST_DIR}"
	cp "${LIB_DIR}/$lib" "${DST_DIR}"
done

echo -e "${GREEN}[ OK ] Copied dll files${NC}"