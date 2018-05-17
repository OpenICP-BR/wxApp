#!/bin/bash

SRC_DIR=$1
RES_DIR=$2
mkdir -p "${RES_DIR}"
cp "${SRC_DIR}/res/ui.xrc" "${RES_DIR}"
cp "${SRC_DIR}/res/logo.svg" "${RES_DIR}"
mkdir -p "${RES_DIR}/CAs"
cp "${SRC_DIR}/res/icp-chain/"*.crt "${RES_DIR}/CAs"
cp "${SRC_DIR}/res/test-chain/intermediate-ca.crt" "${RES_DIR}/CAs"