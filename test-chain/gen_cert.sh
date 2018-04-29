#!/bin/bash

export NAME=$1
openssl req -config intermediate/openssl.cnf \
      -key intermediate/private/$NAME.pem \
      -new -sha256 -out intermediate/csr/$NAME.csr.pem
