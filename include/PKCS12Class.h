#pragma once
#include <ctime>
#include <openssl/pkcs12.h>
#include "Common.h"
#include "CertClass.h"

#define PKCS12_UNLOCK_ERR_FILE_NOT_LOADED 1
#define PKCS12_UNLOCK_ERR_WRONG_PASSWORD 2
#define PKCS12_UNLOCK_ERR_FAILED_TO_PARSE 3

#define PKCS12_SIGN_ERR_FAILED_TO_APPEND_SIGNATURE 1
#define PKCS12_SIGN_ERR_ALREADY_SIGNED_BY_SAME_PERSON 2
#define PKCS12_SIGN_ERR_INVALID_CERT 3
#define PKCS12_SIGN_ERR_INPUT_NOT_ALLOWED 4
#define PKCS12_SIGN_ERR_OUTPUT_NOT_ALLOWED 5
#define PKCS12_SIGN_ERR_FAILED_TO_LOAD_SIGNATURE 6

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
	int SignFile(wxString path);
	int SignFile(wxString path, wxString &err_msg);
	void SetPassword(wxString pass);
	bool SaveKeylessCert(wxString dir);
	bool SaveEncryptedP12(wxString dir);
	wxString NotBeforeString();
	wxString NotAfterString();
	wxString FingerPrintSHA256_HumanReadable();
	wxString FingerPrintSHA256_FileFriendly();
	~PKCS12Class();
};