#!/bin/bash

git clone https://github.com/OpenICP-BR/libICP
cd libICP
make install-deps
make all
cd c-wrapper
make libICP.a libICP++.a
