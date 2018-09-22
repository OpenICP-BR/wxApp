#!/bin/bash

GREEN='\033[0;32m'
NC='\033[0m' # No Color

SRC_DIR=$1
RES_DIR=$2
mkdir -p "${RES_DIR}"
cp "${SRC_DIR}/res/ui.xrc" "${RES_DIR}"
cp "${SRC_DIR}/res/logo.icns" "${RES_DIR}"
mkdir -p "${RES_DIR}/CAs"
cp "${SRC_DIR}/res/icp-chain/"*.crt "${RES_DIR}/CAs"
cp "${SRC_DIR}/res/test-chain/root.crt" "${RES_DIR}/CAs"
echo -e "${GREEN}Copied resource files${NC}"