# #!/bin/bash

GREEN='\033[0;32m'
NC='\033[0m' # No Color

BUNDLE_DIR="`pwd`/bin/openicp.app/Contents"
BIN_DIR="${BUNDLE_DIR}/MacOS/"
LIB_DIR="${BUNDLE_DIR}/libs/"
BIN_FILE="${BIN_DIR}/openicp"
dylibbundler -od -b -x "${BIN_FILE}" -d "${LIB_DIR}"
echo -e "${GREEN}Fixed dylibs${NC}"