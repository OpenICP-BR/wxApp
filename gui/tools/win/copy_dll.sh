#!/bin/bash

GREEN='\033[0;32m'
NC='\033[0m' # No Color

DST_DIR=$1
LIB_DIR=/c/msys64/mingw32/bin/
LIBS=(
	libexpat-1.dll
	wxmsw30u_aui_gcc_custom.dll
	libgcc_s_dw2-1.dll
	wxmsw30u_core_gcc_custom.dll
	libjpeg-8.dll
	wxmsw30u_gl_gcc_custom.dll
	liblzma-5.dll
	wxmsw30u_html_gcc_custom.dll
	libpng16-16.dll
	wxmsw30u_propgrid_gcc_custom.dll
	libstdc++-6.dll
	wxmsw30u_qa_gcc_custom.dll
	libtiff-5.dll
	wxmsw30u_ribbon_gcc_custom.dll
	libwinpthread-1.dll
	wxmsw30u_richtext_gcc_custom.dll
	wxbase30u_gcc_custom.dll
	wxmsw30u_stc_gcc_custom.dll
	wxbase30u_net_gcc_custom.dll
	wxmsw30u_webview_gcc_custom.dll
	wxbase30u_xml_gcc_custom.dll
	wxmsw30u_xrc_gcc_custom.dll
	wxmsw30u_adv_gcc_custom.dll
	zlib1.dll
)

for lib in ${LIBS[@]}; do
	echo cp "${LIB_DIR}/$lib" "${DST_DIR}"
	cp "${LIB_DIR}/$lib" "${DST_DIR}"
done

echo -e "${GREEN}[ OK ] Copied dll files${NC}"