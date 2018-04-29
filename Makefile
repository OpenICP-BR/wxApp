.PHONY: all run
export CGO_CPPFLAGS_ALLOW := .*
export CGO_CXXFLAGS_ALLOW := .*
export CGO_LDFLAGS_ALLOW := .*
export CGO_CFLAGS_ALLOW := .*

all: openicp

run: openicp
	bin/openicp

openicp: *.go bindata.go
	echo $$CGO_CFLAGS_ALLOW
	go build -o bin/openicp

bindata.go: openicp.xrc test-chain/*.crt
	go-bindata -o bindata.go openicp.xrc test-chain/*.crt