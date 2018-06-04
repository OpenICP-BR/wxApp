package main

package main

import (
	"github.com/mkideal/cli"
)

type commonArgT struct {
	CACache string `cli:"c,ca-cahce" usage:"sets the directory that holds the CAs"`
	AllowFakeICP bool `cli:"allow_fake_icp" usage:"used only for testing (do not touch this)"`
}

func main() {
	cli.Run(new(commonArgT), func(ctx *cli.Context) error {
		argv := ctx.Argv().(*commonArgT)
		ctx.String("Hello, %s!\n", argv.CACache)
		return nil
	})
}