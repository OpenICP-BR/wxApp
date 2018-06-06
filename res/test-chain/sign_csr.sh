#!/bin/bash

export NAME=$1
openssl ca -config intermediate/openssl.cnf  -days 375 -notext -md sha256 -in intermediate/csr/$NAME.csr.pem -out intermediate/certs/$NAME.cert.pem
