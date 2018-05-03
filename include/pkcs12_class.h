#pragma once
#include <ctime>
#include <openssl/pkcs12.h>
#include "common.h"
#include "cert_class.h"

class PKCS12Class {
protected:
	PKCS12 *p12;
	STACK_OF(X509) *ca_stack = NULL;
	EVP_PKEY *key_pair;
	X509 *cert;
public:
	time_t not_before_t, not_after_t;
	wxString not_before_str, not_after_str;
	CertSubIssInfo subject, issuer;
	int LoadFromFile(wxString path);
	int Unlock(wxString pass);
	bool IsValid();
	~PKCS12Class();
};