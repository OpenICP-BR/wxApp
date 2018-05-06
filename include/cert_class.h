#pragma once
#include "common.h"
#include "entity_class.h"
#include <openssl/x509.h>
#include <openssl/pem.h>

class CertClass {
protected:
	X509 *cert;
	bool parseCert();
public:
	CertClass();
	bool LoadPEMString(const char buf[]);
	bool LoadPEMFile(const char path[]);
	EntityInfoClass Subject, Issuer;
	~CertClass();
};