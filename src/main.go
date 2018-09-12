package main

// #include "cgo.h"
// #cgo CXXFLAGS: -g -Wall -I/usr/local/lib/wx/include/osx_cocoa-unicode-3.0 -I/usr/local/include/wx-3.0 -D_FILE_OFFSET_BITS=64 -DWXUSINGDLL -D__WXMAC__ -D__WXOSX__ -D__WXOSX_COCOA__
// #cgo LDFLAGS: -lstdc++ -L/usr/local/lib   -framework IOKit -framework Carbon -framework Cocoa -framework AudioToolbox -framework System -framework OpenGL -lwx_osx_cocoau_xrc-3.0 -lwx_osx_cocoau_webview-3.0 -lwx_osx_cocoau_html-3.0 -lwx_osx_cocoau_qa-3.0 -lwx_osx_cocoau_adv-3.0 -lwx_osx_cocoau_core-3.0 -lwx_baseu_xml-3.0 -lwx_baseu_net-3.0 -lwx_baseu-3.0
import "C"
import "os"

func main() {
	// Convert CLI arguments to array of C strings
	args := C.str_array_new(C.int(len(os.Args)))
	for i, v := range os.Args {
		str := C.CString(v)
		C.str_array_set(args, C.int(i), str)
	}

	// Start the app
	C.start_app(C.int(1), args)

	// Clear some memory
	C.str_array_free(C.int(len(os.Args)), args)
}
