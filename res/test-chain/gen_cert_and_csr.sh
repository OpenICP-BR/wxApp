#!/bin/bash

export NAME=$1
openssl req -utf8 -config intermediate/openssl.cnf \
      -key intermediate/private/$NAME.pem \
      -new -sha256 -out intermediate/csr/$NAME.csr.pem
