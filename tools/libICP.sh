#!/bin/bash

mkdir -pv $GOPATH/src/github.com/OpenICP-BR
go get github.com/OpenICP-BR/libICP
cd $GOPATH/src/github.com/OpenICP-BR/libICP
make install-deps
make all
cd c-wrapper
make libICP.a libICP++.a
