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
	wxString fp_sha_256_human, fp_sha_256_fs;
public:
	CertClass();
	CertClass(X509 *new_cert);
	X509* _getX509();
	bool LoadPEMString(const char buf[]);
	bool LoadPEMFile(const char path[]);
	bool LoadCert(X509 *new_cert);
	bool SaveCert(wxString dir);
	wxString NiceName();
	wxString NotBeforeString();
	wxString NotAfterString();
	wxString FingerPrintSHA256_HumanReadable();
	wxString FingerPrintSHA256_FileFriendly();
	EntityInfoClass Subject, Issuer;
	~CertClass();
};

X509* PEM2X509(const char data[]);
X509* FILE2X509(const char path[]);
void print_openssl_err();