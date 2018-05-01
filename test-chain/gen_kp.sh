#!/bin/bash

export NAME=$1
openssl genrsa -aes256 -out intermediate/private/$NAME.pem 2048
