package main

// #include "setup_cgo.h"
import "C"
import (
	"fmt"
	"os"
)

func main() {
	fmt.Println("[golang] OpenICP-BR version: " + version())
	wxEntry(os.Args)
}

func version() string {
	a := int(C.get_openicp_version_major())
	b := int(C.get_openicp_version_minor())
	c := int(C.get_openicp_version_patch())
	d := C.GoString(C.get_openicp_version_suffix())

	if d == "" {
		return fmt.Sprintf("%d.%d.%d", a, b, c)
	} else {
		return fmt.Sprintf("%d.%d.%d-%s", a, b, c, d)
	}
}
