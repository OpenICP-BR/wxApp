#!/bin/bash

SRC_DIR=$1
RES_DIR=$2
cp "${SRC_DIR}/res/ui.xrc" "${RES_DIR}"
cp "${SRC_DIR}/res/logo.icns" "${RES_DIR}"
mkdir "${RES_DIR}/CAs"
cp "${SRC_DIR}/res/icp-chain/"*.crt "${RES_DIR}/CAs"
cp "${SRC_DIR}/res/test-chain/intermediate-ca.crt" "${RES_DIR}/CAs"