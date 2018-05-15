#pragma once
#include <ctime>
#include <openssl/pkcs12.h>
#include "Common.h"
#include "CertClass.h"

class PKCS12Class {
protected:
	PKCS12 *p12;
	STACK_OF(X509) *ca_stack = NULL;
	EVP_PKEY *key_pair;
	CertClass cert;
	wxString password;
public:
	time_t not_before_t, not_after_t;
	wxString not_before_str, not_after_str;
	CertClass Cert();
	EntityInfoClass Subject();
	EntityInfoClass Issuer();
	int LoadFromFile(wxString path);
	int Unlock(wxString pass);
	void SetPassword(wxString pass);
	bool SaveKeylessCert(wxString dir);
	bool SaveEncryptedP12(wxString dir);
	wxString NotBeforeString();
	wxString NotAfterString();
	wxString FingerPrintSHA256();
	~PKCS12Class();
};