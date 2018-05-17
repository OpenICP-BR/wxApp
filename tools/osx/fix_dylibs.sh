# #!/bin/bash

BUNDLE_DIR="`pwd`/bin/openicp.app/Contents"
BIN_DIR="${BUNDLE_DIR}/MacOS/"
LIB_DIR="${BUNDLE_DIR}/libs/"
BIN_FILE="${BIN_DIR}/openicp"
dylibbundler -od -b -x "${BIN_FILE}" -d "${LIB_DIR}"