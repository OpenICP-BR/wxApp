package main

// +build darwin,cgo

// #include "setup_cgo.h"
// #cgo CXXFLAGS: -g -Wall -I/usr/local/lib/wx/include/osx_cocoa-unicode-3.0 -I/usr/local/include/wx-3.0 -D_FILE_OFFSET_BITS=64 -DWXUSINGDLL -D__WXMAC__ -D__WXOSX__ -D__WXOSX_COCOA__
// #cgo LDFLAGS: -lstdc++ -L/usr/local/lib   -framework IOKit -framework Carbon -framework Cocoa -framework AudioToolbox -framework System -framework OpenGL -lwx_osx_cocoau_xrc-3.0 -lwx_osx_cocoau_webview-3.0 -lwx_osx_cocoau_html-3.0 -lwx_osx_cocoau_qa-3.0 -lwx_osx_cocoau_adv-3.0 -lwx_osx_cocoau_core-3.0 -lwx_baseu_xml-3.0 -lwx_baseu_net-3.0 -lwx_baseu-3.0
import "C"

func wxEntry(args []string) int {
	// Convert CLI arguments to array of C strings
	l := C.int(len(args))
	cargs := C.str_array_new(l)
	for i, v := range args {
		str := C.CString(v)
		C.str_array_set(cargs, C.int(i), str)
	}
	// Clear some memory
	defer C.str_array_free(l, cargs)

	// Start the app
	return int(C.start_app(l, cargs))
}
