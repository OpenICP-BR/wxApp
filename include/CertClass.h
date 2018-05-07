#pragma once
#include "Common.h"
#include "EntityInfoClass.h"
#include <openssl/x509.h>
#include <openssl/pem.h>

class CertClass {
protected:
	X509 *cert;
	time_t not_before, not_after;
	wxString not_before_str, not_after_str;
public:
	CertClass();
	bool LoadPEMString(const char buf[]);
	bool LoadPEMFile(const char path[]);
	bool LoadCert(X509 *new_cert);
	wxString NotBeforeString();
	wxString NotAfterString();
	EntityInfoClass Subject, Issuer;
	~CertClass();
};