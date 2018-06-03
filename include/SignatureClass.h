#pragma once
#include "Common.h"
#include "CertClass.h"
#include <openssl/x509.h>
#include <openssl/pem.h>

class SignatureClass {
protected:
public:
	CertClass();
	~CertClass();
};