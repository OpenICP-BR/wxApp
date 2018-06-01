#!/bin/bash

GREEN='\033[0;32m'
NC='\033[0m' # No Color

SRC_DIR=$1
DST_PATH=$2

echo cd $SRC_DIR
cd $SRC_DIR

echo tar czvf "${DST_PATH}/openicp.tar.gz" .
tar czvf "${DST_PATH}/openicp.tar.gz" .

echo -e "${GREEN}[ OK ] Generated openicp.tar.gz on ${DST_PATH} ${NC}"