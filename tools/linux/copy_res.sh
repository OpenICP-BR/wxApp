#!/bin/bash

GREEN='\033[0;32m'
NC='\033[0m' # No Color

SRC_DIR=$1
RES_DIR=$2

echo mkdir -p "${RES_DIR}"
mkdir -p "${RES_DIR}"

echo cp "${SRC_DIR}/res/ui.xrc" "${RES_DIR}"
cp "${SRC_DIR}/res/ui.xrc" "${RES_DIR}"

echo cp "${SRC_DIR}/res/logo.svg" "${RES_DIR}"
cp "${SRC_DIR}/res/logo.svg" "${RES_DIR}"

echo mkdir -p "${RES_DIR}/CAs"
mkdir -p "${RES_DIR}/CAs"

echo cp "${SRC_DIR}/res/icp-chain/*.crt" "${RES_DIR}/CAs"
cp "${SRC_DIR}/res/icp-chain/"*.crt "${RES_DIR}/CAs"

echo cp "${SRC_DIR}/res/test-chain/root.crt" "${RES_DIR}/CAs"
cp "${SRC_DIR}/res/test-chain/root.crt" "${RES_DIR}/CAs"

echo -e "${GREEN}[ OK ] Copied resource files${NC}"