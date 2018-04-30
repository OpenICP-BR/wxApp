#!/bin/bash

export NAME=$1
openssl pkcs12 -inkey intermediate/private/$NAME.pem -in intermediate/certs/$NAME.cert.pem -export -out $NAME.p12
