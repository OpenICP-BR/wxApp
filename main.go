package main

import (
	"github.com/dontpanic92/wxGo/wx"
	"fmt"
)

func main() {
	wx.NewApp()
	fmt.Printf("%+v\n", wx.NewXmlResource().LoadAllFiles("ui.xrc"))
	f := wx.NewDialog(wx.NullWindow, -1, "Hello World")
	f.ShowModal()
	f.Destroy()
}
